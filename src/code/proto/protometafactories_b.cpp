// The factories and creators the proto game registers for its reflected classes (content/metafactory.h): the class meta
// type, the factory or creator and the registration function of each class, in the order the engine has them
// (0x10290630 on; no assert path names the unit, the file names are guesses).
#include "code/content/metafactory.h"
#include "code/proto/behaviours/anchortogroundbehaviour.h"
#include "code/proto/behaviours/charactermotionbehaviour.h"
#include "code/proto/behaviours/collisionactionbehaviour.h"
#include "code/proto/behaviours/motionstatebehaviour.h"

namespace content
{
	template ClassMetaType* GetClassMetaType<proto::CharacterMotionBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::CollisionActionBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::AnchorToGroundBehaviour>();
	template ClassMetaType* GetClassMetaType<proto::MotionStateBehaviour>();
}

namespace engine
{
	template class MetaBehaviourCreatorImpl<proto::CharacterMotionBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CharacterMotionBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::CollisionActionBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::CollisionActionBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::AnchorToGroundBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::AnchorToGroundBehaviour>();
	template class MetaBehaviourCreatorImpl<proto::MotionStateBehaviour>;
	template void RegisterMetaBehaviourCreator<proto::MotionStateBehaviour>();
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10293EA0
// FUNCTION: ENGINE 0x10293F00
// FUNCTION: ENGINE 0x10293F30
// FUNCTION: ENGINE 0x10294180
// FUNCTION: ENGINE 0x102941E0
// FUNCTION: ENGINE 0x10294210
// FUNCTION: ENGINE 0x10297C20
// FUNCTION: ENGINE 0x10297C80
// FUNCTION: ENGINE 0x10297CB0
// FUNCTION: ENGINE 0x102980F0
// FUNCTION: ENGINE 0x10298150
// FUNCTION: ENGINE 0x10298180
// FUNCTION: ENGINE 0x1029B820
// FUNCTION: ENGINE 0x1029B9A0
// FUNCTION: ENGINE 0x1029D860
// FUNCTION: ENGINE 0x1029DB00
