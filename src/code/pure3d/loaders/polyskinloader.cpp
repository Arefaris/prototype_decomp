// pure3d::PolySkinLoader: see the header. The file name is a guess.
#include <new>

#include "code/pure3d/loaders/polyskinloader.h"

#include "code/container/arraydynamicallocatornew.h"
#include "code/pure3d/context.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/loaders/drawableloaders.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10B90CA0
	void PolySkinLoader::LoadObject(core::IRefCount** object, content::ObjectName* name,
		content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		char text[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(text, length, 1, 1);
			text[length] = 0;
		}
		{
			unsigned int scratch;
			reader->Read(&scratch, 1, 4, 1);
		}
		char skeletonName[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(skeletonName, length, 1, 1);
			skeletonName[length] = 0;
		}
		Skeleton* skeleton = inventory->Find<Skeleton>(skeletonName);
		Pose* pose = 0;
		if (skeleton != 0 && sCreatePoses)
		{
			pose = skeleton->CreatePose(3);
		}
		math::Sphere sphere;
		sphere.centre.Set(0.0f, 0.0f, 0.0f);
		OldVertexAnimKeyFrameList* group = 0;
		ExpressionAnimationController* controller = 0;
		bool gpu = false;
		unsigned int count = ReadWord(reader);
		PartArray parts;
		parts.Allocate(count);
		math::AABB box;
		while (reader->HasChunk())
		{
			unsigned int id = reader->BeginChunk();
			switch (id)
			{
			case 0x10020:
			{
				groupLoader->SetIndex(index);
				DrawablePart part(0, 0);
				groupLoader->MakePrimitive(&part, reader, inventory, true, gpu);
				PushBack(parts, part);
				break;
			}
			case 0x10002:
			{
				int dead = 1;
				break;
			}
			case 0x10003:
				reader->Read(&box.min, 3, 4, 1);
				reader->Read(&box.max, 3, 4, 1);
				break;
			case 0x10004:
			{
				reader->Read(&sphere.centre, 3, 4, 1);
				float radius;
				reader->Read(&radius, 1, 4, 1);
				sphere.radius = radius;
				break;
			}
			case 0x1002B:
			{
				int value;
				reader->Read(&value, 1, 4, 1);
				gpu = value > 0;
				break;
			}
			case 0x122000:
			{
				int first;
				reader->Read(&first, 1, 4, 1);
				int second;
				reader->Read(&second, 1, 4, 1);
				break;
			}
			case 0x121305:
			{
				VertexAnimKeyFrameListReader groupReader;
				core::RefAssign(group, groupReader.Read(reader, inventory));
				break;
			}
			case 0x121201:
			{
				FrameControllerLoader* loader = dynamic_cast<FrameControllerLoader*>(content::gLoadManager->GetLoader(0x121201));
				loader->AddRef();
				FrameController* loaded = 0;
				content::ObjectName controllerName;
				loader->LoadObject((core::IRefCount**)&loaded, &controllerName, reader, inventory);
				FrameController* newController = loaded;
				if (newController != 0)
				{
					if (dynamic_cast<ExpressionAnimationController*>(newController) != 0)
					{
						controller = (ExpressionAnimationController*)newController;
					}
					else
					{
						core::SafeRelease(newController);
					}
				}
				loader->Release();
				break;
			}
			default:
				break;
			}
			reader->EndChunk();
		}
		if (group != 0)
		{
			int i = 0;
			int partCount = parts.end - parts.begin;
			for (; i < partCount; i++)
			{
				VertexAnimKeyFrameList* list = new VertexAnimKeyFrameList(group, i);
				list->AddRef();
				Primitive* primitive = parts[i].primitive;
				Skin* skin = dynamic_cast<Skin*>(primitive);
				PrimitiveState* state = parts[i].state;
				SkinState* skinState = dynamic_cast<SkinState*>(state);
				if (list->GetCount() > 0 && skin != 0 && skinState != 0)
				{
					skinState->SetExpressionState(list);
				}
				core::SafeRelease(list);
			}
		}
		Drawable* drawable = new Drawable(text, parts, true);
		drawable->AddRef();
		if (pose != 0)
		{
			drawable->SetPose(pose);
		}
		if (controller != 0)
		{
			int partCount = parts.end - parts.begin;
			for (int i = 0; i < partCount; i++)
			{
				if (parts[i].primitive != 0 && parts[i].primitive->type == 4)
				{
					static_cast<SkinState*>(parts[i].state)->SetController2(controller);
				}
			}
		}
		core::SafeRelease(controller);
		core::SafeRelease(group);
		WrappedDrawableHelper* helper = context->GetWrappedDrawableHelper();
		*object = helper->Wrap(drawable);
		(*object)->AddRef();
		drawable->Release();
		*name = content::ObjectName(text, 1);
	}
}
