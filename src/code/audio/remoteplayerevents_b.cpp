// More instances of audio::RemotePlayerEvent_Param1, the ones the helicopter and vehicle sound players post events with
// (the engine's unit keeps its own copy of every member, after the instances of remoteplayerevents.cpp). The file name is a guess.
#include "code/audio/remoteplayerevent.h"
#include "code/mgraph/nodes.h"

template class audio::RemotePlayerEvent_Param1<const om::Vector&>;
template class audio::RemotePlayerEvent_Param1<float>;
template class audio::RemotePlayerEvent_Param1<const om::DynamicArray<om::String, unsigned short>&>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104A6150
// FUNCTION: ENGINE 0x104A6170
// FUNCTION: ENGINE 0x104A61C0
// FUNCTION: ENGINE 0x104A61E0
// FUNCTION: ENGINE 0x104A6220
// FUNCTION: ENGINE 0x104A6240
// FUNCTION: ENGINE 0x104A6250
// FUNCTION: ENGINE 0x104A6260
// FUNCTION: ENGINE 0x104A6280
// FUNCTION: ENGINE 0x104A70F0
// FUNCTION: ENGINE 0x104A7120
// FUNCTION: ENGINE 0x104A71A0
// FUNCTION: ENGINE 0x104A72B0
// FUNCTION: ENGINE 0x104A72E0
// FUNCTION: ENGINE 0x104A7380
// FUNCTION: ENGINE 0x104A73C0
// FUNCTION: ENGINE 0x104A73E0
// FUNCTION: ENGINE 0x104A7410
// FUNCTION: ENGINE 0x104A7430
