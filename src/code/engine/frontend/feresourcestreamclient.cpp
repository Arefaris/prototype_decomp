// engine::FEResourceStreamClient's text bible load objects (unit 0x10873290 - 0x10873560; no assert path, the file
// name is a guess).
#include <new>
#include "code/engine/frontend/feresourcestreamclient.h"
#include "code/scaleformp3d/resourcedictionary.h"

namespace engine
{
	// Whether the texts made for the keyboard are looked for first (0x111D0390, set at start-up; name guessed)
	extern bool gUseKeyboardTexts;

	// FUNCTION: ENGINE 0x108732E0
	void SetUseKeyboardTexts(bool value)
	{
		gUseKeyboardTexts = value;
	}

	// FUNCTION: ENGINE 0x10873F30
	const char* GetLocalizedText(const char* key)
	{
		core::Name<core::CaseSensitiveKey> name(key, 1);
		return gFEResourceStreamClient->GetText(name);
	}

	// FUNCTION: ENGINE 0x10873F60
	const char* GetSpeakerText(const core::Name<core::CaseSensitiveKey>& name)
	{
		return gFEResourceStreamClient->GetText(name);
	}

	// FUNCTION: ENGINE 0x108733D0
	// NONMATCHING: the engine pushes the size for the allocation behind the store of the reference count, ours before it, 90 %
#ifdef NONMATCHING
	FEResourceStreamClient::TextBibleStorage::TextBibleStorage(unsigned int newSize)
	{
		size = newSize;
		buffer = new char[newSize];
		cursor = buffer;
	}
#endif

	// FUNCTION: ENGINE 0x10873330
	FEResourceStreamClient::TextBibleStorage::~TextBibleStorage()
	{
		delete[] buffer;
	}

	// FUNCTION: ENGINE 0x10873350
	char* FEResourceStreamClient::TextBibleStorage::Take(int bytes)
	{
		char* start = cursor;
		cursor += bytes;
		return start;
	}

	// FUNCTION: ENGINE 0x10873360
	unsigned int FEResourceStreamClient::TextBibleStorage::GetSize() const
	{
		return size;
	}

	// FUNCTION: ENGINE 0x108734B0
	FEResourceStreamClient::TextBibleHolder::TextBibleHolder(TextBibleStorage* newStorage)
	{
		storage = newStorage;
		storage->AddRef();
	}

	// FUNCTION: ENGINE 0x10873370
	FEResourceStreamClient::TextBibleHolder::~TextBibleHolder()
	{
		storage->Release();
	}

	// FUNCTION: ENGINE 0x10873390
	FEResourceStreamClient::TextBibleStorage* FEResourceStreamClient::TextBibleHolder::GetStorage() const
	{
		return storage;
	}

	// FUNCTION: ENGINE 0x10873430
	// NONMATCHING: the engine pushes the size for the take behind the store of the reference count, ours before it, 87.2 %
#ifdef NONMATCHING
	FEResourceStreamClient::TextBibleEntry::TextBibleEntry(TextBibleSource* source, unsigned int length,
		TextBibleStorage* storage)
	{
		text = storage->Take(length + 1);
		source->stream->Read(text, length, 1, 1);
		text[length] = 0;
	}
#endif
}

// The lookups of the dictionaries and the texts by name (the filters the inventory is handed)
// FUNCTION: ENGINE 0x10873510
template class content::LoadInventory::DynamicCaster<scaleformp3d::ResourceDictionary>;
// FUNCTION: ENGINE 0x10873540
template class content::LoadInventory::DynamicCaster<engine::FEResourceStreamClient::TextBibleEntry>;
