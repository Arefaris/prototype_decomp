// Fight items of the motion group: FactionTypeCondition, FactionCondition, FactionSetTrack, FactionDefaultTrack (unit 0x1015D620 - 0x1015E4B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/faction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFactionTypeConditionProperties;  // 0x11254504

			// FUNCTION: ENGINE 0x1015D620
			bool FactionTypeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015D630
			bool FactionTypeCondition::SetFactionType(int newValue)
			{
				factionType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015D680
			fight::Property* FactionTypeCondition::GetProperty(int index)
			{
				return gFactionTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1015D6A0
			void FactionTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gFactionTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x1015D6B0
			FactionTypeCondition::FactionTypeCondition() : fight::Condition(0), compare(0), factionType(0)
			{
			}

			// FUNCTION: ENGINE 0x1015D6E0
			FactionTypeCondition::~FactionTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x1015DE70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FactionTypeCondition::RegisterProperties()
			{
				if (gFactionTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<FactionTypeCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &FactionTypeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<FactionTypeCondition>("factionType", gFactionTypeConditionFactionTypeTable, gFactionTypeConditionFactionTypeCount, &FactionTypeCondition::SetFactionType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gFactionTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015DDB0
			fight::ConditionFactory* CreateFactionTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FactionTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015DF70
			void RegisterFactionTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FactionTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFactionConditionProperties;  // 0x11254508

			// FUNCTION: ENGINE 0x1015D640
			bool FactionCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015D830
			bool FactionCondition::SetFaction(const fight::Name& newValue)
			{
				faction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015D6F0
			fight::Property* FactionCondition::GetProperty(int index)
			{
				return gFactionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1015D710
			void FactionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gFactionConditionProperties);
			}

			// FUNCTION: ENGINE 0x1015D8A0
			FactionCondition::FactionCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x1015D8D0
			FactionCondition::~FactionCondition()
			{
			}

			// FUNCTION: ENGINE 0x1015E120
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FactionCondition::RegisterProperties()
			{
				if (gFactionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<FactionCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &FactionCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<FactionCondition>("faction", &FactionCondition::SetFaction);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gFactionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015DDE0
			fight::ConditionFactory* CreateFactionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FactionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015DFA0
			void RegisterFactionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FactionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFactionSetTrackProperties;  // 0x1125450C

			// FUNCTION: ENGINE 0x1015D650
			bool FactionSetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015D850
			bool FactionSetTrack::SetFaction(const fight::Name& newValue)
			{
				faction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015D670
			bool FactionSetTrack::SetNotifyAI(bool newValue)
			{
				notifyAI = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015D720
			fight::Property* FactionSetTrack::GetProperty(int index)
			{
				return gFactionSetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015D740
			void FactionSetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFactionSetTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015D8E0
			FactionSetTrack::FactionSetTrack() : timeBegin(0.0f), notifyAI(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1015D920
			float FactionSetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1015D930
			float FactionSetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1015D940
			FactionSetTrack::~FactionSetTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015E210
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FactionSetTrack::RegisterProperties()
			{
				if (gFactionSetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FactionSetTrack>("timeBegin", &FactionSetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<FactionSetTrack>("faction", &FactionSetTrack::SetFaction);
					properties[1] = property;
					property = new fight::PropertyBool<FactionSetTrack>("notifyAI", &FactionSetTrack::SetNotifyAI);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gFactionSetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015DE10
			fight::TrackFactory* CreateFactionSetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FactionSetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015DFD0
			void RegisterFactionSetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FactionSetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gFactionDefaultTrackProperties;  // 0x11254510

			// FUNCTION: ENGINE 0x1015D7B0
			fight::Property* FactionDefaultTrack::GetProperty(int index)
			{
				return gFactionDefaultTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015D7D0
			void FactionDefaultTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFactionDefaultTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015D7E0
			FactionDefaultTrack::FactionDefaultTrack()
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1015D800
			float FactionDefaultTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1015D810
			float FactionDefaultTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1015D820
			FactionDefaultTrack::~FactionDefaultTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015D750
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FactionDefaultTrack::RegisterProperties()
			{
				if (gFactionDefaultTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gFactionDefaultTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015DE40
			fight::TrackFactory* CreateFactionDefaultTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FactionDefaultTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015E000
			void RegisterFactionDefaultTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FactionDefaultTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<FactionTypeCondition>;
			template class fight::ConditionFactoryTemplate<FactionTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<FactionTypeCondition>;
			template class fight::PropertyEnumConstList<FactionCondition>;
			template class fight::PropertyName<FactionCondition>;
			template class fight::ConditionFactoryTemplate<FactionCondition>;
			template class fight::ConditionFactoryCasterTemplate<FactionCondition>;
			template class fight::PropertyFloatConstRange<FactionSetTrack>;
			template class fight::PropertyName<FactionSetTrack>;
			template class fight::PropertyBool<FactionSetTrack>;
			template class fight::TrackFactoryTemplate<FactionSetTrack>;
			template class fight::TrackFactoryCasterTemplate<FactionSetTrack>;
			template class fight::TrackFactoryTemplate<FactionDefaultTrack>;
			template class fight::TrackFactoryCasterTemplate<FactionDefaultTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1015D870
// FUNCTION: ENGINE 0x1015D950
// FUNCTION: ENGINE 0x1015D980
// FUNCTION: ENGINE 0x1015D990
// FUNCTION: ENGINE 0x1015D9C0
// FUNCTION: ENGINE 0x1015D9D0
// FUNCTION: ENGINE 0x1015DA00
// FUNCTION: ENGINE 0x1015DA10
// FUNCTION: ENGINE 0x1015DA40
// FUNCTION: ENGINE 0x1015DA50
// FUNCTION: ENGINE 0x1015DA80
// FUNCTION: ENGINE 0x1015DAB0
// FUNCTION: ENGINE 0x1015DAD0
// FUNCTION: ENGINE 0x1015DB20
// FUNCTION: ENGINE 0x1015DB50
// FUNCTION: ENGINE 0x1015DB80
// FUNCTION: ENGINE 0x1015DBC0
// FUNCTION: ENGINE 0x1015DBD0
// FUNCTION: ENGINE 0x1015DC00
// FUNCTION: ENGINE 0x1015DC20
// FUNCTION: ENGINE 0x1015DC30
// FUNCTION: ENGINE 0x1015DC70
// FUNCTION: ENGINE 0x1015DC80
// FUNCTION: ENGINE 0x1015DCB0
// FUNCTION: ENGINE 0x1015DCD0
// FUNCTION: ENGINE 0x1015DCE0
// FUNCTION: ENGINE 0x1015DD10
// FUNCTION: ENGINE 0x1015DD40
// FUNCTION: ENGINE 0x1015DD50
// FUNCTION: ENGINE 0x1015DD80
// FUNCTION: ENGINE 0x1015DDA0
// FUNCTION: ENGINE 0x1015E030
// FUNCTION: ENGINE 0x1015E060
// FUNCTION: ENGINE 0x1015E080
// FUNCTION: ENGINE 0x1015E0B0
// FUNCTION: ENGINE 0x1015E0D0
// FUNCTION: ENGINE 0x1015E100
// FUNCTION: ENGINE 0x1015E320
// FUNCTION: ENGINE 0x1015E370
// FUNCTION: ENGINE 0x1015E3A0
// FUNCTION: ENGINE 0x1015E3C0
// FUNCTION: ENGINE 0x1015E3F0
// FUNCTION: ENGINE 0x1015E410
// FUNCTION: ENGINE 0x1015E460
