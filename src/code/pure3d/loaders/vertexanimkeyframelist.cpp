// pure3d::VertexAnimKeyFrameList and the reader of the old vertex animation chunk (unit around 0x10775290 -
// 0x10777000; the file name is a guess). Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/loaders/drawableloaders.h"

// This unit's copies of the reference helpers for the old key frame list

// FUNCTION: ENGINE 0x10775610
template void core::RefAssign<pure3d::OldVertexAnimKeyFrameList>(pure3d::OldVertexAnimKeyFrameList*& pointer,
	pure3d::OldVertexAnimKeyFrameList* object);

// FUNCTION: ENGINE 0x10775640
template void core::SafeRelease<pure3d::OldVertexAnimKeyFrameList>(pure3d::OldVertexAnimKeyFrameList*& object);

namespace pure3d
{
	// FUNCTION: ENGINE 0x107752F0
	VertexAnimKeyFrameListReader::VertexAnimKeyFrameListReader()
	{
	}

	// FUNCTION: ENGINE 0x10775300
	VertexAnimKeyFrameListReader::~VertexAnimKeyFrameListReader()
	{
	}

	// FUNCTION: ENGINE 0x107758C0
	unsigned int VertexAnimKeyFrameList::GetCount()
	{
		return keysEnd - keysBegin;
	}
}
