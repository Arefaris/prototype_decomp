// Fight items of the motion group: DebugLayerCondition, DebugSphereTrack, DebugAxisTrack (unit 0x101521B0 - 0x10153160; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_debug.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDebugLayerConditionProperties;  // 0x112543CC

			// FUNCTION: ENGINE 0x101523C0
			bool DebugLayerCondition::SetDebugLayer(const char* newValue)
			{
				debugLayer = fight::ReplaceString(debugLayer, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x10152210
			bool DebugLayerCondition::SetEnabled(bool newValue)
			{
				enabled = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10152330
			fight::Property* DebugLayerCondition::GetProperty(int index)
			{
				return gDebugLayerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10152350
			void DebugLayerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDebugLayerConditionProperties);
			}

			// FUNCTION: ENGINE 0x10152360
			DebugLayerCondition::DebugLayerCondition() : fight::Condition(0), debugLayer(0), enabled(true)
			{
			}

			// FUNCTION: ENGINE 0x10152390
			DebugLayerCondition::~DebugLayerCondition()
			{
				delete[] debugLayer;
			}

			// FUNCTION: ENGINE 0x10152A30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DebugLayerCondition::RegisterProperties()
			{
				if (gDebugLayerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyString<DebugLayerCondition>("debugLayer", &DebugLayerCondition::SetDebugLayer);
					properties[0] = property;
					property = new fight::PropertyBool<DebugLayerCondition>("enabled", &DebugLayerCondition::SetEnabled);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDebugLayerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101529A0
			fight::ConditionFactory* CreateDebugLayerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DebugLayerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10152B10
			void RegisterDebugLayerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DebugLayerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDebugSphereTrackProperties;  // 0x112543D0

			// FUNCTION: ENGINE 0x10152220
			bool DebugSphereTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10152240
			bool DebugSphereTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10152260
			bool DebugSphereTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10152450
			bool DebugSphereTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10152280
			bool DebugSphereTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101522A0
			bool DebugSphereTrack::SetColour(const math::Colour128& newValue)
			{
				colour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101523F0
			fight::Property* DebugSphereTrack::GetProperty(int index)
			{
				return gDebugSphereTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10152410
			void DebugSphereTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDebugSphereTrackProperties);
			}

			// FUNCTION: ENGINE 0x101524C0
			DebugSphereTrack::DebugSphereTrack() : colour(1.0f, 1.0f, 0.0f, 1.0f), offset(0.0f, 0.0f, 0.0f), radius(1.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10152540
			float DebugSphereTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10152550
			float DebugSphereTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10152560
			DebugSphereTrack::~DebugSphereTrack()
			{
			}

			// FUNCTION: ENGINE 0x10152CB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DebugSphereTrack::RegisterProperties()
			{
				if (gDebugSphereTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DebugSphereTrack>("timeBegin", &DebugSphereTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DebugSphereTrack>("timeEnd", &DebugSphereTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DebugSphereTrack>("radius", &DebugSphereTrack::SetRadius);
					properties[2] = property;
					property = new fight::PropertyNameList<DebugSphereTrack>("joint", &DebugSphereTrack::SetJoint);
					properties[3] = property;
					property = new fight::PropertyVector<DebugSphereTrack>("offset", &DebugSphereTrack::SetOffset);
					properties[4] = property;
					property = new fight::PropertyColour<DebugSphereTrack>("colour", &DebugSphereTrack::SetColour);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gDebugSphereTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101529D0
			fight::TrackFactory* CreateDebugSphereTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DebugSphereTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10152B40
			void RegisterDebugSphereTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DebugSphereTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDebugAxisTrackProperties;  // 0x112543D4

			// FUNCTION: ENGINE 0x101522D0
			bool DebugAxisTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101522F0
			bool DebugAxisTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10152310
			bool DebugAxisTrack::SetScale(float newValue)
			{
				scale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10152470
			bool DebugAxisTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10152420
			fight::Property* DebugAxisTrack::GetProperty(int index)
			{
				return gDebugAxisTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10152440
			void DebugAxisTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDebugAxisTrackProperties);
			}

			// FUNCTION: ENGINE 0x10152570
			DebugAxisTrack::DebugAxisTrack() : scale(1.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101525D0
			float DebugAxisTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101525E0
			float DebugAxisTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101525F0
			DebugAxisTrack::~DebugAxisTrack()
			{
			}

			// FUNCTION: ENGINE 0x10152E80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DebugAxisTrack::RegisterProperties()
			{
				if (gDebugAxisTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DebugAxisTrack>("timeBegin", &DebugAxisTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DebugAxisTrack>("timeEnd", &DebugAxisTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DebugAxisTrack>("scale", &DebugAxisTrack::SetScale);
					properties[2] = property;
					property = new fight::PropertyNameList<DebugAxisTrack>("joint", &DebugAxisTrack::SetJoint);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gDebugAxisTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10152A00
			fight::TrackFactory* CreateDebugAxisTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DebugAxisTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10152B70
			void RegisterDebugAxisTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DebugAxisTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyString<DebugLayerCondition>;
			template class fight::PropertyBool<DebugLayerCondition>;
			template class fight::ConditionFactoryTemplate<DebugLayerCondition>;
			template class fight::ConditionFactoryCasterTemplate<DebugLayerCondition>;
			template class fight::PropertyFloatConstRange<DebugSphereTrack>;
			template class fight::PropertyNameList<DebugSphereTrack>;
			template class fight::PropertyVector<DebugSphereTrack>;
			template class fight::PropertyColour<DebugSphereTrack>;
			template class fight::TrackFactoryTemplate<DebugSphereTrack>;
			template class fight::TrackFactoryCasterTemplate<DebugSphereTrack>;
			template class fight::PropertyFloatConstRange<DebugAxisTrack>;
			template class fight::PropertyNameList<DebugAxisTrack>;
			template class fight::TrackFactoryTemplate<DebugAxisTrack>;
			template class fight::TrackFactoryCasterTemplate<DebugAxisTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10152490
// FUNCTION: ENGINE 0x10152610
// FUNCTION: ENGINE 0x10152620
// FUNCTION: ENGINE 0x10152650
// FUNCTION: ENGINE 0x10152660
// FUNCTION: ENGINE 0x10152690
// FUNCTION: ENGINE 0x101526A0
// FUNCTION: ENGINE 0x101526D0
// FUNCTION: ENGINE 0x10152700
// FUNCTION: ENGINE 0x10152730
// FUNCTION: ENGINE 0x10152760
// FUNCTION: ENGINE 0x10152780
// FUNCTION: ENGINE 0x10152790
// FUNCTION: ENGINE 0x101527C0
// FUNCTION: ENGINE 0x101527E0
// FUNCTION: ENGINE 0x101527F0
// FUNCTION: ENGINE 0x10152820
// FUNCTION: ENGINE 0x10152850
// FUNCTION: ENGINE 0x10152860
// FUNCTION: ENGINE 0x10152890
// FUNCTION: ENGINE 0x101528B0
// FUNCTION: ENGINE 0x101528C0
// FUNCTION: ENGINE 0x10152900
// FUNCTION: ENGINE 0x10152920
// FUNCTION: ENGINE 0x10152930
// FUNCTION: ENGINE 0x10152960
// FUNCTION: ENGINE 0x10152990
// FUNCTION: ENGINE 0x10152BA0
// FUNCTION: ENGINE 0x10152BD0
// FUNCTION: ENGINE 0x10152BF0
// FUNCTION: ENGINE 0x10152C00
// FUNCTION: ENGINE 0x10152C30
// FUNCTION: ENGINE 0x10152C50
// FUNCTION: ENGINE 0x10152C60
// FUNCTION: ENGINE 0x10152C90
// FUNCTION: ENGINE 0x10152FD0
// FUNCTION: ENGINE 0x10153020
// FUNCTION: ENGINE 0x10153050
// FUNCTION: ENGINE 0x10153070
// FUNCTION: ENGINE 0x101530A0
// FUNCTION: ENGINE 0x101530C0
// FUNCTION: ENGINE 0x10153110
