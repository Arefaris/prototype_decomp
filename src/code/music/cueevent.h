// The cue events of the music library (RTTI: music::CueEvent, music::CueEventDerived<T> and the events
// CueEventSetCurrentCuePlayer, CueEventSetCurrentCell, CueEventSetCurrentCue and CueEventSync): small messages that
// are read and written in binary form through the reflection of their own class. Every event class derives from
// CueEventDerived<itself>, which answers slots 3 and 4 with the description of that class.
#ifndef MUSIC_CUEEVENT_H
#define MUSIC_CUEEVENT_H

#include "code/om/allocation.h"
#include "code/om/metaclass.h"

namespace music
{
	class CueEvent
	{
	public:
		// Inlined by the derived classes (the engine's own copies are 0x105D2880 and 0x105D2A60)
		CueEvent()
		{
		}
		virtual ~CueEvent()
		{
		}
		// Slots 1 and 2 (0x105D28B0 / 0x105D28D0): read and write the event through its description
		virtual void Read(om::BinaryStream* stream);
		virtual void Write(om::BinaryStream* stream);
		// Slots 3 and 4 (0x105D2900 / 0x105D28F0): the description of the event's class, none here
		virtual om::MetaClassBase* GetMetaClassForWrite();
		virtual om::MetaClassBase* GetMetaClassForRead();
		OM_ALLOCATION(CueEvent);

		int unknown4;
	};

	template<class T> class CueEventDerived : public CueEvent
	{
	public:
		CueEventDerived()
		{
		}
		virtual ~CueEventDerived()
		{
		}
		virtual om::MetaClassBase* GetMetaClassForWrite();
		virtual om::MetaClassBase* GetMetaClassForRead();
		OM_ALLOCATION(CueEventDerived);
	};

	class CueEventSetCurrentCuePlayer : public CueEventDerived<CueEventSetCurrentCuePlayer>
	{
	public:
		// 0x105D30B0 / 0x105D30F0
		CueEventSetCurrentCuePlayer(const om::ClassName& newPlayer);
		virtual ~CueEventSetCurrentCuePlayer();
		OM_ALLOCATION(CueEventSetCurrentCuePlayer);

		om::ClassName player;  // 8
	};

	class CueEventSetCurrentCell : public CueEventDerived<CueEventSetCurrentCell>
	{
	public:
		// 0x105D3180 / 0x105D31C0
		CueEventSetCurrentCell(unsigned int newFirst, unsigned int newSecond);
		virtual ~CueEventSetCurrentCell();
		// 0x105D2A90 / 0x105D2AA0
		void SetFirst(const unsigned int& newFirst);
		void SetSecond(const unsigned int& newSecond);
		OM_ALLOCATION(CueEventSetCurrentCell);

		unsigned int first;  // 8
		unsigned int second;  // 0xC
	};

	class CueEventSetCurrentCue : public CueEventDerived<CueEventSetCurrentCue>
	{
	public:
		// 0x105D5550 / 0x105D5590
		CueEventSetCurrentCue(const om::ClassName& newCue);
		virtual ~CueEventSetCurrentCue();
		OM_ALLOCATION(CueEventSetCurrentCue);

		om::ClassName cue;  // 8
	};

	class CueEventSync : public CueEventDerived<CueEventSync>
	{
	public:
		// 0x105D5640 / 0x105D5680
		CueEventSync(const CueEventSetCurrentCue& event);
		virtual ~CueEventSync();
		OM_ALLOCATION(CueEventSync);

		om::ClassName cue;  // 8
	};

	template<class T> om::MetaClassBase* CueEventDerived<T>::GetMetaClassForWrite()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<T>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(T));
		}
		return static_cast<om::MetaClassBase*>(cache);
	}

	template<class T> om::MetaClassBase* CueEventDerived<T>::GetMetaClassForRead()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<T>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(T));
		}
		return static_cast<om::MetaClassBase*>(cache);
	}

	template<class T> const char* CueEventDerived<T>::AllocationTag()
	{
		return "";
	}
}

#endif
