// Fight items of the motion group: CollisionHitTrack (unit 0x1014B6C0 - 0x1014D220; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_collisionhit.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gCollisionHitTrackProperties;  // 0x11254378

			// FUNCTION: ENGINE 0x1014B6C0
			bool CollisionHitTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B6E0
			bool CollisionHitTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B700
			bool CollisionHitTrack::SetUseShapecast(bool newValue)
			{
				useShapecast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B730
			bool CollisionHitTrack::SetCollisionCountMax(int newValue)
			{
				collisionCountMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B750
			bool CollisionHitTrack::SetTimeBetweenHits(float newValue)
			{
				timeBetweenHits = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BCC0
			bool CollisionHitTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BCE0
			bool CollisionHitTrack::SetJointEnd(const fight::Name& newValue)
			{
				jointEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B770
			bool CollisionHitTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B7A0
			bool CollisionHitTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B7C0
			bool CollisionHitTrack::SetArcOffset(float newValue)
			{
				arcOffset = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B7F0
			bool CollisionHitTrack::SetArcRange(float newValue)
			{
				arcRange = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B820
			bool CollisionHitTrack::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B840
			bool CollisionHitTrack::SetDamageMin(float newValue)
			{
				damageMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B860
			bool CollisionHitTrack::SetDamageMax(float newValue)
			{
				damageMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B880
			bool CollisionHitTrack::SetUseTransformationDamageMultiplier(bool newValue)
			{
				useTransformationDamageMultiplier = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B8A0
			bool CollisionHitTrack::SetUseWeaponDamageMultiplier(bool newValue)
			{
				useWeaponDamageMultiplier = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B8C0
			bool CollisionHitTrack::SetFriendlyFire(float newValue)
			{
				friendlyFire = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B8E0
			bool CollisionHitTrack::SetAttackType(int newValue)
			{
				attackType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BD00
			bool CollisionHitTrack::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B900
			bool CollisionHitTrack::SetDamageType(int newValue)
			{
				damageType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BD20
			bool CollisionHitTrack::SetEffectType(const fight::Name& newValue)
			{
				effectType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B920
			bool CollisionHitTrack::SetScaleX(float newValue)
			{
				scaleX = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B940
			bool CollisionHitTrack::SetScaleY(float newValue)
			{
				scaleY = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B960
			bool CollisionHitTrack::SetEffectScale(float newValue)
			{
				effectScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B980
			bool CollisionHitTrack::SetPropAreaEmissionScale(float newValue)
			{
				propAreaEmissionScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B9A0
			bool CollisionHitTrack::SetPropAreaEmissionScaleFunction(int newValue)
			{
				propAreaEmissionScaleFunction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B9C0
			bool CollisionHitTrack::SetPropAreaSizeScale(float newValue)
			{
				propAreaSizeScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014B9E0
			bool CollisionHitTrack::SetPropAreaSizeScaleFunction(int newValue)
			{
				propAreaSizeScaleFunction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BA00
			bool CollisionHitTrack::SetImpulseMin(const math::Vector& newValue)
			{
				impulseMin.x = newValue.x;
				impulseMin.y = newValue.y;
				impulseMin.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BA30
			bool CollisionHitTrack::SetImpulseMax(const math::Vector& newValue)
			{
				impulseMax.x = newValue.x;
				impulseMax.y = newValue.y;
				impulseMax.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BA60
			bool CollisionHitTrack::SetImpulseRandomPlusMinus(float newValue)
			{
				impulseRandomPlusMinus = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BA80
			bool CollisionHitTrack::SetUseMotion(bool newValue)
			{
				useMotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BAA0
			bool CollisionHitTrack::SetCollisionDirection(const math::Vector& newValue)
			{
				collisionDirection.x = newValue.x;
				collisionDirection.y = newValue.y;
				collisionDirection.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BAD0
			bool CollisionHitTrack::SetDeformDirStr(float newValue)
			{
				deformDirStr = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BAF0
			bool CollisionHitTrack::SetDeformStr(float newValue)
			{
				deformStr = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BD40
			bool CollisionHitTrack::SetCollisionFlag(const fight::Name& newValue)
			{
				collisionFlag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BB10
			fight::BranchHolder* CollisionHitTrack::SetGiverBranch()
			{
				return &giverBranch;
			}

			// FUNCTION: ENGINE 0x1014BB20
			fight::BranchHolder* CollisionHitTrack::SetReceiverBranch()
			{
				return &receiverBranch;
			}

			// FUNCTION: ENGINE 0x1014BB30
			bool CollisionHitTrack::SetUseDamageOriginator(bool newValue)
			{
				useDamageOriginator = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BB50
			bool CollisionHitTrack::SetSendAlert(bool newValue)
			{
				sendAlert = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BB80
			bool CollisionHitTrack::SetSendOnlyToAIManager(bool newValue)
			{
				sendOnlyToAIManager = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BBB0
			bool CollisionHitTrack::SetUseOriginatorToValidate(bool newValue)
			{
				useOriginatorToValidate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BBD0
			bool CollisionHitTrack::SetIsThrown(bool newValue)
			{
				isThrown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BBF0
			bool CollisionHitTrack::SetMomentumDamageVelocity(float newValue)
			{
				momentumDamageVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BC10
			bool CollisionHitTrack::SetMomentumDamageMax(float newValue)
			{
				momentumDamageMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BC30
			bool CollisionHitTrack::SetTravelVelocity(float newValue)
			{
				travelVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BC50
			bool CollisionHitTrack::SetTravelTowardTarget(int newValue)
			{
				travelTowardTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BC70
			bool CollisionHitTrack::SetIgnorePowerTarget(bool newValue)
			{
				ignorePowerTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014BC90
			fight::Property* CollisionHitTrack::GetProperty(int index)
			{
				return gCollisionHitTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014BCB0
			void CollisionHitTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCollisionHitTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014BD60
			CollisionHitTrack::CollisionHitTrack() : giverBranch(0), receiverBranch(0), collisionDirection(0.0f, 0.0f, 0.0f), impulseMax(0.0f, 0.0f, 0.0f), impulseMin(0.0f, 0.0f, 0.0f), offset(0.0f, 0.0f, 0.0f), arcOffset(0.0f), arcRange(0.0f), damageMax(0.0f), damageMin(0.0f), deformDirStr(1.0f), deformStr(1.0f), effectScale(1.0f), friendlyFire(1.0f), impulseRandomPlusMinus(0.0f), momentumDamageMax(0.0f), momentumDamageVelocity(0.0f), propAreaEmissionScale(0.0f), propAreaSizeScale(0.0f), radius(1.0f), scaleX(1.0f), scaleY(1.0f), timeBegin(0.0f), timeBetweenHits(-1.0f), timeEnd(-1.0f), travelVelocity(0.0f), attackType(0), collisionCountMax(-1), damageType(0), propAreaEmissionScaleFunction(0), propAreaSizeScaleFunction(0), travelTowardTarget(0), collideWith(gCollisionHitTrackCollideWithDefault), ignorePowerTarget(false), isThrown(false), sendAlert(true), sendOnlyToAIManager(false), useDamageOriginator(false), useMotion(false), useOriginatorToValidate(false), useShapecast(true), useTransformationDamageMultiplier(true), useWeaponDamageMultiplier(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1014BF90
			float CollisionHitTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1014BFA0
			float CollisionHitTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1014BFB0
			CollisionHitTrack::~CollisionHitTrack()
			{
			}

			// FUNCTION: ENGINE 0x1014C4D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CollisionHitTrack::RegisterProperties()
			{
				if (gCollisionHitTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("timeBegin", &CollisionHitTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("timeEnd", &CollisionHitTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("useShapecast", &CollisionHitTrack::SetUseShapecast);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<CollisionHitTrack>("collisionCountMax", &CollisionHitTrack::SetCollisionCountMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("timeBetweenHits", &CollisionHitTrack::SetTimeBetweenHits);
					properties[4] = property;
					property = new fight::PropertyNameList<CollisionHitTrack>("joint", &CollisionHitTrack::SetJoint);
					properties[5] = property;
					property = new fight::PropertyNameList<CollisionHitTrack>("jointEnd", &CollisionHitTrack::SetJointEnd);
					properties[6] = property;
					property = new fight::PropertyVector<CollisionHitTrack>("offset", &CollisionHitTrack::SetOffset);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("radius", &CollisionHitTrack::SetRadius);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("arcOffset", &CollisionHitTrack::SetArcOffset);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("arcRange", &CollisionHitTrack::SetArcRange);
					properties[10] = property;
					property = new fight::PropertyBitfieldConstList<CollisionHitTrack>("collideWith", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &CollisionHitTrack::SetCollideWith);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("damageMin", &CollisionHitTrack::SetDamageMin);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("damageMax", &CollisionHitTrack::SetDamageMax);
					properties[13] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("useTransformationDamageMultiplier", &CollisionHitTrack::SetUseTransformationDamageMultiplier);
					properties[14] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("useWeaponDamageMultiplier", &CollisionHitTrack::SetUseWeaponDamageMultiplier);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("friendlyFire", &CollisionHitTrack::SetFriendlyFire);
					properties[16] = property;
					property = new fight::PropertyEnumConstList<CollisionHitTrack>("attackType", gTendrilDevastatorTrackAttackTypeTable, gTendrilDevastatorTrackAttackTypeCount, &CollisionHitTrack::SetAttackType);
					properties[17] = property;
					property = new fight::PropertyNameList<CollisionHitTrack>("hitType", &CollisionHitTrack::SetHitType);
					properties[18] = property;
					property = new fight::PropertyEnumConstList<CollisionHitTrack>("damageType", gDevastatorTargetHitTrackDamageTypeTable, gDevastatorTargetHitTrackDamageTypeCount, &CollisionHitTrack::SetDamageType);
					properties[19] = property;
					property = new fight::PropertyNameList<CollisionHitTrack>("effectType", &CollisionHitTrack::SetEffectType);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("scaleX", &CollisionHitTrack::SetScaleX);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("scaleY", &CollisionHitTrack::SetScaleY);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("effectScale", &CollisionHitTrack::SetEffectScale);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("propAreaEmissionScale", &CollisionHitTrack::SetPropAreaEmissionScale);
					properties[24] = property;
					property = new fight::PropertyEnumConstList<CollisionHitTrack>("propAreaEmissionScaleFunction", gCollisionHitTrackPropAreaEmissionScaleFunctionTable, gCollisionHitTrackPropAreaEmissionScaleFunctionCount, &CollisionHitTrack::SetPropAreaEmissionScaleFunction);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("propAreaSizeScale", &CollisionHitTrack::SetPropAreaSizeScale);
					properties[26] = property;
					property = new fight::PropertyEnumConstList<CollisionHitTrack>("propAreaSizeScaleFunction", gCollisionHitTrackPropAreaEmissionScaleFunctionTable, gCollisionHitTrackPropAreaEmissionScaleFunctionCount, &CollisionHitTrack::SetPropAreaSizeScaleFunction);
					properties[27] = property;
					property = new fight::PropertyVector<CollisionHitTrack>("impulseMin", &CollisionHitTrack::SetImpulseMin);
					properties[28] = property;
					property = new fight::PropertyVector<CollisionHitTrack>("impulseMax", &CollisionHitTrack::SetImpulseMax);
					properties[29] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("impulseRandomPlusMinus", &CollisionHitTrack::SetImpulseRandomPlusMinus);
					properties[30] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("useMotion", &CollisionHitTrack::SetUseMotion);
					properties[31] = property;
					property = new fight::PropertyVector<CollisionHitTrack>("collisionDirection", &CollisionHitTrack::SetCollisionDirection);
					properties[32] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("deformDirStr", &CollisionHitTrack::SetDeformDirStr);
					properties[33] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("deformStr", &CollisionHitTrack::SetDeformStr);
					properties[34] = property;
					property = new fight::PropertyName<CollisionHitTrack>("collisionFlag", &CollisionHitTrack::SetCollisionFlag);
					properties[35] = property;
					property = new fight::PropertyBranch<CollisionHitTrack>("giverBranch", &CollisionHitTrack::SetGiverBranch);
					properties[36] = property;
					property = new fight::PropertyBranch<CollisionHitTrack>("receiverBranch", &CollisionHitTrack::SetReceiverBranch);
					properties[37] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("useDamageOriginator", &CollisionHitTrack::SetUseDamageOriginator);
					properties[38] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("sendAlert", &CollisionHitTrack::SetSendAlert);
					properties[39] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("sendOnlyToAIManager", &CollisionHitTrack::SetSendOnlyToAIManager);
					properties[40] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("useOriginatorToValidate", &CollisionHitTrack::SetUseOriginatorToValidate);
					properties[41] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("isThrown", &CollisionHitTrack::SetIsThrown);
					properties[42] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("momentumDamageVelocity", &CollisionHitTrack::SetMomentumDamageVelocity);
					properties[43] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("momentumDamageMax", &CollisionHitTrack::SetMomentumDamageMax);
					properties[44] = property;
					property = new fight::PropertyFloatConstRange<CollisionHitTrack>("travelVelocity", &CollisionHitTrack::SetTravelVelocity);
					properties[45] = property;
					property = new fight::PropertyEnumConstList<CollisionHitTrack>("travelTowardTarget", gCollisionHitTrackTravelTowardTargetTable, gCollisionHitTrackTravelTowardTargetCount, &CollisionHitTrack::SetTravelTowardTarget);
					properties[46] = property;
					property = new fight::PropertyBool<CollisionHitTrack>("ignorePowerTarget", &CollisionHitTrack::SetIgnorePowerTarget);
					properties[47] = property;
					fight::RegisterPropertyList(properties, &gCollisionHitTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014C3C0
			fight::TrackFactory* CreateCollisionHitTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CollisionHitTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014C3F0
			void RegisterCollisionHitTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CollisionHitTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<CollisionHitTrack>;
			template class fight::PropertyBool<CollisionHitTrack>;
			template class fight::PropertyIntConstRange<CollisionHitTrack>;
			template class fight::PropertyNameList<CollisionHitTrack>;
			template class fight::PropertyVector<CollisionHitTrack>;
			template class fight::PropertyBitfieldConstList<CollisionHitTrack>;
			template class fight::PropertyEnumConstList<CollisionHitTrack>;
			template class fight::PropertyName<CollisionHitTrack>;
			template class fight::PropertyBranch<CollisionHitTrack>;
			template class fight::TrackFactoryTemplate<CollisionHitTrack>;
			template class fight::TrackFactoryCasterTemplate<CollisionHitTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
