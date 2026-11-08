// Fight items of the ai group: TankRamTrack (unit 0x10246860 - 0x10246F80; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_tankram.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/fightitems/ai/aiactionmessages.h"
#include "code/proto/fightitems/ai/aiactionhelpers.h"
#include "code/math/worldbounds.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gTankRamTrackProperties;  // 0x11255B54

			// FUNCTION: ENGINE 0x10246860
			bool TankRamTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246880
			bool TankRamTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102468A0
			bool TankRamTrack::SetTimePreparingForward(float newValue)
			{
				timePreparingForward = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102468C0
			bool TankRamTrack::SetTimePreparingBackward(float newValue)
			{
				timePreparingBackward = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102468E0
			bool TankRamTrack::SetMaxTurningSpeedFactor(float newValue)
			{
				maxTurningSpeedFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246900
			bool TankRamTrack::SetRollingScaleFactor(float newValue)
			{
				rollingScaleFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246920
			bool TankRamTrack::SetRollingScaleBackwardsFactor(float newValue)
			{
				rollingScaleBackwardsFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246940
			bool TankRamTrack::SetRollingScaleFactorPush(float newValue)
			{
				rollingScaleFactorPush = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246960
			bool TankRamTrack::SetRollingScaleBackwardsFactorPush(float newValue)
			{
				rollingScaleBackwardsFactorPush = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246980
			bool TankRamTrack::SetToleranceForward(float newValue)
			{
				toleranceForward = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102469A0
			bool TankRamTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102469C0
			fight::Property* TankRamTrack::GetProperty(int index)
			{
				return gTankRamTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102469E0
			void TankRamTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTankRamTrackProperties);
			}

			// FUNCTION: ENGINE 0x102469F0
			TankRamTrack::TankRamTrack() : maxTurningSpeedFactor(1.0f), rollingScaleBackwardsFactor(1.0f), rollingScaleBackwardsFactorPush(1.0f), rollingScaleFactor(1.0f), rollingScaleFactorPush(1.0f), speed(1.0f), timeBegin(0.0f), timeEnd(0.0f), timePreparingBackward(0.0f), timePreparingForward(0.0f), toleranceForward(0.8f)
			{
			}

			// FUNCTION: ENGINE 0x10246A70
			float TankRamTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10246A80
			float TankRamTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10246A90
			TankRamTrack::~TankRamTrack()
			{
			}

			// FUNCTION: ENGINE 0x10246BB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TankRamTrack::RegisterProperties()
			{
				if (gTankRamTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("timeBegin", &TankRamTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("timeEnd", &TankRamTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("timePreparingForward", &TankRamTrack::SetTimePreparingForward);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("timePreparingBackward", &TankRamTrack::SetTimePreparingBackward);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("maxTurningSpeedFactor", &TankRamTrack::SetMaxTurningSpeedFactor);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("rollingScaleFactor", &TankRamTrack::SetRollingScaleFactor);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("rollingScaleBackwardsFactor", &TankRamTrack::SetRollingScaleBackwardsFactor);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("rollingScaleFactorPush", &TankRamTrack::SetRollingScaleFactorPush);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("rollingScaleBackwardsFactorPush", &TankRamTrack::SetRollingScaleBackwardsFactorPush);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("toleranceForward", &TankRamTrack::SetToleranceForward);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("speed", &TankRamTrack::SetSpeed);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gTankRamTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10246B80
			fight::TrackFactory* CreateTankRamTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TankRamTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10246EB0
			void RegisterTankRamTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TankRamTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10208100
			// EQUIVALENT: scheduling; the integer store at +0x48 follows the float stores in the engine, ours hoists it; the same stores
			TankRamAction::TankRamAction(TankRamTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown30(0.0f), unknown34(-1.0f), unknown38(0.0f), unknown3C(0.0f), unknown40(0.0f), unknown44(0.0f), unknown48(0)
			{
			}

			// FUNCTION: ENGINE 0x10207F30
			TankRamAction::~TankRamAction()
			{
			}

			// FUNCTION: ENGINE 0x10207F60
			void TankRamAction::Slot6()
			{
				if (target.Get() != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						ClearVehicleAccelerationsMessage clearMessage;
						object->SendMessage(&clearMessage);
						SetBrakingInMotionMovementMessage brakeMessage(true);
						object->SendMessage(&brakeMessage);
						SetReverseGearMovementMessage reverseMessage(false);
						object->SendMessage(&reverseMessage);
					}
				}
			}

			// FUNCTION: ENGINE 0x102085F0
			// NONMATCHING: the engine shares the load of the two positions with the vector copies and keeps the other object in ecx, the negated direction is stored differently, about 33 %
#ifdef NONMATCHING
			bool TankRamAction::Slot7(int arg, float value)
			{
				if (link.Get() == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				engine::GameObject* other = unknown2C.Get();
				if (other == 0)
				{
					return false;
				}
				math::Vector direction;
				math::Vector reversed;
				switch (unknown48)
				{
				case 2:
					{
						math::Vector from(object->transform->value.m[3][0], object->transform->value.m[3][1], object->transform->value.m[3][2]);
						math::Vector to(other->transform->value.m[3][0], other->transform->value.m[3][1], other->transform->value.m[3][2]);
						direction.x = to.x - from.x;
						direction.y = 0.0f;
						direction.z = to.z - from.z;
					}
					direction.Normalize();
					direction.x = math::WORLD_MIN - direction.x;
					direction.y = math::WORLD_MIN - direction.y;
					direction.z = math::WORLD_MIN - direction.z;
					Unknown103B8510(object, link.Get()->speed, &direction, false);
					unknown38 = unknown38 + value;
					{
						TankRamTrack* track = link.Get();
						if (track->timePreparingForward < unknown38)
						{
							SetVehicleAccelerationsMessage accelerations;
							accelerations.unknownC = track->maxTurningSpeedFactor;
							accelerations.unknown10 = track->rollingScaleFactorPush;
							object->SendMessage(&accelerations);
							SetReverseGearMovementMessage reverse(false);
							object->SendMessage(&reverse);
							unknown48 = 1;
							return true;
						}
					}
					break;
				case 4:
					{
						math::Vector from(object->transform->value.m[3][0], object->transform->value.m[3][1], object->transform->value.m[3][2]);
						math::Vector to(other->transform->value.m[3][0], other->transform->value.m[3][1], other->transform->value.m[3][2]);
						direction.x = to.x - from.x;
						direction.y = 0.0f;
						direction.z = to.z - from.z;
					}
					direction.Normalize();
					reversed.x = math::WORLD_MIN - direction.x;
					reversed.y = math::WORLD_MIN - direction.y;
					reversed.z = math::WORLD_MIN - direction.z;
					Unknown103B8510(object, link.Get()->speed, &reversed, false);
					unknown38 = unknown38 + value;
					{
						TankRamTrack* track = link.Get();
						if (track->timePreparingBackward < unknown38)
						{
							SetVehicleAccelerationsMessage accelerations;
							accelerations.unknownC = track->maxTurningSpeedFactor;
							accelerations.unknown10 = track->rollingScaleBackwardsFactorPush;
							object->SendMessage(&accelerations);
							SetReverseGearMovementMessage reverse(true);
							object->SendMessage(&reverse);
							unknown48 = 3;
							return true;
						}
					}
					break;
				case 1:
				case 3:
					{
						math::Vector from(object->transform->value.m[3][0], object->transform->value.m[3][1], object->transform->value.m[3][2]);
						math::Vector to(other->transform->value.m[3][0], other->transform->value.m[3][1], other->transform->value.m[3][2]);
						direction.x = to.x - from.x;
						direction.y = 0.0f;
						direction.z = to.z - from.z;
					}
					direction.Normalize();
					Unknown103B8510(object, link.Get()->speed, &direction, false);
					break;
				default:
					return false;
				}
				return true;
			}
#endif

			// FUNCTION: ENGINE 0x102089D0
			fight::Action* TankRamTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new TankRamAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<TankRamTrack>;
			template class fight::TrackFactoryTemplate<TankRamTrack>;
			template class fight::TrackFactoryCasterTemplate<TankRamTrack>;
		}
	}
}

template core::Link<proto::fightitems::ai::TankRamTrack>::~Link();
template proto::fightitems::ai::TankRamTrack* core::Link<proto::fightitems::ai::TankRamTrack>::Get() const;
template core::Link<proto::fightitems::ai::TankRamTrack>::Link(proto::fightitems::ai::TankRamTrack*);

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10207E90
// FUNCTION: ENGINE 0x10207EC0
// FUNCTION: ENGINE 0x102081B0
// FUNCTION: ENGINE 0x10246AA0
// FUNCTION: ENGINE 0x10246AD0
// FUNCTION: ENGINE 0x10246AE0
// FUNCTION: ENGINE 0x10246B10
// FUNCTION: ENGINE 0x10246B40
// FUNCTION: ENGINE 0x10246B70
// FUNCTION: ENGINE 0x10246EE0
// FUNCTION: ENGINE 0x10246F10
// FUNCTION: ENGINE 0x10246F30
// FUNCTION: ENGINE 0x10207EB0
// FUNCTION: ENGINE 0x10207DA0
// FUNCTION: ENGINE 0x10207DE0
// FUNCTION: ENGINE 0x10207E30
// FUNCTION: ENGINE 0x102178F0
// FUNCTION: ENGINE 0x102179E0
