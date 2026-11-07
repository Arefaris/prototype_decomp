// The reflection of the shader palette and its element classes (unit 0x102E5580 - 0x102E86C0; no assert path names it,
// the file name is a guess): proto::ShaderInputPatch with its Bool / Float1 / Float4 forms, proto::ShaderPaletteEntryTemplate,
// proto::ShaderPaletteData and proto::ShaderPalette, the helpers of their arrays and the function that builds the
// palette's data from its entries.
#include "code/proto/shaders/shaderpalette.h"
#include "code/proto/shaders/shaderpalettearrays.h"

// The engine's copies of every member of the four arrays (explicit instantiations: most of them have no caller)
template class container::ArrayDynamic<proto::ShaderPaletteEntryTemplate, container::AllocatorNew>;
template class container::ArrayDynamic<proto::ShaderInputPatchFloat4, container::AllocatorNew>;
template class container::ArrayDynamic<proto::ShaderInputPatch*, container::AllocatorNew>;
template class container::ArrayDynamic<proto::ShaderPaletteData, container::AllocatorNew>;

namespace content
{
	template<> void EnumInfo<proto::ShaderPaletteEntryType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code);
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME32_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseInsensitiveKey32>*)&((type*)0)->member, (int)&((type*)0)->member)

	static const content::EnumValue sEntryTypeValues[] =
	{
		{ "EntryType_Unknown", 0 },
		{ "EntryType_Bool", 1 },
		{ "EntryType_Float1", 1 },
		{ "EntryType_Float4", 1 },
		{ "EntryType_Colour", 2 }
	};
}

namespace content
{
	// FUNCTION: ENGINE 0x102E5580
	template<> void EnumInfo<proto::ShaderPaletteEntryType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::ShaderPaletteEntryType";
		*code = "pn";
		*values = proto::sEntryTypeValues;
		*count = 5;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x102E55C0
	content::ClassInfo* ShaderInputPatch::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShaderInputPatch";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102E5600
	content::ClassInfo* ShaderInputPatchBool::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShaderInputPatchBool";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102E5640
	content::ClassInfo* ShaderInputPatchFloat1::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShaderInputPatchFloat1";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102E5680
	content::ClassInfo* ShaderInputPatchFloat4::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShaderInputPatchFloat4";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102E56C0
	content::ClassInfo* ShaderPaletteData::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShaderPaletteData";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102E5700
	content::ClassInfo* ShaderPaletteEntryTemplate::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShaderPaletteEntryTemplate";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102E5740
	content::ClassInfo* ShaderPalette::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShaderPalette";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102E5A80
	content::MemberList* ShaderInputPatch::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<ShaderInputPatch>(false, false, "p"),
				PROTO_NAME32_OFFSET(ShaderInputPatch, name.name), "name" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102E5B20
	content::MemberList* ShaderPaletteEntryTemplate::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<ShaderPaletteEntryType>(), 0xc, "type" },
			{ content::GetMemberNameMetaType<ShaderPaletteEntryTemplate, 0>(false, false, "p"),
				PROTO_NAME32_OFFSET(ShaderPaletteEntryTemplate, name), "name" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102E67E0
	content::MemberList* ShaderInputPatchBool::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ShaderInputPatch>();
		static content::BaseClassCasterImpl<ShaderInputPatch, ShaderInputPatchBool> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ShaderInputPatchBool, bool, 0>("p"),
				PROTO_OFFSET(ShaderInputPatchBool, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102E68B0
	content::MemberList* ShaderInputPatchFloat1::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ShaderInputPatch>();
		static content::BaseClassCasterImpl<ShaderInputPatch, ShaderInputPatchFloat1> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ShaderInputPatchFloat1, float, 0>("p"),
				PROTO_OFFSET(ShaderInputPatchFloat1, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102E6980
	content::MemberList* ShaderInputPatchFloat4::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ShaderInputPatch>();
		static content::BaseClassCasterImpl<ShaderInputPatch, ShaderInputPatchFloat4> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberColourMetaType<ShaderInputPatchFloat4, 0>("p"),
				PROTO_OFFSET(ShaderInputPatchFloat4, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102E7030
	content::MemberList* ShaderPaletteData::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<ShaderPaletteData, ColourArray>(
				content::GetClassMetaType<ShaderInputPatchFloat4>(), "p"),
				PROTO_OFFSET(ShaderPaletteData, colours), "entries" },
			{ content::GetArrayDynamicMetaType<ShaderPaletteData, PatchArray>(
				content::GetObjectMetaType<ShaderInputPatch>("p"), "p"),
				PROTO_OFFSET(ShaderPaletteData, patches), "patchEntries" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102E7430
	content::MemberList* ShaderPalette::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<ShaderPalette, EntryArray>(
				content::GetClassMetaType<ShaderPaletteEntryTemplate>(), "p"),
				PROTO_OFFSET(ShaderPalette, entries), "paletteTemplate" },
			{ content::GetArrayDynamicMetaType<ShaderPalette, DataArray>(
				content::GetClassMetaType<ShaderPaletteData>(), "p"),
				PROTO_OFFSET(ShaderPalette, data), "palette" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102E7D50
	ShaderPaletteData::ShaderPaletteData(const ShaderPaletteData& other)
		: colours(other.colours), patches(other.patches)
	{
	}

	// FUNCTION: ENGINE 0x102E5CB0
	void ShaderPaletteData::FillShaderInputs(pure3d::pddiShaderInputInitData* data)
	{
		int colourCount = colours.Size();
		for (int i = 0; i < colourCount; i++)
		{
			colours[i].AddShaderInput(data);
		}
		int patchCount = patches.Size();
		for (int i = 0; i < patchCount; i++)
		{
			patches[i]->AddShaderInput(data);
		}
	}

	// FUNCTION: ENGINE 0x102E5D30
	void ShaderPaletteData::AddBindings(engine::render::Drawable* drawable)
	{
		int colourCount = colours.Size();
		for (int i = 0; i < colourCount; i++)
		{
			colours[i].AddBinding(drawable);
		}
		int patchCount = patches.Size();
		for (int i = 0; i < patchCount; i++)
		{
			patches[i]->AddBinding(drawable);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102E5790
// FUNCTION: ENGINE 0x102E57A0
// FUNCTION: ENGINE 0x102E57C0
// FUNCTION: ENGINE 0x102E57D0
// FUNCTION: ENGINE 0x102E5850
// FUNCTION: ENGINE 0x102E58C0
// FUNCTION: ENGINE 0x102E58D0
// FUNCTION: ENGINE 0x102E5910
// FUNCTION: ENGINE 0x102E5920
// FUNCTION: ENGINE 0x102E5960
// FUNCTION: ENGINE 0x102E5970
// FUNCTION: ENGINE 0x102E5990
// FUNCTION: ENGINE 0x102E59D0
// FUNCTION: ENGINE 0x102E59E0
// FUNCTION: ENGINE 0x102E59F0
// FUNCTION: ENGINE 0x102E5A00
// FUNCTION: ENGINE 0x102E5A10
// FUNCTION: ENGINE 0x102E5A20
// FUNCTION: ENGINE 0x102E5A30
// FUNCTION: ENGINE 0x102E5A40
// FUNCTION: ENGINE 0x102E5A50
// FUNCTION: ENGINE 0x102E5A60
// FUNCTION: ENGINE 0x102E5BF0
// FUNCTION: ENGINE 0x102E5C00
// FUNCTION: ENGINE 0x102E5C30
// FUNCTION: ENGINE 0x102E5C40
// FUNCTION: ENGINE 0x102E5C70
// FUNCTION: ENGINE 0x102E5C80
// FUNCTION: ENGINE 0x102E5DB0
// FUNCTION: ENGINE 0x102E5DC0
// FUNCTION: ENGINE 0x102E5E20
// FUNCTION: ENGINE 0x102E5E30
// FUNCTION: ENGINE 0x102E5E90
// FUNCTION: ENGINE 0x102E5EF0
// FUNCTION: ENGINE 0x102E5F30
// FUNCTION: ENGINE 0x102E5F70
// FUNCTION: ENGINE 0x102E5F80
// FUNCTION: ENGINE 0x102E5FA0
// FUNCTION: ENGINE 0x102E5FC0
// FUNCTION: ENGINE 0x102E5FD0
// FUNCTION: ENGINE 0x102E5FE0
// FUNCTION: ENGINE 0x102E6000
// FUNCTION: ENGINE 0x102E6010
// FUNCTION: ENGINE 0x102E6030
// FUNCTION: ENGINE 0x102E6050
// FUNCTION: ENGINE 0x102E60B0
// FUNCTION: ENGINE 0x102E60C0
// FUNCTION: ENGINE 0x102E60D0
// FUNCTION: ENGINE 0x102E60E0
// FUNCTION: ENGINE 0x102E6120
// FUNCTION: ENGINE 0x102E6150
// FUNCTION: ENGINE 0x102E6180
// FUNCTION: ENGINE 0x102E6190
// FUNCTION: ENGINE 0x102E61B0
// FUNCTION: ENGINE 0x102E61D0
// FUNCTION: ENGINE 0x102E6230
// FUNCTION: ENGINE 0x102E6250
// FUNCTION: ENGINE 0x102E6260
// FUNCTION: ENGINE 0x102E6280
// FUNCTION: ENGINE 0x102E6290
// FUNCTION: ENGINE 0x102E62B0
// FUNCTION: ENGINE 0x102E62D0
// FUNCTION: ENGINE 0x102E62F0
// FUNCTION: ENGINE 0x102E6360
// FUNCTION: ENGINE 0x102E6370
// FUNCTION: ENGINE 0x102E63B0
// FUNCTION: ENGINE 0x102E63D0
// FUNCTION: ENGINE 0x102E63F0
// FUNCTION: ENGINE 0x102E6410
// FUNCTION: ENGINE 0x102E6430
// FUNCTION: ENGINE 0x102E6450
// FUNCTION: ENGINE 0x102E6470
// FUNCTION: ENGINE 0x102E6490
// FUNCTION: ENGINE 0x102E6580
// FUNCTION: ENGINE 0x102E65E0
// FUNCTION: ENGINE 0x102E6620
// FUNCTION: ENGINE 0x102E6660
// FUNCTION: ENGINE 0x102E6690
// FUNCTION: ENGINE 0x102E66C0
// FUNCTION: ENGINE 0x102E6A50
// FUNCTION: ENGINE 0x102E6AB0
// FUNCTION: ENGINE 0x102E6B10
// FUNCTION: ENGINE 0x102E6B70
// FUNCTION: ENGINE 0x102E6BD0
// FUNCTION: ENGINE 0x102E6CD0
// FUNCTION: ENGINE 0x102E6D20
// FUNCTION: ENGINE 0x102E6EB0
// FUNCTION: ENGINE 0x102E6F10
// FUNCTION: ENGINE 0x102E6F40
// FUNCTION: ENGINE 0x102E6F90
// FUNCTION: ENGINE 0x102E6FE0
// FUNCTION: ENGINE 0x102E7120
// FUNCTION: ENGINE 0x102E71D0
// FUNCTION: ENGINE 0x102E7300
// FUNCTION: ENGINE 0x102E7340
// FUNCTION: ENGINE 0x102E73A0
// FUNCTION: ENGINE 0x102E7410
// FUNCTION: ENGINE 0x102E7510
// FUNCTION: ENGINE 0x102E7590
// FUNCTION: ENGINE 0x102E75D0
// FUNCTION: ENGINE 0x102E7740
// FUNCTION: ENGINE 0x102E7780
// FUNCTION: ENGINE 0x102E77D0
// FUNCTION: ENGINE 0x102E7870
// FUNCTION: ENGINE 0x102E7900
// FUNCTION: ENGINE 0x102E7980
// FUNCTION: ENGINE 0x102E7A10
// FUNCTION: ENGINE 0x102E7AA0
// FUNCTION: ENGINE 0x102E7AE0
// FUNCTION: ENGINE 0x102E7B30
// FUNCTION: ENGINE 0x102E7BE0
// FUNCTION: ENGINE 0x102E7D80
// FUNCTION: ENGINE 0x102E7E80
// FUNCTION: ENGINE 0x102E7EB0
// FUNCTION: ENGINE 0x102E7F40
// FUNCTION: ENGINE 0x102E8020
// FUNCTION: ENGINE 0x102E8260
// FUNCTION: ENGINE 0x102E82B0
// FUNCTION: ENGINE 0x102E82F0
// FUNCTION: ENGINE 0x102E8580
// FUNCTION: ENGINE 0x102E8600
