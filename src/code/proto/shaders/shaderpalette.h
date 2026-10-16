// proto::ShaderPalette (RTTI 0x1107119C, vftable 0x10DE50EC, bases content::MetaLoadObject / LoadObject /
// core::IRefCount): the palette of shaders a vehicle is painted from, read from the game's content files. It holds two
// element arrays over operator new[] (the RTTI names their element types proto::ShaderPaletteEntryTemplate and
// proto::ShaderPaletteData). File name, member names and the layout beyond the arrays are guesses.
#ifndef PROTO_SHADERS_SHADERPALETTE_H
#define PROTO_SHADERS_SHADERPALETTE_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"

namespace proto
{
	// One entry of the palette (0x10 bytes): the text it holds is freed with the entry when the entry owns it
	// (0x1007EEE0 is the destructor)
	struct ShaderPaletteEntryTemplate
	{
		~ShaderPaletteEntryTemplate();

		int unknown0;
		char* text;
		bool ownsText;
		unsigned char unknown9[7];
	};

	// One shader's data (0x20 bytes: two arrays, of 0x20-byte objects and of pointers to owned objects; 0x102A2950 is
	// the destructor that frees them)
	struct ShaderPaletteData
	{
		~ShaderPaletteData();

		unsigned char unknown0[0x20];
	};

	class ShaderPalette : public content::MetaLoadObject
	{
	public:
		// 0x102A60B0. The destructor is the first function of the class that is not inline: it carries the vftable.
		virtual ~ShaderPalette();
		// 0x102E5780 (the thunk 0x1002AB6C is what the vftable holds)
		virtual bool Slot5();

		container::ArrayDynamic<ShaderPaletteEntryTemplate, container::AllocatorNew> entries;   // +0x08
		int unknown14;
		container::ArrayDynamic<ShaderPaletteData, container::AllocatorNew> data;               // +0x18
	};
}

#endif
