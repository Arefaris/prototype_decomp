// pure3d::LightSelection (0x10717920 - 0x10718DB9; file name guessed from the class). Only the small accessors and
// the scales the lit passes call are reconstructed. Names are guesses.
#include <algorithm>
#include <math.h>

#include "code/container/arrayfixed.h"
#include "code/pure3d/light.h"
#include "code/pure3d/lighting.h"
#include "code/pure3d/lightselection.h"
#include "code/pure3d/pass.h"
#include "code/pure3d/scene.h"
#include "code/pure3d/view.h"

namespace pure3d
{
	// A selected light and how far it is from the eye; the sort orders them nearest first
	struct LightDistance
	{
		Light* light;
		float distance;
	};

	inline bool operator<(const LightDistance& a, const LightDistance& b)
	{
		return a.distance < b.distance;
	}

	// FUNCTION: ENGINE 0x10718830
	LightSelection::LightSelection() : mode(0), unknown34(false)
	{
	}

	// FUNCTION: ENGINE 0x107188C0
	LightSelection::~LightSelection()
	{
	}

	// FUNCTION: ENGINE 0x10718900
	void LightSelection::Start()
	{
		gLightSelection = new LightSelection;
	}

	// FUNCTION: ENGINE 0x107189C0
	void LightSelection::Stop()
	{
		delete gLightSelection;
		gLightSelection = 0;
	}

	// FUNCTION: ENGINE 0x10717920
	LightSelection* LightSelection::Get()
	{
		return gLightSelection;
	}

	// FUNCTION: ENGINE 0x10717930
	void LightSelection::SetMode(int newMode)
	{
		if (unknown34 && newMode == 1)
		{
			newMode = 3;
		}
		mode = newMode;
	}

	// FUNCTION: ENGINE 0x10717950
	int LightSelection::GetMode()
	{
		return mode;
	}

	// FUNCTION: ENGINE 0x10717960
	LightList* LightSelection::GetActiveLights()
	{
		return &active;
	}

	// FUNCTION: ENGINE 0x10717970
	LightList* LightSelection::GetVertexLights()
	{
		return &vertex;
	}

	// FUNCTION: ENGINE 0x10717980
	void LightSelection::SetUnknown34(bool value)
	{
		unknown34 = value;
	}

	// FUNCTION: ENGINE 0x10717990
	float LightSelection::GetRangeScale(Light* light)
	{
		float scale = 1.0f;
		if (light->GetUserData())
		{
			scale = ((ProtoLightUserData*)light->GetUserData())->unknown10;
		}
		return scale;
	}

	// FUNCTION: ENGINE 0x107179D0
	float LightSelection::GetIntensityScale(Light* light, int scaleMode)
	{
		float scale = 1.0f;
		if (light->GetUserData())
		{
			ProtoLightUserData* data = (ProtoLightUserData*)light->GetUserData();
			switch (scaleMode)
			{
			case 0:
				scale = data->unknownC;
				break;
			case 1:
				scale = data->unknown8;
				break;
			}
		}
		return scale;
	}

	// FUNCTION: ENGINE 0x10718170
	void LightSelection::UploadVertexLights()
	{
		for (unsigned int slot = 0; slot < 5; slot++)
		{
			UploadLight(0, slot, 0);
		}
		if (Get()->GetMode() != 0)
		{
			unsigned int size = vertex.end - vertex.begin;
			unsigned int count = size > 5 ? 5 : size;
			for (unsigned int slot = 0; slot < count; slot++)
			{
				UploadLight(vertex.begin[slot], slot, 0);
			}
		}
	}

	// FUNCTION: ENGINE 0x10718B30
	void LightSelection::Fill(PassContext* context)
	{
		LightList* all = &candidates;
		LightList* act = &active;
		LightList* vert = &vertex;
		all->end = all->begin;
		act->end = act->begin;
		vert->end = vert->begin;
		context->scene->GetLightingScene()->CollectLights(all);
		for (unsigned int i = 0; i < (unsigned int)(all->end - all->begin); i++)
		{
			Light* light = all->begin[i];
			bool spot = light->type == Light::TYPE_SPOT;
			bool unlimited = light->GetDecay()->GetKind() == 0 && (light->type == Light::TYPE_DIRECTIONAL || light->type == Light::TYPE_AMBIENT);
			if (spot || unlimited)
			{
				active.PushBack(light);
			}
		}
		for (unsigned int i = 0; i < (unsigned int)(all->end - all->begin); i++)
		{
			Light* light = all->begin[i];
			if (light->type == Light::TYPE_POINT)
			{
				active.PushBack(light);
			}
		}
		for (unsigned int i = 0; i < (unsigned int)(all->end - all->begin); i++)
		{
			Light* light = all->begin[i];
			if (light->type == Light::TYPE_POINT)
			{
				ProtoLightUserData* data = dynamic_cast<ProtoLightUserData*>(light->GetUserData());
				if (data == 0 || data->cheap == 1)
				{
					vertex.PushBack(light);
				}
			}
		}
		container::ArrayFixed<LightDistance, 1024> sorted;
		const math::Matrix& transform = context->camera->transform;
		math::Vector eye;
		eye.x = transform.m[3][0];
		eye.y = transform.m[3][1];
		eye.z = transform.m[3][2];
		for (unsigned int i = 0; i < (unsigned int)(vertex.end - vertex.begin); i++)
		{
			Light* light = vertex.begin[i];
			const math::Vector* position = light->GetPosition();
			float dx = eye.x - position->x;
			float dy = eye.y - position->y;
			float dz = eye.z - position->z;
			LightDistance entry;
			entry.light = light;
			entry.distance = sqrtf(dz * dz + dy * dy + dx * dx);
			sorted.PushBack(entry);
		}
		// std::sort is called out of line, as the engine does
		void (*sorter)(LightDistance*, LightDistance*) = std::sort<LightDistance*>;
		sorter(sorted.Begin(), sorted.End());
		vertex.end = vertex.begin;
		for (unsigned int i = 0; i < (unsigned int)sorted.Size(); i++)
		{
			vertex.PushBack(sorted[i].light);
		}
	}
}

// The sort of the selected vertex lights is the toolchain's <algorithm> for LightDistance*; the unit keeps every instance of
// it as a COMDAT function of its own, and the compiler reproduces each one
// FUNCTION: ENGINE 0x10717B00
template void container::Construct<pure3d::LightDistance>(pure3d::LightDistance*, const pure3d::LightDistance&);

// FUNCTION: ENGINE 0x10717B20
template void container::Destroy<pure3d::LightDistance>(pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10717B30
template pure3d::LightDistance* std::_Checked_base<pure3d::LightDistance*>(pure3d::LightDistance*&, std::_Unchanged_checked_iterator_base_type_tag);

// FUNCTION: ENGINE 0x10717B40
template std::pair<pure3d::LightDistance*, pure3d::LightDistance*>::pair(pure3d::LightDistance* const&, pure3d::LightDistance* const&);

// FUNCTION: ENGINE 0x10717B60
template int* std::_Dist_type<pure3d::LightDistance*>(pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10717B70
template pure3d::LightDistance* std::_Val_type<pure3d::LightDistance*>(pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10717B80
template void std::swap<pure3d::LightDistance>(pure3d::LightDistance&, pure3d::LightDistance&);

// FUNCTION: ENGINE 0x10717BB0
template void std::_Push_heap<pure3d::LightDistance*, int, pure3d::LightDistance>(pure3d::LightDistance*, int, int, pure3d::LightDistance);

// FUNCTION: ENGINE 0x10717C10
template std::random_access_iterator_tag std::_Iter_random<pure3d::LightDistance*, pure3d::LightDistance*>(pure3d::LightDistance* const&, pure3d::LightDistance* const&);

// FUNCTION: ENGINE 0x10717C20
template std::_Nonscalar_ptr_iterator_tag std::_Ptr_cat<pure3d::LightDistance*, pure3d::LightDistance*>(pure3d::LightDistance*&, pure3d::LightDistance*&);

// FUNCTION: ENGINE 0x10717C30
template pure3d::LightDistance* std::_Copy_backward_opt<pure3d::LightDistance*, pure3d::LightDistance*, std::forward_iterator_tag>(pure3d::LightDistance*, pure3d::LightDistance*, pure3d::LightDistance*, std::forward_iterator_tag, std::_Nonscalar_ptr_iterator_tag, std::_Range_checked_iterator_tag);

// FUNCTION: ENGINE 0x10717FB0
template void container::Destroy<pure3d::LightDistance>(pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10717FC0
template pure3d::LightDistance* std::_Checked_base<pure3d::LightDistance*>(pure3d::LightDistance*&);

// FUNCTION: ENGINE 0x10717FD0
template void std::iter_swap<pure3d::LightDistance*, pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718000
template void std::_Med3<pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718070
template void std::_Adjust_heap<pure3d::LightDistance*, int, pure3d::LightDistance>(pure3d::LightDistance*, int, int, pure3d::LightDistance);

// FUNCTION: ENGINE 0x107180F0
template pure3d::LightDistance* std::_Copy_backward_opt<pure3d::LightDistance*, pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*, pure3d::LightDistance*, std::random_access_iterator_tag, std::_Nonscalar_ptr_iterator_tag, std::_Range_checked_iterator_tag);

// FUNCTION: ENGINE 0x10718130
template void std::_Pop_heap<pure3d::LightDistance*, int, pure3d::LightDistance>(pure3d::LightDistance*, pure3d::LightDistance*, pure3d::LightDistance*, pure3d::LightDistance, int*);

// FUNCTION: ENGINE 0x10718200
template void std::_Median<pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718290
template void std::_Make_heap<pure3d::LightDistance*, int, pure3d::LightDistance>(pure3d::LightDistance*, pure3d::LightDistance*, int*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x107182E0
template pure3d::LightDistance* stdext::unchecked_copy_backward<pure3d::LightDistance*, pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718320
template void std::_Pop_heap_0<pure3d::LightDistance*, pure3d::LightDistance>(pure3d::LightDistance*, pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718390
template std::pair<pure3d::LightDistance*, pure3d::LightDistance*> std::_Unguarded_partition<pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718710
template void std::make_heap<pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718740
template void std::_Insertion_sort1<pure3d::LightDistance*, pure3d::LightDistance>(pure3d::LightDistance*, pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x107187E0
template void std::pop_heap<pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718950
template void std::_Insertion_sort<pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718970
template void std::_Sort_heap<pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x107189F0
template void std::sort_heap<pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*);

// FUNCTION: ENGINE 0x10718A00
template void std::_Sort<pure3d::LightDistance*, int>(pure3d::LightDistance*, pure3d::LightDistance*, int);

// FUNCTION: ENGINE 0x10718AF0
template void std::sort<pure3d::LightDistance*>(pure3d::LightDistance*, pure3d::LightDistance*);

