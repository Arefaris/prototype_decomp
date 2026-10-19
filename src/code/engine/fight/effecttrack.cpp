// The effect track of the fight tree and the accessors of the effect it plays (see effecttrack.h).
#include "code/engine/fight/effecttrack.h"

namespace engine
{
	GameObject* __fastcall GameObjectHandleGet(const GameObjectHandle* handle);

	// ---- the game's hook ---------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x108056E0
	EffectTrackCheck GetEffectTrackCheck()
	{
		return gEffectTrackCheck;
	}

	// FUNCTION: ENGINE 0x108056F0
	int GetEffectTrackCheckContext()
	{
		return gEffectTrackCheckContext;
	}

	// FUNCTION: ENGINE 0x10805700
	void SetEffectTrackCheck(EffectTrackCheck check, int context)
	{
		gEffectTrackCheck = check;
		gEffectTrackCheckContext = context;
	}

	// FUNCTION: ENGINE 0x10805720
	void SetEffectSuspendCount(int count)
	{
		gEffectSuspendSaved = count;
		gEffectSuspendCount = count;
	}

	// FUNCTION: ENGINE 0x10805730
	void RestoreEffectSuspendCount()
	{
		gEffectSuspendCount = gEffectSuspendSaved;
	}

	// FUNCTION: ENGINE 0x10805740
	void LeaveEffectSuspend()
	{
		gEffectSuspendCount--;
	}

	// ---- the spawn matrix --------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x10805750
	// NONMATCHING: register allocation and scheduling of the head: the engine keeps the 1.0f constant in xmm3 from the
	// function's first instruction (the static's own y component) and loads the direction's components z, x, y where
	// ours loads x, z, y and reloads 1.0f twice; the tail from the comparison on is the engine's (23.6 %)
#ifdef NONMATCHING
	void EffectSpawnTransform::BuildMatrix(const math::Matrix& parent, math::Matrix& matrix) const
	{
		// The world up axis, built on the first call
		static math::Vector sUp(0.0f, 1.0f, 0.0f);
		math::Vector direction(parent.m[1][0], parent.m[1][1], parent.m[1][2]);
		if (1.0f - direction.Dot(sUp) > 0.01f)
		{
			math::Vector side;
			side.Cross(direction, sUp);
			matrix.Identity();
			matrix.SetTranslation(math::Vector(parent.m[3][0], parent.m[3][1], parent.m[3][2]));
			matrix.SetBasis(side, sUp);
		}
		else
		{
			// The effect already points along the up axis: the parent's frame is the spawn frame
			matrix = parent;
		}
	}
#endif

	// ---- the engine's copies of core's reference helpers ---------------------------------------------------------

	// FUNCTION: ENGINE 0x108058E0
	void AssignEffectRef(core::IRefCount*& pointer, core::IRefCount* object)
	{
		if (object != 0)
		{
			object->AddRef();
		}
		if (pointer != 0)
		{
			pointer->Release();
		}
		pointer = object;
	}

	// FUNCTION: ENGINE 0x10805910
	void ReleaseEffectRef(core::IRefCount*& object)
	{
		if (object != 0)
		{
			object->Release();
			object = 0;
		}
	}

	// ---- the actions that carry the effect ---------------------------------------------------------------------

	// FUNCTION: ENGINE 0x108075F0
	EffectAction::EffectAction(EffectTrack* newTrack, fight::Track* listener, GameObjectHandle newTarget, core::IRefCount* effect, int mode)
		: fight::Action(0xE00), link(newTrack), watch(listener), unknown34(mode), unknown3c(0), target(newTarget),
		  unknown44(0), unknown48(0xffff), unknown4c(false)
	{
		AssignEffectRef(unknown44, effect);
	}

	// FUNCTION: ENGINE 0x10807550
	AbortEffectAction::AbortEffectAction(AbortEffectTrack* newTrack, fight::Track* listener)
		: fight::Action(0xE00), link(newTrack)
	{
		(void)listener;
	}

	// FUNCTION: ENGINE 0x10807700
	MotionTrailAction::MotionTrailAction(MotionTrailTrack* newTrack, fight::Track* listener, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), watch(listener), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x10805B10
	AbortEffectAction::~AbortEffectAction()
	{
	}

	// FUNCTION: ENGINE 0x10805B40
	// NONMATCHING: the +0x3C reference is released through another unit's copy of the release helper (0x104FF200),
	// ours calls ReleaseEffectRef for both members (same bytes, wrong call target)
#ifdef NONMATCHING
	EffectAction::~EffectAction()
	{
		ReleaseEffectRef(unknown44);
		ReleaseEffectRef(unknown3c);
	}
#endif

	// FUNCTION: ENGINE 0x10805CF0
	MotionTrailAction::~MotionTrailAction()
	{
	}

	// ---- the slots of the actions ------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x108075C0
	bool AbortEffectAction::Slot5(int arg, float value)
	{
		render::EffectManager* manager = render::GetEffectManager();
		AbortEffectTrack* track = link.object;
		manager->AbortSlot(&track->slot, track->allowFade, track->fadeTime);
		return false;
	}

	// FUNCTION: ENGINE 0x108076B0
	bool EffectAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		if (gEffectSuspendCount == 0)
		{
			unknown4c = true;
			return true;
		}
		return BeginEffect(link, target, &effectHandle, &watch, unknown34, &unknown3c, unknown44, this);
	}

	// FUNCTION: ENGINE 0x10805CA0
	void EffectAction::Slot6()
	{
		render::EffectManager* manager = render::GetEffectManager();
		if (manager != 0 && link.object != 0 && link.object->abortWhenInterrupted)
		{
			manager->StopEffect(effectHandle.value, link.object->fadeTime);
		}
	}

	// FUNCTION: ENGINE 0x10805BD0
	// EQUIVALENT: the same instructions; the address of the attach joint pushed for FindPart is computed in edx where the
	// engine uses eax (98.6 %)
	bool EffectAction::Slot7(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		if (unknown4c)
		{
			if (gEffectSuspendCount > 0)
			{
				unknown4c = false;
				return Slot5(0, value);
			}
			return true;
		}
		bool keep = link.object->abortWhenInterrupted;
		if (link.object->attachSpace == 2 && link.object->abortBelowJointScale > 0.0f)
		{
			GameObject* object = GameObjectHandleGet(&target);
			if (object != 0)
			{
				AttributePtr<proto::PartLookup*> attribute = object->GetAttributePtr<proto::PartLookup*>(proto::gDrawableAttributeName);
				if (attribute.value != 0)
				{
					proto::PartLookup* lookup = *attribute.value;
					if (lookup != 0)
					{
						if (unknown48 == 0xffff)
						{
							unknown48 = lookup->FindPart(link.object->attachJoint);
						}
						if (unknown48 != 0xffff)
						{
							if (link.object->abortBelowJointScale > lookup->parts[unknown48].scale)
							{
								keep = false;
							}
						}
					}
				}
			}
		}
		return keep;
	}

	// FUNCTION: ENGINE 0x10805FF0
	void MotionTrailAction::Slot6()
	{
		render::EffectManager* manager = render::GetEffectManager();
		if (manager != 0 && link.object != 0 && link.object->abortWhenInterrupted)
		{
			manager->ReleaseDrawable(&drawable);
		}
	}

	// ---- the tracks' action makers -----------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x10807860
	fight::Action* AbortEffectTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new AbortEffectAction(this, listener);
	}

	// FUNCTION: ENGINE 0x108078A0
	fight::Action* MotionTrailTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new MotionTrailAction(this, listener, handle);
	}

	// ---- the tracks' accessors (the engine reads the track classes through them) --------------------------------

	// FUNCTION: ENGINE 0x10805550
	math::Vector MotionTrailTrack::GetShrinkOffset() const
	{
		return shrinkOffset;
	}

	// FUNCTION: ENGINE 0x10805580
	int MotionTrailTrack::GetNumJoints() const
	{
		return numJoints;
	}

	// FUNCTION: ENGINE 0x10805590
	fight::Name* MotionTrailTrack::GetJoint1()
	{
		return &joint1;
	}

	// FUNCTION: ENGINE 0x108055A0
	math::Vector MotionTrailTrack::GetJointOffset1() const
	{
		return jointOffset1;
	}

	// FUNCTION: ENGINE 0x108055C0
	fight::Name* MotionTrailTrack::GetJoint2()
	{
		return &joint2;
	}

	// FUNCTION: ENGINE 0x108055D0
	math::Vector MotionTrailTrack::GetJointOffset2() const
	{
		return jointOffset2;
	}

	// FUNCTION: ENGINE 0x108055F0
	fight::Name* MotionTrailTrack::GetJoint3()
	{
		return &joint3;
	}

	// FUNCTION: ENGINE 0x10805600
	math::Vector MotionTrailTrack::GetJointOffset3() const
	{
		return jointOffset3;
	}

	// FUNCTION: ENGINE 0x10805620
	fight::Name* MotionTrailTrack::GetJoint4()
	{
		return &joint4;
	}

	// FUNCTION: ENGINE 0x10805630
	math::Vector MotionTrailTrack::GetJointOffset4() const
	{
		return jointOffset4;
	}

	// FUNCTION: ENGINE 0x10805650
	fight::Name* MotionTrailTrack::GetJoint5()
	{
		return &joint5;
	}

	// FUNCTION: ENGINE 0x10805660
	math::Vector MotionTrailTrack::GetJointOffset5() const
	{
		return jointOffset5;
	}

	// FUNCTION: ENGINE 0x10805690
	fight::Name* MotionTrailTrack::GetJoint6()
	{
		return &joint6;
	}

	// FUNCTION: ENGINE 0x108056A0
	math::Vector MotionTrailTrack::GetJointOffset6() const
	{
		return jointOffset6;
	}

	// FUNCTION: ENGINE 0x108056D0
	bool MotionTrailTrack::GetAbortWhenInterrupted() const
	{
		return abortWhenInterrupted;
	}

	// FUNCTION: ENGINE 0x10805530
	bool MotionTrailTrack::GetDragged() const
	{
		return dragged;
	}

	// FUNCTION: ENGINE 0x10805540
	fight::Name* MotionTrailTrack::GetShrinkJoint()
	{
		return &shrinkJoint;
	}

	// FUNCTION: ENGINE 0x10804EF0
	fight::Name* AbortEffectTrack::GetSlot()
	{
		return &slot;
	}

	// FUNCTION: ENGINE 0x10804F00
	bool AbortEffectTrack::GetAllowFade() const
	{
		return allowFade;
	}

	// FUNCTION: ENGINE 0x10804F10
	float AbortEffectTrack::GetFadeTime() const
	{
		return fadeTime;
	}

	// FUNCTION: ENGINE 0x10804F20
	float EffectTrack::GetTimeEnd() const
	{
		return timeEnd;
	}

	// FUNCTION: ENGINE 0x10804F30
	fight::Name* EffectTrack::GetEffectName()
	{
		return &effectName;
	}

	// FUNCTION: ENGINE 0x10804F40
	fight::Name* EffectTrack::GetParentObjectName()
	{
		return &parentObjectName;
	}

	// FUNCTION: ENGINE 0x10804F50
	int EffectTrack::GetEmitSpace() const
	{
		return emitSpace;
	}

	// FUNCTION: ENGINE 0x10804F60
	fight::Name* EffectTrack::GetEmitJoint()
	{
		return &emitJoint;
	}

	// FUNCTION: ENGINE 0x10804F70
	math::Vector EffectTrack::GetOffset() const
	{
		return offset;
	}

	// FUNCTION: ENGINE 0x10804F90
	math::Vector EffectTrack::GetOrientation() const
	{
		return orientation;
	}

	// FUNCTION: ENGINE 0x10804FB0
	int EffectTrack::GetAttachSpace() const
	{
		return attachSpace;
	}

	// FUNCTION: ENGINE 0x10804FC0
	fight::Name* EffectTrack::GetAttachJoint()
	{
		return &attachJoint;
	}

	// FUNCTION: ENGINE 0x10804FD0
	bool EffectTrack::GetAbortWhenInterrupted() const
	{
		return abortWhenInterrupted;
	}

	// FUNCTION: ENGINE 0x10804FE0
	fight::Name* EffectTrack::GetSlot()
	{
		return &slot;
	}

	// FUNCTION: ENGINE 0x10804FF0
	float EffectTrack::GetAbortBelowJointScale() const
	{
		return abortBelowJointScale;
	}

	// FUNCTION: ENGINE 0x10805000
	float EffectTrack::GetFadeTime() const
	{
		return fadeTime;
	}

	// FUNCTION: ENGINE 0x10805010
	int EffectTrack::GetEffectStore() const
	{
		return effectStore;
	}

	// FUNCTION: ENGINE 0x10805020
	float EffectTrack::GetScale() const
	{
		return scale;
	}

	// FUNCTION: ENGINE 0x10805030
	bool EffectTrack::GetCollides() const
	{
		return collides;
	}

	// FUNCTION: ENGINE 0x10805040
	float EffectTrack::GetRestitution() const
	{
		return restitution;
	}

	// FUNCTION: ENGINE 0x10805050
	float EffectTrack::GetFriction() const
	{
		return friction;
	}

	// FUNCTION: ENGINE 0x10805060
	float EffectTrack::GetRenderOffset() const
	{
		return renderOffset;
	}

	// FUNCTION: ENGINE 0x10805070
	bool EffectTrack::GetUsePropScaling() const
	{
		return usePropScaling;
	}

	// FUNCTION: ENGINE 0x10805080
	fight::Name* EffectTrack::GetCloneName()
	{
		return &cloneName;
	}

	// FUNCTION: ENGINE 0x10805090
	bool EffectTrack::GetBiases() const
	{
		return biases;
	}

	// FUNCTION: ENGINE 0x108050A0
	float EffectTrack::GetBiasesEmissionRate() const
	{
		return biasesEmissionRate;
	}

	// FUNCTION: ENGINE 0x108050B0
	float EffectTrack::GetBiasesEmissionRateAreaScale() const
	{
		return biasesEmissionRateAreaScale;
	}

	// FUNCTION: ENGINE 0x108050C0
	int EffectTrack::GetBiasesEmissionRateScaleFunction() const
	{
		return biasesEmissionRateScaleFunction;
	}

	// FUNCTION: ENGINE 0x108050D0
	float EffectTrack::GetBiasesLifeSpan() const
	{
		return biasesLifeSpan;
	}

	// FUNCTION: ENGINE 0x108050E0
	float EffectTrack::GetBiasesLifeSpanVariance() const
	{
		return biasesLifeSpanVariance;
	}

	// FUNCTION: ENGINE 0x108050F0
	float EffectTrack::GetBiasesSpeed() const
	{
		return biasesSpeed;
	}

	// FUNCTION: ENGINE 0x10805100
	float EffectTrack::GetBiasesSpeedVariance() const
	{
		return biasesSpeedVariance;
	}

	// FUNCTION: ENGINE 0x10805110
	float EffectTrack::GetBiasesSize1D() const
	{
		return biasesSize1D;
	}

	// FUNCTION: ENGINE 0x10805120
	float EffectTrack::GetBiasesSize1DVariance() const
	{
		return biasesSize1DVariance;
	}

	// FUNCTION: ENGINE 0x10805130
	float EffectTrack::GetBiasesSize1DAreaScale() const
	{
		return biasesSize1DAreaScale;
	}

	// FUNCTION: ENGINE 0x10805140
	int EffectTrack::GetBiasesSize1DScaleFunction() const
	{
		return biasesSize1DScaleFunction;
	}

	// FUNCTION: ENGINE 0x10805150
	float EffectTrack::GetBiasesSpin1D() const
	{
		return biasesSpin1D;
	}

	// FUNCTION: ENGINE 0x10805160
	float EffectTrack::GetBiasesSpin1DVariance() const
	{
		return biasesSpin1DVariance;
	}

	// FUNCTION: ENGINE 0x10805170
	float EffectTrack::GetBiasesWeight() const
	{
		return biasesWeight;
	}

	// FUNCTION: ENGINE 0x10805180
	float EffectTrack::GetBiasesWeightVariance() const
	{
		return biasesWeightVariance;
	}

	// FUNCTION: ENGINE 0x10805190
	float EffectTrack::GetBiasesAngle() const
	{
		return biasesAngle;
	}

	// FUNCTION: ENGINE 0x108051A0
	float EffectTrack::GetBiasesAngleVariance() const
	{
		return biasesAngleVariance;
	}

	// FUNCTION: ENGINE 0x108051B0
	float EffectTrack::GetBiasesGravity() const
	{
		return biasesGravity;
	}

	// FUNCTION: ENGINE 0x108051C0
	float EffectTrack::GetBiasesDrag() const
	{
		return biasesDrag;
	}

	// FUNCTION: ENGINE 0x108051D0
	float EffectTrack::GetBiasesColourRed() const
	{
		return biasesColourRed;
	}

	// FUNCTION: ENGINE 0x108051E0
	float EffectTrack::GetBiasesColourGreen() const
	{
		return biasesColourGreen;
	}

	// FUNCTION: ENGINE 0x108051F0
	float EffectTrack::GetBiasesColourBlue() const
	{
		return biasesColourBlue;
	}

	// FUNCTION: ENGINE 0x10805200
	float EffectTrack::GetBiasesAlpha() const
	{
		return biasesAlpha;
	}

	// FUNCTION: ENGINE 0x10805210
	float EffectTrack::GetBiasesColourOverLifeRed() const
	{
		return biasesColourOverLifeRed;
	}

	// FUNCTION: ENGINE 0x10805220
	float EffectTrack::GetBiasesColourOverLifeGreen() const
	{
		return biasesColourOverLifeGreen;
	}

	// FUNCTION: ENGINE 0x10805230
	float EffectTrack::GetBiasesColourOverLifeBlue() const
	{
		return biasesColourOverLifeBlue;
	}

	// FUNCTION: ENGINE 0x10805240
	float EffectTrack::GetBiasesAlphaOverLife() const
	{
		return biasesAlphaOverLife;
	}

	// FUNCTION: ENGINE 0x10805250
	float EffectTrack::GetBiasesColourVariance() const
	{
		return biasesColourVariance;
	}

	// FUNCTION: ENGINE 0x10805260
	float EffectTrack::GetBiasesAlphaVariance() const
	{
		return biasesAlphaVariance;
	}

	// FUNCTION: ENGINE 0x10805270
	float EffectTrack::GetBiasesGeneratorRadius() const
	{
		return biasesGeneratorRadius;
	}

	// FUNCTION: ENGINE 0x10805280
	float EffectTrack::GetBiasesGeneratorRadial() const
	{
		return biasesGeneratorRadial;
	}

	// FUNCTION: ENGINE 0x10805290
	float EffectTrack::GetBiasesGeneratorHorizSpread() const
	{
		return biasesGeneratorHorizSpread;
	}

	// FUNCTION: ENGINE 0x108052A0
	float EffectTrack::GetBiasesGeneratorVertSpread() const
	{
		return biasesGeneratorVertSpread;
	}

	// FUNCTION: ENGINE 0x108052B0
	float EffectTrack::GetBiasesGeneratorWidth() const
	{
		return biasesGeneratorWidth;
	}

	// FUNCTION: ENGINE 0x108052C0
	float EffectTrack::GetBiasesGeneratorHeight() const
	{
		return biasesGeneratorHeight;
	}

	// FUNCTION: ENGINE 0x108052D0
	math::Vector EffectTrack::GetBiasesMeshGeneratorScale() const
	{
		return biasesMeshGeneratorScale;
	}

	// FUNCTION: ENGINE 0x108052F0
	bool EffectTrack::GetOverrides() const
	{
		return overrides;
	}

	// FUNCTION: ENGINE 0x10805300
	float EffectTrack::GetOverridesEmissionRate() const
	{
		return overridesEmissionRate;
	}

	// FUNCTION: ENGINE 0x10805310
	float EffectTrack::GetOverridesEmissionRatePerMeter() const
	{
		return overridesEmissionRatePerMeter;
	}

	// FUNCTION: ENGINE 0x10805320
	float EffectTrack::GetOverridesMaxParticles() const
	{
		return overridesMaxParticles;
	}

	// FUNCTION: ENGINE 0x10805330
	float EffectTrack::GetOverridesParticleAllocation() const
	{
		return overridesParticleAllocation;
	}

	// FUNCTION: ENGINE 0x10805340
	float EffectTrack::GetOverridesLifeSpan() const
	{
		return overridesLifeSpan;
	}

	// FUNCTION: ENGINE 0x10805350
	float EffectTrack::GetOverridesLifeSpanVariance() const
	{
		return overridesLifeSpanVariance;
	}

	// FUNCTION: ENGINE 0x10805360
	float EffectTrack::GetOverridesSpeed() const
	{
		return overridesSpeed;
	}

	// FUNCTION: ENGINE 0x10805370
	float EffectTrack::GetOverridesSpeedVariance() const
	{
		return overridesSpeedVariance;
	}

	// FUNCTION: ENGINE 0x10805380
	float EffectTrack::GetOverridesSize1D() const
	{
		return overridesSize1D;
	}

	// FUNCTION: ENGINE 0x10805390
	float EffectTrack::GetOverridesSize1DVariance() const
	{
		return overridesSize1DVariance;
	}

	// FUNCTION: ENGINE 0x108053A0
	float EffectTrack::GetOverridesSpin1D() const
	{
		return overridesSpin1D;
	}

	// FUNCTION: ENGINE 0x108053B0
	float EffectTrack::GetOverridesSpin1DVariance() const
	{
		return overridesSpin1DVariance;
	}

	// FUNCTION: ENGINE 0x108053C0
	float EffectTrack::GetOverridesWeight() const
	{
		return overridesWeight;
	}

	// FUNCTION: ENGINE 0x108053D0
	float EffectTrack::GetOverridesWeightVariance() const
	{
		return overridesWeightVariance;
	}

	// FUNCTION: ENGINE 0x108053E0
	float EffectTrack::GetOverridesAngle() const
	{
		return overridesAngle;
	}

	// FUNCTION: ENGINE 0x108053F0
	float EffectTrack::GetOverridesAngleVariance() const
	{
		return overridesAngleVariance;
	}

	// FUNCTION: ENGINE 0x10805400
	float EffectTrack::GetOverridesGravity() const
	{
		return overridesGravity;
	}

	// FUNCTION: ENGINE 0x10805410
	float EffectTrack::GetOverridesDrag() const
	{
		return overridesDrag;
	}

	// FUNCTION: ENGINE 0x10805420
	float EffectTrack::GetOverridesColourRed() const
	{
		return overridesColourRed;
	}

	// FUNCTION: ENGINE 0x10805430
	float EffectTrack::GetOverridesColourGreen() const
	{
		return overridesColourGreen;
	}

	// FUNCTION: ENGINE 0x10805440
	float EffectTrack::GetOverridesColourBlue() const
	{
		return overridesColourBlue;
	}

	// FUNCTION: ENGINE 0x10805450
	float EffectTrack::GetOverridesAlpha() const
	{
		return overridesAlpha;
	}

	// FUNCTION: ENGINE 0x10805460
	float EffectTrack::GetOverridesColourVariance() const
	{
		return overridesColourVariance;
	}

	// FUNCTION: ENGINE 0x10805470
	float EffectTrack::GetOverridesAlphaVariance() const
	{
		return overridesAlphaVariance;
	}

	// FUNCTION: ENGINE 0x10805480
	float EffectTrack::GetOverridesGeneratorWidth() const
	{
		return overridesGeneratorWidth;
	}

	// FUNCTION: ENGINE 0x10805490
	float EffectTrack::GetOverridesGeneratorHeight() const
	{
		return overridesGeneratorHeight;
	}

	// FUNCTION: ENGINE 0x108054A0
	fight::TrackGroup* EffectTrack::GetLodsGroup()
	{
		return &lods;
	}

	// FUNCTION: ENGINE 0x108054B0
	fight::Name* MotionTrailTrack::GetShader()
	{
		return &shader;
	}

	// FUNCTION: ENGINE 0x108054C0
	float MotionTrailTrack::GetGenerateTime() const
	{
		return generateTime;
	}

	// FUNCTION: ENGINE 0x108054D0
	float MotionTrailTrack::GetFadeInTime() const
	{
		return fadeInTime;
	}

	// FUNCTION: ENGINE 0x108054E0
	float MotionTrailTrack::GetFadeOutTime() const
	{
		return fadeOutTime;
	}

	// FUNCTION: ENGINE 0x108054F0
	float MotionTrailTrack::GetTextureTime() const
	{
		return textureTime;
	}

	// FUNCTION: ENGINE 0x10805500
	float MotionTrailTrack::GetFadeTime() const
	{
		return fadeTime;
	}

	// FUNCTION: ENGINE 0x10805510
	float MotionTrailTrack::GetFadeInTrailTime() const
	{
		return fadeInTrailTime;
	}

	// FUNCTION: ENGINE 0x10805520
	float MotionTrailTrack::GetShrinkTime() const
	{
		return shrinkTime;
	}

	// FUNCTION: ENGINE 0x10804EE0
	// NONMATCHING: the engine loads the member into ecx and the out pointer into eax, ours the other way round
#ifdef NONMATCHING
	void AbortEffectTrack::GetSlotIndex(int& value) const
	{
		value = slot.index;
	}
#endif
}
