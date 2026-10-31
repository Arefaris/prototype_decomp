// Fight items of the motion group: ImpulseTrack (unit 0x10180910 - 0x10180EC0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_impulse.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gImpulseTrackProperties;  // 0x11254748

			// FUNCTION: ENGINE 0x10180910
			bool ImpulseTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10180930
			bool ImpulseTrack::SetImpulse(const math::Vector& newValue)
			{
				impulse.x = newValue.x;
				impulse.y = newValue.y;
				impulse.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101809C0
			bool ImpulseTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10180950
			bool ImpulseTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10180970
			bool ImpulseTrack::SetOrientation(const math::Vector& newValue)
			{
				orientation.x = newValue.x;
				orientation.y = newValue.y;
				orientation.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10180990
			fight::Property* ImpulseTrack::GetProperty(int index)
			{
				return gImpulseTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101809B0
			void ImpulseTrack::ClearProperties()
			{
				fight::FreePropertyList(&gImpulseTrackProperties);
			}

			// FUNCTION: ENGINE 0x101809E0
			ImpulseTrack::ImpulseTrack() : joint("", 1), impulse(0.0f, 0.0f, 0.0f), offset(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10180A60
			float ImpulseTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10180A70
			float ImpulseTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10180A80
			ImpulseTrack::~ImpulseTrack()
			{
			}

			// FUNCTION: ENGINE 0x10180C90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ImpulseTrack::RegisterProperties()
			{
				if (gImpulseTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ImpulseTrack>("timeBegin", &ImpulseTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyVector<ImpulseTrack>("impulse", &ImpulseTrack::SetImpulse);
					properties[1] = property;
					property = new fight::PropertyNameList<ImpulseTrack>("joint", &ImpulseTrack::SetJoint);
					properties[2] = property;
					property = new fight::PropertyVector<ImpulseTrack>("offset", &ImpulseTrack::SetOffset);
					properties[3] = property;
					property = new fight::PropertyVector<ImpulseTrack>("orientation", &ImpulseTrack::SetOrientation);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gImpulseTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10180BD0
			fight::TrackFactory* CreateImpulseTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ImpulseTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10180C00
			void RegisterImpulseTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ImpulseTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<ImpulseTrack>;
			template class fight::PropertyVector<ImpulseTrack>;
			template class fight::PropertyNameList<ImpulseTrack>;
			template class fight::TrackFactoryTemplate<ImpulseTrack>;
			template class fight::TrackFactoryCasterTemplate<ImpulseTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10180A90
// FUNCTION: ENGINE 0x10180AA0
// FUNCTION: ENGINE 0x10180AD0
// FUNCTION: ENGINE 0x10180B00
// FUNCTION: ENGINE 0x10180B30
// FUNCTION: ENGINE 0x10180B60
// FUNCTION: ENGINE 0x10180B70
// FUNCTION: ENGINE 0x10180BA0
// FUNCTION: ENGINE 0x10180BC0
// FUNCTION: ENGINE 0x10180C30
// FUNCTION: ENGINE 0x10180C60
// FUNCTION: ENGINE 0x10180C80
// FUNCTION: ENGINE 0x10180E20
// FUNCTION: ENGINE 0x10180E50
// FUNCTION: ENGINE 0x10180E70
