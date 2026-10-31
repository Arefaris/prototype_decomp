// engine::LightBehaviour (RTTI and reflection names; base engine::Behaviour): a light of the world. Reflected: the
// kind of light (pure3d::Light::LightType, its movement, shadow type and decay shape), the colour and the six
// spherical harmonics colours, intensity, umbra and penumbra, the shadow's settings and cascades (the PS3 values are
// kept in the data), decay and attenuation, the offset transform, the size of an area light, the flags of what it
// affects and the groups it belongs to. Unit 0x1089B580 - 0x1089FF00 (no assert path; the directory and file name are
// guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_LIGHTBEHAVIOUR_H
#define ENGINE_LIGHTBEHAVIOUR_H

#include "code/container/arrayc.h"
#include "code/container/arraydynamic.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/lightmessages.h"
#include "code/engine/message.h"
#include "code/engine/primitivemessages.h"
#include "code/engine/render/async/light.h"
#include "code/math/colour128.h"
#include "code/math/matrix.h"
#include "code/pure3d/framecontroller.h"
#include "code/pure3d/light.h"

namespace engine
{
	// How a light may move (reflected as engine::LightMovementType)
	enum LightMovementType
	{
		LIGHT_DYNAMIC_MOBILE = 0,
		LIGHT_DYNAMIC_IMMOBILE = 1,
		LIGHT_STATIC = 2
	};

	// How a light casts its shadow (reflected as pure3d::Shadow::ShadowType)
	enum LightShadowType
	{
		SHADOW_SPOT_SIMPLE = 0,
		SHADOW_SPOT_TSM = 1,
		SHADOW_DIRECTIONAL_BBOX = 2,
		SHADOW_DIRECTIONAL_TSM = 3,
		SHADOW_DIRECTIONAL_CSM = 4,
		SHADOW_SUNLIGHT_BBOX = 5,
		SHADOW_SUNLIGHT_TSM = 6,
		SHADOW_AUTOMATIC = 7
	};

	// Switches a light on or off (RTTI and reflection names; no constructor of the unit is used here)
	struct EnableLightMessage : public IntrusiveMessage
	{
		EnableLightMessage() : IntrusiveMessage(7, 0)
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		bool on;  // +0xC
	};

	// Gives a light another colour
	struct ChangeLightColourMessage : public IntrusiveMessage
	{
		ChangeLightColourMessage() : IntrusiveMessage(7, 1)
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		math::Colour128 colour;  // +0xC
	};

	// Starts a light's animation (type 0xA, id 0; the constructor is inline in the senders; names guessed)
	struct SetLightAnimationMessage : public IntrusiveMessage
	{
		pure3d::Entity* animation;  // +0xC
		float relativeSpeed;  // +0x10
		float startFrame;  // +0x14
		float rangeStart;  // +0x18
		float rangeEnd;  // +0x1C
		int cycleMode;  // +0x20
		int numCycles;  // +0x24
	};

	// Hands the light a block of user data (type 9, id 4; names guessed)
	struct SetLightUserDataMessage : public IntrusiveMessage
	{
		pure3d::LightUserData* data;  // +0xC
	};

	// The sequence player tells the behaviour which object it plays on (type 0x17, ids 4 and 6; the object at +0x18)
	struct LightSequenceMessage : public IntrusiveMessage
	{
		int unknownC;
		int unknown10;
		int unknown14;
		GameObjectHandle target;  // +0x18
	};

	class LightBehaviour : public Behaviour
	{
	public:
		// The controller that plays an animation on the light (RTTI engine::LightBehaviour::Controller; base
		// pure3d::SimpleFrameController, 0x48 bytes, two more virtual slots)
		class Controller : public pure3d::SimpleFrameController
		{
		public:
			// 0x1089BD40
			explicit Controller(LightBehaviour* newBehaviour);
			// 0x1089BD80 (deleting destructor 0x1089CB80)
			virtual ~Controller();

			// vftable slot 3 (0x1089BD90): the controller drives the behaviour, not an entity
			virtual void SetTarget(pure3d::Entity* target);
			// slot 5 (0x1089CBA0): applies the animation's values to the behaviour
			virtual void Unknown5();
			// slot 24 (0x1089BDA0): light animations only
			virtual bool IsSupported(pure3d::Animation* animation);
			// slots 25 and 26 (0x1089BD60 / 0x1089BD70)
			virtual bool Slot25();
			virtual int Slot26();

			LightBehaviour* behaviour;  // +0x40
			bool paused;  // +0x44
		};

		// 0x1089F9D0 (another unit; the second argument is the kind of light)
		explicit LightBehaviour(GameObject* newOwner, pure3d::Light::LightType newType = pure3d::Light::TYPE_AMBIENT);
		// 0x1089FF00: a behaviour with the settings of a light
		LightBehaviour(GameObject* newOwner, pure3d::Light* source);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1089C500): makes the light of the render thread
		virtual void Slot1();
		// slot 3 (0x1089BAA0)
		virtual void OnActiveChanged(bool active);
		// slot 4 (0x1089F140): sends the changes to the light
		virtual void Update(float dt, unsigned short mask);
		// slot 5 (0x1089BAC0): answers the query of the light's properties
		virtual void OnPostedMessage(Message* message);
		// slot 6 (0x1089F520)
		virtual void OnMessage(Message* message);

		// 0x1089BA30: the light has to be told about the changes
		void MarkDirty();
		// 0x1089BA50: switches the light with the behaviour's activity
		void UpdateActive(bool active);
		// 0x1089BC30: advances the animation of the light
		void AdvanceController(float dt);
		// 0x1089BCB0 / 0x1089BCD0 / 0x1089BCF0
		void ResetController();
		void SetControllerPaused(AnimationControlMessage* message);
		void UpdateListening();
		// 0x1089BDD0
		void SetShadowType(LightShadowType newShadowType);
		// 0x1089C9F0 / 0x1089CA20: the target's transform times the matrix, and the other way
		void SetTargetOffset(const math::Matrix& matrix);
		math::Matrix* GetTargetOffset(math::Matrix* result);
		// 0x1089CA70 / 0x1089CA60: the animation stops / goes on
		void ResumeController();
		void PauseController();
		// 0x1089CA80: plays a range of the animation
		void PlayAnimationRange(AnimationControlMessage* message);
		// 0x1089DD00: works the transform out of the Euler angles
		void ApplyAngles();
		// 0x1089E210: works the Euler angles out of the transform
		void UpdateAngles();
		// 0x1089E410 / 0x1089E460: makes / frees the controller
		void CreateController();
		void DestroyController();
		// 0x1089E490: starts an animation
		void SetAnimation(SetLightAnimationMessage* message);
		// 0x1089E5C0 / 0x1089E660: the sequence player starts / stops using the object
		void OnSequenceStart(LightSequenceMessage* message);
		void OnSequenceStop();

		float eulerAngleX;  // +0xC
		float eulerAngleY;  // +0x10
		float eulerAngleZ;  // +0x14
		math::Matrix appliedTransform;  // +0x18
		render::Light light;  // +0x58
		bool dirty;  // +0x5C
		pure3d::Light::LightType type;  // +0x60
		LightMovementType movement;  // +0x64
		math::Colour128 colour;  // +0x68
		math::Colour128 sphericalHarmonicColour[6];  // +0x78
		float intensity;  // +0xD8
		float ambientContribution;  // +0xDC
		float umbra;  // +0xE0
		float penumbra;  // +0xE4
		LightShadowType shadowType;  // +0xE8
		bool castShadow;  // +0xEC
		int shadowResolution;  // +0xF0
		float shadowSoftness;  // +0xF4
		float shadowOffset;  // +0xF8
		pure3d::DecayRange::DecayShape decayShape;  // +0xFC
		float decayInner;  // +0x100
		float decayOuter;  // +0x104
		float attenConstant;  // +0x108
		float attenLinear;  // +0x10C
		float attenQuadratic;  // +0x110
		bool isDynamic;  // +0x114
		bool isCheap;  // +0x115
		math::Matrix offsetTransform;  // +0x118
		float length;  // +0x158
		float width;  // +0x15C
		float height;  // +0x160
		bool useSphericalHarmonicValues;  // +0x164
		float scale;  // +0x168
		bool renderingEnabled;  // +0x16C
		bool emitSpecular;  // +0x16D
		unsigned char unknown16E[2];
		float shadowRangeMultiplier;  // +0x170
		float shadowRadiusMultiplier;  // +0x174
		float shadowMaxRadius;  // +0x178
		unsigned int affectsFlags;  // +0x17C
		unsigned int numShadowCascades;  // +0x180
		float shadowCascadeExtent[5];  // +0x184
		unsigned int numShadowCascadesPS3;  // +0x198
		float shadowCascadeExtentPS3[5];  // +0x19C
		container::ArrayC<float, 27> sphericalHarmonicValues;  // +0x1B0
		container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorNew> lightGroups;  // +0x21C
		unsigned char unknown228[4];
		float animationTime;  // +0x22C
		bool controllerPaused;  // +0x230
		GameObjectHandle sequenceTarget;  // +0x232
		math::Matrix targetTransform;  // +0x238
		math::Matrix targetInverse;  // +0x278
		Controller* controller;  // +0x2B8
	};

	// 0x1089C1B0 / 0x1089C1E0: the behaviour's reference to its controller, taken before the old one is let go; let go
	void AssignController(LightBehaviour::Controller*& slot, LightBehaviour::Controller* controller);
	void ReleaseController(LightBehaviour::Controller*& slot);
}

#endif
