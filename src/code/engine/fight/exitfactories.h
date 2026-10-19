// The factory makers of three fight nodes whose classes belong to other units: the exit track (RTTI:
// engine::ExitTrack) and the message and print message conditions (engine::MessageCondition /
// engine::PrintMessageCondition). The unit runs 0x108123A0 - 0x108127E0 (no assert path; file name guessed); the
// classes keep their constructors, property lists and slot bodies in 0x108B6C40 - 0x108B71E0, so only what the
// factory templates touch is declared here: the sizes, the constructors and the property list functions.
#ifndef ENGINE_FIGHT_EXITFACTORIES_H
#define ENGINE_FIGHT_EXITFACTORIES_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	class ExitTrack : public fight::Track
	{
	public:
		// 0x108B6C60
		ExitTrack();
		virtual ~ExitTrack();
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// ClearProperties 0x108B6C50, RegisterProperties 0x108B6DC0
		static void RegisterProperties();
		static void ClearProperties();

		int unknown10[3];
	};

	class MessageCondition : public fight::Condition
	{
	public:
		// 0x108B6EA0
		MessageCondition();
		virtual ~MessageCondition();
		virtual fight::Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		// ClearProperties 0x108B6F10, RegisterProperties 0x108B7040
		static void RegisterProperties();
		static void ClearProperties();

		int unknownc;
	};

	class PrintMessageCondition : public fight::Condition
	{
	public:
		// 0x108B7120
		PrintMessageCondition();
		virtual ~PrintMessageCondition();
		virtual fight::Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		// ClearProperties 0x108B70E0, RegisterProperties 0x108B71E0
		static void RegisterProperties();
		static void ClearProperties();

		int unknownc[3];
	};

	// 0x108127A0 / 0x108127C0 / 0x108127E0
	fight::TrackFactory* CreateExitTrackFactory(const char* name);
	fight::ConditionFactory* CreateMessageConditionFactory(const char* name);
	fight::ConditionFactory* CreatePrintMessageConditionFactory(const char* name);
}

#endif
