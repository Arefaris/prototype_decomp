// The fight tracks that show and hide primitives, destroy an object and control an animation (unit 0x108AF960 - 0x108B0840; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_PRIMITIVETRACKS_H
#define ENGINE_FIGHT_PRIMITIVETRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::PrimitiveVisibilityTrack (16 vftable slots, 0x20 bytes)
	class PrimitiveVisibilityTrack : public fight::Track
	{
	public:
		// 0x108AF9E0
		PrimitiveVisibilityTrack();
		virtual ~PrimitiveVisibilityTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108EEA10)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetPrimitiveName(const fight::Name& value);
		bool SetVisible(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name primitiveName;  // +0x10
		float timeBegin;  // +0x18
		bool visible;  // +0x1C
	};

	extern fight::Property** gPrimitiveVisibilityTrackProperties;
	// 0x108AFC70
	// 0x108AFCB0
	fight::TrackFactory* CreatePrimitiveVisibilityTrackFactory(const char* name);
	void RegisterPrimitiveVisibilityTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::ExplicitPrimitiveVisibilityTrack (16 vftable slots, 0x30 bytes)
	class ExplicitPrimitiveVisibilityTrack : public engine::PrimitiveVisibilityTrack
	{
	public:
		// 0x108AFA40
		ExplicitPrimitiveVisibilityTrack();
		virtual ~ExplicitPrimitiveVisibilityTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 15 (0x108EEA50)
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

	extern fight::Property** gExplicitPrimitiveVisibilityTrackProperties;
	// 0x108AFC90
	// 0x108AFCE0
	fight::TrackFactory* CreateExplicitPrimitiveVisibilityTrackFactory(const char* name);
	void RegisterExplicitPrimitiveVisibilityTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::DestroyTrack (16 vftable slots, 0x14 bytes)
	class DestroyTrack : public fight::Track
	{
	public:
		// 0x108B0100
		DestroyTrack();
		virtual ~DestroyTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108EEC60)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
	};

	extern fight::Property** gDestroyTrackProperties;
	// 0x108B0200
	// 0x108B02A0
	fight::TrackFactory* CreateDestroyTrackFactory(const char* name);
	void RegisterDestroyTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::AnimationControlTrack (16 vftable slots, 0x28 bytes)
	class AnimationControlTrack : public fight::Track
	{
	public:
		// 0x108B03E0
		AnimationControlTrack();
		virtual ~AnimationControlTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108EEFB0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetStartFrame(float value);
		bool SetEndFrame(float value);
		bool SetRelativeSpeed(float value);
		bool SetCycleMode(int value);
		bool SetNumCycles(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float endFrame;  // +0x10
		float relativeSpeed;  // +0x14
		float startFrame;  // +0x18
		float timeBegin;  // +0x1C
		int cycleMode;  // +0x20
		int numCycles;  // +0x24
	};

	extern fight::Property** gAnimationControlTrackProperties;
	// 0x108B05E0
	// 0x108B0780
	fight::TrackFactory* CreateAnimationControlTrackFactory(const char* name);
	void RegisterAnimationControlTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
