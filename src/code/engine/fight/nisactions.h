// The actions of the non-interactive sequence, subtitle and object light group tracks (unit 0x108EF6E0 - 0x108F0240,
// no assert path; file name guessed). The tracks are in nistracks.cpp.
#ifndef ENGINE_FIGHT_NISACTIONS_H
#define ENGINE_FIGHT_NISACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/nistracks.h"

namespace engine
{
	// 0x108EF6F0 / 0x108EF720: this unit's copies of the helpers that store and release a reference counted pointer
	void AssignNISRef(core::IRefCount** slot, core::IRefCount* value);
	void ReleaseNISRef(core::IRefCount** slot);

	// RTTI: engine::NISExecuteAction (9 vftable slots, size 0x30): plays a non-interactive sequence on an object
	class NISExecuteAction : public fight::Action
	{
	public:
		// 0x108EF840: the object is looked up by name
		NISExecuteAction(NISExecuteTrack* newTrack, core::IRefCount* newOwner, fight::Name objectName);
		// 0x108EF7B0
		virtual ~NISExecuteAction();

		// vftable slot 5 (0x108EF920)
		virtual bool Slot5(int arg, float value);

		core::Link<NISExecuteTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		core::IRefCount* owner;  // +0x2C
	};

	// RTTI: engine::SubTitleAction (9 vftable slots, size 0x2C): shows the track's subtitle
	class SubTitleAction : public fight::Action
	{
	public:
		// 0x108EFB60
		SubTitleAction(SubTitleTrack* newTrack, core::IRefCount* owner);
		// 0x108EFAD0
		virtual ~SubTitleAction();

		// vftable slot 5 (0x108EFBD0) and slot 6 (0x108EFA40)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<SubTitleTrack> link;  // +0x1C
		int subtitle;  // +0x28
	};

	// RTTI: engine::SetObjectLightGroupAction (9 vftable slots, size 0x2C): puts an object in the track's light group
	class SetObjectLightGroupAction : public fight::Action
	{
	public:
		// 0x108EFEA0
		SetObjectLightGroupAction(SetObjectLightGroupTrack* newTrack, GameObjectHandle newTarget);
		// 0x108EFF30: the object is looked up by name
		SetObjectLightGroupAction(SetObjectLightGroupTrack* newTrack, fight::Name objectName);
		// 0x108EFD70
		virtual ~SetObjectLightGroupAction();

		// vftable slot 5 (0x108EFFA0) and slot 6 (0x108EFDA0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<SetObjectLightGroupTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};
}

#endif
