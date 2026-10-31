// Fight items of the ai group: ExecuteTaskTrack, SpawnTaskTrack (unit 0x102527C0 - 0x10253340; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_task.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gExecuteTaskTrackProperties;  // 0x11255C14

			// FUNCTION: ENGINE 0x102527C0
			bool ExecuteTaskTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102527E0
			bool ExecuteTaskTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102528E0
			bool ExecuteTaskTrack::SetTask(const fight::Name& newValue)
			{
				task = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10252800
			fight::BranchHolder* ExecuteTaskTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x10252810
			fight::ConditionList* ExecuteTaskTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x10252880
			fight::Property* ExecuteTaskTrack::GetProperty(int index)
			{
				return gExecuteTaskTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102528A0
			void ExecuteTaskTrack::ClearProperties()
			{
				fight::FreePropertyList(&gExecuteTaskTrackProperties);
			}

			// FUNCTION: ENGINE 0x10252920
			ExecuteTaskTrack::ExecuteTaskTrack() : branch(0), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10252980
			float ExecuteTaskTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10252990
			float ExecuteTaskTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x102529A0
			ExecuteTaskTrack::~ExecuteTaskTrack()
			{
			}

			// FUNCTION: ENGINE 0x10252EE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ExecuteTaskTrack::RegisterProperties()
			{
				if (gExecuteTaskTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ExecuteTaskTrack>("timeBegin", &ExecuteTaskTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ExecuteTaskTrack>("timeEnd", &ExecuteTaskTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<ExecuteTaskTrack>("task", &ExecuteTaskTrack::SetTask);
					properties[2] = property;
					property = new fight::PropertyBranch<ExecuteTaskTrack>("branch", &ExecuteTaskTrack::SetBranch);
					properties[3] = property;
					property = new fight::PropertyConditionGroup<ExecuteTaskTrack>("conditions", &ExecuteTaskTrack::SetConditions);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gExecuteTaskTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10252D80
			fight::TrackFactory* CreateExecuteTaskTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ExecuteTaskTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10252DE0
			void RegisterExecuteTaskTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ExecuteTaskTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSpawnTaskTrackProperties;  // 0x11255C18

			// FUNCTION: ENGINE 0x10252820
			bool SpawnTaskTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10252840
			bool SpawnTaskTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10252900
			bool SpawnTaskTrack::SetTask(const fight::Name& newValue)
			{
				task = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10252860
			fight::BranchHolder* SpawnTaskTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x10252870
			fight::ConditionList* SpawnTaskTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x102528B0
			fight::Property* SpawnTaskTrack::GetProperty(int index)
			{
				return gSpawnTaskTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102528D0
			void SpawnTaskTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSpawnTaskTrackProperties);
			}

			// FUNCTION: ENGINE 0x102529D0
			SpawnTaskTrack::SpawnTaskTrack() : branch(0), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10252A30
			float SpawnTaskTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10252A40
			float SpawnTaskTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10252A50
			SpawnTaskTrack::~SpawnTaskTrack()
			{
			}

			// FUNCTION: ENGINE 0x10253070
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpawnTaskTrack::RegisterProperties()
			{
				if (gSpawnTaskTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SpawnTaskTrack>("timeBegin", &SpawnTaskTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SpawnTaskTrack>("timeEnd", &SpawnTaskTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<SpawnTaskTrack>("task", &SpawnTaskTrack::SetTask);
					properties[2] = property;
					property = new fight::PropertyBranch<SpawnTaskTrack>("branch", &SpawnTaskTrack::SetBranch);
					properties[3] = property;
					property = new fight::PropertyConditionGroup<SpawnTaskTrack>("conditions", &SpawnTaskTrack::SetConditions);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gSpawnTaskTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10252DB0
			fight::TrackFactory* CreateSpawnTaskTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnTaskTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10252E10
			void RegisterSpawnTaskTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnTaskTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<ExecuteTaskTrack>;
			template class fight::PropertyName<ExecuteTaskTrack>;
			template class fight::PropertyBranch<ExecuteTaskTrack>;
			template class fight::PropertyConditionGroup<ExecuteTaskTrack>;
			template class fight::TrackFactoryTemplate<ExecuteTaskTrack>;
			template class fight::TrackFactoryCasterTemplate<ExecuteTaskTrack>;
			template class fight::PropertyFloatConstRange<SpawnTaskTrack>;
			template class fight::PropertyName<SpawnTaskTrack>;
			template class fight::PropertyBranch<SpawnTaskTrack>;
			template class fight::PropertyConditionGroup<SpawnTaskTrack>;
			template class fight::TrackFactoryTemplate<SpawnTaskTrack>;
			template class fight::TrackFactoryCasterTemplate<SpawnTaskTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10252A80
// FUNCTION: ENGINE 0x10252A90
// FUNCTION: ENGINE 0x10252AC0
// FUNCTION: ENGINE 0x10252AD0
// FUNCTION: ENGINE 0x10252B00
// FUNCTION: ENGINE 0x10252B30
// FUNCTION: ENGINE 0x10252B60
// FUNCTION: ENGINE 0x10252B90
// FUNCTION: ENGINE 0x10252BC0
// FUNCTION: ENGINE 0x10252BD0
// FUNCTION: ENGINE 0x10252C00
// FUNCTION: ENGINE 0x10252C20
// FUNCTION: ENGINE 0x10252C50
// FUNCTION: ENGINE 0x10252C70
// FUNCTION: ENGINE 0x10252CA0
// FUNCTION: ENGINE 0x10252CD0
// FUNCTION: ENGINE 0x10252CE0
// FUNCTION: ENGINE 0x10252D10
// FUNCTION: ENGINE 0x10252D30
// FUNCTION: ENGINE 0x10252D60
// FUNCTION: ENGINE 0x10252E40
// FUNCTION: ENGINE 0x10252E70
// FUNCTION: ENGINE 0x10252E90
// FUNCTION: ENGINE 0x10252EC0
// FUNCTION: ENGINE 0x10253200
// FUNCTION: ENGINE 0x10253230
// FUNCTION: ENGINE 0x10253250
// FUNCTION: ENGINE 0x10253280
// FUNCTION: ENGINE 0x102532A0
// FUNCTION: ENGINE 0x102532F0
