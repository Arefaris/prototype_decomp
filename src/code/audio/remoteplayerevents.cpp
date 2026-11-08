// The instances of audio::RemotePlayerEvent_Param1 and _Param2 the game posts events with (the engine's unit keeps one
// copy of every member of each: constructor, Execute, destructors, class operator new / delete). The file name is a guess.
#include "code/audio/remoteplayerevent.h"
#include "code/mgraph/nodes.h"
#include "code/om/name.h"

template class audio::RemotePlayerEvent_Param1<unsigned int>;
template class audio::RemotePlayerEvent_Param1<bool>;
template class audio::RemotePlayerEvent_Param1<const om::String&>;
template class audio::RemotePlayerEvent_Param2<unsigned int, float>;
template class audio::RemotePlayerEvent_Param1<const dsp::MixVoiceChannelBinVolumes&>;
template class audio::RemotePlayerEvent_Param1<const om::DynamicArray<om::Name<om::CaseSensitive64BitKey>, unsigned short>&>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104A2CC0
// FUNCTION: ENGINE 0x104A2CD0
// FUNCTION: ENGINE 0x104A2D20
// FUNCTION: ENGINE 0x104A2E10
// FUNCTION: ENGINE 0x104A2E30
// FUNCTION: ENGINE 0x104A3480
// FUNCTION: ENGINE 0x104A3510
// FUNCTION: ENGINE 0x104A3530
// FUNCTION: ENGINE 0x104A3550
// FUNCTION: ENGINE 0x104A3590
// FUNCTION: ENGINE 0x104A35B0
// FUNCTION: ENGINE 0x104A35F0
// FUNCTION: ENGINE 0x104A3610
// FUNCTION: ENGINE 0x104A3630
// FUNCTION: ENGINE 0x104A3670
// FUNCTION: ENGINE 0x104A3690
// FUNCTION: ENGINE 0x104A36F0
// FUNCTION: ENGINE 0x104A3730
// FUNCTION: ENGINE 0x104A3740
// FUNCTION: ENGINE 0x104A3750
// FUNCTION: ENGINE 0x104A3770
// FUNCTION: ENGINE 0x104A3790
// FUNCTION: ENGINE 0x104A37B0
// FUNCTION: ENGINE 0x104A37D0
// FUNCTION: ENGINE 0x104A37F0
// FUNCTION: ENGINE 0x104A3810
// FUNCTION: ENGINE 0x104A38E0
// FUNCTION: ENGINE 0x104A39C0
// FUNCTION: ENGINE 0x104A3B10
// FUNCTION: ENGINE 0x104A3DE0
// FUNCTION: ENGINE 0x104A4420
// FUNCTION: ENGINE 0x104A4450
// FUNCTION: ENGINE 0x104A4480
// FUNCTION: ENGINE 0x104A44C0
// FUNCTION: ENGINE 0x104A44F0
// FUNCTION: ENGINE 0x104A4540
// FUNCTION: ENGINE 0x104A4600
// FUNCTION: ENGINE 0x104A4950
// FUNCTION: ENGINE 0x104A4980
// FUNCTION: ENGINE 0x104A49B0
// FUNCTION: ENGINE 0x104A49E0
// FUNCTION: ENGINE 0x104A4A20
// FUNCTION: ENGINE 0x104A56F0
// FUNCTION: ENGINE 0x104A5730
// FUNCTION: ENGINE 0x104A5750
// FUNCTION: ENGINE 0x104A5780
// FUNCTION: ENGINE 0x104A57B0
