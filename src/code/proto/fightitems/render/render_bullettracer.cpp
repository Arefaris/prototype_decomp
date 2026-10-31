// Fight items of the render group: BulletTracerTrack (unit 0x1025FC60 - 0x10262C90; no assert path, the file name is a guess).
#include "code/proto/fightitems/render/render_bullettracer.h"

namespace proto
{
	namespace fightitems
	{
		namespace render
		{
			fight::Property** gBulletTracerTrackProperties;  // 0x11255DC8

			// FUNCTION: ENGINE 0x102618D0
			bool BulletTracerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102618F0
			bool BulletTracerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261910
			bool BulletTracerTrack::SetWait(float newValue)
			{
				wait = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261D90
			bool BulletTracerTrack::SetHeadParametersShader(const fight::Name& newValue)
			{
				headParametersShader = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261930
			bool BulletTracerTrack::SetHeadParametersGenerateTime(float newValue)
			{
				headParametersGenerateTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261950
			bool BulletTracerTrack::SetHeadParametersFadeInTime(float newValue)
			{
				headParametersFadeInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261970
			bool BulletTracerTrack::SetHeadParametersFadeOutTime(float newValue)
			{
				headParametersFadeOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261990
			bool BulletTracerTrack::SetHeadParametersFadeInTrailTime(float newValue)
			{
				headParametersFadeInTrailTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102619B0
			bool BulletTracerTrack::SetHeadParametersFadeOutTrailTime(float newValue)
			{
				headParametersFadeOutTrailTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102619D0
			bool BulletTracerTrack::SetHeadParametersShrinkInTime(float newValue)
			{
				headParametersShrinkInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102619F0
			bool BulletTracerTrack::SetHeadParametersShrinkOutTime(float newValue)
			{
				headParametersShrinkOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261A10
			bool BulletTracerTrack::SetHeadParametersThickness(float newValue)
			{
				headParametersThickness = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261A30
			bool BulletTracerTrack::SetHeadParametersTextureLength(float newValue)
			{
				headParametersTextureLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261A50
			bool BulletTracerTrack::SetHeadParametersTextureScrollRate(float newValue)
			{
				headParametersTextureScrollRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261A70
			bool BulletTracerTrack::SetHeadParametersStartColour(const math::Colour128& newValue)
			{
				headParametersStartColour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261AA0
			bool BulletTracerTrack::SetHeadParametersEndColour(const math::Colour128& newValue)
			{
				headParametersEndColour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261DB0
			bool BulletTracerTrack::SetTailParametersShader(const fight::Name& newValue)
			{
				tailParametersShader = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261AD0
			bool BulletTracerTrack::SetTailParametersGenerateTime(float newValue)
			{
				tailParametersGenerateTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261AF0
			bool BulletTracerTrack::SetTailParametersFadeInTime(float newValue)
			{
				tailParametersFadeInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261B10
			bool BulletTracerTrack::SetTailParametersFadeOutTime(float newValue)
			{
				tailParametersFadeOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261B30
			bool BulletTracerTrack::SetTailParametersFadeInTrailTime(float newValue)
			{
				tailParametersFadeInTrailTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261B50
			bool BulletTracerTrack::SetTailParametersFadeOutTrailTime(float newValue)
			{
				tailParametersFadeOutTrailTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261B70
			bool BulletTracerTrack::SetTailParametersShrinkInTime(float newValue)
			{
				tailParametersShrinkInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261B90
			bool BulletTracerTrack::SetTailParametersShrinkOutTime(float newValue)
			{
				tailParametersShrinkOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261BB0
			bool BulletTracerTrack::SetTailParametersThickness(float newValue)
			{
				tailParametersThickness = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261BD0
			bool BulletTracerTrack::SetTailParametersTextureLength(float newValue)
			{
				tailParametersTextureLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261BF0
			bool BulletTracerTrack::SetTailParametersTextureScrollRate(float newValue)
			{
				tailParametersTextureScrollRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261C10
			bool BulletTracerTrack::SetTailParametersStartColour(const math::Colour128& newValue)
			{
				tailParametersStartColour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261C40
			bool BulletTracerTrack::SetTailParametersEndColour(const math::Colour128& newValue)
			{
				tailParametersEndColour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261C70
			bool BulletTracerTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10261DD0
			bool BulletTracerTrack::SetAttachJoint(const fight::Name& newValue)
			{
				attachJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10261C90
			fight::Property* BulletTracerTrack::GetProperty(int index)
			{
				return gBulletTracerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10261CB0
			void BulletTracerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gBulletTracerTrackProperties);
			}

			// FUNCTION: ENGINE 0x10261CC0
			void BulletTracerTrack::ApplyGroup(int group, bool value)
			{
				const int* members;
				switch (group)
				{
				case 0:
					members = gBulletTracerTrackHeadParametersMembers;
					value = value && headParameters;
					break;
				case 1:
					members = gBulletTracerTrackTailParametersMembers;
					value = value && tailParameters;
					break;
				default:
					return;
				}
				for (int i = 0; members[i] != -1; i++)
				{
					unsigned __int64 bit = 1ui64 << members[i];
					if (value)
					{
						overrideMask |= bit;
					}
					else
					{
						overrideMask &= ~bit;
					}
					ApplyGroup(members[i], value);
				}
			}

			// FUNCTION: ENGINE 0x10261FC0
			bool BulletTracerTrack::Slot16(int index)
			{
				return (overrideMask & (1ui64 << index)) != 0;
			}

			// FUNCTION: ENGINE 0x10262020
			bool BulletTracerTrack::SetHeadParameters(bool newValue)
			{
				headParameters = newValue;
				ApplyGroup(0, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x10262040
			bool BulletTracerTrack::SetTailParameters(bool newValue)
			{
				tailParameters = newValue;
				ApplyGroup(1, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x10261DF0
			BulletTracerTrack::BulletTracerTrack() : headParametersEndColour(1.0f, 1.0f, 1.0f, 1.0f), headParametersStartColour(1.0f, 1.0f, 1.0f, 1.0f), tailParametersEndColour(1.0f, 1.0f, 1.0f, 1.0f), tailParametersStartColour(1.0f, 1.0f, 1.0f, 1.0f), offset(0.0f, 0.0f, 0.0f), headParametersFadeInTime(1.0f), headParametersFadeInTrailTime(1.0f), headParametersFadeOutTime(1.0f), headParametersFadeOutTrailTime(1.0f), headParametersGenerateTime(1.0f), headParametersShrinkInTime(0.0f), headParametersShrinkOutTime(1.0f), headParametersTextureLength(1.0f), headParametersTextureScrollRate(1.0f), headParametersThickness(1.0f), tailParametersFadeInTime(1.0f), tailParametersFadeInTrailTime(1.0f), tailParametersFadeOutTime(1.0f), tailParametersFadeOutTrailTime(1.0f), tailParametersGenerateTime(1.0f), tailParametersShrinkInTime(0.0f), tailParametersShrinkOutTime(1.0f), tailParametersTextureLength(1.0f), tailParametersTextureScrollRate(1.0f), tailParametersThickness(1.0f), timeBegin(0.0f), timeEnd(-1.0f), wait(0.0f), headParameters(true), tailParameters(true)
			{
			}

			// FUNCTION: ENGINE 0x10261FB0
			float BulletTracerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10262000
			float BulletTracerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10262010
			BulletTracerTrack::~BulletTracerTrack()
			{
			}

			// FUNCTION: ENGINE 0x10262380
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void BulletTracerTrack::RegisterProperties()
			{
				if (gBulletTracerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("timeBegin", &BulletTracerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("timeEnd", &BulletTracerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("wait", &BulletTracerTrack::SetWait);
					properties[2] = property;
					property = new fight::PropertyGroup<BulletTracerTrack>("headParameters", &BulletTracerTrack::SetHeadParameters, gBulletTracerTrackHeadParametersMembers);
					properties[3] = property;
					property = new fight::PropertyName<BulletTracerTrack>("headParametersShader", &BulletTracerTrack::SetHeadParametersShader);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersGenerateTime", &BulletTracerTrack::SetHeadParametersGenerateTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersFadeInTime", &BulletTracerTrack::SetHeadParametersFadeInTime);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersFadeOutTime", &BulletTracerTrack::SetHeadParametersFadeOutTime);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersFadeInTrailTime", &BulletTracerTrack::SetHeadParametersFadeInTrailTime);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersFadeOutTrailTime", &BulletTracerTrack::SetHeadParametersFadeOutTrailTime);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersShrinkInTime", &BulletTracerTrack::SetHeadParametersShrinkInTime);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersShrinkOutTime", &BulletTracerTrack::SetHeadParametersShrinkOutTime);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersThickness", &BulletTracerTrack::SetHeadParametersThickness);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersTextureLength", &BulletTracerTrack::SetHeadParametersTextureLength);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("headParametersTextureScrollRate", &BulletTracerTrack::SetHeadParametersTextureScrollRate);
					properties[14] = property;
					property = new fight::PropertyColour<BulletTracerTrack>("headParametersStartColour", &BulletTracerTrack::SetHeadParametersStartColour);
					properties[15] = property;
					property = new fight::PropertyColour<BulletTracerTrack>("headParametersEndColour", &BulletTracerTrack::SetHeadParametersEndColour);
					properties[16] = property;
					property = new fight::PropertyGroup<BulletTracerTrack>("tailParameters", &BulletTracerTrack::SetTailParameters, gBulletTracerTrackTailParametersMembers);
					properties[17] = property;
					property = new fight::PropertyName<BulletTracerTrack>("tailParametersShader", &BulletTracerTrack::SetTailParametersShader);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersGenerateTime", &BulletTracerTrack::SetTailParametersGenerateTime);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersFadeInTime", &BulletTracerTrack::SetTailParametersFadeInTime);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersFadeOutTime", &BulletTracerTrack::SetTailParametersFadeOutTime);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersFadeInTrailTime", &BulletTracerTrack::SetTailParametersFadeInTrailTime);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersFadeOutTrailTime", &BulletTracerTrack::SetTailParametersFadeOutTrailTime);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersShrinkInTime", &BulletTracerTrack::SetTailParametersShrinkInTime);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersShrinkOutTime", &BulletTracerTrack::SetTailParametersShrinkOutTime);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersThickness", &BulletTracerTrack::SetTailParametersThickness);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersTextureLength", &BulletTracerTrack::SetTailParametersTextureLength);
					properties[27] = property;
					property = new fight::PropertyFloatConstRange<BulletTracerTrack>("tailParametersTextureScrollRate", &BulletTracerTrack::SetTailParametersTextureScrollRate);
					properties[28] = property;
					property = new fight::PropertyColour<BulletTracerTrack>("tailParametersStartColour", &BulletTracerTrack::SetTailParametersStartColour);
					properties[29] = property;
					property = new fight::PropertyColour<BulletTracerTrack>("tailParametersEndColour", &BulletTracerTrack::SetTailParametersEndColour);
					properties[30] = property;
					property = new fight::PropertyVector<BulletTracerTrack>("offset", &BulletTracerTrack::SetOffset);
					properties[31] = property;
					property = new fight::PropertyNameList<BulletTracerTrack>("attachJoint", &BulletTracerTrack::SetAttachJoint);
					properties[32] = property;
					fight::RegisterPropertyList(properties, &gBulletTracerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10262270
			fight::TrackFactory* CreateBulletTracerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<BulletTracerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102622A0
			void RegisterBulletTracerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<BulletTracerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<BulletTracerTrack>;
			template class fight::PropertyGroup<BulletTracerTrack>;
			template class fight::PropertyName<BulletTracerTrack>;
			template class fight::PropertyColour<BulletTracerTrack>;
			template class fight::PropertyVector<BulletTracerTrack>;
			template class fight::PropertyNameList<BulletTracerTrack>;
			template class fight::TrackFactoryTemplate<BulletTracerTrack>;
			template class fight::TrackFactoryCasterTemplate<BulletTracerTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10262060
// FUNCTION: ENGINE 0x10262070
// FUNCTION: ENGINE 0x102620A0
// FUNCTION: ENGINE 0x102620D0
// FUNCTION: ENGINE 0x10262100
// FUNCTION: ENGINE 0x10262130
// FUNCTION: ENGINE 0x10262140
// FUNCTION: ENGINE 0x10262170
// FUNCTION: ENGINE 0x10262190
// FUNCTION: ENGINE 0x102621A0
// FUNCTION: ENGINE 0x102621B0
// FUNCTION: ENGINE 0x102621E0
// FUNCTION: ENGINE 0x10262200
// FUNCTION: ENGINE 0x10262210
// FUNCTION: ENGINE 0x10262240
// FUNCTION: ENGINE 0x10262260
// FUNCTION: ENGINE 0x102622D0
// FUNCTION: ENGINE 0x10262300
// FUNCTION: ENGINE 0x10262320
// FUNCTION: ENGINE 0x10262350
// FUNCTION: ENGINE 0x10262370
// FUNCTION: ENGINE 0x10262BE0
// FUNCTION: ENGINE 0x10262C10
// FUNCTION: ENGINE 0x10262C40
