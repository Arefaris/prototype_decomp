// Fight items of the ai group: TakeOffTrack, LandTrack (unit 0x102356A0 - 0x10236270; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_TAKEOFF_H
#define PROTO_FIGHTITEMS_AI_AI_TAKEOFF_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::TakeOffTrack (16 vftable slots, 0x24 bytes)
			class TakeOffTrack : public fight::Track
			{
			public:
				// 0x10235880
				TakeOffTrack();
				virtual ~TakeOffTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F9EC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSpeed(float newValue);
				bool SetAcceleration(float newValue);
				bool SetMinHeight(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float acceleration;  // +0x10
					float minHeight;  // +0x14
					float speed;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
			};

			extern fight::Property** gTakeOffTrackProperties;
			fight::TrackFactory* CreateTakeOffTrackFactory(const char* name);
			void RegisterTakeOffTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::LandTrack (16 vftable slots, 0x30 bytes)
			class LandTrack : public fight::Track
			{
			public:
				// 0x10235950
				LandTrack();
				virtual ~LandTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F9E70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSpeed(float newValue);
				bool SetToleraceAngleStartLanding(float newValue);
				bool SetClearDestination(bool newValue);
				bool SetTurnOffRotor(bool newValue);
				bool SetIgnoreOrientation(bool newValue);
				bool SetToleranceY(float newValue);
				bool SetToleranceXZ(float newValue);
				bool SetDistanceToGround(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distanceToGround;  // +0x10
					float speed;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					float toleraceAngleStartLanding;  // +0x20
					float toleranceXZ;  // +0x24
					float toleranceY;  // +0x28
					bool clearDestination;  // +0x2C
					bool ignoreOrientation;  // +0x2D
					bool turnOffRotor;  // +0x2E
					unsigned char unknown2F[0x1];
			};

			extern fight::Property** gLandTrackProperties;
			fight::TrackFactory* CreateLandTrackFactory(const char* name);
			void RegisterLandTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
