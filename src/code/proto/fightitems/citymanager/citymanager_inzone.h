// Fight items of the citymanager group: InZoneCondition (unit 0x1027DCE0 - 0x1027E100; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_CITYMANAGER_CITYMANAGER_INZONE_H
#define PROTO_FIGHTITEMS_CITYMANAGER_CITYMANAGER_INZONE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/citymanager/citymanagerdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace citymanager
		{
			// RTTI: proto::fightitems::citymanager::InZoneCondition (10 vftable slots, 0x10 bytes)
			class InZoneCondition : public fight::Condition
			{
			public:
				// 0x1027DDF0
				InZoneCondition();
				virtual ~InZoneCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1027DD00, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetZoneType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int zoneType;  // +0xC
			};

			extern fight::Property** gInZoneConditionProperties;
			fight::ConditionFactory* CreateInZoneConditionFactory(const char* name);
			void RegisterInZoneConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
