#include "code/core/language.h"

namespace core
{
	// GLOBAL: ENGINE 0x110BD254
	int gLanguage = '?';
	// GLOBAL: ENGINE 0x1127CA1C
	static ILanguageListener* sLanguageListeners[8];
	// GLOBAL: ENGINE 0x1127CA3C
	static bool sLanguageReady;
	// GLOBAL: ENGINE 0x1127CA40
	static int sLanguageListenerCount;

	// FUNCTION: ENGINE 0x1064ACF0
	void InitLanguage()
	{
		gLanguage = 'E';
		for (int i = 0; i < 8; i++)
		{
			sLanguageListeners[i] = 0;
		}
		sLanguageReady = true;
	}

	// FUNCTION: ENGINE 0x1064AD30
	void ShutdownLanguage()
	{
		gLanguage = '?';
		sLanguageReady = false;
	}

	// FUNCTION: ENGINE 0x1064AD50
	void SetLanguage(int language)
	{
		gLanguage = language;
		for (int priority = 0; priority < 3; priority++)
		{
			for (int i = 0; i < sLanguageListenerCount; i++)
			{
				if (sLanguageListeners[i]->GetPriority() == priority)
				{
					sLanguageListeners[i]->OnLanguageChanged(gLanguage);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1064ADB0
	void AddLanguageListener(ILanguageListener* listener)
	{
		sLanguageListeners[sLanguageListenerCount] = listener;
		sLanguageListenerCount++;
	}

	// FUNCTION: ENGINE 0x1064ADD0
	// The last listener takes the place of the removed one
	void RemoveLanguageListener(ILanguageListener* listener)
	{
		for (int i = 0; i < sLanguageListenerCount; i++)
		{
			if (sLanguageListeners[i] == listener)
			{
				sLanguageListeners[i] = 0;
				sLanguageListenerCount--;
				if (i != sLanguageListenerCount)
				{
					sLanguageListeners[i] = sLanguageListeners[sLanguageListenerCount];
					sLanguageListeners[sLanguageListenerCount] = 0;
				}
				return;
			}
		}
	}
}
