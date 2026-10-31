// Fight items of the ai group: AirHoverTrack, AirDodgeTrack (unit 0x1021BA30 - 0x1021C6F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_AIR_H
#define PROTO_FIGHTITEMS_AI_AI_AIR_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::AirHoverTrack (16 vftable slots, 0x44 bytes)
			class AirHoverTrack : public fight::Track
			{
			public:
				// 0x1021BC40
				AirHoverTrack();
				virtual ~AirHoverTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101DF5F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDistanceMin(float newValue);
				bool SetDistanceMax(float newValue);
				bool SetHeightMin(float newValue);
				bool SetHeightMax(float newValue);
				bool SetSpeed(float newValue);
				bool SetShootingDistance(float newValue);
				bool SetUseMissiles(bool newValue);
				bool SetMinFireTime(float newValue);
				bool SetMaxFireTime(float newValue);
				bool SetMinWaitTime(float newValue);
				bool SetMaxWaitTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distanceMax;  // +0x10
					float distanceMin;  // +0x14
					float heightMax;  // +0x18
					float heightMin;  // +0x1C
					float maxFireTime;  // +0x20
					float maxWaitTime;  // +0x24
					float minFireTime;  // +0x28
					float minWaitTime;  // +0x2C
					float shootingDistance;  // +0x30
					float speed;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
					bool useMissiles;  // +0x40
					unsigned char unknown41[0x3];
			};

			extern fight::Property** gAirHoverTrackProperties;
			fight::TrackFactory* CreateAirHoverTrackFactory(const char* name);
			void RegisterAirHoverTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AirDodgeTrack (16 vftable slots, 0x1C bytes)
			class AirDodgeTrack : public fight::Track
			{
			public:
				// 0x1021BD70
				AirDodgeTrack();
				virtual ~AirDodgeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101DF760, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetUseDirection(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool useDirection;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gAirDodgeTrackProperties;
			fight::TrackFactory* CreateAirDodgeTrackFactory(const char* name);
			void RegisterAirDodgeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::AirHoverAction (9 vftable slots, 0x2C bytes)
			class AirHoverAction : public fight::Action
			{
			public:
				// 0x101DEBA0
				AirHoverAction(AirHoverTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101DE980
				virtual ~AirHoverAction();

				// vftable slot 5 (0x101DE520)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101DE530)
				virtual void Slot6();
				// vftable slot 7 (0x101DF7B0)
				virtual bool Slot7(int arg, float value);

				core::Link<AirHoverTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				unsigned char unknown2C[0xC];
				bool unknown38;  // +0x38
				bool unknown39;  // +0x39
				unsigned char unknown3A[0x2];
				float unknown3C;  // +0x3C
			};

			// RTTI: proto::fightitems::ai::AirDodgeAction (9 vftable slots, 0x2C bytes)
			class AirDodgeAction : public fight::Action
			{
			public:
				// 0x101DF040
				AirDodgeAction(AirDodgeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101DEA90
				virtual ~AirDodgeAction();

				// vftable slot 5 (0x101DF0F0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101DE540)
				virtual void Slot6();
				// vftable slot 7 (0x101DF4E0)
				virtual bool Slot7(int arg, float value);

				core::Link<AirDodgeTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				unsigned char unknown2C[0x1C];
			};

			// ---- actions end
		}
	}
}

#endif
