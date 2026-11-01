// Fight items of the motion group: UndergroundStateCondition, UndergroundSetTrack, AnchorToGroundTrack, UndergroundTeleportTrack (unit 0x101C3390 - 0x101C42E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_UNDERGROUND_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_UNDERGROUND_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::UndergroundStateCondition (10 vftable slots, 0x10 bytes)
			class UndergroundStateCondition : public fight::Condition
			{
			public:
				// 0x101C3490
				UndergroundStateCondition();
				virtual ~UndergroundStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101241D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				int GetState() const
				{
					return state;
				}

				// The members the properties write
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int state;  // +0xC
			};

			extern fight::Property** gUndergroundStateConditionProperties;
			fight::ConditionFactory* CreateUndergroundStateConditionFactory(const char* name);
			void RegisterUndergroundStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::UndergroundSetTrack (16 vftable slots, 0x18 bytes)
			class UndergroundSetTrack : public fight::Track
			{
			public:
				// 0x101C3500
				UndergroundSetTrack();
				virtual ~UndergroundSetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101247B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				bool GetUnderground() const
				{
					return underground;
				}
				bool GetInstantaneous() const
				{
					return instantaneous;
				}

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetUnderground(bool newValue);
				bool SetInstantaneous(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool instantaneous;  // +0x14
					bool underground;  // +0x15
					unsigned char unknown16[0x2];
			};

			extern fight::Property** gUndergroundSetTrackProperties;
			fight::TrackFactory* CreateUndergroundSetTrackFactory(const char* name);
			void RegisterUndergroundSetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AnchorToGroundTrack (16 vftable slots, 0x18 bytes)
			class AnchorToGroundTrack : public fight::Track
			{
			public:
				// 0x101C35A0
				AnchorToGroundTrack();
				virtual ~AnchorToGroundTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10124800, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				bool GetAnchor() const
				{
					return anchor;
				}
				bool GetGroundLevel() const
				{
					return groundLevel;
				}

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetAnchor(bool newValue);
				bool SetGroundLevel(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool anchor;  // +0x14
					bool groundLevel;  // +0x15
					unsigned char unknown16[0x2];
			};

			extern fight::Property** gAnchorToGroundTrackProperties;
			fight::TrackFactory* CreateAnchorToGroundTrackFactory(const char* name);
			void RegisterAnchorToGroundTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::UndergroundTeleportTrack (16 vftable slots, 0x18 bytes)
			class UndergroundTeleportTrack : public fight::Track
			{
			public:
				// 0x101C3640
				UndergroundTeleportTrack();
				virtual ~UndergroundTeleportTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10124850, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				float GetDistanceUnderground() const
				{
					return distanceUnderground;
				}

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetDistanceUnderground(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distanceUnderground;  // +0x10
					float timeBegin;  // +0x14
			};

			extern fight::Property** gUndergroundTeleportTrackProperties;
			fight::TrackFactory* CreateUndergroundTeleportTrackFactory(const char* name);
			void RegisterUndergroundTeleportTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// 0x10123E80: the factories of the unit's conditions the fight system registers together (name guess)
			bool RegisterUndergroundStateFactories(fight::TrackRegistry* registry);

			// 0x103B9BB0 (another unit): puts the object under the ground or brings it back, at once or by the tunneling state
			// (name guess)
			void SetTunnelingState(engine::GameObject* object, bool underground, bool instantaneous);
			// 0x103BCE10 (another unit): finds the height of the ground under a position (name guess)
			bool FindGroundHeight(const math::Vector* position, float* height, int flags);

			// RTTI: proto::fightitems::motion::UndergroundSetAction (9 vftable slots, 0x2C bytes)
			class UndergroundSetAction : public fight::Action
			{
			public:
				// 0x101243D0
				UndergroundSetAction(UndergroundSetTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10124100
				virtual ~UndergroundSetAction();

				// vftable slot 5 (0x10124480)
				virtual bool Slot5(int arg, float value);

				core::Link<UndergroundSetTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::motion::AnchorToGroundAction (9 vftable slots, 0x2C bytes)
			class AnchorToGroundAction : public fight::Action
			{
			public:
				// 0x101244E0
				AnchorToGroundAction(AnchorToGroundTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10124150
				virtual ~AnchorToGroundAction();

				// vftable slot 5 (0x10124590)
				virtual bool Slot5(int arg, float value);

				core::Link<AnchorToGroundTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::motion::UndergroundTeleportAction (9 vftable slots, 0x2C bytes)
			class UndergroundTeleportAction : public fight::Action
			{
			public:
				// 0x10124620
				UndergroundTeleportAction(UndergroundTeleportTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101241A0
				virtual ~UndergroundTeleportAction();

				// vftable slot 5 (0x101246D0)
				virtual bool Slot5(int arg, float value);

				core::Link<UndergroundTeleportTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
