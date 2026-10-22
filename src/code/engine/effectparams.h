// engine::EffectParams (RTTI name; base fight::Params): what an effect track of a fight tree is started with. Holds the
// object the effect is attached to, the track it runs as (it leaves the track's list again when the parameters
// die) and a reference to the effect. The file name is a guess; the unit 0x1089B580 - 0x1089B620 holds the
// constructor and the destructor. Member names are guesses.
#ifndef ENGINE_EFFECTPARAMS_H
#define ENGINE_EFFECTPARAMS_H

#include "code/core/refptr.h"
#include "code/engine/fight/branch.h"
#include "code/engine/fight/params.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	class EffectParams : public fight::Params
	{
	public:
		// 0x1089B580
		explicit EffectParams(int value);
		// 0x1089B5D0 (deleting destructor 0x1089B600)
		virtual ~EffectParams();

		int unknownC;
		float unknown10;
		HandleBase handle;  // +0x14
		float unknown18;
		void* unknown1C;
		fight::Branch* track;  // +0x20
		int unknown24;
		int unknown28;
		core::IRefCount* effect;  // +0x2C
	};
}

#endif
