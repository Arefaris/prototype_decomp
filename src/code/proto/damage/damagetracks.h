// Fight items of the damage tracks: DebugDamageTrack, CauseDamageTrack (unit 0x10503C60 - 0x105049C0; no assert path, the file name is a guess).
#ifndef PROTO_DAMAGETRACKS_H
#define PROTO_DAMAGETRACKS_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/core/linklist.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/damage/damagedata.h"

namespace proto
{
	// RTTI: proto::DebugDamageTrack (16 vftable slots, 0x30 bytes)
	class DebugDamageTrack : public fight::Track
	{
	public:
		// 0x10503E20
		DebugDamageTrack();
		virtual ~DebugDamageTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x104FB4B0, another unit)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float newValue);
		bool SetDistance(float newValue);
		bool SetDamageType(int newValue);
		bool SetScaleX(float newValue);
		bool SetScaleY(float newValue);
		bool SetDamageSource(const fight::Name& newValue);

		// The getters the actions read the track through (0x104FABD0 - 0x104FAC10; names after the properties)
		float GetDistance() const;
		int GetDamageType() const;
		float GetScaleX() const;
		float GetScaleY() const;
		const fight::Name& GetDamageSource() const;

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name damageSource;  // +0x10
		float distance;  // +0x18
		float scaleX;  // +0x1C
		float scaleY;  // +0x20
		float timeBegin;  // +0x24
		int damageType;  // +0x28
		unsigned char unknown2C[0x4];
	};

	extern fight::Property** gDebugDamageTrackProperties;
	fight::TrackFactory* CreateDebugDamageTrackFactory(const char* name);
	void RegisterDebugDamageTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: proto::CauseDamageTrack (16 vftable slots, 0x30 bytes)
	class CauseDamageTrack : public fight::Track
	{
	public:
		// 0x10503EC0
		CauseDamageTrack();
		virtual ~CauseDamageTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x104FB180, another unit)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float newValue);
		bool SetForceZeroHealth(bool newValue);
		bool SetDamage(float newValue);
		bool SetAttackType(int newValue);
		bool SetOriginator(int newValue);
		bool SetGrabSlot(const fight::Name& newValue);
		bool SetIgnoreShield(bool newValue);
		bool SetSendAlert(bool newValue);

		// The getters the actions read the track through (0x104FAC20 - 0x104FAC80)
		bool GetForceZeroHealth() const;
		float GetDamage() const;
		const fight::Name& GetGrabSlot() const;
		bool GetIgnoreShield() const;
		bool GetSendAlert() const;

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name grabSlot;  // +0x10
		float damage;  // +0x18
		float timeBegin;  // +0x1C
		int attackType;  // +0x20
		int originator;  // +0x24
		bool forceZeroHealth;  // +0x28
		bool ignoreShield;  // +0x29
		bool sendAlert;  // +0x2A
		unsigned char unknown2B[0x5];
	};

	extern fight::Property** gCauseDamageTrackProperties;
	fight::TrackFactory* CreateCauseDamageTrackFactory(const char* name);
	void RegisterCauseDamageTrackFactory(fight::TrackRegistry* registry, const char* name);

}

namespace proto
{
	// RTTI: proto::DebugDamageAction (9 vftable slots, 0x28 bytes)
	class DebugDamageAction : public fight::Action
	{
	public:
		// 0x104FB220
		explicit DebugDamageAction(DebugDamageTrack* newTrack);
		// 0x104FAE50 (the deleting destructor is 0x104FB290)
		virtual ~DebugDamageAction();

		// vftable slot 7 (0x104FB2C0): left to the engine
		virtual bool Slot7(int arg, float value);

		core::Link<DebugDamageTrack> link;  // +0x1C
	};

	// RTTI: proto::CauseDamageAction (9 vftable slots, 0x30 bytes)
	class CauseDamageAction : public fight::Action
	{
	public:
		// 0x104FAF40
		CauseDamageAction(CauseDamageTrack* newTrack, const engine::HandleBase& newOriginator, const engine::HandleBase& newTarget);
		// 0x104FAE00 (the deleting destructor is 0x104FAFC0)
		virtual ~CauseDamageAction();

		// vftable slot 5 (0x104FB4F0): left to the engine
		virtual bool Slot5(int arg, float value);

		engine::HandleBase originator;  // +0x1C
		engine::HandleBase target;  // +0x20
		core::Link<CauseDamageTrack> link;  // +0x24
	};
}

namespace proto
{
	namespace fightitems
	{
		// 0x104FAC90: registers the factories of the damage tracks (name guess)
		bool RegisterAt104FAC90Factories(fight::TrackRegistry* registry);
	}
}

#endif
