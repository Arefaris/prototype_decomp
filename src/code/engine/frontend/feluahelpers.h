// engine::FELuaHelper (RTTI name, base engine::render::FlashDebugDrawCallback): the front end's helper functions for
// the scripts (fe_GetPlatformType and fe_ReleaseAssert). Unit 0x108E1BC0 - 0x108E20B0 (the assert path is
// code/engine/frontend/feluahelpers.cpp); names other than the RTTI ones and the script names are guesses.
#ifndef ENGINE_FRONTEND_FELUAHELPERS_H
#define ENGINE_FRONTEND_FELUAHELPERS_H

namespace engine
{
	namespace render
	{
		// RTTI: engine::render::FlashDebugDrawCallback (a struct with one pure vftable slot)
		struct FlashDebugDrawCallback
		{
			// 0x108E1BC0 (the engine's out-of-line copy)
			FlashDebugDrawCallback()
			{
			}
			virtual void Slot0() = 0;
		};
	}

	class FELuaHelper : public render::FlashDebugDrawCallback
	{
	public:
		// 0x108E1FB0: registers the script functions
		FELuaHelper();
		// 0x108E1BD0 (0x108E1CB0 deletes): takes them out again
		~FELuaHelper();

		// vftable slot 0 (0x108E1C10)
		virtual void Slot0()
		{
		}

		// 0x108E1CA0: fe_GetPlatformType
		const char* GetPlatformType();
		// 0x108E1C40: fe_ReleaseAssert, a report that stays in the final build
		void ReleaseAssert(bool ok, const char* message);
	};
}

#endif
