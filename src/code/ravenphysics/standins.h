// Stand-ins for the small leaf functions of 0x10680000 - 0x106A0000: bare accessors, three-word constructors and
// element addressing the engine keeps out of line. The image names no owner for them, so every class is a stand-in grouped
// by the neighbourhood of its functions and every member is a guess; a unit that recovers the real classes should move the
// functions onto them.
#ifndef RAVENPHYSICS_STANDINS_H
#define RAVENPHYSICS_STANDINS_H

namespace ravenphysics
{
	class ScratchStack;
	class StackAllocator;

	// Three words, all zero; the parameter names the engine function (the constructor of a three-word block)
	template <int Function>
	struct ZeroedWords
	{
		ZeroedWords();

		int first;
		int second;
		int third;
	};

	// Two words taken from the arguments; the parameter names the engine function
	template <int Function>
	struct WordPair
	{
		WordPair(int newFirst, int newSecond);

		int first;
		int second;
	};

	// Two words, both zero; the parameter names the engine function
	template <int Function>
	struct ZeroedTwoWords
	{
		ZeroedTwoWords();

		int first;
		int second;
	};

	struct Block10682020
	{
		int Unknown10682020() const;
		int* Unknown10682030(int index);

		int* m0;
		int m4;
	};

	struct Block10682040
	{
		unsigned char* Unknown10682040(int index);
		int Unknown10682050() const;

		unsigned char* m0;
		int m4;
	};

	struct Block10682060
	{
		int* Unknown10682060(int index);
		int* Unknown10682070(int index);

		int* m0;
	};

	struct Block10682080
	{
		double* Unknown10682080(int index);

		double* m0;
	};

	struct Block10682090
	{
		int* Unknown10682090(int index);
		int* Unknown106820A0(int index);
		int* Unknown106820B0(int index);
		int* Unknown106820C0(int index);
		int* Unknown106820D0(int index);

		int* m0;
	};

	struct Block106823A0
	{
		void Unknown106823A0(int newCount, int unused);
		void Unknown106823D0(int newCount, int unused);
		void Unknown10682400(int newCount, int unused);
		void Unknown10682430(int unused);
		void Unknown10682460(int unused);
		void Unknown10682490(int unused);

		void* m0;
		int m4;
	};

	struct Block106824C0
	{
		int Unknown106824C0() const;
		int Unknown106824D0() const;

		int m0;
		int m4;
	};

	struct Block10682670
	{
		unsigned short Unknown10682670(unsigned int key) const;
		unsigned short Unknown10682690(unsigned int key) const;

		unsigned char unknown0[0xC];
		unsigned short mC;
	};

	struct Block10682820
	{
		void Unknown10682820(int newCount, int unused);
		void Unknown10682850(int newCount, int unused);
		void Unknown10682880(int newCount, int unused);
		void Unknown106828B0(int newCount, int unused);
		void Unknown106828E0(int newCount, int unused);
		void Unknown10682910(int unused);
		void Unknown10682940(int unused);
		void Unknown10682970(int unused);
		void Unknown106829A0(int unused);
		void Unknown106829D0(int unused);
		void Unknown10682A00(int unused);

		void* m0;
		int m4;
	};

	struct Block10682E30
	{
		void Unknown10682E30();
		void Unknown10682E60();
		void Unknown10682E90();

		void* m0;
		int m4;
	};

	struct Block10684FA0
	{
		int* Unknown10684FA0(int index);
		int Unknown10684FD0() const;
		int Unknown10684FE0() const;

		int* m0;
		int m4;
	};

	struct Block10685040
	{
		Block10685040* Unknown10685040();
		void Unknown10685050();

	};

	struct Block106850B0
	{
		Block106850B0* Unknown106850B0();
		void Unknown106850C0();

	};

	struct Block10685120
	{
		Block10685120* Unknown10685120();
		void Unknown10685130();
		int Unknown10685140() const;

		int m0;
	};

	struct Block106851A0
	{
		void Unknown106851A0();
		void Unknown106851B0();

	};

	struct Block106853A0
	{
		void Unknown106853A0();
		void Unknown106853B0();

	};

	struct Block106859C0
	{
		void Unknown106859C0();
		void Unknown106859D0();

		int m0;
		int m4;
	};

	struct Block106861D0
	{
		int Unknown106861D0() const;
		int* Unknown106861E0(int index);

		int* m0;
		int m4;
	};

	struct Block10686220
	{
		void Unknown10686220(int newCount, int unused);
		void Unknown10686250(int unused);

		void* m0;
		int m4;
	};

	struct Block10686370
	{
		unsigned short Unknown10686370(unsigned int key) const;

		unsigned char unknown0[0xC];
		unsigned short mC;
	};

	struct Block10686A60
	{
		long Unknown10686A60();
		long Unknown10686A70();
		int Unknown10686AA0() const;
		unsigned char* Unknown10686AB0();
		unsigned char* Unknown10686AC0();
		unsigned char* Unknown10686AD0();
		unsigned char* Unknown10686AE0();
		unsigned char* Unknown10686AF0();
		unsigned char* Unknown10686B00();
		unsigned char* Unknown10686B10();
		unsigned char* Unknown10686B20();
		unsigned char* Unknown10686B30();

		volatile long m0;
		unsigned char unknown4[0x8];
		int mC;
		unsigned char unknown10[0x70];
		unsigned char m80;
		unsigned char unknown81[0x1F];
		unsigned char mA0;
		unsigned char unknownA1[0x1F];
		unsigned char mC0;
		unsigned char unknownC1[0x7];
		unsigned char mC8;
		unsigned char unknownC9[0x2B];
		unsigned char mF4;
		unsigned char unknownF5[0xF];
		unsigned char m104;
		unsigned char unknown105[0x33];
		unsigned char m138;
		unsigned char unknown139[0x7];
		unsigned char m140;
		unsigned char unknown141[0x7];
		unsigned char m148;
	};

	struct Block10686DD0
	{
		int Unknown10686DD0() const;
		int Unknown10686E00() const;

		int m0;
		unsigned char unknown4[0x4];
		int m8;
	};

	struct Block10686E10
	{
		unsigned char* Unknown10686E10(int index);
		int Unknown10686E20() const;
		unsigned char* Unknown10686E30();

		unsigned char* m0;
		int m4;
		unsigned char unknown8[0x10];
		unsigned char m18;
	};

	struct Block10686E60
	{
		int Unknown10686E60() const;
		int Unknown10686E80() const;
		int Unknown10686E90() const;

		int m0;
		int m4;
	};

	struct Block10686EE0
	{
		unsigned char* Unknown10686F10(int index);
		int Unknown10686F20() const;

		unsigned char* m0;
		int m4;
	};

	struct Block10686F70
	{
		int Unknown10686F70() const;
		int Unknown10686F80() const;
		int Unknown10686FB0() const;
		int Unknown10687000() const;

		int m0;
		int m4;
	};

	struct Block10687110
	{
		void Unknown10687190(int newFirst, int newSecond);
		unsigned char* Unknown106871B0();
		Block10687110* Unknown106871D0();
		void Unknown106871E0();
		int Unknown106871F0() const;
		Block10687110* Unknown10687200();
		void Unknown10687210();
		int Unknown10687220() const;

		int m0;
		int m4;
		unsigned char unknown8[0x8];
		unsigned char m10;
		unsigned char unknown11[0xF];
		int m20;
		unsigned char unknown24[0x8];
		bool m2C;
		unsigned char unknown2D[0x3];
		int m30;
	};

	struct Block10687230
	{
		void Unknown10687230(int newCount, StackAllocator* stack);
		Block10687230* Unknown10687250();
		void Unknown10687260();

		void* m0;
		int m4;
		unsigned char unknown8[0x24];
		bool m2C;
		unsigned char unknown2D[0x3];
		int m30;
	};

	struct Block106872D0
	{
		int Unknown106872D0() const;
		int Unknown106872E0() const;
		Block106872D0* Unknown106872F0();
		void Unknown10687300();

		unsigned char unknown0[0x20];
		int m20;
		int m24;
		int m28;
		bool m2C;
		unsigned char unknown2D[0x3];
		int m30;
	};

	struct Block10687370
	{
		int Unknown10687370() const;
		int Unknown10687380() const;
		Block10687370* Unknown10687390();
		void Unknown106873A0();
		int Unknown106873C0() const;
		int Unknown106873D0() const;

		unsigned char unknown0[0x20];
		int m20;
		int m24;
		int m28;
		bool m2C;
		unsigned char unknown2D[0x3];
		int m30;
	};

	struct Block10687490
	{
		void Unknown10687490(int newCount, ScratchStack* stack);
		Block10687490* Unknown106874B0();
		void Unknown106874C0();
		int Unknown106874E0() const;
		Block10687490* Unknown106874F0();
		void Unknown10687500();
		int Unknown10687530() const;

		void* m0;
		int m4;
		unsigned char unknown8[0x18];
		int m20;
		unsigned char unknown24[0x8];
		bool m2C;
		unsigned char unknown2D[0x3];
		int m30;
	};

	struct Block10687800
	{
		int Unknown10687800() const;

		int m0;
	};

	struct Block10687870
	{
		void Unknown10687870(int newFirst, int newSecond);

		int m0;
		int m4;
	};

	struct Block10687900
	{
		void Unknown10687900(int newCount, ScratchStack* stack);

		void* m0;
		int m4;
	};

	struct Block10687930
	{
		void Unknown10687930(int newFirst, int newThird);
		void Unknown10687950(int newFirst, int newSecond);
		unsigned char* Unknown10687990();
		int Unknown106879A0() const;
		int Unknown106879B0() const;

		int m0;
		int m4;
		int m8;
		unsigned char unknownC[0xA4];
		unsigned char mB0;
	};

	struct Block10687E00
	{
		void Unknown10687E10(int newFirst, int newThird);

		int m0;
		int m4;
		int m8;
	};

	struct Block10687E80
	{
		void Unknown10687E80(int newCount, StackAllocator* stack);

		void* m0;
		int m4;
		int m8;
	};

	struct Block10687FB0
	{
		void Unknown10687FB0(int newCount, StackAllocator* stack);
		void Unknown10687FF0(int newCount, StackAllocator* stack);
		void Unknown10688020(int newCount, StackAllocator* stack);
		void Unknown10688050(int newCount, StackAllocator* stack);
		void Unknown10688080(int newCount, ScratchStack* stack);
		void Unknown106880B0(int newCount, ScratchStack* stack);
		void Unknown106880E0(int newCount, ScratchStack* stack);
		void Unknown10688110(int newCount, ScratchStack* stack);
		void Unknown10688140(int newCount, ScratchStack* stack);
		void Unknown10688170(int newCount, ScratchStack* stack);
		void Unknown106881A0(int newCount, ScratchStack* stack);

		void* m0;
		int m4;
		int m8;
	};

	struct Block10688390
	{
		void Unknown10688390(int newFirst, int newThird);

		int m0;
		int m4;
		int m8;
	};

	struct Block1068A8E0
	{
		int Unknown1068A8E0() const;
		bool Unknown1068A8F0() const;
		int Unknown1068A900() const;
		int Unknown1068A910() const;
		int Unknown1068A920() const;
		int Unknown1068A930() const;

		int m0;
		int m4;
		int m8;
	};

	struct Block1068A990
	{
		Block1068A990* Unknown1068A990();

	};

	struct Block1068A9F0
	{
		Block1068A9F0* Unknown1068A9F0();

	};

	struct Block1068AA50
	{
		Block1068AA50* Unknown1068AA50();

	};

	struct Block1068B510
	{
		unsigned char* Unknown1068B510();

		unsigned char unknown0[0x74];
		unsigned char m74;
	};

	struct Block1068B900
	{
		bool Unknown1068B900() const;

		unsigned char unknown0[0x4];
		int m4;
		int m8;
	};

	struct Block1068B970
	{
		int Unknown1068B970() const;
		int Unknown1068B980() const;
		int Unknown1068B990() const;
		int Unknown1068B9A0() const;
		int Unknown1068B9B0() const;
		int Unknown1068B9C0() const;
		bool Unknown1068B9E0() const;
		int Unknown1068B9F0() const;

		int m0;
		int m4;
		int m8;
	};

	struct Block1068BA50
	{
		Block1068BA50* Unknown1068BA50();

	};

	struct Block1068BAB0
	{
		Block1068BAB0* Unknown1068BAB0();
		void Unknown1068BAC0();

	};

	struct Block1068BB30
	{
		void Unknown1068BB30();

	};

	struct Block1068BB90
	{
		Block1068BB90* Unknown1068BB90();

	};

	struct Block1068BBF0
	{
		Block1068BBF0* Unknown1068BBF0();

	};

	struct Block1068BCE0
	{
		void Unknown1068BCE0();

	};

	struct Block1068C730
	{
		void Unknown1068C730();

	};

	struct Block1068D2F0
	{
		void Unknown1068D2F0();

		int m0;
		int m4;
	};

	struct Block1068DF70
	{
		void Unknown1068DF70();
		void Unknown1068DF80();

		int m0;
		int m4;
	};

	struct Block106900A0
	{
		long Unknown106900A0();
		long Unknown106900B0();

		volatile long m0;
	};

	struct Block106900F0
	{
		int Unknown106900F0() const;

		unsigned char unknown0[0xC];
		int mC;
	};

	struct Block10690790
	{
		int Unknown10690790() const;
		int Unknown106907A0() const;
		int Unknown106907C0() const;

		unsigned char unknown0[0x4];
		int m4;
		int m8;
	};

	struct Block10690840
	{
		void Unknown10690840(int newFirst, int newSecond);

		int m0;
		int m4;
	};

	struct Block10690880
	{
		void Unknown10690880(int newCount, ScratchStack* stack);
		void Unknown106908B0(int newCount, ScratchStack* stack);

		void* m0;
		int m4;
		int m8;
	};

	struct Block10690930
	{
		int Unknown10690930() const;

		unsigned char unknown0[0x4];
		int m4;
	};

	struct Block106915E0
	{
		long Unknown106915E0();
		long Unknown106915F0();
		Block106915E0* Unknown10691610();

		volatile long m0;
	};

	struct Block10691F10
	{
		void Unknown10691F10();

	};

	struct Block106950F0
	{
		float Unknown106950F0() const;
		float Unknown10695100() const;
		float Unknown10695110() const;
		float Unknown10695120() const;

		unsigned char unknown0[0x8];
		float m8;
		float mC;
		float m10;
		float m14;
	};

	struct Block10695170
	{
		unsigned char* Unknown10695170();

		unsigned char unknown0[0x40];
		unsigned char m40;
	};

	struct Block106952A0
	{
		unsigned short Unknown106952A0(int unused);

	};

	struct Block10695630
	{
		unsigned char* Unknown10695630();
		unsigned char* Unknown10695640();

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0x63];
		unsigned char m88;
	};

	struct Block10695760
	{
		unsigned char* Unknown10695760();
		unsigned char* Unknown10695770();
		float Unknown10695780() const;
		float Unknown10695790() const;
		float Unknown106957A0() const;
		unsigned char* Unknown106957B0();
		unsigned char* Unknown106957C0();
		unsigned char* Unknown106957D0();
		float Unknown106957E0() const;

		float m0;
		unsigned char unknown4[0x1C];
		unsigned char m20;
		unsigned char unknown21[0x3];
		unsigned char m24;
		unsigned char unknown25[0x7];
		unsigned char m2C;
		unsigned char unknown2D[0x3];
		unsigned char m30;
		unsigned char unknown31[0xB];
		float m3C;
		float m40;
		float m44;
		unsigned char unknown48[0x64];
		unsigned char mAC;
	};

	struct Block10695FC0
	{
		unsigned char* Unknown10695FC0();
		unsigned char* Unknown10695FD0();
		float Unknown10695FE0() const;
		float Unknown10695FF0() const;
		float Unknown10696000() const;
		float Unknown10696010() const;

		unsigned char unknown0[0x28];
		unsigned char m28;
		unsigned char unknown29[0x17];
		unsigned char m40;
		unsigned char unknown41[0xB];
		float m4C;
		float m50;
		float m54;
		unsigned char unknown58[0x44];
		float m9C;
	};

	struct Block10696950
	{
		unsigned char* Unknown10696950();
		float Unknown10696960() const;
		unsigned char* Unknown10696970();

		unsigned char unknown0[0x60];
		unsigned char m60;
		unsigned char unknown61[0x17];
		unsigned char m78;
		unsigned char unknown79[0xB];
		float m84;
	};

	struct Block10697A90
	{
		unsigned char* Unknown10697A90();
		unsigned char* Unknown10697AA0();
		unsigned char* Unknown10697AB0();

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0xB];
		unsigned char m30;
		unsigned char unknown31[0xB];
		unsigned char m3C;
	};

	struct Block106990C0
	{
		unsigned char* Unknown106990C0();
		unsigned char* Unknown106990D0();
		float Unknown106990E0() const;
		float Unknown106990F0() const;
		float Unknown10699100() const;
		unsigned char* Unknown10699110();
		unsigned char* Unknown10699120();

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0xB];
		unsigned char m30;
		unsigned char unknown31[0xB];
		float m3C;
		float m40;
		float m44;
		unsigned char m48;
		unsigned char unknown49[0xB];
		unsigned char m54;
	};

	struct Block10699AC0
	{
		unsigned char* Unknown10699AC0();
		float Unknown10699AD0() const;
		float Unknown10699AE0() const;
		unsigned char* Unknown10699AF0();
		unsigned char* Unknown10699B00();

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0x23];
		float m48;
		float m4C;
		unsigned char m50;
		unsigned char unknown51[0xB];
		unsigned char m5C;
	};

	struct Block1069AA30
	{
		unsigned char* Unknown1069AA30();
		unsigned char* Unknown1069AA40();

		unsigned char unknown0[0x48];
		unsigned char m48;
		unsigned char unknown49[0x3];
		unsigned char m4C;
	};

	struct Block1069AF70
	{
		float Unknown1069AF70() const;
		float Unknown1069AF80() const;
		unsigned char* Unknown1069AF90();
		unsigned char* Unknown1069AFA0();
		unsigned char* Unknown1069AFB0();

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0xB];
		unsigned char m30;
		unsigned char unknown31[0xB];
		unsigned char m3C;
		unsigned char unknown3D[0xB];
		float m48;
		float m4C;
	};

	struct Block1069B820
	{
		unsigned char* Unknown1069B820();
		unsigned char* Unknown1069B830();
		float Unknown1069B840() const;
		float Unknown1069B850() const;

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0xB];
		unsigned char m30;
		unsigned char unknown31[0xF];
		float m40;
		float m44;
	};

	struct Block1069C210
	{
		float Unknown1069C210() const;
		float Unknown1069C220() const;

		unsigned char unknown0[0x50];
		float m50;
		float m54;
	};

	struct Block1069C710
	{
		unsigned char* Unknown1069C710();
		unsigned char* Unknown1069C720();

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0x63];
		unsigned char m88;
	};

	struct Block1069C7C0
	{
		float Unknown1069C7C0() const;
		unsigned char* Unknown1069C7D0();
		unsigned char* Unknown1069C7E0();
		float Unknown1069C7F0() const;
		float Unknown1069C800() const;
		float Unknown1069C810() const;
		float Unknown1069C820() const;

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0xB];
		unsigned char m30;
		unsigned char unknown31[0x17];
		float m48;
		float m4C;
		float m50;
		float m54;
		unsigned char unknown58[0x4];
		float m5C;
	};

	struct Block1069D0D0
	{
		unsigned char* Unknown1069D0D0();
		unsigned char* Unknown1069D0E0();
		float Unknown1069D0F0() const;
		float Unknown1069D100() const;
		float Unknown1069D110() const;

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0xB];
		unsigned char m30;
		unsigned char unknown31[0xB];
		float m3C;
		float m40;
		float m44;
	};

	struct Block1069DA70
	{
		unsigned char* Unknown1069DA70();
		unsigned char* Unknown1069DA80();

		unsigned char unknown0[0x58];
		unsigned char m58;
		unsigned char unknown59[0xB];
		unsigned char m64;
	};

	struct Block1069DAD0
	{
		unsigned char* Unknown1069DAD0();
		float Unknown1069DAE0() const;
		float Unknown1069DAF0() const;

		unsigned char unknown0[0x28];
		unsigned char m28;
		unsigned char unknown29[0x23];
		float m4C;
		float m50;
	};

	struct Block1069EA60
	{
		unsigned char* Unknown1069EA60();
		unsigned char* Unknown1069EA70();
		float Unknown1069EA80() const;
		float Unknown1069EA90() const;
		float Unknown1069EAA0() const;
		float Unknown1069EAB0() const;
		void Unknown1069EAE0(float value);
		float Unknown1069EAF0() const;
		float Unknown1069EB00() const;
		float Unknown1069EB10() const;

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0xB];
		unsigned char m30;
		unsigned char unknown31[0x17];
		float m48;
		float m4C;
		float m50;
		float m54;
		float m58;
		unsigned char unknown5C[0x4];
		float m60;
		unsigned char unknown64[0x4];
		float m68;
	};

	struct Block1069F4A0
	{
		unsigned char* Unknown1069F4A0();
		float Unknown1069F4B0() const;
		float Unknown1069F4C0() const;

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0xB];
		float m30;
		float m34;
	};

	struct Block1069F7A0
	{
		unsigned char* Unknown1069F7A0();
		unsigned char* Unknown1069F7B0();
		float Unknown1069F7C0() const;
		float Unknown1069F7D0() const;

		unsigned char unknown0[0x24];
		unsigned char m24;
		unsigned char unknown25[0xB];
		unsigned char m30;
		unsigned char unknown31[0xB];
		float m3C;
		float m40;
	};

	struct Block1069FD00
	{
		float Unknown1069FD00() const;
		unsigned char* Unknown1069FD10();

		unsigned char unknown0[0x24];
		float m24;
		unsigned char unknown28[0x1C];
		unsigned char m44;
	};

	struct Block1069FFE0
	{
		unsigned char* Unknown1069FFE0();
		unsigned char* Unknown1069FFF0();

		unsigned char unknown0[0x48];
		unsigned char m48;
		unsigned char unknown49[0xB];
		unsigned char m54;
	};

}

#endif
