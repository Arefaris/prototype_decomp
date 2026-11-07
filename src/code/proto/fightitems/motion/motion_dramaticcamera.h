// Fight items of the motion group: DramaticCameraTrack (unit 0x1035C460 - 0x1035D8B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_DRAMATICCAMERA_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_DRAMATICCAMERA_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/fightitems/motion/motioncommon.h"
#include "code/proto/camera/cameramanager.h"

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

				// The accessors the engine keeps out of line
				// 0x10359530
				math::Vector GetOffset() const;

				// The accessors the engine keeps out of line
				// 0x10359510
				bool GetParent() const;
				// 0x10359520
				const fight::Name& GetGrabSlot() const;
				// 0x10359550
				bool GetTrackCharacter() const;
				// 0x10359560
				bool GetAbortWhenInterrupted() const;
				// 0x10359570
				float GetFirstFrameHoldTime() const;
				// 0x10359580
				float GetLastFrameHoldTime() const;
				// 0x10359590
				float GetBlendInTime() const;
				// 0x103595A0
				float GetBlendOutTime() const;
				// 0x103595B0
				float GetNoCameraWeight() const;
				// 0x103595C0
				const fight::Name& GetAnimation1() const;
				// 0x103595D0
				float GetStartFrame1() const;
				// 0x103595E0
				float GetEndFrame1() const;
				// 0x103595F0
				float GetSpeed1() const;
				// 0x10359600
				bool GetEnableNormal1() const;
				// 0x10359610
				bool GetEnableMirror1() const;
				// 0x10359620
				float GetAnimationWeight1() const;
				// 0x10359630
				const fight::Name& GetAnimation2() const;
				// 0x10359640
				float GetStartFrame2() const;
				// 0x10359650
				float GetEndFrame2() const;
				// 0x10359660
				float GetSpeed2() const;
				// 0x10359670
				bool GetEnableNormal2() const;
				// 0x10359680
				bool GetEnableMirror2() const;
				// 0x10359690
				float GetAnimationWeight2() const;
				// 0x103596A0
				const fight::Name& GetAnimation3() const;
				// 0x103596B0
				float GetStartFrame3() const;
				// 0x103596C0
				float GetEndFrame3() const;
				// 0x103596D0
				float GetSpeed3() const;
				// 0x103596E0
				bool GetEnableNormal3() const;
				// 0x103596F0
				bool GetEnableMirror3() const;
				// 0x10359700
				float GetAnimationWeight3() const;
				// 0x10359710
				const fight::Name& GetAnimation4() const;
				// 0x10359720
				float GetStartFrame4() const;
				// 0x10359730
				float GetEndFrame4() const;
				// 0x10359740
				float GetSpeed4() const;
				// 0x10359750
				bool GetEnableNormal4() const;
				// 0x10359760
				bool GetEnableMirror4() const;
				// 0x10359770
				float GetAnimationWeight4() const;

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


			// ---- actions begin
			// RTTI: proto::fightitems::motion::DramaticCameraAction (9 vftable slots, 0x2C bytes)
			class DramaticCameraAction : public fight::Action
			{
			public:
				// 0x103598F0
				DramaticCameraAction(DramaticCameraTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10359850
				virtual ~DramaticCameraAction();

				// vftable slot 5 (0x10359A40)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10359E20)
				virtual void Slot6();
				// vftable slot 7 (0x10359780)
				virtual bool Slot7(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<DramaticCameraTrack> link;  // +0x20
			};

			// ---- actions end
		}
	}
}

#endif
