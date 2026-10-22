// engine::controller::PhysicalController (RTTI: derives from PhysicalControllerInterface): binds the input points of
// the attached controllers (keyboard, mouse, joysticks) to the values of a player's state and drives the force
// feedback motors with a list of timed effects. All member and method names are guesses.
#ifndef ENGINE_CONTROLLER_PHYSICALCONTROLLER_H
#define ENGINE_CONTROLLER_PHYSICALCONTROLLER_H

#include "code/core/controller.h"

namespace engine
{
	namespace controller
	{
		class PlayerInfo;

		// One timed force feedback effect (20 bytes): it ramps up over the attack time, holds for the hold time and
		// ramps down over the release time
		struct RumbleEffect
		{
			// 0x10845BF0: the time left of the effect, 0 when it has ended
			float GetTimeLeft() const
			{
				float total = release + attack + hold;
				return total > elapsed ? total - elapsed : 0.0f;
			}
			// 0x10846150: the intensity at the elapsed time
			float GetIntensity() const;

			float hold;
			float attack;
			float release;
			float elapsed;
			float intensity;
		};

		// The effects running on one motor
		struct RumbleEffectList
		{
			// 0x10845CD0: starts an effect, replacing the one with the least time left when the list is full
			void Add(float hold, float intensity, float attack, float release, int capacity);
			// 0x10845D70: advances the effects and removes the ones that have ended
			void Update(float delta);
			// 0x10846000: the longest time left of all effects
			float GetTimeLeft() const;
			// 0x10846FC0: the strongest current intensity of all effects
			float GetIntensity() const;

			RumbleEffect* effects;
			int count;
		};

		// The interface the input system talks to (RTTI: PhysicalControllerInterface, all pure)
		class PhysicalControllerInterface
		{
		public:
			// 0x10845C70
			PhysicalControllerInterface()
			{
			}
			// Reads the bound input points into the player's state
			virtual void Read(PlayerInfo* player) = 0;
			// Starts a force feedback effect on a motor, or stops the motor's effects when the intensity is 0
			virtual void SetRumble(int motor, float hold, float intensity, float attack, float release) = 0;
			virtual void SetRumbleEnabled(bool enabled) = 0;
			// Advances the effects and drives the motors
			virtual void UpdateRumble(float delta) = 0;
			virtual int GetBoundCount() = 0;
			virtual void ResetRead() = 0;
		};

		class PhysicalController : public PhysicalControllerInterface
		{
		public:
			// A button bound to input points: kind 1 and 3 read the input point (and feed value), kind 2 feeds the
			// values value and value2 from point2 (16 bytes)
			struct ButtonBinding
			{
				int kind;
				int value;
				union
				{
					core::IControllerInputPoint* point;
					int value2;
				};
				core::IControllerInputPoint* point2;
			};

			// An axis bound to input points (28 bytes). Kinds 1 and 2 read one point, 3 reads two (positive and negative
			// direction), 4 and 5 the mouse, 6 a hat switch
			struct AxisBinding
			{
				int kind;
				int axis;
				union
				{
					core::IControllerInputPoint* point;
					int axis2;
				};
				union
				{
					core::IControllerInputPoint* point2;
					float unknownC;
				};
				float raw;
				float accumulated;
				int unknown18;
			};

			// The part of an axis binding after its kind that the mouse and hat readers take
			struct MouseView
			{
				int axis;
				core::IControllerInputPoint* point;
				float unknown8;
				float raw;
				float accumulated;
			};

			struct HatView
			{
				int xAxis;
				int yAxis;
				core::IControllerInputPoint* point;
			};

			// What a controller is bound to: the buttons (20 bytes each: the kind, the player value, the index of the
			// input point, for kind 2 the second value and the index of the second point) and the axes (24 bytes
			// each)
			struct ButtonSource
			{
				int kind;
				int value;
				int index;
				int index2;
				int unknown10;
			};

			struct AxisSource
			{
				int kind;
				int axis;
				int index;
				int index2;
				int index3;
				int unknown14;
			};

			struct Mapping
			{
				// 0x10845BB0 / 0x10845BD0
				ButtonSource* GetButton(int index);
				AxisSource* GetAxis(int index);

				int buttonCount;
				ButtonSource* buttons;
				int axisCount;
				AxisSource* axes;
			};

			// A motor of a controller (8 bytes)
			struct Motor
			{
				int index;
				core::IControllerOutputPoint* output;
			};

			// 0x10846E50
			PhysicalController(int buttonCapacity, int axisCapacity, int motorCount, int effectCapacity);
			virtual void Read(PlayerInfo* player);
			virtual void SetRumble(int motor, float hold, float intensity, float attack, float release);
			virtual void SetRumbleEnabled(bool enabled);
			virtual void UpdateRumble(float delta);
			virtual int GetBoundCount();
			virtual void ResetRead();
			virtual ~PhysicalController();

			// 0x10846490: lets go of the old bindings and binds the input points the mapping names
			void Bind(const Mapping* mapping);
			// 0x10847010: the controller whose input points are bound (reference counted)
			void SetController(core::IController* newController);
			// 0x10845C80: stops all motors
			void StopRumble();
			// 0x10846B00: reads the buttons into the player, 0x108472A0 the axes
			void UpdateButtons(PlayerInfo* player);
			void UpdateAxes(PlayerInfo* player);
			// 0x10847150: a mouse axis (the sensitivity setting scales it)
			void ReadMouse(MouseView* mouse, PlayerInfo* player);
			// 0x10846D40: a hat switch as two axes
			void ReadHat(HatView* hat, PlayerInfo* player);
			// 0x10846340 / 0x108463A0 / 0x10846430: the binding that feeds a player value / drives an axis (in one
			// direction)
			ButtonBinding* FindButton(int value);
			AxisBinding* FindAxis(int axis);
			AxisBinding* FindAxisDirection(int axis, bool positive);
			// 0x108461D0 / 0x108462F0: lets go of the bound input points and of the motors
			void ReleaseBindings();
			void ReleaseMotors();

			int buttonCapacity;
			int buttonCount;
			ButtonBinding* buttons;
			int axisCapacity;
			int axisCount;
			AxisBinding* axes;
			int motorCount;
			int motorsFound;
			Motor* motors;
			int effectCapacity;
			bool rumbleEnabled;
			float deadZone;
			float fullZone;
			core::IController* controller;
			int boundCount;
			bool read;
			// One list per motor (the manager makes its controllers with two motors: the object is 0x54 bytes)
			RumbleEffectList lists[2];
		};
	}
}

#endif
