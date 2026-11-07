// The branches of the fight tree that name a playback set and hold the tracks of a playback (engine::PlaybackSet,
// engine::PlaybackNode; code/engine/fight/playbackbranches.cpp; the file name is a guess, the unit starts at 0x108B0860
// and has no assert path). Names are guesses unless the RTTI gives them.
#include "code/engine/fight/playbackset.h"

namespace engine
{
	// The texts the two branch kinds register their factories under (0x111D7DC4 / 0x111D7F34)
	extern const char* const gPlaybackSetText;
	extern const char* const gPlaybackNodeText;

	// GLOBAL: ENGINE 0x113182E0
	fight::Property** gPlaybackSetProperties;
	// GLOBAL: ENGINE 0x113182F8
	fight::Property** gPlaybackNodeProperties;

	// ---- engine::PlaybackSet -----------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x108B0860
	fight::Property* PlaybackSet::GetProperty(int index)
	{
		return gPlaybackSetProperties[index];
	}

	// FUNCTION: ENGINE 0x108B0870
	void PlaybackSet::ClearProperties()
	{
		fight::FreePropertyList(&gPlaybackSetProperties);
	}

	// FUNCTION: ENGINE 0x108B0880
	bool PlaybackSet::SetOwner(GameObject* newOwner)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x108B0890
	fight::Branch* PlaybackSet::Slot10(fight::Sequencer* sequencer, void* params, int a, bool b)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x108B08A0
	bool PlaybackSet::SetLogicTreeName(const core::Name<core::CaseSensitiveKey>& value)
	{
		logicTreeName = value;
		return true;
	}

	// FUNCTION: ENGINE 0x108B08C0
	PlaybackSet::PlaybackSet()
		: unknown30(0)
	{
	}

	// FUNCTION: ENGINE 0x108B0A40
	// NONMATCHING: shrink-wrap
#ifdef NONMATCHING
	void PlaybackSet::RegisterProperties()
	{
		if (gPlaybackSetProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<PlaybackSet>("LogicTreeName", &PlaybackSet::SetLogicTreeName);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gPlaybackSetProperties);
		}
	}
#endif

	// ---- engine::PlaybackNode ----------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x108B0C00
	fight::TrackGroup* PlaybackNode::GetTracks()
	{
		return &tracks;
	}

	// FUNCTION: ENGINE 0x108B0C10
	fight::TrackGroup* PlaybackNode::GetRestore()
	{
		return &restore;
	}

	// FUNCTION: ENGINE 0x108B0C60
	fight::Property* PlaybackNode::GetProperty(int index)
	{
		return gPlaybackNodeProperties[index];
	}

	// FUNCTION: ENGINE 0x108B0C70
	void PlaybackNode::ClearProperties()
	{
		fight::FreePropertyList(&gPlaybackNodeProperties);
	}

	// FUNCTION: ENGINE 0x108B0C80
	void PlaybackNode::Slot14(fight::Branch* newParent)
	{
		fight::Branch::Slot14(newParent);
		Slot7();
	}

	// FUNCTION: ENGINE 0x108B0CA0
	fight::Branch* PlaybackNode::Slot10(fight::Sequencer* sequencer, void* params, int a, bool b)
	{
		return this;
	}

	// FUNCTION: ENGINE 0x108B0CB0
	bool PlaybackNode::Slot11(fight::Sequencer* sequencer, void* params, int a)
	{
		return sequencer->SetPending(this, (int)sequencer, (core::IRefCount*)params, a);
	}

	// FUNCTION: ENGINE 0x108B0E60
	// NONMATCHING: shrink-wrap
#ifdef NONMATCHING
	void PlaybackNode::RegisterProperties()
	{
		if (gPlaybackNodeProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyTrackGroup<PlaybackNode>("tracks", &PlaybackNode::GetTracks);
			properties[0] = property;
			property = new fight::PropertyTrackGroup<PlaybackNode>("restore", &PlaybackNode::GetRestore);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gPlaybackNodeProperties);
		}
	}
#endif

	// ---- the properties and factories --------------------------------------------------------------------------------

	template class fight::PropertyName<PlaybackSet>;
	template class fight::PropertyTrackGroup<PlaybackNode>;
	template class fight::BranchFactoryTemplate<PlaybackSet>;
	template class fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<PlaybackSet> >;
	template class fight::BranchFactoryTemplate<PlaybackNode>;
	template class fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<PlaybackNode> >;

	// FUNCTION: ENGINE 0x108B0980
	fight::BranchFactory* CreatePlaybackSetBranchFactory(const char* name)
	{
		fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<PlaybackSet> > caster;
		return fight::FindBranchFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B0E40
	fight::BranchFactory* CreatePlaybackNodeBranchFactory(const char* name)
	{
		fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<PlaybackNode> > caster;
		return fight::FindBranchFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B09A0
	void RegisterPlaybackSetBranchFactory(fight::TrackRegistry* registry)
	{
		fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<PlaybackSet> > caster;
		registry->AddFactory(fight::FindBranchFactory(gPlaybackSetText, &caster));
	}

	// FUNCTION: ENGINE 0x108B0F20
	void RegisterPlaybackNodeBranchFactory(fight::TrackRegistry* registry)
	{
		fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<PlaybackNode> > caster;
		registry->AddFactory(fight::FindBranchFactory(gPlaybackNodeText, &caster));
	}
}
