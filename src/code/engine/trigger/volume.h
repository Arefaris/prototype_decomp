// engine::trigger::Volume, SphereVolume and OBBVolume (RTTI names; the reflection names are "engine::trigger::Volume"
// and so on): the shape a trigger tests objects against, made as an object of the physics library that follows the
// transform of its owner. A volume is reflected with the mask of what it reacts to; the sphere and the box add their
// shape. Unit 0x10841550 - 0x10842010 (no assert path; the directory and file names are guesses). Member and method
// names are guesses.
#ifndef ENGINE_TRIGGER_VOLUME_H
#define ENGINE_TRIGGER_VOLUME_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/obb.h"
#include "code/math/sphere.h"
#include "code/ravenphysics/context.h"

namespace engine
{
	class GameObject;

	namespace trigger
	{
		class Volume
		{
		public:
			// 0x10841BC0
			Volume();
			// vftable slot 0 (0x10841BE0 deletes; the derived classes' deleting destructors call the body 0x10841830)
			virtual ~Volume();
			// vftable slot 1: makes the physics object of the shape (pure here)
			virtual void CreateObject() = 0;
			// vftable slot 2 (0x10841610): asks the owner (its vftable slot 4)
			virtual bool IsOwnerReady();
			// vftable slot 3: gives the physics object the shape (pure here)
			virtual void ApplyShape() = 0;
			// vftable slots 4 and 5 (0x10841630 / 0x10841640): do nothing here
			virtual void Slot4();
			virtual void Slot5();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10841620: the handle of the physics object
			ravenphysics::ObjectHandle* GetHandle();
			// 0x10841650: the handle of the owner
			GameObjectHandle GetOwnerHandle();
			// 0x10841870: moves the physics object
			void SetObjectTransform(const math::Matrix& transform);
			// 0x108418B0: the transform of the owner
			void GetOwnerTransform(math::Matrix* out);
			// 0x108418D0: what the physics object tests against follows from the kind and the mask
			void ApplyFilter();
			// 0x10841C00: the kind (1: the owner is what is tested against) of the volume; makes the physics object
			void SetKind(int newKind);
			// 0x10841C30
			void SetOwner(GameObjectHandle newOwner);
			// 0x10841C70
			void SetInteractionMask(unsigned int mask);

			int kind;  // +0x04
			unsigned int interactionMask;  // +0x08
			ravenphysics::ObjectHandle handle;  // +0x0C
			GameObject* owner;  // +0x10
		};

		class SphereVolume : public Volume
		{
		public:
			// 0x10841CD0 / 0x10841C80
			SphereVolume();
			explicit SphereVolume(const math::Sphere& newSphere);
			// vftable slot 0: the implicit destructor (0x10841CB0 deletes; it calls the body of Volume's)
			virtual void CreateObject();
			virtual void ApplyShape();
			virtual void Slot4();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10841960: takes the sphere (and gives the physics object it)
			void SetSphere(const math::Sphere& newSphere);

			math::Sphere sphere;  // +0x14
		};

		class OBBVolume : public Volume
		{
		public:
			// 0x10841D90 / 0x10841D00
			OBBVolume();
			explicit OBBVolume(const math::OBB& newBox);
			// vftable slot 0: the implicit destructor (0x10841D70 deletes; it calls the body of Volume's)
			virtual void CreateObject();
			virtual void ApplyShape();
			virtual void Slot4();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10841A30
			void SetBox(const math::OBB& newBox);

			math::OBB box;  // +0x14
		};
	}
}

#endif
