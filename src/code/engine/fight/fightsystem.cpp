// The set-up of the fight system (see fightsystem.h).
#include "code/core/heap.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/random.h"

namespace engine
{
	// The names of the fight contexts the engine makes (the pointers at 0x111C17CC - 0x111C17E0)
	const char* gPropLogicContextName = "PropLogic";
	const char* gMotionContextName = "Motion";
	const char* gPlaybackContextName = "Playback";
	const char* gNISContextName = "NIS";
	const char* gPlaybackTrackName = "playback";

	// The loaders the fight files and chunks are read with
	fight::FileLoader* gFightFileLoader;
	fight::FileLoader* gFightBinaryFileLoader;
	fight::FightChunkP3DLoader* gFightChunkLoader;
	fight::LegacyFightChunkP3DLoader* gLegacyFightChunkLoader;

	// FUNCTION: ENGINE 0x10811DC0
	FightSystemParams::FightSystemParams() : heap0(0), heap1(1), heap2(0)
	{
	}

	// FUNCTION: ENGINE 0x10811DE0
	// The factories most contexts have in common (the registry is in a register)
	static void RegisterSharedFactories(fight::TrackRegistry* registry)
	{
		fight::RegisterCoreFactories(registry);
		fight::RegisterCoreTrackFactories(registry);
		RegisterAudioTrackFactories(registry);
		RegisterOnlineConditionFactories(registry);
		RegisterAnimationControlTrackFactory(registry, "animationControl");
		RegisterDestroyTrackFactory(registry, "destroy");
		RegisterEffectTrackFactory(registry, "effect");
		RegisterAbortEffectTrackFactory(registry, "abortEffect");
		RegisterEffectLODBiasTrackFactory(registry, "effectLODBias");
		RegisterEffectLODSwitchTrackFactory(registry, "effectLODSwitch");
		RegisterEffectLODDisableTrackFactory(registry, "effectLODDisable");
		RegisterHealthTrackFactory(registry, "health");
		RegisterPrimitiveVisibilityTrackFactory(registry, "primitiveDisplaySimple");
		RegisterPrimitiveDisplayTrackFactory(registry, "primitiveDisplay");
		RegisterPuppetAnimationTrackFactory(registry, "animation");
		RegisterSetRotationAttributeTrackFactory(registry, "setRotationAttribute");
		RegisterSetTransformAttributeTrackFactory(registry, "setTransformAttribute");
		RegisterSimpleMessageTrackFactory(registry, "simpleMessage");
		RegisterScenarioStringTrackFactory(registry, "scenarioStringEvent");
		RegisterVelocityLinearTrackFactory(registry, "velocityLinear");
		RegisterVelocityAngularTrackFactory(registry, "velocityAngular");
	}

	// FUNCTION: ENGINE 0x10811EC0
	int AlwaysTrue()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10811ED0
	// EQUIVALENT: the same two generator steps and the same loads and stores; the engine keeps the address of the
	// second state in edx and works in esi, ours in edx and ecx (19.0 %)
	float DrawRandom()
	{
		return math::gRandom->NextFloat01();
	}

	// FUNCTION: ENGINE 0x10811F30
	void ResolveBranchRefs()
	{
		bool previous = fight::gResolvingBranchRefs;
		fight::gResolvingBranchRefs = true;
		LoadListeners* listeners = gLoadListeners;
		if (listeners != 0)
		{
			int count = listeners->GetCount();
			if (count != 0)
			{
				do
				{
					count--;
					listeners->GetContext(count)->ResolveBranchRefs();
				}
				while (count != 0);
			}
		}
		fight::gResolvingBranchRefs = previous;
	}

	// FUNCTION: ENGINE 0x10811FD0
	void StopFightSystem()
	{
		content::LoadManager* manager = content::gLoadManager;
		if (gFightFileLoader != 0)
		{
			if (manager != 0)
			{
				manager->RemoveFileLoader(gFightFileLoader);
			}
			gFightFileLoader->Release();
			gFightFileLoader = 0;
		}
		if (gFightBinaryFileLoader != 0)
		{
			if (manager != 0)
			{
				manager->RemoveFileLoader(gFightBinaryFileLoader);
			}
			gFightBinaryFileLoader->Release();
			gFightBinaryFileLoader = 0;
		}
		if (gFightChunkLoader != 0)
		{
			if (manager != 0)
			{
				manager->RemoveLoader(gFightChunkLoader);
			}
			gFightChunkLoader->Release();
			gFightChunkLoader = 0;
		}
		if (gLegacyFightChunkLoader != 0)
		{
			if (manager != 0)
			{
				manager->RemoveLoader(gLegacyFightChunkLoader);
			}
			gLegacyFightChunkLoader->Release();
			gLegacyFightChunkLoader = 0;
		}
		LoadListeners* listeners = gLoadListeners;
		LuaScriptManager* script = GetScriptManager();
		script->Unregister(listeners);
		DestroyLoadListeners();
	}

	// FUNCTION: ENGINE 0x108120A0
	void MakePlaybackContext()
	{
		LoadListeners* listeners = gLoadListeners;
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(fight::Name(gPlaybackContextName, 1));
		listeners->AddContext(registry);
		RegisterPlaybackNodeBranchFactory(registry);
		RegisterPlaybackSetBranchFactory(registry);
		RegisterSharedFactories(registry);
		registry->Prepare();
		registry->Complete();
	}

	// FUNCTION: ENGINE 0x10812120
	void MakeNISContext()
	{
		LoadListeners* listeners = gLoadListeners;
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(fight::Name(gNISContextName, 1));
		listeners->AddContext(registry);
		fight::RegisterCoreFactories(registry);
		fight::RegisterCommentTrackFactory(registry, "comment");
		fight::RegisterPrintTrackFactory(registry, "print");
		fight::RegisterTrackGroupTrackFactory(registry, "trackGroup");
		RegisterNISNodeBranchFactory(registry);
		RegisterNISRootNodeBranchFactory(registry);
		fight::RegisterNodeBranchFactory(registry);
		RegisterSpawnObjectTrackFactory(registry, "spawnObject");
		RegisterTeleportTrackFactory(registry, "teleport");
		RegisterLightTrackFactory(registry, "light");
		RegisterTimeDilationTrackFactory(registry, "timeDilation");
		RegisterEffectTrackFactory(registry, "effect");
		RegisterAbortEffectTrackFactory(registry, "abortEffect");
		RegisterMotionTrailTrackFactory(registry, "motionTrail");
		RegisterAudioTrackFactories(registry);
		RegisterSwapDrawableTrackFactory(registry, "swapDrawable");
		RegisterCameraAnimationTrackFactory(registry, "cameraAnimation");
		RegisterCameraClippingPlanesTrackFactory(registry, "cameraClipPlanes");
		RegisterExplicitLightAnimationTrackFactory(registry, "lightAnimation");
		RegisterSequenceNISNodeTrackFactory(registry, "SequenceNISNode");
		scenario::RegisterLuaTrackFactory(registry, "lua");
		RegisterNISAnimationTrackFactory(registry, "animation");
		animation::RegisterAttachObjectTrackFactory(registry, "attachObject");
		animation::RegisterDetachObjectTrackFactory(registry, "detachObject");
		animation::RegisterDetachFromParentTrackFactory(registry, "detachFromParent");
		animation::RegisterShaderAnimationTrackFactory(registry, "shaderAnimation");
		framebufferfx::RegisterDepthOfFieldTrackFactory(registry, "depthOfField");
		framebufferfx::RegisterBloomTrackFactory(registry, "bloom");
		framebufferfx::RegisterColourMatrixTrackFactory(registry, "colourMatrix");
		framebufferfx::RegisterScatterTrackFactory(registry, "scatter");
		framebufferfx::RegisterToneMapTrackFactory(registry, "toneMap");
		framebufferfx::RegisterFadeTrackFactory(registry, "fade");
		framebufferfx::RegisterLetterboxTrackFactory(registry, "letterbox");
		RegisterExplicitPrimitiveVisibilityTrackFactory(registry, "visibility");
		RegisterExplicitSetObjectLightGroupTrackFactory(registry, "setLightGroup");
		RegisterSubTitleTrackFactory(registry, "subtitle");
		RegisterNISExecuteTrackFactory(registry, "execute");
		registry->Prepare();
		registry->Complete();
	}

	// FUNCTION: ENGINE 0x10812310
	void MakeAIContext()
	{
		LoadListeners* listeners = gLoadListeners;
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(fight::Name("AI", 1));
		listeners->AddContext(registry);
		fight::RegisterBranchFactories(registry);
		fight::RegisterCoreFactories(registry);
		fight::RegisterCoreTrackFactories(registry);
		fight::RegisterFlowTrackFactories(registry);
		fight::RegisterEventTrackFactory(registry, "onEvent");
		registry->Prepare();
		registry->Complete();
	}

	// FUNCTION: ENGINE 0x10812610
	// EQUIVALENT: the engine loads the new loader's vftable before it stores the pointer in the global, ours stores
	// first (four times, 97.0 %); the calls and their order are the same
	void StartFightSystem(const FightSystemParams* params)
	{
		fight::SetHeapId(0, params->heap0);
		fight::SetHeapId(1, params->heap1);
		fight::SetHeapId(2, params->heap2);
		LoadListeners* listeners = CreateLoadListeners();
		if (listeners != 0)
		{
			int heap = core::SetCurrentHeap(fight::GetHeapId(0));
			fight::SetPlatformCallback(AlwaysTrue, 0);
			fight::SetRandomCallback(DrawRandom, 0);
			content::LoadManager* manager = content::gLoadManager;
			if (manager != 0)
			{
				fight::FileLoader* fileLoader = new fight::FileLoader(false);
				gFightFileLoader = fileLoader;
				fileLoader->AddRef();
				manager->AddFileLoader(gFightFileLoader, "fig");
				fileLoader = new fight::FileLoader(true);
				gFightBinaryFileLoader = fileLoader;
				fileLoader->AddRef();
				manager->AddFileLoader(gFightBinaryFileLoader, "fib");
				fight::FightChunkP3DLoader* chunkLoader = new fight::FightChunkP3DLoader;
				gFightChunkLoader = chunkLoader;
				chunkLoader->AddRef();
				manager->AddLoader(gFightChunkLoader, 0x20000701);
				fight::LegacyFightChunkP3DLoader* legacyLoader = new fight::LegacyFightChunkP3DLoader;
				gLegacyFightChunkLoader = legacyLoader;
				legacyLoader->AddRef();
				manager->AddLoader(gLegacyFightChunkLoader, 0x20000700);
			}
			core::SetCurrentHeap(heap);
		}
		LuaScriptManager* script = GetScriptManager();
		script->SetOwner(listeners);
		script->Register("fight_ResolveBranchRefs", ResolveBranchRefs);
		script->ClearOwner();
	}

	// FUNCTION: ENGINE 0x10812800
	// The tracks of the motion and the playback contexts (the registry is in a register)
	static void RegisterMotionTracks(fight::TrackRegistry* registry)
	{
		RegisterAudioTrackFactories(registry);
		RegisterOnlineConditionFactories(registry);
		{
			fight::TrackFactoryCasterTemplate<ExitTrack> caster;
			registry->AddFactory(fight::FindTrackFactory("exit", &caster));
		}
		RegisterPlaybackStateConditionFactory(registry, "playbackState");
		RegisterPlaybackTrackFactory(registry, gPlaybackTrackName);
		animation::RegisterExpressionAnimationTrackFactory(registry, "expressionAnimation");
		animation::RegisterEnableMotionTrackedExpressionTrackFactory(registry, "enableMotionTrackedExpression");
		animation::RegisterDisableMotionTrackedExpressionTrackFactory(registry, "disableMotionTrackedExpression");
		RegisterPuppetAnimationTrackFactory(registry, "animation");
		animation::RegisterShaderAnimationTrackFactory(registry, "shaderAnimation");
		animation::RegisterAttachObjectTrackFactory(registry, "attachObject");
		animation::RegisterDetachObjectTrackFactory(registry, "detachObject");
		animation::RegisterDetachFromParentTrackFactory(registry, "detachFromParent");
		RegisterSimpleMessageTrackFactory(registry, "simpleMessage");
		RegisterPrimitiveVisibilityTrackFactory(registry, "primitiveDisplaySimple");
		RegisterSetObjectLightGroupTrackFactory(registry, "setLightGroup");
		fight::RegisterCoreFactories(registry);
		fight::RegisterCoreTrackFactories(registry);
		fight::RegisterFlowTrackFactories(registry);
		fight::RegisterEventTrackFactory(registry, "onEvent");
		RegisterLightAnimationTrackFactory(registry, "lightAnimation");
	}

	// FUNCTION: ENGINE 0x10812900
	// The conditions and the few tracks of the prop logic context (the registry is in a register)
	static void RegisterPropLogicFactories(fight::TrackRegistry* registry)
	{
		fight::RegisterCoreFactories(registry);
		fight::RegisterCoreTrackFactories(registry);
		RegisterAudioTrackFactories(registry);
		RegisterOnlineConditionFactories(registry);
		{
			fight::ConditionFactoryCasterTemplate<MessageCondition> caster;
			registry->AddFactory(fight::FindConditionFactory("message", &caster));
		}
		RegisterHealthConditionFactory(registry, "health");
		RegisterPlaybackStateConditionFactory(registry, "playbackState");
		{
			fight::ConditionFactoryCasterTemplate<PrintMessageCondition> caster;
			registry->AddFactory(fight::FindConditionFactory("printMessage", &caster));
		}
		RegisterAnimationControlTrackFactory(registry, "animationControl");
		RegisterPlaybackTrackFactory(registry, gPlaybackTrackName);
		RegisterPrimitiveVisibilityTrackFactory(registry, "primitiveDisplaySimple");
		RegisterSetRotationAttributeTrackFactory(registry, "setRotationAttribute");
		RegisterSetTransformAttributeTrackFactory(registry, "setTransformAttribute");
		RegisterSimpleMessageTrackFactory(registry, "simpleMessage");
		RegisterScenarioStringTrackFactory(registry, "scenarioStringEvent");
	}

	// FUNCTION: ENGINE 0x108129D0
	void MakePropLogicContext()
	{
		LoadListeners* listeners = gLoadListeners;
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(fight::Name(gPropLogicContextName, 1));
		listeners->AddContext(registry);
		fight::RegisterBranchFactories(registry);
		RegisterPropLogicFactories(registry);
		fight::RegisterFlowTrackFactories(registry);
		fight::RegisterEventTrackFactory(registry, "onMessage");
		registry->Prepare();
		registry->Complete();
	}

	// FUNCTION: ENGINE 0x10812A50
	void MakeMotionContext()
	{
		LoadListeners* listeners = gLoadListeners;
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(fight::Name(gMotionContextName, 1));
		listeners->AddContext(registry);
		fight::RegisterBranchFactories(registry);
		{
			fight::ConditionFactoryCasterTemplate<MessageCondition> caster;
			registry->AddFactory(fight::FindConditionFactory("message", &caster));
		}
		RegisterAttributeNameConditionFactory(registry, "attributeName");
		animation::RegisterPuppetPhaseConditionFactory(registry, "puppetPhase");
		animation::RegisterVelocityConditionFactory(registry, "velocity");
		animation::RegisterVelocityAngularConditionFactory(registry, "velocityAngular");
		scenario::RegisterLuaConditionFactory(registry, "lua");
		RegisterHealthConditionFactory(registry, "health");
		RegisterObjectTemplateConditionFactory(registry, "objectTemplate");
		RegisterPCKeyboardConditionFactory(registry, "pckeyboard");
		RegisterMotionTracks(registry);
		RegisterCharacterTrackFactories(registry);
		RegisterEffectTrackFactory(registry, "effect");
		RegisterAbortEffectTrackFactory(registry, "abortEffect");
		RegisterEffectLODBiasTrackFactory(registry, "effectLODBias");
		RegisterEffectLODSwitchTrackFactory(registry, "effectLODSwitch");
		RegisterEffectLODDisableTrackFactory(registry, "effectLODDisable");
		RegisterLightTrackFactory(registry, "light");
		RegisterMotionTrailTrackFactory(registry, "motionTrail");
		RegisterUndamageableTrackFactory(registry, "undamageable");
		RegisterScenarioStringTrackFactory(registry, "scenarioStringEvent");
		animation::RegisterJointLockTrackFactory(registry, "jointLock");
		animation::RegisterPuppetMoveTrackFactory(registry, "move");
		scenario::RegisterLuaTrackFactory(registry, "lua");
		RegisterPhysicsTrackFactories(registry);
		framebufferfx::RegisterToneMapTrackFactory(registry, "FX_toneMap");
		framebufferfx::RegisterDepthOfFieldTrackFactory(registry, "FX_depthOfField");
		framebufferfx::RegisterBloomTrackFactory(registry, "FX_bloom");
		framebufferfx::RegisterScatterTrackFactory(registry, "FX_scatter");
		framebufferfx::RegisterColourMatrixTrackFactory(registry, "FX_colourMatrix");
		registry->Prepare();
		registry->Complete();
	}
}
