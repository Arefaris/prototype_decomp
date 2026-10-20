// The fight tracks that run a non-interactive sequence, show a subtitle, set an object's light group and attach or detach objects (unit 0x108B1120 - 0x108B2EF0; no assert path, file name guessed).
#include "code/engine/fight/nistracks.h"
#include <new>

namespace engine
{
	fight::Property** gNISExecuteTrackProperties;  // 0x11318308

	// FUNCTION: ENGINE 0x108B10F0
	bool NISExecuteTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B1100
	fight::BranchHolder* NISExecuteTrack::GetReceiverBranch()
	{
		return &receiverBranch;
	}

	// FUNCTION: ENGINE 0x108B1110
	bool NISExecuteTrack::SetInterruptPriority(int newValue)
	{
		interruptPriority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B1140
	bool NISExecuteTrack::SetObjectName(const fight::Name& newValue)
	{
		objectName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B1120
	fight::Property* NISExecuteTrack::GetProperty(int index)
	{
		return gNISExecuteTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B1130
	void NISExecuteTrack::ClearProperties()
	{
		fight::FreePropertyList(&gNISExecuteTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B1160
	// ctor stores: [('mov', 'dword', 0, '0x10e7b3a4'), ('movss', 'dword', 64, '0.0f'), ('mov', 'dword', 68, '0xfffffffb'), ('mov', 'dword', 12, '1')]
	NISExecuteTrack::NISExecuteTrack() : receiverBranch("Motion"), timeBegin(0.0f), interruptPriority(0xfffffffb)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108B11A0
	float NISExecuteTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B11B0
	float NISExecuteTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108B11C0
	NISExecuteTrack::~NISExecuteTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B13A0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void NISExecuteTrack::RegisterProperties()
	{
		if (gNISExecuteTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<NISExecuteTrack>("objectName", &NISExecuteTrack::SetObjectName);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<NISExecuteTrack>("timeBegin", &NISExecuteTrack::SetTimeBegin);
			properties[1] = property;
			property = new fight::PropertyBranch<NISExecuteTrack>("receiverBranch", &NISExecuteTrack::GetReceiverBranch);
			properties[2] = property;
			property = new fight::PropertyIntConstRange<NISExecuteTrack>("interruptPriority", &NISExecuteTrack::SetInterruptPriority);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gNISExecuteTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B1310
	fight::TrackFactory* CreateNISExecuteTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<NISExecuteTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B1330
	void RegisterNISExecuteTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<NISExecuteTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBranch<NISExecuteTrack>;
	template class fight::PropertyFloatConstRange<NISExecuteTrack>;
	template class fight::PropertyIntConstRange<NISExecuteTrack>;
	template class fight::PropertyName<NISExecuteTrack>;
	template class fight::TrackFactoryTemplate<NISExecuteTrack>;
	template class fight::TrackFactoryCasterTemplate<NISExecuteTrack>;

	fight::Property** gSubTitleTrackProperties;  // 0x1131830C

	// FUNCTION: ENGINE 0x108B1540
	bool SubTitleTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B1550
	bool SubTitleTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B1610
	bool SubTitleTrack::SetSubTitle(const char* newValue)
	{
		subTitle = fight::ReplaceString(subTitle, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108B1630
	bool SubTitleTrack::SetSubTitleType(const char* newValue)
	{
		subTitleType = fight::ReplaceString(subTitleType, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108B1650
	bool SubTitleTrack::SetSpeaker(const char* newValue)
	{
		speaker = fight::ReplaceString(speaker, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108B1560
	fight::Property* SubTitleTrack::GetProperty(int index)
	{
		return gSubTitleTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B1570
	void SubTitleTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSubTitleTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B1580
	// ctor stores: [('movss', 'dword', 28, '0.0f'), ('mov', 'dword', 16, '0'), ('mov', 'dword', 20, '0'), ('mov', 'dword', 24, '0'), ('mov', 'dword', 0, '0x10e7b4ac'), ('movss', 'dword', 32, '-1.0f')]
	SubTitleTrack::SubTitleTrack() : speaker(0), subTitle(0), subTitleType(0), timeBegin(0.0f), timeEnd(-1.0f)
	{
	}

	// FUNCTION: ENGINE 0x108B15C0
	float SubTitleTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B15D0
	float SubTitleTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B15E0
	SubTitleTrack::~SubTitleTrack()
	{
		delete[] subTitle;
		delete[] subTitleType;
		delete[] speaker;
	}

	// FUNCTION: ENGINE 0x108B1790
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SubTitleTrack::RegisterProperties()
	{
		if (gSubTitleTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SubTitleTrack>("timeBegin", &SubTitleTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<SubTitleTrack>("timeEnd", &SubTitleTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyString<SubTitleTrack>("subTitle", &SubTitleTrack::SetSubTitle);
			properties[2] = property;
			property = new fight::PropertyString<SubTitleTrack>("subTitleType", &SubTitleTrack::SetSubTitleType);
			properties[3] = property;
			property = new fight::PropertyString<SubTitleTrack>("speaker", &SubTitleTrack::SetSpeaker);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gSubTitleTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B1770
	fight::TrackFactory* CreateSubTitleTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SubTitleTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B18D0
	void RegisterSubTitleTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SubTitleTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<SubTitleTrack>;
	template class fight::PropertyString<SubTitleTrack>;
	template class fight::TrackFactoryTemplate<SubTitleTrack>;
	template class fight::TrackFactoryCasterTemplate<SubTitleTrack>;

	fight::Property** gSetObjectLightGroupTrackProperties;  // 0x11318310

	// FUNCTION: ENGINE 0x108B1990
	bool SetObjectLightGroupTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B19A0
	bool SetObjectLightGroupTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B1A00
	bool SetObjectLightGroupTrack::SetGroupName(const fight::Name& newValue)
	{
		groupName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B19C0
	fight::Property* SetObjectLightGroupTrack::GetProperty(int index)
	{
		return gSetObjectLightGroupTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B19D0
	void SetObjectLightGroupTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSetObjectLightGroupTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B1A40
	// ctor stores: [('mov', 'dword', 0, '0x10e7b58c'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '-1.0f'), ('mov', 'dword', 12, '1')]
	SetObjectLightGroupTrack::SetObjectLightGroupTrack() : timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108B1A80
	float SetObjectLightGroupTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B1A90
	float SetObjectLightGroupTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B1AA0
	SetObjectLightGroupTrack::~SetObjectLightGroupTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B1DB0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SetObjectLightGroupTrack::RegisterProperties()
	{
		if (gSetObjectLightGroupTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SetObjectLightGroupTrack>("timeBegin", &SetObjectLightGroupTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<SetObjectLightGroupTrack>("timeEnd", &SetObjectLightGroupTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<SetObjectLightGroupTrack>("groupName", &SetObjectLightGroupTrack::SetGroupName);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gSetObjectLightGroupTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B1C90
	fight::TrackFactory* CreateSetObjectLightGroupTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetObjectLightGroupTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B1CD0
	void RegisterSetObjectLightGroupTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetObjectLightGroupTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<SetObjectLightGroupTrack>;
	template class fight::PropertyName<SetObjectLightGroupTrack>;
	template class fight::TrackFactoryTemplate<SetObjectLightGroupTrack>;
	template class fight::TrackFactoryCasterTemplate<SetObjectLightGroupTrack>;

	fight::Property** gExplicitSetObjectLightGroupTrackProperties;  // 0x11318314

	// FUNCTION: ENGINE 0x108B19B0
	bool ExplicitSetObjectLightGroupTrack::SetToBeContinued(bool newValue)
	{
		toBeContinued = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B1A20
	bool ExplicitSetObjectLightGroupTrack::SetObject(const fight::Name& newValue)
	{
		object = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B19E0
	fight::Property* ExplicitSetObjectLightGroupTrack::GetProperty(int index)
	{
		return gExplicitSetObjectLightGroupTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B19F0
	void ExplicitSetObjectLightGroupTrack::ClearProperties()
	{
		fight::FreePropertyList(&gExplicitSetObjectLightGroupTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B1AB0
	// ctor stores: [('mov', 'dword', 0, '0x10e7b5d4'), ('mov', 'byte', 40, '1')]
	ExplicitSetObjectLightGroupTrack::ExplicitSetObjectLightGroupTrack() : toBeContinued(1)
	{
	}

	// FUNCTION: ENGINE 0x108B1AD0
	ExplicitSetObjectLightGroupTrack::~ExplicitSetObjectLightGroupTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B1E90
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void ExplicitSetObjectLightGroupTrack::RegisterProperties()
	{
		if (gExplicitSetObjectLightGroupTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<ExplicitSetObjectLightGroupTrack>("object", &ExplicitSetObjectLightGroupTrack::SetObject);
			properties[0] = property;
			property = new fight::PropertyBool<ExplicitSetObjectLightGroupTrack>("toBeContinued", &ExplicitSetObjectLightGroupTrack::SetToBeContinued);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<ExplicitSetObjectLightGroupTrack>("timeBegin", &engine::SetObjectLightGroupTrack::SetTimeBegin);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<ExplicitSetObjectLightGroupTrack>("timeEnd", &engine::SetObjectLightGroupTrack::SetTimeEnd);
			properties[3] = property;
			property = new fight::PropertyName<ExplicitSetObjectLightGroupTrack>("groupName", &engine::SetObjectLightGroupTrack::SetGroupName);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gExplicitSetObjectLightGroupTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B1CB0
	fight::TrackFactory* CreateExplicitSetObjectLightGroupTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<ExplicitSetObjectLightGroupTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B1D00
	void RegisterExplicitSetObjectLightGroupTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<ExplicitSetObjectLightGroupTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<ExplicitSetObjectLightGroupTrack>;
	template class fight::PropertyFloatConstRange<ExplicitSetObjectLightGroupTrack>;
	template class fight::PropertyName<ExplicitSetObjectLightGroupTrack>;
	template class fight::TrackFactoryTemplate<ExplicitSetObjectLightGroupTrack>;
	template class fight::TrackFactoryCasterTemplate<ExplicitSetObjectLightGroupTrack>;

	namespace animation
	{
		fight::Property** gDetachFromParentTrackProperties;  // 0x11318318

		// FUNCTION: ENGINE 0x108B20F0
		bool DetachFromParentTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B21C0
		fight::Property* DetachFromParentTrack::GetProperty(int index)
		{
			return gDetachFromParentTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x108B21D0
		void DetachFromParentTrack::ClearProperties()
		{
			fight::FreePropertyList(&gDetachFromParentTrackProperties);
		}

		// FUNCTION: ENGINE 0x108B21E0
		// ctor stores: [('mov', 'dword', 0, '0x10e7b724'), ('movss', 'dword', 16, '0.0f')]
		DetachFromParentTrack::DetachFromParentTrack() : timeBegin(0.0f)
		{
		}

		// FUNCTION: ENGINE 0x108B2200
		float DetachFromParentTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108B2210
		float DetachFromParentTrack::Slot10() const
		{
			return -1.0f;
		}

		// FUNCTION: ENGINE 0x108B2220
		DetachFromParentTrack::~DetachFromParentTrack()
		{
		}

		// FUNCTION: ENGINE 0x108B27C0
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void DetachFromParentTrack::RegisterProperties()
		{
			if (gDetachFromParentTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<DetachFromParentTrack>("timeBegin", &DetachFromParentTrack::SetTimeBegin);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gDetachFromParentTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108B2760
		fight::TrackFactory* CreateDetachFromParentTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<DetachFromParentTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108B2840
		void RegisterDetachFromParentTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<DetachFromParentTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyFloatConstRange<DetachFromParentTrack>;
		template class fight::TrackFactoryTemplate<DetachFromParentTrack>;
		template class fight::TrackFactoryCasterTemplate<DetachFromParentTrack>;
	}

	namespace animation
	{
		extern fight::EnumEntry gAttachObjectTrackModeIfUsingPhysicsTable[];
		extern fight::EnumEntry gAttachObjectTrackCharacterModeIfSimulatedTable[];

		fight::Property** gAttachObjectTrackProperties;  // 0x1131831C

		// FUNCTION: ENGINE 0x108B2100
		bool AttachObjectTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2110
		bool AttachObjectTrack::SetBlendDuration(float newValue)
		{
			blendDuration = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2120
		bool AttachObjectTrack::SetParentOffset(const math::Vector& newValue)
		{
			parentOffset.x = newValue.x;
			parentOffset.y = newValue.y;
			parentOffset.z = newValue.z;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2140
		bool AttachObjectTrack::SetChildOffset(const math::Vector& newValue)
		{
			childOffset.x = newValue.x;
			childOffset.y = newValue.y;
			childOffset.z = newValue.z;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2160
		bool AttachObjectTrack::SetChildOrientation(const math::Vector& newValue)
		{
			childOrientation.x = newValue.x;
			childOrientation.y = newValue.y;
			childOrientation.z = newValue.z;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2180
		bool AttachObjectTrack::SetUsePhysics(bool newValue)
		{
			usePhysics = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2190
		bool AttachObjectTrack::SetModeIfUsingPhysics(int newValue)
		{
			modeIfUsingPhysics = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B21A0
		bool AttachObjectTrack::SetCharacterModeIfSimulated(int newValue)
		{
			characterModeIfSimulated = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2270
		bool AttachObjectTrack::SetParentName(const fight::Name& newValue)
		{
			parentName = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2290
		bool AttachObjectTrack::SetParentJointName(const fight::Name& newValue)
		{
			parentJointName = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B22B0
		bool AttachObjectTrack::SetObjectToAttach(const fight::Name& newValue)
		{
			objectToAttach = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B22D0
		bool AttachObjectTrack::SetChildJointName(const fight::Name& newValue)
		{
			childJointName = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2230
		fight::Property* AttachObjectTrack::GetProperty(int index)
		{
			return gAttachObjectTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x108B2240
		void AttachObjectTrack::ClearProperties()
		{
			fight::FreePropertyList(&gAttachObjectTrackProperties);
		}

		// FUNCTION: ENGINE 0x108B2330
		// ctor stores: [('mov', 'dword', 0, '0x10e7b76c'), ('movss', 'dword', 48, '0.0f'), ('movss', 'dword', 52, '0.0f'), ('movss', 'dword', 56, '0.0f'), ('movss', 'dword', 60, '0.0f'), ('movss', 'dword', 64, '0.0f'), ('movss', 'dword', 68, '0.0f'), ('movss', 'dword', 72, '0.0f'), ('movss', 'dword', 76, '0.0f'), ('movss', 'dword', 80, '0.0f'), ('mov', 'dword', 92, '0'), ('mov', 'dword', 96, '0'), ('mov', 'byte', 100, '0'), ('movss', 'dword', 84, '0.0f'), ('movss', 'dword', 88, '0.0f')]
		AttachObjectTrack::AttachObjectTrack() : childOffset(0.0f, 0.0f, 0.0f), childOrientation(0.0f, 0.0f, 0.0f), parentOffset(0.0f, 0.0f, 0.0f), blendDuration(0.0f), timeBegin(0.0f), characterModeIfSimulated(0), modeIfUsingPhysics(0), usePhysics(false)
		{
		}

		// FUNCTION: ENGINE 0x108B23B0
		float AttachObjectTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108B23C0
		float AttachObjectTrack::Slot10() const
		{
			return -1.0f;
		}

		// FUNCTION: ENGINE 0x108B23D0
		AttachObjectTrack::~AttachObjectTrack()
		{
		}

		// FUNCTION: ENGINE 0x108B29A0
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void AttachObjectTrack::RegisterProperties()
		{
			if (gAttachObjectTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<AttachObjectTrack>("timeBegin", &AttachObjectTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<AttachObjectTrack>("blendDuration", &AttachObjectTrack::SetBlendDuration);
				properties[1] = property;
				property = new fight::PropertyName<AttachObjectTrack>("parentName", &AttachObjectTrack::SetParentName);
				properties[2] = property;
				property = new fight::PropertyName<AttachObjectTrack>("parentJointName", &AttachObjectTrack::SetParentJointName);
				properties[3] = property;
				property = new fight::PropertyVector<AttachObjectTrack>("parentOffset", &AttachObjectTrack::SetParentOffset);
				properties[4] = property;
				property = new fight::PropertyName<AttachObjectTrack>("objectToAttach", &AttachObjectTrack::SetObjectToAttach);
				properties[5] = property;
				property = new fight::PropertyName<AttachObjectTrack>("childJointName", &AttachObjectTrack::SetChildJointName);
				properties[6] = property;
				property = new fight::PropertyVector<AttachObjectTrack>("childOffset", &AttachObjectTrack::SetChildOffset);
				properties[7] = property;
				property = new fight::PropertyVector<AttachObjectTrack>("childOrientation", &AttachObjectTrack::SetChildOrientation);
				properties[8] = property;
				property = new fight::PropertyBool<AttachObjectTrack>("usePhysics", &AttachObjectTrack::SetUsePhysics);
				properties[9] = property;
				property = new fight::PropertyEnumConstList<AttachObjectTrack>("modeIfUsingPhysics", gAttachObjectTrackModeIfUsingPhysicsTable, 3, &AttachObjectTrack::SetModeIfUsingPhysics);
				properties[10] = property;
				property = new fight::PropertyEnumConstList<AttachObjectTrack>("characterModeIfSimulated", gAttachObjectTrackCharacterModeIfSimulatedTable, 3, &AttachObjectTrack::SetCharacterModeIfSimulated);
				properties[11] = property;
				fight::RegisterPropertyList(properties, &gAttachObjectTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108B2780
		fight::TrackFactory* CreateAttachObjectTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<AttachObjectTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108B2870
		void RegisterAttachObjectTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<AttachObjectTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyBool<AttachObjectTrack>;
		template class fight::PropertyEnumConstList<AttachObjectTrack>;
		template class fight::PropertyFloatConstRange<AttachObjectTrack>;
		template class fight::PropertyName<AttachObjectTrack>;
		template class fight::PropertyVector<AttachObjectTrack>;
		template class fight::TrackFactoryTemplate<AttachObjectTrack>;
		template class fight::TrackFactoryCasterTemplate<AttachObjectTrack>;
	}

	namespace animation
	{
		fight::Property** gDetachObjectTrackProperties;  // 0x11318320

		// FUNCTION: ENGINE 0x108B21B0
		bool DetachObjectTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B22F0
		bool DetachObjectTrack::SetObjectToDetach(const fight::Name& newValue)
		{
			objectToDetach = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B2250
		fight::Property* DetachObjectTrack::GetProperty(int index)
		{
			return gDetachObjectTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x108B2260
		void DetachObjectTrack::ClearProperties()
		{
			fight::FreePropertyList(&gDetachObjectTrackProperties);
		}

		// FUNCTION: ENGINE 0x108B23E0
		// ctor stores: [('mov', 'dword', 0, '0x10e7b7b4'), ('movss', 'dword', 24, '0.0f')]
		DetachObjectTrack::DetachObjectTrack() : timeBegin(0.0f)
		{
		}

		// FUNCTION: ENGINE 0x108B2410
		float DetachObjectTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108B2420
		float DetachObjectTrack::Slot10() const
		{
			return -1.0f;
		}

		// FUNCTION: ENGINE 0x108B2430
		DetachObjectTrack::~DetachObjectTrack()
		{
		}

		// FUNCTION: ENGINE 0x108B2C50
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void DetachObjectTrack::RegisterProperties()
		{
			if (gDetachObjectTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<DetachObjectTrack>("timeBegin", &DetachObjectTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyName<DetachObjectTrack>("objectToDetach", &DetachObjectTrack::SetObjectToDetach);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gDetachObjectTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x108B27A0
		fight::TrackFactory* CreateDetachObjectTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<DetachObjectTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108B28A0
		void RegisterDetachObjectTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<DetachObjectTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyFloatConstRange<DetachObjectTrack>;
		template class fight::PropertyName<DetachObjectTrack>;
		template class fight::TrackFactoryTemplate<DetachObjectTrack>;
		template class fight::TrackFactoryCasterTemplate<DetachObjectTrack>;
	}

}
