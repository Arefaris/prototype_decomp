// The fight track that sets one of the smart hint manager's timers (RTTI proto::SmartHintSetTimerTrack and
// proto::SmartHintSetTimerAction): the timer to set and the value to set it to. Unit 0x1059E9A0 - 0x1059EF80 (no
// assert path; the file name is a guess). The class names are original, the members are guessed.
#ifndef PROTO_SMARTHINT_SMARTHINTSETTIMER_H
#define PROTO_SMARTHINT_SMARTHINTSETTIMER_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/smarthint/smarthintmanager.h"

namespace proto
{
	class SmartHintSetTimerTrack : public fight::Track
	{
	public:
		// 0x1059EBF0
		SmartHintSetTimerTrack();
		virtual ~SmartHintSetTimerTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimer(int newTimer);
		bool SetValue(float newValue);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float value;  // +0x10
		int timer;  // +0x14
	};

	extern fight::Property** gSmartHintSetTimerTrackProperties;
	fight::TrackFactory* CreateSmartHintSetTimerTrackFactory(const char* name);
	void RegisterSmartHintSetTimerTrackFactory(fight::TrackRegistry* registry, const char* name);

	// The action the track makes: sets the timer when it runs
	class SmartHintSetTimerAction : public fight::Action
	{
	public:
		// 0x1059EA40
		SmartHintSetTimerAction(SmartHintSetTimerTrack* newTrack, engine::GameObjectHandle newTarget);
		virtual ~SmartHintSetTimerAction();

		// vftable slot 5
		virtual bool Slot5(int arg, float value);

		engine::GameObjectHandle target;  // +0x1C
		core::Link<SmartHintSetTimerTrack> link;  // +0x20
	};
}

#endif
