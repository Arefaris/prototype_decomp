// Fight items of the motion group: JointAnchorToAnimationTrack (unit 0x10182180 - 0x101827B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_jointanchortoanimation.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gJointAnchorToAnimationTrackProperties;  // 0x11254784

			// FUNCTION: ENGINE 0x10182180
			bool JointAnchorToAnimationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101821A0
			bool JointAnchorToAnimationTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10182220
			bool JointAnchorToAnimationTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10182240
			bool JointAnchorToAnimationTrack::SetAnimation(const fight::Name& newValue)
			{
				animation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101821C0
			bool JointAnchorToAnimationTrack::SetFrame(float newValue)
			{
				frame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101821E0
			bool JointAnchorToAnimationTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101821F0
			fight::Property* JointAnchorToAnimationTrack::GetProperty(int index)
			{
				return gJointAnchorToAnimationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10182210
			void JointAnchorToAnimationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gJointAnchorToAnimationTrackProperties);
			}

			// FUNCTION: ENGINE 0x10182260
			JointAnchorToAnimationTrack::JointAnchorToAnimationTrack() : joint("Character_Root", 1), frame(0.0f), timeBegin(0.0f), timeEnd(0.0f), priority(-10)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101822C0
			float JointAnchorToAnimationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101822D0
			float JointAnchorToAnimationTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101822E0
			JointAnchorToAnimationTrack::~JointAnchorToAnimationTrack()
			{
			}

			// FUNCTION: ENGINE 0x10182540
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JointAnchorToAnimationTrack::RegisterProperties()
			{
				if (gJointAnchorToAnimationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<JointAnchorToAnimationTrack>("timeBegin", &JointAnchorToAnimationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<JointAnchorToAnimationTrack>("timeEnd", &JointAnchorToAnimationTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<JointAnchorToAnimationTrack>("joint", &JointAnchorToAnimationTrack::SetJoint);
					properties[2] = property;
					property = new fight::PropertyName<JointAnchorToAnimationTrack>("animation", &JointAnchorToAnimationTrack::SetAnimation);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<JointAnchorToAnimationTrack>("frame", &JointAnchorToAnimationTrack::SetFrame);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<JointAnchorToAnimationTrack>("priority", &JointAnchorToAnimationTrack::SetPriority);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gJointAnchorToAnimationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10182430
			fight::TrackFactory* CreateJointAnchorToAnimationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<JointAnchorToAnimationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10182460
			void RegisterJointAnchorToAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<JointAnchorToAnimationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100DC8C0
			JointAnchorToAnimationAction::JointAnchorToAnimationAction(JointAnchorToAnimationTrack* newTrack, core::IRefCount* owner) : fight::Action(0xE00), link(newTrack), driver(0), secondDriver(0)
			{
				target = engine::GetObjectHandle(owner);
				matrix.Identity();
			}

			// FUNCTION: ENGINE 0x100DC700
			JointAnchorToAnimationAction::~JointAnchorToAnimationAction()
			{
				engine::ReleaseDriverCopy2(&driver);
				ReleaseDriverJoint(secondDriver);
			}

			// FUNCTION: ENGINE 0x100DD100
			fight::Action* JointAnchorToAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new JointAnchorToAnimationAction(this, owner);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<JointAnchorToAnimationTrack>;
			template class fight::PropertyNameList<JointAnchorToAnimationTrack>;
			template class fight::PropertyName<JointAnchorToAnimationTrack>;
			template class fight::PropertyIntConstRange<JointAnchorToAnimationTrack>;
			template class fight::TrackFactoryTemplate<JointAnchorToAnimationTrack>;
			template class fight::TrackFactoryCasterTemplate<JointAnchorToAnimationTrack>;
		}
	}
}

// Explicit instances of the track links' accessors (the engine keeps their copies):
template proto::fightitems::motion::JointAnchorToAnimationTrack* core::Link<proto::fightitems::motion::JointAnchorToAnimationTrack>::Get() const;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100DC620
// FUNCTION: ENGINE 0x100DC640
// FUNCTION: ENGINE 0x100DC650
// FUNCTION: ENGINE 0x100DC960
// FUNCTION: ENGINE 0x101822F0
// FUNCTION: ENGINE 0x10182300
// FUNCTION: ENGINE 0x10182330
// FUNCTION: ENGINE 0x10182360
// FUNCTION: ENGINE 0x10182390
// FUNCTION: ENGINE 0x101823C0
// FUNCTION: ENGINE 0x101823D0
// FUNCTION: ENGINE 0x10182400
// FUNCTION: ENGINE 0x10182420
// FUNCTION: ENGINE 0x10182490
// FUNCTION: ENGINE 0x101824C0
// FUNCTION: ENGINE 0x101824E0
// FUNCTION: ENGINE 0x101824F0
// FUNCTION: ENGINE 0x10182520
// FUNCTION: ENGINE 0x10182710
// FUNCTION: ENGINE 0x10182740
// FUNCTION: ENGINE 0x10182760
