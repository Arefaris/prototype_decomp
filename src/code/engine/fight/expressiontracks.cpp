// The fight tracks that switch motion tracked expressions, play expression animations, lock joints, move puppets and make an object undamageable (unit 0x108B72A0 - 0x108B8CE0; no assert path, file name guessed).
#include "code/engine/fight/expressiontracks.h"

namespace engine
{
	namespace animation
	{
		fight::Property** gDisableMotionTrackedExpressionTrackProperties;  // 0x1131842C

		// FUNCTION: ENGINE 0x108B7260
		bool DisableMotionTrackedExpressionTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7270
		bool DisableMotionTrackedExpressionTrack::SetBlendDuration(float newValue)
		{
			blendDuration = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B72A0
		fight::Property* DisableMotionTrackedExpressionTrack::GetProperty(int index)
		{
			return gDisableMotionTrackedExpressionTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x108B72B0
		void DisableMotionTrackedExpressionTrack::ClearProperties()
		{
			fight::FreePropertyList(&gDisableMotionTrackedExpressionTrackProperties);
		}

		// FUNCTION: ENGINE 0x108B72C0
		// ctor stores: [('mov', 'dword', 0, '0x10e7c91c'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f'), ('mov', 'dword', 12, '1')]
		DisableMotionTrackedExpressionTrack::DisableMotionTrackedExpressionTrack() : blendDuration(0.0f), timeBegin(0.0f)
		{
			unknownC = 1;  // TODO base member
		}

		// FUNCTION: ENGINE 0x108B72F0
		float DisableMotionTrackedExpressionTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108B7300
		float DisableMotionTrackedExpressionTrack::Slot10() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x108B7310
		DisableMotionTrackedExpressionTrack::~DisableMotionTrackedExpressionTrack()
		{
		}

		// FUNCTION: ENGINE 0x108B7540
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void DisableMotionTrackedExpressionTrack::RegisterProperties()
		{
			if (gDisableMotionTrackedExpressionTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<DisableMotionTrackedExpressionTrack>("timeBegin", &DisableMotionTrackedExpressionTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<DisableMotionTrackedExpressionTrack>("blendDuration", &DisableMotionTrackedExpressionTrack::SetBlendDuration);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gDisableMotionTrackedExpressionTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108B7500
		fight::TrackFactory* CreateDisableMotionTrackedExpressionTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<DisableMotionTrackedExpressionTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108B76A0
		void RegisterDisableMotionTrackedExpressionTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<DisableMotionTrackedExpressionTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyFloatConstRange<DisableMotionTrackedExpressionTrack>;
		template class fight::TrackFactoryTemplate<DisableMotionTrackedExpressionTrack>;
		template class fight::TrackFactoryCasterTemplate<DisableMotionTrackedExpressionTrack>;
	}

	namespace animation
	{
		fight::Property** gEnableMotionTrackedExpressionTrackProperties;  // 0x11318430

		// FUNCTION: ENGINE 0x108B7280
		bool EnableMotionTrackedExpressionTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7290
		bool EnableMotionTrackedExpressionTrack::SetBlendDuration(float newValue)
		{
			blendDuration = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7320
		fight::Property* EnableMotionTrackedExpressionTrack::GetProperty(int index)
		{
			return gEnableMotionTrackedExpressionTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x108B7330
		void EnableMotionTrackedExpressionTrack::ClearProperties()
		{
			fight::FreePropertyList(&gEnableMotionTrackedExpressionTrackProperties);
		}

		// FUNCTION: ENGINE 0x108B7340
		// ctor stores: [('mov', 'dword', 0, '0x10e7c964'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f'), ('mov', 'dword', 12, '1')]
		EnableMotionTrackedExpressionTrack::EnableMotionTrackedExpressionTrack() : blendDuration(0.0f), timeBegin(0.0f)
		{
			unknownC = 1;  // TODO base member
		}

		// FUNCTION: ENGINE 0x108B7370
		float EnableMotionTrackedExpressionTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108B7380
		float EnableMotionTrackedExpressionTrack::Slot10() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x108B7390
		EnableMotionTrackedExpressionTrack::~EnableMotionTrackedExpressionTrack()
		{
		}

		// FUNCTION: ENGINE 0x108B75F0
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void EnableMotionTrackedExpressionTrack::RegisterProperties()
		{
			if (gEnableMotionTrackedExpressionTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<EnableMotionTrackedExpressionTrack>("timeBegin", &EnableMotionTrackedExpressionTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<EnableMotionTrackedExpressionTrack>("blendDuration", &EnableMotionTrackedExpressionTrack::SetBlendDuration);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gEnableMotionTrackedExpressionTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108B7520
		fight::TrackFactory* CreateEnableMotionTrackedExpressionTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<EnableMotionTrackedExpressionTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108B76D0
		void RegisterEnableMotionTrackedExpressionTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<EnableMotionTrackedExpressionTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyFloatConstRange<EnableMotionTrackedExpressionTrack>;
		template class fight::TrackFactoryTemplate<EnableMotionTrackedExpressionTrack>;
		template class fight::TrackFactoryCasterTemplate<EnableMotionTrackedExpressionTrack>;
	}

	namespace animation
	{
		extern fight::EnumEntry gExpressionAnimationTrackCyclicTable[];

		fight::Property** gExpressionAnimationTrackProperties;  // 0x11318438

		// FUNCTION: ENGINE 0x108B7820
		bool ExpressionAnimationTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7830
		bool ExpressionAnimationTrack::SetTimeEnd(float newValue)
		{
			timeEnd = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7840
		bool ExpressionAnimationTrack::SetSpeed(float newValue)
		{
			speed = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7850
		bool ExpressionAnimationTrack::SetInitFrame(float newValue)
		{
			initFrame = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7860
		bool ExpressionAnimationTrack::SetStartFrame(float newValue)
		{
			startFrame = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7870
		bool ExpressionAnimationTrack::SetEndFrame(float newValue)
		{
			endFrame = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7880
		bool ExpressionAnimationTrack::SetCyclic(int newValue)
		{
			cyclic = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B78B0
		bool ExpressionAnimationTrack::SetAnimation(const fight::Name& newValue)
		{
			animation = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7890
		fight::Property* ExpressionAnimationTrack::GetProperty(int index)
		{
			return gExpressionAnimationTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x108B78A0
		void ExpressionAnimationTrack::ClearProperties()
		{
			fight::FreePropertyList(&gExpressionAnimationTrackProperties);
		}

		// FUNCTION: ENGINE 0x108B78D0
		// ctor stores: [('mov', 'dword', 0, '0x10e7ca3c'), ('movss', 'dword', 24, '-1.0f'), ('movss', 'dword', 28, '0.0f'), ('movss', 'dword', 32, '1.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '0.0f'), ('movss', 'dword', 44, '-1.0f'), ('mov', 'dword', 48, '0')]
		ExpressionAnimationTrack::ExpressionAnimationTrack() : endFrame(-1.0f), initFrame(0.0f), speed(1.0f), startFrame(0.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0)
		{
		}

		// FUNCTION: ENGINE 0x108B7930
		float ExpressionAnimationTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108B7940
		float ExpressionAnimationTrack::Slot10() const
		{
			return -1.0f;
		}

		// FUNCTION: ENGINE 0x108B7950
		ExpressionAnimationTrack::~ExpressionAnimationTrack()
		{
		}

		// FUNCTION: ENGINE 0x108B7B30
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void ExpressionAnimationTrack::RegisterProperties()
		{
			if (gExpressionAnimationTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<ExpressionAnimationTrack>("timeBegin", &ExpressionAnimationTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<ExpressionAnimationTrack>("timeEnd", &ExpressionAnimationTrack::SetTimeEnd);
				properties[1] = property;
				property = new fight::PropertyName<ExpressionAnimationTrack>("animation", &ExpressionAnimationTrack::SetAnimation);
				properties[2] = property;
				property = new fight::PropertyFloatConstRange<ExpressionAnimationTrack>("speed", &ExpressionAnimationTrack::SetSpeed);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<ExpressionAnimationTrack>("initFrame", &ExpressionAnimationTrack::SetInitFrame);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<ExpressionAnimationTrack>("startFrame", &ExpressionAnimationTrack::SetStartFrame);
				properties[5] = property;
				property = new fight::PropertyFloatConstRange<ExpressionAnimationTrack>("endFrame", &ExpressionAnimationTrack::SetEndFrame);
				properties[6] = property;
				property = new fight::PropertyEnumConstList<ExpressionAnimationTrack>("cyclic", gExpressionAnimationTrackCyclicTable, 4, &ExpressionAnimationTrack::SetCyclic);
				properties[7] = property;
				fight::RegisterPropertyList(properties, &gExpressionAnimationTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108B7AA0
		fight::TrackFactory* CreateExpressionAnimationTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<ExpressionAnimationTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108B7AC0
		void RegisterExpressionAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<ExpressionAnimationTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyEnumConstList<ExpressionAnimationTrack>;
		template class fight::PropertyFloatConstRange<ExpressionAnimationTrack>;
		template class fight::PropertyName<ExpressionAnimationTrack>;
		template class fight::TrackFactoryTemplate<ExpressionAnimationTrack>;
		template class fight::TrackFactoryCasterTemplate<ExpressionAnimationTrack>;
	}

	namespace animation
	{
		extern fight::EnumEntry gJointLockTrackTranslationLockTable[];

		fight::Property** gJointLockTrackProperties;  // 0x11318460

		// FUNCTION: ENGINE 0x108B7E40
		bool JointLockTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7E50
		bool JointLockTrack::SetTimeEnd(float newValue)
		{
			timeEnd = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7E60
		bool JointLockTrack::SetTranslationLock(int newValue)
		{
			translationLock = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7E70
		bool JointLockTrack::SetOffsetTranslation(const math::Vector& newValue)
		{
			offsetTranslation.x = newValue.x;
			offsetTranslation.y = newValue.y;
			offsetTranslation.z = newValue.z;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7E90
		bool JointLockTrack::SetOffsetOrientation(const math::Vector& newValue)
		{
			// Degrees in the property, radians in the track
			math::Vector v(newValue.x, newValue.y, newValue.z);
			v.Scale(0.01745329238474369f);
			offsetOrientation.x = v.x;
			offsetOrientation.y = v.y;
			offsetOrientation.z = v.z;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7ED0
		bool JointLockTrack::SetAutoUpdate(bool newValue)
		{
			autoUpdate = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7EE0
		bool JointLockTrack::SetPriority(int newValue)
		{
			priority = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7EF0
		bool JointLockTrack::SetBlendInTime(float newValue)
		{
			blendInTime = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7F00
		bool JointLockTrack::SetBlendOutTime(float newValue)
		{
			blendOutTime = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B8040
		bool JointLockTrack::SetLockedJoint(const fight::Name& newValue)
		{
			lockedJoint = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7F80
		fight::Property* JointLockTrack::GetProperty(int index)
		{
			return gJointLockTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x108B7F90
		void JointLockTrack::ClearProperties()
		{
			fight::FreePropertyList(&gJointLockTrackProperties);
		}

		// FUNCTION: ENGINE 0x108B8060
		// ctor stores: [('mov', 'dword', 0, '0x10e7cc4c'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f'), ('movss', 'dword', 32, '0.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '0.0f'), ('movss', 'dword', 44, '0.0f'), ('movss', 'dword', 48, '0.0f'), ('movss', 'dword', 52, '0.0f'), ('movss', 'dword', 56, '0.0f'), ('mov', 'dword', 64, '0'), ('mov', 'dword', 68, '0'), ('movss', 'dword', 60, '-1.0f'), ('mov', 'byte', 72, '1')]
		JointLockTrack::JointLockTrack() : offsetOrientation(0.0f, 0.0f, 0.0f), offsetTranslation(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), translationLock(0), autoUpdate(1)
		{
		}

		// FUNCTION: ENGINE 0x108B80D0
		float JointLockTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108B80E0
		float JointLockTrack::Slot10() const
		{
			return timeEnd - timeBegin;
		}

		// FUNCTION: ENGINE 0x108B80F0
		JointLockTrack::~JointLockTrack()
		{
		}

		// FUNCTION: ENGINE 0x108B8730
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void JointLockTrack::RegisterProperties()
		{
			if (gJointLockTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<JointLockTrack>("timeBegin", &JointLockTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<JointLockTrack>("timeEnd", &JointLockTrack::SetTimeEnd);
				properties[1] = property;
				property = new fight::PropertyNameList<JointLockTrack>("lockedJoint", &JointLockTrack::SetLockedJoint);
				properties[2] = property;
				property = new fight::PropertyEnumConstList<JointLockTrack>("translationLock", gJointLockTrackTranslationLockTable, 4, &JointLockTrack::SetTranslationLock);
				properties[3] = property;
				property = new fight::PropertyVector<JointLockTrack>("offsetTranslation", &JointLockTrack::SetOffsetTranslation);
				properties[4] = property;
				property = new fight::PropertyVector<JointLockTrack>("offsetOrientation", &JointLockTrack::SetOffsetOrientation);
				properties[5] = property;
				property = new fight::PropertyBool<JointLockTrack>("autoUpdate", &JointLockTrack::SetAutoUpdate);
				properties[6] = property;
				property = new fight::PropertyIntConstRange<JointLockTrack>("priority", &JointLockTrack::SetPriority);
				properties[7] = property;
				property = new fight::PropertyFloatConstRange<JointLockTrack>("blendInTime", &JointLockTrack::SetBlendInTime);
				properties[8] = property;
				property = new fight::PropertyFloatConstRange<JointLockTrack>("blendOutTime", &JointLockTrack::SetBlendOutTime);
				properties[9] = property;
				fight::RegisterPropertyList(properties, &gJointLockTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108B8480
		fight::TrackFactory* CreateJointLockTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<JointLockTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108B8630
		void RegisterJointLockTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<JointLockTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyBool<JointLockTrack>;
		template class fight::PropertyEnumConstList<JointLockTrack>;
		template class fight::PropertyFloatConstRange<JointLockTrack>;
		template class fight::PropertyIntConstRange<JointLockTrack>;
		template class fight::PropertyNameList<JointLockTrack>;
		template class fight::PropertyVector<JointLockTrack>;
		template class fight::TrackFactoryTemplate<JointLockTrack>;
		template class fight::TrackFactoryCasterTemplate<JointLockTrack>;
	}

	namespace animation
	{
		fight::Property** gPuppetMoveTrackProperties;  // 0x11318464

		// FUNCTION: ENGINE 0x108B7F10
		bool PuppetMoveTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7F20
		bool PuppetMoveTrack::SetTimeEnd(float newValue)
		{
			timeEnd = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7F30
		bool PuppetMoveTrack::SetDistance(const math::Vector& newValue)
		{
			distance.x = newValue.x;
			distance.y = newValue.y;
			distance.z = newValue.z;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7F50
		bool PuppetMoveTrack::SetPriority(int newValue)
		{
			priority = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7F60
		bool PuppetMoveTrack::SetBlendInTime(float newValue)
		{
			blendInTime = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7F70
		bool PuppetMoveTrack::SetBlendOutTime(float newValue)
		{
			blendOutTime = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B7FA0
		fight::Property* PuppetMoveTrack::GetProperty(int index)
		{
			return gPuppetMoveTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x108B7FB0
		void PuppetMoveTrack::ClearProperties()
		{
			fight::FreePropertyList(&gPuppetMoveTrackProperties);
		}

		// FUNCTION: ENGINE 0x108B7FC0
		// ctor stores: [('mov', 'dword', 0, '0x10e7cc04'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f'), ('movss', 'dword', 32, '0.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '1.0f'), ('mov', 'dword', 44, '0xffffffff'), ('mov', 'dword', 12, '1')]
		PuppetMoveTrack::PuppetMoveTrack() : distance(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(1.0f), priority(0xffffffff)
		{
			unknownC = 1;  // TODO base member
		}

		// FUNCTION: ENGINE 0x108B8010
		float PuppetMoveTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108B8020
		float PuppetMoveTrack::Slot10() const
		{
			return timeEnd - timeBegin;
		}

		// FUNCTION: ENGINE 0x108B8030
		PuppetMoveTrack::~PuppetMoveTrack()
		{
		}

		// FUNCTION: ENGINE 0x108B84C0
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void PuppetMoveTrack::RegisterProperties()
		{
			if (gPuppetMoveTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<PuppetMoveTrack>("timeBegin", &PuppetMoveTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<PuppetMoveTrack>("timeEnd", &PuppetMoveTrack::SetTimeEnd);
				properties[1] = property;
				property = new fight::PropertyVector<PuppetMoveTrack>("distance", &PuppetMoveTrack::SetDistance);
				properties[2] = property;
				property = new fight::PropertyIntConstRange<PuppetMoveTrack>("priority", &PuppetMoveTrack::SetPriority);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<PuppetMoveTrack>("blendInTime", &PuppetMoveTrack::SetBlendInTime);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<PuppetMoveTrack>("blendOutTime", &PuppetMoveTrack::SetBlendOutTime);
				properties[5] = property;
				fight::RegisterPropertyList(properties, &gPuppetMoveTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108B84A0
		fight::TrackFactory* CreatePuppetMoveTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<PuppetMoveTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108B8660
		void RegisterPuppetMoveTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<PuppetMoveTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyFloatConstRange<PuppetMoveTrack>;
		template class fight::PropertyIntConstRange<PuppetMoveTrack>;
		template class fight::PropertyVector<PuppetMoveTrack>;
		template class fight::TrackFactoryTemplate<PuppetMoveTrack>;
		template class fight::TrackFactoryCasterTemplate<PuppetMoveTrack>;
	}

	fight::Property** gUndamageableTrackProperties;  // 0x11318488

	// FUNCTION: ENGINE 0x108B8A40
	bool UndamageableTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B8A50
	bool UndamageableTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B8A60
	fight::Property* UndamageableTrack::GetProperty(int index)
	{
		return gUndamageableTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B8A70
	void UndamageableTrack::ClearProperties()
	{
		fight::FreePropertyList(&gUndamageableTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B8A80
	// ctor stores: [('movss', 'dword', 16, '0.0f'), ('mov', 'dword', 0, '0x10e7ce7c'), ('movss', 'dword', 20, '-1.0f'), ('mov', 'dword', 12, '1')]
	UndamageableTrack::UndamageableTrack() : timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108B8AB0
	float UndamageableTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B8AC0
	float UndamageableTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B8AD0
	UndamageableTrack::~UndamageableTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B8BB0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void UndamageableTrack::RegisterProperties()
	{
		if (gUndamageableTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<UndamageableTrack>("timeBegin", &UndamageableTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<UndamageableTrack>("timeEnd", &UndamageableTrack::SetTimeEnd);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gUndamageableTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B8B90
	fight::TrackFactory* CreateUndamageableTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<UndamageableTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B8C60
	void RegisterUndamageableTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<UndamageableTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<UndamageableTrack>;
	template class fight::TrackFactoryTemplate<UndamageableTrack>;
	template class fight::TrackFactoryCasterTemplate<UndamageableTrack>;

}
