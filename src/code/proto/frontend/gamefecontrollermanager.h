// proto::GameFEControllerManager (RTTI; bases engine::IRealTimeTask at 0 and engine::DBObserver at 4): the front end's
// controller remapping. While a remap is in progress it polls the connected controllers every frame; it publishes the
// state in the game database subject "RemapStatus" and follows the setting "SettingsMouseSensitivity". The member names
// are guesses. Unit 0x104AD5F0 - 0x104AF380 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_GAMEFECONTROLLERMANAGER_H
#define PROTO_FRONTEND_GAMEFECONTROLLERMANAGER_H

#include "code/engine/dbobserver.h"
#include "code/engine/gamestate.h"

namespace proto
{
	class GameFEControllerManager : public engine::IRealTimeTask, public engine::DBObserver
	{
	public:
		// 0x104AD5F0
		GameFEControllerManager();
		// 0x104AD6D0
		~GameFEControllerManager();
		// IRealTimeTask slot 0 (0x104AF370): polls the controllers while a remap is in progress
		virtual void Update(engine::UpdateContext context);
		// DBObserver slot 0 (0x104AECA0): the mouse sensitivity setting changed
		virtual void OnDBSlot0(int a, int b);
		// 0x104AD720 (name guess): one step of the remapping
		void Remap();

		bool remapping;  // +8
		bool unknown9;
		int unknownC;
		int unknown10;
		int unknown14;
	};
}

#endif
