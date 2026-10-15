// choreo::Puppet (the animation state of a character: the drivers that play clips and move the root, layered by
// priority and fade, and the pose they are mixed into) and choreo::Driver (RTTI name; the drivers of the engine
// derive from it: AnimationDriver, LocomotionDriver, RootDriver, ...). Only what the puppet update reads; layouts are
// partial and names are guesses.
#ifndef CHOREO_PUPPET_H
#define CHOREO_PUPPET_H

#include "code/core/name.h"
#include "code/math/matrix.h"
#include "code/pure3d/posedata.h"

namespace choreo
{
	struct PuppetCounts;
	struct PoseBlendCursors;

	// What a driver is told about what it drives (the pose its channels belong to)
	struct DriverInfo
	{
		unsigned char unknown0[0xC];
		void* mPose;                 // 0x0C
	};

	// The drivers are not updated through their vftable but through a table indexed by the driver's type.
	// The virtuals are in the order of the engine's vftables: the binding of slot 0, the release of slot 1, the two
	// ranges of the pose a driver partitions (slots 2 and 3, which every driver class overrides) and the destructor.
	class Driver
	{
	public:
		// 0x1094A4E0: a driver of the given type, not yet taking part in the blend
		Driver(int type);
		// slot 0: binds the driver to the pose it drives (nothing in the base, 0x109496E0)
		virtual void Bind(const DriverInfo& info);
		// slot 1: releases what the driver was bound to (nothing in the base, 0x109496F0)
		virtual void Unbind();
		// The first and the last joint of the pose the driver drives
		virtual unsigned int GetFirstJoint() const = 0;
		virtual unsigned int GetLastJoint() const = 0;
		// 0x1094A5B0
		virtual ~Driver();

		// 0x1094A440 / 0x1094A4A0: whether the driver takes part in the blend / moves the root (names guessed)
		void Unknown1094A440(bool enabled);
		void Unknown1094A4A0(bool enabled);

		core::Name<core::CaseSensitiveKey> mName;  // 0x04
		unsigned char unknownC[4];                 // 0x0C
		int mUnknown10;                            // 0x10
		int mType;                                 // 0x14
		// Bit 1: the driver takes part in the blend, bit 4: it moves the root, bit 5: the owner stopped it
		unsigned char mFlags;                      // 0x18
		unsigned char unknown19[3];
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
