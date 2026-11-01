// Fight items of the hit effects: FXLight_PointTrack (unit 0x10505220 - 0x1050DEE0; no assert path, the file name is a guess).
#include "code/proto/hiteffects/hiteffect_fxlight.h"

namespace proto
{
	namespace HitEffectManager
	{
		fight::Property** gFXLight_PointTrackProperties;  // 0x1126F67C

		// FUNCTION: ENGINE 0x10505220
		bool FXLight_PointTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505240
		bool FXLight_PointTrack::SetTimeEnd(float newValue)
		{
			timeEnd = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505260
		bool FXLight_PointTrack::SetEmitSpace(int newValue)
		{
			emitSpace = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105089E0
		bool FXLight_PointTrack::SetEmitJoint(const fight::Name& newValue)
		{
			emitJoint = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505280
		bool FXLight_PointTrack::SetBlendFromImpulseToHit(float newValue)
		{
			blendFromImpulseToHit = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105052A0
		bool FXLight_PointTrack::SetAttachTo(int newValue)
		{
			attachTo = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105052C0
		bool FXLight_PointTrack::SetAttachSpace(int newValue)
		{
			attachSpace = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10508A00
		bool FXLight_PointTrack::SetAttachJoint(const fight::Name& newValue)
		{
			attachJoint = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105052E0
		bool FXLight_PointTrack::SetOffset(const math::Vector& newValue)
		{
			offset.x = newValue.x;
			offset.y = newValue.y;
			offset.z = newValue.z;
			return true;
		}

		// FUNCTION: ENGINE 0x10505300
		bool FXLight_PointTrack::SetOrientation(const math::Vector& newValue)
		{
			math::Vector scaled = newValue;
			scaled.x *= 0.017453292f;
			scaled.y *= 0.017453292f;
			scaled.z *= 0.017453292f;
			orientation.x = scaled.x;
			orientation.y = scaled.y;
			orientation.z = scaled.z;
			return true;
		}

		// FUNCTION: ENGINE 0x10505350
		bool FXLight_PointTrack::SetRunTillInterrupted(bool newValue)
		{
			runTillInterrupted = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505370
		bool FXLight_PointTrack::SetWait(float newValue)
		{
			wait = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505390
		bool FXLight_PointTrack::SetFadeIn(float newValue)
		{
			fadeIn = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105053B0
		bool FXLight_PointTrack::SetDuration(float newValue)
		{
			duration = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105053D0
		bool FXLight_PointTrack::SetFadeOut(float newValue)
		{
			fadeOut = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105053F0
		bool FXLight_PointTrack::SetWaitRand(float newValue)
		{
			waitRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505410
		bool FXLight_PointTrack::SetFadeInRand(float newValue)
		{
			fadeInRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505430
		bool FXLight_PointTrack::SetDurationRand(float newValue)
		{
			durationRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505450
		bool FXLight_PointTrack::SetFadeOutRand(float newValue)
		{
			fadeOutRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505470
		bool FXLight_PointTrack::SetIntensity(float newValue)
		{
			intensity = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505490
		bool FXLight_PointTrack::SetRadius(float newValue)
		{
			radius = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105054B0
		bool FXLight_PointTrack::SetIntensityRand(float newValue)
		{
			intensityRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105054D0
		bool FXLight_PointTrack::SetRadiusRand(float newValue)
		{
			radiusRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105054F0
		bool FXLight_PointTrack::SetFlickerIntensityFreq(float newValue)
		{
			flickerIntensityFreq = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505510
		bool FXLight_PointTrack::SetFlickerIntensityFreqRand(float newValue)
		{
			flickerIntensityFreqRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505530
		bool FXLight_PointTrack::SetFlickerIntensityMag(float newValue)
		{
			flickerIntensityMag = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505550
		bool FXLight_PointTrack::SetFlickerIntensityMagRand(float newValue)
		{
			flickerIntensityMagRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505570
		bool FXLight_PointTrack::SetFlickerRadiusFreq(float newValue)
		{
			flickerRadiusFreq = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505590
		bool FXLight_PointTrack::SetFlickerRadiusFreqRand(float newValue)
		{
			flickerRadiusFreqRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105055B0
		bool FXLight_PointTrack::SetFlickerRadiusMag(float newValue)
		{
			flickerRadiusMag = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105055D0
		bool FXLight_PointTrack::SetFlickerRadiusMagRand(float newValue)
		{
			flickerRadiusMagRand = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105055F0
		bool FXLight_PointTrack::SetStartColour(const math::Colour128& newValue)
		{
			startColour = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505620
		bool FXLight_PointTrack::SetEndColour(const math::Colour128& newValue)
		{
			endColour = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10505650
		bool FXLight_PointTrack::SetFalloff(bool newValue)
		{
			falloff = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105088B0
		fight::Property* FXLight_PointTrack::GetProperty(int index)
		{
			return gFXLight_PointTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x105088D0
		void FXLight_PointTrack::ClearProperties()
		{
			fight::FreePropertyList(&gFXLight_PointTrackProperties);
		}

		// FUNCTION: ENGINE 0x10508AC0
		FXLight_PointTrack::FXLight_PointTrack() : endColour(1.0f, 1.0f, 1.0f, 1.0f), startColour(1.0f, 1.0f, 1.0f, 1.0f), offset(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f), blendFromImpulseToHit(0.5f), duration(1.0f), durationRand(0.0f), fadeIn(0.0f), fadeInRand(0.0f), fadeOut(1.0f), fadeOutRand(0.0f), flickerIntensityFreq(0.0f), flickerIntensityFreqRand(0.0f), flickerIntensityMag(0.0f), flickerIntensityMagRand(0.0f), flickerRadiusFreq(0.0f), flickerRadiusFreqRand(0.0f), flickerRadiusMag(0.0f), flickerRadiusMagRand(0.0f), intensity(1.0f), intensityRand(0.0f), radius(1e+01f), radiusRand(0.0f), timeBegin(0.0f), timeEnd(-1.0f), wait(0.0f), waitRand(0.0f), attachSpace(0), attachTo(0), emitSpace(0), falloff(true), runTillInterrupted(false)
		{
		}

		// FUNCTION: ENGINE 0x10508C60
		float FXLight_PointTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x10508C70
		float FXLight_PointTrack::Slot10() const
		{
			return timeEnd - timeBegin;
		}

		// FUNCTION: ENGINE 0x10508C80
		FXLight_PointTrack::~FXLight_PointTrack()
		{
		}

		// FUNCTION: ENGINE 0x1050BF40
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void FXLight_PointTrack::RegisterProperties()
		{
			if (gFXLight_PointTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("timeBegin", &FXLight_PointTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("timeEnd", &FXLight_PointTrack::SetTimeEnd);
				properties[1] = property;
				property = new fight::PropertyEnumConstList<FXLight_PointTrack>("emitSpace", gFXLight_PointTrackEmitSpaceTable, gFXLight_PointTrackEmitSpaceCount, &FXLight_PointTrack::SetEmitSpace);
				properties[2] = property;
				property = new fight::PropertyNameList<FXLight_PointTrack>("emitJoint", &FXLight_PointTrack::SetEmitJoint);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("blendFromImpulseToHit", &FXLight_PointTrack::SetBlendFromImpulseToHit);
				properties[4] = property;
				property = new fight::PropertyEnumConstList<FXLight_PointTrack>("attachTo", gFXLight_PointTrackAttachToTable, gFXLight_PointTrackAttachToCount, &FXLight_PointTrack::SetAttachTo);
				properties[5] = property;
				property = new fight::PropertyEnumConstList<FXLight_PointTrack>("attachSpace", gFXLight_PointTrackAttachSpaceTable, gFXLight_PointTrackAttachSpaceCount, &FXLight_PointTrack::SetAttachSpace);
				properties[6] = property;
				property = new fight::PropertyNameList<FXLight_PointTrack>("attachJoint", &FXLight_PointTrack::SetAttachJoint);
				properties[7] = property;
				property = new fight::PropertyVector<FXLight_PointTrack>("offset", &FXLight_PointTrack::SetOffset);
				properties[8] = property;
				property = new fight::PropertyVector<FXLight_PointTrack>("orientation", &FXLight_PointTrack::SetOrientation);
				properties[9] = property;
				property = new fight::PropertyBool<FXLight_PointTrack>("runTillInterrupted", &FXLight_PointTrack::SetRunTillInterrupted);
				properties[10] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("wait", &FXLight_PointTrack::SetWait);
				properties[11] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("fadeIn", &FXLight_PointTrack::SetFadeIn);
				properties[12] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("duration", &FXLight_PointTrack::SetDuration);
				properties[13] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("fadeOut", &FXLight_PointTrack::SetFadeOut);
				properties[14] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("waitRand", &FXLight_PointTrack::SetWaitRand);
				properties[15] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("fadeInRand", &FXLight_PointTrack::SetFadeInRand);
				properties[16] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("durationRand", &FXLight_PointTrack::SetDurationRand);
				properties[17] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("fadeOutRand", &FXLight_PointTrack::SetFadeOutRand);
				properties[18] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("intensity", &FXLight_PointTrack::SetIntensity);
				properties[19] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("radius", &FXLight_PointTrack::SetRadius);
				properties[20] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("intensityRand", &FXLight_PointTrack::SetIntensityRand);
				properties[21] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("radiusRand", &FXLight_PointTrack::SetRadiusRand);
				properties[22] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerIntensityFreq", &FXLight_PointTrack::SetFlickerIntensityFreq);
				properties[23] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerIntensityFreqRand", &FXLight_PointTrack::SetFlickerIntensityFreqRand);
				properties[24] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerIntensityMag", &FXLight_PointTrack::SetFlickerIntensityMag);
				properties[25] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerIntensityMagRand", &FXLight_PointTrack::SetFlickerIntensityMagRand);
				properties[26] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerRadiusFreq", &FXLight_PointTrack::SetFlickerRadiusFreq);
				properties[27] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerRadiusFreqRand", &FXLight_PointTrack::SetFlickerRadiusFreqRand);
				properties[28] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerRadiusMag", &FXLight_PointTrack::SetFlickerRadiusMag);
				properties[29] = property;
				property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerRadiusMagRand", &FXLight_PointTrack::SetFlickerRadiusMagRand);
				properties[30] = property;
				property = new fight::PropertyColour<FXLight_PointTrack>("startColour", &FXLight_PointTrack::SetStartColour);
				properties[31] = property;
				property = new fight::PropertyColour<FXLight_PointTrack>("endColour", &FXLight_PointTrack::SetEndColour);
				properties[32] = property;
				property = new fight::PropertyBool<FXLight_PointTrack>("falloff", &FXLight_PointTrack::SetFalloff);
				properties[33] = property;
				fight::RegisterPropertyList(properties, &gFXLight_PointTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x1050BD70
		fight::TrackFactory* CreateFXLight_PointTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<FXLight_PointTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x1050BDD0
		void RegisterFXLight_PointTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<FXLight_PointTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyFloatConstRange<FXLight_PointTrack>;
		template class fight::PropertyEnumConstList<FXLight_PointTrack>;
		template class fight::PropertyNameList<FXLight_PointTrack>;
		template class fight::PropertyVector<FXLight_PointTrack>;
		template class fight::PropertyBool<FXLight_PointTrack>;
		template class fight::PropertyColour<FXLight_PointTrack>;
		template class fight::TrackFactoryTemplate<FXLight_PointTrack>;
		template class fight::TrackFactoryCasterTemplate<FXLight_PointTrack>;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1050B7B0
// FUNCTION: ENGINE 0x1050B7C0
// FUNCTION: ENGINE 0x1050B830
// FUNCTION: ENGINE 0x1050B890
// FUNCTION: ENGINE 0x1050B8C0
// FUNCTION: ENGINE 0x1050B8F0
// FUNCTION: ENGINE 0x1050B900
// FUNCTION: ENGINE 0x1050B940
// FUNCTION: ENGINE 0x1050B950
// FUNCTION: ENGINE 0x1050B980
// FUNCTION: ENGINE 0x1050B9A0
// FUNCTION: ENGINE 0x1050B9B0
// FUNCTION: ENGINE 0x1050B9E0
// FUNCTION: ENGINE 0x1050BA00
// FUNCTION: ENGINE 0x1050BA10
// FUNCTION: ENGINE 0x1050BA40
// FUNCTION: ENGINE 0x1050BA60
// FUNCTION: ENGINE 0x1050BA70
// FUNCTION: ENGINE 0x1050BAA0
// FUNCTION: ENGINE 0x1050BAC0
// FUNCTION: ENGINE 0x1050BE30
// FUNCTION: ENGINE 0x1050BE60
// FUNCTION: ENGINE 0x1050BE80
// FUNCTION: ENGINE 0x1050DD80
// FUNCTION: ENGINE 0x1050DDB0
// FUNCTION: ENGINE 0x1050DE40
