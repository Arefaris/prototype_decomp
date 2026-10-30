// The small leaf functions of 0x10680000 - 0x106A0000; see standins.h.
#include "code/ravenphysics/standins.h"

namespace ravenphysics
{
	template <int Function>
	ZeroedWords<Function>::ZeroedWords()
	{
		first = 0;
		second = 0;
		third = 0;
	}

	// FUNCTION: ENGINE 0x10685230
	template struct ZeroedWords<0x10685230>;

	// FUNCTION: ENGINE 0x106852C0
	template struct ZeroedWords<0x106852C0>;

	// FUNCTION: ENGINE 0x106852D0
	template struct ZeroedWords<0x106852D0>;

	// FUNCTION: ENGINE 0x10687CF0
	template struct ZeroedWords<0x10687CF0>;

	// FUNCTION: ENGINE 0x10687D10
	template struct ZeroedWords<0x10687D10>;

	// FUNCTION: ENGINE 0x10687D40
	template struct ZeroedWords<0x10687D40>;

	// FUNCTION: ENGINE 0x10687D50
	template struct ZeroedWords<0x10687D50>;

	// FUNCTION: ENGINE 0x10687D60
	template struct ZeroedWords<0x10687D60>;

	// FUNCTION: ENGINE 0x10687D70
	template struct ZeroedWords<0x10687D70>;

	// FUNCTION: ENGINE 0x10687D80
	template struct ZeroedWords<0x10687D80>;

	// FUNCTION: ENGINE 0x10687D90
	template struct ZeroedWords<0x10687D90>;

	// FUNCTION: ENGINE 0x10687DA0
	template struct ZeroedWords<0x10687DA0>;

	// FUNCTION: ENGINE 0x10687DB0
	template struct ZeroedWords<0x10687DB0>;

	// FUNCTION: ENGINE 0x10687DC0
	template struct ZeroedWords<0x10687DC0>;

	// FUNCTION: ENGINE 0x10687DD0
	template struct ZeroedWords<0x10687DD0>;

	// FUNCTION: ENGINE 0x10687DE0
	template struct ZeroedWords<0x10687DE0>;

	// FUNCTION: ENGINE 0x10687DF0
	template struct ZeroedWords<0x10687DF0>;

	// FUNCTION: ENGINE 0x10687E00
	template struct ZeroedWords<0x10687E00>;

	// FUNCTION: ENGINE 0x106884B0
	template struct ZeroedWords<0x106884B0>;

	// FUNCTION: ENGINE 0x10688540
	template struct ZeroedWords<0x10688540>;

	// FUNCTION: ENGINE 0x10688580
	template struct ZeroedWords<0x10688580>;

	// FUNCTION: ENGINE 0x1068AC10
	template struct ZeroedWords<0x1068AC10>;

	// FUNCTION: ENGINE 0x1068AC70
	template struct ZeroedWords<0x1068AC70>;

	// FUNCTION: ENGINE 0x1068ACD0
	template struct ZeroedWords<0x1068ACD0>;

	// FUNCTION: ENGINE 0x1068B330
	template struct ZeroedWords<0x1068B330>;

	// FUNCTION: ENGINE 0x1068C2B0
	template struct ZeroedWords<0x1068C2B0>;

	// FUNCTION: ENGINE 0x1068C310
	template struct ZeroedWords<0x1068C310>;

	// FUNCTION: ENGINE 0x1068C370
	template struct ZeroedWords<0x1068C370>;

	// FUNCTION: ENGINE 0x1068C390
	template struct ZeroedWords<0x1068C390>;

	// FUNCTION: ENGINE 0x1068C3F0
	template struct ZeroedWords<0x1068C3F0>;

	template <int Function>
	WordPair<Function>::WordPair(int newFirst, int newSecond)
	{
		first = newFirst;
		second = newSecond;
	}

	// FUNCTION: ENGINE 0x10686DE0
	template struct WordPair<0x10686DE0>;

	// FUNCTION: ENGINE 0x10686FC0
	template struct WordPair<0x10686FC0>;

	// FUNCTION: ENGINE 0x10686FE0
	template struct WordPair<0x10686FE0>;

	// FUNCTION: ENGINE 0x10687010
	template struct WordPair<0x10687010>;

	// FUNCTION: ENGINE 0x10687030
	template struct WordPair<0x10687030>;

	// FUNCTION: ENGINE 0x10687050
	template struct WordPair<0x10687050>;

	// FUNCTION: ENGINE 0x10687070
	template struct WordPair<0x10687070>;

	// FUNCTION: ENGINE 0x10687090
	template struct WordPair<0x10687090>;

	// FUNCTION: ENGINE 0x106870B0
	template struct WordPair<0x106870B0>;

	// FUNCTION: ENGINE 0x106870D0
	template struct WordPair<0x106870D0>;

	// FUNCTION: ENGINE 0x106870F0
	template struct WordPair<0x106870F0>;

	// FUNCTION: ENGINE 0x10687110
	template struct WordPair<0x10687110>;

	// FUNCTION: ENGINE 0x10687130
	template struct WordPair<0x10687130>;

	// FUNCTION: ENGINE 0x10687150
	template struct WordPair<0x10687150>;

	// FUNCTION: ENGINE 0x10687170
	template struct WordPair<0x10687170>;

	// FUNCTION: ENGINE 0x10682020
	int Block10682020::Unknown10682020() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10682030
	int* Block10682020::Unknown10682030(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x10682040
	unsigned char* Block10682040::Unknown10682040(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x10682050
	int Block10682040::Unknown10682050() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10682060
	int* Block10682060::Unknown10682060(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x10682070
	int* Block10682060::Unknown10682070(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x10682080
	double* Block10682080::Unknown10682080(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x10682090
	int* Block10682090::Unknown10682090(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x106820A0
	int* Block10682090::Unknown106820A0(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x106820B0
	int* Block10682090::Unknown106820B0(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x106820C0
	int* Block10682090::Unknown106820C0(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x106820D0
	int* Block10682090::Unknown106820D0(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x106824C0
	int Block106824C0::Unknown106824C0() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x106824D0
	int Block106824C0::Unknown106824D0() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10684FA0
	int* Block10684FA0::Unknown10684FA0(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x10684FD0
	int Block10684FA0::Unknown10684FD0() const
	{
		return m4 - 8;
	}

	// FUNCTION: ENGINE 0x10684FE0
	int Block10684FA0::Unknown10684FE0() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10685040
	Block10685040* Block10685040::Unknown10685040()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x10685050
	void Block10685040::Unknown10685050()
	{
	}

	// FUNCTION: ENGINE 0x106850B0
	Block106850B0* Block106850B0::Unknown106850B0()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x106850C0
	void Block106850B0::Unknown106850C0()
	{
	}

	// FUNCTION: ENGINE 0x10685120
	Block10685120* Block10685120::Unknown10685120()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x10685130
	void Block10685120::Unknown10685130()
	{
	}

	// FUNCTION: ENGINE 0x10685140
	int Block10685120::Unknown10685140() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x106851A0
	void Block106851A0::Unknown106851A0()
	{
	}

	// FUNCTION: ENGINE 0x106851B0
	void Block106851A0::Unknown106851B0()
	{
	}

	// FUNCTION: ENGINE 0x106853A0
	void Block106853A0::Unknown106853A0()
	{
	}

	// FUNCTION: ENGINE 0x106853B0
	void Block106853A0::Unknown106853B0()
	{
	}

	// FUNCTION: ENGINE 0x106859C0
	void Block106859C0::Unknown106859C0()
	{
		m4 = m0;
	}

	// FUNCTION: ENGINE 0x106859D0
	void Block106859C0::Unknown106859D0()
	{
		m4 = m0;
	}

	// FUNCTION: ENGINE 0x106861D0
	int Block106861D0::Unknown106861D0() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x106861E0
	int* Block106861D0::Unknown106861E0(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x10686AA0
	int Block10686AA0::Unknown10686AA0() const
	{
		return mC;
	}

	// FUNCTION: ENGINE 0x10686AB0
	unsigned char* Block10686AA0::Unknown10686AB0()
	{
		return &mC8;
	}

	// FUNCTION: ENGINE 0x10686AC0
	unsigned char* Block10686AA0::Unknown10686AC0()
	{
		return &mF4;
	}

	// FUNCTION: ENGINE 0x10686AD0
	unsigned char* Block10686AA0::Unknown10686AD0()
	{
		return &m104;
	}

	// FUNCTION: ENGINE 0x10686AE0
	unsigned char* Block10686AA0::Unknown10686AE0()
	{
		return &m138;
	}

	// FUNCTION: ENGINE 0x10686AF0
	unsigned char* Block10686AA0::Unknown10686AF0()
	{
		return &m140;
	}

	// FUNCTION: ENGINE 0x10686B00
	unsigned char* Block10686AA0::Unknown10686B00()
	{
		return &m148;
	}

	// FUNCTION: ENGINE 0x10686B10
	unsigned char* Block10686AA0::Unknown10686B10()
	{
		return &mA0;
	}

	// FUNCTION: ENGINE 0x10686B20
	unsigned char* Block10686AA0::Unknown10686B20()
	{
		return &m80;
	}

	// FUNCTION: ENGINE 0x10686B30
	unsigned char* Block10686AA0::Unknown10686B30()
	{
		return &mC0;
	}

	// FUNCTION: ENGINE 0x10686DD0
	int Block10686DD0::Unknown10686DD0() const
	{
		return m8;
	}

	// FUNCTION: ENGINE 0x10686E00
	int Block10686DD0::Unknown10686E00() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x10686E10
	unsigned char* Block10686E10::Unknown10686E10(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x10686E20
	int Block10686E10::Unknown10686E20() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10686E30
	unsigned char* Block10686E10::Unknown10686E30()
	{
		return &m18;
	}

	// FUNCTION: ENGINE 0x10686E60
	int Block10686E60::Unknown10686E60() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x10686E80
	int Block10686E60::Unknown10686E80() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x10686E90
	int Block10686E60::Unknown10686E90() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10686F10
	unsigned char* Block10686F10::Unknown10686F10(int index)
	{
		return m0 + index;
	}

	// FUNCTION: ENGINE 0x10686F20
	int Block10686F10::Unknown10686F20() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10686F70
	int Block10686F70::Unknown10686F70() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x10686F80
	int Block10686F70::Unknown10686F80() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10686FB0
	int Block10686F70::Unknown10686FB0() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10687000
	int Block10686F70::Unknown10687000() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x10687190
	void Block10687110::Unknown10687190(int newFirst, int newSecond)
	{
		m0 = newFirst;
		m4 = newSecond;
	}

	// FUNCTION: ENGINE 0x106871B0
	unsigned char* Block10687110::Unknown106871B0()
	{
		return &m10;
	}

	// FUNCTION: ENGINE 0x106871E0
	void Block10687110::Unknown106871E0()
	{
		m30--;
	}

	// FUNCTION: ENGINE 0x106871F0
	int Block10687110::Unknown106871F0() const
	{
		return m20;
	}

	// FUNCTION: ENGINE 0x10687210
	void Block10687110::Unknown10687210()
	{
		m30--;
	}

	// FUNCTION: ENGINE 0x10687220
	int Block10687110::Unknown10687220() const
	{
		return m20;
	}

	// FUNCTION: ENGINE 0x10687260
	void Block10687260::Unknown10687260()
	{
		m30--;
	}

	// FUNCTION: ENGINE 0x106872E0
	int Block106872E0::Unknown106872E0() const
	{
		return m20;
	}

	// FUNCTION: ENGINE 0x10687300
	void Block106872E0::Unknown10687300()
	{
		m30--;
	}

	// FUNCTION: ENGINE 0x10687380
	int Block10687380::Unknown10687380() const
	{
		return m20;
	}

	// FUNCTION: ENGINE 0x106873A0
	void Block10687380::Unknown106873A0()
	{
		m30--;
	}

	// FUNCTION: ENGINE 0x106873D0
	int Block10687380::Unknown106873D0() const
	{
		return m20;
	}

	// FUNCTION: ENGINE 0x106874C0
	void Block106874C0::Unknown106874C0()
	{
		m30--;
	}

	// FUNCTION: ENGINE 0x106874E0
	int Block106874C0::Unknown106874E0() const
	{
		return m20;
	}

	// FUNCTION: ENGINE 0x10687500
	void Block106874C0::Unknown10687500()
	{
		m30--;
	}

	// FUNCTION: ENGINE 0x10687530
	int Block106874C0::Unknown10687530() const
	{
		return m20;
	}

	// FUNCTION: ENGINE 0x10687800
	int Block10687800::Unknown10687800() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x10687870
	void Block10687870::Unknown10687870(int newFirst, int newSecond)
	{
		m0 = newFirst;
		m4 = newSecond;
	}

	// FUNCTION: ENGINE 0x10687950
	void Block10687950::Unknown10687950(int newFirst, int newSecond)
	{
		m0 = newFirst;
		m4 = newSecond;
	}

	// FUNCTION: ENGINE 0x10687990
	unsigned char* Block10687950::Unknown10687990()
	{
		return &mB0;
	}

	// FUNCTION: ENGINE 0x106879A0
	int Block10687950::Unknown106879A0() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x106879B0
	int Block10687950::Unknown106879B0() const
	{
		return m8;
	}

	// FUNCTION: ENGINE 0x1068A8E0
	int Block1068A8E0::Unknown1068A8E0() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x1068A900
	int Block1068A8E0::Unknown1068A900() const
	{
		return m4 - 48;
	}

	// FUNCTION: ENGINE 0x1068A910
	int Block1068A8E0::Unknown1068A910() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x1068A920
	int Block1068A8E0::Unknown1068A920() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x1068A930
	int Block1068A8E0::Unknown1068A930() const
	{
		return m4 - 12;
	}

	// FUNCTION: ENGINE 0x1068A990
	Block1068A990* Block1068A990::Unknown1068A990()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x1068A9F0
	Block1068A9F0* Block1068A9F0::Unknown1068A9F0()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x1068AA50
	Block1068AA50* Block1068AA50::Unknown1068AA50()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x1068B510
	unsigned char* Block1068B510::Unknown1068B510()
	{
		return &m74;
	}

	// FUNCTION: ENGINE 0x1068B970
	int Block1068B970::Unknown1068B970() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x1068B980
	int Block1068B970::Unknown1068B980() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x1068B990
	int Block1068B970::Unknown1068B990() const
	{
		return m4 - 12;
	}

	// FUNCTION: ENGINE 0x1068B9A0
	int Block1068B970::Unknown1068B9A0() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x1068B9B0
	int Block1068B970::Unknown1068B9B0() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x1068B9C0
	int Block1068B970::Unknown1068B9C0() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x1068B9F0
	int Block1068B970::Unknown1068B9F0() const
	{
		return m4 - 56;
	}

	// FUNCTION: ENGINE 0x1068BA50
	Block1068BA50* Block1068BA50::Unknown1068BA50()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x1068BAB0
	Block1068BAB0* Block1068BAB0::Unknown1068BAB0()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x1068BAC0
	void Block1068BAB0::Unknown1068BAC0()
	{
	}

	// FUNCTION: ENGINE 0x1068BB30
	void Block1068BB30::Unknown1068BB30()
	{
	}

	// FUNCTION: ENGINE 0x1068BB90
	Block1068BB90* Block1068BB90::Unknown1068BB90()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x1068BBF0
	Block1068BBF0* Block1068BBF0::Unknown1068BBF0()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x1068BCE0
	void Block1068BCE0::Unknown1068BCE0()
	{
	}

	// FUNCTION: ENGINE 0x1068C730
	void Block1068C730::Unknown1068C730()
	{
	}

	// FUNCTION: ENGINE 0x1068D2F0
	void Block1068D2F0::Unknown1068D2F0()
	{
		m4 = m0;
	}

	// FUNCTION: ENGINE 0x1068DF70
	void Block1068DF70::Unknown1068DF70()
	{
		m4 = m0;
	}

	// FUNCTION: ENGINE 0x1068DF80
	void Block1068DF70::Unknown1068DF80()
	{
		m4 = m0;
	}

	// FUNCTION: ENGINE 0x106900F0
	int Block106900F0::Unknown106900F0() const
	{
		return mC;
	}

	// FUNCTION: ENGINE 0x10690790
	int Block10690790::Unknown10690790() const
	{
		return m8;
	}

	// FUNCTION: ENGINE 0x106907A0
	int Block10690790::Unknown106907A0() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x106907C0
	int Block10690790::Unknown106907C0() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10690840
	void Block10690840::Unknown10690840(int newFirst, int newSecond)
	{
		m0 = newFirst;
		m4 = newSecond;
	}

	// FUNCTION: ENGINE 0x10690930
	int Block10690930::Unknown10690930() const
	{
		return m4;
	}

	// FUNCTION: ENGINE 0x10691610
	Block10691610* Block10691610::Unknown10691610()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x10691F10
	void Block10691F10::Unknown10691F10()
	{
	}

	// FUNCTION: ENGINE 0x106950F0
	float Block106950F0::Unknown106950F0() const
	{
		return m8;
	}

	// FUNCTION: ENGINE 0x10695100
	float Block106950F0::Unknown10695100() const
	{
		return mC;
	}

	// FUNCTION: ENGINE 0x10695110
	float Block106950F0::Unknown10695110() const
	{
		return m10;
	}

	// FUNCTION: ENGINE 0x10695120
	float Block106950F0::Unknown10695120() const
	{
		return m14;
	}

	// FUNCTION: ENGINE 0x10695170
	unsigned char* Block10695170::Unknown10695170()
	{
		return &m40;
	}

	// FUNCTION: ENGINE 0x106952A0
	unsigned short Block106952A0::Unknown106952A0(int unused)
	{
		return 3;
	}

	// FUNCTION: ENGINE 0x10695630
	unsigned char* Block10695630::Unknown10695630()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x10695640
	unsigned char* Block10695630::Unknown10695640()
	{
		return &m88;
	}

	// FUNCTION: ENGINE 0x10695760
	unsigned char* Block10695760::Unknown10695760()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x10695770
	unsigned char* Block10695760::Unknown10695770()
	{
		return &m30;
	}

	// FUNCTION: ENGINE 0x10695780
	float Block10695760::Unknown10695780() const
	{
		return m3C;
	}

	// FUNCTION: ENGINE 0x10695790
	float Block10695760::Unknown10695790() const
	{
		return m40;
	}

	// FUNCTION: ENGINE 0x106957A0
	float Block10695760::Unknown106957A0() const
	{
		return m44;
	}

	// FUNCTION: ENGINE 0x106957B0
	unsigned char* Block10695760::Unknown106957B0()
	{
		return &mAC;
	}

	// FUNCTION: ENGINE 0x106957C0
	unsigned char* Block10695760::Unknown106957C0()
	{
		return &m20;
	}

	// FUNCTION: ENGINE 0x106957D0
	unsigned char* Block10695760::Unknown106957D0()
	{
		return &m2C;
	}

	// FUNCTION: ENGINE 0x106957E0
	float Block10695760::Unknown106957E0() const
	{
		return m0;
	}

	// FUNCTION: ENGINE 0x10695FC0
	unsigned char* Block10695FC0::Unknown10695FC0()
	{
		return &m28;
	}

	// FUNCTION: ENGINE 0x10695FD0
	unsigned char* Block10695FC0::Unknown10695FD0()
	{
		return &m40;
	}

	// FUNCTION: ENGINE 0x10695FE0
	float Block10695FC0::Unknown10695FE0() const
	{
		return m4C;
	}

	// FUNCTION: ENGINE 0x10695FF0
	float Block10695FC0::Unknown10695FF0() const
	{
		return m50;
	}

	// FUNCTION: ENGINE 0x10696000
	float Block10695FC0::Unknown10696000() const
	{
		return m54;
	}

	// FUNCTION: ENGINE 0x10696010
	float Block10695FC0::Unknown10696010() const
	{
		return m9C;
	}

	// FUNCTION: ENGINE 0x10696950
	unsigned char* Block10696950::Unknown10696950()
	{
		return &m60;
	}

	// FUNCTION: ENGINE 0x10696960
	float Block10696950::Unknown10696960() const
	{
		return m84;
	}

	// FUNCTION: ENGINE 0x10696970
	unsigned char* Block10696950::Unknown10696970()
	{
		return &m78;
	}

	// FUNCTION: ENGINE 0x10697A90
	unsigned char* Block10697A90::Unknown10697A90()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x10697AA0
	unsigned char* Block10697A90::Unknown10697AA0()
	{
		return &m30;
	}

	// FUNCTION: ENGINE 0x10697AB0
	unsigned char* Block10697A90::Unknown10697AB0()
	{
		return &m3C;
	}

	// FUNCTION: ENGINE 0x106990C0
	unsigned char* Block106990C0::Unknown106990C0()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x106990D0
	unsigned char* Block106990C0::Unknown106990D0()
	{
		return &m30;
	}

	// FUNCTION: ENGINE 0x106990E0
	float Block106990C0::Unknown106990E0() const
	{
		return m3C;
	}

	// FUNCTION: ENGINE 0x106990F0
	float Block106990C0::Unknown106990F0() const
	{
		return m40;
	}

	// FUNCTION: ENGINE 0x10699100
	float Block106990C0::Unknown10699100() const
	{
		return m44;
	}

	// FUNCTION: ENGINE 0x10699110
	unsigned char* Block106990C0::Unknown10699110()
	{
		return &m48;
	}

	// FUNCTION: ENGINE 0x10699120
	unsigned char* Block106990C0::Unknown10699120()
	{
		return &m54;
	}

	// FUNCTION: ENGINE 0x10699AC0
	unsigned char* Block10699AC0::Unknown10699AC0()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x10699AD0
	float Block10699AC0::Unknown10699AD0() const
	{
		return m48;
	}

	// FUNCTION: ENGINE 0x10699AE0
	float Block10699AC0::Unknown10699AE0() const
	{
		return m4C;
	}

	// FUNCTION: ENGINE 0x10699AF0
	unsigned char* Block10699AC0::Unknown10699AF0()
	{
		return &m50;
	}

	// FUNCTION: ENGINE 0x10699B00
	unsigned char* Block10699AC0::Unknown10699B00()
	{
		return &m5C;
	}

	// FUNCTION: ENGINE 0x1069AA30
	unsigned char* Block1069AA30::Unknown1069AA30()
	{
		return &m48;
	}

	// FUNCTION: ENGINE 0x1069AA40
	unsigned char* Block1069AA30::Unknown1069AA40()
	{
		return &m4C;
	}

	// FUNCTION: ENGINE 0x1069AF70
	float Block1069AF70::Unknown1069AF70() const
	{
		return m48;
	}

	// FUNCTION: ENGINE 0x1069AF80
	float Block1069AF70::Unknown1069AF80() const
	{
		return m4C;
	}

	// FUNCTION: ENGINE 0x1069AF90
	unsigned char* Block1069AF70::Unknown1069AF90()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x1069AFA0
	unsigned char* Block1069AF70::Unknown1069AFA0()
	{
		return &m30;
	}

	// FUNCTION: ENGINE 0x1069AFB0
	unsigned char* Block1069AF70::Unknown1069AFB0()
	{
		return &m3C;
	}

	// FUNCTION: ENGINE 0x1069B820
	unsigned char* Block1069B820::Unknown1069B820()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x1069B830
	unsigned char* Block1069B820::Unknown1069B830()
	{
		return &m30;
	}

	// FUNCTION: ENGINE 0x1069B840
	float Block1069B820::Unknown1069B840() const
	{
		return m40;
	}

	// FUNCTION: ENGINE 0x1069B850
	float Block1069B820::Unknown1069B850() const
	{
		return m44;
	}

	// FUNCTION: ENGINE 0x1069C210
	float Block1069C210::Unknown1069C210() const
	{
		return m50;
	}

	// FUNCTION: ENGINE 0x1069C220
	float Block1069C210::Unknown1069C220() const
	{
		return m54;
	}

	// FUNCTION: ENGINE 0x1069C710
	unsigned char* Block1069C710::Unknown1069C710()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x1069C720
	unsigned char* Block1069C710::Unknown1069C720()
	{
		return &m88;
	}

	// FUNCTION: ENGINE 0x1069C7C0
	float Block1069C7C0::Unknown1069C7C0() const
	{
		return m48;
	}

	// FUNCTION: ENGINE 0x1069C7D0
	unsigned char* Block1069C7C0::Unknown1069C7D0()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x1069C7E0
	unsigned char* Block1069C7C0::Unknown1069C7E0()
	{
		return &m30;
	}

	// FUNCTION: ENGINE 0x1069C7F0
	float Block1069C7C0::Unknown1069C7F0() const
	{
		return m4C;
	}

	// FUNCTION: ENGINE 0x1069C800
	float Block1069C7C0::Unknown1069C800() const
	{
		return m50;
	}

	// FUNCTION: ENGINE 0x1069C810
	float Block1069C7C0::Unknown1069C810() const
	{
		return m54;
	}

	// FUNCTION: ENGINE 0x1069C820
	float Block1069C7C0::Unknown1069C820() const
	{
		return m5C;
	}

	// FUNCTION: ENGINE 0x1069D0D0
	unsigned char* Block1069D0D0::Unknown1069D0D0()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x1069D0E0
	unsigned char* Block1069D0D0::Unknown1069D0E0()
	{
		return &m30;
	}

	// FUNCTION: ENGINE 0x1069D0F0
	float Block1069D0D0::Unknown1069D0F0() const
	{
		return m3C;
	}

	// FUNCTION: ENGINE 0x1069D100
	float Block1069D0D0::Unknown1069D100() const
	{
		return m40;
	}

	// FUNCTION: ENGINE 0x1069D110
	float Block1069D0D0::Unknown1069D110() const
	{
		return m44;
	}

	// FUNCTION: ENGINE 0x1069DA70
	unsigned char* Block1069DA70::Unknown1069DA70()
	{
		return &m58;
	}

	// FUNCTION: ENGINE 0x1069DA80
	unsigned char* Block1069DA70::Unknown1069DA80()
	{
		return &m64;
	}

	// FUNCTION: ENGINE 0x1069DAD0
	unsigned char* Block1069DAD0::Unknown1069DAD0()
	{
		return &m28;
	}

	// FUNCTION: ENGINE 0x1069DAE0
	float Block1069DAD0::Unknown1069DAE0() const
	{
		return m4C;
	}

	// FUNCTION: ENGINE 0x1069DAF0
	float Block1069DAD0::Unknown1069DAF0() const
	{
		return m50;
	}

	// FUNCTION: ENGINE 0x1069EA60
	unsigned char* Block1069EA60::Unknown1069EA60()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x1069EA70
	unsigned char* Block1069EA60::Unknown1069EA70()
	{
		return &m30;
	}

	// FUNCTION: ENGINE 0x1069EA80
	float Block1069EA60::Unknown1069EA80() const
	{
		return m4C;
	}

	// FUNCTION: ENGINE 0x1069EA90
	float Block1069EA60::Unknown1069EA90() const
	{
		return m50;
	}

	// FUNCTION: ENGINE 0x1069EAA0
	float Block1069EA60::Unknown1069EAA0() const
	{
		return m54;
	}

	// FUNCTION: ENGINE 0x1069EAB0
	float Block1069EA60::Unknown1069EAB0() const
	{
		return m58;
	}

	// FUNCTION: ENGINE 0x1069EAE0
	void Block1069EA60::Unknown1069EAE0(float value)
	{
		m48 = value;
	}

	// FUNCTION: ENGINE 0x1069EAF0
	float Block1069EA60::Unknown1069EAF0() const
	{
		return m48;
	}

	// FUNCTION: ENGINE 0x1069EB00
	float Block1069EA60::Unknown1069EB00() const
	{
		return m60;
	}

	// FUNCTION: ENGINE 0x1069EB10
	float Block1069EA60::Unknown1069EB10() const
	{
		return m68;
	}

	// FUNCTION: ENGINE 0x1069F4A0
	unsigned char* Block1069F4A0::Unknown1069F4A0()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x1069F4B0
	float Block1069F4A0::Unknown1069F4B0() const
	{
		return m30;
	}

	// FUNCTION: ENGINE 0x1069F4C0
	float Block1069F4A0::Unknown1069F4C0() const
	{
		return m34;
	}

	// FUNCTION: ENGINE 0x1069F7A0
	unsigned char* Block1069F7A0::Unknown1069F7A0()
	{
		return &m24;
	}

	// FUNCTION: ENGINE 0x1069F7B0
	unsigned char* Block1069F7A0::Unknown1069F7B0()
	{
		return &m30;
	}

	// FUNCTION: ENGINE 0x1069F7C0
	float Block1069F7A0::Unknown1069F7C0() const
	{
		return m3C;
	}

	// FUNCTION: ENGINE 0x1069F7D0
	float Block1069F7A0::Unknown1069F7D0() const
	{
		return m40;
	}

	// FUNCTION: ENGINE 0x1069FD00
	float Block1069FD00::Unknown1069FD00() const
	{
		return m24;
	}

	// FUNCTION: ENGINE 0x1069FD10
	unsigned char* Block1069FD00::Unknown1069FD10()
	{
		return &m44;
	}

	// FUNCTION: ENGINE 0x1069FFE0
	unsigned char* Block1069FFE0::Unknown1069FFE0()
	{
		return &m48;
	}

	// FUNCTION: ENGINE 0x1069FFF0
	unsigned char* Block1069FFE0::Unknown1069FFF0()
	{
		return &m54;
	}

}
