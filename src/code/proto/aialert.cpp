#include "code/proto/aialert.h"

namespace content
{
	// The values of proto::AiAlert
	static const EnumValue sAiAlertValues[] =
	{
		{ "proto::AiAlert_None", 0 },
		{ "proto::AiAlert_Explosion", 1 },
		{ "proto::AiAlert_Throw", 2 },
		{ "proto::AiAlert_Shapeshift", 3 },
		{ "proto::AiAlert_Gunfire", 4 },
		{ "proto::AiAlert_Grab", 5 },
		{ "proto::AiAlert_Hit", 6 },
		{ "proto::AiAlert_Shove", 7 },
		{ "proto::AiAlert_ExtremeLocomotion", 8 },
		{ "proto::AiAlert_Landing", 9 },
		{ "proto::AiAlert_Consume", 10 },
		{ "proto::AiAlert_Death", 11 },
		{ "proto::AiAlert_BulletHit", 12 },
		{ "proto::AiAlert_ScatterPeds", 13 },
		{ "proto::AiAlert_MissileFire", 14 },
		{ "proto::AiAlert_PanicingPedestrian", 15 },
		{ "proto::AiAlert_DeadBody", 16 },
		{ "proto::AiAlert_GrabScream", 17 },
		{ "proto::AiAlert_FlyingObject", 18 },
		{ "proto::AiAlert_ThrowLand", 19 },
		{ "proto::AiAlert_EnterVehicle", 20 },
		{ "proto::AiAlert_GenerateDiversion", 21 },
		{ "proto::AiAlert_BurningVehicle", 22 },
		{ "proto::AiAlert_CarAccident", 23 }
	};

	// FUNCTION: ENGINE 0x103608E0
	template<> void EnumInfo<proto::AiAlert>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::AiAlert";
		*code = "p";
		*values = sAiAlertValues;
		*count = proto::AIALERT_COUNT;
	}
}
