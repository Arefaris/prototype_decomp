// engine::GameObjectTemplateBuilder (RTTI and reflection names; a content::MetaObjectTemplate): unit 0x1090C110 -
// 0x1090D700 (no assert path; the file name is a guess). Only the class information is reconstructed so far; the class
// itself is declared in reflectedclasses.h.
#include "code/engine/reflectedclasses.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1090C110
	content::ClassInfo* GameObjectTemplateBuilder::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "GameObjectTemplateBuilder";
		sInfo.code = "p";
		return &sInfo;
	}
}
