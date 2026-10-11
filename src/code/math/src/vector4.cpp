// Vector4 and the Matrix wrappers that take it (one original unit, 0x107DD200-0x107DD690). The wrappers copy
// their Vector4 argument into a local Vector member by member before calling the Vector overloads in matrix.cpp;
// that copy is what the compiler saw.
#include <math.h>

#include "code/math/matrix.h"
#include "code/math/vector4.h"

namespace math
{
	// FUNCTION: ENGINE 0x107DD1A0
	int Vector4::IsClose(const Vector4& other, float tolerance) const
	{
		return fabsf(x - other.x) <= tolerance && fabsf(y - other.y) <= tolerance && fabsf(z - other.z) <= tolerance
			&& fabsf(w - other.w) <= tolerance;
	}

	// FUNCTION: ENGINE 0x107DD200
	void Vector4::Transform(const Matrix& m)
	{
		Vector4 result;
		m.Transform(*this, result);
		x = result.x;
		y = result.y;
		z = result.z;
		w = result.w;
	}

	// FUNCTION: ENGINE 0x107DD250
	void Vector4::Transform(const Vector4& v, const Matrix& m)
	{
		m.Transform(v, *this);
	}

	// FUNCTION: ENGINE 0x107DD270
	void Vector4::Rotate(const Matrix& m)
	{
		Vector result;
		m.Rotate(*this, result);
		x = result.x;
		y = result.y;
		z = result.z;
	}

	// FUNCTION: ENGINE 0x107DD2B0
	unsigned int Vector4::Pack() const
	{
		return ((((((int)w << 10) | ((int)(z * 511.0f) & 0x3FF)) << 10) | ((int)(y * 511.0f) & 0x3FF)) << 10)
			| ((int)(x * 511.0f) & 0x3FF);
	}

	// FUNCTION: ENGINE 0x107DD310
	void Vector4::Unpack(unsigned int packed)
	{
		int ix = packed & 0x3ff;
		int iy = (packed >> 10) & 0x3ff;
		int iz = (packed >> 20) & 0x3ff;
		int iw = packed >> 30;
		if (ix & 0x200) ix |= 0xfffffc00;
		if (iy & 0x200) iy |= 0xfffffc00;
		if (iz & 0x200) iz |= 0xfffffc00;
		if (iw & 2) iw |= 0xfffffffc;
		x = ix * (1.0f / 511.0f);
		y = iy * (1.0f / 511.0f);
		z = iz * (1.0f / 511.0f);
		w = (float)iw;
	}

	// FUNCTION: ENGINE 0x107DD3B0
	void Matrix::Reset()
	{
		Identity();
	}

	// FUNCTION: ENGINE 0x107DD3C0
	void Matrix::SetTranslation(const Vector4& v)
	{
		Vector t;
		t.x = v.x;
		t.y = v.y;
		t.z = v.z;
		SetTranslation(t);
	}

	// FUNCTION: ENGINE 0x107DD400
	void Matrix::SetPosition(const Vector4& v)
	{
		SetTranslation(v);
	}

	// FUNCTION: ENGINE 0x107DD410
	void Matrix::SetRows(const Vector4& v)
	{
		float values[3];
		values[0] = v.x;
		values[1] = v.y;
		values[2] = v.z;
		int i = 0;
		do
		{
			m[i][0] = values[i];
			m[i][1] = values[i];
			m[i][2] = values[i];
			i++;
		}
		while (i < 3);
	}

	// FUNCTION: ENGINE 0x107DD470
	void Matrix::SetRowsLerp(float t, const Vector4& v)
	{
		Vector s;
		s.x = v.x;
		s.y = v.y;
		s.z = v.z;
		float u = 1.0f - t;
		m[0][0] = u * s.x + t; m[0][1] = u * s.x; m[0][2] = u * s.x;
		m[1][0] = u * s.y; m[1][1] = u * s.y + t; m[1][2] = u * s.y;
		m[2][0] = u * s.z; m[2][1] = u * s.z; m[2][2] = u * s.z + t;
	}

	// FUNCTION: ENGINE 0x107DD4F0
	void Matrix::SetScale(const Vector4& s)
	{
		Vector t;
		t.x = s.x;
		t.y = s.y;
		t.z = s.z;
		Scale(t.x, t.y, t.z);
	}

	// FUNCTION: ENGINE 0x107DD520
	void Matrix::TransformPoint(const Vector4& v, Vector4& out) const
	{
		Vector t;
		Vector result;
		t.x = v.x;
		t.y = v.y;
		t.z = v.z;
		Transform(t, result);
		out.x = result.x;
		out.y = result.y;
		out.z = result.z;
		out.w = v.w;
	}

	// FUNCTION: ENGINE 0x107DD590
	Matrix& Matrix::GetMatrix()
	{
		return *this;
	}

	// FUNCTION: ENGINE 0x107DD5A0
	void Matrix::SetTranslation(float x, float y, float z)
	{
		SetTranslation(Vector4(x, y, z, 1.0f));
	}

	// FUNCTION: ENGINE 0x107DD5F0
	void Matrix::SetPosition(float x, float y, float z)
	{
		SetTranslation(x, y, z);
	}

	// FUNCTION: ENGINE 0x107DD620
	void Matrix::SetScale(float x, float y, float z)
	{
		SetScale(Vector4(x, y, z, 1.0f));
	}

	// FUNCTION: ENGINE 0x107DD670
	void Matrix::SetScale(float s)
	{
		SetScale(s, s, s);
	}

	// FUNCTION: ENGINE 0x107DD690
	void Matrix::SetHueRotation(float angle, const Vector4& luminance)
	{
		Matrix rx;
		Matrix ry;
		rx.Identity();
		ry.Identity();
		// rotate the grey vector onto +Z
		float mag = sqrt(2.0);
		float xrs = 1.0f / mag;
		float xrc = 1.0f / mag;
		rx.m[1][1] = xrc;
		rx.m[1][2] = xrs;
		rx.m[2][1] = -xrs;
		rx.m[2][2] = xrc;
		float inv = 1.0 / sqrt(3.0);
		float yrs = -1.0f * inv;
		float yrc = mag * inv;
		ry.m[0][0] = yrc;
		ry.m[0][2] = -yrs;
		ry.m[2][0] = yrs;
		ry.m[2][2] = yrc;
		Matrix result;
		result.Identity();
		result.Multiply(result, rx);
		result.Multiply(result, ry);
		// shear the space to make the luminance plane horizontal
		Vector l;
		l.x = luminance.x;
		l.y = luminance.y;
		l.z = luminance.z;
		Vector t;
		result.Transform(l, t);
		float zsx = t.x / t.z;
		float zsy = t.y / t.z;
		Matrix shear;
		shear.Identity();
		shear.m[0][2] = zsx;
		shear.m[1][2] = zsy;
		result.Multiply(result, shear);
		// rotate the hue
		Matrix rz;
		rz.Identity();
		rz.RotationZ(angle);
		result.Multiply(result, rz);
		// unshear, then rotate the grey vector back
		shear.Identity();
		shear.m[0][2] = -zsx;
		shear.m[1][2] = -zsy;
		result.Multiply(result, shear);
		ry.m[0][0] = yrc;
		ry.m[0][2] = yrs;
		ry.m[2][0] = -yrs;
		ry.m[2][2] = yrc;
		result.Multiply(result, ry);
		rx.m[1][1] = xrc;
		rx.m[1][2] = -xrs;
		rx.m[2][1] = xrs;
		rx.m[2][2] = xrc;
		result.Multiply(result, rx);
		*this = result;
	}

	// FUNCTION: ENGINE 0x107DD970
	void Matrix::Concatenate(Matrix& other)
	{
		Multiply(*this, other.GetMatrix());
	}

	// FUNCTION: ENGINE 0x107DD990
	void Matrix::Concatenate(Matrix& a, Matrix& b)
	{
		Multiply(a.GetMatrix(), b.GetMatrix());
	}

	// FUNCTION: ENGINE 0x107DD9B0
	void Matrix::SetPosition(float s)
	{
		SetPosition(s, s, s);
	}
}
