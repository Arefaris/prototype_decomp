// Fight items of the ai group: FixedDestinationDistanceCondition, FixedDestinationGotoTrack, FixedDestinationJumpToTrack, ClearFixedAreaDestinationTrack, FixedDestinationFlytoTrack (unit 0x102305F0 - 0x10231FB0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_fixeddestination.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/fightitems/ai/aiactionmessages.h"
#include "code/proto/fightitems/ai/aiactionhelpers.h"
#include "code/proto/scenariomessages.h"
#include "code/proto/fightitems/motion/motioncommon.h"
#include "code/core/strings.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gFixedDestinationDistanceConditionProperties;  // 0x112559C8

			// FUNCTION: ENGINE 0x102305F0
			bool FixedDestinationDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230600
			bool FixedDestinationDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230610
			bool FixedDestinationDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101F16D0
			bool FixedDestinationDistanceCondition::Evaluate(int a, int b, int c, int d)
			{
				bool result = false;
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object != 0)
				{
					GetFixedDestinationMessage message;
					object->SendMessage(&message);
					if (message.destination == 0)
					{
						return false;
					}
					math::Vector target(message.destination->position.x, message.destination->position.y, message.destination->position.z);
					math::Matrix* world = object->transform->GetPointer();
					math::Vector position(world->m[3][0], world->m[3][1], world->m[3][2]);
					math::Vector offset;
					offset.Sub(target, position);
					int selector = direction;
					float limit = distance;
					int op = compare;
					result = fight::CompareVectorMeasure(op, &offset, selector, limit);
				}
				return result;
			}

			// FUNCTION: ENGINE 0x10230870
			fight::Property* FixedDestinationDistanceCondition::GetProperty(int index)
			{
				return gFixedDestinationDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10230890
			void FixedDestinationDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gFixedDestinationDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x102308A0
			FixedDestinationDistanceCondition::FixedDestinationDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x102308E0
			FixedDestinationDistanceCondition::~FixedDestinationDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x102313B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FixedDestinationDistanceCondition::RegisterProperties()
			{
				if (gFixedDestinationDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<FixedDestinationDistanceCondition>("direction", motion::gCrowdPositionConditionDirectionTable, motion::gCrowdPositionConditionDirectionCount, &FixedDestinationDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<FixedDestinationDistanceCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &FixedDestinationDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationDistanceCondition>("distance", &FixedDestinationDistanceCondition::SetDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gFixedDestinationDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102312C0
			fight::ConditionFactory* CreateFixedDestinationDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FixedDestinationDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231BA0
			void RegisterFixedDestinationDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FixedDestinationDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFixedDestinationGotoTrackProperties;  // 0x112559CC

			// FUNCTION: ENGINE 0x10230630
			bool FixedDestinationGotoTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230650
			bool FixedDestinationGotoTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230670
			bool FixedDestinationGotoTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230690
			bool FixedDestinationGotoTrack::SetBraking(bool newValue)
			{
				braking = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102306A0
			bool FixedDestinationGotoTrack::SetIgnoreRestrictions(bool newValue)
			{
				ignoreRestrictions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102306B0
			bool FixedDestinationGotoTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102308F0
			fight::Property* FixedDestinationGotoTrack::GetProperty(int index)
			{
				return gFixedDestinationGotoTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10230910
			void FixedDestinationGotoTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFixedDestinationGotoTrackProperties);
			}

			// FUNCTION: ENGINE 0x10230920
			FixedDestinationGotoTrack::FixedDestinationGotoTrack() : timeBegin(0.0f), timeEnd(-1.0f), tolerance(0.5f), braking(true), clearDestination(true), ignoreRestrictions(true)
			{
			}

			// FUNCTION: ENGINE 0x10230970
			float FixedDestinationGotoTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10230980
			float FixedDestinationGotoTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10230990
			FixedDestinationGotoTrack::~FixedDestinationGotoTrack()
			{
			}

			// FUNCTION: ENGINE 0x102314F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FixedDestinationGotoTrack::RegisterProperties()
			{
				if (gFixedDestinationGotoTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FixedDestinationGotoTrack>("timeBegin", &FixedDestinationGotoTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationGotoTrack>("timeEnd", &FixedDestinationGotoTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationGotoTrack>("tolerance", &FixedDestinationGotoTrack::SetTolerance);
					properties[2] = property;
					property = new fight::PropertyBool<FixedDestinationGotoTrack>("braking", &FixedDestinationGotoTrack::SetBraking);
					properties[3] = property;
					property = new fight::PropertyBool<FixedDestinationGotoTrack>("ignoreRestrictions", &FixedDestinationGotoTrack::SetIgnoreRestrictions);
					properties[4] = property;
					property = new fight::PropertyBool<FixedDestinationGotoTrack>("clearDestination", &FixedDestinationGotoTrack::SetClearDestination);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gFixedDestinationGotoTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102312F0
			fight::TrackFactory* CreateFixedDestinationGotoTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationGotoTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231BD0
			void RegisterFixedDestinationGotoTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationGotoTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gFixedDestinationJumpToTrackProperties;  // 0x112559D0

			// FUNCTION: ENGINE 0x102306C0
			bool FixedDestinationJumpToTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102306E0
			bool FixedDestinationJumpToTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230700
			bool FixedDestinationJumpToTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102309A0
			fight::Property* FixedDestinationJumpToTrack::GetProperty(int index)
			{
				return gFixedDestinationJumpToTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102309C0
			void FixedDestinationJumpToTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFixedDestinationJumpToTrackProperties);
			}

			// FUNCTION: ENGINE 0x102309D0
			FixedDestinationJumpToTrack::FixedDestinationJumpToTrack() : timeBegin(0.0f), timeEnd(-1.0f), clearDestination(true)
			{
			}

			// FUNCTION: ENGINE 0x10230A10
			float FixedDestinationJumpToTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10230A20
			float FixedDestinationJumpToTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10230A30
			FixedDestinationJumpToTrack::~FixedDestinationJumpToTrack()
			{
			}

			// FUNCTION: ENGINE 0x102316C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FixedDestinationJumpToTrack::RegisterProperties()
			{
				if (gFixedDestinationJumpToTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FixedDestinationJumpToTrack>("timeBegin", &FixedDestinationJumpToTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationJumpToTrack>("timeEnd", &FixedDestinationJumpToTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<FixedDestinationJumpToTrack>("clearDestination", &FixedDestinationJumpToTrack::SetClearDestination);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gFixedDestinationJumpToTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10231320
			fight::TrackFactory* CreateFixedDestinationJumpToTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationJumpToTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231C00
			void RegisterFixedDestinationJumpToTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationJumpToTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gClearFixedAreaDestinationTrackProperties;  // 0x112559D4

			// FUNCTION: ENGINE 0x10230710
			bool ClearFixedAreaDestinationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230730
			bool ClearFixedAreaDestinationTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230750
			bool ClearFixedAreaDestinationTrack::SetClearOnBegin(bool newValue)
			{
				clearOnBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230A40
			fight::Property* ClearFixedAreaDestinationTrack::GetProperty(int index)
			{
				return gClearFixedAreaDestinationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10230A60
			void ClearFixedAreaDestinationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gClearFixedAreaDestinationTrackProperties);
			}

			// FUNCTION: ENGINE 0x10230A70
			ClearFixedAreaDestinationTrack::ClearFixedAreaDestinationTrack() : timeBegin(0.0f), timeEnd(-1.0f), clearOnBegin(true)
			{
			}

			// FUNCTION: ENGINE 0x10230AB0
			float ClearFixedAreaDestinationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10230AC0
			float ClearFixedAreaDestinationTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10230AD0
			ClearFixedAreaDestinationTrack::~ClearFixedAreaDestinationTrack()
			{
			}

			// FUNCTION: ENGINE 0x102317D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ClearFixedAreaDestinationTrack::RegisterProperties()
			{
				if (gClearFixedAreaDestinationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ClearFixedAreaDestinationTrack>("timeBegin", &ClearFixedAreaDestinationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ClearFixedAreaDestinationTrack>("timeEnd", &ClearFixedAreaDestinationTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ClearFixedAreaDestinationTrack>("clearOnBegin", &ClearFixedAreaDestinationTrack::SetClearOnBegin);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gClearFixedAreaDestinationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10231350
			fight::TrackFactory* CreateClearFixedAreaDestinationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearFixedAreaDestinationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231C30
			void RegisterClearFixedAreaDestinationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearFixedAreaDestinationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gFixedDestinationFlytoTrackProperties;  // 0x112559D8

			// FUNCTION: ENGINE 0x10230760
			bool FixedDestinationFlytoTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230780
			bool FixedDestinationFlytoTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307A0
			bool FixedDestinationFlytoTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307C0
			bool FixedDestinationFlytoTrack::SetBraking(bool newValue)
			{
				braking = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307D0
			bool FixedDestinationFlytoTrack::SetIgnoreRestrictions(bool newValue)
			{
				ignoreRestrictions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307E0
			bool FixedDestinationFlytoTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307F0
			bool FixedDestinationFlytoTrack::SetFreeArea(float newValue)
			{
				freeArea = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230810
			bool FixedDestinationFlytoTrack::SetMinHeight(float newValue)
			{
				minHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230830
			bool FixedDestinationFlytoTrack::SetMaxSpeed(float newValue)
			{
				maxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230850
			bool FixedDestinationFlytoTrack::SetSpeedFactor(const math::Vector& newValue)
			{
				speedFactor.x = newValue.x;
				speedFactor.y = newValue.y;
				speedFactor.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10230AE0
			fight::Property* FixedDestinationFlytoTrack::GetProperty(int index)
			{
				return gFixedDestinationFlytoTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10230B00
			void FixedDestinationFlytoTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFixedDestinationFlytoTrackProperties);
			}

			// FUNCTION: ENGINE 0x10230B10
			FixedDestinationFlytoTrack::FixedDestinationFlytoTrack() : speedFactor(-1.0f, -1.0f, -1.0f), freeArea(0.0f), maxSpeed(1.0f), minHeight(6.0f), timeBegin(0.0f), timeEnd(-1.0f), tolerance(0.5f), braking(true), clearDestination(true), ignoreRestrictions(true)
			{
			}

			// FUNCTION: ENGINE 0x10230BA0
			float FixedDestinationFlytoTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10230BB0
			float FixedDestinationFlytoTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10230BC0
			FixedDestinationFlytoTrack::~FixedDestinationFlytoTrack()
			{
			}

			// FUNCTION: ENGINE 0x102318E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FixedDestinationFlytoTrack::RegisterProperties()
			{
				if (gFixedDestinationFlytoTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("timeBegin", &FixedDestinationFlytoTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("timeEnd", &FixedDestinationFlytoTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("tolerance", &FixedDestinationFlytoTrack::SetTolerance);
					properties[2] = property;
					property = new fight::PropertyBool<FixedDestinationFlytoTrack>("braking", &FixedDestinationFlytoTrack::SetBraking);
					properties[3] = property;
					property = new fight::PropertyBool<FixedDestinationFlytoTrack>("ignoreRestrictions", &FixedDestinationFlytoTrack::SetIgnoreRestrictions);
					properties[4] = property;
					property = new fight::PropertyBool<FixedDestinationFlytoTrack>("clearDestination", &FixedDestinationFlytoTrack::SetClearDestination);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("freeArea", &FixedDestinationFlytoTrack::SetFreeArea);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("minHeight", &FixedDestinationFlytoTrack::SetMinHeight);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("maxSpeed", &FixedDestinationFlytoTrack::SetMaxSpeed);
					properties[8] = property;
					property = new fight::PropertyVector<FixedDestinationFlytoTrack>("speedFactor", &FixedDestinationFlytoTrack::SetSpeedFactor);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gFixedDestinationFlytoTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10231380
			fight::TrackFactory* CreateFixedDestinationFlytoTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationFlytoTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231C60
			void RegisterFixedDestinationFlytoTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationFlytoTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// FUNCTION: ENGINE 0x101F1AF0
			void FixedDestinationGotoAction::MoveToDestination(engine::GameObject* object)
			{
				MoveParams params;
				params.tolerance = link.Get()->tolerance;
				params.braking = link.Get()->braking;
				params.ignoreRestrictions = link.Get()->ignoreRestrictions;
				Unknown103B8330(object, &unknown2C, &params);
			}

			// FUNCTION: ENGINE 0x101F2770
			bool FixedDestinationGotoAction::Slot5(int arg, float value)
			{
				if (link.Get() == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				GetTaskAIMsg task;
				object->SendMessage(&task);
				unknown38 = task.task;
				GetFixedDestinationMessage message;
				object->SendMessage(&message);
				if (message.destination != 0)
				{
					unknown2C.x = message.destination->position.x;
					unknown2C.y = message.destination->position.y;
					unknown2C.z = message.destination->position.z;
					message.destination->source = this;
					MoveToDestination(object);
					return true;
				}
				Unknown103B82F0(object);
				return false;
			}

			// FUNCTION: ENGINE 0x101F28B0
			// NONMATCHING: the engine stores the arrived flag before it pushes the object, ours after loading this, 98 %
#ifdef NONMATCHING
			bool FixedDestinationGotoAction::Slot7(int arg, float value)
			{
				if (link.Get() == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				GetFixedDestinationMessage message;
				object->SendMessage(&message);
				if (message.destination != 0)
				{
					message.destination->source = this;
					math::Vector position(message.destination->position.x, message.destination->position.y, message.destination->position.z);
					if (math::DistanceSquared(position, unknown2C) > engine::driving::gOne)
					{
						unknown40 = false;
						unknown2C.x = position.x;
						unknown2C.y = position.y;
						unknown2C.z = position.z;
						MoveToDestination(object);
					}
					if (!unknown40 && Unknown103B8440(object))
					{
						DestinationReachedMessage reached(target, "goto");
						engine::SendMessage(&reached, &engine::gScenario38);
						unknown40 = true;
					}
					return true;
				}
				unknown2C.z = 0.0f;
				unknown2C.y = 0.0f;
				unknown2C.x = 0.0f;
				return false;
			}
#endif

			// FUNCTION: ENGINE 0x101F1290
			void ClearFixedDestinationUnlessGoto(fight::Action* action, const core::Name<core::CaseSensitiveKey>* task, engine::GameObject* object)
			{
				GetTaskAIMsg message;
				object->SendMessage(&message);
				if (*task != message.task)
				{
					for (int i = 0; i < 8; i++)
					{
						if (message.task == engine::gGotoTable[i].name)
						{
							return;
						}
					}
				}
				ClearFixedDestinationMessage clear(action);
				object->SendMessage(&clear);
			}

			// FUNCTION: ENGINE 0x101F1AA0
			void FixedDestinationGotoAction::Slot6()
			{
				if (link.object->clearDestination)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						ClearFixedDestinationUnlessGoto(this, &unknown38, object);
					}
				}
			}

			// FUNCTION: ENGINE 0x101F20E0
			void FixedDestinationJumpToAction::Slot6()
			{
				if (link.object->clearDestination)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						ClearFixedDestinationUnlessGoto(this, &unknown38, object);
					}
				}
			}
			// FUNCTION: ENGINE 0x101F2560
			ClearFixedAreaDestinationAction::ClearFixedAreaDestinationAction(ClearFixedAreaDestinationTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101F16A0
			ClearFixedAreaDestinationAction::~ClearFixedAreaDestinationAction()
			{
			}

			// FUNCTION: ENGINE 0x101F2B00
			fight::Action* ClearFixedAreaDestinationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ClearFixedAreaDestinationAction(this, handle, effect, listener);
			}

			// FUNCTION: ENGINE 0x101F19D0
			FixedDestinationGotoAction::FixedDestinationGotoAction(FixedDestinationGotoTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(math::kZeroVector), unknown40(false)
			{
			}

			// FUNCTION: ENGINE 0x101F15B0
			FixedDestinationGotoAction::~FixedDestinationGotoAction()
			{
			}

			// FUNCTION: ENGINE 0x101F2720
			fight::Action* FixedDestinationGotoTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FixedDestinationGotoAction(this, handle);
			}
			// FUNCTION: ENGINE 0x101F1B60
			FixedDestinationFlytoAction::FixedDestinationFlytoAction(FixedDestinationFlytoTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(math::kZeroVector), unknown38(false)
			{
			}

			// FUNCTION: ENGINE 0x101F1600
			FixedDestinationFlytoAction::~FixedDestinationFlytoAction()
			{
			}

			// FUNCTION: ENGINE 0x101F2A60
			fight::Action* FixedDestinationFlytoTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FixedDestinationFlytoAction(this, handle);
			}
			// FUNCTION: ENGINE 0x101F1D70
			FixedDestinationJumpToAction::FixedDestinationJumpToAction(FixedDestinationJumpToTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(math::kZeroVector), unknown40(false)
			{
			}

			// FUNCTION: ENGINE 0x101F1650
			FixedDestinationJumpToAction::~FixedDestinationJumpToAction()
			{
			}

			// FUNCTION: ENGINE 0x101F2AB0
			fight::Action* FixedDestinationJumpToTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FixedDestinationJumpToAction(this, handle);
			}
			// FUNCTION: ENGINE 0x101F2610
			bool ClearFixedAreaDestinationAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				if (link.object->clearOnBegin)
				{
					ClearFixedAreaDestinationMessage message;
					object->SendMessage(&message);
				}
				return true;
			}

			// FUNCTION: ENGINE 0x101F26A0
			void ClearFixedAreaDestinationAction::Slot6()
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0 && !link.object->clearOnBegin)
					{
						ClearFixedAreaDestinationMessage message;
						object->SendMessage(&message);
					}
				}
			}

			// ---- actions end
			template class fight::PropertyEnumConstList<FixedDestinationDistanceCondition>;
			template class fight::PropertyFloatConstRange<FixedDestinationDistanceCondition>;
			template class fight::ConditionFactoryTemplate<FixedDestinationDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<FixedDestinationDistanceCondition>;
			template class fight::PropertyFloatConstRange<FixedDestinationGotoTrack>;
			template class fight::PropertyBool<FixedDestinationGotoTrack>;
			template class fight::TrackFactoryTemplate<FixedDestinationGotoTrack>;
			template class fight::TrackFactoryCasterTemplate<FixedDestinationGotoTrack>;
			template class fight::PropertyFloatConstRange<FixedDestinationJumpToTrack>;
			template class fight::PropertyBool<FixedDestinationJumpToTrack>;
			template class fight::TrackFactoryTemplate<FixedDestinationJumpToTrack>;
			template class fight::TrackFactoryCasterTemplate<FixedDestinationJumpToTrack>;
			template class fight::PropertyFloatConstRange<ClearFixedAreaDestinationTrack>;
			template class fight::PropertyBool<ClearFixedAreaDestinationTrack>;
			template class fight::TrackFactoryTemplate<ClearFixedAreaDestinationTrack>;
			template class fight::TrackFactoryCasterTemplate<ClearFixedAreaDestinationTrack>;
			template class fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>;
			template class fight::PropertyBool<FixedDestinationFlytoTrack>;
			template class fight::PropertyVector<FixedDestinationFlytoTrack>;
			template class fight::TrackFactoryTemplate<FixedDestinationFlytoTrack>;
			template class fight::TrackFactoryCasterTemplate<FixedDestinationFlytoTrack>;
		}
	}
}

template core::Link<proto::fightitems::ai::ClearFixedAreaDestinationTrack>::~Link();
template core::Link<proto::fightitems::ai::FixedDestinationGotoTrack>::~Link();
template core::Link<proto::fightitems::ai::FixedDestinationFlytoTrack>::~Link();
template core::Link<proto::fightitems::ai::FixedDestinationJumpToTrack>::~Link();
template proto::fightitems::ai::ClearFixedAreaDestinationTrack* core::Link<proto::fightitems::ai::ClearFixedAreaDestinationTrack>::Get() const;
template core::Link<proto::fightitems::ai::ClearFixedAreaDestinationTrack>::Link(proto::fightitems::ai::ClearFixedAreaDestinationTrack*);
template proto::fightitems::ai::FixedDestinationGotoTrack* core::Link<proto::fightitems::ai::FixedDestinationGotoTrack>::Get() const;
template core::Link<proto::fightitems::ai::FixedDestinationGotoTrack>::Link(proto::fightitems::ai::FixedDestinationGotoTrack*);
template proto::fightitems::ai::FixedDestinationFlytoTrack* core::Link<proto::fightitems::ai::FixedDestinationFlytoTrack>::Get() const;
template core::Link<proto::fightitems::ai::FixedDestinationFlytoTrack>::Link(proto::fightitems::ai::FixedDestinationFlytoTrack*);
template proto::fightitems::ai::FixedDestinationJumpToTrack* core::Link<proto::fightitems::ai::FixedDestinationJumpToTrack>::Get() const;
template core::Link<proto::fightitems::ai::FixedDestinationJumpToTrack>::Link(proto::fightitems::ai::FixedDestinationJumpToTrack*);

namespace proto
{
	// FUNCTION: ENGINE 0x101F1030
	DestinationReachedMessage::DestinationReachedMessage(engine::GameObjectHandle arrived, const char* newData) : engine::ScenarioMessage(0x1A)
	{
		handles[0] = arrived;
		core::StrNCpy(data, newData, 0x40u);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101F25E0
// FUNCTION: ENGINE 0x10230BD0
// FUNCTION: ENGINE 0x10230C00
// FUNCTION: ENGINE 0x10230C30
// FUNCTION: ENGINE 0x10230C60
// FUNCTION: ENGINE 0x10230C90
// FUNCTION: ENGINE 0x10230CC0
// FUNCTION: ENGINE 0x10230CD0
// FUNCTION: ENGINE 0x10230D00
// FUNCTION: ENGINE 0x10230D10
// FUNCTION: ENGINE 0x10230D40
// FUNCTION: ENGINE 0x10230D50
// FUNCTION: ENGINE 0x10230D80
// FUNCTION: ENGINE 0x10230D90
// FUNCTION: ENGINE 0x10230DC0
// FUNCTION: ENGINE 0x10230DD0
// FUNCTION: ENGINE 0x10230E00
// FUNCTION: ENGINE 0x10230E40
// FUNCTION: ENGINE 0x10230E50
// FUNCTION: ENGINE 0x10230E80
// FUNCTION: ENGINE 0x10230EA0
// FUNCTION: ENGINE 0x10230EB0
// FUNCTION: ENGINE 0x10230EE0
// FUNCTION: ENGINE 0x10230F10
// FUNCTION: ENGINE 0x10230F20
// FUNCTION: ENGINE 0x10230F50
// FUNCTION: ENGINE 0x10230F80
// FUNCTION: ENGINE 0x10230F90
// FUNCTION: ENGINE 0x10230FC0
// FUNCTION: ENGINE 0x10230FE0
// FUNCTION: ENGINE 0x10230FF0
// FUNCTION: ENGINE 0x10231020
// FUNCTION: ENGINE 0x10231050
// FUNCTION: ENGINE 0x10231060
// FUNCTION: ENGINE 0x10231090
// FUNCTION: ENGINE 0x102310B0
// FUNCTION: ENGINE 0x102310C0
// FUNCTION: ENGINE 0x102310F0
// FUNCTION: ENGINE 0x10231120
// FUNCTION: ENGINE 0x10231130
// FUNCTION: ENGINE 0x10231160
// FUNCTION: ENGINE 0x10231180
// FUNCTION: ENGINE 0x10231190
// FUNCTION: ENGINE 0x102311C0
// FUNCTION: ENGINE 0x102311F0
// FUNCTION: ENGINE 0x10231200
// FUNCTION: ENGINE 0x10231230
// FUNCTION: ENGINE 0x10231250
// FUNCTION: ENGINE 0x10231260
// FUNCTION: ENGINE 0x10231290
// FUNCTION: ENGINE 0x102312B0
// FUNCTION: ENGINE 0x10231C90
// FUNCTION: ENGINE 0x10231CC0
// FUNCTION: ENGINE 0x10231CE0
// FUNCTION: ENGINE 0x10231D10
// FUNCTION: ENGINE 0x10231D30
// FUNCTION: ENGINE 0x10231D60
// FUNCTION: ENGINE 0x10231D80
// FUNCTION: ENGINE 0x10231DB0
// FUNCTION: ENGINE 0x10231DD0
// FUNCTION: ENGINE 0x10231E00
// FUNCTION: ENGINE 0x10231E20
// FUNCTION: ENGINE 0x10231E70
// FUNCTION: ENGINE 0x10231EC0
// FUNCTION: ENGINE 0x10231F10
// FUNCTION: ENGINE 0x10231F60
// FUNCTION: ENGINE 0x101F1360
// FUNCTION: ENGINE 0x101F1380
// FUNCTION: ENGINE 0x101F13E0
// FUNCTION: ENGINE 0x101F13F0
// FUNCTION: ENGINE 0x101F1440
// FUNCTION: ENGINE 0x101F1450
// FUNCTION: ENGINE 0x101F1590
// FUNCTION: ENGINE 0x101F15E0
// FUNCTION: ENGINE 0x101F1860
// FUNCTION: ENGINE 0x101F1870
// FUNCTION: ENGINE 0x101F1880
// FUNCTION: ENGINE 0x101F18F0
// FUNCTION: ENGINE 0x101F0FA0
// FUNCTION: ENGINE 0x101F0FD0
// FUNCTION: ENGINE 0x101F0F20
// FUNCTION: ENGINE 0x101F0F60
// FUNCTION: ENGINE 0x101F0F90
// FUNCTION: ENGINE 0x101F1020
// FUNCTION: ENGINE 0x101F1240
