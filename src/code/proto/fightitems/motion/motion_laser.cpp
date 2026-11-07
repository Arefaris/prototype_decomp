// Fight items of the motion group: LaserTrack (unit 0x10187250 - 0x10187C50; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_laser.h"
#include "code/engine/physics/getintersectionpropertiesmessage.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gLaserTrackProperties;  // 0x112547A8

			// FUNCTION: ENGINE 0x10187250
			bool LaserTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187270
			bool LaserTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101873F0
			bool LaserTrack::SetShader(const fight::Name& newValue)
			{
				shader = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187290
			bool LaserTrack::SetThickness(float newValue)
			{
				thickness = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101872B0
			bool LaserTrack::SetColour(const math::Colour128& newValue)
			{
				colour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187410
			bool LaserTrack::SetMyJoint(const fight::Name& newValue)
			{
				myJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101872E0
			bool LaserTrack::SetMyOffset(const math::Vector& newValue)
			{
				myOffset.x = newValue.x;
				myOffset.y = newValue.y;
				myOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10187430
			bool LaserTrack::SetTargetJoint(const fight::Name& newValue)
			{
				targetJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187300
			bool LaserTrack::SetTargetOffset(const math::Vector& newValue)
			{
				targetOffset.x = newValue.x;
				targetOffset.y = newValue.y;
				targetOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10187320
			bool LaserTrack::SetTrackingSpeed(float newValue)
			{
				trackingSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187340
			bool LaserTrack::SetLongitudinalOffset(float newValue)
			{
				longitudinalOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187360
			bool LaserTrack::SetPerpendicularOffset(float newValue)
			{
				perpendicularOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187380
			bool LaserTrack::SetPerpendicularFinalOffset(float newValue)
			{
				perpendicularFinalOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101873A0
			bool LaserTrack::SetPerpendicularFinalTime(float newValue)
			{
				perpendicularFinalTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101873C0
			fight::Property* LaserTrack::GetProperty(int index)
			{
				return gLaserTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101873E0
			void LaserTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLaserTrackProperties);
			}

			// FUNCTION: ENGINE 0x10187450
			LaserTrack::LaserTrack() : colour(1.0f, 1.0f, 1.0f, 1.0f), myOffset(0.0f, 0.0f, 0.0f), targetOffset(0.0f, 0.0f, 0.0f), longitudinalOffset(1.0f), perpendicularFinalOffset(0.0f), perpendicularFinalTime(-1.0f), perpendicularOffset(0.0f), thickness(1.0f), timeBegin(0.0f), timeEnd(-1.0f), trackingSpeed(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10187510
			float LaserTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10187520
			float LaserTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10187530
			LaserTrack::~LaserTrack()
			{
			}

			// FUNCTION: ENGINE 0x101877F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LaserTrack::RegisterProperties()
			{
				if (gLaserTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LaserTrack>("timeBegin", &LaserTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LaserTrack>("timeEnd", &LaserTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<LaserTrack>("shader", &LaserTrack::SetShader);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LaserTrack>("thickness", &LaserTrack::SetThickness);
					properties[3] = property;
					property = new fight::PropertyColour<LaserTrack>("colour", &LaserTrack::SetColour);
					properties[4] = property;
					property = new fight::PropertyNameList<LaserTrack>("myJoint", &LaserTrack::SetMyJoint);
					properties[5] = property;
					property = new fight::PropertyVector<LaserTrack>("myOffset", &LaserTrack::SetMyOffset);
					properties[6] = property;
					property = new fight::PropertyNameList<LaserTrack>("targetJoint", &LaserTrack::SetTargetJoint);
					properties[7] = property;
					property = new fight::PropertyVector<LaserTrack>("targetOffset", &LaserTrack::SetTargetOffset);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<LaserTrack>("trackingSpeed", &LaserTrack::SetTrackingSpeed);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<LaserTrack>("longitudinalOffset", &LaserTrack::SetLongitudinalOffset);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<LaserTrack>("perpendicularOffset", &LaserTrack::SetPerpendicularOffset);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<LaserTrack>("perpendicularFinalOffset", &LaserTrack::SetPerpendicularFinalOffset);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<LaserTrack>("perpendicularFinalTime", &LaserTrack::SetPerpendicularFinalTime);
					properties[13] = property;
					fight::RegisterPropertyList(properties, &gLaserTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101876E0
			fight::TrackFactory* CreateLaserTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LaserTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10187710
			void RegisterLaserTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LaserTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100E40D0
			// NONMATCHING: the engine stores the last component of the vector before the flag and the word behind it (92 %)
#ifdef NONMATCHING
			LaserAction::LaserAction(LaserTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), drawable(0xffffffff), unknown30(0.0f)
			{
				unknown34.x = math::kZeroVector.x;
				unknown34.y = math::kZeroVector.y;
				unknown34.z = math::kZeroVector.z;
				unknown40 = false;
				unknown44 = 0;
			}
#endif

			// FUNCTION: ENGINE 0x100E3BB0
			LaserAction::~LaserAction()
			{
				if (drawable.IsValid())
				{
					engine::render::Drawable::Destroy(&drawable, 0);
				}
			}

			// FUNCTION: ENGINE 0x100E3A80
			void LaserAction::Slot6()
			{
				if (drawable.IsValid())
				{
					engine::render::Drawable::Destroy(&drawable, 0);
				}
			}

			// FUNCTION: ENGINE 0x100E44D0
			fight::Action* LaserTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new LaserAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100E3C00
			bool LaserAction::Slot5(int arg, float value)
			{
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				engine::GetIntersectionPropertiesMessage message;
				object->PostMessage(&message);
				unknown44 = message.result;
				return true;
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<LaserTrack>;
			template class fight::PropertyName<LaserTrack>;
			template class fight::PropertyColour<LaserTrack>;
			template class fight::PropertyNameList<LaserTrack>;
			template class fight::PropertyVector<LaserTrack>;
			template class fight::TrackFactoryTemplate<LaserTrack>;
			template class fight::TrackFactoryCasterTemplate<LaserTrack>;
		}
	}
}

template proto::fightitems::motion::LaserTrack* core::Link<proto::fightitems::motion::LaserTrack>::Get() const;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100E3B20
// FUNCTION: ENGINE 0x10187540
// FUNCTION: ENGINE 0x10187550
// FUNCTION: ENGINE 0x10187580
// FUNCTION: ENGINE 0x101875B0
// FUNCTION: ENGINE 0x101875E0
// FUNCTION: ENGINE 0x10187610
// FUNCTION: ENGINE 0x10187620
// FUNCTION: ENGINE 0x10187650
// FUNCTION: ENGINE 0x10187670
// FUNCTION: ENGINE 0x10187680
// FUNCTION: ENGINE 0x101876B0
// FUNCTION: ENGINE 0x101876D0
// FUNCTION: ENGINE 0x10187740
// FUNCTION: ENGINE 0x10187770
// FUNCTION: ENGINE 0x10187790
// FUNCTION: ENGINE 0x101877C0
// FUNCTION: ENGINE 0x101877E0
// FUNCTION: ENGINE 0x10187BB0
// FUNCTION: ENGINE 0x10187BE0
// FUNCTION: ENGINE 0x10187C00
