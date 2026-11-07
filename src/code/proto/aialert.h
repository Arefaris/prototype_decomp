// proto::AiAlert (RTTI name and reflected enumeration): the kinds of event the ai characters notice and react to.
// Unit 0x103608E0 (no assert path; the file name is a guess).
#ifndef PROTO_AIALERT_H
#define PROTO_AIALERT_H

#include "code/content/metatype.h"

namespace proto
{
	enum AiAlert
	{
		AIALERT_NONE = 0,
		AIALERT_EXPLOSION = 1,
		AIALERT_THROW = 2,
		AIALERT_SHAPESHIFT = 3,
		AIALERT_GUNFIRE = 4,
		AIALERT_GRAB = 5,
		AIALERT_HIT = 6,
		AIALERT_SHOVE = 7,
		AIALERT_EXTREME_LOCOMOTION = 8,
		AIALERT_LANDING = 9,
		AIALERT_CONSUME = 10,
		AIALERT_DEATH = 11,
		AIALERT_BULLET_HIT = 12,
		AIALERT_SCATTER_PEDS = 13,
		AIALERT_MISSILE_FIRE = 14,
		AIALERT_PANICING_PEDESTRIAN = 15,
		AIALERT_DEAD_BODY = 16,
		AIALERT_GRAB_SCREAM = 17,
		AIALERT_FLYING_OBJECT = 18,
		AIALERT_THROW_LAND = 19,
		AIALERT_ENTER_VEHICLE = 20,
		AIALERT_GENERATE_DIVERSION = 21,
		AIALERT_BURNING_VEHICLE = 22,
		AIALERT_CAR_ACCIDENT = 23
	};

	enum
	{
		AIALERT_COUNT = 24
	};
}

#endif
