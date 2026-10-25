// The music library's cue events (0x105D2880 - 0x105D56F0, between the cell player's code): the base class and the
// events that set the current cue player, cell and cue and the one that synchronises.
#include "code/music/cueevent.h"
#include "code/om/delegate.h"
#include "code/om/metaenum.h"
#include "code/om/metamethod.h"
#include "code/om/invoke.h"
#include "code/om/metaproperty.h"

#pragma warning(disable: 4661)

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

namespace music
{
	// FUNCTION: ENGINE 0x105D4DF0
	const om::ClassName& CueEventSetCurrentCuePlayer::GetCuePlayerName() const
	{
		return player;
	}

	// FUNCTION: ENGINE 0x105DC640
	void CueEventSetCurrentCuePlayer::SetCuePlayerName(const om::ClassName& newPlayer)
	{
		player = newPlayer;
	}

	// FUNCTION: ENGINE 0x105D4E10
	const unsigned int& CueEventSetCurrentCell::GetFirst() const
	{
		return first;
	}

	// FUNCTION: ENGINE 0x105D4E90
	const unsigned int& CueEventSetCurrentCell::GetSecond() const
	{
		return second;
	}

	// FUNCTION: ENGINE 0x105D4E20
	const om::ClassName& CueEventSetCurrentCue::GetCueName() const
	{
		return cue;
	}

	// FUNCTION: ENGINE 0x105DC660
	void CueEventSetCurrentCue::SetCueName(const om::ClassName& newCue)
	{
		cue = newCue;
	}

	// FUNCTION: ENGINE 0x105EBEC0
	unsigned __int64 CueEventSync::GetBarrierAsUint64() const
	{
		return cue.key;
	}

	// FUNCTION: ENGINE 0x105E2AD0
	void CueEventSync::SetBarrierAsUint64(unsigned __int64 newBarrier)
	{
		cue.key = newBarrier;
	}

	// FUNCTION: ENGINE 0x105D4E30
	const om::ClassName& CueEventNewCuePlayer::GetCuePlayerName() const
	{
		return cuePlayerName;
	}

	// FUNCTION: ENGINE 0x105EDA40
	void CueEventNewCuePlayer::SetCuePlayerName(const om::ClassName& newCuePlayerName)
	{
		cuePlayerName = newCuePlayerName;
	}

	// FUNCTION: ENGINE 0x105D4E00
	const om::ClassName& CueEventNewCuePlayer::GetCueName() const
	{
		return cueName;
	}

	// FUNCTION: ENGINE 0x105EDA60
	void CueEventNewCuePlayer::SetCueName(const om::ClassName& newCueName)
	{
		cueName = newCueName;
	}

	// FUNCTION: ENGINE 0x105ECE60
	const char* CueEventNewCuePlayer::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D4E60
	const om::ClassName& CueEventDestroyCuePlayer::GetCuePlayerName() const
	{
		return cuePlayerName;
	}

	// FUNCTION: ENGINE 0x105EDB50
	void CueEventDestroyCuePlayer::SetCuePlayerName(const om::ClassName& newCuePlayerName)
	{
		cuePlayerName = newCuePlayerName;
	}

	// FUNCTION: ENGINE 0x105ECE70
	const char* CueEventDestroyCuePlayer::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D4E70
	const om::ClassName& CueEventSetPartName::GetPartName() const
	{
		return partName;
	}

	// FUNCTION: ENGINE 0x105EDBF0
	void CueEventSetPartName::SetPartName(const om::ClassName& newPartName)
	{
		partName = newPartName;
	}

	// FUNCTION: ENGINE 0x105ECE80
	const char* CueEventSetPartName::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D4E80
	const om::ClassName& CueEventSetLayerName::GetLayerName() const
	{
		return layerName;
	}

	// FUNCTION: ENGINE 0x105EDC30
	void CueEventSetLayerName::SetLayerName(const om::ClassName& newLayerName)
	{
		layerName = newLayerName;
	}

	// FUNCTION: ENGINE 0x105ECE90
	const char* CueEventSetLayerName::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D4EA0
	const unsigned int& CueEventMoveCell::GetDestinationPartIndex() const
	{
		return destinationPartIndex;
	}

	// FUNCTION: ENGINE 0x105EBD70
	void CueEventMoveCell::SetDestinationPartIndex(const unsigned int& newDestinationPartIndex)
	{
		destinationPartIndex = newDestinationPartIndex;
	}

	// FUNCTION: ENGINE 0x105D4EB0
	const unsigned int& CueEventMoveCell::GetDestinationLayerIndex() const
	{
		return destinationLayerIndex;
	}

	// FUNCTION: ENGINE 0x105EBD80
	void CueEventMoveCell::SetDestinationLayerIndex(const unsigned int& newDestinationLayerIndex)
	{
		destinationLayerIndex = newDestinationLayerIndex;
	}

	// FUNCTION: ENGINE 0x105ECEA0
	const char* CueEventMoveCell::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D4EC0
	const unsigned int& CueEventMovePart::GetDestinationPartIndex() const
	{
		return destinationPartIndex;
	}

	// FUNCTION: ENGINE 0x105EBD90
	void CueEventMovePart::SetDestinationPartIndex(const unsigned int& newDestinationPartIndex)
	{
		destinationPartIndex = newDestinationPartIndex;
	}

	// FUNCTION: ENGINE 0x105D4ED0
	const unsigned int& CueEventMovePart::GetSourcePartIndex() const
	{
		return sourcePartIndex;
	}

	// FUNCTION: ENGINE 0x105EBDA0
	void CueEventMovePart::SetSourcePartIndex(const unsigned int& newSourcePartIndex)
	{
		sourcePartIndex = newSourcePartIndex;
	}

	// FUNCTION: ENGINE 0x105ECEB0
	const char* CueEventMovePart::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105EBF50
	CueEventCellPlayerState::CueEventCellPlayerState(const CellPlayer& player) :
		state(static_cast<CellPlayer::State>(player.state))
	{
	}

	// FUNCTION: ENGINE 0x105D4EE0
	const CellPlayer::State& CueEventCellPlayerState::GetState() const
	{
		return state;
	}

	// FUNCTION: ENGINE 0x105EBDC0
	void CueEventCellPlayerState::SetState(const CellPlayer::State& newState)
	{
		state = newState;
	}

	// FUNCTION: ENGINE 0x105D2EC0
	const char* CueEventCellPlayerState::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D4EF0
	const om::ClassName& CueEventSetCellType::GetCellTypeName() const
	{
		return cellTypeName;
	}

	// FUNCTION: ENGINE 0x105EDCC0
	void CueEventSetCellType::SetCellTypeName(const om::ClassName& newCellTypeName)
	{
		cellTypeName = newCellTypeName;
	}

	// FUNCTION: ENGINE 0x105D4F00
	const om::ClassName& CueEventSetCellType::GetCellInstanceName() const
	{
		return cellInstanceName;
	}

	// FUNCTION: ENGINE 0x105EE0C0
	void CueEventSetCellType::SetCellInstanceName(const om::ClassName& newCellInstanceName)
	{
		cellInstanceName = newCellInstanceName;
	}

	// FUNCTION: ENGINE 0x105ECEC0
	const char* CueEventSetCellType::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105EBFA0
	CueEventSetBPM::CueEventSetBPM(float newBPM) :
		bpm(newBPM)
	{
	}

	// FUNCTION: ENGINE 0x105D4F90
	const float& CueEventSetBPM::GetBPM() const
	{
		return bpm;
	}

	// FUNCTION: ENGINE 0x105EBE10
	void CueEventSetBPM::SetBPM(const float& newBPM)
	{
		bpm = newBPM;
	}

	// FUNCTION: ENGINE 0x105ECED0
	const char* CueEventSetBPM::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105DBE80
	const om::ClassName& CueEventCommand::GetName() const
	{
		return name;
	}

	// FUNCTION: ENGINE 0x105EDDB0
	void CueEventCommand::SetName(const om::ClassName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x105DFA40
	const unsigned int& CueEventCommand::GetEventType() const
	{
		return eventType;
	}

	// FUNCTION: ENGINE 0x105EBE50
	void CueEventCommand::SetEventType(const unsigned int& newEventType)
	{
		eventType = newEventType;
	}

	// FUNCTION: ENGINE 0x105D2ED0
	const char* CueEventCommand::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105EBFF0
	CueEventSetFade::CueEventSetFade(Fade newFade, int newKind) :
		fade(newFade),
		isFadeOut(newKind == 1)
	{
	}

	// FUNCTION: ENGINE 0x105DBEC0
	const Fade& CueEventSetFade::GetFade() const
	{
		return fade;
	}

	// FUNCTION: ENGINE 0x105EBEF0
	void CueEventSetFade::SetFade(const Fade& newFade)
	{
		fade = newFade;
	}

	// FUNCTION: ENGINE 0x105EBF10
	const om::Bool32& CueEventSetFade::GetIsFadeOut() const
	{
		return isFadeOut;
	}

	// FUNCTION: ENGINE 0x105EBF20
	void CueEventSetFade::SetIsFadeOut(const om::Bool32& newIsFadeOut)
	{
		isFadeOut = newIsFadeOut;
	}

	// FUNCTION: ENGINE 0x105ECEF0
	const char* CueEventSetFade::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105D51E0
	const char* CueEventCueState::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105ECEE0
	const char* CueEventCellState::AllocationTag()
	{
		return "";
	}
}

namespace om
{
	// FUNCTION: ENGINE 0x105F1DD0
	template<> int MetaClass<music::CueEventNewCuePlayer>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventNewCuePlayer);
	}

	// FUNCTION: ENGINE 0x105EC1C0
	template<> void MetaClass<music::CueEventNewCuePlayer>::Slot6(void* object)
	{
		delete static_cast<music::CueEventNewCuePlayer*>(object);
	}

	// FUNCTION: ENGINE 0x105EE770
	template<> int MetaClass<music::CueEventDestroyCuePlayer>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventDestroyCuePlayer);
	}

	// FUNCTION: ENGINE 0x105EC280
	template<> void MetaClass<music::CueEventDestroyCuePlayer>::Slot6(void* object)
	{
		delete static_cast<music::CueEventDestroyCuePlayer*>(object);
	}

	// FUNCTION: ENGINE 0x105EE7A0
	template<> int MetaClass<music::CueEventSetCurrentCuePlayer>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventSetCurrentCuePlayer);
	}

	// FUNCTION: ENGINE 0x105EC300
	template<> void MetaClass<music::CueEventSetCurrentCuePlayer>::Slot6(void* object)
	{
		delete static_cast<music::CueEventSetCurrentCuePlayer*>(object);
	}

	// FUNCTION: ENGINE 0x105EE7D0
	template<> int MetaClass<music::CueEventSetCurrentCue>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventSetCurrentCue);
	}

	// FUNCTION: ENGINE 0x105EC380
	template<> void MetaClass<music::CueEventSetCurrentCue>::Slot6(void* object)
	{
		delete static_cast<music::CueEventSetCurrentCue*>(object);
	}

	// FUNCTION: ENGINE 0x105EE800
	template<> int MetaClass<music::CueEventSetPartName>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventSetPartName);
	}

	// FUNCTION: ENGINE 0x105EC440
	template<> void MetaClass<music::CueEventSetPartName>::Slot6(void* object)
	{
		delete static_cast<music::CueEventSetPartName*>(object);
	}

	// FUNCTION: ENGINE 0x105EE830
	template<> int MetaClass<music::CueEventSetLayerName>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventSetLayerName);
	}

	// FUNCTION: ENGINE 0x105EC500
	template<> void MetaClass<music::CueEventSetLayerName>::Slot6(void* object)
	{
		delete static_cast<music::CueEventSetLayerName*>(object);
	}

	// FUNCTION: ENGINE 0x105EE860
	template<> int MetaClass<music::CueEventSetCurrentCell>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventSetCurrentCell);
	}

	// FUNCTION: ENGINE 0x105EC580
	template<> void MetaClass<music::CueEventSetCurrentCell>::Slot6(void* object)
	{
		delete static_cast<music::CueEventSetCurrentCell*>(object);
	}

	// FUNCTION: ENGINE 0x105EE8A0
	template<> int MetaClass<music::CueEventCellPlayerState>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventCellPlayerState);
	}

	// FUNCTION: ENGINE 0x105EC600
	template<> void MetaClass<music::CueEventCellPlayerState>::Slot6(void* object)
	{
		delete static_cast<music::CueEventCellPlayerState*>(object);
	}

	// FUNCTION: ENGINE 0x105EE8C0
	template<> int MetaClass<music::CueEventSetCellType>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventSetCellType);
	}

	// FUNCTION: ENGINE 0x105EC680
	template<> void MetaClass<music::CueEventSetCellType>::Slot6(void* object)
	{
		delete static_cast<music::CueEventSetCellType*>(object);
	}

	// FUNCTION: ENGINE 0x105EE8F0
	template<> int MetaClass<music::CueEventSetBPM>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventSetBPM);
	}

	// FUNCTION: ENGINE 0x105EC700
	template<> void MetaClass<music::CueEventSetBPM>::Slot6(void* object)
	{
		delete static_cast<music::CueEventSetBPM*>(object);
	}

	// FUNCTION: ENGINE 0x105EE910
	template<> int MetaClass<music::CueEventCommand>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventCommand);
	}

	// FUNCTION: ENGINE 0x105EC780
	template<> void MetaClass<music::CueEventCommand>::Slot6(void* object)
	{
		delete static_cast<music::CueEventCommand*>(object);
	}

	// FUNCTION: ENGINE 0x105F79B0
	template<> int MetaClass<music::CueEventCueState>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventCueState);
	}

	// FUNCTION: ENGINE 0x105EC800
	template<> void MetaClass<music::CueEventCueState>::Slot6(void* object)
	{
		delete static_cast<music::CueEventCueState*>(object);
	}

	// FUNCTION: ENGINE 0x105EE940
	template<> int MetaClass<music::CueEventMoveCell>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventMoveCell);
	}

	// FUNCTION: ENGINE 0x105EC8C0
	template<> void MetaClass<music::CueEventMoveCell>::Slot6(void* object)
	{
		delete static_cast<music::CueEventMoveCell*>(object);
	}

	// FUNCTION: ENGINE 0x105EE960
	template<> int MetaClass<music::CueEventMovePart>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventMovePart);
	}

	// FUNCTION: ENGINE 0x105EC980
	template<> void MetaClass<music::CueEventMovePart>::Slot6(void* object)
	{
		delete static_cast<music::CueEventMovePart*>(object);
	}

	// FUNCTION: ENGINE 0x105EE980
	template<> int MetaClass<music::CueEventCellState>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventCellState);
	}

	// FUNCTION: ENGINE 0x105ECA00
	template<> void MetaClass<music::CueEventCellState>::Slot6(void* object)
	{
		delete static_cast<music::CueEventCellState*>(object);
	}

	// FUNCTION: ENGINE 0x105EE9B0
	template<> int MetaClass<music::CueEventSync>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventSync);
	}

	// FUNCTION: ENGINE 0x105ECA80
	template<> void MetaClass<music::CueEventSync>::Slot6(void* object)
	{
		delete static_cast<music::CueEventSync*>(object);
	}

	// FUNCTION: ENGINE 0x105EE9E0
	template<> int MetaClass<music::CueEventSetFade>::Slot5()
	{
		return reinterpret_cast<int>(new music::CueEventSetFade);
	}

	// FUNCTION: ENGINE 0x105ECB10
	template<> void MetaClass<music::CueEventSetFade>::Slot6(void* object)
	{
		delete static_cast<music::CueEventSetFade*>(object);
	}
}

namespace om
{
	// FUNCTION: ENGINE 0x105D2D80
	template MetaMethod1Base<void, const music::CellPlayer::State&>* MetaProperty<const music::CellPlayer::State&>::GetSetter();
	// FUNCTION: ENGINE 0x105D3070
	template MetaMethod0Base<const music::CellPlayer::State&>* MetaProperty<const music::CellPlayer::State&>::GetGetter();
	// FUNCTION: ENGINE 0x105D3080
	template MetaMethod1Base<void, const float&>* MetaProperty<const float&>::GetSetter();
	// FUNCTION: ENGINE 0x105EFA20
	template const char* Garbage<music::CellPlayer::State>::AllocationTag();
	// FUNCTION: ENGINE 0x105EFCB0
	template const char* Garbage<float>::AllocationTag();
}

namespace music
{
	// FUNCTION: ENGINE 0x105D5410
	template const char* CueEventDerived<CueEventNewCuePlayer>::AllocationTag();
	// FUNCTION: ENGINE 0x105D5CD0
	template void* CueEventDerived<CueEventNewCuePlayer>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D5D40
	template void CueEventDerived<CueEventNewCuePlayer>::operator delete(void*);
}

namespace om
{
	// FUNCTION: ENGINE 0x105D7870
	template MetaMethod1Base<void, const unsigned int&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105D78E0
	template MetaMethod1Base<void, const unsigned int&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105F07F0
	template const char* Garbage<Bool32>::AllocationTag();
	// FUNCTION: ENGINE 0x105D8B50
	template MetaMethod1Base<void, unsigned __int64>* MetaProperty<unsigned __int64>::GetSetter();
	// FUNCTION: ENGINE 0x105D8B60
	template MetaMethod0Base<const float&>* MetaProperty<const float&>::GetGetter();
	// FUNCTION: ENGINE 0x105D8B70
	template MetaMethod1Base<void, const Bool32&>* MetaProperty<const Bool32&>::GetSetter();
	// FUNCTION: ENGINE 0x105D8B80
	template MetaMethod0Base<unsigned __int64>* MetaProperty<unsigned __int64>::GetGetter();
	// FUNCTION: ENGINE 0x105D8BA0
	template MetaMethod0Base<const Bool32&>* MetaProperty<const Bool32&>::GetGetter();
	// FUNCTION: ENGINE 0x105F15C0
	template void* Garbage<Bool32>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F14C0
	template void* Garbage<music::CellPlayer::State>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F1540
	template void* Garbage<float>::operator new(size_t);
	// FUNCTION: ENGINE 0x105DFF00
	template MetaMethod1Base<void, const music::Fade&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105DFF10
	template MetaMethod0Base<const music::Fade&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105DFF60
	template MetaMethod1Base<void, const music::Fade&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105E2CB0
	template MetaClass<music::CueEventNewCuePlayer>::~MetaClass();
	// FUNCTION: ENGINE 0x105E2CC0
	template void MetaClass<music::CueEventNewCuePlayer>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E5160
	template MetaClass<music::CueEventDestroyCuePlayer>::~MetaClass();
	// FUNCTION: ENGINE 0x105E5170
	template void MetaClass<music::CueEventDestroyCuePlayer>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E52D0
	template MetaMethod1Base<void, unsigned __int64>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105E52E0
	template MetaMethod1Base<void, const music::CellPlayer::State&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105E52F0
	template MetaMethod0Base<const music::CellPlayer::State&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105E5300
	template MetaMethod1Base<void, const float&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105E5310
	template MetaProperty<const music::CellPlayer::State&>::~MetaProperty();
	// FUNCTION: ENGINE 0x105E5320
	template MetaProperty<const float&>::~MetaProperty();
	// FUNCTION: ENGINE 0x105E5B10
	template MetaMethod0Base<const float&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105E5B20
	template void MetaMethod1<music::CueEventSync, music::CueEventSync, void, unsigned __int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E5BB0
	template MetaMethod0Base<unsigned __int64>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105E5BC0
	template void MetaMethod1<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, void, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E5C50
	template MetaMethod1Base<void, const Bool32&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105E5C60
	template void MetaMethod0Const<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E5D00
	template MetaMethod0Base<const Bool32&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105E5D10
	template void MetaMethod1<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, void, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E5DB0
	template MetaMethod1<music::CueEventSync, music::CueEventSync, void, unsigned __int64>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105E5DC0
	template void MetaMethod0Const<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E5EE0
	template MetaMethod1<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, void, const ClassName&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105E5EF0
	template void MetaMethod1<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, void, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105F1520
	template void Garbage<music::CellPlayer::State>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E62F0
	template DelegateProperty<music::CellPlayer::State>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105E6320
	template DelegateProperty<unsigned __int64>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105E6CA0
	template void DelegateMetaProperty<const music::CellPlayer::State&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E6CC0
	template DelegateProperty<Bool32>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105E6D80
	template void DelegateMetaProperty<unsigned __int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E6DA0
	template DelegateMetaProperty<const music::CellPlayer::State&>::~DelegateMetaProperty();
}

namespace music
{
	// FUNCTION: ENGINE 0x105EBDD0
	template CueEventDerived<CueEventCellPlayerState>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EBDE0
	template CueEventDerived<CueEventNewCuePlayer>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EBDF0
	template CueEventDerived<CueEventSetCellType>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EBE00
	template CueEventDerived<CueEventDestroyCuePlayer>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EBE20
	template CueEventDerived<CueEventSetBPM>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EBE30
	template CueEventDerived<CueEventSetPartName>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EBE60
	template CueEventDerived<CueEventCommand>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EBE70
	template CueEventDerived<CueEventSetLayerName>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EBE80
	template CueEventDerived<CueEventCueState>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EBE90
	template CueEventDerived<CueEventMoveCell>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EBEA0
	template CueEventDerived<CueEventCellState>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EBEB0
	template CueEventDerived<CueEventMovePart>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EBF30
	template CueEventDerived<CueEventSetFade>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EBF40
	template CueEventDerived<CueEventCellPlayerState>::~CueEventDerived();
}

namespace om
{
	// FUNCTION: ENGINE 0x105F15A0
	template void Garbage<float>::operator delete(void*);
}

namespace music
{
	// FUNCTION: ENGINE 0x105EBF90
	template CueEventDerived<CueEventSetCellType>::~CueEventDerived();
}

namespace om
{
	// FUNCTION: ENGINE 0x105F1620
	template void Garbage<Bool32>::operator delete(void*);
}

namespace music
{
	// FUNCTION: ENGINE 0x105EBFE0
	template CueEventDerived<CueEventSetBPM>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EC040
	template CueEventDerived<CueEventCommand>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EC070
	template void CueEventDerived<CueEventDestroyCuePlayer>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EC090
	template void CueEventDerived<CueEventSetPartName>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EC0B0
	template void CueEventDerived<CueEventSetLayerName>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EC0D0
	template void CueEventDerived<CueEventMoveCell>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EC0F0
	template void CueEventDerived<CueEventMovePart>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E6280
	template void CueEventDerived<CueEventCellPlayerState>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EC130
	template void CueEventDerived<CueEventSetCellType>::operator delete(void*);
}

namespace om
{
	// FUNCTION: ENGINE 0x105EC150
	template MetaClass<music::CueEventNewCuePlayer>::MetaClass(const ClassName&, MetaClassBase*);
}

namespace music
{
	// FUNCTION: ENGINE 0x105EC180
	template CueEventDerived<CueEventSetFade>::~CueEventDerived();
}

namespace om
{
	// FUNCTION: ENGINE 0x105EC1B0
	template const type_info* MetaClass<music::CueEventNewCuePlayer>::GetType();
	// FUNCTION: ENGINE 0x105EC1E0
	template MetaClass<music::CueEventDestroyCuePlayer>::MetaClass(const ClassName&, MetaClassBase*);
}

namespace music
{
	// FUNCTION: ENGINE 0x105EC210
	template CueEventDerived<CueEventDestroyCuePlayer>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EC220
	template CueEventDerived<CueEventCueState>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EBF70
	template void CueEventDerived<CueEventSetBPM>::operator delete(void*);
}

namespace om
{
	// FUNCTION: ENGINE 0x105EC270
	template const type_info* MetaClass<music::CueEventDestroyCuePlayer>::GetType();
	// FUNCTION: ENGINE 0x105EC2A0
	template MetaClass<music::CueEventSetCurrentCuePlayer>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105EC2F0
	template const type_info* MetaClass<music::CueEventSetCurrentCuePlayer>::GetType();
	// FUNCTION: ENGINE 0x105EC320
	template MetaClass<music::CueEventSetCurrentCue>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105EC370
	template const type_info* MetaClass<music::CueEventSetCurrentCue>::GetType();
	// FUNCTION: ENGINE 0x105EC3A0
	template MetaClass<music::CueEventSetPartName>::MetaClass(const ClassName&, MetaClassBase*);
}

namespace music
{
	// FUNCTION: ENGINE 0x105EC3D0
	template CueEventDerived<CueEventSetPartName>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EC3E0
	template CueEventDerived<CueEventCellState>::~CueEventDerived();
	// FUNCTION: ENGINE 0x105EC410
	template void CueEventDerived<CueEventCommand>::operator delete(void*);
}

namespace om
{
	// FUNCTION: ENGINE 0x105EC430
	template const type_info* MetaClass<music::CueEventSetPartName>::GetType();
	// FUNCTION: ENGINE 0x105EC460
	template MetaClass<music::CueEventSetLayerName>::MetaClass(const ClassName&, MetaClassBase*);
}

namespace music
{
	// FUNCTION: ENGINE 0x105EC490
	template CueEventDerived<CueEventSetLayerName>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EC4D0
	template void CueEventDerived<CueEventSetFade>::operator delete(void*);
}

namespace om
{
	// FUNCTION: ENGINE 0x105EC4F0
	template const type_info* MetaClass<music::CueEventSetLayerName>::GetType();
	// FUNCTION: ENGINE 0x105EC520
	template MetaClass<music::CueEventSetCurrentCell>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105EC570
	template const type_info* MetaClass<music::CueEventSetCurrentCell>::GetType();
	// FUNCTION: ENGINE 0x105EC5A0
	template MetaClass<music::CueEventCellPlayerState>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105EC5F0
	template const type_info* MetaClass<music::CueEventCellPlayerState>::GetType();
	// FUNCTION: ENGINE 0x105EC620
	template MetaClass<music::CueEventSetCellType>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105EC670
	template const type_info* MetaClass<music::CueEventSetCellType>::GetType();
	// FUNCTION: ENGINE 0x105EC6A0
	template MetaClass<music::CueEventSetBPM>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105EC6F0
	template const type_info* MetaClass<music::CueEventSetBPM>::GetType();
	// FUNCTION: ENGINE 0x105EC720
	template MetaClass<music::CueEventCommand>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105EC770
	template const type_info* MetaClass<music::CueEventCommand>::GetType();
	// FUNCTION: ENGINE 0x105EC7A0
	template MetaClass<music::CueEventCueState>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105EC7F0
	template const type_info* MetaClass<music::CueEventCueState>::GetType();
	// FUNCTION: ENGINE 0x105EC820
	template MetaClass<music::CueEventMoveCell>::MetaClass(const ClassName&, MetaClassBase*);
}

namespace music
{
	// FUNCTION: ENGINE 0x105EC850
	template CueEventDerived<CueEventMoveCell>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EBFC0
	template void CueEventDerived<CueEventCueState>::operator delete(void*);
}

namespace om
{
	// FUNCTION: ENGINE 0x105EC8B0
	template const type_info* MetaClass<music::CueEventMoveCell>::GetType();
	// FUNCTION: ENGINE 0x105EC8E0
	template MetaClass<music::CueEventMovePart>::MetaClass(const ClassName&, MetaClassBase*);
}

namespace music
{
	// FUNCTION: ENGINE 0x105EC910
	template CueEventDerived<CueEventMovePart>::CueEventDerived();
	// FUNCTION: ENGINE 0x105EC950
	template void CueEventDerived<CueEventCellState>::operator delete(void*);
}

namespace om
{
	// FUNCTION: ENGINE 0x105EC970
	template const type_info* MetaClass<music::CueEventMovePart>::GetType();
	// FUNCTION: ENGINE 0x105EC9A0
	template MetaClass<music::CueEventCellState>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105EC9F0
	template const type_info* MetaClass<music::CueEventCellState>::GetType();
	// FUNCTION: ENGINE 0x105ECA20
	template MetaClass<music::CueEventSync>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105ECA70
	template const type_info* MetaClass<music::CueEventSync>::GetType();
	// FUNCTION: ENGINE 0x105ECAA0
	template MetaClass<music::CueEventSetFade>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105ECB00
	template const type_info* MetaClass<music::CueEventSetFade>::GetType();
	// FUNCTION: ENGINE 0x105ECB30
	template MetaClass<music::CueEventSetCurrentCuePlayer>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECB40
	template MetaClass<music::CueEventSetCurrentCue>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECB50
	template MetaClass<music::CueEventSetPartName>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECB60
	template MetaClass<music::CueEventSetLayerName>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECB70
	template MetaClass<music::CueEventSetCurrentCell>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECB80
	template MetaClass<music::CueEventCellPlayerState>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECB90
	template MetaClass<music::CueEventSetCellType>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECBA0
	template MetaClass<music::CueEventSetBPM>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECBB0
	template MetaClass<music::CueEventCommand>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECBC0
	template MetaClass<music::CueEventCueState>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECBD0
	template MetaClass<music::CueEventMoveCell>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECBE0
	template MetaClass<music::CueEventMovePart>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECBF0
	template MetaClass<music::CueEventCellState>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECC00
	template MetaClass<music::CueEventSync>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECC10
	template MetaClass<music::CueEventSetFade>::~MetaClass();
	// FUNCTION: ENGINE 0x105ECC40
	template void MetaClass<music::CueEventSetCurrentCuePlayer>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECC60
	template void MetaClass<music::CueEventSetCurrentCue>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECC80
	template void MetaClass<music::CueEventSetPartName>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECCA0
	template void MetaClass<music::CueEventSetLayerName>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECCC0
	template void MetaClass<music::CueEventSetCurrentCell>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECCE0
	template void MetaClass<music::CueEventCellPlayerState>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECD00
	template void MetaClass<music::CueEventSetCellType>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECD20
	template void MetaClass<music::CueEventSetBPM>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECD40
	template void MetaClass<music::CueEventCommand>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECD60
	template void MetaClass<music::CueEventCueState>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECD80
	template void MetaClass<music::CueEventMoveCell>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECDA0
	template void MetaClass<music::CueEventMovePart>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECDC0
	template void MetaClass<music::CueEventCellState>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECDE0
	template void MetaClass<music::CueEventSync>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECE00
	template void MetaClass<music::CueEventSetFade>::operator delete(void*);
	// FUNCTION: ENGINE 0x105ECF20
	template const char* MetaClass<music::CueEventNewCuePlayer>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECF30
	template const char* MetaClass<music::CueEventDestroyCuePlayer>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECF40
	template const char* MetaClass<music::CueEventSetCurrentCuePlayer>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECF50
	template const char* MetaClass<music::CueEventSetCurrentCue>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECF60
	template const char* MetaClass<music::CueEventSetPartName>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECF70
	template const char* MetaClass<music::CueEventSetLayerName>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECF80
	template const char* MetaClass<music::CueEventSetCurrentCell>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECF90
	template const char* MetaClass<music::CueEventCellPlayerState>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECFA0
	template const char* MetaClass<music::CueEventSetCellType>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECFB0
	template const char* MetaClass<music::CueEventSetBPM>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECFC0
	template const char* MetaClass<music::CueEventCommand>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECFD0
	template const char* MetaClass<music::CueEventCueState>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECFE0
	template const char* MetaClass<music::CueEventMoveCell>::AllocationTag();
	// FUNCTION: ENGINE 0x105ECFF0
	template const char* MetaClass<music::CueEventMovePart>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED000
	template const char* MetaClass<music::CueEventCellState>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED010
	template const char* MetaClass<music::CueEventSync>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED020
	template const char* MetaClass<music::CueEventSetFade>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED040
	template MetaProperty<const music::CellPlayer::State&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::CellPlayer::State&>*, MetaMethod0Base<const music::CellPlayer::State&>*, unsigned int);
	// FUNCTION: ENGINE 0x105ED080
	template const type_info* MetaProperty<const music::CellPlayer::State&>::GetValueType();
	// FUNCTION: ENGINE 0x105ED090
	template MetaProperty<const float&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const float&>*, MetaMethod0Base<const float&>*, unsigned int);
	// FUNCTION: ENGINE 0x105ED0D0
	template const type_info* MetaProperty<const float&>::GetValueType();
	// FUNCTION: ENGINE 0x105ED0E0
	template MetaProperty<unsigned __int64>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, unsigned __int64>*, MetaMethod0Base<unsigned __int64>*, unsigned int);
	// FUNCTION: ENGINE 0x105ED150
	template const type_info* MetaProperty<unsigned __int64>::GetValueType();
	// FUNCTION: ENGINE 0x105ED160
	template MetaProperty<const Bool32&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const Bool32&>*, MetaMethod0Base<const Bool32&>*, unsigned int);
	// FUNCTION: ENGINE 0x105ED1A0
	template const type_info* MetaProperty<const Bool32&>::GetValueType();
	// FUNCTION: ENGINE 0x105ED1B0
	template MetaMethod0Const<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, const ClassName&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105ED1C0
	template MetaMethod1<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, void, const ClassName&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105ED1D0
	template MetaMethod0Const<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, const ClassName&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105ED1E0
	template MetaMethod1<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, void, const ClassName&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105ED1F0
	template MetaMethod0Const<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, const ClassName&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105ED200
	template MetaMethod1<music::CueEventSetPartName, music::CueEventSetPartName, void, const ClassName&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105ED210
	template MetaMethod0Const<music::CueEventSetPartName, music::CueEventSetPartName, const ClassName&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105ED220
	template MetaMethod1<music::CueEventSetLayerName, music::CueEventSetLayerName, void, const ClassName&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105ED230
	template MetaProperty<unsigned __int64>::~MetaProperty();
	// FUNCTION: ENGINE 0x105ED240
	template MetaProperty<const Bool32&>::~MetaProperty();
	// FUNCTION: ENGINE 0x105ED270
	template MetaMethod1Base<void, unsigned __int64>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105ED2F0
	template MetaMethod1Base<void, const float&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105ED350
	template MetaMethod0Base<unsigned __int64>::MetaMethod0Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105ED390
	template MetaMethod1Base<void, const Bool32&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105ED520
	template const char* MetaMethod1<music::CueEventSync, music::CueEventSync, void, unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED530
	template const char* MetaMethod1<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, void, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED540
	template const char* MetaMethod0Const<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED550
	template const char* MetaMethod1<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, void, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED560
	template const char* MetaMethod0Const<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED570
	template const char* MetaMethod1<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, void, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED580
	template const char* MetaMethod0Const<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED590
	template const char* MetaMethod1<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, void, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED5A0
	template const char* MetaMethod0Const<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED5B0
	template const char* MetaMethod1<music::CueEventSetPartName, music::CueEventSetPartName, void, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED5C0
	template const char* MetaMethod0Const<music::CueEventSetPartName, music::CueEventSetPartName, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED5D0
	template const char* MetaMethod1<music::CueEventSetLayerName, music::CueEventSetLayerName, void, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED5E0
	template const char* MetaMethod0Const<music::CueEventSetLayerName, music::CueEventSetLayerName, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED5F0
	template const char* MetaMethod1<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, void, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED600
	template const char* MetaMethod0Const<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED610
	template const char* MetaMethod1<music::CueEventCellPlayerState, music::CueEventCellPlayerState, void, const music::CellPlayer::State&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED620
	template const char* MetaMethod0Const<music::CueEventCellPlayerState, music::CueEventCellPlayerState, const music::CellPlayer::State&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED630
	template const char* MetaProperty<const music::CellPlayer::State&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED640
	template const char* MetaMethod1<music::CueEventSetCellType, music::CueEventSetCellType, void, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED650
	template const char* MetaMethod0Const<music::CueEventSetCellType, music::CueEventSetCellType, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED660
	template const char* MetaMethod1<music::CueEventSetBPM, music::CueEventSetBPM, void, const float&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED670
	template const char* MetaMethod0Const<music::CueEventSetBPM, music::CueEventSetBPM, const float&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED680
	template const char* MetaProperty<const float&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED690
	template const char* MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED6A0
	template const char* MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED6B0
	template const char* MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED6C0
	template const char* MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED6D0
	template const char* MetaMethod1<music::CueEventMoveCell, music::CueEventMoveCell, void, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED6E0
	template const char* MetaMethod0Const<music::CueEventMoveCell, music::CueEventMoveCell, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED6F0
	template const char* MetaMethod1<music::CueEventMovePart, music::CueEventMovePart, void, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED700
	template const char* MetaMethod0Const<music::CueEventMovePart, music::CueEventMovePart, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED710
	template const char* MetaMethod0Const<music::CueEventSync, music::CueEventSync, unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED720
	template const char* MetaProperty<unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED730
	template const char* MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const music::Fade&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED740
	template const char* MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const music::Fade&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED750
	template const char* MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const Bool32&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED760
	template const char* MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const Bool32&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED770
	template const char* MetaProperty<const Bool32&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED860
	template bool ReadBinary<music::CellPlayer::State>(BinaryStream*, music::CellPlayer::State*);
	// FUNCTION: ENGINE 0x105ED890
	template void WriteBinary<music::CellPlayer::State>(BinaryStream*, const music::CellPlayer::State&);
	// FUNCTION: ENGINE 0x105ED8C0
	template bool ReadBinary<Bool32>(BinaryStream*, Bool32*);
	// FUNCTION: ENGINE 0x105ED8F0
	template void WriteBinary<Bool32>(BinaryStream*, const Bool32&);
	// FUNCTION: ENGINE 0x105ED920
	template const char* DelegateMetaProperty<const music::CellPlayer::State&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED930
	template const char* DelegateMetaProperty<const float&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED940
	template const char* DelegateMetaProperty<unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED950
	template const char* DelegateMetaProperty<const Bool32&>::AllocationTag();
	// FUNCTION: ENGINE 0x105ED960
	template bool ReadText<music::CellPlayer::State>(const TextValue*, music::CellPlayer::State*);
	// FUNCTION: ENGINE 0x105ED990
	template void WriteText<music::CellPlayer::State>(TextValue*, const music::CellPlayer::State&);
	// FUNCTION: ENGINE 0x105ED9C0
	template bool ReadText<Bool32>(const TextValue*, Bool32*);
	// FUNCTION: ENGINE 0x105ED9F0
	template void WriteText<Bool32>(TextValue*, const Bool32&);
}

namespace music
{
	// FUNCTION: ENGINE 0x105EDA80
	template CueEventDerived<CueEventNewCuePlayer>::CueEventDerived();
}

namespace om
{
	// FUNCTION: ENGINE 0x105EEA40
	template void* MetaClass<music::CueEventDestroyCuePlayer>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEA60
	template void* MetaClass<music::CueEventSetCurrentCuePlayer>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEA80
	template void* MetaClass<music::CueEventSetCurrentCue>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEAA0
	template void* MetaClass<music::CueEventSetPartName>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEAC0
	template void* MetaClass<music::CueEventSetLayerName>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEAE0
	template void* MetaClass<music::CueEventSetCurrentCell>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEB00
	template void* MetaClass<music::CueEventCellPlayerState>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEB20
	template void* MetaClass<music::CueEventSetCellType>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEB40
	template void* MetaClass<music::CueEventSetBPM>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEB60
	template void* MetaClass<music::CueEventCommand>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEB80
	template void* MetaClass<music::CueEventCueState>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEBC0
	template void* MetaClass<music::CueEventMoveCell>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEBE0
	template void* MetaClass<music::CueEventMovePart>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEC00
	template void* MetaClass<music::CueEventCellState>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEC20
	template void* MetaClass<music::CueEventSync>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEC40
	template void* MetaClass<music::CueEventSetFade>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EEFD0
	template void* MetaMethod1<music::CueEventSync, music::CueEventSync, void, unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7590
	template music::CellPlayer::State* ReadArgument<music::CellPlayer::State>(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x105F7610
	template float* ReadArgument<float>(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x105F7670
	template Bool32* ReadArgument<Bool32>(BinaryStream*, GarbageList*);

	// FUNCTION: ENGINE 0x105F79E0
	template void MetaMethod1<music::CueEventSync, music::CueEventSync, void, unsigned __int64>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EEFF0
	template MetaMethod1<music::CueEventSync, music::CueEventSync, void, unsigned __int64>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSync::*)(unsigned __int64));
	// FUNCTION: ENGINE 0x105EF020
	template void MetaMethod1<music::CueEventSync, music::CueEventSync, void, unsigned __int64>::Call(void*, unsigned __int64);
	// FUNCTION: ENGINE 0x105EF040
	template MetaMethod0Const<music::CueEventSetLayerName, music::CueEventSetLayerName, const ClassName&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EF050
	template void MetaMethod0Const<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF0B0
	template MetaMethod1<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, void, const ClassName&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventNewCuePlayer::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105EF0E0
	template void MetaMethod1<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, void, const ClassName&>::Call(void*, const ClassName&);
	// FUNCTION: ENGINE 0x105EF100
	template MetaMethod1<music::CueEventCellPlayerState, music::CueEventCellPlayerState, void, const music::CellPlayer::State&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EF110
	template void MetaMethod1<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, void, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF130
	template void* MetaMethod0Const<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F6F00
	template void MetaMethod0Const<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF150
	template MetaMethod0Const<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, const ClassName&>::MetaMethod0Const(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventNewCuePlayer::*)(void)const);
	// FUNCTION: ENGINE 0x105EF180
	template const ClassName& MetaMethod0Const<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, const ClassName&>::Call(void*);
	// FUNCTION: ENGINE 0x105EF190
	template MetaMethod0Const<music::CueEventCellPlayerState, music::CueEventCellPlayerState, const music::CellPlayer::State&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EF1A0
	template void MetaMethod0Const<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF1C0
	template void* MetaMethod1<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, void, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7B60
	template void MetaMethod1<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, void, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF1E0
	template MetaMethod1<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, void, const ClassName&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventDestroyCuePlayer::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105EF210
	template void MetaMethod1<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, void, const ClassName&>::Call(void*, const ClassName&);
	// FUNCTION: ENGINE 0x105EF230
	template MetaMethod1<music::CueEventSetCellType, music::CueEventSetCellType, void, const ClassName&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EF240
	template void MetaMethod1<music::CueEventSetPartName, music::CueEventSetPartName, void, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF260
	template void* MetaMethod0Const<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F6F90
	template void MetaMethod0Const<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF280
	template MetaMethod0Const<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, const ClassName&>::MetaMethod0Const(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventDestroyCuePlayer::*)(void)const);
	// FUNCTION: ENGINE 0x105EF2B0
	template const ClassName& MetaMethod0Const<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, const ClassName&>::Call(void*);
	// FUNCTION: ENGINE 0x105EF2C0
	template MetaMethod0Const<music::CueEventSetCellType, music::CueEventSetCellType, const ClassName&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EF2D0
	template void MetaMethod0Const<music::CueEventSetPartName, music::CueEventSetPartName, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF2F0
	template void* MetaMethod1<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, void, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7C30
	template void MetaMethod1<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, void, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF310
	template MetaMethod1<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, void, const ClassName&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSetCurrentCuePlayer::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105EF340
	template void MetaMethod1<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, void, const ClassName&>::Call(void*, const ClassName&);
	// FUNCTION: ENGINE 0x105EF360
	template MetaMethod1<music::CueEventSetBPM, music::CueEventSetBPM, void, const float&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EF370
	template void MetaMethod1<music::CueEventSetLayerName, music::CueEventSetLayerName, void, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF390
	template void* MetaMethod0Const<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7020
	template void MetaMethod0Const<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF3B0
	template MetaMethod0Const<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, const ClassName&>::MetaMethod0Const(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetCurrentCuePlayer::*)(void)const);
	// FUNCTION: ENGINE 0x105EF3E0
	template const ClassName& MetaMethod0Const<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, const ClassName&>::Call(void*);
	// FUNCTION: ENGINE 0x105EF3F0
	template MetaMethod0Const<music::CueEventSetBPM, music::CueEventSetBPM, const float&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EF400
	template void MetaMethod0Const<music::CueEventSetLayerName, music::CueEventSetLayerName, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF420
	template void* MetaMethod1<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, void, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7D00
	template void MetaMethod1<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, void, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF440
	template MetaMethod1<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, void, const ClassName&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSetCurrentCue::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105EF470
	template void MetaMethod1<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, void, const ClassName&>::Call(void*, const ClassName&);
	// FUNCTION: ENGINE 0x105EF490
	template MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const ClassName&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EF4A0
	template void MetaMethod1<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, void, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF4C0
	template void* MetaMethod0Const<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F70B0
	template void MetaMethod0Const<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF4E0
	template MetaMethod0Const<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, const ClassName&>::MetaMethod0Const(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetCurrentCue::*)(void)const);
	// FUNCTION: ENGINE 0x105EF510
	template const ClassName& MetaMethod0Const<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, const ClassName&>::Call(void*);
	// FUNCTION: ENGINE 0x105EF520
	template MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const ClassName&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EF530
	template void MetaMethod0Const<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF550
	template void* MetaMethod1<music::CueEventSetPartName, music::CueEventSetPartName, void, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7DD0
	template void MetaMethod1<music::CueEventSetPartName, music::CueEventSetPartName, void, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF570
	template MetaMethod1<music::CueEventSetPartName, music::CueEventSetPartName, void, const ClassName&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSetPartName::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105EF5A0
	template void MetaMethod1<music::CueEventSetPartName, music::CueEventSetPartName, void, const ClassName&>::Call(void*, const ClassName&);
	// FUNCTION: ENGINE 0x105EF5C0
	template MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const unsigned int&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EF5D0
	template void MetaMethod1<music::CueEventCellPlayerState, music::CueEventCellPlayerState, void, const music::CellPlayer::State&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF5F0
	template void* MetaMethod0Const<music::CueEventSetPartName, music::CueEventSetPartName, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7140
	template void MetaMethod0Const<music::CueEventSetPartName, music::CueEventSetPartName, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF610
	template MetaMethod0Const<music::CueEventSetPartName, music::CueEventSetPartName, const ClassName&>::MetaMethod0Const(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetPartName::*)(void)const);
	// FUNCTION: ENGINE 0x105EF640
	template const ClassName& MetaMethod0Const<music::CueEventSetPartName, music::CueEventSetPartName, const ClassName&>::Call(void*);
	// FUNCTION: ENGINE 0x105EF650
	template MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const unsigned int&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EF660
	template void MetaMethod0Const<music::CueEventCellPlayerState, music::CueEventCellPlayerState, const music::CellPlayer::State&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF680
	template void* MetaMethod1<music::CueEventSetLayerName, music::CueEventSetLayerName, void, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7EA0
	template void MetaMethod1<music::CueEventSetLayerName, music::CueEventSetLayerName, void, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF6A0
	template MetaMethod1<music::CueEventSetLayerName, music::CueEventSetLayerName, void, const ClassName&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSetLayerName::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105EF6D0
	template void MetaMethod1<music::CueEventSetLayerName, music::CueEventSetLayerName, void, const ClassName&>::Call(void*, const ClassName&);
	// FUNCTION: ENGINE 0x105EF6F0
	template MetaMethod1<music::CueEventMoveCell, music::CueEventMoveCell, void, const unsigned int&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EF700
	template void MetaMethod1<music::CueEventSetCellType, music::CueEventSetCellType, void, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF720
	template void* MetaMethod0Const<music::CueEventSetLayerName, music::CueEventSetLayerName, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F71D0
	template void MetaMethod0Const<music::CueEventSetLayerName, music::CueEventSetLayerName, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF740
	template MetaMethod0Const<music::CueEventSetLayerName, music::CueEventSetLayerName, const ClassName&>::MetaMethod0Const(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetLayerName::*)(void)const);
	// FUNCTION: ENGINE 0x105EF770
	template const ClassName& MetaMethod0Const<music::CueEventSetLayerName, music::CueEventSetLayerName, const ClassName&>::Call(void*);
	// FUNCTION: ENGINE 0x105EF780
	template MetaMethod0Const<music::CueEventMoveCell, music::CueEventMoveCell, const unsigned int&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EF790
	template void MetaMethod0Const<music::CueEventSetCellType, music::CueEventSetCellType, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF7B0
	template void* MetaMethod1<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, void, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7F70
	template void MetaMethod1<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, void, const unsigned int&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF7D0
	template MetaMethod1<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, void, const unsigned int&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSetCurrentCell::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105EF800
	template void MetaMethod1<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, void, const unsigned int&>::Call(void*, const unsigned int&);
	// FUNCTION: ENGINE 0x105EF820
	template MetaMethod1<music::CueEventMovePart, music::CueEventMovePart, void, const unsigned int&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EF830
	template void MetaMethod1<music::CueEventSetBPM, music::CueEventSetBPM, void, const float&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF850
	template void* MetaMethod0Const<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EF8E0
	template void MetaMethod0Const<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, const unsigned int&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF870
	template MetaMethod0Const<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, const unsigned int&>::MetaMethod0Const(MetaClassBase*, const ClassName&, unsigned int const & (__thiscall music::CueEventSetCurrentCell::*)(void)const);
	// FUNCTION: ENGINE 0x105EF8A0
	template const unsigned int& MetaMethod0Const<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, const unsigned int&>::Call(void*);
	// FUNCTION: ENGINE 0x105EF8B0
	template MetaMethod0Const<music::CueEventMovePart, music::CueEventMovePart, const unsigned int&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EF8C0
	template void MetaMethod0Const<music::CueEventSetBPM, music::CueEventSetBPM, const float&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EF980
	template void* MetaMethod1<music::CueEventCellPlayerState, music::CueEventCellPlayerState, void, const music::CellPlayer::State&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F8040
	template void MetaMethod1<music::CueEventCellPlayerState, music::CueEventCellPlayerState, void, const music::CellPlayer::State&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EF9A0
	template MetaMethod1<music::CueEventCellPlayerState, music::CueEventCellPlayerState, void, const music::CellPlayer::State&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventCellPlayerState::*)(const music::CellPlayer::State&));
	// FUNCTION: ENGINE 0x105EF9D0
	template void MetaMethod1<music::CueEventCellPlayerState, music::CueEventCellPlayerState, void, const music::CellPlayer::State&>::Call(void*, const music::CellPlayer::State&);
	// FUNCTION: ENGINE 0x105EF9F0
	template MetaMethod0Const<music::CueEventSync, music::CueEventSync, unsigned __int64>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EFA00
	template void MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EFA30
	template void* MetaMethod0Const<music::CueEventCellPlayerState, music::CueEventCellPlayerState, const music::CellPlayer::State&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7260
	template void MetaMethod0Const<music::CueEventCellPlayerState, music::CueEventCellPlayerState, const music::CellPlayer::State&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EFA50
	template MetaMethod0Const<music::CueEventCellPlayerState, music::CueEventCellPlayerState, const music::CellPlayer::State&>::MetaMethod0Const(MetaClassBase*, const ClassName&, music::CellPlayer::State const & (__thiscall music::CueEventCellPlayerState::*)(void)const);
	// FUNCTION: ENGINE 0x105EFA80
	template const music::CellPlayer::State& MetaMethod0Const<music::CueEventCellPlayerState, music::CueEventCellPlayerState, const music::CellPlayer::State&>::Call(void*);
	// FUNCTION: ENGINE 0x105EFA90
	template MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const Bool32&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EFAA0
	template void MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EFAC0
	template void* MetaProperty<const music::CellPlayer::State&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EFAE0
	template void* MetaMethod1<music::CueEventSetCellType, music::CueEventSetCellType, void, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F8110
	template void MetaMethod1<music::CueEventSetCellType, music::CueEventSetCellType, void, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EFB00
	template MetaMethod1<music::CueEventSetCellType, music::CueEventSetCellType, void, const ClassName&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSetCellType::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105EFB30
	template void MetaMethod1<music::CueEventSetCellType, music::CueEventSetCellType, void, const ClassName&>::Call(void*, const ClassName&);
	// FUNCTION: ENGINE 0x105EFB50
	template MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const Bool32&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EFB60
	template void MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EFB80
	template void* MetaMethod0Const<music::CueEventSetCellType, music::CueEventSetCellType, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7310
	template void MetaMethod0Const<music::CueEventSetCellType, music::CueEventSetCellType, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EFBA0
	template MetaMethod0Const<music::CueEventSetCellType, music::CueEventSetCellType, const ClassName&>::MetaMethod0Const(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetCellType::*)(void)const);
	// FUNCTION: ENGINE 0x105EFBD0
	template const ClassName& MetaMethod0Const<music::CueEventSetCellType, music::CueEventSetCellType, const ClassName&>::Call(void*);
	// FUNCTION: ENGINE 0x105EFBE0
	template MetaMethod1<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, void, const ClassName&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EFBF0
	template void MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EFC10
	template void* MetaMethod1<music::CueEventSetBPM, music::CueEventSetBPM, void, const float&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F81E0
	template void MetaMethod1<music::CueEventSetBPM, music::CueEventSetBPM, void, const float&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EFC30
	template MetaMethod1<music::CueEventSetBPM, music::CueEventSetBPM, void, const float&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSetBPM::*)(const float&));
	// FUNCTION: ENGINE 0x105EFC60
	template void MetaMethod1<music::CueEventSetBPM, music::CueEventSetBPM, void, const float&>::Call(void*, const float&);
	// FUNCTION: ENGINE 0x105EFC80
	template MetaMethod0Const<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, const ClassName&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EFC90
	template void MetaMethod1<music::CueEventMoveCell, music::CueEventMoveCell, void, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EFCC0
	template void* MetaMethod0Const<music::CueEventSetBPM, music::CueEventSetBPM, const float&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EFD70
	template void MetaMethod0Const<music::CueEventSetBPM, music::CueEventSetBPM, const float&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EFCE0
	template MetaMethod0Const<music::CueEventSetBPM, music::CueEventSetBPM, const float&>::MetaMethod0Const(MetaClassBase*, const ClassName&, float const & (__thiscall music::CueEventSetBPM::*)(void)const);
	// FUNCTION: ENGINE 0x105EFD10
	template const float& MetaMethod0Const<music::CueEventSetBPM, music::CueEventSetBPM, const float&>::Call(void*);
	// FUNCTION: ENGINE 0x105EFD20
	template MetaMethod1<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, void, const unsigned int&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EFD30
	template void MetaMethod0Const<music::CueEventMoveCell, music::CueEventMoveCell, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EFE10
	template void* MetaProperty<const float&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105EFE30
	template void* MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F82B0
	template void MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EFE50
	template MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const ClassName&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventCommand::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105EFE80
	template void MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const ClassName&>::Call(void*, const ClassName&);
	// FUNCTION: ENGINE 0x105EFEA0
	template MetaMethod0Const<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, const unsigned int&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EFEB0
	template void MetaMethod1<music::CueEventMovePart, music::CueEventMovePart, void, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EFED0
	template void* MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F73A0
	template void MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EFEF0
	template MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const ClassName&>::MetaMethod0Const(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventCommand::*)(void)const);
	// FUNCTION: ENGINE 0x105EFF20
	template const ClassName& MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const ClassName&>::Call(void*);
	// FUNCTION: ENGINE 0x105EFF30
	template MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const music::Fade&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105EFF40
	template void MetaMethod0Const<music::CueEventMovePart, music::CueEventMovePart, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105EFF60
	template void* MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F8380
	template void MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const unsigned int&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105EFF80
	template MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const unsigned int&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventCommand::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105EFFB0
	template void MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const unsigned int&>::Call(void*, const unsigned int&);
	// FUNCTION: ENGINE 0x105EFFD0
	template MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const music::Fade&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105EFFE0
	template void MetaMethod0Const<music::CueEventSync, music::CueEventSync, unsigned __int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x105F0000
	template void* MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F0090
	template void MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const unsigned int&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F0020
	template MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const unsigned int&>::MetaMethod0Const(MetaClassBase*, const ClassName&, unsigned int const & (__thiscall music::CueEventCommand::*)(void)const);
	// FUNCTION: ENGINE 0x105F0050
	template const unsigned int& MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const unsigned int&>::Call(void*);
	// FUNCTION: ENGINE 0x105F0070
	template void MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const music::Fade&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105F0130
	template void* MetaMethod1<music::CueEventMoveCell, music::CueEventMoveCell, void, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F8450
	template void MetaMethod1<music::CueEventMoveCell, music::CueEventMoveCell, void, const unsigned int&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F0150
	template MetaMethod1<music::CueEventMoveCell, music::CueEventMoveCell, void, const unsigned int&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventMoveCell::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105F0180
	template void MetaMethod1<music::CueEventMoveCell, music::CueEventMoveCell, void, const unsigned int&>::Call(void*, const unsigned int&);
	// FUNCTION: ENGINE 0x105F01B0
	template void MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const music::Fade&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105F01D0
	template void* MetaMethod0Const<music::CueEventMoveCell, music::CueEventMoveCell, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F0260
	template void MetaMethod0Const<music::CueEventMoveCell, music::CueEventMoveCell, const unsigned int&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F01F0
	template MetaMethod0Const<music::CueEventMoveCell, music::CueEventMoveCell, const unsigned int&>::MetaMethod0Const(MetaClassBase*, const ClassName&, unsigned int const & (__thiscall music::CueEventMoveCell::*)(void)const);
	// FUNCTION: ENGINE 0x105F0220
	template const unsigned int& MetaMethod0Const<music::CueEventMoveCell, music::CueEventMoveCell, const unsigned int&>::Call(void*);
	// FUNCTION: ENGINE 0x105F0240
	template void MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const Bool32&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105F0300
	template void* MetaMethod1<music::CueEventMovePart, music::CueEventMovePart, void, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F8520
	template void MetaMethod1<music::CueEventMovePart, music::CueEventMovePart, void, const unsigned int&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F0320
	template MetaMethod1<music::CueEventMovePart, music::CueEventMovePart, void, const unsigned int&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventMovePart::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105F0350
	template void MetaMethod1<music::CueEventMovePart, music::CueEventMovePart, void, const unsigned int&>::Call(void*, const unsigned int&);
	// FUNCTION: ENGINE 0x105F0380
	template void MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const Bool32&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105F03A0
	template void* MetaMethod0Const<music::CueEventMovePart, music::CueEventMovePart, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F0430
	template void MetaMethod0Const<music::CueEventMovePart, music::CueEventMovePart, const unsigned int&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F03C0
	template MetaMethod0Const<music::CueEventMovePart, music::CueEventMovePart, const unsigned int&>::MetaMethod0Const(MetaClassBase*, const ClassName&, unsigned int const & (__thiscall music::CueEventMovePart::*)(void)const);
	// FUNCTION: ENGINE 0x105F03F0
	template const unsigned int& MetaMethod0Const<music::CueEventMovePart, music::CueEventMovePart, const unsigned int&>::Call(void*);
	// FUNCTION: ENGINE 0x105F04D0
	template void* MetaMethod0Const<music::CueEventSync, music::CueEventSync, unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F0590
	template void MetaMethod0Const<music::CueEventSync, music::CueEventSync, unsigned __int64>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F04F0
	template MetaMethod0Const<music::CueEventSync, music::CueEventSync, unsigned __int64>::MetaMethod0Const(MetaClassBase*, const ClassName&, unsigned __int64 (__thiscall music::CueEventSync::*)(void)const);
	// FUNCTION: ENGINE 0x105F0520
	template unsigned __int64 MetaMethod0Const<music::CueEventSync, music::CueEventSync, unsigned __int64>::Call(void*);
	// FUNCTION: ENGINE 0x105F0600
	template void* MetaProperty<unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F0620
	template void* MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const music::Fade&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F85F0
	template void MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const music::Fade&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F0640
	template MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const music::Fade&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSetFade::*)(const music::Fade&));
	// FUNCTION: ENGINE 0x105F0670
	template void MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const music::Fade&>::Call(void*, const music::Fade&);
	// FUNCTION: ENGINE 0x105F06C0
	template void* MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const music::Fade&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F7430
	template void MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const music::Fade&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F06E0
	template MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const music::Fade&>::MetaMethod0Const(MetaClassBase*, const ClassName&, music::Fade const & (__thiscall music::CueEventSetFade::*)(void)const);
	// FUNCTION: ENGINE 0x105F0710
	template const music::Fade& MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const music::Fade&>::Call(void*);
	// FUNCTION: ENGINE 0x105F0750
	template void* MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const Bool32&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F86C0
	template void MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const Bool32&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F0770
	template MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const Bool32&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::CueEventSetFade::*)(const Bool32&));
	// FUNCTION: ENGINE 0x105F07A0
	template void MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const Bool32&>::Call(void*, const Bool32&);
	// FUNCTION: ENGINE 0x105F0800
	template void* MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const Bool32&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F74E0
	template void MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const Bool32&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105F0820
	template MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const Bool32&>::MetaMethod0Const(MetaClassBase*, const ClassName&, Bool32 const & (__thiscall music::CueEventSetFade::*)(void)const);
	// FUNCTION: ENGINE 0x105F0850
	template const Bool32& MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const Bool32&>::Call(void*);
	// FUNCTION: ENGINE 0x105F0890
	template void* MetaProperty<const Bool32&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F1050
	template bool MetaProperty<const float&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105F10E0
	template void MetaProperty<const float&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105F1160
	template bool MetaProperty<const float&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105F11A0
	template void MetaProperty<const float&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105F11D0
	template bool MetaProperty<unsigned __int64>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105F1270
	template void MetaProperty<unsigned __int64>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105F12F0
	// EQUIVALENT: register allocation and scheduling: the engine loads the stream before it reserves the frame and keeps the object address in edx (56.1 %)
	template bool MetaProperty<unsigned __int64>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105F1340
	// EQUIVALENT: register allocation: the engine loads the buffer into ecx and the address of the value into edx, ours the other way round (70.0 %)
	template void MetaProperty<unsigned __int64>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105F1440
	template void* DelegateMetaProperty<const music::CellPlayer::State&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F1460
	template void* DelegateMetaProperty<const float&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F1480
	template void* DelegateMetaProperty<unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F14A0
	template void* DelegateMetaProperty<const Bool32&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105F14E0
	template Garbage<music::CellPlayer::State>::Garbage(music::CellPlayer::State*);
	// FUNCTION: ENGINE 0x105F1500
	template Garbage<music::CellPlayer::State>::~Garbage();
	// FUNCTION: ENGINE 0x105F1560
	template Garbage<float>::Garbage(float*);
	// FUNCTION: ENGINE 0x105F1580
	template Garbage<float>::~Garbage();
	// FUNCTION: ENGINE 0x105F15E0
	template Garbage<Bool32>::Garbage(Bool32*);
	// FUNCTION: ENGINE 0x105F1600
	template Garbage<Bool32>::~Garbage();
	// FUNCTION: ENGINE 0x105F1640
	template DelegateProperty<music::CellPlayer::State>::DelegateProperty();
	// FUNCTION: ENGINE 0x105F1650
	template MetaTypeBase* DelegateProperty<music::CellPlayer::State>::GetMetaType();
	// FUNCTION: ENGINE 0x105F1660
	template DelegateMetaProperty<unsigned __int64>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105F1670
	template DelegateProperty<unsigned __int64>::DelegateProperty();
	// FUNCTION: ENGINE 0x105F1680
	template MetaTypeBase* DelegateProperty<unsigned __int64>::GetMetaType();
	// FUNCTION: ENGINE 0x105F1690
	template DelegateMetaProperty<const Bool32&>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105F16A0
	template DelegateProperty<Bool32>::DelegateProperty();
	// FUNCTION: ENGINE 0x105F16B0
	template MetaTypeBase* DelegateProperty<Bool32>::GetMetaType();
	// FUNCTION: ENGINE 0x105F16C0
	template DelegateMetaProperty<const float&>::~DelegateMetaProperty();
}

namespace music
{
	// FUNCTION: ENGINE 0x105F19D0
	template om::MetaClassBase* CueEventDerived<CueEventNewCuePlayer>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F19F0
	template om::MetaClassBase* CueEventDerived<CueEventNewCuePlayer>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1A10
	template om::MetaClassBase* CueEventDerived<CueEventDestroyCuePlayer>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1A30
	template om::MetaClassBase* CueEventDerived<CueEventDestroyCuePlayer>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1A50
	template om::MetaClassBase* CueEventDerived<CueEventSetPartName>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1A70
	template om::MetaClassBase* CueEventDerived<CueEventSetPartName>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1A90
	template om::MetaClassBase* CueEventDerived<CueEventSetLayerName>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1AB0
	template om::MetaClassBase* CueEventDerived<CueEventSetLayerName>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1AD0
	template om::MetaClassBase* CueEventDerived<CueEventMoveCell>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1AF0
	template om::MetaClassBase* CueEventDerived<CueEventMoveCell>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1B10
	template om::MetaClassBase* CueEventDerived<CueEventMovePart>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1B30
	template om::MetaClassBase* CueEventDerived<CueEventMovePart>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1B50
	template om::MetaClassBase* CueEventDerived<CueEventCellPlayerState>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1B70
	template om::MetaClassBase* CueEventDerived<CueEventCellPlayerState>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1B90
	template om::MetaClassBase* CueEventDerived<CueEventSetCellType>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1BB0
	template om::MetaClassBase* CueEventDerived<CueEventSetCellType>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1BD0
	template om::MetaClassBase* CueEventDerived<CueEventSetBPM>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1BF0
	template om::MetaClassBase* CueEventDerived<CueEventSetBPM>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1C10
	template om::MetaClassBase* CueEventDerived<CueEventCommand>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1C30
	template om::MetaClassBase* CueEventDerived<CueEventCommand>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1C50
	template om::MetaClassBase* CueEventDerived<CueEventCueState>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1C70
	template om::MetaClassBase* CueEventDerived<CueEventCueState>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1C90
	template om::MetaClassBase* CueEventDerived<CueEventCellState>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1CB0
	template om::MetaClassBase* CueEventDerived<CueEventCellState>::GetMetaClassForWrite();
	// FUNCTION: ENGINE 0x105F1CD0
	template om::MetaClassBase* CueEventDerived<CueEventSetFade>::GetMetaClassForRead();
	// FUNCTION: ENGINE 0x105F1CF0
	template om::MetaClassBase* CueEventDerived<CueEventSetFade>::GetMetaClassForWrite();
}

namespace om
{
	// FUNCTION: ENGINE 0x105F1D10
	template void MetaClass<music::CueEventNewCuePlayer>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F1E00
	template void MetaClass<music::CueEventDestroyCuePlayer>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F1EC0
	template void MetaClass<music::CueEventSetCurrentCuePlayer>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F1F80
	template void MetaClass<music::CueEventSetCurrentCue>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2040
	template void MetaClass<music::CueEventSetPartName>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2100
	template void MetaClass<music::CueEventSetLayerName>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F21C0
	template void MetaClass<music::CueEventSetCurrentCell>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2280
	template void MetaClass<music::CueEventCellPlayerState>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2340
	template void MetaClass<music::CueEventSetCellType>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2400
	template void MetaClass<music::CueEventSetBPM>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F24C0
	template void MetaClass<music::CueEventCommand>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2580
	template void MetaClass<music::CueEventCueState>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2640
	template void MetaClass<music::CueEventMoveCell>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2700
	template void MetaClass<music::CueEventMovePart>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F27C0
	template void MetaClass<music::CueEventCellState>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2880
	template void MetaClass<music::CueEventSync>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2940
	template void MetaClass<music::CueEventSetFade>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105F2A00
	template MetaMethod1<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, void, const ClassName&>* MetaMethod1<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, void, const ClassName&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventNewCuePlayer::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105F2A40
	template MetaMethod0Const<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, const ClassName&>* MetaMethod0Const<music::CueEventNewCuePlayer, music::CueEventNewCuePlayer, const ClassName&>::Create(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventNewCuePlayer::*)(void)const);
	// FUNCTION: ENGINE 0x105F2AE0
	template MetaMethod1<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, void, const ClassName&>* MetaMethod1<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, void, const ClassName&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventDestroyCuePlayer::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105F2B20
	template MetaMethod0Const<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, const ClassName&>* MetaMethod0Const<music::CueEventDestroyCuePlayer, music::CueEventDestroyCuePlayer, const ClassName&>::Create(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventDestroyCuePlayer::*)(void)const);
	// FUNCTION: ENGINE 0x105F2BC0
	template MetaMethod1<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, void, const ClassName&>* MetaMethod1<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, void, const ClassName&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSetCurrentCuePlayer::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105F2C00
	template MetaMethod0Const<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, const ClassName&>* MetaMethod0Const<music::CueEventSetCurrentCuePlayer, music::CueEventSetCurrentCuePlayer, const ClassName&>::Create(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetCurrentCuePlayer::*)(void)const);
	// FUNCTION: ENGINE 0x105F2CA0
	template MetaMethod1<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, void, const ClassName&>* MetaMethod1<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, void, const ClassName&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSetCurrentCue::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105F2CE0
	template MetaMethod0Const<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, const ClassName&>* MetaMethod0Const<music::CueEventSetCurrentCue, music::CueEventSetCurrentCue, const ClassName&>::Create(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetCurrentCue::*)(void)const);
	// FUNCTION: ENGINE 0x105F2D80
	template MetaMethod1<music::CueEventSetPartName, music::CueEventSetPartName, void, const ClassName&>* MetaMethod1<music::CueEventSetPartName, music::CueEventSetPartName, void, const ClassName&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSetPartName::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105F2DC0
	template MetaMethod0Const<music::CueEventSetPartName, music::CueEventSetPartName, const ClassName&>* MetaMethod0Const<music::CueEventSetPartName, music::CueEventSetPartName, const ClassName&>::Create(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetPartName::*)(void)const);
	// FUNCTION: ENGINE 0x105F2E60
	template MetaMethod1<music::CueEventSetLayerName, music::CueEventSetLayerName, void, const ClassName&>* MetaMethod1<music::CueEventSetLayerName, music::CueEventSetLayerName, void, const ClassName&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSetLayerName::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105F2EA0
	template MetaMethod0Const<music::CueEventSetLayerName, music::CueEventSetLayerName, const ClassName&>* MetaMethod0Const<music::CueEventSetLayerName, music::CueEventSetLayerName, const ClassName&>::Create(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetLayerName::*)(void)const);
	// FUNCTION: ENGINE 0x105F2F40
	template MetaMethod1<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, void, const unsigned int&>* MetaMethod1<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, void, const unsigned int&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSetCurrentCell::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105F2F80
	template MetaMethod0Const<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, const unsigned int&>* MetaMethod0Const<music::CueEventSetCurrentCell, music::CueEventSetCurrentCell, const unsigned int&>::Create(MetaClassBase*, const ClassName&, unsigned int const & (__thiscall music::CueEventSetCurrentCell::*)(void)const);
	// FUNCTION: ENGINE 0x105F3020
	template MetaMethod1<music::CueEventCellPlayerState, music::CueEventCellPlayerState, void, const music::CellPlayer::State&>* MetaMethod1<music::CueEventCellPlayerState, music::CueEventCellPlayerState, void, const music::CellPlayer::State&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventCellPlayerState::*)(const music::CellPlayer::State&));
	// FUNCTION: ENGINE 0x105F3060
	template MetaMethod0Const<music::CueEventCellPlayerState, music::CueEventCellPlayerState, const music::CellPlayer::State&>* MetaMethod0Const<music::CueEventCellPlayerState, music::CueEventCellPlayerState, const music::CellPlayer::State&>::Create(MetaClassBase*, const ClassName&, music::CellPlayer::State const & (__thiscall music::CueEventCellPlayerState::*)(void)const);
	// FUNCTION: ENGINE 0x105F30A0
	template void MetaProperty<const music::CellPlayer::State&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::CellPlayer::State&>*, MetaMethod0Base<const music::CellPlayer::State&>*, unsigned int);
	// FUNCTION: ENGINE 0x105F3100
	template MetaMethod1<music::CueEventSetCellType, music::CueEventSetCellType, void, const ClassName&>* MetaMethod1<music::CueEventSetCellType, music::CueEventSetCellType, void, const ClassName&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSetCellType::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105F3140
	template MetaMethod0Const<music::CueEventSetCellType, music::CueEventSetCellType, const ClassName&>* MetaMethod0Const<music::CueEventSetCellType, music::CueEventSetCellType, const ClassName&>::Create(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventSetCellType::*)(void)const);
	// FUNCTION: ENGINE 0x105F31E0
	template MetaMethod1<music::CueEventSetBPM, music::CueEventSetBPM, void, const float&>* MetaMethod1<music::CueEventSetBPM, music::CueEventSetBPM, void, const float&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSetBPM::*)(const float&));
	// FUNCTION: ENGINE 0x105F3220
	template MetaMethod0Const<music::CueEventSetBPM, music::CueEventSetBPM, const float&>* MetaMethod0Const<music::CueEventSetBPM, music::CueEventSetBPM, const float&>::Create(MetaClassBase*, const ClassName&, float const & (__thiscall music::CueEventSetBPM::*)(void)const);
	// FUNCTION: ENGINE 0x105F3260
	template void MetaProperty<const float&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const float&>*, MetaMethod0Base<const float&>*, unsigned int);
	// FUNCTION: ENGINE 0x105F32C0
	template MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const ClassName&>* MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const ClassName&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventCommand::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105F3300
	template MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const ClassName&>* MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const ClassName&>::Create(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::CueEventCommand::*)(void)const);
	// FUNCTION: ENGINE 0x105F33A0
	template MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const unsigned int&>* MetaMethod1<music::CueEventCommand, music::CueEventCommand, void, const unsigned int&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventCommand::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105F33E0
	template MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const unsigned int&>* MetaMethod0Const<music::CueEventCommand, music::CueEventCommand, const unsigned int&>::Create(MetaClassBase*, const ClassName&, unsigned int const & (__thiscall music::CueEventCommand::*)(void)const);
	// FUNCTION: ENGINE 0x105F3480
	template MetaMethod1<music::CueEventMoveCell, music::CueEventMoveCell, void, const unsigned int&>* MetaMethod1<music::CueEventMoveCell, music::CueEventMoveCell, void, const unsigned int&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventMoveCell::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105F34C0
	template MetaMethod0Const<music::CueEventMoveCell, music::CueEventMoveCell, const unsigned int&>* MetaMethod0Const<music::CueEventMoveCell, music::CueEventMoveCell, const unsigned int&>::Create(MetaClassBase*, const ClassName&, unsigned int const & (__thiscall music::CueEventMoveCell::*)(void)const);
	// FUNCTION: ENGINE 0x105F3560
	template MetaMethod1<music::CueEventMovePart, music::CueEventMovePart, void, const unsigned int&>* MetaMethod1<music::CueEventMovePart, music::CueEventMovePart, void, const unsigned int&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventMovePart::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105F35A0
	template MetaMethod0Const<music::CueEventMovePart, music::CueEventMovePart, const unsigned int&>* MetaMethod0Const<music::CueEventMovePart, music::CueEventMovePart, const unsigned int&>::Create(MetaClassBase*, const ClassName&, unsigned int const & (__thiscall music::CueEventMovePart::*)(void)const);
	// FUNCTION: ENGINE 0x105F3640
	template MetaMethod1<music::CueEventSync, music::CueEventSync, void, unsigned __int64>* MetaMethod1<music::CueEventSync, music::CueEventSync, void, unsigned __int64>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSync::*)(unsigned __int64));
	// FUNCTION: ENGINE 0x105F3680
	template MetaMethod0Const<music::CueEventSync, music::CueEventSync, unsigned __int64>* MetaMethod0Const<music::CueEventSync, music::CueEventSync, unsigned __int64>::Create(MetaClassBase*, const ClassName&, unsigned __int64 (__thiscall music::CueEventSync::*)(void)const);
	// FUNCTION: ENGINE 0x105F36C0
	template void MetaProperty<unsigned __int64>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, unsigned __int64>*, MetaMethod0Base<unsigned __int64>*, unsigned int);
	// FUNCTION: ENGINE 0x105F3710
	template MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const music::Fade&>* MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const music::Fade&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSetFade::*)(const music::Fade&));
	// FUNCTION: ENGINE 0x105F3750
	template MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const music::Fade&>* MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const music::Fade&>::Create(MetaClassBase*, const ClassName&, music::Fade const & (__thiscall music::CueEventSetFade::*)(void)const);
	// FUNCTION: ENGINE 0x105F37F0
	template MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const Bool32&>* MetaMethod1<music::CueEventSetFade, music::CueEventSetFade, void, const Bool32&>::Create(MetaClassBase*, const ClassName&, void (music::CueEventSetFade::*)(const Bool32&));
	// FUNCTION: ENGINE 0x105F3830
	template MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const Bool32&>* MetaMethod0Const<music::CueEventSetFade, music::CueEventSetFade, const Bool32&>::Create(MetaClassBase*, const ClassName&, Bool32 const & (__thiscall music::CueEventSetFade::*)(void)const);
	// FUNCTION: ENGINE 0x105F3870
	template void MetaProperty<const Bool32&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const Bool32&>*, MetaMethod0Base<const Bool32&>*, unsigned int);
	// FUNCTION: ENGINE 0x105F3930
	template bool MetaProperty<const music::CellPlayer::State&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105F39C0
	template void MetaProperty<const music::CellPlayer::State&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105F3A50
	template bool MetaProperty<const music::CellPlayer::State&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105F3AB0
	template void MetaProperty<const music::CellPlayer::State&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105F3AF0
	template bool MetaProperty<const Bool32&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105F3B80
	template void MetaProperty<const Bool32&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105F3C10
	template bool MetaProperty<const Bool32&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105F3C70
	template void MetaProperty<const Bool32&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105F3DA0
	template DelegateMetaProperty<const music::CellPlayer::State&>::DelegateMetaProperty(void*, MetaProperty<const music::CellPlayer::State&>*);
	// FUNCTION: ENGINE 0x105F3DD0
	template void DelegateMetaProperty<const music::CellPlayer::State&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105F3DE0
	template void DelegateMetaProperty<const Bool32&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105F3E10
	template music::CellPlayer::State DelegateMetaProperty<const music::CellPlayer::State&>::Get();
	// FUNCTION: ENGINE 0x105F3E30
	template void DelegateMetaProperty<const music::CellPlayer::State&>::Set(music::CellPlayer::State);
	// FUNCTION: ENGINE 0x105F3E50
	template DelegateMetaProperty<const float&>::DelegateMetaProperty(void*, MetaProperty<const float&>*);
	// FUNCTION: ENGINE 0x105F3E80
	template void DelegateMetaProperty<const float&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105F3E90
	template void DelegateMetaProperty<const float&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105F3EC0
	template float DelegateMetaProperty<const float&>::Get();
	// FUNCTION: ENGINE 0x105F3EE0
	template void DelegateMetaProperty<const float&>::Set(float);
	// FUNCTION: ENGINE 0x105F3F00
	template DelegateMetaProperty<unsigned __int64>::DelegateMetaProperty(void*, MetaProperty<unsigned __int64>*);
	// FUNCTION: ENGINE 0x105F3F30
	template void DelegateMetaProperty<unsigned __int64>::SetObject(void*);
	// FUNCTION: ENGINE 0x105F3F70
	template unsigned __int64 DelegateMetaProperty<unsigned __int64>::Get();
	// FUNCTION: ENGINE 0x105F3F90
	template void DelegateMetaProperty<unsigned __int64>::Set(unsigned __int64);
	// FUNCTION: ENGINE 0x105F3FC0
	template DelegateMetaProperty<const Bool32&>::DelegateMetaProperty(void*, MetaProperty<const Bool32&>*);
	// FUNCTION: ENGINE 0x105F3FF0
	template void DelegateMetaProperty<const Bool32&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105F4030
	template Bool32 DelegateMetaProperty<const Bool32&>::Get();
	// FUNCTION: ENGINE 0x105F4050
	template void DelegateMetaProperty<const Bool32&>::Set(Bool32);
	// FUNCTION: ENGINE 0x105F76E0
	template DelegatePropertyBase* MetaProperty<const music::CellPlayer::State&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105F7730
	template DelegatePropertyBase* MetaProperty<const float&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105F7780
	template DelegatePropertyBase* MetaProperty<unsigned __int64>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105F77D0
	template DelegatePropertyBase* MetaProperty<const Bool32&>::CreateDelegate(void*);
}
