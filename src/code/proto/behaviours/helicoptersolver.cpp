#include "code/proto/reflectedstubs.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10312760
	content::ClassInfo* HelicopterSolverBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031DFE0
	content::ClassInfo* HelicopterSolverGenericProperties::CameraParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverGenericProperties::CameraParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E020
	content::ClassInfo* HelicopterSolverGenericProperties::EffectsParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverGenericProperties::EffectsParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E060
	content::ClassInfo* HelicopterSolverGenericProperties::HealthParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverGenericProperties::HealthParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E0A0
	content::ClassInfo* HelicopterSolverGenericProperties::PowerParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverGenericProperties::PowerParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E0E0
	content::ClassInfo* HelicopterSolverGenericProperties::RotorParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverGenericProperties::RotorParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E120
	content::ClassInfo* HelicopterSolverGenericProperties::SoundParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverGenericProperties::SoundParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E160
	content::ClassInfo* HelicopterSolverProperties::AIParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverProperties::AIParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E1A0
	content::ClassInfo* HelicopterSolverProperties::HoverParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverProperties::HoverParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E1E0
	content::ClassInfo* HelicopterSolverProperties::LateralAxisLinearParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverProperties::LateralAxisLinearParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E220
	content::ClassInfo* HelicopterSolverProperties::LateralAxisAngularParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverProperties::LateralAxisAngularParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E260
	content::ClassInfo* HelicopterSolverProperties::LongitudinalAxisLinearParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverProperties::LongitudinalAxisLinearParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E2A0
	content::ClassInfo* HelicopterSolverProperties::LongitudinalAxisAngularParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverProperties::LongitudinalAxisAngularParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E2E0
	content::ClassInfo* HelicopterSolverProperties::VerticalAxisParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverProperties::VerticalAxisParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E320
	content::ClassInfo* HelicopterSolverProperties::YawAxisParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverProperties::YawAxisParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E360
	content::ClassInfo* HelicopterSolverGenericProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverGenericProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1031E3A0
	content::ClassInfo* HelicopterSolverProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterSolverProperties";
		sInfo.code = "p";
		return &sInfo;
	}
}

// The engine's copy of the reflection's caster of the behaviour
template class content::BaseClassCasterImpl<engine::Behaviour, proto::HelicopterSolverBehaviour>;
// FUNCTION: ENGINE 0x10313740
