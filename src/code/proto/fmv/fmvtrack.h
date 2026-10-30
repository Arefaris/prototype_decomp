// The fight track that plays a movie and its action (RTTI proto::FMVTrack and proto::FMVAction). Unit 0x10577630 -
// 0x10578EA0 (no assert path; the file name is a guess). The class names are original, the members are guessed.
#ifndef PROTO_FMV_FMVTRACK_H
#define PROTO_FMV_FMVTRACK_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/trackfactory.h"

namespace proto
{
	class FMVTrack : public fight::Track
	{
	public:
		// 0x10578740
		FMVTrack();
		virtual ~FMVTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x10577AA0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetFilename(const char* value);
		bool SetUseFMVState(bool value);
		bool SetClearSubtitles(bool value);
		bool SetIsPreLoaded(bool value);
		bool SetUseBlackFades(bool value);
		bool SetFadeInOnEnter(bool value);
		bool SetStayFadedOnExit(bool value);
		bool SetFadeUpOnExit(bool value);
		bool SetDelayUninstall(bool value);
		bool SetUninstallDelayTime(float value);
		bool SetWhiteFadeTime(float value);
		bool SetTimer(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		char* filename;  // +0x10
		float timeBegin;  // +0x14
		float timeEnd;  // +0x18
		float timer;  // +0x1C
		float uninstallDelayTime;  // +0x20
		float whiteFadeTime;  // +0x24
		bool clearSubtitles;  // +0x28
		bool delayUninstall;  // +0x29
		bool fadeInOnEnter;  // +0x2A
		bool fadeUpOnExit;  // +0x2B
		bool isPreLoaded;  // +0x2C
		bool stayFadedOnExit;  // +0x2D
		bool useBlackFades;  // +0x2E
		bool useFMVState;  // +0x2F
	};

	extern fight::Property** gFMVTrackProperties;
	fight::TrackFactory* CreateFMVTrackFactory(const char* name);
	void RegisterFMVTrackFactory(fight::TrackRegistry* registry, const char* name);

	// The action of the movie track
	class FMVAction : public fight::Action
	{
	public:
		// 0x10577830
		FMVAction(FMVTrack* newTrack, core::IRefCount* newOwner);
		virtual ~FMVAction();

		// vftable slot 5 (0x10577AF0), 6 (0x105778E0) and 7 (0x10577C00)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		int unknown1C;
		core::Link<FMVTrack> link;  // +0x20
		core::IRefCount* owner;  // +0x2C
		int unknown30;
		bool unknown34;
		bool unknown35;
		int unknown38;
		float unknown3C;
	};
}

#endif
