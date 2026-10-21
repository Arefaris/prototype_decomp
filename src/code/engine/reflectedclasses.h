// The reflected classes of other units that the engine's factories (metafactories.cpp) construct. Their layouts are
// not recovered: a class is its size (a LoadObject with unknown content, or a plain block), its constructor and the
// two functions of its reflection, all of them in the units of the classes. Replace an entry by the real class when
// its unit is reconstructed.
#ifndef ENGINE_REFLECTEDCLASSES_H
#define ENGINE_REFLECTEDCLASSES_H

#include "code/content/loadinventory.h"
#include "code/engine/gameobject/behaviour.h"

	// SurfaceDefinition: constructor 0x109117B0, reflection 0x10911500 / 0x10911670
	class SurfaceDefinition : public content::MetaLoadObject
	{
	public:
		SurfaceDefinition();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x328];
	};


namespace engine
{
	// ActorSpawner: constructor 0x10905DE0, reflection 0x10905BC0 / 0x10905FE0
	class ActorSpawner : public content::MetaLoadObject
	{
	public:
		ActorSpawner();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x58];
	};

	// ActorCrowdSpawner: constructor 0x109066D0, reflection 0x10905C00 / 0x109060B0
	class ActorCrowdSpawner : public content::MetaLoadObject
	{
	public:
		ActorCrowdSpawner();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0xC8];
	};

	// CharacterIntentionInputMap: constructor 0x108253C0, reflection 0x10821940 / 0x10824380
	class CharacterIntentionInputMap : public content::MetaLoadObject
	{
	public:
		CharacterIntentionInputMap();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x68];
	};

	// CharacterSolverProperties: constructor 0x109084D0, reflection 0x10907E90 / 0x109097A0
	struct CharacterSolverProperties : public content::MetaLoadObject
	{
	public:
		CharacterSolverProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x1C];
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

	// NamedInventoryCreator: constructor 0x1090D9B0, reflection 0x1090D720 / 0x1090D900
	class NamedInventoryCreator : public content::MetaLoadObject
	{
	public:
		NamedInventoryCreator();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x10];
	};

	// RemoteCamera: constructor 0x1090DD30, reflection 0x1090DA00 / 0x1090DBD0
	class RemoteCamera : public content::MetaLoadObject
	{
	public:
		RemoteCamera();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x34];
	};

	// SecondaryPhysicsProperties: constructor 0x109103D0, reflection 0x1090DF10 / 0x1090FDD0
	class SecondaryPhysicsProperties : public content::MetaLoadObject
	{
	public:
		SecondaryPhysicsProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x14];
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

	// TrackedMotionToExpressionMap: constructor 0x109146F0, reflection 0x10911970 / 0x109138D0
	class TrackedMotionToExpressionMap : public content::MetaLoadObject
	{
	public:
		TrackedMotionToExpressionMap();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x18];
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

	// SecondaryPhysicsAmbientWind: constructor 0x109161C0, reflection 0x10915FD0 / 0x10916290
	class SecondaryPhysicsAmbientWind
	{
	public:
		SecondaryPhysicsAmbientWind();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[0x14];
	};

	// SecondaryPhysicsPinJoint: constructor 0x10916400, reflection 0x10916360 / 0x109166E0
	class SecondaryPhysicsPinJoint
	{
	public:
		SecondaryPhysicsPinJoint();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[0x10];
	};

	// SecondaryPhysicsPoweredJoint: constructor 0x10917900, reflection 0x109167D0 / 0x10917770
	class SecondaryPhysicsPoweredJoint
	{
	public:
		SecondaryPhysicsPoweredJoint();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[0x1C];
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

	// CharacterIntentionBehaviour: constructor 0x1091CBC0, reflection 0x1091C500 / 0x1091CA80
	class CharacterIntentionBehaviour : public engine::Behaviour
	{
	public:
		CharacterIntentionBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x7C];
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

	// FirstPersonControlBehaviour: constructor 0x1091EBD0, reflection 0x1091DF60 / 0x1091E210
	class FirstPersonControlBehaviour : public engine::Behaviour
	{
	public:
		FirstPersonControlBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x28];
	};

	// KnockBehaviour: constructor 0x1091ECB0, reflection 0x1091EC70 / 0x1091F230
	class KnockBehaviour : public engine::Behaviour
	{
	public:
		KnockBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x18];
	};

	// MotionTreeBehaviour: constructor 0x1091F480, reflection 0x1091F380 / 0x1091F750
	class MotionTreeBehaviour : public engine::Behaviour
	{
	public:
		MotionTreeBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x64];
	};

	// NISPlayerBehaviour: constructor 0x1091FA50, reflection 0x1091F890 / 0x1091FEA0
	class NISPlayerBehaviour : public engine::Behaviour
	{
	public:
		NISPlayerBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x74];
	};

	// PatrolPathBehaviour: constructor 0x10867600, reflection 0x10864CB0 / 0x10866C40
	class PatrolPathBehaviour : public engine::Behaviour
	{
	public:
		PatrolPathBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x5C];
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

	// PropLogicTreeBehaviour: constructor 0x109214F0, reflection 0x10921440 / 0x109215C0
	class PropLogicTreeBehaviour : public engine::Behaviour
	{
	public:
		PropLogicTreeBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x5C];
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

	// PropBehaviour: constructor 0x108414B0, reflection 0x10841060 / 0x10841200
	class PropBehaviour : public engine::Behaviour
	{
	public:
		PropBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x0];
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

	// RenderBehaviour: constructor 0x108636B0, reflection 0x10862350 / 0x10862F60
	class RenderBehaviour : public engine::Behaviour
	{
	public:
		RenderBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x34];
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

	// SplineBehaviour: constructor 0x10867760, reflection 0x10864D40 / 0x10866D20
	class SplineBehaviour : public engine::Behaviour
	{
	public:
		SplineBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x64];
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

	// JawFlapBehaviour: constructor 0x1091A290, reflection 0x10919F50 / 0x1091AEB0
	class JawFlapBehaviour : public engine::Behaviour
	{
	public:
		JawFlapBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x3C];
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
	// FPSCamera: constructor 0x10915490, reflection 0x10915450 / 0x10915540
	class FPSCamera
	{
	public:
		FPSCamera();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[0x48];
	};

	// OnFootCamera: constructor 0x10915860, reflection 0x109157E0 / 0x10915A50
	class OnFootCamera
	{
	public:
		OnFootCamera();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[0x80];
	};

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
	// CarPhysicsAttributes: constructor 0x10906E20, reflection 0x10906C40 / 0x10906D80
	class CarPhysicsAttributes : public content::MetaLoadObject
	{
	public:
		CarPhysicsAttributes();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x210];
	};

	// HelicopterPhysicsAttributes: constructor 0x10906FC0, reflection 0x10906E90 / 0x10906F40
	class HelicopterPhysicsAttributes : public content::MetaLoadObject
	{
	public:
		HelicopterPhysicsAttributes();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x64];
	};

	// VehiclePhysicsAttributes: constructor 0x10905B60, reflection 0x10905A00 / 0x10905AE0
	class VehiclePhysicsAttributes : public content::MetaLoadObject
	{
	public:
		VehiclePhysicsAttributes();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x1C];
	};

	// WheelCollectionData: constructor 0x10907B60, reflection 0x10907020 / 0x109075A0
	class WheelCollectionData : public content::MetaLoadObject
	{
	public:
		WheelCollectionData();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x18];
	};

	// CarIntentionBehaviour: constructor 0x1091CEA0, reflection 0x1091CD30 / 0x1091CF50
	class CarIntentionBehaviour : public engine::Behaviour
	{
	public:
		CarIntentionBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x14];
	};

	// CarPhysicsBehaviour: constructor 0x1091D920, reflection 0x1091D020 / 0x1091D7B0
	class CarPhysicsBehaviour : public engine::Behaviour
	{
	public:
		CarPhysicsBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x108];
	};

	// HelicopterIntentionBehaviour: constructor 0x1091DAC0, reflection 0x1091D980 / 0x1091DB70
	class HelicopterIntentionBehaviour : public engine::Behaviour
	{
	public:
		HelicopterIntentionBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x14];
	};

	// HelicopterPhysicsBehaviour: constructor 0x1091DC40, reflection 0x1091DC00 / 0x1091DEA0
	class HelicopterPhysicsBehaviour : public engine::Behaviour
	{
	public:
		HelicopterPhysicsBehaviour(engine::GameObject* owner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0xF8];
	};

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

	// LocationRenderSettings: constructor 0x10914A70, reflection 0x10914850 / 0x109149C0
	class LocationRenderSettings : public content::MetaLoadObject
	{
	public:
		LocationRenderSettings();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x8];
	};

}
}

namespace ravenphysics
{
	// ConstraintAngularSpringSharedProperties: constructor 0x1066B980, reflection 0x1066B6E0 / 0x1066BB70
	class ConstraintAngularSpringSharedProperties : public content::MetaLoadObject
	{
	public:
		ConstraintAngularSpringSharedProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x8];
	};

	// ConstraintAngularVelocitySharedProperties: constructor 0x1066C060, reflection 0x1066BDF0 / 0x1066C250
	class ConstraintAngularVelocitySharedProperties : public content::MetaLoadObject
	{
	public:
		ConstraintAngularVelocitySharedProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x8];
	};

	// ConstraintListFactory: constructor 0x106A6CE0, reflection 0x106A56F0 / 0x106A6B70
	class ConstraintListFactory : public content::MetaLoadObject
	{
	public:
		ConstraintListFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x10];
	};

	// ConstraintSpringAlongAxisSharedProperties: constructor 0x10670050, reflection 0x1066FCD0 / 0x10670470
	class ConstraintSpringAlongAxisSharedProperties : public content::MetaLoadObject
	{
	public:
		ConstraintSpringAlongAxisSharedProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0xC];
	};

	// DeformableOrientationConstraintSharedProperties: constructor 0x10692DF0, reflection 0x10692C50 / 0x10693060
	class DeformableOrientationConstraintSharedProperties : public content::MetaLoadObject
	{
	public:
		DeformableOrientationConstraintSharedProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x8];
	};

	// DeformableSliderConstraintSharedProperties: constructor 0x10692590, reflection 0x10692180 / 0x10692930
	class DeformableSliderConstraintSharedProperties : public content::MetaLoadObject
	{
	public:
		DeformableSliderConstraintSharedProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x10];
	};

	// IntersectionPropertiesLoader: constructor 0x10654020, reflection 0x10653640 / 0x10653CC0
	class IntersectionPropertiesLoader : public content::MetaLoadObject
	{
	public:
		IntersectionPropertiesLoader();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x40];
	};

	// MassProperties: constructor 0x10670E90, reflection 0x10670C40 / 0x10671030
	class MassProperties : public content::MetaLoadObject
	{
	public:
		MassProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x38];
	};

	// MaterialLoader: constructor 0x1066A890, reflection 0x1066A2A0 / 0x1066A740
	class MaterialLoader : public content::MetaLoadObject
	{
	public:
		MaterialLoader();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x28];
	};

	// PoweredConstraintSharedProperties: constructor 0x10693B90, reflection 0x106939E0 / 0x10693D40
	class PoweredConstraintSharedProperties : public content::MetaLoadObject
	{
	public:
		PoweredConstraintSharedProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x8];
	};

	// SimplePhysicsObjectFactory: constructor 0x1066DF60, reflection 0x1066C720 / 0x1066E7B0
	class SimplePhysicsObjectFactory : public content::MetaLoadObject
	{
	public:
		SimplePhysicsObjectFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x18];
	};

}

#endif
