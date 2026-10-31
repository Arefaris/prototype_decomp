// Fight items of the motion group: HaveIconTypeCondition, HUDMarkerTrack (unit 0x1017CA90 - 0x1017D680; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_hudmarker.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gHaveIconTypeConditionProperties;  // 0x11254700

			// FUNCTION: ENGINE 0x1017CA90
			bool HaveIconTypeCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CB50
			fight::Property* HaveIconTypeCondition::GetProperty(int index)
			{
				return gHaveIconTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1017CB70
			void HaveIconTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHaveIconTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x1017CB80
			HaveIconTypeCondition::HaveIconTypeCondition() : fight::Condition(0), type(0)
			{
			}

			// FUNCTION: ENGINE 0x1017CBB0
			HaveIconTypeCondition::~HaveIconTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x1017D0F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HaveIconTypeCondition::RegisterProperties()
			{
				if (gHaveIconTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<HaveIconTypeCondition>("type", gHaveIconTypeConditionTypeTable, gHaveIconTypeConditionTypeCount, &HaveIconTypeCondition::SetType);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHaveIconTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017D090
			fight::ConditionFactory* CreateHaveIconTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveIconTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017D1A0
			void RegisterHaveIconTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveIconTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHUDMarkerTrackProperties;  // 0x11254704

			// FUNCTION: ENGINE 0x1017CAA0
			bool HUDMarkerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CAC0
			bool HUDMarkerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CAE0
			bool HUDMarkerTrack::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CAF0
			bool HUDMarkerTrack::SetDisplayType(int newValue)
			{
				displayType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CB00
			bool HUDMarkerTrack::SetAnimType(int newValue)
			{
				animType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CB10
			bool HUDMarkerTrack::SetColor(int newValue)
			{
				color = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CB20
			bool HUDMarkerTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CB40
			bool HUDMarkerTrack::SetUseGrabSlot(bool newValue)
			{
				useGrabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CBF0
			bool HUDMarkerTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017CBC0
			fight::Property* HUDMarkerTrack::GetProperty(int index)
			{
				return gHUDMarkerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1017CBE0
			void HUDMarkerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHUDMarkerTrackProperties);
			}

			// FUNCTION: ENGINE 0x1017CC40
			HUDMarkerTrack::HUDMarkerTrack() : radius(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), animType(0), color(0), type(0), displayType(0), useGrabSlot(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1017CCA0
			float HUDMarkerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1017CCB0
			float HUDMarkerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1017CCC0
			HUDMarkerTrack::~HUDMarkerTrack()
			{
			}

			// FUNCTION: ENGINE 0x1017D2B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HUDMarkerTrack::RegisterProperties()
			{
				if (gHUDMarkerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HUDMarkerTrack>("timeBegin", &HUDMarkerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HUDMarkerTrack>("timeEnd", &HUDMarkerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<HUDMarkerTrack>("type", gHaveIconTypeConditionTypeTable, gHaveIconTypeConditionTypeCount, &HUDMarkerTrack::SetType);
					properties[2] = property;
					property = new fight::PropertyBitfieldConstList<HUDMarkerTrack>("displayType", gHUDMarkerTrackDisplayTypeTable, gHUDMarkerTrackDisplayTypeCount, &HUDMarkerTrack::SetDisplayType);
					properties[3] = property;
					property = new fight::PropertyEnumConstList<HUDMarkerTrack>("animType", gHUDMarkerTrackAnimTypeTable, gHUDMarkerTrackAnimTypeCount, &HUDMarkerTrack::SetAnimType);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<HUDMarkerTrack>("color", gHUDMarkerTrackColorTable, gHUDMarkerTrackColorCount, &HUDMarkerTrack::SetColor);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<HUDMarkerTrack>("radius", &HUDMarkerTrack::SetRadius);
					properties[6] = property;
					property = new fight::PropertyBool<HUDMarkerTrack>("useGrabSlot", &HUDMarkerTrack::SetUseGrabSlot);
					properties[7] = property;
					property = new fight::PropertyNameList<HUDMarkerTrack>("grabSlot", &HUDMarkerTrack::SetGrabSlot);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gHUDMarkerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017D0C0
			fight::TrackFactory* CreateHUDMarkerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HUDMarkerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017D1D0
			void RegisterHUDMarkerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HUDMarkerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<HaveIconTypeCondition>;
			template class fight::ConditionFactoryTemplate<HaveIconTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<HaveIconTypeCondition>;
			template class fight::PropertyFloatConstRange<HUDMarkerTrack>;
			template class fight::PropertyEnumConstList<HUDMarkerTrack>;
			template class fight::PropertyBitfieldConstList<HUDMarkerTrack>;
			template class fight::PropertyBool<HUDMarkerTrack>;
			template class fight::PropertyNameList<HUDMarkerTrack>;
			template class fight::TrackFactoryTemplate<HUDMarkerTrack>;
			template class fight::TrackFactoryCasterTemplate<HUDMarkerTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1017CC10
// FUNCTION: ENGINE 0x1017CCD0
// FUNCTION: ENGINE 0x1017CCE0
// FUNCTION: ENGINE 0x1017CD10
// FUNCTION: ENGINE 0x1017CD20
// FUNCTION: ENGINE 0x1017CD50
// FUNCTION: ENGINE 0x1017CD80
// FUNCTION: ENGINE 0x1017CDC0
// FUNCTION: ENGINE 0x1017CDD0
// FUNCTION: ENGINE 0x1017CE00
// FUNCTION: ENGINE 0x1017CE20
// FUNCTION: ENGINE 0x1017CE30
// FUNCTION: ENGINE 0x1017CE60
// FUNCTION: ENGINE 0x1017CE90
// FUNCTION: ENGINE 0x1017CEA0
// FUNCTION: ENGINE 0x1017CEE0
// FUNCTION: ENGINE 0x1017CEF0
// FUNCTION: ENGINE 0x1017CF20
// FUNCTION: ENGINE 0x1017CF40
// FUNCTION: ENGINE 0x1017CF50
// FUNCTION: ENGINE 0x1017CF90
// FUNCTION: ENGINE 0x1017CFA0
// FUNCTION: ENGINE 0x1017CFC0
// FUNCTION: ENGINE 0x1017CFD0
// FUNCTION: ENGINE 0x1017D030
// FUNCTION: ENGINE 0x1017D060
// FUNCTION: ENGINE 0x1017D080
// FUNCTION: ENGINE 0x1017D200
// FUNCTION: ENGINE 0x1017D230
// FUNCTION: ENGINE 0x1017D250
// FUNCTION: ENGINE 0x1017D260
// FUNCTION: ENGINE 0x1017D290
// FUNCTION: ENGINE 0x1017D590
// FUNCTION: ENGINE 0x1017D5E0
// FUNCTION: ENGINE 0x1017D610
// FUNCTION: ENGINE 0x1017D630
