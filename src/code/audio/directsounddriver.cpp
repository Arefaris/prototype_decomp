// The audio renderer driver of the DirectSound devices (0x10ABCF20 - 0x10AC0000): the slots of the driver class and the
// forms of its enumerations in text and binary form.
#include "code/audio/drivers.h"
#include "code/om/invoke.h"
#include "code/om/metaproperty.h"

namespace audio
{
	// 0x113276D4
	char DirectSoundRendererDriverImpl::unknownStatic;

	// FUNCTION: ENGINE 0x10ABCFB0
	const char* DirectSoundRendererDriverImpl::Slot1()
	{
		return &unknownStatic;
	}

	// FUNCTION: ENGINE 0x10ABCFC0
	bool DirectSoundRendererDriverImpl::Slot5()
	{
		return thread.IsCurrentThread();
	}

	// FUNCTION: ENGINE 0x10ABCFE0
	int DirectSoundRendererDriverImpl::Slot17()
	{
		return unknown254;
	}

	// FUNCTION: ENGINE 0x10ABEF40
	om::MetaTypeBase* DirectSoundRendererDriverImpl::GetMetaType()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<DirectSoundRendererDriverImpl>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(DirectSoundRendererDriverImpl));
		}
		return cache;
	}
}

namespace om
{
	// FUNCTION: ENGINE 0x10ABE9E0
	template void WriteResult<audio::BufferLocation>(BinaryStream*, const audio::BufferLocation&);
	// FUNCTION: ENGINE 0x10ABEA10
	template void WriteResult<audio::MixType>(BinaryStream*, const audio::MixType&);
	// FUNCTION: ENGINE 0x10ABEA40
	template void WriteResult<audio::Focus>(BinaryStream*, const audio::Focus&);
	// FUNCTION: ENGINE 0x10ABEB60
	template bool ReadText<audio::BufferLocation>(const TextValue*, audio::BufferLocation*);
	// FUNCTION: ENGINE 0x10ABEB90
	template void WriteText<audio::BufferLocation>(TextValue*, const audio::BufferLocation&);
	// FUNCTION: ENGINE 0x10ABEBC0
	template bool ReadText<audio::MixType>(const TextValue*, audio::MixType*);
	// FUNCTION: ENGINE 0x10ABEBF0
	template void WriteText<audio::MixType>(TextValue*, const audio::MixType&);
	// FUNCTION: ENGINE 0x10ABEC20
	template bool ReadText<audio::Focus>(const TextValue*, audio::Focus*);
	// FUNCTION: ENGINE 0x10ABEC50
	template void WriteText<audio::Focus>(TextValue*, const audio::Focus&);
	// FUNCTION: ENGINE 0x10ABFD90
	template bool ReadBinary<audio::BufferLocation>(BinaryStream*, audio::BufferLocation*);
	// FUNCTION: ENGINE 0x10ABFDC0
	template bool ReadBinary<audio::MixType>(BinaryStream*, audio::MixType*);
	// FUNCTION: ENGINE 0x10ABFDF0
	template bool ReadBinary<audio::Focus>(BinaryStream*, audio::Focus*);
	// FUNCTION: ENGINE 0x10ABFE20
	template bool WriteBinary<audio::BufferLocation>(BinaryStream*, const audio::BufferLocation&);
	// FUNCTION: ENGINE 0x10ABFE50
	template bool WriteBinary<audio::MixType>(BinaryStream*, const audio::MixType&);
	// FUNCTION: ENGINE 0x10ABFE80
	template bool WriteBinary<audio::Focus>(BinaryStream*, const audio::Focus&);
}
