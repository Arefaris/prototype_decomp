// Fight items of the render group: FogTrack (unit 0x102630C0 - 0x102640B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_RENDER_RENDER_FOG_H
#define PROTO_FIGHTITEMS_RENDER_RENDER_FOG_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/render/renderdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace render
		{
			// RTTI: proto::fightitems::render::FogTrack (16 vftable slots, 0xA8 bytes)
			class FogTrack : public fight::Track
			{
			public:
				// 0x10263430
				FogTrack();
				virtual ~FogTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10261270, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetWait(float newValue);
				bool SetFadeIn(float newValue);
				bool SetDuration(float newValue);
				bool SetFadeOut(float newValue);
				bool SetFadingFunction(int newValue);
				bool SetEnable(bool newValue);
				bool SetEffectController(const fight::Name& newValue);
				bool SetEmitSpace(int newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetAttachSpace(int newValue);
				bool SetFogAreaSize(const math::Vector& newValue);
				bool SetGeneratorWidthBias(float newValue);
				bool SetGeneratorHeightBias(float newValue);
				bool SetFogThickness(float newValue);
				bool SetDarkTint(const math::Colour128& newValue);
				bool SetLightTint(const math::Colour128& newValue);
				bool SetFogHorizTiling(float newValue);
				bool SetFogVertTiling(float newValue);
				bool SetRandomMoveDir(bool newValue);
				bool SetFogMoveDir(const math::Vector& newValue);
				bool SetSpeed(float newValue);
				bool SetFogFalloff(float newValue);
				bool SetFalloffModifier(float newValue);
				bool SetFogVariation(float newValue);
				bool SetNoiseStrength(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name effectController;  // +0x10
					math::Colour128 darkTint;  // +0x18
					math::Colour128 lightTint;  // +0x28
					math::Vector fogAreaSize;  // +0x38
					math::Vector fogMoveDir;  // +0x44
					math::Vector offset;  // +0x50
					float duration;  // +0x5C
					float fadeIn;  // +0x60
					float fadeOut;  // +0x64
					float falloffModifier;  // +0x68
					float fogFalloff;  // +0x6C
					float fogHorizTiling;  // +0x70
					float fogThickness;  // +0x74
					float fogVariation;  // +0x78
					float fogVertTiling;  // +0x7C
					float generatorHeightBias;  // +0x80
					float generatorWidthBias;  // +0x84
					float noiseStrength;  // +0x88
					float speed;  // +0x8C
					float wait;  // +0x90
					int attachSpace;  // +0x94
					int emitSpace;  // +0x98
					int fadingFunction;  // +0x9C
					bool enable;  // +0xA0
					bool randomMoveDir;  // +0xA1
					unsigned char unknownA2[0x6];
			};

			extern fight::Property** gFogTrackProperties;
			fight::TrackFactory* CreateFogTrackFactory(const char* name);
			void RegisterFogTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
