// The fight track that shows and hides the primitives of an object's drawable (engine::PrimitiveDisplayTrack, code/engine/
// fight/primitivedisplaytrack.cpp; the file name is a guess, the unit starts at 0x108AEDB0 and has no assert path) and
// its action. Names are guesses unless the RTTI gives them.
#include "code/engine/fight/primitivedisplaytrack.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/playbackset.h"
#include <new>

namespace fight
{
	// FUNCTION: ENGINE 0x108AF0D0
	int PropertyTypePropertyList::GetType() const
	{
		return 0x11;
	}

	template class PropertyPropertyList<engine::PrimitiveDisplayTrack>;
}

namespace engine
{
	// The texts the properties are named with (0x111D74B4 / 0x111D74B0; the engine keeps them in pointers)
	extern const char* const gPrimitiveDisplayTimeBeginText;
	extern const char* const gPrimitiveDisplayCountText;

	// FUNCTION: ENGINE 0x108AF170
	bool PrimitiveDisplayTrackPropertyTimeBegin::Set(void* object, float newValue)
	{
		value = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AF160
	float PrimitiveDisplayTrackPropertyTimeBegin::GetValue(void* object)
	{
		return value;
	}

	// FUNCTION: ENGINE 0x108AEE30
	const fight::EnumEntry* PrimitiveDisplayTrackPropertyEnumPrimitiveDisplay::GetEntry(void* object, int index)
	{
		if ((unsigned int)index <= 2)
		{
			return &gOnTable[index];
		}
		return (const fight::EnumEntry*)&gEmpty81;
	}

	// FUNCTION: ENGINE 0x108AEE20
	int PrimitiveDisplayTrackPropertyEnumPrimitiveDisplay::GetCount(void* object) const
	{
		return 3;
	}

	// FUNCTION: ENGINE 0x108AF120
	bool PrimitiveDisplayTrackPropertyEnumPrimitiveDisplay::Set(void* object, int newValue)
	{
		value = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AF110
	int PrimitiveDisplayTrackPropertyEnumPrimitiveDisplay::GetValue(void* object)
	{
		return value;
	}

	// FUNCTION: ENGINE 0x108AEDB0
	int PrimitiveDisplayTrack::GetPrimitiveCount()
	{
		return primitiveCount;
	}

	// FUNCTION: ENGINE 0x108AEE50
	fight::Property* PrimitiveDisplayTrack::GetPrimitive(int index)
	{
		fight::Property* result = 0;
		if (index >= 0 && index < primitiveCount)
		{
			result = &primitives[index];
		}
		return result;
	}

	// FUNCTION: ENGINE 0x108AEE70
	fight::Property* PrimitiveDisplayTrack::GetProperty(int index)
	{
		fight::Property* result = 0;
		if (index >= 0 && index < primitiveCount + 1)
		{
			if (index != 0)
			{
				return &primitives[index - 1];
			}
			result = &timeBegin;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x108AEEA0
	fight::Property* PrimitiveDisplayTrack::Slot1(int index)
	{
		fight::Property* property = 0;
		if (index == 0)
		{
			return &timeBegin;
		}
		if (index == 1)
		{
			property = &primitiveList;
		}
		return property;
	}

	// FUNCTION: ENGINE 0x108AEFF0
	void PrimitiveDisplayTrack::RegisterProperties()
	{
	}

	// FUNCTION: ENGINE 0x108AF000
	void PrimitiveDisplayTrack::ClearProperties()
	{
	}

	// FUNCTION: ENGINE 0x108AF350
	// NONMATCHING: the engine's array new puts a four-byte count in front of the items where ours puts eight (the property base is declared 8-aligned; 98.4 %)
#ifdef NONMATCHING
	bool PrimitiveDisplayTrack::SetPrimitiveCount(int newCount)
	{
		FreePrimitives();
		primitives = 0;
		primitiveCount = newCount;
		primitives = new PrimitiveDisplayTrackPropertyEnumPrimitiveDisplay[newCount];
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x108AF320
	void PrimitiveDisplayTrack::ClearPrimitives()
	{
		FreePrimitives();
		primitives = 0;
		primitiveCount = 0;
	}

	// FUNCTION: ENGINE 0x108AF790
	void PrimitiveDisplayTrack::Reset()
	{
		fight::PropertyTypeFloat* property = &timeBegin;
		property->Set(0, 0.0f);
		FreePrimitives();
		primitives = 0;
		primitiveCount = 0;
	}

	// FUNCTION: ENGINE 0x108AF7D0
	PrimitiveDisplayTrack::PrimitiveDisplayTrack()
		: timeBegin(gPrimitiveDisplayTimeBeginText), primitives(0), primitiveCount(0),
		primitiveList(gPrimitiveDisplayCountText, &PrimitiveDisplayTrack::GetPrimitiveCount, &PrimitiveDisplayTrack::GetPrimitive, &PrimitiveDisplayTrack::SetPrimitiveCount)
	{
	}

	// FUNCTION: ENGINE 0x108AF860
	// NONMATCHING: the engine stores the vftable between the arguments of the call and loads the property's vftable first (39.7 %)
#ifdef NONMATCHING
	PrimitiveDisplayTrack::~PrimitiveDisplayTrack()
	{
		fight::PropertyTypeFloat* property = &timeBegin;
		property->Set(0, 0.0f);
		FreePrimitives();
		primitives = 0;
		primitiveCount = 0;
	}
#endif

	// FUNCTION: ENGINE 0x108AEF40
	void PrimitiveDisplayTrack::Slot3(int arg)
	{
		fight::Track::Slot3(arg);
		PlaybackSet* set = 0;
		for (fight::Branch* branch = ((fight::Branch*)arg)->parent; branch != 0 && set == 0; branch = branch->parent)
		{
			set = dynamic_cast<PlaybackSet*>(branch);
		}
	}

	// FUNCTION: ENGINE 0x108AF840
	float PrimitiveDisplayTrack::GetTimeBegin() const
	{
		return const_cast<PrimitiveDisplayTrackPropertyTimeBegin&>(timeBegin).GetValue(0);
	}

	// FUNCTION: ENGINE 0x108AF850
	float PrimitiveDisplayTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108AF8B0
	fight::Action* PrimitiveDisplayTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PrimitiveDisplayAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108AF400
	PrimitiveDisplayAction::PrimitiveDisplayAction(PrimitiveDisplayTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xe00), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x108AF1E0
	PrimitiveDisplayAction::~PrimitiveDisplayAction()
	{
	}

	template class fight::TrackFactoryTemplate<PrimitiveDisplayTrack>;
	template class fight::TrackFactoryCasterTemplate<PrimitiveDisplayTrack>;

	// FUNCTION: ENGINE 0x108AF300
	fight::TrackFactory* CreatePrimitiveDisplayTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PrimitiveDisplayTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AF3D0
	void RegisterPrimitiveDisplayTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PrimitiveDisplayTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}
}

// Kept copies (template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108AEF80
// FUNCTION: ENGINE 0x108AEFA0
// FUNCTION: ENGINE 0x108AEFE0
// FUNCTION: ENGINE 0x108AF010
// FUNCTION: ENGINE 0x108AF040
// FUNCTION: ENGINE 0x108AF070
// FUNCTION: ENGINE 0x108AF0B0
// FUNCTION: ENGINE 0x108AF130
// FUNCTION: ENGINE 0x108AF210
// FUNCTION: ENGINE 0x108AF240
// FUNCTION: ENGINE 0x108AF250
// FUNCTION: ENGINE 0x108AF270
// FUNCTION: ENGINE 0x108AF290
// FUNCTION: ENGINE 0x108AF8F0
