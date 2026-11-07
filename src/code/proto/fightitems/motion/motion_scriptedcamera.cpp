// Fight items of the motion group: ScriptedCameraTrack (unit 0x1035E310 - 0x1035EFF0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_scriptedcamera.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gScriptedCameraTrackProperties;  // 0x11263888

			// FUNCTION: ENGINE 0x1035E310
			bool ScriptedCameraTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E330
			bool ScriptedCameraTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E350
			bool ScriptedCameraTrack::SetAutoEnd(bool newValue)
			{
				autoEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E360
			bool ScriptedCameraTrack::SetParent(bool newValue)
			{
				parent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E520
			bool ScriptedCameraTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E540
			bool ScriptedCameraTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E370
			bool ScriptedCameraTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E390
			bool ScriptedCameraTrack::SetTrackObject(bool newValue)
			{
				trackObject = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E560
			bool ScriptedCameraTrack::SetAnimation(const fight::Name& newValue)
			{
				animation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E3A0
			bool ScriptedCameraTrack::SetRotateY(bool newValue)
			{
				rotateY = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E3B0
			bool ScriptedCameraTrack::SetMirrorX(bool newValue)
			{
				mirrorX = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E3C0
			bool ScriptedCameraTrack::SetStartFrame(float newValue)
			{
				startFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E3E0
			bool ScriptedCameraTrack::SetEndFrame(float newValue)
			{
				endFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E400
			bool ScriptedCameraTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E420
			bool ScriptedCameraTrack::SetCyclic(int newValue)
			{
				cyclic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E430
			bool ScriptedCameraTrack::SetDofNear(float newValue)
			{
				dofNear = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E450
			bool ScriptedCameraTrack::SetDofFar(float newValue)
			{
				dofFar = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E470
			bool ScriptedCameraTrack::SetDofRange(float newValue)
			{
				dofRange = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E490
			bool ScriptedCameraTrack::SetDofAperture(float newValue)
			{
				dofAperture = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E4B0
			bool ScriptedCameraTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E4D0
			bool ScriptedCameraTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035E4F0
			fight::Property* ScriptedCameraTrack::GetProperty(int index)
			{
				return gScriptedCameraTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1035E510
			void ScriptedCameraTrack::ClearProperties()
			{
				fight::FreePropertyList(&gScriptedCameraTrackProperties);
			}

			// FUNCTION: ENGINE 0x1035E580
			ScriptedCameraTrack::ScriptedCameraTrack() : offset(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), dofAperture(5.0f), dofFar(-1.0f), dofNear(-1.0f), dofRange(1.0f), endFrame(-1.0f), speed(1.0f), startFrame(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0), autoEnd(false), mirrorX(false), parent(false), rotateY(false), trackObject(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1035E650
			float ScriptedCameraTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1035E660
			float ScriptedCameraTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1035E670
			ScriptedCameraTrack::~ScriptedCameraTrack()
			{
			}

			// FUNCTION: ENGINE 0x1035E9E0
			// NONMATCHING: shrink-wrap (the engine saves esi in the entry block before the guard's branch, the compiler places the push after it)
#ifdef NONMATCHING
			void ScriptedCameraTrack::RegisterProperties()
			{
				if (gScriptedCameraTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("timeBegin", &ScriptedCameraTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("timeEnd", &ScriptedCameraTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ScriptedCameraTrack>("autoEnd", &ScriptedCameraTrack::SetAutoEnd);
					properties[2] = property;
					property = new fight::PropertyBool<ScriptedCameraTrack>("parent", &ScriptedCameraTrack::SetParent);
					properties[3] = property;
					property = new fight::PropertyNameList<ScriptedCameraTrack>("grabSlot", &ScriptedCameraTrack::SetGrabSlot);
					properties[4] = property;
					property = new fight::PropertyNameList<ScriptedCameraTrack>("joint", &ScriptedCameraTrack::SetJoint);
					properties[5] = property;
					property = new fight::PropertyVector<ScriptedCameraTrack>("offset", &ScriptedCameraTrack::SetOffset);
					properties[6] = property;
					property = new fight::PropertyBool<ScriptedCameraTrack>("trackObject", &ScriptedCameraTrack::SetTrackObject);
					properties[7] = property;
					property = new fight::PropertyName<ScriptedCameraTrack>("animation", &ScriptedCameraTrack::SetAnimation);
					properties[8] = property;
					property = new fight::PropertyBool<ScriptedCameraTrack>("rotateY", &ScriptedCameraTrack::SetRotateY);
					properties[9] = property;
					property = new fight::PropertyBool<ScriptedCameraTrack>("mirrorX", &ScriptedCameraTrack::SetMirrorX);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("startFrame", &ScriptedCameraTrack::SetStartFrame);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("endFrame", &ScriptedCameraTrack::SetEndFrame);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("speed", &ScriptedCameraTrack::SetSpeed);
					properties[13] = property;
					property = new fight::PropertyEnumConstList<ScriptedCameraTrack>("cyclic", gScriptedCameraTrackCyclicTable, 3, &ScriptedCameraTrack::SetCyclic);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("dofNear", &ScriptedCameraTrack::SetDofNear);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("dofFar", &ScriptedCameraTrack::SetDofFar);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("dofRange", &ScriptedCameraTrack::SetDofRange);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("dofAperture", &ScriptedCameraTrack::SetDofAperture);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("blendInTime", &ScriptedCameraTrack::SetBlendInTime);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<ScriptedCameraTrack>("blendOutTime", &ScriptedCameraTrack::SetBlendOutTime);
					properties[20] = property;
					fight::RegisterPropertyList(properties, &gScriptedCameraTrackProperties);
				}
			}
#endif

			// FUNCTION: ENGINE 0x1035E8D0
			fight::TrackFactory* CreateScriptedCameraTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScriptedCameraTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1035E900
			void RegisterScriptedCameraTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScriptedCameraTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<ScriptedCameraTrack>;
			template class fight::PropertyBool<ScriptedCameraTrack>;
			template class fight::PropertyNameList<ScriptedCameraTrack>;
			template class fight::PropertyVector<ScriptedCameraTrack>;
			template class fight::PropertyName<ScriptedCameraTrack>;
			template class fight::PropertyEnumConstList<ScriptedCameraTrack>;
			template class fight::TrackFactoryTemplate<ScriptedCameraTrack>;
			template class fight::TrackFactoryCasterTemplate<ScriptedCameraTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1035E680
// FUNCTION: ENGINE 0x1035E690
// FUNCTION: ENGINE 0x1035E6C0
// FUNCTION: ENGINE 0x1035E6F0
// FUNCTION: ENGINE 0x1035E720
// FUNCTION: ENGINE 0x1035E750
// FUNCTION: ENGINE 0x1035E760
// FUNCTION: ENGINE 0x1035E790
// FUNCTION: ENGINE 0x1035E7B0
// FUNCTION: ENGINE 0x1035E7C0
// FUNCTION: ENGINE 0x1035E7F0
// FUNCTION: ENGINE 0x1035E810
// FUNCTION: ENGINE 0x1035E820
// FUNCTION: ENGINE 0x1035E860
// FUNCTION: ENGINE 0x1035E870
// FUNCTION: ENGINE 0x1035E8A0
// FUNCTION: ENGINE 0x1035E8C0
// FUNCTION: ENGINE 0x1035E930
// FUNCTION: ENGINE 0x1035E960
// FUNCTION: ENGINE 0x1035E980
// FUNCTION: ENGINE 0x1035E990
// FUNCTION: ENGINE 0x1035E9C0
// FUNCTION: ENGINE 0x1035EF50
// FUNCTION: ENGINE 0x1035EF80
// FUNCTION: ENGINE 0x1035EFA0
