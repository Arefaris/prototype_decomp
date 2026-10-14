// engine::Display (name guess): the display mode object; only one accessor is reconstructed so far. Unit 0x10616xxx
// (no assert path); member names are guesses.
#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H

namespace engine
{
	class Display
	{
	public:
		// 0x10616130
		int GetWidth();

		int unknown0;
		int width;
	};
}

#endif
