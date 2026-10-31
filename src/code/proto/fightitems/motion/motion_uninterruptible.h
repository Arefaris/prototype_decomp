// Fight items of the motion group: InvulnerableTrack, SpecificUninterruptibleTrack, UninterruptibleTrack (unit 0x101C42E0 - 0x101C4FB0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_UNINTERRUPTIBLE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_UNINTERRUPTIBLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::InvulnerableTrack (16 vftable slots, 0x18 bytes)
			class InvulnerableTrack : public fight::Track
			{
			public:
				// 0x101C4410
				InvulnerableTrack();
				virtual ~InvulnerableTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10124B70, another unit)
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

			extern fight::Property** gInvulnerableTrackProperties;
			fight::TrackFactory* CreateInvulnerableTrackFactory(const char* name);
			void RegisterInvulnerableTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SpecificUninterruptibleTrack (16 vftable slots, 0x1C bytes)
			class SpecificUninterruptibleTrack : public fight::Track
			{
			public:
				// 0x101C44B0
				SpecificUninterruptibleTrack();
				virtual ~SpecificUninterruptibleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10125610, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetIgnoreGrabs(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool ignoreGrabs;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gSpecificUninterruptibleTrackProperties;
			fight::TrackFactory* CreateSpecificUninterruptibleTrackFactory(const char* name);
			void RegisterSpecificUninterruptibleTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::UninterruptibleTrack (16 vftable slots, 0x1C bytes)
			class UninterruptibleTrack : public fight::Track
			{
			public:
				// 0x101C4550
				UninterruptibleTrack();
				virtual ~UninterruptibleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101255C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetIgnoreHits(bool newValue);
				bool SetIgnoreGrabs(bool newValue);
				bool SetAllowDevastatorGrabs(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool allowDevastatorGrabs;  // +0x18
					bool ignoreGrabs;  // +0x19
					bool ignoreHits;  // +0x1A
					unsigned char unknown1B[0x1];
			};

			extern fight::Property** gUninterruptibleTrackProperties;
			fight::TrackFactory* CreateUninterruptibleTrackFactory(const char* name);
			void RegisterUninterruptibleTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
