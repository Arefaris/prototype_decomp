// The effect track of the fight tree: a fight::Track that starts a particle effect when its action begins, the two
// action classes that carry it (engine::EffectAction plays the effect, engine::AbortEffectAction stops it) and the
// reflected accessors of the track and of the effect itself. Unit 0x10804EC0 - 0x10807550 (no assert path; the
// directory and file names are guesses). The class and member names are guesses until the binary tells the real
// ones; the layouts are read off the engine's accessors.
#ifndef ENGINE_FIGHT_EFFECTTRACK_H
#define ENGINE_FIGHT_EFFECTTRACK_H

#include "code/core/linklist.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/fight/trackfactory.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace engine
{
	// The game's veto on an effect track's begin (set through the track factory's exposed functions; names guessed)
	typedef bool (*EffectTrackCheck)(unsigned int, const float*, int);
	extern EffectTrackCheck gEffectTrackCheck;
	extern int gEffectTrackCheckContext;
	// The counter a script holds the effect tracks with; 0x111BEA74 keeps the value in force when it was changed
	extern int gEffectSuspendSaved;
	extern int gEffectSuspendCount;

	// The engine's own copies of core's reference helpers, per type (core::RefAssign / core::SafeRelease)
	// 0x108058E0 / 0x10805910
	void AssignEffectRef(core::IRefCount*& pointer, core::IRefCount* object);
	void ReleaseEffectRef(core::IRefCount*& object);

	// RTTI: engine::AbortEffectTrack (16 vftable slots, 0x28 bytes)
	class AbortEffectTrack : public fight::Track
	{
	public:
		// 0x1080C940
		AbortEffectTrack();
		virtual ~AbortEffectTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x10807860)
		virtual void Slot15();

		// The members the properties write
		bool SetSlot(const fight::Name& value);
		bool SetAllowFade(bool value);
		bool SetFadeTime(float value);
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);

		// The members the engine reads through accessors
		// 0x10804EF0
		fight::Name* GetSlot();
		// 0x10804F00
		bool GetAllowFade() const;
		// 0x10804F10
		float GetFadeTime() const;
		// 0x10804EE0: the high word of the slot name
		void GetSlotIndex(int& value) const;

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name slot;  // +0x10
		float fadeTime;  // +0x18
		float timeBegin;  // +0x1C
		float timeEnd;  // +0x20
		bool allowFade;  // +0x24
	};

	extern fight::Property** gAbortEffectTrackProperties;
	// 0x1080D460
	// 0x1080D4C0
	fight::TrackFactory* CreateAbortEffectTrackFactory(const char* name);
	void RegisterAbortEffectTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::EffectTrack (17 vftable slots, 0x1B0 bytes)
	class EffectTrack : public fight::Track
	{
	public:
		// 0x1080C9A0
		EffectTrack();
		virtual ~EffectTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x10807790)
		virtual void Slot15();
		// vftable slot 16 (0x1080CCD0)
		// vftable slot 16 (0x1080CCD0): whether the override bit of a property is set
		virtual bool Slot16(int index);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetEffectName(const fight::Name& value);
		bool SetParentObjectName(const fight::Name& value);
		bool SetEmitSpace(int value);
		bool SetEmitJoint(const fight::Name& value);
		bool SetOffset(const math::Vector& value);
		bool SetOrientation(const math::Vector& value);
		bool SetAttachSpace(int value);
		bool SetAttachJoint(const fight::Name& value);
		bool SetAbortWhenInterrupted(bool value);
		bool SetSlot(const fight::Name& value);
		bool SetAbortBelowJointScale(float value);
		bool SetFadeTime(float value);
		bool SetEffectController(const fight::Name& value);
		bool SetEffectStore(int value);
		bool SetHighPriority(bool value);
		bool SetScale(float value);
		bool SetCollides(bool value);
		bool SetRestitution(float value);
		bool SetFriction(float value);
		bool SetRenderOffset(float value);
		bool SetUsePropScaling(bool value);
		bool SetCloneName(const fight::Name& value);
		bool SetCloneTint(const math::Colour128& value);
		bool SetBiases(bool value);
		bool SetBiasesEmissionRate(float value);
		bool SetBiasesEmissionRateAreaScale(float value);
		bool SetBiasesEmissionRateScaleFunction(int value);
		bool SetBiasesLifeSpan(float value);
		bool SetBiasesLifeSpanVariance(float value);
		bool SetBiasesSpeed(float value);
		bool SetBiasesSpeedVariance(float value);
		bool SetBiasesSize1D(float value);
		bool SetBiasesSize1DVariance(float value);
		bool SetBiasesSize1DAreaScale(float value);
		bool SetBiasesSize1DScaleFunction(int value);
		bool SetBiasesSpin1D(float value);
		bool SetBiasesSpin1DVariance(float value);
		bool SetBiasesWeight(float value);
		bool SetBiasesWeightVariance(float value);
		bool SetBiasesAngle(float value);
		bool SetBiasesAngleVariance(float value);
		bool SetBiasesGravity(float value);
		bool SetBiasesDrag(float value);
		bool SetBiasesColourRed(float value);
		bool SetBiasesColourGreen(float value);
		bool SetBiasesColourBlue(float value);
		bool SetBiasesAlpha(float value);
		bool SetBiasesColourOverLifeRed(float value);
		bool SetBiasesColourOverLifeGreen(float value);
		bool SetBiasesColourOverLifeBlue(float value);
		bool SetBiasesAlphaOverLife(float value);
		bool SetBiasesColourVariance(float value);
		bool SetBiasesAlphaVariance(float value);
		bool SetBiasesGeneratorRadius(float value);
		bool SetBiasesGeneratorRadial(float value);
		bool SetBiasesGeneratorHorizSpread(float value);
		bool SetBiasesGeneratorVertSpread(float value);
		bool SetBiasesGeneratorWidth(float value);
		bool SetBiasesGeneratorHeight(float value);
		bool SetBiasesMeshGeneratorScale(const math::Vector& value);
		bool SetOverrides(bool value);
		bool SetOverridesEmissionRate(float value);
		bool SetOverridesEmissionRatePerMeter(float value);
		bool SetOverridesMaxParticles(float value);
		bool SetOverridesParticleAllocation(float value);
		bool SetOverridesLifeSpan(float value);
		bool SetOverridesLifeSpanVariance(float value);
		bool SetOverridesSpeed(float value);
		bool SetOverridesSpeedVariance(float value);
		bool SetOverridesSize1D(float value);
		bool SetOverridesSize1DVariance(float value);
		bool SetOverridesSpin1D(float value);
		bool SetOverridesSpin1DVariance(float value);
		bool SetOverridesWeight(float value);
		bool SetOverridesWeightVariance(float value);
		bool SetOverridesAngle(float value);
		bool SetOverridesAngleVariance(float value);
		bool SetOverridesGravity(float value);
		bool SetOverridesDrag(float value);
		bool SetOverridesColourRed(float value);
		bool SetOverridesColourGreen(float value);
		bool SetOverridesColourBlue(float value);
		bool SetOverridesAlpha(float value);
		bool SetOverridesColourVariance(float value);
		bool SetOverridesAlphaVariance(float value);
		bool SetOverridesGeneratorWidth(float value);
		bool SetOverridesGeneratorHeight(float value);
		fight::TrackGroup* GetLods();

		// The members the engine reads through accessors
		// 0x10804F20
		float GetTimeEnd() const;
		// 0x10804F30
		fight::Name* GetEffectName();
		// 0x10804F40
		fight::Name* GetParentObjectName();
		// 0x10804F50
		int GetEmitSpace() const;
		// 0x10804F60
		fight::Name* GetEmitJoint();
		// 0x10804F70
		math::Vector GetOffset() const;
		// 0x10804F90
		math::Vector GetOrientation() const;
		// 0x10804FB0
		int GetAttachSpace() const;
		// 0x10804FC0
		fight::Name* GetAttachJoint();
		// 0x10804FD0
		bool GetAbortWhenInterrupted() const;
		// 0x10804FE0
		fight::Name* GetSlot();
		// 0x10804FF0
		float GetAbortBelowJointScale() const;
		// 0x10805000
		float GetFadeTime() const;
		// 0x10805010
		int GetEffectStore() const;
		// 0x10805020
		float GetScale() const;
		// 0x10805030
		bool GetCollides() const;
		// 0x10805040
		float GetRestitution() const;
		// 0x10805050
		float GetFriction() const;
		// 0x10805060
		float GetRenderOffset() const;
		// 0x10805070
		bool GetUsePropScaling() const;
		// 0x10805080
		fight::Name* GetCloneName();
		// 0x10805090
		bool GetBiases() const;
		// 0x108050A0
		float GetBiasesEmissionRate() const;
		// 0x108050B0
		float GetBiasesEmissionRateAreaScale() const;
		// 0x108050C0
		int GetBiasesEmissionRateScaleFunction() const;
		// 0x108050D0
		float GetBiasesLifeSpan() const;
		// 0x108050E0
		float GetBiasesLifeSpanVariance() const;
		// 0x108050F0
		float GetBiasesSpeed() const;
		// 0x10805100
		float GetBiasesSpeedVariance() const;
		// 0x10805110
		float GetBiasesSize1D() const;
		// 0x10805120
		float GetBiasesSize1DVariance() const;
		// 0x10805130
		float GetBiasesSize1DAreaScale() const;
		// 0x10805140
		int GetBiasesSize1DScaleFunction() const;
		// 0x10805150
		float GetBiasesSpin1D() const;
		// 0x10805160
		float GetBiasesSpin1DVariance() const;
		// 0x10805170
		float GetBiasesWeight() const;
		// 0x10805180
		float GetBiasesWeightVariance() const;
		// 0x10805190
		float GetBiasesAngle() const;
		// 0x108051A0
		float GetBiasesAngleVariance() const;
		// 0x108051B0
		float GetBiasesGravity() const;
		// 0x108051C0
		float GetBiasesDrag() const;
		// 0x108051D0
		float GetBiasesColourRed() const;
		// 0x108051E0
		float GetBiasesColourGreen() const;
		// 0x108051F0
		float GetBiasesColourBlue() const;
		// 0x10805200
		float GetBiasesAlpha() const;
		// 0x10805210
		float GetBiasesColourOverLifeRed() const;
		// 0x10805220
		float GetBiasesColourOverLifeGreen() const;
		// 0x10805230
		float GetBiasesColourOverLifeBlue() const;
		// 0x10805240
		float GetBiasesAlphaOverLife() const;
		// 0x10805250
		float GetBiasesColourVariance() const;
		// 0x10805260
		float GetBiasesAlphaVariance() const;
		// 0x10805270
		float GetBiasesGeneratorRadius() const;
		// 0x10805280
		float GetBiasesGeneratorRadial() const;
		// 0x10805290
		float GetBiasesGeneratorHorizSpread() const;
		// 0x108052A0
		float GetBiasesGeneratorVertSpread() const;
		// 0x108052B0
		float GetBiasesGeneratorWidth() const;
		// 0x108052C0
		float GetBiasesGeneratorHeight() const;
		// 0x108052D0
		math::Vector GetBiasesMeshGeneratorScale() const;
		// 0x108052F0
		bool GetOverrides() const;
		// 0x10805300
		float GetOverridesEmissionRate() const;
		// 0x10805310
		float GetOverridesEmissionRatePerMeter() const;
		// 0x10805320
		float GetOverridesMaxParticles() const;
		// 0x10805330
		float GetOverridesParticleAllocation() const;
		// 0x10805340
		float GetOverridesLifeSpan() const;
		// 0x10805350
		float GetOverridesLifeSpanVariance() const;
		// 0x10805360
		float GetOverridesSpeed() const;
		// 0x10805370
		float GetOverridesSpeedVariance() const;
		// 0x10805380
		float GetOverridesSize1D() const;
		// 0x10805390
		float GetOverridesSize1DVariance() const;
		// 0x108053A0
		float GetOverridesSpin1D() const;
		// 0x108053B0
		float GetOverridesSpin1DVariance() const;
		// 0x108053C0
		float GetOverridesWeight() const;
		// 0x108053D0
		float GetOverridesWeightVariance() const;
		// 0x108053E0
		float GetOverridesAngle() const;
		// 0x108053F0
		float GetOverridesAngleVariance() const;
		// 0x10805400
		float GetOverridesGravity() const;
		// 0x10805410
		float GetOverridesDrag() const;
		// 0x10805420
		float GetOverridesColourRed() const;
		// 0x10805430
		float GetOverridesColourGreen() const;
		// 0x10805440
		float GetOverridesColourBlue() const;
		// 0x10805450
		float GetOverridesAlpha() const;
		// 0x10805460
		float GetOverridesColourVariance() const;
		// 0x10805470
		float GetOverridesAlphaVariance() const;
		// 0x10805480
		float GetOverridesGeneratorWidth() const;
		// 0x10805490
		float GetOverridesGeneratorHeight() const;
		// 0x108054A0
		fight::TrackGroup* GetLodsGroup();

		// 0x1080C680: sets or clears the override bits of a group's properties (and of the groups inside it)
		void ApplyGroup(int group, bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		// The bits of the properties the track overrides (Slot16 tests one, ApplyGroup sets a group's)
		unsigned __int64 overrideMask;  // +0x10
		fight::Name attachJoint;  // +0x18
		fight::Name cloneName;  // +0x20
		fight::Name effectController;  // +0x28
		fight::Name effectName;  // +0x30
		fight::Name emitJoint;  // +0x38
		fight::Name parentObjectName;  // +0x40
		fight::Name slot;  // +0x48
		math::Colour128 cloneTint;  // +0x50
		math::Vector biasesMeshGeneratorScale;  // +0x60
		math::Vector offset;  // +0x6C
		math::Vector orientation;  // +0x78
		fight::TrackGroup lods;  // +0x84
		float abortBelowJointScale;  // +0x88
		float biasesAlpha;  // +0x8C
		float biasesAlphaOverLife;  // +0x90
		float biasesAlphaVariance;  // +0x94
		float biasesAngle;  // +0x98
		float biasesAngleVariance;  // +0x9C
		float biasesColourBlue;  // +0xA0
		float biasesColourGreen;  // +0xA4
		float biasesColourOverLifeBlue;  // +0xA8
		float biasesColourOverLifeGreen;  // +0xAC
		float biasesColourOverLifeRed;  // +0xB0
		float biasesColourRed;  // +0xB4
		float biasesColourVariance;  // +0xB8
		float biasesDrag;  // +0xBC
		float biasesEmissionRate;  // +0xC0
		float biasesEmissionRateAreaScale;  // +0xC4
		float biasesGeneratorHeight;  // +0xC8
		float biasesGeneratorHorizSpread;  // +0xCC
		float biasesGeneratorRadial;  // +0xD0
		float biasesGeneratorRadius;  // +0xD4
		float biasesGeneratorVertSpread;  // +0xD8
		float biasesGeneratorWidth;  // +0xDC
		float biasesGravity;  // +0xE0
		float biasesLifeSpan;  // +0xE4
		float biasesLifeSpanVariance;  // +0xE8
		float biasesSize1D;  // +0xEC
		float biasesSize1DAreaScale;  // +0xF0
		float biasesSize1DVariance;  // +0xF4
		float biasesSpeed;  // +0xF8
		float biasesSpeedVariance;  // +0xFC
		float biasesSpin1D;  // +0x100
		float biasesSpin1DVariance;  // +0x104
		float biasesWeight;  // +0x108
		float biasesWeightVariance;  // +0x10C
		float fadeTime;  // +0x110
		float friction;  // +0x114
		float overridesAlpha;  // +0x118
		float overridesAlphaVariance;  // +0x11C
		float overridesAngle;  // +0x120
		float overridesAngleVariance;  // +0x124
		float overridesColourBlue;  // +0x128
		float overridesColourGreen;  // +0x12C
		float overridesColourRed;  // +0x130
		float overridesColourVariance;  // +0x134
		float overridesDrag;  // +0x138
		float overridesEmissionRate;  // +0x13C
		float overridesEmissionRatePerMeter;  // +0x140
		float overridesGeneratorHeight;  // +0x144
		float overridesGeneratorWidth;  // +0x148
		float overridesGravity;  // +0x14C
		float overridesLifeSpan;  // +0x150
		float overridesLifeSpanVariance;  // +0x154
		float overridesMaxParticles;  // +0x158
		float overridesParticleAllocation;  // +0x15C
		float overridesSize1D;  // +0x160
		float overridesSize1DVariance;  // +0x164
		float overridesSpeed;  // +0x168
		float overridesSpeedVariance;  // +0x16C
		float overridesSpin1D;  // +0x170
		float overridesSpin1DVariance;  // +0x174
		float overridesWeight;  // +0x178
		float overridesWeightVariance;  // +0x17C
		float renderOffset;  // +0x180
		float restitution;  // +0x184
		float scale;  // +0x188
		float timeBegin;  // +0x18C
		float timeEnd;  // +0x190
		int attachSpace;  // +0x194
		int biasesEmissionRateScaleFunction;  // +0x198
		int biasesSize1DScaleFunction;  // +0x19C
		int effectStore;  // +0x1A0
		int emitSpace;  // +0x1A4
		bool abortWhenInterrupted;  // +0x1A8
		bool biases;  // +0x1A9
		bool collides;  // +0x1AA
		bool highPriority;  // +0x1AB
		bool overrides;  // +0x1AC
		bool usePropScaling;  // +0x1AD
	};

	extern fight::Property** gEffectTrackProperties;
	// 0x1080D480
	// 0x1080D4F0
	fight::TrackFactory* CreateEffectTrackFactory(const char* name);
	void RegisterEffectTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::MotionTrailTrack (16 vftable slots, 0xD8 bytes)
	class MotionTrailTrack : public fight::Track
	{
	public:
		// 0x1080CD70
		MotionTrailTrack();
		virtual ~MotionTrailTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108078A0)
		virtual void Slot15();

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetShader(const fight::Name& value);
		bool SetGenerateTime(float value);
		bool SetFadeInTime(float value);
		bool SetFadeOutTime(float value);
		bool SetTextureTime(float value);
		bool SetFadeTime(float value);
		bool SetFadeInTrailTime(float value);
		bool SetShrinkTime(float value);
		bool SetDragged(bool value);
		bool SetShrinkJoint(const fight::Name& value);
		bool SetShrinkOffset(const math::Vector& value);
		bool SetNumJoints(int value);
		bool SetJoint1(const fight::Name& value);
		bool SetJointOffset1(const math::Vector& value);
		bool SetJoint2(const fight::Name& value);
		bool SetJointOffset2(const math::Vector& value);
		bool SetJoint3(const fight::Name& value);
		bool SetJointOffset3(const math::Vector& value);
		bool SetJoint4(const fight::Name& value);
		bool SetJointOffset4(const math::Vector& value);
		bool SetJoint5(const fight::Name& value);
		bool SetJointOffset5(const math::Vector& value);
		bool SetJoint6(const fight::Name& value);
		bool SetJointOffset6(const math::Vector& value);
		bool SetAbortWhenInterrupted(bool value);
		bool SetRunTillStop(bool value);
		bool SetSlot(int value);

		// The members the engine reads through accessors
		// 0x10805550
		math::Vector GetShrinkOffset() const;
		// 0x10805580
		int GetNumJoints() const;
		// 0x10805590
		fight::Name* GetJoint1();
		// 0x108055A0
		math::Vector GetJointOffset1() const;
		// 0x108055C0
		fight::Name* GetJoint2();
		// 0x108055D0
		math::Vector GetJointOffset2() const;
		// 0x108055F0
		fight::Name* GetJoint3();
		// 0x10805600
		math::Vector GetJointOffset3() const;
		// 0x10805620
		fight::Name* GetJoint4();
		// 0x10805630
		math::Vector GetJointOffset4() const;
		// 0x10805650
		fight::Name* GetJoint5();
		// 0x10805660
		math::Vector GetJointOffset5() const;
		// 0x10805690
		fight::Name* GetJoint6();
		// 0x108056A0
		math::Vector GetJointOffset6() const;
		// 0x108056D0
		bool GetAbortWhenInterrupted() const;
		// 0x10805530
		bool GetDragged() const;
		// 0x10805540
		fight::Name* GetShrinkJoint();
		// 0x108054B0
		fight::Name* GetShader();
		// 0x108054C0
		float GetGenerateTime() const;
		// 0x108054D0
		float GetFadeInTime() const;
		// 0x108054E0
		float GetFadeOutTime() const;
		// 0x108054F0
		float GetTextureTime() const;
		// 0x10805500
		float GetFadeTime() const;
		// 0x10805510
		float GetFadeInTrailTime() const;
		// 0x10805520
		float GetShrinkTime() const;

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name joint1;  // +0x10
		fight::Name joint2;  // +0x18
		fight::Name joint3;  // +0x20
		fight::Name joint4;  // +0x28
		fight::Name joint5;  // +0x30
		fight::Name joint6;  // +0x38
		fight::Name shader;  // +0x40
		fight::Name shrinkJoint;  // +0x48
		math::Vector jointOffset1;  // +0x50
		math::Vector jointOffset2;  // +0x5C
		math::Vector jointOffset3;  // +0x68
		math::Vector jointOffset4;  // +0x74
		math::Vector jointOffset5;  // +0x80
		math::Vector jointOffset6;  // +0x8C
		math::Vector shrinkOffset;  // +0x98
		float fadeInTime;  // +0xA4
		float fadeInTrailTime;  // +0xA8
		float fadeOutTime;  // +0xAC
		float fadeTime;  // +0xB0
		float generateTime;  // +0xB4
		float shrinkTime;  // +0xB8
		float textureTime;  // +0xBC
		float timeBegin;  // +0xC0
		float timeEnd;  // +0xC4
		int numJoints;  // +0xC8
		int slot;  // +0xCC
		bool abortWhenInterrupted;  // +0xD0
		bool dragged;  // +0xD1
		bool runTillStop;  // +0xD2
		int unknownd4;
	};

	extern fight::Property** gMotionTrailTrackProperties;
	// 0x1080D4A0
	// 0x1080D520
	fight::TrackFactory* CreateMotionTrailTrackFactory(const char* name);
	void RegisterMotionTrailTrackFactory(fight::TrackRegistry* registry, const char* name);

	// 0x10805750 builds the spawn matrix of an effect from the parent matrix it hangs off: the parent's second row is
	// the direction the effect is aimed along and its translation row the origin. The engine's copy pops two arguments
	// and never reads ecx, so it is a member function that does not touch its object; its class is not known.
	class EffectSpawnTransform
	{
	public:
		void BuildMatrix(const math::Matrix& parent, math::Matrix& matrix) const;
	};

	// The node an action registers on a track it watches instead of driving it: the track keeps that list at +0x24
	// and the node is inserted and removed through the track (register, unregister)
	class TrackWatch
	{
	public:
		TrackWatch(fight::Track* newTrack)
		{
			track = newTrack;
			next = 0;
			prev = 0;
			if (newTrack != 0)
			{
				newTrack->Register(this);
			}
		}
		~TrackWatch()
		{
			if (track != 0)
			{
				track->Unregister(this);
			}
		}

		fight::Track* track;
		TrackWatch* next;
		TrackWatch* prev;
	};

	// The action that plays a particle effect (RTTI: engine::EffectAction, 9 vtable slots, size 0x50)
	class EffectAction : public fight::Action
	{
	public:
		EffectAction(EffectTrack* newTrack, fight::Track* listener, int object, core::IRefCount* effect, int mode);
		virtual ~EffectAction();

		core::Link<EffectTrack> link;
		TrackWatch watch;
		int unknown34;
		int unknown38;
		core::IRefCount* unknown3c;
		int unknown40;
		core::IRefCount* unknown44;
		int unknown48;
		bool unknown4c;
	};

	// The action that stops an effect again (RTTI: engine::AbortEffectAction, 9 vtable slots, size 0x28)
	class AbortEffectAction : public fight::Action
	{
	public:
		AbortEffectAction(AbortEffectTrack* newTrack, fight::Track* listener);
		virtual ~AbortEffectAction();

		// vftable slot 5 (0x108075C0): stops the effect the track plays (name guess)
		virtual bool Slot5(int arg, float value);

		core::Link<AbortEffectTrack> link;
	};

	// The action that starts a motion trail (RTTI: engine::MotionTrailAction, 9 vtable slots, size 0x3C)
	class MotionTrailAction : public fight::Action
	{
	public:
		MotionTrailAction(MotionTrailTrack* newTrack, fight::Track* listener, int value);
		virtual ~MotionTrailAction();

		// vftable slot 5 (0x10805D30) and slot 6 (0x10805FF0) (names guessed)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<MotionTrailTrack> link;
		TrackWatch watch;
		int unknown34;
		int unknown38;
	};
}

#endif
