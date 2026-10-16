// proto::LODRenderBehaviour (RTTI 0x11075320, vftable 0x10DEA9F4, base engine::Behaviour): the behaviour that picks
// which level of detail of a drawable set is drawn, fades between two levels and drives the drawables of the level it
// chose. File name, member names and the layout are guesses; the RTTI member getters name the reflected fields
// (a bool, a DrawableArchetype reference and a pure3d::Animation reference).
#ifndef PROTO_RENDER_LODRENDERBEHAVIOUR_H
#define PROTO_RENDER_LODRENDERBEHAVIOUR_H

#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	namespace camera
	{
		class Camera;
	}
}

namespace proto
{
	// A level's fade range: the distance its drawables start to fade in at, the distance they are fully faded at
	// and the rate the fade runs at (name guess; the table is 0x1107517C, three 12-byte records)
	struct LODRange
	{
		float minimum;
		float maximum;
		float rate;
	};

	// The three records (name guess)
	extern LODRange gLODRanges[3];
	// 0x11075120: a multiplier on every level's fade distance (name guess)
	extern float gLODDistanceScale;

	// 0x11263108: the object the behaviour asks for the detail scale of the camera in view (name guess). The
	// engine's method (0x1032C430) reads the float at the object's +0x68 and, without a camera, the pointer chain
	// +0x14 / +0x40; only the method is needed here.
	class LODDetailScale
	{
	public:
		// 0x1032C430: the scale the camera asks for, 1 when it has none
		float GetScale(const engine::camera::Camera* camera) const;
	};

	extern LODDetailScale* gLODDetailScale;

	class LODRenderBehaviour : public engine::Behaviour
	{
	public:
		// 0x102DA3A0: hands the drawables of the level range over to the game object and queues the transform
		void ChangeDrawableLevels(unsigned int previous, const unsigned char* first, const unsigned char* last);
		// 0x102DA700: picks the level the fade position asks for and tells the drawables when it changes
		void UpdateLevel();
		// 0x102DA540: the fade of the level drawn, from the distance to the camera and the level's range
		void UpdateFade();

		// +0x0C: the source of the pose handed to the drawables (its +4 is a pure3d::Pose)
		void* unknown0C;
		// +0x10: the scale the drawables are given (a math::Vector sits at its +4)
		void* unknown10;
		unsigned char unknown14[0x1C - 0x14];
		// +0x1C / +0x24: the level records of the drawables shown now (name guess)
		const unsigned char* shownFirst;
		// +0x20 / +0x28: the ones shown before the level was forced (name guess)
		const unsigned char* forcedFirst;
		const unsigned char* shownLast;
		const unsigned char* forcedLast;
		// +0x2C: the drawable the animation plays on (name guess)
		const unsigned char* animated;
		// +0x30: the object the levels come from, +0x34 the level's index in it (-1: none)
		const void* available;
		int availableIndex;
		// +0x38: which of the three distance ranges (the table at 0x11075114) the object is in
		// +0x38: which of the three distance ranges (gLODDistances) the object is in
		unsigned int distanceLevel;
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
		unsigned char unknown68[0x78 - 0x68];
		// +0x78: a multiplier on this behaviour's fade distance
		float fadeScale;
		unsigned char unknown7C[0x9C - 0x7C];
		// +0x9C: bit 0 the drawables are bound, bit 2 the level was forced
		unsigned char flags;
	};
}

#endif
