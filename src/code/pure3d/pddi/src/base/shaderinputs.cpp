// pure3d::pddiBaseContext::Constants, constructor, destructor and the table of names (unit around 0x1061A3E0 -
// 0x1061ABB0; the file name is guessed from the RTTI name pddiShaderInputs, no assert path survives).
#include "code/pure3d/pddi.h"
#include <new>

namespace pure3d
{
	// FUNCTION: ENGINE 0x1061A3E0
	pddiBaseContext::Constants::Constants() : values(0), count(0), names(0), ownsValues(false), ownsNames(false)
	{
	}

	// FUNCTION: ENGINE 0x1061A470
	void pddiBaseContext::Constants::SetTexture(int* slot, pddiSurface* surface)
	{
		pddiSurface** texture = (pddiSurface**)&values[*slot];
		if (surface != 0)
		{
			surface->AddRef();
		}
		if (*texture != 0)
		{
			(*texture)->Release();
		}
		*texture = surface;
	}

	// FUNCTION: ENGINE 0x1061A4F0
	// EQUIVALENT: register allocation (the engine counts in esi and keeps the number of entries in edi, this compiler the other way round), 14.5 %
	ConstantName* ConstantNames::Find(const core::Name<core::CaseInsensitiveKey32>* name)
	{
		ConstantName* first = begin;
		unsigned int total = end - first;
		ConstantName* entry = first;
		for (unsigned int i = 0; i < total; i++, entry++)
		{
			if (entry->name == *name)
			{
				return first + i;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1061A540
	ConstantSlot* pddiBaseContext::Constants::Find(ConstantSlot* slot, int kind,
		const core::Name<core::CaseInsensitiveKey32>* name)
	{
		if (slot == 0)
		{
			return 0;
		}
		ConstantName* constant = names->Find(name);
		if (constant == 0)
		{
			slot->index = -1;
			return slot;
		}
		unsigned int bits = ((unsigned int*)constant)[1];
		if (kind != ((int)(bits << 12) >> 28))
		{
			slot->index = -1;
			return slot;
		}
		slot->index = (unsigned short)bits;
		return slot;
	}

	// FUNCTION: ENGINE 0x1061ABB0
	pddiBaseContext::Constants::~Constants()
	{
		for (unsigned int i = 0; i < (unsigned int)(names->end - names->begin); i++)
		{
			ConstantName* constant = names->begin + i;
			if ((((unsigned int*)constant)[1] & 0xF0000) == 0)
			{
				ConstantSlot slot(constant);
				SetTexture(&slot.index, 0);
			}
		}
		if (ownsValues)
		{
			delete[] (char*)values;
			values = 0;
			ownsValues = false;
		}
		if (ownsNames)
		{
			ConstantNames* table = names;
			if (table != 0)
			{
				void* entries = table->begin;
				if (entries != 0)
				{
					delete[] (char*)entries;
				}
				operator delete(table);
			}
			names = 0;
			ownsNames = false;
		}
	}
}

// Kept copies (compiler-generated and inline functions of this unit):
// FUNCTION: ENGINE 0x1061AC60
