// The reflected classes of other units that the engine's factories (metafactories.cpp) construct. Their layouts are
// not recovered: a class is its size (a LoadObject with unknown content, or a plain block), its constructor and the
// two functions of its reflection, all of them in the units of the classes. Replace an entry by the real class when
// its unit is reconstructed.
#ifndef ENGINE_REFLECTEDCLASSES_H
#define ENGINE_REFLECTEDCLASSES_H

#include "code/content/loadinventory.h"
#include "code/math/obb.h"
#include "code/engine/world/location.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/render/renderbehaviour.h"
#include "code/engine/advertisementbehaviour.h"
#include "code/engine/gameobjecttemplatebuilder.h"
#include "code/engine/physicsbehaviour.h"
#include "code/engine/poseanimationbehaviour.h"
#include "code/engine/ragdolllodbehaviour.h"
#include "code/engine/secondaryphysicsproperties.h"
#include "code/engine/trackedmotiontoexpressionmap.h"
#include "code/engine/tagbehaviour.h"
#include "code/engine/touchbehaviour.h"
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

		math::OBB obb;  // +8
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

	// RagdollBehaviour: constructor 0x10927BA0, reflection 0x10925050 / 0x10927330
	class RagdollBehaviour : public engine::Behaviour
	{
	public:
		RagdollBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[8];
		ravenphysics::PhysicsObjectFactory* ragdollFactory;  // +0x14
		ravenphysics::PhysicsObjectFactory* lowLODRagdollFactory;  // +0x18
		ravenphysics::PhysicsObjectFactory* ragdoll;  // +0x1C
		unsigned char unknown20[0x18];
		ravenphysics::IntersectionPropertiesLoader* intersectionProperties;  // +0x38
		unsigned char unknown3C[0x40];
		bool createRagdollPhysicsObject;  // +0x7C
		bool isKeyframeUpdated;  // +0x7D
		ravenphysics::MaterialLoader* overrideMaterial;  // +0x80
		unsigned char unknown84[0x10];
	};

	// SecondaryPhysicsBehaviour: constructor 0x10929460, reflection 0x10927F60 / 0x10928F80
	class SecondaryPhysicsBehaviour : public engine::Behaviour
	{
	public:
		SecondaryPhysicsBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x28];
		SecondaryPhysicsProperties* sharedProperties;  // +0x34
		int unknown38;
		bool sendPoseSyncMessage;  // +0x3C
	};

	// TrackedMotionToExpressionBehaviour: constructor 0x1092AF30, reflection 0x1092A440 / 0x1092AA40
	class TrackedMotionToExpressionBehaviour : public engine::Behaviour
	{
	public:
		TrackedMotionToExpressionBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		TrackedMotionToExpressionMap* map;  // +0xC
		unsigned char unknown10[0x2C];
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

#endif
