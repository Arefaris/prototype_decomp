// engine::AdvertisementBehaviour (RTTI and reflection names; base engine::Behaviour): unit 0x10917A30 - 0x10919F50 (no
// assert path; the file name is a guess). Only the class information is reconstructed so far; the class itself is
// declared in reflectedclasses.h.
#include "code/engine/reflectedclasses.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10917A30
	content::ClassInfo* AdvertisementBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::AdvertisementBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}
}
