// engine::world::LocationRenderSettings (RTTI and reflection names): a content library object that holds the
// ambient occlusion settings of a location. The first one created is the current one for the whole world. Unit
// 0x10914850 - 0x10914AB0 (no assert path; the directory and file name are guesses). The reflected member names are
// original; the rest is guessed.
#ifndef ENGINE_WORLD_LOCATIONRENDERSETTINGS_H
#define ENGINE_WORLD_LOCATIONRENDERSETTINGS_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"

namespace engine
{
	namespace world
	{
		class LocationRenderSettings : public content::MetaLoadObject
		{
		public:
			// 0x10914A70: the first one made becomes the current one
			LocationRenderSettings();
			// 0x10914890 (deleting destructor 0x109148F0): a destroyed current one is dropped
			virtual ~LocationRenderSettings();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// vftable slot 3 (0x10914910): nothing to do once loaded
			virtual void Slot3(int unused);

			// 0x109148B0
			static LocationRenderSettings* GetCurrent();
			// 0x109148C0 / 0x109148D0 and the setters 0x10914920 / 0x10914930
			float GetAmbientOcclusionScale() const;
			float GetAmbientOcclusionBias() const;
			void SetAmbientOcclusionScale(float value);
			void SetAmbientOcclusionBias(float value);

			static LocationRenderSettings* sCurrent;  // 0x1131C67C

			float ambientOcclusionScale;  // +8
			float ambientOcclusionBias;  // +0xC
		};
	}
}

#endif
