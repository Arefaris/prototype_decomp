// Fight items of the motion group: ConsumeGrabberTrack, ConsumeByParentTrack, NISConsumeByParentTrack, ScaleJointForConsumeTrack, ConsumeMeTrack, ConsumeTrack (unit 0x1014D220 - 0x1014F4D0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_consume.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gConsumeGrabberTrackProperties;  // 0x11254390

			// FUNCTION: ENGINE 0x1014D220
			bool ConsumeGrabberTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D240
			bool ConsumeGrabberTrack::SetStealthy(bool newValue)
			{
				stealthy = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D420
			fight::Property* ConsumeGrabberTrack::GetProperty(int index)
			{
				return gConsumeGrabberTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014D440
			void ConsumeGrabberTrack::ClearProperties()
			{
				fight::FreePropertyList(&gConsumeGrabberTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014D450
			ConsumeGrabberTrack::ConsumeGrabberTrack() : timeBegin(0.0f), stealthy(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1014D480
			float ConsumeGrabberTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1014D490
			float ConsumeGrabberTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1014D4A0
			ConsumeGrabberTrack::~ConsumeGrabberTrack()
			{
			}

			// FUNCTION: ENGINE 0x1014E200
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ConsumeGrabberTrack::RegisterProperties()
			{
				if (gConsumeGrabberTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ConsumeGrabberTrack>("timeBegin", &ConsumeGrabberTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<ConsumeGrabberTrack>("stealthy", &ConsumeGrabberTrack::SetStealthy);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gConsumeGrabberTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014E0E0
			fight::TrackFactory* CreateConsumeGrabberTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConsumeGrabberTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014E3C0
			void RegisterConsumeGrabberTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConsumeGrabberTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gConsumeByParentTrackProperties;  // 0x11254394

			// FUNCTION: ENGINE 0x1014D250
			bool ConsumeByParentTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D270
			bool ConsumeByParentTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D600
			bool ConsumeByParentTrack::SetRagdollIfNeeded(const fight::Name& newValue)
			{
				ragdollIfNeeded = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D290
			bool ConsumeByParentTrack::SetSwitchToRagdollMode(bool newValue)
			{
				switchToRagdollMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D620
			bool ConsumeByParentTrack::SetParentObjectName(const fight::Name& newValue)
			{
				parentObjectName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D640
			bool ConsumeByParentTrack::SetParentDestinationJoint(const fight::Name& newValue)
			{
				parentDestinationJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D2A0
			bool ConsumeByParentTrack::SetParentPositionOffset(const math::Vector& newValue)
			{
				parentPositionOffset.x = newValue.x;
				parentPositionOffset.y = newValue.y;
				parentPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D2C0
			bool ConsumeByParentTrack::SetConsumeUpwards(bool newValue)
			{
				consumeUpwards = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D2D0
			bool ConsumeByParentTrack::SetBoneSweepConstant(float newValue)
			{
				boneSweepConstant = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D2F0
			bool ConsumeByParentTrack::SetTransformationConsume(bool newValue)
			{
				transformationConsume = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D300
			bool ConsumeByParentTrack::SetTransformationConsumeTime(float newValue)
			{
				transformationConsumeTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D320
			bool ConsumeByParentTrack::SetStealthy(bool newValue)
			{
				stealthy = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D660
			bool ConsumeByParentTrack::SetConsumableProperties(const fight::Name& newValue)
			{
				consumableProperties = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D4B0
			fight::Property* ConsumeByParentTrack::GetProperty(int index)
			{
				return gConsumeByParentTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014D4D0
			void ConsumeByParentTrack::ClearProperties()
			{
				fight::FreePropertyList(&gConsumeByParentTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014D710
			ConsumeByParentTrack::ConsumeByParentTrack() : parentPositionOffset(0.0f, 0.0f, 0.0f), boneSweepConstant(1.0f), timeBegin(0.0f), timeEnd(-1.0f), transformationConsumeTime(0.0f), consumeUpwards(true), stealthy(false), switchToRagdollMode(true), transformationConsume(true)
			{
			}

			// FUNCTION: ENGINE 0x1014D7B0
			float ConsumeByParentTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1014D7C0
			float ConsumeByParentTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1014D7D0
			ConsumeByParentTrack::~ConsumeByParentTrack()
			{
			}

			// FUNCTION: ENGINE 0x1014E7A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ConsumeByParentTrack::RegisterProperties()
			{
				if (gConsumeByParentTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ConsumeByParentTrack>("timeBegin", &ConsumeByParentTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ConsumeByParentTrack>("timeEnd", &ConsumeByParentTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<ConsumeByParentTrack>("ragdollIfNeeded", &ConsumeByParentTrack::SetRagdollIfNeeded);
					properties[2] = property;
					property = new fight::PropertyBool<ConsumeByParentTrack>("switchToRagdollMode", &ConsumeByParentTrack::SetSwitchToRagdollMode);
					properties[3] = property;
					property = new fight::PropertyName<ConsumeByParentTrack>("parentObjectName", &ConsumeByParentTrack::SetParentObjectName);
					properties[4] = property;
					property = new fight::PropertyNameList<ConsumeByParentTrack>("parentDestinationJoint", &ConsumeByParentTrack::SetParentDestinationJoint);
					properties[5] = property;
					property = new fight::PropertyVector<ConsumeByParentTrack>("parentPositionOffset", &ConsumeByParentTrack::SetParentPositionOffset);
					properties[6] = property;
					property = new fight::PropertyBool<ConsumeByParentTrack>("consumeUpwards", &ConsumeByParentTrack::SetConsumeUpwards);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<ConsumeByParentTrack>("boneSweepConstant", &ConsumeByParentTrack::SetBoneSweepConstant);
					properties[8] = property;
					property = new fight::PropertyBool<ConsumeByParentTrack>("transformationConsume", &ConsumeByParentTrack::SetTransformationConsume);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<ConsumeByParentTrack>("transformationConsumeTime", &ConsumeByParentTrack::SetTransformationConsumeTime);
					properties[10] = property;
					property = new fight::PropertyBool<ConsumeByParentTrack>("stealthy", &ConsumeByParentTrack::SetStealthy);
					properties[11] = property;
					property = new fight::PropertyName<ConsumeByParentTrack>("consumableProperties", &ConsumeByParentTrack::SetConsumableProperties);
					properties[12] = property;
					fight::RegisterPropertyList(properties, &gConsumeByParentTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014E110
			fight::TrackFactory* CreateConsumeByParentTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConsumeByParentTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014E3F0
			void RegisterConsumeByParentTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConsumeByParentTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gNISConsumeByParentTrackProperties;  // 0x11254398

			// FUNCTION: ENGINE 0x1014D680
			bool NISConsumeByParentTrack::SetObject(const fight::Name& newValue)
			{
				object = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D330
			bool NISConsumeByParentTrack::SetToBeContinued(bool newValue)
			{
				toBeContinued = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D4E0
			fight::Property* NISConsumeByParentTrack::GetProperty(int index)
			{
				return gNISConsumeByParentTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014D500
			void NISConsumeByParentTrack::ClearProperties()
			{
				fight::FreePropertyList(&gNISConsumeByParentTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014D7E0
			NISConsumeByParentTrack::NISConsumeByParentTrack() : ConsumeByParentTrack(), toBeContinued(true)
			{
			}

			// FUNCTION: ENGINE 0x1014D810
			NISConsumeByParentTrack::~NISConsumeByParentTrack()
			{
			}

			// FUNCTION: ENGINE 0x1014EB20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void NISConsumeByParentTrack::RegisterProperties()
			{
				if (gNISConsumeByParentTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<NISConsumeByParentTrack>("object", &NISConsumeByParentTrack::SetObject);
					properties[0] = property;
					property = new fight::PropertyBool<NISConsumeByParentTrack>("toBeContinued", &NISConsumeByParentTrack::SetToBeContinued);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<NISConsumeByParentTrack>("timeBegin", &ConsumeByParentTrack::SetTimeBegin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<NISConsumeByParentTrack>("timeEnd", &ConsumeByParentTrack::SetTimeEnd);
					properties[3] = property;
					property = new fight::PropertyName<NISConsumeByParentTrack>("ragdollIfNeeded", &ConsumeByParentTrack::SetRagdollIfNeeded);
					properties[4] = property;
					property = new fight::PropertyBool<NISConsumeByParentTrack>("switchToRagdollMode", &ConsumeByParentTrack::SetSwitchToRagdollMode);
					properties[5] = property;
					property = new fight::PropertyName<NISConsumeByParentTrack>("parentObjectName", &ConsumeByParentTrack::SetParentObjectName);
					properties[6] = property;
					property = new fight::PropertyNameList<NISConsumeByParentTrack>("parentDestinationJoint", &ConsumeByParentTrack::SetParentDestinationJoint);
					properties[7] = property;
					property = new fight::PropertyVector<NISConsumeByParentTrack>("parentPositionOffset", &ConsumeByParentTrack::SetParentPositionOffset);
					properties[8] = property;
					property = new fight::PropertyBool<NISConsumeByParentTrack>("consumeUpwards", &ConsumeByParentTrack::SetConsumeUpwards);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<NISConsumeByParentTrack>("boneSweepConstant", &ConsumeByParentTrack::SetBoneSweepConstant);
					properties[10] = property;
					property = new fight::PropertyBool<NISConsumeByParentTrack>("transformationConsume", &ConsumeByParentTrack::SetTransformationConsume);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<NISConsumeByParentTrack>("transformationConsumeTime", &ConsumeByParentTrack::SetTransformationConsumeTime);
					properties[12] = property;
					property = new fight::PropertyBool<NISConsumeByParentTrack>("stealthy", &ConsumeByParentTrack::SetStealthy);
					properties[13] = property;
					property = new fight::PropertyName<NISConsumeByParentTrack>("consumableProperties", &ConsumeByParentTrack::SetConsumableProperties);
					properties[14] = property;
					fight::RegisterPropertyList(properties, &gNISConsumeByParentTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014E140
			fight::TrackFactory* CreateNISConsumeByParentTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<NISConsumeByParentTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014E420
			void RegisterNISConsumeByParentTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<NISConsumeByParentTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gScaleJointForConsumeTrackProperties;  // 0x1125439C

			// FUNCTION: ENGINE 0x1014D340
			bool ScaleJointForConsumeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D360
			bool ScaleJointForConsumeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D6A0
			bool ScaleJointForConsumeTrack::SetJointToScale(const fight::Name& newValue)
			{
				jointToScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D380
			bool ScaleJointForConsumeTrack::SetDesiredScale(float newValue)
			{
				desiredScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D3A0
			bool ScaleJointForConsumeTrack::SetScaleRate(float newValue)
			{
				scaleRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D510
			fight::Property* ScaleJointForConsumeTrack::GetProperty(int index)
			{
				return gScaleJointForConsumeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014D530
			void ScaleJointForConsumeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gScaleJointForConsumeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014D820
			ScaleJointForConsumeTrack::ScaleJointForConsumeTrack() : desiredScale(0.1f), scaleRate(1.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1014D890
			float ScaleJointForConsumeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1014D8A0
			float ScaleJointForConsumeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1014D8B0
			ScaleJointForConsumeTrack::~ScaleJointForConsumeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1014EF10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ScaleJointForConsumeTrack::RegisterProperties()
			{
				if (gScaleJointForConsumeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ScaleJointForConsumeTrack>("timeBegin", &ScaleJointForConsumeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ScaleJointForConsumeTrack>("timeEnd", &ScaleJointForConsumeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<ScaleJointForConsumeTrack>("jointToScale", &ScaleJointForConsumeTrack::SetJointToScale);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ScaleJointForConsumeTrack>("desiredScale", &ScaleJointForConsumeTrack::SetDesiredScale);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ScaleJointForConsumeTrack>("scaleRate", &ScaleJointForConsumeTrack::SetScaleRate);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gScaleJointForConsumeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014E170
			fight::TrackFactory* CreateScaleJointForConsumeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScaleJointForConsumeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014E450
			void RegisterScaleJointForConsumeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScaleJointForConsumeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gConsumeMeTrackProperties;  // 0x112543A0

			// FUNCTION: ENGINE 0x1014D3C0
			bool ConsumeMeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D3E0
			bool ConsumeMeTrack::SetStealthy(bool newValue)
			{
				stealthy = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D540
			fight::Property* ConsumeMeTrack::GetProperty(int index)
			{
				return gConsumeMeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014D560
			void ConsumeMeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gConsumeMeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014D570
			ConsumeMeTrack::ConsumeMeTrack() : timeBegin(0.0f), stealthy(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1014D5A0
			float ConsumeMeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1014D5B0
			float ConsumeMeTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1014D5C0
			ConsumeMeTrack::~ConsumeMeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1014E2E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ConsumeMeTrack::RegisterProperties()
			{
				if (gConsumeMeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ConsumeMeTrack>("timeBegin", &ConsumeMeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<ConsumeMeTrack>("stealthy", &ConsumeMeTrack::SetStealthy);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gConsumeMeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014E1A0
			fight::TrackFactory* CreateConsumeMeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConsumeMeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014E480
			void RegisterConsumeMeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConsumeMeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gConsumeTrackProperties;  // 0x112543A4

			// FUNCTION: ENGINE 0x1014D3F0
			bool ConsumeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D6C0
			bool ConsumeTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D410
			bool ConsumeTrack::SetStealthy(bool newValue)
			{
				stealthy = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014D5D0
			fight::Property* ConsumeTrack::GetProperty(int index)
			{
				return gConsumeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014D5F0
			void ConsumeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gConsumeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014D8F0
			ConsumeTrack::ConsumeTrack() : timeBegin(0.0f), stealthy(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1014D930
			float ConsumeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1014D940
			float ConsumeTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1014D950
			ConsumeTrack::~ConsumeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1014F0A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ConsumeTrack::RegisterProperties()
			{
				if (gConsumeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ConsumeTrack>("timeBegin", &ConsumeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<ConsumeTrack>("grabSlot", &ConsumeTrack::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyBool<ConsumeTrack>("stealthy", &ConsumeTrack::SetStealthy);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gConsumeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014E1D0
			fight::TrackFactory* CreateConsumeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConsumeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014E4B0
			void RegisterConsumeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConsumeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<ConsumeGrabberTrack>;
			template class fight::PropertyBool<ConsumeGrabberTrack>;
			template class fight::TrackFactoryTemplate<ConsumeGrabberTrack>;
			template class fight::TrackFactoryCasterTemplate<ConsumeGrabberTrack>;
			template class fight::PropertyFloatConstRange<ConsumeByParentTrack>;
			template class fight::PropertyName<ConsumeByParentTrack>;
			template class fight::PropertyBool<ConsumeByParentTrack>;
			template class fight::PropertyNameList<ConsumeByParentTrack>;
			template class fight::PropertyVector<ConsumeByParentTrack>;
			template class fight::TrackFactoryTemplate<ConsumeByParentTrack>;
			template class fight::TrackFactoryCasterTemplate<ConsumeByParentTrack>;
			template class fight::PropertyName<NISConsumeByParentTrack>;
			template class fight::PropertyBool<NISConsumeByParentTrack>;
			template class fight::PropertyFloatConstRange<NISConsumeByParentTrack>;
			template class fight::PropertyNameList<NISConsumeByParentTrack>;
			template class fight::PropertyVector<NISConsumeByParentTrack>;
			template class fight::TrackFactoryTemplate<NISConsumeByParentTrack>;
			template class fight::TrackFactoryCasterTemplate<NISConsumeByParentTrack>;
			template class fight::PropertyFloatConstRange<ScaleJointForConsumeTrack>;
			template class fight::PropertyNameList<ScaleJointForConsumeTrack>;
			template class fight::TrackFactoryTemplate<ScaleJointForConsumeTrack>;
			template class fight::TrackFactoryCasterTemplate<ScaleJointForConsumeTrack>;
			template class fight::PropertyFloatConstRange<ConsumeMeTrack>;
			template class fight::PropertyBool<ConsumeMeTrack>;
			template class fight::TrackFactoryTemplate<ConsumeMeTrack>;
			template class fight::TrackFactoryCasterTemplate<ConsumeMeTrack>;
			template class fight::PropertyFloatConstRange<ConsumeTrack>;
			template class fight::PropertyNameList<ConsumeTrack>;
			template class fight::PropertyBool<ConsumeTrack>;
			template class fight::TrackFactoryTemplate<ConsumeTrack>;
			template class fight::TrackFactoryCasterTemplate<ConsumeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1014D6E0
// FUNCTION: ENGINE 0x1014D8C0
// FUNCTION: ENGINE 0x1014D960
// FUNCTION: ENGINE 0x1014D970
// FUNCTION: ENGINE 0x1014D9A0
// FUNCTION: ENGINE 0x1014D9B0
// FUNCTION: ENGINE 0x1014D9E0
// FUNCTION: ENGINE 0x1014D9F0
// FUNCTION: ENGINE 0x1014DA20
// FUNCTION: ENGINE 0x1014DA30
// FUNCTION: ENGINE 0x1014DA60
// FUNCTION: ENGINE 0x1014DA70
// FUNCTION: ENGINE 0x1014DAA0
// FUNCTION: ENGINE 0x1014DAB0
// FUNCTION: ENGINE 0x1014DAE0
// FUNCTION: ENGINE 0x1014DB10
// FUNCTION: ENGINE 0x1014DB40
// FUNCTION: ENGINE 0x1014DB70
// FUNCTION: ENGINE 0x1014DBA0
// FUNCTION: ENGINE 0x1014DBD0
// FUNCTION: ENGINE 0x1014DC00
// FUNCTION: ENGINE 0x1014DC10
// FUNCTION: ENGINE 0x1014DC40
// FUNCTION: ENGINE 0x1014DC60
// FUNCTION: ENGINE 0x1014DC70
// FUNCTION: ENGINE 0x1014DCA0
// FUNCTION: ENGINE 0x1014DCD0
// FUNCTION: ENGINE 0x1014DCE0
// FUNCTION: ENGINE 0x1014DD10
// FUNCTION: ENGINE 0x1014DD30
// FUNCTION: ENGINE 0x1014DD40
// FUNCTION: ENGINE 0x1014DD70
// FUNCTION: ENGINE 0x1014DD90
// FUNCTION: ENGINE 0x1014DDA0
// FUNCTION: ENGINE 0x1014DDD0
// FUNCTION: ENGINE 0x1014DDF0
// FUNCTION: ENGINE 0x1014DE00
// FUNCTION: ENGINE 0x1014DE30
// FUNCTION: ENGINE 0x1014DE60
// FUNCTION: ENGINE 0x1014DE70
// FUNCTION: ENGINE 0x1014DEA0
// FUNCTION: ENGINE 0x1014DEC0
// FUNCTION: ENGINE 0x1014DED0
// FUNCTION: ENGINE 0x1014DF00
// FUNCTION: ENGINE 0x1014DF30
// FUNCTION: ENGINE 0x1014DF40
// FUNCTION: ENGINE 0x1014DF70
// FUNCTION: ENGINE 0x1014DFA0
// FUNCTION: ENGINE 0x1014DFB0
// FUNCTION: ENGINE 0x1014DFE0
// FUNCTION: ENGINE 0x1014E000
// FUNCTION: ENGINE 0x1014E010
// FUNCTION: ENGINE 0x1014E040
// FUNCTION: ENGINE 0x1014E070
// FUNCTION: ENGINE 0x1014E080
// FUNCTION: ENGINE 0x1014E0B0
// FUNCTION: ENGINE 0x1014E0D0
// FUNCTION: ENGINE 0x1014E4E0
// FUNCTION: ENGINE 0x1014E510
// FUNCTION: ENGINE 0x1014E530
// FUNCTION: ENGINE 0x1014E560
// FUNCTION: ENGINE 0x1014E580
// FUNCTION: ENGINE 0x1014E590
// FUNCTION: ENGINE 0x1014E5C0
// FUNCTION: ENGINE 0x1014E5E0
// FUNCTION: ENGINE 0x1014E610
// FUNCTION: ENGINE 0x1014E630
// FUNCTION: ENGINE 0x1014E640
// FUNCTION: ENGINE 0x1014E670
// FUNCTION: ENGINE 0x1014E690
// FUNCTION: ENGINE 0x1014E6A0
// FUNCTION: ENGINE 0x1014E6D0
// FUNCTION: ENGINE 0x1014E6F0
// FUNCTION: ENGINE 0x1014E700
// FUNCTION: ENGINE 0x1014E730
// FUNCTION: ENGINE 0x1014E750
// FUNCTION: ENGINE 0x1014E780
// FUNCTION: ENGINE 0x1014F1B0
// FUNCTION: ENGINE 0x1014F200
// FUNCTION: ENGINE 0x1014F250
// FUNCTION: ENGINE 0x1014F280
// FUNCTION: ENGINE 0x1014F2A0
// FUNCTION: ENGINE 0x1014F2D0
// FUNCTION: ENGINE 0x1014F2F0
// FUNCTION: ENGINE 0x1014F320
// FUNCTION: ENGINE 0x1014F340
// FUNCTION: ENGINE 0x1014F370
// FUNCTION: ENGINE 0x1014F390
// FUNCTION: ENGINE 0x1014F3E0
// FUNCTION: ENGINE 0x1014F430
// FUNCTION: ENGINE 0x1014F480
