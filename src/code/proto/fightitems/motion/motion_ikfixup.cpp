// Fight items of the motion group: IKSurfaceFixupTrack, ShoulderConFixupTrack (unit 0x10180090 - 0x10180910; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_ikfixup.h"
#include "code/proto/fightitems/motion/motionmessages3.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gIKSurfaceFixupTrackProperties;  // 0x1125473C

			// FUNCTION: ENGINE 0x10180090
			bool IKSurfaceFixupTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101800B0
			bool IKSurfaceFixupTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101800D0
			bool IKSurfaceFixupTrack::SetEnabled(bool newValue)
			{
				enabled = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10180130
			fight::Property* IKSurfaceFixupTrack::GetProperty(int index)
			{
				return gIKSurfaceFixupTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10180150
			void IKSurfaceFixupTrack::ClearProperties()
			{
				fight::FreePropertyList(&gIKSurfaceFixupTrackProperties);
			}

			// FUNCTION: ENGINE 0x10180160
			IKSurfaceFixupTrack::IKSurfaceFixupTrack() : timeBegin(0.0f), timeEnd(-1.0f), enabled(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101801A0
			float IKSurfaceFixupTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101801B0
			float IKSurfaceFixupTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101801C0
			IKSurfaceFixupTrack::~IKSurfaceFixupTrack()
			{
			}

			// FUNCTION: ENGINE 0x10180550
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IKSurfaceFixupTrack::RegisterProperties()
			{
				if (gIKSurfaceFixupTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<IKSurfaceFixupTrack>("timeBegin", &IKSurfaceFixupTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<IKSurfaceFixupTrack>("timeEnd", &IKSurfaceFixupTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<IKSurfaceFixupTrack>("enabled", &IKSurfaceFixupTrack::SetEnabled);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gIKSurfaceFixupTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101804F0
			fight::TrackFactory* CreateIKSurfaceFixupTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<IKSurfaceFixupTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10180770
			void RegisterIKSurfaceFixupTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<IKSurfaceFixupTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShoulderConFixupTrackProperties;  // 0x11254740

			// FUNCTION: ENGINE 0x101800E0
			bool ShoulderConFixupTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10180100
			bool ShoulderConFixupTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10180120
			bool ShoulderConFixupTrack::SetEnabled(bool newValue)
			{
				enabled = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101801D0
			fight::Property* ShoulderConFixupTrack::GetProperty(int index)
			{
				return gShoulderConFixupTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101801F0
			void ShoulderConFixupTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShoulderConFixupTrackProperties);
			}

			// FUNCTION: ENGINE 0x10180200
			ShoulderConFixupTrack::ShoulderConFixupTrack() : timeBegin(0.0f), timeEnd(-1.0f), enabled(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10180240
			float ShoulderConFixupTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10180250
			float ShoulderConFixupTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10180260
			ShoulderConFixupTrack::~ShoulderConFixupTrack()
			{
			}

			// FUNCTION: ENGINE 0x10180660
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShoulderConFixupTrack::RegisterProperties()
			{
				if (gShoulderConFixupTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShoulderConFixupTrack>("timeBegin", &ShoulderConFixupTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ShoulderConFixupTrack>("timeEnd", &ShoulderConFixupTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ShoulderConFixupTrack>("enabled", &ShoulderConFixupTrack::SetEnabled);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gShoulderConFixupTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10180520
			fight::TrackFactory* CreateShoulderConFixupTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShoulderConFixupTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101807A0
			void RegisterShoulderConFixupTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShoulderConFixupTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100DAB50
			IKSurfaceFixupAction::IKSurfaceFixupAction(IKSurfaceFixupTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x100DA9F0
			IKSurfaceFixupAction::~IKSurfaceFixupAction()
			{
			}

			// FUNCTION: ENGINE 0x100DAEF0
			fight::Action* IKSurfaceFixupTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new IKSurfaceFixupAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100DAD20
			ShoulderConFixupAction::ShoulderConFixupAction(ShoulderConFixupTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x100DAA40
			ShoulderConFixupAction::~ShoulderConFixupAction()
			{
			}

			// FUNCTION: ENGINE 0x100DAF40
			fight::Action* ShoulderConFixupTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ShoulderConFixupAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100DAC00
			bool IKSurfaceFixupAction::Slot5(int arg, float value)
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
				proto::SetIKSurfaceFixupEnabledMessage message(link.object->enabled);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x100DADD0
			bool ShoulderConFixupAction::Slot5(int arg, float value)
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
				proto::SetShoulderConFixupEnabledMessage message(link.object->enabled);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x100DAC90
			void IKSurfaceFixupAction::Slot6()
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						bool enabled = link.object->enabled;
						proto::SetIKSurfaceFixupEnabledMessage message(!enabled);
						object->SendMessage(&message);
					}
				}
			}

			// FUNCTION: ENGINE 0x100DAE60
			void ShoulderConFixupAction::Slot6()
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						bool enabled = link.object->enabled;
						proto::SetShoulderConFixupEnabledMessage message(!enabled);
						object->SendMessage(&message);
					}
				}
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<IKSurfaceFixupTrack>;
			template class fight::PropertyBool<IKSurfaceFixupTrack>;
			template class fight::TrackFactoryTemplate<IKSurfaceFixupTrack>;
			template class fight::TrackFactoryCasterTemplate<IKSurfaceFixupTrack>;
			template class fight::PropertyFloatConstRange<ShoulderConFixupTrack>;
			template class fight::PropertyBool<ShoulderConFixupTrack>;
			template class fight::TrackFactoryTemplate<ShoulderConFixupTrack>;
			template class fight::TrackFactoryCasterTemplate<ShoulderConFixupTrack>;
		}
	}
}

// Explicit instances of the track links' accessors (the engine keeps their copies):
template proto::fightitems::motion::IKSurfaceFixupTrack* core::Link<proto::fightitems::motion::IKSurfaceFixupTrack>::Get() const;
template proto::fightitems::motion::ShoulderConFixupTrack* core::Link<proto::fightitems::motion::ShoulderConFixupTrack>::Get() const;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100DA760
// FUNCTION: ENGINE 0x100DA790
// FUNCTION: ENGINE 0x100DA7A0
// FUNCTION: ENGINE 0x100DA7D0
// FUNCTION: ENGINE 0x100DA7E0
// FUNCTION: ENGINE 0x100DA810
// FUNCTION: ENGINE 0x100DA840
// FUNCTION: ENGINE 0x100DA870
// FUNCTION: ENGINE 0x100DA8A0
// FUNCTION: ENGINE 0x100DA8D0
// FUNCTION: ENGINE 0x100DA8F0
// FUNCTION: ENGINE 0x100DA910
// FUNCTION: ENGINE 0x100DA920
// FUNCTION: ENGINE 0x100DA970
// FUNCTION: ENGINE 0x100DA980
// FUNCTION: ENGINE 0x100DABD0
// FUNCTION: ENGINE 0x100DADA0
// FUNCTION: ENGINE 0x10180270
// FUNCTION: ENGINE 0x101802A0
// FUNCTION: ENGINE 0x101802D0
// FUNCTION: ENGINE 0x101802E0
// FUNCTION: ENGINE 0x10180310
// FUNCTION: ENGINE 0x10180320
// FUNCTION: ENGINE 0x10180350
// FUNCTION: ENGINE 0x10180380
// FUNCTION: ENGINE 0x101803B0
// FUNCTION: ENGINE 0x101803C0
// FUNCTION: ENGINE 0x101803F0
// FUNCTION: ENGINE 0x10180410
// FUNCTION: ENGINE 0x10180420
// FUNCTION: ENGINE 0x10180450
// FUNCTION: ENGINE 0x10180480
// FUNCTION: ENGINE 0x10180490
// FUNCTION: ENGINE 0x101804C0
// FUNCTION: ENGINE 0x101804E0
// FUNCTION: ENGINE 0x101807D0
// FUNCTION: ENGINE 0x10180800
// FUNCTION: ENGINE 0x10180820
// FUNCTION: ENGINE 0x10180850
// FUNCTION: ENGINE 0x10180870
// FUNCTION: ENGINE 0x101808C0
