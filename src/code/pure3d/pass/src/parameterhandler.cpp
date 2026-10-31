// pure3d::ParameterHandlerTypeless (unit around 0x107A1B30 - 0x107A2D00; the file name is a guess). Names are guesses.
#include "code/math/colour128.h"
#include "code/pure3d/parameterhandler.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107A27B0
	// Takes a parameter node out of the tree for Clear
	bool DeleteParameter(container::TreeBase::Node* node, void* context)
	{
		operator delete[](node);
		return true;
	}

	// FUNCTION: ENGINE 0x107A2C90
	ParameterHandlerTypeless::ParameterHandlerTypeless() : owner(0)
	{
	}

	// FUNCTION: ENGINE 0x107A2CB0
	ParameterHandlerTypeless::~ParameterHandlerTypeless()
	{
		parameters.Clear(DeleteParameter, &parameters);
	}

	// FUNCTION: ENGINE 0x107A1E20
	Colour32::Colour32(const Colour32& other)
	{
		bits = (((other.a << 8 | other.r) << 8) | other.g) << 8 | other.b;
	}

	struct Words4
	{
		unsigned int words[4];
	};

	static inline void Copy4(Words4* to, const Words4* from)
	{
		*to = *from;
	}

	static inline void CopyVector(math::Vector* to, const math::Vector* from)
	{
		to->x = from->x;
		to->y = from->y;
		to->z = from->z;
	}

	static inline void CopyVector2(math::Vector2* to, const math::Vector2* from)
	{
		to->x = from->x;
		to->y = from->y;
	}

	static inline void CopyVector4(math::Vector4* to, const math::Vector4* from)
	{
		to->x = from->x;
		to->y = from->y;
		to->z = from->z;
		to->w = from->w;
	}

	// FUNCTION: ENGINE 0x107A1F80
	bool ParameterHandlerTypeless::SetInt(const ParameterName* name, int value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 2)
			{
				if (node->value.setter != 0)
				{
					*(int*)node->value.setter = value;
					return true;
				}
			}
			else if (node->value.kind == 13 && node->value.setter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, int))node->value.setter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A1FE0
	bool ParameterHandlerTypeless::SetUnknown1FE0(const ParameterName* name, unsigned int value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 3)
			{
				if (node->value.setter != 0)
				{
					*(unsigned int*)node->value.setter = value;
					return true;
				}
			}
			else if (node->value.kind == 14 && node->value.setter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, unsigned int))node->value.setter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2040
	bool ParameterHandlerTypeless::SetFloat(const ParameterName* name, float value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 1)
			{
				if (node->value.setter != 0)
				{
					*(float*)node->value.setter = value;
					return true;
				}
			}
			else if (node->value.kind == 12 && node->value.setter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, float))node->value.setter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A20B0
	bool ParameterHandlerTypeless::SetBool(const ParameterName* name, bool value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 4)
			{
				if (node->value.setter != 0)
				{
					*(bool*)node->value.setter = value;
					return true;
				}
			}
			else if (node->value.kind == 15 && node->value.setter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, bool))node->value.setter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2110
	bool ParameterHandlerTypeless::SetVector(const ParameterName* name, const math::Vector* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 5)
			{
				if (node->value.setter != 0)
				{
					CopyVector((math::Vector*)node->value.setter, value);
					return true;
				}
			}
			else if (node->value.kind == 16 && node->value.setter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, const math::Vector*))node->value.setter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2180
	bool ParameterHandlerTypeless::SetVector2(const ParameterName* name, const math::Vector2* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 6)
			{
				if (node->value.setter != 0)
				{
					CopyVector2((math::Vector2*)node->value.setter, value);
					return true;
				}
			}
			else if (node->value.kind == 17 && node->value.setter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, const math::Vector2*))node->value.setter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A21F0
	bool ParameterHandlerTypeless::SetVector4(const ParameterName* name, const math::Vector4* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 7)
			{
				if (node->value.setter != 0)
				{
					CopyVector4((math::Vector4*)node->value.setter, value);
					return true;
				}
			}
			else if (node->value.kind == 18 && node->value.setter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, const math::Vector4*))node->value.setter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2430
	bool ParameterHandlerTypeless::GetInt(const ParameterName* name, int* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 2)
			{
				if (node->value.setter != 0)
				{
					*value = *(int*)node->value.setter;
					return true;
				}
			}
			else if (node->value.kind == 13 && node->value.getter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, int*))node->value.getter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2490
	bool ParameterHandlerTypeless::GetUnknown2490(const ParameterName* name, unsigned int* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 3)
			{
				if (node->value.setter != 0)
				{
					*value = *(unsigned int*)node->value.setter;
					return true;
				}
			}
			else if (node->value.kind == 14 && node->value.getter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, unsigned int*))node->value.getter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A24F0
	bool ParameterHandlerTypeless::GetFloat(const ParameterName* name, float* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 1)
			{
				if (node->value.setter != 0)
				{
					*value = *(float*)node->value.setter;
					return true;
				}
			}
			else if (node->value.kind == 12 && node->value.getter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, float*))node->value.getter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2550
	bool ParameterHandlerTypeless::GetBool(const ParameterName* name, bool* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 4)
			{
				if (node->value.setter != 0)
				{
					*value = *(bool*)node->value.setter;
					return true;
				}
			}
			else if (node->value.kind == 15 && node->value.getter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, bool*))node->value.getter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A25B0
	bool ParameterHandlerTypeless::GetVector(const ParameterName* name, math::Vector* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 5)
			{
				if (node->value.setter != 0)
				{
					CopyVector(value, (math::Vector*)node->value.setter);
					return true;
				}
			}
			else if (node->value.kind == 16 && node->value.getter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, math::Vector*))node->value.getter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2620
	bool ParameterHandlerTypeless::GetVector4(const ParameterName* name, math::Vector4* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			if (node->value.kind == 7)
			{
				if (node->value.setter != 0)
				{
					CopyVector4(value, (math::Vector4*)node->value.setter);
					return true;
				}
			}
			else if (node->value.kind == 18 && node->value.getter != 0)
			{
				return ((bool (*)(void*, const ParameterName*, math::Vector4*))node->value.getter)(owner, name, value);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A27C0
	bool ParameterHandlerTypeless::SetColour(const ParameterName* name, const math::pddiColour* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			switch (node->value.kind)
			{
			case 8:
				if (node->value.setter != 0)
				{
					*(unsigned int*)node->value.setter = *(const unsigned int*)value;
					return true;
				}
				break;
			case 0x13:
				if (node->value.setter != 0)
				{
					return ((bool (*)(void*, const ParameterName*, const math::pddiColour*))node->value.setter)(owner, name, value);
				}
				break;
			case 9:
			case 0x14:
				{
					unsigned int word = (((value->a << 8 | value->r) << 8) | value->g) << 8 | value->b;
					return SetColourWord(name, &word);
				}
			case 10:
			case 0x15:
				{
					math::Colour128 colour((float)(int)value->r * (1.0f / 255.0f), (float)(int)value->g * (1.0f / 255.0f),
						(float)(int)(*(const unsigned int*)value & 0xff) * (1.0f / 255.0f), (float)(int)value->a * (1.0f / 255.0f));
					return SetColourFloats(name, &colour);
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2270
	bool ParameterHandlerTypeless::SetColourWord(const ParameterName* name, const unsigned int* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			switch (node->value.kind)
			{
			case 8:
			case 0x13:
				{
					const math::pddiColour* colour = (const math::pddiColour*)value;
					unsigned int word = (((colour->a << 8 | colour->r) << 8) | colour->g) << 8 | colour->b;
					return SetColour(name, (const math::pddiColour*)&word);
				}
			case 9:
				if (node->value.setter != 0)
				{
					*(unsigned int*)node->value.setter = *value;
					return true;
				}
				break;
			case 0x14:
				if (node->value.setter != 0)
				{
					return ((bool (*)(void*, const ParameterName*, const unsigned int*))node->value.setter)(owner, name, value);
				}
				break;
			case 10:
			case 0x15:
				{
					const math::pddiColour* colour = (const math::pddiColour*)value;
					math::Colour128 floats((float)(int)colour->r * (1.0f / 255.0f), (float)(int)colour->g * (1.0f / 255.0f),
						(float)(int)(*value & 0xff) * (1.0f / 255.0f), (float)(int)colour->a * (1.0f / 255.0f));
					return SetColourFloats(name, &floats);
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2910
	bool ParameterHandlerTypeless::SetColourFloats(const ParameterName* name, const math::Colour128* value)
	{
		math::pddiColour converted;
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			switch (node->value.kind)
			{
			case 8:
			case 0x13:
				{
					math::pddiColour first;
					const math::pddiColour* colour = first.FromColour128(*value);
					unsigned int word = (((colour->a << 8 | colour->r) << 8) | colour->g) << 8 | colour->b;
					return SetColour(name, (const math::pddiColour*)&word);
				}
			case 9:
			case 0x14:
				{
					return SetColourWord(name, (const unsigned int*)converted.FromColour128(*value));
				}
			case 10:
				if (node->value.setter != 0)
				{
					Copy4((Words4*)node->value.setter, (const Words4*)value);
					return true;
				}
				break;
			case 0x15:
				if (node->value.setter != 0)
				{
					return ((bool (*)(void*, const ParameterName*, const math::Colour128*))node->value.setter)(owner, name, value);
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2A20
	bool ParameterHandlerTypeless::GetColour(const ParameterName* name, math::pddiColour* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			switch (node->value.kind)
			{
			case 8:
				if (node->value.setter != 0)
				{
					*(unsigned int*)value = *(unsigned int*)node->value.setter;
					return true;
				}
				break;
			case 0x13:
				if (node->value.getter != 0)
				{
					return ((bool (*)(void*, const ParameterName*, math::pddiColour*))node->value.getter)(owner, name, value);
				}
				break;
			case 9:
			case 0x14:
				{
					unsigned int word;
					if (GetColourWord(name, &word))
					{
						value->CopyChannels(*(const math::pddiColour*)&word);
					}
				}
				break;
			case 10:
			case 0x15:
				{
					math::Colour128 floats;
					if (GetColourFloats(name, &floats))
					{
						value->FromColour128Sse(floats);
					}
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A26A0
	bool ParameterHandlerTypeless::GetColourWord(const ParameterName* name, unsigned int* value)
	{
		math::pddiColour converted;
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			switch (node->value.kind)
			{
			case 8:
			case 0x13:
				{
					math::pddiColour found;
					if (GetColour(name, &found))
					{
						Colour32 colour(*(const Colour32*)&found);
						*value = colour.bits;
					}
				}
				break;
			case 9:
				if (node->value.setter != 0)
				{
					*value = *(unsigned int*)node->value.setter;
					return true;
				}
				break;
			case 0x14:
				if (node->value.getter != 0)
				{
					return ((bool (*)(void*, const ParameterName*, unsigned int*))node->value.getter)(owner, name, value);
				}
				break;
			case 10:
			case 0x15:
				{
					math::Colour128 floats;
					if (GetColourFloats(name, &floats))
					{
						*value = *(const unsigned int*)converted.FromColour128(floats);
					}
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107A2B10
	// EQUIVALENT: block layout only (the engine places the shared conversion after the second case and jumps to it from
	// the first; ours after the first, 34 %)
	bool ParameterHandlerTypeless::GetColourFloats(const ParameterName* name, math::Colour128* value)
	{
		Node* node = (Node*)parameters.Find(CompareParameter, name);
		if (node != 0)
		{
			unsigned int word;
			switch (node->value.kind)
			{
			case 8:
			case 0x13:
				if (GetColour(name, (math::pddiColour*)&word))
				{
					math::Colour128 floats((float)(int)(word >> 16 & 0xff) * (1.0f / 255.0f), (float)(int)(word >> 8 & 0xff) * (1.0f / 255.0f),
						(float)(int)(word & 0xff) * (1.0f / 255.0f), (float)(int)(word >> 24) * (1.0f / 255.0f));
					*value = floats;
				}
				break;
			case 9:
			case 0x14:
				if (GetColourWord(name, &word))
				{
					math::Colour128 floats((float)(int)(word >> 16 & 0xff) * (1.0f / 255.0f), (float)(int)(word >> 8 & 0xff) * (1.0f / 255.0f),
						(float)(int)(word & 0xff) * (1.0f / 255.0f), (float)(int)(word >> 24) * (1.0f / 255.0f));
					*value = floats;
				}
				break;
			case 10:
				if (node->value.setter != 0)
				{
					Copy4((Words4*)value, (const Words4*)node->value.setter);
					return true;
				}
				break;
			case 0x15:
				if (node->value.getter != 0)
				{
					return ((bool (*)(void*, const ParameterName*, math::Colour128*))node->value.getter)(owner, name, value);
				}
			}
		}
		return false;
	}
}
