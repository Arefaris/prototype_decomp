// pure3d::Camera: the view volume, its planes, projection settings and the window. See camera.h for the model;
// names are guesses.
#include "code/math/sincos.h"
#include "code/math/worldbounds.h"
#include "code/pure3d/camera.h"
#include <math.h>

namespace pure3d
{
	// FUNCTION: ENGINE 0x106DC810
	CameraWindow::CameraWindow()
	{
		enabled = false;
		values[0] = 0.0f;
		values[1] = 0.0f;
		values[2] = 0.0f;
		values[3] = 0.0f;
		flag = true;
	}

	// FUNCTION: ENGINE 0x106DC840
	Camera::~Camera()
	{
	}

	// FUNCTION: ENGINE 0x106DC850
	// NONMATCHING: the window copy: ours loads the second word before the address (68.6 %)
#ifdef NONMATCHING
	void Camera::CopyFrom(const Camera* other)
	{
		if (other)
		{
			unknown10 = other->unknown10;
			fov = other->fov;
			unknown18 = other->unknown18;
			unknown1C = other->unknown1C;
			minZ = other->minZ;
			maxZ = other->maxZ;
			halfX = other->halfX;
			halfY = other->halfY;
			plane0x = other->plane0x;
			plane0z = other->plane0z;
			plane1x = other->plane1x;
			plane1z = other->plane1z;
			plane2y = other->plane2y;
			plane2z = other->plane2z;
			plane3y = other->plane3y;
			plane3z = other->plane3z;
			matrix = other->matrix;
			world = other->world;
			window = other->window;
			width = 0.0f;
			height = 0.0f;
		}
	}
#endif

	// FUNCTION: ENGINE 0x106DC940
	void Camera::UpdatePlanes()
	{
		if (unknown10 == 0)
		{
			float sinA, cosA, sinB, cosB;
			math::SinCos(fov * 0.5f, &sinA, &cosA);
			math::SinCos(unknown18 * 0.5f, &sinB, &cosB);
			float minimum = math::WORLD_MIN;
			plane0x = minimum - cosA;
			plane0z = minimum - sinA;
			plane1z = minimum - sinA;
			plane1x = cosA;
			plane2y = cosB;
			plane2z = minimum - sinB;
			plane3y = minimum - cosB;
			plane3z = minimum - sinB;
		}
	}

	// FUNCTION: ENGINE 0x106DCA20
	void Camera::SetNearPlane(float distance)
	{
		minZ = distance;
	}

	// FUNCTION: ENGINE 0x106DCA30
	void Camera::SetFarPlane(float distance)
	{
		maxZ = distance;
	}

	// FUNCTION: ENGINE 0x106DCA40
	// NONMATCHING: the box-volume branches of the bottom / top / side planes are merged by the engine through other registers (61.9 %)
#ifdef NONMATCHING
	void Camera::GetPlane(int side, math::Plane* plane)
	{
		switch (side)
		{
		case 1:
			plane->normal.x = 0.0f;
			plane->normal.y = 0.0f;
			plane->normal.z = -1.0f;
			plane->d = minZ;
			break;
		case 2:
			plane->normal.x = 0.0f;
			plane->normal.y = 0.0f;
			plane->normal.z = 1.0f;
			plane->d = math::WORLD_MIN - maxZ;
			break;
		case 4:
			if (unknown10 == 0)
			{
				float y = plane2y;
				float z = plane2z;
				plane->normal.x = 0.0f;
				plane->normal.y = y;
				plane->normal.z = z;
				plane->d = 0.0f;
			}
			else
			{
				float y = 1.0f;
				plane->normal.x = 0.0f;
				plane->normal.z = 0.0f;
				plane->normal.y = y;
				plane->d = math::WORLD_MIN - halfY;
			}
			break;
		case 8:
			if (unknown10 == 0)
			{
				float y = plane3y;
				float z = plane3z;
				plane->normal.x = 0.0f;
				plane->normal.y = y;
				plane->normal.z = z;
				plane->d = 0.0f;
			}
			else
			{
				float y = -1.0f;
				plane->normal.x = 0.0f;
				plane->normal.z = 0.0f;
				plane->normal.y = y;
				plane->d = math::WORLD_MIN - halfY;
			}
			break;
		case 0x10:
			if (unknown10 == 0)
			{
				plane->normal.x = plane0x;
				plane->normal.y = 0.0f;
				plane->normal.z = plane0z;
				plane->d = 0.0f;
			}
			else
			{
				plane->normal.x = -1.0f;
				plane->normal.y = 0.0f;
				plane->normal.z = 0.0f;
				plane->d = math::WORLD_MIN - halfX;
			}
			break;
		case 0x20:
			if (unknown10 == 0)
			{
				plane->normal.x = plane1x;
				plane->normal.y = 0.0f;
				plane->normal.z = plane1z;
				plane->d = 0.0f;
			}
			else
			{
				plane->normal.x = 1.0f;
				plane->normal.y = 0.0f;
				plane->normal.z = 0.0f;
				plane->d = math::WORLD_MIN - halfX;
			}
			break;
		}
	}
#endif

	// FUNCTION: ENGINE 0x106DCC00
	// NONMATCHING: the engine keeps this in ecx across its in-unit call of GetPlane (26.3 %, GetPlane is NONMATCHING)
#ifdef NONMATCHING
	void Camera::GetWorldPlane(int side, math::Plane* plane)
	{
		GetPlane(side, plane);
		plane->Transform(world);
	}
#endif

	// FUNCTION: ENGINE 0x106DCC20
	// EQUIVALENT: same operations in the same order; the engine merges both branches' failing exits into one block
	// and cross-jumps their last test, ours keeps a second exit at the end of the second branch
	bool Camera::Contains(const math::Vector& point, float radius) const
	{
		if (unknown10 == 0)
		{
			if (point.z + radius < minZ)
			{
				return false;
			}
			if (point.z - radius > maxZ)
			{
				return false;
			}
			if (plane0x * point.x + plane0z * point.z > radius)
			{
				return false;
			}
			if (plane1x * point.x + plane1z * point.z > radius)
			{
				return false;
			}
			if (plane2y * point.y + plane2z * point.z > radius)
			{
				return false;
			}
			if (plane3y * point.y + plane3z * point.z > radius)
			{
				return false;
			}
		}
		else
		{
			if (point.z + radius < minZ)
			{
				return false;
			}
			if (point.z - radius > maxZ)
			{
				return false;
			}
			if (point.x + radius < math::WORLD_MIN - halfX)
			{
				return false;
			}
			if (point.x - radius > halfX)
			{
				return false;
			}
			if (point.y + radius < math::WORLD_MIN - halfY)
			{
				return false;
			}
			if (point.y - radius > halfY)
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x106DCD70
	bool Camera::IsPointVisible(const math::Vector* point, float radius)
	{
		math::Vector local;
		matrix.Transform(*point, local);
		return Contains(local, radius);
	}

	// FUNCTION: ENGINE 0x106DCDB0
	unsigned int Camera::Classify(const math::Vector* point)
	{
		unsigned int result = 0;
		float x = point->x;
		float y = point->y;
		float z = point->z;
		float limitX = halfX;
		float limitY = halfY;
		if (unknown10 == 0)
		{
			limitX = limitX * z;
			limitY = limitY * z;
		}
		if (z > maxZ)
		{
			result = 2;
		}
		else if (minZ > z)
		{
			result = 1;
		}
		if (y > limitY)
		{
			result |= 4;
		}
		else if (math::WORLD_MIN - y > limitY)
		{
			result |= 8;
		}
		if (x > limitX)
		{
			return result | 0x20;
		}
		if (math::WORLD_MIN - x > limitX)
		{
			result |= 0x10;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x106DCE40
	void Camera::SetMatrix(const math::Matrix& newMatrix)
	{
		world = newMatrix;
		matrix = world;
		matrix.InvertOrthonormal();
	}

	// FUNCTION: ENGINE 0x106DCE70
	void SetViewMatrix(math::Matrix* target, const math::Vector* position, math::Vector forward, math::Vector up)
	{
		target->ClearProjection();
		target->SetBasis(forward, up);
		target->SetTranslation(*position);
	}

	// FUNCTION: ENGINE 0x106DCEA0
	void Camera::GetRayPoints(const float* screen, math::Vector* nearPoint, math::Vector* farPoint)
	{
		float x = halfX * screen[0] * 2.0f;
		float y = screen[1] * halfY * 2.0f;
		if (unknown10 == 0)
		{
			nearPoint->x = minZ * x;
			nearPoint->y = minZ * y;
			nearPoint->z = minZ;
			farPoint->x = maxZ * x;
			farPoint->y = maxZ * y;
			farPoint->z = maxZ;
			return;
		}
		nearPoint->x = x;
		nearPoint->y = y;
		nearPoint->z = minZ;
		farPoint->x = x;
		farPoint->y = y;
		farPoint->z = maxZ;
	}

	// FUNCTION: ENGINE 0x106DCF40
	void Camera::ToWorld(const math::Vector* point, math::Vector* out)
	{
		world.Transform(*point, *out);
	}

	// FUNCTION: ENGINE 0x106DCF50
	void Camera::ToScreen(const math::Vector* point, float* out)
	{
		math::Vector local;
		local.Transform(*point, matrix);
		float scale = 1.0f;
		if (unknown10 == 0 && local.z != 0.0f)
		{
			scale = 1.0f / local.z;
		}
		out[0] = local.x / halfX * scale * 0.5f;
		out[1] = local.y / halfY * scale * 0.5f;
		out[2] = local.z;
	}

	// FUNCTION: ENGINE 0x106DCFE0
	void ConvertFov(float fov, float aspect, float otherAspect, float* vertical, float* horizontal)
	{
		float t = (float)tan(fov * 0.5f);
		*vertical = (float)atan(otherAspect * (t / aspect)) * 2.0f;
		*horizontal = (float)atan(t / aspect) * 2.0f;
	}

	// FUNCTION: ENGINE 0x106DD020
	void Camera::SetWindow(const CameraWindow* newWindow)
	{
		window = *newWindow;
	}

	// FUNCTION: ENGINE 0x106DD060
	void Camera::SetWindow(bool enabled, float a, float b, float c, float d, bool flag)
	{
		window.values[0] = a;
		window.values[1] = b;
		window.values[2] = c;
		window.enabled = enabled;
		window.values[3] = d;
		window.flag = flag;
	}

	// FUNCTION: ENGINE 0x106DD0B0
	void Camera::GetWindow(bool* enabled, float* a, float* b, float* c, float* d, bool* flag)
	{
		*enabled = window.enabled;
		*a = window.values[0];
		*b = window.values[1];
		*c = window.values[2];
		*d = window.values[3];
		*flag = window.flag;
	}

	// FUNCTION: ENGINE 0x106DD100
	void Camera::SetSize(float newWidth, float newHeight)
	{
		width = newWidth;
		height = newHeight;
	}

	// FUNCTION: ENGINE 0x106DD120
	void Camera::GetSize(float* outWidth, float* outHeight)
	{
		*outWidth = width;
		*outHeight = height;
	}

	// FUNCTION: ENGINE 0x106DD160
	void Camera::SetOrthographic(bool value)
	{
		if (unknown10 && value)
		{
			return;
		}
		if (!unknown10 && !value)
		{
			return;
		}
		unknown10 = value;
		UpdatePlanes();
	}

	// FUNCTION: ENGINE 0x106DD190
	void Camera::SetFov(float radians)
	{
		if (radians != fov)
		{
			fov = radians;
			if (unknown10 == 0)
			{
				halfX = (float)tan(radians * 0.5f);
				halfY = halfX / unknown1C;
				float half = (float)atan(halfY);
				unknown18 = half + half;
				UpdatePlanes();
				return;
			}
			halfX = radians * 0.5f;
			halfY = halfX / unknown1C;
			unknown18 = halfY * 2.0f;
			UpdatePlanes();
		}
	}

	// FUNCTION: ENGINE 0x106DD220
	void Camera::SetFovHorizontal(float radians)
	{
		if (radians != unknown18)
		{
			unknown18 = radians;
			if (unknown10 == 0)
			{
				halfY = (float)tan(radians * 0.5f);
				halfX = unknown1C * halfY;
				float half = (float)atan(halfX);
				fov = half + half;
				UpdatePlanes();
				return;
			}
			radians = radians * 0.5f;
			float x = unknown1C * radians;
			halfX = x;
			x = x * 2.0f;
			halfY = radians;
			fov = x;
			UpdatePlanes();
		}
	}

	// FUNCTION: ENGINE 0x106DD2B0
	// NONMATCHING: the product is spilled to the second argument's slot in the engine, to the first one here (97.6 %)
#ifdef NONMATCHING
	void Camera::SetAspect(float aspect, int fixed)
	{
		if (aspect != unknown1C)
		{
			unknown1C = aspect;
			if ((char)fixed != 0)
			{
				halfX = halfY * aspect;
				if (unknown10 == 0)
				{
					float half = (float)atan(halfX);
					fov = half + half;
					UpdatePlanes();
					return;
				}
				fov = halfX * 2.0f;
				UpdatePlanes();
				return;
			}
			halfY = halfX / aspect;
			if (unknown10 == 0)
			{
				float half = (float)atan(halfY);
				unknown18 = half + half;
				UpdatePlanes();
				return;
			}
			unknown18 = halfY * 2.0f;
			UpdatePlanes();
		}
	}
#endif

	// FUNCTION: ENGINE 0x106DD360
	bool Camera::IsInsideView(const math::Vector* point)
	{
		return Classify(point) == 0;
	}

	// FUNCTION: ENGINE 0x106DD380
	bool Camera::IsPointInside(const math::Vector* point)
	{
		math::Vector local;
		matrix.Transform(*point, local);
		return IsInsideView(&local);
	}

	// FUNCTION: ENGINE 0x106DD3B0
	void Camera::SetView(const math::Vector* position, math::Vector forward, math::Vector up)
	{
		SetViewMatrix(&world, position, forward, up);
		matrix = world;
		matrix.InvertOrthonormal();
	}

	// FUNCTION: ENGINE 0x106DD430
	void Camera::GetRay(const float* screen, math::Vector* nearPoint, math::Vector* farPoint)
	{
		math::Vector nearLocal;
		math::Vector farLocal;
		GetRayPoints(screen, &nearLocal, &farLocal);
		ToWorld(&nearLocal, nearPoint);
		ToWorld(&farLocal, farPoint);
	}

	// FUNCTION: ENGINE 0x106DD480
	// NONMATCHING: the matrix address for the first Identity call is formed after the size stores in the engine (85.3 %)
#ifdef NONMATCHING
	Camera::Camera() : unknown10(false), fov(0.0f), unknown18(0.0f), unknown1C(1.0f)
	{
		width = 0.0f;
		height = 0.0f;
		minZ = 1.0f;
		maxZ = 1000.0f;
		matrix.Identity();
		world.Identity();
		SetFov(1.5707964f);
	}
#endif

	// FUNCTION: ENGINE 0x106DD510
	Camera::Camera(const Camera& other) : fov(0.0f), unknown18(0.0f), width(0.0f), height(0.0f)
	{
		unknown10 = other.unknown10;
		unknown1C = other.unknown1C;
		minZ = other.minZ;
		maxZ = other.maxZ;
		world = other.world;
		matrix = other.matrix;
		window = other.window;
		SetFov(other.fov);
	}
}
