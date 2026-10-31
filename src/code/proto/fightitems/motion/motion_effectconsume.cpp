// Fight items of the motion group: EffectConsumeTrack (unit 0x1015CB40 - 0x1015D620; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_effectconsume.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gEffectConsumeTrackProperties;  // 0x11254500

			// FUNCTION: ENGINE 0x1015CB40
			bool EffectConsumeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CB60
			bool EffectConsumeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CCB0
			bool EffectConsumeTrack::SetShader(const fight::Name& newValue)
			{
				shader = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CB80
			bool EffectConsumeTrack::SetSpreadRate(float newValue)
			{
				spreadRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CBA0
			bool EffectConsumeTrack::SetGrowthThreshold(float newValue)
			{
				growthThreshold = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CBC0
			bool EffectConsumeTrack::SetConsumeMode(int newValue)
			{
				consumeMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CBD0
			bool EffectConsumeTrack::SetTimeReverse(float newValue)
			{
				timeReverse = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CBF0
			bool EffectConsumeTrack::SetUseTimeReveal(bool newValue)
			{
				useTimeReveal = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CC00
			bool EffectConsumeTrack::SetTimeReveal(float newValue)
			{
				timeReveal = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CC20
			bool EffectConsumeTrack::SetRevealMode(int newValue)
			{
				revealMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CCD0
			bool EffectConsumeTrack::SetStartJoint1(const fight::Name& newValue)
			{
				startJoint1 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CC30
			bool EffectConsumeTrack::SetStartOffset1(const math::Vector& newValue)
			{
				startOffset1.x = newValue.x;
				startOffset1.y = newValue.y;
				startOffset1.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CC50
			bool EffectConsumeTrack::SetUseSecondStartPoint(bool newValue)
			{
				useSecondStartPoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CCF0
			bool EffectConsumeTrack::SetStartJoint2(const fight::Name& newValue)
			{
				startJoint2 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CC60
			bool EffectConsumeTrack::SetStartOffset2(const math::Vector& newValue)
			{
				startOffset2.x = newValue.x;
				startOffset2.y = newValue.y;
				startOffset2.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1015CC80
			fight::Property* EffectConsumeTrack::GetProperty(int index)
			{
				return gEffectConsumeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015CCA0
			void EffectConsumeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gEffectConsumeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015CD10
			EffectConsumeTrack::EffectConsumeTrack() : startOffset1(0.0f, 0.0f, 0.0f), startOffset2(0.0f, 0.0f, 0.0f), growthThreshold(1.0f), spreadRate(1.0f), timeBegin(0.0f), timeEnd(-1.0f), timeReveal(1.0f), timeReverse(1.0f), consumeMode(0), revealMode(0), useSecondStartPoint(false), useTimeReveal(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1015CDD0
			float EffectConsumeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1015CDE0
			float EffectConsumeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1015CDF0
			EffectConsumeTrack::~EffectConsumeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015D160
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EffectConsumeTrack::RegisterProperties()
			{
				if (gEffectConsumeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<EffectConsumeTrack>("timeBegin", &EffectConsumeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<EffectConsumeTrack>("timeEnd", &EffectConsumeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<EffectConsumeTrack>("shader", &EffectConsumeTrack::SetShader);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<EffectConsumeTrack>("spreadRate", &EffectConsumeTrack::SetSpreadRate);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<EffectConsumeTrack>("growthThreshold", &EffectConsumeTrack::SetGrowthThreshold);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<EffectConsumeTrack>("consumeMode", gEffectConsumeTrackConsumeModeTable, gEffectConsumeTrackConsumeModeCount, &EffectConsumeTrack::SetConsumeMode);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<EffectConsumeTrack>("timeReverse", &EffectConsumeTrack::SetTimeReverse);
					properties[6] = property;
					property = new fight::PropertyBool<EffectConsumeTrack>("useTimeReveal", &EffectConsumeTrack::SetUseTimeReveal);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<EffectConsumeTrack>("timeReveal", &EffectConsumeTrack::SetTimeReveal);
					properties[8] = property;
					property = new fight::PropertyEnumConstList<EffectConsumeTrack>("revealMode", gEffectConsumeTrackRevealModeTable, gEffectConsumeTrackRevealModeCount, &EffectConsumeTrack::SetRevealMode);
					properties[9] = property;
					property = new fight::PropertyNameList<EffectConsumeTrack>("startJoint1", &EffectConsumeTrack::SetStartJoint1);
					properties[10] = property;
					property = new fight::PropertyVector<EffectConsumeTrack>("startOffset1", &EffectConsumeTrack::SetStartOffset1);
					properties[11] = property;
					property = new fight::PropertyBool<EffectConsumeTrack>("useSecondStartPoint", &EffectConsumeTrack::SetUseSecondStartPoint);
					properties[12] = property;
					property = new fight::PropertyNameList<EffectConsumeTrack>("startJoint2", &EffectConsumeTrack::SetStartJoint2);
					properties[13] = property;
					property = new fight::PropertyVector<EffectConsumeTrack>("startOffset2", &EffectConsumeTrack::SetStartOffset2);
					properties[14] = property;
					fight::RegisterPropertyList(properties, &gEffectConsumeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015D050
			fight::TrackFactory* CreateEffectConsumeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<EffectConsumeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015D080
			void RegisterEffectConsumeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<EffectConsumeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100BB030
			// EQUIVALENT: scheduling; the engine stores the vftable before it takes the link's address, ours after it (94.6 %)
			EffectConsumeAction::EffectConsumeAction(EffectConsumeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), unknown20(-1), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x100BAF40
			EffectConsumeAction::~EffectConsumeAction()
			{
			}

			// FUNCTION: ENGINE 0x100BB150
			fight::Action* EffectConsumeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new EffectConsumeAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<EffectConsumeTrack>;
			template class fight::PropertyName<EffectConsumeTrack>;
			template class fight::PropertyEnumConstList<EffectConsumeTrack>;
			template class fight::PropertyBool<EffectConsumeTrack>;
			template class fight::PropertyNameList<EffectConsumeTrack>;
			template class fight::PropertyVector<EffectConsumeTrack>;
			template class fight::TrackFactoryTemplate<EffectConsumeTrack>;
			template class fight::TrackFactoryCasterTemplate<EffectConsumeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1015CE00
// FUNCTION: ENGINE 0x1015CE10
// FUNCTION: ENGINE 0x1015CE40
// FUNCTION: ENGINE 0x1015CE70
// FUNCTION: ENGINE 0x1015CEA0
// FUNCTION: ENGINE 0x1015CED0
// FUNCTION: ENGINE 0x1015CEE0
// FUNCTION: ENGINE 0x1015CF20
// FUNCTION: ENGINE 0x1015CF30
// FUNCTION: ENGINE 0x1015CF60
// FUNCTION: ENGINE 0x1015CF80
// FUNCTION: ENGINE 0x1015CF90
// FUNCTION: ENGINE 0x1015CFC0
// FUNCTION: ENGINE 0x1015CFE0
// FUNCTION: ENGINE 0x1015CFF0
// FUNCTION: ENGINE 0x1015D020
// FUNCTION: ENGINE 0x1015D040
// FUNCTION: ENGINE 0x1015D0B0
// FUNCTION: ENGINE 0x1015D0E0
// FUNCTION: ENGINE 0x1015D100
// FUNCTION: ENGINE 0x1015D130
// FUNCTION: ENGINE 0x1015D150
// FUNCTION: ENGINE 0x1015D580
// FUNCTION: ENGINE 0x1015D5B0
// FUNCTION: ENGINE 0x1015D5D0
// FUNCTION: ENGINE 0x100BAE00
// FUNCTION: ENGINE 0x100BAE90
// FUNCTION: ENGINE 0x100BB0B0
