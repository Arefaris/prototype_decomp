// Fight items of the motion group: CollisionGrabTrack (unit 0x1014A890 - 0x1014B6C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_COLLISIONGRAB_H
#define PROTO_FIGHTITEMS_MOTION_COLLISIONGRAB_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::CollisionGrabTrack (16 vftable slots, 0xA0 bytes)
			class CollisionGrabTrack : public fight::Track
			{
			public:
				// 0x1014AB00
				CollisionGrabTrack();
				virtual ~CollisionGrabTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100A7BD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetRadius(float newValue);
				bool SetUseMotion(bool newValue);
				bool SetArcOffset(float newValue);
				bool SetArcRange(float newValue);
				bool SetCollideWith(int newValue);
				bool SetCheckForObstruction(bool newValue);
				bool SetGrabOnlyPowerTarget(bool newValue);
				bool SetConsiderPlatformAsTarget(bool newValue);
				bool SetReverseAttachOnMountable(bool newValue);
				fight::BranchHolder* SetGiverBranch();
				fight::BranchHolder* SetReceiverBranch();
				bool SetInterruptPriority(int newValue);
				bool SetDevastatorGrab(bool newValue);
				bool SetPhysicsMode(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder giverBranch;  // +0x10
					fight::BranchHolder receiverBranch;  // +0x34
					fight::Name grabSlot;  // +0x58
					fight::Name joint;  // +0x60
					math::Vector offset;  // +0x68
					float arcOffset;  // +0x74
					float arcRange;  // +0x78
					float radius;  // +0x7C
					float timeBegin;  // +0x80
					float timeEnd;  // +0x84
					int interruptPriority;  // +0x88
					int physicsMode;  // +0x8C
					int collideWith;  // +0x90
					bool checkForObstruction;  // +0x94
					bool considerPlatformAsTarget;  // +0x95
					bool devastatorGrab;  // +0x96
					bool grabOnlyPowerTarget;  // +0x97
					bool reverseAttachOnMountable;  // +0x98
					bool useMotion;  // +0x99
					unsigned char unknown9A[0x6];
			};

			extern fight::Property** gCollisionGrabTrackProperties;
			fight::TrackFactory* CreateCollisionGrabTrackFactory(const char* name);
			void RegisterCollisionGrabTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
