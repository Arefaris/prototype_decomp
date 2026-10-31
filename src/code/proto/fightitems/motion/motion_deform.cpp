// Fight items of the motion group: DeformTrack (unit 0x10153950 - 0x10154030; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_deform.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDeformTrackProperties;  // 0x112543E0

			// FUNCTION: ENGINE 0x10153950
			bool DeformTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10153A60
			bool DeformTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10153970
			bool DeformTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10153990
			bool DeformTrack::SetDirection(const math::Vector& newValue)
			{
				direction.x = newValue.x;
				direction.y = newValue.y;
				direction.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101539B0
			bool DeformTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101539D0
			bool DeformTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101539F0
			bool DeformTrack::SetDeformDirStr(float newValue)
			{
				deformDirStr = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10153A10
			bool DeformTrack::SetStrength(float newValue)
			{
				strength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10153A30
			fight::Property* DeformTrack::GetProperty(int index)
			{
				return gDeformTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10153A50
			void DeformTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDeformTrackProperties);
			}

			// FUNCTION: ENGINE 0x10153A80
			DeformTrack::DeformTrack() : direction(0.0f, -1.0f, 0.0f), offset(0.0f, 0.0f, 0.0f), blendTime(1.0f), deformDirStr(1.0f), radius(1.0f), strength(1.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10153B10
			float DeformTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10153B20
			float DeformTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10153B30
			DeformTrack::~DeformTrack()
			{
			}

			// FUNCTION: ENGINE 0x10153D40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DeformTrack::RegisterProperties()
			{
				if (gDeformTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DeformTrack>("timeBegin", &DeformTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<DeformTrack>("joint", &DeformTrack::SetJoint);
					properties[1] = property;
					property = new fight::PropertyVector<DeformTrack>("offset", &DeformTrack::SetOffset);
					properties[2] = property;
					property = new fight::PropertyVector<DeformTrack>("direction", &DeformTrack::SetDirection);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<DeformTrack>("radius", &DeformTrack::SetRadius);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<DeformTrack>("blendTime", &DeformTrack::SetBlendTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<DeformTrack>("deformDirStr", &DeformTrack::SetDeformDirStr);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<DeformTrack>("strength", &DeformTrack::SetStrength);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gDeformTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10153C80
			fight::TrackFactory* CreateDeformTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DeformTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10153CB0
			void RegisterDeformTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DeformTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<DeformTrack>;
			template class fight::PropertyNameList<DeformTrack>;
			template class fight::PropertyVector<DeformTrack>;
			template class fight::TrackFactoryTemplate<DeformTrack>;
			template class fight::TrackFactoryCasterTemplate<DeformTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10153B40
// FUNCTION: ENGINE 0x10153B50
// FUNCTION: ENGINE 0x10153B80
// FUNCTION: ENGINE 0x10153BB0
// FUNCTION: ENGINE 0x10153BE0
// FUNCTION: ENGINE 0x10153C10
// FUNCTION: ENGINE 0x10153C20
// FUNCTION: ENGINE 0x10153C50
// FUNCTION: ENGINE 0x10153C70
// FUNCTION: ENGINE 0x10153CE0
// FUNCTION: ENGINE 0x10153D10
// FUNCTION: ENGINE 0x10153D30
// FUNCTION: ENGINE 0x10153F90
// FUNCTION: ENGINE 0x10153FC0
// FUNCTION: ENGINE 0x10153FE0
