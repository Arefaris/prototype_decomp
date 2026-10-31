// Fight items of the motion group: GrappleLocoSprintTrack, GrappleLocoSteerTrack (unit 0x10173B80 - 0x10174CA0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_grapple.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gGrappleLocoSprintTrackProperties;  // 0x1125468C

			// FUNCTION: ENGINE 0x10173B80
			bool GrappleLocoSprintTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173BA0
			bool GrappleLocoSprintTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173DC0
			bool GrappleLocoSprintTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173DE0
			bool GrappleLocoSprintTrack::SetAnimRun(const fight::Name& newValue)
			{
				animRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173E00
			bool GrappleLocoSprintTrack::SetAnimLeanEast(const fight::Name& newValue)
			{
				animLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173E20
			bool GrappleLocoSprintTrack::SetAnimLeanWest(const fight::Name& newValue)
			{
				animLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173BC0
			bool GrappleLocoSprintTrack::SetSyncFrameRun(float newValue)
			{
				syncFrameRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173BE0
			bool GrappleLocoSprintTrack::SetSyncFrameLeanEast(float newValue)
			{
				syncFrameLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173C00
			bool GrappleLocoSprintTrack::SetSyncFrameLeanWest(float newValue)
			{
				syncFrameLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173E40
			bool GrappleLocoSprintTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173C20
			bool GrappleLocoSprintTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173C30
			bool GrappleLocoSprintTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173C50
			bool GrappleLocoSprintTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173D60
			fight::Property* GrappleLocoSprintTrack::GetProperty(int index)
			{
				return gGrappleLocoSprintTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10173D80
			void GrappleLocoSprintTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrappleLocoSprintTrackProperties);
			}

			// FUNCTION: ENGINE 0x10173F00
			GrappleLocoSprintTrack::GrappleLocoSprintTrack() : blendInTime(0.0f), blendOutTime(0.0f), syncFrameLeanEast(-1.0f), syncFrameLeanWest(-1.0f), syncFrameRun(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x10173F90
			float GrappleLocoSprintTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10173FA0
			float GrappleLocoSprintTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10173FB0
			GrappleLocoSprintTrack::~GrappleLocoSprintTrack()
			{
			}

			// FUNCTION: ENGINE 0x10174460
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrappleLocoSprintTrack::RegisterProperties()
			{
				if (gGrappleLocoSprintTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrappleLocoSprintTrack>("timeBegin", &GrappleLocoSprintTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSprintTrack>("timeEnd", &GrappleLocoSprintTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<GrappleLocoSprintTrack>("locomotion", &GrappleLocoSprintTrack::SetLocomotion);
					properties[2] = property;
					property = new fight::PropertyName<GrappleLocoSprintTrack>("animRun", &GrappleLocoSprintTrack::SetAnimRun);
					properties[3] = property;
					property = new fight::PropertyName<GrappleLocoSprintTrack>("animLeanEast", &GrappleLocoSprintTrack::SetAnimLeanEast);
					properties[4] = property;
					property = new fight::PropertyName<GrappleLocoSprintTrack>("animLeanWest", &GrappleLocoSprintTrack::SetAnimLeanWest);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSprintTrack>("syncFrameRun", &GrappleLocoSprintTrack::SetSyncFrameRun);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSprintTrack>("syncFrameLeanEast", &GrappleLocoSprintTrack::SetSyncFrameLeanEast);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSprintTrack>("syncFrameLeanWest", &GrappleLocoSprintTrack::SetSyncFrameLeanWest);
					properties[8] = property;
					property = new fight::PropertyName<GrappleLocoSprintTrack>("partition", &GrappleLocoSprintTrack::SetPartition);
					properties[9] = property;
					property = new fight::PropertyIntConstRange<GrappleLocoSprintTrack>("priority", &GrappleLocoSprintTrack::SetPriority);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSprintTrack>("blendInTime", &GrappleLocoSprintTrack::SetBlendInTime);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSprintTrack>("blendOutTime", &GrappleLocoSprintTrack::SetBlendOutTime);
					properties[12] = property;
					fight::RegisterPropertyList(properties, &gGrappleLocoSprintTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10174300
			fight::TrackFactory* CreateGrappleLocoSprintTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrappleLocoSprintTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10174360
			void RegisterGrappleLocoSprintTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrappleLocoSprintTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGrappleLocoSteerTrackProperties;  // 0x11254690

			// FUNCTION: ENGINE 0x10173C70
			bool GrappleLocoSteerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173C90
			bool GrappleLocoSteerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173E60
			bool GrappleLocoSteerTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173E80
			bool GrappleLocoSteerTrack::SetAnimIdle(const fight::Name& newValue)
			{
				animIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173EA0
			bool GrappleLocoSteerTrack::SetAnimWalk(const fight::Name& newValue)
			{
				animWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173EC0
			bool GrappleLocoSteerTrack::SetAnimRun(const fight::Name& newValue)
			{
				animRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173CB0
			bool GrappleLocoSteerTrack::SetSyncFrameIdle(float newValue)
			{
				syncFrameIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173CD0
			bool GrappleLocoSteerTrack::SetSyncFrameWalk(float newValue)
			{
				syncFrameWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173CF0
			bool GrappleLocoSteerTrack::SetSyncFrameRun(float newValue)
			{
				syncFrameRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173EE0
			bool GrappleLocoSteerTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173D10
			bool GrappleLocoSteerTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173D20
			bool GrappleLocoSteerTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173D40
			bool GrappleLocoSteerTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10173D90
			fight::Property* GrappleLocoSteerTrack::GetProperty(int index)
			{
				return gGrappleLocoSteerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10173DB0
			void GrappleLocoSteerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGrappleLocoSteerTrackProperties);
			}

			// FUNCTION: ENGINE 0x10173FC0
			GrappleLocoSteerTrack::GrappleLocoSteerTrack() : blendInTime(0.0f), blendOutTime(0.0f), syncFrameIdle(-1.0f), syncFrameRun(-1.0f), syncFrameWalk(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x10174050
			float GrappleLocoSteerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10174060
			float GrappleLocoSteerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10174070
			GrappleLocoSteerTrack::~GrappleLocoSteerTrack()
			{
			}

			// FUNCTION: ENGINE 0x101747E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrappleLocoSteerTrack::RegisterProperties()
			{
				if (gGrappleLocoSteerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GrappleLocoSteerTrack>("timeBegin", &GrappleLocoSteerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSteerTrack>("timeEnd", &GrappleLocoSteerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<GrappleLocoSteerTrack>("locomotion", &GrappleLocoSteerTrack::SetLocomotion);
					properties[2] = property;
					property = new fight::PropertyName<GrappleLocoSteerTrack>("animIdle", &GrappleLocoSteerTrack::SetAnimIdle);
					properties[3] = property;
					property = new fight::PropertyName<GrappleLocoSteerTrack>("animWalk", &GrappleLocoSteerTrack::SetAnimWalk);
					properties[4] = property;
					property = new fight::PropertyName<GrappleLocoSteerTrack>("animRun", &GrappleLocoSteerTrack::SetAnimRun);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSteerTrack>("syncFrameIdle", &GrappleLocoSteerTrack::SetSyncFrameIdle);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSteerTrack>("syncFrameWalk", &GrappleLocoSteerTrack::SetSyncFrameWalk);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSteerTrack>("syncFrameRun", &GrappleLocoSteerTrack::SetSyncFrameRun);
					properties[8] = property;
					property = new fight::PropertyName<GrappleLocoSteerTrack>("partition", &GrappleLocoSteerTrack::SetPartition);
					properties[9] = property;
					property = new fight::PropertyIntConstRange<GrappleLocoSteerTrack>("priority", &GrappleLocoSteerTrack::SetPriority);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSteerTrack>("blendInTime", &GrappleLocoSteerTrack::SetBlendInTime);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<GrappleLocoSteerTrack>("blendOutTime", &GrappleLocoSteerTrack::SetBlendOutTime);
					properties[12] = property;
					fight::RegisterPropertyList(properties, &gGrappleLocoSteerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10174330
			fight::TrackFactory* CreateGrappleLocoSteerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrappleLocoSteerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10174390
			void RegisterGrappleLocoSteerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GrappleLocoSteerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<GrappleLocoSprintTrack>;
			template class fight::PropertyName<GrappleLocoSprintTrack>;
			template class fight::PropertyIntConstRange<GrappleLocoSprintTrack>;
			template class fight::TrackFactoryTemplate<GrappleLocoSprintTrack>;
			template class fight::TrackFactoryCasterTemplate<GrappleLocoSprintTrack>;
			template class fight::PropertyFloatConstRange<GrappleLocoSteerTrack>;
			template class fight::PropertyName<GrappleLocoSteerTrack>;
			template class fight::PropertyIntConstRange<GrappleLocoSteerTrack>;
			template class fight::TrackFactoryTemplate<GrappleLocoSteerTrack>;
			template class fight::TrackFactoryCasterTemplate<GrappleLocoSteerTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10174080
// FUNCTION: ENGINE 0x10174090
// FUNCTION: ENGINE 0x101740C0
// FUNCTION: ENGINE 0x101740D0
// FUNCTION: ENGINE 0x10174100
// FUNCTION: ENGINE 0x10174130
// FUNCTION: ENGINE 0x10174160
// FUNCTION: ENGINE 0x10174190
// FUNCTION: ENGINE 0x101741C0
// FUNCTION: ENGINE 0x101741D0
// FUNCTION: ENGINE 0x10174200
// FUNCTION: ENGINE 0x10174220
// FUNCTION: ENGINE 0x10174230
// FUNCTION: ENGINE 0x10174260
// FUNCTION: ENGINE 0x10174290
// FUNCTION: ENGINE 0x101742A0
// FUNCTION: ENGINE 0x101742D0
// FUNCTION: ENGINE 0x101742F0
// FUNCTION: ENGINE 0x101743C0
// FUNCTION: ENGINE 0x101743F0
// FUNCTION: ENGINE 0x10174410
// FUNCTION: ENGINE 0x10174440
// FUNCTION: ENGINE 0x10174B60
// FUNCTION: ENGINE 0x10174B90
// FUNCTION: ENGINE 0x10174BB0
// FUNCTION: ENGINE 0x10174BE0
// FUNCTION: ENGINE 0x10174C00
// FUNCTION: ENGINE 0x10174C50
