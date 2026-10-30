// The reflected classes of other units that the engine's factories (metafactories.cpp) construct. Their layouts are
// not recovered: a class is its size (a LoadObject with unknown content, or a plain block), its constructor and the
// two functions of its reflection, all of them in the units of the classes. Replace an entry by the real class when
// its unit is reconstructed.
#ifndef ENGINE_REFLECTEDCLASSES_H
#define ENGINE_REFLECTEDCLASSES_H

#include "code/content/loadinventory.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/render/renderbehaviour.h"
#include "code/ravenphysics/constraints/sharedproperties.h"
#include "code/ravenphysics/material.h"
#include "code/ravenphysics/constraintlistfactory.h"
#include "code/ravenphysics/context.h"
#include "code/ravenphysics/physicsobjectfactory.h"

namespace engine
{
	// CharacterIntentionInputMap: constructor 0x108253C0, reflection 0x10821940 / 0x10824380
	class CharacterIntentionInputMap : public content::MetaLoadObject
	{
	public:
		CharacterIntentionInputMap();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x68];
	};

	// GameObjectTemplateBuilder: constructor 0x1090CE10, reflection 0x1090C110 / 0x1090CC30
	class GameObjectTemplateBuilder : public content::MetaLoadObject
	{
	public:
		GameObjectTemplateBuilder();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x30];
	};

	// SkuInfo: constructor 0x10892E60, reflection 0x10892630 / 0x10892CE0
	class SkuInfo : public content::MetaLoadObject
	{
	public:
		SkuInfo();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x38];
	};

	// StreamPackage: constructor 0x107FBDC0, reflection 0x107FAD80 / 0x107FBAC0
	class StreamPackage : public content::MetaLoadObject
	{
	public:
		StreamPackage();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x58];
	};

	// StreamSlotGroup: constructor 0x1083F5E0, reflection 0x1083E7E0 / 0x1083F310
	class StreamSlotGroup : public content::MetaLoadObject
	{
	public:
		StreamSlotGroup();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x68];
	};

	// StreamTrigger: constructor 0x108363D0, reflection 0x108352B0 / 0x10835CE0
	class StreamTrigger : public content::MetaLoadObject
	{
	public:
		StreamTrigger();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x58];
	};

	// SupportingLimbDefinition: constructor 0x107F53F0, reflection 0x107F2A20 / 0x107F4B70
	class SupportingLimbDefinition : public content::MetaLoadObject
	{
	public:
		SupportingLimbDefinition();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x88];
	};

	// SupportingLimbDefinitionList: constructor 0x107F4FD0, reflection 0x107F2A60 / 0x107F48C0
	struct SupportingLimbDefinitionList : public content::MetaLoadObject
	{
	public:
		SupportingLimbDefinitionList();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x10];
	};

	// NISExclusionVolume: constructor 0x108DB770, reflection 0x1088B8A0 / 0x1088C180
	struct NISExclusionVolume : public content::MetaLoadObject
	{
	public:
		NISExclusionVolume();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x3C];
	};

	// AdvertisementBehaviour: constructor 0x10919D70, reflection 0x10917A30 / 0x109197C0
	class AdvertisementBehaviour : public engine::Behaviour
	{
	public:
		AdvertisementBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x1C];
	};

	// CharacterSolverBehaviour: constructor 0x1090AFF0, reflection 0x10907ED0 / 0x1090AA30
	class CharacterSolverBehaviour : public engine::Behaviour
	{
	public:
		CharacterSolverBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0xF4];
	};

	// PlaybackTreeBehaviour: constructor 0x1089AC70, reflection 0x1089AA30 / 0x1089AE60
	class PlaybackTreeBehaviour : public engine::Behaviour
	{
	public:
		PlaybackTreeBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x7C];
	};

	// PoseAnimationBehaviour: constructor 0x10921260, reflection 0x109208B0 / 0x10920AF0
	class PoseAnimationBehaviour : public engine::Behaviour
	{
	public:
		PoseAnimationBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x10];
	};

	// PhysicsBehaviour: constructor 0x10924520, reflection 0x10921A10 / 0x109239B0
	class PhysicsBehaviour : public engine::Behaviour
	{
	public:
		PhysicsBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x5C];
	};

	// RagdollBehaviour: constructor 0x10927BA0, reflection 0x10925050 / 0x10927330
	class RagdollBehaviour : public engine::Behaviour
	{
	public:
		RagdollBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x88];
	};

	// RagdollLODBehaviour: constructor 0x10926350, reflection 0x10925090 / 0x109274D0
	class RagdollLODBehaviour : public engine::Behaviour
	{
	public:
		RagdollLODBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x14];
	};

	// SecondaryPhysicsBehaviour: constructor 0x10929460, reflection 0x10927F60 / 0x10928F80
	class SecondaryPhysicsBehaviour : public engine::Behaviour
	{
	public:
		SecondaryPhysicsBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x34];
	};

	// TagBehaviour: constructor 0x10929EE0, reflection 0x109296D0 / 0x10929BB0
	class TagBehaviour : public engine::Behaviour
	{
	public:
		TagBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x10];
	};

	// TouchBehaviour: constructor 0x1092A030, reflection 0x10929FF0 / 0x1092A370
	class TouchBehaviour : public engine::Behaviour
	{
	public:
		TouchBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x4];
	};

	// TrackedMotionToExpressionBehaviour: constructor 0x1092AF30, reflection 0x1092A440 / 0x1092AA40
	class TrackedMotionToExpressionBehaviour : public engine::Behaviour
	{
	public:
		TrackedMotionToExpressionBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x30];
	};

}

namespace engine
{
namespace animation
{
	// AttachmentPhysicsProperties: constructor 0x1083BF90, reflection 0x1083BB60 / 0x1083C840
	struct AttachmentPhysicsProperties : public content::MetaLoadObject
	{
	public:
		AttachmentPhysicsProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x14];
	};

	// PuppetBehaviour: constructor 0x1091C400, reflection 0x1091B180 / 0x1091BF20
	class PuppetBehaviour : public engine::Behaviour
	{
	public:
		PuppetBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x34];
	};

}
}

namespace engine
{
namespace camera
{
	// ScriptedCamera: constructor 0x10851480, reflection 0x108509B0 / 0x10851420
	class ScriptedCamera
	{
	public:
		ScriptedCamera();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[0x188];
	};

	// CameraBehaviour: constructor 0x108508D0, reflection 0x108504A0 / 0x10850820
	class CameraBehaviour : public engine::Behaviour
	{
	public:
		CameraBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x4];
	};

	// CinematographerBehaviour: constructor 0x10850430, reflection 0x1084FFF0 / 0x10850360
	class CinematographerBehaviour : public engine::Behaviour
	{
	public:
		CinematographerBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x8];
	};

}
}

namespace engine
{
namespace driving
{
}
}

namespace engine
{
namespace trigger
{
	// OBBVolume: constructor 0x10841D90, reflection 0x108415D0 / 0x10841EE0
	class OBBVolume
	{
	public:
		OBBVolume();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[0x50];
	};

	// SphereVolume: constructor 0x10841CD0, reflection 0x10841590 / 0x10841E40
	class SphereVolume
	{
	public:
		SphereVolume();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[0x24];
	};

}
}

namespace engine
{
namespace world
{
	// Location: constructor 0x108D6580, reflection 0x108D5F50 / 0x108D64A0
	class Location : public content::MetaLoadObject
	{
	public:
		Location();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x3C];
	};

}
}

#endif
