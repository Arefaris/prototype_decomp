// GRenderer of the Scaleform GFx library inside the engine DLL (the unit around 0x1095DEE0; file name guessed). Names
// are guesses.
#include "code/gfx/grenderer.h"

// FUNCTION: ENGINE 0x1095DFA0
GRenderer::GRenderer()
{
}

// FUNCTION: ENGINE 0x1095DEE0
GRenderer::~GRenderer()
{
}

// FUNCTION: ENGINE 0x1095DEF0
void GRenderer::Unknown0C()
{
}

// FUNCTION: ENGINE 0x1095DF00
void GRenderer::Unknown10()
{
}

// FUNCTION: ENGINE 0x1095DF10
void GRenderer::SetMarker(const GRendererMarker* marker)
{
}

// FUNCTION: ENGINE 0x1095DF20
void GRenderer::ClearMarker()
{
}

// FUNCTION: ENGINE 0x1095DF30
bool GRenderer::HasMarker()
{
	return false;
}

// FUNCTION: ENGINE 0x1095DF40
bool GRenderer::Unknown80(int argument)
{
	return false;
}

// FUNCTION: ENGINE 0x1095DF50
void GRenderer::Unknown84(int argument)
{
}

// FUNCTION: ENGINE 0x1095DBD0 ; GRefCountBase<class GRenderer>::GRefCountBase<class GRenderer>
#pragma inline_depth(0)
GRefCountBase<GRenderer>* KeepRendererBaseConstructor()
{
	return new GRefCountBase<GRenderer>;
}
#pragma inline_depth()
