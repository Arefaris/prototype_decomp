// Fight items of the motion group: SpawnGibTrack (unit 0x101B4CC0 - 0x101B5700; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SPAWNGIB_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SPAWNGIB_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction2.h"

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

			// ---- actions end
		}
	}
}

#endif
