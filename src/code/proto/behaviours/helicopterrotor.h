// proto::HelicopterRotorAnimationBehaviour (RTTI and reflection names; base engine::Behaviour) and the rotors it turns
// (proto::Rotor with its proto::RotorParams): the joints of a rotor, the primitive groups of its geometry and of its
// blurred shader, the speeds between which they fade and the axis it turns about. Unit 0x1030FFC0 - 0x10312800 (no
// assert path; the file name is a guess). The reflected names are original, the rest is guessed; the reflection and the
// class infos are reconstructed, the animation code and the constructors are left to the engine.
#ifndef PROTO_BEHAVIOURS_HELICOPTERROTOR_H
#define PROTO_BEHAVIOURS_HELICOPTERROTOR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/vector.h"
#include "code/proto/arrayhelper.h"

namespace proto
{
	class HelicopterSolverGenericProperties;

	// How one rotor turns (0x38 bytes)
	class RotorParams
	{
	public:
		RotorParams(); //@0x10312150
		// 0x10310D00 / 0x10310C20 are the out-of-line copies of these; the containers' code has them inline
		RotorParams(const RotorParams& other)
			: jointNames(other.jointNames), geoPrimGroup(other.geoPrimGroup), shaderPrimGroup(other.shaderPrimGroup)
		{
			fadeStart = other.fadeStart;
			fadeEnd = other.fadeEnd;
			speed = other.speed;
			axisOfRotation.x = other.axisOfRotation.x;
			axisOfRotation.y = other.axisOfRotation.y;
			axisOfRotation.z = other.axisOfRotation.z;
		}
		RotorParams& operator=(const RotorParams& other)
		{
			jointNames = other.jointNames;
			geoPrimGroup = other.geoPrimGroup;
			shaderPrimGroup = other.shaderPrimGroup;
			fadeStart = other.fadeStart;
			fadeEnd = other.fadeEnd;
			speed = other.speed;
			axisOfRotation.x = other.axisOfRotation.x;
			axisOfRotation.y = other.axisOfRotation.y;
			axisOfRotation.z = other.axisOfRotation.z;
			return *this;
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		JointNameArray jointNames;  // +0
		int unknownC;
		core::Name<core::CaseSensitiveKey> geoPrimGroup;  // +0x10
		core::Name<core::CaseSensitiveKey> shaderPrimGroup;  // +0x18
		float fadeStart;  // +0x20
		float fadeEnd;  // +0x24
		float speed;  // +0x28
		math::Vector axisOfRotation;  // +0x2C
	};

	// One rotor of a helicopter (0x58 bytes)
	class Rotor
	{
	public:
		typedef container::ArrayDynamic<int, container::AllocatorNew> IndexArray;

		Rotor(); //@0x103121C0
		// 0x10310ED0 / 0x10310CC0 are the out-of-line copies of these
		Rotor(const Rotor& other) : unknown0(other.unknown0), rotorParams(other.rotorParams)
		{
			unknown48 = other.unknown48;
			unknown4C = other.unknown4C;
			unknown50 = other.unknown50;
		}
		Rotor& operator=(const Rotor& other)
		{
			unknown0 = other.unknown0;
			rotorParams = other.rotorParams;
			unknown48 = other.unknown48;
			unknown4C = other.unknown4C;
			unknown50 = other.unknown50;
			return *this;
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		IndexArray unknown0;
		int unknownC;
		RotorParams rotorParams;  // +0x10
		bool unknown48;
		float unknown4C;
		float unknown50;
		int unknown54;
	};

	// Turns the rotors of a helicopter
	class HelicopterRotorAnimationBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<Rotor, container::AllocatorNew> RotorArray;

		explicit HelicopterRotorAnimationBehaviour(engine::GameObject* newOwner); //@0x10311600
		static content::ClassInfo* GetClassInfo(); //@0x1030FFC0
		static content::MemberList* GetMembers();

		RotorArray rotors;  // +0xC
		int unknown18;
		float unknown1C;
		bool unknown20;
		HelicopterSolverGenericProperties* genericProperties;  // +0x24
	};
}

#endif
