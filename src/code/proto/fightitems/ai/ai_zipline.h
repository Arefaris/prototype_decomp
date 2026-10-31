// Fight items of the ai group: ZiplineLandTrack, ZiplineTakeOffTrack (unit 0x10256A40 - 0x102573D0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_ZIPLINE_H
#define PROTO_FIGHTITEMS_AI_AI_ZIPLINE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::ZiplineLandTrack (16 vftable slots, 0x24 bytes)
			class ZiplineLandTrack : public fight::Track
			{
			public:
				// 0x10256B70
				ZiplineLandTrack();
				virtual ~ZiplineLandTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1021AA20, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSpeed(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector speed;  // +0x10
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
			};

			extern fight::Property** gZiplineLandTrackProperties;
			fight::TrackFactory* CreateZiplineLandTrackFactory(const char* name);
			void RegisterZiplineLandTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ZiplineTakeOffTrack (16 vftable slots, 0x34 bytes)
			class ZiplineTakeOffTrack : public fight::Track
			{
			public:
				// 0x10256C20
				ZiplineTakeOffTrack();
				virtual ~ZiplineTakeOffTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1021A9D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetZiplineSpeed(const math::Vector& newValue);
				bool SetZiplineTime(float newValue);
				bool SetCharacterSpeed(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector characterSpeed;  // +0x10
					math::Vector ziplineSpeed;  // +0x1C
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					float ziplineTime;  // +0x30
			};

			extern fight::Property** gZiplineTakeOffTrackProperties;
			fight::TrackFactory* CreateZiplineTakeOffTrackFactory(const char* name);
			void RegisterZiplineTakeOffTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
