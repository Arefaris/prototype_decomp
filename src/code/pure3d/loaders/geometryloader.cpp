// pure3d::GeometryLoader: see the header. The file name is a guess.
#include <new>

#include "code/pure3d/loaders/geometryloader.h"

#include "code/container/arraydynamicallocatornew.h"
#include "code/pure3d/context.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/loaders/drawableloaders.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10B9C3E0
	void GeometryLoader::LoadObject(core::IRefCount** object, content::ObjectName* name,
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
		math::Sphere sphere;
		sphere.centre.Set(0.0f, 0.0f, 0.0f);
		OldVertexAnimKeyFrameList* group = 0;
		VertexAnimController* vertexController = 0;
		VertexRegionAnimController* regionController = 0;
		unsigned int count = ReadWord(reader);
		PartArray parts;
		parts.Create(count);
		bool flagA = true;
		bool flagB = true;
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
				groupLoader->MakePrimitive(&part, reader, inventory, false, false);
				PushBack(parts, part);
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
			case 0x10017:
			{
				int value;
				reader->Read(&value, 1, 4, 1);
				flagA = value != 0;
				break;
			}
			case 0x10022:
			{
				int value;
				reader->Read(&value, 1, 4, 1);
				flagB = value != 0;
				break;
			}
			case 0x122000:
			{
				int unused;
				reader->Read(&unused, 1, 4, 1);
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
					if (dynamic_cast<VertexRegionAnimController*>(newController) != 0)
					{
						regionController = (VertexRegionAnimController*)newController;
					}
					else if (dynamic_cast<VertexAnimController*>(newController) != 0)
					{
						vertexController = (VertexAnimController*)newController;
					}
					else
					{
						core::SafeRelease(newController);
					}
				}
				loader->Release();
				break;
			}
			}
			reader->EndChunk();
		}
		{
			int partCount = parts.end - parts.begin;
			for (int i = 0; i < partCount; i++)
			{
				Primitive* primitive = parts[i].primitive;
				Mesh* mesh = dynamic_cast<Mesh*>(primitive);
				mesh->SetFlag174(flagA);
				mesh->SetFlag175(flagB);
			}
		}
		if ((vertexController != 0 || regionController != 0) && group != 0)
		{
			int i = 0;
			int partCount = parts.end - parts.begin;
			for (; i < partCount; i++)
			{
				VertexAnimKeyFrameList* list = new VertexAnimKeyFrameList(group, i);
				list->AddRef();
				Primitive* primitive = parts[i].primitive;
				Mesh* mesh = dynamic_cast<Mesh*>(primitive);
				PrimitiveState* state = parts[i].state;
				MeshState* meshState = dynamic_cast<MeshState*>(state);
				if (list->GetCount() > 0 && mesh != 0)
				{
					if (meshState == 0)
					{
						meshState = new MeshState(mesh, 0, 0);
						parts[i].SetState(meshState);
					}
					if (regionController != 0)
					{
						VertexRegionAnimController* clone = regionController->Clone();
						clone->SetKeyFrames(list);
						clone->SetMeshState(meshState);
						meshState->SetController3(clone);
					}
					if (vertexController != 0)
					{
						VertexAnimController* clone = vertexController->Clone();
						clone->SetKeyFrames(list);
						clone->SetMeshState(meshState);
						meshState->SetController2(clone);
					}
				}
				core::SafeRelease(list);
			}
		}
		core::SafeRelease(vertexController);
		core::SafeRelease(regionController);
		core::SafeRelease(group);
		Drawable* drawable = new Drawable(text, parts, true);
		drawable->AddRef();
		WrappedDrawableHelper* helper = context->GetWrappedDrawableHelper();
		*object = helper->Wrap(drawable);
		(*object)->AddRef();
		drawable->Release();
		*name = content::ObjectName(text, 1);
	}
}
