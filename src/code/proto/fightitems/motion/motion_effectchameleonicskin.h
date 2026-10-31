// Fight items of the motion group: EffectChameleonicSkinTrack (unit 0x1015C310 - 0x1015CB40; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_EFFECTCHAMELEONICSKIN_H
#define PROTO_FIGHTITEMS_MOTION_EFFECTCHAMELEONICSKIN_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::EffectChameleonicSkinTrack (16 vftable slots, 0x44 bytes)
			class EffectChameleonicSkinTrack : public fight::Track
			{
			public:
				// 0x1015C460
				EffectChameleonicSkinTrack();
				virtual ~EffectChameleonicSkinTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BAB50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetActionOnBegin(int newValue);
				bool SetActionOnEnd(int newValue);
				bool SetWarpingFactor(float newValue);
				bool SetWarpOffsetScale(float newValue);
				bool SetColourType(int newValue);
				bool SetColour(const math::Colour128& newValue);
				bool SetColourMix(float newValue);
				bool SetBlurRadius(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Colour128 colour;  // +0x10
					float blurRadius;  // +0x20
					float colourMix;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					float warpOffsetScale;  // +0x30
					float warpingFactor;  // +0x34
					int actionOnBegin;  // +0x38
					int actionOnEnd;  // +0x3C
					int colourType;  // +0x40
			};

			extern fight::Property** gEffectChameleonicSkinTrackProperties;
			fight::TrackFactory* CreateEffectChameleonicSkinTrackFactory(const char* name);
			void RegisterEffectChameleonicSkinTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::EffectChameleonicSkinAction (9 vftable slots, 0x2C bytes)
			class EffectChameleonicSkinAction : public fight::Action
			{
			public:
				// 0x100BA9B0
				EffectChameleonicSkinAction(EffectChameleonicSkinTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100BA910
				virtual ~EffectChameleonicSkinAction();

				// vftable slot 5 (0x100BA820)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100BAC30)
				virtual void Slot6();
				// vftable slot 7 (0x100BABA0)
				virtual bool Slot7(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<EffectChameleonicSkinTrack> link;  // +0x20
			};

			// ---- actions end
		}
	}
}

#endif
