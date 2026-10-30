// proto::DistrictBehaviour (RTTI and reflection names; base engine::TriggerBehaviour): the trigger of a district of the
// open world, with the stream packages of its pedestrians and vehicles. Unit 0x10571BC0 - 0x10572530 (no assert path;
// the file name is a guess). Only the class info is reconstructed.
#ifndef PROTO_DISTRICTBEHAVIOUR_H
#define PROTO_DISTRICTBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/reflectedclasses2.h"

namespace proto
{
	class DistrictBehaviour : public engine::TriggerBehaviour
	{
	public:
		// 0x10571BC0
		static content::ClassInfo* GetClassInfo();
	};
}

#endif
