// The stream manager's unit (0x1082BEC0 - 0x1082E9xx; engine::StreamManager itself is declared in streampackage.h
// because the packages call it). No assert path names the unit, so the directory, file name and the names here are
// guesses.
#ifndef ENGINE_SYSTEM_STREAMMANAGER_H
#define ENGINE_SYSTEM_STREAMMANAGER_H

#include "code/container/arraydynamicstatic.h"

namespace engine
{
	class StreamPackage;
	class StreamTrigger;
	class TagSet;

	typedef container::ArrayDynamic<StreamPackage*, container::AllocatorCoreStatic<12, 16> > StreamPackageArray;
	typedef container::ArrayDynamic<StreamTrigger*, container::AllocatorCoreStatic<12, 16> > StreamTriggerArray;

	// What one walk of the trigger graph collects into and how far it may still go
	struct StreamCollect
	{
		StreamPackageArray* packages;
		const TagSet* tags;
		int count;
		// The deepest trigger hop that may still contribute (0: nothing is collected)
		int budget;
	};

	// 0x1082D0B0: appends the packages of triggers and of their neighbours, up to budget hops deep
	void CollectPackages(StreamCollect* collect, StreamTriggerArray* triggers, int depth);
	// 0x1082E100: brings the packages `current` holds into line with `target`: drops the ones target has not and
	// loads the first new one when its slot group takes it, or unloads the last dropped one when nothing is loading;
	// `active` records that the group's load priority is set (restricted: it may be set). Name guess.
	void UpdateStreamTransition(StreamPackageArray** target, StreamPackageArray** current, bool* active,
		bool restricted);
	// 0x1082DB20: the packages of trigger (with count == 0) and of its neighbours, into packages
	void AddTriggerPackages(StreamPackageArray* packages, StreamTrigger* trigger, const TagSet& tags, int count,
		int base);
}

#endif
