// pure3d::PrimGroupLoader (RTTI name; base pure3d::RefCounted, 3 vftable slots): what a mesh's "prim group" chunk
// turns into, the description of the primitive groups the mesh's geometry is cut into. It is not a loader in the
// content sense (its base is the plain reference-counted class) and the unit around it is 0x10B8BD30 - 0x10B8C800.
// A PolySkinLoader (and the other loaders) keeps one at +0x18 and builds its primitives through it.
// The member and method names are guesses; the layout is what the constructor and the methods write.
#ifndef PURE3D_GEOMETRY_PRIMGROUPLOADER_H
#define PURE3D_GEOMETRY_PRIMGROUPLOADER_H

#include "code/content/chunkhandler.h"
#include "code/core/refptr.h"
#include "code/pure3d/entity.h"
#include "code/pure3d/shader.h"

namespace pure3d
{
	class DrawablePart;
	class Mesh;
	class MeshState;
	class GpuSkin;
	class GpuSkinState;
	class Skin;
	class SkinState;
	class VertexOffsetList;
	class dxVertexDeclaration;
	class dxIndexBufferState;
	class ShaderParameters;
	struct IndexBufferDescription;
	struct VertexBufferDescription;

	class PrimGroupLoader : public RefCounted
	{
	public:
		// 0x10B8BD30 / 0x10B8C030. The destructor is declared first and not defined here, so that the vftable stays
		// with the engine's own copy of the unit.
		PrimGroupLoader();
		~PrimGroupLoader();

		// 0x10B8BD80: stores the group's own index
		void SetIndex(int index);
		// 0x10B8F1C0: reads the description of the group the reader sits on into this; false when the chunk is not a
		// prim group one
		bool ReadGroup(content::ChunkReader* reader, content::LoadInventory* inventory);
		// 0x10B8FFE0 / 0x10B8F400 / 0x10B8DFF0: make the gpu skin, the skin or the mesh the group describes
		void BuildGpuSkin(void* object, content::ChunkReader* reader, content::LoadInventory* inventory);
		void BuildSkin(void* object, content::ChunkReader* reader, content::LoadInventory* inventory);
		void BuildMesh(void* object, content::ChunkReader* reader, content::LoadInventory* inventory);
		// 0x10B8C060: reads a stream layout chunk (0x10014) into the parameters (name guess)
		void ReadStreams(ShaderParameters* parameters, content::ChunkReader* reader);
		// 0x10B8C270: makes the mesh into the part (and the state that keeps the streams the group animates, when it
		// has any) and locks its buffers (name guess)
		void CreateMesh(DrawablePart* part, Mesh** mesh, MeshState** state, VertexBufferDescription* description,
			ShaderParameters* stateParameters, ShaderParameters* meshParameters, IndexBufferDescription* indices,
			dxVertexDeclaration* stateLock, dxVertexDeclaration* lock, dxIndexBufferState* indexLock);
		// 0x10B8C820: makes the skin into the part with its state and fills the locks the skin chunks are read into:
		// the skin's own vertex data (the bone streams), its buffer and the block at +0x264 (name guess)
		void CreateSkin(DrawablePart* part, Skin** skin, SkinState** state, VertexOffsetList* offsets,
			VertexBufferDescription* sourceStreams, VertexBufferDescription* bufferStreams,
			VertexBufferDescription* stateStreams, IndexBufferDescription* indices, dxVertexDeclaration* sourceLock,
			dxVertexDeclaration* bufferLock, dxVertexDeclaration* unknownLock, dxIndexBufferState* indexLock);
		// 0x10B8BD90: makes the gpu skin into the part with its state and locks its buffers (name guess)
		void CreateGpuSkin(DrawablePart* part, GpuSkin** skin, GpuSkinState** state,
			VertexBufferDescription* description, IndexBufferDescription* indices, dxVertexDeclaration* lock,
			dxIndexBufferState* indexLock);
		// 0x10B90A70: makes the object of the group the reader sits on (the gpu skin for a skin group when gpu, the
		// skin for a skin group, the mesh otherwise) and releases the shader it was read with
		void MakePrimitive(void* object, content::ChunkReader* reader, content::LoadInventory* inventory, bool skin,
			bool gpu);

		// The shader the group draws with (found in the inventory under the name in the chunk)
		Shader* shader;
		int unknownC;
		bool unknown10;
		bool unknown11;
		bool unknown12;
		int unknown14;
		int unknown18;
		int unknown1C;
		int unknown20;
		int unknown24;
		int unknown28;
	};
}

#endif
