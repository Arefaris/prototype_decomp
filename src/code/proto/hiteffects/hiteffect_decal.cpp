// Fight items of the hit effects: DecalTrack (unit 0x105049C0 - 0x10505220; no assert path, the file name is a guess).
#include "code/proto/hiteffects/hiteffect_decal.h"
#include <new>

namespace proto
{
	namespace HitEffectManager
	{
		fight::Property** gDecalTrackProperties;  // 0x1126F678

		// FUNCTION: ENGINE 0x10504AC0
		bool DecalTrack::SetShaderName(const fight::Name& newValue)
		{
			shaderName = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105049C0
		bool DecalTrack::SetRandomSelect(int newValue)
		{
			randomSelect = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105049D0
		bool DecalTrack::SetRandomOrientation(float newValue)
		{
			randomOrientation = newValue * 0.017453292f;
			return true;
		}

		// FUNCTION: ENGINE 0x105049F0
		bool DecalTrack::SetScaleByDamage(bool newValue)
		{
			scaleByDamage = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10504A00
		bool DecalTrack::SetScaleX(float newValue)
		{
			scaleX = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10504A20
		bool DecalTrack::SetScaleY(float newValue)
		{
			scaleY = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10504A90
		bool DecalTrack::SetPatch(const char* newValue)
		{
			patch = fight::ReplaceString(patch, newValue);
			return true;
		}

		// FUNCTION: ENGINE 0x10504A40
		bool DecalTrack::SetDecalStore(int newValue)
		{
			decalStore = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10504A50
		bool DecalTrack::SetCullOffscreen(bool newValue)
		{
			cullOffscreen = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10504A60
		fight::Property* DecalTrack::GetProperty(int index)
		{
			return gDecalTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10504A80
		void DecalTrack::ClearProperties()
		{
			fight::FreePropertyList(&gDecalTrackProperties);
		}

		// FUNCTION: ENGINE 0x10504AE0
		DecalTrack::DecalTrack() : patch(0), randomOrientation(0.0f), scaleX(1.0f), scaleY(1.0f), decalStore(0), randomSelect(0), cullOffscreen(false), scaleByDamage(false)
		{
		}

		// FUNCTION: ENGINE 0x10504B40
		float DecalTrack::GetTimeBegin() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x104FB8C0
		float DecalTrack::Slot10() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x10504B50
		DecalTrack::~DecalTrack()
		{
			delete[] patch;
		}

		// FUNCTION: ENGINE 0x10504EE0
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void DecalTrack::RegisterProperties()
		{
			if (gDecalTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyName<DecalTrack>("shaderName", &DecalTrack::SetShaderName);
				properties[0] = property;
				property = new fight::PropertyIntConstRange<DecalTrack>("randomSelect", &DecalTrack::SetRandomSelect);
				properties[1] = property;
				property = new fight::PropertyFloatConstRange<DecalTrack>("randomOrientation", &DecalTrack::SetRandomOrientation);
				properties[2] = property;
				property = new fight::PropertyBool<DecalTrack>("scaleByDamage", &DecalTrack::SetScaleByDamage);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<DecalTrack>("scaleX", &DecalTrack::SetScaleX);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<DecalTrack>("scaleY", &DecalTrack::SetScaleY);
				properties[5] = property;
				property = new fight::PropertyString<DecalTrack>("patch", &DecalTrack::SetPatch);
				properties[6] = property;
				property = new fight::PropertyEnumConstList<DecalTrack>("decalStore", gDecalTrackDecalStoreTable, gDecalTrackDecalStoreCount, &DecalTrack::SetDecalStore);
				properties[7] = property;
				property = new fight::PropertyBool<DecalTrack>("cullOffscreen", &DecalTrack::SetCullOffscreen);
				properties[8] = property;
				fight::RegisterPropertyList(properties, &gDecalTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x10504E30
		fight::TrackFactory* CreateDecalTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<DecalTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x10504E60
		void RegisterDecalTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<DecalTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyName<DecalTrack>;
		template class fight::PropertyIntConstRange<DecalTrack>;
		template class fight::PropertyFloatConstRange<DecalTrack>;
		template class fight::PropertyBool<DecalTrack>;
		template class fight::PropertyString<DecalTrack>;
		template class fight::PropertyEnumConstList<DecalTrack>;
		template class fight::TrackFactoryTemplate<DecalTrack>;
		template class fight::TrackFactoryCasterTemplate<DecalTrack>;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10504B80
// FUNCTION: ENGINE 0x10504B90
// FUNCTION: ENGINE 0x10504BC0
// FUNCTION: ENGINE 0x10504BF0
// FUNCTION: ENGINE 0x10504C20
// FUNCTION: ENGINE 0x10504C40
// FUNCTION: ENGINE 0x10504C50
// FUNCTION: ENGINE 0x10504C80
// FUNCTION: ENGINE 0x10504CB0
// FUNCTION: ENGINE 0x10504CC0
// FUNCTION: ENGINE 0x10504CF0
// FUNCTION: ENGINE 0x10504D10
// FUNCTION: ENGINE 0x10504D20
// FUNCTION: ENGINE 0x10504D50
// FUNCTION: ENGINE 0x10504D70
// FUNCTION: ENGINE 0x10504D80
// FUNCTION: ENGINE 0x10504DC0
// FUNCTION: ENGINE 0x10504DD0
// FUNCTION: ENGINE 0x10504E00
// FUNCTION: ENGINE 0x10504E20
// FUNCTION: ENGINE 0x10504E90
// FUNCTION: ENGINE 0x10504EC0
// FUNCTION: ENGINE 0x10505180
// FUNCTION: ENGINE 0x105051B0
// FUNCTION: ENGINE 0x105051D0
