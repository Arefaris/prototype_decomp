// Fight items of the motion group: ClassNameCondition (unit 0x10149690 - 0x10149A90; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_CLASSNAME_H
#define PROTO_FIGHTITEMS_MOTION_CLASSNAME_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ClassNameCondition (10 vftable slots, 0x20 bytes)
			class ClassNameCondition : public fight::Condition
			{
			public:
				// 0x101496F0
				ClassNameCondition();
				virtual ~ClassNameCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100A2000, another unit)
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

			extern fight::Property** gClassNameConditionProperties;
			fight::ConditionFactory* CreateClassNameConditionFactory(const char* name);
			void RegisterClassNameConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
