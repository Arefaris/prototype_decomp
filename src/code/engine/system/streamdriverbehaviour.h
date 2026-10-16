// engine::StreamDriverBehaviour (a name guess from the unit around 0x10899770; the RTTI name is not known to the
// repository): the behaviour that follows its game object through the stream triggers and asks the stream manager
// for the packages of the trigger the object stands in. Only its update is reconstructed; the layout follows it, the
// names are guesses.
#ifndef ENGINE_SYSTEM_STREAMDRIVERBEHAVIOUR_H
#define ENGINE_SYSTEM_STREAMDRIVERBEHAVIOUR_H

#include "code/engine/gameobject/behaviour.h"
#include "code/engine/system/streammanager.h"
#include "code/engine/system/tagset.h"
#include "code/math/vector.h"

namespace engine
{
	class StreamPackage;
	class StreamTrigger;

	class StreamDriverBehaviour : public Behaviour
	{
	public:
		// 0x10899830: finds the trigger the owner stands in (the last one, one of its neighbours, any), asks for its
		// packages and for the ones around it, and brings the loaded ones into line
		virtual void Update(float dt, unsigned short mask);

		// 0x1082BF40, 0x10899770, 0x104B1860: steps of the update (names unknown)
		static void Unknown10899770(StreamPackageArray* packages, const math::Vector* position, StreamPackage* package);

		// +0x0C: the tags the packages must match
		TagSet tags;
		unsigned char unknown20[0x34 - 0x20];
		// +0x34: the packages asked for now; +0x38: the ones the trigger wants
		StreamPackageArray* current;
		StreamPackageArray* wanted;
		// +0x3C: every trigger there is; +0x40: the one the owner stood in last
		StreamTriggerArray* triggers;
		StreamTrigger* last;
		unsigned char unknown44[0x4C - 0x44];
		bool unknown4C;
		bool unknown4D;
		bool restricted;
		bool transitioning;
		bool unknown50;
		bool unknown51;
	};

	// 0x1082BF40
	void Unknown1082BF40();
	// 0x104B1860
	void Unknown104B1860(bool value);
}

#endif
