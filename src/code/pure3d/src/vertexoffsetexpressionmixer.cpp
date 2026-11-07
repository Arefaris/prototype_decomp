// pure3d::VertexOffsetExpressionMixer (unit around 0x107315F0 - 0x10731900, with its loader; file name guessed from
// the class). Names are guesses.
#include <new>

#include "code/pure3d/expressiongroup.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10731AA0
	VertexOffsetExpressionMixer::~VertexOffsetExpressionMixer()
	{
	}

	// FUNCTION: ENGINE 0x10731700
	void VertexOffsetExpressionMixer::Apply(VertexOffsetList* expression, VertexAnimKeyFrameList* state)
	{
		expression->Prepare();
		Mix(expression, state);
	}
}
