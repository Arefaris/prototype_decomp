// The fight tracks that show and hide primitives, destroy an object and control an animation (unit 0x108AF960 - 0x108B0840; no assert path, file name guessed).
#include "code/engine/fight/primitivetracks.h"

namespace engine
{
	fight::Property** gPrimitiveVisibilityTrackProperties;  // 0x113182D0

	// FUNCTION: ENGINE 0x108AF930
	bool PrimitiveVisibilityTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AF940
	bool PrimitiveVisibilityTrack::SetVisible(bool newValue)
	{
		visible = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AF9A0
	bool PrimitiveVisibilityTrack::SetPrimitiveName(const fight::Name& newValue)
	{
		primitiveName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AF960
	fight::Property* PrimitiveVisibilityTrack::GetProperty(int index)
	{
		return gPrimitiveVisibilityTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108AF970
	void PrimitiveVisibilityTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPrimitiveVisibilityTrackProperties);
	}

	// FUNCTION: ENGINE 0x108AF9E0
	// ctor stores: [('mov', 'dword', 0, '0x10e7ad54'), ('movss', 'dword', 24, '0.0f'), ('mov', 'byte', 28, '0'), ('mov', 'dword', 12, '1')]
	PrimitiveVisibilityTrack::PrimitiveVisibilityTrack() : timeBegin(0.0f), visible(false)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108AFA10
	float PrimitiveVisibilityTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108AFA20
	float PrimitiveVisibilityTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108AFA30
	PrimitiveVisibilityTrack::~PrimitiveVisibilityTrack()
	{
	}

	// FUNCTION: ENGINE 0x108AFD90
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void PrimitiveVisibilityTrack::RegisterProperties()
	{
		if (gPrimitiveVisibilityTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PrimitiveVisibilityTrack>("timeBegin", &PrimitiveVisibilityTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<PrimitiveVisibilityTrack>("primitiveName", &PrimitiveVisibilityTrack::SetPrimitiveName);
			properties[1] = property;
			property = new fight::PropertyBool<PrimitiveVisibilityTrack>("visible", &PrimitiveVisibilityTrack::SetVisible);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gPrimitiveVisibilityTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108AFC70
	fight::TrackFactory* CreatePrimitiveVisibilityTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PrimitiveVisibilityTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AFCB0
	void RegisterPrimitiveVisibilityTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PrimitiveVisibilityTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<PrimitiveVisibilityTrack>;
	template class fight::PropertyFloatConstRange<PrimitiveVisibilityTrack>;
	template class fight::PropertyName<PrimitiveVisibilityTrack>;
	template class fight::TrackFactoryTemplate<PrimitiveVisibilityTrack>;
	template class fight::TrackFactoryCasterTemplate<PrimitiveVisibilityTrack>;

	fight::Property** gExplicitPrimitiveVisibilityTrackProperties;  // 0x113182D4

	// FUNCTION: ENGINE 0x108AF950
	bool ExplicitPrimitiveVisibilityTrack::SetToBeContinued(bool newValue)
	{
		toBeContinued = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AF9C0
	bool ExplicitPrimitiveVisibilityTrack::SetObject(const fight::Name& newValue)
	{
		object = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AF980
	fight::Property* ExplicitPrimitiveVisibilityTrack::GetProperty(int index)
	{
		return gExplicitPrimitiveVisibilityTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108AF990
	void ExplicitPrimitiveVisibilityTrack::ClearProperties()
	{
		fight::FreePropertyList(&gExplicitPrimitiveVisibilityTrackProperties);
	}

	// FUNCTION: ENGINE 0x108AFA40
	// ctor stores: [('mov', 'dword', 0, '0x10e7ad9c'), ('mov', 'byte', 40, '1')]
	ExplicitPrimitiveVisibilityTrack::ExplicitPrimitiveVisibilityTrack() : toBeContinued(1)
	{
	}

	// FUNCTION: ENGINE 0x108AFA60
	ExplicitPrimitiveVisibilityTrack::~ExplicitPrimitiveVisibilityTrack()
	{
	}

	// FUNCTION: ENGINE 0x108AFE70
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void ExplicitPrimitiveVisibilityTrack::RegisterProperties()
	{
		if (gExplicitPrimitiveVisibilityTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<ExplicitPrimitiveVisibilityTrack>("object", &ExplicitPrimitiveVisibilityTrack::SetObject);
			properties[0] = property;
			property = new fight::PropertyBool<ExplicitPrimitiveVisibilityTrack>("toBeContinued", &ExplicitPrimitiveVisibilityTrack::SetToBeContinued);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<ExplicitPrimitiveVisibilityTrack>("timeBegin", &engine::PrimitiveVisibilityTrack::SetTimeBegin);
			properties[2] = property;
			property = new fight::PropertyName<ExplicitPrimitiveVisibilityTrack>("primitiveName", &engine::PrimitiveVisibilityTrack::SetPrimitiveName);
			properties[3] = property;
			property = new fight::PropertyBool<ExplicitPrimitiveVisibilityTrack>("visible", &engine::PrimitiveVisibilityTrack::SetVisible);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gExplicitPrimitiveVisibilityTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108AFC90
	fight::TrackFactory* CreateExplicitPrimitiveVisibilityTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<ExplicitPrimitiveVisibilityTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AFCE0
	void RegisterExplicitPrimitiveVisibilityTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<ExplicitPrimitiveVisibilityTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<ExplicitPrimitiveVisibilityTrack>;
	template class fight::PropertyFloatConstRange<ExplicitPrimitiveVisibilityTrack>;
	template class fight::PropertyName<ExplicitPrimitiveVisibilityTrack>;
	template class fight::TrackFactoryTemplate<ExplicitPrimitiveVisibilityTrack>;
	template class fight::TrackFactoryCasterTemplate<ExplicitPrimitiveVisibilityTrack>;

	fight::Property** gDestroyTrackProperties;  // 0x113182D8

	// FUNCTION: ENGINE 0x108B00D0
	bool DestroyTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B00E0
	fight::Property* DestroyTrack::GetProperty(int index)
	{
		return gDestroyTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B00F0
	void DestroyTrack::ClearProperties()
	{
		fight::FreePropertyList(&gDestroyTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B0100
	// ctor stores: [('mov', 'dword', 0, '0x10e7af1c'), ('movss', 'dword', 16, '0.0f')]
	DestroyTrack::DestroyTrack() : timeBegin(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x108B0120
	float DestroyTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B0130
	float DestroyTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108B0140
	DestroyTrack::~DestroyTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B0220
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void DestroyTrack::RegisterProperties()
	{
		if (gDestroyTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<DestroyTrack>("timeBegin", &DestroyTrack::SetTimeBegin);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gDestroyTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B0200
	fight::TrackFactory* CreateDestroyTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<DestroyTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B02A0
	void RegisterDestroyTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<DestroyTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<DestroyTrack>;
	template class fight::TrackFactoryTemplate<DestroyTrack>;
	template class fight::TrackFactoryCasterTemplate<DestroyTrack>;

	extern fight::EnumEntry gAnimationControlTrackCycleModeTable[];
	extern const int gAnimationControlTrackCycleModeCount;

	fight::Property** gAnimationControlTrackProperties;  // 0x113182DC

	// FUNCTION: ENGINE 0x108B0360
	bool AnimationControlTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B0370
	bool AnimationControlTrack::SetStartFrame(float newValue)
	{
		startFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B0380
	bool AnimationControlTrack::SetEndFrame(float newValue)
	{
		endFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B0390
	bool AnimationControlTrack::SetRelativeSpeed(float newValue)
	{
		relativeSpeed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B03A0
	bool AnimationControlTrack::SetCycleMode(int newValue)
	{
		cycleMode = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B03B0
	bool AnimationControlTrack::SetNumCycles(int newValue)
	{
		numCycles = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B03C0
	fight::Property* AnimationControlTrack::GetProperty(int index)
	{
		return gAnimationControlTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B03D0
	void AnimationControlTrack::ClearProperties()
	{
		fight::FreePropertyList(&gAnimationControlTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B03E0
	// ctor stores: [('mov', 'dword', 32, '0'), ('mov', 'dword', 36, '0'), ('mov', 'dword', 0, '0x10e7afb4'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '1.0f'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f')]
	AnimationControlTrack::AnimationControlTrack() : endFrame(0.0f), relativeSpeed(1.0f), startFrame(0.0f), timeBegin(0.0f), cycleMode(0), numCycles(0)
	{
	}

	// FUNCTION: ENGINE 0x108B0420
	float AnimationControlTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B0430
	float AnimationControlTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108B0440
	AnimationControlTrack::~AnimationControlTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B0600
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void AnimationControlTrack::RegisterProperties()
	{
		if (gAnimationControlTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<AnimationControlTrack>("timeBegin", &AnimationControlTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<AnimationControlTrack>("startFrame", &AnimationControlTrack::SetStartFrame);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<AnimationControlTrack>("endFrame", &AnimationControlTrack::SetEndFrame);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<AnimationControlTrack>("relativeSpeed", &AnimationControlTrack::SetRelativeSpeed);
			properties[3] = property;
			property = new fight::PropertyEnumConstList<AnimationControlTrack>("cycleMode", gAnimationControlTrackCycleModeTable, gAnimationControlTrackCycleModeCount, &AnimationControlTrack::SetCycleMode);
			properties[4] = property;
			property = new fight::PropertyIntConstRange<AnimationControlTrack>("numCycles", &AnimationControlTrack::SetNumCycles);
			properties[5] = property;
			fight::RegisterPropertyList(properties, &gAnimationControlTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B05E0
	fight::TrackFactory* CreateAnimationControlTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<AnimationControlTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B0780
	void RegisterAnimationControlTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<AnimationControlTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<AnimationControlTrack>;
	template class fight::PropertyFloatConstRange<AnimationControlTrack>;
	template class fight::PropertyIntConstRange<AnimationControlTrack>;
	template class fight::TrackFactoryTemplate<AnimationControlTrack>;
	template class fight::TrackFactoryCasterTemplate<AnimationControlTrack>;

}
