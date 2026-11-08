#include "code/content/metafactory.h"
#include "code/engine/audio/audioemitterbehaviour.h"
#include "code/engine/audio/audiozonebehaviour.h"
#include "code/engine/audio/audioudobehaviour.h"

namespace content
{
	template ClassMetaType* GetClassMetaType<engine::AudioEmitterBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::AudioUDOBehaviour>();
	template ClassMetaType* GetClassMetaType<engine::AudioZoneBehaviour>();
}

namespace engine
{
	template class MetaBehaviourCreatorImpl<engine::AudioEmitterBehaviour>;
	template class MetaBehaviourCreatorImpl<engine::AudioUDOBehaviour>;
	template class MetaBehaviourCreatorImpl<engine::AudioZoneBehaviour>;
	template void RegisterMetaBehaviourCreator<engine::AudioEmitterBehaviour>();
	template void RegisterMetaBehaviourCreator<engine::AudioUDOBehaviour>();
	template void RegisterMetaBehaviourCreator<engine::AudioZoneBehaviour>();

	// The registration of the meta object factories that the second table of the start-up adds (nothing is left to
	// register there)
	// FUNCTION: ENGINE 0x1092B170
	void RegisterMoreMetaObjectFactories()
	{
	}

	// The registration of the behaviour creators that the second table of the start-up adds
	// FUNCTION: ENGINE 0x1092B450
	void RegisterMoreMetaBehaviourCreators()
	{
		RegisterMetaBehaviourCreator<AudioEmitterBehaviour>();
		RegisterMetaBehaviourCreator<AudioUDOBehaviour>();
		RegisterMetaBehaviourCreator<AudioZoneBehaviour>();
	}
}

// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x1092B180
// FUNCTION: ENGINE 0x1092B1D0
// FUNCTION: ENGINE 0x1092B200
// FUNCTION: ENGINE 0x1092B220
// FUNCTION: ENGINE 0x1092B270
// FUNCTION: ENGINE 0x1092B2A0
// FUNCTION: ENGINE 0x1092B2C0
// FUNCTION: ENGINE 0x1092B310
// FUNCTION: ENGINE 0x1092B340
// FUNCTION: ENGINE 0x1092B360
// FUNCTION: ENGINE 0x1092B3B0
// FUNCTION: ENGINE 0x1092B400
