// The patch of the mgraph library (RTTI: mgraph::Patch, an entity that wraps a dynamic object): a graph of nodes that
// the audio and music code plays. Only the class itself is described so far.
#ifndef MGRAPH_PATCH_H
#define MGRAPH_PATCH_H

#include "code/om/dynamicobjectentity.h"

namespace mgraph
{
	// The format of what a patch plays (name guessed): the sample rate sits at 0x1C
	class PatchFormat
	{
	public:
		char unknown0[0x1C];
		unsigned int sampleRate;
	};

	// What a patch plays (name guessed; it is reference counted): the format sits at 8
	class PatchSource
	{
	public:
		int unknown0;
		int unknown4;
		PatchFormat* format;
	};

	class Patch : public om::DynamicObjectEntity
	{
	public:
		// 0x105BE180 is the body, taking the patch out of the pool's list
		virtual ~Patch();
		// 0x105BC710: gives the patch back to the pool of the patches
		static void operator delete(void* memory);

		char unknown48[0x4B8];
		PatchSource* source;  // 0x500
	};

	// 0x105E30A0 (name guessed): the patch of a name, null when the first entity of the name is not one
	Patch* FindPatchByName(const om::ClassName& name);
}

#endif
