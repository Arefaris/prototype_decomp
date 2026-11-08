// The scenario's tutorial flag (0x1130D43C): the tutorial scripts set it, the playback actions test it. The file name
// is a guess; the unit's two functions lie at 0x1082FDC0 and 0x1082FDD0.
namespace engine
{
	// GLOBAL: ENGINE 0x1130D43C
	bool gTutorialMode;

	// FUNCTION: ENGINE 0x1082FDC0
	void scenario_SetTutorialMode(bool on)
	{
		gTutorialMode = on;
	}

	// FUNCTION: ENGINE 0x1082FDD0
	bool IsTutorialActive()
	{
		return gTutorialMode;
	}
}
