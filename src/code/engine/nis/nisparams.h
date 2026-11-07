// engine::NISParams (RTTI name, 3 vftable slots, 0x28 bytes, base engine::GameObjectParams): the parameters the NIS
// nodes start their sequence with (kind 0x10006): the inventory of the stream package that holds the sequence and the
// numbers the node passes on. Unit 0x108A7140 - 0x108A82C0 (shared with the NIS nodes, see nisnodes.h; the file name is
// a guess); the member names are guesses.
#ifndef ENGINE_NIS_NISPARAMS_H
#define ENGINE_NIS_NISPARAMS_H

#include "code/engine/gameobject/gameobjectparams.h"

namespace content
{
	class LoadInventory;
}

namespace engine
{
	class NISParams : public GameObjectParams
	{
	public:
		// 0x108A7140
		explicit NISParams(int value);
		// 0x108A82A0 (left to the engine: it releases the reference at +0x20 through the unit's own copy of the helper;
		// the deleting destructor is 0x108A71B0)
		virtual ~NISParams();

		// 0x108A7170
		void SetInventory(content::LoadInventory* value);
		// 0x108A7180 / 0x108A7190
		int GetUnknown1C() const;
		void SetUnknown1C(int value);
		// 0x108A71A0
		float GetUnknown24() const;

		content::LoadInventory* inventory;  // +0x18
		int unknown1C;
		core::IRefCount* unknown20;  // +0x20: released with the parameters
		float unknown24;
	};
}

#endif
