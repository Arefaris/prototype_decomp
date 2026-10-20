// The fight tracks that play non-interactive sequence animations, animate lights and the camera, swap drawables and dilate time (unit 0x108B2EF0 - 0x108B52D0; no assert path, file name guessed).
#include "code/engine/fight/cameratracks.h"

namespace engine
{
	extern fight::EnumEntry gNISAnimationTrackCyclicTable[];

	fight::Property** gNISAnimationTrackProperties;  // 0x11318358

	// FUNCTION: ENGINE 0x108B2E60
	bool NISAnimationTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2E70
	bool NISAnimationTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2E80
	bool NISAnimationTrack::SetSpeed(float newValue)
	{
		speed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2E90
	bool NISAnimationTrack::SetInitFrame(float newValue)
	{
		initFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2EA0
	bool NISAnimationTrack::SetStartFrame(float newValue)
	{
		startFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2EB0
	bool NISAnimationTrack::SetEndFrame(float newValue)
	{
		endFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2EC0
	bool NISAnimationTrack::SetCyclic(int newValue)
	{
		cyclic = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2ED0
	bool NISAnimationTrack::SetNumCycles(int newValue)
	{
		numCycles = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2EE0
	bool NISAnimationTrack::SetToBeContinued(bool newValue)
	{
		toBeContinued = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2F10
	bool NISAnimationTrack::SetObject(const fight::Name& newValue)
	{
		object = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2F30
	bool NISAnimationTrack::SetAnimation(const fight::Name& newValue)
	{
		animation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B2EF0
	fight::Property* NISAnimationTrack::GetProperty(int index)
	{
		return gNISAnimationTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B2F00
	void NISAnimationTrack::ClearProperties()
	{
		fight::FreePropertyList(&gNISAnimationTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B2F50
	// ctor stores: [('mov', 'dword', 0, '0x10e7ba54'), ('mov', 'dword', 56, '0'), ('mov', 'dword', 60, '0'), ('movss', 'dword', 32, '-1.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '1.0f'), ('movss', 'dword', 44, '0.0f'), ('movss', 'dword', 48, '0.0f'), ('movss', 'dword', 52, '-1.0f'), ('mov', 'byte', 64, '1')]
	NISAnimationTrack::NISAnimationTrack() : endFrame(-1.0f), initFrame(0.0f), speed(1.0f), startFrame(0.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0), numCycles(0), toBeContinued(1)
	{
	}

	// FUNCTION: ENGINE 0x108B2FB0
	float NISAnimationTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B2FC0
	float NISAnimationTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B2FD0
	NISAnimationTrack::~NISAnimationTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B3250
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void NISAnimationTrack::RegisterProperties()
	{
		if (gNISAnimationTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<NISAnimationTrack>("timeBegin", &NISAnimationTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<NISAnimationTrack>("timeEnd", &NISAnimationTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<NISAnimationTrack>("object", &NISAnimationTrack::SetObject);
			properties[2] = property;
			property = new fight::PropertyName<NISAnimationTrack>("animation", &NISAnimationTrack::SetAnimation);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<NISAnimationTrack>("speed", &NISAnimationTrack::SetSpeed);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<NISAnimationTrack>("initFrame", &NISAnimationTrack::SetInitFrame);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<NISAnimationTrack>("startFrame", &NISAnimationTrack::SetStartFrame);
			properties[6] = property;
			property = new fight::PropertyFloatConstRange<NISAnimationTrack>("endFrame", &NISAnimationTrack::SetEndFrame);
			properties[7] = property;
			property = new fight::PropertyEnumConstList<NISAnimationTrack>("cyclic", gNISAnimationTrackCyclicTable, 6, &NISAnimationTrack::SetCyclic);
			properties[8] = property;
			property = new fight::PropertyIntConstRange<NISAnimationTrack>("numCycles", &NISAnimationTrack::SetNumCycles);
			properties[9] = property;
			property = new fight::PropertyBool<NISAnimationTrack>("toBeContinued", &NISAnimationTrack::SetToBeContinued);
			properties[10] = property;
			fight::RegisterPropertyList(properties, &gNISAnimationTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B31C0
	fight::TrackFactory* CreateNISAnimationTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<NISAnimationTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B31E0
	void RegisterNISAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<NISAnimationTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<NISAnimationTrack>;
	template class fight::PropertyEnumConstList<NISAnimationTrack>;
	template class fight::PropertyFloatConstRange<NISAnimationTrack>;
	template class fight::PropertyIntConstRange<NISAnimationTrack>;
	template class fight::PropertyName<NISAnimationTrack>;
	template class fight::TrackFactoryTemplate<NISAnimationTrack>;
	template class fight::TrackFactoryCasterTemplate<NISAnimationTrack>;

	fight::Property** gSequenceNISNodeTrackProperties;  // 0x11318390

	// FUNCTION: ENGINE 0x108B3550
	fight::BranchHolder* SequenceNISNodeTrack::GetBranch()
	{
		return &branch;
	}

	// FUNCTION: ENGINE 0x108B3560
	bool SequenceNISNodeTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B3570
	bool SequenceNISNodeTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B3580
	bool SequenceNISNodeTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B3590
	fight::Property* SequenceNISNodeTrack::GetProperty(int index)
	{
		return gSequenceNISNodeTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B35A0
	void SequenceNISNodeTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSequenceNISNodeTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B35B0
	// ctor stores: [('mov', 'dword', 0, '0x10e7bbc4'), ('movss', 'dword', 52, '0.0f'), ('movss', 'dword', 56, '1.0f'), ('mov', 'dword', 60, '1')]
	SequenceNISNodeTrack::SequenceNISNodeTrack() : branch(0), timeBegin(0.0f), timeEnd(1.0f), priority(1)
	{
	}

	// FUNCTION: ENGINE 0x108B35F0
	float SequenceNISNodeTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B3600
	float SequenceNISNodeTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B3610
	SequenceNISNodeTrack::~SequenceNISNodeTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B3780
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SequenceNISNodeTrack::RegisterProperties()
	{
		if (gSequenceNISNodeTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyBranch<SequenceNISNodeTrack>("branch", &SequenceNISNodeTrack::GetBranch);
			properties[0] = property;
			property = new fight::PropertyIntConstRange<SequenceNISNodeTrack>("priority", &SequenceNISNodeTrack::SetPriority);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<SequenceNISNodeTrack>("timeBegin", &SequenceNISNodeTrack::SetTimeBegin);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<SequenceNISNodeTrack>("timeEnd", &SequenceNISNodeTrack::SetTimeEnd);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gSequenceNISNodeTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B3760
	fight::TrackFactory* CreateSequenceNISNodeTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SequenceNISNodeTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B3890
	void RegisterSequenceNISNodeTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SequenceNISNodeTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBranch<SequenceNISNodeTrack>;
	template class fight::PropertyFloatConstRange<SequenceNISNodeTrack>;
	template class fight::PropertyIntConstRange<SequenceNISNodeTrack>;
	template class fight::TrackFactoryTemplate<SequenceNISNodeTrack>;
	template class fight::TrackFactoryCasterTemplate<SequenceNISNodeTrack>;

	fight::Property** gLightAnimationTrackProperties;  // 0x11318394

	// FUNCTION: ENGINE 0x108B3950
	bool LightAnimationTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B3960
	bool LightAnimationTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B3970
	bool LightAnimationTrack::SetInitFrame(float newValue)
	{
		initFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B3980
	bool LightAnimationTrack::SetStartFrame(float newValue)
	{
		startFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B3990
	bool LightAnimationTrack::SetEndFrame(float newValue)
	{
		endFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B39F0
	bool LightAnimationTrack::SetAnimation(const fight::Name& newValue)
	{
		animation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B39B0
	fight::Property* LightAnimationTrack::GetProperty(int index)
	{
		return gLightAnimationTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B39C0
	void LightAnimationTrack::ClearProperties()
	{
		fight::FreePropertyList(&gLightAnimationTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B3A30
	// ctor stores: [('mov', 'dword', 0, '0x10e7bca4'), ('movss', 'dword', 24, '-1.0f'), ('movss', 'dword', 28, '0.0f'), ('movss', 'dword', 32, '0.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '-1.0f')]
	LightAnimationTrack::LightAnimationTrack() : endFrame(-1.0f), initFrame(0.0f), startFrame(0.0f), timeBegin(0.0f), timeEnd(-1.0f)
	{
	}

	// FUNCTION: ENGINE 0x108B3A70
	float LightAnimationTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B3A80
	float LightAnimationTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B3A90
	LightAnimationTrack::~LightAnimationTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B3DA0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void LightAnimationTrack::RegisterProperties()
	{
		if (gLightAnimationTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<LightAnimationTrack>("timeBegin", &LightAnimationTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<LightAnimationTrack>("timeEnd", &LightAnimationTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<LightAnimationTrack>("animation", &LightAnimationTrack::SetAnimation);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<LightAnimationTrack>("initFrame", &LightAnimationTrack::SetInitFrame);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<LightAnimationTrack>("startFrame", &LightAnimationTrack::SetStartFrame);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<LightAnimationTrack>("endFrame", &LightAnimationTrack::SetEndFrame);
			properties[5] = property;
			fight::RegisterPropertyList(properties, &gLightAnimationTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B3C80
	fight::TrackFactory* CreateLightAnimationTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<LightAnimationTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B3CC0
	void RegisterLightAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<LightAnimationTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<LightAnimationTrack>;
	template class fight::PropertyName<LightAnimationTrack>;
	template class fight::TrackFactoryTemplate<LightAnimationTrack>;
	template class fight::TrackFactoryCasterTemplate<LightAnimationTrack>;

	fight::Property** gExplicitLightAnimationTrackProperties;  // 0x11318398

	// FUNCTION: ENGINE 0x108B39A0
	bool ExplicitLightAnimationTrack::SetToBeContinued(bool newValue)
	{
		toBeContinued = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B3A10
	bool ExplicitLightAnimationTrack::SetObject(const fight::Name& newValue)
	{
		object = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B39D0
	fight::Property* ExplicitLightAnimationTrack::GetProperty(int index)
	{
		return gExplicitLightAnimationTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B39E0
	void ExplicitLightAnimationTrack::ClearProperties()
	{
		fight::FreePropertyList(&gExplicitLightAnimationTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B3AA0
	// ctor stores: [('mov', 'dword', 0, '0x10e7bcec'), ('mov', 'byte', 56, '1')]
	ExplicitLightAnimationTrack::ExplicitLightAnimationTrack() : toBeContinued(1)
	{
	}

	// FUNCTION: ENGINE 0x108B3AC0
	ExplicitLightAnimationTrack::~ExplicitLightAnimationTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B3F10
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void ExplicitLightAnimationTrack::RegisterProperties()
	{
		if (gExplicitLightAnimationTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<ExplicitLightAnimationTrack>("object", &ExplicitLightAnimationTrack::SetObject);
			properties[0] = property;
			property = new fight::PropertyBool<ExplicitLightAnimationTrack>("toBeContinued", &ExplicitLightAnimationTrack::SetToBeContinued);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<ExplicitLightAnimationTrack>("timeBegin", &engine::LightAnimationTrack::SetTimeBegin);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<ExplicitLightAnimationTrack>("timeEnd", &engine::LightAnimationTrack::SetTimeEnd);
			properties[3] = property;
			property = new fight::PropertyName<ExplicitLightAnimationTrack>("animation", &engine::LightAnimationTrack::SetAnimation);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<ExplicitLightAnimationTrack>("initFrame", &engine::LightAnimationTrack::SetInitFrame);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<ExplicitLightAnimationTrack>("startFrame", &engine::LightAnimationTrack::SetStartFrame);
			properties[6] = property;
			property = new fight::PropertyFloatConstRange<ExplicitLightAnimationTrack>("endFrame", &engine::LightAnimationTrack::SetEndFrame);
			properties[7] = property;
			fight::RegisterPropertyList(properties, &gExplicitLightAnimationTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B3CA0
	fight::TrackFactory* CreateExplicitLightAnimationTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<ExplicitLightAnimationTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B3CF0
	void RegisterExplicitLightAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<ExplicitLightAnimationTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<ExplicitLightAnimationTrack>;
	template class fight::PropertyFloatConstRange<ExplicitLightAnimationTrack>;
	template class fight::PropertyName<ExplicitLightAnimationTrack>;
	template class fight::TrackFactoryTemplate<ExplicitLightAnimationTrack>;
	template class fight::TrackFactoryCasterTemplate<ExplicitLightAnimationTrack>;

	fight::Property** gCameraClippingPlanesTrackProperties;  // 0x1131839C

	// FUNCTION: ENGINE 0x108B4200
	bool CameraClippingPlanesTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4210
	bool CameraClippingPlanesTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4220
	bool CameraClippingPlanesTrack::SetNearPlane(float newValue)
	{
		nearPlane = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4230
	bool CameraClippingPlanesTrack::SetFarPlane(float newValue)
	{
		farPlane = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4240
	bool CameraClippingPlanesTrack::SetRestoreAtEnd(bool newValue)
	{
		restoreAtEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4250
	fight::Property* CameraClippingPlanesTrack::GetProperty(int index)
	{
		return gCameraClippingPlanesTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B4260
	void CameraClippingPlanesTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCameraClippingPlanesTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B4270
	// ctor stores: [('movss', 'dword', 16, '1000.0f'), ('movss', 'dword', 20, '0.10000000149011612f'), ('movss', 'dword', 24, '0.0f'), ('mov', 'byte', 32, '1'), ('mov', 'dword', 12, '1'), ('mov', 'dword', 0, '0x10e7be34'), ('movss', 'dword', 28, '1.0f')]
	CameraClippingPlanesTrack::CameraClippingPlanesTrack() : farPlane(1000.0f), nearPlane(0.10000000149011612f), timeBegin(0.0f), timeEnd(1.0f), restoreAtEnd(1)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108B42C0
	float CameraClippingPlanesTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B42D0
	float CameraClippingPlanesTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B42E0
	CameraClippingPlanesTrack::~CameraClippingPlanesTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B4410
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void CameraClippingPlanesTrack::RegisterProperties()
	{
		if (gCameraClippingPlanesTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CameraClippingPlanesTrack>("timeBegin", &CameraClippingPlanesTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<CameraClippingPlanesTrack>("timeEnd", &CameraClippingPlanesTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<CameraClippingPlanesTrack>("nearPlane", &CameraClippingPlanesTrack::SetNearPlane);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<CameraClippingPlanesTrack>("farPlane", &CameraClippingPlanesTrack::SetFarPlane);
			properties[3] = property;
			property = new fight::PropertyBool<CameraClippingPlanesTrack>("restoreAtEnd", &CameraClippingPlanesTrack::SetRestoreAtEnd);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gCameraClippingPlanesTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B43F0
	fight::TrackFactory* CreateCameraClippingPlanesTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CameraClippingPlanesTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B4550
	void RegisterCameraClippingPlanesTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CameraClippingPlanesTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<CameraClippingPlanesTrack>;
	template class fight::PropertyFloatConstRange<CameraClippingPlanesTrack>;
	template class fight::TrackFactoryTemplate<CameraClippingPlanesTrack>;
	template class fight::TrackFactoryCasterTemplate<CameraClippingPlanesTrack>;

	extern fight::EnumEntry gCameraAnimationTrackCyclicTable[];

	fight::Property** gCameraAnimationTrackProperties;  // 0x113183A0

	// FUNCTION: ENGINE 0x108B4610
	bool CameraAnimationTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4620
	bool CameraAnimationTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4630
	bool CameraAnimationTrack::SetInitFrame(float newValue)
	{
		initFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4640
	bool CameraAnimationTrack::SetStartFrame(float newValue)
	{
		startFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4650
	bool CameraAnimationTrack::SetEndFrame(float newValue)
	{
		endFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4660
	bool CameraAnimationTrack::SetCyclic(int newValue)
	{
		cyclic = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4690
	bool CameraAnimationTrack::SetAnimation(const fight::Name& newValue)
	{
		animation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4670
	fight::Property* CameraAnimationTrack::GetProperty(int index)
	{
		return gCameraAnimationTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B4680
	void CameraAnimationTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCameraAnimationTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B46B0
	// ctor stores: [('mov', 'dword', 0, '0x10e7bf04'), ('movss', 'dword', 24, '-1.0f'), ('movss', 'dword', 28, '0.0f'), ('movss', 'dword', 32, '0.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '-1.0f'), ('mov', 'dword', 44, '0')]
	CameraAnimationTrack::CameraAnimationTrack() : endFrame(-1.0f), initFrame(0.0f), startFrame(0.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0)
	{
	}

	// FUNCTION: ENGINE 0x108B4700
	float CameraAnimationTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B4710
	float CameraAnimationTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B4720
	CameraAnimationTrack::~CameraAnimationTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B4900
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void CameraAnimationTrack::RegisterProperties()
	{
		if (gCameraAnimationTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CameraAnimationTrack>("timeBegin", &CameraAnimationTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<CameraAnimationTrack>("timeEnd", &CameraAnimationTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<CameraAnimationTrack>("animation", &CameraAnimationTrack::SetAnimation);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<CameraAnimationTrack>("initFrame", &CameraAnimationTrack::SetInitFrame);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<CameraAnimationTrack>("startFrame", &CameraAnimationTrack::SetStartFrame);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<CameraAnimationTrack>("endFrame", &CameraAnimationTrack::SetEndFrame);
			properties[5] = property;
			property = new fight::PropertyEnumConstList<CameraAnimationTrack>("cyclic", gCameraAnimationTrackCyclicTable, 4, &CameraAnimationTrack::SetCyclic);
			properties[6] = property;
			fight::RegisterPropertyList(properties, &gCameraAnimationTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B4870
	fight::TrackFactory* CreateCameraAnimationTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CameraAnimationTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B4890
	void RegisterCameraAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CameraAnimationTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<CameraAnimationTrack>;
	template class fight::PropertyFloatConstRange<CameraAnimationTrack>;
	template class fight::PropertyName<CameraAnimationTrack>;
	template class fight::TrackFactoryTemplate<CameraAnimationTrack>;
	template class fight::TrackFactoryCasterTemplate<CameraAnimationTrack>;

	fight::Property** gSwapDrawableTrackProperties;  // 0x113183C8

	// FUNCTION: ENGINE 0x108B4B40
	bool SwapDrawableTrack::SetPersistent(bool newValue)
	{
		persistent = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4B70
	bool SwapDrawableTrack::SetObjectName(const fight::Name& newValue)
	{
		objectName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4B90
	bool SwapDrawableTrack::SetDrawableName(const fight::Name& newValue)
	{
		drawableName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4B50
	fight::Property* SwapDrawableTrack::GetProperty(int index)
	{
		return gSwapDrawableTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B4B60
	void SwapDrawableTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSwapDrawableTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B4BB0
	// ctor stores: [('mov', 'dword', 0, '0x10e7bfec'), ('mov', 'byte', 32, '0'), ('mov', 'dword', 12, '1')]
	SwapDrawableTrack::SwapDrawableTrack() : persistent(false)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108B4BE0
	float SwapDrawableTrack::GetTimeBegin() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108B4BF0
	float SwapDrawableTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108B4C00
	SwapDrawableTrack::~SwapDrawableTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B4D50
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SwapDrawableTrack::RegisterProperties()
	{
		if (gSwapDrawableTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<SwapDrawableTrack>("objectName", &SwapDrawableTrack::SetObjectName);
			properties[0] = property;
			property = new fight::PropertyName<SwapDrawableTrack>("drawableName", &SwapDrawableTrack::SetDrawableName);
			properties[1] = property;
			property = new fight::PropertyBool<SwapDrawableTrack>("persistent", &SwapDrawableTrack::SetPersistent);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gSwapDrawableTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B4CC0
	fight::TrackFactory* CreateSwapDrawableTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SwapDrawableTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B4CE0
	void RegisterSwapDrawableTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SwapDrawableTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<SwapDrawableTrack>;
	template class fight::PropertyName<SwapDrawableTrack>;
	template class fight::TrackFactoryTemplate<SwapDrawableTrack>;
	template class fight::TrackFactoryCasterTemplate<SwapDrawableTrack>;

	fight::Property** gTimeDilationTrackProperties;  // 0x113183CC

	// FUNCTION: ENGINE 0x108B4EC0
	bool TimeDilationTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4ED0
	bool TimeDilationTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4EE0
	bool TimeDilationTrack::SetSimulationRate(float newValue)
	{
		simulationRate = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B4EF0
	fight::Property* TimeDilationTrack::GetProperty(int index)
	{
		return gTimeDilationTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B4F00
	void TimeDilationTrack::ClearProperties()
	{
		fight::FreePropertyList(&gTimeDilationTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B4F10
	// ctor stores: [('mov', 'dword', 0, '0x10e7c0ac'), ('movss', 'dword', 16, '1.0f'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '1.0f')]
	TimeDilationTrack::TimeDilationTrack() : simulationRate(1.0f), timeBegin(0.0f), timeEnd(1.0f)
	{
	}

	// FUNCTION: ENGINE 0x108B4F40
	float TimeDilationTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B4F50
	float TimeDilationTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B4F60
	TimeDilationTrack::~TimeDilationTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B5040
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void TimeDilationTrack::RegisterProperties()
	{
		if (gTimeDilationTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<TimeDilationTrack>("timeBegin", &TimeDilationTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<TimeDilationTrack>("timeEnd", &TimeDilationTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<TimeDilationTrack>("simulationRate", &TimeDilationTrack::SetSimulationRate);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gTimeDilationTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B5020
	fight::TrackFactory* CreateTimeDilationTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<TimeDilationTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B5120
	void RegisterTimeDilationTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<TimeDilationTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<TimeDilationTrack>;
	template class fight::TrackFactoryTemplate<TimeDilationTrack>;
	template class fight::TrackFactoryCasterTemplate<TimeDilationTrack>;

}
