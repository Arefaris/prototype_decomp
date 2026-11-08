// pure3d::pddiShaderInputInitData: the description of a shader's inputs (unit 0x10612990 - 0x10613A20; the file name
// is guessed, no assert path survives).
#include <new>
#include <string.h>
#include "code/pure3d/primitive.h"
#include "code/core/heap.h"

namespace pure3d
{
	typedef core::Name<core::CaseInsensitiveKey32> InputName;

	// FUNCTION: ENGINE 0x10612A10
	inline bool ShaderInputList::PushBack(const ShaderInputValue& input)
	{
		if (end < capacity)
		{
			ShaderInputValue* slot = end;
			end++;
			new (slot) ShaderInputValue(input);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10612C20
	// NONMATCHING: register allocation, 24.3 %
#ifdef NONMATCHING
	void ShaderInputList::Resize(int capacityCount)
	{
		int count = Size();
		if (capacityCount != Capacity())
		{
			int newCount = count;
			if (capacityCount < count)
			{
				newCount = capacityCount;
			}
			ShaderInputValue* block = (ShaderInputValue*)operator new[](capacityCount * sizeof(ShaderInputValue));
			if (block == 0)
			{
				capacityCount = 0;
				newCount = 0;
			}
			else
			{
				for (int i = 0; i < newCount; i++)
				{
					new (block + i) ShaderInputValue(begin[i]);
				}
			}
			if (begin != 0)
			{
				operator delete[](begin);
			}
			begin = block;
			end = block + newCount;
			capacity = block + capacityCount;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10612990
	pddiShaderInputInitData::pddiShaderInputInitData()
	{
		{
			core::HeapScope scope(1);
			inputs = new ShaderInputList;
			inputs->Reserve(32);
		}
		hash = 0;
	}

	// FUNCTION: ENGINE 0x10612A70
	pddiShaderInputInitData::pddiShaderInputInitData(const pddiShaderInputInitData& other)
	{
		{
			core::HeapScope scope(1);
			inputs = new ShaderInputList;
			inputs->Reserve(other.inputs->Size());
		}
		for (unsigned int i = 0; i < (unsigned int)other.inputs->Size(); i++)
		{
			inputs->PushBack(other.inputs->begin[i]);
		}
		hash = other.hash;
	}

	// FUNCTION: ENGINE 0x10613840
	pddiShaderInputInitData::~pddiShaderInputInitData()
	{
		hash = 0;
		delete inputs;
	}

	// The first input of that name is the one that counts
	#define FIND_INPUT(name) 		ShaderInputList* list = inputs; 		ShaderInputValue* entry = list->begin; 		for (unsigned int i = 0; i < (unsigned int)list->Size(); i++, entry++) 		{ 			if (entry->name == name) 			{ 				return; 			} 		} 		if (list->end == list->capacity) 		{ 			list->Resize(list->Capacity() + 16); 		}

	// FUNCTION: ENGINE 0x10612D50
	// NONMATCHING: register allocation of the search loop, about 14 %
#ifdef NONMATCHING
	void pddiShaderInputInitData::AddDefault(int kind, const InputName& name)
	{
		FIND_INPUT(name)
		ShaderInputValue input;
		memset(&input, 0, sizeof(ShaderInputValue));
		input.name = name;
		input.kind = kind;
		inputs->PushBack(input);
		hash ^= name.GetKey().hash;
	}
#endif

	// FUNCTION: ENGINE 0x10612E60
	// NONMATCHING: register allocation of the search loop, about 14 %
#ifdef NONMATCHING
	void pddiShaderInputInitData::AddBool(int kind, const InputName& name, bool value)
	{
		FIND_INPUT(name)
		ShaderInputValue input;
		input.name = name;
		input.kind = kind;
		input.value.flag = value;
		inputs->PushBack(input);
		hash ^= name.GetKey().hash;
	}
#endif

	// FUNCTION: ENGINE 0x10612F70
	// NONMATCHING: register allocation of the search loop, about 14 %
#ifdef NONMATCHING
	void pddiShaderInputInitData::AddFloat(int kind, const InputName& name, float value)
	{
		FIND_INPUT(name)
		ShaderInputValue input;
		input.name = name;
		input.kind = kind;
		input.value.number = value;
		inputs->PushBack(input);
		hash ^= name.GetKey().hash;
	}
#endif

	// FUNCTION: ENGINE 0x10613080
	// NONMATCHING: register allocation of the search loop, about 14 %
#ifdef NONMATCHING
	void pddiShaderInputInitData::AddVector2(int kind, const InputName& name, const float* value)
	{
		FIND_INPUT(name)
		ShaderInputValue input;
		input.name = name;
		input.value.vector[0] = value[0];
		input.value.vector[1] = value[1];
		input.kind = kind;
		inputs->PushBack(input);
		hash ^= name.GetKey().hash;
	}
#endif

	// FUNCTION: ENGINE 0x106131A0
	// NONMATCHING: register allocation of the search loop, about 14 %
#ifdef NONMATCHING
	void pddiShaderInputInitData::AddVector3(int kind, const InputName& name, const float* value)
	{
		FIND_INPUT(name)
		ShaderInputValue input;
		input.name = name;
		input.value.vector[0] = value[0];
		input.value.vector[1] = value[1];
		input.value.vector[2] = value[2];
		input.kind = kind;
		inputs->PushBack(input);
		hash ^= name.GetKey().hash;
	}
#endif

	// FUNCTION: ENGINE 0x106132C0
	// NONMATCHING: register allocation of the search loop, about 14 %
#ifdef NONMATCHING
	void pddiShaderInputInitData::AddVector4(int kind, const InputName& name, const float* value)
	{
		FIND_INPUT(name)
		ShaderInputValue input;
		input.name = name;
		input.value.vector[0] = value[0];
		input.value.vector[1] = value[1];
		input.value.vector[2] = value[2];
		input.value.vector[3] = value[3];
		input.kind = kind;
		inputs->PushBack(input);
		hash ^= name.GetKey().hash;
	}
#endif

	// FUNCTION: ENGINE 0x106133F0
	// NONMATCHING: register allocation of the search loop, about 14 %
#ifdef NONMATCHING
	void pddiShaderInputInitData::AddMatrix(int kind, const InputName& name, const float* value)
	{
		FIND_INPUT(name)
		ShaderInputValue input;
		input.name = name;
		for (int i = 0; i < 16; i++)
		{
			input.value.vector[i] = value[i];
		}
		input.kind = kind;
		inputs->PushBack(input);
		hash ^= name.GetKey().hash;
	}
#endif

	// FUNCTION: ENGINE 0x106135A0
	// NONMATCHING: register allocation of the search loop, about 14 %
#ifdef NONMATCHING
	void pddiShaderInputInitData::AddFilter(int kind, const InputName& name, unsigned int filter)
	{
		FIND_INPUT(name)
		ShaderInputValue input;
		input.name = name;
		input.value.words[0] = (input.value.words[0] & 0xF8400150) | (filter & 0xF) | 0x400150;
		input.kind = kind;
		inputs->PushBack(input);
		hash ^= name.GetKey().hash;
	}
#endif

	// FUNCTION: ENGINE 0x106136C0
	// NONMATCHING: register allocation of the search loop, about 14 %
#ifdef NONMATCHING
	void pddiShaderInputInitData::AddSampler(int kind, const InputName& name, const SamplerSetting* value)
	{
		FIND_INPUT(name)
		ShaderInputValue input;
		input.name = name;
		input.value.sampler.h = value->h;
		input.value.sampler.g = value->g;
		input.value.sampler.f = value->f;
		input.value.sampler.e = value->e;
		input.value.sampler.d = value->d;
		input.value.sampler.c = value->c;
		input.value.sampler.b = value->b;
		input.value.sampler.a = value->a;
		input.kind = kind;
		inputs->PushBack(input);
		hash ^= name.GetKey().hash;
	}
#endif

	// FUNCTION: ENGINE 0x10613870
	void pddiShaderInputInitData::SetDefault(int kind, const char* name)
	{
		InputName inputName(name, 1);
		AddDefault(kind, inputName);
	}

	// FUNCTION: ENGINE 0x106138A0
	void pddiShaderInputInitData::SetBool(int kind, const char* name, bool value)
	{
		AddBool(kind, InputName(name, 1), value);
	}

	// FUNCTION: ENGINE 0x106138D0
	void pddiShaderInputInitData::SetFloat(int kind, const char* name, float value)
	{
		AddFloat(kind, InputName(name, 1), value);
	}

	// FUNCTION: ENGINE 0x10613900
	void pddiShaderInputInitData::SetVector2(int kind, const char* name, const float* value)
	{
		AddVector2(kind, InputName(name, 1), value);
	}

	// FUNCTION: ENGINE 0x10613930
	void pddiShaderInputInitData::SetVector3(int kind, const char* name, const float* value)
	{
		AddVector3(kind, InputName(name, 1), value);
	}

	// FUNCTION: ENGINE 0x10613960
	void pddiShaderInputInitData::SetVector4(int kind, const char* name, const float* value)
	{
		AddVector4(kind, InputName(name, 1), value);
	}

	// FUNCTION: ENGINE 0x10613990
	void pddiShaderInputInitData::SetMatrix(int kind, const char* name, const float* value)
	{
		AddMatrix(kind, InputName(name, 1), value);
	}

	// FUNCTION: ENGINE 0x106139C0
	void pddiShaderInputInitData::SetFilter(int kind, const char* name, unsigned int filter)
	{
		AddFilter(kind, InputName(name, 1), filter);
	}

	// FUNCTION: ENGINE 0x106139F0
	void pddiShaderInputInitData::SetSampler(int kind, const char* name, const SamplerSetting* value)
	{
		AddSampler(kind, InputName(name, 1), value);
	}
}
