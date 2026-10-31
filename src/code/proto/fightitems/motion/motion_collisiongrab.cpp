// Fight items of the motion group: CollisionGrabTrack (unit 0x1014A890 - 0x1014B6C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_collisiongrab.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gCollisionGrabTrackProperties;  // 0x11254360

			// FUNCTION: ENGINE 0x1014A890
			bool CollisionGrabTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A8B0
			bool CollisionGrabTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014AAC0
			bool CollisionGrabTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014AAE0
			bool CollisionGrabTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A8D0
			bool CollisionGrabTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A8F0
			bool CollisionGrabTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A910
			bool CollisionGrabTrack::SetUseMotion(bool newValue)
			{
				useMotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A930
			bool CollisionGrabTrack::SetArcOffset(float newValue)
			{
				arcOffset = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A950
			bool CollisionGrabTrack::SetArcRange(float newValue)
			{
				arcRange = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A970
			bool CollisionGrabTrack::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A990
			bool CollisionGrabTrack::SetCheckForObstruction(bool newValue)
			{
				checkForObstruction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A9B0
			bool CollisionGrabTrack::SetGrabOnlyPowerTarget(bool newValue)
			{
				grabOnlyPowerTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A9D0
			bool CollisionGrabTrack::SetConsiderPlatformAsTarget(bool newValue)
			{
				considerPlatformAsTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014A9F0
			bool CollisionGrabTrack::SetReverseAttachOnMountable(bool newValue)
			{
				reverseAttachOnMountable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014AA10
			fight::BranchHolder* CollisionGrabTrack::SetGiverBranch()
			{
				return &giverBranch;
			}

			// FUNCTION: ENGINE 0x1014AA20
			fight::BranchHolder* CollisionGrabTrack::SetReceiverBranch()
			{
				return &receiverBranch;
			}

			// FUNCTION: ENGINE 0x1014AA30
			bool CollisionGrabTrack::SetInterruptPriority(int newValue)
			{
				interruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014AA50
			bool CollisionGrabTrack::SetDevastatorGrab(bool newValue)
			{
				devastatorGrab = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014AA70
			bool CollisionGrabTrack::SetPhysicsMode(int newValue)
			{
				physicsMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014AA90
			fight::Property* CollisionGrabTrack::GetProperty(int index)
			{
				return gCollisionGrabTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014AAB0
			void CollisionGrabTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCollisionGrabTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014AB00
			CollisionGrabTrack::CollisionGrabTrack() : giverBranch(0), receiverBranch(0), offset(0.0f, 0.0f, 0.0f), arcOffset(0.0f), arcRange(0.0f), radius(1.0f), timeBegin(0.0f), timeEnd(0.0f), interruptPriority(-5), physicsMode(0), collideWith(gCollisionGrabTrackCollideWithDefault), checkForObstruction(true), considerPlatformAsTarget(true), devastatorGrab(false), grabOnlyPowerTarget(false), reverseAttachOnMountable(false), useMotion(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1014ABF0
			float CollisionGrabTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1014AC00
			float CollisionGrabTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1014AC10
			CollisionGrabTrack::~CollisionGrabTrack()
			{
			}

			// FUNCTION: ENGINE 0x1014B100
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CollisionGrabTrack::RegisterProperties()
			{
				if (gCollisionGrabTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CollisionGrabTrack>("timeBegin", &CollisionGrabTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CollisionGrabTrack>("timeEnd", &CollisionGrabTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<CollisionGrabTrack>("grabSlot", &CollisionGrabTrack::SetGrabSlot);
					properties[2] = property;
					property = new fight::PropertyNameList<CollisionGrabTrack>("joint", &CollisionGrabTrack::SetJoint);
					properties[3] = property;
					property = new fight::PropertyVector<CollisionGrabTrack>("offset", &CollisionGrabTrack::SetOffset);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<CollisionGrabTrack>("radius", &CollisionGrabTrack::SetRadius);
					properties[5] = property;
					property = new fight::PropertyBool<CollisionGrabTrack>("useMotion", &CollisionGrabTrack::SetUseMotion);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<CollisionGrabTrack>("arcOffset", &CollisionGrabTrack::SetArcOffset);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<CollisionGrabTrack>("arcRange", &CollisionGrabTrack::SetArcRange);
					properties[8] = property;
					property = new fight::PropertyBitfieldConstList<CollisionGrabTrack>("collideWith", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &CollisionGrabTrack::SetCollideWith);
					properties[9] = property;
					property = new fight::PropertyBool<CollisionGrabTrack>("checkForObstruction", &CollisionGrabTrack::SetCheckForObstruction);
					properties[10] = property;
					property = new fight::PropertyBool<CollisionGrabTrack>("grabOnlyPowerTarget", &CollisionGrabTrack::SetGrabOnlyPowerTarget);
					properties[11] = property;
					property = new fight::PropertyBool<CollisionGrabTrack>("considerPlatformAsTarget", &CollisionGrabTrack::SetConsiderPlatformAsTarget);
					properties[12] = property;
					property = new fight::PropertyBool<CollisionGrabTrack>("reverseAttachOnMountable", &CollisionGrabTrack::SetReverseAttachOnMountable);
					properties[13] = property;
					property = new fight::PropertyBranch<CollisionGrabTrack>("giverBranch", &CollisionGrabTrack::SetGiverBranch);
					properties[14] = property;
					property = new fight::PropertyBranch<CollisionGrabTrack>("receiverBranch", &CollisionGrabTrack::SetReceiverBranch);
					properties[15] = property;
					property = new fight::PropertyIntConstRange<CollisionGrabTrack>("interruptPriority", &CollisionGrabTrack::SetInterruptPriority);
					properties[16] = property;
					property = new fight::PropertyBool<CollisionGrabTrack>("devastatorGrab", &CollisionGrabTrack::SetDevastatorGrab);
					properties[17] = property;
					property = new fight::PropertyEnumConstList<CollisionGrabTrack>("physicsMode", gCollisionGrabTrackPhysicsModeTable, gCollisionGrabTrackPhysicsModeCount, &CollisionGrabTrack::SetPhysicsMode);
					properties[18] = property;
					fight::RegisterPropertyList(properties, &gCollisionGrabTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014B040
			fight::TrackFactory* CreateCollisionGrabTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CollisionGrabTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014B070
			void RegisterCollisionGrabTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CollisionGrabTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<CollisionGrabTrack>;
			template class fight::PropertyNameList<CollisionGrabTrack>;
			template class fight::PropertyVector<CollisionGrabTrack>;
			template class fight::PropertyBool<CollisionGrabTrack>;
			template class fight::PropertyBitfieldConstList<CollisionGrabTrack>;
			template class fight::PropertyBranch<CollisionGrabTrack>;
			template class fight::PropertyIntConstRange<CollisionGrabTrack>;
			template class fight::PropertyEnumConstList<CollisionGrabTrack>;
			template class fight::TrackFactoryTemplate<CollisionGrabTrack>;
			template class fight::TrackFactoryCasterTemplate<CollisionGrabTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
