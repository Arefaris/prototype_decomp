// pure3d::extensions::proto::ConsumeEffect and ConsumeEffect2 (unit around 0x10721360 - 0x10726500; file name guessed
// from the class). Names are guesses.
#include <new>

#include "code/pure3d/extensions/proto/consumeeffect.h"

namespace pure3d
{
	namespace extensions
	{
		namespace proto
		{
			// FUNCTION: ENGINE 0x10724AF0
			ConsumeEffect::SharedData::SharedData() : RefCounted(NO_BARRIER)
			{
			}

			// FUNCTION: ENGINE 0x10725180
			void ConsumeEffect::SetTarget(Entity* target)
			{
			}

			// FUNCTION: ENGINE 0x10725190
			void ConsumeEffect::Unknown5()
			{
			}

			// FUNCTION: ENGINE 0x10721490
			bool ConsumeEffect::IsSupported(Animation* animation)
			{
				return false;
			}

			// FUNCTION: ENGINE 0x10726270
			void ConsumeEffect2::SetTarget(Entity* target)
			{
			}

			// FUNCTION: ENGINE 0x10726280
			void ConsumeEffect2::Unknown5()
			{
			}

			// FUNCTION: ENGINE 0x10721360
			bool ConsumeEffect2::IsSupported(Animation* animation)
			{
				return false;
			}
		}
	}
}
