// engine::ExceptionManager (RTTI name): watches the conditions the game cannot go on through, which are a lost lobby,
// a lost peer, a pad that was pulled and the removal of the media, and puts the pop-up dialog of the condition in
// front of the game (ExceptionFEPopUpDialogState). It listens to the online services (an OLS callback), the input
// system (a keyboard and pad callback) and the console manager. The game states that want to hear about a condition
// register an IExceptionHandler. One instance lives in gExceptionManager. Unit 0x108826C0 - 0x10883550 (no assert
// path; the file name is a guess). Names other than the RTTI ones are guesses.
#ifndef ENGINE_SYSTEM_EXCEPTIONMANAGER_H
#define ENGINE_SYSTEM_EXCEPTIONMANAGER_H

#include "code/core/time.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/frontend/dialogstate.h"
#include "code/engine/online/consolemanagercallback.h"
#include "code/engine/online/ols.h"

namespace engine
{
	class ExceptionManager : public OLS::Callback, public controller::InputSystem::InputCallback,
		public ConsoleManager::Callback
	{
	public:
		// What the game states implement to hear about the conditions
		struct IExceptionHandler
		{
			// The condition came up / went away
			virtual void OnRaised(int condition) = 0;
			virtual void OnCleared(int condition) = 0;
		};

		// The pop-up dialog of one condition (RTTI name); it keeps which condition it shows
		class ExceptionFEPopUpDialogState : public FEPopUpDialogState
		{
		public:
			// 0x10882960
			ExceptionFEPopUpDialogState(const char* newTitle, const char* newMessage, const char** newButtons,
				int newButtonCount, int a, int b, const char* name, int newReason);
			// 0x10882DC0 is the deleting destructor, the body is the base's
			// vftable slot 1 (0x10882A00): the dialog went away
			virtual void Slot1();
			// vftable slot 6 (0x10882A20): waits for the condition to go away
			virtual void Slot6();

			int reason;  // +0x1C
		};

		// The set-up of the manager (0x60 bytes are allocated from the heap)
		struct Config
		{
			int heap;
			int unknown4;
			// The movie screen of each condition's dialog
			char screens[4][0x20];
		};

		// 0x10882E60
		explicit ExceptionManager(const Config& config);
		// 0x10882C20 (0x10882E40 is the deleting destructor; nothing calls it)
		~ExceptionManager();

		// vftable slot 0 of the OLS callback (0x10882CF0): the profile's sign-out or the loss of a peer
		virtual void OnMessage(OLSMessage* message);
		// vftable slot 0 of the input callback (0x10882850): keeps the pads that were pulled
		virtual void OnFlags(unsigned int id, int local, unsigned int flags, bool set);
		// vftable slot 3 of the console manager callback (0x108828D0): the peer is lost
		virtual void Slot3(int a, int b);

		// 0x10883040 (called every frame with the time of the frame)
		void Update(core::Time frameTime);

		// 0x108827B0 / 0x108827E0: the handlers to tell (at most four)
		static void AddHandler(IExceptionHandler* handler);
		static void RemoveHandler(IExceptionHandler* handler);
		// 0x10882810: tells them a condition came up (raised) or went away
		static void Notify(int condition, bool raised);

		int heap;  // +0x20
		ExceptionFEPopUpDialogState* dialogs[4];  // +0x24: lobby, peer, controller, media
		bool lobbyLost;  // +0x34
		bool peerLost;  // +0x35
		bool controllerLost;  // +0x36
		bool unknown37;
		bool mediaRemoved;  // +0x38
		int pulledControllers[8];  // +0x3C
		int pulledController;  // +0x5C

		// 0x11316D6C
		static IExceptionHandler* handlers[4];
	};

	// 0x11316D7C
	extern ExceptionManager* gExceptionManager;

	// 0x108832D0 / 0x10883310 / 0x10883340: makes, destroys and updates the instance
	void CreateExceptionManager(const ExceptionManager::Config* config);
	void DestroyExceptionManager();
	void UpdateExceptionManager(core::Time frameTime);
	// 0x10882770
	ExceptionManager* GetExceptionManager();
	// 0x10882950: whether the media were removed
	bool IsMediaRemoved();

	// 0x10882900 / 0x10882910 / 0x10882920: the profile watch and the controller watch, and the function that tells
	// whether the controller watch has anything to wait for
	void SetPauseFlagA(bool value);
	void SetPauseFlagB(bool value);
	void SetControllerWatchCallback(bool (*callback)());
	// 0x10882930
	bool IsControllerWatchActive();

	// The thread that watches the default drive for faults and tells the game which of them it has to show: 0x10883370
	// starts it, 0x10882DE0 stops it; 0x10882E20 sets the flag it keeps, 0x108831C0 reads it
	void StartDriveErrorThread();
	void StopDriveErrorThread();
	long SetDriveFault(int fault);
	bool HasDriveFault();
}

#endif
