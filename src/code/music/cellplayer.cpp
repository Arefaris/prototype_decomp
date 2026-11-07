// The cell player's enumeration of states, reflected as an om meta enumeration (a template instance of the om library).
#include "code/music/cellplayer.h"
#include "code/om/metaclass.h"
#include "code/om/metaenum.h"

namespace music
{
	// FUNCTION: ENGINE 0x105E2A10
	bool CellPlayer::Slot1(int, int, int)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105E2A20
	void CellPlayer::Slot2()
	{
	}

	// FUNCTION: ENGINE 0x105E2A30
	void CellPlayer::Slot3()
	{
	}

	// FUNCTION: ENGINE 0x105E2A40
	void CellPlayer::Slot4()
	{
	}

	// FUNCTION: ENGINE 0x105E2A50
	bool CellPlayer::Slot5()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105E2A60
	void CellPlayer::Slot6(int)
	{
	}

	// FUNCTION: ENGINE 0x105E2A70
	void CellPlayer::Slot7(CellPlayerParameters)
	{
	}

	// FUNCTION: ENGINE 0x105E2A80
	void CellPlayer::Slot8(CellPlayerParameters)
	{
	}

	// FUNCTION: ENGINE 0x105E2A90
	int CellPlayer::Slot9()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x105F9A10
	void CellPlayer::SetState(int newState)
	{
		state = newState;
	}

	// FUNCTION: ENGINE 0x105F9A00
	void CellPlayer::Slot11(int)
	{
	}

	// FUNCTION: ENGINE 0x105E3120
	MGraphCellPlayer::MGraphCellPlayer() :
		graph(0),
		unknown1C(0.0f),
		unknown20(false),
		unknown21(false),
		unknown22(false),
		unknown24(0),
		unknown28(0),
		unknown2C(0)
	{
		first.valid = false;
		first.parameters.unknown0 = 0;
		first.parameters.unknown4 = 0;
		first.parameters.unknown8 = 0;
		first.parameters.unknownC = 0;
		first.parameters.unknown10 = false;
		first.parameters.unknown14 = 0;
		first.parameters.unknown18 = 0;
		first.parameters.unknown1C = 0;
		first.parameters.unknown20 = 0;
		first.parameters.unknown24 = false;
		second.valid = false;
		second.parameters.unknown0 = 0;
		second.parameters.unknown4 = 0;
		second.parameters.unknown8 = 0;
		second.parameters.unknownC = 0;
		second.parameters.unknown10 = false;
		second.parameters.unknown14 = 0;
		second.parameters.unknown18 = 0;
		second.parameters.unknown1C = 0;
		second.parameters.unknown20 = 0;
		second.parameters.unknown24 = false;
	}

	// FUNCTION: ENGINE 0x105E2B70
	void MGraphCellPlayer::Slot2()
	{
		if (state == 2)
		{
			SetState(3);
			unknown22 = false;
		}
		if (state == 1)
		{
			unknown22 = true;
		}
	}

	// FUNCTION: ENGINE 0x105E2BA0
	void MGraphCellPlayer::Slot3()
	{
		int current = state;
		if (current != 6 && current != 7 && current != 0)
		{
			if (current == 3)
			{
				SetState(0);
			}
			else
			{
				SetState(6);
			}
		}
	}

	// FUNCTION: ENGINE 0x105E3210
	void MGraphCellPlayer::Slot4()
	{
		Reset();
	}

	// FUNCTION: ENGINE 0x105E31C0
	bool MGraphCellPlayer::Slot5()
	{
		return unknown21;
	}

	// FUNCTION: ENGINE 0x105E2BD0
	void MGraphCellPlayer::Slot7(CellPlayerParameters parameters)
	{
		first.valid = true;
		first.parameters = parameters;
	}

	// FUNCTION: ENGINE 0x105E2BF0
	void MGraphCellPlayer::Slot8(CellPlayerParameters parameters)
	{
		second.valid = true;
		second.parameters = parameters;
	}
}

namespace om
{

	// FUNCTION: ENGINE 0x105D2D50
	template MetaEnum<music::CellPlayer::State>::MetaEnum(const ClassName&);
	// FUNCTION: ENGINE 0x105D2D90
	template const type_info* MetaEnum<music::CellPlayer::State>::GetType();
	// FUNCTION: ENGINE 0x105D2DA0
	template MetaEnum<music::CellPlayer::State>::~MetaEnum();
	// FUNCTION: ENGINE 0x105D2DB0
	template bool MetaEnum<music::CellPlayer::State>::WriteBinary(BinaryStream*, const void*);
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

namespace om
{
	// FUNCTION: ENGINE 0x105E3870
	template<> int MetaClass<music::MGraphCellPlayer>::Slot5()
	{
		return reinterpret_cast<int>(new music::MGraphCellPlayer);
	}

	// FUNCTION: ENGINE 0x105E2C90
	template<> void MetaClass<music::MGraphCellPlayer>::Slot6(void* object)
	{
		delete static_cast<music::MGraphCellPlayer*>(object);
	}

	// FUNCTION: ENGINE 0x105E2C30
	template MetaClass<music::MGraphCellPlayer>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105E2C80
	template const type_info* MetaClass<music::MGraphCellPlayer>::GetType();
	// FUNCTION: ENGINE 0x105E2D20
	template const char* MetaClass<music::MGraphCellPlayer>::AllocationTag();
	// FUNCTION: ENGINE 0x105E2FE0
	template void* MetaClass<music::MGraphCellPlayer>::operator new(size_t);
}
