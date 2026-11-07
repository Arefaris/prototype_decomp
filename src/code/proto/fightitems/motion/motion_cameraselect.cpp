// Fight items of the motion group: CameraAvatarSelectTrack, CameraTypeSelectTrack (unit 0x1035AC20 - 0x1035B690; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_cameraselect.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gCameraAvatarSelectTrackProperties;  // 0x11263864

			// FUNCTION: ENGINE 0x1035AC20
			bool CameraAvatarSelectTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035AC40
			bool CameraAvatarSelectTrack::SetCameraType(int newValue)
			{
				cameraType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035AC50
			bool CameraAvatarSelectTrack::SetParent(bool newValue)
			{
				parent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035AD80
			bool CameraAvatarSelectTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035ACB0
			fight::Property* CameraAvatarSelectTrack::GetProperty(int index)
			{
				return gCameraAvatarSelectTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1035ACD0
			void CameraAvatarSelectTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCameraAvatarSelectTrackProperties);
			}

			// FUNCTION: ENGINE 0x1035ADA0
			CameraAvatarSelectTrack::CameraAvatarSelectTrack() : timeBegin(0.0f), cameraType(0), parent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1035ADE0
			float CameraAvatarSelectTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1035ADF0
			float CameraAvatarSelectTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1035AE00
			CameraAvatarSelectTrack::~CameraAvatarSelectTrack()
			{
			}

			// FUNCTION: ENGINE 0x1035B430
			// NONMATCHING: shrink-wrap (the engine saves esi in the entry block before the guard's branch, the compiler places the push after it)
#ifdef NONMATCHING
			void CameraAvatarSelectTrack::RegisterProperties()
			{
				if (gCameraAvatarSelectTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CameraAvatarSelectTrack>("timeBegin", &CameraAvatarSelectTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<CameraAvatarSelectTrack>("cameraType", engine::gCharacterChaseTable, gCameraAvatarSelectTrackCameraTypeCount, &CameraAvatarSelectTrack::SetCameraType);
					properties[1] = property;
					property = new fight::PropertyBool<CameraAvatarSelectTrack>("parent", &CameraAvatarSelectTrack::SetParent);
					properties[2] = property;
					property = new fight::PropertyNameList<CameraAvatarSelectTrack>("grabSlot", &CameraAvatarSelectTrack::SetGrabSlot);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gCameraAvatarSelectTrackProperties);
				}
			}
#endif

			// FUNCTION: ENGINE 0x1035B190
			fight::TrackFactory* CreateCameraAvatarSelectTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CameraAvatarSelectTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1035B320
			void RegisterCameraAvatarSelectTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CameraAvatarSelectTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCameraTypeSelectTrackProperties;  // 0x11263868

			// FUNCTION: ENGINE 0x1035AC60
			bool CameraTypeSelectTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035AC80
			bool CameraTypeSelectTrack::SetCameraType(int newValue)
			{
				cameraType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035AC90
			bool CameraTypeSelectTrack::SetCameraBlendTime(float newValue)
			{
				cameraBlendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035ACE0
			fight::Property* CameraTypeSelectTrack::GetProperty(int index)
			{
				return gCameraTypeSelectTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1035AD00
			void CameraTypeSelectTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCameraTypeSelectTrackProperties);
			}

			// FUNCTION: ENGINE 0x1035AD10
			CameraTypeSelectTrack::CameraTypeSelectTrack() : cameraBlendTime(0.0f), timeBegin(0.0f), cameraType(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1035AD50
			float CameraTypeSelectTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1035AD60
			float CameraTypeSelectTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1035AD70
			CameraTypeSelectTrack::~CameraTypeSelectTrack()
			{
			}

			// FUNCTION: ENGINE 0x1035B1F0
			// NONMATCHING: shrink-wrap (the engine saves esi in the entry block before the guard's branch, the compiler places the push after it)
#ifdef NONMATCHING
			void CameraTypeSelectTrack::RegisterProperties()
			{
				if (gCameraTypeSelectTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CameraTypeSelectTrack>("timeBegin", &CameraTypeSelectTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<CameraTypeSelectTrack>("cameraType", engine::gCharacterChaseTable, gCameraAvatarSelectTrackCameraTypeCount, &CameraTypeSelectTrack::SetCameraType);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<CameraTypeSelectTrack>("cameraBlendTime", &CameraTypeSelectTrack::SetCameraBlendTime);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gCameraTypeSelectTrackProperties);
				}
			}
#endif

			// FUNCTION: ENGINE 0x1035B1C0
			fight::TrackFactory* CreateCameraTypeSelectTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CameraTypeSelectTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1035B350
			void RegisterCameraTypeSelectTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CameraTypeSelectTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// FUNCTION: ENGINE 0x10358570
			int CameraAvatarSelectTrack::GetCameraType() const
			{
				return cameraType;
			}

			// FUNCTION: ENGINE 0x10358580
			bool CameraAvatarSelectTrack::GetParent() const
			{
				return parent;
			}

			// FUNCTION: ENGINE 0x10358590
			const fight::Name& CameraAvatarSelectTrack::GetGrabSlot() const
			{
				return grabSlot;
			}

			// FUNCTION: ENGINE 0x103585A0
			int CameraTypeSelectTrack::GetCameraType() const
			{
				return cameraType;
			}

			// FUNCTION: ENGINE 0x103585B0
			float CameraTypeSelectTrack::GetCameraBlendTime() const
			{
				return cameraBlendTime;
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10358890
			CameraAvatarSelectAction::CameraAvatarSelectAction(CameraAvatarSelectTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x10358730
			CameraAvatarSelectAction::~CameraAvatarSelectAction()
			{
			}

			// FUNCTION: ENGINE 0x10358B50
			fight::Action* CameraAvatarSelectTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				if (owner == 0)
				{
					return 0;
				}
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CameraAvatarSelectAction(this, handle);
			}

			// FUNCTION: ENGINE 0x10358A80
			CameraTypeSelectAction::CameraTypeSelectAction(CameraTypeSelectTrack* newTrack) : fight::Action(0x200), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x10358780
			CameraTypeSelectAction::~CameraTypeSelectAction()
			{
			}

			// FUNCTION: ENGINE 0x10358BA0
			fight::Action* CameraTypeSelectTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				if (owner == 0)
				{
					return 0;
				}
				return new CameraTypeSelectAction(this);
			}
			// FUNCTION: ENGINE 0x10358B20
			bool CameraTypeSelectAction::Slot5(int arg, float value)
			{
				if (link.object != 0)
				{
					gCameraManager->SwitchCamera(link.object->cameraType, link.object->cameraBlendTime);
				}
				return false;
			}
			// ---- actions end

			template class fight::PropertyFloatConstRange<CameraAvatarSelectTrack>;
			template class fight::PropertyEnumConstList<CameraAvatarSelectTrack>;
			template class fight::PropertyBool<CameraAvatarSelectTrack>;
			template class fight::PropertyNameList<CameraAvatarSelectTrack>;
			template class fight::TrackFactoryTemplate<CameraAvatarSelectTrack>;
			template class fight::TrackFactoryCasterTemplate<CameraAvatarSelectTrack>;
			template class fight::PropertyFloatConstRange<CameraTypeSelectTrack>;
			template class fight::PropertyEnumConstList<CameraTypeSelectTrack>;
			template class fight::TrackFactoryTemplate<CameraTypeSelectTrack>;
			template class fight::TrackFactoryCasterTemplate<CameraTypeSelectTrack>;
		}
	}
}


namespace proto
{
	namespace fightitems
	{
		// FUNCTION: ENGINE 0x103585C0
		bool RegisterAt103585C0Factories(fight::TrackRegistry* registry)
		{
			motion::RegisterCameraAvatarSelectTrackFactory(registry, "cameraAvatarSelect");
			motion::RegisterCameraTypeSelectTrackFactory(registry, "cameraTypeSelect");
			return true;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1035AE10
// FUNCTION: ENGINE 0x1035AE40
// FUNCTION: ENGINE 0x1035AE50
// FUNCTION: ENGINE 0x1035AE80
// FUNCTION: ENGINE 0x1035AE90
// FUNCTION: ENGINE 0x1035AEC0
// FUNCTION: ENGINE 0x1035AEF0
// FUNCTION: ENGINE 0x1035AF20
// FUNCTION: ENGINE 0x1035AF50
// FUNCTION: ENGINE 0x1035AF60
// FUNCTION: ENGINE 0x1035AFA0
// FUNCTION: ENGINE 0x1035AFB0
// FUNCTION: ENGINE 0x1035AFE0
// FUNCTION: ENGINE 0x1035B000
// FUNCTION: ENGINE 0x1035B010
// FUNCTION: ENGINE 0x1035B040
// FUNCTION: ENGINE 0x1035B060
// FUNCTION: ENGINE 0x1035B070
// FUNCTION: ENGINE 0x1035B0A0
// FUNCTION: ENGINE 0x1035B0D0
// FUNCTION: ENGINE 0x1035B0E0
// FUNCTION: ENGINE 0x1035B120
// FUNCTION: ENGINE 0x1035B130
// FUNCTION: ENGINE 0x1035B160
// FUNCTION: ENGINE 0x1035B180
// FUNCTION: ENGINE 0x1035B380
// FUNCTION: ENGINE 0x1035B3B0
// FUNCTION: ENGINE 0x1035B3D0
// FUNCTION: ENGINE 0x1035B3E0
// FUNCTION: ENGINE 0x1035B410
// FUNCTION: ENGINE 0x1035B5A0
// FUNCTION: ENGINE 0x1035B5F0
// FUNCTION: ENGINE 0x1035B620
// FUNCTION: ENGINE 0x1035B640
