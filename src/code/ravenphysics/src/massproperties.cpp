#include "code/content/vectormetatype.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/massproperties.h"

namespace ravenphysics
{
	// Keeps the properties in the list of the properties in progress (add) or takes them out (0x1067E330, another
	// unit; name guess)
	void Unknown1067E330(MassProperties* properties, bool add);

	// FUNCTION: ENGINE 0x10670C40
	content::ClassInfo* MassProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::MassProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10670C80
	void MassProperties::Slot3(int unused)
	{
		Unknown1067E330(this, true);
	}

	// FUNCTION: ENGINE 0x10670C90
	bool MassProperties::IsReady()
	{
		Unknown1067E330(this, false);
		return true;
	}

	// The sum of two vectors
	static inline math::Vector Sum(const math::Vector& a, const math::Vector& b)
	{
		return math::Vector(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	// FUNCTION: ENGINE 0x10670CA0
	// EQUIVALENT: the same calls and sums; the engine reserves the by-value vector's place before the call of GetUnknown90 and keeps a register for it, 11.4 %
	void MassProperties::ApplyTo(CollisionObject* object)
	{
		object->SetScale(mass);
		if (scaleInertia)
		{
			math::SymmetricMatrix inertia;
			inertia.Invert(*object->GetUnknown58());
			inertia.xx = diagonalInertia.x * inertia.xx;
			inertia.yy = diagonalInertia.y * inertia.yy;
			inertia.zz = diagonalInertia.z * inertia.zz;
			inertia.xy = nonDiagonalInertia.x * inertia.xy;
			inertia.yz = nonDiagonalInertia.y * inertia.yz;
			inertia.xz = nonDiagonalInertia.z * inertia.xz;
			object->SetVectors(&inertia);
		}
		else
		{
			math::SymmetricMatrix inertia(diagonalInertia.x, nonDiagonalInertia.x, nonDiagonalInertia.y,
				diagonalInertia.y, nonDiagonalInertia.z, diagonalInertia.z);
			object->SetVectors(&inertia);
		}
		if (overrideCenterOfMass)
		{
			object->SetPosition(centerOfMass);
			return;
		}
		if (displaceCenterOfMass)
		{
			object->SetPosition(Sum(centerOfMass, *object->GetUnknown90()));
		}
	}

	// FUNCTION: ENGINE 0x10670E90
	// EQUIVALENT: the same stores and calls; the engine stores the vftables and the reference count between the pushes of the name's arguments, 86.8 %
	MassProperties::MassProperties() :
		name("undefined", 1),
		mass(1.0f),
		diagonalInertia(1.0f, 1.0f, 1.0f),
		nonDiagonalInertia(1.0f, 1.0f, 1.0f),
		scaleInertia(true),
		overrideCenterOfMass(false),
		displaceCenterOfMass(false),
		centerOfMass(0.0f, 0.0f, 0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10670F10
	MassProperties::~MassProperties()
	{
	}

	// FUNCTION: ENGINE 0x10670F20
	void MassProperties::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x10671030
	content::MemberList* MassProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<MassProperties, float, 0>("p"),
				content::MemberOffset(&((MassProperties*)0)->mass, (int)&((MassProperties*)0)->mass), "mass" },
			{ content::GetMemberVectorMetaType<MassProperties, 0>("p"), (int)&((MassProperties*)0)->diagonalInertia,
				"diagonalInertia" },
			{ content::GetMemberVectorMetaType<MassProperties, 1>("p"),
				(int)&((MassProperties*)0)->nonDiagonalInertia, "nonDiagonalInertia" },
			{ content::GetMemberPrimitiveMetaType<MassProperties, bool, 0>("p"),
				content::MemberOffset(&((MassProperties*)0)->scaleInertia, (int)&((MassProperties*)0)->scaleInertia),
				"scaleInertia" },
			{ content::GetMemberPrimitiveMetaType<MassProperties, bool, 1>("p"),
				content::MemberOffset(&((MassProperties*)0)->overrideCenterOfMass,
				(int)&((MassProperties*)0)->overrideCenterOfMass), "overrideCenterOfMass" },
			{ content::GetMemberPrimitiveMetaType<MassProperties, bool, 2>("p"),
				content::MemberOffset(&((MassProperties*)0)->displaceCenterOfMass,
				(int)&((MassProperties*)0)->displaceCenterOfMass), "displaceCenterOfMass" },
			{ content::GetMemberVectorMetaType<MassProperties, 2>("p"), (int)&((MassProperties*)0)->centerOfMass,
				"centerOfMass" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// Kept copies of the reflection above
	// FUNCTION: ENGINE 0x10670E00
	// FUNCTION: ENGINE 0x10670E30
	// FUNCTION: ENGINE 0x10670E60
	// FUNCTION: ENGINE 0x10670F30
	// FUNCTION: ENGINE 0x10670F70
	// FUNCTION: ENGINE 0x10670FB0
	// FUNCTION: ENGINE 0x10670FF0
	// FUNCTION: ENGINE 0x10671190
}
