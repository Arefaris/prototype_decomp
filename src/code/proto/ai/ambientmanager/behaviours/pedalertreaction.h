// proto::PedAlertReaction and proto::PedAlertReactionTable (RTTI and reflection names; plain classes): how a
// pedestrian reacts to one kind of alert (an explosion, gunfire, a grab, ...) and the table of those reactions, one
// per kind (24, in the order of the "alertType_" names). Unit 0x10432F90 - 0x10433280 and 0x10438290 - 0x10438590,
// 0x1043B1F0, 0x1043EC40 (scattered; no assert path, the file name is a guess). The reflected names are original,
// the rest is guessed.
#ifndef PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_PEDALERTREACTION_H
#define PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_PEDALERTREACTION_H

#include "code/content/metatype.h"
#include "code/proto/ai/ambientmanager/ambientenums.h"

namespace proto
{
	// 0x30 bytes
	class PedAlertReaction
	{
	public:
		// 0x10433180
		PedAlertReaction();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10433220 / 0x10433200: the reflected angle in degrees (the reaction keeps its cosine)
		float GetMaxAngleForReaction() const;
		void SetMaxAngleForReaction(float degrees);
		// 0x10433240
		float GetMaxAngleCosine() const;

		bool createPedestrianAlert;  // +0
		float alertLength;  // +4
		float alertRadius;  // +8
		float chanceToIgnore;  // +0xC
		float maxAngleCosine;  // +0x10
		bool panic;  // +0x14
		bool target;  // +0x15
		AlertTargetChoice targetChoice;  // +0x18
		int priority;  // +0x1C
		bool overridesEqualPriority;  // +0x20
		float rubberneckDistance;  // +0x24
		float rubberneckTime;  // +0x28
		float rubberneckPanicChance;  // +0x2C
	};

	// 0x480 bytes
	class PedAlertReactionTable
	{
	public:
		// 0x10433250
		PedAlertReactionTable();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		PedAlertReaction reactions[24];
	};
}

#endif
