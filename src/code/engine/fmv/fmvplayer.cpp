// The full-motion video player (see the header). Everything the player keeps is global and guarded by one critical
// section: the queue of requests, the decoder of the movie that plays and a few flags. Names are guesses.
#include "code/engine/fmv/fmvplayer.h"

#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/core/name.h"
#include "code/core/object.h"
#include "code/core/strings.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/fmv/fmvsubtitlemanager.h"
#include "code/engine/fmv/subtitleoptions.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/render/async/canvas.h"
#include "code/engine/scenariomessage.h"
#include "code/engine/system/streampackage.h"
#include "code/pure3d/context.h"
#include "code/pure3d/pddi.h"
#include <new>
#include <string.h>

namespace core
{
	unsigned int GetMilliseconds();
}

namespace container
{
	// What the list frees its nodes with (operator delete[])
	struct NodeAllocator
	{
		void Free(void* block)
		{
			delete[] (char*)block;
		}
	};

	// The queue of requests: nodes of a doubly linked list with the first and the last node and the count. The
	// member functions that link nodes are in another unit (0x1060E6C0, 0x1060E730, 0x1060E770, 0x1060E900)
	template<class T> struct DoubleListNode
	{
		explicit DoubleListNode(const T& newValue)
		{
			value = newValue;
		}

		DoubleListNode* next;
		DoubleListNode* previous;
		T value;
	};

	template<class T> class DoubleListIterator
	{
	public:
		typedef DoubleListNode<T> Node;

		DoubleListIterator(Node* newNode)
		{
			node = newNode;
		}
		T& operator*() const
		{
			return node->value;
		}
		bool operator!=(const DoubleListIterator& other) const
		{
			return node != other.node;
		}
		DoubleListIterator& operator++()
		{
			node = node->next;
			return *this;
		}
		DoubleListIterator operator++(int)
		{
			DoubleListIterator old = *this;
			node = node->next;
			return old;
		}

		Node* node;
	};

	template<class T> class DoubleList
	{
	public:
		typedef DoubleListNode<T> Node;
		typedef DoubleListIterator<T> Iterator;

		explicit DoubleList(NodeAllocator allocator)
		{
			Reset();
		}
		int Size() const
		{
			return count;
		}
		bool IsEmpty() const
		{
			return count == 0;
		}
		Iterator Begin() const
		{
			return Iterator(head);
		}
		Iterator Insert(Iterator position, const T& value)
		{
			Node* node = (Node*)new char[sizeof(Node)];
			if (node != 0)
			{
				node->value = value;
				Insert(position.node, node);
			}
			return Iterator(node);
		}
		void PushBack(const T& value)
		{
			Node* node = (Node*)new char[sizeof(Node)];
			if (node != 0)
			{
				node->value = value;
				Insert(0, node);
			}
		}
		void PopFront()
		{
			Node* first = head;
			Remove(first);
			delete[] (char*)first;
		}
		void Clear()
		{
			Node* node = head;
			while (node != 0)
			{
				Node* current = node;
				node = node->next;
				delete[] (char*)current;
			}
			Reset();
		}

		void Reset();
		void Remove(Node* node);
		void Insert(Node* position, Node* node);

		Node* head;
		Node* tail;
		int count;
	};
}

namespace engine
{
	// The decoder (0x254 bytes, another unit; its constructor is 0x105A0FB0)
	class MoviePlayer
	{
	public:
		MoviePlayer();
		virtual void Slot0();
		virtual void Slot1();
		virtual void Destroy();

		void Unknown1059F380(int value);
		bool Unknown1059F3A0();
		bool Unknown1059F3B0();
		void Unknown1059F3E0(float volume);
		void Unknown1059F4C0(bool value);
		void Unknown1059F4D0(float left, float top, float right, float bottom);
		unsigned int Unknown1059F510();
		float Unknown1059F530();
		bool Unknown1059FD20();
		void Unknown1059FD40();
		void Unknown105A0170();
		void Unknown105A01B0();
		void Unknown105A0330();
		void Unknown105A0D80(const char* path, int unknown, int a, int b, float* c);
		bool Unknown105A0E30();
	};

	// A movie that is asked for (0x34 bytes)
	struct FmvRequest
	{
		char* path;                      // +0x00: a copy
		int id;                          // +0x04
		StreamPackage* package;          // +0x08: the package of the subtitles
		FmvSubtitleManager* subtitles;   // +0x0C
		bool unknown10;
		bool unknown11;
		bool unknown12;
		bool unknown13;
		int state;                       // +0x14: 1 asked for ... 10 over
		bool unknown18;
		bool unknown19;
		float left;                      // +0x1C: the part of the screen the movie fills
		float top;
		float right;
		float bottom;
		float time;                      // +0x2C: the seconds it has run
		unsigned int startMilliseconds;  // +0x30
	};

	// Which output channel each of the movie's tracks goes to (36 bytes)
	struct ChannelMap
	{
		struct Entry
		{
			short track;
			short channels;
		};

		// FUNCTION: ENGINE 0x1082EC10
		ChannelMap()
		{
			count = 0;
			memset(entries, 0, sizeof(entries));
		}

		int count;
		Entry entries[8];
	};

	// The list's inline members, as the engine's unit keeps them
	template struct container::DoubleListNode<FmvRequest>;
	template class container::DoubleListIterator<FmvRequest>;
	template class container::DoubleList<FmvRequest>;

	// Free functions of other units
	int Unknown1059F080();
	void Unknown1059F090(int value);
	void Unknown1059F060();
	void Unknown1059F020(int id, void (*callback)());
	void Unknown108A0830(int a, int b);
	void Unknown108A0890();
	void Unknown1085F920(bool value);
	int Unknown10A9B0B0();
	void Unknown104B18C0();
	void Unknown104B1880();
	void Unknown108831C0();


	// The names of the audio settings the volume is made of, and the channel the end message goes to (all made by
	// their units' initialisers)
	extern core::Name<core::CaseSensitiveKey> gUserMixName;
	extern core::Name<core::CaseSensitiveKey> gDialogName;
	extern core::Name<core::CaseSensitiveKey> gFmvName;
	extern core::Name<core::CaseSensitiveKey> gMasterName;
	extern content::ObjectName gFmvNoSlotGroup;
	extern container::DoubleList<FmvRequest> gRequests;
	extern MessageListeners gMovieListeners;

	// The unit's globals
	unsigned char gMovieLock[24];
	MoviePlayer* gMovie;
	MoviePlayer* gPreloadedMovie;
	unsigned int gSkipTime;
	int gMovieFrame;
	float gMovieTime;
	bool gSkipMovies;
	bool gSkipRequested;
	bool gStopRequested;
	bool gNoCanvas;
	bool gRestoreCanvas;
	bool gInitialised;
	ChannelMap gChannelMap;

	bool gSavedSubtitleFlag = true;
	bool gMovieDone = true;
	float gMovieVolume = 1.0f;
	int gSavedAudio = -1;
	float gMovieScale = 1.0f;
	int gUseChannelMap;
	ChannelMap* gChannelMapPointer;
	int gStartDelay = 3;

	// FUNCTION: ENGINE 0x1082ECA0
	// Copies the movie's name into a buffer of size characters
	static void CopyPath(char* buffer, const char* path, unsigned int size)
	{
		unsigned int length = 0;
		core::StrNCpy(buffer, path, size, &length);
		gMovieScale = 1.0f;
	}

	// FUNCTION: ENGINE 0x1082ECD0
	// The channels of the tracks (five of them)
	static ChannelMap MakeChannelMap()
	{
		ChannelMap map;
		map.count = 5;
		map.entries[0].track = 0;
		map.entries[0].channels = 3;
		map.entries[1].track = 1;
		map.entries[1].channels = 4;
		map.entries[2].track = 2;
		map.entries[2].channels = 8;
		map.entries[3].track = 3;
		map.entries[3].channels = 0xC0;
		map.entries[4].track = 4;
		map.entries[4].channels = 0x30;
		return map;
	}

	// FUNCTION: ENGINE 0x1082ED30
	// Makes the decoder of the request's movie
	static MoviePlayer* CreateMovie(FmvRequest* request)
	{
		char path[260];
		core::gObjectHeap = 1;
		void* memory = core::HeapAlloc(1, 0x254);
		MoviePlayer* movie = memory != 0 ? new (memory) MoviePlayer() : 0;
		movie->Unknown1059F4D0(request->left, request->top, request->right, request->bottom);
		CopyPath(path, request->path, 0x101);
		movie->Unknown105A0D80(path, Unknown10A9B0B0(), 0, 0, &gMovieScale);
		return movie;
	}

	// FUNCTION: ENGINE 0x1082EDC0
	// The audio state while a movie plays: the game's is saved and its volume set to 0
	static void SaveAudioState()
	{
		gSavedAudio = Unknown1059F080();
		Unknown1059F090(0);
	}

	// FUNCTION: ENGINE 0x1082EDE0
	static void RestoreAudioState()
	{
		Unknown1059F090(gSavedAudio);
	}

	// FUNCTION: ENGINE 0x1082EDF0
	// Lets go of the request's subtitles and package
	static void ReleaseRequest(FmvRequest* request)
	{
		if (request->subtitles != 0)
		{
			request->subtitles->Release();
			request->subtitles = 0;
		}
		if (request->package != 0)
		{
			request->package->Unload(0, false);
		}
	}

	// FUNCTION: ENGINE 0x1082EE20
	// Ends the request when a skip or a stop was asked for
	static void CheckSkip(FmvRequest* request)
	{
		if (!gStopRequested)
		{
			if (!gSkipRequested)
			{
				return;
			}
			if (!gNoCanvas && gMovie->Unknown1059F510() < 60)
			{
				if (gSkipRequested)
				{
					gSkipRequested = false;
				}
				return;
			}
		}
		request->state = 6;
		gStopRequested = false;
		gSkipTime = 0;
		gSkipRequested = false;
	}

	// FUNCTION: ENGINE 0x1082EE80
	bool SetSkipMovies(bool skip)
	{
		bool old = gSkipMovies;
		gSkipMovies = skip;
		return old;
	}

	// FUNCTION: ENGINE 0x1082EE90
	void SetMovieVolume(float volume)
	{
		core::CriticalSectionEnter(gMovieLock);
		gMovieVolume = volume;
		core::CriticalSectionLeave(gMovieLock);
	}

	// FUNCTION: ENGINE 0x1082EEC0
	void UpdateMovieVolume()
	{
		float a = gAudioEmitterSystem->Unknown10877E60(&gUserMixName, &gDialogName);
		float b = gAudioEmitterSystem->Unknown10877850(&gFmvName);
		float c = gAudioEmitterSystem->Unknown10877850(&gMasterName);
		SetMovieVolume(c * b * a);
	}

	// FUNCTION: ENGINE 0x1082EF20
	void FadeMovieOut()
	{
		core::CriticalSectionEnter(gMovieLock);
		if (gMovie != 0)
		{
			gMovie->Unknown1059F380(250);
		}
		core::CriticalSectionLeave(gMovieLock);
	}

	// FUNCTION: ENGINE 0x1082EF50
	void ResumeMovie()
	{
		core::CriticalSectionEnter(gMovieLock);
		if (gMovie != 0)
		{
			gMovie->Unknown1059FD40();
		}
		core::CriticalSectionLeave(gMovieLock);
	}

	// FUNCTION: ENGINE 0x1082EF80
	bool IsMovieUnknown()
	{
		core::CriticalSectionEnter(gMovieLock);
		bool result = false;
		if (gMovie != 0)
		{
			result = gMovie->Unknown1059F3B0();
		}
		core::CriticalSectionLeave(gMovieLock);
		return result;
	}

	// FUNCTION: ENGINE 0x1082EFC0
	void ReleasePreloadedMovie()
	{
		core::CriticalSectionEnter(gMovieLock);
		if (gPreloadedMovie != 0)
		{
			gPreloadedMovie->Unknown105A0170();
			gPreloadedMovie->Destroy();
			gPreloadedMovie = 0;
		}
		core::CriticalSectionLeave(gMovieLock);
	}

	// FUNCTION: ENGINE 0x1082F020
	bool IsMovieLoaded()
	{
		bool result = false;
		if (!gInitialised)
		{
			return false;
		}
		core::CriticalSectionEnter(gMovieLock);
		if (gMovie != 0)
		{
			result = gMovie->Unknown105A0E30();
		}
		core::CriticalSectionLeave(gMovieLock);
		return result;
	}

	// FUNCTION: ENGINE 0x1082F060
	bool IsMovieDone()
	{
		return gMovieDone;
	}

	// FUNCTION: ENGINE 0x1082F070
	bool SkipMovie()
	{
		if (gMovie != 0 && !gSkipRequested)
		{
			gSkipRequested = true;
			gSkipTime = core::GetMilliseconds();
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1082F0A0
	void StopMovie()
	{
		if (gMovie != 0 && !gStopRequested)
		{
			gStopRequested = true;
		}
	}

	// FUNCTION: ENGINE 0x1082F0C0
	void SetMovieNoCanvas(bool value)
	{
		gNoCanvas = value;
	}

	// FUNCTION: ENGINE 0x1082F190
	// The request is over: the canvas and the end message
	static void FinishRequest(FmvRequest* request)
	{
		if (request->unknown13 && !gNoCanvas)
		{
			Unknown104B18C0();
			render::QueueCanvas108BCA80(false, 0.0f, true, 0.0f, false);
			if (!request->unknown11)
			{
				Unknown104B1880();
			}
		}
		if (!request->unknown12)
		{
			ScenarioNISEndMessage message(core::Name<core::CaseSensitiveKey>("FMV", 1));
			SendMessage(&message, &gMovieListeners);
		}
		char* path = request->path;
		gSkipRequested = false;
		gStopRequested = false;
		if (path != 0)
		{
			delete[] path;
			request->path = 0;
		}
	}

	// FUNCTION: ENGINE 0x1082F240
	// Gets the subtitles of the request ready; true when there is nothing more to wait for
	static bool PrepareSubtitles(FmvRequest* request)
	{
		bool ready = true;
		request->subtitles = 0;
		if (request->package != 0)
		{
			if (request->package->requestCount <= 0)
			{
				content::ObjectName groupName("FMVSubTitleSlotGroup", 1);
				StreamSlotGroup* group = StreamManager::FindSlotGroup(groupName);
				gSavedSubtitleFlag = group->unknown68;
				group->unknown68 = !request->unknown12;
				request->package->Load(0, 0xFFFF, gFmvNoSlotGroup, false);
				ready = false;
			}
			else if (request->package->GetState() == 5)
			{
				if (request->package->GetState() == 5)
				{
					request->subtitles = Unknown108C1130(request->path, request->package);
					request->unknown10 = !gSubtitleOptions->unknown1E;
					gSubtitleOptions->Unknown10876EF0(true);
				}
			}
			else
			{
				ready = false;
			}
		}
		return ready;
	}

	// FUNCTION: ENGINE 0x1082F300
	// EQUIVALENT: register allocation and scheduling of five spots (the decoder pointer's register, a push before the this load, two stores, the pddi calls), 53 percent as laid out
	void UpdateMovies()
	{
		if (gInitialised)
		{
			core::CriticalSectionEnter(gMovieLock);
			container::DoubleList<FmvRequest>::Node* node = gRequests.head;
			if (gInitialised && gRequests.count != 0)
			{
				FmvRequest* request = &node->value;
				bool updated = false;
				if (request->state == 3)
				{
					MoviePlayer* movie;
					gMovie = movie = gPreloadedMovie;
					if (movie == 0)
					{
						gMovie = movie = CreateMovie(request);
					}
					request->state = movie != 0 ? 4 : 6;
				}
				if (request->state == 4)
				{
					if (!gMovie->Unknown105A0E30())
					{
						if (gMovie->Unknown1059FD20())
						{
							gMovie->Unknown1059F4C0(request->unknown19);
							gMovie->Unknown1059F3E0(gMovieVolume);
							gMovie->Unknown1059FD40();
							request->state = 5;
							gMovieDone = false;
						}
						else
						{
							request->state = 6;
						}
						gMovieFrame = 0;
						gMovieTime = 0.0f;
						gRestoreCanvas = true;
					}
				}
				if (request->state == 5)
				{
					CheckSkip(request);
					gMovie->Unknown1059F3E0(gMovieVolume);
					gMovie->Unknown105A01B0();
					gMovieFrame = gMovie->Unknown1059F510();
					gMovieTime = gMovie->Unknown1059F530();
					request->time = (float)(core::GetMilliseconds() - request->startMilliseconds) * 0.001f +
						request->time;
					request->startMilliseconds = core::GetMilliseconds();
					if (gMovie->Unknown1059F3A0())
					{
						request->state = 6;
					}
					else
					{
						gMovie->Unknown105A0330();
						updated = true;
					}
				}
				if (request->state == 9)
				{
					if (gMovie != 0)
					{
						gMovie->Destroy();
						gMovie = 0;
					}
					gPreloadedMovie = 0;
					request->state = 10;
				}
				if (!updated)
				{
					int color;
					pure3d::pddi->GetViewUnknown4(&color);
					pure3d::pddi->SetViewUnknown4(0xFF000000);
					pure3d::pddi->Clear(-1);
					pure3d::pddi->SetViewUnknown4(color);
				}
			}
			core::CriticalSectionLeave(gMovieLock);
		}
	}

	// FUNCTION: ENGINE 0x1082F530
	bool IsMoviePlaying()
	{
		if (!gInitialised)
		{
			return false;
		}
		core::CriticalSectionEnter(gMovieLock);
		int count = gRequests.count;
		core::CriticalSectionLeave(gMovieLock);
		if (count != 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1082F570
	int GetQueuedMovieCount()
	{
		core::CriticalSectionEnter(gMovieLock);
		int count = gRequests.count;
		core::CriticalSectionLeave(gMovieLock);
		return count;
	}

	// FUNCTION: ENGINE 0x1082F5D0
	void ShutdownMovies()
	{
		core::CriticalSectionEnter(gMovieLock);
		gInitialised = false;
		core::CriticalSectionLeave(gMovieLock);
		core::CriticalSectionDelete(gMovieLock);
		if (gMovie != 0)
		{
			gMovie->Destroy();
			gMovie = 0;
			gPreloadedMovie = 0;
		}
		LuaScriptManager* manager = GetScriptManager();
		manager->RemoveFunction("fmv_Skip");
		manager = GetScriptManager();
		manager->RemoveFunction("fmv_IsPlaying");
		Unknown1059F060();
		Unknown108A0890();
	}

	// FUNCTION: ENGINE 0x1082F6D0
	void InitMovies()
	{
		gSkipMovies = HasCommandLineOption("SkipMovies");
		Unknown108A0830(11, 0);
		Unknown1059F020(0x7D, Unknown108831C0);
		GetScriptManager()->Register("fmv_Skip", SkipMovie);
		GetScriptManager()->Register("fmv_Stop", StopMovie);
		GetScriptManager()->Register("fmv_IsPlaying", IsMoviePlaying);
		GetScriptManager()->Register("fmv_IsLoaded", IsMovieLoaded);
		core::CriticalSectionInit(gMovieLock);
		gChannelMap = MakeChannelMap();
		gChannelMapPointer = &gChannelMap;
		gUseChannelMap = 1;
		gInitialised = true;
	}

	// FUNCTION: ENGINE 0x1082F7A0
	// EQUIVALENT: the first list node's register in the pop, 89 percent
	void UpdateMovieState()
	{
		core::CriticalSectionEnter(gMovieLock);
		if (gRequests.count != 0)
		{
			FmvRequest* request = &gRequests.head->value;
			if (request->state == 1)
			{
				gSkipRequested = false;
				gStopRequested = false;
				Unknown1085F920(false);
				if (request->id != -1 || gStartDelay == 0)
				{
					gStartDelay = 3;
					SaveAudioState();
					request->state = 2;
				}
				gStartDelay--;
			}
			if (request->state == 2)
			{
				if (PrepareSubtitles(request))
				{
					request->state = 3;
				}
			}
			if (request->state == 5)
			{
				UpdateMovieVolume();
				if (request->subtitles != 0)
				{
					request->subtitles->Update(gMovieTime);
				}
			}
			if (request->state == 6)
			{
				FinishRequest(request);
				ReleaseRequest(request);
				gNoCanvas = false;
				request->state = 7;
			}
			if (request->state == 7)
			{
				if (request->package == 0)
				{
					request->state = 9;
				}
				else if (request->package->IsUnloaded())
				{
					request->package = 0;
					content::ObjectName groupName("FMVSubTitleSlotGroup", 1);
					StreamManager::FindSlotGroup(groupName)->unknown68 = gSavedSubtitleFlag;
					request->state = 9;
				}
			}
			if (request->state == 8)
			{
				request->state = 9;
			}
			if (request->state == 10)
			{
				RestoreAudioState();
				Unknown1085F920(true);
				gRequests.PopFront();
				gMovieDone = true;
			}
			if (gRestoreCanvas && !gNoCanvas)
			{
				Unknown104B1880();
				gRestoreCanvas = false;
			}
		}
		core::CriticalSectionLeave(gMovieLock);
	}

	// FUNCTION: ENGINE 0x1082F990
	void PlayMovie(const char* path, bool unknown12, int id, int unused, bool unknown13, bool unknown11,
		int unknown18, bool unknown19)
	{
		UpdateMovieVolume();
		if (gPreloadedMovie == 0 && !gSkipMovies)
		{
			FmvRequest request;
			request.left = 0.0f;
			request.top = 0.0f;
			request.unknown10 = false;
			request.right = 1.0f;
			request.bottom = 1.0f;
			request.id = id;
			request.package = Unknown108C1210(path);
			request.subtitles = 0;
			request.startMilliseconds = core::GetMilliseconds();
			request.unknown11 = unknown11;
			request.unknown12 = unknown12;
			request.time = 0.0f;
			request.state = 1;
			request.unknown13 = unknown13;
			request.unknown18 = unknown18 == 0;
			request.unknown19 = unknown19;
			request.path = new char[core::StrLen(path) + 1];
			core::StrCpy(request.path, path);
			core::CriticalSectionEnter(gMovieLock);
			gRequests.PushBack(request);
			core::CriticalSectionLeave(gMovieLock);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1082F0D0
// FUNCTION: ENGINE 0x1082F0E0
// FUNCTION: ENGINE 0x1082F0F0
// FUNCTION: ENGINE 0x1082F100
// FUNCTION: ENGINE 0x1082F110
// FUNCTION: ENGINE 0x1082F130
// FUNCTION: ENGINE 0x1082F150
// FUNCTION: ENGINE 0x1082F160
// FUNCTION: ENGINE 0x1082F5C0
// FUNCTION: ENGINE 0x1082F650
// FUNCTION: ENGINE 0x1082F680
// FUNCTION: ENGINE 0x1082F6C0
// FUNCTION: ENGINE 0x1082F920
// FUNCTION: ENGINE 0x1082F960
