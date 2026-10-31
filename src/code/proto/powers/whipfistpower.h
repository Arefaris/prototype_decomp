// proto::WhipFistPower (RTTI and reflection names; base proto::Power): the whip arm: a chain of segments between a
// start and an end joint that the power stretches towards a target. Unit 0x1008C970 - 0x100911E0 (no assert path;
// directory and file name are guesses). The reflected names are original, the rest is guessed; only the
// reflection is reconstructed.
#ifndef PROTO_POWERS_WHIPFISTPOWER_H
#define PROTO_POWERS_WHIPFISTPOWER_H

#include "code/core/name.h"
#include "code/engine/render/drawablearchetype.h"
#include "code/math/vector.h"
#include "code/proto/powers/power.h"

namespace proto
{
	class WhipFistPower : public Power
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 14 (0x1008CB30)
		virtual bool GetMessageMask(unsigned int* mask);

		unsigned char unknownC[4];
		int segmentCount;  // +0x10
		unsigned char unknown14[0x10];
		int fixedSegmentCount;  // +0x24
		unsigned char unknown28[8];
		core::Name<core::CaseSensitiveKey> preStartJoint;  // +0x30
		core::Name<core::CaseSensitiveKey> startJoint;  // +0x38
		core::Name<core::CaseSensitiveKey> endJoint;  // +0x40
		float segmentLength;  // +0x48
		unsigned char unknown4C[0x98];
		int moveEndJoint;  // +0xE4
		math::Vector endJointRotationOffset;  // +0xE8
		unsigned char unknownF4[0x30];
		engine::render::DrawableArchetype* segmentDrawable;  // +0x124
		unsigned char unknown128[8];
	};
}

#endif
