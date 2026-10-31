// Fight items of the motion group: UnlockableCondition (unit 0x101C4FB0 - 0x101C5300; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_UNLOCKABLE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_UNLOCKABLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::UnlockableCondition (10 vftable slots, 0x10 bytes)
			class UnlockableCondition : public fight::Condition
			{
			public:
				// 0x101C4FF0
				UnlockableCondition();
				virtual ~UnlockableCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10125670, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetUnlockable(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int unlockable;  // +0xC
			};

			extern fight::Property** gUnlockableConditionProperties;
			fight::ConditionFactory* CreateUnlockableConditionFactory(const char* name);
			void RegisterUnlockableConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
