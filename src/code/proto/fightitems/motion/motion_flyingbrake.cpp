// Fight items of the motion group: FlyingBrakeTrack (unit 0x1015FAE0 - 0x101601F0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_flyingbrake.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFlyingBrakeTrackProperties;  // 0x11254534

			// FUNCTION: ENGINE 0x1015FAE0
			bool FlyingBrakeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FB00
			bool FlyingBrakeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FB20
			bool FlyingBrakeTrack::SetVelocityXZ(float newValue)
			{
				velocityXZ = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FB40
			bool FlyingBrakeTrack::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FB60
			bool FlyingBrakeTrack::SetGravityUp(float newValue)
			{
				gravityUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FB80
			bool FlyingBrakeTrack::SetTerminalVelocity(float newValue)
			{
				terminalVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FBA0
			bool FlyingBrakeTrack::SetVelocityUp(float newValue)
			{
				velocityUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FBC0
			bool FlyingBrakeTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FBD0
			bool FlyingBrakeTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FBF0
			bool FlyingBrakeTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015FC10
			fight::Property* FlyingBrakeTrack::GetProperty(int index)
			{
				return gFlyingBrakeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015FC30
			void FlyingBrakeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFlyingBrakeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015FC40
			FlyingBrakeTrack::FlyingBrakeTrack() : blendInTime(0.0f), blendOutTime(0.0f), gravity(1e+01f), gravityUp(5e+01f), terminalVelocity(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), velocityUp(-1.0f), velocityXZ(5e+01f), priority(-5)
			{
			}

			// FUNCTION: ENGINE 0x1015FCC0
			float FlyingBrakeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1015FCD0
			float FlyingBrakeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1015FCE0
			FlyingBrakeTrack::~FlyingBrakeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015FE60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FlyingBrakeTrack::RegisterProperties()
			{
				if (gFlyingBrakeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FlyingBrakeTrack>("timeBegin", &FlyingBrakeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FlyingBrakeTrack>("timeEnd", &FlyingBrakeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FlyingBrakeTrack>("velocityXZ", &FlyingBrakeTrack::SetVelocityXZ);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FlyingBrakeTrack>("gravity", &FlyingBrakeTrack::SetGravity);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FlyingBrakeTrack>("gravityUp", &FlyingBrakeTrack::SetGravityUp);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FlyingBrakeTrack>("terminalVelocity", &FlyingBrakeTrack::SetTerminalVelocity);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FlyingBrakeTrack>("velocityUp", &FlyingBrakeTrack::SetVelocityUp);
					properties[6] = property;
					property = new fight::PropertyIntConstRange<FlyingBrakeTrack>("priority", &FlyingBrakeTrack::SetPriority);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<FlyingBrakeTrack>("blendInTime", &FlyingBrakeTrack::SetBlendInTime);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<FlyingBrakeTrack>("blendOutTime", &FlyingBrakeTrack::SetBlendOutTime);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gFlyingBrakeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015FE30
			fight::TrackFactory* CreateFlyingBrakeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingBrakeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10160120
			void RegisterFlyingBrakeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingBrakeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100BE320
			FlyingBrakeAction::FlyingBrakeAction(FlyingBrakeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), driver(0), unknown30(0.0f, 0.0f, 0.0f), unknown3C(0.0f, 0.0f, 0.0f), unknown48(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x100BE200
			FlyingBrakeAction::~FlyingBrakeAction()
			{
				engine::ReleaseDriverCopy2((choreo::Driver**)&driver);
			}

			// FUNCTION: ENGINE 0x100BE8E0
			fight::Action* FlyingBrakeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FlyingBrakeAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<FlyingBrakeTrack>;
			template class fight::PropertyIntConstRange<FlyingBrakeTrack>;
			template class fight::TrackFactoryTemplate<FlyingBrakeTrack>;
			template class fight::TrackFactoryCasterTemplate<FlyingBrakeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100BE160
// FUNCTION: ENGINE 0x100BE190
// FUNCTION: ENGINE 0x100BE3C0
