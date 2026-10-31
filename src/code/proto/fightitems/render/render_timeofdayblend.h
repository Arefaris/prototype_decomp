// Fight items of the render group: TimeOfDayBlendTrack (unit 0x102643C0 - 0x10264E40; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_RENDER_RENDER_TIMEOFDAYBLEND_H
#define PROTO_FIGHTITEMS_RENDER_RENDER_TIMEOFDAYBLEND_H

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
			// RTTI: proto::fightitems::render::TimeOfDayBlendTrack (16 vftable slots, 0x48 bytes)
			class TimeOfDayBlendTrack : public fight::Track
			{
			public:
				// 0x10264580
				TimeOfDayBlendTrack();
				virtual ~TimeOfDayBlendTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102618A0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetGroupName(const fight::Name& newValue);
				bool SetVariationName(const fight::Name& newValue);
				bool SetFadeIn(float newValue);
				bool SetDuration(float newValue);
				bool SetFadeOut(float newValue);
				bool SetLevel(int newValue);
				bool SetSky(bool newValue);
				bool SetGlobalLighting(bool newValue);
				bool SetLighting(bool newValue);
				bool SetBloom(bool newValue);
				bool SetColourMatrix(bool newValue);
				bool SetShaders(bool newValue);
				bool SetClouds(bool newValue);
				bool SetFog(bool newValue);
				bool SetAbortable(bool newValue);
				bool SetDynamicDuration(bool newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name groupName;  // +0x10
					fight::Name variationName;  // +0x18
					float duration;  // +0x20
					float fadeIn;  // +0x24
					float fadeOut;  // +0x28
					float timeBegin;  // +0x2C
					float timeEnd;  // +0x30
					int level;  // +0x34
					bool abortable;  // +0x38
					bool bloom;  // +0x39
					bool clouds;  // +0x3A
					bool colourMatrix;  // +0x3B
					bool dynamicDuration;  // +0x3C
					bool fog;  // +0x3D
					bool globalLighting;  // +0x3E
					bool lighting;  // +0x3F
					bool shaders;  // +0x40
					bool sky;  // +0x41
					unsigned char unknown42[0x6];
			};

			extern fight::Property** gTimeOfDayBlendTrackProperties;
			fight::TrackFactory* CreateTimeOfDayBlendTrackFactory(const char* name);
			void RegisterTimeOfDayBlendTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
