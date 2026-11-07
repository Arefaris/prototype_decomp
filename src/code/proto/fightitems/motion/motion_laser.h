// Fight items of the motion group: LaserTrack (unit 0x10187250 - 0x10187C50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_LASER_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_LASER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/engine/render/async/drawable.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::LaserTrack (16 vftable slots, 0x70 bytes)
			class LaserTrack : public fight::Track
			{
			public:
				// 0x10187450
				LaserTrack();
				virtual ~LaserTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100E44D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetShader(const fight::Name& newValue);
				bool SetThickness(float newValue);
				bool SetColour(const math::Colour128& newValue);
				bool SetMyJoint(const fight::Name& newValue);
				bool SetMyOffset(const math::Vector& newValue);
				bool SetTargetJoint(const fight::Name& newValue);
				bool SetTargetOffset(const math::Vector& newValue);
				bool SetTrackingSpeed(float newValue);
				bool SetLongitudinalOffset(float newValue);
				bool SetPerpendicularOffset(float newValue);
				bool SetPerpendicularFinalOffset(float newValue);
				bool SetPerpendicularFinalTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name myJoint;  // +0x10
					fight::Name shader;  // +0x18
					fight::Name targetJoint;  // +0x20
					math::Colour128 colour;  // +0x28
					math::Vector myOffset;  // +0x38
					math::Vector targetOffset;  // +0x44
					float longitudinalOffset;  // +0x50
					float perpendicularFinalOffset;  // +0x54
					float perpendicularFinalTime;  // +0x58
					float perpendicularOffset;  // +0x5C
					float thickness;  // +0x60
					float timeBegin;  // +0x64
					float timeEnd;  // +0x68
					float trackingSpeed;  // +0x6C
			};

			extern fight::Property** gLaserTrackProperties;
			fight::TrackFactory* CreateLaserTrackFactory(const char* name);
			void RegisterLaserTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::LaserAction (9 vftable slots, 0x48 bytes)
			class LaserAction : public fight::Action
			{
			public:
				// 0x100E40D0
				LaserAction(LaserTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100E3BB0
				virtual ~LaserAction();

				// vftable slot 5 (0x100E3C00)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100E3A80)
				virtual void Slot6();
				// vftable slot 7 (0x100E4960)
				virtual bool Slot7(int arg, float value);

				core::Link<LaserTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				engine::render::Drawable drawable;  // +0x2C
				float unknown30;  // +0x30
				math::Vector unknown34;  // +0x34
				bool unknown40;  // +0x40
				unsigned char unknown41[0x3];
				int unknown44;  // +0x44
			};

			// ---- actions end
		}
	}
}

#endif
