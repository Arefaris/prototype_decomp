// Fight items of the motion group: DeformTrack (unit 0x10153950 - 0x10154030; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_DEFORM_H
#define PROTO_FIGHTITEMS_MOTION_DEFORM_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DeformTrack (16 vftable slots, 0x48 bytes)
			class DeformTrack : public fight::Track
			{
			public:
				// 0x10153A80
				DeformTrack();
				virtual ~DeformTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B1550, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetDirection(const math::Vector& newValue);
				bool SetRadius(float newValue);
				bool SetBlendTime(float newValue);
				bool SetDeformDirStr(float newValue);
				bool SetStrength(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					math::Vector direction;  // +0x18
					math::Vector offset;  // +0x24
					float blendTime;  // +0x30
					float deformDirStr;  // +0x34
					float radius;  // +0x38
					float strength;  // +0x3C
					float timeBegin;  // +0x40
					unsigned char unknown44[0x4];
			};

			extern fight::Property** gDeformTrackProperties;
			fight::TrackFactory* CreateDeformTrackFactory(const char* name);
			void RegisterDeformTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
