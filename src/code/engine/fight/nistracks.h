// The fight tracks that run a non-interactive sequence, show a subtitle, set an object's light group and attach or detach objects (unit 0x108B1120 - 0x108B2EF0; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_NISTRACKS_H
#define ENGINE_FIGHT_NISTRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::NISExecuteTrack (16 vftable slots, 0x48 bytes)
	class NISExecuteTrack : public fight::Track
	{
	public:
		// 0x108B1160
		NISExecuteTrack();
		virtual ~NISExecuteTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108EF9D0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetObjectName(const fight::Name& value);
		bool SetTimeBegin(float value);
		fight::BranchHolder* GetReceiverBranch();
		bool SetInterruptPriority(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::BranchHolder receiverBranch;  // +0x10
		int unknown34;
		fight::Name objectName;  // +0x38
		float timeBegin;  // +0x40
		int interruptPriority;  // +0x44
	};

	extern fight::Property** gNISExecuteTrackProperties;
	// 0x108B1310
	// 0x108B1330
	fight::TrackFactory* CreateNISExecuteTrackFactory(const char* name);
	void RegisterNISExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::SubTitleTrack (16 vftable slots, 0x24 bytes)
	class SubTitleTrack : public fight::Track
	{
	public:
		// 0x108B1580
		SubTitleTrack();
		virtual ~SubTitleTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108EFC40)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetSubTitle(const char* value);
		bool SetSubTitleType(const char* value);
		bool SetSpeaker(const char* value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		char* speaker;  // +0x10
		char* subTitle;  // +0x14
		char* subTitleType;  // +0x18
		float timeBegin;  // +0x1C
		float timeEnd;  // +0x20
	};

	extern fight::Property** gSubTitleTrackProperties;
	// 0x108B1770
	// 0x108B18D0
	fight::TrackFactory* CreateSubTitleTrackFactory(const char* name);
	void RegisterSubTitleTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::SetObjectLightGroupTrack (16 vftable slots, 0x20 bytes)
	class SetObjectLightGroupTrack : public fight::Track
	{
	public:
		// 0x108B1A40
		SetObjectLightGroupTrack();
		virtual ~SetObjectLightGroupTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F0040)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetGroupName(const fight::Name& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name groupName;  // +0x10
		float timeBegin;  // +0x18
		float timeEnd;  // +0x1C
	};

	extern fight::Property** gSetObjectLightGroupTrackProperties;
	// 0x108B1C90
	// 0x108B1CD0
	fight::TrackFactory* CreateSetObjectLightGroupTrackFactory(const char* name);
	void RegisterSetObjectLightGroupTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::ExplicitSetObjectLightGroupTrack (16 vftable slots, 0x30 bytes)
	class ExplicitSetObjectLightGroupTrack : public engine::SetObjectLightGroupTrack
	{
	public:
		// 0x108B1AB0
		ExplicitSetObjectLightGroupTrack();
		virtual ~ExplicitSetObjectLightGroupTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 15 (0x108F0080)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetObject(const fight::Name& value);
		bool SetToBeContinued(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name object;  // +0x20
		bool toBeContinued;  // +0x28
		int unknown2c;
	};

	extern fight::Property** gExplicitSetObjectLightGroupTrackProperties;
	// 0x108B1CB0
	// 0x108B1D00
	fight::TrackFactory* CreateExplicitSetObjectLightGroupTrackFactory(const char* name);
	void RegisterExplicitSetObjectLightGroupTrackFactory(fight::TrackRegistry* registry, const char* name);

	namespace animation
	{
		// RTTI: engine::animation::DetachFromParentTrack (16 vftable slots, 0x14 bytes)
		class DetachFromParentTrack : public fight::Track
		{
		public:
			// 0x108B21E0
			DetachFromParentTrack();
			virtual ~DetachFromParentTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108F08B0)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float timeBegin;  // +0x10
		};

		extern fight::Property** gDetachFromParentTrackProperties;
		// 0x108B2760
		// 0x108B2840
		fight::TrackFactory* CreateDetachFromParentTrackFactory(const char* name);
		void RegisterDetachFromParentTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace animation
	{
		// RTTI: engine::animation::AttachObjectTrack (16 vftable slots, 0x68 bytes)
		class AttachObjectTrack : public fight::Track
		{
		public:
			// 0x108B2330
			AttachObjectTrack();
			virtual ~AttachObjectTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108F0830)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetBlendDuration(float value);
			bool SetParentName(const fight::Name& value);
			bool SetParentJointName(const fight::Name& value);
			bool SetParentOffset(const math::Vector& value);
			bool SetObjectToAttach(const fight::Name& value);
			bool SetChildJointName(const fight::Name& value);
			bool SetChildOffset(const math::Vector& value);
			bool SetChildOrientation(const math::Vector& value);
			bool SetUsePhysics(bool value);
			bool SetModeIfUsingPhysics(int value);
			bool SetCharacterModeIfSimulated(int value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			fight::Name childJointName;  // +0x10
			fight::Name objectToAttach;  // +0x18
			fight::Name parentJointName;  // +0x20
			fight::Name parentName;  // +0x28
			math::Vector childOffset;  // +0x30
			math::Vector childOrientation;  // +0x3C
			math::Vector parentOffset;  // +0x48
			float blendDuration;  // +0x54
			float timeBegin;  // +0x58
			int characterModeIfSimulated;  // +0x5C
			int modeIfUsingPhysics;  // +0x60
			bool usePhysics;  // +0x64
		};

		extern fight::Property** gAttachObjectTrackProperties;
		// 0x108B2780
		// 0x108B2870
		fight::TrackFactory* CreateAttachObjectTrackFactory(const char* name);
		void RegisterAttachObjectTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace animation
	{
		// RTTI: engine::animation::DetachObjectTrack (16 vftable slots, 0x20 bytes)
		class DetachObjectTrack : public fight::Track
		{
		public:
			// 0x108B23E0
			DetachObjectTrack();
			virtual ~DetachObjectTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108F0870)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetObjectToDetach(const fight::Name& value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			fight::Name objectToDetach;  // +0x10
			float timeBegin;  // +0x18
			int unknown1c;
		};

		extern fight::Property** gDetachObjectTrackProperties;
		// 0x108B27A0
		// 0x108B28A0
		fight::TrackFactory* CreateDetachObjectTrackFactory(const char* name);
		void RegisterDetachObjectTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

}

#endif
