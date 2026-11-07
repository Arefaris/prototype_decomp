// Fight items of the motion group: BlockFramerCamTrack (unit 0x1035D8B0 - 0x1035DC50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_BLOCKFRAMERCAM_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_BLOCKFRAMERCAM_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/camera/framercam.h"
#include "code/proto/camera/cameramanager.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::BlockFramerCamTrack (16 vftable slots, 0x18 bytes)
			class BlockFramerCamTrack : public fight::Track
			{
			public:
				// 0x1035D920
				BlockFramerCamTrack();
				virtual ~BlockFramerCamTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1035A0B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gBlockFramerCamTrackProperties;
			fight::TrackFactory* CreateBlockFramerCamTrackFactory(const char* name);
			void RegisterBlockFramerCamTrackFactory(fight::TrackRegistry* registry, const char* name);


			// ---- actions begin
			// RTTI: proto::fightitems::motion::BlockFramerCamAction (9 vftable slots, 0x2C bytes)
			class BlockFramerCamAction : public fight::Action
			{
			public:
				// 0x1035A010
				BlockFramerCamAction(BlockFramerCamTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10359F90
				virtual ~BlockFramerCamAction();

				// vftable slot 5 (0x10359EC0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10359EE0)
				virtual void Slot6();

				engine::GameObjectHandle target;  // +0x1C
				core::Link<BlockFramerCamTrack> link;  // +0x20
			};

			// ---- actions end
		}
	}
}

#endif
