// pure3d::PrimGroupLoader: the description of a mesh's primitive groups (see primgrouploader.h). The file name and
// the directory are guesses (no assert path survives in the binary).
#include "code/pure3d/geometry/primgrouploader.h"
#include "code/core/strings.h"
#include "code/math/aabb.h"
#include "code/math/sphere.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/dxindexbuffer.h"
#include "code/pure3d/pddi/dx9/dxvertexbuffer.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/vertexstream.h"

namespace pure3d
{
	// The vertex semantic names the streams are found by (globals of the vertex format unit; names guessed):
	// "position", "normal", "binormal", "tangent", "colour0", "blendoffset", "blendnormal", "hdrColour"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F180;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1B8;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1BC;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1DC;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F130;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F340;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F31C;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F0D0;
	// "weights" and "indices", the bone streams of a skin
	extern core::Name<core::CaseInsensitiveKey32> gName1127F16C;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F0B4;

	// The controllers a mesh chunk lists (0x10B92620 fills its two pointers with new[]; names guessed)
	class FrameControllerList
	{
	public:
		FrameControllerList() : begin(0), end(0)
		{
		}
		~FrameControllerList()
		{
			if (begin != 0)
			{
				delete[] begin;
			}
		}
		unsigned int Size() const
		{
			return end - begin;
		}
		FrameController*& operator[](int index)
		{
			return begin[index];
		}

		FrameController** begin;
		FrameController** end;
		// A third word the reader does not set (its capacity, or an allocator)
		int unknown8;
	};

	// 0x10B92620 (the controller loader's unit): reads the 0x121204 chunk's controllers into the list
	void ReadControllers(FrameControllerList* controllers, content::ChunkReader* reader,
		content::LoadInventory* inventory);

	// The helpers of this unit the builders call (not reconstructed; names unknown): 0x10B8C1D0 marks the packed
	// streams of a description, 0x10B8C5D0 splits a description between the two buffers by the flags, 0x10B8CB70 /
	// 0x10B8DDE0 fill the locked buffers when the group carries no vertex chunks (with and without the prim group's
	// third flag)
	void Unknown10B8C1D0(ShaderParameters* description);
	void Unknown10B8C5D0(int flags, ShaderParameters* description, ShaderParameters* stateParameters,
		ShaderParameters* meshParameters);
	void Unknown10B8CB70(dxVertexDeclaration* lock, dxVertexDeclaration* stateLock, dxIndexBufferState* indexLock,
		int vertexCount, int indexCount);
	void Unknown10B8DDE0(dxVertexDeclaration* lock, dxVertexDeclaration* stateLock, dxIndexBufferState* indexLock,
		int vertexCount, int indexCount);

	// Three halves as the four a packed stream holds (through a vector and a copy of it)
	__forceinline Half4 RepackHalves(Half3 value)
	{
		math::Vector vector = value.ToVector();
		math::Vector copy = vector;
		Half4 packed;
		packed.Set(copy);
		return packed;
	}

	// The shader of that name in the inventory, none when there is none (name guess)
	inline Shader* FindShader(content::LoadInventory* inventory, const char* name)
	{
		content::LoadInventory::DynamicCaster<Shader> caster;
		return (Shader*)inventory->FindObject(&caster, content::ObjectName(name, 1), true);
	}

	// FUNCTION: ENGINE 0x10B8F1C0
	bool PrimGroupLoader::ReadGroup(content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		if (reader->GetChunkId() != 0x10020)
		{
			return false;
		}
		ReadWord(reader);
		char shaderName[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(shaderName, length, 1, 1);
			shaderName[length] = 0;
		}
		core::SafeRelease(shader);
		shader = FindShader(inventory, shaderName);
		// A group whose shader is missing draws with the error shader
		Shader* found = shader;
		if (found == 0)
		{
			found = new Shader("error");
			shader = found;
		}
		found->AddRef();
		unknownC = ReadWord(reader);
		unknown1C = unknown18 & ReadWord(reader);
		unknown20 = ReadWord(reader);
		unknown24 = ReadWord(reader);
		unknown28 = ReadWord(reader);
		unknown10 = ReadWord(reader) != 0;
		unknown11 = ReadWord(reader) != 0;
		unknown12 = ReadWord(reader) != 0;
		unknown14 = ReadWord(reader);
		unknown1C |= 0x2000;
		return true;
	}

	// FUNCTION: ENGINE 0x10B8BD90
	void PrimGroupLoader::CreateGpuSkin(DrawablePart* part, GpuSkin** skin, GpuSkinState** state,
		VertexBufferDescription* description, IndexBufferDescription* indices, dxVertexDeclaration* lock,
		dxIndexBufferState* indexLock)
	{
		*skin = new GpuSkin(description, indices, unknownC);
		part->SetPrimitive(*skin);
		*state = new GpuSkinState(*skin);
		part->SetState(*state);
		(*skin)->Unknown4(shader);
		(*skin)->LockBuffer(lock);
		if ((unsigned int)unknown24 > 0)
		{
			(*skin)->LockIndices(indexLock);
		}
	}

	// FUNCTION: ENGINE 0x10B8C270
	void PrimGroupLoader::CreateMesh(DrawablePart* part, Mesh** mesh, MeshState** state,
		VertexBufferDescription* description, ShaderParameters* stateParameters, ShaderParameters* meshParameters,
		IndexBufferDescription* indices, dxVertexDeclaration* stateLock, dxVertexDeclaration* lock,
		dxIndexBufferState* indexLock)
	{
		if (unknown14 != 0)
		{
			// The streams the group animates go into the state's buffers, with the list of offsets they get
			VertexOffsetList* offsets = new VertexOffsetList(unknown20, unknown14);
			offsets->Prepare();
			*mesh = new Mesh(meshParameters, stateParameters, indices, unknownC);
			part->SetPrimitive(*mesh);
			stateParameters->unknown8 |= 1;
			*state = new MeshState(*mesh, stateParameters, offsets);
			part->SetState(*state);
		}
		else
		{
			description->unknown8 |= 1;
			*mesh = new Mesh(description, 0, indices, unknownC);
			part->SetPrimitive(*mesh);
		}
		(*mesh)->Unknown4(shader);
		if ((unsigned int)unknown24 > 0)
		{
			(*mesh)->LockIndices(indexLock);
		}
		(*mesh)->LockVertices(lock);
		if (unknown14 != 0)
		{
			(*mesh)->DescribeStateVertices(stateLock);
		}
		else
		{
			*stateLock = *lock;
		}
	}

	// FUNCTION: ENGINE 0x10B8C820
	void PrimGroupLoader::CreateSkin(DrawablePart* part, Skin** skin, SkinState** state, VertexOffsetList* offsets,
		VertexBufferDescription* sourceStreams, VertexBufferDescription* bufferStreams,
		VertexBufferDescription* stateStreams, IndexBufferDescription* indices, dxVertexDeclaration* sourceLock,
		dxVertexDeclaration* bufferLock, dxVertexDeclaration* unknownLock, dxIndexBufferState* indexLock)
	{
		if (unknown14 != 0)
		{
			// The buffer's streams the group animates go into the state
			ShaderParameters stateParameters;
			ShaderParameters meshParameters;
			Unknown10B8C5D0(unknown14, bufferStreams, &stateParameters, &meshParameters);
			meshParameters.unknownC = bufferStreams->unknownC;
			stateParameters.unknownC = bufferStreams->unknownC;
			stateParameters.unknown8 = 1;
			meshParameters.unknown8 = 1;
			if (stateParameters.unknown4 > 0)
			{
				*skin = new Skin(sourceStreams, &meshParameters, &stateParameters, indices, unknownC);
				part->SetPrimitive(*skin);
				stateParameters.unknown8 |= 1;
				*state = new SkinState(*skin, stateStreams, sourceStreams, &stateParameters, offsets, gSkinStateFlag);
				part->SetState(*state);
			}
			else
			{
				*skin = new Skin(sourceStreams, bufferStreams, 0, indices, unknownC);
				part->SetPrimitive(*skin);
				*state = new SkinState(*skin, stateStreams, sourceStreams, 0, offsets, gSkinStateFlag);
				part->SetState(*state);
			}
		}
		else
		{
			*skin = new Skin(sourceStreams, bufferStreams, 0, indices, unknownC);
			part->SetPrimitive(*skin);
			*state = new SkinState(*skin, stateStreams, sourceStreams, 0, offsets, gSkinStateFlag);
			part->SetState(*state);
		}
		(*skin)->Unknown4(shader);
		(*skin)->DescribeSource(sourceLock);
		(*skin)->LockBuffer(bufferLock);
		(*skin)->DescribeUnknown264(unknownLock);
		if ((unsigned int)unknown24 > 0)
		{
			(*skin)->LockIndices(indexLock);
		}
	}

	// FUNCTION: ENGINE 0x10B8DFF0
	void PrimGroupLoader::BuildMesh(void* object, content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		unsigned int format = unknown1C;
		unsigned int colourCount;
		if ((format & 0x20) != 0)
		{
			colourCount = 1;
		}
		else if ((format & 0x4000) != 0)
		{
			colourCount = format >> 15 & 7;
		}
		else
		{
			colourCount = 0;
		}
		unsigned int texCount = format & 0xF;
		Mesh* mesh = 0;
		MeshState* state = 0;
		IndexBufferDescription indexDescription(unknown24, 3, 8);
		VertexBufferDescription description(unknown20, unknown1C, 0, unknown12);
		ShaderParameters stateParameters;
		ShaderParameters meshParameters;
		Unknown10B8C1D0(&description);
		if (unknown14 != 0)
		{
			Unknown10B8C5D0(unknown14, &description, &stateParameters, &meshParameters);
			meshParameters.unknownC = description.unknownC;
			stateParameters.unknownC = description.unknownC;
			stateParameters.unknown8 = 1;
			meshParameters.unknown8 = 1;
			indexDescription.usage = 1;
			if (shader != 0 && !shader->flags.Test(3))
			{
				meshParameters.unknown8 = 0x21;
			}
		}
		else
		{
			if (shader != 0 && !shader->flags.Test(3))
			{
				description.unknown8 |= 0x20;
			}
			indexDescription.usage = 1;
		}
		dxVertexDeclaration stateLock;
		dxVertexDeclaration lock;
		dxIndexBufferState indexLock;
		stateLock.unknown110 = 0;
		lock.unknown110 = 0;
		bool filled = false;
		bool first = true;
		while (reader->HasChunk())
		{
			unsigned int id = reader->BeginChunk();
			if (first)
			{
				first = false;
				if (id == 0x10014)
				{
					filled = true;
					do
					{
						ReadWord(reader);
						unsigned int kind = ReadWord(reader);
						if (kind == 1)
						{
							ReadStreams(&meshParameters, reader);
						}
						else if (kind == 2)
						{
							ReadStreams(unknown14 != 0 ? &stateParameters : &description, reader);
						}
						reader->EndChunk();
						if (!reader->HasChunk())
						{
							break;
						}
						id = reader->BeginChunk();
					}
					while (id == 0x10014);
				}
				CreateMesh((DrawablePart*)object, &mesh, &state, &description, &stateParameters, &meshParameters,
					&indexDescription, &stateLock, &lock, &indexLock);
			}
			switch (id)
			{
			case 0x10012:
			{
				reader->ReadUnsigned();
				reader->ReadUnsigned();
				unsigned int count = reader->ReadUnsigned();
				pddi->Unknown24(0x102)->ReadVertices(reader, &lock, count);
				filled = true;
				break;
			}
			case 0x10013:
			{
				reader->ReadUnsigned();
				reader->ReadUnsigned();
				unsigned int count = reader->ReadUnsigned();
				pddi->Unknown24(0x102)->ReadIndices(reader, &indexLock, count);
				break;
			}
			case 0x10005:
				if ((unknown1C & 0x2000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector4> stream(&lock, gName1127F180);
					if (!stream.enabled)
					{
						stream.Init(&stateLock, gName1127F180);
					}
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10031:
				if ((unknown1C & 0x2000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<Half4> stream(&lock, gName1127F180);
					for (unsigned int i = 0; i < count; i++)
					{
						Half3 value;
						reader->Read(&value, 3, 2, 1);
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.Next();
					}
				}
				break;
			case 0x10006:
				if ((unknown1C & 0x10) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&lock, gName1127F1B8);
					if (!stream.enabled)
					{
						stream.Init(&stateLock, gName1127F1B8);
					}
					for (unsigned int i = 0; i < count; i++)
					{
						math::Vector value;
						reader->Read(&value, 3, 4, 1);
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.Next();
					}
				}
				break;
			case 0x10032:
				if ((unknown1C & 0x10) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<Half4> stream(&lock, gName1127F1B8);
					for (unsigned int i = 0; i < count; i++)
					{
						Half3 value;
						reader->Read(&value, 3, 2, 1);
						*stream.current = RepackHalves(value);
						stream.Next();
					}
				}
				break;
			case 0x10016:
				if ((unknown1C & 0x800) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&lock, gName1127F1BC);
					if (!stream.enabled)
					{
						stream.Init(&stateLock, gName1127F1BC);
					}
					for (unsigned int i = 0; i < count; i++)
					{
						math::Vector value;
						reader->Read(&value, 3, 4, 1);
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.Next();
					}
				}
				break;
			case 0x10033:
				if ((unknown1C & 0x800) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<Half4> stream(&lock, gName1127F1BC);
					for (unsigned int i = 0; i < count; i++)
					{
						Half3 value;
						reader->Read(&value, 3, 2, 1);
						*stream.current = RepackHalves(value);
						stream.Next();
					}
				}
				break;
			case 0x10015:
				if ((unknown1C & 0x1000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector4> stream(&lock, gName1127F1DC);
					if (!stream.enabled)
					{
						stream.Init(&stateLock, gName1127F1DC);
					}
					for (unsigned int i = 0; i < count; i++)
					{
						math::Vector4 value;
						reader->Read(&value, 3, 4, 1);
						value.w = 1.0f;
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.current->w = value.w;
						stream.Next();
					}
				}
				break;
			case 0x10028:
				if ((unknown1C & 0x1000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector4> stream(&lock, gName1127F1DC);
					if (!stream.enabled)
					{
						stream.Init(&stateLock, gName1127F1DC);
					}
					for (unsigned int i = 0; i < count; i++)
					{
						math::Vector4 value;
						reader->Read(&value, 4, 4, 1);
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.current->w = value.w;
						stream.Next();
					}
				}
				break;
			case 0x10034:
				if ((unknown1C & 0x1000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<Half4> stream(&lock, gName1127F1DC);
					for (unsigned int i = 0; i < count; i++)
					{
						Half4 value;
						reader->Read(&value, 4, 2, 1);
						*stream.current = value;
						stream.Next();
					}
				}
				break;
			case 0x10008:
				if ((unknown1C & 0x20) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<unsigned int> stream(&lock, gName1127F130);
					if (!stream.enabled)
					{
						stream.Init(&stateLock, gName1127F130);
					}
					for (unsigned int i = 0; i < count; i++)
					{
						unsigned int colour;
						reader->Read(&colour, 1, 4, 1);
						*stream.current = colour >> 16 & 0xff | (colour & 0xff) << 16 | colour & 0xff00ff00;
						stream.Next();
					}
				}
				break;
			case 0x1001C:
				if ((unknown1C & 0x4000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					unsigned int index = reader->ReadUnsigned();
					if (index < colourCount)
					{
						char name[0x40];
						core::SNPrintf(name, 0x40, "colour%d", index);
						VertexStream<unsigned int> stream(&lock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						if (!stream.enabled)
						{
							stream.Init(&stateLock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						}
						for (unsigned int i = 0; i < count; i++)
						{
							unsigned int colour;
							reader->Read(&colour, 1, 4, 1);
							*stream.current = SwapColour(colour);
							stream.Next();
						}
					}
				}
				break;
			case 0x10038:
				if ((unknown1C & 0x80000000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&lock, gName1127F0D0);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10007:
				if ((unknown1C & 0xF) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					unsigned int index = reader->ReadUnsigned();
					if (index < texCount)
					{
						char name[0x40];
						core::SNPrintf(name, 0x40, "tex%d", index);
						VertexStream<unsigned int> stream(&lock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						if (!stream.enabled)
						{
							stream.Init(&stateLock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						}
						for (unsigned int i = 0; i < count; i++)
						{
							reader->ReadData(stream.current, 2, 4);
							stream.Next();
						}
					}
				}
				break;
			case 0x10035:
				if ((unknown1C & 0xF) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					unsigned int index = reader->ReadUnsigned();
					if (index < texCount)
					{
						char name[0x40];
						core::SNPrintf(name, 0x40, "tex%d", index);
						VertexStream<Half2> stream(&lock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						for (unsigned int i = 0; i < count; i++)
						{
							Half2 value;
							reader->Read(&value, 2, 2, 1);
							stream.current->u = value.u;
							stream.current->v = value.v;
							stream.Next();
						}
					}
				}
				break;
			case 0x1000A:
			{
				unsigned int count = reader->ReadUnsigned();
				unsigned short* indices = (unsigned short*)indexLock.unknown10;
				for (unsigned int i = 0; i < count; i++)
				{
					indices[i] = (unsigned short)ReadWord(reader);
				}
				break;
			}
			case 0x10030:
				if ((unknown1C & 0x20000000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&lock, gName1127F340);
					if (!stream.enabled)
					{
						stream.Init(&stateLock, gName1127F340);
					}
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10037:
				if ((unknown1C & 0x40000000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&lock, gName1127F31C);
					if (!stream.enabled)
					{
						stream.Init(&stateLock, gName1127F31C);
					}
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10036:
				if ((unknown1C & 0x20000000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<Half3> stream(&lock, gName1127F340);
					for (unsigned int i = 0; i < count; i++)
					{
						Half3 value;
						reader->Read(&value, 3, 2, 1);
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.Next();
					}
				}
				break;
			case 0x10003:
			{
				math::AABB box;
				reader->ReadVector(&box.min);
				reader->ReadVector(&box.max);
				mesh->SetBoundingBox(box);
				break;
			}
			case 0x10004:
			{
				math::Sphere sphere;
				sphere.centre.Set(0.0f, 0.0f, 0.0f);
				reader->ReadVector(&sphere.centre);
				sphere.radius = reader->ReadFloat();
				mesh->SetBoundingSphere(sphere);
				break;
			}
			case 0x121204:
			{
				FrameControllerList controllers;
				ReadControllers(&controllers, reader, inventory);
				if (controllers.Size() > 0)
				{
					ShaderAnimationController* controller = dynamic_cast<ShaderAnimationController*>(controllers[0]);
					if (controller != 0)
					{
						if (state == 0)
						{
							state = new MeshState(mesh, 0, 0);
							((DrawablePart*)object)->SetState(state);
						}
						state->SetController1(controller);
					}
					for (unsigned int i = 0; i < controllers.Size(); i++)
					{
						core::SafeRelease(controllers[i]);
					}
				}
				break;
			}
			}
			reader->EndChunk();
		}
		if (!filled)
		{
			if (unknown12)
			{
				Unknown10B8CB70(&lock, &stateLock, &indexLock, unknown20, unknown24);
			}
			else
			{
				Unknown10B8DDE0(&lock, &stateLock, &indexLock, unknown20, unknown24);
			}
		}
		if ((unsigned int)unknown24 > 0)
		{
			mesh->UnlockIndices();
		}
		mesh->UnlockVertices();
		if (mesh->HasUnknown140())
		{
			mesh->Unknown107074B0();
		}
	}

	// FUNCTION: ENGINE 0x10B8F400
	void PrimGroupLoader::BuildSkin(void* object, content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		unsigned int format = unknown1C;
		unsigned int colourCount;
		if ((format & 0x20) != 0)
		{
			colourCount = 1;
		}
		else if ((format & 0x4000) != 0)
		{
			colourCount = format >> 15 & 7;
		}
		else
		{
			colourCount = 0;
		}
		unsigned int texCount = format & 0xF;
		// A skin has no binormals
		unknown1C = format & ~0x800;
		Skin* skin = 0;
		SkinState* state = 0;
		VertexOffsetList* offsets = 0;
		if (unknown14 != 0)
		{
			offsets = new VertexOffsetList(unknown20, unknown14);
			offsets->Prepare();
		}
		// The streams split three ways: those the skinning reads (the source), those the buffer keeps as they are
		// and those the state's skinned buffer holds
		unsigned int stateBits = unknown1C & 0x20003010;
		unsigned int bufferBits = unknown1C & 0xDFFFC66F;
		unsigned int sourceBits = unknown1C & 0x20003190;
		VertexBufferDescription sourceStreams(unknown20, sourceBits, 0x11, false);
		VertexBufferDescription bufferStreams(unknown20, bufferBits, 1, false);
		VertexBufferDescription stateStreams(unknown20, stateBits, 0x13, false);
		IndexBufferDescription indexDescription(unknown24, 3, 1);
		dxVertexDeclaration sourceLock;
		dxVertexDeclaration bufferLock;
		dxVertexDeclaration unknownLock;
		dxIndexBufferState indexLock;
		MatrixPaletteList* palettes = new MatrixPaletteList;
		bool first = true;
		while (reader->HasChunk())
		{
			unsigned int id = reader->BeginChunk();
			if (first)
			{
				first = false;
				while (id == 0x10014)
				{
					ReadWord(reader);
					unsigned int kind = ReadWord(reader);
					if (kind == 1)
					{
						ReadStreams(&bufferStreams, reader);
					}
					else if (kind == 2)
					{
						ReadStreams(&sourceStreams, reader);
					}
					reader->EndChunk();
					if (!reader->HasChunk())
					{
						break;
					}
					id = reader->BeginChunk();
				}
				CreateSkin((DrawablePart*)object, &skin, &state, offsets, &sourceStreams, &bufferStreams, &stateStreams,
					&indexDescription, &sourceLock, &bufferLock, &unknownLock, &indexLock);
			}
			switch (id)
			{
			case 0x10012:
			{
				reader->ReadUnsigned();
				unsigned int kind = reader->ReadUnsigned();
				unsigned int count = reader->ReadUnsigned();
				if (kind == 1)
				{
					pddi->Unknown24(0x102)->ReadVertices(reader, &bufferLock, count);
				}
				else if (kind == 2)
				{
					void* data;
					int size;
					skin->GetDrawData(&data, &size);
					reader->ReadData(data, count, 1);
				}
				break;
			}
			case 0x10013:
			{
				reader->ReadUnsigned();
				reader->ReadUnsigned();
				unsigned int count = reader->ReadUnsigned();
				pddi->Unknown24(0x102)->ReadIndices(reader, &indexLock, count);
				break;
			}
			case 0x10005:
				if ((unknown1C & 0x2000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&sourceLock, gName1127F180);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10006:
				if ((unknown1C & 0x10) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&sourceLock, gName1127F1B8);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10016:
				if ((unknown1C & 0x800) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&sourceLock, gName1127F1BC);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10015:
				if ((unknown1C & 0x1000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector4> stream(&sourceLock, gName1127F1DC);
					for (unsigned int i = 0; i < count; i++)
					{
						math::Vector4 value;
						reader->Read(&value, 3, 4, 1);
						value.w = 1.0f;
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.current->w = value.w;
						stream.Next();
					}
				}
				break;
			case 0x10028:
				if ((unknown1C & 0x1000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector4> stream(&sourceLock, gName1127F1DC);
					for (unsigned int i = 0; i < count; i++)
					{
						math::Vector4 value;
						reader->Read(&value, 4, 4, 1);
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.current->w = value.w;
						stream.Next();
					}
				}
				break;
			case 0x10008:
				if ((unknown1C & 0x20) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<unsigned int> stream(&bufferLock, gName1127F130);
					if (!stream.enabled)
					{
						stream.Init(&unknownLock, gName1127F130);
					}
					for (unsigned int i = 0; i < count; i++)
					{
						unsigned int colour;
						reader->Read(&colour, 1, 4, 1);
						*stream.current = colour >> 16 & 0xff | (colour & 0xff) << 16 | colour & 0xff00ff00;
						stream.Next();
					}
				}
				break;
			case 0x1001C:
				if ((unknown1C & 0x4000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					unsigned int index = reader->ReadUnsigned();
					if (index < colourCount)
					{
						char name[0x40];
						core::SNPrintf(name, 0x40, "colour%d", index);
						VertexStream<unsigned int> stream(&bufferLock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						if (!stream.enabled)
						{
							stream.Init(&unknownLock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						}
						for (unsigned int i = 0; i < count; i++)
						{
							unsigned int colour;
							reader->Read(&colour, 1, 4, 1);
							*stream.current = SwapColour(colour);
							stream.Next();
						}
					}
				}
				break;
			case 0x10007:
				if ((unknown1C & 0xF) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					unsigned int index = reader->ReadUnsigned();
					if (index < texCount)
					{
						char name[0x40];
						core::SNPrintf(name, 0x40, "tex%d", index);
						VertexStream<unsigned int> stream(&bufferLock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						for (unsigned int i = 0; i < count; i++)
						{
							reader->Read(stream.current, 2, 4, 1);
							stream.Next();
						}
					}
				}
				break;
			case 0x1000A:
			{
				unsigned int count = reader->ReadUnsigned();
				unsigned short* indices = (unsigned short*)indexLock.unknown10;
				for (unsigned int i = 0; i < count; i++)
				{
					indices[i] = (unsigned short)ReadWord(reader);
				}
				break;
			}
			case 0x1000C:
				if ((unknown1C & 0x100) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<float> stream(&sourceLock, gName1127F16C);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x1000B:
				if ((unknown1C & 0x80) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					// The bone indices come as one word a stream.current, the first index in its top byte
					unsigned int value = 0;
					VertexStream<unsigned char> stream(&sourceLock, gName1127F0B4);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(&value, 1, 4, 1);
						stream.current[0] = (unsigned char)(value >> 24);
						stream.current[1] = (unsigned char)(value >> 16);
						stream.current[2] = (unsigned char)(value >> 8);
						stream.current[3] = (unsigned char)value;
						stream.Next();
					}
				}
				break;
			case 0x1000D:
				if ((unknown1C & 0x80) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					MatrixPaletteList::Indices* indices = &palettes->indices;
					indices->Resize(count);
					for (unsigned int i = 0; i < count; i++)
					{
						indices->begin[i] = ReadWord(reader);
					}
				}
				break;
			case 0x10030:
				if ((unknown1C & 0x20000000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&sourceLock, gName1127F340);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10003:
			{
				math::AABB box;
				reader->ReadVector(&box.min);
				reader->ReadVector(&box.max);
				skin->SetBoundingBox(box);
				state->SetBoundingBox(box);
				break;
			}
			case 0x10004:
			{
				math::Vector4 centre;
				centre.x = 0.0f;
				centre.y = 0.0f;
				centre.z = 0.0f;
				reader->ReadVector((math::Vector*)&centre);
				centre.w = reader->ReadFloat();
				skin->SetCentre(centre);
				break;
			}
			case 0x121204:
			{
				FrameControllerList controllers;
				ReadControllers(&controllers, reader, inventory);
				if (controllers.Size() > 0)
				{
					ShaderAnimationController* controller = dynamic_cast<ShaderAnimationController*>(controllers[0]);
					if (controller != 0)
					{
						state->SetController1(controller);
					}
					for (unsigned int i = 0; i < controllers.Size(); i++)
					{
						core::SafeRelease(controllers[i]);
					}
				}
				break;
			}
			}
			reader->EndChunk();
		}
		skin->UnlockBuffer();
		skin->Unknown1071EFC0();
		if ((unsigned int)unknown24 > 0)
		{
			skin->UnlockIndices();
		}
		skin->Finish(palettes);
		palettes->Release();
		if (state != 0)
		{
			state->Unknown5();
		}
	}

	// FUNCTION: ENGINE 0x10B8FFE0
	void PrimGroupLoader::BuildGpuSkin(void* object, content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		unsigned int format = unknown1C;
		unsigned int colourCount;
		if ((format & 0x20) != 0)
		{
			colourCount = 1;
		}
		else if ((format & 0x4000) != 0)
		{
			colourCount = format >> 15 & 7;
		}
		else
		{
			colourCount = 0;
		}
		unsigned int texCount = format & 0xF;
		// A skin has no binormals
		unknown1C = format & ~0x800;
		GpuSkin* skin = 0;
		GpuSkinState* state = 0;
		VertexBufferDescription description(unknown20, unknown1C, 1, false);
		IndexBufferDescription indexDescription(unknown24, 3, 1);
		dxVertexDeclaration lock;
		dxIndexBufferState indexLock;
		bool first = true;
		while (reader->HasChunk())
		{
			unsigned int id = reader->BeginChunk();
			if (first)
			{
				first = false;
				while (id == 0x10014)
				{
					ReadWord(reader);
					unsigned int kind = ReadWord(reader);
					if (kind == 2)
					{
						ReadStreams(&description, reader);
					}
					reader->EndChunk();
					if (!reader->HasChunk())
					{
						break;
					}
					id = reader->BeginChunk();
				}
				CreateGpuSkin((DrawablePart*)object, &skin, &state, &description, &indexDescription, &lock, &indexLock);
			}
			switch (id)
			{
			case 0x10012:
			{
				reader->ReadUnsigned();
				reader->ReadUnsigned();
				unsigned int count = reader->ReadUnsigned();
				pddi->Unknown24(0x102)->ReadVertices(reader, &lock, count);
				break;
			}
			case 0x10013:
			{
				reader->ReadUnsigned();
				reader->ReadUnsigned();
				unsigned int count = reader->ReadUnsigned();
				pddi->Unknown24(0x102)->ReadIndices(reader, &indexLock, count);
				break;
			}
			case 0x10005:
				if ((unknown1C & 0x2000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&lock, gName1127F180);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10006:
				if ((unknown1C & 0x10) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&lock, gName1127F1B8);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10016:
				if ((unknown1C & 0x800) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&lock, gName1127F1BC);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10015:
				if ((unknown1C & 0x1000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector4> stream(&lock, gName1127F1DC);
					for (unsigned int i = 0; i < count; i++)
					{
						math::Vector4 value;
						reader->Read(&value, 3, 4, 1);
						value.w = 1.0f;
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.current->w = value.w;
						stream.Next();
					}
				}
				break;
			case 0x10028:
				if ((unknown1C & 0x1000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector4> stream(&lock, gName1127F1DC);
					for (unsigned int i = 0; i < count; i++)
					{
						math::Vector4 value;
						reader->Read(&value, 4, 4, 1);
						stream.current->x = value.x;
						stream.current->y = value.y;
						stream.current->z = value.z;
						stream.current->w = value.w;
						stream.Next();
					}
				}
				break;
			case 0x10008:
				if ((unknown1C & 0x20) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<unsigned int> stream(&lock, gName1127F130);
					for (unsigned int i = 0; i < count; i++)
					{
						unsigned int colour;
						reader->Read(&colour, 1, 4, 1);
						*stream.current = colour >> 16 & 0xff | (colour & 0xff) << 16 | colour & 0xff00ff00;
						stream.Next();
					}
				}
				break;
			case 0x1001C:
				if ((unknown1C & 0x4000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					unsigned int index = reader->ReadUnsigned();
					if (index < colourCount)
					{
						char name[0x40];
						core::SNPrintf(name, 0x40, "colour%d", index);
						VertexStream<unsigned int> stream(&lock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						for (unsigned int i = 0; i < count; i++)
						{
							unsigned int colour;
							reader->Read(&colour, 1, 4, 1);
							*stream.current = SwapColour(colour);
							stream.Next();
						}
					}
				}
				break;
			case 0x10007:
				if ((unknown1C & 0xF) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					unsigned int index = reader->ReadUnsigned();
					if (index < texCount)
					{
						char name[0x40];
						core::SNPrintf(name, 0x40, "tex%d", index);
						VertexStream<unsigned int> stream(&lock, core::Name<core::CaseInsensitiveKey32>(name, 1));
						for (unsigned int i = 0; i < count; i++)
						{
							reader->Read(stream.current, 2, 4, 1);
							stream.Next();
						}
					}
				}
				break;
			case 0x1000A:
			{
				unsigned int count = reader->ReadUnsigned();
				unsigned short* indices = (unsigned short*)indexLock.unknown10;
				for (unsigned int i = 0; i < count; i++)
				{
					indices[i] = (unsigned short)ReadWord(reader);
				}
				break;
			}
			case 0x1000C:
				if ((unknown1C & 0x100) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<float> stream(&lock, gName1127F16C);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x1000B:
				if ((unknown1C & 0x80) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					// The bone indices come as one word a stream.current, the first index in its top byte
					unsigned int value = 0;
					VertexStream<unsigned char> stream(&lock, gName1127F0B4);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(&value, 1, 4, 1);
						stream.current[0] = (unsigned char)(value >> 24);
						stream.current[1] = (unsigned char)(value >> 16);
						stream.current[2] = (unsigned char)(value >> 8);
						stream.current[3] = (unsigned char)value;
						stream.Next();
					}
				}
				break;
			case 0x1000D:
				if ((unknown1C & 0x80) != 0)
				{
					MatrixPaletteList* palettes = new MatrixPaletteList;
					unsigned int count = reader->ReadUnsigned();
					MatrixPaletteList::Indices* indices = &palettes->indices;
					indices->Resize(count);
					for (unsigned int i = 0; i < count; i++)
					{
						indices->begin[i] = ReadWord(reader);
					}
					skin->SetPalette(palettes);
				}
				break;
			case 0x10030:
				if ((unknown1C & 0x20000000) != 0)
				{
					unsigned int count = reader->ReadUnsigned();
					VertexStream<math::Vector> stream(&lock, gName1127F340);
					for (unsigned int i = 0; i < count; i++)
					{
						reader->Read(stream.current, 3, 4, 1);
						stream.Next();
					}
				}
				break;
			case 0x10003:
			{
				math::AABB box;
				reader->ReadVector(&box.min);
				reader->ReadVector(&box.max);
				skin->SetBoundingBox(box);
				state->SetBoundingBox(box);
				break;
			}
			case 0x10004:
			{
				math::Vector4 centre;
				centre.x = 0.0f;
				centre.y = 0.0f;
				centre.z = 0.0f;
				reader->ReadVector((math::Vector*)&centre);
				centre.w = reader->ReadFloat();
				skin->SetCentre(centre);
				break;
			}
			case 0x121204:
			{
				FrameControllerList controllers;
				ReadControllers(&controllers, reader, inventory);
				if (controllers.Size() > 0)
				{
					ShaderAnimationController* controller = dynamic_cast<ShaderAnimationController*>(controllers[0]);
					if (controller != 0)
					{
						state->SetShaderController(controller);
					}
					for (unsigned int i = 0; i < controllers.Size(); i++)
					{
						core::SafeRelease(controllers[i]);
					}
				}
				break;
			}
			}
			reader->EndChunk();
		}
		skin->UnlockBuffer();
		if ((unsigned int)unknown24 > 0)
		{
			skin->UnlockIndices();
		}
		if (state != 0)
		{
			state->Unknown5();
		}
	}

	// FUNCTION: ENGINE 0x10B90A70
	void PrimGroupLoader::MakePrimitive(void* object, content::ChunkReader* reader, content::LoadInventory* inventory,
		bool skin, bool gpu)
	{
		if (ReadGroup(reader, inventory))
		{
			if (skin)
			{
				if (gpu)
				{
					BuildGpuSkin(object, reader, inventory);
					core::SafeRelease(shader);
					return;
				}
				BuildSkin(object, reader, inventory);
				core::SafeRelease(shader);
				return;
			}
			BuildMesh(object, reader, inventory);
			core::SafeRelease(shader);
		}
	}
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x10B8BD30
	PrimGroupLoader::PrimGroupLoader()
	{
		shader = 0;
		unknownC = 0;
		unknown10 = false;
		unknown11 = true;
		unknown12 = false;
		unknown14 = 0;
		unknown18 = -1;
		unknown1C = -1;
		unknown20 = 0;
		unknown24 = 0;
		unknown28 = 0;
	}
}
