// engine::SupportingLimbGetActiveMessageConst (RTTI name): in a header of its own because the magnetic boots unit needs it
// together with the messages of gameobjectmessages.h, which clash with those of supportingsurface.h.
#ifndef ENGINE_PHYSICS_SUPPORTINGLIMBACTIVEMESSAGE_H
#define ENGINE_PHYSICS_SUPPORTINGLIMBACTIVEMESSAGE_H

#include "code/engine/message.h"
#include "code/engine/physics/supportinglimb.h"

namespace engine
{
	// RTTI: engine::SupportingLimbGetActiveMessageConst (a character answers with its active supporting limb)
	struct SupportingLimbGetActiveMessageConst : public NonintrusiveMessage
	{
		SupportingLimbGetActiveMessageConst() : NonintrusiveMessage(0x11, 4)
		{
			limb = 0;
		}
		virtual ~SupportingLimbGetActiveMessageConst()
		{
		}

		const SupportingLimb* limb;
	};
}

#endif
