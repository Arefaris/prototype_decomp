// Fight items of the motion group: DecalTrack (unit 0x10153160 - 0x10153950; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_decal.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDecalTrackProperties;  // 0x112543DC

			// FUNCTION: ENGINE 0x10153160
			bool DecalTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10153290
			bool DecalTrack::SetShaderName(const fight::Name& newValue)
			{
				shaderName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10153180
			bool DecalTrack::SetOrientation(float newValue)
			{
				orientation = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101531A0
			bool DecalTrack::SetScaleX(float newValue)
			{
				scaleX = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101531C0
			bool DecalTrack::SetScaleY(float newValue)
			{
				scaleY = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101532B0
			bool DecalTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101531E0
			bool DecalTrack::SetPositionOffset(const math::Vector& newValue)
			{
				positionOffset.x = newValue.x;
				positionOffset.y = newValue.y;
				positionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10153200
			bool DecalTrack::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10153220
			bool DecalTrack::SetMinNormalArc(float newValue)
			{
				minNormalArc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10153240
			bool DecalTrack::SetFadeOutTime(float newValue)
			{
				fadeOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10153260
			fight::Property* DecalTrack::GetProperty(int index)
			{
				return gDecalTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10153280
			void DecalTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDecalTrackProperties);
			}

			// FUNCTION: ENGINE 0x101532D0
			DecalTrack::DecalTrack() : positionOffset(0.0f, 0.0f, 0.0f), fadeOutTime(-1.0f), maxDistance(-1.0f), minNormalArc(-0.017453292f), orientation(0.0f), scaleX(1.0f), scaleY(1.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10153370
			float DecalTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10153380
			float DecalTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10153390
			DecalTrack::~DecalTrack()
			{
			}

			// FUNCTION: ENGINE 0x101535F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DecalTrack::RegisterProperties()
			{
				if (gDecalTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DecalTrack>("timeBegin", &DecalTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<DecalTrack>("shaderName", &DecalTrack::SetShaderName);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DecalTrack>("orientation", &DecalTrack::SetOrientation);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<DecalTrack>("scaleX", &DecalTrack::SetScaleX);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<DecalTrack>("scaleY", &DecalTrack::SetScaleY);
					properties[4] = property;
					property = new fight::PropertyNameList<DecalTrack>("joint", &DecalTrack::SetJoint);
					properties[5] = property;
					property = new fight::PropertyVector<DecalTrack>("positionOffset", &DecalTrack::SetPositionOffset);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<DecalTrack>("maxDistance", &DecalTrack::SetMaxDistance);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<DecalTrack>("minNormalArc", &DecalTrack::SetMinNormalArc);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<DecalTrack>("fadeOutTime", &DecalTrack::SetFadeOutTime);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gDecalTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101534E0
			fight::TrackFactory* CreateDecalTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DecalTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10153510
			void RegisterDecalTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DecalTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<DecalTrack>;
			template class fight::PropertyName<DecalTrack>;
			template class fight::PropertyNameList<DecalTrack>;
			template class fight::PropertyVector<DecalTrack>;
			template class fight::TrackFactoryTemplate<DecalTrack>;
			template class fight::TrackFactoryCasterTemplate<DecalTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101533A0
// FUNCTION: ENGINE 0x101533B0
// FUNCTION: ENGINE 0x101533E0
// FUNCTION: ENGINE 0x10153410
// FUNCTION: ENGINE 0x10153440
// FUNCTION: ENGINE 0x10153470
// FUNCTION: ENGINE 0x10153480
// FUNCTION: ENGINE 0x101534B0
// FUNCTION: ENGINE 0x101534D0
// FUNCTION: ENGINE 0x10153540
// FUNCTION: ENGINE 0x10153570
// FUNCTION: ENGINE 0x10153590
// FUNCTION: ENGINE 0x101535C0
// FUNCTION: ENGINE 0x101535E0
// FUNCTION: ENGINE 0x101538B0
// FUNCTION: ENGINE 0x101538E0
// FUNCTION: ENGINE 0x10153900
