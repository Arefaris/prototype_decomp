// Fight items of the ai group: ThreatCondition, ThreatInMemoryCondition, ThreatCanSeeCondition, LastThreatConditionGroupCondition, ThreatCanGrabCondition, ThreatStoreCondition, ThreatBallTrack, ThreatDodgeTrack, ThreatMemoryResetTrack, ThreatSendToTargetTrack (unit 0x10253340 - 0x10255E00; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_threat.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gThreatConditionProperties;  // 0x11255C20

			// FUNCTION: ENGINE 0x10253880
			bool ThreatCondition::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253560
			fight::Property* ThreatCondition::GetProperty(int index)
			{
				return gThreatConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10253580
			void ThreatCondition::ClearProperties()
			{
				fight::FreePropertyList(&gThreatConditionProperties);
			}

			// FUNCTION: ENGINE 0x102539A0
			ThreatCondition::ThreatCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x102539D0
			ThreatCondition::~ThreatCondition()
			{
			}

			// FUNCTION: ENGINE 0x10254F90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThreatCondition::RegisterProperties()
			{
				if (gThreatConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ThreatCondition>("name", &ThreatCondition::SetName);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gThreatConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10254760
			fight::ConditionFactory* CreateThreatConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254A80
			void RegisterThreatConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gThreatInMemoryConditionProperties;  // 0x11255C24

			// FUNCTION: ENGINE 0x102535F0
			fight::Property* ThreatInMemoryCondition::GetProperty(int index)
			{
				return gThreatInMemoryConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10253610
			void ThreatInMemoryCondition::ClearProperties()
			{
				fight::FreePropertyList(&gThreatInMemoryConditionProperties);
			}

			// FUNCTION: ENGINE 0x10253620
			ThreatInMemoryCondition::ThreatInMemoryCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10253640
			ThreatInMemoryCondition::~ThreatInMemoryCondition()
			{
			}

			// FUNCTION: ENGINE 0x10253590
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThreatInMemoryCondition::RegisterProperties()
			{
				if (gThreatInMemoryConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gThreatInMemoryConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10254790
			fight::ConditionFactory* CreateThreatInMemoryConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatInMemoryCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254AB0
			void RegisterThreatInMemoryConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatInMemoryCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gThreatCanSeeConditionProperties;  // 0x11255C28

			// FUNCTION: ENGINE 0x102538A0
			bool ThreatCanSeeCondition::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253340
			bool ThreatCanSeeCondition::SetFOV(float newValue)
			{
				fOV = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10253360
			bool ThreatCanSeeCondition::SetDirection(const math::Vector& newValue)
			{
				direction.x = newValue.x;
				direction.y = newValue.y;
				direction.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10253380
			bool ThreatCanSeeCondition::SetIgnoreY(bool newValue)
			{
				ignoreY = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253390
			bool ThreatCanSeeCondition::SetGiversPerspective(bool newValue)
			{
				giversPerspective = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253650
			fight::Property* ThreatCanSeeCondition::GetProperty(int index)
			{
				return gThreatCanSeeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10253670
			void ThreatCanSeeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gThreatCanSeeConditionProperties);
			}

			// FUNCTION: ENGINE 0x10253A10
			ThreatCanSeeCondition::ThreatCanSeeCondition() : fight::Condition(0), direction(0.0f, 0.0f, -1.0f), fOV(0.0f), giversPerspective(false), ignoreY(true)
			{
			}

			// FUNCTION: ENGINE 0x10253A70
			ThreatCanSeeCondition::~ThreatCanSeeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10255030
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThreatCanSeeCondition::RegisterProperties()
			{
				if (gThreatCanSeeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ThreatCanSeeCondition>("name", &ThreatCanSeeCondition::SetName);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ThreatCanSeeCondition>("fOV", &ThreatCanSeeCondition::SetFOV);
					properties[1] = property;
					property = new fight::PropertyVector<ThreatCanSeeCondition>("direction", &ThreatCanSeeCondition::SetDirection);
					properties[2] = property;
					property = new fight::PropertyBool<ThreatCanSeeCondition>("ignoreY", &ThreatCanSeeCondition::SetIgnoreY);
					properties[3] = property;
					property = new fight::PropertyBool<ThreatCanSeeCondition>("giversPerspective", &ThreatCanSeeCondition::SetGiversPerspective);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gThreatCanSeeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102547C0
			fight::ConditionFactory* CreateThreatCanSeeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatCanSeeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254AE0
			void RegisterThreatCanSeeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatCanSeeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gLastThreatConditionGroupConditionProperties;  // 0x11255C2C

			// FUNCTION: ENGINE 0x102533A0
			fight::ConditionList* LastThreatConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x10253680
			fight::Property* LastThreatConditionGroupCondition::GetProperty(int index)
			{
				return gLastThreatConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x102536A0
			void LastThreatConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gLastThreatConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x102536B0
			LastThreatConditionGroupCondition::LastThreatConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x102536E0
			LastThreatConditionGroupCondition::~LastThreatConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x10254940
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LastThreatConditionGroupCondition::RegisterProperties()
			{
				if (gLastThreatConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<LastThreatConditionGroupCondition>("conditions", &LastThreatConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gLastThreatConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102547F0
			fight::ConditionFactory* CreateLastThreatConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<LastThreatConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254B10
			void RegisterLastThreatConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<LastThreatConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gThreatCanGrabConditionProperties;  // 0x11255C30

			// FUNCTION: ENGINE 0x102538C0
			bool ThreatCanGrabCondition::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102533B0
			bool ThreatCanGrabCondition::SetSetGrabTarget(bool newValue)
			{
				setGrabTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253700
			fight::Property* ThreatCanGrabCondition::GetProperty(int index)
			{
				return gThreatCanGrabConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10253720
			void ThreatCanGrabCondition::ClearProperties()
			{
				fight::FreePropertyList(&gThreatCanGrabConditionProperties);
			}

			// FUNCTION: ENGINE 0x10253AB0
			ThreatCanGrabCondition::ThreatCanGrabCondition() : fight::Condition(0), setGrabTarget(true)
			{
			}

			// FUNCTION: ENGINE 0x10253AE0
			ThreatCanGrabCondition::~ThreatCanGrabCondition()
			{
			}

			// FUNCTION: ENGINE 0x102551C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThreatCanGrabCondition::RegisterProperties()
			{
				if (gThreatCanGrabConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ThreatCanGrabCondition>("name", &ThreatCanGrabCondition::SetName);
					properties[0] = property;
					property = new fight::PropertyBool<ThreatCanGrabCondition>("setGrabTarget", &ThreatCanGrabCondition::SetSetGrabTarget);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gThreatCanGrabConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10254820
			fight::ConditionFactory* CreateThreatCanGrabConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatCanGrabCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254B40
			void RegisterThreatCanGrabConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatCanGrabCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gThreatStoreConditionProperties;  // 0x11255C34

			// FUNCTION: ENGINE 0x102538E0
			bool ThreatStoreCondition::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102533C0
			bool ThreatStoreCondition::SetThreatObject(int newValue)
			{
				threatObject = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253730
			fight::Property* ThreatStoreCondition::GetProperty(int index)
			{
				return gThreatStoreConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10253750
			void ThreatStoreCondition::ClearProperties()
			{
				fight::FreePropertyList(&gThreatStoreConditionProperties);
			}

			// FUNCTION: ENGINE 0x10253AF0
			ThreatStoreCondition::ThreatStoreCondition() : fight::Condition(0), threatObject(0)
			{
			}

			// FUNCTION: ENGINE 0x10253B20
			ThreatStoreCondition::~ThreatStoreCondition()
			{
			}

			// FUNCTION: ENGINE 0x102552A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThreatStoreCondition::RegisterProperties()
			{
				if (gThreatStoreConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ThreatStoreCondition>("name", &ThreatStoreCondition::SetName);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ThreatStoreCondition>("threatObject", gThreatStoreConditionThreatObjectTable, gThreatStoreConditionThreatObjectCount, &ThreatStoreCondition::SetThreatObject);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gThreatStoreConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10254850
			fight::ConditionFactory* CreateThreatStoreConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatStoreCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254B70
			void RegisterThreatStoreConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ThreatStoreCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gThreatBallTrackProperties;  // 0x11255C38

			// FUNCTION: ENGINE 0x102533D0
			bool ThreatBallTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102533F0
			bool ThreatBallTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253410
			bool ThreatBallTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10253430
			bool ThreatBallTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253450
			bool ThreatBallTrack::SetTimeToLive(float newValue)
			{
				timeToLive = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253900
			bool ThreatBallTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253920
			bool ThreatBallTrack::SetThreatName(const fight::Name& newValue)
			{
				threatName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253760
			fight::Property* ThreatBallTrack::GetProperty(int index)
			{
				return gThreatBallTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10253780
			void ThreatBallTrack::ClearProperties()
			{
				fight::FreePropertyList(&gThreatBallTrackProperties);
			}

			// FUNCTION: ENGINE 0x10253B30
			ThreatBallTrack::ThreatBallTrack() : offset(0.0f, 0.0f, 0.0f), radius(0.0f), timeBegin(0.0f), timeEnd(-1.0f), timeToLive(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10253BA0
			float ThreatBallTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10253BB0
			float ThreatBallTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10253BC0
			ThreatBallTrack::~ThreatBallTrack()
			{
			}

			// FUNCTION: ENGINE 0x10255390
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThreatBallTrack::RegisterProperties()
			{
				if (gThreatBallTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ThreatBallTrack>("timeBegin", &ThreatBallTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ThreatBallTrack>("timeEnd", &ThreatBallTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<ThreatBallTrack>("offset", &ThreatBallTrack::SetOffset);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ThreatBallTrack>("radius", &ThreatBallTrack::SetRadius);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ThreatBallTrack>("timeToLive", &ThreatBallTrack::SetTimeToLive);
					properties[4] = property;
					property = new fight::PropertyNameList<ThreatBallTrack>("joint", &ThreatBallTrack::SetJoint);
					properties[5] = property;
					property = new fight::PropertyName<ThreatBallTrack>("threatName", &ThreatBallTrack::SetThreatName);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gThreatBallTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10254880
			fight::TrackFactory* CreateThreatBallTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThreatBallTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254BA0
			void RegisterThreatBallTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThreatBallTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gThreatDodgeTrackProperties;  // 0x11255C3C

			// FUNCTION: ENGINE 0x10253470
			bool ThreatDodgeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253490
			bool ThreatDodgeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102534B0
			bool ThreatDodgeTrack::SetDistanceToThreat(float newValue)
			{
				distanceToThreat = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253940
			bool ThreatDodgeTrack::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102534D0
			fight::BranchHolder* ThreatDodgeTrack::SetDodgeBranch()
			{
				return &dodgeBranch;
			}

			// FUNCTION: ENGINE 0x102534E0
			bool ThreatDodgeTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102534F0
			fight::ConditionList* ThreatDodgeTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x10253790
			fight::Property* ThreatDodgeTrack::GetProperty(int index)
			{
				return gThreatDodgeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102537B0
			void ThreatDodgeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gThreatDodgeTrackProperties);
			}

			// FUNCTION: ENGINE 0x10253BD0
			ThreatDodgeTrack::ThreatDodgeTrack() : dodgeBranch(0), distanceToThreat(2.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x10253C40
			float ThreatDodgeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10253C50
			float ThreatDodgeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10253C60
			ThreatDodgeTrack::~ThreatDodgeTrack()
			{
			}

			// FUNCTION: ENGINE 0x102555A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThreatDodgeTrack::RegisterProperties()
			{
				if (gThreatDodgeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ThreatDodgeTrack>("timeBegin", &ThreatDodgeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ThreatDodgeTrack>("timeEnd", &ThreatDodgeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ThreatDodgeTrack>("distanceToThreat", &ThreatDodgeTrack::SetDistanceToThreat);
					properties[2] = property;
					property = new fight::PropertyName<ThreatDodgeTrack>("name", &ThreatDodgeTrack::SetName);
					properties[3] = property;
					property = new fight::PropertyBranch<ThreatDodgeTrack>("dodgeBranch", &ThreatDodgeTrack::SetDodgeBranch);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<ThreatDodgeTrack>("priority", &ThreatDodgeTrack::SetPriority);
					properties[5] = property;
					property = new fight::PropertyConditionGroup<ThreatDodgeTrack>("conditions", &ThreatDodgeTrack::SetConditions);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gThreatDodgeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102548B0
			fight::TrackFactory* CreateThreatDodgeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThreatDodgeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254BD0
			void RegisterThreatDodgeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThreatDodgeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gThreatMemoryResetTrackProperties;  // 0x11255C40

			// FUNCTION: ENGINE 0x10253500
			bool ThreatMemoryResetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102537C0
			fight::Property* ThreatMemoryResetTrack::GetProperty(int index)
			{
				return gThreatMemoryResetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102537E0
			void ThreatMemoryResetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gThreatMemoryResetTrackProperties);
			}

			// FUNCTION: ENGINE 0x102537F0
			ThreatMemoryResetTrack::ThreatMemoryResetTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10253820
			float ThreatMemoryResetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10253830
			float ThreatMemoryResetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10253840
			ThreatMemoryResetTrack::~ThreatMemoryResetTrack()
			{
			}

			// FUNCTION: ENGINE 0x102549E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThreatMemoryResetTrack::RegisterProperties()
			{
				if (gThreatMemoryResetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ThreatMemoryResetTrack>("timeBegin", &ThreatMemoryResetTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gThreatMemoryResetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102548E0
			fight::TrackFactory* CreateThreatMemoryResetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThreatMemoryResetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254C00
			void RegisterThreatMemoryResetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThreatMemoryResetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gThreatSendToTargetTrackProperties;  // 0x11255C44

			// FUNCTION: ENGINE 0x10253960
			bool ThreatSendToTargetTrack::SetThreatName(const fight::Name& newValue)
			{
				threatName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253980
			bool ThreatSendToTargetTrack::SetThrownObjectFromGrabSlot(const fight::Name& newValue)
			{
				thrownObjectFromGrabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253520
			bool ThreatSendToTargetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253540
			bool ThreatSendToTargetTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10253850
			fight::Property* ThreatSendToTargetTrack::GetProperty(int index)
			{
				return gThreatSendToTargetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10253870
			void ThreatSendToTargetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gThreatSendToTargetTrackProperties);
			}

			// FUNCTION: ENGINE 0x10253CC0
			ThreatSendToTargetTrack::ThreatSendToTargetTrack() : timeBegin(0.0f), timeEnd(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10253D10
			float ThreatSendToTargetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10253D20
			float ThreatSendToTargetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10253D30
			ThreatSendToTargetTrack::~ThreatSendToTargetTrack()
			{
			}

			// FUNCTION: ENGINE 0x102557B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThreatSendToTargetTrack::RegisterProperties()
			{
				if (gThreatSendToTargetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ThreatSendToTargetTrack>("threatName", &ThreatSendToTargetTrack::SetThreatName);
					properties[0] = property;
					property = new fight::PropertyName<ThreatSendToTargetTrack>("thrownObjectFromGrabSlot", &ThreatSendToTargetTrack::SetThrownObjectFromGrabSlot);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ThreatSendToTargetTrack>("timeBegin", &ThreatSendToTargetTrack::SetTimeBegin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ThreatSendToTargetTrack>("timeEnd", &ThreatSendToTargetTrack::SetTimeEnd);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gThreatSendToTargetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10254910
			fight::TrackFactory* CreateThreatSendToTargetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThreatSendToTargetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10254C30
			void RegisterThreatSendToTargetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThreatSendToTargetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyName<ThreatCondition>;
			template class fight::ConditionFactoryTemplate<ThreatCondition>;
			template class fight::ConditionFactoryCasterTemplate<ThreatCondition>;
			template class fight::ConditionFactoryTemplate<ThreatInMemoryCondition>;
			template class fight::ConditionFactoryCasterTemplate<ThreatInMemoryCondition>;
			template class fight::PropertyName<ThreatCanSeeCondition>;
			template class fight::PropertyFloatConstRange<ThreatCanSeeCondition>;
			template class fight::PropertyVector<ThreatCanSeeCondition>;
			template class fight::PropertyBool<ThreatCanSeeCondition>;
			template class fight::ConditionFactoryTemplate<ThreatCanSeeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ThreatCanSeeCondition>;
			template class fight::PropertyConditionGroup<LastThreatConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<LastThreatConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<LastThreatConditionGroupCondition>;
			template class fight::PropertyName<ThreatCanGrabCondition>;
			template class fight::PropertyBool<ThreatCanGrabCondition>;
			template class fight::ConditionFactoryTemplate<ThreatCanGrabCondition>;
			template class fight::ConditionFactoryCasterTemplate<ThreatCanGrabCondition>;
			template class fight::PropertyName<ThreatStoreCondition>;
			template class fight::PropertyEnumConstList<ThreatStoreCondition>;
			template class fight::ConditionFactoryTemplate<ThreatStoreCondition>;
			template class fight::ConditionFactoryCasterTemplate<ThreatStoreCondition>;
			template class fight::PropertyFloatConstRange<ThreatBallTrack>;
			template class fight::PropertyVector<ThreatBallTrack>;
			template class fight::PropertyNameList<ThreatBallTrack>;
			template class fight::PropertyName<ThreatBallTrack>;
			template class fight::TrackFactoryTemplate<ThreatBallTrack>;
			template class fight::TrackFactoryCasterTemplate<ThreatBallTrack>;
			template class fight::PropertyFloatConstRange<ThreatDodgeTrack>;
			template class fight::PropertyName<ThreatDodgeTrack>;
			template class fight::PropertyBranch<ThreatDodgeTrack>;
			template class fight::PropertyIntConstRange<ThreatDodgeTrack>;
			template class fight::PropertyConditionGroup<ThreatDodgeTrack>;
			template class fight::TrackFactoryTemplate<ThreatDodgeTrack>;
			template class fight::TrackFactoryCasterTemplate<ThreatDodgeTrack>;
			template class fight::PropertyFloatConstRange<ThreatMemoryResetTrack>;
			template class fight::TrackFactoryTemplate<ThreatMemoryResetTrack>;
			template class fight::TrackFactoryCasterTemplate<ThreatMemoryResetTrack>;
			template class fight::PropertyName<ThreatSendToTargetTrack>;
			template class fight::PropertyFloatConstRange<ThreatSendToTargetTrack>;
			template class fight::TrackFactoryTemplate<ThreatSendToTargetTrack>;
			template class fight::TrackFactoryCasterTemplate<ThreatSendToTargetTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102539E0
// FUNCTION: ENGINE 0x10253A80
// FUNCTION: ENGINE 0x10253C90
// FUNCTION: ENGINE 0x10253D40
// FUNCTION: ENGINE 0x10253D50
// FUNCTION: ENGINE 0x10253D80
// FUNCTION: ENGINE 0x10253D90
// FUNCTION: ENGINE 0x10253DC0
// FUNCTION: ENGINE 0x10253DF0
// FUNCTION: ENGINE 0x10253E10
// FUNCTION: ENGINE 0x10253E60
// FUNCTION: ENGINE 0x10253E70
// FUNCTION: ENGINE 0x10253EA0
// FUNCTION: ENGINE 0x10253EB0
// FUNCTION: ENGINE 0x10253EE0
// FUNCTION: ENGINE 0x10253EF0
// FUNCTION: ENGINE 0x10253F20
// FUNCTION: ENGINE 0x10253F30
// FUNCTION: ENGINE 0x10253F60
// FUNCTION: ENGINE 0x10253F70
// FUNCTION: ENGINE 0x10253FA0
// FUNCTION: ENGINE 0x10253FB0
// FUNCTION: ENGINE 0x10253FE0
// FUNCTION: ENGINE 0x10253FF0
// FUNCTION: ENGINE 0x10254020
// FUNCTION: ENGINE 0x10254030
// FUNCTION: ENGINE 0x10254060
// FUNCTION: ENGINE 0x10254090
// FUNCTION: ENGINE 0x102540C0
// FUNCTION: ENGINE 0x102540F0
// FUNCTION: ENGINE 0x10254120
// FUNCTION: ENGINE 0x10254150
// FUNCTION: ENGINE 0x10254180
// FUNCTION: ENGINE 0x102541B0
// FUNCTION: ENGINE 0x102541E0
// FUNCTION: ENGINE 0x10254210
// FUNCTION: ENGINE 0x10254220
// FUNCTION: ENGINE 0x10254250
// FUNCTION: ENGINE 0x10254270
// FUNCTION: ENGINE 0x10254280
// FUNCTION: ENGINE 0x102542B0
// FUNCTION: ENGINE 0x102542D0
// FUNCTION: ENGINE 0x102542E0
// FUNCTION: ENGINE 0x10254310
// FUNCTION: ENGINE 0x10254330
// FUNCTION: ENGINE 0x10254360
// FUNCTION: ENGINE 0x10254380
// FUNCTION: ENGINE 0x10254390
// FUNCTION: ENGINE 0x102543D0
// FUNCTION: ENGINE 0x102543E0
// FUNCTION: ENGINE 0x10254410
// FUNCTION: ENGINE 0x10254430
// FUNCTION: ENGINE 0x10254440
// FUNCTION: ENGINE 0x10254470
// FUNCTION: ENGINE 0x102544A0
// FUNCTION: ENGINE 0x102544B0
// FUNCTION: ENGINE 0x102544E0
// FUNCTION: ENGINE 0x10254500
// FUNCTION: ENGINE 0x10254510
// FUNCTION: ENGINE 0x10254540
// FUNCTION: ENGINE 0x10254570
// FUNCTION: ENGINE 0x10254580
// FUNCTION: ENGINE 0x102545B0
// FUNCTION: ENGINE 0x102545D0
// FUNCTION: ENGINE 0x10254600
// FUNCTION: ENGINE 0x10254620
// FUNCTION: ENGINE 0x10254630
// FUNCTION: ENGINE 0x10254660
// FUNCTION: ENGINE 0x10254680
// FUNCTION: ENGINE 0x102546B0
// FUNCTION: ENGINE 0x102546E0
// FUNCTION: ENGINE 0x102546F0
// FUNCTION: ENGINE 0x10254720
// FUNCTION: ENGINE 0x10254750
// FUNCTION: ENGINE 0x10254C60
// FUNCTION: ENGINE 0x10254C90
// FUNCTION: ENGINE 0x10254CB0
// FUNCTION: ENGINE 0x10254CE0
// FUNCTION: ENGINE 0x10254D00
// FUNCTION: ENGINE 0x10254D30
// FUNCTION: ENGINE 0x10254D50
// FUNCTION: ENGINE 0x10254D80
// FUNCTION: ENGINE 0x10254DA0
// FUNCTION: ENGINE 0x10254DD0
// FUNCTION: ENGINE 0x10254DF0
// FUNCTION: ENGINE 0x10254E00
// FUNCTION: ENGINE 0x10254E30
// FUNCTION: ENGINE 0x10254E50
// FUNCTION: ENGINE 0x10254E80
// FUNCTION: ENGINE 0x10254EA0
// FUNCTION: ENGINE 0x10254ED0
// FUNCTION: ENGINE 0x10254EF0
// FUNCTION: ENGINE 0x10254F20
// FUNCTION: ENGINE 0x10254F40
// FUNCTION: ENGINE 0x10254F70
// FUNCTION: ENGINE 0x10255900
// FUNCTION: ENGINE 0x10255950
// FUNCTION: ENGINE 0x102559A0
// FUNCTION: ENGINE 0x102559D0
// FUNCTION: ENGINE 0x102559F0
// FUNCTION: ENGINE 0x10255A20
// FUNCTION: ENGINE 0x10255A40
// FUNCTION: ENGINE 0x10255A70
// FUNCTION: ENGINE 0x10255A90
// FUNCTION: ENGINE 0x10255AC0
// FUNCTION: ENGINE 0x10255AE0
// FUNCTION: ENGINE 0x10255B10
// FUNCTION: ENGINE 0x10255B30
// FUNCTION: ENGINE 0x10255B60
// FUNCTION: ENGINE 0x10255B80
// FUNCTION: ENGINE 0x10255BB0
// FUNCTION: ENGINE 0x10255BD0
// FUNCTION: ENGINE 0x10255C20
// FUNCTION: ENGINE 0x10255C70
// FUNCTION: ENGINE 0x10255CC0
// FUNCTION: ENGINE 0x10255D10
// FUNCTION: ENGINE 0x10255D60
// FUNCTION: ENGINE 0x10255DB0
