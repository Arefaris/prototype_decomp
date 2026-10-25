// The path behaviours: see the header. The unit has no name of its own in the binary, the file name is a guess.
#include "code/engine/gameobject/behaviours/pathbehaviour.h"
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/message.h"
#include "code/engine/surfacedefinition.h"
#include <new>

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	extern content::ObjectName gTransformName;

	// The identities under which the two path scripts are registered (0x11315C98, 0x11315C9C; names guessed)
	int gPatrolPathScriptOwner;
	int gSplineScriptOwner;

	// The script functions that make a patrol path or a spline do nothing in this build (names guessed)
	// FUNCTION: ENGINE 0x10864CF0
	void CreatePatrolPath(const char* name, int count)
	{
	}

	// FUNCTION: ENGINE 0x10864D80
	void CreateSpline(const char* name, int count)
	{
	}

	// FUNCTION: ENGINE 0x10866860
	void RegisterPatrolPathScript()
	{
		LuaScriptManager* script = GetScriptManager();
		script->SetOwner(&gPatrolPathScriptOwner);
		script->Register("path_CreatePatrolPath", CreatePatrolPath);
		script->ClearOwner();
	}

	// FUNCTION: ENGINE 0x10866950
	void RegisterSplineScript()
	{
		LuaScriptManager* script = GetScriptManager();
		script->SetOwner(&gSplineScriptOwner);
		script->Register("path_CreateSpline", CreateSpline);
		script->ClearOwner();
	}

	// FUNCTION: ENGINE 0x10864DB0
	void UnregisterPatrolPathScript()
	{
		LuaScriptManager* script = GetScriptManager();
		script->Unregister(&gPatrolPathScriptOwner);
	}

	// FUNCTION: ENGINE 0x10864EA0
	void UnregisterSplineScript()
	{
		LuaScriptManager* script = GetScriptManager();
		script->Unregister(&gSplineScriptOwner);
	}

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

	// The engine copies vectors component by component
	static inline void CopyVector(math::Vector& dest, const math::Vector& source)
	{
		dest.x = source.x;
		dest.y = source.y;
		dest.z = source.z;
	}

	static inline void TranslationOf(const math::Matrix& matrix, math::Vector& out)
	{
		out.x = matrix.m[3][0];
		out.y = matrix.m[3][1];
		out.z = matrix.m[3][2];
	}

	// The point halfway between a and b, and the point as far from a as a is from b
	static inline void Midpoint(math::Vector& out, const math::Vector& a, const math::Vector& b)
	{
		out.x = (a.x + b.x) * 0.5f;
		out.y = (a.y + b.y) * 0.5f;
		out.z = (a.z + b.z) * 0.5f;
	}

	static inline void Extrapolate(math::Vector& out, const math::Vector& a, const math::Vector& b)
	{
		out.x = a.x * 2.0f - b.x;
		out.y = a.y * 2.0f - b.y;
		out.z = a.z * 2.0f - b.z;
	}

	// FUNCTION: ENGINE 0x10864C30
	content::ClassInfo* IPathBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::IPathBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10864C70
	content::ClassInfo* PatrolPoint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PatrolPoint";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10864CB0
	content::ClassInfo* PatrolPathBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PatrolPathBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10864D00
	content::ClassInfo* SplineCV::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SplineCV";
		sInfo.code = "pn";
		return &sInfo;
	}

	// 0x10864D90 (constructor, kept copy) and 0x10864FA0 (IsDerived): the caster the class meta type of
	// engine::IPathBehaviour carries for engine::SplineBehaviour. The unit kept them out of line, which is what an
	// explicit instantiation makes the compiler do.
	template struct content::BaseClassCasterImpl<IPathBehaviour, SplineBehaviour>;

	// FUNCTION: ENGINE 0x10864DF0
	SplineCV::SplineCV()
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

	// FUNCTION: ENGINE 0x10864E30
	SplineCV::~SplineCV()
	{
	}

	// FUNCTION: ENGINE 0x10864D40
	content::ClassInfo* SplineBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SplineBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10865350
	PatrolPoint::PatrolPoint() : position(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10864DA0
	PatrolPoint::~PatrolPoint()
	{
	}

	// FUNCTION: ENGINE 0x10865D10
	content::MemberList* IPathBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, IPathBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10865D70
	content::MemberList* PatrolPoint::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<PatrolPoint, 0>("p"), 4, "pos" },
			{ content::GetMemberVectorMetaType<PatrolPoint, 1>("p"), 0x10, "ori" },
			{ content::GetMemberStringMetaType<0>(&((PatrolPoint*)content::gStringMemberBase)->text, "p"),
				content::StringBufferOffset(&((PatrolPoint*)content::gStringMemberBase)->text)
				+ (int)&((PatrolPoint*)0)->text, "text" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10865E60
	content::MemberList* SplineCV::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<SplineCV, float, 0>("p"), ENGINE_OFFSET(SplineCV, key.time),
				"time" },
			{ content::GetMemberVectorMetaType<SplineCV, 0>("p"), 8, "position" },
			{ content::GetMemberPrimitiveMetaType<SplineCV, float, 1>("p"), ENGINE_OFFSET(SplineCV, tension),
				"tension" },
			{ content::GetMemberPrimitiveMetaType<SplineCV, float, 2>("p"), ENGINE_OFFSET(SplineCV, continuity),
				"continuity" },
			{ content::GetMemberPrimitiveMetaType<SplineCV, float, 3>("p"), ENGINE_OFFSET(SplineCV, bias),
				"bias" },
			{ content::GetMemberPrimitiveMetaType<SplineCV, bool, 0>("p"), ENGINE_OFFSET(SplineCV, forceSpeedMatch),
				"forceSpeedMatch" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10866C40
	content::MemberList* PatrolPathBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<IPathBehaviour>();
		static content::BaseClassCasterImpl<IPathBehaviour, PatrolPathBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<PatrolPathBehaviour, bool, 0>("p"),
				ENGINE_OFFSET(PatrolPathBehaviour, closed), "closed" },
			{ content::GetArrayDynamicMetaType<PatrolPathBehaviour, PatrolPathBehaviour::PointArray>(
				content::GetObjectMetaType<PatrolPoint>("pn"), "pn"), ENGINE_OFFSET(PatrolPathBehaviour, points),
				"points" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10866D20
	content::MemberList* SplineBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<IPathBehaviour>();
		static content::BaseClassCasterImpl<IPathBehaviour, SplineBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<SplineBehaviour, SplineBehaviour::PointArray>(
				content::GetObjectMetaType<SplineCV>("pn"), "pn"), ENGINE_OFFSET(SplineBehaviour, points),
				"points" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10867600
	PatrolPathBehaviour::PatrolPathBehaviour(GameObject* newOwner) : IPathBehaviour(newOwner), closed(false),
		unknown20(0), unknown24(false), followOwner(true)
	{
		SetIdentity(transform);
		Listen2(4, true);
		Listen(0x1a, true);
		owner->SetAttributeAndGet<math::Matrix>(gTransformName, math::Matrix::IDENTITY, false);
		if (owner->transform == 0)
		{
			owner->transform = (Attribute<math::Matrix>*)owner->FindAttribute(gTransformName);
		}
		transform = owner->transform->value;
	}

	// FUNCTION: ENGINE 0x10867760
	SplineBehaviour::SplineBehaviour(GameObject* newOwner) : IPathBehaviour(newOwner), spline(0), unknown20(0),
		unknown24(0), unknown28(0), unknown2C(false), followOwner(true)
	{
		SetIdentity(transform);
		Listen2(4, true);
		Listen(0x1a, true);
		owner->SetAttributeAndGet<math::Matrix>(gTransformName, math::Matrix::IDENTITY, false);
		if (owner->transform == 0)
		{
			owner->transform = (Attribute<math::Matrix>*)owner->FindAttribute(gTransformName);
		}
		transform = owner->transform->value;
	}

	// FUNCTION: ENGINE 0x108668F0
	// EQUIVALENT: register allocation only: the engine keeps this in esi and the point cursor in edi, ours the other way round, 79.4 %
	PatrolPathBehaviour::~PatrolPathBehaviour()
	{
		PatrolPoint** point = points.begin;
		while (point != points.end)
		{
			delete *point;
			point++;
		}
	}

	// FUNCTION: ENGINE 0x108669E0
	// EQUIVALENT: the engine reads the spline pointer after emptying the array and keeps this in esi, ours reads it before, 89.7 %
	SplineBehaviour::~SplineBehaviour()
	{
		for (SplineCV** point = points.begin; point != points.end; point++)
		{
			delete *point;
		}
		points.end = points.begin;
		if (spline != 0)
		{
			delete spline;
		}
	}

	// FUNCTION: ENGINE 0x108653B0
	void PatrolPathBehaviour::Slot1()
	{
		IPathBehaviour::Slot1();
	}

	// FUNCTION: ENGINE 0x10864DD0
	void PatrolPathBehaviour::Update(float dt, unsigned short mask)
	{
	}

	// FUNCTION: ENGINE 0x10864EC0
	void SplineBehaviour::Update(float dt, unsigned short mask)
	{
	}

	// FUNCTION: ENGINE 0x10865520
	int PatrolPathBehaviour::GetPointCount()
	{
		return points.Size();
	}

	// FUNCTION: ENGINE 0x10865610
	int SplineBehaviour::GetPointCount()
	{
		return points.Size();
	}

	// FUNCTION: ENGINE 0x10865530
	// EQUIVALENT: register allocation only: the engine keeps the output pointer in eax and the transform in edx, ours the other way round, 68.9 %
	void PatrolPathBehaviour::GetPoint(math::Vector* position, int index)
	{
		owner->transform->value.GetTranslation(*position);
		if (index >= 0 && index < (int)points.Size())
		{
			if (points[index] != 0)
			{
				CopyVector(*position, points[index]->position);
			}
		}
	}

	// FUNCTION: ENGINE 0x10865620
	// EQUIVALENT: register allocation only: the engine keeps the output pointer in eax and the transform in edx, ours the other way round, 68.9 %
	void SplineBehaviour::GetPoint(math::Vector* position, int index)
	{
		owner->transform->value.GetTranslation(*position);
		if (index >= 0 && index < (int)points.Size())
		{
			if (points[index] != 0)
			{
				CopyVector(*position, points[index]->key.position);
			}
		}
	}

	// FUNCTION: ENGINE 0x10865590
	bool PatrolPathBehaviour::SetPoint(int index, const math::Vector* position)
	{
		bool result = false;
		if (index >= 0 && index < (int)points.Size())
		{
			if (points[index] != 0)
			{
				CopyVector(points[index]->position, *position);
				if (index == 0)
				{
					followOwner = false;
					owner->SetPosition(*position);
					followOwner = true;
				}
				result = true;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10866260
	bool SplineBehaviour::SetPoint(int index, const math::Vector* position)
	{
		bool result = false;
		if (index >= 0 && index < (int)points.Size())
		{
			if (points[index] != 0)
			{
				CopyVector(points[index]->key.position, *position);
				result = true;
				if (index == 1)
				{
					followOwner = false;
					owner->SetPosition(*position);
					followOwner = true;
				}
			}
		}
		BuildSpline();
		return result;
	}

	// FUNCTION: ENGINE 0x10865FA0
	void PatrolPathBehaviour::RemovePoint(int index)
	{
		if (index >= 0)
		{
			if (index < (int)points.Size())
			{
				PatrolPoint** slot = &points[index];
				if (*slot != 0)
				{
					delete *slot;
				}
				points.Erase(slot);
			}
			if (index == 0 && points.Size() > 0)
			{
				followOwner = false;
				owner->SetPosition(points[0]->position);
				followOwner = true;
			}
		}
	}

	// FUNCTION: ENGINE 0x108662D0
	void SplineBehaviour::RemovePoint(int index)
	{
		if (index >= 0 && index < (int)points.Size())
		{
			SplineCV** slot = &points[index];
			if (*slot != 0)
			{
				delete *slot;
			}
			points.Erase(slot);
		}
		if (index == 1 && points.Size() > 1)
		{
			followOwner = false;
			owner->SetPosition(points[1]->key.position);
			followOwner = true;
		}
		BuildSpline();
	}

	// FUNCTION: ENGINE 0x10866940
	void PatrolPathBehaviour::Slot14(int index)
	{
	}

	// FUNCTION: ENGINE 0x10866A50
	void SplineBehaviour::Slot14(int index)
	{
	}

	// FUNCTION: ENGINE 0x10865510
	void PatrolPathBehaviour::Slot15()
	{
	}

	// FUNCTION: ENGINE 0x10866250
	void SplineBehaviour::Slot15()
	{
		BuildSpline();
	}

	// FUNCTION: ENGINE 0x108660F0
	void SplineBehaviour::Slot1()
	{
		IPathBehaviour::Slot1();
		BuildSpline();
	}

	// FUNCTION: ENGINE 0x10865680
	void SplineBehaviour::BuildSpline()
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
			SplineCV* point = points[i];
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

	// FUNCTION: ENGINE 0x10866020
	// NONMATCHING: the engine keeps the position of the next point in registers across the loop and writes it back every pass, best 20 %
#ifdef NONMATCHING
	void PatrolPathBehaviour::CreatePoints(int count)
	{
		const math::Matrix& matrix = owner->transform->value;
		math::Vector cursor(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
		if (points.Size() == 0)
		{
			points.Allocate(count);
			if (count > 0)
			{
				do
				{
					PatrolPoint* point = new PatrolPoint;
					point->position.y = cursor.y;
					cursor.y += 10.0f;
					point->position.x = cursor.x;
					point->position.z = cursor.z;
					points.PushBack(point);
				}
				while (--count != 0);
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10866360
	// NONMATCHING: scheduling of the cursor's stores and loads differs, best 47 %
#ifdef NONMATCHING
	void SplineBehaviour::CreatePoints(int count, const math::Vector* step)
	{
		SplineCV::Key cursor;
		cursor.time = -1.0f;
		cursor.position.x = owner->transform->value.m[3][0];
		cursor.position.y = owner->transform->value.m[3][1];
		cursor.position.z = owner->transform->value.m[3][2];
		if (points.Size() == 0)
		{
			points.Allocate(count);
			for (; count > 0; count--)
			{
				SplineCV* point = new SplineCV;
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
				points.PushBack(point);
			}
		}
		BuildSpline();
	}
#endif

	// FUNCTION: ENGINE 0x108653C0
	void PatrolPathBehaviour::OnMessage(Message* message)
	{
		if (message->type == 0x1a)
		{
			math::Matrix previous = transform;
			transform = owner->transform->value;
			if (followOwner)
			{
				previous.Invert();
				previous.Multiply(previous, owner->transform->value);
				for (int i = 0; i < (int)points.Size(); i++)
				{
					if (points[i] != 0)
					{
						points[i]->position.Transform(previous);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10866100
	void SplineBehaviour::OnMessage(Message* message)
	{
		if (message->type == 0x1a)
		{
			math::Matrix previous = transform;
			transform = owner->transform->value;
			if (followOwner)
			{
				previous.Invert();
				previous.Multiply(previous, owner->transform->value);
				for (int i = 0; i < (int)points.Size(); i++)
				{
					if (points[i] != 0)
					{
						points[i]->key.position.Transform(previous);
					}
				}
			}
			BuildSpline();
		}
	}

	// FUNCTION: ENGINE 0x108671E0
	// NONMATCHING: the neighbours' vectors are handled through references the compiler materialises, block order differs, best 27 %
#ifdef NONMATCHING
	void SplineBehaviour::InsertBefore(int index)
	{
		if (points[index] != 0)
		{
			SplineCV::Key target;
			target.time = 0.0f;
			target.position.x = 0.0f;
			target.position.y = 0.0f;
			target.position.z = 0.0f;
			if (points.Size() == 1)
			{
				SplineCV* only = points[0];
				target.position.x = only->key.position.x;
				target.position.y = only->key.position.y - 10.0f;
				target.position.z = only->key.position.z;
				target.time = only->key.time - 1.0f;
			}
			else if (index == 0)
			{
				SplineCV* first = points[0];
				SplineCV* second = points[1];
				target.position.x = first->key.position.x * 2.0f - second->key.position.x;
				target.position.y = first->key.position.y * 2.0f - second->key.position.y;
				target.position.z = first->key.position.z * 2.0f - second->key.position.z;
				target.time = first->key.time * 2.0f - second->key.time;
			}
			else if (index > 0 && index < (int)points.Size())
			{
				SplineCV* current = points[index];
				SplineCV* before = points[index - 1];
				target.position.x = (before->key.position.x + current->key.position.x) * 0.5f;
				target.position.y = (current->key.position.y + before->key.position.y) * 0.5f;
				target.position.z = (current->key.position.z + before->key.position.z) * 0.5f;
				target.time = (before->key.time + current->key.time) * 0.5f;
			}
			SplineCV* point = new SplineCV;
			point->key.position.x = target.position.x;
			point->key.position.y = target.position.y;
			point->key.position.z = target.position.z;
			point->key.time = target.time;
			if (points.Size() >= points.Capacity())
			{
				points.Reserve(points.Size() + 1);
			}
			points.Insert(points.begin + index, point);
			if (index == 1)
			{
				followOwner = false;
				owner->SetPosition(points[1]->key.position);
				followOwner = true;
			}
			BuildSpline();
		}
	}
#endif

	// FUNCTION: ENGINE 0x108673D0
	// NONMATCHING: as InsertBefore, best 23 %
#ifdef NONMATCHING
	void SplineBehaviour::InsertAfter(int index)
	{
		if (points[index] != 0)
		{
			SplineCV::Key target;
			target.time = 0.0f;
			target.position.x = 0.0f;
			target.position.y = 0.0f;
			target.position.z = 0.0f;
			if (points.Size() == 1)
			{
				SplineCV* only = points[0];
				target.position.x = only->key.position.x;
				target.position.y = only->key.position.y + 10.0f;
				target.position.z = only->key.position.z;
				target.time = only->key.time + 1.0f;
			}
			else if (index < 0 || index >= (int)points.Size() - 1)
			{
				if (index == (int)points.Size() - 1)
				{
					SplineCV* last = points[points.Size() - 1];
					SplineCV* before = points[points.Size() - 2];
					target.position.x = last->key.position.x * 2.0f - before->key.position.x;
					target.position.y = last->key.position.y * 2.0f - before->key.position.y;
					target.position.z = last->key.position.z * 2.0f - before->key.position.z;
					target.time = last->key.time * 2.0f - before->key.time;
				}
			}
			else
			{
				SplineCV* next = points[index + 1];
				SplineCV* current = points[index];
				target.position.x = (next->key.position.x + current->key.position.x) * 0.5f;
				target.position.y = (next->key.position.y + current->key.position.y) * 0.5f;
				target.position.z = (next->key.position.z + current->key.position.z) * 0.5f;
				target.time = (current->key.time + next->key.time) * 0.5f;
			}
			SplineCV* point = new SplineCV;
			point->key.position.x = target.position.x;
			point->key.position.y = target.position.y;
			point->key.position.z = target.position.z;
			point->key.time = target.time;
			if (points.Size() >= points.Capacity())
			{
				points.Reserve(points.Size() + 1);
			}
			points.Insert(points.begin + 1 + index, point);
			if (index == 0)
			{
				followOwner = false;
				owner->SetPosition(points[1]->key.position);
				followOwner = true;
			}
			BuildSpline();
		}
	}
#endif

	// FUNCTION: ENGINE 0x10866E00
	// NONMATCHING: the neighbours' vectors are handled through references the compiler materialises, block order differs, best 27 %
#ifdef NONMATCHING
	void PatrolPathBehaviour::InsertBefore(int index)
	{
		if (points[index] == 0)
		{
			return;
		}
		math::Vector target(0.0f, 0.0f, 0.0f);
		if (points.Size() == 1)
		{
			PatrolPoint* only = points[0];
			target.x = only->position.x;
			target.y = only->position.y - 10.0f;
			target.z = only->position.z;
		}
		else
		{
			PatrolPoint* current;
			PatrolPoint* other;
			if (index == 0)
			{
				current = points[0];
				if (!closed)
				{
					other = points[1];
					target.x = current->position.x * 2.0f - other->position.x;
					target.y = current->position.y * 2.0f - other->position.y;
					target.z = current->position.z * 2.0f - other->position.z;
					goto place;
				}
				other = points[points.Size() - 1];
			}
			else
			{
				if (index < 1 || index >= (int)points.Size())
				{
					goto place;
				}
				current = points[index];
				other = points[index - 1];
			}
			target.z = (current->position.z + other->position.z) * 0.5f;
			target.y = (current->position.y + other->position.y) * 0.5f;
			target.x = (current->position.x + other->position.x) * 0.5f;
		}
	place:
		PatrolPoint* point = new PatrolPoint;
		point->position.x = target.x;
		point->position.y = target.y;
		point->position.z = target.z;
		if (points.Size() >= points.Capacity())
		{
			points.Reserve(points.Size() + 1);
		}
		points.Insert(points.begin + index, point);
		if (index == 0)
		{
			followOwner = false;
			owner->SetPosition(points[0]->position);
			followOwner = true;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10866FC0
	// NONMATCHING: as InsertBefore, best 23 %
#ifdef NONMATCHING
	void PatrolPathBehaviour::InsertAfter(int index)
	{
		if (points[index] != 0)
		{
			math::Vector target(0.0f, 0.0f, 0.0f);
			if (points.Size() == 1)
			{
				PatrolPoint* only = points[0];
				target.x = only->position.x;
				target.y = only->position.y + 10.0f;
				target.z = only->position.z;
			}
			else if (index < 0 || index >= (int)points.Size() - 1)
			{
				if (index == (int)points.Size() - 1)
				{
					if (!closed)
					{
						PatrolPoint* last = points[points.Size() - 1];
						PatrolPoint* before = points[points.Size() - 2];
						target.x = last->position.x * 2.0f - before->position.x;
						target.y = last->position.y * 2.0f - before->position.y;
						target.z = last->position.z * 2.0f - before->position.z;
					}
					else
					{
						PatrolPoint* first = points[0];
						PatrolPoint* current = points[index];
						target.x = (current->position.x + first->position.x) * 0.5f;
						target.y = (first->position.y + current->position.y) * 0.5f;
						target.z = (first->position.z + current->position.z) * 0.5f;
					}
				}
			}
			else
			{
				PatrolPoint* next = points[index + 1];
				PatrolPoint* current = points[index];
				target.x = (next->position.x + current->position.x) * 0.5f;
				target.y = (next->position.y + current->position.y) * 0.5f;
				target.z = (next->position.z + current->position.z) * 0.5f;
			}
			PatrolPoint* point = new PatrolPoint;
			point->position.x = target.x;
			point->position.y = target.y;
			point->position.z = target.z;
			if (points.Size() >= points.Capacity())
			{
				points.Reserve(points.Size() + 1);
			}
			points.Insert(points.begin + 1 + index, point);
		}
	}
#endif
}

namespace container
{
	template class ArrayDynamicNew<engine::PatrolPoint*>;
	template class ArrayDynamicNew<engine::SplineCV*>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108650B0
// FUNCTION: ENGINE 0x108650E0
// FUNCTION: ENGINE 0x10865140
// FUNCTION: ENGINE 0x10865150
// FUNCTION: ENGINE 0x10865180
// FUNCTION: ENGINE 0x108652E0
// FUNCTION: ENGINE 0x10865320
// FUNCTION: ENGINE 0x108659F0
// FUNCTION: ENGINE 0x10865A30
// FUNCTION: ENGINE 0x10865A70
// FUNCTION: ENGINE 0x10865AB0
// FUNCTION: ENGINE 0x10865AF0
// FUNCTION: ENGINE 0x10865B30
// FUNCTION: ENGINE 0x10865B80
// FUNCTION: ENGINE 0x10865C10
// FUNCTION: ENGINE 0x108666A0
// FUNCTION: ENGINE 0x108666F0
// FUNCTION: ENGINE 0x10866740
// FUNCTION: ENGINE 0x10866790
// FUNCTION: ENGINE 0x10866AE0
// FUNCTION: ENGINE 0x10866B30

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10864D90
// FUNCTION: ENGINE 0x10864EE0
// FUNCTION: ENGINE 0x10864EF0
// FUNCTION: ENGINE 0x10864F00
// FUNCTION: ENGINE 0x10864F10
// FUNCTION: ENGINE 0x10864F20
// FUNCTION: ENGINE 0x10864F30
// FUNCTION: ENGINE 0x10864F40
// FUNCTION: ENGINE 0x10864F50
// FUNCTION: ENGINE 0x10864F60
// FUNCTION: ENGINE 0x10864F70
// FUNCTION: ENGINE 0x10864F80
// FUNCTION: ENGINE 0x10864F90
// FUNCTION: ENGINE 0x10864FD0
// FUNCTION: ENGINE 0x10865040
// FUNCTION: ENGINE 0x10865110
// FUNCTION: ENGINE 0x10865190
// FUNCTION: ENGINE 0x108651B0
// FUNCTION: ENGINE 0x10865200
// FUNCTION: ENGINE 0x10865220
// FUNCTION: ENGINE 0x108652D0
// FUNCTION: ENGINE 0x10865310
// FUNCTION: ENGINE 0x10865390
// FUNCTION: ENGINE 0x108655F0
// FUNCTION: ENGINE 0x10865790
// FUNCTION: ENGINE 0x108657A0
// FUNCTION: ENGINE 0x108657F0
// FUNCTION: ENGINE 0x10865850
// FUNCTION: ENGINE 0x10865860
// FUNCTION: ENGINE 0x10865870
// FUNCTION: ENGINE 0x108658C0
// FUNCTION: ENGINE 0x10865920
// FUNCTION: ENGINE 0x10865930
// FUNCTION: ENGINE 0x10865960
// FUNCTION: ENGINE 0x10865B70
// FUNCTION: ENGINE 0x10865BB0
// FUNCTION: ENGINE 0x10865BC0
// FUNCTION: ENGINE 0x10865BD0
// FUNCTION: ENGINE 0x10865BE0
// FUNCTION: ENGINE 0x10865BF0
// FUNCTION: ENGINE 0x10865C00
// FUNCTION: ENGINE 0x10865C40
// FUNCTION: ENGINE 0x10865C50
// FUNCTION: ENGINE 0x10865C60
// FUNCTION: ENGINE 0x10865C70
// FUNCTION: ENGINE 0x10865C80
// FUNCTION: ENGINE 0x10866480
// FUNCTION: ENGINE 0x10866530
// FUNCTION: ENGINE 0x108667E0
// FUNCTION: ENGINE 0x10866820
// FUNCTION: ENGINE 0x10866DE0
// FUNCTION: ENGINE 0x108671C0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
