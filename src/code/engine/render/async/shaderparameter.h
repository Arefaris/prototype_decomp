// The game thread's calls on the render thread's named render parameters (the values the render passes run with, by
// the name of a context and of a parameter): each call queues a StructRenderEvent that carries the two names and the
// value (RTTI: engine::render::StructRenderEvent<engine::render::ParameterReference<T>>), and the render thread sets
// the value (SetParameter) or starts an interpolator for it (InterpolateParameter, the pool is
// ParameterInterpolatorPool). The names of the calls, of the members and of the unnamed classes are guesses; the
// ParameterReference, ParameterInterpolator and StructRenderEvent templates are the engine's own names.
#ifndef ENGINE_RENDER_ASYNC_SHADERPARAMETER_H
#define ENGINE_RENDER_ASYNC_SHADERPARAMETER_H

#include "code/core/name.h"
#include "code/engine/render/async/renderevent.h"
#include "code/engine/render/async/private/parameterinterpolator.h"
#include "code/math/pddicolour.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"
#include "code/math/vector4.h"
#include "code/pure3d/context.h"

namespace pure3d
{
	// The named parameters of a render context (a tree of name -> typed value at +8; a parameter of the type is set
	// through the pointer the node holds, or through the function the node holds for the "function" types). Each
	// member returns whether the parameter exists and has the type. All names are guesses.
	class RenderParams
	{
	public:
		// 0x107A1FE0 (node types 3 and 0xE)
		bool SetUnknown1FE0(const core::Name<core::CaseSensitiveKey>* name, unsigned int value);
		// 0x107A1F80 (2 / 0xD)
		bool SetInt(const core::Name<core::CaseSensitiveKey>* name, int value);
		// 0x107A2040 (1 / 0xC)
		bool SetFloat(const core::Name<core::CaseSensitiveKey>* name, float value);
		// 0x107A20B0 (4 / 0xF)
		bool SetBool(const core::Name<core::CaseSensitiveKey>* name, bool value);
		// 0x107A2110 / 0x107A2180 / 0x107A21F0 / 0x107A27C0
		bool SetVector(const core::Name<core::CaseSensitiveKey>* name, const math::Vector* value);
		bool SetVector2(const core::Name<core::CaseSensitiveKey>* name, const math::Vector2* value);
		bool SetVector4(const core::Name<core::CaseSensitiveKey>* name, const math::Vector4* value);
		bool SetColour(const core::Name<core::CaseSensitiveKey>* name, const math::pddiColour* value);

		// The values the parameters have now: 0x107A2430 / 0x107A24F0 / 0x107A2550 / 0x107A25B0 / 0x107A2620 /
		// 0x107A2A20
		bool GetInt(const core::Name<core::CaseSensitiveKey>* name, int* value);
		bool GetFloat(const core::Name<core::CaseSensitiveKey>* name, float* value);
		bool GetBool(const core::Name<core::CaseSensitiveKey>* name, bool* value);
		bool GetVector(const core::Name<core::CaseSensitiveKey>* name, math::Vector* value);
		bool GetVector4(const core::Name<core::CaseSensitiveKey>* name, math::Vector4* value);
		bool GetColour(const core::Name<core::CaseSensitiveKey>* name, math::pddiColour* value);
	};
}

namespace engine
{
	namespace render
	{
		// What a call carries: the context's name, the parameter's name, the value and (for the calls that
		// interpolate) the duration; the events keep it at +8
		template<class T> struct ParameterReference
		{
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> context;
			core::Name<core::CaseSensitiveKey> parameter;
			T value;
			float duration;
		};

		// An event that carries a structure for a free function on the render thread
		template<class S> class StructRenderEvent : public RenderEvent
		{
		public:
			typedef void (*Function)(S*);

			explicit StructRenderEvent(Function function) : mFunction(function)
			{
			}
			virtual void Execute()
			{
				mFunction(&mData);
				delete this;
			}

			Function mFunction;
			S mData;
		};

		// The interpolators of the parameters of one type (RTTI: engine::render::ParameterInterpolator<T>). The
		// parameter goes from the value it has now (mStart) to mTarget over the duration; the value is the blend by the
		// curve ParameterInterpolatorTypeless::Ease makes of the part of the time that passed (the blend of the
		// unsigned integer colours sums the bytes). The constructors read the parameter's value into mStart.
		template<class T> class ParameterInterpolator;

		template<> class ParameterInterpolator<float> : public ParameterInterpolatorTypeless
		{
		public:
			ParameterInterpolator(pure3d::RenderParams* params, const core::Name<core::CaseSensitiveKey>& name,
				const float* target, float duration, int type);
			virtual bool Update(float time);

			float mTarget;  // +0x28
			float mStart;   // +0x2C
		};

		template<> class ParameterInterpolator<int> : public ParameterInterpolatorTypeless
		{
		public:
			ParameterInterpolator(pure3d::RenderParams* params, const core::Name<core::CaseSensitiveKey>& name,
				const int* target, float duration, int type);
			virtual bool Update(float time);

			int mTarget;  // +0x28
			int mStart;   // +0x2C
		};

		template<> class ParameterInterpolator<bool> : public ParameterInterpolatorTypeless
		{
		public:
			ParameterInterpolator(pure3d::RenderParams* params, const core::Name<core::CaseSensitiveKey>& name,
				const bool* target, float duration, int type);
			virtual bool Update(float time);

			bool mTarget;  // +0x28
			bool mStart;   // +0x29
		};

		template<> class ParameterInterpolator<math::Vector> : public ParameterInterpolatorTypeless
		{
		public:
			ParameterInterpolator(pure3d::RenderParams* params, const core::Name<core::CaseSensitiveKey>& name,
				const math::Vector* target, float duration, int type);
			virtual bool Update(float time);

			math::Vector mTarget;  // +0x28
			math::Vector mStart;   // +0x34
		};

		template<> class ParameterInterpolator<math::Vector4> : public ParameterInterpolatorTypeless
		{
		public:
			ParameterInterpolator(pure3d::RenderParams* params, const core::Name<core::CaseSensitiveKey>& name,
				const math::Vector4* target, float duration, int type);
			virtual bool Update(float time);

			math::Vector4 mTarget;  // +0x28
			math::Vector4 mStart;   // +0x38
		};

		template<> class ParameterInterpolator<math::pddiColour> : public ParameterInterpolatorTypeless
		{
		public:
			ParameterInterpolator(pure3d::RenderParams* params, const core::Name<core::CaseSensitiveKey>& name,
				const math::pddiColour* target, float duration, int type);
			virtual bool Update(float time);

			math::pddiColour mTarget;  // +0x28
			math::pddiColour mStart;   // +0x2C
		};

		// The game thread's calls (0x10829130 - 0x10829D70). The first name is the context's, the second the
		// parameter's
		typedef core::Name<core::CaseSensitiveKey> ParameterName;

		// 0x10829130: stops the interpolators of the parameter
		void StopParameterInterpolation(const ParameterName& context, const ParameterName& parameter);
		// 0x10829270 / 0x108291D0 / 0x10829220 / 0x108292C0 / 0x10829330 / 0x10829390 / 0x10829400
		void SetParameter(const ParameterName& context, const ParameterName& parameter, int value);
		void SetParameter(const ParameterName& context, const ParameterName& parameter, bool value);
		void SetParameter(const ParameterName& context, const ParameterName& parameter, float value);
		void SetParameter(const ParameterName& context, const ParameterName& parameter, math::Vector value);
		void SetParameter(const ParameterName& context, const ParameterName& parameter, math::Vector2 value);
		void SetParameter(const ParameterName& context, const ParameterName& parameter, math::Vector4 value);
		void SetParameter(const ParameterName& context, const ParameterName& parameter, math::pddiColour value);
		// 0x10829BC0 / 0x10829C20 / 0x10829B60 / 0x10829C80 / 0x10829CF0 / 0x10829D70: from the value it has now to
		// the value over the duration
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, int value,
			float duration);
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, bool value,
			float duration);
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, float value,
			float duration);
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, math::Vector value,
			float duration);
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter, math::Vector4 value,
			float duration);
		void InterpolateParameter(const ParameterName& context, const ParameterName& parameter,
			math::pddiColour value, float duration);

		// The shader parameter called "Enable" (0x11281628; shared with the pure3d units, name guess)
		extern ParameterName gParameterEnable;
		// 0x10829A00: SetParameter of "Enable"
		void SetParameterEnabled(const ParameterName& context, bool enabled);
		// 0x10829A20 / 0x10829A40 / 0x10829A50: the same calls under another name
		void SetFloatParameter(const ParameterName& context, const ParameterName& parameter, float value);
		void SetIntParameter(const ParameterName& context, const ParameterName& parameter, int value);
		void SetBoolParameter(const ParameterName& context, const ParameterName& parameter, bool value);
		// 0x10829A60 / 0x10829A90 / 0x10829AC0 / 0x10829B00: the calls that take the value by address
		void SetParameter(const ParameterName& context, const ParameterName& parameter, const math::Vector* value);
		void SetParameter(const ParameterName& context, const ParameterName& parameter, const math::Vector2* value);
		void SetParameter(const ParameterName& context, const ParameterName& parameter, const math::Vector4* value);
		void SetParameter(const ParameterName& context, const ParameterName& parameter,
			const math::pddiColour* value);
		// 0x10829F80 / 0x10829FB0 / 0x10829FD0 / 0x10829FF0 / 0x1082A030 / 0x1082A070: the interpolating calls with the duration first
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			float value);
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			int value);
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			bool value);
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			const math::Vector* value);
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			const math::Vector4* value);
		void InterpolateParameterOver(const ParameterName& context, const ParameterName& parameter, float duration,
			const math::pddiColour* value);
	}
}

#endif
