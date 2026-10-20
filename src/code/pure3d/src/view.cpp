// pure3d::View (code/pure3d/src/view.cpp, file name guessed from the class): the camera, the window and the
// transforms between the spaces. Names are guesses.
#include "code/core/refptr.h"
#include "code/engine/display.h"
#include "code/pure3d/context.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/view.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1073A260
	// EQUIVALENT: the engine stores the second vftable after the window's first two floats and loads its constants
	// before the stores; ours keeps the member stores in source order (89.6 %)
	View::View() : RefCounted(NO_BARRIER)
	{
		left = 0.0f;
		top = 0.0f;
		bottom = 1.0f;
		right = 1.0f;
		requestedAspect = engine::gDisplay->GetUnknown804Ratio();
		fixedAspect = false;
		updatesCamera = false;
		camera = 0;
		clearColour = 0xFF000000;
		clearDepth = 1.0f;
		clearStencil = 0;
		clearFlags = 3;
		matrix.Identity();
		UpdateAspect();
	}

	// FUNCTION: ENGINE 0x1073A2E0
	View::~View()
	{
		core::SafeRelease(camera);
	}

	// FUNCTION: ENGINE 0x1073A300
	void View::SetCamera(CameraData* newCamera)
	{
		core::RefAssign(camera, newCamera);
		if (camera != 0 && updatesCamera)
		{
			camera->SetAspect(aspect, 0);
		}
	}

	// FUNCTION: ENGINE 0x1073A340
	void View::SetWindow(float newLeft, float newTop, float newRight, float newBottom)
	{
		left = newLeft;
		top = newTop;
		right = newRight;
		bottom = newBottom;
		fixedAspect = false;
		requestedAspect = engine::gDisplay->GetUnknown804Ratio() * ((right - left) / (bottom - top));
		UpdateAspect();
	}

	// FUNCTION: ENGINE 0x10739BA0
	void View::GetWindow(float* outLeft, float* outTop, float* outRight, float* outBottom)
	{
		*outLeft = left;
		*outTop = top;
		*outRight = right;
		*outBottom = bottom;
	}

	// FUNCTION: ENGINE 0x10739BD0
	void View::End()
	{
	}

	// FUNCTION: ENGINE 0x1073A1D0
	void View::UpdateAspect()
	{
		if (!fixedAspect)
		{
			aspect = ((right - left) / (bottom - top)) * engine::gDisplay->GetUnknown804Ratio();
		}
		else
		{
			aspect = requestedAspect;
		}
		if (updatesCamera && camera != 0)
		{
			camera->SetAspect(aspect, 0);
		}
	}

	// FUNCTION: ENGINE 0x1073A220
	bool View::SetUpdatesCamera(bool value)
	{
		bool old = updatesCamera;
		updatesCamera = value;
		if (camera != 0 && value)
		{
			camera->SetAspect(aspect, 0);
		}
		return old;
	}

	// FUNCTION: ENGINE 0x1073A250
	bool View::SetFixedAspect(bool value)
	{
		bool old = fixedAspect;
		fixedAspect = value;
		return old;
	}

	// FUNCTION: ENGINE 0x1073A3A0
	void View::SetAspect(float newAspect, bool centre)
	{
		left = 0.0f;
		top = 0.0f;
		right = 1.0f;
		bottom = 1.0f;
		requestedAspect = newAspect;
		float screen = engine::gDisplay->GetUnknown804Ratio();
		if (!fixedAspect)
		{
			if (newAspect >= screen)
			{
				bottom = screen / newAspect;
			}
			else
			{
				right = newAspect / screen;
			}
		}
		if (centre)
		{
			float x = (1.0f - (right - left)) * 0.5f;
			left += x;
			right += x;
			float y = (1.0f - (bottom - top)) * 0.5f;
			top += y;
			bottom += y;
		}
		UpdateAspect();
	}

	// FUNCTION: ENGINE 0x1073A490
	void View::Apply()
	{
		context->SetView(this);
		pddi->SetViewUnknown10(camera->unknown10 != false);
		float width;
		float height;
		camera->GetSize(&width, &height);
		pddi->SetViewUnknown24(camera->nearClip, camera->farClip, camera->unknown14, camera->unknown1C, width,
			height);
		pddi->SetViewUnknown14(left, top, right, bottom);
		math::Matrix world;
		world.Multiply(camera->transform, matrix);
		world.Invert();
		pddi->SetViewMatrix(&world);
		pddi->SetWorldMatrix(&math::Matrix::IDENTITY);
		if (clearFlags != 0)
		{
			pddi->SetViewUnknown4(clearColour);
			pddi->SetViewUnknown8(clearDepth);
			pddi->SetViewUnknownC(clearStencil);
			pddi->Clear(clearFlags);
		}
	}

	// FUNCTION: ENGINE 0x10739BE0
	void View::ToDeviceSpace(const math::Vector& point, math::Vector* out)
	{
		out->Transform(point, *pddi->GetUnknown10614850());
	}

	// FUNCTION: ENGINE 0x10739C00
	void View::ToCameraSpace(const math::Vector& point, math::Vector* out)
	{
		if (camera != 0)
		{
			out->Transform(point, camera->view);
		}
	}

	// FUNCTION: ENGINE 0x10739F00
	void View::ToWorldSpace(const math::Vector& point, math::Vector* out)
	{
		if (camera != 0)
		{
			out->Transform(point, camera->transform);
		}
	}

	// FUNCTION: ENGINE 0x10739C20
	void View::Project(const math::Vector* point, math::Vector* out)
	{
		CameraData* current = camera;
		if (current != 0)
		{
			if (point->z != 0.0f)
			{
				float inverse = 1.0f / point->z;
				float width = current->halfWidth;
				float height = current->halfHeight;
				out->x = (point->x / width) * inverse * 0.5f;
				out->y = (point->y / height) * inverse * 0.5f;
				out->z = point->z;
			}
			else
			{
				out->x = 0.0f;
				out->y = 0.0f;
				out->z = 1.0f;
			}
		}
	}

	// FUNCTION: ENGINE 0x10739CB0
	void View::ToWindow(const math::Vector* point, math::Vector* out)
	{
		if (camera != 0)
		{
			out->z = 0.0f;
			out->x = (right - left) * (point->x + 0.5f) + (left - 0.5f);
			out->y = (bottom - top) * (point->y - 0.5f) + (0.5f - top);
			out->x = (float)engine::gDisplay->GetWidth() * (out->x + 0.5f);
			out->y = (float)engine::gDisplay->GetUnknown8() * (1.0f - (out->y + 0.5f));
		}
	}

	// FUNCTION: ENGINE 0x10739D80
	void View::FromWindow(const math::Vector* point, math::Vector* out)
	{
		math::Vector local;
		local.x = point->x / (float)engine::gDisplay->GetWidth() - 0.5f;
		int height = engine::gDisplay->GetUnknown8();
		float z = point->z;
		float y = (1.0f - point->y / (float)height) - 0.5f;
		out->x = ((local.x + 0.5f) - left) / (right - left) - 0.5f;
		out->y = 0.5f - ((0.5f - y) - top) / (bottom - top);
		out->z = z;
	}

	// FUNCTION: ENGINE 0x10739E50
	void View::GetFrustumPoints(const math::Vector2* position, math::Vector* outNear, math::Vector* outFar)
	{
		if (camera != 0)
		{
			float x = camera->halfWidth * position->x;
			float y = camera->halfHeight * position->y;
			outNear->z = 1.0f;
			x *= 2.0f;
			outNear->x = x;
			y *= 2.0f;
			outNear->y = y;
			float nearClip = camera->nearClip;
			outNear->x = nearClip * x;
			outNear->y = nearClip * y;
			outNear->z = nearClip;
			outFar->x = x;
			outFar->z = 1.0f;
			outFar->y = y;
			float farClip = camera->farClip;
			outFar->x = farClip * x;
			outFar->y = farClip * y;
			outFar->z = farClip;
		}
	}

	// FUNCTION: ENGINE 0x10739F20
	void View::WorldToCameraWindow(math::Vector point, math::Vector* out)
	{
		math::Vector local;
		ToDeviceSpace(point, &local);
		ToCameraSpace(local, &local);
		Project(&local, out);
	}

	// FUNCTION: ENGINE 0x10739F60
	void View::WorldToCameraSpace(math::Vector point, math::Vector* out)
	{
		math::Vector local;
		ToDeviceSpace(point, &local);
		ToCameraSpace(local, out);
	}

	// FUNCTION: ENGINE 0x10739F90
	void View::WorldToWindow(math::Vector point, math::Vector* out)
	{
		math::Vector local;
		if (camera != 0)
		{
			ToDeviceSpace(point, &local);
			ToCameraSpace(local, &local);
			Project(&local, &local);
			ToWindow(&local, out);
		}
	}

	// FUNCTION: ENGINE 0x10739FF0
	void View::DeviceToCameraWindow(math::Vector point, math::Vector* out)
	{
		math::Vector local;
		if (camera != 0)
		{
			ToCameraSpace(point, &local);
			Project(&local, out);
		}
	}

	// FUNCTION: ENGINE 0x1073A030
	// EQUIVALENT: the engine multiplies the local's x by the inverse with x loaded first; ours commutes the operands (65 %)
	void View::ProjectWorldPoint(float x, float y, float z, math::Vector* out)
	{
		math::Vector local;
		if (camera != 0)
		{
			local.x = x;
			local.y = y;
			local.z = z;
			local.Transform(*pddi->GetUnknown10614850());
			local.Transform(camera->view);
			if (local.z != 0.0f)
			{
				float inverse = 1.0f / local.z;
				out->x = local.x * inverse * 0.5f;
				out->y = local.y * inverse * 0.5f;
				out->z = local.z;
			}
			else
			{
				out->x = 0.0f;
				out->y = 0.0f;
				out->z = 1.0f;
			}
		}
	}

	// FUNCTION: ENGINE 0x1073A110
	// EQUIVALENT: the engine multiplies the local's x by the inverse with x loaded first; ours commutes the operands (61 %)
	void View::ProjectCameraPoint(float x, float y, float z, math::Vector* out)
	{
		math::Vector local;
		if (camera != 0)
		{
			local.x = x;
			local.y = y;
			local.z = z;
			local.Transform(camera->view);
			if (local.z != 0.0f)
			{
				float inverse = 1.0f / local.z;
				out->x = local.x * inverse * 0.5f;
				out->y = local.y * inverse * 0.5f;
				out->z = local.z;
			}
			else
			{
				out->x = 0.0f;
				out->y = 0.0f;
				out->z = 1.0f;
			}
		}
	}

	// FUNCTION: ENGINE 0x1073A5C0
	void View::FromDeviceSpace(const math::Vector& point, math::Vector* out)
	{
		math::Matrix inverse;
		inverse = *pddi->GetUnknown10614850();
		inverse.InvertOrthonormal();
		out->Transform(point, inverse);
	}

	// FUNCTION: ENGINE 0x1073A600
	void View::GetWorldRay(math::Vector position, math::Vector* outNear, math::Vector* outFar)
	{
		math::Vector nearPoint;
		math::Vector farPoint;
		GetFrustumPoints((const math::Vector2*)&position, &nearPoint, &farPoint);
		ToWorldSpace(nearPoint, &nearPoint);
		ToWorldSpace(farPoint, &farPoint);
		FromDeviceSpace(nearPoint, outNear);
		FromDeviceSpace(farPoint, outFar);
	}

	// FUNCTION: ENGINE 0x1073A670
	void View::GetWindowRay(math::Vector position, math::Vector* outNear, math::Vector* outFar)
	{
		math::Vector local;
		FromWindow(&position, &local);
		GetWorldRay(local, outNear, outFar);
	}
}
