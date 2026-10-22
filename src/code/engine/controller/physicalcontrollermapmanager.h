// engine::controller::PhysicalControllerMapManager (RTTI name): listens to the controller system for controllers that
// are connected or disconnected and gives each connected one the button and axis map of its kind (one map per entry
// of a table of eleven: keyboard, mouse, the gamepads the engine knows by name, a default). The controller objects it
// keeps (one per player slot) take the map. ControllerMap is the pair of arrays a map consists of (no RTTI: the class
// has no virtual function). Unit 0x10880AA0 - 0x108810F0 and 0x10882140 - 0x108822C0 (no assert path; the file name is
// a guess). Names other than the RTTI ones are guesses.
#ifndef ENGINE_CONTROLLER_PHYSICALCONTROLLERMAPMANAGER_H
#define ENGINE_CONTROLLER_PHYSICALCONTROLLERMAPMANAGER_H

#include "code/engine/controller/physicalcontroller.h"
#include "code/core/controller.h"

namespace engine
{
	namespace controller
	{
		class PhysicalControllerManager;

		// One button of a controller (0x14 bytes)
		struct ButtonMapping
		{
			int unknown0;
			int unknown4;
			int unknown8;
			int unknownC;
			int unknown10;
		};

		// One axis of a controller (0x18 bytes); the first word is zero while the axis is unused
		struct AxisMapping
		{
			int unknown0;
			int unknown4;
			int unknown8;
			int unknownC;
			int unknown10;
			int unknown14;
		};

		// The buttons and axes a kind of controller has, as arrays in the heap
		class ControllerMap
		{
		public:
			// 0x10882140: clears the first word of every entry
			ControllerMap(unsigned int newButtonCount, unsigned int newAxisCount);
			// 0x108821D0
			~ControllerMap();
			// 0x108821F0 / 0x10882240 / 0x10882280
			void SetButton(int index, const ButtonMapping* button);
			void SetAxis(int index, const AxisMapping* axis);
			void ClearAxis(int index);
			// The map as the physical controller binds it (PhysicalController::Mapping has this layout)
			const PhysicalController::Mapping* AsMapping() const
			{
				return reinterpret_cast<const PhysicalController::Mapping*>(this);
			}

			unsigned int buttonCount;
			ButtonMapping* buttons;
			unsigned int axisCount;
			AxisMapping* axes;
		};

		// One row of the table of the controller kinds at 0x111D17B0: the name the kind goes by (the start of a
		// controller's name), the entries of its map
		struct ControllerKind
		{
			const char* name;
			const ButtonMapping* buttons;
			int buttonCount;
			const AxisMapping* axes;
			int axisCount;
			int unknown14;
			int unknown18;
		};

		class PhysicalControllerMapManager : public core::IControllerConnectionChangeCallback
		{
		public:
			// 0x10880C80
			PhysicalControllerMapManager(int newControllerCount, int a, int b, int newOptions, int newHeap, int c);
			// 0x108810D0 (the deleting destructor), 0x10880D60
			virtual ~PhysicalControllerMapManager();

			// vftable slot 0 (0x10880AD0): the controller system tells a controller was connected or disconnected
			virtual void OnControllerChanged(core::IController* changed);
			// vftable slot 2 (0x10880DE0): finds the kind of the controller and gives it its map
			virtual void OnConnected(core::IController* changed);
			// vftable slot 3 (0x10880F50): lets go of the controller; keeps the default setting when a gamepad is left
			virtual void OnDisconnected(core::IController* changed);
			// vftable slot 4 (0x10880B70): the index of the player slot the controller belongs to (its location tells
			// which: Keyboard0, Mouse0, JoystickN, PortN), -1 for none
			virtual int GetSlot(core::IController* changed);

			// 0x10880AB0: remembers the manager and starts the controller system
			void Start(PhysicalControllerManager* newManager);
			// 0x10880B00: builds the map of a kind
			ControllerMap* CreateMap(const ButtonMapping* buttons, int buttonCount, const AxisMapping* axes, int axisCount);
			// 0x10880C10: gives the controller in the slot the map
			void SetMap(unsigned char slot, ControllerMap* map);
			// 0x10880C30: the controller of the slot, 0 while it has no controller attached
			PhysicalController* GetConnected(unsigned char slot);
			// 0x10880C50: calls slot 2 of the controller of the slot
			void CallController(unsigned char slot, int value);

			PhysicalControllerManager* manager;  // +4
			int controllerCount;  // +8
			unsigned int options;  // +0xC
			int heap;  // +0x10
			PhysicalController** controllers;  // +0x14
			ControllerMap* maps[11];  // +0x18, one per row of the table
		};

		// 0x111D17B0 (eleven rows)
		extern ControllerKind gControllerKinds[11];
	}
}

#endif
