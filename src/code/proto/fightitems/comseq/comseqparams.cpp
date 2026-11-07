#include "code/proto/fightitems/comseq/comseqparams.h"

namespace proto
{
	namespace fightitems
	{
		namespace comseq
		{
			// FUNCTION: ENGINE 0x1038C000
			ComSeqParams::ComSeqParams(int newValue) : engine::GameObjectParams(newValue), params(10)
			{
			}

			// FUNCTION: ENGINE 0x1038C060
			int ComSeqParams::GetTypeCode()
			{
				return 0x2100d;
			}

			// FUNCTION: ENGINE 0x1038B980
			ParamEntry* ComSeqParams::AddParam(core::Name<core::CaseSensitiveKey> name)
			{
				ParamEntry* item = params.end;
				if (item < params.capacity)
				{
					params.end = item + 1;
					if (item != 0)
					{
						new (&item->name) core::Name<core::CaseSensitiveKey>();
						item->value.index = -1;
					}
					else
					{
						item = 0;
					}
				}
				else
				{
					item = 0;
				}
				item->name = name;
				return item;
			}
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1038B770
// FUNCTION: ENGINE 0x1038B8E0
// FUNCTION: ENGINE 0x1038B930
// FUNCTION: ENGINE 0x1038B9E0
// FUNCTION: ENGINE 0x1038BA10
// FUNCTION: ENGINE 0x1038BFD0
// FUNCTION: ENGINE 0x1038C070
// FUNCTION: ENGINE 0x1038C0C0
