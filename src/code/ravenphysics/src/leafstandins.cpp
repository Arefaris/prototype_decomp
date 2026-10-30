// The tiny leaf functions of 0x106A0000 - 0x106C0000; see leafstandins.h.
#include "code/ravenphysics/leafstandins.h"

namespace ravenphysics
{
	template <int Function, int Offset>
	char* LeafAddress<Function, Offset>::Get()
	{
		return &member;
	}

	template <int Function, int Offset>
	int LeafWord<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	unsigned short LeafHalf<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	int LeafSignedHalf<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	int LeafUnsignedHalf<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	unsigned char LeafByte<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	float LeafFloat<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function>
	LeafSelf<Function>* LeafSelf<Function>::Get()
	{
		return this;
	}

	template <int Function>
	void LeafNothing()
	{
	}

	template <int Function>
	int LeafZero()
	{
		return 0;
	}

	template <int Function>
	bool LeafFalse()
	{
		return false;
	}

	template <int Function>
	int LeafSecondArgument(int first, int second)
	{
		return second;
	}

	template <int Function, int Size>
	LeafElement<Size>* LeafArray<Function, Size>::At(int index)
	{
		return items + index;
	}

	template <int Function, int Offset>
	void LeafSetWord<Function, Offset>::Set(int newValue)
	{
		member = newValue;
	}

	template <int Function, int First, int Second>
	LeafInitTwo<Function, First, Second>::LeafInitTwo()
	{
		first = First;
		second = Second;
	}

	template <int Function>
	LeafZeroThree<Function>::LeafZeroThree()
	{
		first = 0;
		second = 0;
		third = 0;
	}

	template <int Function>
	LeafTwoWords<Function>::LeafTwoWords(int newFirst, int newSecond)
	{
		first = newFirst;
		second = newSecond;
	}

	template <int Function>
	void LeafSetTwoWords<Function>::Set(int newFirst, int newSecond)
	{
		first = newFirst;
		second = newSecond;
	}


	// FUNCTION: ENGINE 0x106A0000
	template struct LeafAddress<0x106A0000, 104>;

	// FUNCTION: ENGINE 0x106A0010
	template struct LeafAddress<0x106A0010, 96>;

	// FUNCTION: ENGINE 0x106A0020
	template struct LeafAddress<0x106A0020, 112>;

	// FUNCTION: ENGINE 0x106A0B10
	template struct LeafAddress<0x106A0B10, 72>;

	// FUNCTION: ENGINE 0x106A0B20
	template struct LeafAddress<0x106A0B20, 84>;

	// FUNCTION: ENGINE 0x106A12B0
	template struct LeafFloat<0x106A12B0, 4>;

	// FUNCTION: ENGINE 0x106A12C0
	template struct LeafFloat<0x106A12C0, 8>;

	// FUNCTION: ENGINE 0x106A12D0
	template struct LeafAddress<0x106A12D0, 48>;

	// FUNCTION: ENGINE 0x106A12E0
	template struct LeafAddress<0x106A12E0, 56>;

	// FUNCTION: ENGINE 0x106A14A0
	template struct LeafAddress<0x106A14A0, 64>;

	// FUNCTION: ENGINE 0x106A14C0
	template struct LeafAddress<0x106A14C0, 88>;

	// FUNCTION: ENGINE 0x106A14D0
	template struct LeafFloat<0x106A14D0, 100>;

	// FUNCTION: ENGINE 0x106A14E0
	template struct LeafFloat<0x106A14E0, 128>;

	// FUNCTION: ENGINE 0x106A14F0
	template struct LeafFloat<0x106A14F0, 132>;

	// FUNCTION: ENGINE 0x106A1500
	template struct LeafFloat<0x106A1500, 136>;

	// FUNCTION: ENGINE 0x106A1510
	template struct LeafFloat<0x106A1510, 140>;

	// FUNCTION: ENGINE 0x106A38E0
	template struct LeafSelf<0x106A38E0>;

	// FUNCTION: ENGINE 0x106A38F0
	template struct LeafWord<0x106A38F0, 4>;

	// FUNCTION: ENGINE 0x106A3900
	template struct LeafAddress<0x106A3900, 8>;

	// FUNCTION: ENGINE 0x106A3910
	template struct LeafWord<0x106A3910, 12>;

	// FUNCTION: ENGINE 0x106A3920
	template struct LeafHalf<0x106A3920, 40>;

	// FUNCTION: ENGINE 0x106A3930
	template struct LeafAddress<0x106A3930, 20>;

	// FUNCTION: ENGINE 0x106A3940
	template struct LeafWord<0x106A3940, 24>;

	// FUNCTION: ENGINE 0x106A3950
	template struct LeafAddress<0x106A3950, 28>;

	// FUNCTION: ENGINE 0x106A3960
	template struct LeafWord<0x106A3960, 32>;

	// FUNCTION: ENGINE 0x106A3970
	template struct LeafHalf<0x106A3970, 42>;

	// FUNCTION: ENGINE 0x106A3980
	template struct LeafWord<0x106A3980, 16>;

	// FUNCTION: ENGINE 0x106A3990
	template struct LeafWord<0x106A3990, 36>;

	// FUNCTION: ENGINE 0x106A39A0
	template struct LeafWord<0x106A39A0, 76>;

	// FUNCTION: ENGINE 0x106A39B0
	template struct LeafWord<0x106A39B0, 80>;

	// FUNCTION: ENGINE 0x106A5E20
	template struct LeafArray<0x106A5E20, 12>;

	// FUNCTION: ENGINE 0x106A5E30
	template struct LeafSelf<0x106A5E30>;

	// FUNCTION: ENGINE 0x106A5E40
	template void LeafNothing<0x106A5E40>();

	// FUNCTION: ENGINE 0x106A5E50
	template int LeafSecondArgument<0x106A5E50>(int, int);

	// FUNCTION: ENGINE 0x106A5E60
	template int LeafSecondArgument<0x106A5E60>(int, int);

	// FUNCTION: ENGINE 0x106A6010
	template struct LeafZeroThree<0x106A6010>;

	// FUNCTION: ENGINE 0x106A6160
	template struct LeafWord<0x106A6160, 0>;

	// FUNCTION: ENGINE 0x106A7700
	template struct LeafUnsignedHalf<0x106A7700, 1024>;

	// FUNCTION: ENGINE 0x106A7A60
	template void LeafNothing<0x106A7A60>();

	// FUNCTION: ENGINE 0x106A7AD0
	template struct LeafArray<0x106A7AD0, 12>;

	// FUNCTION: ENGINE 0x106A80C0
	template void LeafNothing<0x106A80C0>();

	// FUNCTION: ENGINE 0x106A80D0
	template void LeafNothing<0x106A80D0>();

	// FUNCTION: ENGINE 0x106A80E0
	template void LeafNothing<0x106A80E0>();

	// FUNCTION: ENGINE 0x106A8110
	template struct LeafWord<0x106A8110, 8>;

	// FUNCTION: ENGINE 0x106A8E90
	template struct LeafSelf<0x106A8E90>;

	// FUNCTION: ENGINE 0x106A8FC0
	template struct LeafFloat<0x106A8FC0, 4>;

	// FUNCTION: ENGINE 0x106A8FD0
	template struct LeafFloat<0x106A8FD0, 0>;

	// FUNCTION: ENGINE 0x106A9210
	template struct LeafWord<0x106A9210, 0>;

	// FUNCTION: ENGINE 0x106A9230
	template struct LeafHalf<0x106A9230, 0>;

	// FUNCTION: ENGINE 0x106A9240
	template struct LeafWord<0x106A9240, 8>;

	// FUNCTION: ENGINE 0x106A9250
	template struct LeafWord<0x106A9250, 28>;

	// FUNCTION: ENGINE 0x106A9290
	template struct LeafArray<0x106A9290, 8>;

	// FUNCTION: ENGINE 0x106A92A0
	template struct LeafWord<0x106A92A0, 4>;

	// FUNCTION: ENGINE 0x106A92B0
	template struct LeafArray<0x106A92B0, 36>;

	// FUNCTION: ENGINE 0x106A92C0
	template struct LeafWord<0x106A92C0, 4>;

	// FUNCTION: ENGINE 0x106A92D0
	template struct LeafArray<0x106A92D0, 16>;

	// FUNCTION: ENGINE 0x106A92E0
	template struct LeafWord<0x106A92E0, 0>;

	// FUNCTION: ENGINE 0x106A92F0
	template struct LeafWord<0x106A92F0, 4>;

	// FUNCTION: ENGINE 0x106A9300
	template struct LeafArray<0x106A9300, 64>;

	// FUNCTION: ENGINE 0x106A9310
	template struct LeafWord<0x106A9310, 0>;

	// FUNCTION: ENGINE 0x106A9340
	template struct LeafArray<0x106A9340, 32>;

	// FUNCTION: ENGINE 0x106A9350
	template struct LeafWord<0x106A9350, 0>;

	// FUNCTION: ENGINE 0x106A9380
	template struct LeafArray<0x106A9380, 32>;

	// FUNCTION: ENGINE 0x106A9390
	template struct LeafWord<0x106A9390, 0>;

	// FUNCTION: ENGINE 0x106A93A0
	template struct LeafArray<0x106A93A0, 16>;

	// FUNCTION: ENGINE 0x106A93B0
	template struct LeafWord<0x106A93B0, 0>;

	// FUNCTION: ENGINE 0x106A93C0
	template struct LeafArray<0x106A93C0, 28>;

	// FUNCTION: ENGINE 0x106A93E0
	template struct LeafInitTwo<0x106A93E0, 0, 0>;

	// FUNCTION: ENGINE 0x106A9400
	template struct LeafInitTwo<0x106A9400, 0, 0>;

	// FUNCTION: ENGINE 0x106A9420
	template struct LeafArray<0x106A9420, 8>;

	// FUNCTION: ENGINE 0x106A9430
	template struct LeafArray<0x106A9430, 8>;

	// FUNCTION: ENGINE 0x106A9440
	template struct LeafArray<0x106A9440, 12>;

	// FUNCTION: ENGINE 0x106AA3F0
	template struct LeafWord<0x106AA3F0, 0>;

	// FUNCTION: ENGINE 0x106AA400
	template struct LeafWord<0x106AA400, 0>;

	// FUNCTION: ENGINE 0x106AA410
	template struct LeafSignedHalf<0x106AA410, 8>;

	// FUNCTION: ENGINE 0x106AA420
	template struct LeafHalf<0x106AA420, 0>;

	// FUNCTION: ENGINE 0x106AA430
	template struct LeafHalf<0x106AA430, 2>;

	// FUNCTION: ENGINE 0x106AA440
	template struct LeafHalf<0x106AA440, 8>;

	// FUNCTION: ENGINE 0x106AA460
	template struct LeafHalf<0x106AA460, 6>;

	// FUNCTION: ENGINE 0x106AA470
	template struct LeafHalf<0x106AA470, 4>;

	// FUNCTION: ENGINE 0x106AA5A0
	template struct LeafInitTwo<0x106AA5A0, 0, 0>;

	// FUNCTION: ENGINE 0x106AA5C0
	template struct LeafArray<0x106AA5C0, 12>;

	// FUNCTION: ENGINE 0x106AA5D0
	template struct LeafArray<0x106AA5D0, 304>;

	// FUNCTION: ENGINE 0x106AA610
	template struct LeafArray<0x106AA610, 28>;

	// FUNCTION: ENGINE 0x106AA660
	template struct LeafInitTwo<0x106AA660, 0, 0>;

	// FUNCTION: ENGINE 0x106AA700
	template struct LeafTwoWords<0x106AA700>;

	// FUNCTION: ENGINE 0x106AA870
	template struct LeafSetTwoWords<0x106AA870>;

	// FUNCTION: ENGINE 0x106AB0F0
	template struct LeafZeroThree<0x106AB0F0>;

	// FUNCTION: ENGINE 0x106AB410
	template struct LeafWord<0x106AB410, 4>;

	// FUNCTION: ENGINE 0x106AB420
	template struct LeafArray<0x106AB420, 2>;

	// FUNCTION: ENGINE 0x106AB430
	template struct LeafArray<0x106AB430, 12>;

	// FUNCTION: ENGINE 0x106AB440
	template struct LeafWord<0x106AB440, 4>;

	// FUNCTION: ENGINE 0x106AB450
	template struct LeafSetTwoWords<0x106AB450>;

	// FUNCTION: ENGINE 0x106ABB20
	template void LeafNothing<0x106ABB20>();

	// FUNCTION: ENGINE 0x106ABEA0
	template struct LeafArray<0x106ABEA0, 2>;

	// FUNCTION: ENGINE 0x106ABEB0
	template struct LeafArray<0x106ABEB0, 8>;

	// FUNCTION: ENGINE 0x106AC1E0
	template struct LeafWord<0x106AC1E0, 8>;

	// FUNCTION: ENGINE 0x106AC1F0
	template struct LeafArray<0x106AC1F0, 1>;

	// FUNCTION: ENGINE 0x106AC200
	template struct LeafArray<0x106AC200, 4>;

	// FUNCTION: ENGINE 0x106AC970
	template struct LeafWord<0x106AC970, 4>;

	// FUNCTION: ENGINE 0x106ACBC0
	template struct LeafWord<0x106ACBC0, 8>;

	// FUNCTION: ENGINE 0x106ACBF0
	template struct LeafArray<0x106ACBF0, 4>;

	// FUNCTION: ENGINE 0x106ACC00
	template struct LeafSetWord<0x106ACC00, 4>;

	// FUNCTION: ENGINE 0x106ACC10
	template struct LeafArray<0x106ACC10, 16>;

	// FUNCTION: ENGINE 0x106ACC20
	template struct LeafArray<0x106ACC20, 16>;

	// FUNCTION: ENGINE 0x106ACC30
	template struct LeafArray<0x106ACC30, 16>;

	// FUNCTION: ENGINE 0x106ACC40
	template struct LeafInitTwo<0x106ACC40, 0, 0>;

	// FUNCTION: ENGINE 0x106ACC90
	template struct LeafArray<0x106ACC90, 16>;

	// FUNCTION: ENGINE 0x106ACCA0
	template struct LeafWord<0x106ACCA0, 4>;

	// FUNCTION: ENGINE 0x106AD340
	template struct LeafArray<0x106AD340, 8>;

	// FUNCTION: ENGINE 0x106AD350
	template struct LeafArray<0x106AD350, 4>;

	// FUNCTION: ENGINE 0x106AD3A0
	template struct LeafWord<0x106AD3A0, 8>;

	// FUNCTION: ENGINE 0x106AD3B0
	template struct LeafArray<0x106AD3B0, 8>;

	// FUNCTION: ENGINE 0x106AD3C0
	template struct LeafArray<0x106AD3C0, 4>;

	// FUNCTION: ENGINE 0x106AD3F0
	template struct LeafArray<0x106AD3F0, 4>;

	// FUNCTION: ENGINE 0x106AD400
	template struct LeafWord<0x106AD400, 4>;

	// FUNCTION: ENGINE 0x106AD410
	template struct LeafTwoWords<0x106AD410>;

	// FUNCTION: ENGINE 0x106AD450
	template struct LeafSetTwoWords<0x106AD450>;

	// FUNCTION: ENGINE 0x106AD960
	template struct LeafZeroThree<0x106AD960>;

	// FUNCTION: ENGINE 0x106AEDF0
	template struct LeafSelf<0x106AEDF0>;

	// FUNCTION: ENGINE 0x106AF010
	template struct LeafInitTwo<0x106AF010, 0, 0>;

	// FUNCTION: ENGINE 0x106AF0A0
	template struct LeafWord<0x106AF0A0, 4>;

	// FUNCTION: ENGINE 0x106AF0B0
	template void LeafNothing<0x106AF0B0>();

	// FUNCTION: ENGINE 0x106AF100
	template void LeafNothing<0x106AF100>();

	// FUNCTION: ENGINE 0x106AF150
	template struct LeafSetWord<0x106AF150, 4>;

	// FUNCTION: ENGINE 0x106AF160
	template struct LeafArray<0x106AF160, 36>;

	// FUNCTION: ENGINE 0x106AF170
	template struct LeafArray<0x106AF170, 36>;

	// FUNCTION: ENGINE 0x106AF180
	template struct LeafWord<0x106AF180, 4>;

	// FUNCTION: ENGINE 0x106AF190
	template void LeafNothing<0x106AF190>();

	// FUNCTION: ENGINE 0x106AF1E0
	template struct LeafSetWord<0x106AF1E0, 4>;

	// FUNCTION: ENGINE 0x106AF1F0
	template void LeafNothing<0x106AF1F0>();

	// FUNCTION: ENGINE 0x106AF240
	template struct LeafSetWord<0x106AF240, 4>;

	// FUNCTION: ENGINE 0x106AF250
	template void LeafNothing<0x106AF250>();

	// FUNCTION: ENGINE 0x106AF350
	template struct LeafSetWord<0x106AF350, 4>;

	// FUNCTION: ENGINE 0x106AF380
	template struct LeafWord<0x106AF380, 0>;

	// FUNCTION: ENGINE 0x106AF390
	template struct LeafSetWord<0x106AF390, 4>;

	// FUNCTION: ENGINE 0x106AF3C0
	template struct LeafWord<0x106AF3C0, 0>;

	// FUNCTION: ENGINE 0x106AF3D0
	template struct LeafWord<0x106AF3D0, 4>;

	// FUNCTION: ENGINE 0x106AF400
	template struct LeafWord<0x106AF400, 0>;

	// FUNCTION: ENGINE 0x106AF410
	template struct LeafWord<0x106AF410, 4>;

	// FUNCTION: ENGINE 0x106AF420
	template struct LeafTwoWords<0x106AF420>;

	// FUNCTION: ENGINE 0x106AF440
	template struct LeafTwoWords<0x106AF440>;

	// FUNCTION: ENGINE 0x106AF460
	template struct LeafTwoWords<0x106AF460>;

	// FUNCTION: ENGINE 0x106AF480
	template struct LeafTwoWords<0x106AF480>;

	// FUNCTION: ENGINE 0x106B23F0
	template void LeafNothing<0x106B23F0>();

	// FUNCTION: ENGINE 0x106B2400
	template void LeafNothing<0x106B2400>();

	// FUNCTION: ENGINE 0x106B2410
	template void LeafNothing<0x106B2410>();

	// FUNCTION: ENGINE 0x106B2890
	template bool LeafFalse<0x106B2890>();

	// FUNCTION: ENGINE 0x106B28A0
	template bool LeafFalse<0x106B28A0>();

	// FUNCTION: ENGINE 0x106B28B0
	template bool LeafFalse<0x106B28B0>();

	// FUNCTION: ENGINE 0x106B2940
	template struct LeafByte<0x106B2940, 44>;

	// FUNCTION: ENGINE 0x106B2950
	template struct LeafByte<0x106B2950, 45>;

	// FUNCTION: ENGINE 0x106B2960
	template struct LeafWord<0x106B2960, 48>;

	// FUNCTION: ENGINE 0x106B3570
	template struct LeafSelf<0x106B3570>;

	// FUNCTION: ENGINE 0x106B3580
	template struct LeafAddress<0x106B3580, 8>;

	// FUNCTION: ENGINE 0x106B35B0
	template struct LeafSelf<0x106B35B0>;

	// FUNCTION: ENGINE 0x106B35C0
	template struct LeafAddress<0x106B35C0, 40>;

	// FUNCTION: ENGINE 0x106B3600
	template struct LeafArray<0x106B3600, 64>;

	// FUNCTION: ENGINE 0x106B3CF0
	template struct LeafWord<0x106B3CF0, 80>;

	// FUNCTION: ENGINE 0x106B3D10
	template struct LeafInitTwo<0x106B3D10, 0, 0>;

	// FUNCTION: ENGINE 0x106B3D60
	template struct LeafWord<0x106B3D60, 4>;

	// FUNCTION: ENGINE 0x106B3D90
	template void LeafNothing<0x106B3D90>();

	// FUNCTION: ENGINE 0x106B3E00
	template struct LeafArray<0x106B3E00, 4>;

	// FUNCTION: ENGINE 0x106B3E10
	template struct LeafWord<0x106B3E10, 0>;

	// FUNCTION: ENGINE 0x106B3E30
	template struct LeafWord<0x106B3E30, 4>;

	// FUNCTION: ENGINE 0x106B3E40
	template void LeafNothing<0x106B3E40>();

	// FUNCTION: ENGINE 0x106B3EA0
	template void LeafNothing<0x106B3EA0>();

	// FUNCTION: ENGINE 0x106B3F10
	template void LeafNothing<0x106B3F10>();

	// FUNCTION: ENGINE 0x106B3F60
	template struct LeafArray<0x106B3F60, 8>;

	// FUNCTION: ENGINE 0x106B3F70
	template struct LeafTwoWords<0x106B3F70>;

	// FUNCTION: ENGINE 0x106B3F90
	template struct LeafTwoWords<0x106B3F90>;

	// FUNCTION: ENGINE 0x106B3FB0
	template struct LeafTwoWords<0x106B3FB0>;

	// FUNCTION: ENGINE 0x106B4090
	template int LeafZero<0x106B4090>();

	// FUNCTION: ENGINE 0x106B40A0
	template int LeafZero<0x106B40A0>();

	// FUNCTION: ENGINE 0x106B5460
	template struct LeafAddress<0x106B5460, 4>;

	// FUNCTION: ENGINE 0x106B5470
	template struct LeafWord<0x106B5470, 0>;

	// FUNCTION: ENGINE 0x106B5480
	template struct LeafWord<0x106B5480, 12>;

	// FUNCTION: ENGINE 0x106B5490
	template struct LeafWord<0x106B5490, 20>;

	// FUNCTION: ENGINE 0x106B54C0
	template struct LeafArray<0x106B54C0, 8>;

	// FUNCTION: ENGINE 0x106B5720
	template struct LeafAddress<0x106B5720, 24>;

	// FUNCTION: ENGINE 0x106B5730
	template struct LeafAddress<0x106B5730, 24>;

	// FUNCTION: ENGINE 0x106B5740
	template struct LeafAddress<0x106B5740, 36>;

	// FUNCTION: ENGINE 0x106B5750
	template struct LeafAddress<0x106B5750, 12>;

	// FUNCTION: ENGINE 0x106B5760
	template struct LeafAddress<0x106B5760, 58>;

	// FUNCTION: ENGINE 0x106B5800
	template struct LeafWord<0x106B5800, 84>;

	// FUNCTION: ENGINE 0x106B58D0
	template struct LeafTwoWords<0x106B58D0>;

	// FUNCTION: ENGINE 0x106B58F0
	template struct LeafTwoWords<0x106B58F0>;

	// FUNCTION: ENGINE 0x106B5910
	template struct LeafTwoWords<0x106B5910>;

	// FUNCTION: ENGINE 0x106B5930
	template struct LeafTwoWords<0x106B5930>;

	// FUNCTION: ENGINE 0x106B5970
	template struct LeafWord<0x106B5970, 0>;

	// FUNCTION: ENGINE 0x106B5980
	template struct LeafArray<0x106B5980, 12>;

	// FUNCTION: ENGINE 0x106B59A0
	template struct LeafWord<0x106B59A0, 0>;

	// FUNCTION: ENGINE 0x106B59C0
	template struct LeafWord<0x106B59C0, 0>;

	// FUNCTION: ENGINE 0x106B59F0
	template struct LeafArray<0x106B59F0, 52>;

	// FUNCTION: ENGINE 0x106B5A10
	template struct LeafArray<0x106B5A10, 4>;

	// FUNCTION: ENGINE 0x106B5A20
	template struct LeafWord<0x106B5A20, 4>;

	// FUNCTION: ENGINE 0x106B5A80
	template struct LeafWord<0x106B5A80, 0>;

	// FUNCTION: ENGINE 0x106B5AB0
	template struct LeafArray<0x106B5AB0, 12>;

	// FUNCTION: ENGINE 0x106B5AE0
	template struct LeafWord<0x106B5AE0, 0>;

	// FUNCTION: ENGINE 0x106B5AF0
	template struct LeafArray<0x106B5AF0, 12>;

	// FUNCTION: ENGINE 0x106B5B00
	template struct LeafWord<0x106B5B00, 0>;

	// FUNCTION: ENGINE 0x106B5B10
	template struct LeafWord<0x106B5B10, 4>;

	// FUNCTION: ENGINE 0x106B5B40
	template struct LeafArray<0x106B5B40, 8>;

	// FUNCTION: ENGINE 0x106B5C20
	template struct LeafSelf<0x106B5C20>;

	// FUNCTION: ENGINE 0x106B5C30
	template void LeafNothing<0x106B5C30>();

	// FUNCTION: ENGINE 0x106B5C90
	template struct LeafSelf<0x106B5C90>;

	// FUNCTION: ENGINE 0x106B5CA0
	template void LeafNothing<0x106B5CA0>();

	// FUNCTION: ENGINE 0x106B5E00
	template int LeafZero<0x106B5E00>();

	// FUNCTION: ENGINE 0x106B5E50
	template void LeafNothing<0x106B5E50>();

	// FUNCTION: ENGINE 0x106B5E80
	template void LeafNothing<0x106B5E80>();

	// FUNCTION: ENGINE 0x106B5E90
	template void LeafNothing<0x106B5E90>();

	// FUNCTION: ENGINE 0x106B5F80
	template int LeafZero<0x106B5F80>();

	// FUNCTION: ENGINE 0x106B5F90
	template int LeafZero<0x106B5F90>();

	// FUNCTION: ENGINE 0x106B5FA0
	template int LeafZero<0x106B5FA0>();

	// FUNCTION: ENGINE 0x106B5FB0
	template int LeafZero<0x106B5FB0>();

	// FUNCTION: ENGINE 0x106B5FC0
	template int LeafZero<0x106B5FC0>();

	// FUNCTION: ENGINE 0x106B6810
	template struct LeafZeroThree<0x106B6810>;

	// FUNCTION: ENGINE 0x106B68A0
	template struct LeafZeroThree<0x106B68A0>;

	// FUNCTION: ENGINE 0x106B68C0
	template struct LeafZeroThree<0x106B68C0>;

	// FUNCTION: ENGINE 0x106B6970
	template void LeafNothing<0x106B6970>();

	// FUNCTION: ENGINE 0x106B6A00
	template void LeafNothing<0x106B6A00>();

	// FUNCTION: ENGINE 0x106B6A10
	template void LeafNothing<0x106B6A10>();

	// FUNCTION: ENGINE 0x106B7310
	template void LeafNothing<0x106B7310>();

	// FUNCTION: ENGINE 0x106B7B30
	template struct LeafWord<0x106B7B30, 4>;

	// FUNCTION: ENGINE 0x106B7B40
	template struct LeafWord<0x106B7B40, 8>;

	// FUNCTION: ENGINE 0x106BBD60
	template struct LeafFloat<0x106BBD60, 76>;

	// FUNCTION: ENGINE 0x106BBDA0
	template struct LeafFloat<0x106BBDA0, 236>;

	// FUNCTION: ENGINE 0x106BCB00
	template struct LeafWord<0x106BCB00, 12>;

	// FUNCTION: ENGINE 0x106BCB10
	template struct LeafWord<0x106BCB10, 16>;

	// FUNCTION: ENGINE 0x106BF7D0
	template struct LeafSelf<0x106BF7D0>;

	// FUNCTION: ENGINE 0x106BF830
	template struct LeafWord<0x106BF830, 0>;

	// FUNCTION: ENGINE 0x106BF860
	template struct LeafArray<0x106BF860, 36>;

	// FUNCTION: ENGINE 0x106BF870
	template struct LeafWord<0x106BF870, 0>;

	// FUNCTION: ENGINE 0x106BF8B0
	template struct LeafSelf<0x106BF8B0>;

	// FUNCTION: ENGINE 0x106BF8C0
	template struct LeafWord<0x106BF8C0, 96>;
}
