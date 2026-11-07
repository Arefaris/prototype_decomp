// proto::fightitems::comseq::ComSeqParams (RTTI name, base engine::GameObjectParams, 4 vftable slots): the parameters
// of a combat sequence - a table of named values (a vector, number, name, object handle or flag each) that the script
// fills from a Lua table. Unit 0x1038B300 - 0x1038C100 (no assert path; the file name is a guess); member names are
// guesses.
#ifndef PROTO_FIGHTITEMS_COMSEQ_COMSEQPARAMS_H
#define PROTO_FIGHTITEMS_COMSEQ_COMSEQPARAMS_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjectparams.h"
#include "code/math/vector.h"
#include "code/proto/variant.h"

namespace proto
{
	namespace fightitems
	{
		namespace comseq
		{
			typedef proto::Variant<math::Vector, float, int, core::Name<core::CaseSensitiveKey>, engine::GameObjectHandle,
				bool> ParamValue;

			// One named value (0x18 bytes)
			struct ParamEntry
			{
				ParamEntry()
				{
				}

				core::Name<core::CaseSensitiveKey> name;  // +0
				ParamValue value;  // +8
			};

			class ComSeqParams : public engine::GameObjectParams
			{
			public:
				typedef container::ArrayDynamic<ParamEntry, container::AllocatorNew> ParamArray;

				// 0x1038C000: room for ten values
				explicit ComSeqParams(int newValue);
				// 0x1038C070 (the deleting destructor is 0x1038C0C0, which expands it)
				virtual ~ComSeqParams()
				{
				}
				// Vftable slot 3 (0x1038C060): the type code of the parameters
				virtual int GetTypeCode();
				// 0x1038B980: takes the next free entry for name (null when the table is full)
				ParamEntry* AddParam(core::Name<core::CaseSensitiveKey> name);

				ParamArray params;  // +0x18
			};
		}
	}
}

#endif
