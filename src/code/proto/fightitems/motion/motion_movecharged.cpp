// Fight items of the motion group: MoveChargedTrack (unit 0x10193360 - 0x101939C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_movecharged.h"
#include "code/proto/fightitems/motion/motionmessages.h"
#include "code/engine/fight/fightcommon.h"

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
			fight::Property** gMoveChargedTrackProperties;  // 0x11254834

			// FUNCTION: ENGINE 0x10193360
			bool MoveChargedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193380
			bool MoveChargedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101933A0
			bool MoveChargedTrack::SetDistanceMin(const math::Vector& newValue)
			{
				distanceMin.x = newValue.x;
				distanceMin.y = newValue.y;
				distanceMin.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101933C0
			bool MoveChargedTrack::SetDistanceMax(const math::Vector& newValue)
			{
				distanceMax.x = newValue.x;
				distanceMax.y = newValue.y;
				distanceMax.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101933E0
			bool MoveChargedTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101933F0
			bool MoveChargedTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193410
			bool MoveChargedTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193430
			fight::Property* MoveChargedTrack::GetProperty(int index)
			{
				return gMoveChargedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10193450
			void MoveChargedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMoveChargedTrackProperties);
			}

			// FUNCTION: ENGINE 0x10193460
			MoveChargedTrack::MoveChargedTrack() : distanceMax(0.0f, 0.0f, 0.0f), distanceMin(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(1.0f), priority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101934E0
			float MoveChargedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101934F0
			float MoveChargedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10193500
			MoveChargedTrack::~MoveChargedTrack()
			{
			}

			// FUNCTION: ENGINE 0x101936E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MoveChargedTrack::RegisterProperties()
			{
				if (gMoveChargedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MoveChargedTrack>("timeBegin", &MoveChargedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MoveChargedTrack>("timeEnd", &MoveChargedTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<MoveChargedTrack>("distanceMin", &MoveChargedTrack::SetDistanceMin);
					properties[2] = property;
					property = new fight::PropertyVector<MoveChargedTrack>("distanceMax", &MoveChargedTrack::SetDistanceMax);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<MoveChargedTrack>("priority", &MoveChargedTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<MoveChargedTrack>("blendInTime", &MoveChargedTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<MoveChargedTrack>("blendOutTime", &MoveChargedTrack::SetBlendOutTime);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gMoveChargedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101936B0
			fight::TrackFactory* CreateMoveChargedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MoveChargedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101938F0
			void RegisterMoveChargedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MoveChargedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100F6070
			MoveChargedAction::MoveChargedAction(MoveChargedTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), driver(0), distance(0.0f, 0.0f, 0.0f)
			{
			}

			// FUNCTION: ENGINE 0x100F5F40
			MoveChargedAction::~MoveChargedAction()
			{
				engine::ReleaseDriverCopy2((choreo::Driver**)&driver);
			}

			// FUNCTION: ENGINE 0x100F6570
			fight::Action* MoveChargedTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new MoveChargedAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100F5F80
			void MoveChargedAction::Slot6()
			{
				if (driver != 0)
				{
					driver->mDelta.Reset();
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						choreo::Puppet* puppet = engine::GetPuppet(object);
						if (puppet != 0)
						{
							puppet->RemoveDriver(driver, false);
							engine::ReleaseDriverCopy2((choreo::Driver**)&driver);
						}
					}
				}
			}

			// FUNCTION: ENGINE 0x100F6120
			// NONMATCHING: the engine copies and updates the member vector component by component through memory with the minimum kept in registers, the clamp compares the message value in memory (75 %)
#ifdef NONMATCHING
			bool MoveChargedAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
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
				float blendIn = link.object->blendInTime;
				int priority = link.object->priority;
				float blendOut = link.object->blendOutTime;
				driver = new choreo::RootDriver;
				content::ObjectName driverName("moveCharged", 1);
				driver->SetName(driverName);
				driver->AddRef();
				driver->SetMask(1);
				puppet->SetDriver(driver, choreo::gMinusOne, priority, 1.0f, blendIn, blendOut, choreo::gMinusOne);
				ChargeGetMessage message(2);
				object->SendMessage(&message);
				if (message.value < 0.0f)
				{
					message.value = 0.0f;
				}
				if (0.0f <= message.value - engine::driving::gOne)
				{
					message.value = engine::driving::gOne;
				}
				float minX = link.object->distanceMin.x;
				float minY = link.object->distanceMin.y;
				float minZ = link.object->distanceMin.z;
				float maxX = link.object->distanceMax.x;
				float maxY = link.object->distanceMax.y;
				float maxZ = link.object->distanceMax.z;
				distance.x = maxX;
				distance.y = maxY;
				distance.z = maxZ;
				distance.x = distance.x - minX;
				distance.y = distance.y - minY;
				distance.z = distance.z - minZ;
				distance.x = distance.x * message.value;
				distance.z = message.value * distance.z;
				distance.y = message.value * distance.y;
				distance.x = distance.x + minX;
				distance.y = distance.y + minY;
				distance.z = distance.z + minZ;
				return true;
			}
#endif

			// FUNCTION: ENGINE 0x100F63C0
			// NONMATCHING: the engine keeps the track in ecx after its test, orders the clamp of the blend factor as comiss t, 0 / jae and scales the three components in registers (21 %)
#ifdef NONMATCHING
			bool MoveChargedAction::Slot7(int arg, float value)
			{
				if (arg == 0)
				{
					if (driver == 0)
					{
						return false;
					}
					if (link.object == 0)
					{
						return false;
					}
					engine::GameObject* object = target.Get();
					if (object == 0)
					{
						return false;
					}
					math::Vector offset;
					offset.x = distance.x;
					offset.y = distance.y;
					offset.z = distance.z;
					float duration = link.object->Slot10();
					if (duration > 0.0f)
					{
						float t = value / duration;
						if (t < 0.0f)
						{
							t = 0.0f;
						}
						if (0.0f <= t - engine::driving::gOne)
						{
							t = engine::driving::gOne;
						}
						offset.x = t * offset.x;
						offset.y = t * offset.y;
						offset.z = offset.z * t;
					}
					if (0.00001f < value)
					{
						float inverse = engine::driving::gOne / value;
						math::Vector velocity;
						velocity.x = offset.x * inverse;
						velocity.y = offset.y * inverse;
						velocity.z = offset.z * inverse;
						driver->mDelta.SetVelocity(velocity);
						return true;
					}
					driver->mDelta.SetDelta(offset);
				}
				return true;
			}
#endif

			// ---- actions end
			template class fight::PropertyFloatConstRange<MoveChargedTrack>;
			template class fight::PropertyVector<MoveChargedTrack>;
			template class fight::PropertyIntConstRange<MoveChargedTrack>;
			template class fight::TrackFactoryTemplate<MoveChargedTrack>;
			template class fight::TrackFactoryCasterTemplate<MoveChargedTrack>;
		}
	}
}

template proto::fightitems::motion::MoveChargedTrack* core::Link<proto::fightitems::motion::MoveChargedTrack>::Get() const;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100F5EC0
// FUNCTION: ENGINE 0x100F5EA0
// FUNCTION: ENGINE 0x100F5ED0
// FUNCTION: ENGINE 0x100F60F0
// FUNCTION: ENGINE 0x10193510
// FUNCTION: ENGINE 0x10193540
// FUNCTION: ENGINE 0x10193550
// FUNCTION: ENGINE 0x10193580
// FUNCTION: ENGINE 0x101935B0
// FUNCTION: ENGINE 0x101935E0
// FUNCTION: ENGINE 0x101935F0
// FUNCTION: ENGINE 0x10193620
// FUNCTION: ENGINE 0x10193640
// FUNCTION: ENGINE 0x10193650
// FUNCTION: ENGINE 0x10193680
// FUNCTION: ENGINE 0x101936A0
// FUNCTION: ENGINE 0x10193920
// FUNCTION: ENGINE 0x10193950
// FUNCTION: ENGINE 0x10193970
