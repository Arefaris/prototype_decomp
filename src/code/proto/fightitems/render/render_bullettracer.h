// Fight items of the render group: BulletTracerTrack (unit 0x1025FC60 - 0x10262C90; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_RENDER_RENDER_BULLETTRACER_H
#define PROTO_FIGHTITEMS_RENDER_RENDER_BULLETTRACER_H

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
			// RTTI: proto::fightitems::render::BulletTracerTrack (17 vftable slots, 0xE0 bytes)
			class BulletTracerTrack : public fight::Track
			{
			public:
				// 0x10261DF0
				BulletTracerTrack();
				virtual ~BulletTracerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10260830, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);
				// vftable slot 16: whether the track overrides a property
				virtual bool Slot16(int index);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetWait(float newValue);
				bool SetHeadParameters(bool newValue);
				bool SetHeadParametersShader(const fight::Name& newValue);
				bool SetHeadParametersGenerateTime(float newValue);
				bool SetHeadParametersFadeInTime(float newValue);
				bool SetHeadParametersFadeOutTime(float newValue);
				bool SetHeadParametersFadeInTrailTime(float newValue);
				bool SetHeadParametersFadeOutTrailTime(float newValue);
				bool SetHeadParametersShrinkInTime(float newValue);
				bool SetHeadParametersShrinkOutTime(float newValue);
				bool SetHeadParametersThickness(float newValue);
				bool SetHeadParametersTextureLength(float newValue);
				bool SetHeadParametersTextureScrollRate(float newValue);
				bool SetHeadParametersStartColour(const math::Colour128& newValue);
				bool SetHeadParametersEndColour(const math::Colour128& newValue);
				bool SetTailParameters(bool newValue);
				bool SetTailParametersShader(const fight::Name& newValue);
				bool SetTailParametersGenerateTime(float newValue);
				bool SetTailParametersFadeInTime(float newValue);
				bool SetTailParametersFadeOutTime(float newValue);
				bool SetTailParametersFadeInTrailTime(float newValue);
				bool SetTailParametersFadeOutTrailTime(float newValue);
				bool SetTailParametersShrinkInTime(float newValue);
				bool SetTailParametersShrinkOutTime(float newValue);
				bool SetTailParametersThickness(float newValue);
				bool SetTailParametersTextureLength(float newValue);
				bool SetTailParametersTextureScrollRate(float newValue);
				bool SetTailParametersStartColour(const math::Colour128& newValue);
				bool SetTailParametersEndColour(const math::Colour128& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetAttachJoint(const fight::Name& newValue);

				// 0x10261CC0: sets or clears the override bits of a group's members (name guess)
				void ApplyGroup(int group, bool value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned __int64 overrideMask;  // +0x10
					fight::Name attachJoint;  // +0x18
					fight::Name headParametersShader;  // +0x20
					fight::Name tailParametersShader;  // +0x28
					math::Colour128 headParametersEndColour;  // +0x30
					math::Colour128 headParametersStartColour;  // +0x40
					math::Colour128 tailParametersEndColour;  // +0x50
					math::Colour128 tailParametersStartColour;  // +0x60
					math::Vector offset;  // +0x70
					float headParametersFadeInTime;  // +0x7C
					float headParametersFadeInTrailTime;  // +0x80
					float headParametersFadeOutTime;  // +0x84
					float headParametersFadeOutTrailTime;  // +0x88
					float headParametersGenerateTime;  // +0x8C
					float headParametersShrinkInTime;  // +0x90
					float headParametersShrinkOutTime;  // +0x94
					float headParametersTextureLength;  // +0x98
					float headParametersTextureScrollRate;  // +0x9C
					float headParametersThickness;  // +0xA0
					float tailParametersFadeInTime;  // +0xA4
					float tailParametersFadeInTrailTime;  // +0xA8
					float tailParametersFadeOutTime;  // +0xAC
					float tailParametersFadeOutTrailTime;  // +0xB0
					float tailParametersGenerateTime;  // +0xB4
					float tailParametersShrinkInTime;  // +0xB8
					float tailParametersShrinkOutTime;  // +0xBC
					float tailParametersTextureLength;  // +0xC0
					float tailParametersTextureScrollRate;  // +0xC4
					float tailParametersThickness;  // +0xC8
					float timeBegin;  // +0xCC
					float timeEnd;  // +0xD0
					float wait;  // +0xD4
					bool headParameters;  // +0xD8
					bool tailParameters;  // +0xD9
					unsigned char unknownDA[0x6];
			};

			extern fight::Property** gBulletTracerTrackProperties;
			fight::TrackFactory* CreateBulletTracerTrackFactory(const char* name);
			void RegisterBulletTracerTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
