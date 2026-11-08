// Fight items of the motion group: MoveChargedTrack (unit 0x10193360 - 0x101939C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_MOVECHARGED_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_MOVECHARGED_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::MoveChargedTrack (16 vftable slots, 0x3C bytes)
			class MoveChargedTrack : public fight::Track
			{
			public:
				// 0x10193460
				MoveChargedTrack();
				virtual ~MoveChargedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F6570, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDistanceMin(const math::Vector& newValue);
				bool SetDistanceMax(const math::Vector& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector distanceMax;  // +0x10
					math::Vector distanceMin;  // +0x1C
					float blendInTime;  // +0x28
					float blendOutTime;  // +0x2C
					float timeBegin;  // +0x30
					float timeEnd;  // +0x34
					int priority;  // +0x38
			};

			extern fight::Property** gMoveChargedTrackProperties;
			fight::TrackFactory* CreateMoveChargedTrackFactory(const char* name);
			void RegisterMoveChargedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::MoveChargedAction (9 vftable slots, 0x3C bytes)
			class MoveChargedAction : public fight::Action
			{
			public:
				// 0x100F6070
				MoveChargedAction(MoveChargedTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100F5F40
				virtual ~MoveChargedAction();

				// vftable slot 5 (0x100F6120)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100F5F80)
				virtual void Slot6();
				// vftable slot 7 (0x100F63C0)
				virtual bool Slot7(int arg, float value);

				core::Link<MoveChargedTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::RootDriver* driver;  // +0x2C
				math::Vector distance;  // +0x30
			};

			// ---- actions end
		}
	}
}

#endif
