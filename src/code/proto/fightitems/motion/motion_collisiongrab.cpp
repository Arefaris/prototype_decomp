// Fight items of the motion group: CollisionGrabTrack (unit 0x1014A890 - 0x1014B6C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_collisiongrab.h"
#include <new>
#include "code/proto/fightitems/motion/motion_consume.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/fightitems/motion/motionactionmessages.h"

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

			// FUNCTION: ENGINE 0x100A7180
			CollisionGrabAction::CollisionGrabAction(fight::Track* listener, CollisionGrabTrack* newTrack, core::IRefCount* owner, engine::GameObjectHandle newTarget) : CollisionAction(newTarget, listener, newTrack), link(newTrack)
			{
				const ReactionEvent* event = (const ReactionEvent*)owner;
				if (event != 0 && event->kind == 0x2100b)
				{
					grabber = ((const CollisionGrabEvent*)event)->grabber;
				}
			}

			// FUNCTION: ENGINE 0x100A6EE0
			CollisionGrabAction::~CollisionGrabAction()
			{
			}

			// FUNCTION: ENGINE 0x100A7BD0
			fight::Action* CollisionGrabTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CollisionGrabAction(listener, this, owner, handle);
			}

			// FUNCTION: ENGINE 0x100A7080
			void CollisionGrabAction::Slot6()
			{
				CollisionAction::Slot6();
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					OutOfCombatTimerSetMessage message(0.0f);
					object->SendMessage(&message);
				}
			}

			// FUNCTION: ENGINE 0x100A7250
			int CollisionGrabAction::GetCollideWith()
			{
				return link.Get()->collideWith;
			}

			// FUNCTION: ENGINE 0x100A7260
			float CollisionGrabAction::GetArcOffset()
			{
				return link.Get()->arcOffset;
			}

			// FUNCTION: ENGINE 0x100A7270
			float CollisionGrabAction::GetArcRange()
			{
				return link.Get()->arcRange;
			}

			// FUNCTION: ENGINE 0x100A6F30
			int CollisionGrabAction::Slot14()
			{
				return -1;
			}

			// FUNCTION: ENGINE 0x100A7280
			int CollisionGrabAction::GetJointIndex()
			{
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return 0xffff;
				}
				return FindDrawablePart(object, &link.Get()->joint);
			}

			// FUNCTION: ENGINE 0x100A72D0
			// NONMATCHING: the engine advances the pointer to the offset after the first load and loads the destination first (78.8 %)
#ifdef NONMATCHING
			math::Vector* CollisionGrabAction::GetOffset(math::Vector* offset)
			{
				math::Vector copy(link.Get()->offset);
				offset->x = copy.x;
				offset->y = copy.y;
				offset->z = copy.z;
				return offset;
			}
#endif

			// FUNCTION: ENGINE 0x100A7300
			bool CollisionGrabAction::GetUseMotion()
			{
				return link.Get()->useMotion;
			}

			// FUNCTION: ENGINE 0x100A7310
			float CollisionGrabAction::GetRadius()
			{
				return link.Get()->radius;
			}

			// FUNCTION: ENGINE 0x100A6F40
			// NONMATCHING: the engine reads the end of the hits for the search through the start of the storage and keeps the handle in edi (38.5 %)
#ifdef NONMATCHING
			void CollisionGrabAction::Slot24(engine::GameObject* object)
			{
				engine::GameObjectHandle handle = engine::GetHandle(object);
				if (hits.Size() != 10)
				{
					engine::GameObjectHandle* it = hits.Begin();
					engine::GameObjectHandle* last = hits.End();
					while (it != last && !SameHandle(*it, handle))
					{
						++it;
					}
					if (it == hits.End())
					{
						hits.PushBack(handle);
					}
				}
			}
#endif

			// FUNCTION: ENGINE 0x100A7320
			bool CollisionGrabAction::Slot25(engine::GameObject* object)
			{
				if (grabber.IsValid())
				{
					if (object != grabber.Get())
					{
						return false;
					}
				}
				AttemptGrabMessage message(target, link.Get()->devastatorGrab);
				object->SendMessage(&message);
				if (message.grabbed && message.allowed)
				{
					return true;
				}
				return false;
			}

			// FUNCTION: ENGINE 0x100A7B90
			bool CollisionGrabAction::Slot27()
			{
				if (link.Get() == 0)
				{
					return CollisionAction::Slot27();
				}
				return link.Get()->grabOnlyPowerTarget;
			}

			// FUNCTION: ENGINE 0x100A7BB0
			bool CollisionGrabAction::Slot29()
			{
				if (link.Get() == 0)
				{
					return CollisionAction::Slot29();
				}
				return link.Get()->considerPlatformAsTarget;
			}

			// FUNCTION: ENGINE 0x100A6870
			const fight::Name& CollisionGrabTrack::GetGrabSlot() const
			{
				return grabSlot;
			}

			// FUNCTION: ENGINE 0x100A6880
			const fight::Name& CollisionGrabTrack::GetJoint() const
			{
				return joint;
			}

			// FUNCTION: ENGINE 0x100A6890
			math::Vector CollisionGrabTrack::GetOffset() const
			{
				return offset;
			}

			// FUNCTION: ENGINE 0x100A68B0
			float CollisionGrabTrack::GetRadius() const
			{
				return radius;
			}

			// FUNCTION: ENGINE 0x100A68C0
			bool CollisionGrabTrack::GetUseMotion() const
			{
				return useMotion;
			}

			// FUNCTION: ENGINE 0x100A68D0
			int CollisionGrabTrack::GetCollideWith() const
			{
				return collideWith;
			}

			// FUNCTION: ENGINE 0x100A68E0
			bool CollisionGrabTrack::GetCheckForObstruction() const
			{
				return checkForObstruction;
			}

			// FUNCTION: ENGINE 0x100A68F0
			bool CollisionGrabTrack::GetGrabOnlyPowerTarget() const
			{
				return grabOnlyPowerTarget;
			}

			// FUNCTION: ENGINE 0x100A6900
			bool CollisionGrabTrack::GetConsiderPlatformAsTarget() const
			{
				return considerPlatformAsTarget;
			}

			// FUNCTION: ENGINE 0x100A6910
			bool CollisionGrabTrack::GetReverseAttachOnMountable() const
			{
				return reverseAttachOnMountable;
			}

			// FUNCTION: ENGINE 0x100A6920
			const fight::BranchHolder& CollisionGrabTrack::GetGiverBranch() const
			{
				return giverBranch;
			}

			// FUNCTION: ENGINE 0x100A6930
			const fight::BranchHolder& CollisionGrabTrack::GetReceiverBranch() const
			{
				return receiverBranch;
			}

			// FUNCTION: ENGINE 0x100A6940
			int CollisionGrabTrack::GetInterruptPriority() const
			{
				return interruptPriority;
			}

			// FUNCTION: ENGINE 0x100A6950
			bool CollisionGrabTrack::GetDevastatorGrab() const
			{
				return devastatorGrab;
			}

			// FUNCTION: ENGINE 0x100A6960
			int CollisionGrabTrack::GetPhysicsMode() const
			{
				return physicsMode;
			}

			// FUNCTION: ENGINE 0x100A6F10
			float CollisionGrabTrack::GetArcOffset() const
			{
				return arcOffset;
			}

			// FUNCTION: ENGINE 0x100A6F20
			float CollisionGrabTrack::GetArcRange() const
			{
				return arcRange;
			}

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
// FUNCTION: ENGINE 0x1014AC50
// FUNCTION: ENGINE 0x1014AC60
// FUNCTION: ENGINE 0x1014AC90
// FUNCTION: ENGINE 0x1014ACC0
// FUNCTION: ENGINE 0x1014ACF0
// FUNCTION: ENGINE 0x1014AD20
// FUNCTION: ENGINE 0x1014AD30
// FUNCTION: ENGINE 0x1014AD60
// FUNCTION: ENGINE 0x1014AD80
// FUNCTION: ENGINE 0x1014AD90
// FUNCTION: ENGINE 0x1014ADC0
// FUNCTION: ENGINE 0x1014ADE0
// FUNCTION: ENGINE 0x1014ADF0
// FUNCTION: ENGINE 0x1014AE30
// FUNCTION: ENGINE 0x1014AE40
// FUNCTION: ENGINE 0x1014AE60
// FUNCTION: ENGINE 0x1014AE70
// FUNCTION: ENGINE 0x1014AED0
// FUNCTION: ENGINE 0x1014AF10
// FUNCTION: ENGINE 0x1014AF30
// FUNCTION: ENGINE 0x1014AF60
// FUNCTION: ENGINE 0x1014AF80
// FUNCTION: ENGINE 0x1014AF90
// FUNCTION: ENGINE 0x1014AFD0
// FUNCTION: ENGINE 0x1014AFE0
// FUNCTION: ENGINE 0x1014B010
// FUNCTION: ENGINE 0x1014B030
// FUNCTION: ENGINE 0x1014B0A0
// FUNCTION: ENGINE 0x1014B0D0
// FUNCTION: ENGINE 0x1014B0F0
// FUNCTION: ENGINE 0x1014B610
// FUNCTION: ENGINE 0x1014B640
// FUNCTION: ENGINE 0x1014B670
// FUNCTION: ENGINE 0x100A6BC0
// FUNCTION: ENGINE 0x100A6BF0
// FUNCTION: ENGINE 0x100A6C60
// FUNCTION: ENGINE 0x100A6DE0
// FUNCTION: ENGINE 0x100A6E10
// FUNCTION: ENGINE 0x100A7220
// FUNCTION: ENGINE 0x100A6BB0
// FUNCTION: ENGINE 0x100A6CE0
// FUNCTION: ENGINE 0x100A6CF0
// FUNCTION: ENGINE 0x100A6D20
// FUNCTION: ENGINE 0x100A6970
// FUNCTION: ENGINE 0x100A6A80
// FUNCTION: ENGINE 0x100A69B0
// FUNCTION: ENGINE 0x100A6AD0
