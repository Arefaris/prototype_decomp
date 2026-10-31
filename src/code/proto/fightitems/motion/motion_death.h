// Fight items of the motion group: DeathOnEndTrack, DeathTrack (unit 0x10151930 - 0x101521B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_DEATH_H
#define PROTO_FIGHTITEMS_MOTION_DEATH_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DeathOnEndTrack (16 vftable slots, 0x18 bytes)
			class DeathOnEndTrack : public fight::Track
			{
			public:
				// 0x101519E0
				DeathOnEndTrack();
				virtual ~DeathOnEndTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B0630, another unit)
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

			extern fight::Property** gDeathOnEndTrackProperties;
			fight::TrackFactory* CreateDeathOnEndTrackFactory(const char* name);
			void RegisterDeathOnEndTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DeathTrack (16 vftable slots, 0x20 bytes)
			class DeathTrack : public fight::Track
			{
			public:
				// 0x10151AD0
				DeathTrack();
				virtual ~DeathTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B0670, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetDeadTemplate(const fight::Name& newValue);
				bool SetCopyDrawable(bool newValue);
				bool SetGrabberIsOriginator(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name deadTemplate;  // +0x10
					float timeBegin;  // +0x18
					bool copyDrawable;  // +0x1C
					bool grabberIsOriginator;  // +0x1D
					unsigned char unknown1E[0x2];
			};

			extern fight::Property** gDeathTrackProperties;
			fight::TrackFactory* CreateDeathTrackFactory(const char* name);
			void RegisterDeathTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
