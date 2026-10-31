// Fight items of the playback group: SpawnObjectTrack, ManageLifetimeTrack (unit 0x1025C660 - 0x1025E0E0; no assert path, the file name is a guess).
#include "code/proto/fightitems/playback/playback_spawnobject.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace playback
		{
			fight::Property** gSpawnObjectTrackProperties;  // 0x11255CFC

			// FUNCTION: ENGINE 0x1025C660
			bool SpawnObjectTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CBB0
			bool SpawnObjectTrack::SetTemplateName(const fight::Name& newValue)
			{
				templateName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CBD0
			bool SpawnObjectTrack::SetObjectName(const fight::Name& newValue)
			{
				objectName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C680
			bool SpawnObjectTrack::SetAddSuffix(bool newValue)
			{
				addSuffix = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CB50
			bool SpawnObjectTrack::SetInitialState(const char* newValue)
			{
				initialState = fight::ReplaceString(initialState, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x1025CBF0
			bool SpawnObjectTrack::SetSpecificPlaybackSet(const fight::Name& newValue)
			{
				specificPlaybackSet = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C6A0
			bool SpawnObjectTrack::SetSpawnSpace(int newValue)
			{
				spawnSpace = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CC10
			bool SpawnObjectTrack::SetSpawnJoint(const fight::Name& newValue)
			{
				spawnJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C6C0
			bool SpawnObjectTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C6E0
			bool SpawnObjectTrack::SetOrientation(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				orientation.x = scaled.x;
				orientation.y = scaled.y;
				orientation.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C730
			bool SpawnObjectTrack::SetAttachToParent(bool newValue)
			{
				attachToParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C760
			bool SpawnObjectTrack::SetDetachAfterSpawn(bool newValue)
			{
				detachAfterSpawn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C790
			bool SpawnObjectTrack::SetAICharacter(bool newValue)
			{
				aICharacter = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CC30
			bool SpawnObjectTrack::SetAutomaticTag(const fight::Name& newValue)
			{
				automaticTag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CC50
			bool SpawnObjectTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C7B0
			bool SpawnObjectTrack::SetCopyPose(bool newValue)
			{
				copyPose = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C7D0
			bool SpawnObjectTrack::SetInheritSpawnerVelocity(bool newValue)
			{
				inheritSpawnerVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C800
			bool SpawnObjectTrack::SetLinearVelocity(const math::Vector& newValue)
			{
				linearVelocity.x = newValue.x;
				linearVelocity.y = newValue.y;
				linearVelocity.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C820
			bool SpawnObjectTrack::SetAngularVelocity(const math::Vector& newValue)
			{
				angularVelocity.x = newValue.x;
				angularVelocity.y = newValue.y;
				angularVelocity.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C840
			bool SpawnObjectTrack::SetCollideWithSpawnerDelay(float newValue)
			{
				collideWithSpawnerDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C860
			bool SpawnObjectTrack::SetSpawnSleeping(bool newValue)
			{
				spawnSleeping = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C890
			bool SpawnObjectTrack::SetManageLifetime(bool newValue)
			{
				manageLifetime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C8C0
			bool SpawnObjectTrack::SetManageLifetimeThrownProp(bool newValue)
			{
				manageLifetimeThrownProp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C8E0
			bool SpawnObjectTrack::SetInheritSpawnerTarget(bool newValue)
			{
				inheritSpawnerTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C900
			bool SpawnObjectTrack::SetInheritSpawnerCharge(int newValue)
			{
				inheritSpawnerCharge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C920
			bool SpawnObjectTrack::SetUseParentScale(bool newValue)
			{
				useParentScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C940
			bool SpawnObjectTrack::SetSetScale(bool newValue)
			{
				setScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C960
			bool SpawnObjectTrack::SetScale(const math::Vector& newValue)
			{
				scale.x = newValue.x;
				scale.y = newValue.y;
				scale.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C990
			bool SpawnObjectTrack::SetProbability(float newValue)
			{
				probability = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C9B0
			bool SpawnObjectTrack::SetUseSpawnerAsDamageOriginator(bool newValue)
			{
				useSpawnerAsDamageOriginator = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025C9E0
			bool SpawnObjectTrack::SetDamageOriginatorFromSpawner(bool newValue)
			{
				damageOriginatorFromSpawner = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CA00
			bool SpawnObjectTrack::SetTransferTargetLocks(bool newValue)
			{
				transferTargetLocks = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CA20
			bool SpawnObjectTrack::SetSendMessageToScenarioTree(bool newValue)
			{
				sendMessageToScenarioTree = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CA40
			bool SpawnObjectTrack::SetApplyColourTint(bool newValue)
			{
				applyColourTint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CA70
			bool SpawnObjectTrack::SetInheritPackage(bool newValue)
			{
				inheritPackage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CA90
			bool SpawnObjectTrack::SetTintColour(const math::Colour128& newValue)
			{
				tintColour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CAC0
			bool SpawnObjectTrack::SetCacheDamageOrigionatorAsCollider(bool newValue)
			{
				cacheDamageOrigionatorAsCollider = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CB20
			fight::Property* SpawnObjectTrack::GetProperty(int index)
			{
				return gSpawnObjectTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1025CB40
			void SpawnObjectTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSpawnObjectTrackProperties);
			}

			// FUNCTION: ENGINE 0x1025CC90
			SpawnObjectTrack::SpawnObjectTrack() : tintColour(0.5019608f, 0.5019608f, 0.5019608f, 1.0f), angularVelocity(0.0f, 0.0f, 0.0f), linearVelocity(0.0f, 0.0f, 0.0f), offset(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), initialState(0), collideWithSpawnerDelay(0.5f), probability(1.0f), timeBegin(0.0f), inheritSpawnerCharge(0), spawnSpace(0), aICharacter(false), addSuffix(true), applyColourTint(false), attachToParent(false), cacheDamageOrigionatorAsCollider(true), copyPose(false), damageOriginatorFromSpawner(true), detachAfterSpawn(false), inheritPackage(true), inheritSpawnerTarget(false), inheritSpawnerVelocity(false), manageLifetime(true), manageLifetimeThrownProp(false), sendMessageToScenarioTree(false), setScale(false), spawnSleeping(false), transferTargetLocks(false), useParentScale(false), useSpawnerAsDamageOriginator(false)
			{
			}

			// FUNCTION: ENGINE 0x1025CDE0
			float SpawnObjectTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1025CDF0
			float SpawnObjectTrack::Slot10() const
			{
				return -1.0f;
			}

			// FUNCTION: ENGINE 0x1025CE00
			SpawnObjectTrack::~SpawnObjectTrack()
			{
				delete[] initialState;
			}

			// FUNCTION: ENGINE 0x1025D4C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpawnObjectTrack::RegisterProperties()
			{
				if (gSpawnObjectTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SpawnObjectTrack>("timeBegin", &SpawnObjectTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<SpawnObjectTrack>("templateName", &SpawnObjectTrack::SetTemplateName);
					properties[1] = property;
					property = new fight::PropertyName<SpawnObjectTrack>("objectName", &SpawnObjectTrack::SetObjectName);
					properties[2] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("addSuffix", &SpawnObjectTrack::SetAddSuffix);
					properties[3] = property;
					property = new fight::PropertyString<SpawnObjectTrack>("initialState", &SpawnObjectTrack::SetInitialState);
					properties[4] = property;
					property = new fight::PropertyName<SpawnObjectTrack>("specificPlaybackSet", &SpawnObjectTrack::SetSpecificPlaybackSet);
					properties[5] = property;
					property = new fight::PropertyEnumConstList<SpawnObjectTrack>("spawnSpace", motion::gShootTrackFixedDirectionSpaceTable, motion::gShootTrackFixedDirectionSpaceCount, &SpawnObjectTrack::SetSpawnSpace);
					properties[6] = property;
					property = new fight::PropertyNameList<SpawnObjectTrack>("spawnJoint", &SpawnObjectTrack::SetSpawnJoint);
					properties[7] = property;
					property = new fight::PropertyVector<SpawnObjectTrack>("offset", &SpawnObjectTrack::SetOffset);
					properties[8] = property;
					property = new fight::PropertyVector<SpawnObjectTrack>("orientation", &SpawnObjectTrack::SetOrientation);
					properties[9] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("attachToParent", &SpawnObjectTrack::SetAttachToParent);
					properties[10] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("detachAfterSpawn", &SpawnObjectTrack::SetDetachAfterSpawn);
					properties[11] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("aICharacter", &SpawnObjectTrack::SetAICharacter);
					properties[12] = property;
					property = new fight::PropertyName<SpawnObjectTrack>("automaticTag", &SpawnObjectTrack::SetAutomaticTag);
					properties[13] = property;
					property = new fight::PropertyNameList<SpawnObjectTrack>("grabSlot", &SpawnObjectTrack::SetGrabSlot);
					properties[14] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("copyPose", &SpawnObjectTrack::SetCopyPose);
					properties[15] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("inheritSpawnerVelocity", &SpawnObjectTrack::SetInheritSpawnerVelocity);
					properties[16] = property;
					property = new fight::PropertyVector<SpawnObjectTrack>("linearVelocity", &SpawnObjectTrack::SetLinearVelocity);
					properties[17] = property;
					property = new fight::PropertyVector<SpawnObjectTrack>("angularVelocity", &SpawnObjectTrack::SetAngularVelocity);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<SpawnObjectTrack>("collideWithSpawnerDelay", &SpawnObjectTrack::SetCollideWithSpawnerDelay);
					properties[19] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("spawnSleeping", &SpawnObjectTrack::SetSpawnSleeping);
					properties[20] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("manageLifetime", &SpawnObjectTrack::SetManageLifetime);
					properties[21] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("manageLifetimeThrownProp", &SpawnObjectTrack::SetManageLifetimeThrownProp);
					properties[22] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("inheritSpawnerTarget", &SpawnObjectTrack::SetInheritSpawnerTarget);
					properties[23] = property;
					property = new fight::PropertyEnumConstList<SpawnObjectTrack>("inheritSpawnerCharge", motion::gChargeConditionTypeTable, motion::gChargeConditionTypeCount, &SpawnObjectTrack::SetInheritSpawnerCharge);
					properties[24] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("useParentScale", &SpawnObjectTrack::SetUseParentScale);
					properties[25] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("setScale", &SpawnObjectTrack::SetSetScale);
					properties[26] = property;
					property = new fight::PropertyVector<SpawnObjectTrack>("scale", &SpawnObjectTrack::SetScale);
					properties[27] = property;
					property = new fight::PropertyFloatConstRange<SpawnObjectTrack>("probability", &SpawnObjectTrack::SetProbability);
					properties[28] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("useSpawnerAsDamageOriginator", &SpawnObjectTrack::SetUseSpawnerAsDamageOriginator);
					properties[29] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("damageOriginatorFromSpawner", &SpawnObjectTrack::SetDamageOriginatorFromSpawner);
					properties[30] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("transferTargetLocks", &SpawnObjectTrack::SetTransferTargetLocks);
					properties[31] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("sendMessageToScenarioTree", &SpawnObjectTrack::SetSendMessageToScenarioTree);
					properties[32] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("applyColourTint", &SpawnObjectTrack::SetApplyColourTint);
					properties[33] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("inheritPackage", &SpawnObjectTrack::SetInheritPackage);
					properties[34] = property;
					property = new fight::PropertyColour<SpawnObjectTrack>("tintColour", &SpawnObjectTrack::SetTintColour);
					properties[35] = property;
					property = new fight::PropertyBool<SpawnObjectTrack>("cacheDamageOrigionatorAsCollider", &SpawnObjectTrack::SetCacheDamageOrigionatorAsCollider);
					properties[36] = property;
					fight::RegisterPropertyList(properties, &gSpawnObjectTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1025D2F0
			fight::TrackFactory* CreateSpawnObjectTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnObjectTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1025D350
			void RegisterSpawnObjectTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnObjectTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gManageLifetimeTrackProperties;  // 0x11255D00

			// FUNCTION: ENGINE 0x1025CAE0
			bool ManageLifetimeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CB00
			bool ManageLifetimeTrack::SetManageLifetime(bool newValue)
			{
				manageLifetime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CB10
			bool ManageLifetimeTrack::SetAttachedToParent(bool newValue)
			{
				attachedToParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CC70
			bool ManageLifetimeTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025CB80
			fight::Property* ManageLifetimeTrack::GetProperty(int index)
			{
				return gManageLifetimeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1025CBA0
			void ManageLifetimeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gManageLifetimeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1025CE30
			ManageLifetimeTrack::ManageLifetimeTrack() : timeBegin(0.0f), attachedToParent(false), manageLifetime(true)
			{
			}

			// FUNCTION: ENGINE 0x1025CE70
			float ManageLifetimeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1025CE80
			float ManageLifetimeTrack::Slot10() const
			{
				return -1.0f;
			}

			// FUNCTION: ENGINE 0x1025CE90
			ManageLifetimeTrack::~ManageLifetimeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1025DE40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ManageLifetimeTrack::RegisterProperties()
			{
				if (gManageLifetimeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ManageLifetimeTrack>("timeBegin", &ManageLifetimeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<ManageLifetimeTrack>("manageLifetime", &ManageLifetimeTrack::SetManageLifetime);
					properties[1] = property;
					property = new fight::PropertyBool<ManageLifetimeTrack>("attachedToParent", &ManageLifetimeTrack::SetAttachedToParent);
					properties[2] = property;
					property = new fight::PropertyNameList<ManageLifetimeTrack>("grabSlot", &ManageLifetimeTrack::SetGrabSlot);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gManageLifetimeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1025D320
			fight::TrackFactory* CreateManageLifetimeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ManageLifetimeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1025D380
			void RegisterManageLifetimeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ManageLifetimeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<SpawnObjectTrack>;
			template class fight::PropertyNameList<SpawnObjectTrack>;
			template class fight::PropertyName<SpawnObjectTrack>;
			template class fight::PropertyBool<SpawnObjectTrack>;
			template class fight::PropertyString<SpawnObjectTrack>;
			template class fight::PropertyEnumConstList<SpawnObjectTrack>;
			template class fight::PropertyVector<SpawnObjectTrack>;
			template class fight::PropertyColour<SpawnObjectTrack>;
			template class fight::TrackFactoryTemplate<SpawnObjectTrack>;
			template class fight::TrackFactoryCasterTemplate<SpawnObjectTrack>;
			template class fight::PropertyFloatConstRange<ManageLifetimeTrack>;
			template class fight::PropertyBool<ManageLifetimeTrack>;
			template class fight::PropertyNameList<ManageLifetimeTrack>;
			template class fight::TrackFactoryTemplate<ManageLifetimeTrack>;
			template class fight::TrackFactoryCasterTemplate<ManageLifetimeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1025CEA0
// FUNCTION: ENGINE 0x1025CEB0
// FUNCTION: ENGINE 0x1025CEE0
// FUNCTION: ENGINE 0x1025CEF0
// FUNCTION: ENGINE 0x1025CF20
// FUNCTION: ENGINE 0x1025CF50
// FUNCTION: ENGINE 0x1025CF80
// FUNCTION: ENGINE 0x1025CFB0
// FUNCTION: ENGINE 0x1025CFE0
// FUNCTION: ENGINE 0x1025CFF0
// FUNCTION: ENGINE 0x1025D020
// FUNCTION: ENGINE 0x1025D040
// FUNCTION: ENGINE 0x1025D050
// FUNCTION: ENGINE 0x1025D080
// FUNCTION: ENGINE 0x1025D0A0
// FUNCTION: ENGINE 0x1025D0B0
// FUNCTION: ENGINE 0x1025D0F0
// FUNCTION: ENGINE 0x1025D100
// FUNCTION: ENGINE 0x1025D130
// FUNCTION: ENGINE 0x1025D150
// FUNCTION: ENGINE 0x1025D160
// FUNCTION: ENGINE 0x1025D190
// FUNCTION: ENGINE 0x1025D1B0
// FUNCTION: ENGINE 0x1025D1C0
// FUNCTION: ENGINE 0x1025D1F0
// FUNCTION: ENGINE 0x1025D210
// FUNCTION: ENGINE 0x1025D220
// FUNCTION: ENGINE 0x1025D250
// FUNCTION: ENGINE 0x1025D280
// FUNCTION: ENGINE 0x1025D290
// FUNCTION: ENGINE 0x1025D2C0
// FUNCTION: ENGINE 0x1025D2E0
// FUNCTION: ENGINE 0x1025D3B0
// FUNCTION: ENGINE 0x1025D3E0
// FUNCTION: ENGINE 0x1025D400
// FUNCTION: ENGINE 0x1025D410
// FUNCTION: ENGINE 0x1025D440
// FUNCTION: ENGINE 0x1025D460
// FUNCTION: ENGINE 0x1025D490
// FUNCTION: ENGINE 0x1025D4B0
// FUNCTION: ENGINE 0x1025DF90
// FUNCTION: ENGINE 0x1025DFC0
// FUNCTION: ENGINE 0x1025DFF0
// FUNCTION: ENGINE 0x1025E020
// FUNCTION: ENGINE 0x1025E040
// FUNCTION: ENGINE 0x1025E090
