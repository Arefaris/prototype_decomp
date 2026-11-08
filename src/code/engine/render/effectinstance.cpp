// The effect instance's unit (0x10820010 - 0x10821720, no assert path; the file name is a guess): what a drawable effect
// is made from, and the records of the effects that play.
#include "code/core/refptr.h"
#include "code/engine/render/effectmanager.h"
#include "code/pure3d/drawable.h"
#include "code/math/pddicolour.h"

namespace engine
{
	namespace render
	{
		// FUNCTION: ENGINE 0x10820080
		// NONMATCHING: 31.7 %, the engine loads the two constants once into registers and stores them where they
		// belong; ours reloads one before every store
#ifdef NONMATCHING
		EffectSetup::EffectSetup()
			: unknown50(choreo::gMinusOne), biasUnknown(engine::driving::gOne), key(0), unknown5C(0.0f),
			unknown60(false), optionsA(engine::driving::gOne), optionsB(engine::driving::gOne),
			optionsC(choreo::gMinusOne), useStore(false),
			colour((int)math::pddiColour::WHITE.r * (1.0f / 255.0f), (int)math::pddiColour::WHITE.g * (1.0f / 255.0f),
				(int)math::pddiColour::WHITE.b * (1.0f / 255.0f), (int)math::pddiColour::WHITE.a * (1.0f / 255.0f)),
			storeDrawable(0xFFFFFFFF)
		{
		}
#endif
	
		// FUNCTION: ENGINE 0x108213D0
		EffectInstance::~EffectInstance()
		{
			core::SafeRelease<pure3d::Drawable>(particleDrawable);
			for (int i = 0; i < lodCount; i++)
			{
				lods.begin[i]->Release();
			}
			lods.end = lods.begin;
			if (lods.begin != 0)
			{
				delete[] lods.begin;
			}
		}

		// FUNCTION: ENGINE 0x10821420
		// NONMATCHING: 17.5 %, the same tests and calls; the engine lays the two failure exits out as one shared block
		// behind the store test and branches on the same flags the other way round
#ifdef NONMATCHING
		bool EffectInstance::AddLOD(EffectLOD* lod)
		{
			if (usesStore)
			{
				if (lod->kind != EFFECT_LOD_DISABLE)
				{
					goto fail;
				}
				lod->AddRef();
				lod->drawable = drawable;
			}
			else
			{
				if (fromStore && lodCount > 0)
				{
					goto fail;
				}
				if (lodCount == 8)
				{
					goto fail;
				}
				lod->AddRef();
				lod->drawable = drawable;
				if (lodCount == 0)
				{
					((EffectLODBias*)lod)->Apply();
					unknown8C = 0;
				}
			}
			lods.InsertSorted(&lod, CompareEffectLODs);
			lodCount = lods.end - lods.begin;
			return true;
		fail:
			lod->Release();
			return false;
		}
#endif
	}
}
