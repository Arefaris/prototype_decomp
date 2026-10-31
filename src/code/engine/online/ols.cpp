// engine::OLS (RTTI name; the online services singleton, 0x1130E738; unit 0x108441E0 - 0x10844C40, no assert path, the
// file name is a guess). Of the unit only the singleton's getter is reconstructed.
#include "code/engine/online/ols.h"

namespace engine
{
	// The singleton (created by the engine's start-up)
	extern OLS* gOLS;

	// FUNCTION: ENGINE 0x108441E0
	OLS* OLS::Get()
	{
		return gOLS;
	}
}
