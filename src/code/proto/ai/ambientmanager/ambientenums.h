// The enumerations of the ambient population's reflected classes (RTTI and reflection names): which kinds of
// ambient objects an exclusion volume keeps out, the states of a traffic light and how an alert chooses the
// object it reacts to. The names
// of the values are the reflected ones.
#ifndef PROTO_AI_AMBIENTMANAGER_AMBIENTENUMS_H
#define PROTO_AI_AMBIENTMANAGER_AMBIENTENUMS_H

#include "code/content/metatype.h"

namespace proto
{
	enum AmbientExcludeType
	{
		AMBIENT_EXCLUDE_PEDESTRIANS = 0,
		AMBIENT_EXCLUDE_TRAFFIC_VEHICLES = 1
	};

	// RTTI proto::IntersectionData::State: the state of one traffic light
	enum IntersectionState
	{
		INTERSECTION_STATE_NONE = 0,
		INTERSECTION_STATE_GREEN = 1,
		INTERSECTION_STATE_YELLOW = 2,
		INTERSECTION_STATE_RED = 3
	};

	enum AlertTargetChoice
	{
		ALERT_TARGET_CHOICE_CLOSEST = 0,
		ALERT_TARGET_CHOICE_GIVER = 1,
		ALERT_TARGET_CHOICE_TAKER = 2,
		ALERT_TARGET_CHOICE_CLOSEST_WEIGHTED_GIVER = 3,
		ALERT_TARGET_CHOICE_CLOSEST_WEIGHTED_TAKER = 4
	};
}

#endif
