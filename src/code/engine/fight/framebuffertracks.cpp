// The fight tracks that drive the frame buffer effects: tone mapping, fades, depth of field, colour matrices, scatter, letterbox and bloom (unit 0x10815900 - 0x10817A00).
#include "code/engine/fight/framebuffertracks.h"

namespace engine
{
	namespace framebufferfx
	{
		fight::Property** gToneMapTrackProperties;  // 0x11284C38

		// FUNCTION: ENGINE 0x108154D0
		bool ToneMapTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108154E0
		bool ToneMapTrack::SetEnable(bool newValue)
		{
			enable = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108154F0
		bool ToneMapTrack::SetBlendFromPreviousState(bool newValue)
		{
			blendFromPreviousState = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815500
		bool ToneMapTrack::SetAdaptRate(float newValue)
		{
			adaptRate = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815510
		bool ToneMapTrack::SetAverageLuminanceTarget(float newValue)
		{
			averageLuminanceTarget = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108158E0
		fight::Property* ToneMapTrack::GetProperty(int index)
		{
			return gToneMapTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x108158F0
		void ToneMapTrack::ClearProperties()
		{
			fight::FreePropertyList(&gToneMapTrackProperties);
		}

		// FUNCTION: ENGINE 0x10815900
		// ctor stores: [('mov', 'dword', 0, '0x10e6d4f4'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f'), ('mov', 'byte', 28, '0'), ('mov', 'byte', 29, '1')]
		ToneMapTrack::ToneMapTrack() : adaptRate(0.0f), averageLuminanceTarget(0.0f), timeBegin(0.0f), blendFromPreviousState(false), enable(1)
		{
		}

		// FUNCTION: ENGINE 0x10815930
		float ToneMapTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x10815940
		float ToneMapTrack::Slot10() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x10815950
		ToneMapTrack::~ToneMapTrack()
		{
		}

		// FUNCTION: ENGINE 0x10816680
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void ToneMapTrack::RegisterProperties()
		{
			if (gToneMapTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<ToneMapTrack>("timeBegin", &ToneMapTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyBool<ToneMapTrack>("enable", &ToneMapTrack::SetEnable);
				properties[1] = property;
				property = new fight::PropertyBool<ToneMapTrack>("blendFromPreviousState", &ToneMapTrack::SetBlendFromPreviousState);
				properties[2] = property;
				property = new fight::PropertyFloatConstRange<ToneMapTrack>("adaptRate", &ToneMapTrack::SetAdaptRate);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<ToneMapTrack>("averageLuminanceTarget", &ToneMapTrack::SetAverageLuminanceTarget);
				properties[4] = property;
				fight::RegisterPropertyList(properties, &gToneMapTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108165A0
		fight::TrackFactory* CreateToneMapTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<ToneMapTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108173F0
		void RegisterToneMapTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<ToneMapTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyBool<ToneMapTrack>;
		template class fight::PropertyFloatConstRange<ToneMapTrack>;
		template class fight::TrackFactoryTemplate<ToneMapTrack>;
		template class fight::TrackFactoryCasterTemplate<ToneMapTrack>;
	}

	namespace framebufferfx
	{
		fight::Property** gFadeTrackProperties;  // 0x11284C3C

		// FUNCTION: ENGINE 0x10815520
		bool FadeTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815530
		bool FadeTrack::SetTimeEnd(float newValue)
		{
			timeEnd = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815540
		bool FadeTrack::SetType(int newValue)
		{
			type = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815960
		fight::Property* FadeTrack::GetProperty(int index)
		{
			return gFadeTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10815970
		void FadeTrack::ClearProperties()
		{
			fight::FreePropertyList(&gFadeTrackProperties);
		}

		// FUNCTION: ENGINE 0x10815980
		// ctor stores: [('movss', 'dword', 16, '0.0f'), ('mov', 'dword', 0, '0x10e6d53c'), ('movss', 'dword', 20, '-1.0f'), ('mov', 'dword', 24, '0'), ('mov', 'dword', 12, '1')]
		FadeTrack::FadeTrack() : timeBegin(0.0f), timeEnd(-1.0f), type(0)
		{
			unknownC = 1;  // TODO base member
		}

		// FUNCTION: ENGINE 0x108159C0
		float FadeTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108159D0
		float FadeTrack::Slot10() const
		{
			return timeEnd - timeBegin;
		}

		// FUNCTION: ENGINE 0x108159E0
		FadeTrack::~FadeTrack()
		{
		}

		// FUNCTION: ENGINE 0x108167C0
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void FadeTrack::RegisterProperties()
		{
			if (gFadeTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<FadeTrack>("timeBegin", &FadeTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<FadeTrack>("timeEnd", &FadeTrack::SetTimeEnd);
				properties[1] = property;
				property = new fight::PropertyEnum<FadeTrack>("type", &FadeTrack::GetTypeEntry, &FadeTrack::GetTypeCount, &FadeTrack::SetType);
				properties[2] = property;
				fight::RegisterPropertyList(properties, &gFadeTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108165C0
		fight::TrackFactory* CreateFadeTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<FadeTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x10817420
		void RegisterFadeTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<FadeTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyEnum<FadeTrack>;
		template class fight::PropertyFloatConstRange<FadeTrack>;
		template class fight::TrackFactoryTemplate<FadeTrack>;
		template class fight::TrackFactoryCasterTemplate<FadeTrack>;
	}

	namespace framebufferfx
	{
		fight::Property** gDepthOfFieldTrackProperties;  // 0x11284C40

		// FUNCTION: ENGINE 0x10815550
		bool DepthOfFieldTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815560
		bool DepthOfFieldTrack::SetEnable(bool newValue)
		{
			enable = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815570
		bool DepthOfFieldTrack::SetBlendFromPreviousState(bool newValue)
		{
			blendFromPreviousState = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815580
		bool DepthOfFieldTrack::SetNearDepth(float newValue)
		{
			nearDepth = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815590
		bool DepthOfFieldTrack::SetFarDepth(float newValue)
		{
			farDepth = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108155A0
		bool DepthOfFieldTrack::SetRange(float newValue)
		{
			range = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108155B0
		bool DepthOfFieldTrack::SetAperture(float newValue)
		{
			aperture = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108159F0
		fight::Property* DepthOfFieldTrack::GetProperty(int index)
		{
			return gDepthOfFieldTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10815A00
		void DepthOfFieldTrack::ClearProperties()
		{
			fight::FreePropertyList(&gDepthOfFieldTrackProperties);
		}

		// FUNCTION: ENGINE 0x10815A10
		// ctor stores: [('movss', 'dword', 16, '1.0f'), ('movss', 'dword', 24, '1.0f'), ('movss', 'dword', 28, '1.0f'), ('mov', 'dword', 0, '0x10e6d584'), ('movss', 'dword', 20, '5.0f'), ('movss', 'dword', 32, '0.0f'), ('mov', 'byte', 36, '0'), ('mov', 'byte', 37, '1')]
		DepthOfFieldTrack::DepthOfFieldTrack() : aperture(1.0f), farDepth(5.0f), nearDepth(1.0f), range(1.0f), timeBegin(0.0f), blendFromPreviousState(false), enable(1)
		{
		}

		// FUNCTION: ENGINE 0x10815A60
		float DepthOfFieldTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x10815A70
		float DepthOfFieldTrack::Slot10() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x10815A80
		DepthOfFieldTrack::~DepthOfFieldTrack()
		{
		}

		// FUNCTION: ENGINE 0x108168B0
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void DepthOfFieldTrack::RegisterProperties()
		{
			if (gDepthOfFieldTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<DepthOfFieldTrack>("timeBegin", &DepthOfFieldTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyBool<DepthOfFieldTrack>("enable", &DepthOfFieldTrack::SetEnable);
				properties[1] = property;
				property = new fight::PropertyBool<DepthOfFieldTrack>("blendFromPreviousState", &DepthOfFieldTrack::SetBlendFromPreviousState);
				properties[2] = property;
				property = new fight::PropertyFloatConstRange<DepthOfFieldTrack>("nearDepth", &DepthOfFieldTrack::SetNearDepth);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<DepthOfFieldTrack>("farDepth", &DepthOfFieldTrack::SetFarDepth);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<DepthOfFieldTrack>("range", &DepthOfFieldTrack::SetRange);
				properties[5] = property;
				property = new fight::PropertyFloatConstRange<DepthOfFieldTrack>("aperture", &DepthOfFieldTrack::SetAperture);
				properties[6] = property;
				fight::RegisterPropertyList(properties, &gDepthOfFieldTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108165E0
		fight::TrackFactory* CreateDepthOfFieldTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<DepthOfFieldTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x10817450
		void RegisterDepthOfFieldTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<DepthOfFieldTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyBool<DepthOfFieldTrack>;
		template class fight::PropertyFloatConstRange<DepthOfFieldTrack>;
		template class fight::TrackFactoryTemplate<DepthOfFieldTrack>;
		template class fight::TrackFactoryCasterTemplate<DepthOfFieldTrack>;
	}

	namespace framebufferfx
	{
		fight::Property** gColourMatrixTrackProperties;  // 0x11284C44

		// FUNCTION: ENGINE 0x108155C0
		bool ColourMatrixTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108155D0
		bool ColourMatrixTrack::SetEnable(bool newValue)
		{
			enable = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108155E0
		bool ColourMatrixTrack::SetBlendFromPreviousState(bool newValue)
		{
			blendFromPreviousState = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108155F0
		bool ColourMatrixTrack::SetBrightness(float newValue)
		{
			brightness = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815600
		bool ColourMatrixTrack::SetContrast(float newValue)
		{
			contrast = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815610
		bool ColourMatrixTrack::SetMidpoint(float newValue)
		{
			midpoint = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815620
		bool ColourMatrixTrack::SetSaturate(float newValue)
		{
			saturate = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815630
		bool ColourMatrixTrack::SetHue(float newValue)
		{
			hue = newValue * 0.01745329238474369f;
			return true;
		}

		// FUNCTION: ENGINE 0x10815650
		bool ColourMatrixTrack::SetTint(const math::Colour128& newValue)
		{
			tint = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815A90
		fight::Property* ColourMatrixTrack::GetProperty(int index)
		{
			return gColourMatrixTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10815AA0
		void ColourMatrixTrack::ClearProperties()
		{
			fight::FreePropertyList(&gColourMatrixTrackProperties);
		}

		// FUNCTION: ENGINE 0x10815AB0
		// ctor stores: [('mov', 'dword', 0, '0x10e6d5cc'), ('movss', 'dword', 16, '1.0f'), ('movss', 'dword', 20, '1.0f'), ('movss', 'dword', 24, '1.0f'), ('movss', 'dword', 28, '1.0f'), ('movss', 'dword', 32, '0.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '0.0f'), ('movss', 'dword', 44, '0.5f'), ('movss', 'dword', 48, '1.0f'), ('movss', 'dword', 52, '0.0f'), ('mov', 'byte', 56, '0'), ('mov', 'byte', 57, '1')]
		ColourMatrixTrack::ColourMatrixTrack() : tint(1.0f, 1.0f, 1.0f, 1.0f), brightness(0.0f), contrast(0.0f), hue(0.0f), midpoint(0.5f), saturate(1.0f), timeBegin(0.0f), blendFromPreviousState(false), enable(1)
		{
		}

		// FUNCTION: ENGINE 0x10815B10
		float ColourMatrixTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x10815B20
		float ColourMatrixTrack::Slot10() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x10815B30
		ColourMatrixTrack::~ColourMatrixTrack()
		{
		}

		// FUNCTION: ENGINE 0x10816A50
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void ColourMatrixTrack::RegisterProperties()
		{
			if (gColourMatrixTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<ColourMatrixTrack>("timeBegin", &ColourMatrixTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyBool<ColourMatrixTrack>("enable", &ColourMatrixTrack::SetEnable);
				properties[1] = property;
				property = new fight::PropertyBool<ColourMatrixTrack>("blendFromPreviousState", &ColourMatrixTrack::SetBlendFromPreviousState);
				properties[2] = property;
				property = new fight::PropertyFloatConstRange<ColourMatrixTrack>("brightness", &ColourMatrixTrack::SetBrightness);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<ColourMatrixTrack>("contrast", &ColourMatrixTrack::SetContrast);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<ColourMatrixTrack>("midpoint", &ColourMatrixTrack::SetMidpoint);
				properties[5] = property;
				property = new fight::PropertyFloatConstRange<ColourMatrixTrack>("saturate", &ColourMatrixTrack::SetSaturate);
				properties[6] = property;
				property = new fight::PropertyFloatConstRange<ColourMatrixTrack>("hue", &ColourMatrixTrack::SetHue);
				properties[7] = property;
				property = new fight::PropertyColour<ColourMatrixTrack>("tint", &ColourMatrixTrack::SetTint);
				properties[8] = property;
				fight::RegisterPropertyList(properties, &gColourMatrixTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x10816600
		fight::TrackFactory* CreateColourMatrixTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<ColourMatrixTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x10817480
		void RegisterColourMatrixTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<ColourMatrixTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyBool<ColourMatrixTrack>;
		template class fight::PropertyColour<ColourMatrixTrack>;
		template class fight::PropertyFloatConstRange<ColourMatrixTrack>;
		template class fight::TrackFactoryTemplate<ColourMatrixTrack>;
		template class fight::TrackFactoryCasterTemplate<ColourMatrixTrack>;
	}

	namespace framebufferfx
	{
		fight::Property** gScatterTrackProperties;  // 0x11284C48

		// FUNCTION: ENGINE 0x10815670
		bool ScatterTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815680
		bool ScatterTrack::SetEnable(bool newValue)
		{
			enable = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815690
		bool ScatterTrack::SetBlendFromPreviousState(bool newValue)
		{
			blendFromPreviousState = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108156A0
		bool ScatterTrack::SetScatterColour(const math::Colour128& newValue)
		{
			scatterColour = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108156C0
		bool ScatterTrack::SetSaturationMin(float newValue)
		{
			saturationMin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108156D0
		bool ScatterTrack::SetSaturationMax(float newValue)
		{
			saturationMax = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108156E0
		bool ScatterTrack::SetContrastMin(float newValue)
		{
			contrastMin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108156F0
		bool ScatterTrack::SetContrastMax(float newValue)
		{
			contrastMax = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815700
		bool ScatterTrack::SetBrightnessMin(float newValue)
		{
			brightnessMin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815710
		bool ScatterTrack::SetBrightnessMax(float newValue)
		{
			brightnessMax = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815720
		bool ScatterTrack::SetTintMin(float newValue)
		{
			tintMin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815730
		bool ScatterTrack::SetTintMax(float newValue)
		{
			tintMax = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815740
		bool ScatterTrack::SetDistanceBrightening(float newValue)
		{
			distanceBrightening = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815750
		bool ScatterTrack::SetContrastDropoff(float newValue)
		{
			contrastDropoff = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815B40
		fight::Property* ScatterTrack::GetProperty(int index)
		{
			return gScatterTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10815B50
		void ScatterTrack::ClearProperties()
		{
			fight::FreePropertyList(&gScatterTrackProperties);
		}

		// FUNCTION: ENGINE 0x10815B60
		// ctor stores: [('mov', 'dword', 0, '0x10e6d614'), ('movss', 'dword', 16, '0.6078431606292725f'), ('movss', 'dword', 20, '0.8392156958580017f'), ('movss', 'dword', 24, '1.0f'), ('movss', 'dword', 28, '1.0f'), ('movss', 'dword', 32, '0.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '0.0f'), ('movss', 'dword', 44, '0.0f'), ('movss', 'dword', 48, '0.0f'), ('movss', 'dword', 52, '0.0f'), ('movss', 'dword', 56, '1.0f'), ('movss', 'dword', 60, '1.0f'), ('movss', 'dword', 64, '0.0f'), ('movss', 'dword', 68, '0.0f'), ('movss', 'dword', 72, '0.0f'), ('mov', 'byte', 76, '0'), ('mov', 'byte', 77, '1')]
		ScatterTrack::ScatterTrack() : scatterColour(0.6078431606292725f, 0.8392156958580017f, 1.0f, 1.0f), brightnessMax(0.0f), brightnessMin(0.0f), contrastDropoff(0.0f), contrastMax(0.0f), contrastMin(0.0f), distanceBrightening(0.0f), saturationMax(1.0f), saturationMin(1.0f), timeBegin(0.0f), tintMax(0.0f), tintMin(0.0f), blendFromPreviousState(false), enable(1)
		{
		}

		// FUNCTION: ENGINE 0x10815BE0
		float ScatterTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x10815BF0
		float ScatterTrack::Slot10() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x10815C00
		ScatterTrack::~ScatterTrack()
		{
		}

		// FUNCTION: ENGINE 0x10816C50
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void ScatterTrack::RegisterProperties()
		{
			if (gScatterTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("timeBegin", &ScatterTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyBool<ScatterTrack>("enable", &ScatterTrack::SetEnable);
				properties[1] = property;
				property = new fight::PropertyBool<ScatterTrack>("blendFromPreviousState", &ScatterTrack::SetBlendFromPreviousState);
				properties[2] = property;
				property = new fight::PropertyColour<ScatterTrack>("scatterColour", &ScatterTrack::SetScatterColour);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("saturationMin", &ScatterTrack::SetSaturationMin);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("saturationMax", &ScatterTrack::SetSaturationMax);
				properties[5] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("contrastMin", &ScatterTrack::SetContrastMin);
				properties[6] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("contrastMax", &ScatterTrack::SetContrastMax);
				properties[7] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("brightnessMin", &ScatterTrack::SetBrightnessMin);
				properties[8] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("brightnessMax", &ScatterTrack::SetBrightnessMax);
				properties[9] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("tintMin", &ScatterTrack::SetTintMin);
				properties[10] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("tintMax", &ScatterTrack::SetTintMax);
				properties[11] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("distanceBrightening", &ScatterTrack::SetDistanceBrightening);
				properties[12] = property;
				property = new fight::PropertyFloatConstRange<ScatterTrack>("contrastDropoff", &ScatterTrack::SetContrastDropoff);
				properties[13] = property;
				fight::RegisterPropertyList(properties, &gScatterTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x10816620
		fight::TrackFactory* CreateScatterTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<ScatterTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108174B0
		void RegisterScatterTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<ScatterTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyBool<ScatterTrack>;
		template class fight::PropertyColour<ScatterTrack>;
		template class fight::PropertyFloatConstRange<ScatterTrack>;
		template class fight::TrackFactoryTemplate<ScatterTrack>;
		template class fight::TrackFactoryCasterTemplate<ScatterTrack>;
	}

	namespace framebufferfx
	{
		fight::Property** gLetterboxTrackProperties;  // 0x11284C4C

		// FUNCTION: ENGINE 0x10815760
		bool LetterboxTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815770
		bool LetterboxTrack::SetTimeEnd(float newValue)
		{
			timeEnd = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815780
		bool LetterboxTrack::SetAspectRatio(float newValue)
		{
			aspectRatio = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815C10
		fight::Property* LetterboxTrack::GetProperty(int index)
		{
			return gLetterboxTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10815C20
		void LetterboxTrack::ClearProperties()
		{
			fight::FreePropertyList(&gLetterboxTrackProperties);
		}

		// FUNCTION: ENGINE 0x10815C30
		// ctor stores: [('movss', 'dword', 16, '1.7799999713897705f'), ('movss', 'dword', 20, '0.0f'), ('mov', 'dword', 0, '0x10e6d65c'), ('movss', 'dword', 24, '-1.0f'), ('mov', 'dword', 12, '1')]
		LetterboxTrack::LetterboxTrack() : aspectRatio(1.7799999713897705f), timeBegin(0.0f), timeEnd(-1.0f)
		{
			unknownC = 1;  // TODO base member
		}

		// FUNCTION: ENGINE 0x10815C70
		float LetterboxTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x10815C80
		float LetterboxTrack::Slot10() const
		{
			return timeEnd - timeBegin;
		}

		// FUNCTION: ENGINE 0x10815C90
		LetterboxTrack::~LetterboxTrack()
		{
		}

		// FUNCTION: ENGINE 0x10816F50
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void LetterboxTrack::RegisterProperties()
		{
			if (gLetterboxTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<LetterboxTrack>("timeBegin", &LetterboxTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<LetterboxTrack>("timeEnd", &LetterboxTrack::SetTimeEnd);
				properties[1] = property;
				property = new fight::PropertyFloatConstRange<LetterboxTrack>("aspectRatio", &LetterboxTrack::SetAspectRatio);
				properties[2] = property;
				fight::RegisterPropertyList(properties, &gLetterboxTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x10816640
		fight::TrackFactory* CreateLetterboxTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<LetterboxTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108174E0
		void RegisterLetterboxTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<LetterboxTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyFloatConstRange<LetterboxTrack>;
		template class fight::TrackFactoryTemplate<LetterboxTrack>;
		template class fight::TrackFactoryCasterTemplate<LetterboxTrack>;
	}

	namespace framebufferfx
	{
		fight::Property** gBloomTrackProperties;  // 0x11284C50

		// FUNCTION: ENGINE 0x10815790
		bool BloomTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108157A0
		bool BloomTrack::SetTimeEnd(float newValue)
		{
			timeEnd = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108157B0
		bool BloomTrack::SetEnable(bool newValue)
		{
			enable = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108157C0
		bool BloomTrack::SetDisableOnFinish(bool newValue)
		{
			disableOnFinish = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108157D0
		bool BloomTrack::SetBlendFromPreviousState(bool newValue)
		{
			blendFromPreviousState = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108157E0
		bool BloomTrack::SetBrightness(float newValue)
		{
			brightness = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108157F0
		bool BloomTrack::SetContrast(float newValue)
		{
			contrast = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815800
		bool BloomTrack::SetMidpoint(float newValue)
		{
			midpoint = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815810
		bool BloomTrack::SetSaturate(float newValue)
		{
			saturate = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815820
		bool BloomTrack::SetHue(float newValue)
		{
			hue = newValue * 0.01745329238474369f;
			return true;
		}

		// FUNCTION: ENGINE 0x10815840
		bool BloomTrack::SetTint(const math::Colour128& newValue)
		{
			tint = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815860
		bool BloomTrack::SetBloom(float newValue)
		{
			bloom = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815870
		bool BloomTrack::SetBackbuffer(float newValue)
		{
			backbuffer = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815880
		bool BloomTrack::SetRadiusX(float newValue)
		{
			radiusX = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815890
		bool BloomTrack::SetRadiusY(float newValue)
		{
			radiusY = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108158A0
		bool BloomTrack::SetColour(const math::Colour128& newValue)
		{
			colour = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108158C0
		bool BloomTrack::SetLuminanceCutoff(float newValue)
		{
			luminanceCutoff = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108158D0
		bool BloomTrack::SetFalloff(float newValue)
		{
			falloff = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10815CA0
		fight::Property* BloomTrack::GetProperty(int index)
		{
			return gBloomTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10815CB0
		void BloomTrack::ClearProperties()
		{
			fight::FreePropertyList(&gBloomTrackProperties);
		}

		// FUNCTION: ENGINE 0x10815CC0
		// ctor stores: [('mov', 'dword', 0, '0x10e6d6ac'), ('movss', 'dword', 16, '0.21176470816135406f'), ('movss', 'dword', 20, '0.7137255072593689f'), ('movss', 'dword', 24, '0.07058823853731155f'), ('movss', 'dword', 28, '1.0f'), ('movss', 'dword', 32, '1.0f'), ('movss', 'dword', 36, '1.0f'), ('movss', 'dword', 40, '1.0f'), ('movss', 'dword', 44, '1.0f'), ('movss', 'dword', 52, '1.0f'), ('movss', 'dword', 64, '1.0f'), ('movss', 'dword', 72, '1.0f'), ('movss', 'dword', 76, '0.5f'), ('movss', 'dword', 88, '1.0f'), ('mov', 'byte', 101, '1'), ('mov', 'byte', 102, '1'), ('mov', 'dword', 12, '1'), ('movss', 'dword', 48, '0.0f'), ('movss', 'dword', 56, '0.0f'), ('movss', 'dword', 60, '0.0f'), ('movss', 'dword', 68, '0.0f'), ('movss', 'dword', 80, '10.0f'), ('movss', 'dword', 84, '10.0f'), ('movss', 'dword', 92, '0.0f'), ('movss', 'dword', 96, '-1.0f'), ('mov', 'byte', 100, '0')]
		BloomTrack::BloomTrack() : colour(0.21176470816135406f, 0.7137255072593689f, 0.07058823853731155f, 1.0f), tint(1.0f, 1.0f, 1.0f, 1.0f), backbuffer(0.0f), bloom(1.0f), brightness(0.0f), contrast(0.0f), falloff(1.0f), hue(0.0f), luminanceCutoff(1.0f), midpoint(0.5f), radiusX(10.0f), radiusY(10.0f), saturate(1.0f), timeBegin(0.0f), timeEnd(-1.0f), blendFromPreviousState(false), disableOnFinish(1), enable(1)
		{
			unknownC = 1;  // TODO base member
		}

		// FUNCTION: ENGINE 0x10815D90
		float BloomTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x10815DA0
		float BloomTrack::Slot10() const
		{
			return timeEnd - timeBegin;
		}

		// FUNCTION: ENGINE 0x10815DB0
		BloomTrack::~BloomTrack()
		{
		}

		// FUNCTION: ENGINE 0x10817030
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void BloomTrack::RegisterProperties()
		{
			if (gBloomTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<BloomTrack>("timeBegin", &BloomTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("timeEnd", &BloomTrack::SetTimeEnd);
				properties[1] = property;
				property = new fight::PropertyBool<BloomTrack>("enable", &BloomTrack::SetEnable);
				properties[2] = property;
				property = new fight::PropertyBool<BloomTrack>("disableOnFinish", &BloomTrack::SetDisableOnFinish);
				properties[3] = property;
				property = new fight::PropertyBool<BloomTrack>("blendFromPreviousState", &BloomTrack::SetBlendFromPreviousState);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("brightness", &BloomTrack::SetBrightness);
				properties[5] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("contrast", &BloomTrack::SetContrast);
				properties[6] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("midpoint", &BloomTrack::SetMidpoint);
				properties[7] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("saturate", &BloomTrack::SetSaturate);
				properties[8] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("hue", &BloomTrack::SetHue);
				properties[9] = property;
				property = new fight::PropertyColour<BloomTrack>("tint", &BloomTrack::SetTint);
				properties[10] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("bloom", &BloomTrack::SetBloom);
				properties[11] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("backbuffer", &BloomTrack::SetBackbuffer);
				properties[12] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("radiusX", &BloomTrack::SetRadiusX);
				properties[13] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("radiusY", &BloomTrack::SetRadiusY);
				properties[14] = property;
				property = new fight::PropertyColour<BloomTrack>("colour", &BloomTrack::SetColour);
				properties[15] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("luminanceCutoff", &BloomTrack::SetLuminanceCutoff);
				properties[16] = property;
				property = new fight::PropertyFloatConstRange<BloomTrack>("falloff", &BloomTrack::SetFalloff);
				properties[17] = property;
				fight::RegisterPropertyList(properties, &gBloomTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x10816660
		fight::TrackFactory* CreateBloomTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<BloomTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x10817510
		void RegisterBloomTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<BloomTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyBool<BloomTrack>;
		template class fight::PropertyColour<BloomTrack>;
		template class fight::PropertyFloatConstRange<BloomTrack>;
		template class fight::TrackFactoryTemplate<BloomTrack>;
		template class fight::TrackFactoryCasterTemplate<BloomTrack>;
	}

}
