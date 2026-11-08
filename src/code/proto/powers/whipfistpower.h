// proto::WhipFistPower (RTTI and reflection names; base proto::Power): the whip arm: a chain of segments between a
// start and an end joint that the power stretches towards a target. Unit 0x1008C970 - 0x100911E0 (no assert path;
// directory and file name are guesses). The reflected names are original, the rest is guessed; only the
// reflection is reconstructed.
#ifndef PROTO_POWERS_WHIPFISTPOWER_H
#define PROTO_POWERS_WHIPFISTPOWER_H

#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/render/async/drawable.h"
#include "code/engine/render/drawablearchetype.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/proto/powers/power.h"

namespace proto
{
	// One segment of the whip (0x20 bytes; guesses): seven floats of state and the drawable that shows it
	struct WhipFistSegment
	{
		// 0x1008C9B0
		WhipFistSegment();
		// 0x1008C9F0
		~WhipFistSegment();

		float unknown0;
		float unknown4;
		float unknown8;
		float unknownC;
		float unknown10;
		float unknown14;
		float unknown18;
		engine::render::Drawable drawable;  // +0x1C
	};

	// Eight words behind the whip's joint offset (0x20 bytes; the engine zeroes them in the constructors, 0x1008CA70)
	struct WhipFistChain
	{
		// 0x1008CA70
		WhipFistChain();

		float unknown0;
		float unknown4;
		float unknown8;
		float unknownC;
		float unknown10;
		float unknown14;
		float unknown18;
		float unknown1C;
	};

	class WhipFistPower : public Power
	{
	public:
		// 0x1008CFD0
		WhipFistPower();
		// 0x1008D190
		WhipFistPower(const WhipFistPower& other);
		// 0x1008D380
		virtual ~WhipFistPower();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 7 (0x1008D420), 9 (0x1008E040, not reconstructed), 10 (0x1008EE00, not reconstructed), 11 (0x100910B0, not reconstructed)
		// and 14 (0x1008CB30); slots 8, 12 and 13 are the base class's
		virtual Power* Clone();
		virtual void Slot9(float unknown);
		virtual void Slot10(float dt);
		virtual void Slot11(engine::Message* message);
		virtual bool GetMessageMask(unsigned int* mask);

		WhipFistSegment* segments;  // +0xC (an array allocated with new[])
		int segmentCount;  // +0x10
		int unknown14;
		int unknown18;
		int unknown1C;
		void* unknown20;  // an array allocated with new[]
		int fixedSegmentCount;  // +0x24
		int unknown28;
		float unknown2C;
		core::Name<core::CaseSensitiveKey> preStartJoint;  // +0x30
		core::Name<core::CaseSensitiveKey> startJoint;  // +0x38
		core::Name<core::CaseSensitiveKey> endJoint;  // +0x40
		float segmentLength;  // +0x48
		float unknown4C;
		float unknown50;
		float unknown54;
		float unknown58;
		float unknown5C;
		float unknown60;
		engine::HandleBase unknown64;
		float unknown68;
		float unknown6C;
		float unknown70;
		bool unknown74;
		float unknown78;
		float unknown7C;
		float unknown80;
		float unknown84;
		float unknown88;
		bool unknown8C;
		float unknown90;
		float unknown94;
		float unknown98;
		float unknown9C;
		float unknownA0;
		math::Matrix unknownA4;
		int moveEndJoint;  // +0xE4
		math::Vector endJointRotationOffset;  // +0xE8
		WhipFistChain chain;  // +0xF4
		int unknown114;
		int unknown118;
		int unknown11C;
		int unknown120;
		engine::render::DrawableArchetype* segmentDrawable;  // +0x124
		float unknown128;
		int unknown12C;
	};
}

#endif
