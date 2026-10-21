#include "code/engine/trackedmotiontoexpressionmap.h"
#include "code/core/refptr.h"
#include <float.h>
#include <new>

namespace content
{
	static const EnumValue sBlendTypeValues[] =
	{
		{ "Add", 0 },
		{ "Min", 1 },
		{ "Max", 2 },
		{ "Override", 3 }
	};

	// FUNCTION: ENGINE 0x109118C0
	template<> void EnumInfo<engine::TrackedMotionToExpressionMap::PropertyMapping::BlendType>::Get(const char** name,
		const EnumValue** values, int* count, const char** code)
	{
		*name = "engine::TrackedMotionToExpressionMap::PropertyMapping::BlendType";
		*code = "pn";
		*values = sBlendTypeValues;
		*count = 4;
	}
}

namespace engine
{
	typedef TrackedMotionToExpressionMap Map;

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10911880
	content::ClassInfo* Map::PropertyMappingKeyValuePair::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::TrackedMotionToExpressionMap::PropertyMappingKeyValuePair";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109118F0
	content::ClassInfo* Map::PropertyMapping::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::TrackedMotionToExpressionMap::PropertyMapping";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10911930
	content::ClassInfo* Map::JointData::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::TrackedMotionToExpressionMap::JointData";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10911970
	content::ClassInfo* Map::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::TrackedMotionToExpressionMap";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109119C0
	void Map::PropertyMapping::ResolveExpression(const pure3d::ExpressionGroup* group)
	{
		expressionIndex = group->FindExpression(expressionName);
	}

	// FUNCTION: ENGINE 0x109119E0
	const math::Vector* Map::JointData::GetOffset() const
	{
		math::Vector v(offset.transform.m[3][0], offset.transform.m[3][1], offset.transform.m[3][2]);
		math::Vector* result = &offsetTranslation;
		result->x = v.x;
		result->y = v.y;
		result->z = v.z;
		return result;
	}

	// FUNCTION: ENGINE 0x10911A10
	void Map::JointData::SetOffset(const math::Vector* value)
	{
		offset.transform.m[3][0] = value->x;
		offset.transform.m[3][1] = value->y;
		offset.transform.m[3][2] = value->z;
	}

	// FUNCTION: ENGINE 0x10911E30
	// NONMATCHING: the engine loads the lower bound into a register before the first test, ours compares it from
	// memory and enters the loop one test later, best 15.8 %
#ifdef NONMATCHING
	bool Map::PropertyMapping::IsCurveSorted() const
	{
		bool sorted = true;
		float previous = -FLT_MAX;
		PropertyMappingKeyValuePair* point = mappingCurve.begin;
		if (point != mappingCurve.end)
		{
			for (;;)
			{
				float key = point->key;
				if (!(previous < key))
				{
					sorted = false;
					break;
				}
				point++;
				previous = key;
				if (point == mappingCurve.end)
				{
					return sorted;
				}
			}
		}
		return sorted;
	}
#endif

	// FUNCTION: ENGINE 0x10911E60
	// NONMATCHING: the arithmetic is right; the engine keeps the previous key and the result in SSE registers through
	// the loop and computes the interpolation in SSE, ours spills them and interpolates on the x87 stack, best 2.1 %
#ifdef NONMATCHING
	float Map::PropertyMapping::EvaluateCurve(float x) const
	{
		PropertyMappingKeyValuePair* point = mappingCurve.begin;
		float previousKey = point->key;
		float result = point->value;
		if (previousKey < x)
		{
			PropertyMappingKeyValuePair* end = mappingCurve.end;
			PropertyMappingKeyValuePair* next = point + 1;
			if (next != end)
			{
				float key;
				while (key = next->key, key <= x)
				{
					result = next->value;
					next++;
					previousKey = key;
					if (next == end)
					{
						return result;
					}
				}
				x = ((next->value - result) * (x - previousKey)) / (next->key - previousKey) + result;
				if (next == end)
				{
					x = result;
				}
				return x;
			}
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x10911EE0
	void Map::JointData::Resolve(const pure3d::Skeleton* skeleton, const pure3d::ExpressionGroup* group)
	{
		core::Name<core::CaseSensitiveKey> none((const char*)0, 1);
		if (jointName != none)
		{
			offset.handle = skeleton->FindJoint(jointName);
		}
		else
		{
			offset.handle = 0xffff;
		}
		PropertyMapping* last = trackedProperties.end;
		for (PropertyMapping* property = trackedProperties.begin; property != last; property++)
		{
			property->ResolveExpression(group);
		}
	}

	// FUNCTION: ENGINE 0x10911F50
	void Map::ResolveAll()
	{
		if (skeleton != 0)
		{
			JointData* last = jointData.end;
			for (JointData* joint = jointData.begin; joint != last; joint++)
			{
				joint->Resolve(skeleton, expressionGroup);
			}
		}
	}

	// FUNCTION: ENGINE 0x10912A20
	content::MemberList* Map::PropertyMappingKeyValuePair::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<PropertyMappingKeyValuePair, float, 0>("pn"),
				ENGINE_OFFSET(PropertyMappingKeyValuePair, key), "key" },
			{ content::GetMemberPrimitiveMetaType<PropertyMappingKeyValuePair, float, 1>("pn"),
				ENGINE_OFFSET(PropertyMappingKeyValuePair, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10912AD0
	bool Map::Slot5()
	{
		ResolveAll();
		return true;
	}

	// FUNCTION: ENGINE 0x109131F0
	content::MemberList* Map::PropertyMapping::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetObjectMetaType<MotionFeatureExtractor>("pn"),
				ENGINE_OFFSET(PropertyMapping, featureExtractor), "featureExtractor" },
			{ content::GetNameMetaType<PropertyMapping>(true, true, "pn"),
				ENGINE_NAME_OFFSET(PropertyMapping, expressionName), "expressionName" },
			{ content::GetMemberPrimitiveMetaType<PropertyMapping, float, 0>("pn"),
				ENGINE_OFFSET(PropertyMapping, weight), "weight" },
			{ content::GetEnumMetaType<BlendType>(), 0x18, "blendType" },
			{ content::GetArrayDynamicMetaType<PropertyMapping, CurveArray>(
				content::GetClassMetaType<PropertyMappingKeyValuePair>(), "pn"),
				ENGINE_OFFSET(PropertyMapping, mappingCurve), "mappingCurve" },
			{ content::GetMemberPrimitiveMetaType<PropertyMapping, bool, 0>(""),
				ENGINE_OFFSET(PropertyMapping, debugDisable), "debugDisable" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// FUNCTION: ENGINE 0x109134C0
	content::MemberList* Map::JointData::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<JointData>(true, true, "pn"), ENGINE_NAME_OFFSET(JointData, jointName),
				"jointName" },
			{ content::GetMemberVectorMetaType<JointData, 0>(&JointData::GetOffset, &JointData::SetOffset, "pn"), 0,
				"offset" },
			{ content::GetObjectMetaType<MotionTrackingFilter>("pn"), ENGINE_OFFSET(JointData, motionFilter),
				"motionFilter" },
			{ content::GetArrayDynamicMetaType<JointData, PropertyArray>(
				content::GetClassMetaType<PropertyMapping>(), "pn"),
				ENGINE_OFFSET(JointData, trackedProperties), "trackedProperties" },
			{ content::GetMemberPrimitiveMetaType<JointData, bool, 0>(""), ENGINE_OFFSET(JointData, debugDisable),
				"debugDisable" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x109135F0
	Map::PropertyMapping::PropertyMapping() : featureExtractor(0), expressionIndex(-1), weight(1.0f),
		blendType(BLEND_ADD), debugDisable(false)
	{
	}

	// FUNCTION: ENGINE 0x10913630
	Map::PropertyMapping::~PropertyMapping()
	{
		delete featureExtractor;
	}

	// FUNCTION: ENGINE 0x109138D0
	content::MemberList* Map::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<Map, pure3d::Skeleton>("pn"), ENGINE_OFFSET(Map, skeleton), "skeleton" },
			{ content::GetReferenceMetaType<Map, pure3d::ExpressionGroup>("pn"), ENGINE_OFFSET(Map, expressionGroup),
				"expressionGroup" },
			{ content::GetArrayDynamicMetaType<Map, JointArray>(content::GetClassMetaType<JointData>(), "pn"),
				ENGINE_OFFSET(Map, jointData), "jointData" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10914180
	Map::JointData::JointData() : motionFilter(0), debugDisable(false)
	{
	}

	// FUNCTION: ENGINE 0x109141B0
	Map::JointData::~JointData()
	{
		delete motionFilter;
	}

	// FUNCTION: ENGINE 0x109146F0
	Map::TrackedMotionToExpressionMap() : skeleton(0), expressionGroup(0)
	{
	}

	// FUNCTION: ENGINE 0x10914720
	Map::~TrackedMotionToExpressionMap()
	{
		core::SafeRelease(skeleton);
		core::SafeRelease(expressionGroup);
	}
}

namespace container
{
	template class ArrayDynamic<engine::TrackedMotionToExpressionMap::PropertyMappingKeyValuePair, AllocatorNew>;
	template class ArrayDynamic<engine::TrackedMotionToExpressionMap::PropertyMapping, AllocatorNew>;
	template class ArrayDynamic<engine::TrackedMotionToExpressionMap::JointData, AllocatorNew>;
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x109119B0
// FUNCTION: ENGINE 0x10911A40
// FUNCTION: ENGINE 0x10911A50
// FUNCTION: ENGINE 0x10911A60
// FUNCTION: ENGINE 0x10911A70
// FUNCTION: ENGINE 0x10911A80
// FUNCTION: ENGINE 0x10911A90
// FUNCTION: ENGINE 0x10911AC0
// FUNCTION: ENGINE 0x10911AE0
// FUNCTION: ENGINE 0x10911B60
// FUNCTION: ENGINE 0x10911BC0
// FUNCTION: ENGINE 0x10911BD0
// FUNCTION: ENGINE 0x10911C30
// FUNCTION: ENGINE 0x10911C40
// FUNCTION: ENGINE 0x10911CC0
// FUNCTION: ENGINE 0x10911CD0
// FUNCTION: ENGINE 0x10911D20
// FUNCTION: ENGINE 0x10911D30
// FUNCTION: ENGINE 0x10911D70
// FUNCTION: ENGINE 0x10911D80
// FUNCTION: ENGINE 0x10911D90
// FUNCTION: ENGINE 0x10911DA0
// FUNCTION: ENGINE 0x10911DB0
// FUNCTION: ENGINE 0x10911DD0
// FUNCTION: ENGINE 0x109121C0
// FUNCTION: ENGINE 0x109121D0
// FUNCTION: ENGINE 0x109121E0
// FUNCTION: ENGINE 0x109121F0
// FUNCTION: ENGINE 0x10912230
// FUNCTION: ENGINE 0x10912270
// FUNCTION: ENGINE 0x109122B0
// FUNCTION: ENGINE 0x109122F0
// FUNCTION: ENGINE 0x10912340
// FUNCTION: ENGINE 0x10912350
// FUNCTION: ENGINE 0x10912370
// FUNCTION: ENGINE 0x10912380
// FUNCTION: ENGINE 0x109123D0
// FUNCTION: ENGINE 0x109123E0
// FUNCTION: ENGINE 0x109123F0
// FUNCTION: ENGINE 0x10912400
// FUNCTION: ENGINE 0x10912440
// FUNCTION: ENGINE 0x10912460
// FUNCTION: ENGINE 0x10912490
// FUNCTION: ENGINE 0x109124C0
// FUNCTION: ENGINE 0x109124D0
// FUNCTION: ENGINE 0x109124F0
// FUNCTION: ENGINE 0x10912500
// FUNCTION: ENGINE 0x10912550
// FUNCTION: ENGINE 0x10912570
// FUNCTION: ENGINE 0x10912590
// FUNCTION: ENGINE 0x109125A0
// FUNCTION: ENGINE 0x109125B0
// FUNCTION: ENGINE 0x109125E0
// FUNCTION: ENGINE 0x10912610
// FUNCTION: ENGINE 0x10912620
// FUNCTION: ENGINE 0x10912650
// FUNCTION: ENGINE 0x10912670
// FUNCTION: ENGINE 0x10912690
// FUNCTION: ENGINE 0x109126D0
// FUNCTION: ENGINE 0x109126E0
// FUNCTION: ENGINE 0x109126F0
// FUNCTION: ENGINE 0x10912700
// FUNCTION: ENGINE 0x10912710
// FUNCTION: ENGINE 0x10912730
// FUNCTION: ENGINE 0x10912740
// FUNCTION: ENGINE 0x10912760
// FUNCTION: ENGINE 0x10912780
// FUNCTION: ENGINE 0x109127A0
// FUNCTION: ENGINE 0x109127C0
// FUNCTION: ENGINE 0x109127E0
// FUNCTION: ENGINE 0x10912800
// FUNCTION: ENGINE 0x10912820
// FUNCTION: ENGINE 0x10912840
// FUNCTION: ENGINE 0x10912880
// FUNCTION: ENGINE 0x109128B0
// FUNCTION: ENGINE 0x109128E0
// FUNCTION: ENGINE 0x10912950
// FUNCTION: ENGINE 0x10912D70
// FUNCTION: ENGINE 0x10912DC0
// FUNCTION: ENGINE 0x10912DD0
// FUNCTION: ENGINE 0x10912E20
// FUNCTION: ENGINE 0x10912E70
// FUNCTION: ENGINE 0x10912EE0
// FUNCTION: ENGINE 0x10912F30
// FUNCTION: ENGINE 0x10912F80
// FUNCTION: ENGINE 0x10912FD0
// FUNCTION: ENGINE 0x10913020
// FUNCTION: ENGINE 0x109130B0
// FUNCTION: ENGINE 0x109131A0
// FUNCTION: ENGINE 0x10913340
// FUNCTION: ENGINE 0x10913360
// FUNCTION: ENGINE 0x109133B0
// FUNCTION: ENGINE 0x10913410
// FUNCTION: ENGINE 0x10913470
// FUNCTION: ENGINE 0x10913660
// FUNCTION: ENGINE 0x10913760
// FUNCTION: ENGINE 0x109137D0
// FUNCTION: ENGINE 0x109137F0
// FUNCTION: ENGINE 0x10913860
// FUNCTION: ENGINE 0x10913A80
// FUNCTION: ENGINE 0x10913AB0
// FUNCTION: ENGINE 0x10913AE0
// FUNCTION: ENGINE 0x10913B30
// FUNCTION: ENGINE 0x10913CF0
// FUNCTION: ENGINE 0x10913D20
// FUNCTION: ENGINE 0x10913EA0
// FUNCTION: ENGINE 0x10913F50
// FUNCTION: ENGINE 0x10913F90
// FUNCTION: ENGINE 0x10914300
// FUNCTION: ENGINE 0x10914360
// FUNCTION: ENGINE 0x10914390
// FUNCTION: ENGINE 0x109143C0
// FUNCTION: ENGINE 0x10914460
// FUNCTION: ENGINE 0x10914490
// FUNCTION: ENGINE 0x109144D0
// FUNCTION: ENGINE 0x109145D0
// FUNCTION: ENGINE 0x10914610
// FUNCTION: ENGINE 0x10914650
// FUNCTION: ENGINE 0x109146C0
// FUNCTION: ENGINE 0x10914780
