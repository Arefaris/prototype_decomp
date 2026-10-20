// engine::render::Light (RTTI name, from the RenderEventN template arguments): the game thread's handle to a light of
// the render thread. The handle comes from the controller table (renderglobals.cpp); the light object itself is a
// pure3d::Light the table slot keeps. Every setter queues a render event that calls one of light.cpp's static
// functions on the render thread; those find the light by its handle and forward to the pure3d::Light. No assert path
// names the unit (0x1082A0B0 - 0x1082B8D0), so the file names are guesses, as are the method names, which say what the
// pure3d::Light member they reach does.
#ifndef ENGINE_RENDER_ASYNC_LIGHT_H
#define ENGINE_RENDER_ASYNC_LIGHT_H

#include "code/core/name.h"
#include "code/engine/render/async/private/controller.h"
#include "code/math/colour128.h"
#include "code/math/matrix.h"
#include "code/pure3d/light.h"

namespace engine
{
	namespace render
	{
		class Light
		{
		public:
			// A new controller slot for the light (the handle comes straight from the table)
			Light() : handle(AllocateController())
			{
			}

			// A handle that names no light (records that keep a light's handle start out with this)
			struct NoLight
			{
			};
			explicit Light(const NoLight&)
			{
			}

			// 0x1082B370 / 0x1082B3A0: a new light of the type; a copy of the pure3d::Light (all its settings are
			// queued one by one)
			static Light Create(pure3d::Light::LightType type);
			static Light Create(pure3d::Light* source);
			// 0x1082B610: queues the destruction of the light and invalidates the handle
			static void Destroy(Light* light);

			// 0x1082A320: the handle names a light the table still has
			bool IsValid() const;

			// The game thread's setters (each queues an event)
			// 0x1082B630 / 0x1082B650 / 0x1082B680 / 0x1082B6A0 / 0x1082B6E0 / 0x1082B710 / 0x1082B730 / 0x1082B750
			void SetActive(bool active);
			void SetUserData(pure3d::LightUserData* data);
			void SetUnknown128(float value);
			void SetColour(const math::Colour128& colour);
			void SetTransform(const math::Matrix& transform);
			void SetUnknown120(float value);
			void SetUnknown124(float value);
			void SetName(core::Name<core::CaseSensitiveKey> name);
			// 0x1082B780 / 0x1082B7A0 / 0x1082B7D0 / 0x1082B7F0 / 0x1082B820
			void SetUnknown216(bool value);
			void SetDecayRanges(float range, float second);
			void SetDecayShape(pure3d::DecayRange::DecayShape shape);
			void AddToGroup(const core::Name<core::CaseSensitiveKey>& name);
			void RemoveFromGroup(const core::Name<core::CaseSensitiveKey>& name);

			// The render thread's side, for the light the handle names (nothing when the table lost it)
			// 0x1082A330 / 0x1082A350 / 0x1082A400 - 0x1082A790
			void ApplyColour(const math::Vector4* colour);
			void ApplyTransform(const math::Matrix* transform);
			void ApplyUnknown120(float value);
			void ApplyUnknown128(float value);
			void ApplyUnknown124(float value);
			void ApplyShadowUnknown1074ED30(int value);
			void ApplyShadowEnabled(bool enabled);
			void ApplyUnknown164(int value);
			void ApplyUnknown168(float value);
			void ApplyUnknown16C(float value);
			void ApplyShadowCount(unsigned int count);
			void ApplyShadowCascade(unsigned int index, float value);
			void ApplyUnknown194(float a, float b, float c);
			void ApplyUnknown130(bool value);
			void ApplyName(const core::Name<core::CaseSensitiveKey>* name);
			void ApplyUnknown17C(float value);
			void ApplyUnknown180(float value);
			void ApplyUnknown184(float value);
			void ApplyUnknown1075C500(const unsigned int* a, const unsigned int* b, const unsigned int* c);
			void ApplyUnknown188(bool value);
			void ApplyUnknown107587C0(float value);
			void ApplyUnknown190(bool value);
			void ApplyUnknown20C(int value);
			void ApplyShadowUnknown1074ED10(float value);
			void ApplyShadowUnknown1074F0C0(float value);
			void ApplyShadowUnknown1074ECE0(float value);
			void ApplyDecay(int kind, float range, float second);
			void ApplyAddToGroup(const core::Name<core::CaseSensitiveKey>* name);
			void ApplyRemoveFromGroup(const core::Name<core::CaseSensitiveKey>* name);

			// 0x1082A860 - 0x1082A8C0: the frame controller the light's slot runs
			void SetController(pure3d::FrameController* controller);
			void StartController();
			void StopController();
			void ResetController();

			ControllerHandle handle;
		};
	}
}

#endif
