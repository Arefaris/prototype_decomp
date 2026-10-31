// The content loaders and load objects of the om entities of the audio, music and graph libraries (0x10AAC1D0 -
// 0x10AAD260): the template instances of om::AtgContentEntityLoader<T> and om::AtgContentEntity<T>.
#include "code/audio/drivers.h"
#include "code/audio/mix.h"
#include "code/mgraph/patch.h"
#include "code/music/cue.h"
#include "code/om/atgcontent.h"

#pragma warning(disable: 4661)

namespace om
{
	// FUNCTION: ENGINE 0x10AAC670
	AtgContentEntityBase::AtgContentEntityBase(Entity* newEntity)
	{
		reference.entity = newEntity;
		if (newEntity != 0)
		{
			ThreadSafeRefCount::AddRef(&newEntity->count);
		}
	}

	// FUNCTION: ENGINE 0x10AAC200
	// NONMATCHING: the entity's slot answers a byte that the engine normalises to 0 or 1, ours passes the bool on in a tail call (52.9 %)
#ifdef NONMATCHING
	bool AtgContentEntityBase::IsReady()
	{
		return reference.entity->Slot1();
	}
#endif

	// FUNCTION: ENGINE 0x10AAC220
	void AtgContentEntityBase::Slot3(int unused)
	{
		StreamContext context;
		context.Set(GetStreamContextObject(), GetStreamContextObject(), GetStreamContextObject(), GetStreamContextObject());
		StreamContext* pointer = &context;
		reference.entity->Slot8(&pointer);
	}

	// FUNCTION: ENGINE 0x10AAC3D0
	AtgContentEntityLoaderBase::AtgContentEntityLoaderBase(EntityTypeBase* newType) :
		entityType(newType)
	{
	}

	// FUNCTION: ENGINE 0x10AAC740
	template char const* AtgContentEntityLoader<audio::Mix>::AllocationTag();
	// FUNCTION: ENGINE 0x10AAC750
	template char const* AtgContentEntityLoader<mgraph::Patch>::AllocationTag();
	// FUNCTION: ENGINE 0x10AAC760
	template char const* AtgContentEntityLoader<audio::AudioFile>::AllocationTag();
	// FUNCTION: ENGINE 0x10AAC770
	template char const* AtgContentEntityLoader<music::Cue>::AllocationTag();
	// FUNCTION: ENGINE 0x10AAC850
	template void* AtgContentEntityLoader<audio::Mix>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AAC870
	template void* AtgContentEntityLoader<mgraph::Patch>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AAC890
	template void* AtgContentEntityLoader<audio::AudioFile>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AAC8B0
	template void* AtgContentEntityLoader<music::Cue>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AAC8F0
	template AtgContentEntityLoader<audio::Mix>::AtgContentEntityLoader();
	// FUNCTION: ENGINE 0x10AAC930
	template void AtgContentEntityLoader<audio::Mix>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AAC950
	template char const* AtgContentEntity<audio::Mix>::AllocationTag();
	// FUNCTION: ENGINE 0x10AAC960
	template AtgContentEntityLoader<mgraph::Patch>::~AtgContentEntityLoader();
	// FUNCTION: ENGINE 0x10AAC970
	template void* AtgContentEntity<audio::Mix>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AAC990
	template AtgContentEntityLoader<mgraph::Patch>::AtgContentEntityLoader();
	// FUNCTION: ENGINE 0x10AAC9C0
	template void AtgContentEntityLoader<mgraph::Patch>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AAC9E0
	template char const* AtgContentEntity<mgraph::Patch>::AllocationTag();
	// FUNCTION: ENGINE 0x10AAC9F0
	template AtgContentEntityLoader<audio::AudioFile>::~AtgContentEntityLoader();
	// FUNCTION: ENGINE 0x10AACA00
	template void* AtgContentEntity<mgraph::Patch>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AACA20
	template AtgContentEntityLoader<audio::AudioFile>::AtgContentEntityLoader();
	// FUNCTION: ENGINE 0x10AACA50
	template void AtgContentEntityLoader<audio::AudioFile>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AACA70
	template char const* AtgContentEntity<audio::AudioFile>::AllocationTag();
	// FUNCTION: ENGINE 0x10AACA80
	template AtgContentEntityLoader<music::Cue>::~AtgContentEntityLoader();
	// FUNCTION: ENGINE 0x10AACA90
	template void* AtgContentEntity<audio::AudioFile>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AACAB0
	template AtgContentEntityLoader<music::Cue>::AtgContentEntityLoader();
	// FUNCTION: ENGINE 0x10AACAE0
	template void AtgContentEntityLoader<music::Cue>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AACB00
	template char const* AtgContentEntity<music::Cue>::AllocationTag();
	// FUNCTION: ENGINE 0x10AACB10
	template AtgContentEntityLoader<audio::Mix>::~AtgContentEntityLoader();
	// FUNCTION: ENGINE 0x10AACB20
	template void* AtgContentEntity<music::Cue>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AACDE0
	template AtgContentEntity<audio::Mix>::AtgContentEntity(Entity*);
	// FUNCTION: ENGINE 0x10AACE00
	template void AtgContentEntity<audio::Mix>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AACE20
	template AtgContentEntity<audio::Mix>::~AtgContentEntity();
	// FUNCTION: ENGINE 0x10AACE60
	template AtgContentEntity<mgraph::Patch>::AtgContentEntity(Entity*);
	// FUNCTION: ENGINE 0x10AACE80
	template void AtgContentEntity<mgraph::Patch>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AACEA0
	template AtgContentEntity<mgraph::Patch>::~AtgContentEntity();
	// FUNCTION: ENGINE 0x10AACEE0
	template AtgContentEntity<audio::AudioFile>::AtgContentEntity(Entity*);
	// FUNCTION: ENGINE 0x10AACF00
	template void AtgContentEntity<audio::AudioFile>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AACF20
	template AtgContentEntity<audio::AudioFile>::~AtgContentEntity();
	// FUNCTION: ENGINE 0x10AACF60
	template AtgContentEntity<music::Cue>::AtgContentEntity(Entity*);
	// FUNCTION: ENGINE 0x10AACF80
	template void AtgContentEntity<music::Cue>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AACFA0
	template AtgContentEntity<music::Cue>::~AtgContentEntity();
	// FUNCTION: ENGINE 0x10AAD160
	template AtgContentEntityBase* AtgContentEntityLoader<audio::Mix>::CreateContent(Entity*);
	// FUNCTION: ENGINE 0x10AAD1A0
	template AtgContentEntityBase* AtgContentEntityLoader<mgraph::Patch>::CreateContent(Entity*);
	// FUNCTION: ENGINE 0x10AAD1E0
	template AtgContentEntityBase* AtgContentEntityLoader<audio::AudioFile>::CreateContent(Entity*);
	// FUNCTION: ENGINE 0x10AAD220
	template AtgContentEntityBase* AtgContentEntityLoader<music::Cue>::CreateContent(Entity*);
}
