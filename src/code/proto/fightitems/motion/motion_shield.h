// Fight items of the motion group: ShieldHealthCondition, ShieldStateCondition, ShieldProtectingCondition, ShieldDeployTrack, ShieldSetStateTrack, ShieldReflectTrack (unit 0x101AB8A0 - 0x101ACEE0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SHIELD_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SHIELD_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction2.h"
#include "code/proto/fightitems/motion/motionmessages2.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ShieldHealthCondition (10 vftable slots, 0x14 bytes)
			class ShieldHealthCondition : public fight::Condition
			{
			public:
				// 0x101AB9E0
				ShieldHealthCondition();
				virtual ~ShieldHealthCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1010F3D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetHealthPercentage(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float healthPercentage;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gShieldHealthConditionProperties;
			fight::ConditionFactory* CreateShieldHealthConditionFactory(const char* name);
			void RegisterShieldHealthConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShieldStateCondition (10 vftable slots, 0x10 bytes)
			class ShieldStateCondition : public fight::Condition
			{
			public:
				// 0x101ABA60
				ShieldStateCondition();
				virtual ~ShieldStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1010F590, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int state;  // +0xC
			};

			extern fight::Property** gShieldStateConditionProperties;
			fight::ConditionFactory* CreateShieldStateConditionFactory(const char* name);
			void RegisterShieldStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShieldProtectingCondition (10 vftable slots, 0xC bytes)
			class ShieldProtectingCondition : public fight::Condition
			{
			public:
				// 0x101ABB30
				ShieldProtectingCondition();
				virtual ~ShieldProtectingCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1010F4E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gShieldProtectingConditionProperties;
			fight::ConditionFactory* CreateShieldProtectingConditionFactory(const char* name);
			void RegisterShieldProtectingConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShieldDeployTrack (16 vftable slots, 0x18 bytes)
			class ShieldDeployTrack : public fight::Track
			{
			public:
				// 0x101ABB90
				ShieldDeployTrack();
				virtual ~ShieldDeployTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1010F240, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gShieldDeployTrackProperties;
			fight::TrackFactory* CreateShieldDeployTrackFactory(const char* name);
			void RegisterShieldDeployTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShieldSetStateTrack (16 vftable slots, 0x18 bytes)
			class ShieldSetStateTrack : public fight::Track
			{
			public:
				// 0x101ABC30
				ShieldSetStateTrack();
				virtual ~ShieldSetStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1010FBE0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					int state;  // +0x14
			};

			extern fight::Property** gShieldSetStateTrackProperties;
			fight::TrackFactory* CreateShieldSetStateTrackFactory(const char* name);
			void RegisterShieldSetStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShieldReflectTrack (16 vftable slots, 0x1C bytes)
			class ShieldReflectTrack : public fight::Track
			{
			public:
				// 0x101ABCD0
				ShieldReflectTrack();
				virtual ~ShieldReflectTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1010FC40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetReflectBullets(bool newValue);
				bool SetReflectMissiles(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool reflectBullets;  // +0x18
					bool reflectMissiles;  // +0x19
					unsigned char unknown1A[0x2];
			};

			extern fight::Property** gShieldReflectTrackProperties;
			fight::TrackFactory* CreateShieldReflectTrackFactory(const char* name);
			void RegisterShieldReflectTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::motion::ShieldSetStateAction (9 vftable slots, 0x2C bytes)
			class ShieldSetStateAction : public fight::Action
			{
			public:
				// 0x1010F8C0
				ShieldSetStateAction(ShieldSetStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1010F660
				virtual ~ShieldSetStateAction();

				// vftable slot 5 (0x1010F970)
				virtual bool Slot5(int arg, float value);

				core::Link<ShieldSetStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::motion::ShieldReflectAction (9 vftable slots, 0x2C bytes)
			class ShieldReflectAction : public fight::Action
			{
			public:
				// 0x1010FA00
				ShieldReflectAction(ShieldReflectTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1010F7B0
				virtual ~ShieldReflectAction();

				// vftable slot 5 (0x1010FAB0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1010FB50)
				virtual void Slot6();

				core::Link<ShieldReflectTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
