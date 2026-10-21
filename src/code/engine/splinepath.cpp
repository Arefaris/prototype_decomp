#include "code/engine/splinepath.h"
#include "code/math/vector4.h"
#include <new>

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// The engine's identity matrix copied element by element
	static inline void SetIdentity(math::Matrix& matrix)
	{
		matrix.m[0][0] = math::Matrix::IDENTITY.m[0][0];
		matrix.m[0][1] = math::Matrix::IDENTITY.m[0][1];
		matrix.m[0][2] = math::Matrix::IDENTITY.m[0][2];
		matrix.m[0][3] = math::Matrix::IDENTITY.m[0][3];
		matrix.m[1][0] = math::Matrix::IDENTITY.m[1][0];
		matrix.m[1][1] = math::Matrix::IDENTITY.m[1][1];
		matrix.m[1][2] = math::Matrix::IDENTITY.m[1][2];
		matrix.m[1][3] = math::Matrix::IDENTITY.m[1][3];
		matrix.m[2][0] = math::Matrix::IDENTITY.m[2][0];
		matrix.m[2][1] = math::Matrix::IDENTITY.m[2][1];
		matrix.m[2][2] = math::Matrix::IDENTITY.m[2][2];
		matrix.m[2][3] = math::Matrix::IDENTITY.m[2][3];
		matrix.m[3][0] = math::Matrix::IDENTITY.m[3][0];
		matrix.m[3][1] = math::Matrix::IDENTITY.m[3][1];
		matrix.m[3][2] = math::Matrix::IDENTITY.m[3][2];
		matrix.m[3][3] = math::Matrix::IDENTITY.m[3][3];
	}

	// FUNCTION: ENGINE 0x10910550
	content::ClassInfo* SplinePathCV::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SplinePathCV";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10910590
	content::ClassInfo* IPath::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::IPath";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109105D0
	content::MemberList* IPath::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10910600
	content::ClassInfo* SplinePath::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SplinePath";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10910640
	SplinePathCV::SplinePathCV()
	{
		key.time = 0.0f;
		key.position.x = 0.0f;
		key.position.y = 0.0f;
		key.position.z = 0.0f;
		tension = 0.0f;
		continuity = 0.0f;
		bias = 0.0f;
		forceSpeedMatch = false;
	}

	// FUNCTION: ENGINE 0x10910680
	SplinePathCV::~SplinePathCV()
	{
	}

	// FUNCTION: ENGINE 0x10910690
	bool SplinePath::Slot5()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x109106A0
	math::Spline* SplinePath::GetSpline() const
	{
		return spline;
	}

	// FUNCTION: ENGINE 0x109108A0
	void SplinePath::BuildSpline()
	{
		int count = points.Size();
		if (spline != 0)
		{
			delete spline;
		}
		spline = 0;
		spline = new math::Spline(count, 4, false);
		for (int i = 0; i < count; i++)
		{
			SplinePathCV* point = points[i];
			const math::Vector* position = &point->key.position;
			math::Vector4 key;
			key.x = position->x;
			key.y = position->y;
			key.z = position->z;
			key.w = 1.0f;
			key.w = points[i]->key.time;
			// The tangent record: the three Kochanek-Bartels parameters and the flag in the last word (the spline
			// stores it as a Vector4)
			struct
			{
				float tension;
				float continuity;
				float bias;
				bool adjust;
			} tangent;
			tangent.tension = points[i]->tension;
			tangent.continuity = points[i]->continuity;
			tangent.bias = points[i]->bias;
			tangent.adjust = points[i]->forceSpeedMatch;
			spline->SetKey(i, key);
			spline->SetTangent(i, *(const math::Vector4*)&tangent);
		}
	}

	// FUNCTION: ENGINE 0x10910D30
	content::MemberList* SplinePathCV::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<SplinePathCV, float, 0>("p"), ENGINE_OFFSET(SplinePathCV, key.time),
				"time" },
			{ content::GetMemberVectorMetaType<SplinePathCV, 0>("p"), 8, "position" },
			{ content::GetMemberPrimitiveMetaType<SplinePathCV, float, 1>("p"), ENGINE_OFFSET(SplinePathCV, tension),
				"tension" },
			{ content::GetMemberPrimitiveMetaType<SplinePathCV, float, 2>("p"),
				ENGINE_OFFSET(SplinePathCV, continuity), "continuity" },
			{ content::GetMemberPrimitiveMetaType<SplinePathCV, float, 3>("p"), ENGINE_OFFSET(SplinePathCV, bias),
				"bias" },
			{ content::GetMemberPrimitiveMetaType<SplinePathCV, bool, 0>("p"),
				ENGINE_OFFSET(SplinePathCV, forceSpeedMatch), "forceSpeedMatch" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10910E70
	void SplinePath::Slot3(int unused)
	{
		if (points.Size() > 0)
		{
			transform.SetTranslation(points[0]->key.position);
		}
		BuildSpline();
	}

	// FUNCTION: ENGINE 0x10910EB0
	// EQUIVALENT: same loads, additions (step + position) and stores; the engine keeps the old position in xmm1 - xmm3,
	// ours reloads x and adds from memory (66.8 %)
	void SplinePath::CreatePoints(int count, const math::Vector* step)
	{
		SplinePathCV::Key cursor;
		cursor.time = -1.0f;
		cursor.position.x = transform.m[3][0];
		cursor.position.y = transform.m[3][1];
		cursor.position.z = transform.m[3][2];
		PointArray* array = &points;
		if (array->Size() == 0)
		{
			array->Allocate(count);
			if (count > 0)
			{
				do
				{
					SplinePathCV* point = new SplinePathCV;
					float time = cursor.time;
					float x = cursor.position.x;
					float y = cursor.position.y;
					float z = cursor.position.z;
					point->key.time = time;
					cursor.time = time + 1.0f;
					point->key.position.x = x;
					point->key.position.y = y;
					point->key.position.z = z;
					cursor.position.x = step->x + x;
					cursor.position.y = step->y + y;
					cursor.position.z = step->z + z;
					if (array->end < array->capacity)
					{
						SplinePathCV** slot = array->end++;
						if (slot != 0)
						{
							*slot = point;
						}
					}
				}
				while (--count != 0);
			}
		}
		BuildSpline();
	}

	// FUNCTION: ENGINE 0x10911250
	content::MemberList* SplinePath::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<IPath>();
		static content::BaseClassCasterImpl<IPath, SplinePath> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<SplinePath, PointArray>(content::GetObjectMetaType<SplinePathCV>("pn"),
				"pn"), ENGINE_OFFSET(SplinePath, points), "points" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10911310
	SplinePath::SplinePath()
	{
		SetIdentity(transform);
		spline = 0;
		unknown5C = 0;
		unknown60 = false;
	}

	// FUNCTION: ENGINE 0x10911410
	// EQUIVALENT: the engine empties the array before it reads the spline pointer, ours reads the pointer first (89.7 %)
	SplinePath::~SplinePath()
	{
		for (SplinePathCV** point = points.begin; point != points.end; point++)
		{
			delete *point;
		}
		points.end = points.begin;
		if (spline != 0)
		{
			delete spline;
		}
	}
}

namespace content
{
	void ArrayDynamicHelper<engine::SplinePath::PointArray>::Insert(void* array, int index, int unused)
	{
		A* a = (A*)array;
		if (a->Size() >= a->Capacity())
		{
			a->Reserve(a->Size() + 1);
		}
		T* position = a->begin + index;
		T* from = a->end;
		if (from + 1 <= a->capacity)
		{
			T* to = from + 1;
			a->end = to;
			while (from != position)
			{
				from--;
				to--;
				if (to != 0)
				{
					*to = *from;
				}
			}
			if (position != 0)
			{
				*position = Default();
			}
		}
	}

	void ArrayDynamicHelper<engine::SplinePath::PointArray>::Erase(void* array, int index, int unused)
	{
		A* a = (A*)array;
		T* position = a->begin + index;
		T* last = a->end;
		T* destination = position;
		for (T* source = position + 1; source != last; source++, destination++)
		{
			*destination = *source;
		}
		a->end--;
	}

	void ArrayDynamicHelper<engine::SplinePath::PointArray>::Expand(void* array, unsigned int count)
	{
		A* a = (A*)array;
		if (a->Capacity() == 0)
		{
			a->Allocate(count);
		}
		else if (count + a->Size() > a->Capacity())
		{
			a->Reserve(count + a->Size());
		}
	}
}

namespace container
{
	template class ArrayDynamic<engine::SplinePathCV*, AllocatorNew>;
}



// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x109106F0
// FUNCTION: ENGINE 0x10910700
// FUNCTION: ENGINE 0x10910710
// FUNCTION: ENGINE 0x10910760
// FUNCTION: ENGINE 0x109107B0
// FUNCTION: ENGINE 0x109107D0
// FUNCTION: ENGINE 0x10910800
// FUNCTION: ENGINE 0x10910810
// FUNCTION: ENGINE 0x10910840
// FUNCTION: ENGINE 0x10910850
// FUNCTION: ENGINE 0x10910880
// FUNCTION: ENGINE 0x109109B0
// FUNCTION: ENGINE 0x109109C0
// FUNCTION: ENGINE 0x10910A40
// FUNCTION: ENGINE 0x10910A80
// FUNCTION: ENGINE 0x10910AC0
// FUNCTION: ENGINE 0x10910B00
// FUNCTION: ENGINE 0x10910B40
// FUNCTION: ENGINE 0x10910B90
// FUNCTION: ENGINE 0x10910BA0
// FUNCTION: ENGINE 0x10910BC0
// FUNCTION: ENGINE 0x10910BD0
// FUNCTION: ENGINE 0x10910BE0
// FUNCTION: ENGINE 0x10910C00
// FUNCTION: ENGINE 0x10910C10
// FUNCTION: ENGINE 0x10910C50
// FUNCTION: ENGINE 0x10910C80
// FUNCTION: ENGINE 0x10910C90
// FUNCTION: ENGINE 0x10910CD0
// FUNCTION: ENGINE 0x10910D00
// FUNCTION: ENGINE 0x10910FD0
// FUNCTION: ENGINE 0x10910FE0
// FUNCTION: ENGINE 0x10911030
// FUNCTION: ENGINE 0x10911070
// FUNCTION: ENGINE 0x10911180
// FUNCTION: ENGINE 0x109111D0
// FUNCTION: ENGINE 0x10911480
// FUNCTION: ENGINE 0x109114E0
