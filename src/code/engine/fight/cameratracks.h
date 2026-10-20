// The fight tracks that play non-interactive sequence animations, animate lights and the camera, swap drawables and dilate time (unit 0x108B2EF0 - 0x108B52D0; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_CAMERATRACKS_H
#define ENGINE_FIGHT_CAMERATRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::NISAnimationTrack (16 vftable slots, 0x48 bytes)
	class NISAnimationTrack : public fight::Track
	{
	public:
		// 0x108B2F50
		NISAnimationTrack();
		virtual ~NISAnimationTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F1270)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetObject(const fight::Name& value);
		bool SetAnimation(const fight::Name& value);
		bool SetSpeed(float value);
		bool SetInitFrame(float value);
		bool SetStartFrame(float value);
		bool SetEndFrame(float value);
		bool SetCyclic(int value);
		bool SetNumCycles(int value);
		bool SetToBeContinued(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name animation;  // +0x10
		fight::Name object;  // +0x18
		float endFrame;  // +0x20
		float initFrame;  // +0x24
		float speed;  // +0x28
		float startFrame;  // +0x2C
		float timeBegin;  // +0x30
		float timeEnd;  // +0x34
		int cyclic;  // +0x38
		int numCycles;  // +0x3C
		bool toBeContinued;  // +0x40
		int unknown44;
	};

	extern fight::Property** gNISAnimationTrackProperties;
	// 0x108B31C0
	// 0x108B31E0
	fight::TrackFactory* CreateNISAnimationTrackFactory(const char* name);
	void RegisterNISAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::SequenceNISNodeTrack (16 vftable slots, 0x40 bytes)
	class SequenceNISNodeTrack : public fight::Track
	{
	public:
		// 0x108B35B0
		SequenceNISNodeTrack();
		virtual ~SequenceNISNodeTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F1830)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		fight::BranchHolder* GetBranch();
		bool SetPriority(int value);
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::BranchHolder branch;  // +0x10
		float timeBegin;  // +0x34
		float timeEnd;  // +0x38
		int priority;  // +0x3C
	};

	extern fight::Property** gSequenceNISNodeTrackProperties;
	// 0x108B3760
	// 0x108B3890
	fight::TrackFactory* CreateSequenceNISNodeTrackFactory(const char* name);
	void RegisterSequenceNISNodeTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::LightAnimationTrack (16 vftable slots, 0x30 bytes)
	class LightAnimationTrack : public fight::Track
	{
	public:
		// 0x108B3A30
		LightAnimationTrack();
		virtual ~LightAnimationTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F1F80)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetAnimation(const fight::Name& value);
		bool SetInitFrame(float value);
		bool SetStartFrame(float value);
		bool SetEndFrame(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name animation;  // +0x10
		float endFrame;  // +0x18
		float initFrame;  // +0x1C
		float startFrame;  // +0x20
		float timeBegin;  // +0x24
		float timeEnd;  // +0x28
		int unknown2c;
	};

	extern fight::Property** gLightAnimationTrackProperties;
	// 0x108B3C80
	// 0x108B3CC0
	fight::TrackFactory* CreateLightAnimationTrackFactory(const char* name);
	void RegisterLightAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::ExplicitLightAnimationTrack (16 vftable slots, 0x40 bytes)
	class ExplicitLightAnimationTrack : public engine::LightAnimationTrack
	{
	public:
		// 0x108B3AA0
		ExplicitLightAnimationTrack();
		virtual ~ExplicitLightAnimationTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 15 (0x108F1FC0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetObject(const fight::Name& value);
		bool SetToBeContinued(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name object;  // +0x30
		bool toBeContinued;  // +0x38
		int unknown3c;
	};

	extern fight::Property** gExplicitLightAnimationTrackProperties;
	// 0x108B3CA0
	// 0x108B3CF0
	fight::TrackFactory* CreateExplicitLightAnimationTrackFactory(const char* name);
	void RegisterExplicitLightAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::CameraClippingPlanesTrack (16 vftable slots, 0x24 bytes)
	class CameraClippingPlanesTrack : public fight::Track
	{
	public:
		// 0x108B4270
		CameraClippingPlanesTrack();
		virtual ~CameraClippingPlanesTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F2310)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetNearPlane(float value);
		bool SetFarPlane(float value);
		bool SetRestoreAtEnd(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float farPlane;  // +0x10
		float nearPlane;  // +0x14
		float timeBegin;  // +0x18
		float timeEnd;  // +0x1C
		bool restoreAtEnd;  // +0x20
	};

	extern fight::Property** gCameraClippingPlanesTrackProperties;
	// 0x108B43F0
	// 0x108B4550
	fight::TrackFactory* CreateCameraClippingPlanesTrackFactory(const char* name);
	void RegisterCameraClippingPlanesTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::CameraAnimationTrack (16 vftable slots, 0x30 bytes)
	class CameraAnimationTrack : public fight::Track
	{
	public:
		// 0x108B46B0
		CameraAnimationTrack();
		virtual ~CameraAnimationTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F2870)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetAnimation(const fight::Name& value);
		bool SetInitFrame(float value);
		bool SetStartFrame(float value);
		bool SetEndFrame(float value);
		bool SetCyclic(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name animation;  // +0x10
		float endFrame;  // +0x18
		float initFrame;  // +0x1C
		float startFrame;  // +0x20
		float timeBegin;  // +0x24
		float timeEnd;  // +0x28
		int cyclic;  // +0x2C
	};

	extern fight::Property** gCameraAnimationTrackProperties;
	// 0x108B4870
	// 0x108B4890
	fight::TrackFactory* CreateCameraAnimationTrackFactory(const char* name);
	void RegisterCameraAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::SwapDrawableTrack (16 vftable slots, 0x28 bytes)
	class SwapDrawableTrack : public fight::Track
	{
	public:
		// 0x108B4BB0
		SwapDrawableTrack();
		virtual ~SwapDrawableTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F28A0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetObjectName(const fight::Name& value);
		bool SetDrawableName(const fight::Name& value);
		bool SetPersistent(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name drawableName;  // +0x10
		fight::Name objectName;  // +0x18
		bool persistent;  // +0x20
		int unknown24;
	};

	extern fight::Property** gSwapDrawableTrackProperties;
	// 0x108B4CC0
	// 0x108B4CE0
	fight::TrackFactory* CreateSwapDrawableTrackFactory(const char* name);
	void RegisterSwapDrawableTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::TimeDilationTrack (16 vftable slots, 0x1C bytes)
	class TimeDilationTrack : public fight::Track
	{
	public:
		// 0x108B4F10
		TimeDilationTrack();
		virtual ~TimeDilationTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F2AE0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetSimulationRate(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float simulationRate;  // +0x10
		float timeBegin;  // +0x14
		float timeEnd;  // +0x18
	};

	extern fight::Property** gTimeDilationTrackProperties;
	// 0x108B5020
	// 0x108B5120
	fight::TrackFactory* CreateTimeDilationTrackFactory(const char* name);
	void RegisterTimeDilationTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
