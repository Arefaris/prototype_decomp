// Fight items of the ai group: CanGunButtCondition, ReservePositionTrack, CommanderInCombatTrack, EngageTrack, ReserveHydraPositionTrack, ReserveGunButtTrack, ReserveTargetsPositionTrack (unit 0x1022D810 - 0x1022F8E0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_reserveposition.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gCanGunButtConditionProperties;  // 0x11255994

			// FUNCTION: ENGINE 0x1022DC30
			fight::Property* CanGunButtCondition::GetProperty(int index)
			{
				return gCanGunButtConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022DC50
			void CanGunButtCondition::ClearProperties()
			{
				fight::FreePropertyList(&gCanGunButtConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022DC60
			CanGunButtCondition::CanGunButtCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1022DC80
			CanGunButtCondition::~CanGunButtCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022DBD0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CanGunButtCondition::RegisterProperties()
			{
				if (gCanGunButtConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gCanGunButtConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022E880
			fight::ConditionFactory* CreateCanGunButtConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CanGunButtCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022F030
			void RegisterCanGunButtConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CanGunButtCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReservePositionTrackProperties;  // 0x11255998

			// FUNCTION: ENGINE 0x1022D810
			bool ReservePositionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D830
			bool ReservePositionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D850
			bool ReservePositionTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D870
			bool ReservePositionTrack::SetPosTolerance(float newValue)
			{
				posTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D890
			bool ReservePositionTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DC90
			fight::Property* ReservePositionTrack::GetProperty(int index)
			{
				return gReservePositionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1022DCB0
			void ReservePositionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReservePositionTrackProperties);
			}

			// FUNCTION: ENGINE 0x1022DCC0
			ReservePositionTrack::ReservePositionTrack() : offset(0.0f, 0.0f, 0.0f), posTolerance(1.0f), radius(2.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1022DD30
			float ReservePositionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1022DD40
			float ReservePositionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1022DD50
			ReservePositionTrack::~ReservePositionTrack()
			{
			}

			// FUNCTION: ENGINE 0x1022E9D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReservePositionTrack::RegisterProperties()
			{
				if (gReservePositionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReservePositionTrack>("timeBegin", &ReservePositionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReservePositionTrack>("timeEnd", &ReservePositionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReservePositionTrack>("radius", &ReservePositionTrack::SetRadius);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ReservePositionTrack>("posTolerance", &ReservePositionTrack::SetPosTolerance);
					properties[3] = property;
					property = new fight::PropertyVector<ReservePositionTrack>("offset", &ReservePositionTrack::SetOffset);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gReservePositionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022E8B0
			fight::TrackFactory* CreateReservePositionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReservePositionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022F060
			void RegisterReservePositionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReservePositionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCommanderInCombatTrackProperties;  // 0x1125599C

			// FUNCTION: ENGINE 0x1022D8B0
			bool CommanderInCombatTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D8D0
			bool CommanderInCombatTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DD60
			fight::Property* CommanderInCombatTrack::GetProperty(int index)
			{
				return gCommanderInCombatTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1022DD80
			void CommanderInCombatTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCommanderInCombatTrackProperties);
			}

			// FUNCTION: ENGINE 0x1022DD90
			CommanderInCombatTrack::CommanderInCombatTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1022DDD0
			float CommanderInCombatTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1022DDE0
			float CommanderInCombatTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1022DDF0
			CommanderInCombatTrack::~CommanderInCombatTrack()
			{
			}

			// FUNCTION: ENGINE 0x1022EB60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CommanderInCombatTrack::RegisterProperties()
			{
				if (gCommanderInCombatTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CommanderInCombatTrack>("timeBegin", &CommanderInCombatTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CommanderInCombatTrack>("timeEnd", &CommanderInCombatTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gCommanderInCombatTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022E8E0
			fight::TrackFactory* CreateCommanderInCombatTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CommanderInCombatTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022F090
			void RegisterCommanderInCombatTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CommanderInCombatTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gEngageTrackProperties;  // 0x112559A0

			// FUNCTION: ENGINE 0x1022D8F0
			bool EngageTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D910
			bool EngageTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D930
			bool EngageTrack::SetMinStopDistance(float newValue)
			{
				minStopDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D950
			bool EngageTrack::SetMaxStopDistance(float newValue)
			{
				maxStopDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D970
			bool EngageTrack::SetExtraMoveDistance(float newValue)
			{
				extraMoveDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D990
			bool EngageTrack::SetMinTimeInPosition(float newValue)
			{
				minTimeInPosition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D9B0
			bool EngageTrack::SetMaxTimeInPosition(float newValue)
			{
				maxTimeInPosition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D9D0
			bool EngageTrack::SetMaxTimeMelee(float newValue)
			{
				maxTimeMelee = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022D9F0
			bool EngageTrack::SetKneelingProbability(float newValue)
			{
				kneelingProbability = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DA10
			bool EngageTrack::SetMinSpeed(float newValue)
			{
				minSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DA30
			bool EngageTrack::SetMaxSpeed(float newValue)
			{
				maxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022E070
			bool EngageTrack::SetWeaponGrabSlot(const fight::Name& newValue)
			{
				weaponGrabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DE00
			fight::Property* EngageTrack::GetProperty(int index)
			{
				return gEngageTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1022DE20
			void EngageTrack::ClearProperties()
			{
				fight::FreePropertyList(&gEngageTrackProperties);
			}

			// FUNCTION: ENGINE 0x1022E120
			EngageTrack::EngageTrack() : extraMoveDistance(5.0f), kneelingProbability(0.2f), maxSpeed(1.0f), maxStopDistance(2e+01f), maxTimeInPosition(2e+01f), maxTimeMelee(5.0f), minSpeed(0.8f), minStopDistance(1e+01f), minTimeInPosition(1e+01f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1022E1D0
			float EngageTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1022E1E0
			float EngageTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1022E1F0
			EngageTrack::~EngageTrack()
			{
			}

			// FUNCTION: ENGINE 0x1022F370
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EngageTrack::RegisterProperties()
			{
				if (gEngageTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<EngageTrack>("timeBegin", &EngageTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("timeEnd", &EngageTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("minStopDistance", &EngageTrack::SetMinStopDistance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("maxStopDistance", &EngageTrack::SetMaxStopDistance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("extraMoveDistance", &EngageTrack::SetExtraMoveDistance);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("minTimeInPosition", &EngageTrack::SetMinTimeInPosition);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("maxTimeInPosition", &EngageTrack::SetMaxTimeInPosition);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("maxTimeMelee", &EngageTrack::SetMaxTimeMelee);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("kneelingProbability", &EngageTrack::SetKneelingProbability);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("minSpeed", &EngageTrack::SetMinSpeed);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<EngageTrack>("maxSpeed", &EngageTrack::SetMaxSpeed);
					properties[10] = property;
					property = new fight::PropertyNameList<EngageTrack>("weaponGrabSlot", &EngageTrack::SetWeaponGrabSlot);
					properties[11] = property;
					fight::RegisterPropertyList(properties, &gEngageTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022E910
			fight::TrackFactory* CreateEngageTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<EngageTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022F0C0
			void RegisterEngageTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<EngageTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReserveHydraPositionTrackProperties;  // 0x112559A4

			// FUNCTION: ENGINE 0x1022DA50
			bool ReserveHydraPositionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DA70
			bool ReserveHydraPositionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DA90
			bool ReserveHydraPositionTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DAB0
			bool ReserveHydraPositionTrack::SetPosTolerance(float newValue)
			{
				posTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DAD0
			bool ReserveHydraPositionTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DE30
			fight::Property* ReserveHydraPositionTrack::GetProperty(int index)
			{
				return gReserveHydraPositionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1022DE50
			void ReserveHydraPositionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReserveHydraPositionTrackProperties);
			}

			// FUNCTION: ENGINE 0x1022DE60
			ReserveHydraPositionTrack::ReserveHydraPositionTrack() : offset(0.0f, 0.0f, 0.0f), posTolerance(1.0f), radius(2.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1022DED0
			float ReserveHydraPositionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1022DEE0
			float ReserveHydraPositionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1022DEF0
			ReserveHydraPositionTrack::~ReserveHydraPositionTrack()
			{
			}

			// FUNCTION: ENGINE 0x1022EC40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReserveHydraPositionTrack::RegisterProperties()
			{
				if (gReserveHydraPositionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReserveHydraPositionTrack>("timeBegin", &ReserveHydraPositionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReserveHydraPositionTrack>("timeEnd", &ReserveHydraPositionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReserveHydraPositionTrack>("radius", &ReserveHydraPositionTrack::SetRadius);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ReserveHydraPositionTrack>("posTolerance", &ReserveHydraPositionTrack::SetPosTolerance);
					properties[3] = property;
					property = new fight::PropertyVector<ReserveHydraPositionTrack>("offset", &ReserveHydraPositionTrack::SetOffset);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gReserveHydraPositionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022E940
			fight::TrackFactory* CreateReserveHydraPositionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReserveHydraPositionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022F0F0
			void RegisterReserveHydraPositionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReserveHydraPositionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReserveGunButtTrackProperties;  // 0x112559A8

			// FUNCTION: ENGINE 0x1022DAF0
			bool ReserveGunButtTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DB10
			bool ReserveGunButtTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DB30
			bool ReserveGunButtTrack::SetReserveLength(float newValue)
			{
				reserveLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DF00
			fight::Property* ReserveGunButtTrack::GetProperty(int index)
			{
				return gReserveGunButtTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1022DF20
			void ReserveGunButtTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReserveGunButtTrackProperties);
			}

			// FUNCTION: ENGINE 0x1022DF30
			ReserveGunButtTrack::ReserveGunButtTrack() : reserveLength(2.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1022DF80
			float ReserveGunButtTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1022DF90
			float ReserveGunButtTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1022DFA0
			ReserveGunButtTrack::~ReserveGunButtTrack()
			{
			}

			// FUNCTION: ENGINE 0x1022EDD0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReserveGunButtTrack::RegisterProperties()
			{
				if (gReserveGunButtTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReserveGunButtTrack>("timeBegin", &ReserveGunButtTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReserveGunButtTrack>("timeEnd", &ReserveGunButtTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReserveGunButtTrack>("reserveLength", &ReserveGunButtTrack::SetReserveLength);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gReserveGunButtTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022E970
			fight::TrackFactory* CreateReserveGunButtTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReserveGunButtTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022F120
			void RegisterReserveGunButtTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReserveGunButtTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReserveTargetsPositionTrackProperties;  // 0x112559AC

			// FUNCTION: ENGINE 0x1022DB50
			bool ReserveTargetsPositionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DB70
			bool ReserveTargetsPositionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DB90
			bool ReserveTargetsPositionTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DBB0
			bool ReserveTargetsPositionTrack::SetPosTolerance(float newValue)
			{
				posTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022DFB0
			fight::Property* ReserveTargetsPositionTrack::GetProperty(int index)
			{
				return gReserveTargetsPositionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1022DFD0
			void ReserveTargetsPositionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReserveTargetsPositionTrackProperties);
			}

			// FUNCTION: ENGINE 0x1022DFE0
			ReserveTargetsPositionTrack::ReserveTargetsPositionTrack() : posTolerance(5.0f), radius(2.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1022E040
			float ReserveTargetsPositionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1022E050
			float ReserveTargetsPositionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1022E060
			ReserveTargetsPositionTrack::~ReserveTargetsPositionTrack()
			{
			}

			// FUNCTION: ENGINE 0x1022EEE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReserveTargetsPositionTrack::RegisterProperties()
			{
				if (gReserveTargetsPositionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReserveTargetsPositionTrack>("timeBegin", &ReserveTargetsPositionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReserveTargetsPositionTrack>("timeEnd", &ReserveTargetsPositionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReserveTargetsPositionTrack>("radius", &ReserveTargetsPositionTrack::SetRadius);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ReserveTargetsPositionTrack>("posTolerance", &ReserveTargetsPositionTrack::SetPosTolerance);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gReserveTargetsPositionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022E9A0
			fight::TrackFactory* CreateReserveTargetsPositionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReserveTargetsPositionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022F150
			void RegisterReserveTargetsPositionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReserveTargetsPositionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}


			// FUNCTION: ENGINE 0x101EDF30
			// EQUIVALENT: register allocation and scheduling (the engine loads the manager pointer before the target's handle, ours the other way round); the same calls with the same arguments (best 88.0 %)
			bool CanGunButtCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return true;
				}
				engine::GameObjectHandle target = proto::Unknown103B8B80(object);
				return proto::gAISystem->strafeRunTokens->Unknown103840E0(target);
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101EFC50
			CommanderInCombatAction::CommanderInCombatAction(CommanderInCombatTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101EE280
			CommanderInCombatAction::~CommanderInCombatAction()
			{
			}

			// FUNCTION: ENGINE 0x101ED7A0
			bool CommanderInCombatAction::Slot7(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101F0550
			fight::Action* CommanderInCombatTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CommanderInCombatAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101EFB20
			ReserveGunButtAction::ReserveGunButtAction(ReserveGunButtTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101EE230
			ReserveGunButtAction::~ReserveGunButtAction()
			{
			}

			// FUNCTION: ENGINE 0x101ED770
			void ReserveGunButtAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101ED760
			bool ReserveGunButtAction::Slot7(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101F0500
			fight::Action* ReserveGunButtTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ReserveGunButtAction(this, handle);
			}

			// ---- actions end
			template class fight::ConditionFactoryTemplate<CanGunButtCondition>;
			template class fight::ConditionFactoryCasterTemplate<CanGunButtCondition>;
			template class fight::PropertyFloatConstRange<ReservePositionTrack>;
			template class fight::PropertyVector<ReservePositionTrack>;
			template class fight::TrackFactoryTemplate<ReservePositionTrack>;
			template class fight::TrackFactoryCasterTemplate<ReservePositionTrack>;
			template class fight::PropertyFloatConstRange<CommanderInCombatTrack>;
			template class fight::TrackFactoryTemplate<CommanderInCombatTrack>;
			template class fight::TrackFactoryCasterTemplate<CommanderInCombatTrack>;
			template class fight::PropertyFloatConstRange<EngageTrack>;
			template class fight::PropertyNameList<EngageTrack>;
			template class fight::TrackFactoryTemplate<EngageTrack>;
			template class fight::TrackFactoryCasterTemplate<EngageTrack>;
			template class fight::PropertyFloatConstRange<ReserveHydraPositionTrack>;
			template class fight::PropertyVector<ReserveHydraPositionTrack>;
			template class fight::TrackFactoryTemplate<ReserveHydraPositionTrack>;
			template class fight::TrackFactoryCasterTemplate<ReserveHydraPositionTrack>;
			template class fight::PropertyFloatConstRange<ReserveGunButtTrack>;
			template class fight::TrackFactoryTemplate<ReserveGunButtTrack>;
			template class fight::TrackFactoryCasterTemplate<ReserveGunButtTrack>;
			template class fight::PropertyFloatConstRange<ReserveTargetsPositionTrack>;
			template class fight::TrackFactoryTemplate<ReserveTargetsPositionTrack>;
			template class fight::TrackFactoryCasterTemplate<ReserveTargetsPositionTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1022E090
// FUNCTION: ENGINE 0x1022E0C0
// FUNCTION: ENGINE 0x1022E0F0
// FUNCTION: ENGINE 0x1022E200
// FUNCTION: ENGINE 0x1022E230
// FUNCTION: ENGINE 0x1022E260
// FUNCTION: ENGINE 0x1022E290
// FUNCTION: ENGINE 0x1022E2A0
// FUNCTION: ENGINE 0x1022E2D0
// FUNCTION: ENGINE 0x1022E300
// FUNCTION: ENGINE 0x1022E320
// FUNCTION: ENGINE 0x1022E370
// FUNCTION: ENGINE 0x1022E380
// FUNCTION: ENGINE 0x1022E3B0
// FUNCTION: ENGINE 0x1022E3C0
// FUNCTION: ENGINE 0x1022E3F0
// FUNCTION: ENGINE 0x1022E400
// FUNCTION: ENGINE 0x1022E430
// FUNCTION: ENGINE 0x1022E440
// FUNCTION: ENGINE 0x1022E470
// FUNCTION: ENGINE 0x1022E480
// FUNCTION: ENGINE 0x1022E4B0
// FUNCTION: ENGINE 0x1022E4C0
// FUNCTION: ENGINE 0x1022E4F0
// FUNCTION: ENGINE 0x1022E520
// FUNCTION: ENGINE 0x1022E550
// FUNCTION: ENGINE 0x1022E580
// FUNCTION: ENGINE 0x1022E590
// FUNCTION: ENGINE 0x1022E5C0
// FUNCTION: ENGINE 0x1022E5E0
// FUNCTION: ENGINE 0x1022E5F0
// FUNCTION: ENGINE 0x1022E620
// FUNCTION: ENGINE 0x1022E650
// FUNCTION: ENGINE 0x1022E660
// FUNCTION: ENGINE 0x1022E690
// FUNCTION: ENGINE 0x1022E6C0
// FUNCTION: ENGINE 0x1022E6D0
// FUNCTION: ENGINE 0x1022E700
// FUNCTION: ENGINE 0x1022E730
// FUNCTION: ENGINE 0x1022E740
// FUNCTION: ENGINE 0x1022E770
// FUNCTION: ENGINE 0x1022E790
// FUNCTION: ENGINE 0x1022E7A0
// FUNCTION: ENGINE 0x1022E7D0
// FUNCTION: ENGINE 0x1022E800
// FUNCTION: ENGINE 0x1022E810
// FUNCTION: ENGINE 0x1022E840
// FUNCTION: ENGINE 0x1022E870
// FUNCTION: ENGINE 0x1022F180
// FUNCTION: ENGINE 0x1022F1B0
// FUNCTION: ENGINE 0x1022F1D0
// FUNCTION: ENGINE 0x1022F1E0
// FUNCTION: ENGINE 0x1022F210
// FUNCTION: ENGINE 0x1022F230
// FUNCTION: ENGINE 0x1022F260
// FUNCTION: ENGINE 0x1022F280
// FUNCTION: ENGINE 0x1022F2B0
// FUNCTION: ENGINE 0x1022F2D0
// FUNCTION: ENGINE 0x1022F300
// FUNCTION: ENGINE 0x1022F320
// FUNCTION: ENGINE 0x1022F350
// FUNCTION: ENGINE 0x1022F6B0
// FUNCTION: ENGINE 0x1022F700
// FUNCTION: ENGINE 0x1022F750
// FUNCTION: ENGINE 0x1022F7A0
// FUNCTION: ENGINE 0x1022F7F0
// FUNCTION: ENGINE 0x1022F840
// FUNCTION: ENGINE 0x1022F870
// FUNCTION: ENGINE 0x1022F890
