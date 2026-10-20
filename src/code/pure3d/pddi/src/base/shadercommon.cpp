// pure3d::pddiShaderCommon, the part every shader shares: its constants, the checksum of them and the setters and
// getters by name (unit around 0x10613BC0 - 0x10614640; the file name is guessed from the RTTI name, no assert path
// survives).
#include "code/core/crc32.h"
#include "code/core/interlocked.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"

namespace pure3d
{
	// 0x11276B98: counts the changes of every shader's constants (name guess); 0x110BB348: the stamp of the shader the
	// device drew with last (-1 for none)
	extern unsigned int gShaderStampCounter;
	extern unsigned int gCurrentShaderStamp;
	// 0x11276BD0 / 0x11276BA0: what the getters answer for an input there is not (a null vector and the identity)
	extern float gDefaultVector[4];
	extern math::Matrix gDefaultMatrix;

	typedef core::Name<core::CaseInsensitiveKey32> ShaderInputName;

	// FUNCTION: ENGINE 0x10613BE0
	bool pddiShaderCommon::IsCurrent()
	{
		return stamp == gCurrentShaderStamp;
	}

	// FUNCTION: ENGINE 0x10613BF0
	void ResetShaderStamp()
	{
		gCurrentShaderStamp = 0xFFFFFFFF;
	}

	// FUNCTION: ENGINE 0x10613CB0
	// EQUIVALENT: the address of the values lands in edx here, in eax in the engine, 95.5 %
	void pddiShaderCommon::UpdateHash()
	{
		hash = 0xFFFFFFFF;
		hashDirty = false;
		hash = core::Crc32(constants->values, constants->count * 4, 0xFFFFFFFF);
	}

	// FUNCTION: ENGINE 0x10613CE0
	const ShaderInputName* pddiShaderCommon::GetTemplateName()
	{
		return &shaderTemplate->templateName;
	}

	// FUNCTION: ENGINE 0x10613D10
	bool pddiShaderCommon::HasInput(const ShaderInputName& name, const int& kind)
	{
		ConstantSlot slot;
		constants->Find(&slot, kind, &name);
		return slot.index != -1;
	}

	// FUNCTION: ENGINE 0x10613C00
	pddiShaderCommon::pddiShaderCommon(pddiBaseShaderTemplate* newTemplate)
	{
		hash = 0xFFFFFFFE;
		hashDirty = true;
		stamp = gShaderStampCounter++;
		shaderTemplate = newTemplate;
		newTemplate->AddRef();
		constants = new pddiBaseContext::Constants();
		newTemplate->InitConstants(constants);
		hashDirty = true;
	}

	// FUNCTION: ENGINE 0x10613C70
	void pddiShaderCommon::Unknown7(int unused, int* first, int* second)
	{
		first[0] = 0;
		first[1] = 0;
		first[2] = 0;
		first[3] = 0;
		first[4] = 0;
		first[5] = 0;
		first[6] = 0;
		first[7] = 0;
		second[0] = 0;
		second[1] = 0;
		second[2] = 0;
		second[3] = 0;
		second[4] = 0;
		second[5] = 0;
		second[6] = 0;
		second[7] = 0;
	}

	// FUNCTION: ENGINE 0x10613CF0
	void pddiShaderCommon::CopyConstants(pddiShaderCommon* other)
	{
		constants->CopyValuesFrom(other->constants);
	}

	// FUNCTION: ENGINE 0x10614560
	unsigned int pddiShaderCommon::GetHash()
	{
		if (hashDirty == true)
		{
			UpdateHash();
		}
		return hash;
	}

	// FUNCTION: ENGINE 0x106145D0
	int pddiShaderCommon::IsSameAs(pddiShaderCommon* other)
	{
		if (shaderTemplate == other->shaderTemplate)
		{
			if (hashDirty == true)
			{
				UpdateHash();
			}
			unsigned int mine = hash;
			if (other->hashDirty == true)
			{
				other->UpdateHash();
			}
			if (mine == other->hash)
			{
				return 1;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106145A0
	pddiShaderCommon::~pddiShaderCommon()
	{
		delete constants;
		ReleaseRef(&shaderTemplate);
	}

	// FUNCTION: ENGINE 0x10614540
	template void ReleaseRef<pddiBaseShaderTemplate>(pddiBaseShaderTemplate** ref);

	// FUNCTION: ENGINE 0x10613EC0
	void pddiShaderCommon::SetBool(const ShaderInputName& name, bool value)
	{
		ConstantSlot slot;
		constants->Find(&slot, 6, &name);
		if (slot.index != -1)
		{
			stamp = gShaderStampCounter++;
			unsigned int* flags = (unsigned int*)constants->values;
			unsigned int bit = 1 << slot.index;
			if (value)
			{
				*flags |= bit;
			}
			else
			{
				*flags &= ~bit;
			}
			hashDirty = true;
		}
	}

	// FUNCTION: ENGINE 0x10613F30
	void pddiShaderCommon::SetTexture(const ShaderInputName& name, dxTexture* texture)
	{
		ConstantSlot slot;
		constants->Find(&slot, 0, &name);
		if (slot.index != -1)
		{
			constants->SetTexture(&slot.index, (pddiSurface*)texture);
			stamp = gShaderStampCounter++;
			hashDirty = true;
		}
	}

	// FUNCTION: ENGINE 0x10613F90
	void pddiShaderCommon::SetFloat(const ShaderInputName& name, float value)
	{
		ConstantSlot slot;
		constants->Find(&slot, 1, &name);
		if (slot.index != -1)
		{
			stamp = gShaderStampCounter++;
			constants->values[slot.index] = value;
			hashDirty = true;
		}
	}

	// FUNCTION: ENGINE 0x10613FF0
	void pddiShaderCommon::SetVector2(const ShaderInputName& name, const float* value)
	{
		ConstantSlot slot;
		constants->Find(&slot, 2, &name);
		if (slot.index != -1)
		{
			stamp = gShaderStampCounter++;
			float* destination = constants->values + slot.index;
			destination[0] = value[0];
			destination[1] = value[1];
			hashDirty = true;
		}
	}

	// FUNCTION: ENGINE 0x10614050
	void pddiShaderCommon::SetVector3(const ShaderInputName& name, const math::Vector& value)
	{
		ConstantSlot slot;
		constants->Find(&slot, 3, &name);
		if (slot.index != -1)
		{
			stamp = gShaderStampCounter++;
			float* destination = constants->values + slot.index;
			destination[0] = value.x;
			destination[1] = value.y;
			destination[2] = value.z;
			hashDirty = true;
		}
	}

	// FUNCTION: ENGINE 0x106140C0
	void pddiShaderCommon::SetVector4(const ShaderInputName& name, const math::Vector4& value)
	{
		ConstantSlot slot;
		constants->Find(&slot, 4, &name);
		if (slot.index != -1)
		{
			stamp = gShaderStampCounter++;
			float* destination = constants->values + slot.index;
			destination[0] = value.x;
			destination[1] = value.y;
			destination[2] = value.z;
			destination[3] = value.w;
			hashDirty = true;
		}
	}

	// FUNCTION: ENGINE 0x10614130
	void pddiShaderCommon::SetColour(const ShaderInputName& name, const math::Vector4& value)
	{
		SetVector4(name, value);
	}

	// FUNCTION: ENGINE 0x10614140
	void pddiShaderCommon::SetMatrix(const ShaderInputName& name, const float* value)
	{
		ConstantSlot slot;
		constants->Find(&slot, 5, &name);
		if (slot.index != -1)
		{
			stamp = gShaderStampCounter++;
			*(math::Matrix*)(constants->values + slot.index) = *(const math::Matrix*)value;
			hashDirty = true;
		}
	}

	// FUNCTION: ENGINE 0x106141A0
	bool pddiShaderCommon::GetBool(const ShaderInputName& name)
	{
		ConstantSlot slot;
		constants->Find(&slot, 6, &name);
		if (slot.index == -1)
		{
			return false;
		}
		unsigned char word = (unsigned char)(*(unsigned int*)constants->values >> slot.index);
		unsigned char bit = word & 1;
		return bit;
	}

	// FUNCTION: ENGINE 0x106141F0
	float pddiShaderCommon::GetFloat(const ShaderInputName& name)
	{
		ConstantSlot slot;
		constants->Find(&slot, 1, &name);
		if (slot.index == -1)
		{
			return 0.0f;
		}
		return constants->values[slot.index];
	}

	// FUNCTION: ENGINE 0x10614230
	const float* pddiShaderCommon::GetVector2(const ShaderInputName& name)
	{
		ConstantSlot slot;
		constants->Find(&slot, 2, &name);
		if (slot.index == -1)
		{
			return gDefaultVector;
		}
		return constants->values + slot.index;
	}

	// FUNCTION: ENGINE 0x10614280
	const float* pddiShaderCommon::GetVector3(const ShaderInputName& name)
	{
		ConstantSlot slot;
		constants->Find(&slot, 3, &name);
		if (slot.index == -1)
		{
			return gDefaultVector;
		}
		return constants->values + slot.index;
	}

	// FUNCTION: ENGINE 0x106142D0
	const float* pddiShaderCommon::GetVector4(const ShaderInputName& name)
	{
		ConstantSlot slot;
		constants->Find(&slot, 4, &name);
		if (slot.index == -1)
		{
			return gDefaultVector;
		}
		return constants->values + slot.index;
	}

	// FUNCTION: ENGINE 0x10614320
	const float* pddiShaderCommon::GetMatrix(const ShaderInputName& name)
	{
		ConstantSlot slot;
		constants->Find(&slot, 5, &name);
		if (slot.index == -1)
		{
			return &gDefaultMatrix.m[0][0];
		}
		return constants->values + slot.index;
	}

	// FUNCTION: ENGINE 0x10614370
	pddiSurface* pddiShaderCommon::GetTexture(const ShaderInputName& name)
	{
		ConstantSlot slot;
		constants->Find(&slot, 0, &name);
		if (slot.index == -1)
		{
			return 0;
		}
		return *(pddiSurface**)&constants->values[slot.index];
	}

	// FUNCTION: ENGINE 0x10613D50
	void pddiShaderCommon::SetSampler(const ShaderInputName& name, bool linear, int addressU, int addressV, int unused)
	{
		ConstantSlot slot;
		constants->Find(&slot, 0, &name);
		if (slot.index != -1)
		{
			stamp = gShaderStampCounter++;
			unsigned int filter = (linear != false) + 1;
			unsigned int packed = ((((addressV & 3) | 4) << 2) | (addressU & 3));
			SamplerEntry* entry = (SamplerEntry*)&constants->values[slot.index];
			unsigned int word = *(unsigned int*)&entry->bits;
			*(unsigned int*)&entry->bits = (word & 0xFFFFFD0F) | (packed << 4);
			constants->SetSamplerFilters(&slot, filter, filter, filter, 1);
		}
	}

	// FUNCTION: ENGINE 0x10613DE0
	void pddiShaderCommon::SetSamplerAddress(const ShaderInputName& name, int addressU, int addressV, int addressW)
	{
		ConstantSlot slot;
		constants->Find(&slot, 0, &name);
		if (slot.index != -1)
		{
			stamp = gShaderStampCounter++;
			unsigned int packed = ((((addressW & 3) << 2) | (addressV & 3)) << 2) | (addressU & 3);
			SamplerEntry* entry = (SamplerEntry*)&constants->values[slot.index];
			unsigned int word = *(unsigned int*)&entry->bits;
			*(unsigned int*)&entry->bits = (word & 0xFFFFFC0F) | (packed << 4);
		}
	}

	// FUNCTION: ENGINE 0x10613E60
	void pddiShaderCommon::SetSamplerFilters(const ShaderInputName& name, int minFilter, int magFilter, int mipFilter,
		unsigned int anisotropy)
	{
		ConstantSlot slot;
		constants->Find(&slot, 0, &name);
		if (slot.index != -1)
		{
			stamp = gShaderStampCounter++;
			constants->SetSamplerFilters(&slot, minFilter, magFilter, mipFilter, anisotropy);
		}
	}

	// FUNCTION: ENGINE 0x106143B0
	// NONMATCHING: the filter flag is folded to a mask test, the original tests the extracted field of a local kept in memory; 26.5%
#ifdef NONMATCHING
	void pddiShaderCommon::GetSampler(const ShaderInputName& name, bool* linear, int* addressU, int* addressV,
		int* unknown)
	{
		ConstantSlot slot;
		constants->Find(&slot, 0, &name);
		if (slot.index != -1)
		{
			constants->GetSamplerAddress(slot, addressU, addressV, 0);
			if (unknown != 0)
			{
				*unknown = constants->GetSamplerUnknown(slot);
			}
			if (linear != 0)
			{
				int minFilter;
				constants->GetSamplerFilters(slot, &minFilter, 0, 0, 0);
				*linear = minFilter != 0;
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10614470
	void pddiShaderCommon::GetSamplerAddress(const ShaderInputName& name, int* addressU, int* addressV, int* addressW)
	{
		ConstantSlot slot;
		constants->Find(&slot, 0, &name);
		if (slot.index != -1)
		{
			SamplerEntry* entry = (SamplerEntry*)&constants->values[slot.index];
			if (addressU != 0)
			{
				*addressU = entry->bits.addressU;
			}
			if (addressV != 0)
			{
				*addressV = entry->bits.addressV;
			}
			if (addressW != 0)
			{
				*addressW = entry->bits.addressW;
			}
		}
	}

	// FUNCTION: ENGINE 0x106144F0
	void pddiShaderCommon::GetSamplerFilters(const ShaderInputName& name, int* minFilter, int* magFilter,
		int* mipFilter, unsigned int* anisotropy)
	{
		ConstantSlot slot;
		constants->Find(&slot, 0, &name);
		if (slot.index != -1)
		{
			constants->GetSamplerFilters(slot, minFilter, magFilter, mipFilter, anisotropy);
		}
	}
}
