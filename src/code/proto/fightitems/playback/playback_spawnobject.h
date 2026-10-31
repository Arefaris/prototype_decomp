// Fight items of the playback group: SpawnObjectTrack, ManageLifetimeTrack (unit 0x1025C660 - 0x1025E0E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_PLAYBACK_PLAYBACK_SPAWNOBJECT_H
#define PROTO_FIGHTITEMS_PLAYBACK_PLAYBACK_SPAWNOBJECT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/playback/playbackdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace playback
		{
			// RTTI: proto::fightitems::playback::SpawnObjectTrack (16 vftable slots, 0xA8 bytes)
			class SpawnObjectTrack : public fight::Track
			{
			public:
				// 0x1025CC90
				SpawnObjectTrack();
				virtual ~SpawnObjectTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1025B3E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTemplateName(const fight::Name& newValue);
				bool SetObjectName(const fight::Name& newValue);
				bool SetAddSuffix(bool newValue);
				bool SetInitialState(const char* newValue);
				bool SetSpecificPlaybackSet(const fight::Name& newValue);
				bool SetSpawnSpace(int newValue);
				bool SetSpawnJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetOrientation(const math::Vector& newValue);
				bool SetAttachToParent(bool newValue);
				bool SetDetachAfterSpawn(bool newValue);
				bool SetAICharacter(bool newValue);
				bool SetAutomaticTag(const fight::Name& newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetCopyPose(bool newValue);
				bool SetInheritSpawnerVelocity(bool newValue);
				bool SetLinearVelocity(const math::Vector& newValue);
				bool SetAngularVelocity(const math::Vector& newValue);
				bool SetCollideWithSpawnerDelay(float newValue);
				bool SetSpawnSleeping(bool newValue);
				bool SetManageLifetime(bool newValue);
				bool SetManageLifetimeThrownProp(bool newValue);
				bool SetInheritSpawnerTarget(bool newValue);
				bool SetInheritSpawnerCharge(int newValue);
				bool SetUseParentScale(bool newValue);
				bool SetSetScale(bool newValue);
				bool SetScale(const math::Vector& newValue);
				bool SetProbability(float newValue);
				bool SetUseSpawnerAsDamageOriginator(bool newValue);
				bool SetDamageOriginatorFromSpawner(bool newValue);
				bool SetTransferTargetLocks(bool newValue);
				bool SetSendMessageToScenarioTree(bool newValue);
				bool SetApplyColourTint(bool newValue);
				bool SetInheritPackage(bool newValue);
				bool SetTintColour(const math::Colour128& newValue);
				bool SetCacheDamageOrigionatorAsCollider(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name automaticTag;  // +0x10
					fight::Name grabSlot;  // +0x18
					fight::Name objectName;  // +0x20
					fight::Name spawnJoint;  // +0x28
					fight::Name specificPlaybackSet;  // +0x30
					fight::Name templateName;  // +0x38
					math::Colour128 tintColour;  // +0x40
					math::Vector angularVelocity;  // +0x50
					math::Vector linearVelocity;  // +0x5C
					math::Vector offset;  // +0x68
					math::Vector orientation;  // +0x74
					math::Vector scale;  // +0x80
					char* initialState;  // +0x8C
					float collideWithSpawnerDelay;  // +0x90
					float probability;  // +0x94
					float timeBegin;  // +0x98
					int inheritSpawnerCharge;  // +0x9C
					int spawnSpace;  // +0xA0
					bool aICharacter : 1;  // +0xA4 bit 0
					bool addSuffix : 1;  // +0xA4 bit 1
					bool applyColourTint : 1;  // +0xA4 bit 2
					bool attachToParent : 1;  // +0xA4 bit 3
					bool cacheDamageOrigionatorAsCollider : 1;  // +0xA4 bit 4
					bool copyPose : 1;  // +0xA4 bit 5
					bool damageOriginatorFromSpawner : 1;  // +0xA4 bit 6
					bool detachAfterSpawn : 1;  // +0xA4 bit 7
					bool inheritPackage : 1;  // +0xA5 bit 0
					bool inheritSpawnerTarget : 1;  // +0xA5 bit 1
					bool inheritSpawnerVelocity : 1;  // +0xA5 bit 2
					bool manageLifetime : 1;  // +0xA5 bit 3
					bool manageLifetimeThrownProp : 1;  // +0xA5 bit 4
					bool sendMessageToScenarioTree : 1;  // +0xA5 bit 5
					bool setScale : 1;  // +0xA5 bit 6
					bool spawnSleeping : 1;  // +0xA5 bit 7
					bool transferTargetLocks : 1;  // +0xA6 bit 0
					bool useParentScale : 1;  // +0xA6 bit 1
					bool useSpawnerAsDamageOriginator : 1;  // +0xA6 bit 2
					bool unknownBitA6_3 : 1;  // +0xA6 bit 3
					bool unknownBitA6_4 : 1;  // +0xA6 bit 4
					bool unknownBitA6_5 : 1;  // +0xA6 bit 5
					bool unknownBitA6_6 : 1;  // +0xA6 bit 6
					bool unknownBitA6_7 : 1;  // +0xA6 bit 7
					unsigned char unknownA7[0x1];
			};

			extern fight::Property** gSpawnObjectTrackProperties;
			fight::TrackFactory* CreateSpawnObjectTrackFactory(const char* name);
			void RegisterSpawnObjectTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::playback::ManageLifetimeTrack (16 vftable slots, 0x20 bytes)
			class ManageLifetimeTrack : public fight::Track
			{
			public:
				// 0x1025CE30
				ManageLifetimeTrack();
				virtual ~ManageLifetimeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1025B450, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetManageLifetime(bool newValue);
				bool SetAttachedToParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					bool attachedToParent;  // +0x1C
					bool manageLifetime;  // +0x1D
					unsigned char unknown1E[0x2];
			};

			extern fight::Property** gManageLifetimeTrackProperties;
			fight::TrackFactory* CreateManageLifetimeTrackFactory(const char* name);
			void RegisterManageLifetimeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
