// pure3d::VertexOffsetExpressionMixer (unit around 0x107315F0 - 0x10731900, with its loader; file name guessed from
// the class). Names are guesses.
#include "code/pure3d/primitive.h"

namespace pure3d
{
	class Expression
	{
	public:
		// 0x1073F220
		void Prepare();
	};

	// FUNCTION: ENGINE 0x10731700
	void VertexOffsetExpressionMixer::Apply(Expression* expression, ExpressionState* state)
	{
		expression->Prepare();
		Mix(expression, state);
	}
}
