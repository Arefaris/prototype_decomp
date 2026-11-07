// Fight items of the motion group: DramaticCameraTrack (unit 0x1035C460 - 0x1035D8B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_DRAMATICCAMERA_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_DRAMATICCAMERA_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DramaticCameraTrack (16 vftable slots, 0xB0 bytes)
			class DramaticCameraTrack : public fight::Track
			{
			public:
				// 0x1035C990
				DramaticCameraTrack();
				virtual ~DramaticCameraTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10359E70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetTrackCharacter(bool newValue);
				bool SetAbortWhenInterrupted(bool newValue);
				bool SetFirstFrameHoldTime(float newValue);
				bool SetLastFrameHoldTime(float newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetNoCameraWeight(float newValue);
				bool SetAnimation1(const fight::Name& newValue);
				bool SetStartFrame1(float newValue);
				bool SetEndFrame1(float newValue);
				bool SetSpeed1(float newValue);
				bool SetEnableNormal1(bool newValue);
				bool SetEnableMirror1(bool newValue);
				bool SetAnimationWeight1(float newValue);
				bool SetAnimation2(const fight::Name& newValue);
				bool SetStartFrame2(float newValue);
				bool SetEndFrame2(float newValue);
				bool SetSpeed2(float newValue);
				bool SetEnableNormal2(bool newValue);
				bool SetEnableMirror2(bool newValue);
				bool SetAnimationWeight2(float newValue);
				bool SetAnimation3(const fight::Name& newValue);
				bool SetStartFrame3(float newValue);
				bool SetEndFrame3(float newValue);
				bool SetSpeed3(float newValue);
				bool SetEnableNormal3(bool newValue);
				bool SetEnableMirror3(bool newValue);
				bool SetAnimationWeight3(float newValue);
				bool SetAnimation4(const fight::Name& newValue);
				bool SetStartFrame4(float newValue);
				bool SetEndFrame4(float newValue);
				bool SetSpeed4(float newValue);
				bool SetEnableNormal4(bool newValue);
				bool SetEnableMirror4(bool newValue);
				bool SetAnimationWeight4(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animation1;  // +0x10
					fight::Name animation2;  // +0x18
					fight::Name animation3;  // +0x20
					fight::Name animation4;  // +0x28
					fight::Name grabSlot;  // +0x30
					math::Vector offset;  // +0x38
					float animationWeight1;  // +0x44
					float animationWeight2;  // +0x48
					float animationWeight3;  // +0x4C
					float animationWeight4;  // +0x50
					float blendInTime;  // +0x54
					float blendOutTime;  // +0x58
					float endFrame1;  // +0x5C
					float endFrame2;  // +0x60
					float endFrame3;  // +0x64
					float endFrame4;  // +0x68
					float firstFrameHoldTime;  // +0x6C
					float lastFrameHoldTime;  // +0x70
					float noCameraWeight;  // +0x74
					float speed1;  // +0x78
					float speed2;  // +0x7C
					float speed3;  // +0x80
					float speed4;  // +0x84
					float startFrame1;  // +0x88
					float startFrame2;  // +0x8C
					float startFrame3;  // +0x90
					float startFrame4;  // +0x94
					float timeBegin;  // +0x98
					float timeEnd;  // +0x9C
					bool abortWhenInterrupted;  // +0xA0
					bool enableMirror1;  // +0xA1
					bool enableMirror2;  // +0xA2
					bool enableMirror3;  // +0xA3
					bool enableMirror4;  // +0xA4
					bool enableNormal1;  // +0xA5
					bool enableNormal2;  // +0xA6
					bool enableNormal3;  // +0xA7
					bool enableNormal4;  // +0xA8
					bool parent;  // +0xA9
					bool trackCharacter;  // +0xAA
					unsigned char unknownAB[0x5];
			};

			extern fight::Property** gDramaticCameraTrackProperties;
			fight::TrackFactory* CreateDramaticCameraTrackFactory(const char* name);
			void RegisterDramaticCameraTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
