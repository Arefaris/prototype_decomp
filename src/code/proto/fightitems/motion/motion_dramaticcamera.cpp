// Fight items of the motion group: DramaticCameraTrack (unit 0x1035C460 - 0x1035D8B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_dramaticcamera.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDramaticCameraTrackProperties;  // 0x1126387C

			// FUNCTION: ENGINE 0x1035C460
			bool DramaticCameraTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C480
			bool DramaticCameraTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C4A0
			bool DramaticCameraTrack::SetParent(bool newValue)
			{
				parent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C8F0
			bool DramaticCameraTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C4C0
			bool DramaticCameraTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C4E0
			bool DramaticCameraTrack::SetTrackCharacter(bool newValue)
			{
				trackCharacter = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C500
			bool DramaticCameraTrack::SetAbortWhenInterrupted(bool newValue)
			{
				abortWhenInterrupted = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C520
			bool DramaticCameraTrack::SetFirstFrameHoldTime(float newValue)
			{
				firstFrameHoldTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C540
			bool DramaticCameraTrack::SetLastFrameHoldTime(float newValue)
			{
				lastFrameHoldTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C560
			bool DramaticCameraTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C580
			bool DramaticCameraTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C5A0
			bool DramaticCameraTrack::SetNoCameraWeight(float newValue)
			{
				noCameraWeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C910
			bool DramaticCameraTrack::SetAnimation1(const fight::Name& newValue)
			{
				animation1 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C5C0
			bool DramaticCameraTrack::SetStartFrame1(float newValue)
			{
				startFrame1 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C5E0
			bool DramaticCameraTrack::SetEndFrame1(float newValue)
			{
				endFrame1 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C600
			bool DramaticCameraTrack::SetSpeed1(float newValue)
			{
				speed1 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C620
			bool DramaticCameraTrack::SetEnableNormal1(bool newValue)
			{
				enableNormal1 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C640
			bool DramaticCameraTrack::SetEnableMirror1(bool newValue)
			{
				enableMirror1 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C660
			bool DramaticCameraTrack::SetAnimationWeight1(float newValue)
			{
				animationWeight1 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C930
			bool DramaticCameraTrack::SetAnimation2(const fight::Name& newValue)
			{
				animation2 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C680
			bool DramaticCameraTrack::SetStartFrame2(float newValue)
			{
				startFrame2 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C6A0
			bool DramaticCameraTrack::SetEndFrame2(float newValue)
			{
				endFrame2 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C6C0
			bool DramaticCameraTrack::SetSpeed2(float newValue)
			{
				speed2 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C6E0
			bool DramaticCameraTrack::SetEnableNormal2(bool newValue)
			{
				enableNormal2 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C700
			bool DramaticCameraTrack::SetEnableMirror2(bool newValue)
			{
				enableMirror2 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C720
			bool DramaticCameraTrack::SetAnimationWeight2(float newValue)
			{
				animationWeight2 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C950
			bool DramaticCameraTrack::SetAnimation3(const fight::Name& newValue)
			{
				animation3 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C740
			bool DramaticCameraTrack::SetStartFrame3(float newValue)
			{
				startFrame3 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C760
			bool DramaticCameraTrack::SetEndFrame3(float newValue)
			{
				endFrame3 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C780
			bool DramaticCameraTrack::SetSpeed3(float newValue)
			{
				speed3 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C7A0
			bool DramaticCameraTrack::SetEnableNormal3(bool newValue)
			{
				enableNormal3 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C7C0
			bool DramaticCameraTrack::SetEnableMirror3(bool newValue)
			{
				enableMirror3 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C7E0
			bool DramaticCameraTrack::SetAnimationWeight3(float newValue)
			{
				animationWeight3 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C970
			bool DramaticCameraTrack::SetAnimation4(const fight::Name& newValue)
			{
				animation4 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C800
			bool DramaticCameraTrack::SetStartFrame4(float newValue)
			{
				startFrame4 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C820
			bool DramaticCameraTrack::SetEndFrame4(float newValue)
			{
				endFrame4 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C840
			bool DramaticCameraTrack::SetSpeed4(float newValue)
			{
				speed4 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C860
			bool DramaticCameraTrack::SetEnableNormal4(bool newValue)
			{
				enableNormal4 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C880
			bool DramaticCameraTrack::SetEnableMirror4(bool newValue)
			{
				enableMirror4 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C8A0
			bool DramaticCameraTrack::SetAnimationWeight4(float newValue)
			{
				animationWeight4 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035C8C0
			fight::Property* DramaticCameraTrack::GetProperty(int index)
			{
				return gDramaticCameraTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1035C8E0
			void DramaticCameraTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDramaticCameraTrackProperties);
			}

			// FUNCTION: ENGINE 0x1035C990
			DramaticCameraTrack::DramaticCameraTrack() : offset(0.0f, 0.0f, 0.0f), animationWeight1(1.0f), animationWeight2(1.0f), animationWeight3(1.0f), animationWeight4(1.0f), blendInTime(0.0f), blendOutTime(0.0f), endFrame1(-1.0f), endFrame2(-1.0f), endFrame3(-1.0f), endFrame4(-1.0f), firstFrameHoldTime(0.0f), lastFrameHoldTime(0.0f), noCameraWeight(0.0f), speed1(1.0f), speed2(1.0f), speed3(1.0f), speed4(1.0f), startFrame1(-1.0f), startFrame2(-1.0f), startFrame3(-1.0f), startFrame4(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), abortWhenInterrupted(true), enableMirror1(false), enableMirror2(false), enableMirror3(false), enableMirror4(false), enableNormal1(true), enableNormal2(true), enableNormal3(true), enableNormal4(true), parent(false), trackCharacter(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1035CB10
			float DramaticCameraTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1035CB20
			float DramaticCameraTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1035CB30
			DramaticCameraTrack::~DramaticCameraTrack()
			{
			}

			// FUNCTION: ENGINE 0x1035CDF0
			// NONMATCHING: shrink-wrap (the engine saves esi in the entry block before the guard's branch, the compiler places the push after it)
#ifdef NONMATCHING
			void DramaticCameraTrack::RegisterProperties()
			{
				if (gDramaticCameraTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("timeBegin", &DramaticCameraTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("timeEnd", &DramaticCameraTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("parent", &DramaticCameraTrack::SetParent);
					properties[2] = property;
					property = new fight::PropertyNameList<DramaticCameraTrack>("grabSlot", &DramaticCameraTrack::SetGrabSlot);
					properties[3] = property;
					property = new fight::PropertyVector<DramaticCameraTrack>("offset", &DramaticCameraTrack::SetOffset);
					properties[4] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("trackCharacter", &DramaticCameraTrack::SetTrackCharacter);
					properties[5] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("abortWhenInterrupted", &DramaticCameraTrack::SetAbortWhenInterrupted);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("firstFrameHoldTime", &DramaticCameraTrack::SetFirstFrameHoldTime);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("lastFrameHoldTime", &DramaticCameraTrack::SetLastFrameHoldTime);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("blendInTime", &DramaticCameraTrack::SetBlendInTime);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("blendOutTime", &DramaticCameraTrack::SetBlendOutTime);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("noCameraWeight", &DramaticCameraTrack::SetNoCameraWeight);
					properties[11] = property;
					property = new fight::PropertyName<DramaticCameraTrack>("animation1", &DramaticCameraTrack::SetAnimation1);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("startFrame1", &DramaticCameraTrack::SetStartFrame1);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("endFrame1", &DramaticCameraTrack::SetEndFrame1);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("speed1", &DramaticCameraTrack::SetSpeed1);
					properties[15] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("enableNormal1", &DramaticCameraTrack::SetEnableNormal1);
					properties[16] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("enableMirror1", &DramaticCameraTrack::SetEnableMirror1);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("animationWeight1", &DramaticCameraTrack::SetAnimationWeight1);
					properties[18] = property;
					property = new fight::PropertyName<DramaticCameraTrack>("animation2", &DramaticCameraTrack::SetAnimation2);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("startFrame2", &DramaticCameraTrack::SetStartFrame2);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("endFrame2", &DramaticCameraTrack::SetEndFrame2);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("speed2", &DramaticCameraTrack::SetSpeed2);
					properties[22] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("enableNormal2", &DramaticCameraTrack::SetEnableNormal2);
					properties[23] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("enableMirror2", &DramaticCameraTrack::SetEnableMirror2);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("animationWeight2", &DramaticCameraTrack::SetAnimationWeight2);
					properties[25] = property;
					property = new fight::PropertyName<DramaticCameraTrack>("animation3", &DramaticCameraTrack::SetAnimation3);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("startFrame3", &DramaticCameraTrack::SetStartFrame3);
					properties[27] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("endFrame3", &DramaticCameraTrack::SetEndFrame3);
					properties[28] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("speed3", &DramaticCameraTrack::SetSpeed3);
					properties[29] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("enableNormal3", &DramaticCameraTrack::SetEnableNormal3);
					properties[30] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("enableMirror3", &DramaticCameraTrack::SetEnableMirror3);
					properties[31] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("animationWeight3", &DramaticCameraTrack::SetAnimationWeight3);
					properties[32] = property;
					property = new fight::PropertyName<DramaticCameraTrack>("animation4", &DramaticCameraTrack::SetAnimation4);
					properties[33] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("startFrame4", &DramaticCameraTrack::SetStartFrame4);
					properties[34] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("endFrame4", &DramaticCameraTrack::SetEndFrame4);
					properties[35] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("speed4", &DramaticCameraTrack::SetSpeed4);
					properties[36] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("enableNormal4", &DramaticCameraTrack::SetEnableNormal4);
					properties[37] = property;
					property = new fight::PropertyBool<DramaticCameraTrack>("enableMirror4", &DramaticCameraTrack::SetEnableMirror4);
					properties[38] = property;
					property = new fight::PropertyFloatConstRange<DramaticCameraTrack>("animationWeight4", &DramaticCameraTrack::SetAnimationWeight4);
					properties[39] = property;
					fight::RegisterPropertyList(properties, &gDramaticCameraTrackProperties);
				}
			}
#endif

			// FUNCTION: ENGINE 0x1035CCE0
			fight::TrackFactory* CreateDramaticCameraTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DramaticCameraTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1035CD10
			void RegisterDramaticCameraTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DramaticCameraTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// FUNCTION: ENGINE 0x10359510
			bool DramaticCameraTrack::GetParent() const
			{
				return parent;
			}

			// FUNCTION: ENGINE 0x10359520
			const fight::Name& DramaticCameraTrack::GetGrabSlot() const
			{
				return grabSlot;
			}

			// FUNCTION: ENGINE 0x10359550
			bool DramaticCameraTrack::GetTrackCharacter() const
			{
				return trackCharacter;
			}

			// FUNCTION: ENGINE 0x10359560
			bool DramaticCameraTrack::GetAbortWhenInterrupted() const
			{
				return abortWhenInterrupted;
			}

			// FUNCTION: ENGINE 0x10359570
			float DramaticCameraTrack::GetFirstFrameHoldTime() const
			{
				return firstFrameHoldTime;
			}

			// FUNCTION: ENGINE 0x10359580
			float DramaticCameraTrack::GetLastFrameHoldTime() const
			{
				return lastFrameHoldTime;
			}

			// FUNCTION: ENGINE 0x10359590
			float DramaticCameraTrack::GetBlendInTime() const
			{
				return blendInTime;
			}

			// FUNCTION: ENGINE 0x103595A0
			float DramaticCameraTrack::GetBlendOutTime() const
			{
				return blendOutTime;
			}

			// FUNCTION: ENGINE 0x103595B0
			float DramaticCameraTrack::GetNoCameraWeight() const
			{
				return noCameraWeight;
			}

			// FUNCTION: ENGINE 0x103595C0
			const fight::Name& DramaticCameraTrack::GetAnimation1() const
			{
				return animation1;
			}

			// FUNCTION: ENGINE 0x103595D0
			float DramaticCameraTrack::GetStartFrame1() const
			{
				return startFrame1;
			}

			// FUNCTION: ENGINE 0x103595E0
			float DramaticCameraTrack::GetEndFrame1() const
			{
				return endFrame1;
			}

			// FUNCTION: ENGINE 0x103595F0
			float DramaticCameraTrack::GetSpeed1() const
			{
				return speed1;
			}

			// FUNCTION: ENGINE 0x10359600
			bool DramaticCameraTrack::GetEnableNormal1() const
			{
				return enableNormal1;
			}

			// FUNCTION: ENGINE 0x10359610
			bool DramaticCameraTrack::GetEnableMirror1() const
			{
				return enableMirror1;
			}

			// FUNCTION: ENGINE 0x10359620
			float DramaticCameraTrack::GetAnimationWeight1() const
			{
				return animationWeight1;
			}

			// FUNCTION: ENGINE 0x10359630
			const fight::Name& DramaticCameraTrack::GetAnimation2() const
			{
				return animation2;
			}

			// FUNCTION: ENGINE 0x10359640
			float DramaticCameraTrack::GetStartFrame2() const
			{
				return startFrame2;
			}

			// FUNCTION: ENGINE 0x10359650
			float DramaticCameraTrack::GetEndFrame2() const
			{
				return endFrame2;
			}

			// FUNCTION: ENGINE 0x10359660
			float DramaticCameraTrack::GetSpeed2() const
			{
				return speed2;
			}

			// FUNCTION: ENGINE 0x10359670
			bool DramaticCameraTrack::GetEnableNormal2() const
			{
				return enableNormal2;
			}

			// FUNCTION: ENGINE 0x10359680
			bool DramaticCameraTrack::GetEnableMirror2() const
			{
				return enableMirror2;
			}

			// FUNCTION: ENGINE 0x10359690
			float DramaticCameraTrack::GetAnimationWeight2() const
			{
				return animationWeight2;
			}

			// FUNCTION: ENGINE 0x103596A0
			const fight::Name& DramaticCameraTrack::GetAnimation3() const
			{
				return animation3;
			}

			// FUNCTION: ENGINE 0x103596B0
			float DramaticCameraTrack::GetStartFrame3() const
			{
				return startFrame3;
			}

			// FUNCTION: ENGINE 0x103596C0
			float DramaticCameraTrack::GetEndFrame3() const
			{
				return endFrame3;
			}

			// FUNCTION: ENGINE 0x103596D0
			float DramaticCameraTrack::GetSpeed3() const
			{
				return speed3;
			}

			// FUNCTION: ENGINE 0x103596E0
			bool DramaticCameraTrack::GetEnableNormal3() const
			{
				return enableNormal3;
			}

			// FUNCTION: ENGINE 0x103596F0
			bool DramaticCameraTrack::GetEnableMirror3() const
			{
				return enableMirror3;
			}

			// FUNCTION: ENGINE 0x10359700
			float DramaticCameraTrack::GetAnimationWeight3() const
			{
				return animationWeight3;
			}

			// FUNCTION: ENGINE 0x10359710
			const fight::Name& DramaticCameraTrack::GetAnimation4() const
			{
				return animation4;
			}

			// FUNCTION: ENGINE 0x10359720
			float DramaticCameraTrack::GetStartFrame4() const
			{
				return startFrame4;
			}

			// FUNCTION: ENGINE 0x10359730
			float DramaticCameraTrack::GetEndFrame4() const
			{
				return endFrame4;
			}

			// FUNCTION: ENGINE 0x10359740
			float DramaticCameraTrack::GetSpeed4() const
			{
				return speed4;
			}

			// FUNCTION: ENGINE 0x10359750
			bool DramaticCameraTrack::GetEnableNormal4() const
			{
				return enableNormal4;
			}

			// FUNCTION: ENGINE 0x10359760
			bool DramaticCameraTrack::GetEnableMirror4() const
			{
				return enableMirror4;
			}

			// FUNCTION: ENGINE 0x10359770
			float DramaticCameraTrack::GetAnimationWeight4() const
			{
				return animationWeight4;
			}

			// FUNCTION: ENGINE 0x10359530
			math::Vector DramaticCameraTrack::GetOffset() const
			{
				return offset;
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x103598F0
			DramaticCameraAction::DramaticCameraAction(DramaticCameraTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x10359850
			DramaticCameraAction::~DramaticCameraAction()
			{
			}

			// FUNCTION: ENGINE 0x10359E70
			fight::Action* DramaticCameraTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new DramaticCameraAction(this, handle);
			}

			// FUNCTION: ENGINE 0x10359780
			bool DramaticCameraAction::Slot7(int arg, float value)
			{
				return gCameraManager->IsDramaticCameraEnabled();
			}

			// FUNCTION: ENGINE 0x10359E20
			void DramaticCameraAction::Slot6()
			{
				if (link.object != 0 && link.object->abortWhenInterrupted)
				{
					CameraManager* manager = gCameraManager;
					if (manager != 0 && manager->IsDramaticCameraEnabled())
					{
						manager->EndDramaticCamera(choreo::gMinusOne);
					}
				}
			}

			// ---- actions end

			template class fight::PropertyFloatConstRange<DramaticCameraTrack>;
			template class fight::PropertyBool<DramaticCameraTrack>;
			template class fight::PropertyNameList<DramaticCameraTrack>;
			template class fight::PropertyVector<DramaticCameraTrack>;
			template class fight::PropertyName<DramaticCameraTrack>;
			template class fight::TrackFactoryTemplate<DramaticCameraTrack>;
			template class fight::TrackFactoryCasterTemplate<DramaticCameraTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1035CB40
// FUNCTION: ENGINE 0x1035CB50
// FUNCTION: ENGINE 0x1035CB80
// FUNCTION: ENGINE 0x1035CBB0
// FUNCTION: ENGINE 0x1035CBE0
// FUNCTION: ENGINE 0x1035CC10
// FUNCTION: ENGINE 0x1035CC20
// FUNCTION: ENGINE 0x1035CC50
// FUNCTION: ENGINE 0x1035CC70
// FUNCTION: ENGINE 0x1035CC80
// FUNCTION: ENGINE 0x1035CCB0
// FUNCTION: ENGINE 0x1035CCD0
// FUNCTION: ENGINE 0x1035CD40
// FUNCTION: ENGINE 0x1035CD70
// FUNCTION: ENGINE 0x1035CD90
// FUNCTION: ENGINE 0x1035CDA0
// FUNCTION: ENGINE 0x1035CDD0
// FUNCTION: ENGINE 0x1035D800
// FUNCTION: ENGINE 0x1035D830
// FUNCTION: ENGINE 0x1035D860
