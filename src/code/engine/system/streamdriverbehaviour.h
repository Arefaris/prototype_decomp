// engine::StreamDriverBehaviour (a name guess from the unit around 0x10899770; the RTTI name is not known to the
// repository): the behaviour that follows its game object through the stream triggers and asks the stream manager
// for the packages of the trigger the object stands in. Only its update is reconstructed; the layout follows it, the
// names are guesses.
#ifndef ENGINE_SYSTEM_STREAMDRIVERBEHAVIOUR_H
#define ENGINE_SYSTEM_STREAMDRIVERBEHAVIOUR_H

#include "code/content/metatype.h"
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
		// 0x108991C0
		explicit StreamDriverBehaviour(GameObject* newOwner);
		// 0x10899560 (deleting destructor 0x10899710)
		virtual ~StreamDriverBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x108992B0): makes the package and trigger lists and takes the triggers that match the tags
		virtual void Slot1();
		// vftable slot 3 (0x10898FB0): lets the lists go when the behaviour is switched off
		virtual void OnActiveChanged(bool active);
		// 0x10899830: finds the trigger the owner stands in (the last one, one of its neighbours, any), asks for its
		// packages and for the ones around it, and brings the loaded ones into line
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10899370): the stream messages of the world (type 0x18)
		virtual void OnMessage(Message* message);

		// 0x10898490 / 0x10898480: the trigger tags as the reflection reads and writes them
		const char* GetTriggerTags();
		void SetTriggerTags(const char* text);
		// 0x108984A0 (lockWhenStreaming)
		void SetRestricted(bool value);
		// 0x10899030: collects the triggers again and finds the one the owner stands in
		void RefreshTriggers();
		// 0x10899110: asks for the packages as they are given
		void SetWantedPackages(StreamPackage** packages, int count);

		// 0x1082BF40, 0x10899770, 0x104B1860: steps of the update (names unknown)
		static void Unknown10899770(StreamPackageArray* packages, const math::Vector* position, StreamPackage* package);

		// +0x0C: the tags the packages must match
		TagSet tags;
		// +0x20: the tags as they were when the lists were made
		TagSet tagsCopy;
		// +0x34: the packages asked for now; +0x38: the ones the trigger wants
		StreamPackageArray* current;
		StreamPackageArray* wanted;
		// +0x3C: every trigger there is; +0x40: the one the owner stood in last
		StreamTriggerArray* triggers;
		StreamTrigger* last;
		unsigned int maxPackagesPerTransition;  // +0x44
		unsigned int maxFilteredTriggers;  // +0x48
		bool unknown4C;
		bool unknown4D;
		bool restricted;  // +0x4E, reflected as lockWhenStreaming
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
