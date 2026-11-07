// Fight items of the motion group: SpawnGibTrack (unit 0x101B4CC0 - 0x101B5700; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SPAWNGIB_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SPAWNGIB_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::SpawnGibTrack (16 vftable slots, 0x58 bytes)
			class SpawnGibTrack : public fight::Track
			{
			public:
				// 0x101B4EA0
				SpawnGibTrack();
				virtual ~SpawnGibTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10118940, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGibName(const fight::Name& newValue);
				bool SetAddSuffix(bool newValue);
				bool SetTemplateName(const fight::Name& newValue);
				bool SetCopyShader(bool newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetRotation(const math::Vector& newValue);
				bool SetAttachToParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetInheritPose(bool newValue);
				bool SetAttachToGrandParent(bool newValue);
				bool SetImpulseScale(float newValue);
				bool SetTransferTargetLocks(bool newValue);
				bool SetCopyTranformationDescription(bool newValue);
				bool SetUseParentExclusionGroup(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

				// Accessors the engine keeps as unreferenced copies in the action half (names guessed)
				math::Vector GetOffset() const;

				// Accessors the engine keeps as unreferenced copies in the action half (names guessed)
				const fight::Name& GetGibName() const;
				bool GetAddSuffix() const;
				const fight::Name& GetTemplateName() const;
				bool GetCopyShader() const;
				const fight::Name& GetJoint() const;
				bool GetAttachToParent() const;
				const fight::Name& GetGrabSlot() const;
				bool GetInheritPose() const;
				bool GetAttachToGrandParent() const;
				float GetImpulseScale() const;
				bool GetTransferTargetLocks() const;
				bool GetCopyTranformationDescription() const;
				bool GetUseParentExclusionGroup() const;

					fight::Name gibName;  // +0x10
					fight::Name grabSlot;  // +0x18
					fight::Name joint;  // +0x20
					fight::Name templateName;  // +0x28
					math::Vector offset;  // +0x30
					math::Vector rotation;  // +0x3C
					float impulseScale;  // +0x48
					float timeBegin;  // +0x4C
					bool addSuffix;  // +0x50
					bool attachToGrandParent;  // +0x51
					bool attachToParent;  // +0x52
					bool copyShader;  // +0x53
					bool copyTranformationDescription;  // +0x54
					bool inheritPose;  // +0x55
					bool transferTargetLocks;  // +0x56
					bool useParentExclusionGroup;  // +0x57
			};

			extern fight::Property** gSpawnGibTrackProperties;
			fight::TrackFactory* CreateSpawnGibTrackFactory(const char* name);
			void RegisterSpawnGibTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// 0x10117A80 / 0x10117AC0: this unit's copies of the helpers that store a reference counted object and release one (name guesses)
			void AssignRefCountedSpawnGib(core::IRefCount** slot, core::IRefCount* value);
			void SafeReleaseRefSpawnGib(core::IRefCount*& object);

			// RTTI: proto::fightitems::motion::SpawnGibAction (9 vftable slots, 0x30 bytes): spawns the gibs of an object
			class SpawnGibAction : public fight::Action
			{
			public:
				// 0x10117CC0
				SpawnGibAction(SpawnGibTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* newOwner);
				// 0x10117C10
				virtual ~SpawnGibAction();

				// vftable slot 5 (0x10117D80, the engine's)
				virtual bool Slot5(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<SpawnGibTrack> link;  // +0x20
				core::IRefCount* owner;  // +0x2C
			};

			// ---- actions end
		}
	}
}

#endif
