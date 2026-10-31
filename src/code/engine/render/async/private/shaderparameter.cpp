// The game thread's render parameter calls and the render thread's side of them (see the header): the events the
// calls queue, the interpolators they start and the parameter setters the events run. The unit's other halves are
// canvas.cpp and light.cpp (the file name is a guess).
#include <math.h>
#include <new>

#include "code/engine/render/async/shaderparameter.h"
#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"
#include "code/pure3d/context.h"

namespace engine
{
	namespace render
	{
		// 0x10817B00 (renderglobals.cpp): the render object, which keeps the interpolator pool at +8 (name guessed)
		class RenderObject
		{
		public:
			unsigned int unknown0;
			unsigned int unknown4;
			ParameterInterpolatorPool* interpolators;
		};
		RenderObject* GetRenderObject();

		// 0x1130CCD8: the event a call is filling in (set by Begin..., queued and cleared by the call) (name guess)
		extern RenderEvent* gStructEvent;

		// The events' structure is allocated with the event; a call fills it in and queues the event (the allocation
		// can fail, which leaves a null event for the queue to drop)
		template<class T> T* BeginStructEvent(void (*function)(T*))
		{
			StructRenderEvent<T>* event = new (AllocRenderEvent(sizeof(StructRenderEvent<T>))) StructRenderEvent<T>(
				function);
			gStructEvent = event;
			return &event->mData;
		}

		// The blends of the vector parameters (the engine inlines them and keeps a copy of each)
		inline void LerpFourth(math::Vector* result, const math::Vector* a, const math::Vector* b, float t,
			float inverse)
		{
		}
		inline void LerpFourth(math::Vector4* result, const math::Vector4* a, const math::Vector4* b, float t,
			float inverse)
		{
			result->w = a->w * inverse + b->w * t;
		}
		template<class V> inline void LerpVector(V* result, const V* a, const V* b, float t)
		{
			float inverse = 1.0f - t;
			math::Vector second(*b);
			second.Scale(t);
			math::Vector first(*a);
			first.Scale(inverse);
			result->Add(first, second);
			LerpFourth(result, a, b, t, inverse);
		}
		// FUNCTION: ENGINE 0x10827EC0
		// EQUIVALENT: scheduling and register use (62 %): the engine loads the six operands first and adds after the
		// products of both vectors; the sums are the same
		template void LerpVector<math::Vector>(math::Vector* result, const math::Vector* a, const math::Vector* b,
			float t);
		// FUNCTION: ENGINE 0x10827F30
		// EQUIVALENT: scheduling and register use (8 %): as the Vector one
		template void LerpVector<math::Vector4>(math::Vector4* result, const math::Vector4* a,
			const math::Vector4* b, float t);

		// The easing curves (0: the part itself, 1: a quarter of a sine, 2: a quarter of a cosine, else a smooth step)
		// FUNCTION: ENGINE 0x10827980
		// EQUIVALENT: block layout (86.8 %): the engine tests 0 < t first and keeps the clamp to zero as the fall-through
		// block that shares its store with the clamp to one; this compiler puts the test the other way round (every
		// spelling of the clamp tried gives one of the two layouts, 63 % or 87 %)
		float ParameterInterpolatorTypeless::Ease(float t) const
		{
			switch (mType)
			{
			case 0:
				break;
			case 1:
				return sinf(t * math::HALF_PI);
			case 2:
				return cosf(t * math::HALF_PI + math::PI) + 1.0f;
			default:
				if (t <= 0.0f)
				{
					t = 0.0f;
				}
				else if (t >= 1.0f)
				{
					t = 1.0f;
				}
				else
				{
					t = (3.0f - t * 2.0f) * t * t;
				}
			}
			return t;
		}

		ParameterInterpolator<float>::ParameterInterpolator(pure3d::ParameterHandlerTypeless* params,
			const core::Name<core::CaseSensitiveKey>& name, const float* target, float duration, int type) :
			ParameterInterpolatorTypeless((int)params, name, duration, type), mTarget(*target), mStart(0.0f)
		{
			params->GetFloat(&name, &mStart);
		}

		// FUNCTION: ENGINE 0x10827A30
		bool ParameterInterpolator<float>::Update(float time)
		{
			mTimeLeft = mTimeLeft - time;
			float part = math::Max(0.0f, math::Min(mTimeLeft / mDuration, 1.0f));
			float curve = Ease(1.0f - part);
			((pure3d::ParameterHandlerTypeless*)mId)->SetFloat(&mName, (1.0f - curve) * mStart + mTarget * curve);
			return mTimeLeft >= 0.0f;
		}

		// FUNCTION: ENGINE 0x10827AB0
		ParameterInterpolator<int>::ParameterInterpolator(pure3d::ParameterHandlerTypeless* params,
			const core::Name<core::CaseSensitiveKey>& name, const int* target, float duration, int type) :
			ParameterInterpolatorTypeless((int)params, name, duration, type), mTarget(*target), mStart(0)
		{
			params->GetInt(&name, &mStart);
		}

		// FUNCTION: ENGINE 0x10827B30
		bool ParameterInterpolator<int>::Update(float time)
		{
			mTimeLeft = mTimeLeft - time;
			float part = math::Max(0.0f, math::Min(mTimeLeft / mDuration, 1.0f));
			int start = mStart;
			float curve = Ease(1.0f - part);
			((pure3d::ParameterHandlerTypeless*)mId)->SetInt(&mName, (int)(curve * (mTarget - start)) + start);
			return mTimeLeft >= 0.0f;
		}

		// FUNCTION: ENGINE 0x10827BC0
		ParameterInterpolator<bool>::ParameterInterpolator(pure3d::ParameterHandlerTypeless* params,
			const core::Name<core::CaseSensitiveKey>& name, const bool* target, float duration, int type) :
			ParameterInterpolatorTypeless((int)params, name, duration, type), mTarget(*target), mStart(false)
		{
			params->GetBool(&name, &mStart);
		}

		// FUNCTION: ENGINE 0x10827C40
		bool ParameterInterpolator<bool>::Update(float time)
		{
			mTimeLeft = mTimeLeft - time;
			float part = math::Max(0.0f, math::Min(mTimeLeft / mDuration, 1.0f));
			float curve = Ease(1.0f - part);
			bool value;
			if (curve >= 0.5f)
			{
				value = mTarget;
			}
			else
			{
				value = mStart;
			}
			((pure3d::ParameterHandlerTypeless*)mId)->SetBool(&mName, value);
			return mTimeLeft >= 0.0f;
		}

		// FUNCTION: ENGINE 0x10827CD0
		ParameterInterpolator<math::Vector>::ParameterInterpolator(pure3d::ParameterHandlerTypeless* params,
			const core::Name<core::CaseSensitiveKey>& name, const math::Vector* target, float duration, int type) :
			ParameterInterpolatorTypeless((int)params, name, duration, type), mTarget(*target)
		{
			params->GetVector(&name, &mStart);
		}

		// FUNCTION: ENGINE 0x10828C70
		// EQUIVALENT: scheduling and register use (30 %): the engine loads the six operands of the blend together, then
		// stores the three sums; the sums and the order of the operations are the same
		bool ParameterInterpolator<math::Vector>::Update(float time)
		{
			mTimeLeft = mTimeLeft - time;
			float part = math::Max(0.0f, math::Min(mTimeLeft / mDuration, 1.0f));
			float curve = Ease(1.0f - part);
			math::Vector value;
			LerpVector(&value, &mStart, &mTarget, curve);
			((pure3d::ParameterHandlerTypeless*)mId)->SetVector(&mName, &value);
			return mTimeLeft >= 0.0f;
		}

		// FUNCTION: ENGINE 0x10827D40
		ParameterInterpolator<math::Vector4>::ParameterInterpolator(pure3d::ParameterHandlerTypeless* params,
			const core::Name<core::CaseSensitiveKey>& name, const math::Vector4* target, float duration, int type) :
			ParameterInterpolatorTypeless((int)params, name, duration, type), mTarget(*target)
		{
			params->GetVector4(&name, &mStart);
		}

		// FUNCTION: ENGINE 0x10828D60
		// EQUIVALENT: scheduling and register use (35 %): as the Vector one
		bool ParameterInterpolator<math::Vector4>::Update(float time)
		{
			mTimeLeft = mTimeLeft - time;
			float part = math::Max(0.0f, math::Min(mTimeLeft / mDuration, 1.0f));
			float curve = Ease(1.0f - part);
			math::Vector4 value;
			LerpVector(&value, &mStart, &mTarget, curve);
			((pure3d::ParameterHandlerTypeless*)mId)->SetVector4(&mName, &value);
			return mTimeLeft >= 0.0f;
		}

		// The colour made of the two, channel by channel (the sums are not clamped)
		void BlendColours(math::pddiColour* result, const math::pddiColour* start, const math::pddiColour* target,
			float curve);

		// FUNCTION: ENGINE 0x10827FD0
		// NONMATCHING: the engine keeps the two temporary colours in the slots of its dead arguments (target and curve),
		// ours are two locals of their own, which makes the frame 4 bytes bigger and moves the second product (19 %)
#ifdef NONMATCHING
		void BlendColours(math::pddiColour* result, const math::pddiColour* start, const math::pddiColour* target,
			float curve)
		{
			math::Vector4 channels;
			channels.x = (int)target->r * (1.0f / 255.0f) * curve;
			channels.y = (int)target->g * (1.0f / 255.0f) * curve;
			channels.z = (int)target->b * (1.0f / 255.0f) * curve;
			channels.w = (int)target->a * (1.0f / 255.0f) * curve;
			math::pddiColour b(channels);
			channels.w = 1.0f - curve;
			channels.x = (int)start->r * (1.0f / 255.0f) * channels.w;
			channels.y = (int)start->g * (1.0f / 255.0f) * channels.w;
			channels.z = (int)start->b * (1.0f / 255.0f) * channels.w;
			channels.w = (int)start->a * (1.0f / 255.0f) * channels.w;
			math::pddiColour a(channels);
			result->b = a.b + b.b;
			result->g = a.g + b.g;
			result->r = a.r + b.r;
			result->a = a.a + b.a;
		}
#endif

		// FUNCTION: ENGINE 0x10827DB0
		ParameterInterpolator<math::pddiColour>::ParameterInterpolator(pure3d::ParameterHandlerTypeless* params,
			const core::Name<core::CaseSensitiveKey>& name, const math::pddiColour* target, float duration, int type) :
			ParameterInterpolatorTypeless((int)params, name, duration, type), mTarget(*target)
		{
			params->GetColour(&name, &mStart);
		}

		// FUNCTION: ENGINE 0x10828E70
		bool ParameterInterpolator<math::pddiColour>::Update(float time)
		{
			mTimeLeft = mTimeLeft - time;
			float part = math::Max(0.0f, math::Min(mTimeLeft / mDuration, 1.0f));
			float curve = Ease(1.0f - part);
			math::pddiColour value;
			BlendColours(&value, &mStart, &mTarget, curve);
			((pure3d::ParameterHandlerTypeless*)mId)->SetColour(&mName, &value);
			return mTimeLeft >= 0.0f;
		}

		// The render thread's side of the calls
		// FUNCTION: ENGINE 0x10826A00
		static void ApplyReset(ParameterReference<int>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				RenderObject* object = GetRenderObject();
				object->interpolators->Release((int)params, reference->parameter);
			}
		}

		// FUNCTION: ENGINE 0x10827580
		static void ApplyInt(ParameterReference<int>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				params->SetInt(&reference->parameter, reference->value);
			}
		}

		// FUNCTION: ENGINE 0x10826A80
		static void ApplyBool(ParameterReference<bool>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				params->SetBool(&reference->parameter, reference->value);
			}
		}

		// FUNCTION: ENGINE 0x10826AB0
		static void ApplyFloat(ParameterReference<float>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				params->SetFloat(&reference->parameter, reference->value);
			}
		}

		// FUNCTION: ENGINE 0x108275B0
		static void ApplyVector(ParameterReference<math::Vector>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				params->SetVector(&reference->parameter, &reference->value);
			}
		}

		// FUNCTION: ENGINE 0x108275E0
		static void ApplyVector2(ParameterReference<math::Vector2>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				params->SetVector2(&reference->parameter, &reference->value);
			}
		}

		// FUNCTION: ENGINE 0x10827610
		static void ApplyVector4(ParameterReference<math::Vector4>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				params->SetVector4(&reference->parameter, &reference->value);
			}
		}

		// FUNCTION: ENGINE 0x10827640
		static void ApplyColour(ParameterReference<math::pddiColour>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				params->SetColour(&reference->parameter, &reference->value);
			}
		}

		// The render thread's side of the interpolating calls
		// FUNCTION: ENGINE 0x10829500
		static void StartFloat(ParameterReference<float>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				ParameterInterpolatorPool* pool = GetRenderObject()->interpolators;
				float duration = reference->duration;
				ParameterInterpolatorTypeless* slot = pool->Alloc();
				if (slot != 0)
				{
					new (slot) ParameterInterpolator<float>(params, reference->parameter, &reference->value, duration, 0);
				}
			}
		}

		// FUNCTION: ENGINE 0x10829560
		static void StartInt(ParameterReference<int>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				ParameterInterpolatorPool* pool = GetRenderObject()->interpolators;
				float duration = reference->duration;
				ParameterInterpolatorTypeless* slot = pool->Alloc();
				if (slot != 0)
				{
					new (slot) ParameterInterpolator<int>(params, reference->parameter, &reference->value, duration, 0);
				}
			}
		}

		// FUNCTION: ENGINE 0x108295C0
		static void StartBool(ParameterReference<bool>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				ParameterInterpolatorPool* pool = GetRenderObject()->interpolators;
				float duration = reference->duration;
				ParameterInterpolatorTypeless* slot = pool->Alloc();
				if (slot != 0)
				{
					new (slot) ParameterInterpolator<bool>(params, reference->parameter, &reference->value, duration, 0);
				}
			}
		}

		// FUNCTION: ENGINE 0x10829620
		static void StartVector(ParameterReference<math::Vector>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				ParameterInterpolatorPool* pool = GetRenderObject()->interpolators;
				float duration = reference->duration;
				ParameterInterpolatorTypeless* slot = pool->Alloc();
				if (slot != 0)
				{
					new (slot) ParameterInterpolator<math::Vector>(params, reference->parameter, &reference->value,
						duration, 0);
				}
			}
		}

		// FUNCTION: ENGINE 0x10829680
		static void StartVector4(ParameterReference<math::Vector4>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				ParameterInterpolatorPool* pool = GetRenderObject()->interpolators;
				float duration = reference->duration;
				ParameterInterpolatorTypeless* slot = pool->Alloc();
				if (slot != 0)
				{
					new (slot) ParameterInterpolator<math::Vector4>(params, reference->parameter, &reference->value,
						duration, 0);
				}
			}
		}

		// FUNCTION: ENGINE 0x108296E0
		static void StartColour(ParameterReference<math::pddiColour>* reference)
		{
			pure3d::ParameterHandlerTypeless* params = pure3d::context->passes->Unknown1074DB10(&reference->context);
			if (params != 0)
			{
				ParameterInterpolatorPool* pool = GetRenderObject()->interpolators;
				float duration = reference->duration;
				ParameterInterpolatorTypeless* slot = pool->Alloc();
				if (slot != 0)
				{
					new (slot) ParameterInterpolator<math::pddiColour>(params, reference->parameter, &reference->value,
						duration, 0);
				}
			}
		}

		// The calls
		// FUNCTION: ENGINE 0x10829130
		void StopParameterInterpolation(const ParameterName& context, const ParameterName& parameter)
		{
			ParameterReference<int>* reference = BeginStructEvent(ApplyReset);
			reference->context = context;
			reference->parameter = parameter;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x108291D0
		void SetParameter(const ParameterName& context, const ParameterName& parameter, bool value)
		{
			ParameterReference<bool>* reference = BeginStructEvent(ApplyBool);
			reference->context = context;
			reference->parameter = parameter;
			reference->value = value;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829220
		void SetParameter(const ParameterName& context, const ParameterName& parameter, float value)
		{
			ParameterReference<float>* reference = BeginStructEvent(ApplyFloat);
			reference->context = context;
			reference->parameter = parameter;
			reference->value = value;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829270
		void SetParameter(const ParameterName& context, const ParameterName& parameter, int value)
		{
			ParameterReference<int>* reference = BeginStructEvent(ApplyInt);
			reference->context = context;
			reference->parameter = parameter;
			reference->value = value;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x108292C0
		void SetParameter(const ParameterName& context, const ParameterName& parameter, math::Vector value)
		{
			ParameterReference<math::Vector>* reference = BeginStructEvent(ApplyVector);
			reference->context = context;
			reference->parameter = parameter;
			reference->value.x = value.x;
			reference->value.y = value.y;
			reference->value.z = value.z;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829330
		void SetParameter(const ParameterName& context, const ParameterName& parameter, math::Vector2 value)
		{
			ParameterReference<math::Vector2>* reference = BeginStructEvent(ApplyVector2);
			reference->context = context;
			reference->parameter = parameter;
			reference->value.x = value.x;
			reference->value.y = value.y;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829390
		void SetParameter(const ParameterName& context, const ParameterName& parameter, math::Vector4 value)
		{
			ParameterReference<math::Vector4>* reference = BeginStructEvent(ApplyVector4);
			reference->context = context;
			reference->parameter = parameter;
			reference->value.x = value.x;
			reference->value.y = value.y;
			reference->value.z = value.z;
			reference->value.w = value.w;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829400
		void SetParameter(const ParameterName& context, const ParameterName& parameter, math::pddiColour value)
		{
			ParameterReference<math::pddiColour>* reference = BeginStructEvent(ApplyColour);
			reference->context = context;
			reference->parameter = parameter;
			reference->value = value;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829B60
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, float value,
			float duration)
		{
			ParameterReference<float>* reference = BeginStructEvent(StartFloat);
			reference->context = context;
			reference->parameter = parameter;
			reference->value = value;
			reference->duration = duration;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829BC0
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, int value,
			float duration)
		{
			ParameterReference<int>* reference = BeginStructEvent(StartInt);
			reference->context = context;
			reference->parameter = parameter;
			reference->value = value;
			reference->duration = duration;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829C20
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, bool value,
			float duration)
		{
			ParameterReference<bool>* reference = BeginStructEvent(StartBool);
			reference->context = context;
			reference->parameter = parameter;
			reference->value = value;
			reference->duration = duration;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829C80
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, math::Vector value,
			float duration)
		{
			ParameterReference<math::Vector>* reference = BeginStructEvent(StartVector);
			reference->context = context;
			reference->parameter = parameter;
			reference->value.x = value.x;
			reference->value.y = value.y;
			reference->value.z = value.z;
			reference->duration = duration;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829CF0
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, math::Vector4 value,
			float duration)
		{
			ParameterReference<math::Vector4>* reference = BeginStructEvent(StartVector4);
			reference->context = context;
			reference->parameter = parameter;
			reference->value.x = value.x;
			reference->value.y = value.y;
			reference->value.z = value.z;
			reference->value.w = value.w;
			reference->duration = duration;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829D70
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter,
			math::pddiColour value, float duration)
		{
			ParameterReference<math::pddiColour>* reference = BeginStructEvent(StartColour);
			reference->context = context;
			reference->parameter = parameter;
			reference->value = value;
			reference->duration = duration;
			PushRenderEvent(gStructEvent);
			gStructEvent = 0;
		}

		// FUNCTION: ENGINE 0x10829A00
		void SetParameterEnabled(const ParameterName& context, bool enabled)
		{
			SetParameter(context, gParameterEnable, enabled);
		}

		// FUNCTION: ENGINE 0x10829A20
		void SetFloatParameter(const ParameterName& context, const ParameterName& parameter, float value)
		{
			SetParameter(context, parameter, value);
		}

		// FUNCTION: ENGINE 0x10829A40
		void SetIntParameter(const ParameterName& context, const ParameterName& parameter, int value)
		{
			SetParameter(context, parameter, value);
		}

		// FUNCTION: ENGINE 0x10829A50
		void SetBoolParameter(const ParameterName& context, const ParameterName& parameter, bool value)
		{
			SetParameter(context, parameter, value);
		}

		// FUNCTION: ENGINE 0x10829A60
		void SetParameter(const ParameterName& context, const ParameterName& parameter, const math::Vector* value)
		{
			SetParameter(context, parameter, *value);
		}

		// FUNCTION: ENGINE 0x10829A90
		void SetParameter(const ParameterName& context, const ParameterName& parameter, const math::Vector2* value)
		{
			SetParameter(context, parameter, *value);
		}

		// FUNCTION: ENGINE 0x10829AC0
		void SetParameter(const ParameterName& context, const ParameterName& parameter, const math::Vector4* value)
		{
			SetParameter(context, parameter, *value);
		}

		// FUNCTION: ENGINE 0x10829B00
		void SetParameter(const ParameterName& context, const ParameterName& parameter,
			const math::pddiColour* value)
		{
			SetParameter(context, parameter, *value);
		}

		// FUNCTION: ENGINE 0x10829F80
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			float value)
		{
			InterpolateParameter(context, parameter, value, duration);
		}

		// FUNCTION: ENGINE 0x10829FB0
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			int value)
		{
			InterpolateParameter(context, parameter, value, duration);
		}

		// FUNCTION: ENGINE 0x10829FD0
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			bool value)
		{
			InterpolateParameter(context, parameter, value, duration);
		}

		// FUNCTION: ENGINE 0x10829FF0
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			const math::Vector* value)
		{
			InterpolateParameter(context, parameter, *value, duration);
		}

		// FUNCTION: ENGINE 0x1082A030
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			const math::Vector4* value)
		{
			InterpolateParameter(context, parameter, *value, duration);
		}

		// FUNCTION: ENGINE 0x1082A070
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			const math::pddiColour* value)
		{
			InterpolateParameter(context, parameter, *value, duration);
		}

		// The event classes the calls queue (the structure's allocation is the template function above)
		// FUNCTION: ENGINE 0x10827440
		// FUNCTION: ENGINE 0x108287C0
		template class StructRenderEvent<ParameterReference<int> >;
		// FUNCTION: ENGINE 0x108276E0
		// FUNCTION: ENGINE 0x10828A90
		template class StructRenderEvent<ParameterReference<bool> >;
		// FUNCTION: ENGINE 0x10827720
		// FUNCTION: ENGINE 0x10828AB0
		template class StructRenderEvent<ParameterReference<float> >;
		// FUNCTION: ENGINE 0x10827760
		// FUNCTION: ENGINE 0x10828AD0
		template class StructRenderEvent<ParameterReference<math::Vector> >;
		// FUNCTION: ENGINE 0x108277A0
		// FUNCTION: ENGINE 0x10828AF0
		template class StructRenderEvent<ParameterReference<math::Vector2> >;
		// FUNCTION: ENGINE 0x108277E0
		// FUNCTION: ENGINE 0x10828B10
		template class StructRenderEvent<ParameterReference<math::Vector4> >;
		// FUNCTION: ENGINE 0x10827820
		// FUNCTION: ENGINE 0x10828B30
		template class StructRenderEvent<ParameterReference<math::pddiColour> >;

		// The functions that make the events
		// FUNCTION: ENGINE 0x10828690
		template ParameterReference<int>* BeginStructEvent<ParameterReference<int> >(void (*function)(ParameterReference<int>*));
		// FUNCTION: ENGINE 0x10828830
		template ParameterReference<bool>* BeginStructEvent<ParameterReference<bool> >(void (*function)(ParameterReference<bool>*));
		// FUNCTION: ENGINE 0x10828880
		template ParameterReference<float>* BeginStructEvent<ParameterReference<float> >(void (*function)(ParameterReference<float>*));
		// FUNCTION: ENGINE 0x108288D0
		template ParameterReference<math::Vector>* BeginStructEvent<ParameterReference<math::Vector> >(void (*function)(ParameterReference<math::Vector>*));
		// FUNCTION: ENGINE 0x10828920
		template ParameterReference<math::Vector2>* BeginStructEvent<ParameterReference<math::Vector2> >(void (*function)(ParameterReference<math::Vector2>*));
		// FUNCTION: ENGINE 0x10828970
		template ParameterReference<math::Vector4>* BeginStructEvent<ParameterReference<math::Vector4> >(void (*function)(ParameterReference<math::Vector4>*));
		// FUNCTION: ENGINE 0x108289C0
		template ParameterReference<math::pddiColour>* BeginStructEvent<ParameterReference<math::pddiColour> >(void (*function)(ParameterReference<math::pddiColour>*));
	}
}
