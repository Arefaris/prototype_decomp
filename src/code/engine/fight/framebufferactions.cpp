// The actions of the frame buffer tracks (tone mapping, fades, depth of field, colour matrices, scatter, letterbox and bloom; unit 0x108BB810 - 0x108BC250, no assert path; file name guessed). The tracks are in framebuffertracks.cpp.
#include "code/engine/fight/framebufferactions.h"
#include "code/engine/fight/fightcommon.h"
#include "code/engine/render/async/canvas.h"
#include "code/engine/render/async/shaderparameter.h"
#include "code/engine/render/viewhandle.h"
#include "code/math/pddicolour.h"
#include "code/math/vector4.h"
#include "code/pure3d/framebufferpass.h"
#include "code/pure3d/passnames.h"

namespace engine
{
	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBC40
		BloomAction::BloomAction(BloomTrack* newTrack)
			: fight::Action(0x600), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB810
		BloomAction::~BloomAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC100
		fight::Action* BloomTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new BloomAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBD00
		ToneMapAction::ToneMapAction(ToneMapTrack* newTrack)
			: fight::Action(0x200), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB850
		ToneMapAction::~ToneMapAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC130
		fight::Action* ToneMapTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new ToneMapAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBE10
		bool ScatterAction::Slot5(int arg, float value)
		{
			return false;
		}

		// FUNCTION: ENGINE 0x108BBDA0
		ScatterAction::ScatterAction(ScatterTrack* newTrack)
			: fight::Action(0x200), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB890
		ScatterAction::~ScatterAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC160
		fight::Action* ScatterTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new ScatterAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBE20
		DepthOfFieldAction::DepthOfFieldAction(DepthOfFieldTrack* newTrack)
			: fight::Action(0x200), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB8D0
		DepthOfFieldAction::~DepthOfFieldAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC190
		fight::Action* DepthOfFieldTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new DepthOfFieldAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBEC0
		ColourMatrixAction::ColourMatrixAction(ColourMatrixTrack* newTrack)
			: fight::Action(0x200), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB910
		ColourMatrixAction::~ColourMatrixAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC1C0
		fight::Action* ColourMatrixTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new ColourMatrixAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BAE40
		bool FadeAction::Slot7(int arg, float value)
		{
			return true;
		}

		// FUNCTION: ENGINE 0x108BBF60
		FadeAction::FadeAction(FadeTrack* newTrack)
			: fight::Action(0xA00), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB950
		FadeAction::~FadeAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC1F0
		fight::Action* FadeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new FadeAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBFF0
		LetterboxAction::LetterboxAction(LetterboxTrack* newTrack)
			: fight::Action(0x600), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB990
		LetterboxAction::~LetterboxAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC220
		fight::Action* LetterboxTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new LetterboxAction(this);
		}

	}

}

namespace engine
{
	namespace framebufferfx
	{
		// Sets the parameters of the tone map pass to the track's values
		// FUNCTION: ENGINE 0x108BAB40
		__declspec(noinline) static bool ApplyToneMap(ToneMapTrack* track)
		{
			render::SetParameterEnabled(pure3d::gTonemapPass, track->enable);
			render::SetFloatParameter(pure3d::gTonemapPass, pure3d::gToneMapName100, track->adaptRate);
			render::SetFloatParameter(pure3d::gTonemapPass, pure3d::gToneMapNameFC, track->averageLuminanceTarget);
			return false;
		}

		// The same, moving to the values over the track's duration
		// FUNCTION: ENGINE 0x108BAB90
		__declspec(noinline) static bool BlendToneMap(ToneMapTrack* track)
		{
			render::SetParameterEnabled(pure3d::gTonemapPass, track->enable);
			render::InterpolateParameterOver(pure3d::gTonemapPass, pure3d::gToneMapName100, track->Slot10(), track->adaptRate);
			render::InterpolateParameterOver(pure3d::gTonemapPass, pure3d::gToneMapNameFC, track->Slot10(), track->averageLuminanceTarget);
			return false;
		}

		// FUNCTION: ENGINE 0x108BBD70
		bool ToneMapAction::Slot5(int arg, float value)
		{
			if (link.object != 0)
			{
				if (link.object->blendFromPreviousState)
				{
					BlendToneMap(link.object);
					return false;
				}
				ApplyToneMap(link.object);
			}
			return false;
		}

		// Sets the parameters of the depth of field pass to the track's values
		// FUNCTION: ENGINE 0x108BAC00
		__declspec(noinline) static bool ApplyDepthOfField(DepthOfFieldTrack* track)
		{
			render::SetParameterEnabled(pure3d::gDepthOfFieldPass, track->enable);
			render::SetFloatParameter(pure3d::gDepthOfFieldPass, pure3d::gParamDofNearDepth, track->nearDepth);
			render::SetFloatParameter(pure3d::gDepthOfFieldPass, pure3d::gParamDofFarDepth, track->farDepth);
			render::SetFloatParameter(pure3d::gDepthOfFieldPass, pure3d::gParamDofRange, track->range);
			render::SetFloatParameter(pure3d::gDepthOfFieldPass, pure3d::gParamDofAperture, track->aperture);
			return false;
		}

		// The same, moving to the values over the track's duration
		// FUNCTION: ENGINE 0x108BAC80
		__declspec(noinline) static bool BlendDepthOfField(DepthOfFieldTrack* track)
		{
			render::SetParameterEnabled(pure3d::gDepthOfFieldPass, true);
			render::InterpolateParameterOver(pure3d::gDepthOfFieldPass, pure3d::gParamDofNearDepth, track->Slot10(), track->nearDepth);
			render::InterpolateParameterOver(pure3d::gDepthOfFieldPass, pure3d::gParamDofFarDepth, track->Slot10(), track->farDepth);
			render::InterpolateParameterOver(pure3d::gDepthOfFieldPass, pure3d::gParamDofRange, track->Slot10(), track->range);
			render::InterpolateParameterOver(pure3d::gDepthOfFieldPass, pure3d::gParamDofAperture, track->Slot10(), track->aperture);
			return false;
		}

		// FUNCTION: ENGINE 0x108BBE90
		bool DepthOfFieldAction::Slot5(int arg, float value)
		{
			if (link.object != 0)
			{
				if (link.object->blendFromPreviousState)
				{
					BlendDepthOfField(link.object);
					return false;
				}
				ApplyDepthOfField(link.object);
			}
			return false;
		}

		// Sets the parameters of the colour matrix pass to the track's values
		// FUNCTION: ENGINE 0x108BB350
		__declspec(noinline) static bool ApplyColourMatrix(ColourMatrixTrack* track)
		{
			render::SetParameterEnabled(pure3d::gColourMatrixPass, track->enable);
			render::SetFloatParameter(pure3d::gColourMatrixPass, pure3d::gParamBrightness, track->brightness);
			render::SetFloatParameter(pure3d::gColourMatrixPass, pure3d::gParamConstrast, track->contrast);
			render::SetFloatParameter(pure3d::gColourMatrixPass, pure3d::gParamMidpoint, track->midpoint);
			render::SetFloatParameter(pure3d::gColourMatrixPass, pure3d::gParamSaturation, track->saturate);
			render::SetFloatParameter(pure3d::gColourMatrixPass, pure3d::gParamHue, track->hue);
			math::Vector4 channels;
			channels.x = track->tint.r;
			channels.y = track->tint.g;
			channels.z = track->tint.b;
			channels.w = track->tint.a;
			math::pddiColour tint(channels);
			render::SetParameter(pure3d::gColourMatrixPass, pure3d::gParamTint, &tint);
			return false;
		}

		// The same, moving to the values over the track's duration
		// FUNCTION: ENGINE 0x108BB430
		__declspec(noinline) static bool BlendColourMatrix(ColourMatrixTrack* track)
		{
			render::SetParameterEnabled(pure3d::gColourMatrixPass, true);
			render::InterpolateParameterOver(pure3d::gColourMatrixPass, pure3d::gParamBrightness, track->Slot10(), track->brightness);
			render::InterpolateParameterOver(pure3d::gColourMatrixPass, pure3d::gParamConstrast, track->Slot10(), track->contrast);
			render::InterpolateParameterOver(pure3d::gColourMatrixPass, pure3d::gParamMidpoint, track->Slot10(), track->midpoint);
			render::InterpolateParameterOver(pure3d::gColourMatrixPass, pure3d::gParamSaturation, track->Slot10(), track->saturate);
			render::InterpolateParameterOver(pure3d::gColourMatrixPass, pure3d::gParamHue, track->Slot10(), track->hue);
			math::Vector4 channels;
			channels.x = track->tint.r;
			channels.y = track->tint.g;
			channels.z = track->tint.b;
			channels.w = track->tint.a;
			math::pddiColour tint(channels);
			render::InterpolateParameterOver(pure3d::gColourMatrixPass, pure3d::gParamTint, track->Slot10(), &tint);
			return false;
		}

		// FUNCTION: ENGINE 0x108BBF30
		bool ColourMatrixAction::Slot5(int arg, float value)
		{
			if (link.object != 0)
			{
				if (link.object->blendFromPreviousState)
				{
					BlendColourMatrix(link.object);
					return false;
				}
				ApplyColourMatrix(link.object);
			}
			return false;
		}

		// Sets the parameters of the bloom pass to the track's values
		// FUNCTION: ENGINE 0x108BAF20
		__declspec(noinline) static void ApplyBloom(BloomTrack* track)
		{
			render::SetParameterEnabled(pure3d::gBloomPass, true);
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gParamBrightness, track->brightness);
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gParamConstrast, track->contrast);
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gParamMidpoint, track->midpoint);
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gParamSaturation, track->saturate);
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gParamHue, track->hue);
			math::Vector4 channels;
			channels.x = track->tint.r;
			channels.y = track->tint.g;
			channels.z = track->tint.b;
			channels.w = track->tint.a;
			{
				math::pddiColour tint(channels);
				render::SetParameter(pure3d::gBloomPass, pure3d::gParamTint, &tint);
			}
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gParamBloomstrength, track->bloom);
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gParamBackbufferstrength, track->backbuffer);
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gParamRadiusx, track->radiusX);
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gParamRadiusy, track->radiusY);
			channels.x = track->colour.r;
			channels.y = track->colour.g;
			channels.z = track->colour.b;
			channels.w = track->colour.a;
			{
				math::pddiColour colour(channels);
				render::SetParameter(pure3d::gBloomPass, pure3d::gColour, &colour);
			}
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gCutoff, track->luminanceCutoff);
			render::SetFloatParameter(pure3d::gBloomPass, pure3d::gFalloffPower, track->falloff);
		}

		// The same, moving to the values over the track's duration
		// FUNCTION: ENGINE 0x108BB0E0
		__declspec(noinline) static void BlendBloom(BloomTrack* track)
		{
			render::SetParameterEnabled(pure3d::gBloomPass, true);
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamBrightness, track->Slot10(), track->brightness);
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamConstrast, track->Slot10(), track->contrast);
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamMidpoint, track->Slot10(), track->midpoint);
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamSaturation, track->Slot10(), track->saturate);
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamHue, track->Slot10(), track->hue);
			math::Vector4 channels;
			channels.x = track->tint.r;
			channels.y = track->tint.g;
			channels.z = track->tint.b;
			channels.w = track->tint.a;
			{
				math::pddiColour tint(channels);
				render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamTint, track->Slot10(), &tint);
			}
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamBloomstrength, track->Slot10(), track->bloom);
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamBackbufferstrength, track->Slot10(), track->backbuffer);
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamRadiusx, track->Slot10(), track->radiusX);
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gParamRadiusy, track->Slot10(), track->radiusY);
			channels.x = track->colour.r;
			channels.y = track->colour.g;
			channels.z = track->colour.b;
			channels.w = track->colour.a;
			{
				math::pddiColour colour(channels);
				render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gColour, track->Slot10(), &colour);
			}
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gCutoff, track->Slot10(), track->luminanceCutoff);
			render::InterpolateParameterOver(pure3d::gBloomPass, pure3d::gFalloffPower, track->Slot10(), track->falloff);
		}

		// FUNCTION: ENGINE 0x108BBCB0
		bool BloomAction::Slot5(int arg, float value)
		{
			if (link.object == 0)
			{
				return false;
			}
			if (link.object->blendFromPreviousState)
			{
				BlendBloom(link.object);
				return true;
			}
			ApplyBloom(link.object);
			return true;
		}

		// FUNCTION: ENGINE 0x108BBCE0
		void BloomAction::Slot6()
		{
			if (link.object == 0 || link.object->disableOnFinish)
			{
				render::SetParameterEnabled(pure3d::gBloomPass, false);
			}
		}

		// The canvas calls of a fade by its kind (the first four arguments are the same for all)
		// FUNCTION: ENGINE 0x108BAD30
		__declspec(noinline) static bool ApplyFade(FadeTrack* track)
		{
			switch (track->type)
			{
			case 0:
				render::QueueCanvas108BCA10(1.0f, false, 0.0f, true, track->Slot10(), false, false);
				return false;
			case 1:
				render::QueueCanvas108BCA10(1.0f, false, 0.0f, true, 0.0f, false, false);
				render::QueueCanvas108BCA80(false, 0.0f, true, track->Slot10(), false);
				return false;
			case 2:
				render::QueueCanvas108BCA10(1.0f, false, 0.0f, true, track->Slot10(), true, false);
				return false;
			case 3:
				render::QueueCanvas108BCA10(1.0f, false, 0.0f, true, 0.0f, true, false);
				render::QueueCanvas108BCA80(false, 0.0f, true, track->Slot10(), false);
				return false;
			case 4:
				render::QueueCanvas108BCA10(1.0f, false, 0.0f, true, track->Slot10(), true, true);
				return false;
			case 5:
				render::QueueCanvas108BCA10(1.0f, false, 0.0f, true, 0.0f, true, true);
				render::QueueCanvas108BCA80(false, 0.0f, true, track->Slot10(), true);
				return false;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108BBFD0
		bool FadeAction::Slot5(int arg, float value)
		{
			if (link.object != 0)
			{
				ApplyFade(link.object);
			}
			return true;
		}

		// FUNCTION: ENGINE 0x108BC060
		bool LetterboxAction::Slot5(int arg, float value)
		{
			if (link.object == 0)
			{
				return false;
			}
			float target = link.object->aspectRatio;
			float ratio = GetAspect() / target;
			if (ratio < 1.0f)
			{
				render::QueueCanvas108BCAC0(driving::gOne - ratio, false, 0.0f, false, 0.0f);
			}
			return true;
		}

		// FUNCTION: ENGINE 0x108BC0C0
		void LetterboxAction::Slot6()
		{
			if (link.object != 0)
			{
				float target = link.object->aspectRatio;
				float ratio = GetAspect() / target;
				if (ratio < 1.0f)
				{
					render::QueueCanvas108BCB00(false, 0.0f, true, 0.0f);
				}
			}
		}
	}
}
