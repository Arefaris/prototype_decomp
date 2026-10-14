// choreo::Puppet (the animation state of a character: the drivers that play clips and move the root, layered by
// priority and fade, and the pose they are mixed into) and choreo::Driver (RTTI name; the drivers of the engine
// derive from it: AnimationDriver, LocomotionDriver, RootDriver, ...). Only what the puppet update reads; layouts are
// partial and names are guesses.
#ifndef CHOREO_PUPPET_H
#define CHOREO_PUPPET_H

#include "code/math/matrix.h"
#include "code/pure3d/posedata.h"

namespace choreo
{
	struct PuppetCounts;
	struct PoseBlendCursors;

	// The drivers are not updated through their vftable but through a table indexed by the driver's type
	class Driver
	{
	public:
		virtual void Unknown0();

		unsigned char unknown4[0x10];
		int mType;
		// Bit 5: the owner stopped the driver
		unsigned int mFlags;
	};

	// The update function of each driver type
	typedef void (*DriverUpdateFunction)(Driver* driver, float dt);
	// 0x111EC7C8
	extern DriverUpdateFunction gDriverUpdate[];
	// 0x109560C0: the update function of the driver's type
	void UpdateDriver(Driver* driver, float dt);

	// One driver of a puppet with its lifetime and fade (0x2C bytes)
	struct DriverEntry
	{
		Driver* mDriver;
		unsigned char unknown4[4];
		// Seconds left (counted down while the driver is not endless)
		float mLifetime;
		bool mEndless;
		unsigned char unknownD[0x13];
		float mBlendIn;
		float mBlendOut;
		// 0 to 1: how far the driver is blended in
		float mFade;
	};

	class Puppet
	{
	public:
		static const unsigned int MAX_DRIVERS = 16;

		// 0x10949080: resets the root, fades the drivers in and out (dropping the finished ones) and lets each of
		// them step
		void Update(float dt);
		// 0x10949040: puts the drivers in priority order when they changed
		void SortDrivers();
		// 0x10948770: writes the pose blend nodes of the puppet where the cursors stand
		void BuildNodes(PuppetCounts* counts, PoseBlendCursors* cursors);
		// 0x10946D00: turns the root translation and rotation of the update into the root delta matrix
		void BuildRootDelta();
		// 0x10947910: updates the pose's matrices
		void UpdatePose();
		// 0x10947920
		void Unknown10947920();

		// The root motion of this update as a matrix
		math::Matrix mRootDelta;
		unsigned char unknown40[0x148];
		pure3d::PoseData* mPose;
		float mTimeScale;
		unsigned int mDriverCount;
		DriverEntry mEntries[MAX_DRIVERS];
		bool mSortNeeded;
		unsigned char unknown455[3];
		// Counts the drivers that were dropped
		unsigned int mRemovedCount;
	};
}

#endif
