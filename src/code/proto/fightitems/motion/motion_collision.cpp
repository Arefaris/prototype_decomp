// Fight items of the motion group: DetectObbCollisionCondition, HitSurfaceCondition (unit 0x10149DC0 - 0x1014A890; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_collision.h"
#include "code/proto/behaviours/collisionmessages.h"
#include "code/proto/behaviours/collisionactionbehaviour.h"
#include "code/proto/fightitems/motion/motionactionmessages.h"
#include "code/proto/fightitems/motion/motioncommon.h"
#include <math.h>

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDetectObbCollisionConditionProperties;  // 0x11254340

			// FUNCTION: ENGINE 0x10149DC0
			bool DetectObbCollisionCondition::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149DD0
			bool DetectObbCollisionCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149F30
			bool DetectObbCollisionCondition::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149DE0
			bool DetectObbCollisionCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10149E00
			bool DetectObbCollisionCondition::SetOrientation(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				orientation.x = scaled.x;
				orientation.y = scaled.y;
				orientation.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10149E50
			bool DetectObbCollisionCondition::SetExtents(const math::Vector& newValue)
			{
				extents.x = newValue.x;
				extents.y = newValue.y;
				extents.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10149E90
			fight::Property* DetectObbCollisionCondition::GetProperty(int index)
			{
				return gDetectObbCollisionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10149EB0
			void DetectObbCollisionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDetectObbCollisionConditionProperties);
			}

			// FUNCTION: ENGINE 0x10149F50
			DetectObbCollisionCondition::DetectObbCollisionCondition() : fight::Condition(0), extents(0.0f, 0.0f, 0.0f), offset(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f), collideWith(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x10149FC0
			DetectObbCollisionCondition::~DetectObbCollisionCondition()
			{
			}

			// FUNCTION: ENGINE 0x1014A5C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DetectObbCollisionCondition::RegisterProperties()
			{
				if (gDetectObbCollisionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBitfieldConstList<DetectObbCollisionCondition>("collideWith", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &DetectObbCollisionCondition::SetCollideWith);
					properties[0] = property;
					property = new fight::PropertyBool<DetectObbCollisionCondition>("match", &DetectObbCollisionCondition::SetMatch);
					properties[1] = property;
					property = new fight::PropertyNameList<DetectObbCollisionCondition>("joint", &DetectObbCollisionCondition::SetJoint);
					properties[2] = property;
					property = new fight::PropertyVector<DetectObbCollisionCondition>("offset", &DetectObbCollisionCondition::SetOffset);
					properties[3] = property;
					property = new fight::PropertyVector<DetectObbCollisionCondition>("orientation", &DetectObbCollisionCondition::SetOrientation);
					properties[4] = property;
					property = new fight::PropertyVector<DetectObbCollisionCondition>("extents", &DetectObbCollisionCondition::SetExtents);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gDetectObbCollisionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014A360
			fight::ConditionFactory* CreateDetectObbCollisionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectObbCollisionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014A4B0
			void RegisterDetectObbCollisionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectObbCollisionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHitSurfaceConditionProperties;  // 0x11254344

			// FUNCTION: ENGINE 0x10149E70
			bool HitSurfaceCondition::SetSurface(int newValue)
			{
				surface = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149E80
			bool HitSurfaceCondition::SetHitSurface(bool newValue)
			{
				hitSurface = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149EC0
			fight::Property* HitSurfaceCondition::GetProperty(int index)
			{
				return gHitSurfaceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10149EE0
			void HitSurfaceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHitSurfaceConditionProperties);
			}

			// FUNCTION: ENGINE 0x10149EF0
			HitSurfaceCondition::HitSurfaceCondition() : fight::Condition(0), surface(0), hitSurface(true)
			{
			}

			// FUNCTION: ENGINE 0x10149F20
			HitSurfaceCondition::~HitSurfaceCondition()
			{
			}

			// FUNCTION: ENGINE 0x1014A3C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HitSurfaceCondition::RegisterProperties()
			{
				if (gHitSurfaceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<HitSurfaceCondition>("surface", gHitSurfaceConditionSurfaceTable, gHitSurfaceConditionSurfaceCount, &HitSurfaceCondition::SetSurface);
					properties[0] = property;
					property = new fight::PropertyBool<HitSurfaceCondition>("hitSurface", &HitSurfaceCondition::SetHitSurface);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHitSurfaceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014A390
			fight::ConditionFactory* CreateHitSurfaceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HitSurfaceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014A4E0
			void RegisterHitSurfaceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HitSurfaceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			// ---- actions begin

			// Two words the unit keeps for the slots that answer a default (file statics of the unit)
			static int sSlot10Value = -1;  // 0x10FF0EC4
			static int sSlot11Value;  // 0x112536C0

			// FUNCTION: ENGINE 0x100A5A00
			CollisionAction::CollisionAction(engine::GameObjectHandle newTarget, fight::Track* listener, fight::Track* newTrack) : fight::Action(0x600), target(newTarget), behaviour(0), unknown28(false), unknown29(false), watch(listener), link(newTrack), unknown80(0), volume(0), jointIndex(0xffff), unknown98(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x100A5BA0
			CollisionAction::~CollisionAction()
			{
				delete volume;
				volume = 0;
			}

			// FUNCTION: ENGINE 0x100A3790
			void CollisionAction::Slot6()
			{
				if (Slot22() && unknown20.Get() != 0 && behaviour != 0)
				{
					SetCollisionActiveMessage message(false);
					behaviour->SetCollisionActive(&message);
				}
			}

			// FUNCTION: ENGINE 0x100A4320
			void CollisionAction::Slot23()
			{
				unknown20 = target;
				engine::GameObject* object = unknown20.Get();
				if (unknown29)
				{
					if (object == 0)
					{
						behaviour = 0;
						return;
					}
					GetDamageOriginatorDamageMessage originatorMessage;
					object->SendMessage(&originatorMessage);
					engine::GameObject* originator = originatorMessage.originator.Get();
					if (originator != 0)
					{
						unknown20 = originatorMessage.originator;
						object = originator;
					}
				}
				if (object != 0)
				{
					GetCollisionActionBehaviourMessage behaviourMessage;
					object->SendMessage(&behaviourMessage);
					behaviour = behaviourMessage.behaviour;
				}
				else
				{
					behaviour = 0;
				}
			}

			// FUNCTION: ENGINE 0x100A5B90
			bool CollisionAction::Slot9()
			{
				return true;
			}

			// FUNCTION: ENGINE 0x100A2CC0
			int CollisionAction::Slot10()
			{
				return sSlot10Value;
			}

			// FUNCTION: ENGINE 0x100A2CD0
			int CollisionAction::GetCollideWith()
			{
				return sSlot11Value;
			}

			// FUNCTION: ENGINE 0x100A5AD0
			float CollisionAction::GetArcOffset()
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x100A5AE0
			float CollisionAction::GetArcRange()
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x100A5AF0
			int CollisionAction::Slot14()
			{
				return -1;
			}

			// FUNCTION: ENGINE 0x100A5B00
			float CollisionAction::Slot15(int unused)
			{
				return choreo::gMinusOne;
			}

			// FUNCTION: ENGINE 0x100A5B10
			int CollisionAction::GetJointIndex()
			{
				return 0xffff;
			}

			// FUNCTION: ENGINE 0x100A5B20
			math::Vector* CollisionAction::GetOffset(math::Vector* offset)
			{
				offset->x = 0.0f;
				offset->y = 0.0f;
				offset->z = 0.0f;
				return offset;
			}

			// FUNCTION: ENGINE 0x100A5B40
			bool CollisionAction::GetUseMotion()
			{
				return false;
			}

			// FUNCTION: ENGINE 0x100A5B50
			float CollisionAction::GetRadius()
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x100A5B60
			float CollisionAction::Slot21()
			{
				return choreo::gMinusOne;
			}

			// FUNCTION: ENGINE 0x100A5B70
			bool CollisionAction::Slot22()
			{
				return true;
			}

			// FUNCTION: ENGINE 0x100A5B80
			bool CollisionAction::Slot25(engine::GameObject* object)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x100A2CE0
			bool CollisionAction::Slot27()
			{
				return false;
			}

			// FUNCTION: ENGINE 0x100A2CF0
			bool CollisionAction::Slot28()
			{
				return false;
			}

			// FUNCTION: ENGINE 0x100A2D00
			bool CollisionAction::Slot29()
			{
				return true;
			}

			// FUNCTION: ENGINE 0x100A2D10
			bool CollisionAction::Slot30(engine::GameObject* object)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x100A6060
			// NONMATCHING: the engine keeps the two near flags in dl and cl the other way round and repeats the compare with the wanted flag in each branch of the third surface (64 %)
#ifdef NONMATCHING
			bool HitSurfaceCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				bool wanted = hitSurface;
				GetCachedWallCollisionMessage message;
				object->SendMessage(&message);
				if (message.found != wanted)
				{
					return false;
				}
				if (!wanted)
				{
					return true;
				}
				float z0 = message.unknown1C * 0.0f;
				float x0 = message.unknown14 * 0.0f;
				float up = message.unknown18 + x0 + z0;
				if (!(up - choreo::gMinusOne >= 0.0f))
				{
					up = choreo::gMinusOne;
				}
				float upArgument = up;
				if (upArgument - engine::driving::gOne >= 0.0f)
				{
					upArgument = engine::driving::gOne;
				}
				float angleUp = (float)acos(upArgument);
				float down = choreo::gMinusOne * message.unknown18 + x0 + z0;
				if (!(down - choreo::gMinusOne >= 0.0f))
				{
					down = choreo::gMinusOne;
				}
				float downArgument = down;
				if (downArgument - engine::driving::gOne >= 0.0f)
				{
					downArgument = engine::driving::gOne;
				}
				float angleDown = (float)acos(downArgument);
				bool nearDown;
				bool nearUp;
				nearUp = angleUp < 0.7853982f;
				nearDown = angleDown < 0.7853982f;
				switch (surface)
				{
				case 0:
					return nearUp == wanted;
				case 1:
					return nearDown == wanted;
				case 2:
					{
						bool onSide = true;
						if (nearUp || nearDown)
						{
							onSide = false;
						}
						return onSide == wanted;
					}
				default:
					return false;
				}
			}
#endif

			// ---- actions end
			template class fight::PropertyBitfieldConstList<DetectObbCollisionCondition>;
			template class fight::PropertyBool<DetectObbCollisionCondition>;
			template class fight::PropertyNameList<DetectObbCollisionCondition>;
			template class fight::PropertyVector<DetectObbCollisionCondition>;
			template class fight::ConditionFactoryTemplate<DetectObbCollisionCondition>;
			template class fight::ConditionFactoryCasterTemplate<DetectObbCollisionCondition>;
			template class fight::PropertyEnumConstList<HitSurfaceCondition>;
			template class fight::PropertyBool<HitSurfaceCondition>;
			template class fight::ConditionFactoryTemplate<HitSurfaceCondition>;
			template class fight::ConditionFactoryCasterTemplate<HitSurfaceCondition>;
		}
	}
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::EnumEntry gHitSurfaceConditionSurfaceTable[3] =
				{
					{ fight::Name("Ground", 0) },
					{ fight::Name("Roof", 0) },
					{ fight::Name("Wall", 0) }
				};
		}
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D4D990
// FUNCTION: ENGINE 0x10D81370


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10149FD0
// FUNCTION: ENGINE 0x1014A000
// FUNCTION: ENGINE 0x1014A010
// FUNCTION: ENGINE 0x1014A040
// FUNCTION: ENGINE 0x1014A050
// FUNCTION: ENGINE 0x1014A080
// FUNCTION: ENGINE 0x1014A0B0
// FUNCTION: ENGINE 0x1014A0F0
// FUNCTION: ENGINE 0x1014A100
// FUNCTION: ENGINE 0x1014A120
// FUNCTION: ENGINE 0x1014A130
// FUNCTION: ENGINE 0x1014A190
// FUNCTION: ENGINE 0x1014A1C0
// FUNCTION: ENGINE 0x1014A1E0
// FUNCTION: ENGINE 0x1014A1F0
// FUNCTION: ENGINE 0x1014A220
// FUNCTION: ENGINE 0x1014A240
// FUNCTION: ENGINE 0x1014A250
// FUNCTION: ENGINE 0x1014A290
// FUNCTION: ENGINE 0x1014A2A0
// FUNCTION: ENGINE 0x1014A2D0
// FUNCTION: ENGINE 0x1014A2F0
// FUNCTION: ENGINE 0x1014A300
// FUNCTION: ENGINE 0x1014A330
// FUNCTION: ENGINE 0x1014A350
// FUNCTION: ENGINE 0x1014A510
// FUNCTION: ENGINE 0x1014A540
// FUNCTION: ENGINE 0x1014A560
// FUNCTION: ENGINE 0x1014A570
// FUNCTION: ENGINE 0x1014A5A0
// FUNCTION: ENGINE 0x1014A7A0
// FUNCTION: ENGINE 0x1014A7F0
// FUNCTION: ENGINE 0x1014A820
// FUNCTION: ENGINE 0x1014A840
// FUNCTION: ENGINE 0x100A2E50
// FUNCTION: ENGINE 0x100A2EB0
// FUNCTION: ENGINE 0x100A2280
// FUNCTION: ENGINE 0x100A2360
// FUNCTION: ENGINE 0x100A2560
// FUNCTION: ENGINE 0x100A2C90
// FUNCTION: ENGINE 0x100A2D20
// FUNCTION: ENGINE 0x100A2D70
// FUNCTION: ENGINE 0x100A2EC0
// FUNCTION: ENGINE 0x100A4970
// FUNCTION: ENGINE 0x100A59D0
// FUNCTION: ENGINE 0x100A59F0
// FUNCTION: ENGINE 0x100A5C30
// FUNCTION: ENGINE 0x100A5F60
// FUNCTION: ENGINE 0x100A25B0
// FUNCTION: ENGINE 0x100A2A10
// FUNCTION: ENGINE 0x100A2A40
// FUNCTION: ENGINE 0x100A2A90
// FUNCTION: ENGINE 0x100A2AE0
// FUNCTION: ENGINE 0x100A2FF0
// FUNCTION: ENGINE 0x100A3080
