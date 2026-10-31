// Fight items of the motion group: PadRumbleSetTrack, PadRumbleRefTrack, PadRumbleClearTrack (unit 0x101998F0 - 0x1019A8A0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_padrumble.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gPadRumbleSetTrackProperties;  // 0x112548C8

			// FUNCTION: ENGINE 0x101998F0
			bool PadRumbleSetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199910
			bool PadRumbleSetTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199930
			bool PadRumbleSetTrack::SetMotor(int newValue)
			{
				motor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199940
			bool PadRumbleSetTrack::SetScale(float newValue)
			{
				scale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199960
			bool PadRumbleSetTrack::SetFadeInTime(float newValue)
			{
				fadeInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199980
			bool PadRumbleSetTrack::SetHoldTime(float newValue)
			{
				holdTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101999A0
			bool PadRumbleSetTrack::SetFadeOutTime(float newValue)
			{
				fadeOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101999C0
			bool PadRumbleSetTrack::SetUseObjectPos(bool newValue)
			{
				useObjectPos = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101999D0
			bool PadRumbleSetTrack::SetFullIntensityRadius(float newValue)
			{
				fullIntensityRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101999F0
			bool PadRumbleSetTrack::SetFallOffRadius(float newValue)
			{
				fallOffRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199A10
			bool PadRumbleSetTrack::SetCancelOnTrackEnd(bool newValue)
			{
				cancelOnTrackEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199A90
			fight::Property* PadRumbleSetTrack::GetProperty(int index)
			{
				return gPadRumbleSetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10199AB0
			void PadRumbleSetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPadRumbleSetTrackProperties);
			}

			// FUNCTION: ENGINE 0x10199AC0
			PadRumbleSetTrack::PadRumbleSetTrack() : fadeInTime(0.0f), fadeOutTime(0.0f), fallOffRadius(5e+01f), fullIntensityRadius(5.0f), holdTime(0.2f), scale(0.0f), timeBegin(0.0f), timeEnd(-1.0f), motor(0), cancelOnTrackEnd(false), useObjectPos(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10199B50
			float PadRumbleSetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10199B60
			float PadRumbleSetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10199B70
			PadRumbleSetTrack::~PadRumbleSetTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019A160
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PadRumbleSetTrack::RegisterProperties()
			{
				if (gPadRumbleSetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PadRumbleSetTrack>("timeBegin", &PadRumbleSetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PadRumbleSetTrack>("timeEnd", &PadRumbleSetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<PadRumbleSetTrack>("motor", gPadRumbleSetTrackMotorTable, gPadRumbleSetTrackMotorCount, &PadRumbleSetTrack::SetMotor);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<PadRumbleSetTrack>("scale", &PadRumbleSetTrack::SetScale);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<PadRumbleSetTrack>("fadeInTime", &PadRumbleSetTrack::SetFadeInTime);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<PadRumbleSetTrack>("holdTime", &PadRumbleSetTrack::SetHoldTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<PadRumbleSetTrack>("fadeOutTime", &PadRumbleSetTrack::SetFadeOutTime);
					properties[6] = property;
					property = new fight::PropertyBool<PadRumbleSetTrack>("useObjectPos", &PadRumbleSetTrack::SetUseObjectPos);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<PadRumbleSetTrack>("fullIntensityRadius", &PadRumbleSetTrack::SetFullIntensityRadius);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<PadRumbleSetTrack>("fallOffRadius", &PadRumbleSetTrack::SetFallOffRadius);
					properties[9] = property;
					property = new fight::PropertyBool<PadRumbleSetTrack>("cancelOnTrackEnd", &PadRumbleSetTrack::SetCancelOnTrackEnd);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gPadRumbleSetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019A0D0
			fight::TrackFactory* CreatePadRumbleSetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PadRumbleSetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019A630
			void RegisterPadRumbleSetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PadRumbleSetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPadRumbleRefTrackProperties;  // 0x112548CC

			// FUNCTION: ENGINE 0x10199A20
			bool PadRumbleRefTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199A40
			bool PadRumbleRefTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199A60
			fight::BranchHolder* PadRumbleRefTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x10199B80
			fight::Property* PadRumbleRefTrack::GetProperty(int index)
			{
				return gPadRumbleRefTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10199BA0
			void PadRumbleRefTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPadRumbleRefTrackProperties);
			}

			// FUNCTION: ENGINE 0x10199BB0
			PadRumbleRefTrack::PadRumbleRefTrack() : branch("Motion"), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10199C00
			float PadRumbleRefTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10199C10
			float PadRumbleRefTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10199C20
			PadRumbleRefTrack::~PadRumbleRefTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019A480
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PadRumbleRefTrack::RegisterProperties()
			{
				if (gPadRumbleRefTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PadRumbleRefTrack>("timeBegin", &PadRumbleRefTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PadRumbleRefTrack>("timeEnd", &PadRumbleRefTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBranch<PadRumbleRefTrack>("branch", &PadRumbleRefTrack::SetBranch);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gPadRumbleRefTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019A100
			fight::TrackFactory* CreatePadRumbleRefTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PadRumbleRefTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019A660
			void RegisterPadRumbleRefTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PadRumbleRefTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPadRumbleClearTrackProperties;  // 0x112548D0

			// FUNCTION: ENGINE 0x10199A70
			bool PadRumbleClearTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10199C40
			fight::Property* PadRumbleClearTrack::GetProperty(int index)
			{
				return gPadRumbleClearTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10199C60
			void PadRumbleClearTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPadRumbleClearTrackProperties);
			}

			// FUNCTION: ENGINE 0x10199C70
			PadRumbleClearTrack::PadRumbleClearTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10199CA0
			float PadRumbleClearTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10199CB0
			float PadRumbleClearTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10199CC0
			PadRumbleClearTrack::~PadRumbleClearTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019A590
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PadRumbleClearTrack::RegisterProperties()
			{
				if (gPadRumbleClearTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PadRumbleClearTrack>("timeBegin", &PadRumbleClearTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPadRumbleClearTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019A130
			fight::TrackFactory* CreatePadRumbleClearTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PadRumbleClearTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019A690
			void RegisterPadRumbleClearTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PadRumbleClearTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101008D0
			PadRumbleRefAction::PadRumbleRefAction(fight::Track* listener, PadRumbleRefTrack* newTrack, int newEffect, core::IRefCount* newOwner) : fight::Action(0x760), link(newTrack), effect(newEffect), owner(0)
			{
				engine::AssignRefCounted(&owner, newOwner);
			}

			// FUNCTION: ENGINE 0x10100440
			PadRumbleRefAction::~PadRumbleRefAction()
			{
				core::SafeReleaseRef(owner);
				sequencer.End();
			}

			// FUNCTION: ENGINE 0x10100150
			fight::Sequencer* PadRumbleRefAction::GetChild()
			{
				return &sequencer;
			}

			// FUNCTION: ENGINE 0x101009A0
			bool PadRumbleRefAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				fight::Branch* branch = link.object->branch.GetBranch();
				if (branch == 0)
				{
					return false;
				}
				sequencer.SetPending(branch, effect, owner, 0);
				return sequencer.Unknown105A45A0(true);
			}

			// FUNCTION: ENGINE 0x10100160
			void PadRumbleRefAction::Slot6()
			{
				sequencer.Reset();
			}

			// FUNCTION: ENGINE 0x10100B40
			fight::Action* PadRumbleRefTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new PadRumbleRefAction(listener, this, (int)effect, owner);
			}

			// FUNCTION: ENGINE 0x101005B0
			PadRumbleClearAction::PadRumbleClearAction(PadRumbleClearTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101003A0
			PadRumbleClearAction::~PadRumbleClearAction()
			{
			}

			// FUNCTION: ENGINE 0x101009F0
			fight::Action* PadRumbleClearTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new PadRumbleClearAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<PadRumbleSetTrack>;
			template class fight::PropertyEnumConstList<PadRumbleSetTrack>;
			template class fight::PropertyBool<PadRumbleSetTrack>;
			template class fight::TrackFactoryTemplate<PadRumbleSetTrack>;
			template class fight::TrackFactoryCasterTemplate<PadRumbleSetTrack>;
			template class fight::PropertyFloatConstRange<PadRumbleRefTrack>;
			template class fight::PropertyBranch<PadRumbleRefTrack>;
			template class fight::TrackFactoryTemplate<PadRumbleRefTrack>;
			template class fight::TrackFactoryCasterTemplate<PadRumbleRefTrack>;
			template class fight::PropertyFloatConstRange<PadRumbleClearTrack>;
			template class fight::TrackFactoryTemplate<PadRumbleClearTrack>;
			template class fight::TrackFactoryCasterTemplate<PadRumbleClearTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10100210
// FUNCTION: ENGINE 0x10100230
// FUNCTION: ENGINE 0x10100270
// FUNCTION: ENGINE 0x101002D0
// FUNCTION: ENGINE 0x10100630
// FUNCTION: ENGINE 0x10100970
// FUNCTION: ENGINE 0x10199CD0
// FUNCTION: ENGINE 0x10199D00
// FUNCTION: ENGINE 0x10199D30
// FUNCTION: ENGINE 0x10199D60
// FUNCTION: ENGINE 0x10199D70
// FUNCTION: ENGINE 0x10199DA0
// FUNCTION: ENGINE 0x10199DB0
// FUNCTION: ENGINE 0x10199DE0
// FUNCTION: ENGINE 0x10199DF0
// FUNCTION: ENGINE 0x10199E20
// FUNCTION: ENGINE 0x10199E50
// FUNCTION: ENGINE 0x10199E80
// FUNCTION: ENGINE 0x10199E90
// FUNCTION: ENGINE 0x10199ED0
// FUNCTION: ENGINE 0x10199EE0
// FUNCTION: ENGINE 0x10199F10
// FUNCTION: ENGINE 0x10199F30
// FUNCTION: ENGINE 0x10199F40
// FUNCTION: ENGINE 0x10199F70
// FUNCTION: ENGINE 0x10199F90
// FUNCTION: ENGINE 0x10199FA0
// FUNCTION: ENGINE 0x10199FD0
// FUNCTION: ENGINE 0x1019A000
// FUNCTION: ENGINE 0x1019A010
// FUNCTION: ENGINE 0x1019A040
// FUNCTION: ENGINE 0x1019A060
// FUNCTION: ENGINE 0x1019A090
// FUNCTION: ENGINE 0x1019A0C0
// FUNCTION: ENGINE 0x1019A6C0
// FUNCTION: ENGINE 0x1019A6F0
// FUNCTION: ENGINE 0x1019A710
// FUNCTION: ENGINE 0x1019A740
// FUNCTION: ENGINE 0x1019A760
// FUNCTION: ENGINE 0x1019A790
// FUNCTION: ENGINE 0x1019A7B0
// FUNCTION: ENGINE 0x1019A800
// FUNCTION: ENGINE 0x1019A850
