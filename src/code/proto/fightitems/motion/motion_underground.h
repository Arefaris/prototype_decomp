// Fight items of the motion group: UndergroundStateCondition, UndergroundSetTrack, AnchorToGroundTrack, UndergroundTeleportTrack (unit 0x101C3390 - 0x101C42E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_UNDERGROUND_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_UNDERGROUND_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

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

		}
	}
}

#endif
