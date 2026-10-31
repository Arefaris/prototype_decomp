// Fight items of the motion group: ClearCollisionRecordTrack (unit 0x10149A90 - 0x10149DC0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_clearcollisionrecord.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gClearCollisionRecordTrackProperties;  // 0x1125433C

			// FUNCTION: ENGINE 0x10149A90
			bool ClearCollisionRecordTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149AB0
			fight::Property* ClearCollisionRecordTrack::GetProperty(int index)
			{
				return gClearCollisionRecordTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10149AD0
			void ClearCollisionRecordTrack::ClearProperties()
			{
				fight::FreePropertyList(&gClearCollisionRecordTrackProperties);
			}

			// FUNCTION: ENGINE 0x10149AE0
			ClearCollisionRecordTrack::ClearCollisionRecordTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10149B10
			float ClearCollisionRecordTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10149B20
			float ClearCollisionRecordTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10149B30
			ClearCollisionRecordTrack::~ClearCollisionRecordTrack()
			{
			}

			// FUNCTION: ENGINE 0x10149C50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ClearCollisionRecordTrack::RegisterProperties()
			{
				if (gClearCollisionRecordTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ClearCollisionRecordTrack>("timeBegin", &ClearCollisionRecordTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gClearCollisionRecordTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10149C20
			fight::TrackFactory* CreateClearCollisionRecordTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearCollisionRecordTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10149CF0
			void RegisterClearCollisionRecordTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearCollisionRecordTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100A23B0
			ClearCollisionRecordAction::ClearCollisionRecordAction(ClearCollisionRecordTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x100A22A0
			ClearCollisionRecordAction::~ClearCollisionRecordAction()
			{
			}

			// FUNCTION: ENGINE 0x100A2450
			fight::Action* ClearCollisionRecordTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ClearCollisionRecordAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<ClearCollisionRecordTrack>;
			template class fight::TrackFactoryTemplate<ClearCollisionRecordTrack>;
			template class fight::TrackFactoryCasterTemplate<ClearCollisionRecordTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100A2210
// FUNCTION: ENGINE 0x100A2230
// FUNCTION: ENGINE 0x100A2420
