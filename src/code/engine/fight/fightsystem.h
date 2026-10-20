// The set-up of the fight system (unit 0x10811DC0 - 0x10812A50, no assert path; the file name is a guess): the global
// initialisers that make the engine's fight contexts (Playback, NIS, PropLogic, Motion) and the registration of the
// track, condition and branch factories each of them knows, the system's start-up and shutdown, and the callbacks it
// hands to the fight core. Names are guesses from the strings and RTTI; the factory registration functions belong to
// the units of the classes they register and are declared here with their addresses.
#ifndef ENGINE_FIGHT_FIGHTSYSTEM_H
#define ENGINE_FIGHT_FIGHTSYSTEM_H

#include "code/content/chunkhandler.h"
#include "code/content/loadmanager.h"
#include "code/engine/fight/exitfactories.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/system/streampackage.h"

namespace fight
{
	// The loader of the fight files' contents (RTTI: fight::FileLoader, 6 vftable slots, 0xC bytes; 0x10A9BA00)
	class FileLoader : public content::FileLoader
	{
	public:
		FileLoader(bool unknown);

		unsigned char unknown8;
	};

	// The chunk loaders of the fight chunks (RTTI: fight::FightChunkP3DLoader / fight::LegacyFightChunkP3DLoader, 8
	// vftable slots, 0x10 bytes; constructors 0x10A9BF00 / 0x10A9BF50)
	class FightChunkP3DLoader : public content::SimpleChunkHandler
	{
	public:
		FightChunkP3DLoader();
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);
	};

	class LegacyFightChunkP3DLoader : public content::SimpleChunkHandler
	{
	public:
		LegacyFightChunkP3DLoader();
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);
	};

	// 0x105A83C0 / 0x105A83B0: the heap a part of the fight system allocates from (a table of three; the setter
	// answers the old one)
	int SetHeapId(int index, int heap);
	int GetHeapId(int index);

	// 0x105B2150 / 0x105A74F0: the function the 'platform' condition asks and the one the 'random' condition draws
	// from, each with a word that is passed on
	void SetPlatformCallback(int (*function)(), int argument);
	void SetRandomCallback(float (*function)(), int argument);

	// The factories of the fight core (0x105A65A0 - 0x105A6670, 0x105A6570: the conditions and tracks every context
	// has, 0x105A64B0: a track by name, 0x105ADA30: the branch of the plain node)
	void RegisterCoreFactories(TrackRegistry* registry);
	void RegisterCoreTrackFactories(TrackRegistry* registry);
	void RegisterFlowTrackFactories(TrackRegistry* registry);
	void RegisterBranchFactories(TrackRegistry* registry);
	void RegisterEventTrackFactory(TrackRegistry* registry, const char* name);
	void RegisterNodeBranchFactory(TrackRegistry* registry);
	// 0x105B07F0 / 0x105AEF50 / 0x105AFC30: the comment, print and track group tracks
	void RegisterCommentTrackFactory(TrackRegistry* registry, const char* name);
	void RegisterPrintTrackFactory(TrackRegistry* registry, const char* name);
	void RegisterTrackGroupTrackFactory(TrackRegistry* registry, const char* name);

	// 0x11276204: set while the branch references are resolved
	extern bool gResolvingBranchRefs;
}

namespace engine
{
	// The arguments of the fight system's start-up (0x10811DC0: the three heaps, 0, 1 and 0 to begin with)
	struct FightSystemParams
	{
		FightSystemParams();

		int heap0;
		int heap1;
		int heap2;
	};

	// 0x105A4AC0 / 0x105A50B0: makes the list of the contexts, and destroys it
	LoadListeners* CreateLoadListeners();
	void DestroyLoadListeners();

	// 0x10812610 / 0x10811FD0
	void StartFightSystem(const FightSystemParams* params);
	void StopFightSystem();

	// The contexts the engine makes while it starts up (the initialisers of 0x108129D0, 0x108120A0, 0x10812A50 and
	// 0x10812120)
	void MakePropLogicContext();
	void MakePlaybackContext();
	void MakeMotionContext();
	void MakeNISContext();


	// The registration functions the units of the other fight classes define
	void RegisterPlaybackTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPlaybackStateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEffectTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAbortEffectTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMotionTrailTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEffectLODBiasTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEffectLODSwitchTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEffectLODDisableTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHealthTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterScenarioStringTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHealthConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterObjectTemplateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAttributeNameConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAudioTrackFactories(fight::TrackRegistry* registry);

	namespace scenario
	{
		void RegisterLuaTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterLuaConditionFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace framebufferfx
	{
		void RegisterToneMapTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterFadeTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterDepthOfFieldTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterColourMatrixTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterScatterTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterLetterboxTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterBloomTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	// The track registration of the classes of other units: the name the track is known by in the fight data is
	// passed (0x108AD790 ...)
	void RegisterAnimationControlTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDestroyTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPrimitiveVisibilityTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPrimitiveDisplayTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPuppetAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetRotationAttributeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetTransformAttributeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSimpleMessageTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVelocityLinearTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVelocityAngularTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpawnObjectTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTeleportTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLightTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTimeDilationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSwapDrawableTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCameraAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCameraClippingPlanesTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterExplicitLightAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSequenceNISNodeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterNISAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterExplicitPrimitiveVisibilityTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterExplicitSetObjectLightGroupTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSubTitleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterNISExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetObjectLightGroupTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLightAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterUndamageableTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPCKeyboardConditionFactory(fight::TrackRegistry* registry, const char* name);

	// The registration of whole groups of classes: the online conditions (0x108B0840), the physics tracks
	// (0x108B7DA0) and the character tracks (0x108B8D20)
	void RegisterOnlineConditionFactories(fight::TrackRegistry* registry);
	void RegisterPhysicsTrackFactories(fight::TrackRegistry* registry);
	void RegisterCharacterTrackFactories(fight::TrackRegistry* registry);

	// The branch factories of the playback and NIS nodes
	void RegisterNISNodeBranchFactory(fight::TrackRegistry* registry);
	void RegisterNISRootNodeBranchFactory(fight::TrackRegistry* registry);
	void RegisterPlaybackNodeBranchFactory(fight::TrackRegistry* registry);
	void RegisterPlaybackSetBranchFactory(fight::TrackRegistry* registry);

	namespace animation
	{
		void RegisterShaderAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterVelocityConditionFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterVelocityAngularConditionFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterAttachObjectTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterDetachObjectTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterDetachFromParentTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterDisableMotionTrackedExpressionTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterEnableMotionTrackedExpressionTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterExpressionAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterJointLockTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterPuppetMoveTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterPuppetPhaseConditionFactory(fight::TrackRegistry* registry, const char* name);
	}
}

#endif
