// Fight items of the motion group: TargetClassTrack, TargetableTrack, TemporaryTargetableTrack (unit 0x101BD3C0 - 0x101BE030; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_targetclass.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gTargetClassTrackProperties;  // 0x11254B98

			// FUNCTION: ENGINE 0x101BD3C0
			bool TargetClassTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BD3E0
			bool TargetClassTrack::SetTargetClass(int newValue)
			{
				targetClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BD460
			fight::Property* TargetClassTrack::GetProperty(int index)
			{
				return gTargetClassTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BD480
			void TargetClassTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTargetClassTrackProperties);
			}

			// FUNCTION: ENGINE 0x101BD490
			TargetClassTrack::TargetClassTrack() : timeBegin(0.0f), targetClass(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101BD4D0
			float TargetClassTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101BD4E0
			float TargetClassTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101BD4F0
			TargetClassTrack::~TargetClassTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BDAB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetClassTrack::RegisterProperties()
			{
				if (gTargetClassTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TargetClassTrack>("timeBegin", &TargetClassTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<TargetClassTrack>("targetClass", gAutoTargetTrackMinPriorityTargetClassTable, gAutoTargetTrackMinPriorityTargetClassCount, &TargetClassTrack::SetTargetClass);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTargetClassTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BDA20
			fight::TrackFactory* CreateTargetClassTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TargetClassTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BDDC0
			void RegisterTargetClassTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TargetClassTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTargetableTrackProperties;  // 0x11254B9C

			// FUNCTION: ENGINE 0x101BD3F0
			bool TargetableTrack::SetTargetable(bool newValue)
			{
				targetable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BD500
			fight::Property* TargetableTrack::GetProperty(int index)
			{
				return gTargetableTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BD520
			void TargetableTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTargetableTrackProperties);
			}

			// FUNCTION: ENGINE 0x101BD530
			TargetableTrack::TargetableTrack() : targetable(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101BD560
			float TargetableTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101BD570
			float TargetableTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101BD580
			TargetableTrack::~TargetableTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BDBA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetableTrack::RegisterProperties()
			{
				if (gTargetableTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetableTrack>("targetable", &TargetableTrack::SetTargetable);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTargetableTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BDA50
			fight::TrackFactory* CreateTargetableTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TargetableTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BDDF0
			void RegisterTargetableTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TargetableTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTemporaryTargetableTrackProperties;  // 0x11254BA0

			// FUNCTION: ENGINE 0x101BD400
			bool TemporaryTargetableTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BD420
			bool TemporaryTargetableTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BD440
			bool TemporaryTargetableTrack::SetOnBegin(int newValue)
			{
				onBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BD450
			bool TemporaryTargetableTrack::SetOnEnd(int newValue)
			{
				onEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BD590
			fight::Property* TemporaryTargetableTrack::GetProperty(int index)
			{
				return gTemporaryTargetableTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BD5B0
			void TemporaryTargetableTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTemporaryTargetableTrackProperties);
			}

			// FUNCTION: ENGINE 0x101BD5C0
			TemporaryTargetableTrack::TemporaryTargetableTrack() : timeBegin(0.0f), timeEnd(-1.0f), onBegin(0), onEnd(0)
			{
			}

			// FUNCTION: ENGINE 0x101BD600
			float TemporaryTargetableTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101BD610
			float TemporaryTargetableTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101BD620
			TemporaryTargetableTrack::~TemporaryTargetableTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BDC40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TemporaryTargetableTrack::RegisterProperties()
			{
				if (gTemporaryTargetableTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TemporaryTargetableTrack>("timeBegin", &TemporaryTargetableTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TemporaryTargetableTrack>("timeEnd", &TemporaryTargetableTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<TemporaryTargetableTrack>("onBegin", gTemporaryTargetableTrackOnBeginTable, gTemporaryTargetableTrackOnBeginCount, &TemporaryTargetableTrack::SetOnBegin);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<TemporaryTargetableTrack>("onEnd", gTemporaryTargetableTrackOnBeginTable, gTemporaryTargetableTrackOnBeginCount, &TemporaryTargetableTrack::SetOnEnd);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gTemporaryTargetableTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BDA80
			fight::TrackFactory* CreateTemporaryTargetableTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TemporaryTargetableTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BDE20
			void RegisterTemporaryTargetableTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TemporaryTargetableTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x1011F560
			TemporaryTargetableAction::TemporaryTargetableAction(TemporaryTargetableTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x1011F140
			TemporaryTargetableAction::~TemporaryTargetableAction()
			{
			}

			// FUNCTION: ENGINE 0x1011F8D0
			fight::Action* TemporaryTargetableTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new TemporaryTargetableAction(this, handle);
			}

			// FUNCTION: ENGINE 0x1011F420
			TargetableAction::TargetableAction(TargetableTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x1011F0F0
			TargetableAction::~TargetableAction()
			{
			}

			// FUNCTION: ENGINE 0x1011F870
			// EQUIVALENT: the range test of the owner kind is add ecx, 0xFFFF0000 where ours has sub ecx, 0x10000 (the same value), the engine loads the handle into esi where ours uses ecx (93.4 %)
			fight::Action* TargetableTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				ActionOwner* actionOwner = AsActionOwner(owner);
				return new TargetableAction(this, actionOwner->handle);
			}

			// FUNCTION: ENGINE 0x1011F2C0
			TargetClassAction::TargetClassAction(TargetClassTrack* newTrack, engine::GameObjectHandle newTarget, fight::Track* listener, core::IRefCount* newOwner) : fight::Action(0x200), link(newTrack), target(newTarget), watch(listener), owner(0)
			{
				engine::AssignRefCounted(&owner, newOwner);
			}

			// FUNCTION: ENGINE 0x1011F080
			TargetClassAction::~TargetClassAction()
			{
				core::SafeReleaseRef(owner);
			}

			// FUNCTION: ENGINE 0x1011F800
			// EQUIVALENT: the range test of the owner kind is add ecx, 0xFFFF0000 where ours has sub ecx, 0x10000 (the same value), the engine loads the handle into esi where ours uses ecx (94.0 %)
			fight::Action* TargetClassTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				ActionOwner* actionOwner = AsActionOwner(owner);
				return new TargetClassAction(this, actionOwner->handle, listener, owner);
			}

			// FUNCTION: ENGINE 0x1011F390
			// EQUIVALENT: block order (the engine falls into the failure return and jumps to the body) (24.6 %)
			bool TargetClassAction::Slot5(int arg, float value)
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						SetTargetClassMessage message(link.object->targetClass);
						object->SendMessage(&message);
						return true;
					}
				}
				return false;
			}

			// FUNCTION: ENGINE 0x1011F4D0
			// EQUIVALENT: block order (the engine falls into the failure return and jumps to the body) (24.6 %)
			bool TargetableAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					SetTargetableTargetMessage message(link.object->targetable);
					object->SendMessage(&message);
					return true;
				}
				return false;
			}

			// FUNCTION: ENGINE 0x1011F610
			// EQUIVALENT: register allocation and the arms of the switch: the engine stores the state byte per arm and keeps a zero in ebx (76.1 %)
			bool TemporaryTargetableAction::Slot5(int arg, float value)
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
				GetTargetableInfoMessage info;
				object->SendMessage(&info);
				targetable = info.targetable;
				bool state;
				switch (link.object->onBegin)
				{
				case 1:
					state = true;
					break;
				case 2:
					state = false;
					break;
				default:
					return true;
				}
				SetTargetableTargetMessage message(state);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x1011F740
			bool TemporaryTargetableAction::Slot7(int arg, float value)
			{
				return link.object != 0 ? true : false;
			}

			// FUNCTION: ENGINE 0x1011F750
			// EQUIVALENT: register allocation and the arms of the switch: the engine stores the state byte per arm and keeps a zero in ebx (16.3 %)
			void TemporaryTargetableAction::Slot6()
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						bool state;
						switch (link.object->onEnd)
						{
						case 1:
							state = true;
							break;
						case 2:
							state = false;
							break;
						case 3:
							state = targetable;
							break;
						default:
							return;
						}
						SetTargetableTargetMessage message(state);
						object->SendMessage(&message);
					}
				}
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<TargetClassTrack>;
			template class fight::PropertyEnumConstList<TargetClassTrack>;
			template class fight::TrackFactoryTemplate<TargetClassTrack>;
			template class fight::TrackFactoryCasterTemplate<TargetClassTrack>;
			template class fight::PropertyBool<TargetableTrack>;
			template class fight::TrackFactoryTemplate<TargetableTrack>;
			template class fight::TrackFactoryCasterTemplate<TargetableTrack>;
			template class fight::PropertyFloatConstRange<TemporaryTargetableTrack>;
			template class fight::PropertyEnumConstList<TemporaryTargetableTrack>;
			template class fight::TrackFactoryTemplate<TemporaryTargetableTrack>;
			template class fight::TrackFactoryCasterTemplate<TemporaryTargetableTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1011EE40
// FUNCTION: ENGINE 0x1011EE70
// FUNCTION: ENGINE 0x1011EEB0
// FUNCTION: ENGINE 0x1011EEE0
// FUNCTION: ENGINE 0x1011EF00
// FUNCTION: ENGINE 0x1011EF20
// FUNCTION: ENGINE 0x1011EF50
// FUNCTION: ENGINE 0x1011EFB0
// FUNCTION: ENGINE 0x1011F010
// FUNCTION: ENGINE 0x1011F360
// FUNCTION: ENGINE 0x1011F4A0
// FUNCTION: ENGINE 0x1011F5E0
// FUNCTION: ENGINE 0x101BD630
// FUNCTION: ENGINE 0x101BD660
// FUNCTION: ENGINE 0x101BD690
// FUNCTION: ENGINE 0x101BD6C0
// FUNCTION: ENGINE 0x101BD6D0
// FUNCTION: ENGINE 0x101BD700
// FUNCTION: ENGINE 0x101BD710
// FUNCTION: ENGINE 0x101BD740
// FUNCTION: ENGINE 0x101BD750
// FUNCTION: ENGINE 0x101BD780
// FUNCTION: ENGINE 0x101BD7B0
// FUNCTION: ENGINE 0x101BD7E0
// FUNCTION: ENGINE 0x101BD7F0
// FUNCTION: ENGINE 0x101BD830
// FUNCTION: ENGINE 0x101BD840
// FUNCTION: ENGINE 0x101BD870
// FUNCTION: ENGINE 0x101BD890
// FUNCTION: ENGINE 0x101BD8A0
// FUNCTION: ENGINE 0x101BD8D0
// FUNCTION: ENGINE 0x101BD8F0
// FUNCTION: ENGINE 0x101BD900
// FUNCTION: ENGINE 0x101BD930
// FUNCTION: ENGINE 0x101BD960
// FUNCTION: ENGINE 0x101BD970
// FUNCTION: ENGINE 0x101BD9B0
// FUNCTION: ENGINE 0x101BD9C0
// FUNCTION: ENGINE 0x101BD9F0
// FUNCTION: ENGINE 0x101BDA10
// FUNCTION: ENGINE 0x101BDE50
// FUNCTION: ENGINE 0x101BDE80
// FUNCTION: ENGINE 0x101BDEA0
// FUNCTION: ENGINE 0x101BDED0
// FUNCTION: ENGINE 0x101BDEF0
// FUNCTION: ENGINE 0x101BDF20
// FUNCTION: ENGINE 0x101BDF40
// FUNCTION: ENGINE 0x101BDF90
// FUNCTION: ENGINE 0x101BDFE0
