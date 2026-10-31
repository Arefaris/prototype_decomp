// Fight items of the ai group: FlyingIdleTrack, IdleTrack (unit 0x10234D10 - 0x102356A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_IDLE_H
#define PROTO_FIGHTITEMS_AI_AI_IDLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::FlyingIdleTrack (16 vftable slots, 0x24 bytes)
			class FlyingIdleTrack : public fight::Track
			{
			public:
				// 0x10234E50
				FlyingIdleTrack();
				virtual ~FlyingIdleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F8930, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinHeight(float newValue);
				bool SetFreeRadius(float newValue);
				bool SetTolerance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float freeRadius;  // +0x10
					float minHeight;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					float tolerance;  // +0x20
			};

			extern fight::Property** gFlyingIdleTrackProperties;
			fight::TrackFactory* CreateFlyingIdleTrackFactory(const char* name);
			void RegisterFlyingIdleTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::IdleTrack (16 vftable slots, 0x20 bytes)
			class IdleTrack : public fight::Track
			{
			public:
				// 0x10234F20
				IdleTrack();
				virtual ~IdleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F87F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetIgnoreDefendAreaHeight(bool newValue);
				bool SetTolerance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					float tolerance;  // +0x18
					bool ignoreDefendAreaHeight;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gIdleTrackProperties;
			fight::TrackFactory* CreateIdleTrackFactory(const char* name);
			void RegisterIdleTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
