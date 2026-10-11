// The game language (all names guessed): a language code ('E' English, 'F' French, ... '?' none) and up to eight
// listeners told about a change in three rounds of priority. Unit 0x1064ACF0 - 0x1064AE22 (language.cpp, name
// guessed); the system's language and the code / name conversions are in the unit at 0x10643EF0.
#ifndef CORE_LANGUAGE_H
#define CORE_LANGUAGE_H

namespace core
{
	struct ILanguageListener
	{
		virtual void OnLanguageChanged(int language) = 0;
		// 0, 1 or 2: the round SetLanguage tells the listener in
		virtual int GetPriority() = 0;
	};

	// 0x110BD254: the current language code ('?' before InitLanguage)
	extern int gLanguage;

	void InitLanguage();
	void ShutdownLanguage();
	void SetLanguage(int language);
	void AddLanguageListener(ILanguageListener* listener);
	void RemoveLanguageListener(ILanguageListener* listener);
}

#endif
