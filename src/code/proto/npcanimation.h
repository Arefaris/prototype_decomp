// proto::NPCAnimation, proto::NPCAnimationList and proto::NPCDrawable (RTTI and reflection names; base
// content::MetaLoadObject): the animations of a pedestrian and the drawable it is shown with. An animation names a
// pure3d animation and skeleton and plays it as a puppet; the list keeps up to twelve animations and, for each of the
// ten states a pedestrian can be in, up to three of them (the reflection names the members "state_Walking",
// "state_Walking1", "state_Walking2" and so on). Unit 0x10476A00 - 0x10479250 (no assert path; the file name is a guess).
// The reflected names are original, the rest is guessed; the reflection, the construction and the destruction are
// reconstructed, the creation of the puppets is left to the engine.
#ifndef PROTO_NPCANIMATION_H
#define PROTO_NPCANIMATION_H

#include "code/choreo/puppetmanager.h"
#include "code/container/arrayfixed.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/engine/render/drawablearchetype.h"

namespace pure3d
{
	class Animation;
	class Skeleton;
	class Pose;
}

namespace choreo
{
	class Puppet;
	class Driver;
}

namespace proto
{
	// One animation of a pedestrian (RTTI proto::NPCAnimation; 0x30 bytes)
	class NPCAnimation : public content::MetaLoadObject
	{
	public:
		// 0x104770B0
		NPCAnimation();
		// 0x10476CB0 (the deleting destructor is 0x10477110)
		virtual ~NPCAnimation();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x10476CE0): makes the pose, the puppet and the driver of the animation; slot 4 (0x10476E30):
		// gives them up again; both are left to the engine
		virtual void Slot3(int unused);
		virtual bool IsReady();
		// vftable slot 5 (0x10476A40)
		virtual bool Slot5();

		// 0x10476A50: copies the state of the puppet's pose into the pose of the animation
		void UpdatePose(float dt);

		pure3d::Animation* animation;  // +8
		pure3d::Pose* pose;  // +0xC
		choreo::Puppet* puppet;  // +0x10
		choreo::PuppetHandle puppetHandle;  // +0x14
		choreo::Driver* driver;  // +0x1C
		pure3d::Skeleton* skeleton;  // +0x20
		float startFrame;  // +0x24
		float locomotionSpeed;  // +0x28
		float animationSpeed;  // +0x2C
	};

	// The animations of a pedestrian for each of its states (RTTI proto::NPCAnimationList; 0xFC bytes)
	class NPCAnimationList : public content::MetaLoadObject
	{
	public:
		// 0x10478E20
		NPCAnimationList();
		// 0x10478D80 (the deleting destructor is 0x10478F70)
		virtual ~NPCAnimationList();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10477140: keeps the animation (once) and enters it in the list of the state; the reflection sets the
		// members through this
		void AddAnimation(int state, NPCAnimation* animation);

		// The members reach the animations through accessors that answer nothing and add what is set
		NPCAnimation* GetStateWalking() const { return 0; }
		void SetStateWalking(NPCAnimation* a) { AddAnimation(2, a); }
		NPCAnimation* GetStateWalking1() const { return 0; }
		void SetStateWalking1(NPCAnimation* a) { AddAnimation(2, a); }
		NPCAnimation* GetStateWalking2() const { return 0; }
		void SetStateWalking2(NPCAnimation* a) { AddAnimation(2, a); }
		NPCAnimation* GetStateStanding() const { return 0; }
		void SetStateStanding(NPCAnimation* a) { AddAnimation(1, a); }
		NPCAnimation* GetStateStanding1() const { return 0; }
		void SetStateStanding1(NPCAnimation* a) { AddAnimation(1, a); }
		NPCAnimation* GetStateStanding2() const { return 0; }
		void SetStateStanding2(NPCAnimation* a) { AddAnimation(1, a); }
		NPCAnimation* GetStateRunning() const { return 0; }
		void SetStateRunning(NPCAnimation* a) { AddAnimation(3, a); }
		NPCAnimation* GetStateRunning1() const { return 0; }
		void SetStateRunning1(NPCAnimation* a) { AddAnimation(3, a); }
		NPCAnimation* GetStateRunning2() const { return 0; }
		void SetStateRunning2(NPCAnimation* a) { AddAnimation(3, a); }
		NPCAnimation* GetStateFloat() const { return 0; }
		void SetStateFloat(NPCAnimation* a) { AddAnimation(4, a); }
		NPCAnimation* GetStateFloat1() const { return 0; }
		void SetStateFloat1(NPCAnimation* a) { AddAnimation(4, a); }
		NPCAnimation* GetStateFloat2() const { return 0; }
		void SetStateFloat2(NPCAnimation* a) { AddAnimation(4, a); }
		NPCAnimation* GetStateDead() const { return 0; }
		void SetStateDead(NPCAnimation* a) { AddAnimation(5, a); }
		NPCAnimation* GetStateDead1() const { return 0; }
		void SetStateDead1(NPCAnimation* a) { AddAnimation(5, a); }
		NPCAnimation* GetStateDead2() const { return 0; }
		void SetStateDead2(NPCAnimation* a) { AddAnimation(5, a); }
		NPCAnimation* GetStateCower() const { return 0; }
		void SetStateCower(NPCAnimation* a) { AddAnimation(6, a); }
		NPCAnimation* GetStateCower1() const { return 0; }
		void SetStateCower1(NPCAnimation* a) { AddAnimation(6, a); }
		NPCAnimation* GetStateCower2() const { return 0; }
		void SetStateCower2(NPCAnimation* a) { AddAnimation(6, a); }
		NPCAnimation* GetStateLowMoraleWalking() const { return 0; }
		void SetStateLowMoraleWalking(NPCAnimation* a) { AddAnimation(7, a); }
		NPCAnimation* GetStateLowMoraleWalking1() const { return 0; }
		void SetStateLowMoraleWalking1(NPCAnimation* a) { AddAnimation(7, a); }
		NPCAnimation* GetStateLowMoraleWalking2() const { return 0; }
		void SetStateLowMoraleWalking2(NPCAnimation* a) { AddAnimation(7, a); }
		NPCAnimation* GetStateLowMoraleStanding() const { return 0; }
		void SetStateLowMoraleStanding(NPCAnimation* a) { AddAnimation(9, a); }
		NPCAnimation* GetStateLowMoraleStanding1() const { return 0; }
		void SetStateLowMoraleStanding1(NPCAnimation* a) { AddAnimation(9, a); }
		NPCAnimation* GetStateLowMoraleStanding2() const { return 0; }
		void SetStateLowMoraleStanding2(NPCAnimation* a) { AddAnimation(9, a); }
		NPCAnimation* GetStateSpawnDead() const { return 0; }
		void SetStateSpawnDead(NPCAnimation* a) { AddAnimation(10, a); }
		NPCAnimation* GetStateSpawnDead1() const { return 0; }
		void SetStateSpawnDead1(NPCAnimation* a) { AddAnimation(10, a); }
		NPCAnimation* GetStateSpawnDead2() const { return 0; }
		void SetStateSpawnDead2(NPCAnimation* a) { AddAnimation(10, a); }
		NPCAnimation* GetStateRubbernecking() const { return 0; }
		void SetStateRubbernecking(NPCAnimation* a) { AddAnimation(11, a); }
		NPCAnimation* GetStateRubbernecking1() const { return 0; }
		void SetStateRubbernecking1(NPCAnimation* a) { AddAnimation(11, a); }
		NPCAnimation* GetStateRubbernecking2() const { return 0; }
		void SetStateRubbernecking2(NPCAnimation* a) { AddAnimation(11, a); }

		container::ArrayFixed<NPCAnimation*, 12> animations;  // +8: the animations, each held once
		container::ArrayFixed<int, 3> states[12];  // +0x3C: for each state the indices into the animations
	};

	// The drawable a pedestrian is shown with and the animations it plays (RTTI proto::NPCDrawable; 0x10 bytes)
	class NPCDrawable : public content::MetaLoadObject
	{
	public:
		// 0x10478F20
		NPCDrawable();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		engine::render::DrawableArchetype* drawable;  // +8
		NPCAnimationList* animationList;  // +0xC
	};
}

#endif
