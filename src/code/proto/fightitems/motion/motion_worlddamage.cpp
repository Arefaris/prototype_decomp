// Fight items of the motion group: WorldDamageTrack, ExplicitWorldDamageTrack, WorldConeDamageTrack, ExplicitWorldConeDamageTrack (unit 0x1050DEE0 - 0x10510A30; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_worlddamage.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gWorldDamageTrackProperties;  // 0x1126F688

			// FUNCTION: ENGINE 0x1050DEE0
			bool WorldDamageTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E2E0
			bool WorldDamageTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050DF00
			bool WorldDamageTrack::SetPosition(const math::Vector& newValue)
			{
				position.x = newValue.x;
				position.y = newValue.y;
				position.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1050DF20
			bool WorldDamageTrack::SetDirection(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				direction.x = scaled.x;
				direction.y = scaled.y;
				direction.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1050DF70
			bool WorldDamageTrack::SetUseSupportingLimb(bool newValue)
			{
				useSupportingLimb = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050DF80
			bool WorldDamageTrack::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050DFA0
			bool WorldDamageTrack::SetDamageType(int newValue)
			{
				damageType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050DFB0
			bool WorldDamageTrack::SetAttackType(int newValue)
			{
				attackType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E300
			bool WorldDamageTrack::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E320
			bool WorldDamageTrack::SetEffectType(const fight::Name& newValue)
			{
				effectType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050DFC0
			bool WorldDamageTrack::SetScaleX(float newValue)
			{
				scaleX = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050DFE0
			bool WorldDamageTrack::SetScaleY(float newValue)
			{
				scaleY = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E000
			bool WorldDamageTrack::SetEffectScale(float newValue)
			{
				effectScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E020
			bool WorldDamageTrack::SetPropAreaEmissionScale(float newValue)
			{
				propAreaEmissionScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E040
			bool WorldDamageTrack::SetPropAreaEmissionScaleFunction(int newValue)
			{
				propAreaEmissionScaleFunction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E050
			bool WorldDamageTrack::SetPropAreaSizeScale(float newValue)
			{
				propAreaSizeScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E070
			bool WorldDamageTrack::SetPropAreaSizeScaleFunction(int newValue)
			{
				propAreaSizeScaleFunction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E220
			fight::Property* WorldDamageTrack::GetProperty(int index)
			{
				return gWorldDamageTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1050E240
			void WorldDamageTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWorldDamageTrackProperties);
			}

			// FUNCTION: ENGINE 0x1050E3C0
			WorldDamageTrack::WorldDamageTrack() : direction(0.0f, 0.0f, -1.0f), position(0.0f, 0.0f, 0.0f), distance(1.0f), effectScale(1.0f), propAreaEmissionScale(0.0f), propAreaSizeScale(0.0f), scaleX(1.0f), scaleY(1.0f), timeBegin(0.0f), attackType(0), damageType(0), propAreaEmissionScaleFunction(0), propAreaSizeScaleFunction(0), useSupportingLimb(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1050E480
			float WorldDamageTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1050E490
			float WorldDamageTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1050E4A0
			WorldDamageTrack::~WorldDamageTrack()
			{
			}

			// FUNCTION: ENGINE 0x1050F380
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WorldDamageTrack::RegisterProperties()
			{
				if (gWorldDamageTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WorldDamageTrack>("timeBegin", &WorldDamageTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<WorldDamageTrack>("joint", &WorldDamageTrack::SetJoint);
					properties[1] = property;
					property = new fight::PropertyVector<WorldDamageTrack>("position", &WorldDamageTrack::SetPosition);
					properties[2] = property;
					property = new fight::PropertyVector<WorldDamageTrack>("direction", &WorldDamageTrack::SetDirection);
					properties[3] = property;
					property = new fight::PropertyBool<WorldDamageTrack>("useSupportingLimb", &WorldDamageTrack::SetUseSupportingLimb);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WorldDamageTrack>("distance", &WorldDamageTrack::SetDistance);
					properties[5] = property;
					property = new fight::PropertyEnumConstList<WorldDamageTrack>("damageType", gWorldDamageTrackDamageTypeTable, gWorldDamageTrackDamageTypeCount, &WorldDamageTrack::SetDamageType);
					properties[6] = property;
					property = new fight::PropertyEnumConstList<WorldDamageTrack>("attackType", gWorldDamageTrackAttackTypeTable, gWorldDamageTrackAttackTypeCount, &WorldDamageTrack::SetAttackType);
					properties[7] = property;
					property = new fight::PropertyNameList<WorldDamageTrack>("hitType", &WorldDamageTrack::SetHitType);
					properties[8] = property;
					property = new fight::PropertyNameList<WorldDamageTrack>("effectType", &WorldDamageTrack::SetEffectType);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<WorldDamageTrack>("scaleX", &WorldDamageTrack::SetScaleX);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<WorldDamageTrack>("scaleY", &WorldDamageTrack::SetScaleY);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<WorldDamageTrack>("effectScale", &WorldDamageTrack::SetEffectScale);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<WorldDamageTrack>("propAreaEmissionScale", &WorldDamageTrack::SetPropAreaEmissionScale);
					properties[13] = property;
					property = new fight::PropertyEnumConstList<WorldDamageTrack>("propAreaEmissionScaleFunction", gWorldDamageTrackPropAreaEmissionScaleFunctionTable, gWorldDamageTrackPropAreaEmissionScaleFunctionCount, &WorldDamageTrack::SetPropAreaEmissionScaleFunction);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<WorldDamageTrack>("propAreaSizeScale", &WorldDamageTrack::SetPropAreaSizeScale);
					properties[15] = property;
					property = new fight::PropertyEnumConstList<WorldDamageTrack>("propAreaSizeScaleFunction", gWorldDamageTrackPropAreaEmissionScaleFunctionTable, gWorldDamageTrackPropAreaEmissionScaleFunctionCount, &WorldDamageTrack::SetPropAreaSizeScaleFunction);
					properties[16] = property;
					fight::RegisterPropertyList(properties, &gWorldDamageTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1050EFE0
			fight::TrackFactory* CreateWorldDamageTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WorldDamageTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1050F0A0
			void RegisterWorldDamageTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WorldDamageTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gExplicitWorldDamageTrackProperties;  // 0x1126F68C

			// FUNCTION: ENGINE 0x1050E340
			bool ExplicitWorldDamageTrack::SetObject(const fight::Name& newValue)
			{
				object = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E080
			bool ExplicitWorldDamageTrack::SetToBeContinued(bool newValue)
			{
				toBeContinued = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E250
			fight::Property* ExplicitWorldDamageTrack::GetProperty(int index)
			{
				return gExplicitWorldDamageTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1050E270
			void ExplicitWorldDamageTrack::ClearProperties()
			{
				fight::FreePropertyList(&gExplicitWorldDamageTrackProperties);
			}

			// FUNCTION: ENGINE 0x1050E4B0
			ExplicitWorldDamageTrack::ExplicitWorldDamageTrack() : WorldDamageTrack(), toBeContinued(true)
			{
			}

			// FUNCTION: ENGINE 0x1050E4E0
			ExplicitWorldDamageTrack::~ExplicitWorldDamageTrack()
			{
			}

			// FUNCTION: ENGINE 0x1050F840
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ExplicitWorldDamageTrack::RegisterProperties()
			{
				if (gExplicitWorldDamageTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ExplicitWorldDamageTrack>("object", &ExplicitWorldDamageTrack::SetObject);
					properties[0] = property;
					property = new fight::PropertyBool<ExplicitWorldDamageTrack>("toBeContinued", &ExplicitWorldDamageTrack::SetToBeContinued);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldDamageTrack>("timeBegin", &WorldDamageTrack::SetTimeBegin);
					properties[2] = property;
					property = new fight::PropertyNameList<ExplicitWorldDamageTrack>("joint", &WorldDamageTrack::SetJoint);
					properties[3] = property;
					property = new fight::PropertyVector<ExplicitWorldDamageTrack>("position", &WorldDamageTrack::SetPosition);
					properties[4] = property;
					property = new fight::PropertyVector<ExplicitWorldDamageTrack>("direction", &WorldDamageTrack::SetDirection);
					properties[5] = property;
					property = new fight::PropertyBool<ExplicitWorldDamageTrack>("useSupportingLimb", &WorldDamageTrack::SetUseSupportingLimb);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldDamageTrack>("distance", &WorldDamageTrack::SetDistance);
					properties[7] = property;
					property = new fight::PropertyEnumConstList<ExplicitWorldDamageTrack>("damageType", gWorldDamageTrackDamageTypeTable, gWorldDamageTrackDamageTypeCount, &WorldDamageTrack::SetDamageType);
					properties[8] = property;
					property = new fight::PropertyEnumConstList<ExplicitWorldDamageTrack>("attackType", gWorldDamageTrackAttackTypeTable, gWorldDamageTrackAttackTypeCount, &WorldDamageTrack::SetAttackType);
					properties[9] = property;
					property = new fight::PropertyNameList<ExplicitWorldDamageTrack>("hitType", &WorldDamageTrack::SetHitType);
					properties[10] = property;
					property = new fight::PropertyNameList<ExplicitWorldDamageTrack>("effectType", &WorldDamageTrack::SetEffectType);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldDamageTrack>("scaleX", &WorldDamageTrack::SetScaleX);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldDamageTrack>("scaleY", &WorldDamageTrack::SetScaleY);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldDamageTrack>("effectScale", &WorldDamageTrack::SetEffectScale);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldDamageTrack>("propAreaEmissionScale", &WorldDamageTrack::SetPropAreaEmissionScale);
					properties[15] = property;
					property = new fight::PropertyEnumConstList<ExplicitWorldDamageTrack>("propAreaEmissionScaleFunction", gWorldDamageTrackPropAreaEmissionScaleFunctionTable, gWorldDamageTrackPropAreaEmissionScaleFunctionCount, &WorldDamageTrack::SetPropAreaEmissionScaleFunction);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldDamageTrack>("propAreaSizeScale", &WorldDamageTrack::SetPropAreaSizeScale);
					properties[17] = property;
					property = new fight::PropertyEnumConstList<ExplicitWorldDamageTrack>("propAreaSizeScaleFunction", gWorldDamageTrackPropAreaEmissionScaleFunctionTable, gWorldDamageTrackPropAreaEmissionScaleFunctionCount, &WorldDamageTrack::SetPropAreaSizeScaleFunction);
					properties[18] = property;
					fight::RegisterPropertyList(properties, &gExplicitWorldDamageTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1050F010
			fight::TrackFactory* CreateExplicitWorldDamageTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ExplicitWorldDamageTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1050F0D0
			void RegisterExplicitWorldDamageTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ExplicitWorldDamageTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWorldConeDamageTrackProperties;  // 0x1126F690

			// FUNCTION: ENGINE 0x1050E090
			bool WorldConeDamageTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E0B0
			bool WorldConeDamageTrack::SetPosition(const math::Vector& newValue)
			{
				position.x = newValue.x;
				position.y = newValue.y;
				position.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E0D0
			bool WorldConeDamageTrack::SetDirection(const math::Vector& newValue)
			{
				direction.x = newValue.x;
				direction.y = newValue.y;
				direction.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E0F0
			bool WorldConeDamageTrack::SetUp(const math::Vector& newValue)
			{
				up.x = newValue.x;
				up.y = newValue.y;
				up.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E110
			bool WorldConeDamageTrack::SetMinAngle(float newValue)
			{
				minAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E130
			bool WorldConeDamageTrack::SetMaxAngle(float newValue)
			{
				maxAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E150
			bool WorldConeDamageTrack::SetStartDistance(float newValue)
			{
				startDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E170
			bool WorldConeDamageTrack::SetLength(float newValue)
			{
				length = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E190
			bool WorldConeDamageTrack::SetMinDecals(int newValue)
			{
				minDecals = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E1A0
			bool WorldConeDamageTrack::SetMaxDecals(int newValue)
			{
				maxDecals = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E1B0
			bool WorldConeDamageTrack::SetMinDecalScale(float newValue)
			{
				minDecalScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E1D0
			bool WorldConeDamageTrack::SetMaxDecalScale(float newValue)
			{
				maxDecalScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E1F0
			bool WorldConeDamageTrack::SetDamageType(int newValue)
			{
				damageType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E200
			bool WorldConeDamageTrack::SetAttackType(int newValue)
			{
				attackType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E360
			bool WorldConeDamageTrack::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E380
			bool WorldConeDamageTrack::SetEffectType(const fight::Name& newValue)
			{
				effectType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E280
			fight::Property* WorldConeDamageTrack::GetProperty(int index)
			{
				return gWorldConeDamageTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1050E2A0
			void WorldConeDamageTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWorldConeDamageTrackProperties);
			}

			// FUNCTION: ENGINE 0x1050E4F0
			WorldConeDamageTrack::WorldConeDamageTrack() : direction(0.0f, 0.0f, -1.0f), position(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f), length(1e+01f), maxAngle(0.7853982f), maxDecalScale(1.0f), minAngle(0.7853982f), minDecalScale(1.0f), startDistance(1.0f), timeBegin(0.0f), attackType(0), damageType(0), maxDecals(1), minDecals(1)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1050E5D0
			float WorldConeDamageTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1050E5E0
			float WorldConeDamageTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1050E5F0
			WorldConeDamageTrack::~WorldConeDamageTrack()
			{
			}

			// FUNCTION: ENGINE 0x1050FD80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WorldConeDamageTrack::RegisterProperties()
			{
				if (gWorldConeDamageTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WorldConeDamageTrack>("timeBegin", &WorldConeDamageTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyVector<WorldConeDamageTrack>("position", &WorldConeDamageTrack::SetPosition);
					properties[1] = property;
					property = new fight::PropertyVector<WorldConeDamageTrack>("direction", &WorldConeDamageTrack::SetDirection);
					properties[2] = property;
					property = new fight::PropertyVector<WorldConeDamageTrack>("up", &WorldConeDamageTrack::SetUp);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<WorldConeDamageTrack>("minAngle", &WorldConeDamageTrack::SetMinAngle);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WorldConeDamageTrack>("maxAngle", &WorldConeDamageTrack::SetMaxAngle);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<WorldConeDamageTrack>("startDistance", &WorldConeDamageTrack::SetStartDistance);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<WorldConeDamageTrack>("length", &WorldConeDamageTrack::SetLength);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<WorldConeDamageTrack>("minDecals", &WorldConeDamageTrack::SetMinDecals);
					properties[8] = property;
					property = new fight::PropertyIntConstRange<WorldConeDamageTrack>("maxDecals", &WorldConeDamageTrack::SetMaxDecals);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<WorldConeDamageTrack>("minDecalScale", &WorldConeDamageTrack::SetMinDecalScale);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<WorldConeDamageTrack>("maxDecalScale", &WorldConeDamageTrack::SetMaxDecalScale);
					properties[11] = property;
					property = new fight::PropertyEnumConstList<WorldConeDamageTrack>("damageType", gWorldDamageTrackDamageTypeTable, gWorldDamageTrackDamageTypeCount, &WorldConeDamageTrack::SetDamageType);
					properties[12] = property;
					property = new fight::PropertyEnumConstList<WorldConeDamageTrack>("attackType", gWorldDamageTrackAttackTypeTable, gWorldDamageTrackAttackTypeCount, &WorldConeDamageTrack::SetAttackType);
					properties[13] = property;
					property = new fight::PropertyNameList<WorldConeDamageTrack>("hitType", &WorldConeDamageTrack::SetHitType);
					properties[14] = property;
					property = new fight::PropertyNameList<WorldConeDamageTrack>("effectType", &WorldConeDamageTrack::SetEffectType);
					properties[15] = property;
					fight::RegisterPropertyList(properties, &gWorldConeDamageTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1050F040
			fight::TrackFactory* CreateWorldConeDamageTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WorldConeDamageTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1050F100
			void RegisterWorldConeDamageTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WorldConeDamageTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gExplicitWorldConeDamageTrackProperties;  // 0x1126F694

			// FUNCTION: ENGINE 0x1050E3A0
			bool ExplicitWorldConeDamageTrack::SetObject(const fight::Name& newValue)
			{
				object = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E210
			bool ExplicitWorldConeDamageTrack::SetToBeContinued(bool newValue)
			{
				toBeContinued = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1050E2B0
			fight::Property* ExplicitWorldConeDamageTrack::GetProperty(int index)
			{
				return gExplicitWorldConeDamageTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1050E2D0
			void ExplicitWorldConeDamageTrack::ClearProperties()
			{
				fight::FreePropertyList(&gExplicitWorldConeDamageTrackProperties);
			}

			// FUNCTION: ENGINE 0x1050E600
			ExplicitWorldConeDamageTrack::ExplicitWorldConeDamageTrack() : WorldConeDamageTrack(), toBeContinued(true)
			{
			}

			// FUNCTION: ENGINE 0x1050E630
			ExplicitWorldConeDamageTrack::~ExplicitWorldConeDamageTrack()
			{
			}

			// FUNCTION: ENGINE 0x105101E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ExplicitWorldConeDamageTrack::RegisterProperties()
			{
				if (gExplicitWorldConeDamageTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ExplicitWorldConeDamageTrack>("object", &ExplicitWorldConeDamageTrack::SetObject);
					properties[0] = property;
					property = new fight::PropertyBool<ExplicitWorldConeDamageTrack>("toBeContinued", &ExplicitWorldConeDamageTrack::SetToBeContinued);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldConeDamageTrack>("timeBegin", &WorldConeDamageTrack::SetTimeBegin);
					properties[2] = property;
					property = new fight::PropertyVector<ExplicitWorldConeDamageTrack>("position", &WorldConeDamageTrack::SetPosition);
					properties[3] = property;
					property = new fight::PropertyVector<ExplicitWorldConeDamageTrack>("direction", &WorldConeDamageTrack::SetDirection);
					properties[4] = property;
					property = new fight::PropertyVector<ExplicitWorldConeDamageTrack>("up", &WorldConeDamageTrack::SetUp);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldConeDamageTrack>("minAngle", &WorldConeDamageTrack::SetMinAngle);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldConeDamageTrack>("maxAngle", &WorldConeDamageTrack::SetMaxAngle);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldConeDamageTrack>("startDistance", &WorldConeDamageTrack::SetStartDistance);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldConeDamageTrack>("length", &WorldConeDamageTrack::SetLength);
					properties[9] = property;
					property = new fight::PropertyIntConstRange<ExplicitWorldConeDamageTrack>("minDecals", &WorldConeDamageTrack::SetMinDecals);
					properties[10] = property;
					property = new fight::PropertyIntConstRange<ExplicitWorldConeDamageTrack>("maxDecals", &WorldConeDamageTrack::SetMaxDecals);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldConeDamageTrack>("minDecalScale", &WorldConeDamageTrack::SetMinDecalScale);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<ExplicitWorldConeDamageTrack>("maxDecalScale", &WorldConeDamageTrack::SetMaxDecalScale);
					properties[13] = property;
					property = new fight::PropertyEnumConstList<ExplicitWorldConeDamageTrack>("damageType", gWorldDamageTrackDamageTypeTable, gWorldDamageTrackDamageTypeCount, &WorldConeDamageTrack::SetDamageType);
					properties[14] = property;
					property = new fight::PropertyEnumConstList<ExplicitWorldConeDamageTrack>("attackType", gWorldDamageTrackAttackTypeTable, gWorldDamageTrackAttackTypeCount, &WorldConeDamageTrack::SetAttackType);
					properties[15] = property;
					property = new fight::PropertyNameList<ExplicitWorldConeDamageTrack>("hitType", &WorldConeDamageTrack::SetHitType);
					properties[16] = property;
					property = new fight::PropertyNameList<ExplicitWorldConeDamageTrack>("effectType", &WorldConeDamageTrack::SetEffectType);
					properties[17] = property;
					fight::RegisterPropertyList(properties, &gExplicitWorldConeDamageTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1050F070
			fight::TrackFactory* CreateExplicitWorldConeDamageTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ExplicitWorldConeDamageTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1050F130
			void RegisterExplicitWorldConeDamageTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ExplicitWorldConeDamageTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<WorldDamageTrack>;
			template class fight::PropertyNameList<WorldDamageTrack>;
			template class fight::PropertyVector<WorldDamageTrack>;
			template class fight::PropertyBool<WorldDamageTrack>;
			template class fight::PropertyEnumConstList<WorldDamageTrack>;
			template class fight::TrackFactoryTemplate<WorldDamageTrack>;
			template class fight::TrackFactoryCasterTemplate<WorldDamageTrack>;
			template class fight::PropertyName<ExplicitWorldDamageTrack>;
			template class fight::PropertyBool<ExplicitWorldDamageTrack>;
			template class fight::PropertyFloatConstRange<ExplicitWorldDamageTrack>;
			template class fight::PropertyNameList<ExplicitWorldDamageTrack>;
			template class fight::PropertyVector<ExplicitWorldDamageTrack>;
			template class fight::PropertyEnumConstList<ExplicitWorldDamageTrack>;
			template class fight::TrackFactoryTemplate<ExplicitWorldDamageTrack>;
			template class fight::TrackFactoryCasterTemplate<ExplicitWorldDamageTrack>;
			template class fight::PropertyFloatConstRange<WorldConeDamageTrack>;
			template class fight::PropertyVector<WorldConeDamageTrack>;
			template class fight::PropertyIntConstRange<WorldConeDamageTrack>;
			template class fight::PropertyEnumConstList<WorldConeDamageTrack>;
			template class fight::PropertyNameList<WorldConeDamageTrack>;
			template class fight::TrackFactoryTemplate<WorldConeDamageTrack>;
			template class fight::TrackFactoryCasterTemplate<WorldConeDamageTrack>;
			template class fight::PropertyName<ExplicitWorldConeDamageTrack>;
			template class fight::PropertyBool<ExplicitWorldConeDamageTrack>;
			template class fight::PropertyFloatConstRange<ExplicitWorldConeDamageTrack>;
			template class fight::PropertyVector<ExplicitWorldConeDamageTrack>;
			template class fight::PropertyIntConstRange<ExplicitWorldConeDamageTrack>;
			template class fight::PropertyEnumConstList<ExplicitWorldConeDamageTrack>;
			template class fight::PropertyNameList<ExplicitWorldConeDamageTrack>;
			template class fight::TrackFactoryTemplate<ExplicitWorldConeDamageTrack>;
			template class fight::TrackFactoryCasterTemplate<ExplicitWorldConeDamageTrack>;
		}
	}
}

namespace proto
{
	namespace fightitems
	{
		// FUNCTION: ENGINE 0x10502080
		bool RegisterAt10502080Factories(fight::TrackRegistry* registry)
		{
			motion::RegisterWorldDamageTrackFactory(registry, "worldDamage");
			motion::RegisterWorldConeDamageTrackFactory(registry, "worldConeDamage");
			return true;
		}

		// FUNCTION: ENGINE 0x105020B0
		bool RegisterAt105020B0Factories(fight::TrackRegistry* registry)
		{
			motion::RegisterExplicitWorldDamageTrackFactory(registry, "worldDamage");
			motion::RegisterExplicitWorldConeDamageTrackFactory(registry, "worldConeDamage");
			return true;
		}
	}
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// FUNCTION: ENGINE 0x1011A800
			bool ExplicitWorldDamageTrack::GetToBeContinued() const
			{
				return toBeContinued;
			}

			// FUNCTION: ENGINE 0x1011A800
			bool ExplicitWorldConeDamageTrack::GetToBeContinued() const
			{
				return toBeContinued;
			}
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1050E640
// FUNCTION: ENGINE 0x1050E650
// FUNCTION: ENGINE 0x1050E680
// FUNCTION: ENGINE 0x1050E690
// FUNCTION: ENGINE 0x1050E6C0
// FUNCTION: ENGINE 0x1050E6D0
// FUNCTION: ENGINE 0x1050E700
// FUNCTION: ENGINE 0x1050E710
// FUNCTION: ENGINE 0x1050E740
// FUNCTION: ENGINE 0x1050E770
// FUNCTION: ENGINE 0x1050E7A0
// FUNCTION: ENGINE 0x1050E7D0
// FUNCTION: ENGINE 0x1050E800
// FUNCTION: ENGINE 0x1050E830
// FUNCTION: ENGINE 0x1050E860
// FUNCTION: ENGINE 0x1050E870
// FUNCTION: ENGINE 0x1050E8A0
// FUNCTION: ENGINE 0x1050E8C0
// FUNCTION: ENGINE 0x1050E8D0
// FUNCTION: ENGINE 0x1050E900
// FUNCTION: ENGINE 0x1050E920
// FUNCTION: ENGINE 0x1050E930
// FUNCTION: ENGINE 0x1050E970
// FUNCTION: ENGINE 0x1050E980
// FUNCTION: ENGINE 0x1050E9B0
// FUNCTION: ENGINE 0x1050E9D0
// FUNCTION: ENGINE 0x1050E9E0
// FUNCTION: ENGINE 0x1050EA10
// FUNCTION: ENGINE 0x1050EA30
// FUNCTION: ENGINE 0x1050EA40
// FUNCTION: ENGINE 0x1050EA70
// FUNCTION: ENGINE 0x1050EAA0
// FUNCTION: ENGINE 0x1050EAB0
// FUNCTION: ENGINE 0x1050EAE0
// FUNCTION: ENGINE 0x1050EB00
// FUNCTION: ENGINE 0x1050EB10
// FUNCTION: ENGINE 0x1050EB50
// FUNCTION: ENGINE 0x1050EB60
// FUNCTION: ENGINE 0x1050EB90
// FUNCTION: ENGINE 0x1050EBB0
// FUNCTION: ENGINE 0x1050EBC0
// FUNCTION: ENGINE 0x1050EBF0
// FUNCTION: ENGINE 0x1050EC20
// FUNCTION: ENGINE 0x1050EC30
// FUNCTION: ENGINE 0x1050EC60
// FUNCTION: ENGINE 0x1050EC80
// FUNCTION: ENGINE 0x1050EC90
// FUNCTION: ENGINE 0x1050ECC0
// FUNCTION: ENGINE 0x1050ECE0
// FUNCTION: ENGINE 0x1050ECF0
// FUNCTION: ENGINE 0x1050ED30
// FUNCTION: ENGINE 0x1050ED40
// FUNCTION: ENGINE 0x1050ED70
// FUNCTION: ENGINE 0x1050ED90
// FUNCTION: ENGINE 0x1050EDA0
// FUNCTION: ENGINE 0x1050EDD0
// FUNCTION: ENGINE 0x1050EDF0
// FUNCTION: ENGINE 0x1050EE00
// FUNCTION: ENGINE 0x1050EE30
// FUNCTION: ENGINE 0x1050EE60
// FUNCTION: ENGINE 0x1050EE70
// FUNCTION: ENGINE 0x1050EEA0
// FUNCTION: ENGINE 0x1050EEC0
// FUNCTION: ENGINE 0x1050EED0
// FUNCTION: ENGINE 0x1050EF00
// FUNCTION: ENGINE 0x1050EF20
// FUNCTION: ENGINE 0x1050EF30
// FUNCTION: ENGINE 0x1050EF70
// FUNCTION: ENGINE 0x1050EF80
// FUNCTION: ENGINE 0x1050EFB0
// FUNCTION: ENGINE 0x1050EFD0
// FUNCTION: ENGINE 0x1050F160
// FUNCTION: ENGINE 0x1050F190
// FUNCTION: ENGINE 0x1050F1B0
// FUNCTION: ENGINE 0x1050F1C0
// FUNCTION: ENGINE 0x1050F1F0
// FUNCTION: ENGINE 0x1050F210
// FUNCTION: ENGINE 0x1050F240
// FUNCTION: ENGINE 0x1050F260
// FUNCTION: ENGINE 0x1050F270
// FUNCTION: ENGINE 0x1050F2A0
// FUNCTION: ENGINE 0x1050F2C0
// FUNCTION: ENGINE 0x1050F2D0
// FUNCTION: ENGINE 0x1050F300
// FUNCTION: ENGINE 0x1050F320
// FUNCTION: ENGINE 0x1050F350
// FUNCTION: ENGINE 0x1050F370
// FUNCTION: ENGINE 0x105106C0
// FUNCTION: ENGINE 0x105106F0
// FUNCTION: ENGINE 0x10510710
// FUNCTION: ENGINE 0x10510740
// FUNCTION: ENGINE 0x10510770
// FUNCTION: ENGINE 0x105107A0
// FUNCTION: ENGINE 0x105107C0
// FUNCTION: ENGINE 0x105107F0
// FUNCTION: ENGINE 0x10510820
// FUNCTION: ENGINE 0x10510870
// FUNCTION: ENGINE 0x105108C0
// FUNCTION: ENGINE 0x10510910
