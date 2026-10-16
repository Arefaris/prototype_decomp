// proto::LODRenderBehaviour (RTTI 0x11075320, vftable 0x10DEA9F4, base engine::Behaviour): the behaviour that picks
// which level of detail of a drawable set is drawn, fades between two levels and drives the drawables of the level it
// chose. File name, member names and the layout are guesses; the RTTI member getters name the reflected fields
// (a bool, a DrawableArchetype reference and a pure3d::Animation reference).
#ifndef PROTO_RENDER_LODRENDERBEHAVIOUR_H
#define PROTO_RENDER_LODRENDERBEHAVIOUR_H

namespace engine
{
	class Behaviour;
}

namespace proto
{
	class LODRenderBehaviour
	{
	public:
		// 0x102DA3A0: hands the drawables of the level range over to the game object and queues the transform
		void ChangeDrawableLevels(unsigned int previous, const unsigned char* first, const unsigned char* last);
		// 0x102DA700: picks the level the fade position asks for and tells the drawables when it changes
		void UpdateLevel();

		// +0 (the vftable of engine::Behaviour), +4 the game object's handle, +0x1C / +0x24 two drawable handles
		unsigned char unknown0[0x3C];
		// +0x3C: the smallest number of levels that is ever handed over
		unsigned int minimumLevels;
		// +0x40 / +0x44: the drawables that are ready (equal: none)
		const unsigned char* readyBegin;
		const unsigned char* readyEnd;
		unsigned char unknown48[8];
		// +0x50 / +0x54: the level table, four bytes of the level record per entry
		const unsigned char* levelsBegin;
		const unsigned char* levelsEnd;
		unsigned char unknown58[8];
		// +0x60: the level drawn now (-1: none yet)
		unsigned int level;
		// +0x64: how far the fade between two levels has run (0 - 1)
		float fade;
		unsigned char unknown68[0x9C - 0x68];
		// +0x9C: bit 0 the drawables are bound, bit 2 the level was forced
		unsigned char flags;
	};
}

#endif
