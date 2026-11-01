// Fight items of the motion group: TransformationSlotActiveCondition, TransformationDesiredSensesCondition, ConsumptionNameCondition, TransformationSlotTransformDesiredCondition, TransformationConsumeDescriptionValidCondition, TransformationSlotValidCondition, TransformationAllowedCondition, TransformTrack, TransformationDisallowedTrack, TransformDesiredTrack, TransformCompleteTrack, TransformStartTrack, TransformationAllowedTrack, TransformFadeTrack (unit 0x101BF880 - 0x101C2D60; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_transformation.h"
#include "code/proto/fightitems/motion/motionmessages2.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gTransformationSlotActiveConditionProperties;  // 0x11254BB4

			// FUNCTION: ENGINE 0x101BFFC0
			bool TransformationSlotActiveCondition::SetSlotName(const fight::Name& newValue)
			{
				slotName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF880
			bool TransformationSlotActiveCondition::SetIsActive(bool newValue)
			{
				isActive = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFAD0
			fight::Property* TransformationSlotActiveCondition::GetProperty(int index)
			{
				return gTransformationSlotActiveConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFAF0
			void TransformationSlotActiveCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTransformationSlotActiveConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C00E0
			TransformationSlotActiveCondition::TransformationSlotActiveCondition() : fight::Condition(0), isActive(true)
			{
			}

			// FUNCTION: ENGINE 0x101C0110
			TransformationSlotActiveCondition::~TransformationSlotActiveCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C1F30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformationSlotActiveCondition::RegisterProperties()
			{
				if (gTransformationSlotActiveConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<TransformationSlotActiveCondition>("slotName", &TransformationSlotActiveCondition::SetSlotName);
					properties[0] = property;
					property = new fight::PropertyBool<TransformationSlotActiveCondition>("isActive", &TransformationSlotActiveCondition::SetIsActive);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTransformationSlotActiveConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C0FC0
			fight::ConditionFactory* CreateTransformationSlotActiveConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationSlotActiveCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1830
			void RegisterTransformationSlotActiveConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationSlotActiveCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTransformationDesiredSensesConditionProperties;  // 0x11254BB8

			// FUNCTION: ENGINE 0x101BF890
			bool TransformationDesiredSensesCondition::SetThermalVisionDesired(bool newValue)
			{
				thermalVisionDesired = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF8A0
			bool TransformationDesiredSensesCondition::SetInfectedVisionDesired(bool newValue)
			{
				infectedVisionDesired = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFB00
			fight::Property* TransformationDesiredSensesCondition::GetProperty(int index)
			{
				return gTransformationDesiredSensesConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFB20
			void TransformationDesiredSensesCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTransformationDesiredSensesConditionProperties);
			}

			// FUNCTION: ENGINE 0x101BFB30
			TransformationDesiredSensesCondition::TransformationDesiredSensesCondition() : fight::Condition(0), infectedVisionDesired(false), thermalVisionDesired(false)
			{
			}

			// FUNCTION: ENGINE 0x101BFB60
			TransformationDesiredSensesCondition::~TransformationDesiredSensesCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C1260
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformationDesiredSensesCondition::RegisterProperties()
			{
				if (gTransformationDesiredSensesConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TransformationDesiredSensesCondition>("thermalVisionDesired", &TransformationDesiredSensesCondition::SetThermalVisionDesired);
					properties[0] = property;
					property = new fight::PropertyBool<TransformationDesiredSensesCondition>("infectedVisionDesired", &TransformationDesiredSensesCondition::SetInfectedVisionDesired);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTransformationDesiredSensesConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C0FF0
			fight::ConditionFactory* CreateTransformationDesiredSensesConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationDesiredSensesCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1860
			void RegisterTransformationDesiredSensesConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationDesiredSensesCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gConsumptionNameConditionProperties;  // 0x11254BBC

			// FUNCTION: ENGINE 0x101BFFE0
			bool ConsumptionNameCondition::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF8B0
			bool ConsumptionNameCondition::SetIsActive(bool newValue)
			{
				isActive = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFB70
			fight::Property* ConsumptionNameCondition::GetProperty(int index)
			{
				return gConsumptionNameConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFB90
			void ConsumptionNameCondition::ClearProperties()
			{
				fight::FreePropertyList(&gConsumptionNameConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C0150
			ConsumptionNameCondition::ConsumptionNameCondition() : fight::Condition(0), isActive(true)
			{
			}

			// FUNCTION: ENGINE 0x101C0180
			ConsumptionNameCondition::~ConsumptionNameCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C2010
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ConsumptionNameCondition::RegisterProperties()
			{
				if (gConsumptionNameConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ConsumptionNameCondition>("name", &ConsumptionNameCondition::SetName);
					properties[0] = property;
					property = new fight::PropertyBool<ConsumptionNameCondition>("isActive", &ConsumptionNameCondition::SetIsActive);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gConsumptionNameConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C1020
			fight::ConditionFactory* CreateConsumptionNameConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ConsumptionNameCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1890
			void RegisterConsumptionNameConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ConsumptionNameCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTransformationSlotTransformDesiredConditionProperties;  // 0x11254BC0

			// FUNCTION: ENGINE 0x101C0000
			bool TransformationSlotTransformDesiredCondition::SetSlotName(const fight::Name& newValue)
			{
				slotName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF8C0
			bool TransformationSlotTransformDesiredCondition::SetTransformDesired(bool newValue)
			{
				transformDesired = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF8D0
			bool TransformationSlotTransformDesiredCondition::SetLoaded(bool newValue)
			{
				loaded = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF8E0
			bool TransformationSlotTransformDesiredCondition::SetLoading(bool newValue)
			{
				loading = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF8F0
			bool TransformationSlotTransformDesiredCondition::SetMatchName(bool newValue)
			{
				matchName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C0020
			bool TransformationSlotTransformDesiredCondition::SetDesiredName(const fight::Name& newValue)
			{
				desiredName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFBA0
			fight::Property* TransformationSlotTransformDesiredCondition::GetProperty(int index)
			{
				return gTransformationSlotTransformDesiredConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFBC0
			void TransformationSlotTransformDesiredCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTransformationSlotTransformDesiredConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C0190
			TransformationSlotTransformDesiredCondition::TransformationSlotTransformDesiredCondition() : fight::Condition(0), loaded(false), loading(false), matchName(false), transformDesired(true)
			{
			}

			// FUNCTION: ENGINE 0x101C01E0
			TransformationSlotTransformDesiredCondition::~TransformationSlotTransformDesiredCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C20F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformationSlotTransformDesiredCondition::RegisterProperties()
			{
				if (gTransformationSlotTransformDesiredConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<TransformationSlotTransformDesiredCondition>("slotName", &TransformationSlotTransformDesiredCondition::SetSlotName);
					properties[0] = property;
					property = new fight::PropertyBool<TransformationSlotTransformDesiredCondition>("transformDesired", &TransformationSlotTransformDesiredCondition::SetTransformDesired);
					properties[1] = property;
					property = new fight::PropertyBool<TransformationSlotTransformDesiredCondition>("loaded", &TransformationSlotTransformDesiredCondition::SetLoaded);
					properties[2] = property;
					property = new fight::PropertyBool<TransformationSlotTransformDesiredCondition>("loading", &TransformationSlotTransformDesiredCondition::SetLoading);
					properties[3] = property;
					property = new fight::PropertyBool<TransformationSlotTransformDesiredCondition>("matchName", &TransformationSlotTransformDesiredCondition::SetMatchName);
					properties[4] = property;
					property = new fight::PropertyName<TransformationSlotTransformDesiredCondition>("desiredName", &TransformationSlotTransformDesiredCondition::SetDesiredName);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gTransformationSlotTransformDesiredConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C1050
			fight::ConditionFactory* CreateTransformationSlotTransformDesiredConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationSlotTransformDesiredCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C18C0
			void RegisterTransformationSlotTransformDesiredConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationSlotTransformDesiredCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTransformationConsumeDescriptionValidConditionProperties;  // 0x11254BC4

			// FUNCTION: ENGINE 0x101BF900
			bool TransformationConsumeDescriptionValidCondition::SetIsValid(bool newValue)
			{
				isValid = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFBD0
			fight::Property* TransformationConsumeDescriptionValidCondition::GetProperty(int index)
			{
				return gTransformationConsumeDescriptionValidConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFBF0
			void TransformationConsumeDescriptionValidCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTransformationConsumeDescriptionValidConditionProperties);
			}

			// FUNCTION: ENGINE 0x101BFC00
			TransformationConsumeDescriptionValidCondition::TransformationConsumeDescriptionValidCondition() : fight::Condition(0), isValid(true)
			{
			}

			// FUNCTION: ENGINE 0x101BFC20
			TransformationConsumeDescriptionValidCondition::~TransformationConsumeDescriptionValidCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C1340
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformationConsumeDescriptionValidCondition::RegisterProperties()
			{
				if (gTransformationConsumeDescriptionValidConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TransformationConsumeDescriptionValidCondition>("isValid", &TransformationConsumeDescriptionValidCondition::SetIsValid);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTransformationConsumeDescriptionValidConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C1080
			fight::ConditionFactory* CreateTransformationConsumeDescriptionValidConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationConsumeDescriptionValidCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C18F0
			void RegisterTransformationConsumeDescriptionValidConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationConsumeDescriptionValidCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTransformationSlotValidConditionProperties;  // 0x11254BC8

			// FUNCTION: ENGINE 0x101C0040
			bool TransformationSlotValidCondition::SetSlotName(const fight::Name& newValue)
			{
				slotName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF910
			bool TransformationSlotValidCondition::SetIsValid(bool newValue)
			{
				isValid = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFC30
			fight::Property* TransformationSlotValidCondition::GetProperty(int index)
			{
				return gTransformationSlotValidConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFC50
			void TransformationSlotValidCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTransformationSlotValidConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C0220
			TransformationSlotValidCondition::TransformationSlotValidCondition() : fight::Condition(0), isValid(true)
			{
			}

			// FUNCTION: ENGINE 0x101C0250
			TransformationSlotValidCondition::~TransformationSlotValidCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C22C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformationSlotValidCondition::RegisterProperties()
			{
				if (gTransformationSlotValidConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<TransformationSlotValidCondition>("slotName", &TransformationSlotValidCondition::SetSlotName);
					properties[0] = property;
					property = new fight::PropertyBool<TransformationSlotValidCondition>("isValid", &TransformationSlotValidCondition::SetIsValid);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTransformationSlotValidConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C10B0
			fight::ConditionFactory* CreateTransformationSlotValidConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationSlotValidCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1920
			void RegisterTransformationSlotValidConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationSlotValidCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTransformationAllowedConditionProperties;  // 0x11254BCC

			// FUNCTION: ENGINE 0x101BF920
			bool TransformationAllowedCondition::SetAllowed(bool newValue)
			{
				allowed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFC60
			fight::Property* TransformationAllowedCondition::GetProperty(int index)
			{
				return gTransformationAllowedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFC80
			void TransformationAllowedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTransformationAllowedConditionProperties);
			}

			// FUNCTION: ENGINE 0x101BFC90
			TransformationAllowedCondition::TransformationAllowedCondition() : fight::Condition(0), allowed(true)
			{
			}

			// FUNCTION: ENGINE 0x101BFCB0
			TransformationAllowedCondition::~TransformationAllowedCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C13E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformationAllowedCondition::RegisterProperties()
			{
				if (gTransformationAllowedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TransformationAllowedCondition>("allowed", &TransformationAllowedCondition::SetAllowed);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTransformationAllowedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C10E0
			fight::ConditionFactory* CreateTransformationAllowedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationAllowedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1950
			void RegisterTransformationAllowedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationAllowedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTransformTrackProperties;  // 0x11254BD0

			// FUNCTION: ENGINE 0x101BF930
			bool TransformTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C0060
			bool TransformTrack::SetSlotName(const fight::Name& newValue)
			{
				slotName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF950
			bool TransformTrack::SetStealthy(bool newValue)
			{
				stealthy = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFCC0
			fight::Property* TransformTrack::GetProperty(int index)
			{
				return gTransformTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFCE0
			void TransformTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTransformTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C0290
			TransformTrack::TransformTrack() : timeBegin(0.0f), stealthy(false)
			{
			}

			// FUNCTION: ENGINE 0x101C02C0
			float TransformTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C02D0
			float TransformTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C02E0
			TransformTrack::~TransformTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C23A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformTrack::RegisterProperties()
			{
				if (gTransformTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TransformTrack>("timeBegin", &TransformTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<TransformTrack>("slotName", &TransformTrack::SetSlotName);
					properties[1] = property;
					property = new fight::PropertyBool<TransformTrack>("stealthy", &TransformTrack::SetStealthy);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gTransformTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C1110
			fight::TrackFactory* CreateTransformTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1980
			void RegisterTransformTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTransformationDisallowedTrackProperties;  // 0x11254BD4

			// FUNCTION: ENGINE 0x101BF960
			bool TransformationDisallowedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BF980
			bool TransformationDisallowedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFCF0
			fight::Property* TransformationDisallowedTrack::GetProperty(int index)
			{
				return gTransformationDisallowedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFD10
			void TransformationDisallowedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTransformationDisallowedTrackProperties);
			}

			// FUNCTION: ENGINE 0x101BFD20
			TransformationDisallowedTrack::TransformationDisallowedTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101BFD60
			float TransformationDisallowedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101BFD70
			float TransformationDisallowedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101BFD80
			TransformationDisallowedTrack::~TransformationDisallowedTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C1480
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformationDisallowedTrack::RegisterProperties()
			{
				if (gTransformationDisallowedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TransformationDisallowedTrack>("timeBegin", &TransformationDisallowedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TransformationDisallowedTrack>("timeEnd", &TransformationDisallowedTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTransformationDisallowedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C1140
			fight::TrackFactory* CreateTransformationDisallowedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformationDisallowedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C19B0
			void RegisterTransformationDisallowedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformationDisallowedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTransformDesiredTrackProperties;  // 0x11254BD8

			// FUNCTION: ENGINE 0x101BF9A0
			bool TransformDesiredTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C0080
			bool TransformDesiredTrack::SetSlotName(const fight::Name& newValue)
			{
				slotName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C00A0
			bool TransformDesiredTrack::SetTransformationDescription(const fight::Name& newValue)
			{
				transformationDescription = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFD90
			fight::Property* TransformDesiredTrack::GetProperty(int index)
			{
				return gTransformDesiredTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFDB0
			void TransformDesiredTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTransformDesiredTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C0320
			TransformDesiredTrack::TransformDesiredTrack() : timeBegin(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101C0360
			float TransformDesiredTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C0370
			float TransformDesiredTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C0380
			TransformDesiredTrack::~TransformDesiredTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C24B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformDesiredTrack::RegisterProperties()
			{
				if (gTransformDesiredTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TransformDesiredTrack>("timeBegin", &TransformDesiredTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<TransformDesiredTrack>("slotName", &TransformDesiredTrack::SetSlotName);
					properties[1] = property;
					property = new fight::PropertyName<TransformDesiredTrack>("transformationDescription", &TransformDesiredTrack::SetTransformationDescription);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gTransformDesiredTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C1170
			fight::TrackFactory* CreateTransformDesiredTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformDesiredTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C19E0
			void RegisterTransformDesiredTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformDesiredTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTransformCompleteTrackProperties;  // 0x11254BDC

			// FUNCTION: ENGINE 0x101BF9C0
			bool TransformCompleteTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFDC0
			fight::Property* TransformCompleteTrack::GetProperty(int index)
			{
				return gTransformCompleteTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFDE0
			void TransformCompleteTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTransformCompleteTrackProperties);
			}

			// FUNCTION: ENGINE 0x101BFDF0
			TransformCompleteTrack::TransformCompleteTrack() : timeBegin(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101BFE10
			float TransformCompleteTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101BFE20
			float TransformCompleteTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101BFE30
			TransformCompleteTrack::~TransformCompleteTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C1560
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformCompleteTrack::RegisterProperties()
			{
				if (gTransformCompleteTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TransformCompleteTrack>("timeBegin", &TransformCompleteTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTransformCompleteTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C11A0
			fight::TrackFactory* CreateTransformCompleteTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformCompleteTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1A10
			void RegisterTransformCompleteTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformCompleteTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTransformStartTrackProperties;  // 0x11254BE0

			// FUNCTION: ENGINE 0x101BF9E0
			bool TransformStartTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C00C0
			bool TransformStartTrack::SetSlotName(const fight::Name& newValue)
			{
				slotName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFA00
			bool TransformStartTrack::SetStealthy(bool newValue)
			{
				stealthy = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFE40
			fight::Property* TransformStartTrack::GetProperty(int index)
			{
				return gTransformStartTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFE60
			void TransformStartTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTransformStartTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C03C0
			TransformStartTrack::TransformStartTrack() : timeBegin(0.0f), stealthy(false)
			{
			}

			// FUNCTION: ENGINE 0x101C03F0
			float TransformStartTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C0400
			float TransformStartTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C0410
			TransformStartTrack::~TransformStartTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C25C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformStartTrack::RegisterProperties()
			{
				if (gTransformStartTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TransformStartTrack>("timeBegin", &TransformStartTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<TransformStartTrack>("slotName", &TransformStartTrack::SetSlotName);
					properties[1] = property;
					property = new fight::PropertyBool<TransformStartTrack>("stealthy", &TransformStartTrack::SetStealthy);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gTransformStartTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C11D0
			fight::TrackFactory* CreateTransformStartTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformStartTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1A40
			void RegisterTransformStartTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformStartTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTransformationAllowedTrackProperties;  // 0x11254BE4

			// FUNCTION: ENGINE 0x101BFA10
			bool TransformationAllowedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFA30
			bool TransformationAllowedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFE70
			fight::Property* TransformationAllowedTrack::GetProperty(int index)
			{
				return gTransformationAllowedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFE90
			void TransformationAllowedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTransformationAllowedTrackProperties);
			}

			// FUNCTION: ENGINE 0x101BFEA0
			TransformationAllowedTrack::TransformationAllowedTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101BFEE0
			float TransformationAllowedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101BFEF0
			float TransformationAllowedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101BFF00
			TransformationAllowedTrack::~TransformationAllowedTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C1600
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformationAllowedTrack::RegisterProperties()
			{
				if (gTransformationAllowedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TransformationAllowedTrack>("timeBegin", &TransformationAllowedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TransformationAllowedTrack>("timeEnd", &TransformationAllowedTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTransformationAllowedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C1200
			fight::TrackFactory* CreateTransformationAllowedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformationAllowedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1A70
			void RegisterTransformationAllowedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformationAllowedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTransformFadeTrackProperties;  // 0x11254BE8

			// FUNCTION: ENGINE 0x101BFA50
			bool TransformFadeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFA70
			bool TransformFadeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFA90
			bool TransformFadeTrack::SetFadeAtBegin(float newValue)
			{
				fadeAtBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFAB0
			bool TransformFadeTrack::SetFadeAtEnd(float newValue)
			{
				fadeAtEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BFF10
			fight::Property* TransformFadeTrack::GetProperty(int index)
			{
				return gTransformFadeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BFF30
			void TransformFadeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTransformFadeTrackProperties);
			}

			// FUNCTION: ENGINE 0x101BFF40
			TransformFadeTrack::TransformFadeTrack() : fadeAtBegin(0.0f), fadeAtEnd(1.0f), timeBegin(0.0f), timeEnd(1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101BFF90
			float TransformFadeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101BFFA0
			float TransformFadeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101BFFB0
			TransformFadeTrack::~TransformFadeTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C16E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformFadeTrack::RegisterProperties()
			{
				if (gTransformFadeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TransformFadeTrack>("timeBegin", &TransformFadeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TransformFadeTrack>("timeEnd", &TransformFadeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TransformFadeTrack>("fadeAtBegin", &TransformFadeTrack::SetFadeAtBegin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TransformFadeTrack>("fadeAtEnd", &TransformFadeTrack::SetFadeAtEnd);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gTransformFadeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C1230
			fight::TrackFactory* CreateTransformFadeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformFadeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C1AA0
			void RegisterTransformFadeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TransformFadeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10123210
			TransformationDisallowedAction::TransformationDisallowedAction(TransformationDisallowedTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x10122650
			TransformationDisallowedAction::~TransformationDisallowedAction()
			{
			}

			// FUNCTION: ENGINE 0x10123490
			fight::Action* TransformationDisallowedTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new TransformationDisallowedAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x10122FB0
			TransformCompleteAction::TransformCompleteAction(TransformCompleteTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x10122400
			TransformCompleteAction::~TransformCompleteAction()
			{
			}

			// FUNCTION: ENGINE 0x101233A0
			fight::Action* TransformCompleteTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new TransformCompleteAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x10123170
			TransformationAllowedAction::TransformationAllowedAction(TransformationAllowedTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x10122510
			TransformationAllowedAction::~TransformationAllowedAction()
			{
			}

			// FUNCTION: ENGINE 0x10123440
			fight::Action* TransformationAllowedTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new TransformationAllowedAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x10122A30
			TransformFadeAction::TransformFadeAction(TransformFadeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), link(newTrack), unknown2C(1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10122310
			TransformFadeAction::~TransformFadeAction()
			{
			}

			// FUNCTION: ENGINE 0x101232B0
			fight::Action* TransformFadeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new TransformFadeAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x10122CF0
			TransformAction::TransformAction(TransformTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x10122360
			TransformAction::~TransformAction()
			{
			}

			// FUNCTION: ENGINE 0x10123300
			fight::Action* TransformTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new TransformAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x10123050
			TransformDesiredAction::TransformDesiredAction(TransformDesiredTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x101224C0
			TransformDesiredAction::~TransformDesiredAction()
			{
			}

			// FUNCTION: ENGINE 0x101233F0
			fight::Action* TransformDesiredTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new TransformDesiredAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x10122E70
			TransformStartAction::TransformStartAction(TransformStartTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x101223B0
			TransformStartAction::~TransformStartAction()
			{
			}

			// FUNCTION: ENGINE 0x10123350
			fight::Action* TransformStartTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new TransformStartAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x10121B80
			bool ConsumptionNameCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				core::Name<core::CaseSensitiveKey> nameCopy(GetName());
				bool wanted = GetIsActive();
				GetTransformationSlotByDescriptionNameMessage message(nameCopy);
				object->SendMessage(&message);
				return wanted == message.active;
			}

			// FUNCTION: ENGINE 0x10121C60
			bool TransformationAllowedCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				GetTransformationAllowedMessage message;
				object->SendMessage(&message);
				return message.allowed == GetAllowed();
			}

			// FUNCTION: ENGINE 0x10121D10
			bool TransformationSlotActiveCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				core::Name<core::CaseSensitiveKey> nameCopy(GetSlotName());
				bool wanted = GetIsActive();
				GetTransformationSlotMessage message(nameCopy);
				object->SendMessage(&message);
				if (message.slot == 0)
				{
					return false;
				}
				return message.slot->active == wanted;
			}

			// FUNCTION: ENGINE 0x10122160
			bool TransformationConsumeDescriptionValidCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				bool wanted = GetIsValid();
				ConsumeTransformationDescriptionIsValidMessage message;
				object->SendMessage(&message);
				return message.valid == wanted;
			}

			// FUNCTION: ENGINE 0x10122210
			bool TransformationDesiredSensesCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				GetDesiredSensesPowerMessage message;
				object->SendMessage(&message);
				bool result = false;
				if (message.desired != message.current)
				{
					if (GetThermalVisionDesired() && message.desired == 10)
					{
						result = true;
					}
					if (GetInfectedVisionDesired() && message.desired == 11)
					{
						result = true;
					}
				}
				return result;
			}

			// FUNCTION: ENGINE 0x10122430
			bool TransformCompleteAction::Slot5(int arg, float value)
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					CompleteTransformationMessage message;
					object->SendMessage(&message);
				}
				return false;
			}

			// FUNCTION: ENGINE 0x10122540
			bool TransformationAllowedAction::Slot5(int arg, float value)
			{
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				TransformationAllowedMessage message(true);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x101225C0
			void TransformationAllowedAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					TransformationAllowedMessage message(false);
					object->SendMessage(&message);
				}
			}

			// FUNCTION: ENGINE 0x10122680
			bool TransformationDisallowedAction::Slot5(int arg, float value)
			{
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				TransformationAllowedMessage message(false);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x10122700
			void TransformationDisallowedAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					TransformationAllowedMessage message(true);
					object->SendMessage(&message);
				}
			}

			// FUNCTION: ENGINE 0x10122AE0
			bool TransformFadeAction::Slot5(int arg, float value)
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
				unknown2C = link.Get()->GetFadeAtBegin();
				engine::SetCloudFade message(unknown2C);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x10122B80
			// EQUIVALENT: scheduling: the engine loads the member into xmm0 before the message is built and adds the spilled quotient to it, ours loads the quotient first (the same sum) (70.1 %)
			bool TransformFadeAction::Slot7(int arg, float value)
			{
				TransformFadeTrack* track = link.Get();
				if (track == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				float fadeAtEnd = track->GetFadeAtEnd();
				float fadeAtBegin = track->GetFadeAtBegin();
				float step = (fadeAtEnd - fadeAtBegin) / track->Slot10() * value;
				unknown2C = unknown2C + step;
				engine::SetCloudFade message(unknown2C);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x10122C60
			void TransformFadeAction::Slot6()
			{
				if (link.Get() != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						engine::SetCloudFade message(link.Get()->GetFadeAtEnd());
						object->SendMessage(&message);
					}
				}
			}

			// FUNCTION: ENGINE 0x10122D90
			// EQUIVALENT: shrink-wrap and a duplicated epilogue (ebx and esi are saved behind the owner tests) (23.6 %)
			bool TransformAction::Slot5(int arg, float value)
			{
				if (link.Get() != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						StartTransformationMessage start(link.Get()->GetSlotName(), link.Get()->GetStealthy());
						object->SendMessage(&start);
						CompleteTransformationMessage complete;
						object->SendMessage(&complete);
					}
				}
				return false;
			}

			// FUNCTION: ENGINE 0x10122F10
			// EQUIVALENT: shrink-wrap and a duplicated epilogue (ebx and esi are saved behind the owner tests) (69.5 %)
			bool TransformStartAction::Slot5(int arg, float value)
			{
				if (link.Get() != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						StartTransformationMessage start(link.Get()->GetSlotName(), link.Get()->GetStealthy());
						object->SendMessage(&start);
					}
				}
				return false;
			}

			// FUNCTION: ENGINE 0x101230F0
			// EQUIVALENT: shrink-wrap and a duplicated epilogue (esi is saved behind the owner tests) (66.7 %)
			bool TransformDesiredAction::Slot5(int arg, float value)
			{
				if (link.Get() != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						SetDesiredTransformationMessage message(link.Get()->GetSlotName(), link.Get()->GetTransformationDescription(), false);
						object->SendMessage(&message);
					}
				}
				return false;
			}

			// ---- actions end
			template class fight::PropertyName<TransformationSlotActiveCondition>;
			template class fight::PropertyBool<TransformationSlotActiveCondition>;
			template class fight::ConditionFactoryTemplate<TransformationSlotActiveCondition>;
			template class fight::ConditionFactoryCasterTemplate<TransformationSlotActiveCondition>;
			template class fight::PropertyBool<TransformationDesiredSensesCondition>;
			template class fight::ConditionFactoryTemplate<TransformationDesiredSensesCondition>;
			template class fight::ConditionFactoryCasterTemplate<TransformationDesiredSensesCondition>;
			template class fight::PropertyName<ConsumptionNameCondition>;
			template class fight::PropertyBool<ConsumptionNameCondition>;
			template class fight::ConditionFactoryTemplate<ConsumptionNameCondition>;
			template class fight::ConditionFactoryCasterTemplate<ConsumptionNameCondition>;
			template class fight::PropertyName<TransformationSlotTransformDesiredCondition>;
			template class fight::PropertyBool<TransformationSlotTransformDesiredCondition>;
			template class fight::ConditionFactoryTemplate<TransformationSlotTransformDesiredCondition>;
			template class fight::ConditionFactoryCasterTemplate<TransformationSlotTransformDesiredCondition>;
			template class fight::PropertyBool<TransformationConsumeDescriptionValidCondition>;
			template class fight::ConditionFactoryTemplate<TransformationConsumeDescriptionValidCondition>;
			template class fight::ConditionFactoryCasterTemplate<TransformationConsumeDescriptionValidCondition>;
			template class fight::PropertyName<TransformationSlotValidCondition>;
			template class fight::PropertyBool<TransformationSlotValidCondition>;
			template class fight::ConditionFactoryTemplate<TransformationSlotValidCondition>;
			template class fight::ConditionFactoryCasterTemplate<TransformationSlotValidCondition>;
			template class fight::PropertyBool<TransformationAllowedCondition>;
			template class fight::ConditionFactoryTemplate<TransformationAllowedCondition>;
			template class fight::ConditionFactoryCasterTemplate<TransformationAllowedCondition>;
			template class fight::PropertyFloatConstRange<TransformTrack>;
			template class fight::PropertyName<TransformTrack>;
			template class fight::PropertyBool<TransformTrack>;
			template class fight::TrackFactoryTemplate<TransformTrack>;
			template class fight::TrackFactoryCasterTemplate<TransformTrack>;
			template class fight::PropertyFloatConstRange<TransformationDisallowedTrack>;
			template class fight::TrackFactoryTemplate<TransformationDisallowedTrack>;
			template class fight::TrackFactoryCasterTemplate<TransformationDisallowedTrack>;
			template class fight::PropertyFloatConstRange<TransformDesiredTrack>;
			template class fight::PropertyName<TransformDesiredTrack>;
			template class fight::TrackFactoryTemplate<TransformDesiredTrack>;
			template class fight::TrackFactoryCasterTemplate<TransformDesiredTrack>;
			template class fight::PropertyFloatConstRange<TransformCompleteTrack>;
			template class fight::TrackFactoryTemplate<TransformCompleteTrack>;
			template class fight::TrackFactoryCasterTemplate<TransformCompleteTrack>;
			template class fight::PropertyFloatConstRange<TransformStartTrack>;
			template class fight::PropertyName<TransformStartTrack>;
			template class fight::PropertyBool<TransformStartTrack>;
			template class fight::TrackFactoryTemplate<TransformStartTrack>;
			template class fight::TrackFactoryCasterTemplate<TransformStartTrack>;
			template class fight::PropertyFloatConstRange<TransformationAllowedTrack>;
			template class fight::TrackFactoryTemplate<TransformationAllowedTrack>;
			template class fight::TrackFactoryCasterTemplate<TransformationAllowedTrack>;
			template class fight::PropertyFloatConstRange<TransformFadeTrack>;
			template class fight::TrackFactoryTemplate<TransformFadeTrack>;
			template class fight::TrackFactoryCasterTemplate<TransformFadeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10121210
// FUNCTION: ENGINE 0x10121220
// FUNCTION: ENGINE 0x10121230
// FUNCTION: ENGINE 0x10121240
// FUNCTION: ENGINE 0x10121250
// FUNCTION: ENGINE 0x10121260
// FUNCTION: ENGINE 0x10121270
// FUNCTION: ENGINE 0x101212C0
// FUNCTION: ENGINE 0x101212D0
// FUNCTION: ENGINE 0x101212E0
// FUNCTION: ENGINE 0x10121300
// FUNCTION: ENGINE 0x10121310
// FUNCTION: ENGINE 0x10121320
// FUNCTION: ENGINE 0x10121360
// FUNCTION: ENGINE 0x10121370
// FUNCTION: ENGINE 0x10121380
// FUNCTION: ENGINE 0x10121390
// FUNCTION: ENGINE 0x101213C0
// FUNCTION: ENGINE 0x101213D0
// FUNCTION: ENGINE 0x10121400
// FUNCTION: ENGINE 0x10121410
// FUNCTION: ENGINE 0x10121440
// FUNCTION: ENGINE 0x10121450
// FUNCTION: ENGINE 0x10121480
// FUNCTION: ENGINE 0x10121490
// FUNCTION: ENGINE 0x101214C0
// FUNCTION: ENGINE 0x101214D0
// FUNCTION: ENGINE 0x10121510
// FUNCTION: ENGINE 0x10121520
// FUNCTION: ENGINE 0x10121530
// FUNCTION: ENGINE 0x10121540
// FUNCTION: ENGINE 0x10121550
// FUNCTION: ENGINE 0x10121560
// FUNCTION: ENGINE 0x101215A0
// FUNCTION: ENGINE 0x101215B0
// FUNCTION: ENGINE 0x10121610
// FUNCTION: ENGINE 0x10121620
// FUNCTION: ENGINE 0x10121670
// FUNCTION: ENGINE 0x10121680
// FUNCTION: ENGINE 0x101216B0
// FUNCTION: ENGINE 0x101216E0
// FUNCTION: ENGINE 0x10121710
// FUNCTION: ENGINE 0x10121740
// FUNCTION: ENGINE 0x10121770
// FUNCTION: ENGINE 0x101217A0
// FUNCTION: ENGINE 0x101217C0
// FUNCTION: ENGINE 0x101217E0
// FUNCTION: ENGINE 0x10121800
// FUNCTION: ENGINE 0x10121820
// FUNCTION: ENGINE 0x10121840
// FUNCTION: ENGINE 0x10121860
// FUNCTION: ENGINE 0x10121890
// FUNCTION: ENGINE 0x101218F0
// FUNCTION: ENGINE 0x10121950
// FUNCTION: ENGINE 0x101219A0
// FUNCTION: ENGINE 0x10121A00
// FUNCTION: ENGINE 0x10121A50
// FUNCTION: ENGINE 0x10121AA0
// FUNCTION: ENGINE 0x10121AF0
// FUNCTION: ENGINE 0x10121B20
// FUNCTION: ENGINE 0x10121B50
// FUNCTION: ENGINE 0x10122AB0
// FUNCTION: ENGINE 0x10122D60
// FUNCTION: ENGINE 0x10122EE0
// FUNCTION: ENGINE 0x10123020
// FUNCTION: ENGINE 0x101230C0
// FUNCTION: ENGINE 0x101231E0
// FUNCTION: ENGINE 0x10123280
// FUNCTION: ENGINE 0x101C0120
// FUNCTION: ENGINE 0x101C01F0
// FUNCTION: ENGINE 0x101C0260
// FUNCTION: ENGINE 0x101C02F0
// FUNCTION: ENGINE 0x101C0390
// FUNCTION: ENGINE 0x101C0420
// FUNCTION: ENGINE 0x101C0450
// FUNCTION: ENGINE 0x101C0480
// FUNCTION: ENGINE 0x101C0490
// FUNCTION: ENGINE 0x101C04C0
// FUNCTION: ENGINE 0x101C04D0
// FUNCTION: ENGINE 0x101C0500
// FUNCTION: ENGINE 0x101C0510
// FUNCTION: ENGINE 0x101C0540
// FUNCTION: ENGINE 0x101C0550
// FUNCTION: ENGINE 0x101C0580
// FUNCTION: ENGINE 0x101C0590
// FUNCTION: ENGINE 0x101C05C0
// FUNCTION: ENGINE 0x101C05D0
// FUNCTION: ENGINE 0x101C0600
// FUNCTION: ENGINE 0x101C0610
// FUNCTION: ENGINE 0x101C0640
// FUNCTION: ENGINE 0x101C0650
// FUNCTION: ENGINE 0x101C0680
// FUNCTION: ENGINE 0x101C0690
// FUNCTION: ENGINE 0x101C06C0
// FUNCTION: ENGINE 0x101C06D0
// FUNCTION: ENGINE 0x101C0700
// FUNCTION: ENGINE 0x101C0710
// FUNCTION: ENGINE 0x101C0740
// FUNCTION: ENGINE 0x101C0750
// FUNCTION: ENGINE 0x101C0780
// FUNCTION: ENGINE 0x101C0790
// FUNCTION: ENGINE 0x101C07C0
// FUNCTION: ENGINE 0x101C07D0
// FUNCTION: ENGINE 0x101C0800
// FUNCTION: ENGINE 0x101C0830
// FUNCTION: ENGINE 0x101C0860
// FUNCTION: ENGINE 0x101C0890
// FUNCTION: ENGINE 0x101C08C0
// FUNCTION: ENGINE 0x101C08F0
// FUNCTION: ENGINE 0x101C0920
// FUNCTION: ENGINE 0x101C0950
// FUNCTION: ENGINE 0x101C0980
// FUNCTION: ENGINE 0x101C09A0
// FUNCTION: ENGINE 0x101C09B0
// FUNCTION: ENGINE 0x101C09E0
// FUNCTION: ENGINE 0x101C0A00
// FUNCTION: ENGINE 0x101C0A10
// FUNCTION: ENGINE 0x101C0A40
// FUNCTION: ENGINE 0x101C0A60
// FUNCTION: ENGINE 0x101C0A70
// FUNCTION: ENGINE 0x101C0AA0
// FUNCTION: ENGINE 0x101C0AC0
// FUNCTION: ENGINE 0x101C0AD0
// FUNCTION: ENGINE 0x101C0B00
// FUNCTION: ENGINE 0x101C0B20
// FUNCTION: ENGINE 0x101C0B30
// FUNCTION: ENGINE 0x101C0B60
// FUNCTION: ENGINE 0x101C0B80
// FUNCTION: ENGINE 0x101C0B90
// FUNCTION: ENGINE 0x101C0BC0
// FUNCTION: ENGINE 0x101C0BE0
// FUNCTION: ENGINE 0x101C0BF0
// FUNCTION: ENGINE 0x101C0C20
// FUNCTION: ENGINE 0x101C0C50
// FUNCTION: ENGINE 0x101C0C60
// FUNCTION: ENGINE 0x101C0C90
// FUNCTION: ENGINE 0x101C0CB0
// FUNCTION: ENGINE 0x101C0CC0
// FUNCTION: ENGINE 0x101C0CF0
// FUNCTION: ENGINE 0x101C0D20
// FUNCTION: ENGINE 0x101C0D30
// FUNCTION: ENGINE 0x101C0D60
// FUNCTION: ENGINE 0x101C0D90
// FUNCTION: ENGINE 0x101C0DA0
// FUNCTION: ENGINE 0x101C0DD0
// FUNCTION: ENGINE 0x101C0E00
// FUNCTION: ENGINE 0x101C0E10
// FUNCTION: ENGINE 0x101C0E40
// FUNCTION: ENGINE 0x101C0E70
// FUNCTION: ENGINE 0x101C0E80
// FUNCTION: ENGINE 0x101C0EB0
// FUNCTION: ENGINE 0x101C0ED0
// FUNCTION: ENGINE 0x101C0EE0
// FUNCTION: ENGINE 0x101C0F10
// FUNCTION: ENGINE 0x101C0F40
// FUNCTION: ENGINE 0x101C0F50
// FUNCTION: ENGINE 0x101C0F80
// FUNCTION: ENGINE 0x101C0FB0
// FUNCTION: ENGINE 0x101C1AD0
// FUNCTION: ENGINE 0x101C1B00
// FUNCTION: ENGINE 0x101C1B20
// FUNCTION: ENGINE 0x101C1B50
// FUNCTION: ENGINE 0x101C1B70
// FUNCTION: ENGINE 0x101C1BA0
// FUNCTION: ENGINE 0x101C1BC0
// FUNCTION: ENGINE 0x101C1BF0
// FUNCTION: ENGINE 0x101C1C10
// FUNCTION: ENGINE 0x101C1C40
// FUNCTION: ENGINE 0x101C1C60
// FUNCTION: ENGINE 0x101C1C90
// FUNCTION: ENGINE 0x101C1CB0
// FUNCTION: ENGINE 0x101C1CE0
// FUNCTION: ENGINE 0x101C1D00
// FUNCTION: ENGINE 0x101C1D30
// FUNCTION: ENGINE 0x101C1D50
// FUNCTION: ENGINE 0x101C1D80
// FUNCTION: ENGINE 0x101C1DA0
// FUNCTION: ENGINE 0x101C1DD0
// FUNCTION: ENGINE 0x101C1DF0
// FUNCTION: ENGINE 0x101C1E20
// FUNCTION: ENGINE 0x101C1E40
// FUNCTION: ENGINE 0x101C1E70
// FUNCTION: ENGINE 0x101C1E90
// FUNCTION: ENGINE 0x101C1EC0
// FUNCTION: ENGINE 0x101C1EE0
// FUNCTION: ENGINE 0x101C1F10
// FUNCTION: ENGINE 0x101C26D0
// FUNCTION: ENGINE 0x101C2720
// FUNCTION: ENGINE 0x101C2770
// FUNCTION: ENGINE 0x101C27C0
// FUNCTION: ENGINE 0x101C2810
// FUNCTION: ENGINE 0x101C2860
// FUNCTION: ENGINE 0x101C28B0
// FUNCTION: ENGINE 0x101C2900
// FUNCTION: ENGINE 0x101C2930
// FUNCTION: ENGINE 0x101C2950
// FUNCTION: ENGINE 0x101C2980
// FUNCTION: ENGINE 0x101C29A0
// FUNCTION: ENGINE 0x101C29D0
// FUNCTION: ENGINE 0x101C29F0
// FUNCTION: ENGINE 0x101C2A20
// FUNCTION: ENGINE 0x101C2A40
// FUNCTION: ENGINE 0x101C2A70
// FUNCTION: ENGINE 0x101C2A90
// FUNCTION: ENGINE 0x101C2AC0
// FUNCTION: ENGINE 0x101C2AE0
// FUNCTION: ENGINE 0x101C2B10
// FUNCTION: ENGINE 0x101C2B30
// FUNCTION: ENGINE 0x101C2B80
// FUNCTION: ENGINE 0x101C2BD0
// FUNCTION: ENGINE 0x101C2C20
// FUNCTION: ENGINE 0x101C2C70
// FUNCTION: ENGINE 0x101C2CC0
// FUNCTION: ENGINE 0x101C2D10
