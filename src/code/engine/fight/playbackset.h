// engine::PlaybackSet and engine::PlaybackNode (RTTI names, 18 vftable slots each - the same as their base fight::Branch,
// 0x10E7B204 / 0x10E7B344): the branch of a fight tree that names a playback set, and the one that holds the tracks of a
// playback. Unit 0x108B0860 - 0x108B10A0 (no assert path; the file name is a guess); the member names are guesses.
#ifndef ENGINE_FIGHT_PLAYBACKSET_H
#define ENGINE_FIGHT_PLAYBACKSET_H

#include "code/engine/fight/branch.h"
#include "code/engine/fight/trackfactory.h"

namespace engine
{
	class GameObject;

	// RTTI: engine::PlaybackSet (0x38 bytes)
	class PlaybackSet : public fight::Branch
	{
	public:
		// 0x108B08C0
		PlaybackSet();
		// vftable slot 2 (0x108B0960 is the deleting destructor, 0x108B08F0 the body)
		virtual ~PlaybackSet();

		// vftable slot 10 (0x108B0890): runs nothing
		virtual fight::Branch* Slot10(fight::Sequencer* sequencer, void* params, int a, bool b);
		// vftable slot 0 of the Param part (0x108B0860)
		virtual fight::Property* GetProperty(int index);

		// 0x108B0880 (a stub in this build): gives the set the object it plays on
		bool SetOwner(GameObject* newOwner);
		// 0x108B08A0: the member the property writes
		bool SetLogicTreeName(const core::Name<core::CaseSensitiveKey>& value);

		// 0x108B0A40 / 0x108B0870: the properties of the class, built once / freed
		static void RegisterProperties();
		static void ClearProperties();

		core::Name<core::CaseSensitiveKey> logicTreeName;  // +0x28
		core::IRefCount* unknown30;
		int unknown34;
	};

	// RTTI: engine::PlaybackNode (0x30 bytes)
	class PlaybackNode : public fight::Branch
	{
	public:
		// 0x108B0FB0 (the engine expands it in the factory)
		PlaybackNode()
		{
		}
		// vftable slot 2 (0x108B1070 is the deleting destructor, 0x108B1010 the body; left to the engine: it leaves out the
		// stores of the vftable)
		virtual ~PlaybackNode();

		// vftable slot 10 (0x108B0CA0): the node itself
		virtual fight::Branch* Slot10(fight::Sequencer* sequencer, void* params, int a, bool b);
		// vftable slot 11 (0x108B0CB0) and 12 (0x108B0CD0, left to the engine)
		virtual bool Slot11(fight::Sequencer* sequencer, void* params, int a);
		virtual void Slot12(int a, core::IRefCount* b, fight::Sequencer* sequencer);
		// vftable slot 14 (0x108B0C80): makes another branch the parent and hands the node to its properties
		virtual void Slot14(fight::Branch* newParent);
		// vftable slot 0 of the Param part (0x108B0C60)
		virtual fight::Property* GetProperty(int index);

		// 0x108B0C00 / 0x108B0C10: the members the properties hand out
		fight::TrackGroup* GetTracks();
		fight::TrackGroup* GetRestore();

		// 0x108B0E60 / 0x108B0C70: the properties of the class, built once / freed
		static void RegisterProperties();
		static void ClearProperties();

		fight::TrackGroup tracks;  // +0x28
		fight::TrackGroup restore;  // +0x2C
	};

	// 0x113182E0 / 0x113182F8
	extern fight::Property** gPlaybackSetProperties;
	extern fight::Property** gPlaybackNodeProperties;
}

#endif
