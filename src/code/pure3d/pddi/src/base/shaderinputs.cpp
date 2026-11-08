// pure3d::pddiBaseContext::Constants, constructor, destructor and the table of names (unit around 0x1061A3E0 -
// 0x1061ABB0; the file name is guessed from the RTTI name pddiShaderInputs, no assert path survives).
#include "code/pure3d/pddi.h"
#include <new>
#include <string.h>

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

	// FUNCTION: ENGINE 0x1061A3D0
	float* pddiBaseContext::Constants::GetValueAt(const int* slot)
	{
		return values + *slot;
	}

	// FUNCTION: ENGINE 0x1061A410
	void pddiBaseContext::Constants::CopyTo(Constants* destination)
	{
		destination->names = names;
		destination->count = count;
		destination->values = new float[count];
		memcpy(destination->values, values, destination->count * 4);
		destination->ownsValues = true;
		destination->ownsNames = false;
	}

	// FUNCTION: ENGINE 0x1061A4B0
	void pddiBaseContext::Constants::CopyTexture(const int* slot, const unsigned int* source)
	{
		unsigned int* target = (unsigned int*)(values + *slot);
		pddiSurface* texture = (pddiSurface*)source[0];
		if (texture != 0)
		{
			texture->AddRef();
		}
		pddiSurface* held = (pddiSurface*)target[0];
		if (held != 0)
		{
			held->Release();
		}
		target[0] = source[0];
		target[1] = source[1];
	}

	// FUNCTION: ENGINE 0x1061A5E0
	// NONMATCHING: the copy of the entry and the spill of the slots, 17 %
#ifdef NONMATCHING
	void pddiBaseContext::Constants::CopyValuesFrom(Constants* other)
	{
		ConstantNames* otherNames = other->names;
		ConstantNames* ownNames = names;
		for (unsigned int i = 0; i < (unsigned int)(ownNames->end - ownNames->begin); i++)
		{
			ConstantName* own = ownNames->begin + i;
			for (unsigned int j = 0; j < (unsigned int)(otherNames->end - otherNames->begin); j++)
			{
				if (otherNames->begin[j].name == own->name)
				{
					ConstantName* match = otherNames->begin + j;
					if (match != 0)
					{
						ConstantName entry(*own);
						ConstantSlot from(match);
						ConstantSlot to(&entry);
						switch (entry.kind)
						{
						case 6:
							{
								unsigned int bit = 1 << to.index;
								if ((*(unsigned int*)other->values >> from.index) & 1)
								{
									*(unsigned int*)values |= bit;
								}
								else
								{
									*(unsigned int*)values &= ~bit;
								}
							}
							break;
						case 1:
							values[to.index] = other->values[from.index];
							break;
						case 2:
							{
								float* source = other->values + from.index;
								float* target = values + to.index;
								target[0] = source[0];
								target[1] = source[1];
							}
							break;
						case 3:
							{
								float* source = other->values + from.index;
								float* target = values + to.index;
								target[0] = source[0];
								target[1] = source[1];
								target[2] = source[2];
							}
							break;
						case 4:
							{
								float* source = other->values + from.index;
								float* target = values + to.index;
								target[0] = source[0];
								target[1] = source[1];
								target[2] = source[2];
								target[3] = source[3];
							}
							break;
						case 5:
							*(math::Matrix*)(values + to.index) = *(const math::Matrix*)(other->values + from.index);
							break;
						case 0:
							CopyTexture(&to.index, (const unsigned int*)(other->values + from.index));
							break;
						}
					}
					break;
				}
			}
		}
	}
#endif

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
