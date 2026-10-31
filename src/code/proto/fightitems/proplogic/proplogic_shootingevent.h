// Fight items of the proplogic group: ShootingEventCondition (unit 0x1025E0E0 - 0x1025EFA0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_PROPLOGIC_PROPLOGIC_SHOOTINGEVENT_H
#define PROTO_FIGHTITEMS_PROPLOGIC_PROPLOGIC_SHOOTINGEVENT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/proplogic/proplogicdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace proplogic
		{
			// RTTI: proto::fightitems::proplogic::ShootingEventCondition (10 vftable slots, 0x10 bytes)
			class ShootingEventCondition : public fight::Condition
			{
			public:
				// 0x1025EC90
				ShootingEventCondition();
				virtual ~ShootingEventCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1025E130, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetEvent(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int event;  // +0xC
			};

			extern fight::Property** gShootingEventConditionProperties;
			fight::ConditionFactory* CreateShootingEventConditionFactory(const char* name);
			void RegisterShootingEventConditionFactory(fight::TrackRegistry* registry, const char* name);

			// The event the third argument of a shooting event condition points at when it is a shot (type 0x2100A); the layout is read from
			// the condition (name guess)
			struct ShootingEvent
			{
				unsigned char unknown0[8];
				int type;  // +0x8
				unsigned char unknownC[8];
				unsigned short shot;  // +0x14
			};
		}
	}
}

#endif
