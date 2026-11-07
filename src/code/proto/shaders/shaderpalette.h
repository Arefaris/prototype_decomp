// proto::ShaderPalette (RTTI 0x1107119C, vftable 0x10DE50EC, bases content::MetaLoadObject / LoadObject /
// core::IRefCount): the palette of shaders a vehicle is painted from, read from the game's content files. It holds two
// element arrays over operator new[] (the RTTI names their element types proto::ShaderPaletteEntryTemplate and
// proto::ShaderPaletteData). File name, member names and the layout beyond the arrays are guesses.
#ifndef PROTO_SHADERS_SHADERPALETTE_H
#define PROTO_SHADERS_SHADERPALETTE_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/colourmetatype.h"
#include "code/content/loadinventory.h"
#include "code/core/name.h"
#include "code/core/strings.h"
#include "code/math/colour128.h"
#include "code/proto/arraypad.h"

namespace pure3d
{
	class pddiShaderInputInitData;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}

	namespace render
	{
		class Drawable;
	}
}

namespace core
{
	// 0x1063B7E0: gives a string of StrDup back (name guess)
	void StrFree(char* text);
}

namespace proto
{
	// The kinds of shader input an entry of the palette names (reflected as proto::ShaderPaletteEntryType; the values are
	// the engine's table)
	enum ShaderPaletteEntryType
	{
		EntryType_Unknown = 0,
		EntryType_Bool = 1,
		EntryType_Float1 = 1,
		EntryType_Float4 = 1,
		EntryType_Colour = 2
	};

	// A 32-bit name and the text it was made from (0xC bytes; the text is freed when the name owns it). Name guessed: no
	// RTTI names the class. The engine's copies sit in the first units of the image (0x1007EEC0 and the following).
	struct TextName
	{
		// 0x1007EEC0: the empty name and the engine's empty text
		__declspec(noinline) TextName()
		{
			text = "";
			ownsText = false;
		}
		// 0x10080F40: copies the name and the text (a text the other owns is copied)
		__declspec(noinline) TextName(const TextName& other)
			: name(*(const core::CaseInsensitiveKey32*)&other.name)
		{
			text = "";
			ownsText = false;
			if (other.ownsText)
			{
				SetText(other.text);
			}
			else
			{
				text = other.text;
				ownsText = false;
			}
		}
		// 0x1007EEE0: frees the text it owns
		__declspec(noinline) ~TextName()
		{
			if (ownsText)
			{
				core::StrFree((char*)text);
			}
		}
		// 0x10080700: the same for an existing name
		__declspec(noinline) TextName& operator=(const TextName& other)
		{
			name.hash = other.name.hash;
			if (other.ownsText)
			{
				SetText(other.text);
			}
			else
			{
				if (ownsText)
				{
					core::StrFree((char*)text);
				}
				text = other.text;
				ownsText = false;
			}
			return *this;
		}
		// 0x1007F390: keeps a copy of the text
		__declspec(noinline) void SetText(const char* newText)
		{
			if (newText != text)
			{
				if (ownsText)
				{
					core::StrFree((char*)text);
				}
				if (newText != 0 && *newText != 0)
				{
					text = core::StrDup(newText);
					ownsText = text != core::GetDefaultString();
				}
				else
				{
					ownsText = false;
					text = "";
				}
			}
		}

		core::Name<core::CaseInsensitiveKey32> name;  // +0
		const char* text;  // +4
		bool ownsText;  // +8
	};

	// One entry of the palette (0x10 bytes, RTTI proto::ShaderPaletteEntryTemplate): the name of a shader input and the
	// kind of value it takes
	struct ShaderPaletteEntryTemplate : public TextName
	{
		// 0x102E6260
		ShaderPaletteEntryTemplate()
		{
			type = EntryType_Unknown;
		}
		~ShaderPaletteEntryTemplate()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		ShaderPaletteEntryType type;  // +0xC
	};

}

namespace container
{
	// The engine's arrays of these elements erase with a call of AssignRange
	template<> struct ArrayEraseInline<proto::ShaderPaletteEntryTemplate>
	{
		enum
		{
			value = 0
		};
	};
}

namespace proto
{
	// A value patched into a shader input (RTTI proto::ShaderInputPatch, 0x10 bytes; its vftable is 0x10D97CE0, slot 0 the
	// deleting destructor at 0x1007F670): the name of the input and what the patch does with it (slots 1 and 2, names
	// guessed)
	struct ShaderInputPatch
	{
		// Slot 0 of the vftable 0x10D97CE0 is the deleting destructor 0x1007F670
		virtual ~ShaderInputPatch()
		{
		}
		// Adds the shader input to the description of the shader
		virtual void AddShaderInput(pure3d::pddiShaderInputInitData* data) = 0;
		// Sets the input on a drawable's bindings
		virtual void AddBinding(engine::render::Drawable drawable) = 0;

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		TextName name;  // +4
	};

	// The patch of a boolean input (RTTI proto::ShaderInputPatchBool, 0x14 bytes)
	struct ShaderInputPatchBool : public ShaderInputPatch
	{
		virtual ~ShaderInputPatchBool();
		virtual void AddShaderInput(pure3d::pddiShaderInputInitData* data);
		virtual void AddBinding(engine::render::Drawable drawable);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		bool value;  // +0x10
	};

	// The patch of a single float input (RTTI proto::ShaderInputPatchFloat1, 0x14 bytes)
	struct ShaderInputPatchFloat1 : public ShaderInputPatch
	{
		virtual ~ShaderInputPatchFloat1();
		virtual void AddShaderInput(pure3d::pddiShaderInputInitData* data);
		virtual void AddBinding(engine::render::Drawable drawable);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float value;  // +0x10
	};

	// The patch of a four float input (RTTI proto::ShaderInputPatchFloat4, 0x20 bytes, vftable 0x10D97CF4)
	struct ShaderInputPatchFloat4 : public ShaderInputPatch
	{
		ShaderInputPatchFloat4()
		{
			value.r = engine::driving::gOne;
			value.g = engine::driving::gOne;
			value.b = engine::driving::gOne;
			value.a = engine::driving::gOne;
		}
		virtual ~ShaderInputPatchFloat4()
		{
		}
		virtual void AddShaderInput(pure3d::pddiShaderInputInitData* data);
		virtual void AddBinding(engine::render::Drawable drawable);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		math::Colour128 value;  // +0x10
	};

}

namespace container
{
	template<> struct ArrayEraseInline<proto::ShaderInputPatchFloat4>
	{
		enum
		{
			value = 0
		};
	};
}

namespace proto
{
	// One shader's data (0x20 bytes, RTTI proto::ShaderPaletteData): the colours it patches and the other patches (by
	// pointer, owned)
	struct ShaderPaletteData
	{
		typedef container::ArrayDynamic<ShaderInputPatchFloat4, container::AllocatorNew> ColourArray;
		typedef container::ArrayDynamic<ShaderInputPatch*, container::AllocatorNew> PatchArray;

		// 0x102E7410: empty arrays (the words behind them stay)
		ShaderPaletteData()
		{
		}
		// 0x102E7D50: the copy of the arrays (the words behind them stay)
		ShaderPaletteData(const ShaderPaletteData& other);
		// 0x102A2950: frees the arrays
		~ShaderPaletteData();
		// 0x102E5CB0: adds the shader inputs of the entry's objects to the description (name guess)
		void FillShaderInputs(pure3d::pddiShaderInputInitData* data);
		// 0x102E5D30: the same on a drawable's bindings (name guess)
		void AddBindings(engine::render::Drawable drawable);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		ColourArray colours;  // +0
		ElementArrayPad unknownC;
		PatchArray patches;  // +0x10
		ElementArrayPad unknown1C;
	};

}

namespace container
{
	template<> struct ArrayEraseInline<proto::ShaderPaletteData>
	{
		enum
		{
			value = 0
		};
	};
}

namespace proto
{
	class ShaderPalette : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<ShaderPaletteEntryTemplate, container::AllocatorNew> EntryArray;
		typedef container::ArrayDynamic<ShaderPaletteData, container::AllocatorNew> DataArray;

		// 0x102A60B0. The destructor is the first function of the class that is not inline: it carries the vftable.
		virtual ~ShaderPalette();
		// 0x102E5780 (the thunk 0x1002AB6C is what the vftable holds)
		virtual bool Slot5();

		// 0x102E8340: adds a data set with a patch of all zeros for every colour entry (name guess)
		void AddBlankData();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		EntryArray entries;   // +0x08
		int unknown14;
		DataArray data;               // +0x18
	};
}

#endif
