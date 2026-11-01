#include "code/proto/render/decalbehaviour.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/render/effectmanager.h"

namespace choreo
{
	extern const float gMinusOne;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102EEC20
	void DecalBehaviour::Slot1()
	{
		decals.Allocate(maxDecals);
	}

	// FUNCTION: ENGINE 0x102EEC80
	// NONMATCHING: the engine lays the invalid-decal path out in front of the valid one (best 27 %)
#ifdef NONMATCHING
	void DecalBehaviour::Update(float dt, unsigned short mask)
	{
		float fadeStep = dt / fadeTime;
		Decal* decal = decals.begin;
		if (decal != decals.end)
		{
			do
			{
				if (!decal->drawable.IsValid())
				{
				remove:
					decals.Remove(decal);
					decal--;
				}
				else
				{
					if (decal->timeLeft >= 0.0f)
					{
						decal->timeLeft -= dt;
						if (decal->timeLeft < 0.0f)
						{
							decal->fade = engine::driving::gOne;
						}
					}
					if (decal->fade >= 0.0f)
					{
						decal->fade -= fadeStep;
						if (decal->fade <= 0.0f)
						{
							engine::render::Drawable::Destroy(&decal->drawable, 0);
							goto remove;
						}
						decal->drawable.SetUnknownBC(decal->fade);
					}
				}
				decal++;
			}
			while (decal != decals.end);
		}
	}
#endif

	// FUNCTION: ENGINE 0x102EED90
	void DecalBehaviour::Clear()
	{
		for (Decal* decal = decals.begin; decal != decals.end; decal++)
		{
			if (decal->drawable.IsValid())
			{
				engine::render::Drawable::Destroy(&decal->drawable, 0);
			}
		}
		decals.Clear();
	}

	// FUNCTION: ENGINE 0x102EEDE0
	// NONMATCHING: the engine's frame is four bytes larger (a local above the setup that ours does not have; best 97.5 %)
#ifdef NONMATCHING
	void DecalBehaviour::AddDecal(AddDecalMessage* message)
	{
		if (decals.Size() < maxDecals)
		{
			engine::render::AttachedEffectSetup setup;
			setup.shader = *message->effect;
			setup.unknown8 = 0;
			setup.position.x = message->position->x;
			setup.position.y = message->position->y;
			setup.position.z = message->position->z;
			setup.unknown18.x = message->direction->x;
			setup.unknown18.y = message->direction->y;
			setup.unknown18.z = message->direction->z;
			setup.unknown24.x = message->size[0];
			setup.unknown24.y = message->size[1];
			setup.owner = engine::GetHandle(owner);
			engine::render::GetEffectManager();
			setup.unknown30 = message->unknown1C;
			setup.unknown34 = message->unknown20;
			setup.unknown38 = message->unknown24;
			engine::render::Drawable drawable = engine::render::GetEffectManager()->CreateAttached(&setup);
			if (drawable.IsValid())
			{
				Decal decal = { drawable, 0.0f, choreo::gMinusOne };
				decal.timeLeft = message->lifetime;
				decals.PushBack(decal);
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x102EF000
	// EQUIVALENT: scheduling; the engine loads the one and pushes the first Listen argument between the stores of the array's words, ours stores them first (74 %)
	DecalBehaviour::DecalBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), maxDecals(0x14)
	{
		fadeTime = engine::driving::gOne;
		Listen(2, true);
		Listen(7, true);
		Listen(0x3d, true);
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x102EF080
	DecalBehaviour::~DecalBehaviour()
	{
		Clear();
	}

	// FUNCTION: ENGINE 0x102EF0C0
	void DecalBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 0x3d:
			if (message->id == 0x11)
			{
				AddDecal((AddDecalMessage*)message);
			}
			return;
		case 7:
			switch ((unsigned short)message->id)
			{
			case 3:
			case 4:
			case 5:
				Clear();
			}
			return;
		case 2:
			Clear();
		}
	}

	// FUNCTION: ENGINE 0x102EE790
	content::ClassInfo* DecalBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DecalBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102EEB10
	content::MemberList* DecalBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, DecalBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<DecalBehaviour, unsigned int, 0>("p"),
				PROTO_OFFSET(DecalBehaviour, maxDecals), "maxDecals" },
			{ content::GetMemberPrimitiveMetaType<DecalBehaviour, float, 0>("p"),
				PROTO_OFFSET(DecalBehaviour, fadeTime), "fadeTime" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102EE950
// FUNCTION: ENGINE 0x102EE960
// FUNCTION: ENGINE 0x102EE9A0
// FUNCTION: ENGINE 0x102EE9B0
// FUNCTION: ENGINE 0x102EEA90
// FUNCTION: ENGINE 0x102EEAD0
// FUNCTION: ENGINE 0x102EEFE0
// FUNCTION: ENGINE 0x102EF110

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102EEA80
