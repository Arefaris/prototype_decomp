// Fight items of the ai group: SpawnTemplateCondition, ShouldSpawnCondition, ObjectSpawnedTrack (unit 0x10249C30 - 0x1024A810; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_spawn.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gSpawnTemplateConditionProperties;  // 0x11255B94

			// FUNCTION: ENGINE 0x10249D60
			bool SpawnTemplateCondition::SetTemplateName(const fight::Name& newValue)
			{
				templateName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249C30
			bool SpawnTemplateCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249CA0
			fight::Property* SpawnTemplateCondition::GetProperty(int index)
			{
				return gSpawnTemplateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10249CC0
			void SpawnTemplateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSpawnTemplateConditionProperties);
			}

			// FUNCTION: ENGINE 0x10249DA0
			SpawnTemplateCondition::SpawnTemplateCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10249DD0
			SpawnTemplateCondition::~SpawnTemplateCondition()
			{
			}

			// FUNCTION: ENGINE 0x1024A440
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpawnTemplateCondition::RegisterProperties()
			{
				if (gSpawnTemplateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<SpawnTemplateCondition>("templateName", &SpawnTemplateCondition::SetTemplateName);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SpawnTemplateCondition>("compare", motion::gClassNameConditionCompareTable, motion::gClassNameConditionCompareCount, &SpawnTemplateCondition::SetCompare);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSpawnTemplateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024A180
			fight::ConditionFactory* CreateSpawnTemplateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SpawnTemplateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024A2B0
			void RegisterSpawnTemplateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SpawnTemplateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShouldSpawnConditionProperties;  // 0x11255B98

			// FUNCTION: ENGINE 0x10249C40
			bool ShouldSpawnCondition::SetShould(bool newValue)
			{
				should = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249CD0
			fight::Property* ShouldSpawnCondition::GetProperty(int index)
			{
				return gShouldSpawnConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10249CF0
			void ShouldSpawnCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShouldSpawnConditionProperties);
			}

			// FUNCTION: ENGINE 0x10249D00
			ShouldSpawnCondition::ShouldSpawnCondition() : fight::Condition(0), should(true)
			{
			}

			// FUNCTION: ENGINE 0x10249D20
			ShouldSpawnCondition::~ShouldSpawnCondition()
			{
			}

			// FUNCTION: ENGINE 0x1024A210
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShouldSpawnCondition::RegisterProperties()
			{
				if (gShouldSpawnConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ShouldSpawnCondition>("should", &ShouldSpawnCondition::SetShould);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gShouldSpawnConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024A1B0
			fight::ConditionFactory* CreateShouldSpawnConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShouldSpawnCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024A2E0
			void RegisterShouldSpawnConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShouldSpawnCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObjectSpawnedTrackProperties;  // 0x11255B9C

			// FUNCTION: ENGINE 0x10249C50
			bool ObjectSpawnedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249C70
			bool ObjectSpawnedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249D80
			bool ObjectSpawnedTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249C90
			bool ObjectSpawnedTrack::SetLastGuy(bool newValue)
			{
				lastGuy = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249D30
			fight::Property* ObjectSpawnedTrack::GetProperty(int index)
			{
				return gObjectSpawnedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10249D50
			void ObjectSpawnedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gObjectSpawnedTrackProperties);
			}

			// FUNCTION: ENGINE 0x10249E10
			ObjectSpawnedTrack::ObjectSpawnedTrack() : timeBegin(0.0f), timeEnd(-1.0f), lastGuy(false)
			{
			}

			// FUNCTION: ENGINE 0x10249E50
			float ObjectSpawnedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10249E60
			float ObjectSpawnedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10249E70
			ObjectSpawnedTrack::~ObjectSpawnedTrack()
			{
			}

			// FUNCTION: ENGINE 0x1024A530
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObjectSpawnedTrack::RegisterProperties()
			{
				if (gObjectSpawnedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ObjectSpawnedTrack>("timeBegin", &ObjectSpawnedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObjectSpawnedTrack>("timeEnd", &ObjectSpawnedTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<ObjectSpawnedTrack>("grabSlot", &ObjectSpawnedTrack::SetGrabSlot);
					properties[2] = property;
					property = new fight::PropertyBool<ObjectSpawnedTrack>("lastGuy", &ObjectSpawnedTrack::SetLastGuy);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gObjectSpawnedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024A1E0
			fight::TrackFactory* CreateObjectSpawnedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ObjectSpawnedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024A310
			void RegisterObjectSpawnedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ObjectSpawnedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyName<SpawnTemplateCondition>;
			template class fight::PropertyEnumConstList<SpawnTemplateCondition>;
			template class fight::ConditionFactoryTemplate<SpawnTemplateCondition>;
			template class fight::ConditionFactoryCasterTemplate<SpawnTemplateCondition>;
			template class fight::PropertyBool<ShouldSpawnCondition>;
			template class fight::ConditionFactoryTemplate<ShouldSpawnCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShouldSpawnCondition>;
			template class fight::PropertyFloatConstRange<ObjectSpawnedTrack>;
			template class fight::PropertyNameList<ObjectSpawnedTrack>;
			template class fight::PropertyBool<ObjectSpawnedTrack>;
			template class fight::TrackFactoryTemplate<ObjectSpawnedTrack>;
			template class fight::TrackFactoryCasterTemplate<ObjectSpawnedTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10249DE0
// FUNCTION: ENGINE 0x10249E80
// FUNCTION: ENGINE 0x10249E90
// FUNCTION: ENGINE 0x10249EC0
// FUNCTION: ENGINE 0x10249ED0
// FUNCTION: ENGINE 0x10249F00
// FUNCTION: ENGINE 0x10249F10
// FUNCTION: ENGINE 0x10249F40
// FUNCTION: ENGINE 0x10249F70
// FUNCTION: ENGINE 0x10249FA0
// FUNCTION: ENGINE 0x10249FE0
// FUNCTION: ENGINE 0x10249FF0
// FUNCTION: ENGINE 0x1024A020
// FUNCTION: ENGINE 0x1024A040
// FUNCTION: ENGINE 0x1024A050
// FUNCTION: ENGINE 0x1024A080
// FUNCTION: ENGINE 0x1024A0A0
// FUNCTION: ENGINE 0x1024A0B0
// FUNCTION: ENGINE 0x1024A0E0
// FUNCTION: ENGINE 0x1024A110
// FUNCTION: ENGINE 0x1024A120
// FUNCTION: ENGINE 0x1024A150
// FUNCTION: ENGINE 0x1024A170
// FUNCTION: ENGINE 0x1024A340
// FUNCTION: ENGINE 0x1024A370
// FUNCTION: ENGINE 0x1024A390
// FUNCTION: ENGINE 0x1024A3C0
// FUNCTION: ENGINE 0x1024A3E0
// FUNCTION: ENGINE 0x1024A3F0
// FUNCTION: ENGINE 0x1024A420
// FUNCTION: ENGINE 0x1024A680
// FUNCTION: ENGINE 0x1024A6D0
// FUNCTION: ENGINE 0x1024A700
// FUNCTION: ENGINE 0x1024A720
// FUNCTION: ENGINE 0x1024A750
// FUNCTION: ENGINE 0x1024A770
// FUNCTION: ENGINE 0x1024A7C0
