#include "code/engine/poseanimationbehaviour.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/nis/nis.h"
#include "code/engine/render/async/drawable.h"
#include "code/pure3d/pose.h"
#include "code/pure3d/primitive.h"

namespace proto
{
	// The lookup of the parts of a drawable (effecttrack.h) and the names of the attributes that hold it and the
	// drawable's handle (0x112834C8, 0x112834D0)
	struct PartLookup;
	extern content::ObjectName gDrawableAttributeName;
	extern content::ObjectName gDrawableHandleAttributeName;
}

namespace engine
{
	namespace driving
	{
		// 0x10D94F78: 0.0f in the pooled constants (name guess)
		extern const float gZero;
	}

	extern int gAttributeHeap;
	extern content::ObjectName gAnimationFinished;
	extern content::ObjectName gPoseAwakeName;
	extern content::ObjectName gPoseAnimationControllerName;

	// What the pose keeps of its root joint: the matrix of the root at +0x30
	struct PoseRootView
	{
		unsigned char unknown0[0x30];
		math::Matrix* root;
	};

	// The access to a named bool attribute (the engine inlines the lookup here)
	static inline AttributeWriter<bool> GetBoolWriter(GameObject* object, const content::ObjectName& name)
	{
		BaseAttribute* attribute = object->FindAttribute(name);
		if (attribute != 0)
		{
			bool* value = &((Attribute<bool>*)attribute)->Get();
			return AttributeWriter<bool>(value, name, object);
		}
		return AttributeWriter<bool>();
	}

	// FUNCTION: ENGINE 0x109208B0
	content::ClassInfo* PoseAnimationBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PoseAnimationBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10920AF0
	content::MemberList* PoseAnimationBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, PoseAnimationBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10920C60
	void PoseAnimationBehaviour::CreateController()
	{
		if (controller == 0)
		{
			Attribute<proto::PartLookup*>* drawable =
				(Attribute<proto::PartLookup*>*)owner->FindAttribute(proto::gDrawableAttributeName);
			proto::PartLookup* lookup = drawable->value;
			pure3d::PoseAnimationController* created = new pure3d::PoseAnimationController();
			pure3d::RefCounted::Assign<pure3d::FrameController>(controller, created);
			((pure3d::PoseAnimationController*)controller)->SetPose((pure3d::Pose*)lookup);
			Attribute<pure3d::PoseAnimationController*>* attribute =
				(Attribute<pure3d::PoseAnimationController*>*)owner->FindAttribute(gPoseAnimationControllerName);
			attribute->value = (pure3d::PoseAnimationController*)controller;
		}
	}

	// FUNCTION: ENGINE 0x10920CD0
	void PoseAnimationBehaviour::DestroyController()
	{
		Attribute<pure3d::PoseAnimationController*>* attribute =
			(Attribute<pure3d::PoseAnimationController*>*)owner->FindAttribute(gPoseAnimationControllerName);
		attribute->value = 0;
		pure3d::RefCounted::Release<pure3d::FrameController>(controller);
	}

	// FUNCTION: ENGINE 0x10920DE0
	void PoseAnimationBehaviour::Slot1()
	{
		Attribute<render::Drawable>* attribute =
			(Attribute<render::Drawable>*)owner->FindAttribute(proto::gDrawableHandleAttributeName);
		render::Drawable drawable = attribute->value;
		if (drawable.IsValid())
		{
			drawable.StopAnimation();
			pure3d::Animation* source = (pure3d::Animation*)drawable.GetSourceParameters();
			if (source != 0)
			{
				CreateController();
				controller->SetNameFrom(source);
				((pure3d::AnimationFrameController*)controller)->SetAnimation(source, 0.0f, 0.0f);
			}
		}
	}

	// FUNCTION: ENGINE 0x10920E50
	void PoseAnimationBehaviour::UpdateActivity()
	{
		bool awake = false;
		if (controller != 0 && !paused)
		{
			awake = !controller->Unknown20();
		}
		Listen2(4, awake);
		((Attribute<bool>*)owner->FindAttribute(gAnimationFinished))->Get() = !awake;
		AttributeWriter<bool> writer = GetBoolWriter(owner, gPoseAwakeName);
		*writer.value = awake;
	}

	// FUNCTION: ENGINE 0x10921030
	void PoseAnimationBehaviour::Resume()
	{
		paused = false;
		UpdateActivity();
	}

	// FUNCTION: ENGINE 0x10921040
	void PoseAnimationBehaviour::Pause()
	{
		paused = true;
		UpdateActivity();
	}

	// The object's pose animation controller attribute, made when the object has none (0x10920F10; the engine keeps
	// this instance in the unit)
	// FUNCTION: ENGINE 0x10920F10
	template<> Attribute<pure3d::PoseAnimationController*>*
	GameObject::SetAttributeAndGet<pure3d::PoseAnimationController*>(const content::ObjectName& name,
		pure3d::PoseAnimationController* const& value, bool overwrite)
	{
		Attribute<pure3d::PoseAnimationController*>* attribute =
			(Attribute<pure3d::PoseAnimationController*>*)FindAttribute(name);
		if (attribute == 0)
		{
			if (this == GetConstructingObject())
			{
				core::HeapScope scope(GetConstructionHeap());
				attribute = new Attribute<pure3d::PoseAnimationController*>();
				attribute->value = value;
				AddAttribute(name, attribute);
			}
			else
			{
				core::HeapScope scope(gAttributeHeap);
				attribute = new Attribute<pure3d::PoseAnimationController*>();
				attribute->value = value;
				if (!AddDynamicAttribute(name, attribute))
				{
					delete attribute;
					return 0;
				}
			}
		}
		else if (overwrite)
		{
			attribute->value = value;
		}
		return attribute;
	}

	// FUNCTION: ENGINE 0x10921260
	PoseAnimationBehaviour::PoseAnimationBehaviour(GameObject* newOwner) : Behaviour(newOwner), controller(0),
		pendingTime(0.0f), paused(false)
	{
		Listen(1, true);
		Listen(2, true);
		Listen(10, true);
		Listen(0x17, true);
		owner->SetAttributeAndGet<proto::PartLookup*>(proto::gDrawableAttributeName, 0, false);
		owner->SetAttribute<bool>(gAnimationFinished, false, false);
		owner->SetAttributeAndGet<pure3d::PoseAnimationController*>(gPoseAnimationControllerName, 0, false);
		owner->SetAttribute<bool>(gPoseAwakeName, false, false);
	}

	// FUNCTION: ENGINE 0x109208F0
	void PoseAnimationBehaviour::Rewind()
	{
		if (controller != 0)
		{
			controller->Reset();
		}
	}

	// FUNCTION: ENGINE 0x109209A0
	void PoseAnimationBehaviour::OnControlBegin(PoseControlMessage* message)
	{
		if (!requested.Test(7))
		{
			OnActiveChanged(true);
			SetState(1);
			handle = message->handle;
			return;
		}
		handle = message->handle;
	}

	// FUNCTION: ENGINE 0x109209F0
	void PoseAnimationBehaviour::OnControlEnd(PoseControlMessage* message)
	{
		if (requested.Test(7) && (state & 1) != 0)
		{
			ClearState(1);
			OnActiveChanged(false);
			handle.index = 0xffff;
			handle.serial = 0;
		}
	}

	// FUNCTION: ENGINE 0x10921050
	void PoseAnimationBehaviour::Play(PoseAnimationMessage* message)
	{
		pure3d::Entity* animation = message->animation;
		if (animation != 0)
		{
			if (controller == 0)
			{
				CreateController();
			}
			controller->SetNameFrom(animation);
			((pure3d::AnimationFrameController*)controller)->SetAnimation((pure3d::Animation*)animation, 0.0f, 0.0f);
			float time = message->time;
			if (message->rangeStart > message->time)
			{
				pendingTime = message->time - message->rangeStart;
				time = message->rangeStart;
			}
			if (message->cycleMode == 3)
			{
				time = message->rangeEnd;
			}
			controller->SetFrameRange(message->rangeStart, message->rangeEnd);
			controller->SetFrame(time);
			controller->SetRelativeSpeed(message->speed);
			controller->SetCycleMode((pure3d::Animation::CycleMode)message->cycleMode);
			controller->SetNumCycles(message->numCycles);
			controller->Unknown5();
			UpdateActivity();
			return;
		}
		if (controller != 0)
		{
			((pure3d::PoseAnimationController*)controller)->GetPose()->Unknown106DD760();
			((pure3d::PoseAnimationController*)controller)->GetPose()->Update();
			DestroyController();
		}
		UpdateActivity();
	}

	// FUNCTION: ENGINE 0x10921170
	void PoseAnimationBehaviour::SetPlayback(PoseAnimationPlaybackMessage* message)
	{
		if (controller != 0)
		{
			controller->Reset();
			float start = message->rangeStart;
			float end = message->rangeEnd;
			int mode = message->cycleMode;
			if (mode == 2 || mode == 4)
			{
				controller->SetFrame(start);
			}
			if (mode == 3 || mode == 5)
			{
				controller->SetFrame(end);
			}
			if (mode == 1 || mode == 0)
			{
				controller->SetFrame(start);
			}
			controller->SetFrameRange(start, end);
			controller->SetRelativeSpeed(message->speed);
			controller->SetCycleMode((pure3d::Animation::CycleMode)mode);
			controller->SetNumCycles(message->numCycles);
			UpdateActivity();
		}
	}

	// FUNCTION: ENGINE 0x10921320
	void PoseAnimationBehaviour::OnMessage(Message* message)
	{
		switch (message->type)
		{
		case 1:
			if (controller != 0 && ((PoseAttributeMessage*)message)->name == proto::gDrawableAttributeName)
			{
				Attribute<proto::PartLookup*>* drawable =
					(Attribute<proto::PartLookup*>*)owner->FindAttribute(proto::gDrawableAttributeName);
				if (drawable != 0 && drawable->value != 0)
				{
					((pure3d::PoseAnimationController*)controller)->SetPose((pure3d::Pose*)drawable->value);
				}
			}
			break;
		case 2:
			Rewind();
			break;
		case 10:
			switch ((unsigned short)message->id)
			{
			case 2:
				Resume();
				break;
			case 3:
				Pause();
				break;
			case 0:
				Play((PoseAnimationMessage*)message);
				break;
			case 1:
				SetPlayback((PoseAnimationPlaybackMessage*)message);
				break;
			}
			break;
		case 0x17:
			switch ((unsigned short)message->id)
			{
			case 4:
				OnControlBegin((PoseControlMessage*)message);
				break;
			case 6:
				OnControlEnd((PoseControlMessage*)message);
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10920B50
	void PoseAnimationBehaviour::Update(float dt, unsigned short mask)
	{
		if (controller != 0 && !paused)
		{
			if (pendingTime != driving::gZero)
			{
				float quotient = pendingTime / controller->Unknown8();
				pendingTime = 0.0f;
				dt = quotient + dt;
			}
			controller->Advance(dt * 1000.0f, true);
			Attribute<proto::PartLookup*>* drawable =
				(Attribute<proto::PartLookup*>*)owner->FindAttribute(proto::gDrawableAttributeName);
			pure3d::Pose* pose = (pure3d::Pose*)drawable->value;
			GameObject* target = handle.Get();
			if (target != 0)
			{
				pose->UpdateLocal();
				math::Matrix& result = owner->transform->Get();
				result.Multiply(*((PoseRootView*)pose)->root, target->transform->value);
				*(NISTransform*)((PoseRootView*)pose)->root = *(const NISTransform*)&math::Matrix::IDENTITY;
			}
			pose->Update();
			if (controller->Unknown20())
			{
				((Attribute<bool>*)owner->FindAttribute(gAnimationFinished))->Get() = true;
			}
		}
	}

	// FUNCTION: ENGINE 0x10920DC0
	PoseAnimationBehaviour::~PoseAnimationBehaviour()
	{
		DestroyController();
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10920950
// FUNCTION: ENGINE 0x10920960
// FUNCTION: ENGINE 0x10920970
// FUNCTION: ENGINE 0x10920A60
// FUNCTION: ENGINE 0x10920A80
// FUNCTION: ENGINE 0x10920AB0
// FUNCTION: ENGINE 0x10920AD0
// FUNCTION: ENGINE 0x10920D80
// FUNCTION: ENGINE 0x10920DA0
// FUNCTION: ENGINE 0x10921010
