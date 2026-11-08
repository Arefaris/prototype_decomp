#include "code/proto/behaviours/fadebehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/engine/render/async/drawable.h"

namespace engine
{
	namespace driving
	{
		// 0x10D946E0 / 0x10D95578: 1.0f and 2.0f in the pooled constants (name guesses)
		extern const float gOne;
		extern const float gTwo;
		extern const float gZero;
	}
	extern content::ObjectName gPhysicsObjectAttributeName;
}

namespace proto
{
	// 0x10D977EC: 10.0f in the pooled constants (name guess)
	extern const float gTen;

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// The message the fade reads (type 0x3D, id 0x13): whether to fade in
	struct FadeMessage : public engine::Message
	{
		FadeMessage(int newType, short newId) : engine::Message(newType, newId)
		{
		}

		bool fadeIn;  // +0xC
	};

	// FUNCTION: ENGINE 0x10497550
	content::ClassInfo* FadeoutBehaviourProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FadeoutBehaviourProperties";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10497590
	content::ClassInfo* FadeoutBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FadeoutBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104975D0
	content::ClassInfo* FadeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FadeBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10497610
	FadeoutBehaviour::FadeoutBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), properties(0),
		timeLeft(0.0f)
	{
		Listen(2, true);
	}

	// FUNCTION: ENGINE 0x10497650
	void FadeoutBehaviour::Restart()
	{
		timeLeft = properties->lifeLength + properties->fadeoutLength;
	}

	// FUNCTION: ENGINE 0x10497670
	// NONMATCHING: the engine stores the class's vftable after the first member stores, ours right after the base constructor (39 %)
#ifdef NONMATCHING
	FadeBehaviour::FadeBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		opacity = 0.0f;
		state = FADING_IN;
		fadeInTime = engine::driving::gTwo;
		fadeOutTime = engine::driving::gTwo;
		destroyOnFadeOutComplete = true;
		Listen(2, true);
		Listen(0x3d, true);
	}
#endif

	// FUNCTION: ENGINE 0x104976F0
	// NONMATCHING: the engine stores the opacity after the compare with 1.0 (95.4 %)
#ifdef NONMATCHING
	void FadeBehaviour::Update(float dt, unsigned short mask)
	{
		if (state == FADING_IN)
		{
			float value = dt / fadeInTime + opacity;
			bool done = engine::driving::gOne <= value;
			opacity = value;
			if (done)
			{
				opacity = engine::driving::gOne;
				state = DONE;
			}
		}
		else if (state == FADING_OUT)
		{
			float value = opacity - dt / fadeOutTime;
			opacity = value;
			if (value <= 0.0f)
			{
				opacity = 0.0f;
				state = DONE;
				if (destroyOnFadeOutComplete)
				{
					engine::GameObjectHandle handle = engine::GetHandle(owner);
					handle.DeferUpdate(true);
				}
			}
		}
		engine::render::Drawable drawable(owner);
		drawable.SetUnknownBC(opacity);
		if (state == DONE)
		{
			Listen2(4, false);
		}
	}
#endif

	// FUNCTION: ENGINE 0x104977F0
	void FadeBehaviour::Reset()
	{
		opacity = 0.0f;
		state = FADING_IN;
		engine::render::Drawable drawable(owner);
		drawable.SetUnknownBC(opacity);
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x10497870
	// NONMATCHING: the engine writes the class's vftable in the middle of the member stores, ours writes both vftables first (41 %)
#ifdef NONMATCHING
	FadeoutBehaviourProperties::FadeoutBehaviourProperties() : fadeoutLength(engine::driving::gOne)
	{
		checkPhysicsAtRest = true;
		disablePhysicsForFadeout = true;
		lifeLength = gTen;
	}
#endif

	// The check ObjectHandle::IsValid makes, expanded as the engine does here
	static inline bool IsHandleValid(const ravenphysics::ObjectHandle* handle)
	{
		if (handle->index >= ravenphysics::gCollisionObjectTable->slotCount)
		{
			return false;
		}
		return ravenphysics::gCollisionObjectTable->entries.begin[handle->index].serial == handle->unknown2;
	}

	// FUNCTION: ENGINE 0x10497F40
	void FadeoutBehaviour::Update(float dt, unsigned short mask)
	{
		timeLeft = timeLeft - dt;
		if (properties->checkPhysicsAtRest)
		{
			engine::BaseAttribute* attribute = owner->FindAttribute(engine::gPhysicsObjectAttributeName);
			if (attribute != 0)
			{
				ravenphysics::ObjectHandle* handle = &((engine::Attribute<ravenphysics::ObjectHandle>*)attribute)->value;
				if (handle != 0)
				{
					if (IsHandleValid(handle))
					{
						ravenphysics::PhysicsObject* physics = handle->GetObject();
						if (physics != 0 && (physics->collisionMode & 3) == 2 && physics->IsAsleep())
						{
							Restart();
						}
					}
				}
			}
		}
		dt = timeLeft;
		if (dt <= properties->fadeoutLength && properties->fadeoutLength > engine::driving::gZero)
		{
			dt = dt / properties->fadeoutLength;
			engine::render::Drawable drawable(owner);
			drawable.SetPartsUnknown2C(dt);
			if (properties->disablePhysicsForFadeout)
			{
				engine::PhysicsSetEnabledMessage message(false);
				owner->SendMessage(&message);
			}
		}
		if (timeLeft <= 0.0f)
		{
			engine::GameObjectHandle handle = engine::GetHandle(owner);
			handle.DeferUpdate(true);
		}
	}

	// FUNCTION: ENGINE 0x10497980
	FadeoutBehaviour::~FadeoutBehaviour()
	{
		core::SafeRelease(properties);
	}

	// FUNCTION: ENGINE 0x104979B0
	void FadeoutBehaviour::Slot1()
	{
		Restart();
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x104979D0
	void FadeoutBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
			case 2:
				Restart();
				break;
		}
	}

	// FUNCTION: ENGINE 0x10497A20
	void FadeBehaviour::Slot1()
	{
		Reset();
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x10497A40
	void FadeBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
			case 2:
				Reset();
				break;
			case 0x3d:
				if (message->id == 0x13)
				{
					state = static_cast<FadeMessage*>(message)->fadeIn == 0;
					Listen2(4, true);
				}
				break;
		}
	}

	// FUNCTION: ENGINE 0x10497C90
	content::MemberList* FadeoutBehaviourProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<FadeoutBehaviourProperties, bool, 0>("p"),
				PROTO_OFFSET(FadeoutBehaviourProperties, checkPhysicsAtRest), "checkPhysicsAtRest" },
			{ content::GetMemberPrimitiveMetaType<FadeoutBehaviourProperties, bool, 1>("p"),
				PROTO_OFFSET(FadeoutBehaviourProperties, disablePhysicsForFadeout), "disablePhysicsForFadeout" },
			{ content::GetMemberPrimitiveMetaType<FadeoutBehaviourProperties, float, 0>("p"),
				PROTO_OFFSET(FadeoutBehaviourProperties, fadeoutLength), "fadeoutLength" },
			{ content::GetMemberPrimitiveMetaType<FadeoutBehaviourProperties, float, 1>("p"),
				PROTO_OFFSET(FadeoutBehaviourProperties, lifeLength), "lifeLength" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10497DD0
	content::MemberList* FadeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, FadeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<FadeBehaviour, float, 0>("p"),
				PROTO_OFFSET(FadeBehaviour, fadeInTime), "fadeInTime" },
			{ content::GetMemberPrimitiveMetaType<FadeBehaviour, float, 1>("p"),
				PROTO_OFFSET(FadeBehaviour, fadeOutTime), "fadeOutTime" },
			{ content::GetMemberPrimitiveMetaType<FadeBehaviour, bool, 0>("p"),
				PROTO_OFFSET(FadeBehaviour, destroyOnFadeOutComplete), "destroyOnFadeOutComplete" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10498120
	content::MemberList* FadeoutBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, FadeoutBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<FadeoutBehaviour, FadeoutBehaviourProperties>("p"),
				PROTO_OFFSET(FadeoutBehaviour, properties), "properties" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10497840
// FUNCTION: ENGINE 0x10497850
// FUNCTION: ENGINE 0x104978D0
// FUNCTION: ENGINE 0x10497910
// FUNCTION: ENGINE 0x10497A90
// FUNCTION: ENGINE 0x10497AD0
// FUNCTION: ENGINE 0x10497B10
// FUNCTION: ENGINE 0x10497B50
// FUNCTION: ENGINE 0x10497B90
// FUNCTION: ENGINE 0x10497BD0
// FUNCTION: ENGINE 0x10497C10
// FUNCTION: ENGINE 0x10497C50
// FUNCTION: ENGINE 0x104980C0
// FUNCTION: ENGINE 0x104978E0
// FUNCTION: ENGINE 0x10497920
// FUNCTION: ENGINE 0x10497C60
// FUNCTION: ENGINE 0x10497F10
