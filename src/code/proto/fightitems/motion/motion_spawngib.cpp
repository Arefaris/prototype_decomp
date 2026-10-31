// Fight items of the motion group: SpawnGibTrack (unit 0x101B4CC0 - 0x101B5700; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_spawngib.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gSpawnGibTrackProperties;  // 0x11254AEC

			// FUNCTION: ENGINE 0x101B4CC0
			bool SpawnGibTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4E20
			bool SpawnGibTrack::SetGibName(const fight::Name& newValue)
			{
				gibName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4CE0
			bool SpawnGibTrack::SetAddSuffix(bool newValue)
			{
				addSuffix = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4E40
			bool SpawnGibTrack::SetTemplateName(const fight::Name& newValue)
			{
				templateName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4CF0
			bool SpawnGibTrack::SetCopyShader(bool newValue)
			{
				copyShader = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4E60
			bool SpawnGibTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4D00
			bool SpawnGibTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4D20
			bool SpawnGibTrack::SetRotation(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				rotation.x = scaled.x;
				rotation.y = scaled.y;
				rotation.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4D70
			bool SpawnGibTrack::SetAttachToParent(bool newValue)
			{
				attachToParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4E80
			bool SpawnGibTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4D80
			bool SpawnGibTrack::SetInheritPose(bool newValue)
			{
				inheritPose = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4D90
			bool SpawnGibTrack::SetAttachToGrandParent(bool newValue)
			{
				attachToGrandParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4DA0
			bool SpawnGibTrack::SetImpulseScale(float newValue)
			{
				impulseScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4DC0
			bool SpawnGibTrack::SetTransferTargetLocks(bool newValue)
			{
				transferTargetLocks = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4DD0
			bool SpawnGibTrack::SetCopyTranformationDescription(bool newValue)
			{
				copyTranformationDescription = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4DE0
			bool SpawnGibTrack::SetUseParentExclusionGroup(bool newValue)
			{
				useParentExclusionGroup = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4DF0
			fight::Property* SpawnGibTrack::GetProperty(int index)
			{
				return gSpawnGibTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B4E10
			void SpawnGibTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSpawnGibTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B4EA0
			SpawnGibTrack::SpawnGibTrack() : offset(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), impulseScale(1.0f), timeBegin(0.0f), addSuffix(true), attachToGrandParent(false), attachToParent(false), copyShader(true), copyTranformationDescription(false), inheritPose(false), transferTargetLocks(false), useParentExclusionGroup(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B4F50
			float SpawnGibTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B4F60
			float SpawnGibTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101B4F70
			SpawnGibTrack::~SpawnGibTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B5230
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpawnGibTrack::RegisterProperties()
			{
				if (gSpawnGibTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SpawnGibTrack>("timeBegin", &SpawnGibTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<SpawnGibTrack>("gibName", &SpawnGibTrack::SetGibName);
					properties[1] = property;
					property = new fight::PropertyBool<SpawnGibTrack>("addSuffix", &SpawnGibTrack::SetAddSuffix);
					properties[2] = property;
					property = new fight::PropertyName<SpawnGibTrack>("templateName", &SpawnGibTrack::SetTemplateName);
					properties[3] = property;
					property = new fight::PropertyBool<SpawnGibTrack>("copyShader", &SpawnGibTrack::SetCopyShader);
					properties[4] = property;
					property = new fight::PropertyNameList<SpawnGibTrack>("joint", &SpawnGibTrack::SetJoint);
					properties[5] = property;
					property = new fight::PropertyVector<SpawnGibTrack>("offset", &SpawnGibTrack::SetOffset);
					properties[6] = property;
					property = new fight::PropertyVector<SpawnGibTrack>("rotation", &SpawnGibTrack::SetRotation);
					properties[7] = property;
					property = new fight::PropertyBool<SpawnGibTrack>("attachToParent", &SpawnGibTrack::SetAttachToParent);
					properties[8] = property;
					property = new fight::PropertyNameList<SpawnGibTrack>("grabSlot", &SpawnGibTrack::SetGrabSlot);
					properties[9] = property;
					property = new fight::PropertyBool<SpawnGibTrack>("inheritPose", &SpawnGibTrack::SetInheritPose);
					properties[10] = property;
					property = new fight::PropertyBool<SpawnGibTrack>("attachToGrandParent", &SpawnGibTrack::SetAttachToGrandParent);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<SpawnGibTrack>("impulseScale", &SpawnGibTrack::SetImpulseScale);
					properties[12] = property;
					property = new fight::PropertyBool<SpawnGibTrack>("transferTargetLocks", &SpawnGibTrack::SetTransferTargetLocks);
					properties[13] = property;
					property = new fight::PropertyBool<SpawnGibTrack>("copyTranformationDescription", &SpawnGibTrack::SetCopyTranformationDescription);
					properties[14] = property;
					property = new fight::PropertyBool<SpawnGibTrack>("useParentExclusionGroup", &SpawnGibTrack::SetUseParentExclusionGroup);
					properties[15] = property;
					fight::RegisterPropertyList(properties, &gSpawnGibTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B5120
			fight::TrackFactory* CreateSpawnGibTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnGibTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B5150
			void RegisterSpawnGibTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpawnGibTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<SpawnGibTrack>;
			template class fight::PropertyName<SpawnGibTrack>;
			template class fight::PropertyBool<SpawnGibTrack>;
			template class fight::PropertyNameList<SpawnGibTrack>;
			template class fight::PropertyVector<SpawnGibTrack>;
			template class fight::TrackFactoryTemplate<SpawnGibTrack>;
			template class fight::TrackFactoryCasterTemplate<SpawnGibTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101B4F80
// FUNCTION: ENGINE 0x101B4F90
// FUNCTION: ENGINE 0x101B4FC0
// FUNCTION: ENGINE 0x101B4FF0
// FUNCTION: ENGINE 0x101B5020
// FUNCTION: ENGINE 0x101B5050
// FUNCTION: ENGINE 0x101B5060
// FUNCTION: ENGINE 0x101B5090
// FUNCTION: ENGINE 0x101B50B0
// FUNCTION: ENGINE 0x101B50C0
// FUNCTION: ENGINE 0x101B50F0
// FUNCTION: ENGINE 0x101B5110
// FUNCTION: ENGINE 0x101B5180
// FUNCTION: ENGINE 0x101B51B0
// FUNCTION: ENGINE 0x101B51D0
// FUNCTION: ENGINE 0x101B5200
// FUNCTION: ENGINE 0x101B5220
// FUNCTION: ENGINE 0x101B5660
// FUNCTION: ENGINE 0x101B5690
// FUNCTION: ENGINE 0x101B56B0
