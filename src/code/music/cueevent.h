// The cue events of the music library (RTTI: music::CueEvent, music::CueEventDerived<T> and the events
// CueEventSetCurrentCuePlayer, CueEventSetCurrentCell, CueEventSetCurrentCue and CueEventSync): small messages that
// are read and written in binary form through the reflection of their own class. Every event class derives from
// CueEventDerived<itself>, which answers slots 3 and 4 with the description of that class.
#ifndef MUSIC_CUEEVENT_H
#define MUSIC_CUEEVENT_H

#include "code/music/cell.h"
#include "code/music/cue.h"
#include "code/music/cellplayer.h"
#include "code/music/time.h"
#include "code/om/allocation.h"
#include "code/om/bool32.h"
#include "code/om/metaclass.h"

namespace music
{
	class CueEvent
	{
	public:
		// Inlined by the derived classes (the engine's own copies are 0x105D2880 and 0x105D2A60)
		CueEvent()
		{
		}
		virtual ~CueEvent()
		{
		}
		// Slots 1 and 2 (0x105D28B0 / 0x105D28D0): read and write the event through its description
		virtual void Read(om::BinaryStream* stream);
		virtual void Write(om::BinaryStream* stream);
		// Slots 3 and 4 (0x105D2900 / 0x105D28F0): the description of the event's class, none here
		virtual om::MetaClassBase* GetMetaClassForWrite();
		virtual om::MetaClassBase* GetMetaClassForRead();
		OM_ALLOCATION(CueEvent);

		int unknown4;
	};

	template<class T> class CueEventDerived : public CueEvent
	{
	public:
		CueEventDerived()
		{
		}
		virtual ~CueEventDerived()
		{
		}
		virtual om::MetaClassBase* GetMetaClassForWrite();
		virtual om::MetaClassBase* GetMetaClassForRead();
		OM_ALLOCATION(CueEventDerived);
	};

	class CueEventSetCurrentCuePlayer : public CueEventDerived<CueEventSetCurrentCuePlayer>
	{
	public:
		CueEventSetCurrentCuePlayer()
		{
		}
		// 0x105D30B0 / 0x105D30F0
		CueEventSetCurrentCuePlayer(const om::ClassName& newPlayer);
		virtual ~CueEventSetCurrentCuePlayer();
		const om::ClassName& GetCuePlayerName() const;
		void SetCuePlayerName(const om::ClassName& newPlayer);
		OM_ALLOCATION(CueEventSetCurrentCuePlayer);

		om::ClassName player;  // 8
	};

	class CueEventSetCurrentCell : public CueEventDerived<CueEventSetCurrentCell>
	{
	public:
		CueEventSetCurrentCell()
		{
		}
		// 0x105D3180 / 0x105D31C0
		CueEventSetCurrentCell(unsigned int newFirst, unsigned int newSecond);
		virtual ~CueEventSetCurrentCell();
		const unsigned int& GetFirst() const;
		const unsigned int& GetSecond() const;
		// 0x105D2A90 / 0x105D2AA0
		void SetFirst(const unsigned int& newFirst);
		void SetSecond(const unsigned int& newSecond);
		OM_ALLOCATION(CueEventSetCurrentCell);

		unsigned int first;  // 8
		unsigned int second;  // 0xC
	};

	class CueEventSetCurrentCue : public CueEventDerived<CueEventSetCurrentCue>
	{
	public:
		CueEventSetCurrentCue()
		{
		}
		// 0x105D5550 / 0x105D5590
		CueEventSetCurrentCue(const om::ClassName& newCue);
		virtual ~CueEventSetCurrentCue();
		const om::ClassName& GetCueName() const;
		void SetCueName(const om::ClassName& newCue);
		OM_ALLOCATION(CueEventSetCurrentCue);

		om::ClassName cue;  // 8
	};

	class CueEventSync : public CueEventDerived<CueEventSync>
	{
	public:
		CueEventSync()
		{
		}
		// 0x105D5640 / 0x105D5680
		CueEventSync(const CueEventSetCurrentCue& event);
		virtual ~CueEventSync();
		unsigned __int64 GetBarrierAsUint64() const;
		void SetBarrierAsUint64(unsigned __int64 newBarrier);
		OM_ALLOCATION(CueEventSync);

		om::ClassName cue;  // 8
	};

	// The events below are plain records: their members are read and written through the reflection of the class
	class CueEventNewCuePlayer : public CueEventDerived<CueEventNewCuePlayer>
	{
	public:
		CueEventNewCuePlayer()
		{
		}
		virtual ~CueEventNewCuePlayer()
		{
		}
		const om::ClassName& GetCuePlayerName() const;
		void SetCuePlayerName(const om::ClassName& newCuePlayerName);
		const om::ClassName& GetCueName() const;
		void SetCueName(const om::ClassName& newCueName);
		OM_ALLOCATION(CueEventNewCuePlayer);

		om::ClassName cuePlayerName;  // 8
		om::ClassName cueName;  // 0x10
	};

	class CueEventDestroyCuePlayer : public CueEventDerived<CueEventDestroyCuePlayer>
	{
	public:
		CueEventDestroyCuePlayer()
		{
		}
		virtual ~CueEventDestroyCuePlayer()
		{
		}
		const om::ClassName& GetCuePlayerName() const;
		void SetCuePlayerName(const om::ClassName& newCuePlayerName);
		OM_ALLOCATION(CueEventDestroyCuePlayer);

		om::ClassName cuePlayerName;  // 8
	};

	class CueEventSetPartName : public CueEventDerived<CueEventSetPartName>
	{
	public:
		CueEventSetPartName()
		{
		}
		virtual ~CueEventSetPartName()
		{
		}
		const om::ClassName& GetPartName() const;
		void SetPartName(const om::ClassName& newPartName);
		OM_ALLOCATION(CueEventSetPartName);

		om::ClassName partName;  // 8
	};

	class CueEventSetLayerName : public CueEventDerived<CueEventSetLayerName>
	{
	public:
		CueEventSetLayerName()
		{
		}
		virtual ~CueEventSetLayerName()
		{
		}
		const om::ClassName& GetLayerName() const;
		void SetLayerName(const om::ClassName& newLayerName);
		OM_ALLOCATION(CueEventSetLayerName);

		om::ClassName layerName;  // 8
	};

	class CueEventMoveCell : public CueEventDerived<CueEventMoveCell>
	{
	public:
		CueEventMoveCell()
		{
		}
		virtual ~CueEventMoveCell()
		{
		}
		const unsigned int& GetDestinationPartIndex() const;
		void SetDestinationPartIndex(const unsigned int& newDestinationPartIndex);
		const unsigned int& GetDestinationLayerIndex() const;
		void SetDestinationLayerIndex(const unsigned int& newDestinationLayerIndex);
		OM_ALLOCATION(CueEventMoveCell);

		unsigned int destinationPartIndex;  // 8
		unsigned int destinationLayerIndex;  // 0xC
	};

	class CueEventMovePart : public CueEventDerived<CueEventMovePart>
	{
	public:
		CueEventMovePart()
		{
		}
		virtual ~CueEventMovePart()
		{
		}
		const unsigned int& GetDestinationPartIndex() const;
		void SetDestinationPartIndex(const unsigned int& newDestinationPartIndex);
		const unsigned int& GetSourcePartIndex() const;
		void SetSourcePartIndex(const unsigned int& newSourcePartIndex);
		OM_ALLOCATION(CueEventMovePart);

		unsigned int destinationPartIndex;  // 8
		unsigned int sourcePartIndex;  // 0xC
	};

	class CueEventCellPlayerState : public CueEventDerived<CueEventCellPlayerState>
	{
	public:
		CueEventCellPlayerState()
		{
		}
		// 0x105EBF50: takes the state of a player
		CueEventCellPlayerState(const CellPlayer& player);
		virtual ~CueEventCellPlayerState()
		{
		}
		const CellPlayer::State& GetState() const;
		void SetState(const CellPlayer::State& newState);
		OM_ALLOCATION(CueEventCellPlayerState);

		CellPlayer::State state;  // 8
	};

	class CueEventSetCellType : public CueEventDerived<CueEventSetCellType>
	{
	public:
		CueEventSetCellType()
		{
		}
		virtual ~CueEventSetCellType()
		{
		}
		const om::ClassName& GetCellTypeName() const;
		void SetCellTypeName(const om::ClassName& newCellTypeName);
		const om::ClassName& GetCellInstanceName() const;
		void SetCellInstanceName(const om::ClassName& newCellInstanceName);
		OM_ALLOCATION(CueEventSetCellType);

		om::ClassName cellTypeName;  // 8
		om::ClassName cellInstanceName;  // 0x10
	};

	class CueEventSetBPM : public CueEventDerived<CueEventSetBPM>
	{
	public:
		CueEventSetBPM()
		{
		}
		// 0x105EBFA0
		CueEventSetBPM(float newBPM);
		virtual ~CueEventSetBPM()
		{
		}
		const float& GetBPM() const;
		void SetBPM(const float& newBPM);
		OM_ALLOCATION(CueEventSetBPM);

		float bpm;  // 8
	};

	class CueEventCommand : public CueEventDerived<CueEventCommand>
	{
	public:
		CueEventCommand() :
			name()
		{
		}
		virtual ~CueEventCommand()
		{
		}
		const om::ClassName& GetName() const;
		void SetName(const om::ClassName& newName);
		const unsigned int& GetEventType() const;
		void SetEventType(const unsigned int& newEventType);
		OM_ALLOCATION(CueEventCommand);

		om::ClassName name;  // 8
		unsigned int eventType;  // 0x10
	};

	class CueEventSetFade : public CueEventDerived<CueEventSetFade>
	{
	public:
		CueEventSetFade()
		{
		}
		// 0x105EBFF0: the fade is a fade out when the kind is 1
		CueEventSetFade(Fade newFade, int newKind);
		virtual ~CueEventSetFade()
		{
		}
		const Fade& GetFade() const;
		void SetFade(const Fade& newFade);
		const om::Bool32& GetIsFadeOut() const;
		void SetIsFadeOut(const om::Bool32& newIsFadeOut);
		OM_ALLOCATION(CueEventSetFade);

		Fade fade;  // 8
		om::Bool32 isFadeOut;  // 0x30
	};

	// The cue state and cell state events carry a reference to the cue or the cell they describe and read and write
	// themselves by name
	class CueEventCueState : public CueEventDerived<CueEventCueState>
	{
	public:
		CueEventCueState() :
			cue(0)
		{
		}
		virtual ~CueEventCueState()
		{
			Cue* old = cue;
			if (old != 0)
			{
				cue = 0;
				if (om::ThreadSafeRefCount::Release(&old->count) == 0 && old != 0)
				{
					delete old;
				}
			}
		}
		// Slots 1 and 2 (0x105F5FB0 / 0x105F1960)
		virtual void Read(om::BinaryStream* stream);
		virtual void Write(om::BinaryStream* stream);
		OM_ALLOCATION(CueEventCueState);

		Cue* cue;  // 8
	};

	class CueEventCellState : public CueEventDerived<CueEventCellState>
	{
	public:
		CueEventCellState() :
			cell(0)
		{
		}
		virtual ~CueEventCellState()
		{
		}
		// Slots 1 and 2 (0x105F6820 / 0x105F68A0)
		virtual void Read(om::BinaryStream* stream);
		virtual void Write(om::BinaryStream* stream);
		OM_ALLOCATION(CueEventCellState);

		om::ClassName unknown8;
		Cell* cell;  // 0x10
	};

	template<class T> om::MetaClassBase* CueEventDerived<T>::GetMetaClassForWrite()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<T>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(T));
		}
		return static_cast<om::MetaClassBase*>(cache);
	}

	template<class T> om::MetaClassBase* CueEventDerived<T>::GetMetaClassForRead()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<T>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(T));
		}
		return static_cast<om::MetaClassBase*>(cache);
	}

	template<class T> const char* CueEventDerived<T>::AllocationTag()
	{
		return "";
	}
}

#endif
