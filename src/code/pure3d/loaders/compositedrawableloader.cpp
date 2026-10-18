// pure3d::CompositeDrawableLoader: see the header. The file name is a guess.
#include <new>

#include "code/pure3d/loaders/compositedrawableloader.h"

#include "code/container/arraydynamicallocatornew.h"
#include "code/core/heap.h"
#include "code/core/refptr.h"
#include "code/core/strings.h"
#include "code/pure3d/context.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/loaders/drawableloaders.h"

namespace pure3d
{
	// 0x10E55134: the joint index stored for a part whose primitive is of type 4
	extern const unsigned short gNoJoint;

	// FUNCTION: ENGINE 0x10B91410
	// EQUIVALENT: the same calls, arguments, branches and memory accesses in the same order (31.6 %); the engine keeps
	// the inventory in ebp, a zero in ebx and the heap index in memory through the chunk loop, this compiler picks other
	// registers, orders the frame's variables differently (the same frame size), lays the controller case out before
	// the end of the chunk loop and releases the controller loader once instead of in each branch
	void CompositeDrawableLoader::LoadObject(core::IRefCount** object, content::ObjectName* name,
		content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		ReadWord(reader);
		char text[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(text, length, 1, 1);
			text[length] = 0;
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
		unsigned int count = ReadWord(reader);
		int heap = core::GetCurrentHeap();
		core::SetCurrentHeap(1);
		SegmentArray segments;
		segments.Create(count);
		PartArray parts;
		parts.Create(256);
		JointArray joints;
		joints.Create(256);
		core::SetCurrentHeap(heap);
		FrameController* controller = 0;
		FrameController* visibility = 0;
		VertexOffsetExpressionMixer* subMixer = 0;
		VertexOffsetExpressionMixer* chunkMixer = 0;
		while (reader->HasChunk())
		{
			unsigned int id = reader->BeginChunk();
			switch (id)
			{
			case 0x123003:
			{
				ReadWord(reader);
				char mixerName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(mixerName, length, 1, 1);
					mixerName[length] = 0;
				}
				if (mixerName[0] != 0)
				{
					content::LoadInventory::DynamicCaster<VertexOffsetExpressionMixer> caster;
					chunkMixer = (VertexOffsetExpressionMixer*)inventory->FindObject(&caster,
						content::ObjectName(mixerName, 1), true);
					if (chunkMixer == 0)
					{
						char message[0x400];
						core::SNPrintf(message, 0x400, "", mixerName, text);
					}
				}
				break;
			}
			case 0x123001:
			{
				ReadWord(reader);
				ReadWord(reader);
				bool cloneStates = skeleton != 0;
				char partName[0x100];
				{
					unsigned char byte;
					reader->Read(&byte, 1, 1, 1);
					unsigned int length = byte;
					reader->Read(partName, length, 1, 1);
					partName[length] = 0;
				}
				ReadWord(reader);
				unsigned int jointValue = ReadWord(reader);
				char nameOverride[0x100];
				nameOverride[0] = 0;
				while (reader->HasChunk())
				{
					if (reader->BeginChunk() == 0x123002)
					{
						ReadWord(reader);
						unsigned char byte;
						reader->Read(&byte, 1, 1, 1);
						unsigned int length = byte;
						reader->Read(nameOverride, length, 1, 1);
						nameOverride[length] = 0;
					}
					reader->EndChunk();
				}
				WrappedDrawableHelper* helper = context->GetWrappedDrawableHelper();
				Drawable* sub = helper->FindDrawable(inventory, content::ObjectName(partName, 1));
				sub->SetFlag100Bit3(true);
				DrawableSegment segment;
				if (nameOverride[0] != 0)
				{
					segment.name.SetText(nameOverride);
				}
				else
				{
					segment.name = sub->mName;
				}
				segment.firstPart = parts.end - parts.begin;
				segment.partCount = sub->parts.end - sub->parts.begin;
				if (segments.end < segments.capacity)
				{
					DrawableSegment* item = segments.end++;
					if (item != 0)
					{
						new (item) DrawableSegment(segment);
					}
				}
					int partCount = sub->parts.end - sub->parts.begin;
					for (int i = 0; i < partCount; i++)
				{
					PartRef primitiveRef(sub, i);
					Primitive* primitive = primitiveRef->primitive;
					PartRef stateRef(sub, i);
					PrimitiveState* state = stateRef->state;
					if (cloneStates == true && state != 0)
					{
						state = state->Unknown3();
					}
					DrawablePart part(primitive, state);
					PushBack(parts, part);
					if (primitive->type == 4)
					{
						if (joints.end < joints.capacity)
						{
							unsigned short* item = joints.end++;
							if (item != 0)
							{
								*item = gNoJoint;
							}
						}
					}
					else
					{
						if (joints.end < joints.capacity)
						{
							unsigned short* item = joints.end++;
							if (item != 0)
							{
								*item = (unsigned short)jointValue;
							}
						}
					}
				}
				if (sub->GetExpressionMixer() != 0 && subMixer == 0)
				{
					subMixer = sub->GetExpressionMixer();
				}
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
					if (dynamic_cast<PoseAnimationController*>(newController) != 0)
					{
						controller = newController;
					}
					else if (dynamic_cast<CompDrawVisibilityAnimationController*>(newController) != 0)
					{
						visibility = newController;
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
		Drawable* drawable = new Drawable(text, parts, true);
		drawable->AddRef();
		if (skeleton != 0 && sCreatePoses)
		{
			drawable->SetPose(skeleton->CreatePose(3));
		}
		else
		{
			drawable->SetSkeleton(skeleton);
		}
		drawable->SetUnknown78(controller);
		drawable->SetSegments(segments);
		drawable->SetUnknown7C(visibility);
		if (chunkMixer != 0)
		{
			drawable->SetExpressionSource(chunkMixer);
		}
		else if (subMixer != 0)
		{
			drawable->SetExpressionSource(subMixer);
		}
		RefCounted::Release(controller);
		RefCounted::Release(subMixer);
		for (unsigned int i = 0; i < (unsigned int)(joints.end - joints.begin); i++)
		{
			drawable->SetPartJoint(i, joints.begin[i]);
		}
		WrappedDrawableHelper* helper = context->GetWrappedDrawableHelper();
		*object = helper->Wrap(drawable);
		(*object)->AddRef();
		drawable->Release();
		*name = content::ObjectName(text, 1);
		if (joints.begin != 0)
		{
			operator delete[](joints.begin);
		}
		container::Destroy(parts.begin, parts.end);
		parts.end = parts.begin;
		if (parts.begin != 0)
		{
			operator delete[](parts.begin);
		}
		segments.end = segments.begin;
		if (segments.begin != 0)
		{
			operator delete[](segments.begin);
		}
	}
}
