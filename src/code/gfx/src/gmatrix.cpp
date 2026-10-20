// GMatrix2D of the Scaleform GFx library inside the engine DLL (the unit around 0x1095CAF0; file name guessed).
#include "code/gfx/gmatrix.h"

// FUNCTION: ENGINE 0x1095CAF0
GMatrix2D::GMatrix2D()
{
	SetIdentity();
}

// FUNCTION: ENGINE 0x1095CB00
void GMatrix2D::SetMatrix(const GMatrix2D& other)
{
	M[0][0] = other.M[0][0];
	M[0][1] = other.M[0][1];
	M[0][2] = other.M[0][2];
	M[1][0] = other.M[1][0];
	M[1][1] = other.M[1][1];
	M[1][2] = other.M[1][2];
}

// FUNCTION: ENGINE 0x1095CB30
void GMatrix2D::SetMatrix(float sx, float shx, float shy, float sy, float tx, float ty)
{
	M[0][0] = sx;
	M[0][1] = shx;
	M[0][2] = tx;
	M[1][0] = shy;
	M[1][1] = sy;
	M[1][2] = ty;
}

// FUNCTION: ENGINE 0x1095CB80
GMatrix2D& GMatrix2D::Translate(float x, float y)
{
	M[0][2] = x + M[0][2];
	M[1][2] = y + M[1][2];
	return *this;
}
