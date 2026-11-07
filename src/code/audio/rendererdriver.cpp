// The audio renderer drivers (0x105E4E50 - 0x105EBCD0): the base class of the device drivers and the reflection of
// audio::RendererDriver and its enumerations made of template instances of the om library.
#include "code/audio/drivers.h"
#include "code/audio/rendererdriver.h"
#include "code/om/delegate.h"
#include "code/om/metaclass.h"
#include "code/om/metaenum.h"
#include "code/om/metamethod.h"
#include "code/om/invoke.h"
#include "code/om/metaproperty.h"
#include "code/om/reflection.h"
#include "code/om/textvalue.h"

#pragma warning(disable: 4661)

namespace audio
{
	// FUNCTION: ENGINE 0x105E4E30
	RendererDriverModel::RendererDriverModel(const om::String& newName) :
		name(newName)
	{
	}

	// FUNCTION: ENGINE 0x105E65E0
	// NONMATCHING: the engine builds a temporary string for the description and copies it, ours constructs it in place (32.7 %)
#ifdef NONMATCHING
	RendererDriver::RendererDriver(const om::String& newName) :
		minLatency(0),
		maxLatency(0),
		minSampleRate(0),
		maxSampleRate(0),
		minNumberOfChannels(0),
		maxNumberOfChannels(0),
		sampleRate(0),
		latency(0),
		numberOfChannels(0),
		name(newName),
		userData(0),
		available(true),
		description(om::String("Unknown", false)),
		foldDownType(FoldDownTypeOff)
	{
		for (int i = 0; i < 8; ++i)
		{
			surroundChannelMap.items[i] = 0xFFFFFFFF;
		}
	}
#endif

	// FUNCTION: ENGINE 0x105E66D0
	om::MetaTypeBase* RendererDriver::GetMetaType()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<RendererDriver>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(RendererDriver));
		}
		return cache;
	}

	// FUNCTION: ENGINE 0x105E5710
	// NONMATCHING: the engine stores both limits before it reads the value in use and tests the lower limit first (56.4 %)
#ifdef NONMATCHING
	void RendererDriver::SetLatencyRange(unsigned int newMinLatency, unsigned int newMaxLatency)
	{
		minLatency = om::AlignUp(newMinLatency, 0x100);
		maxLatency = om::AlignUp(newMaxLatency, 0x100);
		unsigned int current = latency;
		if (current >= minLatency && current <= maxLatency)
		{
			latency = current;
		}
		else if (current > maxLatency)
		{
			latency = maxLatency;
		}
		else
		{
			latency = minLatency;
		}
	}
#endif

	// FUNCTION: ENGINE 0x105E5770
	// NONMATCHING: the engine reads the value in use after the stores and compares it with the new upper limit itself (2 %)
#ifdef NONMATCHING
	void RendererDriver::SetSampleRateRange(unsigned int newMinSampleRate, unsigned int newMaxSampleRate)
	{
		minSampleRate = newMinSampleRate;
		maxSampleRate = newMaxSampleRate;
		unsigned int current = sampleRate;
		if (current >= minSampleRate && current <= maxSampleRate)
		{
			sampleRate = current;
		}
		else if (current > maxSampleRate)
		{
			sampleRate = maxSampleRate;
		}
		else
		{
			sampleRate = minSampleRate;
		}
	}
#endif

	// FUNCTION: ENGINE 0x105E57B0
	// NONMATCHING: the engine reads the value in use after the stores and compares it with the new upper limit itself (4 %)
#ifdef NONMATCHING
	void RendererDriver::SetNumberOfChannelsRange(unsigned int newMinNumberOfChannels, unsigned int newMaxNumberOfChannels)
	{
		minNumberOfChannels = newMinNumberOfChannels;
		maxNumberOfChannels = newMaxNumberOfChannels;
		unsigned int current = numberOfChannels;
		if (current >= minNumberOfChannels && current <= maxNumberOfChannels)
		{
			numberOfChannels = current;
		}
		else if (current > maxNumberOfChannels)
		{
			numberOfChannels = maxNumberOfChannels;
		}
		else
		{
			numberOfChannels = minNumberOfChannels;
		}
	}
#endif

	// FUNCTION: ENGINE 0x105E66F0
	void RendererDriver::SetUserData(unsigned int newUserData)
	{
		userData = newUserData;
	}

	// FUNCTION: ENGINE 0x105E6700
	void RendererDriver::ClearUserData()
	{
		userData = 0;
	}

	// FUNCTION: ENGINE 0x105E57F0
	void RendererDriver::SetSampleRate(unsigned int newSampleRate)
	{
		if (newSampleRate >= minSampleRate && newSampleRate <= maxSampleRate)
		{
			sampleRate = newSampleRate;
		}
		else if (newSampleRate > maxSampleRate)
		{
			sampleRate = maxSampleRate;
		}
		else
		{
			sampleRate = minSampleRate;
		}
	}

	// FUNCTION: ENGINE 0x105E4F30
	unsigned int RendererDriver::GetSampleRate() const
	{
		return sampleRate;
	}

	// FUNCTION: ENGINE 0x105E5820
	void RendererDriver::SetLatency(unsigned int newLatency)
	{
		unsigned int aligned = om::AlignUp(newLatency, 0x100);
		if (aligned >= minLatency && aligned <= maxLatency)
		{
			latency = aligned;
		}
		else if (aligned > maxLatency)
		{
			latency = maxLatency;
		}
		else
		{
			latency = minLatency;
		}
	}

	// FUNCTION: ENGINE 0x105E4F40
	unsigned int RendererDriver::GetLatency() const
	{
		return latency;
	}

	// FUNCTION: ENGINE 0x105E5860
	void RendererDriver::SetNumberOfChannels(unsigned int newNumberOfChannels)
	{
		if (newNumberOfChannels >= minNumberOfChannels && newNumberOfChannels <= maxNumberOfChannels)
		{
			numberOfChannels = newNumberOfChannels;
		}
		else if (newNumberOfChannels > maxNumberOfChannels)
		{
			numberOfChannels = maxNumberOfChannels;
		}
		else
		{
			numberOfChannels = minNumberOfChannels;
		}
	}

	// FUNCTION: ENGINE 0x105E4F50
	unsigned int RendererDriver::GetNumberOfChannels() const
	{
		return numberOfChannels;
	}

	// FUNCTION: ENGINE 0x105E4F60
	om::String RendererDriver::GetChannelName(int channel) const
	{
		return om::Format(0, "Ch %d", channel + 1);
	}

	// FUNCTION: ENGINE 0x105E4E80
	const om::FixedArray<unsigned int, 8>& RendererDriver::GetSurroundChannelMap() const
	{
		return surroundChannelMap;
	}

	// FUNCTION: ENGINE 0x105E4E60
	void RendererDriver::SetFoldDownType(FoldDownType newFoldDownType)
	{
		foldDownType = newFoldDownType;
	}

	// FUNCTION: ENGINE 0x105E4E70
	FoldDownType RendererDriver::GetFoldDownType() const
	{
		return foldDownType;
	}

	// FUNCTION: ENGINE 0x105E6690
	int RendererDriver::Slot17()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x105E4E90
	unsigned int RendererDriver::GetMinLatency() const
	{
		return minLatency;
	}

	// FUNCTION: ENGINE 0x105E4EA0
	unsigned int RendererDriver::GetMaxLatency() const
	{
		return maxLatency;
	}

	// FUNCTION: ENGINE 0x105E4EB0
	unsigned int RendererDriver::GetMinSampleRate() const
	{
		return minSampleRate;
	}

	// FUNCTION: ENGINE 0x105E4EC0
	unsigned int RendererDriver::GetMaxSampleRate() const
	{
		return maxSampleRate;
	}

	// FUNCTION: ENGINE 0x105E4ED0
	unsigned int RendererDriver::GetMinNumberOfChannels() const
	{
		return minNumberOfChannels;
	}

	// FUNCTION: ENGINE 0x105E4EE0
	unsigned int RendererDriver::GetMaxNumberOfChannels() const
	{
		return maxNumberOfChannels;
	}

	// FUNCTION: ENGINE 0x105E4EF0
	void RendererDriver::SetDescription(const om::String& newDescription, bool newAvailable)
	{
		available = newAvailable;
		description = newDescription;
	}

	// FUNCTION: ENGINE 0x105E4F10
	bool RendererDriver::GetDescription(om::String* result) const
	{
		if (result != 0)
		{
			*result = description;
		}
		return available;
	}

	// FUNCTION: ENGINE 0x105E5890
	unsigned int RendererDriver::GetUserData() const
	{
		return userData;
	}
}

namespace om
{
	// FUNCTION: ENGINE 0x105E6710
	template void MetaEnum<audio::FoldDownType>::Create(const ClassName&);
	// FUNCTION: ENGINE 0x105E6770
	template void MetaEnum<audio::FoldDownType>::ReleaseType();
	// FUNCTION: ENGINE 0x105E6870
	template void MetaEnum<audio::WAVEFORMAT>::Create(const ClassName&);
	// FUNCTION: ENGINE 0x105E68D0
	template void MetaEnum<audio::WAVEFORMAT>::ReleaseType();
	// FUNCTION: ENGINE 0x105E4FB0
	template MetaEnum<audio::FoldDownType>::MetaEnum(const ClassName&);
	// FUNCTION: ENGINE 0x105E4FD0
	template const type_info* MetaEnum<audio::FoldDownType>::GetType();
	// FUNCTION: ENGINE 0x105E4FE0
	template MetaEnum<audio::FoldDownType>::~MetaEnum();
	// FUNCTION: ENGINE 0x105E4FF0
	template bool MetaEnum<audio::FoldDownType>::WriteBinary(BinaryStream*, const void*);
	// FUNCTION: ENGINE 0x105E5010
	template void MetaEnum<audio::FoldDownType>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E5030
	template MetaClass<audio::RendererDriver>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105E5060
	template const type_info* MetaClass<audio::RendererDriver>::GetType();
	// FUNCTION: ENGINE 0x105E5070
	template MetaEnum<audio::WAVEFORMAT>::MetaEnum(const ClassName&);
	// FUNCTION: ENGINE 0x105E5090
	template const type_info* MetaEnum<audio::WAVEFORMAT>::GetType();
	// FUNCTION: ENGINE 0x105E50A0
	template MetaEnum<audio::WAVEFORMAT>::~MetaEnum();
	// FUNCTION: ENGINE 0x105E50B0
	template bool MetaEnum<audio::WAVEFORMAT>::WriteBinary(BinaryStream*, const void*);
	// FUNCTION: ENGINE 0x105E50D0
	template void MetaEnum<audio::WAVEFORMAT>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E5200
	template const char* MetaEnum<audio::FoldDownType>::AllocationTag();
	// FUNCTION: ENGINE 0x105E5210
	template const char* MetaClass<audio::RendererDriver>::AllocationTag();
	// FUNCTION: ENGINE 0x105E5220
	template const char* MetaEnum<audio::WAVEFORMAT>::AllocationTag();
	// FUNCTION: ENGINE 0x105E5230
	template MetaProperty<const FixedArray<unsigned int, 8>&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const FixedArray<unsigned int, 8>&>*, MetaMethod0Base<const FixedArray<unsigned int, 8>&>*, unsigned int);
	// FUNCTION: ENGINE 0x105E5270
	template const type_info* MetaProperty<const FixedArray<unsigned int, 8>&>::GetValueType();
	// FUNCTION: ENGINE 0x105E5280
	template MetaProperty<audio::FoldDownType>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, audio::FoldDownType>*, MetaMethod0Base<audio::FoldDownType>*, unsigned int);
	// FUNCTION: ENGINE 0x105E52C0
	template const type_info* MetaProperty<audio::FoldDownType>::GetValueType();
	// FUNCTION: ENGINE 0x105E5330
	template MetaMethod1Base<void, audio::FoldDownType>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105E53B0
	template MetaMethod0Base<audio::FoldDownType>::MetaMethod0Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105E5470
	template FixedArray<unsigned int, 8>::FixedArray(const FixedArray<unsigned int, 8>&);
	// FUNCTION: ENGINE 0x105E54D0
	template const char* MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x105E54E0
	template const char* MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, audio::FoldDownType>::AllocationTag();
	// FUNCTION: ENGINE 0x105E54F0
	template const char* MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, const FixedArray<unsigned int, 8>&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E5500
	template const char* MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, const FixedArray<unsigned int, 8>&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E5510
	template const char* MetaProperty<const FixedArray<unsigned int, 8>&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E5520
	template const char* MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x105E5530
	template const char* MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, audio::FoldDownType>::AllocationTag();
	// FUNCTION: ENGINE 0x105E5540
	template const char* MetaProperty<audio::FoldDownType>::AllocationTag();
	// FUNCTION: ENGINE 0x105E55C0
	template const char* DelegateMetaProperty<const FixedArray<unsigned int, 8>&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E55D0
	template const char* DelegateMetaProperty<audio::FoldDownType>::AllocationTag();
	// FUNCTION: ENGINE 0x105E58E0
	template bool MetaEnum<audio::FoldDownType>::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E5900
	template int MetaEnum<audio::FoldDownType>::Slot5();
	// FUNCTION: ENGINE 0x105E5910
	template void MetaEnum<audio::FoldDownType>::Slot6(void*);
	// FUNCTION: ENGINE 0x105E5940
	template int MetaClass<audio::RendererDriver>::Slot5();
	// FUNCTION: ENGINE 0x105E5950
	template void MetaClass<audio::RendererDriver>::Slot6(void*);
	// FUNCTION: ENGINE 0x105E5970
	template bool MetaEnum<audio::WAVEFORMAT>::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E5990
	template int MetaEnum<audio::WAVEFORMAT>::Slot5();
	// FUNCTION: ENGINE 0x105E59A0
	template void MetaEnum<audio::WAVEFORMAT>::Slot6(void*);
	// FUNCTION: ENGINE 0x105E5A10
	template void* MetaEnum<audio::FoldDownType>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E5A30
	template void* MetaClass<audio::RendererDriver>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E5A50
	template void* MetaEnum<audio::WAVEFORMAT>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E5AA0
	template void* MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E7CC0
	template FixedArray<unsigned int, 8>* ReadArgument<FixedArray<unsigned int, 8> >(BinaryStream*, GarbageList*);

	// FUNCTION: ENGINE 0x105E8140
	template void MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E5AC0
	template MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, unsigned int>::MetaMethod1(MetaClassBase*, const ClassName&, void (audio::RendererDriver::*)(unsigned int));
	// FUNCTION: ENGINE 0x105E5AF0
	template void MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x105E5B40
	template void* MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, audio::FoldDownType>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E8490
	template void MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, audio::FoldDownType>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E5B60
	template MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, audio::FoldDownType>::MetaMethod1(MetaClassBase*, const ClassName&, void (audio::RendererDriver::*)(audio::FoldDownType));
	// FUNCTION: ENGINE 0x105E5B90
	template void MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, audio::FoldDownType>::Call(void*, audio::FoldDownType);
	// FUNCTION: ENGINE 0x105E5BE0
	template void* MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, const FixedArray<unsigned int, 8>&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E8260
	template void MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, const FixedArray<unsigned int, 8>&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E5C00
	template MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, const FixedArray<unsigned int, 8>&>::MetaMethod1(MetaClassBase*, const ClassName&, void (audio::RendererDriver::*)(const FixedArray<unsigned int, 8>&));
	// FUNCTION: ENGINE 0x105E5C30
	template void MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, const FixedArray<unsigned int, 8>&>::Call(void*, const FixedArray<unsigned int, 8>&);
	// FUNCTION: ENGINE 0x105E5C90
	template const char* Garbage<FixedArray<unsigned int, 8>>::AllocationTag();
	// FUNCTION: ENGINE 0x105E5CA0
	template void* MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, const FixedArray<unsigned int, 8>&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E8330
	template void MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, const FixedArray<unsigned int, 8>&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E5CC0
	template MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, const FixedArray<unsigned int, 8>&>::MetaMethod0Const(MetaClassBase*, const ClassName&, FixedArray<unsigned int,8> const & (__thiscall audio::RendererDriver::*)(void)const);
	// FUNCTION: ENGINE 0x105E5CF0
	template const FixedArray<unsigned int, 8>& MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, const FixedArray<unsigned int, 8>&>::Call(void*);
	// FUNCTION: ENGINE 0x105E5D30
	template void* MetaProperty<const FixedArray<unsigned int, 8>&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E5D50
	template void* MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E5DE0
	template void MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E5D70
	template MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, unsigned int>::MetaMethod0Const(MetaClassBase*, const ClassName&, unsigned int (__thiscall audio::RendererDriver::*)(void)const);
	// FUNCTION: ENGINE 0x105E5DA0
	template unsigned int MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x105E5E80
	template void* MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, audio::FoldDownType>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E83D0
	template void MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, audio::FoldDownType>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E5EA0
	template MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, audio::FoldDownType>::MetaMethod0Const(MetaClassBase*, const ClassName&, audio::FoldDownType (__thiscall audio::RendererDriver::*)(void)const);
	// FUNCTION: ENGINE 0x105E5ED0
	template audio::FoldDownType MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, audio::FoldDownType>::Call(void*);
	// FUNCTION: ENGINE 0x105E5F10
	template void* MetaProperty<audio::FoldDownType>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E60B0
	template MetaMethod1Base<void, const FixedArray<unsigned int, 8>&>* MetaProperty<const FixedArray<unsigned int, 8>&>::GetSetter();
	// FUNCTION: ENGINE 0x105E60C0
	template MetaMethod0Base<const FixedArray<unsigned int, 8>&>* MetaProperty<const FixedArray<unsigned int, 8>&>::GetGetter();
	// FUNCTION: ENGINE 0x105E60D0
	template MetaMethod1Base<void, audio::FoldDownType>* MetaProperty<audio::FoldDownType>::GetSetter();
	// FUNCTION: ENGINE 0x105E60E0
	template MetaMethod0Base<audio::FoldDownType>* MetaProperty<audio::FoldDownType>::GetGetter();
	// FUNCTION: ENGINE 0x105E6130
	template void* DelegateMetaProperty<const FixedArray<unsigned int, 8>&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E6150
	template void* DelegateMetaProperty<audio::FoldDownType>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E6170
	template bool WriteBinary<audio::FoldDownType>(BinaryStream*, const audio::FoldDownType&);
	// FUNCTION: ENGINE 0x105E6220
	template void* Garbage<FixedArray<unsigned int, 8>>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E6240
	template Garbage<FixedArray<unsigned int, 8>>::Garbage(FixedArray<unsigned int, 8>*);
	// FUNCTION: ENGINE 0x105E6260
	template void FixedArray<unsigned int, 8>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E62A0
	template Garbage<FixedArray<unsigned int, 8>>::~Garbage();
	// FUNCTION: ENGINE 0x105E62D0
	template DelegateProperty<FixedArray<unsigned int, 8>>::DelegateProperty();
	// FUNCTION: ENGINE 0x105E62E0
	template MetaTypeBase* DelegateProperty<FixedArray<unsigned int, 8>>::GetMetaType();
	// FUNCTION: ENGINE 0x105E6300
	template DelegateProperty<audio::FoldDownType>::DelegateProperty();
	// FUNCTION: ENGINE 0x105E6310
	template MetaTypeBase* DelegateProperty<audio::FoldDownType>::GetMetaType();
	// FUNCTION: ENGINE 0x105E63B0
	template bool ReadText<audio::FoldDownType>(const TextValue*, audio::FoldDownType*);
	// FUNCTION: ENGINE 0x105E63E0
	template void WriteText<audio::FoldDownType>(TextValue*, const audio::FoldDownType&);
	// FUNCTION: ENGINE 0x105E67A0
	template void MetaEnum<audio::FoldDownType>::WriteText(TextValue*, const void*);
	// FUNCTION: ENGINE 0x105E67B0
	template void MetaClass<audio::RendererDriver>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105E6900
	template void MetaEnum<audio::WAVEFORMAT>::WriteText(TextValue*, const void*);
	// FUNCTION: ENGINE 0x105E6910
	template MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, const FixedArray<unsigned int, 8>&>* MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, const FixedArray<unsigned int, 8>&>::Create(MetaClassBase*, const ClassName&, void (audio::RendererDriver::*)(const FixedArray<unsigned int, 8>&));
	// FUNCTION: ENGINE 0x105E6950
	template MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, const FixedArray<unsigned int, 8>&>* MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, const FixedArray<unsigned int, 8>&>::Create(MetaClassBase*, const ClassName&, FixedArray<unsigned int,8> const & (__thiscall audio::RendererDriver::*)(void)const);
	// FUNCTION: ENGINE 0x105E6990
	template void MetaProperty<const FixedArray<unsigned int, 8>&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const FixedArray<unsigned int, 8>&>*, MetaMethod0Base<const FixedArray<unsigned int, 8>&>*, unsigned int);
	// FUNCTION: ENGINE 0x105E69F0
	template MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, unsigned int>* MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, unsigned int>::Create(MetaClassBase*, const ClassName&, void (audio::RendererDriver::*)(unsigned int));
	// FUNCTION: ENGINE 0x105E6A30
	template MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, unsigned int>* MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, unsigned int>::Create(MetaClassBase*, const ClassName&, unsigned int (__thiscall audio::RendererDriver::*)(void)const);
	// FUNCTION: ENGINE 0x105E6AC0
	template MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, audio::FoldDownType>* MetaMethod1<audio::RendererDriver, audio::RendererDriver, void, audio::FoldDownType>::Create(MetaClassBase*, const ClassName&, void (audio::RendererDriver::*)(audio::FoldDownType));
	// FUNCTION: ENGINE 0x105E6B00
	template MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, audio::FoldDownType>* MetaMethod0Const<audio::RendererDriver, audio::RendererDriver, audio::FoldDownType>::Create(MetaClassBase*, const ClassName&, audio::FoldDownType (__thiscall audio::RendererDriver::*)(void)const);
	// FUNCTION: ENGINE 0x105E6B40
	template void MetaProperty<audio::FoldDownType>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, audio::FoldDownType>*, MetaMethod0Base<audio::FoldDownType>*, unsigned int);
	// FUNCTION: ENGINE 0x105E6B90
	template bool ReadBinary<audio::FoldDownType>(BinaryStream*, audio::FoldDownType*);
	// FUNCTION: ENGINE 0x105E6C60
	template DelegateMetaProperty<const FixedArray<unsigned int, 8>&>::DelegateMetaProperty(void*, MetaProperty<const FixedArray<unsigned int, 8>&>*);
	// FUNCTION: ENGINE 0x105E6C90
	template void DelegateMetaProperty<const FixedArray<unsigned int, 8>&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105E6CD0
	template FixedArray<unsigned int, 8> DelegateMetaProperty<const FixedArray<unsigned int, 8>&>::Get();
	// FUNCTION: ENGINE 0x105E6D20
	template void DelegateMetaProperty<const FixedArray<unsigned int, 8>&>::Set(FixedArray<unsigned int, 8>);
	// FUNCTION: ENGINE 0x105E6D40
	template DelegateMetaProperty<audio::FoldDownType>::DelegateMetaProperty(void*, MetaProperty<audio::FoldDownType>*);
	// FUNCTION: ENGINE 0x105E6D70
	template void DelegateMetaProperty<audio::FoldDownType>::SetObject(void*);
	// FUNCTION: ENGINE 0x105E6DB0
	template audio::FoldDownType DelegateMetaProperty<audio::FoldDownType>::Get();
	// FUNCTION: ENGINE 0x105E6DD0
	template void DelegateMetaProperty<audio::FoldDownType>::Set(audio::FoldDownType);
	// FUNCTION: ENGINE 0x105E7B70
	template bool MetaEnum<audio::FoldDownType>::ReadText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105E7BE0
	template bool MetaEnum<audio::WAVEFORMAT>::ReadText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105E7D20
	template bool MetaProperty<const FixedArray<unsigned int, 8>&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105E7DC0
	template void MetaProperty<const FixedArray<unsigned int, 8>&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105E7E70
	template bool MetaProperty<const FixedArray<unsigned int, 8>&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E7EB0
	template bool MetaProperty<const FixedArray<unsigned int, 8>&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E7ED0
	template DelegatePropertyBase* MetaProperty<const FixedArray<unsigned int, 8>&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105E7F20
	template bool MetaProperty<audio::FoldDownType>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105E7FB0
	template void MetaProperty<audio::FoldDownType>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105E8040
	template bool MetaProperty<audio::FoldDownType>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E80A0
	template bool MetaProperty<audio::FoldDownType>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E80F0
	template DelegatePropertyBase* MetaProperty<audio::FoldDownType>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105E8850
	template FixedArray<unsigned int, 8>::FixedArray();
	// FUNCTION: ENGINE 0x105E51A0
	template void FixedArray<unsigned int, 8>::Fill(const unsigned int&);
	// FUNCTION: ENGINE 0x105E5190
	template unsigned int& FixedArray<unsigned int, 8>::operator[](int);
	// FUNCTION: ENGINE 0x105E5C80
	template const char* FixedArray<unsigned int, 8>::AllocationTag();
	// FUNCTION: ENGINE 0x105E6110
	template void* FixedArray<unsigned int, 8>::operator new(size_t);
}

namespace om
{
	// FUNCTION: ENGINE 0x105E5590
	template MetaClassBase* GetCachedClass<FixedArray<unsigned int, 8>>();
	// FUNCTION: ENGINE 0x105E5920
	template MetaClassBase* GetCachedClass<audio::RendererDriver>();
	// FUNCTION: ENGINE 0x105E60F0
	template MetaClassBase* GetCachedClass<audio::FoldDownType>();
}

namespace om
{
	// FUNCTION: ENGINE 0x105E6410
	bool ReadText(const TextValue* text, FixedArray<unsigned int, 8>* value)
	{
		TextValue* node = text->FindChild("Items");
		if (node == 0)
		{
			return true;
		}
		node = node->FindChild("Item");
		unsigned int* item = value->items;
		while (node != 0 && node->text == String::Wrap("Item"))
		{
			ReadText(node, item);
			node = node->parent->children.Next(node);
			item++;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105E6500
	void WriteText(TextValue* text, const FixedArray<unsigned int, 8>& value)
	{
		TextNode* items = new TextNode(text, String::Wrap("Items"));
		for (unsigned int i = 0; i < 8; i++)
		{
			WriteText(new TextNode(items, String::Wrap("Item")), value.items[i]);
		}
	}

	// FUNCTION: ENGINE 0x105E61A0
	bool ReadBinary(BinaryStream* stream, FixedArray<unsigned int, 8>* value)
	{
		for (unsigned int i = 0; i < 8; i++)
		{
			if (!ReadBinary(stream, &value->items[i]))
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105E61E0
	bool WriteBinary(BinaryStream* stream, const FixedArray<unsigned int, 8>& value)
	{
		for (unsigned int i = 0; i < 8; i++)
		{
			if (!WriteBinary(stream, value.items[i]))
			{
				return false;
			}
		}
		return true;
	}
}

namespace audio
{
	// FUNCTION: ENGINE 0x105E5680
	void RendererDriver::SetSurroundChannelMap(const om::FixedArray<unsigned int, 8>& newSurroundChannelMap)
	{
		for (int i = 0; i < 8; i++)
		{
			if (newSurroundChannelMap.items[i] >= maxNumberOfChannels)
			{
				surroundChannelMap.items[i] = 0xFFFFFFFF;
			}
			else
			{
				surroundChannelMap.items[i] = newSurroundChannelMap.items[i];
			}
		}
	}
}

namespace audio
{
	// The number of users of the reflection of WAVEFORMAT (0x112768F4, name guessed)
	int gWaveFormatMetaUsers = 0;

	// FUNCTION: ENGINE 0x105E7A10
	void RegisterWaveFormatMeta()
	{
		if (gWaveFormatMetaUsers == 0)
		{
			{
				om::String text("WAVEFORMAT", false);
				om::MetaEnum<WAVEFORMAT>::Create(om::MakeClassName(text));
			}
			{
				om::String text("EX", true);
				om::ClassName name = om::MakeClassName(text);
				om::MetaTypeBase* type = om::FindMetaType(typeid(WAVEFORMAT));
				static_cast<om::MetaEnumBase*>(type)->AddValue(name, 0);
			}
			{
				om::String text("EXTENSIBLE", true);
				om::ClassName name = om::MakeClassName(text);
				om::MetaTypeBase* type = om::FindMetaType(typeid(WAVEFORMAT));
				static_cast<om::MetaEnumBase*>(type)->AddValue(name, 1);
			}
		}
		gWaveFormatMetaUsers++;
	}

	// FUNCTION: ENGINE 0x105E7B30
	void UnregisterWaveFormatMeta()
	{
		gWaveFormatMetaUsers--;
		if (gWaveFormatMetaUsers == 0)
		{
			om::MetaEnum<WAVEFORMAT>::ReleaseType();
		}
	}
}

namespace audio
{
	// FUNCTION: ENGINE 0x105E7990
	void UnregisterRendererDriverMeta()
	{
		om::MetaEnum<FoldDownType>::ReleaseType();
		om::MetaTypeBase*& cache = om::MetaTypeCache<RendererDriver>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(RendererDriver));
		}
		om::MetaTypeBase* type = cache;
		if (om::ThreadSafeRefCount::Release(&cache->count) == 0 && type != 0)
		{
			delete type;
		}
		cache = 0;
	}
}

namespace audio
{
	// What the fold down needs for each type: the name and the program that does it (0x10E30E54, 8 entries of 12 bytes)
	struct FoldDownDescription
	{
		const char* name;
		const void* program;
		int unknown8;
	};
	extern const FoldDownDescription gFoldDownDescriptions[8];

	// FUNCTION: ENGINE 0x105E4DD0
	om::String GetFoldDownTypeName(FoldDownType type)
	{
		om::String text(gFoldDownDescriptions[type].name, true);
		return om::String(text);
	}
}
