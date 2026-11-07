// The instances of proto::FEHudVariableTemplate<SymbolPathStoragePolicy_FixedLength, 1> (the variable of the typewriter,
// whose path is set after it is made) and of the 128 character string it keeps. Unit 0x104D9A80 - 0x104DAC90 (the template
// instances of the typewriter's unit; no assert path, the file name is a guess).
#include "code/proto/frontend/fehudelement.h"

namespace container
{
	template class StringC<128>;
}

namespace proto
{
	template class FEHudVariableTemplate<SymbolPathStoragePolicy_FixedLength, 1>;
}
