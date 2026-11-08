// Fight items of the ai group: HasPatrolPathCondition, PatrolTrack, PathPatrolTrack (unit 0x10243760 - 0x10244160; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_patrol.h"
#include "code/proto/fightitems/ai/aiactionmessages.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gHasPatrolPathConditionProperties;  // 0x11255B20

			// FUNCTION: ENGINE 0x10243760
			bool HasPatrolPathCondition::SetHasPath(bool newValue)
			{
				hasPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102437F0
			fight::Property* HasPatrolPathCondition::GetProperty(int index)
			{
				return gHasPatrolPathConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10243810
			void HasPatrolPathCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHasPatrolPathConditionProperties);
			}

			// FUNCTION: ENGINE 0x10243820
			HasPatrolPathCondition::HasPatrolPathCondition() : fight::Condition(0), hasPath(true)
			{
			}

			// FUNCTION: ENGINE 0x10243840
			HasPatrolPathCondition::~HasPatrolPathCondition()
			{
			}

			// FUNCTION: ENGINE 0x10243C90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HasPatrolPathCondition::RegisterProperties()
			{
				if (gHasPatrolPathConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HasPatrolPathCondition>("hasPath", &HasPatrolPathCondition::SetHasPath);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHasPatrolPathConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10243C00
			fight::ConditionFactory* CreateHasPatrolPathConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasPatrolPathCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10243EF0
			void RegisterHasPatrolPathConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasPatrolPathCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			// FUNCTION: ENGINE 0x102052B0
			bool HasPatrolPathCondition::Evaluate(int a, int b, int c, int d)
			{
				bool has = false;
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object != 0)
				{
					GetPatrolMovementMessage message;
					object->SendMessage(&message);
					if (message.path != 0 && message.path->IsValid())
					{
						has = true;
					}
				}
				bool same = has == hasPath;
				return same;
			}

			fight::Property** gPatrolTrackProperties;  // 0x11255B24

			// FUNCTION: ENGINE 0x10243770
			bool PatrolTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10243790
			bool PatrolTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10243850
			fight::Property* PatrolTrack::GetProperty(int index)
			{
				return gPatrolTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10243870
			void PatrolTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPatrolTrackProperties);
			}

			// FUNCTION: ENGINE 0x10243880
			PatrolTrack::PatrolTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x102438B0
			float PatrolTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x102438C0
			float PatrolTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x102438D0
			PatrolTrack::~PatrolTrack()
			{
			}

			// FUNCTION: ENGINE 0x10243D30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PatrolTrack::RegisterProperties()
			{
				if (gPatrolTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PatrolTrack>("timeBegin", &PatrolTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PatrolTrack>("timeEnd", &PatrolTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPatrolTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10243C30
			fight::TrackFactory* CreatePatrolTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PatrolTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10243F20
			void RegisterPatrolTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PatrolTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPathPatrolTrackProperties;  // 0x11255B28

			// FUNCTION: ENGINE 0x102437B0
			bool PathPatrolTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102437D0
			bool PathPatrolTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102438E0
			fight::Property* PathPatrolTrack::GetProperty(int index)
			{
				return gPathPatrolTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10243900
			void PathPatrolTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPathPatrolTrackProperties);
			}

			// FUNCTION: ENGINE 0x10243910
			PathPatrolTrack::PathPatrolTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10243940
			float PathPatrolTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10243950
			float PathPatrolTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10243960
			PathPatrolTrack::~PathPatrolTrack()
			{
			}

			// FUNCTION: ENGINE 0x10243E10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PathPatrolTrack::RegisterProperties()
			{
				if (gPathPatrolTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PathPatrolTrack>("timeBegin", &PathPatrolTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PathPatrolTrack>("timeEnd", &PathPatrolTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPathPatrolTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10243C60
			fight::TrackFactory* CreatePathPatrolTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PathPatrolTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10243F50
			void RegisterPathPatrolTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PathPatrolTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// FUNCTION: ENGINE 0x102055B0
			PatrolAction::PatrolAction(PatrolTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), follower(newTarget.Get()), notifier(newTarget.Get()), following(&follower, &notifier), unknown74(choreo::gMinusOne)
			{
			}

			// FUNCTION: ENGINE 0x10205380
			PatrolAction::~PatrolAction()
			{
			}

			// FUNCTION: ENGINE 0x102053C0
			bool PatrolAction::Slot7(int arg, float value)
			{
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				math::Matrix& world = object->transform->value;
				math::Vector position(world.m[3][0], world.m[3][1], world.m[3][2]);
				following.Update(&position, value);
				BroadcastPatrolPointAIMsg message(following.unknown2C);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x10205890
			fight::Action* PatrolTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new PatrolAction(this, handle);
			}

			// FUNCTION: ENGINE 0x102056E0
			PathPatrolAction::PathPatrolAction(PathPatrolTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), follower(newTarget.Get()), notifier(newTarget.Get()), following(&follower, &notifier), unknown78(0)
			{
			}

			// FUNCTION: ENGINE 0x102054C0
			PathPatrolAction::~PathPatrolAction()
			{
			}

			// FUNCTION: ENGINE 0x10205010
			void PathPatrolAction::Slot6()
			{
				following.SetPath(0);
			}

			// FUNCTION: ENGINE 0x102058E0
			fight::Action* PathPatrolTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new PathPatrolAction(this, handle);
			}
			// ---- actions end
			template class fight::PropertyBool<HasPatrolPathCondition>;
			template class fight::ConditionFactoryTemplate<HasPatrolPathCondition>;
			template class fight::ConditionFactoryCasterTemplate<HasPatrolPathCondition>;
			template class fight::PropertyFloatConstRange<PatrolTrack>;
			template class fight::TrackFactoryTemplate<PatrolTrack>;
			template class fight::TrackFactoryCasterTemplate<PatrolTrack>;
			template class fight::PropertyFloatConstRange<PathPatrolTrack>;
			template class fight::TrackFactoryTemplate<PathPatrolTrack>;
			template class fight::TrackFactoryCasterTemplate<PathPatrolTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102050C0
// FUNCTION: ENGINE 0x10243970
// FUNCTION: ENGINE 0x102439A0
// FUNCTION: ENGINE 0x102439D0
// FUNCTION: ENGINE 0x10243A00
// FUNCTION: ENGINE 0x10243A10
// FUNCTION: ENGINE 0x10243A40
// FUNCTION: ENGINE 0x10243A50
// FUNCTION: ENGINE 0x10243A80
// FUNCTION: ENGINE 0x10243A90
// FUNCTION: ENGINE 0x10243AC0
// FUNCTION: ENGINE 0x10243AF0
// FUNCTION: ENGINE 0x10243B10
// FUNCTION: ENGINE 0x10243B20
// FUNCTION: ENGINE 0x10243B50
// FUNCTION: ENGINE 0x10243B80
// FUNCTION: ENGINE 0x10243B90
// FUNCTION: ENGINE 0x10243BC0
// FUNCTION: ENGINE 0x10243BF0
// FUNCTION: ENGINE 0x10243F80
// FUNCTION: ENGINE 0x10243FB0
// FUNCTION: ENGINE 0x10243FD0
// FUNCTION: ENGINE 0x10244000
// FUNCTION: ENGINE 0x10244020
// FUNCTION: ENGINE 0x10244050
// FUNCTION: ENGINE 0x10244070
// FUNCTION: ENGINE 0x102440C0
// FUNCTION: ENGINE 0x10244110
// FUNCTION: ENGINE 0x10204F50
// FUNCTION: ENGINE 0x1020BE30
// FUNCTION: ENGINE 0x1020C180

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102056B0
// FUNCTION: ENGINE 0x102057D0
