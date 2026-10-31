// Fight items of the motion group: HasFailedPatsyCondition, IsPatsyCondition, PatsyDeadCondition, HasPatsyCondition, PatsyConditionGroupCondition, IsFailedPatsyCondition, PatsyCreateTrack, ClearFailedPatsyTrack, ClearPatsyTrack (unit 0x1019A8A0 - 0x1019C4A0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_patsy.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gHasFailedPatsyConditionProperties;  // 0x112548D8

			// FUNCTION: ENGINE 0x1019A8A0
			bool HasFailedPatsyCondition::SetHas(bool newValue)
			{
				has = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019A970
			fight::Property* HasFailedPatsyCondition::GetProperty(int index)
			{
				return gHasFailedPatsyConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019A990
			void HasFailedPatsyCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHasFailedPatsyConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019A9A0
			HasFailedPatsyCondition::HasFailedPatsyCondition() : fight::Condition(0), has(true)
			{
			}

			// FUNCTION: ENGINE 0x1019A9C0
			HasFailedPatsyCondition::~HasFailedPatsyCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019B760
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HasFailedPatsyCondition::RegisterProperties()
			{
				if (gHasFailedPatsyConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HasFailedPatsyCondition>("has", &HasFailedPatsyCondition::SetHas);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHasFailedPatsyConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019B5B0
			fight::ConditionFactory* CreateHasFailedPatsyConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasFailedPatsyCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019BD50
			void RegisterHasFailedPatsyConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasFailedPatsyCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gIsPatsyConditionProperties;  // 0x112548DC

			// FUNCTION: ENGINE 0x1019A8B0
			bool IsPatsyCondition::SetIs(bool newValue)
			{
				is = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019A9D0
			fight::Property* IsPatsyCondition::GetProperty(int index)
			{
				return gIsPatsyConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019A9F0
			void IsPatsyCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsPatsyConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019AA00
			IsPatsyCondition::IsPatsyCondition() : fight::Condition(0), is(true)
			{
			}

			// FUNCTION: ENGINE 0x1019AA20
			IsPatsyCondition::~IsPatsyCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019B800
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsPatsyCondition::RegisterProperties()
			{
				if (gIsPatsyConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<IsPatsyCondition>("is", &IsPatsyCondition::SetIs);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gIsPatsyConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019B5E0
			fight::ConditionFactory* CreateIsPatsyConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsPatsyCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019BD80
			void RegisterIsPatsyConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsPatsyCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPatsyDeadConditionProperties;  // 0x112548E0

			// FUNCTION: ENGINE 0x1019A8C0
			bool PatsyDeadCondition::SetDead(bool newValue)
			{
				dead = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019AA30
			fight::Property* PatsyDeadCondition::GetProperty(int index)
			{
				return gPatsyDeadConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019AA50
			void PatsyDeadCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPatsyDeadConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019AA60
			PatsyDeadCondition::PatsyDeadCondition() : fight::Condition(0), dead(true)
			{
			}

			// FUNCTION: ENGINE 0x1019AA80
			PatsyDeadCondition::~PatsyDeadCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019B8A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PatsyDeadCondition::RegisterProperties()
			{
				if (gPatsyDeadConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<PatsyDeadCondition>("dead", &PatsyDeadCondition::SetDead);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPatsyDeadConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019B610
			fight::ConditionFactory* CreatePatsyDeadConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PatsyDeadCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019BDB0
			void RegisterPatsyDeadConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PatsyDeadCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHasPatsyConditionProperties;  // 0x112548E4

			// FUNCTION: ENGINE 0x1019A8D0
			bool HasPatsyCondition::SetHas(bool newValue)
			{
				has = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019AA90
			fight::Property* HasPatsyCondition::GetProperty(int index)
			{
				return gHasPatsyConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019AAB0
			void HasPatsyCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHasPatsyConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019AAC0
			HasPatsyCondition::HasPatsyCondition() : fight::Condition(0), has(true)
			{
			}

			// FUNCTION: ENGINE 0x1019AAE0
			HasPatsyCondition::~HasPatsyCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019B940
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HasPatsyCondition::RegisterProperties()
			{
				if (gHasPatsyConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HasPatsyCondition>("has", &HasPatsyCondition::SetHas);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHasPatsyConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019B640
			fight::ConditionFactory* CreateHasPatsyConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasPatsyCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019BDE0
			void RegisterHasPatsyConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasPatsyCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPatsyConditionGroupConditionProperties;  // 0x112548E8

			// FUNCTION: ENGINE 0x1019A8E0
			fight::ConditionList* PatsyConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1019AAF0
			fight::Property* PatsyConditionGroupCondition::GetProperty(int index)
			{
				return gPatsyConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019AB10
			void PatsyConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPatsyConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019AB20
			PatsyConditionGroupCondition::PatsyConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1019AB50
			PatsyConditionGroupCondition::~PatsyConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019B9E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PatsyConditionGroupCondition::RegisterProperties()
			{
				if (gPatsyConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<PatsyConditionGroupCondition>("conditions", &PatsyConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPatsyConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019B670
			fight::ConditionFactory* CreatePatsyConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PatsyConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019BE10
			void RegisterPatsyConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PatsyConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gIsFailedPatsyConditionProperties;  // 0x112548EC

			// FUNCTION: ENGINE 0x1019A8F0
			bool IsFailedPatsyCondition::SetIs(bool newValue)
			{
				is = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019AB70
			fight::Property* IsFailedPatsyCondition::GetProperty(int index)
			{
				return gIsFailedPatsyConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019AB90
			void IsFailedPatsyCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsFailedPatsyConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019ABA0
			IsFailedPatsyCondition::IsFailedPatsyCondition() : fight::Condition(0), is(true)
			{
			}

			// FUNCTION: ENGINE 0x1019ABC0
			IsFailedPatsyCondition::~IsFailedPatsyCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019BA80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsFailedPatsyCondition::RegisterProperties()
			{
				if (gIsFailedPatsyConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<IsFailedPatsyCondition>("is", &IsFailedPatsyCondition::SetIs);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gIsFailedPatsyConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019B6A0
			fight::ConditionFactory* CreateIsFailedPatsyConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsFailedPatsyCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019BE40
			void RegisterIsFailedPatsyConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsFailedPatsyCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPatsyCreateTrackProperties;  // 0x112548F0

			// FUNCTION: ENGINE 0x1019A900
			bool PatsyCreateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019A920
			bool PatsyCreateTrack::SetWho(int newValue)
			{
				who = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019ABD0
			fight::Property* PatsyCreateTrack::GetProperty(int index)
			{
				return gPatsyCreateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1019ABF0
			void PatsyCreateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPatsyCreateTrackProperties);
			}

			// FUNCTION: ENGINE 0x1019AC00
			PatsyCreateTrack::PatsyCreateTrack() : timeBegin(0.0f), who(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1019AC40
			float PatsyCreateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1019AC50
			float PatsyCreateTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1019AC60
			PatsyCreateTrack::~PatsyCreateTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019BB20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PatsyCreateTrack::RegisterProperties()
			{
				if (gPatsyCreateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PatsyCreateTrack>("timeBegin", &PatsyCreateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<PatsyCreateTrack>("who", gPatsyCreateTrackWhoTable, gPatsyCreateTrackWhoCount, &PatsyCreateTrack::SetWho);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPatsyCreateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019B6D0
			fight::TrackFactory* CreatePatsyCreateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PatsyCreateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019BE70
			void RegisterPatsyCreateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PatsyCreateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gClearFailedPatsyTrackProperties;  // 0x112548F4

			// FUNCTION: ENGINE 0x1019A930
			bool ClearFailedPatsyTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019AC70
			fight::Property* ClearFailedPatsyTrack::GetProperty(int index)
			{
				return gClearFailedPatsyTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1019AC90
			void ClearFailedPatsyTrack::ClearProperties()
			{
				fight::FreePropertyList(&gClearFailedPatsyTrackProperties);
			}

			// FUNCTION: ENGINE 0x1019ACA0
			ClearFailedPatsyTrack::ClearFailedPatsyTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1019ACD0
			float ClearFailedPatsyTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1019ACE0
			float ClearFailedPatsyTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1019ACF0
			ClearFailedPatsyTrack::~ClearFailedPatsyTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019BC10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ClearFailedPatsyTrack::RegisterProperties()
			{
				if (gClearFailedPatsyTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ClearFailedPatsyTrack>("timeBegin", &ClearFailedPatsyTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gClearFailedPatsyTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019B700
			fight::TrackFactory* CreateClearFailedPatsyTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearFailedPatsyTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019BEA0
			void RegisterClearFailedPatsyTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearFailedPatsyTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gClearPatsyTrackProperties;  // 0x112548F8

			// FUNCTION: ENGINE 0x1019A950
			bool ClearPatsyTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019AD00
			fight::Property* ClearPatsyTrack::GetProperty(int index)
			{
				return gClearPatsyTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1019AD20
			void ClearPatsyTrack::ClearProperties()
			{
				fight::FreePropertyList(&gClearPatsyTrackProperties);
			}

			// FUNCTION: ENGINE 0x1019AD30
			ClearPatsyTrack::ClearPatsyTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1019AD60
			float ClearPatsyTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1019AD70
			float ClearPatsyTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1019AD80
			ClearPatsyTrack::~ClearPatsyTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019BCB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ClearPatsyTrack::RegisterProperties()
			{
				if (gClearPatsyTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ClearPatsyTrack>("timeBegin", &ClearPatsyTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gClearPatsyTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019B730
			fight::TrackFactory* CreateClearPatsyTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearPatsyTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019BED0
			void RegisterClearPatsyTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearPatsyTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyBool<HasFailedPatsyCondition>;
			template class fight::ConditionFactoryTemplate<HasFailedPatsyCondition>;
			template class fight::ConditionFactoryCasterTemplate<HasFailedPatsyCondition>;
			template class fight::PropertyBool<IsPatsyCondition>;
			template class fight::ConditionFactoryTemplate<IsPatsyCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsPatsyCondition>;
			template class fight::PropertyBool<PatsyDeadCondition>;
			template class fight::ConditionFactoryTemplate<PatsyDeadCondition>;
			template class fight::ConditionFactoryCasterTemplate<PatsyDeadCondition>;
			template class fight::PropertyBool<HasPatsyCondition>;
			template class fight::ConditionFactoryTemplate<HasPatsyCondition>;
			template class fight::ConditionFactoryCasterTemplate<HasPatsyCondition>;
			template class fight::PropertyConditionGroup<PatsyConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<PatsyConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<PatsyConditionGroupCondition>;
			template class fight::PropertyBool<IsFailedPatsyCondition>;
			template class fight::ConditionFactoryTemplate<IsFailedPatsyCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsFailedPatsyCondition>;
			template class fight::PropertyFloatConstRange<PatsyCreateTrack>;
			template class fight::PropertyEnumConstList<PatsyCreateTrack>;
			template class fight::TrackFactoryTemplate<PatsyCreateTrack>;
			template class fight::TrackFactoryCasterTemplate<PatsyCreateTrack>;
			template class fight::PropertyFloatConstRange<ClearFailedPatsyTrack>;
			template class fight::TrackFactoryTemplate<ClearFailedPatsyTrack>;
			template class fight::TrackFactoryCasterTemplate<ClearFailedPatsyTrack>;
			template class fight::PropertyFloatConstRange<ClearPatsyTrack>;
			template class fight::TrackFactoryTemplate<ClearPatsyTrack>;
			template class fight::TrackFactoryCasterTemplate<ClearPatsyTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1019AD90
// FUNCTION: ENGINE 0x1019ADC0
// FUNCTION: ENGINE 0x1019ADF0
// FUNCTION: ENGINE 0x1019AE20
// FUNCTION: ENGINE 0x1019AE50
// FUNCTION: ENGINE 0x1019AE80
// FUNCTION: ENGINE 0x1019AEB0
// FUNCTION: ENGINE 0x1019AEE0
// FUNCTION: ENGINE 0x1019AF10
// FUNCTION: ENGINE 0x1019AF40
// FUNCTION: ENGINE 0x1019AF50
// FUNCTION: ENGINE 0x1019AF80
// FUNCTION: ENGINE 0x1019AF90
// FUNCTION: ENGINE 0x1019AFC0
// FUNCTION: ENGINE 0x1019AFD0
// FUNCTION: ENGINE 0x1019B000
// FUNCTION: ENGINE 0x1019B010
// FUNCTION: ENGINE 0x1019B040
// FUNCTION: ENGINE 0x1019B050
// FUNCTION: ENGINE 0x1019B080
// FUNCTION: ENGINE 0x1019B090
// FUNCTION: ENGINE 0x1019B0C0
// FUNCTION: ENGINE 0x1019B0D0
// FUNCTION: ENGINE 0x1019B100
// FUNCTION: ENGINE 0x1019B110
// FUNCTION: ENGINE 0x1019B140
// FUNCTION: ENGINE 0x1019B150
// FUNCTION: ENGINE 0x1019B180
// FUNCTION: ENGINE 0x1019B1B0
// FUNCTION: ENGINE 0x1019B1D0
// FUNCTION: ENGINE 0x1019B1E0
// FUNCTION: ENGINE 0x1019B210
// FUNCTION: ENGINE 0x1019B230
// FUNCTION: ENGINE 0x1019B240
// FUNCTION: ENGINE 0x1019B270
// FUNCTION: ENGINE 0x1019B290
// FUNCTION: ENGINE 0x1019B2A0
// FUNCTION: ENGINE 0x1019B2D0
// FUNCTION: ENGINE 0x1019B2F0
// FUNCTION: ENGINE 0x1019B300
// FUNCTION: ENGINE 0x1019B330
// FUNCTION: ENGINE 0x1019B350
// FUNCTION: ENGINE 0x1019B380
// FUNCTION: ENGINE 0x1019B3A0
// FUNCTION: ENGINE 0x1019B3B0
// FUNCTION: ENGINE 0x1019B3E0
// FUNCTION: ENGINE 0x1019B410
// FUNCTION: ENGINE 0x1019B420
// FUNCTION: ENGINE 0x1019B460
// FUNCTION: ENGINE 0x1019B470
// FUNCTION: ENGINE 0x1019B4A0
// FUNCTION: ENGINE 0x1019B4C0
// FUNCTION: ENGINE 0x1019B4D0
// FUNCTION: ENGINE 0x1019B500
// FUNCTION: ENGINE 0x1019B530
// FUNCTION: ENGINE 0x1019B540
// FUNCTION: ENGINE 0x1019B570
// FUNCTION: ENGINE 0x1019B5A0
// FUNCTION: ENGINE 0x1019BF00
// FUNCTION: ENGINE 0x1019BF30
// FUNCTION: ENGINE 0x1019BF50
// FUNCTION: ENGINE 0x1019BF80
// FUNCTION: ENGINE 0x1019BFA0
// FUNCTION: ENGINE 0x1019BFD0
// FUNCTION: ENGINE 0x1019BFF0
// FUNCTION: ENGINE 0x1019C020
// FUNCTION: ENGINE 0x1019C040
// FUNCTION: ENGINE 0x1019C070
// FUNCTION: ENGINE 0x1019C090
// FUNCTION: ENGINE 0x1019C0C0
// FUNCTION: ENGINE 0x1019C0E0
// FUNCTION: ENGINE 0x1019C110
// FUNCTION: ENGINE 0x1019C130
// FUNCTION: ENGINE 0x1019C160
// FUNCTION: ENGINE 0x1019C180
// FUNCTION: ENGINE 0x1019C1B0
// FUNCTION: ENGINE 0x1019C1D0
// FUNCTION: ENGINE 0x1019C220
// FUNCTION: ENGINE 0x1019C270
// FUNCTION: ENGINE 0x1019C2C0
// FUNCTION: ENGINE 0x1019C310
// FUNCTION: ENGINE 0x1019C360
// FUNCTION: ENGINE 0x1019C3B0
// FUNCTION: ENGINE 0x1019C400
// FUNCTION: ENGINE 0x1019C450
