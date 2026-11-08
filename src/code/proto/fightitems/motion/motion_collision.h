// Fight items of the motion group: DetectObbCollisionCondition, HitSurfaceCondition (unit 0x10149DC0 - 0x1014A890; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_COLLISION_H
#define PROTO_FIGHTITEMS_MOTION_COLLISION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/container/arrayfixed.h"
#include "code/container/arraydynamicnew.h"
#include "code/engine/fight/effecttrack.h"
#include "code/ravenphysics/collision/collisionobject.h"

namespace proto
{
	class CollisionActionBehaviour;

	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DetectObbCollisionCondition (10 vftable slots, 0x48 bytes)
			class DetectObbCollisionCondition : public fight::Condition
			{
			public:
				// 0x10149F50
				DetectObbCollisionCondition();
				virtual ~DetectObbCollisionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100A6350, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCollideWith(int newValue);
				bool SetMatch(bool newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetOrientation(const math::Vector& newValue);
				bool SetExtents(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

				// Getters of the members (the engine keeps their copies)
				int GetCollideWith() const;
				bool GetMatch() const;
				const fight::Name& GetJoint() const;
				math::Vector GetOffset() const;
				math::Vector GetOrientation() const;
				math::Vector GetExtents() const;

					unsigned char unknownC[0x4];
					fight::Name joint;  // +0x10
					math::Vector extents;  // +0x18
					math::Vector offset;  // +0x24
					math::Vector orientation;  // +0x30
					int collideWith;  // +0x3C
					bool match;  // +0x40
					unsigned char unknown41[0x7];
			};

			extern fight::Property** gDetectObbCollisionConditionProperties;
			fight::ConditionFactory* CreateDetectObbCollisionConditionFactory(const char* name);
			void RegisterDetectObbCollisionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HitSurfaceCondition (10 vftable slots, 0x14 bytes)
			class HitSurfaceCondition : public fight::Condition
			{
			public:
				// 0x10149EF0
				HitSurfaceCondition();
				virtual ~HitSurfaceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100A6060, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSurface(int newValue);
				bool SetHitSurface(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

				// Getters of the members (the engine keeps their copies)
				int GetSurface() const;
				bool GetHitSurface() const;

					int surface;  // +0xC
					bool hitSurface;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gHitSurfaceConditionProperties;
			fight::ConditionFactory* CreateHitSurfaceConditionFactory(const char* name);
			void RegisterHitSurfaceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// Whether two handles are the same one: the engine compares the 32 bits at once
			inline bool SameHandle(const engine::HandleBase& lhs, const engine::HandleBase& rhs)
			{
				return *(const unsigned int*)&lhs == *(const unsigned int*)&rhs;
			}

			// RTTI: proto::fightitems::motion::CollisionAction (31 vftable slots, 0x9C bytes): the base of the actions that watch the collision of a
			// volume around a joint of the object (grab, hit, detect and hit weapon); the members the tracks supply are read through the slots
			class CollisionAction : public fight::Action
			{
			public:
				// 0x100A5A00
				CollisionAction(engine::GameObjectHandle newTarget, fight::Track* listener, fight::Track* newTrack);
				// 0x100A5BA0
				virtual ~CollisionAction();

				// vftable slot 5 (0x100A4980)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100A3790)
				virtual void Slot6();
				// vftable slot 7 (0x100A4BE0)
				virtual bool Slot7(int arg, float value);
				// vftable slots 9 - 30 (name guesses where the overrides of the derived actions show what they stand for)
				virtual bool Slot9();
				virtual int Slot10();
				virtual int GetCollideWith();
				virtual float GetArcOffset();
				virtual float GetArcRange();
				virtual int Slot14();
				virtual float Slot15(int unused);
				virtual void Slot16(int a, int b);
				virtual int GetJointIndex();
				virtual math::Vector* GetOffset(math::Vector* offset);
				virtual bool GetUseMotion();
				virtual float GetRadius();
				virtual float Slot21();
				virtual bool Slot22();
				virtual void Slot23();
				virtual void Slot24(engine::GameObject* object) = 0;
				virtual bool Slot25(engine::GameObject* object);
				virtual engine::HandleBase* Slot26(engine::HandleBase* result);
				virtual bool Slot27();
				virtual bool Slot28();
				virtual bool Slot29();
				virtual bool Slot30(engine::GameObject* object);

				engine::GameObjectHandle target;  // +0x1C
				engine::GameObjectHandle unknown20;  // +0x20
				CollisionActionBehaviour* behaviour;  // +0x24
				bool unknown28;  // +0x28
				bool unknown29;  // +0x29
				engine::TrackWatch watch;  // +0x2C
				container::ArrayDynamicNew<unsigned int> unknown38;  // +0x38
				unsigned char unknown44[0x4];
				container::ArrayFixed<engine::GameObjectHandle, 10> hits;  // +0x48
				core::Link<fight::Track> link;  // +0x74
				int unknown80;  // +0x80
				ravenphysics::CollisionVolume* volume;  // +0x84
				int jointIndex;  // +0x88
				math::Vector offset;  // +0x8C
				float unknown98;  // +0x98
			};


			// ---- actions end
		}
	}
}

#endif
