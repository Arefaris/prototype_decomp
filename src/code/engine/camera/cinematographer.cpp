#include "code/engine/camera/cinematographer.h"
#include "code/engine/camera/animatedcamera.h"
#include "code/engine/camera/blendcamera.h"
#include "code/engine/camera/cameraloader.h"
#include "code/engine/camera/director.h"
#include "code/engine/camera/debugcamera.h"
#include "code/engine/controller/inputsystem.h"
#include "code/math/matrix.h"
#include "code/pure3d/camera.h"
#include <math.h>

namespace content
{
	static const EnumValue sCinematographerTypeValues[] =
	{
		{ "DefaultView", 0 },
		{ "SecondView", 1 }
	};

	// FUNCTION: ENGINE 0x1084DE40
	template<> void EnumInfo<engine::camera::CinematographerType>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "engine::camera::CinematographerType";
		*code = "p";
		*values = sCinematographerTypeValues;
		*count = 2;
	}
}

namespace choreo
{
	extern const float gZero;
}

namespace engine
{
	// 0x107F2850 (another unit): whether the player slot is played on this machine
	bool IsLocalSlot(int slot);
	// 0x1085FBF0 / 0x10860C50 (another unit): the handle of the first / second display (names guessed)
	int* GetFirstDisplay(int* out);
	int* GetSecondDisplay(int* out);

	// The audio listener (the class and the global at 0x11316AA0 are another unit; names guessed)
	class AudioListener
	{
	public:
		// 0x108782E0: puts the listener where the matrix is
		void SetListener(const math::Matrix& matrix);
	};
	extern AudioListener* gAudioListener;

	namespace camera
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

		// FUNCTION: ENGINE 0x1084DDF0
		int Cinematographer::GetTypeValue() const
		{
			return type;
		}

		// FUNCTION: ENGINE 0x1084DE00
		void ControllerRef::Clear()
		{
			slot = -1;
			id = -1;
		}

		// FUNCTION: ENGINE 0x1084DE10
		bool ControllerRef::IsDifferent(ControllerRef other) const
		{
			return id != other.id;
		}

		// FUNCTION: ENGINE 0x1084DE30
		int DebugCamera::GetUnknown94() const
		{
			return unknown94;
		}

		// FUNCTION: ENGINE 0x1084FFE0
		void Cinematographer::SetHandle(HandleBase newHandle)
		{
			handle = newHandle;
		}

		// FUNCTION: ENGINE 0x1084DFC0
		void Cinematographer::AddHistoryA(float a, float b, float c, const math::Vector* vector, int index)
		{
			history.AddA(a, b, c, vector, index);
		}

		// FUNCTION: ENGINE 0x1084DFF0
		void Cinematographer::AddHistoryB(float a, float b, float c, float d, const math::Vector* vector, int index)
		{
			history.AddB(a, b, c, d, vector, index);
		}

		// FUNCTION: ENGINE 0x1084E030
		void Cinematographer::SetHistoryParameter(float value)
		{
			history.SetParameter(value);
		}

		// FUNCTION: ENGINE 0x1084E120
		int ReturnSecond(int unused, int value)
		{
			return value;
		}

		// FUNCTION: ENGINE 0x1084E130
		bool ControllerRef::IsValid() const
		{
			return Director::Get()->GetController(*this) != 0;
		}

		// FUNCTION: ENGINE 0x1084E150
		Cinematographer::Cinematographer()
			: type(0), playerIndex(0), enabled(false), unknown1D(false), cut(false), dirty(false), unknown20(false),
			unknown21(false), unknown28(), unknown2C(0.0f), mode(0), state(8), camera38(0), target(0), unknown40(0),
			unknown44(0), blend(0), defaultCamera(0), animated(0), unknown754(false), pendingTime(0.0f),
			unknown7A4(false), unknown7A5(false), unknown7A8(0), active(true), unknown7AD(false)
		{
			offset.Identity();
		}
		// FUNCTION: ENGINE 0x1084E220
		// FUNCTION: ENGINE 0x1084E8B0
		Cinematographer::~Cinematographer()
		{
			Shutdown();
		}

		// FUNCTION: ENGINE 0x1084DEB0
		void Cinematographer::Shutdown()
		{
			if (camera38 != 0)
			{
				camera38->ReleaseThunk();
			}
			if (target != 0)
			{
				((pure3d::Camera*)target)->ReleaseThunk();
			}
			unknown40 = 0;
			unknown44 = 0;
			if (animated != 0)
			{
				delete animated;
				animated = 0;
			}
			if (blend != 0)
			{
				delete blend;
				blend = 0;
			}
			Director* director = Director::Get();
			if (director != 0)
			{
				director->ClearCamera(this);
			}
		}

		// FUNCTION: ENGINE 0x1084DF10
		void Cinematographer::SetPlayerIndex(int value)
		{
			if (!Director::Get()->HasCamera(type, value))
			{
				playerIndex = value;
			}
		}

		// FUNCTION: ENGINE 0x1084DF40
		void Cinematographer::StartTransition(int camera, float time)
		{
			pending.Set((const Camera*)camera);
			pendingTime = time;
		}

		// FUNCTION: ENGINE 0x1084DF70
		void Cinematographer::SetUnknown7A5(bool value)
		{
			if (defaultCamera != 0)
			{
				unknown7A5 = value;
			}
		}

		// FUNCTION: ENGINE 0x1084DF90
		void Cinematographer::SetDefaultCameraEnabled(bool value)
		{
			defaultCamera->SetEnabled(value);
			state = value ? 2 : 8;
		}

		// FUNCTION: ENGINE 0x1084E050
		void Cinematographer::NotifyZoom()
		{
			if (unknown2C != 0.0f)
			{
				Director::Get()->NotifyControllersOfKind((int)this, unknown2C);
			}
		}

		// FUNCTION: ENGINE 0x1084E260
		void Cinematographer::Reset()
		{
			cut = false;
			dirty = false;
			unknown20 = false;
			unknown21 = false;
			unknown1D = false;
			state = 8;
			mode = 0;
			unknown7AD = false;
			if (camera38 != 0)
			{
				camera38->SetMatrix(math::Matrix::IDENTITY);
			}
			if (target != 0)
			{
				((pure3d::Camera*)target)->SetMatrix(math::Matrix::IDENTITY);
			}
			history.Clear();
			unknown754 = false;
			offset.Identity();
			blend->Stop();
			if (Director::Get()->GetController(previous) != 0)
			{
				Director::Get()->GetController(previous)->SetEnabled(false);
				previous.slot = -1;
				previous.id = -1;
			}
			pending.slot = -1;
			pending.id = -1;
			unknown7A4 = false;
			unknown7A5 = false;
			unknown7A8 = 0;
			pendingTime = 0.0f;
			active = true;
		}
		// FUNCTION: ENGINE 0x1084E4A0
		void Cinematographer::SetController(Camera* newController)
		{
			if (Director::Get()->GetController(controller) != 0)
			{
				if (controller.id != ControllerRef(previous).id)
				{
					Director::Get()->GetController(controller)->SetEnabled(false);
				}
			}
			controller.Set(newController);
			newController->SetEnabled(true);
		}

		// FUNCTION: ENGINE 0x1084E660
		void Cinematographer::SetMode(bool value)
		{
			mode = value ? 1 : 0;
			if (!value)
			{
				animated->SetEnabled(false);
			}
			if (Director::Get()->GetController(controller) != 0)
			{
				Director::Get()->GetController(controller)->SetEnabled(!value);
			}
		}

		// FUNCTION: ENGINE 0x1084E6D0
		void Cinematographer::SetDisplay(int display)
		{
			unknown28.value = display;
			if (unknown28.IsValid())
			{
				float aspect = GetAspect();
				if (aspect != unknown2C)
				{
					unknown2C = aspect;
					NotifyZoom();
				}
			}
		}

		// FUNCTION: ENGINE 0x1084E720
		void Cinematographer::Activate(bool value)
		{
			enabled = value;
			if (value)
			{
				int display;
				if (type == 0)
				{
					SetDisplay(*GetFirstDisplay(&display));
				}
				else
				{
					SetDisplay(*GetSecondDisplay(&display));
				}
			}
			else
			{
				unknown28.value = -1;
			}
			Director::Get()->OnCameraDisabled(this);
		}
		// FUNCTION: ENGINE 0x1084E8D0
		void Cinematographer::Start()
		{
			int localCount = 0;
			int first = -1;
			for (int i = 0; i < controller::InputSystem::Get()->slotCount; i++)
			{
				if (IsLocalSlot(i))
				{
					localCount++;
					if (first < 0)
					{
						first = i;
					}
				}
			}
			enabled = false;
			if (IsLocalSlot(playerIndex))
			{
				if (localCount == 1 || playerIndex == first)
				{
					Activate(true);
				}
			}
			animated = new AnimatedCamera();
			animated->Register();
			animated->SetPlayerIndex(playerIndex);
			animated->kind = (int)this;
			blend = new BlendCamera();
			blend->Register();
			blend->SetPlayerIndex(playerIndex);
			blend->kind = (int)this;
			camera38 = new pure3d::Camera();
			target = (CameraTarget*)new pure3d::Camera();
			camera38->AddRef();
			((pure3d::Camera*)target)->AddRef();
			unknown40 = (pure3d::Camera*)target;
			unknown44 = (pure3d::Camera*)target;
			Director* director = Director::Get();
			director->SetCamera(this);
		}
		// FUNCTION: ENGINE 0x1084E340
		bool Cinematographer::UpdateView()
		{
			unknown40 = unknown44 = (pure3d::Camera*)target;
			if (unknown1D)
			{
				return false;
			}
			pure3d::Camera* source = 0;
			bool result = false;
			if (!blend->IsDone())
			{
				source = blend->camera;
				result = blend->Slot4();
			}
			else
			{
				if (mode == 1)
				{
					source = animated->camera;
					result = animated->Slot4();
				}
				else if (Director::Get()->GetController(controller) != 0)
				{
					source = Director::Get()->GetController(controller)->camera;
					result = Director::Get()->GetController(controller)->Slot4();
				}
				if (Director::Get()->GetController(previous) != 0)
				{
					Director::Get()->GetController(previous)->SetEnabled(false);
					previous.slot = -1;
					previous.id = -1;
				}
			}
			if (source != 0)
			{
				camera38->CopyFrom(source);
				((pure3d::Camera*)target)->CopyFrom(camera38);
			}
			if (unknown754)
			{
				math::Matrix combined;
				combined.Multiply(offset, *camera38->GetWorldMatrix());
				((pure3d::Camera*)target)->SetMatrix(combined);
			}
			switch (state)
			{
			case 2:
				if (defaultCamera->unknown94 != 3)
				{
					pure3d::Camera* view = defaultCamera->camera;
					unknown44 = view;
					if (unknown7AD)
					{
						unknown40 = view;
					}
				}
				break;
			}
			return result;
		}

		// FUNCTION: ENGINE 0x1084E530
		void Cinematographer::StartBlend(bool value, float time)
		{
			if (value)
			{
				animated->SetEnabled(value);
			}
			blend->Stop();
			if (Director::Get()->GetController(previous) != 0)
			{
				Director::Get()->GetController(previous)->SetEnabled(false);
				previous.slot = -1;
				previous.id = -1;
			}
			if (time > choreo::gZero)
			{
				if (mode == 0 && value && Director::Get()->GetController(controller) != 0)
				{
					blend->Begin(controller, ControllerRef(animated), false, 3, time);
				}
				else if (mode == 1 && !value && Director::Get()->GetController(controller) != 0)
				{
					blend->Begin(ControllerRef(animated), controller, false, 3, time);
				}
			}
			unknown7A4 = value != 0;
		}

		// FUNCTION: ENGINE 0x1084EA20
		void Cinematographer::UpdatePending()
		{
			if (Director::Get()->GetController(pending) != 0)
			{
				blend->Stop();
				if (Director::Get()->GetController(previous) != 0)
				{
					Director::Get()->GetController(previous)->SetEnabled(false);
					previous.slot = -1;
					previous.id = -1;
				}
				Camera* current = Director::Get()->GetController(controller);
				Camera* next = Director::Get()->GetController(pending);
				if (pendingTime != choreo::gZero && mode == 0 && Director::Get()->GetController(controller) != 0)
				{
					float time = pendingTime;
					bool reverse = time < 0.0f;
					float magnitude = fabsf(time);
					if (next != current || !reverse)
					{
						blend->Begin(controller, pending, reverse, 3, magnitude);
						if (reverse)
						{
							previous.slot = controller.slot;
							previous.id = controller.id;
						}
					}
					SetController(next);
				}
				else
				{
					if (next != current)
					{
						SetController(next);
					}
					dirty = true;
				}
				pending.slot = -1;
				pending.id = -1;
			}
			bool animatedMode = mode == 1;
			if (unknown7A4 != animatedMode)
			{
				SetMode(unknown7A4);
				dirty = true;
			}
			bool defaultState = state == 2;
			if (unknown7A5 != defaultState)
			{
				SetDefaultCameraEnabled(unknown7A5);
				if (defaultCamera->unknown94 != 3 && unknown7AD)
				{
					dirty = true;
				}
			}
		}

		// FUNCTION: ENGINE 0x1084EC10
		void Cinematographer::Update(float delta, float time, int flags)
		{
			switch ((unsigned short)flags)
			{
			case 1:
				if (defaultCamera != 0)
				{
					defaultCamera->ReadInput();
				}
				if (enabled && unknown28.IsValid())
				{
					float aspect = GetAspect();
					if (aspect != unknown2C)
					{
						unknown2C = aspect;
						NotifyZoom();
					}
				}
				unknown754 = history.Evaluate(delta, true, &offset);
				unknown20 = UpdateView();
				if (unknown20 && unknown21 && mode == 1 && !dirty)
				{
					unknown20 = false;
				}
				cut = dirty || unknown20 || unknown21;
				break;
			case 0x80:
				{
					bool changed = UpdateView();
					unknown21 = false;
					if (changed && !unknown20 && mode == 1)
					{
						unknown21 = true;
					}
					cut = dirty || unknown20 || unknown21;
					Director* director = Director::Get();
					int index = director->playerCamera[0];
					bool found = true;
					if (index < 0)
					{
						found = director->NextActiveCamera(&index, 0);
					}
					if (found && index == playerIndex)
					{
						gAudioListener->SetListener(*target->MatrixAt90());
					}
					dirty = false;
					UpdatePending();
				}
				break;
			case 0x200:
				if (enabled)
				{
					unknown28.SetCameras(unknown44, unknown40);
				}
				break;
			}
		}
		// FUNCTION: ENGINE 0x1084DE70
		content::ClassInfo* Cinematographer::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::camera::Cinematographer";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1084E7E0
		content::MemberList* Cinematographer::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetNameMetaTypeCopy<Cinematographer>(true, true, "pn"), ENGINE_NAME_OFFSET(Cinematographer, name),
					"name" },
				{ content::GetEnumMetaType<CinematographerType>(), 8, "type" },
				{ content::GetMemberPrimitiveMetaType<Cinematographer, int, 0>("pn"),
					ENGINE_OFFSET(Cinematographer, playerIndex), "playerIndex" }
			};
			sList.members = sMembers;
			sList.count = 3;
			return &sList;
		}
	}
}

// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x1084E080
// FUNCTION: ENGINE 0x1084E0E0
// FUNCTION: ENGINE 0x1084E7A0
