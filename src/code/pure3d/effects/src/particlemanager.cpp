// The particle module of pure3d (unit around 0x106EA000 - 0x106F2800; the class and file names are guesses): one
// manager, reached through GetParticleManager, that keeps the particle system states and their buffers.
#include "code/math/mathutils.h"
#include "code/math/pddicolour.h"
#include "code/math/vector4.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/vertexstream.h"

namespace math
{
	static inline int ToByte(float value)
	{
		int v = (int)(value * 255.5f);
		if (v < 0)
		{
			v = 0;
		}
		else if (v > 255)
		{
			v = 255;
		}
		return v;
	}

	// FUNCTION: ENGINE 0x102CD6D0
	// EQUIVALENT: the engine tests v < 0 first and then v > 255 on both paths; every clamp form tried here tests in
	// another order
	// An inline of the math headers whose kept copy sits in another unit (the particle colours use it here)
	pddiColour::pddiColour(const Vector4& colour)
	{
		int alpha = ToByte(colour.w);
		int blue = ToByte(colour.z);
		int green = ToByte(colour.y);
		int red = ToByte(colour.x);
		*(unsigned int*)this = ((alpha << 8 | red) << 8 | green) << 8 | blue;
	}
}

namespace pure3d
{
	// 0x1127EE4C
	extern ParticleManager* gParticleManager;

	// FUNCTION: ENGINE 0x106E9910
	bool ParticleSystemState::GetUnknown4B8()
	{
		return unknown4B8;
	}

	// FUNCTION: ENGINE 0x106E9920
	bool ParticleSystemState::GetInheritUnknown4BC()
	{
		return inheritUnknown4BC;
	}

	// FUNCTION: ENGINE 0x106E98D0
	float ParticleSystemState::GetUnknown49C()
	{
		return unknown49C;
	}

	// FUNCTION: ENGINE 0x106E9970
	ParticleGenerator* ParticleSystemState::GetGenerator()
	{
		return generator;
	}

	// FUNCTION: ENGINE 0x106E9940
	// A state may take the flag from the state it was made from
	bool ParticleSystemState::GetUnknown3F4()
	{
		ParticleSystemState* state = this;
		while (state->inheritUnknown4BC)
		{
			state = state->parent;
		}
		return state->unknown3F4;
	}

	// FUNCTION: ENGINE 0x106E9980
	unsigned int ParticleSystemState::GetParticleCount()
	{
		return inheritUnknown4BC ? parent->GetParticleCount() : particleCount;
	}

	// FUNCTION: ENGINE 0x106ED9D0
	// A state may take the flag from the state it was made from
	bool ParticleSystemState::GetUnknown4BC()
	{
		return inheritUnknown4BC ? parent->GetUnknown4BC() : unknown4BC;
	}

	// FUNCTION: ENGINE 0x106EDA80
	ParticleManager* GetParticleManager()
	{
		return gParticleManager;
	}

	// FUNCTION: ENGINE 0x106EDC90
	bool ParticleManager::HasUnknown1A0()
	{
		return unknown1A0 != -1;
	}

	// FUNCTION: ENGINE 0x106EDCA0
	unsigned __int64 ParticleManager::GetUnknown1B0()
	{
		return unknown1B0;
	}

	// FUNCTION: ENGINE 0x106EDAB0
	bool ParticleManager::GetUnknown184()
	{
		return unknown184;
	}

	// FUNCTION: ENGINE 0x106EDAA0
	void ParticleManager::SetUnknown184(bool value)
	{
		unknown184 = value;
	}

	// FUNCTION: ENGINE 0x106EDB20
	bool ParticleManager::GetUnknown198()
	{
		return unknown198;
	}

	// FUNCTION: ENGINE 0x106EDB30
	void ParticleManager::ClearUnknown198()
	{
		unknown198 = false;
	}

	// FUNCTION: ENGINE 0x106EDAC0
	void ParticleManager::SetUnknown199(bool value)
	{
		unknown199 = !value;
	}

	// FUNCTION: ENGINE 0x106EDB40
	void ParticleManager::SetUnknown19A(bool value)
	{
		unknown19A = value;
	}

	// FUNCTION: ENGINE 0x106EDBC0
	void ParticleManager::SetUnknown19C(float value)
	{
		unknown19C = value;
	}

	// FUNCTION: ENGINE 0x106EDBE0
	float ParticleManager::GetUnknown19C()
	{
		return unknown19C;
	}

	// FUNCTION: ENGINE 0x106EDBF0
	void ParticleManager::PushUnknown1A0()
	{
		unknown1A4 = unknown1A0;
		unknown1A0 = -1;
	}

	// FUNCTION: ENGINE 0x106EDC10
	void ParticleManager::PopUnknown1A0()
	{
		unknown1A0 = unknown1A4;
	}

	// FUNCTION: ENGINE 0x106EDC80
	int ParticleManager::GetUnknown1A0()
	{
		return unknown1A0;
	}

	// FUNCTION: ENGINE 0x106EDCB0
	void ParticleManager::SetUnknown1B0(unsigned __int64 value)
	{
		unknown1B0 = value;
	}

	// FUNCTION: ENGINE 0x106EDD50
	float ParticleManager::GetUnknown1BC()
	{
		return unknown1BC;
	}

	// FUNCTION: ENGINE 0x106EDD60
	void ParticleManager::SetUnknown1BC(float value)
	{
		unknown1BC = value;
	}

	// FUNCTION: ENGINE 0x106EDD80
	float ParticleManager::GetUnknown1B8()
	{
		return unknown1B8;
	}

	// FUNCTION: ENGINE 0x106EDD90
	void ParticleManager::SetUnknown1B8(float value)
	{
		unknown1B8 = value;
	}

	// FUNCTION: ENGINE 0x106EE6E0
	// NONMATCHING: the engine keeps the index in esi and the count in edi (80 %)
#ifdef NONMATCHING
	unsigned int ParticleManager::FindParameter(const core::Name<core::CaseInsensitiveKey32>& name)
	{
		unsigned int i = 0;
		ParticleParameter** items = parameters;
		unsigned int count = parametersEnd - items;
		ParticleParameter** item = items;
		for (; i < count; i++, item++)
		{
			if ((*item)->name == name)
			{
				return items[i]->index;
			}
		}
		return -1;
	}
#endif

	// FUNCTION: ENGINE 0x106EE730
	// NONMATCHING: the engine keeps the index in esi and the count in edi (80 %)
#ifdef NONMATCHING
	unsigned int ParticleManager::FindParameterUnknownC(const core::Name<core::CaseInsensitiveKey32>& name)
	{
		unsigned int i = 0;
		ParticleParameter** items = parameters;
		unsigned int count = parametersEnd - items;
		ParticleParameter** item = items;
		for (; i < count; i++, item++)
		{
			if ((*item)->name == name)
			{
				return items[i]->unknownC;
			}
		}
		return -1;
	}
#endif

	// FUNCTION: ENGINE 0x106EE780
	unsigned int ParticleManager::GetEntryCount()
	{
		return entriesEnd - entries;
	}

	// FUNCTION: ENGINE 0x106EE790
	// NONMATCHING: the engine reads the entry through a stepped pointer and reloads it for the name (37 %)
#ifdef NONMATCHING
	int ParticleManager::FindEntry(const core::Name<core::CaseInsensitiveKey32>& name)
	{
		unsigned int count = GetEntryCount();
		ParticleEntry** list = entries;
		for (unsigned int i = 0; i < count; i++)
		{
			if (list[i] && list[i]->name == name)
			{
				return i;
			}
		}
		return -1;
	}
#endif

	// FUNCTION: ENGINE 0x106EE7E0
	int ParticleManager::GetEntryNumber(int index)
	{
		return entries[index]->number;
	}

	// FUNCTION: ENGINE 0x106EE860
	void ParticleManager::ReleaseState(PrimitiveState* state)
	{
		for (unsigned int i = 0; i < states.Size(); i++)
		{
			if (states[i].state == state)
			{
				states[i].released = true;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x106EECB0
	unsigned int ParticleManager::GetMaxParts()
	{
		return states.Capacity() - states.Size();
	}
}

// The streams of vectors and of four-component vectors the particle module's buffers are written through (the
// engine's kept copies sit in this unit)
// FUNCTION: ENGINE 0x106EBB40
template void pure3d::VertexStream<math::Vector>::Init(pure3d::dxVertexDeclaration* lock,
	core::Name<core::CaseInsensitiveKey32> name);

// FUNCTION: ENGINE 0x106EBBA0
template void pure3d::VertexStream<math::Vector4>::Init(pure3d::dxVertexDeclaration* lock,
	core::Name<core::CaseInsensitiveKey32> name);

// FUNCTION: ENGINE 0x106EC110
template pure3d::VertexStream<math::Vector>::VertexStream(pure3d::dxVertexDeclaration* lock,
	core::Name<core::CaseInsensitiveKey32> name);

// FUNCTION: ENGINE 0x106EC140
template pure3d::VertexStream<math::Vector4>::VertexStream(pure3d::dxVertexDeclaration* lock,
	core::Name<core::CaseInsensitiveKey32> name);

// FUNCTION: ENGINE 0x106EBC00
template void pure3d::VertexStream<math::pddiColour>::Init(pure3d::dxVertexDeclaration* lock,
	core::Name<core::CaseInsensitiveKey32> name);

// FUNCTION: ENGINE 0x106EC170
template pure3d::VertexStream<math::pddiColour>::VertexStream(pure3d::dxVertexDeclaration* lock,
	core::Name<core::CaseInsensitiveKey32> name);
