// The cell player's enumeration of states, reflected as an om meta enumeration (a template instance of the om library).
#include "code/music/cellplayer.h"
#include "code/om/metaenum.h"

namespace om
{

	// FUNCTION: ENGINE 0x105D2D50
	template MetaEnum<music::CellPlayer::State>::MetaEnum(const ClassName&);
	// FUNCTION: ENGINE 0x105D2D90
	template const type_info* MetaEnum<music::CellPlayer::State>::GetType();
	// FUNCTION: ENGINE 0x105D2DA0
	template MetaEnum<music::CellPlayer::State>::~MetaEnum();
	// FUNCTION: ENGINE 0x105D2DB0
	// EQUIVALENT: register allocation: the engine loads the value into eax and the stream into ecx, ours ecx and edx (82.6 %)
	template void MetaEnum<music::CellPlayer::State>::WriteBinary(BinaryStream*, const void*);
	// FUNCTION: ENGINE 0x105D2DD0
	template void MetaEnum<music::CellPlayer::State>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D2F00
	template const char* MetaEnum<music::CellPlayer::State>::AllocationTag();
	// FUNCTION: ENGINE 0x105D3440
	template bool MetaEnum<music::CellPlayer::State>::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105D3460
	template int MetaEnum<music::CellPlayer::State>::Slot5();
	// FUNCTION: ENGINE 0x105D3470
	template void MetaEnum<music::CellPlayer::State>::Slot6(void*);
	// FUNCTION: ENGINE 0x105D34B0
	template void* MetaEnum<music::CellPlayer::State>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D3F50
	template void MetaEnum<music::CellPlayer::State>::WriteText(TextValue*, const void*);
	// FUNCTION: ENGINE 0x105D4690
	template bool MetaEnum<music::CellPlayer::State>::ReadText(const TextValue*, void*);
}
