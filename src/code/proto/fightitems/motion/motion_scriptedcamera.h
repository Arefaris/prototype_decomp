// Fight items of the motion group: ScriptedCameraTrack (unit 0x1035E310 - 0x1035EFF0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SCRIPTEDCAMERA_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SCRIPTEDCAMERA_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			extern fight::EnumEntry gScriptedCameraTrackCyclicTable[];  // 0x11263890

			// RTTI: proto::fightitems::motion::ScriptedCameraTrack (16 vftable slots, 0x70 bytes)
			class ScriptedCameraTrack : public fight::Track
			{
			public:
				// 0x1035E580
				ScriptedCameraTrack();
				virtual ~ScriptedCameraTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1035ABD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAutoEnd(bool newValue);
				bool SetParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetTrackObject(bool newValue);
				bool SetAnimation(const fight::Name& newValue);
				bool SetRotateY(bool newValue);
				bool SetMirrorX(bool newValue);
				bool SetStartFrame(float newValue);
				bool SetEndFrame(float newValue);
				bool SetSpeed(float newValue);
				bool SetCyclic(int newValue);
				bool SetDofNear(float newValue);
				bool SetDofFar(float newValue);
				bool SetDofRange(float newValue);
				bool SetDofAperture(float newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animation;  // +0x10
					fight::Name grabSlot;  // +0x18
					fight::Name joint;  // +0x20
					math::Vector offset;  // +0x28
					float blendInTime;  // +0x34
					float blendOutTime;  // +0x38
					float dofAperture;  // +0x3C
					float dofFar;  // +0x40
					float dofNear;  // +0x44
					float dofRange;  // +0x48
					float endFrame;  // +0x4C
					float speed;  // +0x50
					float startFrame;  // +0x54
					float timeBegin;  // +0x58
					float timeEnd;  // +0x5C
					int cyclic;  // +0x60
					bool autoEnd;  // +0x64
					bool mirrorX;  // +0x65
					bool parent;  // +0x66
					bool rotateY;  // +0x67
					bool trackObject;  // +0x68
					unsigned char unknown69[0x7];
			};

			extern fight::Property** gScriptedCameraTrackProperties;
			fight::TrackFactory* CreateScriptedCameraTrackFactory(const char* name);
			void RegisterScriptedCameraTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
