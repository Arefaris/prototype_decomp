// The music library's cue events (0x105D2880 - 0x105D56F0, between the cell player's code): the base class and the
// events that set the current cue player, cell and cue and the one that synchronises.
#include "code/music/cueevent.h"

namespace music
{
	// FUNCTION: ENGINE 0x105D28B0
	void CueEvent::Read(om::BinaryStream* stream)
	{
		GetMetaClassForRead()->ReadBinary(stream, this);
	}

	// FUNCTION: ENGINE 0x105D28D0
	void CueEvent::Write(om::BinaryStream* stream)
	{
		GetMetaClassForWrite()->WriteBinary(stream, this);
	}

	// FUNCTION: ENGINE 0x105D2900
	om::MetaClassBase* CueEvent::GetMetaClassForWrite()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x105D28F0
	om::MetaClassBase* CueEvent::GetMetaClassForRead()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x105D2E40
	const char* CueEvent::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D30B0
	CueEventSetCurrentCuePlayer::CueEventSetCurrentCuePlayer(const om::ClassName& newPlayer) :
		player(newPlayer)
	{
	}

	// FUNCTION: ENGINE 0x105D30F0
	CueEventSetCurrentCuePlayer::~CueEventSetCurrentCuePlayer()
	{
	}

	// FUNCTION: ENGINE 0x105D2EA0
	const char* CueEventSetCurrentCuePlayer::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D3180
	CueEventSetCurrentCell::CueEventSetCurrentCell(unsigned int newFirst, unsigned int newSecond) :
		first(newFirst),
		second(newSecond)
	{
	}

	// FUNCTION: ENGINE 0x105D31C0
	CueEventSetCurrentCell::~CueEventSetCurrentCell()
	{
	}

	// FUNCTION: ENGINE 0x105D2A90
	void CueEventSetCurrentCell::SetFirst(const unsigned int& newFirst)
	{
		first = newFirst;
	}

	// FUNCTION: ENGINE 0x105D2AA0
	void CueEventSetCurrentCell::SetSecond(const unsigned int& newSecond)
	{
		second = newSecond;
	}

	// FUNCTION: ENGINE 0x105D2EB0
	const char* CueEventSetCurrentCell::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D5550
	CueEventSetCurrentCue::CueEventSetCurrentCue(const om::ClassName& newCue) :
		cue(newCue)
	{
	}

	// FUNCTION: ENGINE 0x105D5590
	CueEventSetCurrentCue::~CueEventSetCurrentCue()
	{
	}

	// FUNCTION: ENGINE 0x105D51D0
	const char* CueEventSetCurrentCue::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D5640
	CueEventSync::CueEventSync(const CueEventSetCurrentCue& event) :
		cue(event.cue)
	{
	}

	// FUNCTION: ENGINE 0x105D5680
	CueEventSync::~CueEventSync()
	{
	}

	// FUNCTION: ENGINE 0x105D51F0
	const char* CueEventSync::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D2880
	template CueEventDerived<CueEventSetCurrentCell>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105D2890
	template void CueEventDerived<CueEventSetCurrentCell>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D2A70
	template CueEventDerived<CueEventSetCurrentCuePlayer>::CueEventDerived();
	// FUNCTION: ENGINE 0x105D2AB0
	template CueEventDerived<CueEventSetCurrentCell>::CueEventDerived();
	// FUNCTION: ENGINE 0x105D2AC0
	template CueEventDerived<CueEventSetCurrentCuePlayer>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105D2D30
	template void CueEventDerived<CueEventSetCurrentCuePlayer>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D2E90
	template const char* CueEventDerived<CueEventSetCurrentCell>::AllocationTag();
	// FUNCTION: ENGINE 0x105D3E40
	template om::MetaClassBase* CueEventDerived<CueEventSetCurrentCuePlayer>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105D3E60
	template om::MetaClassBase* CueEventDerived<CueEventSetCurrentCuePlayer>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105D3E80
	template om::MetaClassBase* CueEventDerived<CueEventSetCurrentCell>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105D3EA0
	template om::MetaClassBase* CueEventDerived<CueEventSetCurrentCell>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105D4E40
	template CueEventDerived<CueEventSetCurrentCue>::CueEventDerived();
	// FUNCTION: ENGINE 0x105D4E50
	template CueEventDerived<CueEventSetCurrentCue>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105D4F40
	template CueEventDerived<CueEventSync>::CueEventDerived();
	// FUNCTION: ENGINE 0x105D4F50
	template CueEventDerived<CueEventSync>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105D50E0
	template void CueEventDerived<CueEventSetCurrentCue>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D5100
	template void CueEventDerived<CueEventSync>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D5180
	template const char* CueEventDerived<CueEventSetCurrentCue>::AllocationTag();
	// FUNCTION: ENGINE 0x105D5190
	template const char* CueEventDerived<CueEventSync>::AllocationTag();
	// FUNCTION: ENGINE 0x105D61B0
	template om::MetaClassBase* CueEventDerived<CueEventSetCurrentCue>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105D61D0
	template om::MetaClassBase* CueEventDerived<CueEventSetCurrentCue>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105D61F0
	template om::MetaClassBase* CueEventDerived<CueEventSync>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105D6210
	template om::MetaClassBase* CueEventDerived<CueEventSync>::GetMetaClassForWrite();
}
