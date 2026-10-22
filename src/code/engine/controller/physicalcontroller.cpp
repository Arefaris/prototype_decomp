#include "code/engine/controller/physicalcontroller.h"
#include "code/engine/camera/camera.h"
#include "code/engine/camera/cinematographer.h"
#include "code/engine/camera/director.h"
#include "code/engine/controller/inputsystem.h"
#include "code/core/strings.h"
#include "code/math/worldbounds.h"

namespace engine
{
	namespace controller
	{
		// FUNCTION: ENGINE 0x10845B50
		void PlayerInfo::SetAxisFloat(int axis, float value, int component)
		{
			((float*)analog)[axis * 2 + component] = value;
		}

		// FUNCTION: ENGINE 0x10845B70
		void PlayerInfo::SetViewMatrix(const math::Matrix& matrix)
		{
			viewMatrix = matrix;
		}

		// FUNCTION: ENGINE 0x10845B80
		void PlayerInfo::SetViewPosition(const math::Vector& position)
		{
			viewPosition[0] = position.x;
			viewPosition[1] = position.y;
			viewPosition[2] = position.z;
		}

		// FUNCTION: ENGINE 0x10845BB0
		PhysicalController::ButtonSource* PhysicalController::Mapping::GetButton(int index)
		{
			return &buttons[index];
		}

		// FUNCTION: ENGINE 0x10845BD0
		PhysicalController::AxisSource* PhysicalController::Mapping::GetAxis(int index)
		{
			return &axes[index];
		}

		// FUNCTION: ENGINE 0x10846150
		// EQUIVALENT: same operations in the same order; the engine keeps attack in the first and elapsed in the second stack slot, ours the other way round; 39.5 %
		float RumbleEffect::GetIntensity() const
		{
			float a = attack;
			float e = elapsed;
			if (e < a)
			{
				float r = e / a;
				return r * intensity;
			}
			float attackAndHold = hold + a;
			if (e < attackAndHold)
			{
				return intensity;
			}
			float total = release + attackAndHold;
			if (e < total)
			{
				return (total - e) / (total - attackAndHold) * intensity;
			}
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x10845CD0
		// EQUIVALENT: same operations; the engine keeps the count in esi and the index in edi, ours the other way round; 87.3 %
		void RumbleEffectList::Add(float hold, float intensity, float attack, float release, int capacity)
		{
			int index = count;
			if (index < capacity)
			{
				count = index + 1;
			}
			else
			{
				float weakest = effects[0].intensity;
				index = 0;
				for (int i = 1; i < count; i++)
				{
					if (effects[i].intensity < weakest)
					{
						index = i;
						weakest = effects[i].intensity;
					}
				}
			}
			effects[index].hold = hold;
			effects[index].intensity = intensity;
			effects[index].attack = attack;
			effects[index].release = release;
			effects[index].elapsed = 0.0f;
		}

		// FUNCTION: ENGINE 0x10845D70
		void RumbleEffectList::Update(float delta)
		{
			for (int i = count - 1; i >= 0; i--)
			{
				float advanced = delta;
				advanced += effects[i].elapsed;
				effects[i].elapsed = advanced;
				if (0.0f == effects[i].GetTimeLeft())
				{
					count--;
					effects[i] = effects[count];
				}
			}
		}

		// FUNCTION: ENGINE 0x10846000
		float RumbleEffectList::GetTimeLeft() const
		{
			float longest = 0.0f;
			for (int i = 0; i < count; i++)
			{
				float left = effects[i].GetTimeLeft();
				if (longest < left)
				{
					longest = left;
				}
			}
			return longest;
		}

		// FUNCTION: ENGINE 0x10846FC0
		float RumbleEffectList::GetIntensity() const
		{
			float strongest = 0.0f;
			for (int i = 0; i < count; i++)
			{
				float current = effects[i].GetIntensity();
				if (strongest < current)
				{
					strongest = current;
				}
			}
			return strongest;
		}

		// FUNCTION: ENGINE 0x10846E50
		PhysicalController::PhysicalController(int newButtonCapacity, int newAxisCapacity, int newMotorCount,
			int newEffectCapacity)
		{
			buttonCapacity = newButtonCapacity;
			buttonCount = 0;
			axisCapacity = newAxisCapacity;
			axisCount = 0;
			motorCount = newMotorCount;
			motorsFound = 0;
			effectCapacity = newEffectCapacity;
			rumbleEnabled = false;
			deadZone = 0.1f;
			fullZone = 1.0f;
			controller = 0;
			boundCount = 0;
			read = false;
			buttons = new ButtonBinding[buttonCapacity];
			axes = new AxisBinding[axisCapacity];
			motors = new Motor[motorCount];
			for (int i = 0; i < motorCount; i++)
			{
				lists[i].effects = new RumbleEffect[effectCapacity];
				lists[i].count = 0;
			}
		}

		// FUNCTION: ENGINE 0x10847060
		// FUNCTION: ENGINE 0x10847130
		PhysicalController::~PhysicalController()
		{
			SetController(0);
			for (int i = 0; i < motorCount; i++)
			{
				delete[] lists[i].effects;
			}
			delete[] buttons;
			delete[] axes;
			delete[] motors;
		}

		// FUNCTION: ENGINE 0x10847010
		void PhysicalController::SetController(core::IController* newController)
		{
			if (controller != newController)
			{
				if (controller != 0)
				{
					ReleaseBindings();
					ReleaseMotors();
					boundCount = 0;
					controller->Release();
				}
				controller = newController;
				if (newController != 0)
				{
					newController->AddRef();
				}
			}
		}

		// FUNCTION: ENGINE 0x10845C80
		void PhysicalController::StopRumble()
		{
			for (int i = 0; i < motorsFound; i++)
			{
				lists[i].count = 0;
				if (motors[i].output != 0)
				{
					motors[i].output->SetValue(0.0f);
				}
			}
		}

		// FUNCTION: ENGINE 0x108461D0
		void PhysicalController::ReleaseBindings()
		{
			for (int i = 0; i < buttonCount; i++)
			{
				switch (buttons[i].kind)
				{
				case 1:
				case 3:
					buttons[i].point->Release();
					buttons[i].point = 0;
					break;
				case 2:
					buttons[i].point2->Release();
					buttons[i].point2 = 0;
					break;
				}
			}
			buttonCount = 0;
			for (int i = 0; i < axisCount; i++)
			{
				switch (axes[i].kind)
				{
				case 3:
					if (axes[i].point != 0)
					{
						axes[i].point->Release();
						axes[i].point = 0;
					}
					if (axes[i].point2 != 0)
					{
						axes[i].point2->Release();
						axes[i].point2 = 0;
					}
					break;
				case 6:
					axes[i].point2->Release();
					axes[i].point2 = 0;
					break;
				case 1:
				case 2:
				case 4:
				case 5:
					axes[i].point->Release();
					axes[i].point = 0;
					break;
				}
			}
			axisCount = 0;
		}

		// FUNCTION: ENGINE 0x108462F0
		void PhysicalController::ReleaseMotors()
		{
			for (int i = 0; i < motorsFound; i++)
			{
				if (motors[i].output != 0)
				{
					motors[i].output->Release();
					motors[i].output = 0;
				}
			}
		}

		// FUNCTION: ENGINE 0x10846F70
		void PhysicalController::SetRumble(int motor, float hold, float intensity, float attack, float release)
		{
			RumbleEffectList& list = lists[motor];
			if (0.0f != intensity)
			{
				list.Add(hold, intensity, attack, release, effectCapacity);
			}
			else
			{
				list.count = 0;
			}
		}

		// FUNCTION: ENGINE 0x10846F60
		void PhysicalController::SetRumbleEnabled(bool enabled)
		{
			rumbleEnabled = enabled;
		}

		// FUNCTION: ENGINE 0x108470C0
		void PhysicalController::UpdateRumble(float delta)
		{
			for (int i = 0; i < motorsFound; i++)
			{
				lists[i].Update(delta);
				float level;
				if (rumbleEnabled && lists[i].count > 0)
				{
					level = lists[i].GetIntensity();
				}
				else
				{
					level = 0.0f;
				}
				if (motors[i].output != 0)
				{
					motors[i].output->SetValue(level);
				}
			}
		}

		// FUNCTION: ENGINE 0x10846330
		int PhysicalController::GetBoundCount()
		{
			return boundCount;
		}

		// FUNCTION: ENGINE 0x10846F50
		void PhysicalController::ResetRead()
		{
			read = false;
		}
		// FUNCTION: ENGINE 0x10846B00
		// EQUIVALENT: the engine compares the held button as 0 < value (comiss 0, value; jb), ours as value > 0 (comiss value, 0; ja) in the two-point case; 99.3 %
		void PhysicalController::UpdateButtons(PlayerInfo* player)
		{
			for (int i = 0; i < 42; i++)
			{
				player->buttonValues[i] = 0.0f;
			}
			for (int i = 0; i < buttonCount; i++)
			{
				int index;
				float raw;
				switch (buttons[i].kind)
				{
				case 1:
				case 3:
					index = buttons[i].value;
					if (player->context != 0 && player->buttonValues[index] > 0.0f)
					{
						continue;
					}
					{
						float minimum = 0.0f;
						float maximum = 0.0f;
						buttons[i].point->GetRange(&minimum, &maximum);
						if (buttons[i].kind == 3)
						{
							buttons[i].point->SetRange(-1.0f, 1.0f);
						}
						else
						{
							buttons[i].point->SetRange(0.0f, 1.0f);
						}
						raw = buttons[i].point->Read(0);
						buttons[i].point->SetRange(minimum, maximum);
					}
					break;
				case 2:
				{
					float minimum = 0.0f;
					float maximum = 0.0f;
					buttons[i].point2->GetRange(&minimum, &maximum);
					buttons[i].point2->SetRange(-1.0f, 1.0f);
					raw = buttons[i].point2->Read(0);
					buttons[i].point2->SetRange(minimum, maximum);
					if (raw > 0.0f)
					{
						index = buttons[i].value;
						if (player->context != 0 && 0.0f < player->buttonValues[index])
						{
							continue;
						}
					}
					else if (raw < 0.0f)
					{
						index = buttons[i].value2;
						raw = math::WORLD_MIN - raw;
						if (player->context != 0 && 0.0f < player->buttonValues[index])
						{
							continue;
						}
					}
					else
					{
						continue;
					}
					break;
				}
				default:
					continue;
				}
				float scaled;
				if (raw < deadZone)
				{
					scaled = 0.0f;
				}
				else if (raw > fullZone)
				{
					scaled = 1.0f;
				}
				else
				{
					scaled = (raw - deadZone) / (fullZone - deadZone);
				}
				player->buttonValues[index] = scaled;
			}
		}
		// FUNCTION: ENGINE 0x10846D40
		// EQUIVALENT: register allocation (the engine keeps the zero in xmm1 and loads the axes into xmm0, ours the other way round); 98.1 %
		void PhysicalController::ReadHat(HatView* hat, PlayerInfo* player)
		{
			if (player->context != 0 && player->analog[hat->xAxis].input != 0.0f)
			{
				return;
			}
			if (player->context != 0 && player->analog[hat->yAxis].input != 0.0f)
			{
				return;
			}
			float position = hat->point->Read(0);
			float x;
			if (position >= 0.0625f && position < 0.4375f)
			{
				x = 1.0f;
			}
			else if (position >= 0.5625f && position < 0.9375f)
			{
				x = -1.0f;
			}
			else
			{
				x = 0.0f;
			}
			float y;
			if (position >= 0.0f && position < 0.1875f)
			{
				y = 1.0f;
			}
			else if (position >= 0.3125f && position < 0.6875f)
			{
				y = -1.0f;
			}
			else if (position >= 0.8125f && position < 1.0f)
			{
				y = 1.0f;
			}
			else
			{
				y = 0.0f;
			}
			player->analog[hat->xAxis].input = x;
			player->analog[hat->yAxis].input = y;
		}

		// FUNCTION: ENGINE 0x108472A0
		void PhysicalController::UpdateAxes(PlayerInfo* player)
		{
			for (int i = 0; i < 17; i++)
			{
				player->analog[i].input = 0.0f;
			}
			for (int i = 0; i < axisCount; i++)
			{
				switch (axes[i].kind)
				{
				case 1:
				case 2:
					if (player->context == 0 || player->analog[axes[i].axis].input == 0.0f)
					{
						float minimum = 0.0f;
						float maximum = 0.0f;
						axes[i].point->GetRange(&minimum, &maximum);
						if (axes[i].kind == 2)
						{
							axes[i].point->SetRange(1.0f, -1.0f);
						}
						else
						{
							axes[i].point->SetRange(-1.0f, 1.0f);
						}
						float value = axes[i].point->Read(0);
						axes[i].point->SetRange(minimum, maximum);
						player->analog[axes[i].axis].input = value;
					}
					break;
				case 3:
					if (player->context == 0 || player->analog[axes[i].axis].input == 0.0f)
					{
						float value = 0.0f;
						if (axes[i].point != 0)
						{
							axes[i].point->SetRange(0.0f, 1.0f);
							value = axes[i].point->Read(0);
						}
						if (axes[i].point2 != 0)
						{
							axes[i].point2->SetRange(0.0f, -1.0f);
							value = axes[i].point2->Read(0) + value;
						}
						player->analog[axes[i].axis].input = value;
					}
					break;
				case 4:
				case 5:
					ReadMouse((MouseView*)&axes[i].axis, player);
					break;
				case 6:
					ReadHat((HatView*)&axes[i].axis, player);
					break;
				}
			}
		}

		// FUNCTION: ENGINE 0x108474E0
		// EQUIVALENT: register allocation (ebx and ebp swapped, so is the position of the read flag store); 82.3 %
		void PhysicalController::Read(PlayerInfo* player)
		{
			UpdateButtons(player);
			UpdateAxes(player);
			camera::Director* director = camera::Director::Get();
			const math::Matrix* matrix = &math::Matrix::IDENTITY;
			const math::Vector* position = &math::kZeroVector;
			int slot = InputSystem::Get()->FindSlot(player->id);
			if (slot >= 0)
			{
				int target = director->GetCameraUnknown44(slot, 0);
				if (target != 0)
				{
					matrix = (const math::Matrix*)(target + 0x90);
				}
				camera::Cinematographer* cinematographer = director->GetCamera(slot, 0);
				if (cinematographer != 0)
				{
					camera::Camera* driver = camera::Director::Get()->GetController(cinematographer->controller);
					position = driver != 0 ? &driver->position : &math::kZeroVector;
				}
			}
			player->viewMatrix = *matrix;
			player->viewPosition[0] = position->x;
			player->viewPosition[1] = position->y;
			player->viewPosition[2] = position->z;
			read = true;
		}
		// FUNCTION: ENGINE 0x10846340
		PhysicalController::ButtonBinding* PhysicalController::FindButton(int value)
		{
			for (int i = 0; i < buttonCount; i++)
			{
				switch (buttons[i].kind)
				{
				case 1:
				case 3:
					if (buttons[i].value == value)
					{
						return &buttons[i];
					}
					break;
				case 2:
					if (buttons[i].value == value || buttons[i].value2 == value)
					{
						return &buttons[i];
					}
					break;
				}
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x108463A0
		// EQUIVALENT: the engine gives the kinds 3 and 6 a common return block and the kinds 1, 2, 4 and 5 their own, ours shares one block, so one jump displacement differs; 99.3 %
		PhysicalController::AxisBinding* PhysicalController::FindAxis(int axis)
		{
			for (int i = 0; i < axisCount; i++)
			{
				switch (axes[i].kind)
				{
				case 1:
				case 2:
				case 4:
				case 5:
					if (axes[i].axis == axis)
					{
						return &axes[i];
					}
					break;
				case 3:
				{
					int candidate = axes[i].axis;
					if (candidate == axis)
					{
						return &axes[i];
					}
					break;
				}
				case 6:
					if (axes[i].axis == axis)
					{
						return &axes[i];
					}
					if (axes[i].axis2 == axis)
					{
						return &axes[i];
					}
					break;
				}
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x10846430
		// EQUIVALENT: register allocation (ours keeps the binding array in ebp, the engine in ecx) and the engine compares the point against zero in memory; 36.1 %
		PhysicalController::AxisBinding* PhysicalController::FindAxisDirection(int axis, bool positive)
		{
			for (int i = 0; i < axisCount; i++)
			{
				if (axes[i].kind == 3 && axes[i].axis == axis)
				{
					core::IControllerInputPoint* point = positive ? axes[i].point : axes[i].point2;
					if (point != 0)
					{
						return &axes[i];
					}
				}
			}
			return 0;
		}
		// The input point numbers of a keyboard: the mapping names the keys by an index of its own (0x110BC840)
		extern int* gKeyboardRemap;

		// FUNCTION: ENGINE 0x10846490
		// NONMATCHING: the engine passes the range of a kind-dependent input point as one call with x87 loads of the two bounds, ours compiles the same conditions into SSE or into two calls, and the frame is 4 bytes larger; 74.9 %
#ifdef NONMATCHING
		void PhysicalController::Bind(const Mapping* mapping)
		{
			ReleaseBindings();
			ReleaseMotors();
			bool isKeyboard = false;
			if (core::StrCmp(controller->GetTypeName(), "Keyboard") == 0)
			{
				isKeyboard = true;
			}
			buttonCount = 0;
			for (int i = 0; i < mapping->buttonCount; i++)
			{
				const ButtonSource* source = &mapping->buttons[i];
				if (source->kind == 0)
				{
					continue;
				}
				switch (source->kind)
				{
				case 1:
				case 3:
				{
					core::IControllerInputPoint* point = controller->GetInput(source->index);
					if (isKeyboard)
					{
						point = controller->GetInput(gKeyboardRemap[source->index]);
					}
					if (point != 0)
					{
						if (source->kind == 3)
						{
							point->SetRange(-1.0f, 1.0f);
						}
						else
						{
							point->SetRange(0.0f, 1.0f);
						}
						point->AddRef();
						buttons[buttonCount].kind = source->kind;
						buttons[buttonCount].value = source->value;
						buttons[buttonCount].point = point;
						buttonCount++;
					}
					break;
				}
				case 2:
				{
					core::IControllerInputPoint* point = controller->GetInput(source->index2);
					if (isKeyboard)
					{
						point = controller->GetInput(gKeyboardRemap[source->index2]);
					}
					if (point != 0)
					{
						buttons[buttonCount].kind = source->kind;
						point->SetRange(-1.0f, 1.0f);
						point->AddRef();
						buttons[buttonCount].value = source->value;
						buttons[buttonCount].value2 = source->index;
						buttons[buttonCount].point2 = point;
						boundCount = 16;
						buttonCount++;
					}
					break;
				}
				}
			}
			axisCount = 0;
			for (int i = 0; i < mapping->axisCount; i++)
			{
				const AxisSource* source = &mapping->axes[i];
				if (source->kind == 0)
				{
					continue;
				}
				axes[axisCount].kind = source->kind;
				switch (axes[axisCount].kind)
				{
				case 1:
				case 2:
					axes[axisCount].point = controller->GetInput(source->index);
					if (isKeyboard)
					{
						axes[axisCount].point = controller->GetInput(gKeyboardRemap[source->index]);
					}
					if (axes[axisCount].point != 0)
					{
						axes[axisCount].point->AddRef();
						if (source->kind == 2)
						{
							axes[axisCount].point->SetRange(1.0f, -1.0f);
						}
						else
						{
							axes[axisCount].point->SetRange(-1.0f, 1.0f);
						}
						axes[axisCount].axis = source->axis;
						axisCount++;
					}
					break;
				case 3:
					axes[axisCount].point = controller->GetInput(source->index);
					axes[axisCount].point2 = controller->GetInput(source->index3);
					if (isKeyboard)
					{
						axes[axisCount].point = controller->GetInput(gKeyboardRemap[source->index]);
						axes[axisCount].point2 = controller->GetInput(gKeyboardRemap[source->index3]);
					}
					if (axes[axisCount].point != 0 || axes[axisCount].point2 != 0)
					{
						if (axes[axisCount].point != 0)
						{
							axes[axisCount].point->AddRef();
							axes[axisCount].point->SetRange(0.0f, 1.0f);
						}
						if (axes[axisCount].point2 != 0)
						{
							axes[axisCount].point2->AddRef();
							axes[axisCount].point2->SetRange(0.0f, -1.0f);
						}
						axes[axisCount].axis = source->axis;
						axisCount++;
					}
					break;
				case 4:
				case 5:
					axes[axisCount].point = controller->GetInput(source->index);
					if (axes[axisCount].point != 0)
					{
						axes[axisCount].point->AddRef();
						axes[axisCount].point->SetRange(0.0f, source->kind == 5 ? -1.0f : 1.0f);
						axes[axisCount].axis = source->axis;
						axes[axisCount].unknownC = 0.0f;
						axes[axisCount].accumulated = 0.0f;
						axes[axisCount].unknown18 = 1;
						axisCount++;
					}
					break;
				case 6:
					axes[axisCount].point2 = controller->GetInput(source->index2);
					if (isKeyboard)
					{
						axes[axisCount].point2 = controller->GetInput(gKeyboardRemap[source->index2]);
					}
					if (axes[axisCount].point2 != 0)
					{
						axes[axisCount].point2->AddRef();
						axes[axisCount].axis = source->axis;
						axes[axisCount].axis2 = source->index;
						axisCount++;
					}
					break;
				}
			}
			motorsFound = 0;
			for (int i = 0; i < motorCount; i++)
			{
				core::IControllerOutputPoint* output = controller->GetOutput(i);
				if (output != 0)
				{
					output->AddRef();
					motors[motorsFound].index = i;
					motors[motorsFound].output = output;
					motorsFound++;
				}
			}
		}
#endif
	}
}

// Kept copies (inline members of this unit):
// FUNCTION: ENGINE 0x10845BF0
// FUNCTION: ENGINE 0x10845C70
