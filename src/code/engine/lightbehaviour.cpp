#include "code/engine/lightbehaviour.h"
#include "code/content/arraycmetatype.h"
#include "code/content/colourmetatype.h"
#include "code/engine/attributemessage.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/mathconstants.h"
#include "code/math/vector4.h"
#include <math.h>

namespace content
{
	static const EnumValue sLightTypeValues[] =
	{
		{ "Ambient", 1 },
		{ "Directional", 2 },
		{ "Point", 3 },
		{ "Spot", 4 },
		{ "Line", 5 },
		{ "Area", 6 },
		{ "SH_Ambient", 7 }
	};

	static const EnumValue sLightMovementValues[] =
	{
		{ "Dynamic_Mobile", 0 },
		{ "Dynamic_Immobile", 1 },
		{ "Static", 2 }
	};

	static const EnumValue sDecayShapeValues[] =
	{
		{ "None", 0 },
		{ "Spherical", 1 }
	};

	static const EnumValue sShadowTypeValues[] =
	{
		{ "Automatic", 7 },
		{ "SpotSimple", 0 },
		{ "SpotTSM", 1 },
		{ "DirectionalBBox", 2 },
		{ "DirectionalTSM", 3 },
		{ "SunlightBBox", 5 },
		{ "SunlightTSM", 6 },
		{ "DirectionalCSM", 4 }
	};

	// FUNCTION: ENGINE 0x1089B8B0
	template<> void EnumInfo<pure3d::Light::LightType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "pure3d::Light::LightType";
		*code = "p";
		*values = sLightTypeValues;
		*count = 7;
	}

	// FUNCTION: ENGINE 0x1089B8E0
	template<> void EnumInfo<engine::LightMovementType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "engine::LightMovementType";
		*code = "p";
		*values = sLightMovementValues;
		*count = 3;
	}

	// FUNCTION: ENGINE 0x1089B910
	template<> void EnumInfo<pure3d::DecayRange::DecayShape>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "pure3d::DecayRange::DecayShape";
		*code = "p";
		*values = sDecayShapeValues;
		*count = 2;
	}

	// FUNCTION: ENGINE 0x1089B940
	template<> void EnumInfo<engine::LightShadowType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "pure3d::Shadow::ShadowType";
		*code = "p";
		*values = sShadowTypeValues;
		*count = 8;
	}
}

namespace engine
{
#define ENGINE_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	typedef container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorNew> NameArray;

	// FUNCTION: ENGINE 0x1089B9B0
	content::ClassInfo* EnableLightMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::EnableLightMessage";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1089B9F0
	content::ClassInfo* ChangeLightColourMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::ChangeLightColourMessage";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1089DBA0
	content::MemberList* EnableLightMessage::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<IntrusiveMessage>();
		static content::BaseClassCasterImpl<IntrusiveMessage, EnableLightMessage> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<EnableLightMessage, bool, 0>("p"),
				ENGINE_OFFSET(EnableLightMessage, on), "on" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1089DC50
	content::MemberList* ChangeLightColourMessage::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<IntrusiveMessage>();
		static content::BaseClassCasterImpl<IntrusiveMessage, ChangeLightColourMessage> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberColourMetaType<ChangeLightColourMessage, 0>("p"),
				ENGINE_OFFSET(ChangeLightColourMessage, colour), "colour" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1089B970
	content::ClassInfo* LightBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::LightBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1089E7A0
	content::MemberList* LightBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, LightBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<pure3d::Light::LightType>(),
				0x60, "type" },
			{ content::GetEnumMetaType<LightMovementType>(),
				0x64, "movement" },
			{ content::GetMemberColourMetaType<LightBehaviour, 2>("p"),
				ENGINE_OFFSET(LightBehaviour, colour), "colour" },
			{ content::GetMemberColourMetaType<LightBehaviour, 3>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[0]), "sphericalHarmonicColour0" },
			{ content::GetMemberColourMetaType<LightBehaviour, 4>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[1]), "sphericalHarmonicColour1" },
			{ content::GetMemberColourMetaType<LightBehaviour, 5>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[2]), "sphericalHarmonicColour2" },
			{ content::GetMemberColourMetaType<LightBehaviour, 6>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[3]), "sphericalHarmonicColour3" },
			{ content::GetMemberColourMetaType<LightBehaviour, 7>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[4]), "sphericalHarmonicColour4" },
			{ content::GetMemberColourMetaType<LightBehaviour, 8>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[5]), "sphericalHarmonicColour5" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 9>("p"),
				ENGINE_OFFSET(LightBehaviour, intensity), "intensity" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 10>("p"),
				ENGINE_OFFSET(LightBehaviour, ambientContribution), "ambientContribution" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 11>("p"),
				ENGINE_OFFSET(LightBehaviour, umbra), "umbra" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 12>("p"),
				ENGINE_OFFSET(LightBehaviour, penumbra), "penumbra" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 13>("p"),
				ENGINE_OFFSET(LightBehaviour, castShadow), "castShadow" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, int, 14>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowResolution), "shadowResolution" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 15>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowSoftness), "shadowSoftness" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 16>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowOffset), "shadowOffset" },
			{ content::GetEnumMetaType<pure3d::DecayRange::DecayShape>(),
				0xfc, "decayShape" },
			{ content::GetEnumMetaType<LightShadowType>(),
				0xe8, "shadowType" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 19>("p"),
				ENGINE_OFFSET(LightBehaviour, decayInner), "decayInner" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 20>("p"),
				ENGINE_OFFSET(LightBehaviour, decayOuter), "decayOuter" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 21>("p"),
				ENGINE_OFFSET(LightBehaviour, attenConstant), "attenConstant" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 22>("p"),
				ENGINE_OFFSET(LightBehaviour, attenLinear), "attenLinear" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 23>("p"),
				ENGINE_OFFSET(LightBehaviour, attenQuadratic), "attenQuadratic" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 24>("p"),
				ENGINE_OFFSET(LightBehaviour, isDynamic), "isDynamic" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 25>("p"),
				ENGINE_OFFSET(LightBehaviour, isCheap), "isCheap" },
			{ content::GetMatrixMetaType<LightBehaviour>(false, false, "p"),
				ENGINE_OFFSET(LightBehaviour, offsetTransform), "offsetTransform" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 27>("p"),
				ENGINE_OFFSET(LightBehaviour, length), "length" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 28>("p"),
				ENGINE_OFFSET(LightBehaviour, width), "width" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 29>("p"),
				ENGINE_OFFSET(LightBehaviour, height), "height" },
			{ content::GetArrayCMetaType<LightBehaviour, container::ArrayC<float, 27> >(27, 4,
					content::GetMemberPrimitiveMetaType<LightBehaviour, float, 30>("p"), "p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicValues), "sphericalHarmonicValues" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 31>("p"),
				ENGINE_OFFSET(LightBehaviour, useSphericalHarmonicValues), "useSphericalHarmonicValues" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 32>("p"),
				ENGINE_OFFSET(LightBehaviour, scale), "scale" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 33>("p"),
				ENGINE_OFFSET(LightBehaviour, renderingEnabled), "renderingEnabled" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 34>("p"),
				ENGINE_OFFSET(LightBehaviour, emitSpecular), "emitSpecular" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, unsigned int, 35>("p"),
				ENGINE_OFFSET(LightBehaviour, affectsFlags), "affectsFlags" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 36>("p"),
				ENGINE_OFFSET(LightBehaviour, eulerAngleX), "eulerAngleX" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 37>("p"),
				ENGINE_OFFSET(LightBehaviour, eulerAngleY), "eulerAngleY" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 38>("p"),
				ENGINE_OFFSET(LightBehaviour, eulerAngleZ), "eulerAngleZ" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, unsigned int, 39>("p"),
				ENGINE_OFFSET(LightBehaviour, numShadowCascades), "numShadowCascades" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 40>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[0]), "shadowCascadeExtent1" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 41>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[1]), "shadowCascadeExtent2" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 42>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[2]), "shadowCascadeExtent3" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 43>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[3]), "shadowCascadeExtent4" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 44>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[4]), "shadowCascadeExtent5" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, unsigned int, 45>("p"),
				ENGINE_OFFSET(LightBehaviour, numShadowCascadesPS3), "numShadowCascadesPS3" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 46>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[0]), "shadowCascadeExtentPS3_1" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 47>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[1]), "shadowCascadeExtentPS3_2" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 48>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[2]), "shadowCascadeExtentPS3_3" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 49>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[3]), "shadowCascadeExtentPS3_4" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 50>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[4]), "shadowCascadeExtentPS3_5" },
			{ content::GetArrayDynamicMetaType<LightBehaviour, NameArray>(
					content::GetNameMetaType<LightBehaviour>(true, true, "p"), "p"),
				ENGINE_OFFSET(LightBehaviour, lightGroups), "lightGroups" }
		};
		sList.members = sMembers;
		sList.count = 52;
		return &sList;
	}
}

namespace engine
{
	// The name of the attribute that holds the controller of the light (0x11283530; name guessed)
	extern content::ObjectName gLightControllerName;
	// The name of the transform attribute (0x11283510; gameobject.cpp)
	extern content::ObjectName gTransformName;
	// The name of the attribute "asleep" (0x112834D8; renderbehaviour.cpp)
	extern content::ObjectName gAsleepName;

	// FUNCTION: ENGINE 0x1089BA30
	void LightBehaviour::MarkDirty()
	{
		dirty = true;
		Listen2(0x200, true);
	}

	// FUNCTION: ENGINE 0x1089BA50
	void LightBehaviour::UpdateActive(bool active)
	{
		render::Light handle = light;
		if (handle.IsValid())
		{
			handle.SetActive(active && renderingEnabled);
		}
		MarkDirty();
	}

	// FUNCTION: ENGINE 0x1089BAA0
	void LightBehaviour::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
		UpdateActive(active);
	}

	// FUNCTION: ENGINE 0x1089BAC0
	// EQUIVALENT: the engine copies the three angles through the SSE registers and schedules every store of a
	// value behind the update of the change mask, ours stores first (28 %)
	void LightBehaviour::OnPostedMessage(Message* message)
	{
		if (message->type == 9 && message->id == 3)
		{
			GetLightPropertiesMessage* properties = (GetLightPropertiesMessage*)message;
			unsigned int* changed = &properties->changed;
			properties->colour = colour;
			*changed |= 2;
			properties->eulerAngleX = eulerAngleX;
			properties->eulerAngleY = eulerAngleY;
			properties->eulerAngleZ = eulerAngleZ;
			*changed |= 1;
			properties->intensity = intensity;
			*changed |= 4;
			properties->shadowRadiusMultiplier = shadowRadiusMultiplier;
			*changed |= 8;
			properties->shadowRangeMultiplier = shadowRangeMultiplier;
			*changed |= 0x10;
			properties->shadowMaxRadius = shadowMaxRadius;
			*changed |= 0x20;
			properties->shadowCaster = castShadow;
			*changed |= 0x400;
			properties->umbra = umbra;
			*changed |= 0x100;
			properties->penumbra = penumbra;
			*changed |= 0x200;
			properties->decayInner = decayInner;
			properties->decayOuter = decayOuter;
			*changed |= 0x40;
			properties->unknown44 = ambientContribution;
			*changed |= 0x80;
			properties->unknown54 = shadowType;
			*changed |= 0x800;
			properties->shadowOffset = shadowOffset;
			*changed |= 0x1000;
			properties->unknown5C = numShadowCascades;
			*changed |= 0x2000;
			properties->unknown60 = shadowCascadeExtent[0];
			*changed |= 0x4000;
			properties->unknown64 = shadowCascadeExtent[1];
			*changed |= 0x8000;
			properties->unknown68 = shadowCascadeExtent[2];
			*changed |= 0x10000;
			properties->unknown6C = shadowCascadeExtent[3];
			*changed |= 0x20000;
			properties->unknown70 = shadowCascadeExtent[4];
			*changed |= 0x40000;
		}
	}

	// FUNCTION: ENGINE 0x1089BC30
	void LightBehaviour::AdvanceController(float dt)
	{
		if (controller != 0 && !controllerPaused)
		{
			if (animationTime != 0.0f)
			{
				float elapsed = animationTime / controller->Unknown8();
				animationTime = 0.0f;
				dt = elapsed + dt;
			}
			controller->Advance(dt * 1000.0f, true);
			dirty = true;
		}
	}

	// FUNCTION: ENGINE 0x1089BCB0
	void LightBehaviour::ResetController()
	{
		if (controller != 0)
		{
			controller->Reset();
		}
	}

	// FUNCTION: ENGINE 0x1089BCD0
	void LightBehaviour::SetControllerPaused(AnimationControlMessage* message)
	{
		if (controller != 0)
		{
			controller->paused = *(bool*)&message->startFrame;
		}
	}

	// FUNCTION: ENGINE 0x1089BCF0
	void LightBehaviour::UpdateListening()
	{
		bool listen = false;
		if (controller != 0 && !controllerPaused)
		{
			listen = !controller->Unknown20();
		}
		Listen2(0x200, listen);
	}

	// FUNCTION: ENGINE 0x1089BDD0
	void LightBehaviour::SetShadowType(LightShadowType newShadowType)
	{
		shadowType = newShadowType;
		MarkDirty();
	}

	// FUNCTION: ENGINE 0x1089C500
	void LightBehaviour::Slot1()
	{
		render::Light handle = render::Light::Create(type);
		handle.SetActive(false);
		light = handle;
		dirty = true;
		for (unsigned int i = 0; i < (unsigned int)lightGroups.Size(); i++)
		{
			handle.AddToGroup(lightGroups.begin[i]);
		}
	}

	// FUNCTION: ENGINE 0x1089C1B0
	void AssignController(LightBehaviour::Controller*& slot, LightBehaviour::Controller* controller)
	{
		if (controller != 0)
		{
			controller->AddRef();
		}
		if (slot != 0)
		{
			slot->Release();
		}
		slot = controller;
	}

	// FUNCTION: ENGINE 0x1089C1E0
	void ReleaseController(LightBehaviour::Controller*& slot)
	{
		if (slot != 0)
		{
			slot->Release();
			slot = 0;
		}
	}

	// FUNCTION: ENGINE 0x1089C9F0
	void LightBehaviour::SetTargetOffset(const math::Matrix& matrix)
	{
		owner->transform->Get().Multiply(matrix, targetTransform);
	}

	// FUNCTION: ENGINE 0x1089CA60
	void LightBehaviour::ResumeController()
	{
		controllerPaused = false;
		UpdateListening();
	}

	// FUNCTION: ENGINE 0x1089CA70
	void LightBehaviour::PauseController()
	{
		controllerPaused = true;
		UpdateListening();
	}

	// FUNCTION: ENGINE 0x1089CA80
	void LightBehaviour::PlayAnimationRange(AnimationControlMessage* message)
	{
		if (controller != 0)
		{
			controller->Reset();
			float start = message->startFrame;
			float end = message->endFrame;
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
			controller->SetRelativeSpeed(message->relativeSpeed);
			controller->SetCycleMode((pure3d::Animation::CycleMode)mode);
			controller->SetNumCycles(message->numCycles);
			UpdateListening();
		}
	}

	// FUNCTION: ENGINE 0x1089E410
	// EQUIVALENT: register allocation (the engine keeps the behaviour in edi and the address of the controller in esi, ours
	// the other way round; 82.9 %)
	void LightBehaviour::CreateController()
	{
		if (controller == 0)
		{
			AssignController(controller, new Controller(this));
			Attribute<pure3d::SimpleFrameController*>* attribute =
				(Attribute<pure3d::SimpleFrameController*>*)owner->FindAttribute(gLightControllerName);
			attribute->value = controller;
		}
	}

	// FUNCTION: ENGINE 0x1089E460
	void LightBehaviour::DestroyController()
	{
		Attribute<pure3d::SimpleFrameController*>* attribute =
			(Attribute<pure3d::SimpleFrameController*>*)owner->FindAttribute(gLightControllerName);
		attribute->value = 0;
		ReleaseController(controller);
		controller = 0;
	}

	// FUNCTION: ENGINE 0x1089E490
	void LightBehaviour::SetAnimation(SetLightAnimationMessage* message)
	{
		pure3d::Entity* entity = message->animation;
		if (entity != 0)
		{
			if (controller == 0)
			{
				CreateController();
			}
			controller->SetNameFrom(entity);
			controller->SetAnimation((pure3d::Animation*)entity, 0.0f, 0.0f);
			float frame = message->startFrame;
			if (message->startFrame < message->rangeStart)
			{
				animationTime = message->startFrame - message->rangeStart;
				frame = message->rangeStart;
			}
			if (message->cycleMode == 3)
			{
				frame = message->rangeEnd;
			}
			controller->SetFrameRange(message->rangeStart, message->rangeEnd);
			controller->SetFrame(frame);
			controller->SetRelativeSpeed(message->relativeSpeed);
			controller->SetCycleMode((pure3d::Animation::CycleMode)message->cycleMode);
			controller->SetNumCycles(message->numCycles);
			controller->Unknown5();
			UpdateListening();
			return;
		}
		if (controller != 0)
		{
			DestroyController();
		}
		UpdateListening();
	}

	// FUNCTION: ENGINE 0x1089E5C0
	void LightBehaviour::OnSequenceStart(LightSequenceMessage* message)
	{
		if (!IsActive())
		{
			OnActiveChanged(true);
			SetState(1);
		}
		sequenceTarget = message->target;
		targetTransform.Identity();
		targetInverse.Identity();
		GameObject* target = sequenceTarget.Get();
		if (target != 0)
		{
			targetTransform = target->transform->value;
			targetInverse = targetTransform;
			targetInverse.Invert();
		}
	}

	// FUNCTION: ENGINE 0x1089E660
	// EQUIVALENT: the engine calls DestroyController and returns, ours jumps to it (97.8 %)
	void LightBehaviour::OnSequenceStop()
	{
		if (IsActive() && (state & 1) != 0)
		{
			ClearState(1);
			OnActiveChanged(false);
			sequenceTarget.index = 0xffff;
			sequenceTarget.serial = 0;
			targetTransform.Identity();
			targetInverse.Identity();
		}
		DestroyController();
	}

	// FUNCTION: ENGINE 0x1089F140
	void LightBehaviour::Update(float dt, unsigned short mask)
	{
		UpdateAngles();
		render::Light handle = light;
		AdvanceController(dt);
		math::Matrix transform;
		transform.Multiply(offsetTransform, owner->transform->value);
		handle.ApplyTransform(&transform);
		if (dirty)
		{
			dirty = false;
			math::Colour128 colourVector;
			if (type == pure3d::Light::TYPE_DIRECTIONAL || type == pure3d::Light::TYPE_AMBIENT)
			{
				float scale = intensity;
				colourVector = math::Colour128(colour.r * scale, colour.g * scale, colour.b * scale, 1.0f);
			}
			else
			{
				colourVector = colour;
				colourVector.a = intensity;
				if (intensity > math::EPSILON_SMALL)
				{
					float inverse = 1.0f / intensity;
					handle.ApplyUnknown194(attenConstant * inverse, attenLinear * inverse, attenQuadratic * inverse);
				}
				else
				{
					handle.ApplyUnknown194(0.0f, 0.0f, 0.0f);
				}
			}
			handle.ApplyColour((const math::Vector4*)&colourVector);
			handle.ApplyUnknown128(ambientContribution);
			handle.ApplyUnknown120(umbra);
			handle.ApplyUnknown124(penumbra);
			handle.ApplyDecay(decayShape, decayInner, decayOuter);
			handle.ApplyUnknown130(isDynamic);
			handle.ApplyUnknown17C(length);
			handle.ApplyUnknown180(width);
			handle.ApplyUnknown184(height);
			handle.ApplyUnknown188(isCheap);
			handle.ApplyUnknown107587C0(scale);
			handle.SetActive(IsActive() && renderingEnabled);
			handle.ApplyUnknown190(emitSpecular);
			handle.ApplyUnknown20C(affectsFlags);
			handle.ApplyShadowEnabled(castShadow);
			if (castShadow)
			{
				handle.ApplyUnknown164(shadowResolution);
				handle.ApplyUnknown168(shadowSoftness);
				handle.ApplyUnknown16C(shadowOffset);
				handle.ApplyShadowUnknown1074ED30(shadowType);
				handle.ApplyShadowUnknown1074ED10(shadowRadiusMultiplier);
				handle.ApplyShadowUnknown1074F0C0(shadowRangeMultiplier);
				handle.ApplyShadowUnknown1074ECE0(shadowMaxRadius);
				handle.ApplyShadowCount(numShadowCascadesPS3);
				handle.ApplyShadowCascade(0, shadowCascadeExtent[0]);
				handle.ApplyShadowCascade(1, shadowCascadeExtent[1]);
				handle.ApplyShadowCascade(2, shadowCascadeExtent[2]);
				handle.ApplyShadowCascade(3, shadowCascadeExtent[4]);
				handle.ApplyShadowCascade(4, shadowCascadeExtent[4] + 1.0f);
			}
		}
		BaseAttribute* asleep = owner->FindAttribute(gAsleepName);
		if (controller == 0 && ((asleep != 0 && static_cast<Attribute<bool>*>(asleep)->value) || movement == LIGHT_STATIC))
		{
			Listen2(0x200, false);
		}
	}

	// FUNCTION: ENGINE 0x1089F520
	// EQUIVALENT: the engine copies the five cascade extents through the SSE registers, ours through the x87 unit (76 %)
	void LightBehaviour::OnMessage(Message* message)
	{
		switch (message->type)
		{
		case 0x1a:
			if (!Query2(0x200))
			{
				Listen2(0x200, true);
				return;
			}
			break;
		case 1:
			if (static_cast<AttributeUpdatedMessage*>(message)->name == gAsleepName)
			{
				BaseAttribute* asleep = owner->FindAttribute(gAsleepName);
				if (asleep == 0 || !static_cast<Attribute<bool>*>(asleep)->value)
				{
					Listen2(0x200, true);
					return;
				}
			}
			break;
		case 9:
			switch ((unsigned short)message->id)
			{
			case 0:
				OnActiveChanged(static_cast<EnableLightMessage*>(message)->on);
				return;
			case 1:
				colour = static_cast<ChangeLightColourMessage*>(message)->colour;
				MarkDirty();
				return;
			case 4:
				{
					render::Light handle = light;
					handle.SetUserData(static_cast<SetLightUserDataMessage*>(message)->data);
					return;
				}
			case 2:
				{
					SetLightPropertiesMessage* properties = static_cast<SetLightPropertiesMessage*>(message);
					if ((properties->changed & 2) != 0)
					{
						colour = properties->colour;
					}
					if ((properties->changed & 1) != 0)
					{
						eulerAngleX = properties->eulerAngleX;
						eulerAngleY = properties->eulerAngleY;
						eulerAngleZ = properties->eulerAngleZ;
						ApplyAngles();
					}
					if ((properties->changed & 4) != 0)
					{
						intensity = properties->intensity;
					}
					if ((properties->changed & 8) != 0)
					{
						shadowRadiusMultiplier = properties->shadowRadiusMultiplier;
					}
					if ((properties->changed & 0x10) != 0)
					{
						shadowRangeMultiplier = properties->shadowRangeMultiplier;
					}
					if ((properties->changed & 0x20) != 0)
					{
						shadowMaxRadius = properties->shadowMaxRadius;
					}
					if ((properties->changed & 0x40) != 0)
					{
						decayInner = properties->decayInner;
						MarkDirty();
						decayOuter = properties->decayOuter;
						MarkDirty();
					}
					if ((properties->changed & 0x80) != 0)
					{
						ambientContribution = properties->unknown44;
						MarkDirty();
					}
					if ((properties->changed & 0x100) != 0)
					{
						umbra = properties->umbra;
						MarkDirty();
					}
					if ((properties->changed & 0x200) != 0)
					{
						penumbra = properties->penumbra;
						MarkDirty();
					}
					if ((properties->changed & 0x400) != 0)
					{
						castShadow = properties->shadowCaster;
						MarkDirty();
					}
					if ((properties->changed & 0x800) != 0)
					{
						SetShadowType((LightShadowType)properties->unknown54);
					}
					if ((properties->changed & 0x1000) != 0)
					{
						shadowOffset = properties->shadowOffset;
						MarkDirty();
					}
					if ((properties->changed & 0x2000) != 0)
					{
						numShadowCascades = properties->unknown5C;
					}
					if ((properties->changed & 0x4000) != 0)
					{
						shadowCascadeExtent[0] = properties->unknown60;
					}
					if ((properties->changed & 0x8000) != 0)
					{
						shadowCascadeExtent[1] = properties->unknown64;
					}
					if ((properties->changed & 0x10000) != 0)
					{
						shadowCascadeExtent[2] = properties->unknown68;
					}
					if ((properties->changed & 0x20000) != 0)
					{
						shadowCascadeExtent[3] = properties->unknown6C;
					}
					if ((properties->changed & 0x40000) != 0)
					{
						shadowCascadeExtent[4] = properties->unknown70;
					}
					MarkDirty();
					return;
				}
			}
			break;
		case 2:
			ResetController();
			return;
		case 10:
			switch ((unsigned short)message->id)
			{
			case 2:
				ResumeController();
				return;
			case 3:
				PauseController();
				return;
			case 0:
				SetAnimation(static_cast<SetLightAnimationMessage*>(message));
				return;
			case 1:
				PlayAnimationRange(static_cast<AnimationControlMessage*>(message));
				return;
			case 10:
				SetControllerPaused(static_cast<AnimationControlMessage*>(message));
				return;
			}
			break;
		case 0x17:
			if (message->id == 4)
			{
				OnSequenceStart(static_cast<LightSequenceMessage*>(message));
			}
			else if (message->id == 6)
			{
				OnSequenceStop();
				return;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x1089DD00
	// NONMATCHING: the engine interleaves the four copies of the identity with the rotations and keeps the identity's elements
	// in registers, best 25 %
#ifdef NONMATCHING
	void LightBehaviour::ApplyAngles()
	{
		math::Matrix& current = owner->transform->Get();
		math::Vector translation(current.m[3][0], current.m[3][1], current.m[3][2]);
		math::Matrix rotation(math::Matrix::IDENTITY);
		math::Matrix rotationZ(math::Matrix::IDENTITY);
		rotationZ.RotationZ(eulerAngleZ);
		math::Matrix rotationY(math::Matrix::IDENTITY);
		rotationY.RotationY(eulerAngleY);
		math::Matrix rotationX(math::Matrix::IDENTITY);
		rotationX.RotationX(eulerAngleX);
		rotation = rotationX;
		rotation.Multiply(rotation, rotationY);
		rotation.Multiply(rotation, rotationZ);
		rotation.SetTranslation(translation);
		if (owner->transform == 0)
		{
			owner->transform = static_cast<Attribute<math::Matrix>*>(owner->FindAttribute(gTransformName));
		}
		owner->transform->Get() = rotation;
		appliedTransform = rotation;
		appliedTransform.SetTranslation(math::Vector(0.0f, 0.0f, 0.0f));
		MarkDirty();
	}
#endif

	// FUNCTION: ENGINE 0x1089E210
	// EQUIVALENT: scheduling (the engine stores the last angle behind the preparation of the matrix copy's arguments; 97 %)
	void LightBehaviour::UpdateAngles()
	{
		math::Matrix matrix(math::Matrix::IDENTITY);
		if (owner->FindAttribute(gTransformName) != 0)
		{
			BaseAttribute* attribute = owner->FindAttribute(gTransformName);
			math::Matrix* value = attribute != 0 ? &static_cast<Attribute<math::Matrix>*>(attribute)->value : 0;
			matrix = *value;
		}
		matrix.SetTranslation(math::Vector(0.0f, 0.0f, 0.0f));
		if (!(appliedTransform == matrix))
		{
			eulerAngleX = atan2f(matrix.m[1][2], matrix.m[2][2]);
			eulerAngleY = atan2f(-matrix.m[0][2], sqrtf(matrix.m[0][1] * matrix.m[0][1] + matrix.m[0][0] * matrix.m[0][0]));
			eulerAngleZ = atan2f(matrix.m[0][1], matrix.m[0][0]);
			if (!(3.14159274f > eulerAngleX))
			{
				eulerAngleX -= 6.28318548f;
			}
			if (!(3.14159274f > eulerAngleY))
			{
				eulerAngleY -= 6.28318548f;
			}
			if (!(3.14159274f > eulerAngleZ))
			{
				eulerAngleZ -= 6.28318548f;
			}
			appliedTransform = matrix;
		}
	}

	// FUNCTION: ENGINE 0x1089BD40
	LightBehaviour::Controller::Controller(LightBehaviour* newBehaviour)
	{
		behaviour = newBehaviour;
		paused = false;
	}

	// FUNCTION: ENGINE 0x1089BD80
	LightBehaviour::Controller::~Controller()
	{
	}

	// FUNCTION: ENGINE 0x1089BD90
	void LightBehaviour::Controller::SetTarget(pure3d::Entity* target)
	{
	}

	// FUNCTION: ENGINE 0x1089BDA0
	bool LightBehaviour::Controller::IsSupported(pure3d::Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0)
		{
			return animation->mType == 0x4554494C;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1089BD60
	bool LightBehaviour::Controller::Slot25()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x1089BD70
	int LightBehaviour::Controller::Slot26()
	{
		return 0;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1089BE00
// FUNCTION: ENGINE 0x1089BE20
// FUNCTION: ENGINE 0x1089BE80
// FUNCTION: ENGINE 0x1089BEE0
// FUNCTION: ENGINE 0x1089BFA0
// FUNCTION: ENGINE 0x1089BFD0
// FUNCTION: ENGINE 0x1089C000
// FUNCTION: ENGINE 0x1089C030
// FUNCTION: ENGINE 0x1089C060
// FUNCTION: ENGINE 0x1089C090
// FUNCTION: ENGINE 0x1089C0C0
// FUNCTION: ENGINE 0x1089C0F0
// FUNCTION: ENGINE 0x1089C130
// FUNCTION: ENGINE 0x1089C140
// FUNCTION: ENGINE 0x1089C180
// FUNCTION: ENGINE 0x1089C440
// FUNCTION: ENGINE 0x1089C450
// FUNCTION: ENGINE 0x1089C480
// FUNCTION: ENGINE 0x1089C490
// FUNCTION: ENGINE 0x1089C4C0
// FUNCTION: ENGINE 0x1089C4D0
// FUNCTION: ENGINE 0x1089D0C0
// FUNCTION: ENGINE 0x1089D100
// FUNCTION: ENGINE 0x1089D140
// FUNCTION: ENGINE 0x1089D180
// FUNCTION: ENGINE 0x1089D1C0
// FUNCTION: ENGINE 0x1089D200
// FUNCTION: ENGINE 0x1089D240
// FUNCTION: ENGINE 0x1089D280
// FUNCTION: ENGINE 0x1089D2C0
// FUNCTION: ENGINE 0x1089D300
// FUNCTION: ENGINE 0x1089D340
// FUNCTION: ENGINE 0x1089D380
// FUNCTION: ENGINE 0x1089D3C0
// FUNCTION: ENGINE 0x1089D400
// FUNCTION: ENGINE 0x1089D440
// FUNCTION: ENGINE 0x1089D480
// FUNCTION: ENGINE 0x1089D4C0
// FUNCTION: ENGINE 0x1089D500
// FUNCTION: ENGINE 0x1089D540
// FUNCTION: ENGINE 0x1089D580
// FUNCTION: ENGINE 0x1089D5C0
// FUNCTION: ENGINE 0x1089D600
// FUNCTION: ENGINE 0x1089D640
// FUNCTION: ENGINE 0x1089D680
// FUNCTION: ENGINE 0x1089D6C0
// FUNCTION: ENGINE 0x1089D700
// FUNCTION: ENGINE 0x1089D740
// FUNCTION: ENGINE 0x1089D780
// FUNCTION: ENGINE 0x1089D7C0
// FUNCTION: ENGINE 0x1089D800
// FUNCTION: ENGINE 0x1089D840
// FUNCTION: ENGINE 0x1089D880
// FUNCTION: ENGINE 0x1089D8C0
// FUNCTION: ENGINE 0x1089D900
// FUNCTION: ENGINE 0x1089D940
// FUNCTION: ENGINE 0x1089D980
// FUNCTION: ENGINE 0x1089D9C0
// FUNCTION: ENGINE 0x1089DA00
// FUNCTION: ENGINE 0x1089DA40
// FUNCTION: ENGINE 0x1089DA80
// FUNCTION: ENGINE 0x1089DB00
// FUNCTION: ENGINE 0x1089DB10
// FUNCTION: ENGINE 0x1089DB20
// FUNCTION: ENGINE 0x1089E6C0
// FUNCTION: ENGINE 0x1089E710
