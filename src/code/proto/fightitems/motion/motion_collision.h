// Fight items of the motion group: DetectObbCollisionCondition, HitSurfaceCondition (unit 0x10149DC0 - 0x1014A890; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_COLLISION_H
#define PROTO_FIGHTITEMS_MOTION_COLLISION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
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

					int surface;  // +0xC
					bool hitSurface;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gHitSurfaceConditionProperties;
			fight::ConditionFactory* CreateHitSurfaceConditionFactory(const char* name);
			void RegisterHitSurfaceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
