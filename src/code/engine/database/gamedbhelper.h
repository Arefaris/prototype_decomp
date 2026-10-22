// engine::GameDBHelper (RTTI name): the platform side of the game database. It is told about the online services' events
// (as an OLS callback), makes the database's subjects for the settings and the account when the database starts and
// lets them go when it stops. The window of one instance is kept in a global. Unit 0x10894450 - 0x10894830 (no assert
// path; the file name is a guess). Names other than the RTTI ones are guesses.
#ifndef ENGINE_DATABASE_GAMEDBHELPER_H
#define ENGINE_DATABASE_GAMEDBHELPER_H

#include "code/engine/online/ols.h"

namespace engine
{
	class GameDBHelper : public OLS::Callback
	{
	public:
		struct Config
		{
			// 0x10894450
			Config();

			int unknown0;
		};

		// 0x108944D0: becomes the current helper
		explicit GameDBHelper(const Config& config);
		// 0x10894460
		static GameDBHelper* Get();

		// vftable slot 0 (0x108944A0): an event of the online services
		virtual void OnMessage(OLSMessage* message);
		// slot 1 (0x108944F0 is the deleting destructor; 0x10894470 the body)
		virtual ~GameDBHelper();
		// slot 2 (0x10894490)
		virtual bool Slot2();
		// slot 3 (0x10894510): makes the subjects of the account and the settings
		virtual void Start();
		// slot 4 (0x108946A0): lets them go
		virtual void Stop();
		// slot 5 (0x108947D0): listens to the online services
		virtual bool Enable();
		// slot 6 (0x10894800): stops listening
		virtual void Disable();

		int unknown8;

		// 0x113177E0
		static GameDBHelper* current;
	};
}

#endif
