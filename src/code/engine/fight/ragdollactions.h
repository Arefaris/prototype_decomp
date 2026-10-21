// The actions of the ragdoll tracks (the code sits in 0x1092DD60 - 0x1092FDF0, no assert path; file name guessed). The
// tracks and the conditions are in ragdoll.cpp.
#ifndef ENGINE_FIGHT_RAGDOLLACTIONS_H
#define ENGINE_FIGHT_RAGDOLLACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/ragdoll.h"

namespace engine
{
	// RTTI: engine::RagdollStoreJointVelocitiesAction (9 vftable slots, size 0x20): the track has no members the action reads
	class RagdollStoreJointVelocitiesAction : public fight::Action
	{
	public:
		// 0x1092E030
		explicit RagdollStoreJointVelocitiesAction(GameObjectHandle newTarget);
		// 0x1092E050
		virtual ~RagdollStoreJointVelocitiesAction();

		// vftable slot 5 (0x1092E980) and slot 6 (0x1092E9F0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		GameObjectHandle target;  // +0x1C
	};

	// RTTI: engine::UnpowerRagdollAction (9 vftable slots, size 0x20)
	class UnpowerRagdollAction : public fight::Action
	{
	public:
		// 0x1092E120
		explicit UnpowerRagdollAction(GameObjectHandle newTarget);
		// 0x1092E140
		virtual ~UnpowerRagdollAction();

		// vftable slot 5 (0x1092EB30), 6 (0x1092E160) and 7 (0x1092E150)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		GameObjectHandle target;  // +0x1C
	};

	// RTTI: engine::EnableRagdollAction (9 vftable slots, size 0x2C)
	class EnableRagdollAction : public fight::Action
	{
	public:
		// 0x1092EF40
		EnableRagdollAction(EnableRagdollTrack* newTrack, GameObjectHandle newTarget);
		// 0x1092E840
		virtual ~EnableRagdollAction();

		// vftable slot 5 (0x1092EFD0)
		virtual bool Slot5(int arg, float value);

		core::Link<EnableRagdollTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::DisableRagdollAction (9 vftable slots, size 0x2C)
	class DisableRagdollAction : public fight::Action
	{
	public:
		// 0x1092F140
		DisableRagdollAction(DisableRagdollTrack* newTrack, GameObjectHandle newTarget);
		// 0x1092E880
		virtual ~DisableRagdollAction();

		// vftable slot 5 (0x1092F1E0) and slot 6 (0x1092E8B0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<DisableRagdollTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::DeactivateRagdollAction (9 vftable slots, size 0x2C)
	class DeactivateRagdollAction : public fight::Action
	{
	public:
		// 0x1092F970
		DeactivateRagdollAction(DeactivateRagdollTrack* newTrack, GameObjectHandle newTarget);
		// 0x1092EBC0
		virtual ~DeactivateRagdollAction();

		// vftable slot 5 (0x1092FA00) and slot 6 (0x1092EBF0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<DeactivateRagdollTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::RagdollSetKeyframeUpdatedAction (9 vftable slots, size 0x2C)
	class RagdollSetKeyframeUpdatedAction : public fight::Action
	{
	public:
		// 0x1092FA70
		RagdollSetKeyframeUpdatedAction(RagdollSetKeyframeUpdatedTrack* newTrack, GameObjectHandle newTarget);
		// 0x1092EC60
		virtual ~RagdollSetKeyframeUpdatedAction();

		// vftable slot 5 (0x1092FB00) and slot 6 (0x1092FB90)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<RagdollSetKeyframeUpdatedTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::PowerRagdollByPuppetAction (9 vftable slots, size 0x2C)
	class PowerRagdollByPuppetAction : public fight::Action
	{
	public:
		// 0x1092F800
		PowerRagdollByPuppetAction(PowerRagdollByPuppetTrack* newTrack, GameObjectHandle newTarget);
		// 0x1092EB00
		virtual ~PowerRagdollByPuppetAction();

		// vftable slot 5 (0x1092F890), 6 (0x1092E110) and 7 (0x1092E100)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<PowerRagdollByPuppetTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};
}

#endif
