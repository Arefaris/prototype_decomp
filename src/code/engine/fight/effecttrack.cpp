// The effect track of the fight tree and the accessors of the effect it plays (see effecttrack.h).
#include "code/engine/fight/effecttrack.h"

namespace engine
{
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
	// NONMATCHING: the engine stores the -1 into the member at +0x38 between the other member stores, ours sinks it
	// past the argument setup of the trailing call (92.6 %; the two statements and the member-init list both give it)
#ifdef NONMATCHING
	EffectAction::EffectAction(EffectTrack* newTrack, fight::Track* listener, int object, core::IRefCount* effect, int mode)
		: fight::Action(0xE00), link(newTrack), watch(listener), unknown34(mode), unknown38(-1), unknown3c(0),
		  unknown40(object), unknown44(0), unknown48(0xffff), unknown4c(false)
	{
		AssignEffectRef(unknown44, effect);
	}
#endif

	// FUNCTION: ENGINE 0x10807550
	AbortEffectAction::AbortEffectAction(AbortEffectTrack* newTrack, fight::Track* listener)
		: fight::Action(0xE00), link(newTrack)
	{
		(void)listener;
	}

	// FUNCTION: ENGINE 0x10807700
	// NONMATCHING: the engine stores the -1 into the member at +0x34 before the parameter store, ours puts the
	// parameter store right after its load and sinks the -1 into the epilogue (90.8 %)
#ifdef NONMATCHING
	MotionTrailAction::MotionTrailAction(EffectTrack* newTrack, fight::Track* listener, int value)
		: fight::Action(0xE00), link(newTrack), watch(listener), unknown34(-1), unknown38(value)
	{
	}
#endif

	// FUNCTION: ENGINE 0x10805B10
	AbortEffectAction::~AbortEffectAction()
	{
	}

	// FUNCTION: ENGINE 0x10805B40
	EffectAction::~EffectAction()
	{
		ReleaseEffectRef(unknown44);
		ReleaseEffectRef(unknown3c);
	}

	// FUNCTION: ENGINE 0x10805CF0
	MotionTrailAction::~MotionTrailAction()
	{
	}

	// ---- the effect --------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x10805550
	math::Vector Effect::GetVector98() const
	{
		return vectors50[6];
	}

	// FUNCTION: ENGINE 0x10805580
	int Effect::GetC8() const
	{
		return unknownc8;
	}

	// FUNCTION: ENGINE 0x10805590
	unsigned char* Effect::GetHandle10()
	{
		return unknown10;
	}

	// FUNCTION: ENGINE 0x108055A0
	math::Vector Effect::GetVector50() const
	{
		return vectors50[0];
	}

	// FUNCTION: ENGINE 0x108055C0
	unsigned char* Effect::GetHandle18()
	{
		return unknown18;
	}

	// FUNCTION: ENGINE 0x108055D0
	math::Vector Effect::GetVector5c() const
	{
		return vectors50[1];
	}

	// FUNCTION: ENGINE 0x108055F0
	unsigned char* Effect::GetHandle20()
	{
		return unknown20;
	}

	// FUNCTION: ENGINE 0x10805600
	math::Vector Effect::GetVector68() const
	{
		return vectors50[2];
	}

	// FUNCTION: ENGINE 0x10805620
	unsigned char* Effect::GetHandle28()
	{
		return unknown28;
	}

	// FUNCTION: ENGINE 0x10805630
	math::Vector Effect::GetVector74() const
	{
		return vectors50[3];
	}

	// FUNCTION: ENGINE 0x10805650
	unsigned char* Effect::GetHandle30()
	{
		return unknown30;
	}

	// FUNCTION: ENGINE 0x10805660
	math::Vector Effect::GetVector80() const
	{
		return vectors50[4];
	}

	// FUNCTION: ENGINE 0x10805690
	unsigned char* Effect::GetHandle38()
	{
		return unknown38;
	}

	// FUNCTION: ENGINE 0x108056A0
	math::Vector Effect::GetVector8c() const
	{
		return vectors50[5];
	}

	// FUNCTION: ENGINE 0x108056D0
	bool Effect::GetD0() const
	{
		return unknownd0;
	}

	// ---- the track --------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x10804EE0
	// NONMATCHING: the engine loads the member into ecx and the out pointer into eax, ours the other way round
#ifdef NONMATCHING
	void EffectTrack::GetUnknown14(int& value) const
	{
		value = unknown14;
	}
#endif

	// FUNCTION: ENGINE 0x10804EF0
	int* EffectTrack::GetUnknown10()
	{
		return &unknown10;
	}

	// FUNCTION: ENGINE 0x10804F00
	bool EffectTrack::GetUnknown24() const
	{
		return unknown24;
	}

	// FUNCTION: ENGINE 0x10804F10
	float EffectTrack::GetUnknown18x() const
	{
		return unknown18.x;
	}

	// FUNCTION: ENGINE 0x10804F20
	float EffectTrack::GetUnknown190() const
	{
		return unknown190;
	}

	// FUNCTION: ENGINE 0x10804F30
	unsigned char* EffectTrack::GetUnknown30()
	{
		return unknown30;
	}

	// FUNCTION: ENGINE 0x10804F40
	unsigned char* EffectTrack::GetUnknown40()
	{
		return unknown40;
	}

	// FUNCTION: ENGINE 0x10804F50
	int EffectTrack::GetUnknown1a4() const
	{
		return unknown1a4;
	}

	// FUNCTION: ENGINE 0x10804F60
	unsigned char* EffectTrack::GetUnknown38()
	{
		return unknown38;
	}

	// FUNCTION: ENGINE 0x10804F70
	math::Vector EffectTrack::GetUnknown6c() const
	{
		return unknown6c;
	}

	// FUNCTION: ENGINE 0x10804F90
	math::Vector EffectTrack::GetUnknown78() const
	{
		return unknown78;
	}

	// FUNCTION: ENGINE 0x10804FB0
	int EffectTrack::GetUnknown194() const
	{
		return unknown194;
	}

	// FUNCTION: ENGINE 0x10804FC0
	math::Vector* EffectTrack::GetUnknown18()
	{
		return &unknown18;
	}

	// FUNCTION: ENGINE 0x10804FD0
	bool EffectTrack::GetUnknown1a8() const
	{
		return unknown1a8;
	}

	// FUNCTION: ENGINE 0x10804FE0
	unsigned char* EffectTrack::GetUnknown48()
	{
		return unknown48;
	}

	// FUNCTION: ENGINE 0x10804FF0
	float EffectTrack::GetUnknown88() const
	{
		return unknown88;
	}

	// FUNCTION: ENGINE 0x10805000
	float EffectTrack::GetUnknown110() const
	{
		return unknown110;
	}

	// FUNCTION: ENGINE 0x10805010
	int EffectTrack::GetUnknown1a0() const
	{
		return unknown1a0;
	}

	// FUNCTION: ENGINE 0x10805020
	float EffectTrack::GetUnknown188() const
	{
		return unknown188;
	}

	// FUNCTION: ENGINE 0x10805030
	bool EffectTrack::GetUnknown1aa() const
	{
		return unknown1aa;
	}

	// FUNCTION: ENGINE 0x10805040
	float EffectTrack::GetUnknown184() const
	{
		return unknown184;
	}

	// FUNCTION: ENGINE 0x10805050
	float EffectTrack::GetUnknown114() const
	{
		return unknown114;
	}

	// FUNCTION: ENGINE 0x10805060
	float EffectTrack::GetUnknown180() const
	{
		return unknown180;
	}

	// FUNCTION: ENGINE 0x10805070
	bool EffectTrack::GetUnknown1ad() const
	{
		return unknown1ad;
	}

	// FUNCTION: ENGINE 0x10805080
	float* EffectTrack::GetUnknown20()
	{
		return &unknown18.z;
	}

	// FUNCTION: ENGINE 0x10805090
	bool EffectTrack::GetUnknown1a9() const
	{
		return unknown1a9;
	}

	// FUNCTION: ENGINE 0x108050A0
	float EffectTrack::GetUnknownc0() const
	{
		return unknownc0;
	}

	// FUNCTION: ENGINE 0x108050B0
	float EffectTrack::GetUnknownc4() const
	{
		return unknownc4;
	}

	// FUNCTION: ENGINE 0x108050C0
	int EffectTrack::GetUnknown198() const
	{
		return unknown198;
	}

	// FUNCTION: ENGINE 0x108050D0
	float EffectTrack::GetUnknowne4() const
	{
		return unknowne4;
	}

	// FUNCTION: ENGINE 0x108050E0
	float EffectTrack::GetUnknowne8() const
	{
		return unknowne8;
	}

	// FUNCTION: ENGINE 0x108050F0
	float EffectTrack::GetUnknownf8() const
	{
		return unknownf8;
	}

	// FUNCTION: ENGINE 0x10805100
	float EffectTrack::GetUnknownfc() const
	{
		return unknownfc;
	}

	// FUNCTION: ENGINE 0x10805110
	float EffectTrack::GetUnknownec() const
	{
		return unknownec;
	}

	// FUNCTION: ENGINE 0x10805120
	float EffectTrack::GetUnknownf4() const
	{
		return unknownf4;
	}

	// FUNCTION: ENGINE 0x10805130
	float EffectTrack::GetUnknownf0() const
	{
		return unknownf0;
	}

	// FUNCTION: ENGINE 0x10805140
	int EffectTrack::GetUnknown19c() const
	{
		return unknown19c;
	}

	// FUNCTION: ENGINE 0x10805150
	float EffectTrack::GetUnknown100() const
	{
		return unknown100;
	}

	// FUNCTION: ENGINE 0x10805160
	float EffectTrack::GetUnknown104() const
	{
		return unknown104;
	}

	// FUNCTION: ENGINE 0x10805170
	float EffectTrack::GetUnknown108() const
	{
		return unknown108;
	}

	// FUNCTION: ENGINE 0x10805180
	float EffectTrack::GetUnknown10c() const
	{
		return unknown10c;
	}

	// FUNCTION: ENGINE 0x10805190
	float EffectTrack::GetUnknown98() const
	{
		return unknown98;
	}

	// FUNCTION: ENGINE 0x108051A0
	float EffectTrack::GetUnknown9c() const
	{
		return unknown9c;
	}

	// FUNCTION: ENGINE 0x108051B0
	float EffectTrack::GetUnknowne0() const
	{
		return unknowne0;
	}

	// FUNCTION: ENGINE 0x108051C0
	float EffectTrack::GetUnknownbc() const
	{
		return unknownbc;
	}

	// FUNCTION: ENGINE 0x108051D0
	float EffectTrack::GetUnknownb4() const
	{
		return unknownb4;
	}

	// FUNCTION: ENGINE 0x108051E0
	float EffectTrack::GetUnknowna4() const
	{
		return unknowna4;
	}

	// FUNCTION: ENGINE 0x108051F0
	float EffectTrack::GetUnknowna0() const
	{
		return unknowna0;
	}

	// FUNCTION: ENGINE 0x10805200
	float EffectTrack::GetUnknown8c() const
	{
		return unknown8c;
	}

	// FUNCTION: ENGINE 0x10805210
	float EffectTrack::GetUnknownb0() const
	{
		return unknownb0;
	}

	// FUNCTION: ENGINE 0x10805220
	float EffectTrack::GetUnknownac() const
	{
		return unknownac;
	}

	// FUNCTION: ENGINE 0x10805230
	float EffectTrack::GetUnknowna8() const
	{
		return unknowna8;
	}

	// FUNCTION: ENGINE 0x10805240
	float EffectTrack::GetUnknown90() const
	{
		return unknown90;
	}

	// FUNCTION: ENGINE 0x10805250
	float EffectTrack::GetUnknownb8() const
	{
		return unknownb8;
	}

	// FUNCTION: ENGINE 0x10805260
	float EffectTrack::GetUnknown94() const
	{
		return unknown94;
	}

	// FUNCTION: ENGINE 0x10805270
	float EffectTrack::GetUnknownd4() const
	{
		return unknownd4;
	}

	// FUNCTION: ENGINE 0x10805280
	float EffectTrack::GetUnknownd0() const
	{
		return unknownd0;
	}

	// FUNCTION: ENGINE 0x10805290
	float EffectTrack::GetUnknowncc() const
	{
		return unknowncc;
	}

	// FUNCTION: ENGINE 0x108052A0
	float EffectTrack::GetUnknownd8() const
	{
		return unknownd8;
	}

	// FUNCTION: ENGINE 0x108052B0
	float EffectTrack::GetUnknowndc() const
	{
		return unknowndc;
	}

	// FUNCTION: ENGINE 0x108052C0
	float EffectTrack::GetUnknownc8() const
	{
		return unknownc8;
	}
}
