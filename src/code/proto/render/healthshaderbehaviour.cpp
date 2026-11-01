#include "code/proto/render/healthshaderbehaviour.h"
#include "code/core/heap.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/healthmessages.h"
#include "code/engine/render/async/drawable.h"
#include "code/pure3d/primitive.h"

namespace audio
{
	extern const float gZero;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x102EF1D0
	HealthShaderBehaviour::HealthShaderBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), dirty(true), heap(core::GetCurrentHeap())
	{
		Listen(0x14, true);
		Listen(7, true);
		Listen2(0x100, true);
	}

	// FUNCTION: ENGINE 0x102EF190
	content::ClassInfo* HealthShaderBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HealthShaderBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102EF230
	HealthShaderBehaviour::~HealthShaderBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x102EF240
	void HealthShaderBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 7:
			if (message->id == 9)
			{
				dirty = true;
			}
			break;
		case 0x14:
			switch ((unsigned short)message->id)
			{
			case 0:
			case 2:
			case 3:
				dirty = true;
				break;
			case 0xc:
				if (audio::gZero < ((engine::DamageAppliedMessage*)message)->taken)
				{
					dirty = true;
				}
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x102EF360
	void HealthShaderBehaviour::UpdateShader()
	{
		engine::GetMinHealthMessage minMessage(0.0f);
		owner->SendMessage(&minMessage);
		engine::GetHealthMessage healthMessage;
		owner->PostMessage(&healthMessage);
		float percent = engine::driving::gOne;
		if (minMessage.minHealth < healthMessage.maxHealth)
		{
			float value = (healthMessage.health - minMessage.minHealth) / (healthMessage.maxHealth - minMessage.minHealth);
			if (!(value >= 0.0f))
			{
				value = 0.0f;
			}
			if (value - engine::driving::gOne >= 0.0f)
			{
				value = engine::driving::gOne;
			}
			percent = value;
		}
		engine::GetCurrentDrawable drawableMessage;
		owner->SendMessage(&drawableMessage);
		engine::render::Drawable drawable = drawableMessage.drawable;
		if (drawable.IsValid())
		{
			if (percent < engine::driving::gOne)
			{
				core::HeapScope scope(heap);
				pure3d::pddiShaderInputInitData data;
				data.SetDefault(1, "health_percent");
				drawable.CreateBindings(data);
			}
			drawable.SetBindingFloat(core::Name<core::CaseInsensitiveKey32>("health_percent", 1), percent);
		}
	}

	// FUNCTION: ENGINE 0x102EF5E0
	void HealthShaderBehaviour::Update(float dt, unsigned short mask)
	{
		if (dirty)
		{
			UpdateShader();
			dirty = false;
		}
	}

	// FUNCTION: ENGINE 0x102EF560
	content::MemberList* HealthShaderBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, HealthShaderBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102EF180
// FUNCTION: ENGINE 0x102EF2C0
// FUNCTION: ENGINE 0x102EF2F0
// FUNCTION: ENGINE 0x102EF300
// FUNCTION: ENGINE 0x102EF330

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102EF140
