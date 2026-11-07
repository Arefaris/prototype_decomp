// The front end's resource packages (frontendpackages.cpp).
#ifndef PROTO_ARCHITECTURE_FRONTENDPACKAGES_H
#define PROTO_ARCHITECTURE_FRONTENDPACKAGES_H

namespace proto
{
	// 0x104E2BC0: loads the packages of a front end group and waits for them
	void LoadFrontEndPackages(const char* files, const char* group);
	// 0x104E1A40: lets go of the packages of a group (FETransient, FEPermanent or FETextBible)
	void UnloadFrontEndPackages(const char* group);
	// 0x104E1C50 / 0x104E1C80 / 0x104E1CD0: the transient package's unload (begin, finished) and whether it is loaded
	void BeginFrontEndTransientUnload();
	bool FinishFrontEndTransientUnload();
	bool IsFrontEndTransientLoaded();
	// 0x104E2860: starts loading the transient package
	void StartFrontEndTransientLoad(const char* files, const char* group);
}

#endif
