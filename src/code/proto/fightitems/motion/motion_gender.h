// Fight items of the motion group: GenderCondition (unit 0x10163BA0 - 0x10163FA0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_GENDER_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_GENDER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::GenderCondition (10 vftable slots, 0x20 bytes)
			class GenderCondition : public fight::Condition
			{
			public:
				// 0x10163C00
				GenderCondition();
				virtual ~GenderCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C1E20, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetValue(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name value;  // +0x10
					int compare;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gGenderConditionProperties;
			fight::ConditionFactory* CreateGenderConditionFactory(const char* name);
			void RegisterGenderConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
