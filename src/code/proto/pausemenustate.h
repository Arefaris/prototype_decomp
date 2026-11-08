// proto::PauseMenuState (name from the accessor GetPauseMenuState, which is the only name the binary gives): the state of the
// pause menu. Only the members the head-up display calls are declared (they start and stop the sounds of the pop-ups and
// of the poison effect); the member names are guesses.
#ifndef PROTO_PAUSEMENUSTATE_H
#define PROTO_PAUSEMENUSTATE_H

namespace proto
{
	class PauseMenuState
	{
	public:
		// 0x1049B8A0: starts or stops the sound of the poison effect
		void Unknown1049B8A0(bool poisoned);
		// 0x1049BA60: plays the sound of a pop-up that stays open
		void Unknown1049BA60();
	};

	// 0x1049B3D0
	PauseMenuState* GetPauseMenuState();
}

#endif
