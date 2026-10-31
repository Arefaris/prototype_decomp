// Fight items of the motion group: AutoTargetTrack, AutoTargetClearTrack, AutoTargetPositionTrack, FlyingAutoTargetTrack, PedestrianAutoTargetTrack, AutoTargetPlayerTrack (unit 0x10140FC0 - 0x10143E60; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_autotarget.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gAutoTargetTrackProperties;  // 0x112542A8

			// FUNCTION: ENGINE 0x10140FD0
			bool AutoTargetTrack::SetTimeBegin(float value)
			{
				timeBegin = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10140FF0
			bool AutoTargetTrack::SetTimeEnd(float value)
			{
				timeEnd = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141010
			bool AutoTargetTrack::SetTurningVelocity(float value)
			{
				turningVelocity = value * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10141030
			bool AutoTargetTrack::SetUseInput(bool value)
			{
				useInput = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141040
			bool AutoTargetTrack::SetUseCamera(bool value)
			{
				useCamera = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141050
			bool AutoTargetTrack::SetDirection(const math::Vector& value)
			{
				direction.x = value.x;
				direction.y = value.y;
				direction.z = value.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10141070
			bool AutoTargetTrack::SetArc(float value)
			{
				arc = value * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10141090
			bool AutoTargetTrack::SetMaxDistance(float value)
			{
				maxDistance = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101410B0
			bool AutoTargetTrack::SetCheckArc(bool value)
			{
				checkArc = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101410C0
			bool AutoTargetTrack::SetCheckDistance(bool value)
			{
				checkDistance = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101410D0
			bool AutoTargetTrack::SetOrientOffsetFromTarget(float value)
			{
				orientOffsetFromTarget = value * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101410F0
			bool AutoTargetTrack::SetTargetFilter(int value)
			{
				targetFilter = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141100
			bool AutoTargetTrack::SetTargetOverrides(int value)
			{
				targetOverrides = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141110
			bool AutoTargetTrack::SetMinPriorityTargetClass(int value)
			{
				minPriorityTargetClass = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141120
			bool AutoTargetTrack::SetMaxPriorityTargetClass(int value)
			{
				maxPriorityTargetClass = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141130
			bool AutoTargetTrack::SetPriority(int value)
			{
				priority = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141140
			bool AutoTargetTrack::SetBlendInTime(float value)
			{
				blendInTime = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141160
			bool AutoTargetTrack::SetBlendOutTime(float value)
			{
				blendOutTime = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101415D0
			fight::Property* AutoTargetTrack::GetProperty(int index)
			{
				return gAutoTargetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101415F0
			void AutoTargetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAutoTargetTrackProperties);
			}

			// FUNCTION: ENGINE 0x10141600
			AutoTargetTrack::AutoTargetTrack() : direction(0.0f, 0.0f, -1.0f), arc(3.1415927f), blendInTime(0.0f), blendOutTime(0.0f), maxDistance(5.0f), orientOffsetFromTarget(0.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(0.0f), maxPriorityTargetClass(48), minPriorityTargetClass(47), priority(-5), targetFilter(gAutoTargetTrackTargetFilterDefault), targetOverrides(0), checkArc(false), checkDistance(true), useCamera(false), useInput(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101416C0
			float AutoTargetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101416D0
			float AutoTargetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101416E0
			AutoTargetTrack::~AutoTargetTrack()
			{
			}

			// FUNCTION: ENGINE 0x10142890
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AutoTargetTrack::RegisterProperties()
			{
				if (gAutoTargetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AutoTargetTrack>("timeBegin", &AutoTargetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetTrack>("timeEnd", &AutoTargetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetTrack>("turningVelocity", &AutoTargetTrack::SetTurningVelocity);
					properties[2] = property;
					property = new fight::PropertyBool<AutoTargetTrack>("useInput", &AutoTargetTrack::SetUseInput);
					properties[3] = property;
					property = new fight::PropertyBool<AutoTargetTrack>("useCamera", &AutoTargetTrack::SetUseCamera);
					properties[4] = property;
					property = new fight::PropertyVector<AutoTargetTrack>("direction", &AutoTargetTrack::SetDirection);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetTrack>("arc", &AutoTargetTrack::SetArc);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetTrack>("maxDistance", &AutoTargetTrack::SetMaxDistance);
					properties[7] = property;
					property = new fight::PropertyBool<AutoTargetTrack>("checkArc", &AutoTargetTrack::SetCheckArc);
					properties[8] = property;
					property = new fight::PropertyBool<AutoTargetTrack>("checkDistance", &AutoTargetTrack::SetCheckDistance);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetTrack>("orientOffsetFromTarget", &AutoTargetTrack::SetOrientOffsetFromTarget);
					properties[10] = property;
					property = new fight::PropertyBitfieldConstList<AutoTargetTrack>("targetFilter", gAutoTargetTrackTargetFilterTable, gAutoTargetTrackTargetFilterCount, &AutoTargetTrack::SetTargetFilter);
					properties[11] = property;
					property = new fight::PropertyBitfieldConstList<AutoTargetTrack>("targetOverrides", gAutoTargetTrackTargetOverridesTable, gAutoTargetTrackTargetOverridesCount, &AutoTargetTrack::SetTargetOverrides);
					properties[12] = property;
					property = new fight::PropertyEnumConstList<AutoTargetTrack>("minPriorityTargetClass", gAutoTargetTrackMinPriorityTargetClassTable, gAutoTargetTrackMinPriorityTargetClassCount, &AutoTargetTrack::SetMinPriorityTargetClass);
					properties[13] = property;
					property = new fight::PropertyEnumConstList<AutoTargetTrack>("maxPriorityTargetClass", gAutoTargetTrackMinPriorityTargetClassTable, gAutoTargetTrackMinPriorityTargetClassCount, &AutoTargetTrack::SetMaxPriorityTargetClass);
					properties[14] = property;
					property = new fight::PropertyIntConstRange<AutoTargetTrack>("priority", &AutoTargetTrack::SetPriority);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetTrack>("blendInTime", &AutoTargetTrack::SetBlendInTime);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetTrack>("blendOutTime", &AutoTargetTrack::SetBlendOutTime);
					properties[17] = property;
					fight::RegisterPropertyList(properties, &gAutoTargetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10142770
			fight::TrackFactory* CreateAutoTargetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AutoTargetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10143980
			void RegisterAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AutoTargetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAutoTargetClearTrackProperties;  // 0x112542AC

			// FUNCTION: ENGINE 0x10141180
			bool AutoTargetClearTrack::SetTimeBegin(float value)
			{
				timeBegin = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101416F0
			fight::Property* AutoTargetClearTrack::GetProperty(int index)
			{
				return gAutoTargetClearTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10141710
			void AutoTargetClearTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAutoTargetClearTrackProperties);
			}

			// FUNCTION: ENGINE 0x10141720
			AutoTargetClearTrack::AutoTargetClearTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10141750
			float AutoTargetClearTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10141760
			float AutoTargetClearTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10141770
			AutoTargetClearTrack::~AutoTargetClearTrack()
			{
			}

			// FUNCTION: ENGINE 0x10142D90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AutoTargetClearTrack::RegisterProperties()
			{
				if (gAutoTargetClearTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AutoTargetClearTrack>("timeBegin", &AutoTargetClearTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gAutoTargetClearTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101427A0
			fight::TrackFactory* CreateAutoTargetClearTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AutoTargetClearTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101439B0
			void RegisterAutoTargetClearTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AutoTargetClearTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAutoTargetPositionTrackProperties;  // 0x112542B0

			// FUNCTION: ENGINE 0x101411A0
			bool AutoTargetPositionTrack::SetTimeBegin(float value)
			{
				timeBegin = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101411C0
			bool AutoTargetPositionTrack::SetTimeEnd(float value)
			{
				timeEnd = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101411E0
			bool AutoTargetPositionTrack::SetOffset(const math::Vector& value)
			{
				offset.x = value.x;
				offset.y = value.y;
				offset.z = value.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10141200
			bool AutoTargetPositionTrack::SetVelocity(float value)
			{
				velocity = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141220
			bool AutoTargetPositionTrack::SetPriority(int value)
			{
				priority = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141230
			bool AutoTargetPositionTrack::SetBlendInTime(float value)
			{
				blendInTime = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141250
			bool AutoTargetPositionTrack::SetBlendOutTime(float value)
			{
				blendOutTime = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141780
			fight::Property* AutoTargetPositionTrack::GetProperty(int index)
			{
				return gAutoTargetPositionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101417A0
			void AutoTargetPositionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAutoTargetPositionTrackProperties);
			}

			// FUNCTION: ENGINE 0x101417B0
			AutoTargetPositionTrack::AutoTargetPositionTrack() : offset(0.0f, 0.0f, 1.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), velocity(0.0f), priority(-3)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10141830
			float AutoTargetPositionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10141840
			float AutoTargetPositionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10141850
			AutoTargetPositionTrack::~AutoTargetPositionTrack()
			{
			}

			// FUNCTION: ENGINE 0x10142E30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AutoTargetPositionTrack::RegisterProperties()
			{
				if (gAutoTargetPositionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AutoTargetPositionTrack>("timeBegin", &AutoTargetPositionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetPositionTrack>("timeEnd", &AutoTargetPositionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<AutoTargetPositionTrack>("offset", &AutoTargetPositionTrack::SetOffset);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetPositionTrack>("velocity", &AutoTargetPositionTrack::SetVelocity);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<AutoTargetPositionTrack>("priority", &AutoTargetPositionTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetPositionTrack>("blendInTime", &AutoTargetPositionTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetPositionTrack>("blendOutTime", &AutoTargetPositionTrack::SetBlendOutTime);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gAutoTargetPositionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101427D0
			fight::TrackFactory* CreateAutoTargetPositionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AutoTargetPositionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101439E0
			void RegisterAutoTargetPositionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AutoTargetPositionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gFlyingAutoTargetTrackProperties;  // 0x112542B4

			// FUNCTION: ENGINE 0x10141270
			bool FlyingAutoTargetTrack::SetTimeBegin(float value)
			{
				timeBegin = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141290
			bool FlyingAutoTargetTrack::SetTimeEnd(float value)
			{
				timeEnd = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101412B0
			bool FlyingAutoTargetTrack::SetVelocity(float value)
			{
				velocity = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101412D0
			bool FlyingAutoTargetTrack::SetTurningVelocity(float value)
			{
				turningVelocity = value * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101412F0
			bool FlyingAutoTargetTrack::SetOffset(const math::Vector& value)
			{
				offset.x = value.x;
				offset.y = value.y;
				offset.z = value.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10141310
			bool FlyingAutoTargetTrack::SetArc(float value)
			{
				arc = value * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10141330
			bool FlyingAutoTargetTrack::SetMaxDistance(float value)
			{
				maxDistance = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141350
			bool FlyingAutoTargetTrack::SetCheckArc(bool value)
			{
				checkArc = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141360
			bool FlyingAutoTargetTrack::SetCheckDistance(bool value)
			{
				checkDistance = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141370
			bool FlyingAutoTargetTrack::SetTargetFilter(int value)
			{
				targetFilter = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141380
			bool FlyingAutoTargetTrack::SetStickToTarget(bool value)
			{
				stickToTarget = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141390
			bool FlyingAutoTargetTrack::SetUseExistingAutoTarget(bool value)
			{
				useExistingAutoTarget = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101413A0
			bool FlyingAutoTargetTrack::SetUseReactionHitEvent(bool value)
			{
				useReactionHitEvent = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101413B0
			bool FlyingAutoTargetTrack::SetCharacterHeight(float value)
			{
				characterHeight = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101413D0
			bool FlyingAutoTargetTrack::SetCharacterWidth(float value)
			{
				characterWidth = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101413F0
			bool FlyingAutoTargetTrack::SetMinPriorityTargetClass(int value)
			{
				minPriorityTargetClass = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141400
			bool FlyingAutoTargetTrack::SetMaxPriorityTargetClass(int value)
			{
				maxPriorityTargetClass = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141410
			bool FlyingAutoTargetTrack::SetPriority(int value)
			{
				priority = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141420
			bool FlyingAutoTargetTrack::SetBlendInTime(float value)
			{
				blendInTime = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141440
			bool FlyingAutoTargetTrack::SetBlendOutTime(float value)
			{
				blendOutTime = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141860
			fight::Property* FlyingAutoTargetTrack::GetProperty(int index)
			{
				return gFlyingAutoTargetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10141880
			void FlyingAutoTargetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFlyingAutoTargetTrackProperties);
			}

			// FUNCTION: ENGINE 0x10141890
			FlyingAutoTargetTrack::FlyingAutoTargetTrack() : offset(0.0f, 0.0f, 0.0f), arc(3.1415927f), blendInTime(0.0f), blendOutTime(0.0f), characterHeight(0.0f), characterWidth(0.0f), maxDistance(5.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(0.0f), velocity(1e+01f), maxPriorityTargetClass(48), minPriorityTargetClass(47), priority(-5), targetFilter(gFlyingAutoTargetTrackTargetFilterDefault), checkArc(false), checkDistance(true), stickToTarget(false), useExistingAutoTarget(false), useReactionHitEvent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10141970
			float FlyingAutoTargetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10141980
			float FlyingAutoTargetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10141990
			FlyingAutoTargetTrack::~FlyingAutoTargetTrack()
			{
			}

			// FUNCTION: ENGINE 0x10143040
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FlyingAutoTargetTrack::RegisterProperties()
			{
				if (gFlyingAutoTargetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("timeBegin", &FlyingAutoTargetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("timeEnd", &FlyingAutoTargetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("velocity", &FlyingAutoTargetTrack::SetVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("turningVelocity", &FlyingAutoTargetTrack::SetTurningVelocity);
					properties[3] = property;
					property = new fight::PropertyVector<FlyingAutoTargetTrack>("offset", &FlyingAutoTargetTrack::SetOffset);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("arc", &FlyingAutoTargetTrack::SetArc);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("maxDistance", &FlyingAutoTargetTrack::SetMaxDistance);
					properties[6] = property;
					property = new fight::PropertyBool<FlyingAutoTargetTrack>("checkArc", &FlyingAutoTargetTrack::SetCheckArc);
					properties[7] = property;
					property = new fight::PropertyBool<FlyingAutoTargetTrack>("checkDistance", &FlyingAutoTargetTrack::SetCheckDistance);
					properties[8] = property;
					property = new fight::PropertyBitfieldConstList<FlyingAutoTargetTrack>("targetFilter", gAutoTargetTrackTargetFilterTable, gAutoTargetTrackTargetFilterCount, &FlyingAutoTargetTrack::SetTargetFilter);
					properties[9] = property;
					property = new fight::PropertyBool<FlyingAutoTargetTrack>("stickToTarget", &FlyingAutoTargetTrack::SetStickToTarget);
					properties[10] = property;
					property = new fight::PropertyBool<FlyingAutoTargetTrack>("useExistingAutoTarget", &FlyingAutoTargetTrack::SetUseExistingAutoTarget);
					properties[11] = property;
					property = new fight::PropertyBool<FlyingAutoTargetTrack>("useReactionHitEvent", &FlyingAutoTargetTrack::SetUseReactionHitEvent);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("characterHeight", &FlyingAutoTargetTrack::SetCharacterHeight);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("characterWidth", &FlyingAutoTargetTrack::SetCharacterWidth);
					properties[14] = property;
					property = new fight::PropertyEnumConstList<FlyingAutoTargetTrack>("minPriorityTargetClass", gAutoTargetTrackMinPriorityTargetClassTable, gAutoTargetTrackMinPriorityTargetClassCount, &FlyingAutoTargetTrack::SetMinPriorityTargetClass);
					properties[15] = property;
					property = new fight::PropertyEnumConstList<FlyingAutoTargetTrack>("maxPriorityTargetClass", gAutoTargetTrackMinPriorityTargetClassTable, gAutoTargetTrackMinPriorityTargetClassCount, &FlyingAutoTargetTrack::SetMaxPriorityTargetClass);
					properties[16] = property;
					property = new fight::PropertyIntConstRange<FlyingAutoTargetTrack>("priority", &FlyingAutoTargetTrack::SetPriority);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("blendInTime", &FlyingAutoTargetTrack::SetBlendInTime);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<FlyingAutoTargetTrack>("blendOutTime", &FlyingAutoTargetTrack::SetBlendOutTime);
					properties[19] = property;
					fight::RegisterPropertyList(properties, &gFlyingAutoTargetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10142800
			fight::TrackFactory* CreateFlyingAutoTargetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingAutoTargetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10143A10
			void RegisterFlyingAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingAutoTargetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPedestrianAutoTargetTrackProperties;  // 0x112542B8

			// FUNCTION: ENGINE 0x10141460
			bool PedestrianAutoTargetTrack::SetTimeBegin(float value)
			{
				timeBegin = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141480
			bool PedestrianAutoTargetTrack::SetTimeEnd(float value)
			{
				timeEnd = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101414A0
			bool PedestrianAutoTargetTrack::SetTurningVelocity(float value)
			{
				turningVelocity = value * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101414C0
			bool PedestrianAutoTargetTrack::SetOrientOffsetFromTarget(float value)
			{
				orientOffsetFromTarget = value * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101414E0
			bool PedestrianAutoTargetTrack::SetPriority(int value)
			{
				priority = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101414F0
			bool PedestrianAutoTargetTrack::SetBlendInTime(float value)
			{
				blendInTime = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141510
			bool PedestrianAutoTargetTrack::SetBlendOutTime(float value)
			{
				blendOutTime = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101419A0
			fight::Property* PedestrianAutoTargetTrack::GetProperty(int index)
			{
				return gPedestrianAutoTargetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101419C0
			void PedestrianAutoTargetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPedestrianAutoTargetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101419D0
			PedestrianAutoTargetTrack::PedestrianAutoTargetTrack() : blendInTime(0.0f), blendOutTime(0.0f), orientOffsetFromTarget(0.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(0.0f), priority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10141A30
			float PedestrianAutoTargetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10141A40
			float PedestrianAutoTargetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10141A50
			PedestrianAutoTargetTrack::~PedestrianAutoTargetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101435A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PedestrianAutoTargetTrack::RegisterProperties()
			{
				if (gPedestrianAutoTargetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PedestrianAutoTargetTrack>("timeBegin", &PedestrianAutoTargetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PedestrianAutoTargetTrack>("timeEnd", &PedestrianAutoTargetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<PedestrianAutoTargetTrack>("turningVelocity", &PedestrianAutoTargetTrack::SetTurningVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<PedestrianAutoTargetTrack>("orientOffsetFromTarget", &PedestrianAutoTargetTrack::SetOrientOffsetFromTarget);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<PedestrianAutoTargetTrack>("priority", &PedestrianAutoTargetTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<PedestrianAutoTargetTrack>("blendInTime", &PedestrianAutoTargetTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<PedestrianAutoTargetTrack>("blendOutTime", &PedestrianAutoTargetTrack::SetBlendOutTime);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gPedestrianAutoTargetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10142830
			fight::TrackFactory* CreatePedestrianAutoTargetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PedestrianAutoTargetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10143A40
			void RegisterPedestrianAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PedestrianAutoTargetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAutoTargetPlayerTrackProperties;  // 0x112542BC

			// FUNCTION: ENGINE 0x10141530
			bool AutoTargetPlayerTrack::SetTimeBegin(float value)
			{
				timeBegin = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141550
			bool AutoTargetPlayerTrack::SetTimeEnd(float value)
			{
				timeEnd = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141570
			bool AutoTargetPlayerTrack::SetSetTarget(bool value)
			{
				setTarget = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141580
			bool AutoTargetPlayerTrack::SetArc(float value)
			{
				arc = value * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101415A0
			bool AutoTargetPlayerTrack::SetMaxDistance(float value)
			{
				maxDistance = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101415C0
			bool AutoTargetPlayerTrack::SetKeepChecking(bool value)
			{
				keepChecking = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10141A60
			fight::Property* AutoTargetPlayerTrack::GetProperty(int index)
			{
				return gAutoTargetPlayerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10141A80
			void AutoTargetPlayerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAutoTargetPlayerTrackProperties);
			}

			// FUNCTION: ENGINE 0x10141A90
			AutoTargetPlayerTrack::AutoTargetPlayerTrack() : arc(3.1415927f), maxDistance(5.0f), timeBegin(0.0f), timeEnd(-1.0f), keepChecking(true), setTarget(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10141B00
			float AutoTargetPlayerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10141B10
			float AutoTargetPlayerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10141B20
			AutoTargetPlayerTrack::~AutoTargetPlayerTrack()
			{
			}

			// FUNCTION: ENGINE 0x101437B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AutoTargetPlayerTrack::RegisterProperties()
			{
				if (gAutoTargetPlayerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AutoTargetPlayerTrack>("timeBegin", &AutoTargetPlayerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetPlayerTrack>("timeEnd", &AutoTargetPlayerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<AutoTargetPlayerTrack>("setTarget", &AutoTargetPlayerTrack::SetSetTarget);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetPlayerTrack>("arc", &AutoTargetPlayerTrack::SetArc);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetPlayerTrack>("maxDistance", &AutoTargetPlayerTrack::SetMaxDistance);
					properties[4] = property;
					property = new fight::PropertyBool<AutoTargetPlayerTrack>("keepChecking", &AutoTargetPlayerTrack::SetKeepChecking);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gAutoTargetPlayerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10142860
			fight::TrackFactory* CreateAutoTargetPlayerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AutoTargetPlayerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10143A70
			void RegisterAutoTargetPlayerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AutoTargetPlayerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<AutoTargetTrack>;
			template class fight::PropertyBool<AutoTargetTrack>;
			template class fight::PropertyVector<AutoTargetTrack>;
			template class fight::PropertyBitfieldConstList<AutoTargetTrack>;
			template class fight::PropertyEnumConstList<AutoTargetTrack>;
			template class fight::PropertyIntConstRange<AutoTargetTrack>;
			template class fight::TrackFactoryTemplate<AutoTargetTrack>;
			template class fight::TrackFactoryCasterTemplate<AutoTargetTrack>;
			template class fight::PropertyFloatConstRange<AutoTargetClearTrack>;
			template class fight::TrackFactoryTemplate<AutoTargetClearTrack>;
			template class fight::TrackFactoryCasterTemplate<AutoTargetClearTrack>;
			template class fight::PropertyFloatConstRange<AutoTargetPositionTrack>;
			template class fight::PropertyVector<AutoTargetPositionTrack>;
			template class fight::PropertyIntConstRange<AutoTargetPositionTrack>;
			template class fight::TrackFactoryTemplate<AutoTargetPositionTrack>;
			template class fight::TrackFactoryCasterTemplate<AutoTargetPositionTrack>;
			template class fight::PropertyFloatConstRange<FlyingAutoTargetTrack>;
			template class fight::PropertyVector<FlyingAutoTargetTrack>;
			template class fight::PropertyBool<FlyingAutoTargetTrack>;
			template class fight::PropertyBitfieldConstList<FlyingAutoTargetTrack>;
			template class fight::PropertyEnumConstList<FlyingAutoTargetTrack>;
			template class fight::PropertyIntConstRange<FlyingAutoTargetTrack>;
			template class fight::TrackFactoryTemplate<FlyingAutoTargetTrack>;
			template class fight::TrackFactoryCasterTemplate<FlyingAutoTargetTrack>;
			template class fight::PropertyFloatConstRange<PedestrianAutoTargetTrack>;
			template class fight::PropertyIntConstRange<PedestrianAutoTargetTrack>;
			template class fight::TrackFactoryTemplate<PedestrianAutoTargetTrack>;
			template class fight::TrackFactoryCasterTemplate<PedestrianAutoTargetTrack>;
			template class fight::PropertyFloatConstRange<AutoTargetPlayerTrack>;
			template class fight::PropertyBool<AutoTargetPlayerTrack>;
			template class fight::TrackFactoryTemplate<AutoTargetPlayerTrack>;
			template class fight::TrackFactoryCasterTemplate<AutoTargetPlayerTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10141B30
// FUNCTION: ENGINE 0x10141B60
// FUNCTION: ENGINE 0x10141B90
// FUNCTION: ENGINE 0x10141BC0
// FUNCTION: ENGINE 0x10141BF0
// FUNCTION: ENGINE 0x10141C20
// FUNCTION: ENGINE 0x10141C60
// FUNCTION: ENGINE 0x10141C70
// FUNCTION: ENGINE 0x10141CA0
// FUNCTION: ENGINE 0x10141CB0
// FUNCTION: ENGINE 0x10141CE0
// FUNCTION: ENGINE 0x10141CF0
// FUNCTION: ENGINE 0x10141D20
// FUNCTION: ENGINE 0x10141D30
// FUNCTION: ENGINE 0x10141D60
// FUNCTION: ENGINE 0x10141D70
// FUNCTION: ENGINE 0x10141DA0
// FUNCTION: ENGINE 0x10141DB0
// FUNCTION: ENGINE 0x10141DE0
// FUNCTION: ENGINE 0x10141E10
// FUNCTION: ENGINE 0x10141E40
// FUNCTION: ENGINE 0x10141E50
// FUNCTION: ENGINE 0x10141E90
// FUNCTION: ENGINE 0x10141EB0
// FUNCTION: ENGINE 0x10141EC0
// FUNCTION: ENGINE 0x10141EF0
// FUNCTION: ENGINE 0x10141F10
// FUNCTION: ENGINE 0x10141F20
// FUNCTION: ENGINE 0x10141F60
// FUNCTION: ENGINE 0x10141F70
// FUNCTION: ENGINE 0x10141F90
// FUNCTION: ENGINE 0x10141FA0
// FUNCTION: ENGINE 0x10142000
// FUNCTION: ENGINE 0x10142040
// FUNCTION: ENGINE 0x10142050
// FUNCTION: ENGINE 0x10142080
// FUNCTION: ENGINE 0x101420A0
// FUNCTION: ENGINE 0x101420B0
// FUNCTION: ENGINE 0x101420E0
// FUNCTION: ENGINE 0x10142100
// FUNCTION: ENGINE 0x10142110
// FUNCTION: ENGINE 0x10142140
// FUNCTION: ENGINE 0x10142170
// FUNCTION: ENGINE 0x10142180
// FUNCTION: ENGINE 0x101421B0
// FUNCTION: ENGINE 0x101421E0
// FUNCTION: ENGINE 0x101421F0
// FUNCTION: ENGINE 0x10142220
// FUNCTION: ENGINE 0x10142240
// FUNCTION: ENGINE 0x10142250
// FUNCTION: ENGINE 0x10142280
// FUNCTION: ENGINE 0x101422A0
// FUNCTION: ENGINE 0x101422B0
// FUNCTION: ENGINE 0x101422E0
// FUNCTION: ENGINE 0x10142310
// FUNCTION: ENGINE 0x10142320
// FUNCTION: ENGINE 0x10142350
// FUNCTION: ENGINE 0x10142370
// FUNCTION: ENGINE 0x10142380
// FUNCTION: ENGINE 0x101423B0
// FUNCTION: ENGINE 0x101423D0
// FUNCTION: ENGINE 0x101423E0
// FUNCTION: ENGINE 0x10142420
// FUNCTION: ENGINE 0x10142430
// FUNCTION: ENGINE 0x10142450
// FUNCTION: ENGINE 0x10142460
// FUNCTION: ENGINE 0x101424C0
// FUNCTION: ENGINE 0x10142500
// FUNCTION: ENGINE 0x10142510
// FUNCTION: ENGINE 0x10142540
// FUNCTION: ENGINE 0x10142560
// FUNCTION: ENGINE 0x10142570
// FUNCTION: ENGINE 0x101425A0
// FUNCTION: ENGINE 0x101425C0
// FUNCTION: ENGINE 0x101425D0
// FUNCTION: ENGINE 0x10142600
// FUNCTION: ENGINE 0x10142630
// FUNCTION: ENGINE 0x10142640
// FUNCTION: ENGINE 0x10142670
// FUNCTION: ENGINE 0x10142690
// FUNCTION: ENGINE 0x101426A0
// FUNCTION: ENGINE 0x101426D0
// FUNCTION: ENGINE 0x10142700
// FUNCTION: ENGINE 0x10142710
// FUNCTION: ENGINE 0x10142740
// FUNCTION: ENGINE 0x10142760
// FUNCTION: ENGINE 0x10143AA0
// FUNCTION: ENGINE 0x10143AD0
// FUNCTION: ENGINE 0x10143AF0
// FUNCTION: ENGINE 0x10143B20
// FUNCTION: ENGINE 0x10143B40
// FUNCTION: ENGINE 0x10143B70
// FUNCTION: ENGINE 0x10143B90
// FUNCTION: ENGINE 0x10143BC0
// FUNCTION: ENGINE 0x10143BE0
// FUNCTION: ENGINE 0x10143C10
// FUNCTION: ENGINE 0x10143C30
// FUNCTION: ENGINE 0x10143C60
// FUNCTION: ENGINE 0x10143C80
// FUNCTION: ENGINE 0x10143CD0
// FUNCTION: ENGINE 0x10143D20
// FUNCTION: ENGINE 0x10143D70
// FUNCTION: ENGINE 0x10143DC0
// FUNCTION: ENGINE 0x10143E10
