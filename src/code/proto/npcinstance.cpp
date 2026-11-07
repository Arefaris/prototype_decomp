#include "code/proto/npcinstance.h"
#include "code/core/refptr.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10479270
	NPCInstance::NPCInstance() : lod(1), unknown10(1), unknown11(false), registered(false), scale(1.0f), type(0), render(0), paletteIndex(0)
	{
	}

	// FUNCTION: ENGINE 0x10479550
	NPCInstance::~NPCInstance()
	{
		DestroyDrawable();
		core::SafeRelease(type);
		core::SafeRelease(render);
	}

	// FUNCTION: ENGINE 0x104792C0
	void NPCInstance::SetRegistered(bool newRegistered)
	{
		if (newRegistered != registered)
		{
			drawable.SetRegistered(newRegistered);
			registered = newRegistered;
		}
	}

	// FUNCTION: ENGINE 0x104792F0
	int NPCInstance::GetLod() const
	{
		return lod;
	}

	// FUNCTION: ENGINE 0x10479300
	int NPCInstance::GetUnknown10() const
	{
		return unknown10;
	}

	// FUNCTION: ENGINE 0x10479310
	NPCType* NPCInstance::GetType() const
	{
		return type;
	}

	// FUNCTION: ENGINE 0x10479320
	void NPCInstance::DestroyDrawable()
	{
		registered = false;
		if (drawable.IsValid())
		{
			drawable.SetRegistered(false);
			engine::render::Drawable::Destroy(&drawable, 0);
		}
	}

	// FUNCTION: ENGINE 0x10479360
	void NPCInstance::SetObject(engine::GameObject* newObject)
	{
		object = newObject;
	}

	// FUNCTION: ENGINE 0x10479370
	void NPCInstance::SetLod(int newLod)
	{
		lod = newLod;
	}

	// FUNCTION: ENGINE 0x10479380
	void NPCInstance::SetUnknown10(char newValue)
	{
		unknown10 = newValue;
	}

	// FUNCTION: ENGINE 0x10479390
	NPCRender* NPCInstance::GetRender() const
	{
		return render;
	}

	// FUNCTION: ENGINE 0x10479460
	void NPCInstance::SetScale(float newScale)
	{
		if (newScale != scale)
		{
			scale = newScale;
			drawable.SetUnknownBC(newScale);
		}
	}

	// FUNCTION: ENGINE 0x104794A0
	void NPCInstance::SetTransform(const math::Matrix& transform)
	{
		drawable.SetTransformQueued(transform);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104794B0
// FUNCTION: ENGINE 0x104798C0
