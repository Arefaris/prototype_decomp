// Fight items of the motion group: WhipFistExtendBlockedOrNotCondition, WhipFistResetTargetTrack, TendrilTrack, WhipFistRetractTrack, WhipFistFreezeSegmentsTrack, WhipFistSegmentFixToJointTrack, TendrilFromParentTrack, WhipFistExtendTrack, WhipFistPullParentToTargetTrack, WhipFistAnimatedTrack, WhipFistMakeTautTrack (unit 0x101D0A00 - 0x101D5F50; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_whipfist.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gWhipFistExtendBlockedOrNotConditionProperties;  // 0x11254CC0

			// FUNCTION: ENGINE 0x101D0A00
			bool WhipFistExtendBlockedOrNotCondition::SetBlocked(bool newValue)
			{
				blocked = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1760
			fight::Property* WhipFistExtendBlockedOrNotCondition::GetProperty(int index)
			{
				return gWhipFistExtendBlockedOrNotConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101D1780
			void WhipFistExtendBlockedOrNotCondition::ClearProperties()
			{
				fight::FreePropertyList(&gWhipFistExtendBlockedOrNotConditionProperties);
			}

			// FUNCTION: ENGINE 0x101D1790
			WhipFistExtendBlockedOrNotCondition::WhipFistExtendBlockedOrNotCondition() : fight::Condition(0), blocked(false)
			{
			}

			// FUNCTION: ENGINE 0x101D17B0
			WhipFistExtendBlockedOrNotCondition::~WhipFistExtendBlockedOrNotCondition()
			{
			}

			// FUNCTION: ENGINE 0x101D3440
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WhipFistExtendBlockedOrNotCondition::RegisterProperties()
			{
				if (gWhipFistExtendBlockedOrNotConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<WhipFistExtendBlockedOrNotCondition>("blocked", &WhipFistExtendBlockedOrNotCondition::SetBlocked);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gWhipFistExtendBlockedOrNotConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D3230
			fight::ConditionFactory* CreateWhipFistExtendBlockedOrNotConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<WhipFistExtendBlockedOrNotCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D4250
			void RegisterWhipFistExtendBlockedOrNotConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<WhipFistExtendBlockedOrNotCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gWhipFistResetTargetTrackProperties;  // 0x11254CC4

			// FUNCTION: ENGINE 0x101D0A10
			bool WhipFistResetTargetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D17C0
			fight::Property* WhipFistResetTargetTrack::GetProperty(int index)
			{
				return gWhipFistResetTargetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D17E0
			void WhipFistResetTargetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWhipFistResetTargetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D17F0
			WhipFistResetTargetTrack::WhipFistResetTargetTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101D1820
			float WhipFistResetTargetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1830
			float WhipFistResetTargetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101D1840
			WhipFistResetTargetTrack::~WhipFistResetTargetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D34E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WhipFistResetTargetTrack::RegisterProperties()
			{
				if (gWhipFistResetTargetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WhipFistResetTargetTrack>("timeBegin", &WhipFistResetTargetTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gWhipFistResetTargetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D3260
			fight::TrackFactory* CreateWhipFistResetTargetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistResetTargetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D4280
			void RegisterWhipFistResetTargetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistResetTargetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTendrilTrackProperties;  // 0x11254CC8

			// FUNCTION: ENGINE 0x101D0A30
			bool TendrilTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0A50
			bool TendrilTrack::SetTimeReverse(float newValue)
			{
				timeReverse = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0A70
			bool TendrilTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1DA0
			bool TendrilTrack::SetDrawable(const fight::Name& newValue)
			{
				drawable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0A90
			bool TendrilTrack::SetScale(float newValue)
			{
				scale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0AB0
			bool TendrilTrack::SetKeepGoing(bool newValue)
			{
				keepGoing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0AD0
			bool TendrilTrack::SetHitRadius(float newValue)
			{
				hitRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0AF0
			bool TendrilTrack::SetTrackingVelocity(float newValue)
			{
				trackingVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0B10
			bool TendrilTrack::SetTrackingDeceleration(float newValue)
			{
				trackingDeceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0B30
			bool TendrilTrack::SetSwapDirection(bool newValue)
			{
				swapDirection = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0B50
			bool TendrilTrack::SetStaticEndPoint(bool newValue)
			{
				staticEndPoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1DC0
			bool TendrilTrack::SetStartJoint(const fight::Name& newValue)
			{
				startJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0B70
			bool TendrilTrack::SetStartJointOffset(const math::Vector& newValue)
			{
				startJointOffset.x = newValue.x;
				startJointOffset.y = newValue.y;
				startJointOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1DE0
			bool TendrilTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0B90
			bool TendrilTrack::SetUseGrabber(bool newValue)
			{
				useGrabber = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1E00
			bool TendrilTrack::SetGrabSlotJoint(const fight::Name& newValue)
			{
				grabSlotJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0BB0
			bool TendrilTrack::SetGrabSlotJointOffset(const math::Vector& newValue)
			{
				grabSlotJointOffset.x = newValue.x;
				grabSlotJointOffset.y = newValue.y;
				grabSlotJointOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0BD0
			bool TendrilTrack::SetForwardVelocity(float newValue)
			{
				forwardVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0BF0
			bool TendrilTrack::SetReverseVelocity(float newValue)
			{
				reverseVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0C10
			bool TendrilTrack::SetCircleRadius(float newValue)
			{
				circleRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0C30
			bool TendrilTrack::SetZAxisRotation(float newValue)
			{
				zAxisRotation = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0C60
			bool TendrilTrack::SetXAxisRotation(float newValue)
			{
				xAxisRotation = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0C90
			bool TendrilTrack::SetSegmentCount(int newValue)
			{
				segmentCount = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0CB0
			bool TendrilTrack::SetWaveSpeed(float newValue)
			{
				waveSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0CD0
			bool TendrilTrack::SetWaveLength(float newValue)
			{
				waveLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0CF0
			bool TendrilTrack::SetWaveAmplitude(float newValue)
			{
				waveAmplitude = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0D10
			bool TendrilTrack::SetWaveAmplitudeRampUp(float newValue)
			{
				waveAmplitudeRampUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0D30
			bool TendrilTrack::SetWaveAmplitudeRampDown(float newValue)
			{
				waveAmplitudeRampDown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0D50
			bool TendrilTrack::SetCorkscrewAngle(float newValue)
			{
				corkscrewAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0D70
			bool TendrilTrack::SetCorkscrewRotationSpeed(float newValue)
			{
				corkscrewRotationSpeed = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0D90
			bool TendrilTrack::SetCorkscrewTravelingSpeed(float newValue)
			{
				corkscrewTravelingSpeed = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0DB0
			bool TendrilTrack::SetDevastatorDamageMultiplier(float newValue)
			{
				devastatorDamageMultiplier = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0DD0
			bool TendrilTrack::SetTimeBetweenHits(float newValue)
			{
				timeBetweenHits = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0DF0
			fight::ConditionList* TendrilTrack::SetReverseConditions()
			{
				return &reverseConditions;
			}

			// FUNCTION: ENGINE 0x101D1850
			fight::Property* TendrilTrack::GetProperty(int index)
			{
				return gTendrilTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D1870
			void TendrilTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTendrilTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D1F00
			TendrilTrack::TendrilTrack() : grabSlotJointOffset(0.0f, 0.0f, 0.0f), startJointOffset(0.0f, 0.0f, 0.0f), circleRadius(1.0f), corkscrewAngle(0.0f), corkscrewRotationSpeed(0.0f), corkscrewTravelingSpeed(0.0f), devastatorDamageMultiplier(1.0f), forwardVelocity(1.0f), hitRadius(0.0f), reverseVelocity(1.0f), scale(1.0f), timeBegin(0.0f), timeBetweenHits(0.0f), timeEnd(-1.0f), timeReverse(-1.0f), trackingDeceleration(0.0f), trackingVelocity(0.0f), waveAmplitude(0.3f), waveAmplitudeRampDown(0.2f), waveAmplitudeRampUp(0.2f), waveLength(2.0f), waveSpeed(1e+01f), xAxisRotation(0.0f), zAxisRotation(0.0f), segmentCount(5), keepGoing(false), staticEndPoint(false), swapDirection(false), useGrabber(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101D20A0
			float TendrilTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D20B0
			float TendrilTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D20C0
			TendrilTrack::~TendrilTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D48A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TendrilTrack::RegisterProperties()
			{
				if (gTendrilTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("timeBegin", &TendrilTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("timeReverse", &TendrilTrack::SetTimeReverse);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("timeEnd", &TendrilTrack::SetTimeEnd);
					properties[2] = property;
					property = new fight::PropertyName<TendrilTrack>("drawable", &TendrilTrack::SetDrawable);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("scale", &TendrilTrack::SetScale);
					properties[4] = property;
					property = new fight::PropertyBool<TendrilTrack>("keepGoing", &TendrilTrack::SetKeepGoing);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("hitRadius", &TendrilTrack::SetHitRadius);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("trackingVelocity", &TendrilTrack::SetTrackingVelocity);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("trackingDeceleration", &TendrilTrack::SetTrackingDeceleration);
					properties[8] = property;
					property = new fight::PropertyBool<TendrilTrack>("swapDirection", &TendrilTrack::SetSwapDirection);
					properties[9] = property;
					property = new fight::PropertyBool<TendrilTrack>("staticEndPoint", &TendrilTrack::SetStaticEndPoint);
					properties[10] = property;
					property = new fight::PropertyNameList<TendrilTrack>("startJoint", &TendrilTrack::SetStartJoint);
					properties[11] = property;
					property = new fight::PropertyVector<TendrilTrack>("startJointOffset", &TendrilTrack::SetStartJointOffset);
					properties[12] = property;
					property = new fight::PropertyNameList<TendrilTrack>("grabSlot", &TendrilTrack::SetGrabSlot);
					properties[13] = property;
					property = new fight::PropertyBool<TendrilTrack>("useGrabber", &TendrilTrack::SetUseGrabber);
					properties[14] = property;
					property = new fight::PropertyNameList<TendrilTrack>("grabSlotJoint", &TendrilTrack::SetGrabSlotJoint);
					properties[15] = property;
					property = new fight::PropertyVector<TendrilTrack>("grabSlotJointOffset", &TendrilTrack::SetGrabSlotJointOffset);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("forwardVelocity", &TendrilTrack::SetForwardVelocity);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("reverseVelocity", &TendrilTrack::SetReverseVelocity);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("circleRadius", &TendrilTrack::SetCircleRadius);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("zAxisRotation", &TendrilTrack::SetZAxisRotation);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("xAxisRotation", &TendrilTrack::SetXAxisRotation);
					properties[21] = property;
					property = new fight::PropertyIntConstRange<TendrilTrack>("segmentCount", &TendrilTrack::SetSegmentCount);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("waveSpeed", &TendrilTrack::SetWaveSpeed);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("waveLength", &TendrilTrack::SetWaveLength);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("waveAmplitude", &TendrilTrack::SetWaveAmplitude);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("waveAmplitudeRampUp", &TendrilTrack::SetWaveAmplitudeRampUp);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("waveAmplitudeRampDown", &TendrilTrack::SetWaveAmplitudeRampDown);
					properties[27] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("corkscrewAngle", &TendrilTrack::SetCorkscrewAngle);
					properties[28] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("corkscrewRotationSpeed", &TendrilTrack::SetCorkscrewRotationSpeed);
					properties[29] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("corkscrewTravelingSpeed", &TendrilTrack::SetCorkscrewTravelingSpeed);
					properties[30] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("devastatorDamageMultiplier", &TendrilTrack::SetDevastatorDamageMultiplier);
					properties[31] = property;
					property = new fight::PropertyFloatConstRange<TendrilTrack>("timeBetweenHits", &TendrilTrack::SetTimeBetweenHits);
					properties[32] = property;
					property = new fight::PropertyConditionGroup<TendrilTrack>("reverseConditions", &TendrilTrack::SetReverseConditions);
					properties[33] = property;
					fight::RegisterPropertyList(properties, &gTendrilTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D3290
			fight::TrackFactory* CreateTendrilTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TendrilTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D42B0
			void RegisterTendrilTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TendrilTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWhipFistRetractTrackProperties;  // 0x11254CCC

			// FUNCTION: ENGINE 0x101D0E00
			bool WhipFistRetractTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0E20
			bool WhipFistRetractTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0E40
			bool WhipFistRetractTrack::SetVelocity(float newValue)
			{
				velocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0E60
			bool WhipFistRetractTrack::SetSoundLeadTime(float newValue)
			{
				soundLeadTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0E80
			bool WhipFistRetractTrack::SetMinSegmentsRemaining(int newValue)
			{
				minSegmentsRemaining = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1880
			fight::Property* WhipFistRetractTrack::GetProperty(int index)
			{
				return gWhipFistRetractTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D18A0
			void WhipFistRetractTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWhipFistRetractTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D18B0
			WhipFistRetractTrack::WhipFistRetractTrack() : soundLeadTime(0.0f), timeBegin(0.0f), timeEnd(0.0f), velocity(0.0f), minSegmentsRemaining(1)
			{
			}

			// FUNCTION: ENGINE 0x101D18F0
			float WhipFistRetractTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1900
			float WhipFistRetractTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1910
			WhipFistRetractTrack::~WhipFistRetractTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D3580
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WhipFistRetractTrack::RegisterProperties()
			{
				if (gWhipFistRetractTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WhipFistRetractTrack>("timeBegin", &WhipFistRetractTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WhipFistRetractTrack>("timeEnd", &WhipFistRetractTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WhipFistRetractTrack>("velocity", &WhipFistRetractTrack::SetVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WhipFistRetractTrack>("soundLeadTime", &WhipFistRetractTrack::SetSoundLeadTime);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<WhipFistRetractTrack>("minSegmentsRemaining", &WhipFistRetractTrack::SetMinSegmentsRemaining);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gWhipFistRetractTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D32C0
			fight::TrackFactory* CreateWhipFistRetractTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistRetractTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D42E0
			void RegisterWhipFistRetractTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistRetractTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWhipFistFreezeSegmentsTrackProperties;  // 0x11254CD0

			// FUNCTION: ENGINE 0x101D0E90
			bool WhipFistFreezeSegmentsTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0EB0
			bool WhipFistFreezeSegmentsTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0ED0
			bool WhipFistFreezeSegmentsTrack::SetNumSegments(int newValue)
			{
				numSegments = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1920
			fight::Property* WhipFistFreezeSegmentsTrack::GetProperty(int index)
			{
				return gWhipFistFreezeSegmentsTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D1940
			void WhipFistFreezeSegmentsTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWhipFistFreezeSegmentsTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D1950
			WhipFistFreezeSegmentsTrack::WhipFistFreezeSegmentsTrack() : timeBegin(0.0f), timeEnd(-1.0f), numSegments(1)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101D1990
			float WhipFistFreezeSegmentsTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D19A0
			float WhipFistFreezeSegmentsTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D19B0
			WhipFistFreezeSegmentsTrack::~WhipFistFreezeSegmentsTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D3710
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WhipFistFreezeSegmentsTrack::RegisterProperties()
			{
				if (gWhipFistFreezeSegmentsTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WhipFistFreezeSegmentsTrack>("timeBegin", &WhipFistFreezeSegmentsTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WhipFistFreezeSegmentsTrack>("timeEnd", &WhipFistFreezeSegmentsTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<WhipFistFreezeSegmentsTrack>("numSegments", &WhipFistFreezeSegmentsTrack::SetNumSegments);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gWhipFistFreezeSegmentsTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D32F0
			fight::TrackFactory* CreateWhipFistFreezeSegmentsTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistFreezeSegmentsTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D4310
			void RegisterWhipFistFreezeSegmentsTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistFreezeSegmentsTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWhipFistSegmentFixToJointTrackProperties;  // 0x11254CD4

			// FUNCTION: ENGINE 0x101D0EE0
			bool WhipFistSegmentFixToJointTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0F00
			bool WhipFistSegmentFixToJointTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0F20
			bool WhipFistSegmentFixToJointTrack::SetSegmentIndexFromStart(int newValue)
			{
				segmentIndexFromStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1E20
			bool WhipFistSegmentFixToJointTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0F30
			bool WhipFistSegmentFixToJointTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101D19C0
			fight::Property* WhipFistSegmentFixToJointTrack::GetProperty(int index)
			{
				return gWhipFistSegmentFixToJointTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D19E0
			void WhipFistSegmentFixToJointTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWhipFistSegmentFixToJointTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D2140
			WhipFistSegmentFixToJointTrack::WhipFistSegmentFixToJointTrack() : offset(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(-1.0f), segmentIndexFromStart(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101D21A0
			float WhipFistSegmentFixToJointTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D21B0
			float WhipFistSegmentFixToJointTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D21C0
			WhipFistSegmentFixToJointTrack::~WhipFistSegmentFixToJointTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D5130
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WhipFistSegmentFixToJointTrack::RegisterProperties()
			{
				if (gWhipFistSegmentFixToJointTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WhipFistSegmentFixToJointTrack>("timeBegin", &WhipFistSegmentFixToJointTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WhipFistSegmentFixToJointTrack>("timeEnd", &WhipFistSegmentFixToJointTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<WhipFistSegmentFixToJointTrack>("segmentIndexFromStart", &WhipFistSegmentFixToJointTrack::SetSegmentIndexFromStart);
					properties[2] = property;
					property = new fight::PropertyNameList<WhipFistSegmentFixToJointTrack>("joint", &WhipFistSegmentFixToJointTrack::SetJoint);
					properties[3] = property;
					property = new fight::PropertyVector<WhipFistSegmentFixToJointTrack>("offset", &WhipFistSegmentFixToJointTrack::SetOffset);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gWhipFistSegmentFixToJointTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D3320
			fight::TrackFactory* CreateWhipFistSegmentFixToJointTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistSegmentFixToJointTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D4340
			void RegisterWhipFistSegmentFixToJointTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistSegmentFixToJointTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTendrilFromParentTrackProperties;  // 0x11254CD8

			// FUNCTION: ENGINE 0x101D0F50
			bool TendrilFromParentTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0F70
			bool TendrilFromParentTrack::SetTimeReverse(float newValue)
			{
				timeReverse = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0F90
			bool TendrilFromParentTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1E40
			bool TendrilFromParentTrack::SetDrawable(const fight::Name& newValue)
			{
				drawable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0FB0
			bool TendrilFromParentTrack::SetScale(float newValue)
			{
				scale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0FD0
			bool TendrilFromParentTrack::SetKeepGoing(bool newValue)
			{
				keepGoing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0FF0
			bool TendrilFromParentTrack::SetHitRadius(float newValue)
			{
				hitRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1010
			bool TendrilFromParentTrack::SetTrackingVelocity(float newValue)
			{
				trackingVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1030
			bool TendrilFromParentTrack::SetTrackingDeceleration(float newValue)
			{
				trackingDeceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1050
			bool TendrilFromParentTrack::SetSwapDirection(bool newValue)
			{
				swapDirection = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1070
			bool TendrilFromParentTrack::SetStaticEndPoint(bool newValue)
			{
				staticEndPoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1E60
			bool TendrilFromParentTrack::SetStartJoint(const fight::Name& newValue)
			{
				startJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1090
			bool TendrilFromParentTrack::SetStartJointOffset(const math::Vector& newValue)
			{
				startJointOffset.x = newValue.x;
				startJointOffset.y = newValue.y;
				startJointOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1E80
			bool TendrilFromParentTrack::SetGrabSlotJoint(const fight::Name& newValue)
			{
				grabSlotJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D10B0
			bool TendrilFromParentTrack::SetGrabSlotJointOffset(const math::Vector& newValue)
			{
				grabSlotJointOffset.x = newValue.x;
				grabSlotJointOffset.y = newValue.y;
				grabSlotJointOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101D10D0
			bool TendrilFromParentTrack::SetForwardVelocity(float newValue)
			{
				forwardVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D10F0
			bool TendrilFromParentTrack::SetReverseVelocity(float newValue)
			{
				reverseVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1110
			bool TendrilFromParentTrack::SetCircleRadius(float newValue)
			{
				circleRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1130
			bool TendrilFromParentTrack::SetZAxisRotation(float newValue)
			{
				zAxisRotation = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1160
			bool TendrilFromParentTrack::SetXAxisRotation(float newValue)
			{
				xAxisRotation = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1190
			bool TendrilFromParentTrack::SetSegmentCount(int newValue)
			{
				segmentCount = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D11B0
			bool TendrilFromParentTrack::SetWaveSpeed(float newValue)
			{
				waveSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D11D0
			bool TendrilFromParentTrack::SetWaveLength(float newValue)
			{
				waveLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D11F0
			bool TendrilFromParentTrack::SetWaveAmplitude(float newValue)
			{
				waveAmplitude = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1210
			bool TendrilFromParentTrack::SetWaveAmplitudeRampUp(float newValue)
			{
				waveAmplitudeRampUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1230
			bool TendrilFromParentTrack::SetWaveAmplitudeRampDown(float newValue)
			{
				waveAmplitudeRampDown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1250
			bool TendrilFromParentTrack::SetCorkscrewAngle(float newValue)
			{
				corkscrewAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1270
			bool TendrilFromParentTrack::SetCorkscrewRotationSpeed(float newValue)
			{
				corkscrewRotationSpeed = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1290
			bool TendrilFromParentTrack::SetCorkscrewTravelingSpeed(float newValue)
			{
				corkscrewTravelingSpeed = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D12B0
			bool TendrilFromParentTrack::SetDevastatorDamageMultiplier(float newValue)
			{
				devastatorDamageMultiplier = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D12D0
			bool TendrilFromParentTrack::SetTimeBetweenHits(float newValue)
			{
				timeBetweenHits = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D12F0
			fight::ConditionList* TendrilFromParentTrack::SetReverseConditions()
			{
				return &reverseConditions;
			}

			// FUNCTION: ENGINE 0x101D19F0
			fight::Property* TendrilFromParentTrack::GetProperty(int index)
			{
				return gTendrilFromParentTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D1A10
			void TendrilFromParentTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTendrilFromParentTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D21D0
			TendrilFromParentTrack::TendrilFromParentTrack() : grabSlotJointOffset(0.0f, 0.0f, 0.0f), startJointOffset(0.0f, 0.0f, 0.0f), circleRadius(1.0f), corkscrewAngle(0.0f), corkscrewRotationSpeed(0.0f), corkscrewTravelingSpeed(0.0f), devastatorDamageMultiplier(1.0f), forwardVelocity(1.0f), hitRadius(0.0f), reverseVelocity(1.0f), scale(1.0f), timeBegin(0.0f), timeBetweenHits(0.0f), timeEnd(-1.0f), timeReverse(-1.0f), trackingDeceleration(0.0f), trackingVelocity(0.0f), waveAmplitude(0.3f), waveAmplitudeRampDown(0.2f), waveAmplitudeRampUp(0.2f), waveLength(2.0f), waveSpeed(1e+01f), xAxisRotation(0.0f), zAxisRotation(0.0f), segmentCount(5), keepGoing(false), staticEndPoint(false), swapDirection(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101D2350
			float TendrilFromParentTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D2360
			float TendrilFromParentTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D2370
			TendrilFromParentTrack::~TendrilFromParentTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D52C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TendrilFromParentTrack::RegisterProperties()
			{
				if (gTendrilFromParentTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("timeBegin", &TendrilFromParentTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("timeReverse", &TendrilFromParentTrack::SetTimeReverse);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("timeEnd", &TendrilFromParentTrack::SetTimeEnd);
					properties[2] = property;
					property = new fight::PropertyName<TendrilFromParentTrack>("drawable", &TendrilFromParentTrack::SetDrawable);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("scale", &TendrilFromParentTrack::SetScale);
					properties[4] = property;
					property = new fight::PropertyBool<TendrilFromParentTrack>("keepGoing", &TendrilFromParentTrack::SetKeepGoing);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("hitRadius", &TendrilFromParentTrack::SetHitRadius);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("trackingVelocity", &TendrilFromParentTrack::SetTrackingVelocity);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("trackingDeceleration", &TendrilFromParentTrack::SetTrackingDeceleration);
					properties[8] = property;
					property = new fight::PropertyBool<TendrilFromParentTrack>("swapDirection", &TendrilFromParentTrack::SetSwapDirection);
					properties[9] = property;
					property = new fight::PropertyBool<TendrilFromParentTrack>("staticEndPoint", &TendrilFromParentTrack::SetStaticEndPoint);
					properties[10] = property;
					property = new fight::PropertyNameList<TendrilFromParentTrack>("startJoint", &TendrilFromParentTrack::SetStartJoint);
					properties[11] = property;
					property = new fight::PropertyVector<TendrilFromParentTrack>("startJointOffset", &TendrilFromParentTrack::SetStartJointOffset);
					properties[12] = property;
					property = new fight::PropertyNameList<TendrilFromParentTrack>("grabSlotJoint", &TendrilFromParentTrack::SetGrabSlotJoint);
					properties[13] = property;
					property = new fight::PropertyVector<TendrilFromParentTrack>("grabSlotJointOffset", &TendrilFromParentTrack::SetGrabSlotJointOffset);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("forwardVelocity", &TendrilFromParentTrack::SetForwardVelocity);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("reverseVelocity", &TendrilFromParentTrack::SetReverseVelocity);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("circleRadius", &TendrilFromParentTrack::SetCircleRadius);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("zAxisRotation", &TendrilFromParentTrack::SetZAxisRotation);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("xAxisRotation", &TendrilFromParentTrack::SetXAxisRotation);
					properties[19] = property;
					property = new fight::PropertyIntConstRange<TendrilFromParentTrack>("segmentCount", &TendrilFromParentTrack::SetSegmentCount);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("waveSpeed", &TendrilFromParentTrack::SetWaveSpeed);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("waveLength", &TendrilFromParentTrack::SetWaveLength);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("waveAmplitude", &TendrilFromParentTrack::SetWaveAmplitude);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("waveAmplitudeRampUp", &TendrilFromParentTrack::SetWaveAmplitudeRampUp);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("waveAmplitudeRampDown", &TendrilFromParentTrack::SetWaveAmplitudeRampDown);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("corkscrewAngle", &TendrilFromParentTrack::SetCorkscrewAngle);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("corkscrewRotationSpeed", &TendrilFromParentTrack::SetCorkscrewRotationSpeed);
					properties[27] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("corkscrewTravelingSpeed", &TendrilFromParentTrack::SetCorkscrewTravelingSpeed);
					properties[28] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("devastatorDamageMultiplier", &TendrilFromParentTrack::SetDevastatorDamageMultiplier);
					properties[29] = property;
					property = new fight::PropertyFloatConstRange<TendrilFromParentTrack>("timeBetweenHits", &TendrilFromParentTrack::SetTimeBetweenHits);
					properties[30] = property;
					property = new fight::PropertyConditionGroup<TendrilFromParentTrack>("reverseConditions", &TendrilFromParentTrack::SetReverseConditions);
					properties[31] = property;
					fight::RegisterPropertyList(properties, &gTendrilFromParentTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D3350
			fight::TrackFactory* CreateTendrilFromParentTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TendrilFromParentTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D4370
			void RegisterTendrilFromParentTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TendrilFromParentTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWhipFistExtendTrackProperties;  // 0x11254CDC

			// FUNCTION: ENGINE 0x101D1300
			bool WhipFistExtendTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1320
			bool WhipFistExtendTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1340
			bool WhipFistExtendTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1360
			bool WhipFistExtendTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1380
			bool WhipFistExtendTrack::SetDistanceMin(float newValue)
			{
				distanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D13A0
			bool WhipFistExtendTrack::SetDistanceMax(float newValue)
			{
				distanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D13C0
			bool WhipFistExtendTrack::SetTrackingMin(float newValue)
			{
				trackingMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D13E0
			bool WhipFistExtendTrack::SetTrackingMax(float newValue)
			{
				trackingMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1400
			bool WhipFistExtendTrack::SetDamageMin(float newValue)
			{
				damageMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1420
			bool WhipFistExtendTrack::SetDamageMax(float newValue)
			{
				damageMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1440
			bool WhipFistExtendTrack::SetWaveSpeed(float newValue)
			{
				waveSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1460
			bool WhipFistExtendTrack::SetWaveLength(float newValue)
			{
				waveLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1480
			bool WhipFistExtendTrack::SetWaveAmplitude(float newValue)
			{
				waveAmplitude = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D14A0
			bool WhipFistExtendTrack::SetWaveAmplitudeRampUp(float newValue)
			{
				waveAmplitudeRampUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D14C0
			bool WhipFistExtendTrack::SetWaveAmplitudeRampDown(float newValue)
			{
				waveAmplitudeRampDown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D14E0
			bool WhipFistExtendTrack::SetCorkscrewAngle(float newValue)
			{
				corkscrewAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1500
			bool WhipFistExtendTrack::SetCorkscrewRotationSpeed(float newValue)
			{
				corkscrewRotationSpeed = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1520
			bool WhipFistExtendTrack::SetCorkscrewTravelingSpeed(float newValue)
			{
				corkscrewTravelingSpeed = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1540
			bool WhipFistExtendTrack::SetTarget(int newValue)
			{
				target = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1A20
			fight::Property* WhipFistExtendTrack::GetProperty(int index)
			{
				return gWhipFistExtendTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D1A40
			void WhipFistExtendTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWhipFistExtendTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D1A50
			WhipFistExtendTrack::WhipFistExtendTrack() : corkscrewAngle(0.0f), corkscrewRotationSpeed(1.5707964f), corkscrewTravelingSpeed(0.08726647f), damageMax(0.0f), damageMin(0.0f), distanceMax(0.0f), distanceMin(0.0f), timeBegin(0.0f), timeEnd(-1.0f), trackingMax(0.0f), trackingMin(0.0f), velocityMax(0.0f), velocityMin(0.0f), waveAmplitude(1.0f), waveAmplitudeRampDown(1.0f), waveAmplitudeRampUp(0.0f), waveLength(2e+01f), waveSpeed(2e+01f), target(0)
			{
			}

			// FUNCTION: ENGINE 0x101D1B20
			float WhipFistExtendTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1B30
			float WhipFistExtendTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1B40
			WhipFistExtendTrack::~WhipFistExtendTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D3820
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WhipFistExtendTrack::RegisterProperties()
			{
				if (gWhipFistExtendTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("timeBegin", &WhipFistExtendTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("timeEnd", &WhipFistExtendTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("velocityMin", &WhipFistExtendTrack::SetVelocityMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("velocityMax", &WhipFistExtendTrack::SetVelocityMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("distanceMin", &WhipFistExtendTrack::SetDistanceMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("distanceMax", &WhipFistExtendTrack::SetDistanceMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("trackingMin", &WhipFistExtendTrack::SetTrackingMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("trackingMax", &WhipFistExtendTrack::SetTrackingMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("damageMin", &WhipFistExtendTrack::SetDamageMin);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("damageMax", &WhipFistExtendTrack::SetDamageMax);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("waveSpeed", &WhipFistExtendTrack::SetWaveSpeed);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("waveLength", &WhipFistExtendTrack::SetWaveLength);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("waveAmplitude", &WhipFistExtendTrack::SetWaveAmplitude);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("waveAmplitudeRampUp", &WhipFistExtendTrack::SetWaveAmplitudeRampUp);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("waveAmplitudeRampDown", &WhipFistExtendTrack::SetWaveAmplitudeRampDown);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("corkscrewAngle", &WhipFistExtendTrack::SetCorkscrewAngle);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("corkscrewRotationSpeed", &WhipFistExtendTrack::SetCorkscrewRotationSpeed);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<WhipFistExtendTrack>("corkscrewTravelingSpeed", &WhipFistExtendTrack::SetCorkscrewTravelingSpeed);
					properties[17] = property;
					property = new fight::PropertyEnumConstList<WhipFistExtendTrack>("target", gWhipFistExtendTrackTargetTable, gWhipFistExtendTrackTargetCount, &WhipFistExtendTrack::SetTarget);
					properties[18] = property;
					fight::RegisterPropertyList(properties, &gWhipFistExtendTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D3380
			fight::TrackFactory* CreateWhipFistExtendTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistExtendTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D43A0
			void RegisterWhipFistExtendTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistExtendTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWhipFistPullParentToTargetTrackProperties;  // 0x11254CE0

			// FUNCTION: ENGINE 0x101D1550
			bool WhipFistPullParentToTargetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1570
			bool WhipFistPullParentToTargetTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1590
			bool WhipFistPullParentToTargetTrack::SetVelocity(float newValue)
			{
				velocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D15B0
			bool WhipFistPullParentToTargetTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D15D0
			bool WhipFistPullParentToTargetTrack::SetParabolicConstant(float newValue)
			{
				parabolicConstant = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D15F0
			bool WhipFistPullParentToTargetTrack::SetParabolicOffset(float newValue)
			{
				parabolicOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1610
			bool WhipFistPullParentToTargetTrack::SetGoalOffsetFromTarget(const math::Vector& newValue)
			{
				goalOffsetFromTarget.x = newValue.x;
				goalOffsetFromTarget.y = newValue.y;
				goalOffsetFromTarget.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1630
			bool WhipFistPullParentToTargetTrack::SetFaceTargetMaxTurnRate(float newValue)
			{
				faceTargetMaxTurnRate = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1650
			bool WhipFistPullParentToTargetTrack::SetMaxStuckTime(float newValue)
			{
				maxStuckTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1670
			bool WhipFistPullParentToTargetTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1680
			bool WhipFistPullParentToTargetTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D16A0
			bool WhipFistPullParentToTargetTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1B50
			fight::Property* WhipFistPullParentToTargetTrack::GetProperty(int index)
			{
				return gWhipFistPullParentToTargetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D1B70
			void WhipFistPullParentToTargetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWhipFistPullParentToTargetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D1B80
			WhipFistPullParentToTargetTrack::WhipFistPullParentToTargetTrack() : goalOffsetFromTarget(0.0f, 0.0f, 0.0f), acceleration(15.0f), blendInTime(0.0f), blendOutTime(0.0f), faceTargetMaxTurnRate(3.1415927f), maxStuckTime(0.5f), parabolicConstant(3.0f), parabolicOffset(3.0f), timeBegin(0.0f), timeEnd(-1.0f), velocity(2e+01f), priority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101D1C40
			float WhipFistPullParentToTargetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1C50
			float WhipFistPullParentToTargetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1C60
			WhipFistPullParentToTargetTrack::~WhipFistPullParentToTargetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D3D20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WhipFistPullParentToTargetTrack::RegisterProperties()
			{
				if (gWhipFistPullParentToTargetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("timeBegin", &WhipFistPullParentToTargetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("timeEnd", &WhipFistPullParentToTargetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("velocity", &WhipFistPullParentToTargetTrack::SetVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("acceleration", &WhipFistPullParentToTargetTrack::SetAcceleration);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("parabolicConstant", &WhipFistPullParentToTargetTrack::SetParabolicConstant);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("parabolicOffset", &WhipFistPullParentToTargetTrack::SetParabolicOffset);
					properties[5] = property;
					property = new fight::PropertyVector<WhipFistPullParentToTargetTrack>("goalOffsetFromTarget", &WhipFistPullParentToTargetTrack::SetGoalOffsetFromTarget);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("faceTargetMaxTurnRate", &WhipFistPullParentToTargetTrack::SetFaceTargetMaxTurnRate);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("maxStuckTime", &WhipFistPullParentToTargetTrack::SetMaxStuckTime);
					properties[8] = property;
					property = new fight::PropertyIntConstRange<WhipFistPullParentToTargetTrack>("priority", &WhipFistPullParentToTargetTrack::SetPriority);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("blendInTime", &WhipFistPullParentToTargetTrack::SetBlendInTime);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>("blendOutTime", &WhipFistPullParentToTargetTrack::SetBlendOutTime);
					properties[11] = property;
					fight::RegisterPropertyList(properties, &gWhipFistPullParentToTargetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D33B0
			fight::TrackFactory* CreateWhipFistPullParentToTargetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistPullParentToTargetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D43D0
			void RegisterWhipFistPullParentToTargetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistPullParentToTargetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWhipFistAnimatedTrackProperties;  // 0x11254CE4

			// FUNCTION: ENGINE 0x101D16C0
			bool WhipFistAnimatedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D16E0
			bool WhipFistAnimatedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1C70
			fight::Property* WhipFistAnimatedTrack::GetProperty(int index)
			{
				return gWhipFistAnimatedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D1C90
			void WhipFistAnimatedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWhipFistAnimatedTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D1CA0
			WhipFistAnimatedTrack::WhipFistAnimatedTrack() : timeBegin(0.0f), timeEnd(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101D1CD0
			float WhipFistAnimatedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1CE0
			float WhipFistAnimatedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1CF0
			WhipFistAnimatedTrack::~WhipFistAnimatedTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D4060
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WhipFistAnimatedTrack::RegisterProperties()
			{
				if (gWhipFistAnimatedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WhipFistAnimatedTrack>("timeBegin", &WhipFistAnimatedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WhipFistAnimatedTrack>("timeEnd", &WhipFistAnimatedTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gWhipFistAnimatedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D33E0
			fight::TrackFactory* CreateWhipFistAnimatedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistAnimatedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D4400
			void RegisterWhipFistAnimatedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistAnimatedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWhipFistMakeTautTrackProperties;  // 0x11254CE8

			// FUNCTION: ENGINE 0x101D1700
			bool WhipFistMakeTautTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1720
			bool WhipFistMakeTautTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1740
			bool WhipFistMakeTautTrack::SetTautTime(float newValue)
			{
				tautTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D1D00
			fight::Property* WhipFistMakeTautTrack::GetProperty(int index)
			{
				return gWhipFistMakeTautTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D1D20
			void WhipFistMakeTautTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWhipFistMakeTautTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D1D30
			WhipFistMakeTautTrack::WhipFistMakeTautTrack() : tautTime(0.5f), timeBegin(0.0f), timeEnd(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101D1D70
			float WhipFistMakeTautTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1D80
			float WhipFistMakeTautTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D1D90
			WhipFistMakeTautTrack::~WhipFistMakeTautTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D4140
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WhipFistMakeTautTrack::RegisterProperties()
			{
				if (gWhipFistMakeTautTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WhipFistMakeTautTrack>("timeBegin", &WhipFistMakeTautTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WhipFistMakeTautTrack>("timeEnd", &WhipFistMakeTautTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WhipFistMakeTautTrack>("tautTime", &WhipFistMakeTautTrack::SetTautTime);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gWhipFistMakeTautTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D3410
			fight::TrackFactory* CreateWhipFistMakeTautTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistMakeTautTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D4430
			void RegisterWhipFistMakeTautTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WhipFistMakeTautTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyBool<WhipFistExtendBlockedOrNotCondition>;
			template class fight::ConditionFactoryTemplate<WhipFistExtendBlockedOrNotCondition>;
			template class fight::ConditionFactoryCasterTemplate<WhipFistExtendBlockedOrNotCondition>;
			template class fight::PropertyFloatConstRange<WhipFistResetTargetTrack>;
			template class fight::TrackFactoryTemplate<WhipFistResetTargetTrack>;
			template class fight::TrackFactoryCasterTemplate<WhipFistResetTargetTrack>;
			template class fight::PropertyFloatConstRange<TendrilTrack>;
			template class fight::PropertyName<TendrilTrack>;
			template class fight::PropertyBool<TendrilTrack>;
			template class fight::PropertyNameList<TendrilTrack>;
			template class fight::PropertyVector<TendrilTrack>;
			template class fight::PropertyIntConstRange<TendrilTrack>;
			template class fight::PropertyConditionGroup<TendrilTrack>;
			template class fight::TrackFactoryTemplate<TendrilTrack>;
			template class fight::TrackFactoryCasterTemplate<TendrilTrack>;
			template class fight::PropertyFloatConstRange<WhipFistRetractTrack>;
			template class fight::PropertyIntConstRange<WhipFistRetractTrack>;
			template class fight::TrackFactoryTemplate<WhipFistRetractTrack>;
			template class fight::TrackFactoryCasterTemplate<WhipFistRetractTrack>;
			template class fight::PropertyFloatConstRange<WhipFistFreezeSegmentsTrack>;
			template class fight::PropertyIntConstRange<WhipFistFreezeSegmentsTrack>;
			template class fight::TrackFactoryTemplate<WhipFistFreezeSegmentsTrack>;
			template class fight::TrackFactoryCasterTemplate<WhipFistFreezeSegmentsTrack>;
			template class fight::PropertyFloatConstRange<WhipFistSegmentFixToJointTrack>;
			template class fight::PropertyIntConstRange<WhipFistSegmentFixToJointTrack>;
			template class fight::PropertyNameList<WhipFistSegmentFixToJointTrack>;
			template class fight::PropertyVector<WhipFistSegmentFixToJointTrack>;
			template class fight::TrackFactoryTemplate<WhipFistSegmentFixToJointTrack>;
			template class fight::TrackFactoryCasterTemplate<WhipFistSegmentFixToJointTrack>;
			template class fight::PropertyFloatConstRange<TendrilFromParentTrack>;
			template class fight::PropertyName<TendrilFromParentTrack>;
			template class fight::PropertyBool<TendrilFromParentTrack>;
			template class fight::PropertyNameList<TendrilFromParentTrack>;
			template class fight::PropertyVector<TendrilFromParentTrack>;
			template class fight::PropertyIntConstRange<TendrilFromParentTrack>;
			template class fight::PropertyConditionGroup<TendrilFromParentTrack>;
			template class fight::TrackFactoryTemplate<TendrilFromParentTrack>;
			template class fight::TrackFactoryCasterTemplate<TendrilFromParentTrack>;
			template class fight::PropertyFloatConstRange<WhipFistExtendTrack>;
			template class fight::PropertyEnumConstList<WhipFistExtendTrack>;
			template class fight::TrackFactoryTemplate<WhipFistExtendTrack>;
			template class fight::TrackFactoryCasterTemplate<WhipFistExtendTrack>;
			template class fight::PropertyFloatConstRange<WhipFistPullParentToTargetTrack>;
			template class fight::PropertyVector<WhipFistPullParentToTargetTrack>;
			template class fight::PropertyIntConstRange<WhipFistPullParentToTargetTrack>;
			template class fight::TrackFactoryTemplate<WhipFistPullParentToTargetTrack>;
			template class fight::TrackFactoryCasterTemplate<WhipFistPullParentToTargetTrack>;
			template class fight::PropertyFloatConstRange<WhipFistAnimatedTrack>;
			template class fight::TrackFactoryTemplate<WhipFistAnimatedTrack>;
			template class fight::TrackFactoryCasterTemplate<WhipFistAnimatedTrack>;
			template class fight::PropertyFloatConstRange<WhipFistMakeTautTrack>;
			template class fight::TrackFactoryTemplate<WhipFistMakeTautTrack>;
			template class fight::TrackFactoryCasterTemplate<WhipFistMakeTautTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101D1EA0
// FUNCTION: ENGINE 0x101D1ED0
// FUNCTION: ENGINE 0x101D20E0
// FUNCTION: ENGINE 0x101D2110
// FUNCTION: ENGINE 0x101D2390
// FUNCTION: ENGINE 0x101D23C0
// FUNCTION: ENGINE 0x101D23F0
// FUNCTION: ENGINE 0x101D2420
// FUNCTION: ENGINE 0x101D2450
// FUNCTION: ENGINE 0x101D2460
// FUNCTION: ENGINE 0x101D2490
// FUNCTION: ENGINE 0x101D24A0
// FUNCTION: ENGINE 0x101D24D0
// FUNCTION: ENGINE 0x101D24E0
// FUNCTION: ENGINE 0x101D2510
// FUNCTION: ENGINE 0x101D2520
// FUNCTION: ENGINE 0x101D2550
// FUNCTION: ENGINE 0x101D2560
// FUNCTION: ENGINE 0x101D2590
// FUNCTION: ENGINE 0x101D25A0
// FUNCTION: ENGINE 0x101D25D0
// FUNCTION: ENGINE 0x101D25E0
// FUNCTION: ENGINE 0x101D2610
// FUNCTION: ENGINE 0x101D2620
// FUNCTION: ENGINE 0x101D2650
// FUNCTION: ENGINE 0x101D2660
// FUNCTION: ENGINE 0x101D2690
// FUNCTION: ENGINE 0x101D26A0
// FUNCTION: ENGINE 0x101D26D0
// FUNCTION: ENGINE 0x101D26E0
// FUNCTION: ENGINE 0x101D2710
// FUNCTION: ENGINE 0x101D2740
// FUNCTION: ENGINE 0x101D2770
// FUNCTION: ENGINE 0x101D27A0
// FUNCTION: ENGINE 0x101D27D0
// FUNCTION: ENGINE 0x101D27F0
// FUNCTION: ENGINE 0x101D2800
// FUNCTION: ENGINE 0x101D2830
// FUNCTION: ENGINE 0x101D2860
// FUNCTION: ENGINE 0x101D2870
// FUNCTION: ENGINE 0x101D28A0
// FUNCTION: ENGINE 0x101D28D0
// FUNCTION: ENGINE 0x101D28E0
// FUNCTION: ENGINE 0x101D2910
// FUNCTION: ENGINE 0x101D2930
// FUNCTION: ENGINE 0x101D2940
// FUNCTION: ENGINE 0x101D2970
// FUNCTION: ENGINE 0x101D2990
// FUNCTION: ENGINE 0x101D29A0
// FUNCTION: ENGINE 0x101D29D0
// FUNCTION: ENGINE 0x101D29F0
// FUNCTION: ENGINE 0x101D2A00
// FUNCTION: ENGINE 0x101D2A30
// FUNCTION: ENGINE 0x101D2A50
// FUNCTION: ENGINE 0x101D2A80
// FUNCTION: ENGINE 0x101D2AB0
// FUNCTION: ENGINE 0x101D2AC0
// FUNCTION: ENGINE 0x101D2AF0
// FUNCTION: ENGINE 0x101D2B10
// FUNCTION: ENGINE 0x101D2B20
// FUNCTION: ENGINE 0x101D2B50
// FUNCTION: ENGINE 0x101D2B80
// FUNCTION: ENGINE 0x101D2B90
// FUNCTION: ENGINE 0x101D2BC0
// FUNCTION: ENGINE 0x101D2BE0
// FUNCTION: ENGINE 0x101D2BF0
// FUNCTION: ENGINE 0x101D2C20
// FUNCTION: ENGINE 0x101D2C50
// FUNCTION: ENGINE 0x101D2C60
// FUNCTION: ENGINE 0x101D2C90
// FUNCTION: ENGINE 0x101D2CB0
// FUNCTION: ENGINE 0x101D2CC0
// FUNCTION: ENGINE 0x101D2CF0
// FUNCTION: ENGINE 0x101D2D10
// FUNCTION: ENGINE 0x101D2D20
// FUNCTION: ENGINE 0x101D2D50
// FUNCTION: ENGINE 0x101D2D80
// FUNCTION: ENGINE 0x101D2D90
// FUNCTION: ENGINE 0x101D2DC0
// FUNCTION: ENGINE 0x101D2DE0
// FUNCTION: ENGINE 0x101D2DF0
// FUNCTION: ENGINE 0x101D2E20
// FUNCTION: ENGINE 0x101D2E40
// FUNCTION: ENGINE 0x101D2E50
// FUNCTION: ENGINE 0x101D2E80
// FUNCTION: ENGINE 0x101D2EA0
// FUNCTION: ENGINE 0x101D2EB0
// FUNCTION: ENGINE 0x101D2EE0
// FUNCTION: ENGINE 0x101D2F00
// FUNCTION: ENGINE 0x101D2F30
// FUNCTION: ENGINE 0x101D2F60
// FUNCTION: ENGINE 0x101D2F70
// FUNCTION: ENGINE 0x101D2FB0
// FUNCTION: ENGINE 0x101D2FC0
// FUNCTION: ENGINE 0x101D2FF0
// FUNCTION: ENGINE 0x101D3010
// FUNCTION: ENGINE 0x101D3020
// FUNCTION: ENGINE 0x101D3050
// FUNCTION: ENGINE 0x101D3080
// FUNCTION: ENGINE 0x101D3090
// FUNCTION: ENGINE 0x101D30C0
// FUNCTION: ENGINE 0x101D30E0
// FUNCTION: ENGINE 0x101D30F0
// FUNCTION: ENGINE 0x101D3120
// FUNCTION: ENGINE 0x101D3140
// FUNCTION: ENGINE 0x101D3150
// FUNCTION: ENGINE 0x101D3180
// FUNCTION: ENGINE 0x101D31B0
// FUNCTION: ENGINE 0x101D31C0
// FUNCTION: ENGINE 0x101D31F0
// FUNCTION: ENGINE 0x101D3220
// FUNCTION: ENGINE 0x101D4460
// FUNCTION: ENGINE 0x101D4490
// FUNCTION: ENGINE 0x101D44B0
// FUNCTION: ENGINE 0x101D44E0
// FUNCTION: ENGINE 0x101D4500
// FUNCTION: ENGINE 0x101D4510
// FUNCTION: ENGINE 0x101D4540
// FUNCTION: ENGINE 0x101D4560
// FUNCTION: ENGINE 0x101D4570
// FUNCTION: ENGINE 0x101D45A0
// FUNCTION: ENGINE 0x101D45C0
// FUNCTION: ENGINE 0x101D45F0
// FUNCTION: ENGINE 0x101D4610
// FUNCTION: ENGINE 0x101D4620
// FUNCTION: ENGINE 0x101D4650
// FUNCTION: ENGINE 0x101D4670
// FUNCTION: ENGINE 0x101D46A0
// FUNCTION: ENGINE 0x101D46C0
// FUNCTION: ENGINE 0x101D46F0
// FUNCTION: ENGINE 0x101D4710
// FUNCTION: ENGINE 0x101D4740
// FUNCTION: ENGINE 0x101D4760
// FUNCTION: ENGINE 0x101D4790
// FUNCTION: ENGINE 0x101D47B0
// FUNCTION: ENGINE 0x101D47E0
// FUNCTION: ENGINE 0x101D4800
// FUNCTION: ENGINE 0x101D4830
// FUNCTION: ENGINE 0x101D4850
// FUNCTION: ENGINE 0x101D4880
// FUNCTION: ENGINE 0x101D5AD0
// FUNCTION: ENGINE 0x101D5B20
// FUNCTION: ENGINE 0x101D5B70
// FUNCTION: ENGINE 0x101D5BC0
// FUNCTION: ENGINE 0x101D5C10
// FUNCTION: ENGINE 0x101D5C60
// FUNCTION: ENGINE 0x101D5CB0
// FUNCTION: ENGINE 0x101D5D00
// FUNCTION: ENGINE 0x101D5D50
// FUNCTION: ENGINE 0x101D5D80
// FUNCTION: ENGINE 0x101D5DB0
// FUNCTION: ENGINE 0x101D5DE0
// FUNCTION: ENGINE 0x101D5E00
// FUNCTION: ENGINE 0x101D5E30
// FUNCTION: ENGINE 0x101D5E60
// FUNCTION: ENGINE 0x101D5EB0
// FUNCTION: ENGINE 0x101D5F00
