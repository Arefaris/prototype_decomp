// engine::animation::AttachableBehaviour (the physics attachment of a game object to another; unit 0x1083B960 -
// 0x1083E670, no assert path; the file name is a guess): only the functions that do not depend on the attachment
// records are reconstructed so far.
#include "code/engine/fight/effecttrack.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/reflectedclasses2.h"

namespace engine
{
	namespace animation
	{
		// FUNCTION: ENGINE 0x1083C980
		void AttachableBehaviour::Slot1()
		{
			drawableAttribute = owner->FindAttribute(proto::gDrawableAttributeName);
		}
	}
}
