// The objects a free roam event shows the player or watches for (RTTI proto::FREventObjectBase and its derived
// classes): locators (a place with a marker), object definitions (a game object made from a template at a place) and
// trigger volumes (a sphere or a box around a place, or a game object that reports the player). The "Def" classes
// describe the object from the event's data, the others look an existing game object up by name. The names of the
// classes are original (RTTI), the members and the virtual functions are guessed. Unit 0x10585440 - 0x10593A00 (no
// assert path; the file names are guesses).
#ifndef PROTO_FREEROAMEVENTS_FROBJECTS_H
#define PROTO_FREEROAMEVENTS_FROBJECTS_H

#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/obb.h"
#include "code/math/vector.h"

namespace proto
{
	typedef core::Name<core::CaseSensitiveKey> ObjectName;

	// The base of all of them: a name and the game object that stands for it (invalid until it is made)
	struct FREventObjectBase
	{
		FREventObjectBase(ObjectName newName) : name(newName)
		{
		}
		virtual ~FREventObjectBase()
		{
		}
		// Whether the game object of the object exists
		virtual bool IsReady() = 0;
		// Makes the game object
		virtual void Spawn() = 0;
		// Hands the game object back (the base does nothing)
		virtual void Release()
		{
		}
		virtual math::Vector GetPosition() = 0;
		// A kind number the event code tests
		virtual int GetKind() = 0;

		int unknown4;  // a name is laid out at a multiple of 8
		ObjectName name;  // +0x8
		engine::GameObjectHandle handle;  // +0x10
		int unknown14;  // the size of the base is a multiple of 8
	};

	// A place with a map marker
	struct FREventLocatorDef : public FREventObjectBase
	{
		FREventLocatorDef(ObjectName newName, float newX, float newY, float newZ, float new24, float new28,
			float new2C);
		virtual ~FREventLocatorDef();
		virtual bool IsReady();
		virtual void Spawn();
		virtual void Release();
		virtual math::Vector GetPosition();
		virtual int GetKind();

		float x;  // +0x18
		float y;  // +0x1C
		float z;  // +0x20
		float unknown24;
		float unknown28;
		float unknown2C;
	};

	// A game object made from a template at a place
	struct FREventObjectDef : public FREventObjectBase
	{
		FREventObjectDef(ObjectName newName, ObjectName newTemplateName, float newX, float newY, float newZ,
			float newDirectionX, float newDirectionY, float newDirectionZ);
		virtual ~FREventObjectDef();
		virtual bool IsReady();
		virtual void Spawn();
		virtual void Release();
		virtual math::Vector GetPosition();
		virtual int GetKind();

		ObjectName templateName;  // +0x18
		float x;  // +0x20
		float y;  // +0x24
		float z;  // +0x28
		float directionX;  // +0x2C
		float directionY;  // +0x30
		float directionZ;  // +0x34
	};

	// A volume the player can be inside of
	struct FREventTriggerBase : public FREventObjectBase
	{
		FREventTriggerBase(ObjectName newName) : FREventObjectBase(newName)
		{
		}
		virtual ~FREventTriggerBase()
		{
		}
		virtual int GetKind();
		// Whether the player is inside
		virtual bool IsPlayerInside() = 0;
	};

	// A trigger volume described by the event's data
	struct FREventTriggerDef : public FREventTriggerBase
	{
		FREventTriggerDef(ObjectName newName);
		virtual ~FREventTriggerDef();
		virtual bool IsReady();
		virtual void Release();
	};

	// A ball around a place
	struct FREventTriggerDefSphere : public FREventTriggerDef
	{
		FREventTriggerDefSphere(ObjectName newName, float newX, float newY, float newZ, float newRadius);
		virtual void Spawn();
		virtual math::Vector GetPosition();
		virtual bool IsPlayerInside();

		float x;  // +0x18
		float y;  // +0x1C
		float z;  // +0x20
		float radius;  // +0x24
	};

	// A box around a place
	struct FREventTriggerDefCuboid : public FREventTriggerDef
	{
		virtual void Spawn();
		virtual math::Vector GetPosition();
		virtual bool IsPlayerInside();

		math::OBB box;  // +0x18
	};

	// A trigger volume that is a game object of the world (the engine's constructor of this class looks the game
	// object up by the name; it is not part of this reconstruction)
	struct FREventLocator : public FREventObjectBase
	{
		explicit FREventLocator(ObjectName newName);
		virtual ~FREventLocator()
		{
		}
		virtual bool IsReady();
		virtual void Spawn();
		virtual void Release();
		virtual math::Vector GetPosition();
		virtual int GetKind();
	};
}

#endif
