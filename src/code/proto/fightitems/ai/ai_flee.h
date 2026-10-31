// Fight items of the ai group: FleeTrack (unit 0x10231FB0 - 0x10232390; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_FLEE_H
#define PROTO_FIGHTITEMS_AI_AI_FLEE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::FleeTrack (16 vftable slots, 0x1C bytes)
			class FleeTrack : public fight::Track
			{
			public:
				// 0x10232040
				FleeTrack();
				virtual ~FleeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F3470, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFleeDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float fleeDistance;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
			};

			extern fight::Property** gFleeTrackProperties;
			fight::TrackFactory* CreateFleeTrackFactory(const char* name);
			void RegisterFleeTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
