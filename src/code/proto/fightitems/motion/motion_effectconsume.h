// Fight items of the motion group: EffectConsumeTrack (unit 0x1015CB40 - 0x1015D620; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_EFFECTCONSUME_H
#define PROTO_FIGHTITEMS_MOTION_EFFECTCONSUME_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::EffectConsumeTrack (16 vftable slots, 0x68 bytes)
			class EffectConsumeTrack : public fight::Track
			{
			public:
				// 0x1015CD10
				EffectConsumeTrack();
				virtual ~EffectConsumeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BB150, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetShader(const fight::Name& newValue);
				bool SetSpreadRate(float newValue);
				bool SetGrowthThreshold(float newValue);
				bool SetConsumeMode(int newValue);
				bool SetTimeReverse(float newValue);
				bool SetUseTimeReveal(bool newValue);
				bool SetTimeReveal(float newValue);
				bool SetRevealMode(int newValue);
				bool SetStartJoint1(const fight::Name& newValue);
				bool SetStartOffset1(const math::Vector& newValue);
				bool SetUseSecondStartPoint(bool newValue);
				bool SetStartJoint2(const fight::Name& newValue);
				bool SetStartOffset2(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name shader;  // +0x10
					fight::Name startJoint1;  // +0x18
					fight::Name startJoint2;  // +0x20
					math::Vector startOffset1;  // +0x28
					math::Vector startOffset2;  // +0x34
					float growthThreshold;  // +0x40
					float spreadRate;  // +0x44
					float timeBegin;  // +0x48
					float timeEnd;  // +0x4C
					float timeReveal;  // +0x50
					float timeReverse;  // +0x54
					int consumeMode;  // +0x58
					int revealMode;  // +0x5C
					bool useSecondStartPoint;  // +0x60
					bool useTimeReveal;  // +0x61
					unsigned char unknown62[0x6];
			};

			extern fight::Property** gEffectConsumeTrackProperties;
			fight::TrackFactory* CreateEffectConsumeTrackFactory(const char* name);
			void RegisterEffectConsumeTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
