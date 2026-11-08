#include "code/proto/reflectedstubs.h"

// The ClassInfo of the flying, formation, helicopter movement and disguise behaviours, which are declared in
// proto/reflectedstubs.h until their layouts are recovered. Units 0x103CA070, 0x103D7880, 0x103DA2E0 and 0x103DD860 (no
// assert path; the file name is a guess).
namespace proto
{
	// FUNCTION: ENGINE 0x103CA070
	content::ClassInfo* DisguiseBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DisguiseBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103D7880
	content::ClassInfo* FlyingBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "FlyingBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103DA2E0
	content::ClassInfo* FormationBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FormationBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103DD860
	content::ClassInfo* HelicopterMovementBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterMovementBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}
}
