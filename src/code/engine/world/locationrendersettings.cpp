#include "code/engine/world/locationrendersettings.h"

namespace engine
{
	namespace world
	{
		// GLOBAL: ENGINE 0x1131C67C
		LocationRenderSettings* LocationRenderSettings::sCurrent;

		// FUNCTION: ENGINE 0x10914850
		content::ClassInfo* LocationRenderSettings::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::world::LocationRenderSettings";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10914890
		LocationRenderSettings::~LocationRenderSettings()
		{
			if (sCurrent == this)
			{
				sCurrent = 0;
			}
		}

		// FUNCTION: ENGINE 0x109148B0
		LocationRenderSettings* LocationRenderSettings::GetCurrent()
		{
			return sCurrent;
		}

		// FUNCTION: ENGINE 0x109148C0
		float LocationRenderSettings::GetAmbientOcclusionScale() const
		{
			return ambientOcclusionScale;
		}

		// FUNCTION: ENGINE 0x109148D0
		float LocationRenderSettings::GetAmbientOcclusionBias() const
		{
			return ambientOcclusionBias;
		}

		// FUNCTION: ENGINE 0x10914910
		void LocationRenderSettings::Slot3(int unused)
		{
		}

		// FUNCTION: ENGINE 0x10914920
		void LocationRenderSettings::SetAmbientOcclusionScale(float value)
		{
			ambientOcclusionScale = value;
		}

		// FUNCTION: ENGINE 0x10914930
		void LocationRenderSettings::SetAmbientOcclusionBias(float value)
		{
			ambientOcclusionBias = value;
		}

		// FUNCTION: ENGINE 0x109149C0
		content::MemberList* LocationRenderSettings::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberPrimitiveMetaType<LocationRenderSettings, float, 0>("p"),
					content::MemberOffset(&((LocationRenderSettings*)0)->ambientOcclusionScale,
					(int)&((LocationRenderSettings*)0)->ambientOcclusionScale), "ambientOcclusionScale" },
				{ content::GetMemberPrimitiveMetaType<LocationRenderSettings, float, 1>("p"),
					content::MemberOffset(&((LocationRenderSettings*)0)->ambientOcclusionBias,
					(int)&((LocationRenderSettings*)0)->ambientOcclusionBias), "ambientOcclusionBias" }
			};
			sList.members = sMembers;
			sList.count = 2;
			return &sList;
		}

		// FUNCTION: ENGINE 0x10914A70
		// EQUIVALENT: the engine stores the reference count before the scale, ours after it, 73.7 %
		LocationRenderSettings::LocationRenderSettings() : ambientOcclusionScale(1.0f), ambientOcclusionBias(0.0f)
		{
			if (sCurrent == 0)
			{
				sCurrent = this;
			}
		}
	}
}



// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10914940
// FUNCTION: ENGINE 0x10914980
