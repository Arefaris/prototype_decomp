// engine::render::Light: see the header. The render thread's functions find the light by its controller handle and
// forward the value to the pure3d::Light; the game thread's methods queue them.
#include <new>

#include "code/core/heap.h"
#include "code/core/refptr.h"
#include "code/engine/render/async/light.h"
#include "code/engine/render/async/renderevent.h"
#include "code/pure3d/lighting.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/scene.h"

namespace engine
{
	namespace render
	{
		// 0x10817B10 (renderglobals.cpp): the scene the render thread draws
		pure3d::Scene* GetRenderList();

		// The reference helpers the controller table's objects go through: other units keep these copies (0x107B2F40
		// releases the object and clears the pointer, 0x107AC0F0 takes a reference to a new one and releases the old)
		void ReleaseControllerObject(void*& object);
		void AssignControllerObject(void*& pointer, pure3d::Light* object);

		// The unit's own copy of the release helper for a frame controller (a plain function: the unit's statics
		// would get a register convention)
		void ReleaseController(pure3d::FrameController*& controller);

		// FUNCTION: ENGINE 0x1082A940
		void ReleaseController(pure3d::FrameController*& controller)
		{
			if (controller != 0)
			{
				controller->Release();
				controller = 0;
			}
		}

		// FUNCTION: ENGINE 0x1082A2B0
		static void DoSetActive(Light light, bool active)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(light.handle);
			if (object != 0)
			{
				object->SetUnknown158(active);
			}
		}

		// FUNCTION: ENGINE 0x1082A2D0
		static void DoSetUserData(Light light, pure3d::LightUserData* data)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(light.handle);
			if (object != 0)
			{
				object->SetUserData(data);
			}
			if (data != 0)
			{
				data->Release();
			}
		}

		// FUNCTION: ENGINE 0x1082A300
		static void DoSetUnknown216(Light light, bool value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(light.handle);
			if (object != 0)
			{
				object->SetUnknown216(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A320
		bool Light::IsValid() const
		{
			return IsValidController(handle);
		}

		// FUNCTION: ENGINE 0x1082A330
		void Light::ApplyColour(const math::Vector4* colour)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetColour(colour);
			}
		}

		// FUNCTION: ENGINE 0x1082A350
		void Light::ApplyTransform(const math::Matrix* transform)
		{
			math::Vector position(transform->m[3][0], transform->m[3][1], transform->m[3][2]);
			math::Vector direction(transform->m[2][0], transform->m[2][1], transform->m[2][2]);
			math::Vector right(transform->m[1][0], transform->m[1][1], transform->m[1][2]);
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetPosition(&position);
				object->SetDirection(&direction);
				object->SetUnknownF0(&right);
			}
		}

		// FUNCTION: ENGINE 0x1082A400
		void Light::ApplyUnknown120(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown120(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A420
		void Light::ApplyUnknown128(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown128(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A440
		void Light::ApplyUnknown124(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown124(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A460
		void Light::ApplyShadowUnknown1074ED30(int value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				if (object->GetShadow() != 0)
				{
					object->GetShadow()->Unknown1074ED30(value);
				}
			}
		}

		// FUNCTION: ENGINE 0x1082A4A0
		void Light::ApplyShadowEnabled(bool enabled)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetShadowEnabled(enabled);
			}
		}

		// FUNCTION: ENGINE 0x1082A4C0
		void Light::ApplyUnknown164(int value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown164(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A4E0
		void Light::ApplyUnknown168(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown168(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A500
		void Light::ApplyUnknown16C(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown16C(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A520
		void Light::ApplyShadowCount(unsigned int count)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->GetShadow()->Unknown1074F4B0(count);
			}
		}

		// FUNCTION: ENGINE 0x1082A550
		void Light::ApplyShadowCascade(unsigned int index, float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->GetShadow()->Unknown1074F110(index, value);
			}
		}

		// FUNCTION: ENGINE 0x1082A580
		void Light::ApplyUnknown194(float a, float b, float c)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown194(a, b, c);
			}
		}

		// FUNCTION: ENGINE 0x1082A5C0
		void Light::ApplyUnknown130(bool value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown130(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A5E0
		void Light::ApplyName(const core::Name<core::CaseSensitiveKey>* name)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetName(*name);
			}
		}

		// FUNCTION: ENGINE 0x1082A600
		void Light::ApplyUnknown17C(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown17C(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A620
		void Light::ApplyUnknown180(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown180(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A640
		void Light::ApplyUnknown184(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown184(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A660
		void Light::ApplyUnknown1075C500(const unsigned int* a, const unsigned int* b, const unsigned int* c)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->Unknown1075C500(a, b, c);
			}
		}

		// FUNCTION: ENGINE 0x1082A680
		void Light::ApplyUnknown188(bool value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown188(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A6A0
		void Light::ApplyUnknown107587C0(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown107587C0(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A6C0
		void Light::ApplyUnknown190(bool value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown190(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A6E0
		void Light::ApplyUnknown20C(int value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->SetUnknown20C(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A700
		void Light::ApplyShadowUnknown1074ED10(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->GetShadow()->Unknown1074ED10(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A730
		void Light::ApplyShadowUnknown1074F0C0(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->GetShadow()->Unknown1074F0C0(value);
			}
		}

		// FUNCTION: ENGINE 0x1082A760
		void Light::ApplyShadowUnknown1074ECE0(float value)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				object->GetShadow()->Unknown1074ECE0(value);
			}
		}

		// Changes the decay of the light; the light leaves its lighting scene while its decay kind changes (the scene
		// sorts the lights by whether they have a range)
		// FUNCTION: ENGINE 0x1082A790
		void Light::ApplyDecay(int kind, float range, float second)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object == 0)
			{
				return;
			}
			bool removed = kind != object->GetDecay()->GetKind() && GetRenderList()->GetLightingScene()->Contains(object);
			if (removed)
			{
				GetRenderList()->RemoveLight(object);
			}
			pure3d::DecayRange decay;
			decay.SetKind(kind);
			decay.SetUnknown1075A7F0(range);
			decay.SetUnknown1075A810(second);
			object->SetDecay(&decay);
			if (removed)
			{
				GetRenderList()->AddLight(object);
			}
		}

		// FUNCTION: ENGINE 0x1082A860
		void Light::SetController(pure3d::FrameController* controller)
		{
			ControllerSlot* slot = GetControllerSlot(handle);
			if (slot != 0)
			{
				slot->controller = controller;
			}
		}

		// FUNCTION: ENGINE 0x1082A880
		void Light::StartController()
		{
			ControllerSlot* slot = GetControllerSlot(handle);
			if (slot != 0)
			{
				slot->active = true;
			}
		}

		// FUNCTION: ENGINE 0x1082A8A0
		void Light::StopController()
		{
			ControllerSlot* slot = GetControllerSlot(handle);
			if (slot != 0)
			{
				slot->active = false;
			}
		}

		// FUNCTION: ENGINE 0x1082A8C0
		void Light::ResetController()
		{
			ControllerSlot* slot = GetControllerSlot(handle);
			if (slot != 0)
			{
				pure3d::FrameController* controller = slot->controller;
				if (controller != 0)
				{
					controller->Reset();
				}
			}
		}

		// FUNCTION: ENGINE 0x1082A8E0
		void Light::ApplyAddToGroup(const core::Name<core::CaseSensitiveKey>* name)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				pure3d::LightGroupTable* table = GetRenderList()->GetLightGroupTable();
				table->Unknown10758020(name, object);
			}
		}

		// FUNCTION: ENGINE 0x1082A910
		void Light::ApplyRemoveFromGroup(const core::Name<core::CaseSensitiveKey>* name)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(handle);
			if (object != 0)
			{
				pure3d::LightGroupTable* table = GetRenderList()->GetLightGroupTable();
				table->Unknown10758090(name, object);
			}
		}

		// FUNCTION: ENGINE 0x1082A960
		static void DoCreate(Light light, pure3d::Light::LightType type, int heap)
		{
			core::HeapScope scope(heap);
			ControllerSlot* slot = GetControllerSlot(light.handle);
			AssignControllerObject(slot->unknown0, new pure3d::Light(type));
			GetRenderList()->AddLight((pure3d::Light*)slot->unknown0);
		}

		// FUNCTION: ENGINE 0x1082A9D0
		static void DoDestroy(Light light)
		{
			ControllerSlot* slot = GetControllerSlot(light.handle);
			if (slot != 0)
			{
				GetRenderList()->RemoveLight((pure3d::Light*)slot->unknown0);
				ReleaseControllerObject(slot->unknown0);
				ReleaseController(slot->controller);
				FreeController(light.handle);
			}
		}

		// FUNCTION: ENGINE 0x1082AA20
		static void DoSetColour(Light light, math::Colour128 colour)
		{
			if (light.IsValid())
			{
				light.ApplyColour((const math::Vector4*)&colour);
			}
		}

		// FUNCTION: ENGINE 0x1082AA40
		static void DoSetUnknown128(Light light, float value)
		{
			if (light.IsValid())
			{
				light.ApplyUnknown128(value);
			}
		}

		// FUNCTION: ENGINE 0x1082AA60
		static void DoSetUnknown120(Light light, float value)
		{
			if (light.IsValid())
			{
				light.ApplyUnknown120(value);
			}
		}

		// FUNCTION: ENGINE 0x1082AA80
		static void DoSetUnknown124(Light light, float value)
		{
			if (light.IsValid())
			{
				light.ApplyUnknown124(value);
			}
		}

		// FUNCTION: ENGINE 0x1082AAA0
		static void DoSetName(Light light, core::Name<core::CaseSensitiveKey> name)
		{
			if (light.IsValid())
			{
				light.ApplyName(&name);
			}
		}

		// FUNCTION: ENGINE 0x1082AAC0
		static void DoSetTransform(Light light, math::Matrix transform)
		{
			if (light.IsValid())
			{
				light.ApplyTransform(&transform);
			}
		}

		// FUNCTION: ENGINE 0x1082AAE0
		static void DoSetDecayShape(Light light, pure3d::DecayRange::DecayShape shape)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(light.handle);
			if (object != 0)
			{
				light.ApplyDecay(shape, object->GetDecay()->GetUnknown10758B20(), object->GetDecay()->GetRange());
			}
		}

		// FUNCTION: ENGINE 0x1082AB30
		static void DoSetDecayRanges(Light light, float range, float second)
		{
			pure3d::Light* object = (pure3d::Light*)GetControllerObject(light.handle);
			if (object != 0)
			{
				light.ApplyDecay(object->GetDecay()->GetKind(), range, second);
			}
		}

		// FUNCTION: ENGINE 0x1082AB70
		static void DoAddToGroup(Light light, core::Name<core::CaseSensitiveKey> name)
		{
			if (light.IsValid())
			{
				light.ApplyAddToGroup(&name);
			}
		}

		// FUNCTION: ENGINE 0x1082AB90
		static void DoRemoveFromGroup(Light light, core::Name<core::CaseSensitiveKey> name)
		{
			if (light.IsValid())
			{
				light.ApplyRemoveFromGroup(&name);
			}
		}

		// The event classes the light methods queue
		// FUNCTION: ENGINE 0x1082ABB0
		// FUNCTION: ENGINE 0x1082ABE0
		template class RenderEvent3<Light, pure3d::Light::LightType, int>;
		// FUNCTION: ENGINE 0x1082AC00
		// FUNCTION: ENGINE 0x1082AC20
		template class RenderEvent1<Light>;
		// FUNCTION: ENGINE 0x1082AC40
		// FUNCTION: ENGINE 0x1082AC60
		template class RenderEvent2<Light, bool>;
		// FUNCTION: ENGINE 0x1082AC80
		// FUNCTION: ENGINE 0x1082ACA0
		template class RenderEvent2<Light, pure3d::LightUserData*>;
		// FUNCTION: ENGINE 0x1082ACC0
		// FUNCTION: ENGINE 0x1082ACF0
		template class RenderEvent2<Light, float>;
		// FUNCTION: ENGINE 0x1082AD10
		// FUNCTION: ENGINE 0x1082AD60
		template class RenderEvent2<Light, math::Colour128>;
		// FUNCTION: ENGINE 0x1082ADA0
		// FUNCTION: ENGINE 0x1082AE70
		// EQUIVALENT: the original copies the matrix argument with the compiler's vector copy-constructor helper (four rows); ours copies the sixteen floats inline
		template class RenderEvent2<Light, math::Matrix>;
		// FUNCTION: ENGINE 0x1082AEA0
		// FUNCTION: ENGINE 0x1082AED0
		// FUNCTION: ENGINE 0x1082AF80
		// FUNCTION: ENGINE 0x1082B340
		template class RenderEvent2<Light, core::Name<core::CaseSensitiveKey> >;
		// FUNCTION: ENGINE 0x1082AEE0
		// FUNCTION: ENGINE 0x1082AF10
		template class RenderEvent3<Light, float, float>;
		// FUNCTION: ENGINE 0x1082AF40
		// FUNCTION: ENGINE 0x1082AF60
		template class RenderEvent2<Light, pure3d::DecayRange::DecayShape>;

		// FUNCTION: ENGINE 0x1082B370
		Light Light::Create(pure3d::Light::LightType type)
		{
			Light light;
			QueueRenderEvent(DoCreate, light, type, core::GetCurrentHeap());
			return light;
		}

		// FUNCTION: ENGINE 0x1082B3A0
		Light Light::Create(pure3d::Light* source)
		{
			Light light = Create((pure3d::Light::LightType)source->type);
			light.ApplyUnknown20C(source->GetUnknown20C());
			light.ApplyUnknown128(source->GetUnknown10758760());
			float a;
			float b;
			float c;
			source->GetUnknown194(&a, &b, &c);
			light.ApplyUnknown194(a, b, c);
			light.ApplyColour(source->GetColour());
			light.ApplyDecay(source->GetDecay()->GetKind(), source->GetDecay()->GetUnknown10758B20(),
				source->GetDecay()->GetRange());
			light.ApplyUnknown184(source->GetUnknown184());
			light.ApplyUnknown130(source->GetUnknown130());
			light.ApplyUnknown17C(source->GetUnknown17C());
			if (source->IsEnabled())
			{
				pure3d::RenderParams* shadow = source->GetShadow();
				light.ApplyShadowCount(shadow->camerasEnd - shadow->cameras);
				for (unsigned int i = 0; i < (unsigned int)(shadow->camerasEnd - shadow->cameras); i++)
				{
					light.ApplyShadowCascade(i, shadow->Unknown1074F130(i));
				}
				light.ApplyShadowEnabled(source->IsEnabled());
				light.ApplyShadowUnknown1074ECE0(shadow->Unknown1074EE50());
				light.ApplyUnknown164(source->GetUnknown164());
				light.ApplyUnknown16C(source->GetUnknown16C());
				light.ApplyShadowUnknown1074ED10(1.0f);
				light.ApplyShadowUnknown1074F0C0(1.0f);
				light.ApplyUnknown168(source->GetUnknown168());
				light.ApplyShadowUnknown1074ED30(shadow->Unknown1074EE00());
			}
			light.ApplyUnknown124(source->GetUnknown10758E50());
			light.ApplyUnknown107587C0(source->GetUnknown107587D0());
			light.ApplyUnknown190(source->GetUnknown190());
			light.ApplyUnknown120(source->GetUnknown120());
			light.ApplyUnknown180(source->GetUnknown180());
			return light;
		}

		// FUNCTION: ENGINE 0x1082B610
		void Light::Destroy(Light* light)
		{
			QueueRenderEvent(DoDestroy, *light);
			light->handle.mHandle = -1;
		}

		// FUNCTION: ENGINE 0x1082B630
		void Light::SetActive(bool active)
		{
			QueueRenderEvent(DoSetActive, *this, active);
		}

		// FUNCTION: ENGINE 0x1082B650
		void Light::SetUserData(pure3d::LightUserData* data)
		{
			if (data != 0)
			{
				data->AddRef();
			}
			QueueRenderEvent(DoSetUserData, *this, data);
		}

		// FUNCTION: ENGINE 0x1082B680
		void Light::SetUnknown128(float value)
		{
			QueueRenderEvent(DoSetUnknown128, *this, value);
		}

		// FUNCTION: ENGINE 0x1082B6A0
		void Light::SetColour(const math::Colour128& colour)
		{
			QueueRenderEvent(DoSetColour, *this, colour);
		}

		// FUNCTION: ENGINE 0x1082B6E0
		// EQUIVALENT: the original copies the matrix argument with the compiler's vector copy-constructor helper (four rows); ours copies the sixteen floats inline
		void Light::SetTransform(const math::Matrix& transform)
		{
			QueueRenderEvent(DoSetTransform, *this, transform);
		}

		// FUNCTION: ENGINE 0x1082B710
		void Light::SetUnknown120(float value)
		{
			QueueRenderEvent(DoSetUnknown120, *this, value);
		}

		// FUNCTION: ENGINE 0x1082B730
		void Light::SetUnknown124(float value)
		{
			QueueRenderEvent(DoSetUnknown124, *this, value);
		}

		// FUNCTION: ENGINE 0x1082B750
		void Light::SetName(core::Name<core::CaseSensitiveKey> name)
		{
			QueueRenderEvent(DoSetName, *this, name);
		}

		// FUNCTION: ENGINE 0x1082B780
		void Light::SetUnknown216(bool value)
		{
			QueueRenderEvent(DoSetUnknown216, *this, value);
		}

		// FUNCTION: ENGINE 0x1082B7A0
		void Light::SetDecayRanges(float range, float second)
		{
			QueueRenderEvent(DoSetDecayRanges, *this, range, second);
		}

		// FUNCTION: ENGINE 0x1082B7D0
		void Light::SetDecayShape(pure3d::DecayRange::DecayShape shape)
		{
			QueueRenderEvent(DoSetDecayShape, *this, shape);
		}

		// FUNCTION: ENGINE 0x1082B7F0
		void Light::AddToGroup(const core::Name<core::CaseSensitiveKey>& name)
		{
			QueueRenderEvent(DoAddToGroup, *this, name);
		}

		// FUNCTION: ENGINE 0x1082B820
		void Light::RemoveFromGroup(const core::Name<core::CaseSensitiveKey>& name)
		{
			QueueRenderEvent(DoRemoveFromGroup, *this, name);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1082AFA0
// FUNCTION: ENGINE 0x1082AFF0
// FUNCTION: ENGINE 0x1082B030
// FUNCTION: ENGINE 0x1082B070
// FUNCTION: ENGINE 0x1082B0B0
// FUNCTION: ENGINE 0x1082B0F0
// FUNCTION: ENGINE 0x1082B150
// FUNCTION: ENGINE 0x1082B240
// FUNCTION: ENGINE 0x1082B2B0
// FUNCTION: ENGINE 0x1082B300
// FUNCTION: ENGINE 0x1082B890
