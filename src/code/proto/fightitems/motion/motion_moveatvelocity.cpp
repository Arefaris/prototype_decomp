// Fight items of the motion group: MoveAtVelocityTrack (unit 0x10192C50 - 0x10193360; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_moveatvelocity.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/math/worldbounds.h"
#include "code/engine/fight/fightcommon.h"

namespace engine
{
	// 0x1005E140: the intention of the character an object is (another unit's copy; name guess)
	CharacterIntention* QueryCharacterIntention(GameObject* object);
}

namespace choreo
{
	extern const float gMinusOne;
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gMoveAtVelocityTrackProperties;  // 0x11254830

			// FUNCTION: ENGINE 0x10192C50
			bool MoveAtVelocityTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192C70
			bool MoveAtVelocityTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192C90
			bool MoveAtVelocityTrack::SetVelocityBegin(const math::Vector& newValue)
			{
				velocityBegin.x = newValue.x;
				velocityBegin.y = newValue.y;
				velocityBegin.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10192CB0
			bool MoveAtVelocityTrack::SetVelocityEnd(const math::Vector& newValue)
			{
				velocityEnd.x = newValue.x;
				velocityEnd.y = newValue.y;
				velocityEnd.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10192CD0
			bool MoveAtVelocityTrack::SetUseInput(bool newValue)
			{
				useInput = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192CE0
			bool MoveAtVelocityTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192CF0
			bool MoveAtVelocityTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192D10
			bool MoveAtVelocityTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192D30
			fight::Property* MoveAtVelocityTrack::GetProperty(int index)
			{
				return gMoveAtVelocityTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10192D50
			void MoveAtVelocityTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMoveAtVelocityTrackProperties);
			}

			// FUNCTION: ENGINE 0x10192D60
			MoveAtVelocityTrack::MoveAtVelocityTrack() : velocityBegin(0.0f, 0.0f, 0.0f), velocityEnd(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(1.0f), priority(-5), useInput(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10192DE0
			float MoveAtVelocityTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10192DF0
			float MoveAtVelocityTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10192E00
			MoveAtVelocityTrack::~MoveAtVelocityTrack()
			{
			}

			// FUNCTION: ENGINE 0x10193040
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MoveAtVelocityTrack::RegisterProperties()
			{
				if (gMoveAtVelocityTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MoveAtVelocityTrack>("timeBegin", &MoveAtVelocityTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MoveAtVelocityTrack>("timeEnd", &MoveAtVelocityTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<MoveAtVelocityTrack>("velocityBegin", &MoveAtVelocityTrack::SetVelocityBegin);
					properties[2] = property;
					property = new fight::PropertyVector<MoveAtVelocityTrack>("velocityEnd", &MoveAtVelocityTrack::SetVelocityEnd);
					properties[3] = property;
					property = new fight::PropertyBool<MoveAtVelocityTrack>("useInput", &MoveAtVelocityTrack::SetUseInput);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<MoveAtVelocityTrack>("priority", &MoveAtVelocityTrack::SetPriority);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<MoveAtVelocityTrack>("blendInTime", &MoveAtVelocityTrack::SetBlendInTime);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<MoveAtVelocityTrack>("blendOutTime", &MoveAtVelocityTrack::SetBlendOutTime);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gMoveAtVelocityTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10193010
			fight::TrackFactory* CreateMoveAtVelocityTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MoveAtVelocityTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10193290
			void RegisterMoveAtVelocityTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MoveAtVelocityTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100F5930
			MoveAtVelocityAction::MoveAtVelocityAction(MoveAtVelocityTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), driver(0), unknown30(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x100F5810
			MoveAtVelocityAction::~MoveAtVelocityAction()
			{
				engine::ReleaseDriverCopy2((choreo::Driver**)&driver);
			}

			// FUNCTION: ENGINE 0x100F5DD0
			fight::Action* MoveAtVelocityTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new MoveAtVelocityAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100F5850
			void MoveAtVelocityAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0 && driver != 0)
				{
					choreo::Puppet* puppet = engine::GetPuppet(object);
					if (puppet != 0)
					{
						puppet->RemoveDriver(driver, false);
						engine::ReleaseDriverCopy2((choreo::Driver**)&driver);
					}
				}
			}

			// FUNCTION: ENGINE 0x100F59D0
			bool MoveAtVelocityAction::Slot5(int arg, float value)
			{
				if (link.Get() == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				choreo::Puppet* puppet = engine::GetPuppet(object);
				if (puppet == 0)
				{
					return false;
				}
				float blendIn = link.Get()->blendInTime;
				int priority = link.Get()->priority;
				float blendOut = link.Get()->blendOutTime;
				driver = new choreo::RootDriver;
				content::ObjectName driverName("moveAtVelocity", 1);
				driver->SetName(driverName);
				driver->AddRef();
				driver->SetMask(1);
				puppet->SetDriver(driver, choreo::gMinusOne, priority, 1.0f, blendIn, blendOut, choreo::gMinusOne);
				return true;
			}

			// FUNCTION: ENGINE 0x100F5B10
			// NONMATCHING: the engine holds the zero and gOne in registers from the duration test on and interleaves the three loads, subtractions, products and sums of the blend; the frame is 8 bytes larger (41 %)
#ifdef NONMATCHING
			bool MoveAtVelocityAction::Slot7(int arg, float value)
			{
				if (arg != 0)
				{
					return true;
				}
				if (driver == 0)
				{
					return false;
				}
				if (link.Get() == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				unknown30 = unknown30 + value;
				math::Vector velocity;
				velocity.x = link.Get()->velocityBegin.x;
				velocity.y = link.Get()->velocityBegin.y;
				velocity.z = link.Get()->velocityBegin.z;
				float duration = link.Get()->Slot10();
				if (duration > 0.0f)
				{
					float t = unknown30 / duration;
					if (t < 0.0f)
					{
						t = 0.0f;
					}
					if (0.0f <= t - engine::driving::gOne)
					{
						t = engine::driving::gOne;
					}
					const math::Vector& end = link.Get()->velocityEnd;
					float x = (end.x - velocity.x) * t + velocity.x;
					float y = (end.y - velocity.y) * t + velocity.y;
					float z = (end.z - velocity.z) * t + velocity.z;
					velocity.x = x;
					velocity.y = y;
					velocity.z = z;
				}
				if (link.Get()->useInput)
				{
					engine::CharacterIntention* intention = engine::QueryCharacterIntention(object);
					if (intention != 0)
					{
						float forward = math::WORLD_MIN - intention->GetAxisCopy(1)->x;
						float sideways = math::WORLD_MIN - intention->GetAxisCopy(0)->x;
						float length = velocity.Normalize();
						float amount = sideways * velocity.z + forward * velocity.x + velocity.y * 0.0f;
						if (amount < 0.0f)
						{
							amount = 0.0f;
						}
						if (0.0f <= amount - engine::driving::gOne)
						{
							amount = engine::driving::gOne;
						}
						amount = amount * length;
						velocity.x = amount * velocity.x;
						velocity.y = velocity.y * amount;
						velocity.z = velocity.z * amount;
					}
				}
				driver->mDelta.SetVelocity(velocity);
				return true;
			}
#endif

			// ---- actions end
			template class fight::PropertyFloatConstRange<MoveAtVelocityTrack>;
			template class fight::PropertyVector<MoveAtVelocityTrack>;
			template class fight::PropertyBool<MoveAtVelocityTrack>;
			template class fight::PropertyIntConstRange<MoveAtVelocityTrack>;
			template class fight::TrackFactoryTemplate<MoveAtVelocityTrack>;
			template class fight::TrackFactoryCasterTemplate<MoveAtVelocityTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100F5770
// FUNCTION: ENGINE 0x100F57A0
// FUNCTION: ENGINE 0x100F59A0
// FUNCTION: ENGINE 0x10192E10
// FUNCTION: ENGINE 0x10192E40
// FUNCTION: ENGINE 0x10192E50
// FUNCTION: ENGINE 0x10192E80
// FUNCTION: ENGINE 0x10192EB0
// FUNCTION: ENGINE 0x10192EE0
// FUNCTION: ENGINE 0x10192EF0
// FUNCTION: ENGINE 0x10192F20
// FUNCTION: ENGINE 0x10192F40
// FUNCTION: ENGINE 0x10192F50
// FUNCTION: ENGINE 0x10192F80
// FUNCTION: ENGINE 0x10192FA0
// FUNCTION: ENGINE 0x10192FB0
// FUNCTION: ENGINE 0x10192FE0
// FUNCTION: ENGINE 0x10193000
// FUNCTION: ENGINE 0x101932C0
// FUNCTION: ENGINE 0x101932F0
// FUNCTION: ENGINE 0x10193310
