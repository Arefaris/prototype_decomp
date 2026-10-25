// The reflection of the typed attributes (unit 0x1086C900 - 0x1086DEC0, no assert path: the file name is a guess):
// engine::BaseAttribute and, for the value types int, float, bool, math::Vector, math::Matrix, core::Name,
// pure3d::Pose* and GenericScriptValue, the pair engine::ConstAttribute<T> (the base that holds the value, reflected
// as "Const...Attribute" with the member "value") and engine::Attribute<T> (reflected as "...Attribute"). The class
// names are original.
#include "code/content/loadinventory.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/genericscriptvalue.h"
#include "code/pure3d/pose.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1086C900
	content::ClassInfo* BaseAttribute::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::BaseAttribute";
		sInfo.code = "";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086C940
	content::MemberList* BaseAttribute::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086C970
	template<> content::ClassInfo* Attribute<math::Vector>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "VectorAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086C9B0
	template<> content::ClassInfo* ConstAttribute<math::Vector>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstVectorAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086C9F0
	template<> content::ClassInfo* Attribute<math::Matrix>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "MatrixAttribute";
		sInfo.code = "pnm";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CA30
	template<> content::ClassInfo* ConstAttribute<math::Matrix>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstPlainMatrixAttribute";
		sInfo.code = "pnm";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CA90
	content::ClassInfo* Attribute<core::Name<core::CaseSensitiveKey> >::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "NameAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CAD0
	content::ClassInfo* ConstAttribute<core::Name<core::CaseSensitiveKey> >::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstNameAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CB30
	template<> content::ClassInfo* Attribute<int>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "IntAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CB70
	template<> content::ClassInfo* ConstAttribute<int>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstIntAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CBD0
	template<> content::ClassInfo* Attribute<float>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "FloatAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CC10
	template<> content::ClassInfo* ConstAttribute<float>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstFloatAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CC70
	template<> content::ClassInfo* Attribute<bool>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "BoolAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CCB0
	template<> content::ClassInfo* ConstAttribute<bool>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstBoolAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CD10
	template<> content::ClassInfo* Attribute<pure3d::Pose*>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PoseAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CD50
	template<> content::ClassInfo* ConstAttribute<pure3d::Pose*>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::ConstPoseAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CDB0
	template<> content::ClassInfo* Attribute<GenericScriptValue>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "GenericScriptAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086CDF0
	template<> content::ClassInfo* ConstAttribute<GenericScriptValue>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ConstGenericScriptAttribute";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1086D290
	template<> content::MemberList* ConstAttribute<math::Matrix>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<BaseAttribute>();
		static content::BaseClassCasterImpl<BaseAttribute, ConstAttribute<math::Matrix> > sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMatrixMetaType<ConstAttribute<math::Matrix> >(false, false, "pnm"),
				ENGINE_OFFSET(ConstAttribute<math::Matrix>, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086D340
	content::MemberList* ConstAttribute<core::Name<core::CaseSensitiveKey> >::GetMembers()
	{
		typedef ConstAttribute<core::Name<core::CaseSensitiveKey> > Self;
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<BaseAttribute>();
		static content::BaseClassCasterImpl<BaseAttribute, Self> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<Self>(true, true, "p"), ENGINE_OFFSET(Self, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086D3F0
	template<> content::MemberList* ConstAttribute<GenericScriptValue>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<BaseAttribute>();
		static content::BaseClassCasterImpl<BaseAttribute, ConstAttribute<GenericScriptValue> > sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<GenericScriptValue>(), ENGINE_OFFSET(ConstAttribute<GenericScriptValue>, value),
				"value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086D670
	template<> content::MemberList* ConstAttribute<math::Vector>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<BaseAttribute>();
		static content::BaseClassCasterImpl<BaseAttribute, ConstAttribute<math::Vector> > sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ConstAttribute<math::Vector>, 0>("p"), 4, "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086D720
	template<> content::MemberList* Attribute<math::Matrix>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ConstAttribute<math::Matrix> >();
		static content::BaseClassCasterImpl<ConstAttribute<math::Matrix>, Attribute<math::Matrix> > sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086D780
	content::MemberList* Attribute<core::Name<core::CaseSensitiveKey> >::GetMembers()
	{
		typedef ConstAttribute<core::Name<core::CaseSensitiveKey> > Base;
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Base>();
		static content::BaseClassCasterImpl<Base, Attribute<core::Name<core::CaseSensitiveKey> > > sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086D7E0
	template<> content::MemberList* ConstAttribute<int>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<BaseAttribute>();
		static content::BaseClassCasterImpl<BaseAttribute, ConstAttribute<int> > sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ConstAttribute<int>, int, 0>("p"),
				ENGINE_OFFSET(ConstAttribute<int>, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086D890
	template<> content::MemberList* ConstAttribute<float>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<BaseAttribute>();
		static content::BaseClassCasterImpl<BaseAttribute, ConstAttribute<float> > sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ConstAttribute<float>, float, 0>("p"),
				ENGINE_OFFSET(ConstAttribute<float>, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086D940
	template<> content::MemberList* ConstAttribute<bool>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<BaseAttribute>();
		static content::BaseClassCasterImpl<BaseAttribute, ConstAttribute<bool> > sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ConstAttribute<bool>, bool, 0>("p"),
				ENGINE_OFFSET(ConstAttribute<bool>, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086D9F0
	template<> content::MemberList* Attribute<GenericScriptValue>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ConstAttribute<GenericScriptValue> >();
		static content::BaseClassCasterImpl<ConstAttribute<GenericScriptValue>, Attribute<GenericScriptValue> > sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086DBE0
	template<> content::MemberList* Attribute<math::Vector>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ConstAttribute<math::Vector> >();
		static content::BaseClassCasterImpl<ConstAttribute<math::Vector>, Attribute<math::Vector> > sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086DC40
	template<> content::MemberList* Attribute<int>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ConstAttribute<int> >();
		static content::BaseClassCasterImpl<ConstAttribute<int>, Attribute<int> > sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086DCA0
	template<> content::MemberList* Attribute<float>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ConstAttribute<float> >();
		static content::BaseClassCasterImpl<ConstAttribute<float>, Attribute<float> > sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086DD00
	template<> content::MemberList* Attribute<bool>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ConstAttribute<bool> >();
		static content::BaseClassCasterImpl<ConstAttribute<bool>, Attribute<bool> > sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086DD60
	template<> content::MemberList* ConstAttribute<pure3d::Pose*>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<BaseAttribute>();
		static content::BaseClassCasterImpl<BaseAttribute, ConstAttribute<pure3d::Pose*> > sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<ConstAttribute<pure3d::Pose*>, pure3d::Pose>("p"),
				ENGINE_OFFSET(ConstAttribute<pure3d::Pose*>, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1086DE60
	template<> content::MemberList* Attribute<pure3d::Pose*>::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ConstAttribute<pure3d::Pose*> >();
		static content::BaseClassCasterImpl<ConstAttribute<pure3d::Pose*>, Attribute<pure3d::Pose*> > sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1086CE50
// FUNCTION: ENGINE 0x1086CE80
// FUNCTION: ENGINE 0x1086CEB0
// FUNCTION: ENGINE 0x1086CEE0
// FUNCTION: ENGINE 0x1086CF10
// FUNCTION: ENGINE 0x1086CF40
// FUNCTION: ENGINE 0x1086CF70
// FUNCTION: ENGINE 0x1086CFA0
// FUNCTION: ENGINE 0x1086CFD0
// FUNCTION: ENGINE 0x1086D000
// FUNCTION: ENGINE 0x1086D030
// FUNCTION: ENGINE 0x1086D060
// FUNCTION: ENGINE 0x1086D090
// FUNCTION: ENGINE 0x1086D0C0
// FUNCTION: ENGINE 0x1086D0F0
// FUNCTION: ENGINE 0x1086D140
// FUNCTION: ENGINE 0x1086D170
// FUNCTION: ENGINE 0x1086D1B0
// FUNCTION: ENGINE 0x1086D1F0
// FUNCTION: ENGINE 0x1086D200
// FUNCTION: ENGINE 0x1086D220
// FUNCTION: ENGINE 0x1086D260
// FUNCTION: ENGINE 0x1086D490
// FUNCTION: ENGINE 0x1086D4E0
// FUNCTION: ENGINE 0x1086D530
// FUNCTION: ENGINE 0x1086D580
// FUNCTION: ENGINE 0x1086D5C0
// FUNCTION: ENGINE 0x1086D600
// FUNCTION: ENGINE 0x1086D650
// FUNCTION: ENGINE 0x1086DA50
// FUNCTION: ENGINE 0x1086DAA0
// FUNCTION: ENGINE 0x1086DAF0
// FUNCTION: ENGINE 0x1086DB40
// FUNCTION: ENGINE 0x1086DB90
// FUNCTION: ENGINE 0x1086DE10

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1086CA70
// FUNCTION: ENGINE 0x1086CA80
// FUNCTION: ENGINE 0x1086CB10
// FUNCTION: ENGINE 0x1086CB20
// FUNCTION: ENGINE 0x1086CBB0
// FUNCTION: ENGINE 0x1086CBC0
// FUNCTION: ENGINE 0x1086CC50
// FUNCTION: ENGINE 0x1086CC60
// FUNCTION: ENGINE 0x1086CCF0
// FUNCTION: ENGINE 0x1086CD00
// FUNCTION: ENGINE 0x1086CD90
// FUNCTION: ENGINE 0x1086CDA0
// FUNCTION: ENGINE 0x1086CE30
// FUNCTION: ENGINE 0x1086CE40
// FUNCTION: ENGINE 0x1086D210
// FUNCTION: ENGINE 0x1086D250
// FUNCTION: ENGINE 0x1086D640
