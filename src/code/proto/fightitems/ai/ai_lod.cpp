// Fight items of the ai group: CanReserveSoldierBudgetCondition, IsInLoadedCellCondition, NPCLODCondition, LodSteerTrack, ResetPhysicVelocitiesTrack, LodMoveTrack, EnableLODPatrolTrack, GameObjectOrientTrack, CharacterizeTrack, CharacterizeFromReservedTrack, SetNPCLODStateTrack, LodGotoFixedDestinationTrack, UnDowngradableTrack, UpdateSoldierReservationBudgetTrack (unit 0x10236270 - 0x10239F70; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_lod.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gCanReserveSoldierBudgetConditionProperties;  // 0x11255A2C

			// FUNCTION: ENGINE 0x10236270
			bool CanReserveSoldierBudgetCondition::SetSoldiers(int newValue)
			{
				soldiers = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236710
			fight::Property* CanReserveSoldierBudgetCondition::GetProperty(int index)
			{
				return gCanReserveSoldierBudgetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10236730
			void CanReserveSoldierBudgetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gCanReserveSoldierBudgetConditionProperties);
			}

			// FUNCTION: ENGINE 0x10236740
			CanReserveSoldierBudgetCondition::CanReserveSoldierBudgetCondition() : fight::Condition(0), soldiers(0)
			{
			}

			// FUNCTION: ENGINE 0x10236770
			CanReserveSoldierBudgetCondition::~CanReserveSoldierBudgetCondition()
			{
			}

			// FUNCTION: ENGINE 0x10238350
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CanReserveSoldierBudgetCondition::RegisterProperties()
			{
				if (gCanReserveSoldierBudgetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyIntConstRange<CanReserveSoldierBudgetCondition>("soldiers", &CanReserveSoldierBudgetCondition::SetSoldiers);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gCanReserveSoldierBudgetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102380B0
			fight::ConditionFactory* CreateCanReserveSoldierBudgetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CanReserveSoldierBudgetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102391D0
			void RegisterCanReserveSoldierBudgetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CanReserveSoldierBudgetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gIsInLoadedCellConditionProperties;  // 0x11255A30

			// FUNCTION: ENGINE 0x102367E0
			fight::Property* IsInLoadedCellCondition::GetProperty(int index)
			{
				return gIsInLoadedCellConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10236800
			void IsInLoadedCellCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsInLoadedCellConditionProperties);
			}

			// FUNCTION: ENGINE 0x10236810
			IsInLoadedCellCondition::IsInLoadedCellCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10236830
			IsInLoadedCellCondition::~IsInLoadedCellCondition()
			{
			}

			// FUNCTION: ENGINE 0x10236780
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsInLoadedCellCondition::RegisterProperties()
			{
				if (gIsInLoadedCellConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gIsInLoadedCellConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102380E0
			fight::ConditionFactory* CreateIsInLoadedCellConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsInLoadedCellCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10239200
			void RegisterIsInLoadedCellConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsInLoadedCellCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gNPCLODConditionProperties;  // 0x11255A34

			// FUNCTION: ENGINE 0x10236280
			bool NPCLODCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236290
			bool NPCLODCondition::SetValue(int newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236840
			fight::Property* NPCLODCondition::GetProperty(int index)
			{
				return gNPCLODConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10236860
			void NPCLODCondition::ClearProperties()
			{
				fight::FreePropertyList(&gNPCLODConditionProperties);
			}

			// FUNCTION: ENGINE 0x10236870
			NPCLODCondition::NPCLODCondition() : fight::Condition(0), compare(0), value(0)
			{
			}

			// FUNCTION: ENGINE 0x102368A0
			NPCLODCondition::~NPCLODCondition()
			{
			}

			// FUNCTION: ENGINE 0x102383F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void NPCLODCondition::RegisterProperties()
			{
				if (gNPCLODConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<NPCLODCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &NPCLODCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<NPCLODCondition>("value", gNPCLODConditionValueTable, gNPCLODConditionValueCount, &NPCLODCondition::SetValue);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gNPCLODConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10238110
			fight::ConditionFactory* CreateNPCLODConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<NPCLODCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10239230
			void RegisterNPCLODConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<NPCLODCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gLodSteerTrackProperties;  // 0x11255A38

			// FUNCTION: ENGINE 0x102362A0
			bool LodSteerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102362C0
			bool LodSteerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102362E0
			bool LodSteerTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236300
			bool LodSteerTrack::SetWalkanim(int newValue)
			{
				walkanim = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236310
			bool LodSteerTrack::SetIdleanim(int newValue)
			{
				idleanim = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102368B0
			fight::Property* LodSteerTrack::GetProperty(int index)
			{
				return gLodSteerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102368D0
			void LodSteerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLodSteerTrackProperties);
			}

			// FUNCTION: ENGINE 0x102368E0
			LodSteerTrack::LodSteerTrack() : speed(1.0f), timeBegin(0.0f), timeEnd(-1.0f), idleanim(0), walkanim(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10236940
			float LodSteerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10236950
			float LodSteerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10236960
			LodSteerTrack::~LodSteerTrack()
			{
			}

			// FUNCTION: ENGINE 0x102384F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LodSteerTrack::RegisterProperties()
			{
				if (gLodSteerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LodSteerTrack>("timeBegin", &LodSteerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LodSteerTrack>("timeEnd", &LodSteerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LodSteerTrack>("speed", &LodSteerTrack::SetSpeed);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<LodSteerTrack>("walk_anim", gLodSteerTrackWalkanimTable, gLodSteerTrackWalkanimCount, &LodSteerTrack::SetWalkanim);
					properties[3] = property;
					property = new fight::PropertyEnumConstList<LodSteerTrack>("idle_anim", gLodSteerTrackWalkanimTable, gLodSteerTrackWalkanimCount, &LodSteerTrack::SetIdleanim);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gLodSteerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10238140
			fight::TrackFactory* CreateLodSteerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LodSteerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10239260
			void RegisterLodSteerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LodSteerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gResetPhysicVelocitiesTrackProperties;  // 0x11255A3C

			// FUNCTION: ENGINE 0x10236320
			bool ResetPhysicVelocitiesTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236340
			bool ResetPhysicVelocitiesTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236970
			fight::Property* ResetPhysicVelocitiesTrack::GetProperty(int index)
			{
				return gResetPhysicVelocitiesTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236990
			void ResetPhysicVelocitiesTrack::ClearProperties()
			{
				fight::FreePropertyList(&gResetPhysicVelocitiesTrackProperties);
			}

			// FUNCTION: ENGINE 0x102369A0
			ResetPhysicVelocitiesTrack::ResetPhysicVelocitiesTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x102369E0
			float ResetPhysicVelocitiesTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x102369F0
			float ResetPhysicVelocitiesTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10236A00
			ResetPhysicVelocitiesTrack::~ResetPhysicVelocitiesTrack()
			{
			}

			// FUNCTION: ENGINE 0x102386B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ResetPhysicVelocitiesTrack::RegisterProperties()
			{
				if (gResetPhysicVelocitiesTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ResetPhysicVelocitiesTrack>("timeBegin", &ResetPhysicVelocitiesTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ResetPhysicVelocitiesTrack>("timeEnd", &ResetPhysicVelocitiesTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gResetPhysicVelocitiesTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10238170
			fight::TrackFactory* CreateResetPhysicVelocitiesTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ResetPhysicVelocitiesTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10239290
			void RegisterResetPhysicVelocitiesTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ResetPhysicVelocitiesTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gLodMoveTrackProperties;  // 0x11255A40

			// FUNCTION: ENGINE 0x10236360
			bool LodMoveTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236380
			bool LodMoveTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102363A0
			bool LodMoveTrack::SetWalkanim(int newValue)
			{
				walkanim = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102363B0
			bool LodMoveTrack::SetIdleanim(int newValue)
			{
				idleanim = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236A10
			fight::Property* LodMoveTrack::GetProperty(int index)
			{
				return gLodMoveTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236A30
			void LodMoveTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLodMoveTrackProperties);
			}

			// FUNCTION: ENGINE 0x10236A40
			LodMoveTrack::LodMoveTrack() : timeBegin(0.0f), timeEnd(-1.0f), idleanim(0), walkanim(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10236A90
			float LodMoveTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10236AA0
			float LodMoveTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10236AB0
			LodMoveTrack::~LodMoveTrack()
			{
			}

			// FUNCTION: ENGINE 0x10238790
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LodMoveTrack::RegisterProperties()
			{
				if (gLodMoveTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LodMoveTrack>("timeBegin", &LodMoveTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LodMoveTrack>("timeEnd", &LodMoveTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<LodMoveTrack>("walk_anim", gLodSteerTrackWalkanimTable, gLodSteerTrackWalkanimCount, &LodMoveTrack::SetWalkanim);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<LodMoveTrack>("idle_anim", gLodSteerTrackWalkanimTable, gLodSteerTrackWalkanimCount, &LodMoveTrack::SetIdleanim);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gLodMoveTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102381A0
			fight::TrackFactory* CreateLodMoveTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LodMoveTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102392C0
			void RegisterLodMoveTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LodMoveTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gEnableLODPatrolTrackProperties;  // 0x11255A44

			// FUNCTION: ENGINE 0x102363C0
			bool EnableLODPatrolTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102363E0
			bool EnableLODPatrolTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236400
			bool EnableLODPatrolTrack::SetActionOnBegin(int newValue)
			{
				actionOnBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236410
			bool EnableLODPatrolTrack::SetActionOnEnd(int newValue)
			{
				actionOnEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236AC0
			fight::Property* EnableLODPatrolTrack::GetProperty(int index)
			{
				return gEnableLODPatrolTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236AE0
			void EnableLODPatrolTrack::ClearProperties()
			{
				fight::FreePropertyList(&gEnableLODPatrolTrackProperties);
			}

			// FUNCTION: ENGINE 0x10236AF0
			EnableLODPatrolTrack::EnableLODPatrolTrack() : timeBegin(0.0f), timeEnd(-1.0f), actionOnBegin(0), actionOnEnd(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10236B40
			float EnableLODPatrolTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10236B50
			float EnableLODPatrolTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10236B60
			EnableLODPatrolTrack::~EnableLODPatrolTrack()
			{
			}

			// FUNCTION: ENGINE 0x10238910
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EnableLODPatrolTrack::RegisterProperties()
			{
				if (gEnableLODPatrolTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<EnableLODPatrolTrack>("timeBegin", &EnableLODPatrolTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<EnableLODPatrolTrack>("timeEnd", &EnableLODPatrolTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<EnableLODPatrolTrack>("actionOnBegin", gEnableLODPatrolTrackActionOnBeginTable, gEnableLODPatrolTrackActionOnBeginCount, &EnableLODPatrolTrack::SetActionOnBegin);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<EnableLODPatrolTrack>("actionOnEnd", gEnableLODPatrolTrackActionOnEndTable, gEnableLODPatrolTrackActionOnEndCount, &EnableLODPatrolTrack::SetActionOnEnd);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gEnableLODPatrolTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102381D0
			fight::TrackFactory* CreateEnableLODPatrolTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<EnableLODPatrolTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102392F0
			void RegisterEnableLODPatrolTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<EnableLODPatrolTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGameObjectOrientTrackProperties;  // 0x11255A48

			// FUNCTION: ENGINE 0x10236420
			bool GameObjectOrientTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236440
			bool GameObjectOrientTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236460
			bool GameObjectOrientTrack::SetMaxTurnYaw(float newValue)
			{
				maxTurnYaw = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10236480
			bool GameObjectOrientTrack::SetMaxTurnPitch(float newValue)
			{
				maxTurnPitch = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x102364A0
			bool GameObjectOrientTrack::SetYaw(bool newValue)
			{
				yaw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102364B0
			bool GameObjectOrientTrack::SetPitch(bool newValue)
			{
				pitch = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102364C0
			bool GameObjectOrientTrack::SetResetIfNotSetting(bool newValue)
			{
				resetIfNotSetting = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236B70
			fight::Property* GameObjectOrientTrack::GetProperty(int index)
			{
				return gGameObjectOrientTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236B90
			void GameObjectOrientTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGameObjectOrientTrackProperties);
			}

			// FUNCTION: ENGINE 0x10236BA0
			GameObjectOrientTrack::GameObjectOrientTrack() : maxTurnPitch(6.2831855f), maxTurnYaw(6.2831855f), timeBegin(0.0f), timeEnd(-1.0f), pitch(true), resetIfNotSetting(true), yaw(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10236C00
			float GameObjectOrientTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10236C10
			float GameObjectOrientTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10236C20
			GameObjectOrientTrack::~GameObjectOrientTrack()
			{
			}

			// FUNCTION: ENGINE 0x10238A90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GameObjectOrientTrack::RegisterProperties()
			{
				if (gGameObjectOrientTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GameObjectOrientTrack>("timeBegin", &GameObjectOrientTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GameObjectOrientTrack>("timeEnd", &GameObjectOrientTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GameObjectOrientTrack>("maxTurnYaw", &GameObjectOrientTrack::SetMaxTurnYaw);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<GameObjectOrientTrack>("maxTurnPitch", &GameObjectOrientTrack::SetMaxTurnPitch);
					properties[3] = property;
					property = new fight::PropertyBool<GameObjectOrientTrack>("yaw", &GameObjectOrientTrack::SetYaw);
					properties[4] = property;
					property = new fight::PropertyBool<GameObjectOrientTrack>("pitch", &GameObjectOrientTrack::SetPitch);
					properties[5] = property;
					property = new fight::PropertyBool<GameObjectOrientTrack>("resetIfNotSetting", &GameObjectOrientTrack::SetResetIfNotSetting);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gGameObjectOrientTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10238200
			fight::TrackFactory* CreateGameObjectOrientTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GameObjectOrientTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10239320
			void RegisterGameObjectOrientTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GameObjectOrientTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCharacterizeTrackProperties;  // 0x11255A4C

			// FUNCTION: ENGINE 0x102364D0
			bool CharacterizeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102364F0
			bool CharacterizeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236F50
			bool CharacterizeTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236C30
			fight::Property* CharacterizeTrack::GetProperty(int index)
			{
				return gCharacterizeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236C50
			void CharacterizeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCharacterizeTrackProperties);
			}

			// FUNCTION: ENGINE 0x10237110
			CharacterizeTrack::CharacterizeTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10237160
			float CharacterizeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10237170
			float CharacterizeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10237180
			CharacterizeTrack::~CharacterizeTrack()
			{
			}

			// FUNCTION: ENGINE 0x102398A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CharacterizeTrack::RegisterProperties()
			{
				if (gCharacterizeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CharacterizeTrack>("timeBegin", &CharacterizeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CharacterizeTrack>("timeEnd", &CharacterizeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<CharacterizeTrack>("grabSlot", &CharacterizeTrack::SetGrabSlot);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gCharacterizeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10238230
			fight::TrackFactory* CreateCharacterizeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CharacterizeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10239350
			void RegisterCharacterizeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CharacterizeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCharacterizeFromReservedTrackProperties;  // 0x11255A50

			// FUNCTION: ENGINE 0x10236510
			bool CharacterizeFromReservedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236530
			bool CharacterizeFromReservedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236F70
			bool CharacterizeFromReservedTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236C60
			fight::Property* CharacterizeFromReservedTrack::GetProperty(int index)
			{
				return gCharacterizeFromReservedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236C80
			void CharacterizeFromReservedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCharacterizeFromReservedTrackProperties);
			}

			// FUNCTION: ENGINE 0x10237190
			CharacterizeFromReservedTrack::CharacterizeFromReservedTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x102371E0
			float CharacterizeFromReservedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x102371F0
			float CharacterizeFromReservedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10237200
			CharacterizeFromReservedTrack::~CharacterizeFromReservedTrack()
			{
			}

			// FUNCTION: ENGINE 0x102399B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CharacterizeFromReservedTrack::RegisterProperties()
			{
				if (gCharacterizeFromReservedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CharacterizeFromReservedTrack>("timeBegin", &CharacterizeFromReservedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CharacterizeFromReservedTrack>("timeEnd", &CharacterizeFromReservedTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<CharacterizeFromReservedTrack>("grabSlot", &CharacterizeFromReservedTrack::SetGrabSlot);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gCharacterizeFromReservedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10238260
			fight::TrackFactory* CreateCharacterizeFromReservedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CharacterizeFromReservedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10239380
			void RegisterCharacterizeFromReservedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CharacterizeFromReservedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetNPCLODStateTrackProperties;  // 0x11255A54

			// FUNCTION: ENGINE 0x10236550
			bool SetNPCLODStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236570
			bool SetNPCLODStateTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236590
			bool SetNPCLODStateTrack::SetValue(int newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236C90
			fight::Property* SetNPCLODStateTrack::GetProperty(int index)
			{
				return gSetNPCLODStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236CB0
			void SetNPCLODStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetNPCLODStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x10236CC0
			SetNPCLODStateTrack::SetNPCLODStateTrack() : timeBegin(0.0f), timeEnd(-1.0f), value(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10236D10
			float SetNPCLODStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10236D20
			float SetNPCLODStateTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10236D30
			SetNPCLODStateTrack::~SetNPCLODStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x10238CA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetNPCLODStateTrack::RegisterProperties()
			{
				if (gSetNPCLODStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetNPCLODStateTrack>("timeBegin", &SetNPCLODStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetNPCLODStateTrack>("timeEnd", &SetNPCLODStateTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<SetNPCLODStateTrack>("value", gLodSteerTrackWalkanimTable, gLodSteerTrackWalkanimCount, &SetNPCLODStateTrack::SetValue);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSetNPCLODStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10238290
			fight::TrackFactory* CreateSetNPCLODStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetNPCLODStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102393B0
			void RegisterSetNPCLODStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetNPCLODStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gLodGotoFixedDestinationTrackProperties;  // 0x11255A58

			// FUNCTION: ENGINE 0x102365A0
			bool LodGotoFixedDestinationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102365C0
			bool LodGotoFixedDestinationTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102365E0
			bool LodGotoFixedDestinationTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236600
			bool LodGotoFixedDestinationTrack::SetVerticalSpeed(float newValue)
			{
				verticalSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236620
			bool LodGotoFixedDestinationTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236640
			bool LodGotoFixedDestinationTrack::SetFreeArea(float newValue)
			{
				freeArea = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236660
			bool LodGotoFixedDestinationTrack::SetMinHeight(float newValue)
			{
				minHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236D40
			fight::Property* LodGotoFixedDestinationTrack::GetProperty(int index)
			{
				return gLodGotoFixedDestinationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236D60
			void LodGotoFixedDestinationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLodGotoFixedDestinationTrackProperties);
			}

			// FUNCTION: ENGINE 0x10236D70
			LodGotoFixedDestinationTrack::LodGotoFixedDestinationTrack() : freeArea(0.0f), minHeight(6.0f), speed(1.0f), timeBegin(0.0f), timeEnd(-1.0f), tolerance(1.0f), verticalSpeed(1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10236DE0
			float LodGotoFixedDestinationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10236DF0
			float LodGotoFixedDestinationTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10236E00
			LodGotoFixedDestinationTrack::~LodGotoFixedDestinationTrack()
			{
			}

			// FUNCTION: ENGINE 0x10238DD0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LodGotoFixedDestinationTrack::RegisterProperties()
			{
				if (gLodGotoFixedDestinationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LodGotoFixedDestinationTrack>("timeBegin", &LodGotoFixedDestinationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LodGotoFixedDestinationTrack>("timeEnd", &LodGotoFixedDestinationTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LodGotoFixedDestinationTrack>("speed", &LodGotoFixedDestinationTrack::SetSpeed);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LodGotoFixedDestinationTrack>("verticalSpeed", &LodGotoFixedDestinationTrack::SetVerticalSpeed);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<LodGotoFixedDestinationTrack>("tolerance", &LodGotoFixedDestinationTrack::SetTolerance);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<LodGotoFixedDestinationTrack>("freeArea", &LodGotoFixedDestinationTrack::SetFreeArea);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<LodGotoFixedDestinationTrack>("minHeight", &LodGotoFixedDestinationTrack::SetMinHeight);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gLodGotoFixedDestinationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102382C0
			fight::TrackFactory* CreateLodGotoFixedDestinationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LodGotoFixedDestinationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102393E0
			void RegisterLodGotoFixedDestinationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LodGotoFixedDestinationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gUnDowngradableTrackProperties;  // 0x11255A5C

			// FUNCTION: ENGINE 0x10236680
			bool UnDowngradableTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102366A0
			bool UnDowngradableTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102366C0
			bool UnDowngradableTrack::SetClearAtEnd(bool newValue)
			{
				clearAtEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236E10
			fight::Property* UnDowngradableTrack::GetProperty(int index)
			{
				return gUnDowngradableTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236E30
			void UnDowngradableTrack::ClearProperties()
			{
				fight::FreePropertyList(&gUnDowngradableTrackProperties);
			}

			// FUNCTION: ENGINE 0x10236E40
			UnDowngradableTrack::UnDowngradableTrack() : timeBegin(0.0f), timeEnd(-1.0f), clearAtEnd(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10236E80
			float UnDowngradableTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10236E90
			float UnDowngradableTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10236EA0
			UnDowngradableTrack::~UnDowngradableTrack()
			{
			}

			// FUNCTION: ENGINE 0x10238FE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void UnDowngradableTrack::RegisterProperties()
			{
				if (gUnDowngradableTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<UnDowngradableTrack>("timeBegin", &UnDowngradableTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<UnDowngradableTrack>("timeEnd", &UnDowngradableTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<UnDowngradableTrack>("clearAtEnd", &UnDowngradableTrack::SetClearAtEnd);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gUnDowngradableTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102382F0
			fight::TrackFactory* CreateUnDowngradableTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<UnDowngradableTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10239410
			void RegisterUnDowngradableTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<UnDowngradableTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gUpdateSoldierReservationBudgetTrackProperties;  // 0x11255A60

			// FUNCTION: ENGINE 0x102366D0
			bool UpdateSoldierReservationBudgetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102366F0
			bool UpdateSoldierReservationBudgetTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10236EB0
			fight::Property* UpdateSoldierReservationBudgetTrack::GetProperty(int index)
			{
				return gUpdateSoldierReservationBudgetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10236ED0
			void UpdateSoldierReservationBudgetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gUpdateSoldierReservationBudgetTrackProperties);
			}

			// FUNCTION: ENGINE 0x10236EE0
			UpdateSoldierReservationBudgetTrack::UpdateSoldierReservationBudgetTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10236F20
			float UpdateSoldierReservationBudgetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10236F30
			float UpdateSoldierReservationBudgetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10236F40
			UpdateSoldierReservationBudgetTrack::~UpdateSoldierReservationBudgetTrack()
			{
			}

			// FUNCTION: ENGINE 0x102390F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void UpdateSoldierReservationBudgetTrack::RegisterProperties()
			{
				if (gUpdateSoldierReservationBudgetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<UpdateSoldierReservationBudgetTrack>("timeBegin", &UpdateSoldierReservationBudgetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<UpdateSoldierReservationBudgetTrack>("timeEnd", &UpdateSoldierReservationBudgetTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gUpdateSoldierReservationBudgetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10238320
			fight::TrackFactory* CreateUpdateSoldierReservationBudgetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<UpdateSoldierReservationBudgetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10239440
			void RegisterUpdateSoldierReservationBudgetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<UpdateSoldierReservationBudgetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}


			// FUNCTION: ENGINE 0x101FB410
			// EQUIVALENT: register allocation (the engine keeps the false result in bl, ours returns a literal; the handle and the budget type use other registers); the same call with the same arguments (best 23.9 %)
			bool CanReserveSoldierBudgetCondition::Evaluate(int a, int b, int c, int d)
			{
				bool result = false;
				engine::GameObjectHandle handle = engine::GetObjectHandle(AsOwner(c));
				if (handle.Get() != 0)
				{
					return proto::gAISystem->soldierBudgets->Unknown10386810(soldiers, handle);
				}
				return result;
			}

			// FUNCTION: ENGINE 0x101FB490
			// EQUIVALENT: register allocation (the engine keeps the false result in bl, ours returns a literal; the handle uses another register); the same call with the same argument (best 30.8 %)
			bool IsInLoadedCellCondition::Evaluate(int a, int b, int c, int d)
			{
				bool result = false;
				engine::GameObjectHandle handle = engine::GetObjectHandle(AsOwner(c));
				if (handle.Get() != 0)
				{
					return proto::gAISystem->soldierBudgets->Unknown103866C0(handle);
				}
				return result;
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101FBCE0
			LodSteerAction::LodSteerAction(LodSteerTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FABE0
			LodSteerAction::~LodSteerAction()
			{
			}

			// FUNCTION: ENGINE 0x101FA1F0
			bool LodSteerAction::Slot5(int arg, float value)
			{
				return false;
			}

			// FUNCTION: ENGINE 0x101FA210
			void LodSteerAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101FA200
			bool LodSteerAction::Slot7(int arg, float value)
			{
				return false;
			}

			// FUNCTION: ENGINE 0x101FC770
			fight::Action* LodSteerTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new LodSteerAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101FBAE0
			ResetPhysicVelocitiesAction::ResetPhysicVelocitiesAction(ResetPhysicVelocitiesTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FAA40
			ResetPhysicVelocitiesAction::~ResetPhysicVelocitiesAction()
			{
			}

			// FUNCTION: ENGINE 0x101FA1E0
			void ResetPhysicVelocitiesAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101FC720
			fight::Action* ResetPhysicVelocitiesTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ResetPhysicVelocitiesAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101FBD90
			LodMoveAction::LodMoveAction(LodMoveTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FAC30
			LodMoveAction::~LodMoveAction()
			{
			}

			// FUNCTION: ENGINE 0x101FA220
			bool LodMoveAction::Slot5(int arg, float value)
			{
				return false;
			}

			// FUNCTION: ENGINE 0x101FA240
			void LodMoveAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101FA230
			bool LodMoveAction::Slot7(int arg, float value)
			{
				return false;
			}

			// FUNCTION: ENGINE 0x101FC7C0
			fight::Action* LodMoveTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new LodMoveAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101FC5E0
			EnableLODPatrolAction::EnableLODPatrolAction(EnableLODPatrolTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(true)
			{
			}

			// FUNCTION: ENGINE 0x101FB340
			EnableLODPatrolAction::~EnableLODPatrolAction()
			{
			}

			// FUNCTION: ENGINE 0x101FA320
			bool EnableLODPatrolAction::Slot5(int arg, float value)
			{
				return false;
			}

			// FUNCTION: ENGINE 0x101FA330
			void EnableLODPatrolAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101FCCE0
			fight::Action* EnableLODPatrolTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new EnableLODPatrolAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101FBA30
			GameObjectOrientAction::GameObjectOrientAction(GameObjectOrientTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FA9F0
			GameObjectOrientAction::~GameObjectOrientAction()
			{
			}

			// FUNCTION: ENGINE 0x101FA1B0
			bool GameObjectOrientAction::Slot5(int arg, float value)
			{
				return false;
			}

			// FUNCTION: ENGINE 0x101FA1D0
			void GameObjectOrientAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101FA1C0
			bool GameObjectOrientAction::Slot7(int arg, float value)
			{
				return false;
			}

			// FUNCTION: ENGINE 0x101FC6D0
			fight::Action* GameObjectOrientTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new GameObjectOrientAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101FB920
			SetNPCLODStateAction::SetNPCLODStateAction(SetNPCLODStateTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FA9A0
			SetNPCLODStateAction::~SetNPCLODStateAction()
			{
			}

			// FUNCTION: ENGINE 0x101FC680
			fight::Action* SetNPCLODStateTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new SetNPCLODStateAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101FBE40
			UnDowngradableAction::UnDowngradableAction(UnDowngradableTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FAC80
			UnDowngradableAction::~UnDowngradableAction()
			{
			}

			// FUNCTION: ENGINE 0x101FC810
			fight::Action* UnDowngradableTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new UnDowngradableAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101FC030
			UpdateSoldierReservationBudgetAction::UpdateSoldierReservationBudgetAction(UpdateSoldierReservationBudgetTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FACD0
			UpdateSoldierReservationBudgetAction::~UpdateSoldierReservationBudgetAction()
			{
			}

			// FUNCTION: ENGINE 0x101FA250
			void UpdateSoldierReservationBudgetAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101FC860
			fight::Action* UpdateSoldierReservationBudgetTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new UpdateSoldierReservationBudgetAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101FC2B0
			CharacterizeAction::CharacterizeAction(CharacterizeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FADC0
			CharacterizeAction::~CharacterizeAction()
			{
			}

			// FUNCTION: ENGINE 0x101FC900
			fight::Action* CharacterizeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CharacterizeAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101FC140
			CharacterizeFromReservedAction::CharacterizeFromReservedAction(CharacterizeFromReservedTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FAD70
			CharacterizeFromReservedAction::~CharacterizeFromReservedAction()
			{
			}

			// FUNCTION: ENGINE 0x101FC8B0
			fight::Action* CharacterizeFromReservedTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CharacterizeFromReservedAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyIntConstRange<CanReserveSoldierBudgetCondition>;
			template class fight::ConditionFactoryTemplate<CanReserveSoldierBudgetCondition>;
			template class fight::ConditionFactoryCasterTemplate<CanReserveSoldierBudgetCondition>;
			template class fight::ConditionFactoryTemplate<IsInLoadedCellCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsInLoadedCellCondition>;
			template class fight::PropertyEnumConstList<NPCLODCondition>;
			template class fight::ConditionFactoryTemplate<NPCLODCondition>;
			template class fight::ConditionFactoryCasterTemplate<NPCLODCondition>;
			template class fight::PropertyFloatConstRange<LodSteerTrack>;
			template class fight::PropertyEnumConstList<LodSteerTrack>;
			template class fight::TrackFactoryTemplate<LodSteerTrack>;
			template class fight::TrackFactoryCasterTemplate<LodSteerTrack>;
			template class fight::PropertyFloatConstRange<ResetPhysicVelocitiesTrack>;
			template class fight::TrackFactoryTemplate<ResetPhysicVelocitiesTrack>;
			template class fight::TrackFactoryCasterTemplate<ResetPhysicVelocitiesTrack>;
			template class fight::PropertyFloatConstRange<LodMoveTrack>;
			template class fight::PropertyEnumConstList<LodMoveTrack>;
			template class fight::TrackFactoryTemplate<LodMoveTrack>;
			template class fight::TrackFactoryCasterTemplate<LodMoveTrack>;
			template class fight::PropertyFloatConstRange<EnableLODPatrolTrack>;
			template class fight::PropertyEnumConstList<EnableLODPatrolTrack>;
			template class fight::TrackFactoryTemplate<EnableLODPatrolTrack>;
			template class fight::TrackFactoryCasterTemplate<EnableLODPatrolTrack>;
			template class fight::PropertyFloatConstRange<GameObjectOrientTrack>;
			template class fight::PropertyBool<GameObjectOrientTrack>;
			template class fight::TrackFactoryTemplate<GameObjectOrientTrack>;
			template class fight::TrackFactoryCasterTemplate<GameObjectOrientTrack>;
			template class fight::PropertyFloatConstRange<CharacterizeTrack>;
			template class fight::PropertyNameList<CharacterizeTrack>;
			template class fight::TrackFactoryTemplate<CharacterizeTrack>;
			template class fight::TrackFactoryCasterTemplate<CharacterizeTrack>;
			template class fight::PropertyFloatConstRange<CharacterizeFromReservedTrack>;
			template class fight::PropertyNameList<CharacterizeFromReservedTrack>;
			template class fight::TrackFactoryTemplate<CharacterizeFromReservedTrack>;
			template class fight::TrackFactoryCasterTemplate<CharacterizeFromReservedTrack>;
			template class fight::PropertyFloatConstRange<SetNPCLODStateTrack>;
			template class fight::PropertyEnumConstList<SetNPCLODStateTrack>;
			template class fight::TrackFactoryTemplate<SetNPCLODStateTrack>;
			template class fight::TrackFactoryCasterTemplate<SetNPCLODStateTrack>;
			template class fight::PropertyFloatConstRange<LodGotoFixedDestinationTrack>;
			template class fight::TrackFactoryTemplate<LodGotoFixedDestinationTrack>;
			template class fight::TrackFactoryCasterTemplate<LodGotoFixedDestinationTrack>;
			template class fight::PropertyFloatConstRange<UnDowngradableTrack>;
			template class fight::PropertyBool<UnDowngradableTrack>;
			template class fight::TrackFactoryTemplate<UnDowngradableTrack>;
			template class fight::TrackFactoryCasterTemplate<UnDowngradableTrack>;
			template class fight::PropertyFloatConstRange<UpdateSoldierReservationBudgetTrack>;
			template class fight::TrackFactoryTemplate<UpdateSoldierReservationBudgetTrack>;
			template class fight::TrackFactoryCasterTemplate<UpdateSoldierReservationBudgetTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10236F90
// FUNCTION: ENGINE 0x10236FC0
// FUNCTION: ENGINE 0x10236FF0
// FUNCTION: ENGINE 0x10237020
// FUNCTION: ENGINE 0x10237050
// FUNCTION: ENGINE 0x10237080
// FUNCTION: ENGINE 0x102370B0
// FUNCTION: ENGINE 0x102370E0
// FUNCTION: ENGINE 0x10237210
// FUNCTION: ENGINE 0x10237240
// FUNCTION: ENGINE 0x10237270
// FUNCTION: ENGINE 0x102372A0
// FUNCTION: ENGINE 0x102372D0
// FUNCTION: ENGINE 0x102372E0
// FUNCTION: ENGINE 0x10237310
// FUNCTION: ENGINE 0x10237320
// FUNCTION: ENGINE 0x10237350
// FUNCTION: ENGINE 0x10237380
// FUNCTION: ENGINE 0x102373A0
// FUNCTION: ENGINE 0x102373F0
// FUNCTION: ENGINE 0x10237400
// FUNCTION: ENGINE 0x10237430
// FUNCTION: ENGINE 0x10237440
// FUNCTION: ENGINE 0x10237470
// FUNCTION: ENGINE 0x10237480
// FUNCTION: ENGINE 0x102374B0
// FUNCTION: ENGINE 0x102374C0
// FUNCTION: ENGINE 0x102374F0
// FUNCTION: ENGINE 0x10237500
// FUNCTION: ENGINE 0x10237530
// FUNCTION: ENGINE 0x10237540
// FUNCTION: ENGINE 0x10237570
// FUNCTION: ENGINE 0x10237580
// FUNCTION: ENGINE 0x102375B0
// FUNCTION: ENGINE 0x102375C0
// FUNCTION: ENGINE 0x102375F0
// FUNCTION: ENGINE 0x10237600
// FUNCTION: ENGINE 0x10237630
// FUNCTION: ENGINE 0x10237640
// FUNCTION: ENGINE 0x10237670
// FUNCTION: ENGINE 0x10237680
// FUNCTION: ENGINE 0x102376B0
// FUNCTION: ENGINE 0x102376C0
// FUNCTION: ENGINE 0x102376F0
// FUNCTION: ENGINE 0x10237720
// FUNCTION: ENGINE 0x10237750
// FUNCTION: ENGINE 0x10237780
// FUNCTION: ENGINE 0x102377A0
// FUNCTION: ENGINE 0x102377B0
// FUNCTION: ENGINE 0x102377F0
// FUNCTION: ENGINE 0x10237800
// FUNCTION: ENGINE 0x10237830
// FUNCTION: ENGINE 0x10237850
// FUNCTION: ENGINE 0x10237860
// FUNCTION: ENGINE 0x10237890
// FUNCTION: ENGINE 0x102378C0
// FUNCTION: ENGINE 0x102378D0
// FUNCTION: ENGINE 0x10237910
// FUNCTION: ENGINE 0x10237920
// FUNCTION: ENGINE 0x10237950
// FUNCTION: ENGINE 0x10237970
// FUNCTION: ENGINE 0x10237980
// FUNCTION: ENGINE 0x102379B0
// FUNCTION: ENGINE 0x102379E0
// FUNCTION: ENGINE 0x102379F0
// FUNCTION: ENGINE 0x10237A20
// FUNCTION: ENGINE 0x10237A50
// FUNCTION: ENGINE 0x10237A60
// FUNCTION: ENGINE 0x10237AA0
// FUNCTION: ENGINE 0x10237AB0
// FUNCTION: ENGINE 0x10237AE0
// FUNCTION: ENGINE 0x10237B00
// FUNCTION: ENGINE 0x10237B10
// FUNCTION: ENGINE 0x10237B40
// FUNCTION: ENGINE 0x10237B70
// FUNCTION: ENGINE 0x10237B80
// FUNCTION: ENGINE 0x10237BC0
// FUNCTION: ENGINE 0x10237BD0
// FUNCTION: ENGINE 0x10237C00
// FUNCTION: ENGINE 0x10237C20
// FUNCTION: ENGINE 0x10237C30
// FUNCTION: ENGINE 0x10237C60
// FUNCTION: ENGINE 0x10237C90
// FUNCTION: ENGINE 0x10237CA0
// FUNCTION: ENGINE 0x10237CD0
// FUNCTION: ENGINE 0x10237CF0
// FUNCTION: ENGINE 0x10237D00
// FUNCTION: ENGINE 0x10237D30
// FUNCTION: ENGINE 0x10237D60
// FUNCTION: ENGINE 0x10237D70
// FUNCTION: ENGINE 0x10237DA0
// FUNCTION: ENGINE 0x10237DD0
// FUNCTION: ENGINE 0x10237DE0
// FUNCTION: ENGINE 0x10237E10
// FUNCTION: ENGINE 0x10237E40
// FUNCTION: ENGINE 0x10237E50
// FUNCTION: ENGINE 0x10237E90
// FUNCTION: ENGINE 0x10237EA0
// FUNCTION: ENGINE 0x10237ED0
// FUNCTION: ENGINE 0x10237EF0
// FUNCTION: ENGINE 0x10237F00
// FUNCTION: ENGINE 0x10237F30
// FUNCTION: ENGINE 0x10237F60
// FUNCTION: ENGINE 0x10237F70
// FUNCTION: ENGINE 0x10237FA0
// FUNCTION: ENGINE 0x10237FD0
// FUNCTION: ENGINE 0x10237FE0
// FUNCTION: ENGINE 0x10238010
// FUNCTION: ENGINE 0x10238030
// FUNCTION: ENGINE 0x10238040
// FUNCTION: ENGINE 0x10238070
// FUNCTION: ENGINE 0x102380A0
// FUNCTION: ENGINE 0x10239470
// FUNCTION: ENGINE 0x102394A0
// FUNCTION: ENGINE 0x102394C0
// FUNCTION: ENGINE 0x102394D0
// FUNCTION: ENGINE 0x10239500
// FUNCTION: ENGINE 0x10239520
// FUNCTION: ENGINE 0x10239530
// FUNCTION: ENGINE 0x10239560
// FUNCTION: ENGINE 0x10239580
// FUNCTION: ENGINE 0x102395B0
// FUNCTION: ENGINE 0x102395D0
// FUNCTION: ENGINE 0x10239600
// FUNCTION: ENGINE 0x10239620
// FUNCTION: ENGINE 0x10239650
// FUNCTION: ENGINE 0x10239670
// FUNCTION: ENGINE 0x102396A0
// FUNCTION: ENGINE 0x102396C0
// FUNCTION: ENGINE 0x102396F0
// FUNCTION: ENGINE 0x10239710
// FUNCTION: ENGINE 0x10239740
// FUNCTION: ENGINE 0x10239760
// FUNCTION: ENGINE 0x10239790
// FUNCTION: ENGINE 0x102397B0
// FUNCTION: ENGINE 0x102397E0
// FUNCTION: ENGINE 0x10239800
// FUNCTION: ENGINE 0x10239830
// FUNCTION: ENGINE 0x10239850
// FUNCTION: ENGINE 0x10239880
// FUNCTION: ENGINE 0x10239AC0
// FUNCTION: ENGINE 0x10239B10
// FUNCTION: ENGINE 0x10239B60
// FUNCTION: ENGINE 0x10239BB0
// FUNCTION: ENGINE 0x10239C00
// FUNCTION: ENGINE 0x10239C50
// FUNCTION: ENGINE 0x10239CA0
// FUNCTION: ENGINE 0x10239CF0
// FUNCTION: ENGINE 0x10239D40
// FUNCTION: ENGINE 0x10239D90
// FUNCTION: ENGINE 0x10239DE0
// FUNCTION: ENGINE 0x10239E30
// FUNCTION: ENGINE 0x10239E60
// FUNCTION: ENGINE 0x10239E80
// FUNCTION: ENGINE 0x10239EB0
// FUNCTION: ENGINE 0x10239ED0
// FUNCTION: ENGINE 0x10239F20
