// GMatrix2D of the Scaleform GFx library inside the engine DLL: a 2 by 3 matrix of floats (the last column is the
// translation). Names are guesses (the RTTI has none; the labels of the functions give the class).
#ifndef GFX_GMATRIX_H
#define GFX_GMATRIX_H

class GMatrix2D
{
public:
	// 0x1095CAF0
	GMatrix2D();
	// 0x1095CB00: copies another matrix
	void SetMatrix(const GMatrix2D& other);
	// 0x1095CB30: the scales, the shears and the translation
	void SetMatrix(float sx, float shx, float shy, float sy, float tx, float ty);
	// 0x1095CB80: moves the translation
	GMatrix2D& Translate(float x, float y);
	// 0x10965FD0
	void SetIdentity();

	float M[2][3];
};

#endif
