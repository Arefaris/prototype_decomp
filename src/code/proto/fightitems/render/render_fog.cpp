// Fight items of the render group: FogTrack (unit 0x102630C0 - 0x102640B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/render/render_fog.h"

namespace proto
{
	namespace fightitems
	{
		namespace render
		{
			fight::Property** gFogTrackProperties;  // 0x11255DD0

			// FUNCTION: ENGINE 0x102630C0
			bool FogTrack::SetWait(float newValue)
			{
				wait = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102630E0
			bool FogTrack::SetFadeIn(float newValue)
			{
				fadeIn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263100
			bool FogTrack::SetDuration(float newValue)
			{
				duration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263120
			bool FogTrack::SetFadeOut(float newValue)
			{
				fadeOut = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263140
			bool FogTrack::SetFadingFunction(int newValue)
			{
				fadingFunction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263160
			bool FogTrack::SetEnable(bool newValue)
			{
				enable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263410
			bool FogTrack::SetEffectController(const fight::Name& newValue)
			{
				effectController = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263180
			bool FogTrack::SetEmitSpace(int newValue)
			{
				emitSpace = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102631A0
			bool FogTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x102631C0
			bool FogTrack::SetAttachSpace(int newValue)
			{
				attachSpace = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102631E0
			bool FogTrack::SetFogAreaSize(const math::Vector& newValue)
			{
				fogAreaSize.x = newValue.x;
				fogAreaSize.y = newValue.y;
				fogAreaSize.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10263200
			bool FogTrack::SetGeneratorWidthBias(float newValue)
			{
				generatorWidthBias = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263220
			bool FogTrack::SetGeneratorHeightBias(float newValue)
			{
				generatorHeightBias = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263240
			bool FogTrack::SetFogThickness(float newValue)
			{
				fogThickness = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263260
			bool FogTrack::SetDarkTint(const math::Colour128& newValue)
			{
				darkTint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263290
			bool FogTrack::SetLightTint(const math::Colour128& newValue)
			{
				lightTint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102632C0
			bool FogTrack::SetFogHorizTiling(float newValue)
			{
				fogHorizTiling = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102632E0
			bool FogTrack::SetFogVertTiling(float newValue)
			{
				fogVertTiling = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263300
			bool FogTrack::SetRandomMoveDir(bool newValue)
			{
				randomMoveDir = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263320
			bool FogTrack::SetFogMoveDir(const math::Vector& newValue)
			{
				fogMoveDir.x = newValue.x;
				fogMoveDir.y = newValue.y;
				fogMoveDir.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10263340
			bool FogTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263360
			bool FogTrack::SetFogFalloff(float newValue)
			{
				fogFalloff = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10263380
			bool FogTrack::SetFalloffModifier(float newValue)
			{
				falloffModifier = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102633A0
			bool FogTrack::SetFogVariation(float newValue)
			{
				fogVariation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102633C0
			bool FogTrack::SetNoiseStrength(float newValue)
			{
				noiseStrength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102633E0
			fight::Property* FogTrack::GetProperty(int index)
			{
				return gFogTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10263400
			void FogTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFogTrackProperties);
			}

			// FUNCTION: ENGINE 0x10263430
			FogTrack::FogTrack() : darkTint(0.19607843f, 0.19607843f, 0.19607843f, 1.0f), lightTint(0.78431374f, 0.78431374f, 0.78431374f, 1.0f), fogAreaSize(2e+01f, 2e+01f, 2e+01f), fogMoveDir(0.0f, -1.0f, 0.0f), offset(0.0f, 0.0f, 0.0f), duration(5.0f), fadeIn(1.0f), fadeOut(1.0f), falloffModifier(4.0f), fogFalloff(1.0f), fogHorizTiling(0.5f), fogThickness(3.0f), fogVariation(2.0f), fogVertTiling(1.0f), generatorHeightBias(1.0f), generatorWidthBias(1.0f), noiseStrength(1.0f), speed(0.02f), wait(0.0f), attachSpace(0), emitSpace(0), fadingFunction(0), enable(true), randomMoveDir(true)
			{
			}

			// FUNCTION: ENGINE 0x102635D0
			float FogTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x102635E0
			float FogTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x102635F0
			FogTrack::~FogTrack()
			{
			}

			// FUNCTION: ENGINE 0x10263960
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FogTrack::RegisterProperties()
			{
				if (gFogTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FogTrack>("wait", &FogTrack::SetWait);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("fadeIn", &FogTrack::SetFadeIn);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("duration", &FogTrack::SetDuration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("fadeOut", &FogTrack::SetFadeOut);
					properties[3] = property;
					property = new fight::PropertyEnumConstList<FogTrack>("fadingFunction", gFogTrackFadingFunctionTable, gFogTrackFadingFunctionCount, &FogTrack::SetFadingFunction);
					properties[4] = property;
					property = new fight::PropertyBool<FogTrack>("enable", &FogTrack::SetEnable);
					properties[5] = property;
					property = new fight::PropertyName<FogTrack>("effectController", &FogTrack::SetEffectController);
					properties[6] = property;
					property = new fight::PropertyEnumConstList<FogTrack>("emitSpace", gFogTrackEmitSpaceTable, gFogTrackEmitSpaceCount, &FogTrack::SetEmitSpace);
					properties[7] = property;
					property = new fight::PropertyVector<FogTrack>("offset", &FogTrack::SetOffset);
					properties[8] = property;
					property = new fight::PropertyEnumConstList<FogTrack>("attachSpace", gFogTrackEmitSpaceTable, gFogTrackEmitSpaceCount, &FogTrack::SetAttachSpace);
					properties[9] = property;
					property = new fight::PropertyVector<FogTrack>("fogAreaSize", &FogTrack::SetFogAreaSize);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("generatorWidthBias", &FogTrack::SetGeneratorWidthBias);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("generatorHeightBias", &FogTrack::SetGeneratorHeightBias);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("fogThickness", &FogTrack::SetFogThickness);
					properties[13] = property;
					property = new fight::PropertyColour<FogTrack>("darkTint", &FogTrack::SetDarkTint);
					properties[14] = property;
					property = new fight::PropertyColour<FogTrack>("lightTint", &FogTrack::SetLightTint);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("fogHorizTiling", &FogTrack::SetFogHorizTiling);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("fogVertTiling", &FogTrack::SetFogVertTiling);
					properties[17] = property;
					property = new fight::PropertyBool<FogTrack>("randomMoveDir", &FogTrack::SetRandomMoveDir);
					properties[18] = property;
					property = new fight::PropertyVector<FogTrack>("fogMoveDir", &FogTrack::SetFogMoveDir);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("speed", &FogTrack::SetSpeed);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("fogFalloff", &FogTrack::SetFogFalloff);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("falloffModifier", &FogTrack::SetFalloffModifier);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("fogVariation", &FogTrack::SetFogVariation);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<FogTrack>("noiseStrength", &FogTrack::SetNoiseStrength);
					properties[24] = property;
					fight::RegisterPropertyList(properties, &gFogTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102638B0
			fight::TrackFactory* CreateFogTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FogTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102638E0
			void RegisterFogTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FogTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<FogTrack>;
			template class fight::PropertyEnumConstList<FogTrack>;
			template class fight::PropertyBool<FogTrack>;
			template class fight::PropertyName<FogTrack>;
			template class fight::PropertyVector<FogTrack>;
			template class fight::PropertyColour<FogTrack>;
			template class fight::TrackFactoryTemplate<FogTrack>;
			template class fight::TrackFactoryCasterTemplate<FogTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10263600
// FUNCTION: ENGINE 0x10263610
// FUNCTION: ENGINE 0x10263640
// FUNCTION: ENGINE 0x10263670
// FUNCTION: ENGINE 0x102636A0
// FUNCTION: ENGINE 0x102636D0
// FUNCTION: ENGINE 0x102636E0
// FUNCTION: ENGINE 0x10263720
// FUNCTION: ENGINE 0x10263730
// FUNCTION: ENGINE 0x10263760
// FUNCTION: ENGINE 0x10263780
// FUNCTION: ENGINE 0x10263790
// FUNCTION: ENGINE 0x102637C0
// FUNCTION: ENGINE 0x102637E0
// FUNCTION: ENGINE 0x102637F0
// FUNCTION: ENGINE 0x10263820
// FUNCTION: ENGINE 0x10263840
// FUNCTION: ENGINE 0x10263850
// FUNCTION: ENGINE 0x10263880
// FUNCTION: ENGINE 0x102638A0
// FUNCTION: ENGINE 0x10263910
// FUNCTION: ENGINE 0x10263940
// FUNCTION: ENGINE 0x10264000
// FUNCTION: ENGINE 0x10264030
// FUNCTION: ENGINE 0x10264060
