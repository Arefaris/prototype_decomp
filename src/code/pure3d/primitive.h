// pure3d primitives and their per-instance states (RTTI names pure3d::Primitive, pure3d::PrimitiveState and the
// states derived from it: MeshState, SkinState, GpuSkinState, ParticleSystemState), the frame controllers that animate
// them (pure3d::FrameController and its subclasses) and the particle generators. Only what the engine's render units
// use so far; layouts are partial and all methods are in other units (pure3d). The type values at Primitive +0x14
// are inferred from the casts that follow the checks: 4 is a SkinState, 0x10 a ParticleSystemState.
#ifndef PURE3D_PRIMITIVE_H
#define PURE3D_PRIMITIVE_H

#include "code/core/asynctask.h"
#include "code/core/name.h"
#include "code/math/pddicolour.h"
#include "code/math/aabb.h"
#include "code/math/sphere.h"
#include "code/math/matrix.h"
#include "code/pure3d/animation.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"
#include "code/pure3d/effects/particledata.h"
#include "code/pure3d/entity.h"
#include "code/pure3d/pose.h"
#include "code/pure3d/shaderparameters.h"

namespace pure3d
{
	class PartBinding;
	class dxVertexBuffer;
	class dxIndexBuffer;
	class Shader;
	class PrimBuffer;
	class PrimitiveState;
	struct PrimStreamParameters;

	class dxTexture;
	struct TextureDescription;

	// A texture of the engine (0x18 bytes): the Direct3D 9 texture it keeps at +0x10 (the word after it is never set)
	class Texture : public Entity
	{
	public:
		// 0x10729AE0 / 0x1072A0E0
		Texture();
		virtual ~Texture();

		// 0x10729B00: makes the device texture the description asks for (a copy of the other texture's image when
		// one is given) and keeps a reference to it; false when the device cannot make it (name guess)
		bool Create(const TextureDescription* description, const Texture* source);
		// 0x1072A100: holds another device texture, letting go of the one held (name guess)
		void SetInfo(dxTexture* newInfo);

		dxTexture* info;
		unsigned int unknown14;
	};

	// The settings of a sampler input as the chunk packs them: a word and the bit fields (the unit 0x106139F0 reads)
	struct SamplerSetting
	{
		unsigned int unknown0;
		unsigned int h : 4;
		unsigned int g : 2;
		unsigned int f : 2;
		unsigned int e : 2;
		unsigned int d : 4;
		unsigned int c : 4;
		unsigned int b : 4;
		unsigned int a : 5;
		unsigned int rest : 5;
	};

	// The description of a shader's inputs (8 bytes, copied and destroyed out of line: 0x10612A70 / 0x10613840)
	class pddiShaderInputInitData
	{
	public:
		// 0x10612990: an empty description (it allocates its array)
		pddiShaderInputInitData();
		pddiShaderInputInitData(const pddiShaderInputInitData& other);
		~pddiShaderInputInitData();

		// The value of the input of that kind and name (the name is made into a core::Name inside) (0x106138A0 - 0x10613990; the input keeps the default when
		// 0x10613870 is called instead)
		void SetBool(int kind, const char* name, bool value);
		void SetFloat(int kind, const char* name, float value);
		void SetVector2(int kind, const char* name, const float* value);
		void SetVector3(int kind, const char* name, const float* value);
		void SetVector4(int kind, const char* name, const float* value);
		void SetMatrix(int kind, const char* name, const float* value);
		// 0x106139F0: a sampler
		void SetSampler(int kind, const char* name, const SamplerSetting* value);
		// 0x10613870: the default value
		void SetDefault(int kind, const char* name);

		void* unknown0;
		int unknown4;
	};

	// RTTI: pure3d::VertexOffsetList (base RefCounted, 3 slots, vftable 0x10E5DE74; 0x38 bytes): the offsets a
	// mesh's or a skin's state adds to the vertices (the expressions are mixed into it), three floats a vertex each,
	// null when the list has none of a kind. The rest of the class lives in its own unit.
	class VertexOffsetList : public RefCounted
	{
	public:
		// 0x1073F590: room for the offsets of count vertices, of the kinds the flags name (bits 4 - 6)
		VertexOffsetList(int count, unsigned int flags);
		// 0x1073F660: a copy (the same offsets, new storage)
		VertexOffsetList(const VertexOffsetList& other);
		// 0x1073F220
		void Prepare();

		int unknown8;
		int count;
		const float* positionOffsets;
		const float* normalOffsets;
		unsigned char unknown18[4];
		const float* tangentOffsets;
		unsigned char unknown20[0x18];
	};

	class ExpressionState;
	class dxVertexDeclaration;
	class dxIndexBufferState;
	struct IndexBufferDescription;
	class VertexAnimKeyFrameList;
	struct VertexBufferDescription;

	class VertexOffsetExpressionMixer : public Entity
	{
	public:
		// 0x107316F0: recomputes the mix when it changed
		void Update();
		// 0x10731700: prepares the expression and mixes the state into it
		void Apply(VertexOffsetList* expression, ExpressionState* state);
		// 0x10731630
		void Mix(VertexOffsetList* expression, ExpressionState* state);

		void* unknown10;
	};

	class ExpressionPose : public RefCounted
	{
	public:
		// 0x10730C10
		void Unknown10730C10(void* target);
	};

	class VertexDeformRegion : public RefCounted
	{
	};

	// The virtual functions are named after what the engine's callers pass them; the slots without a known use
	// are placeholders
	class FrameController : public Entity
	{
	public:
		virtual void Unknown3();
		// Advances the controller by dt
		virtual void Advance(float dt, bool unknown);
		virtual void Unknown5();
		virtual void SetRelativeSpeed(float speed);
		virtual void Unknown7();
		virtual void Unknown8();
		virtual void Unknown9();
		virtual void SetFrame(float frame);
		virtual float GetFrame();
		virtual void SetFrameRange(float start, float end);
		virtual void Unknown13();
		virtual void SetCycleMode(Animation::CycleMode mode);
		virtual void Unknown15();
		virtual void SetNumCycles(unsigned int count);
		virtual void Unknown17();
		virtual void Unknown18();
		virtual void Unknown19();
		virtual bool Unknown20();
		virtual void Reset();
		virtual void SetAnimation(Animation* animation, float a, float b);
		virtual void* GetParameters();
		// Slots 24 - 26 (the vertex controllers below declare them again); 26 makes a new controller of the same kind
		virtual void Unknown24();
		virtual void Unknown25();
		virtual FrameController* Clone();

		// 0x1072E610
		void SetBindingSource(void* source);
	};

	// RTTI: pure3d::SimpleFrameController (bases AnimationFrameController, FrameController): the base of the
	// controllers that animate one thing (a shader, a vertex region, a vertex animation). Only the type is used here.
	class SimpleFrameController : public FrameController
	{
	};

	struct JointChannels;
	struct PoseAnimationInfo;

	// Bases in the RTTI: BlendFrameController, AnimationFrameController
	class PoseAnimationController : public FrameController
	{
	public:
		// 0x10732120 (0x168 bytes)
		PoseAnimationController();

		// 0x10732320: lays the animation's joint values over the pose with the given weight. The root joint gets
		// the change of its channels since previousTime (the root motion), the other joints the values at time; the
		// weight 1 replaces the pose's values, the weight 0 keeps them. previousTime becomes time.
		void Apply(int unknown, float time, float weight, JointChannels* channels, float* previousTime);

		unsigned char unknown10[0x100];
		Pose* mPose;
		unsigned char unknown114[0x31];
		bool mUseFrameTimes;
		unsigned char unknown146[2];
		float* mFrameTimes;
		unsigned char unknown14C[0x10];
		bool mAnimatesRoot;
		unsigned char unknown15D[3];
		PoseAnimationInfo* mInfo;
		unsigned char unknown164[4];
	};

	class MeshState;

	// RTTI: pure3d::VertexRegionAnimController (29 slots; bases SimpleFrameController, AnimationFrameController,
	// FrameController): the controller that follows a vertex region. Its slots 24 - 28 are its own.
	class VertexRegionAnimController : public SimpleFrameController
	{
	public:
		virtual void Unknown24();
		virtual void Unknown25();
		// 0x10730460: a new controller of the same kind (0xE0 bytes)
		virtual VertexRegionAnimController* Clone();
		virtual void Unknown27();
		virtual void Unknown28();

		// 0x1072F8C0
		void SetRegion(VertexDeformRegion* region);
		// 0x1072ED10: the region's transform (+0x98, kept inverted)
		void SetTransform(const math::Matrix& transform);
		// 0x1072F130: takes a reference to the key frames at +0x84
		void SetKeyFrames(VertexAnimKeyFrameList* keyFrames);
		// 0x1072EC30: makes the controller follow the state's mesh
		void SetMeshState(MeshState* state);
		// 0x1072ED30: the byte at +0xD8 (a mesh state's controller of this kind answers whether it is moving)
		bool GetUnknownD8();
	};

	// RTTI: pure3d::VertexAnimController (29 slots, the same bases)
	class VertexAnimController : public SimpleFrameController
	{
	public:
		virtual void Unknown24();
		virtual void Unknown25();
		// 0x1073E470: a new controller of the same kind (0x58 bytes)
		virtual VertexAnimController* Clone();
		virtual void Unknown27();
		virtual void Unknown28();

		// 0x1073E490: takes a reference to the key frames at +0x40
		void SetKeyFrames(VertexAnimKeyFrameList* keyFrames);
		// 0x1073E390: makes the controller follow the state's mesh
		void SetMeshState(MeshState* state);
		// 0x1073E3C0: the byte at +0x50 (name guess)
		bool GetUnknown50();
	};

	// RTTI: pure3d::ShaderAnimationController (27 slots, bases SimpleFrameController, AnimationFrameController,
	// FrameController): the controller that animates a mesh's shader (only its type is used here)
	class ShaderAnimationController : public SimpleFrameController
	{
	public:
		virtual ShaderAnimationController* Clone();
	};

	// What a primitive fills the device's draw data with: the object at DrawablePart::batch (+0xA0). The engine's
	// type runs to the part's render bits, so it covers the world matrix and the block after it that drawable.h
	// names separately; only the fields a primitive's FillBatch writes are named here.
	struct PrimBatch
	{
		int unknown0;
		int sortKey;
		unsigned char unknown8[0x20];
		int unknown28;
		unsigned char unknown2C[0x44];
		unsigned short unknown70;
		unsigned short unknown72;
		int unknown74;
		int unknown78;
		int unknown7C;
		int unknown80;
		// Set by a skin's FillBatch: whether the state had a second pose to blend in
		bool unknown84;
	};

	// The groups a mesh or a state keeps (the two share the call the primitives make into them; the name is a guess)
	class PrimGroupList
	{
	public:
		// 0x106268B0: prepares the batch before the groups go into it
		void PrepareBatch(PrimBatch* batch);
		// 0x10625910: puts the group (or nothing) into the batch and answers the group that went in
		PrimGroupList* AddGroup(PrimBatch* batch, PrimGroupList* group);
	};

	// The word a primitive keeps its flags in (+0xC, the engine's PartAnimationFlags); the setter below is the copy of
	// it that the primitives' unit holds (0x102CC900; it calls 0x102CC2A0 to set and 0x102CC2C0 to clear the bit)
	struct PrimitiveFlagWord
	{
		void SetBit(int bit, bool on);
		// 0x10433DA0 (another unit's copy)
		bool Test(int bit);

		int bits;
	};

	// A primitive's flags (+0xC) and type (+0x14); slot 5 is its bounding box
	class Primitive : public LockableRefCounted
	{
	public:
		// 0x106F2F20: the type is what the primitive is drawn as (0x4000 for the gpu skin)
		explicit Primitive(unsigned int newType);
		virtual ~Primitive();
		// Draws the primitive in the state of a part with the shader of that name
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
			const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding);
		// Prepares the primitive to be drawn with a shader (the bullet tracer's ribbons pass theirs)
		virtual void Unknown4(Shader* shader);
		virtual void GetBoundingBox(math::AABB* box);
		// The centre of the primitive's bounding sphere
		virtual void GetCentre(math::Vector* centre);
		// Fills the batch of a part (see DrawablePart::UpdateBatch); the last argument is cleared when the batch
		// is not drawable as it is
		virtual bool FillBatch(void* batch, PrimitiveState* state, bool* unknown);
		// Slots 8 - 10 (the skins override two of them): the base answers 0, -1 and nothing (the vftable holds the
		// incremental link thunks 0x1001D6DD, 0x10001401 and 0x1001A1A9)
		virtual int Unknown8();
		virtual int GetUnknown9();
		virtual void SetUnknown10(int value);

		// The flags the drawable copies into its parts' render bits (meanings unknown)
		bool GetFlag3() const
		{
			return flag3;
		}
		bool GetFlag4() const
		{
			return flag4;
		}
		bool GetFlag5() const
		{
			return flag5;
		}
		bool GetFlag8() const
		{
			return flag8;
		}

		union
		{
			struct
			{
				unsigned int flag0 : 1;
				unsigned int flag1 : 1;
				unsigned int flag2 : 1;
				unsigned int flag3 : 1;
				unsigned int flag4 : 1;
				unsigned int flag5 : 1;
				unsigned int flag6 : 1;
				unsigned int flag7 : 1;
				unsigned int flag8 : 1;
				unsigned int flags9 : 23;
			};
			PrimitiveFlagWord flagWord;
		};
		unsigned int unknown10;
		int type;
		void* unknown18;
	};

	// Slot 4 advances the state by a time step, slot 7 is its bounding box
	class PrimitiveState : public RefCounted
	{
	public:
		// 0x106F2E20: a state of the primitive; 0x106F2E70: a copy of a state (the primitive and the binding source are
		// shared); 0x106F2ED0: the destructor
		explicit PrimitiveState(Primitive* newPrimitive);
		PrimitiveState(const PrimitiveState& other);
		virtual ~PrimitiveState();
		// SkinState's override makes another state of the same kind (skin.cpp)
		virtual PrimitiveState* Unknown3();
		virtual void Update(float dt);
		virtual void Unknown5();
		virtual bool Unknown6();
		virtual void GetBoundingBox(math::AABB* box);
		virtual void Unknown8(void* source);
		// Called for every part drawn in a shadow pass
		virtual void Unknown9();

		// 0x106F2DE0
		Primitive* GetPrimitive();
		// The state's own binding source, else its primitive's
		void* GetBindingSource()
		{
			if (unknownC)
			{
				return unknownC;
			}
			return primitive->unknown18;
		}
		// 0x106F2F00
		void Unknown106F2F00(int value);

		// 0x107E8030 is an out-of-line copy (unknown types read as 0x1000000)
		int GetType() const
		{
			if (primitive)
			{
				return primitive->type;
			}
			return 0x1000000;
		}

		Primitive* primitive;
		void* unknownC;
	};

	// What a state keeps past the fields above (the mesh and skin loaders walk its group table). The engine's own
	// PrimitiveState declares those members; inserting them here would move every member of the classes derived
	// from it in this header, so the loaders read the same object through this view instead.
	struct PartStateView
	{
		unsigned char unknown0[0x30];
		// The groups the state was made with, and which of them the part draws
		PrimGroupList* groups[2];
		int unknown38;
	};

	// A mesh: the primitive groups its geometry is cut into (slot 3 draws it, slot 7 fills the part's batch).
	class Mesh : public Primitive
	{
	public:
		// 0x10707E90 (0x17C bytes): a mesh of the vertex streams of the first description; the second one is the
		// streams its states keep (none for a mesh without a state), the last argument the prim group's word at +0xC
		Mesh(const ShaderParameters* parameters, const ShaderParameters* stateParameters,
			const IndexBufferDescription* indices, int unknown);
		// 0x10707840
		virtual ~Mesh();
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
			const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding);
		virtual void Unknown4(Shader* shader);
		virtual void GetBoundingBox(math::AABB* box);
		virtual void GetCentre(math::Vector* centre);
		virtual bool FillBatch(void* batch, PrimitiveState* state, bool* unknown);
		virtual int GetUnknown9();
		virtual void SetUnknown10(int value);
		// Slots 11 - 14 are the mesh's own: the first two set a flag byte (+0x174 / +0x175) and refresh the mesh
		// (0x10708010 / 0x10708030)
		virtual void SetFlag174(bool value);
		virtual void SetFlag175(bool value);
		// Slots 13 and 14: the bounds the mesh chunk gives (the loader reads them into a box and a sphere)
		virtual void SetBoundingBox(const math::AABB& box);
		virtual void SetBoundingSphere(const math::Sphere& sphere);

		// 0x10707460: the word at +0x148 (its bit 29 is read by the deform shader's modifier)
		unsigned int GetUnknown148() const;
		// 0x107074A0 / 0x107074C0: let go of the locked vertices and indices; 0x107074D0: whether the word at +0x140
		// is set; 0x107074B0: does nothing (names guessed)
		void UnlockVertices();
		void UnlockIndices();
		// 0x10707470 / 0x10707490: lock the vertices and the indices; 0x107078E0: describes the streams the mesh's
		// states keep into a lock (names guessed)
		void LockVertices(dxVertexDeclaration* lock);
		void LockIndices(dxIndexBufferState* lock);
		void DescribeStateVertices(dxVertexDeclaration* lock);
		bool HasUnknown140();
		void Unknown107074B0();

		// The word the batch carries (the kind of primitive; only its low half is copied), then the vertex buffer and
		// the index buffer the groups live in (their types are the device's, the primitives' draw and batch code
		// reach them through PrimGroupList)
		unsigned int unknown1C;
		union
		{
			PrimGroupList* unknown20;
			dxVertexBuffer* vertexBuffer;
		};
		union
		{
			PrimGroupList* unknown24;
			dxIndexBuffer* indexBuffer;
		};
		// The streams the mesh's states keep (0x10707B00 copies it); the loader fills the vertices behind the pointer
		// at +0x140 (a new[] block of unknown144 bytes)
		ShaderParameters stateParameters;
		void* unknown140;
		int unknown144;
		// The format word of the first description (bit 4: +0x1000: bits 6 and 7 of the flags)
		unsigned int unknown148;
		math::AABB bounds;
		math::Sphere sphere;
		bool unknown174;
		bool unknown175;
		int unknown178;

	private:
		// 0x10707BB0: takes the primitive's flags from the shader's (name guess)
		void SetFlagsFromShader();
	};

	// Particle system parameter names (globals of the particle module at 0x1127F0B8 - 0x1127F338; set up from
	// strings this unit does not see, hence the address names)
	// 0x1127F0B8, 0x1127F144, 0x1127F158, 0x1127F15C, 0x1127F188, 0x1127F1CC, 0x1127F208, 0x1127F20C
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F0B8;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F144;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F158;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F15C;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F188;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F1CC;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F208;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F20C;
	// 0x1127F214, 0x1127F218, 0x1127F284, 0x1127F2AC, 0x1127F2BC, 0x1127F2C8, 0x1127F2DC, 0x1127F330
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F214;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F218;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F284;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2AC;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2BC;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2C8;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2DC;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F330;
	// 0x1127F338, 0x1127F138, 0x1127F164, 0x1127F204, 0x1127F210, 0x1127F254, 0x1127F29C, 0x1127F2B8
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F338;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F138;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F164;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F204;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F210;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F254;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F29C;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2B8;
	// 0x1127F2D8, 0x1127F314, 0x1127F320
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2D8;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F314;
	extern core::Name<core::CaseInsensitiveKey32> gParticleKey1127F320;

	class PrimitiveState;

	// The particle module (0x106EDA80 returns the global at 0x1127EE4C; names guessed)
	class ParticleManager
	{
	public:
		// 0x106EE860: releases what the module keeps for a particle system state
		void ReleaseState(PrimitiveState* state);
		// 0x106EE570: prepares the module's frame (called when a frame opens)
		void Unknown106EE570();
		// 0x106EE6E0: the index of a parameter
		unsigned int FindParameter(const core::Name<core::CaseInsensitiveKey32>& name);
		// 0x106EECB0: the most parts a particle drawable may have
		unsigned int GetMaxParts();
		// 0x106EDBC0: stores the float at +0x19C
		void SetUnknown19C(float value);
		// 0x106EDC90 / 0x106EDCA0
		bool HasUnknown1A0();
		unsigned __int64 GetUnknown1B0();
		// 0x106EDA30: lets go of the surfaces it holds before the device is reset (called by the default pool)
		void Unknown106EDA30();
		// 0x106EE500: hands the buffers over again after the device came back (called by the default pool)
		void Unknown106EE500();
		// 0x106EEC50: the multisample mode the surfaces are made with, from the display's sample count
		void Unknown106EEC50(int samples);

		unsigned char unknown0[0x1A0];
		int unknown1A0;
		unsigned char unknown1A4[0xC];
		unsigned __int64 unknown1B0;
	};
	// 0x106EDA80
	ParticleManager* GetParticleManager();

	class ParticleGenerator;
	class ParticlePointGenerator;
	class ParticlePlaneGenerator;
	class ParticleSphereGenerator;
	class ParticleGridGenerator;
	class ParticleMeshGenerator;

	class ParticleGenerator : public Entity
	{
	public:
		virtual void Unknown3();
		virtual void Unknown4();
		virtual void Unknown5();
		virtual void Unknown6();
		virtual void Unknown7();
		virtual void Unknown8();
		// Advances the generator by the update data
		virtual void Update(ParticleUpdateData* data);
		// Makes the particles of the update data; unknownE4 of the state is the second argument
		virtual void Generate(ParticleUpdateData* data, void* unknownE4);

		// 0x10740E50: the generator's current transform
		void GetUnknown10740E50(math::Matrix* out);
		// 0x107404B0
		void Unknown107404B0(float value);
		// 0x10741730, 0x10741850, 0x10741CE0, 0x10741990, 0x10741250: set a parameter (named by key) of the
		// generator; the meaning of type (0 or 2) is unknown
		void SetParameter(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value);
		void SetParameter2(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value);
		void SetParameter3(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value);
		void SetParameter4(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value);
		void SetParameter5(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value);

		unsigned char unknown10[0xC0];
		void* data;
		ParticleAttributes attributes;
		unsigned char unknown240[0x60];
		math::Matrix transform;
	};

	// The kinds of generator (RTTI names; only the types are used so far)
	class ParticlePointGenerator : public ParticleGenerator
	{
	};

	class ParticlePlaneGenerator : public ParticleGenerator
	{
	};

	class ParticleSphereGenerator : public ParticleGenerator
	{
	};

	class ParticleGridGenerator : public ParticleGenerator
	{
	};

	class ParticleMeshGenerator : public ParticleGenerator
	{
	};

	class MeshState : public PrimitiveState
	{
	public:
		// 0x10707970 (0x3C bytes): a state of the mesh; the description makes the two vertex buffers it keeps, the
		// last argument is held at +0x2C
		MeshState(Mesh* mesh, const ShaderParameters* vertices, VertexOffsetList* expression);
		// 0x10707CA0: a copy of a state (its controllers are cloned, its vertex buffers made again)
		MeshState(const MeshState& other);
		// 0x10707A00
		virtual ~MeshState();
		// Slots 3 - 8: 0x10707E70 makes a copy, 0x107074F0 advances the controllers (and swaps the vertex buffers),
		// 0x107075A0 and 0x107075F0 pass their reset and question on, 0x10707650 gives the box of the mesh,
		// 0x10707690 sets the source the controllers bind to
		virtual PrimitiveState* Unknown3();
		virtual void Update(float dt);
		virtual void Unknown5();
		virtual bool Unknown6();
		virtual void GetBoundingBox(math::AABB* box);
		virtual void Unknown8(void* source);
		// 0x10707A60 / 0x10707AA0 / 0x10707AC0: take a reference to the controller at +0x1C / +0x24 / +0x28
		void SetController1(FrameController* value);
		void SetController2(FrameController* value);
		void SetController3(FrameController* value);
		// 0x10707660, 0x10707670, 0x10707680
		FrameController* GetController1();
		FrameController* GetController2();
		FrameController* GetController3();
		// 0x10707640: the offsets of the expression the controllers mix into the state
		VertexOffsetList* GetExpression();

		unsigned char unknown10[0xC];
		ShaderAnimationController* controller1;
		ShaderAnimationController* controller20;
		SimpleFrameController* controller2;
		VertexRegionAnimController* controller3;
		// The offsets of the expression (+0x2C), the two vertex buffers the state draws from (+0x30 / +0x34; the part
		// draws the one that is current) and which of them is current
		VertexOffsetList* expression;
		dxVertexBuffer* buffers[2];
		int unknown38;
	};

	class Skin;
	class SkinState;

	// RTTI: pure3d::MatrixPaletteList (base RefCounted, 3 slots, vftable 0x10EAF654; 0x14 bytes): the bone of every
	// palette entry of a skin (the prim group loader's unit has its constructor 0x10B8DFA0 and destructor 0x10B8DFC0)
	class MatrixPaletteList : public RefCounted
	{
	public:
		// The indices (a new[] block; 0x10610020 makes room for count of them, set to 0)
		struct Indices
		{
			void Resize(unsigned int count);

			unsigned int* begin;
			unsigned int* end;
			int unknown8;
		};

		MatrixPaletteList();

		Indices indices;
	};

	// 0x106E9820: the colour with its red and blue bytes swapped (name guess)
	unsigned int SwapColour(unsigned int colour);

	// 0x11209CB4: a flag the skin states are made with (name guess)
	extern bool gSkinStateFlag;

	// One entry of the queue a skin state is put on while its skinning job runs (0x10720CF0 pushes it, 0x1071F780
	// drains it); its first word is the list link, the second the state whose job is submitted
	struct SkinJobEntry
	{
		void* next;
		SkinState* state;
	};

	// One stream of vertices a skin state's job writes (0x18 bytes): whether the stream is there, where it starts in
	// the locked block, the pointers the job walks it with and the stride of its vertices (names are guesses)
	struct SkinStream
	{
		bool enabled;
		unsigned char unknown1[3];
		int offset;
		int start;
		int current;
		int end;
		int stride;
	};

	// What a skin state hands its job when the job runs on a worker thread (the record at +0x330 of the state; names
	// are guesses)
	struct SkinJobData
	{
		void* source;
		int destination;
		int unknown8;
		int count;
		int unknown10;
		const float* positionOffsets;
		const float* normalOffsets;
		const float* tangentOffsets;
		bool hasNormals;
		bool hasTangents;
		unsigned char unknown22[6];
		bool wide;
	};

	// One vertex of a skinned mesh as the skinning paths read it: four rows of four floats (the position, the normal,
	// the tangent and a fourth the paths do not use) and the four bones that move it. 0x50 bytes, and the assert of
	// the paths checks that the block they come in is 16-byte aligned.
	struct SkinVertex
	{
		math::Vector4 position;
		math::Vector4 normal;
		math::Vector4 tangent;
		math::Vector4 weights;
		unsigned short bones[4];
		unsigned char unknown48[8];
	};

	// The wider vertex record 0x1071B490 blends: one more row of four floats before the bone indices, so they sit
	// at +0x50 (0x60 bytes)
	struct SkinVertex2
	{
		math::Vector4 position;
		math::Vector4 normal;
		math::Vector4 tangent;
		math::Vector4 weights;
		math::Vector4 offset;
		unsigned short bones[4];
		unsigned char unknown58[8];
	};

	// The two poses a skin state blends over: the one at +0x7C is built by the state's Init, the one at +0x194 only
	// when it animates two of them (the flag at +0x2AC). mPoses holds the two of them.
	class SkinState : public PrimitiveState
	{
	public:
		// 0x10720810 (0x350 bytes): a state of the skin over the streams of the first two descriptions, the streams
		// it keeps itself (none for a skin the group does not animate) and the group's offset list; the flag is the
		// global 0x11209CB4 (argument names guessed)
		SkinState(Skin* skin, const ShaderParameters* stateStreams, const ShaderParameters* parameters,
			const ShaderParameters* stateParameters, VertexOffsetList* offsets, bool flag);
		// The callback the state's skinning task reports its result to (skin.cpp)
		class AsyncTaskAdaptor : public core::AsyncTaskCallback
		{
		public:
			// 0x1071B090
			AsyncTaskAdaptor();
			// 0x1071FCC0: hands the result on to the state at +4
			virtual void OnResult(int result);

			SkinState* mState;
		};

		// Slots 3 - 9 and the state's own slot 10 (skin.cpp)
		virtual PrimitiveState* Unknown3();
		virtual void Unknown5();
		virtual bool Unknown6();
		virtual void GetBoundingBox(math::AABB* box);
		virtual void Unknown8(void* source);
		virtual void Unknown9();
		virtual Pose* GetPose();

		// 0x1071B070: the flag at +0x298
		bool GetUnknown298();
		// 0x1071B1B0: the pointer at +0x70 (the pose the state renders from)
		void* GetUnknown70();
		// 0x1071B200, 0x1071B210: the expression and its state at +0x74 / +0x78
		VertexOffsetList* GetExpression();
		ExpressionState* GetExpressionState();
		// 0x1071B220, 0x1071B230
		FrameController* GetController1();
		FrameController* GetController2();
		// 0x1071B1D0: the pose the state blends towards (the second of mPoses)
		Pose* GetBlendPose();
		// 0x1071B1E0
		Pose* GetPose(int index);
		// 0x1071B170
		void SetBoundingBox(const math::AABB& box);
		// 0x1071B9A0: skins the vertices with the pose's skinning matrices, one bone each (the position through
		// the 4x4, the normal and the tangent through the 3x3), and writes the box of the positions
		void Unknown1071B9A0(math::Vector4* out, const SkinVertex* vertices, int count);
		// 0x1071B610: the same with the four bones of each vertex blended by its weights (the first step checks the
		// device and does nothing when it answers)
		void Unknown1071B610(math::Vector4* out, const SkinVertex* vertices, int count);
		// 0x1071BBD0 / 0x1071BEE0: the same without the tangent (four bones / one bone each)
		void Unknown1071BBD0(math::Vector4* out, const SkinVertex* vertices, int count);
		void Unknown1071BEE0(math::Vector4* out, const SkinVertex* vertices, int count);
		// 0x1071C0C0 / 0x1071C390: the positions only
		void Unknown1071C0C0(math::Vector4* out, const SkinVertex* vertices, int count);
		void Unknown1071C390(math::Vector4* out, const SkinVertex* vertices, int count);
		// 0x1071C530 - 0x1071D770: the same with the expression's offsets added to the vertices first (the
		// positions, normals and tangents, then the positions and normals, then the positions only; four bones or
		// one each) and 0x1071D960 - 0x1071E8F0 for the wider vertex record, which carries a second position
		// offset: the outputs are the skinned positions, normals and tangents and then the skinned offset
		void Unknown1071C530(math::Vector4* out, const SkinVertex* vertices, int count);
		void Unknown1071CA40(math::Vector4* out, const SkinVertex* vertices, int count);
		void Unknown1071CDC0(math::Vector4* out, const SkinVertex* vertices, int count);
		void Unknown1071D1B0(math::Vector4* out, const SkinVertex* vertices, int count);
		void Unknown1071D440(math::Vector4* out, const SkinVertex* vertices, int count);
		void Unknown1071D770(math::Vector4* out, const SkinVertex* vertices, int count);
		void Unknown1071D960(math::Vector4* out, const SkinVertex2* vertices, int count);
		void Unknown1071DD60(math::Vector4* out, const SkinVertex2* vertices, int count);
		void Unknown1071DFF0(math::Vector4* out, const SkinVertex2* vertices, int count);
		void Unknown1071E390(math::Vector4* out, const SkinVertex2* vertices, int count);
		void Unknown1071E5D0(math::Vector4* out, const SkinVertex2* vertices, int count);
		void Unknown1071E8F0(math::Vector4* out, const SkinVertex2* vertices, int count);

		// 0x107211D0: the flag at +0x2AC (the state blends two poses while it is set)
		bool GetUnknown2AC();
		// 0x10721160: the frame's update (the controllers advance when the device's frame changed) and the skinning
		// job of this frame
		virtual void Update(float dt);
		// 0x10720CF0: the skinning job itself: locks the buffer, works out where each stream goes and either queues the
		// job for the worker or skins on the spot
		void Unknown10720CF0();
		// 0x1071EAE0: submits the skinning task
		void SubmitTask();
		// 0x1071F840: takes a reference to the key frame list at +0x78 (the expression the skin's vertices follow)
		void SetExpressionState(VertexAnimKeyFrameList* list);
		// 0x1071F860 / 0x1071F880: take a reference to the state's controller at +0x2DC / +0x2E0 (only the second is
		// reconstructed: the first one's core::RefAssign copy lives in another unit, so its member's type is not
		// known yet)
		void SetController1(FrameController* value);
		void SetController2(FrameController* value);

		int unknown10;
		unsigned char unknown14[0xC];
		// 0x20: the skinning task of this state (0x1071EAE0 submits it, 0x1071EAF0 is its body; the task's callback
		// carries the state at +4)
		core::AsyncTaskJob job;
		unsigned char unknown68[8];
		// 0x70: the pose the state renders from (its skinning matrices at +0x38 are the bone matrices the
		// skinning paths read). GetUnknown70 hands it out as a void pointer, as the engine's callers use it.
		Pose* pose;
		VertexOffsetList* expression;
		ExpressionState* expressionState;
		unsigned char unknown7C[0x21C];
		bool unknown298;
		unsigned char unknown299[0x13];
		bool unknown2AC;
		unsigned char unknown2AD;
		// 0x2AE: set while nothing is to be skinned
		bool unknown2AE;
		unsigned char unknown2AF;
		// The vertex buffers the skinned vertices go into (the engine's callers take them for poses and groups; the
		// job locks the one mPoseIndex names, as a PrimBuffer)
		Pose* mPoses[2];
		int mBlendIndex;
		int mFrame;
		int mPoseIndex;
		math::AABB bounds;
		FrameController* controller1;
		FrameController* controller2;
		// The positions, normals and tangents the job writes
		SkinStream streams[3];
		// 0x32C: set while a job holds the locked buffer
		bool jobPending;
		unsigned char unknown32D[3];
		SkinJobData* jobData;
		unsigned char unknown334[8];
		SkinJobEntry entry;
		unsigned char unknown344[0xC];
	};

	// The instanced skin: a primitive whose parts are drawn from a skin state's pose (skin.cpp). The layout is
	// partial: its shader parameters are at +0x20 (0x107202B0 copies them out), the bounding box at +0x26C, the
	// centre at +0x284 and the vertex buffer at +0x144 (+0x148 its stream).
	class Skin : public Primitive
	{
	public:
		// Slots 3 - 7 and 9 - 12 (skin.cpp)
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
			const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding);
		virtual void Unknown4(Shader* shader);
		virtual void GetBoundingBox(math::AABB* box);
		virtual void GetCentre(math::Vector* centre);
		virtual bool FillBatch(void* batch, PrimitiveState* state, bool* unknown);
		virtual int GetUnknown9();
		virtual void SetUnknown10(int value);
		virtual void SetBoundingBox(const math::AABB& box);
		virtual void SetCentre(const math::Vector4& centre);

		// 0x1071EFB0: the word at +0x1C (the kind of primitive the batch carries)
		unsigned int GetUnknown1C();
		// 0x1071FF00 (0x29C bytes): a skin of the streams of the first description (the second and the third are
		// the mesh's and the state's when the group animates some; argument names guessed)
		Skin(const ShaderParameters* parameters, const ShaderParameters* meshParameters,
			const ShaderParameters* stateParameters, const IndexBufferDescription* indices, int unknown);
		// 0x1071EFE0: unlocks the vertex buffer when there is one
		void UnlockBuffer();
		// 0x1071EFC0: does nothing (name unknown)
		void Unknown1071EFC0();
		// 0x1071EFD0 / 0x1071EFF0: lock and unlock the indices (the object at +0x148)
		void LockIndices(dxIndexBufferState* lock);
		void UnlockIndices();
		// 0x1071FAF0: describes the skin's own vertex data (+0x138) as a lock; 0x1071FA00: locks the vertex buffer
		// (an empty lock without one); 0x1071FA50: describes the block at +0x264 (names guessed)
		void DescribeSource(dxVertexDeclaration* lock);
		void LockBuffer(dxVertexDeclaration* lock);
		void DescribeUnknown264(dxVertexDeclaration* lock);
		// 0x107202C0: builds the skin's vertex data out of what the loader read and the bone palette
		void Finish(MatrixPaletteList* palettes);
		// 0x1071F000: fills the parameters with the descriptor of the buffer
		void FillBufferDesc(ShaderParameters* parameters);
		// 0x107202B0: copies the skin's own shader parameters
		void GetParameters(ShaderParameters* parameters);
		// 0x1071F020: the vertex data the engine draws from and its size (0x50 when the data comes from +0x140)
		void GetDrawData(void** data, int* size);

		unsigned int unknown1C;
		// 0x20: the shader parameters of the skin (GetParameters hands out a copy)
		ShaderParameters parameters;
		// 0x138: the vertex data of the last skinning job; 0x13C its size and 0x140 the fallback block
		void* unknown138;
		int unknown13C;
		void* unknown140;
		// 0x144: the vertex buffer the skinned vertices go into
		PrimBuffer* buffer;
		// 0x148: the group list of this skin's geometry (the batch is prepared through it)
		PrimGroupList* stream;
		unsigned char unknown14C[0x120];
		math::AABB bounds;
		math::Vector4 centre;
		int unknown294;
		// 0x298: set when each vertex has one bone, clear when it has four
		bool unknown298;
	};

	struct VertexBufferDescription;
	struct IndexBufferDescription;
	class dxVertexBuffer;
	class dxIndexBuffer;

	class GpuSkin;

	class GpuSkinState : public PrimitiveState
	{
	public:
		// 0x10B87040, 0x10B87050
		FrameController* GetController();
		void Unknown10B87050(float value);
		// 0x1072DEC0: the object at +0x1C (a buffer; the draw reads its word at +0x38)
		int* GetBuffer();
		// 0x1072DDA0 (0x40 bytes): a state of the gpu skin; 0x1072E100: a copy of a state; 0x1072E190: the destructor
		GpuSkinState(GpuSkin* skin);
		GpuSkinState(const GpuSkinState& other);
		virtual ~GpuSkinState();
		// Slots 3 - 8: 0x1072E1C0 makes a copy, 0x1072DDE0 advances the shader animation once per frame of the
		// device, 0x1072DE20 and 0x1072DE40 pass its reset and its question on, 0x1072DE60 gives the box at +0x24,
		// 0x1072DEE0 sets the source the animation binds to
		virtual PrimitiveState* Unknown3();
		virtual void Update(float dt);
		virtual void Unknown5();
		virtual bool Unknown6();
		virtual void GetBoundingBox(math::AABB* box);
		virtual void Unknown8(void* source);
		// 0x1072DE90: the box at +0x24; 0x1072E1E0: takes a reference to the shader animation at +0x3C (the prim
		// group loader hands it the one of the group; names guessed); 0x1072DED0: hands it out
		void SetBoundingBox(const math::AABB& box);
		void SetShaderController(ShaderAnimationController* controller);
		ShaderAnimationController* GetShaderController();

		unsigned char unknown10[0xC];
		core::IRefCount* buffer;
		// The frame of the device the animation was last advanced in
		int unknown20;
		math::AABB bounds;
		ShaderAnimationController* shaderController;
	};

	// The instanced skin the device skins: a primitive whose parts are drawn from a skin state's pose by a vertex
	// shader (gpuskin.cpp). The members the draw reads are named here; the layout is partial.
	class GpuSkin : public Primitive
	{
	public:
		// 0x1072E3E0: the buffers are made from the descriptions (the second may be empty) and held
		GpuSkin(const VertexBufferDescription* vertices, const IndexBufferDescription* indices, unsigned int kind);
		// 0x1072E200
		virtual ~GpuSkin();
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
			const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding);
		// 0x1072E4F0: the shader goes to the base and to the skin's own state (not reconstructed)
		virtual void Unknown4(Shader* shader);
		virtual void GetBoundingBox(math::AABB* box);
		virtual void GetCentre(math::Vector* centre);
		virtual bool FillBatch(void* batch, PrimitiveState* state, bool* unknown);
		virtual int GetUnknown9();
		virtual void SetUnknown10(int value);
		virtual void SetBoundingBox(const math::AABB& box);
		virtual void SetCentre(const math::Vector4& centre);

		// 0x1072E380 / 0x1072E070: lock the vertex buffer (an empty lock without one) and the indices; 0x1072E080 /
		// 0x1072E090 let go of them; 0x1072E290 takes a reference to the bone palette at +0x140 (names guessed)
		void LockBuffer(dxVertexDeclaration* lock);
		void LockIndices(dxIndexBufferState* lock);
		void UnlockBuffer();
		void UnlockIndices();
		void SetPalette(MatrixPaletteList* palettes);
		// 0x1072DF00: the description of the index buffer (name guess)
		void GetIndexDescription(IndexBufferDescription* description);

		// The kind of primitive the batch carries
		unsigned int unknown1C;
		// The shader parameters the device is set up with
		ShaderParameters parameters;
		// 0x138: the vertex buffer the skin is drawn from, 0x13C its index buffer and 0x140 the bone palette (the draw
		// descriptor takes the address 8 bytes into it)
		dxVertexBuffer* unknown138;
		dxIndexBuffer* unknown13C;
		MatrixPaletteList* unknown140;
		math::AABB bounds;
		math::Vector4 centre;
		int unknown16C;

	private:
		// 0x1072E2F0: takes the primitive's flags from the shader's (called by Unknown4; name guess)
		void SetFlagsFromShader();
	};

	// The per-instance state of a particle system. The setters and parameter forwarders are inline (0x107E8060 -
	// 0x107E80D0 and 0x107E8AA0 - 0x107E8B30 are out-of-line copies); the rest is in the particle module.
	class ParticleSystemState : public PrimitiveState
	{
	public:
		// What the states made from one system share (RTTI pure3d::ParticleSystemState::SharedDetails): the block
		// of data of the system and the tables that say where its attributes are
		struct SharedDetails : public RefCounted
		{
			unsigned char unknown8[0x1CC];
			unsigned char* block;
			unsigned char unknown1D8[8];
			ParticleAttributeTable* attributes1E0;
			unsigned char unknown1E4[0xC];
			ParticleAttributeTable* attributes1F0;
			unsigned char unknown1F4[4];
			ParticleAttributeTable* attributes1F8;
		};

		// 0x1073FD30: prepares the update of the particles and submits its task (called through 0x10709C00)
		void BeginUpdate(float x, float y, float z, bool flag);
		// 0x1079F570: the body of the update task (the system's channels, the generator, the kernels)
		void UpdateParticles(ParticleUpdateData* data);
		// 0x1079F320: the box around the particles, in the emitter's space
		void UpdateBounds(ParticleUpdateData* data);
		// 0x1070C560: counts the live particles (into liveCount); returns how many of the block to update
		unsigned int CountParticles();
		// 0x106E9940: the flag at +0x3F4, or the parent's when it is inherited
		bool GetUnknown3F4();
		// 0x10709D60: the emitter transform
		math::Matrix* GetTransform();
		// 0x10709D70: the first member of the generator of the state that owns the data
		void* GetGeneratorUnknown10();
		// 0x10709E70, 0x10709E50, 0x10709E40, 0x10709CC0, 0x10709CD0
		void Unknown10709E70(float value);
		void Unknown10709E50(float value);
		void Unknown10709E40(bool value);
		void Unknown10709CC0(bool value);
		void Unknown10709CD0();
		// 0x10709CE0: the flag at +0x490
		bool GetUnknown490();
		// 0x106ED9D0: the flag at +0x4BC, or the parent's when it is inherited
		bool GetUnknown4BC();
		// 0x10709D30: the emitter transform (handed on to the generator)
		void SetTransform(const math::Matrix& transform);

		void SetUnknown49C(float value)
		{
			unknown49C = value;
		}
		void SetUnknown4A4(float value)
		{
			unknown4A4 = value;
		}
		void SetUnknown4A8(float value)
		{
			unknown4A8 = value;
		}
		void SetUnknown4B8(bool value)
		{
			unknown4B8 = value;
		}
		void SetGeneratorParameter(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value)
		{
			if (generator)
			{
				generator->SetParameter(key, type, value);
			}
		}
		// Two override parameters are the state's own, the rest go to the generator
		void SetOverride(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value)
		{
			if (key == gParticleKey1127F2AC)
			{
				override414 = *(const float*)value;
			}
			else if (key == gParticleKey1127F330)
			{
				override418 = *(const float*)value;
			}
			else if (generator)
			{
				generator->SetParameter4(key, type, value);
			}
		}
		// Two bias parameters and the four channels of a bias colour are the state's own (the colour's index is
		// looked up once), the rest go to the generator
		void SetBias(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value)
		{
			static unsigned int sColourIndex = GetParticleManager()->FindParameter(gParticleKey1127F254);
			if (key == gParticleKey1127F2AC)
			{
				bias40C = *(const float*)value;
			}
			else if (key == gParticleKey1127F330)
			{
				bias410 = *(const float*)value;
			}
			else if (key == gParticleKey1127F164)
			{
				biasColours[sColourIndex].r = (unsigned int)(*(const float*)value * 255.0f);
			}
			else if (key == gParticleKey1127F314)
			{
				biasColours[sColourIndex].g = (unsigned int)(*(const float*)value * 255.0f);
			}
			else if (key == gParticleKey1127F138)
			{
				biasColours[sColourIndex].b = (unsigned int)(*(const float*)value * 255.0f);
			}
			else if (key == gParticleKey1127F2B8)
			{
				biasColours[sColourIndex].a = (unsigned int)(*(const float*)value * 255.0f);
			}
			else if (generator)
			{
				generator->SetParameter5(key, type, value);
			}
		}
		void SetGeneratorParameter2(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value)
		{
			if (generator)
			{
				generator->SetParameter2(key, type, value);
			}
		}
		void SetGeneratorParameter3(const core::Name<core::CaseInsensitiveKey32>& key, int type, const void* value)
		{
			if (generator)
			{
				generator->SetParameter3(key, type, value);
			}
		}

		unsigned char unknown10[0xC];
		// The update kernels that run in UpdateParticles (bit n: kernel n)
		unsigned int updateKernels;
		unsigned char unknown20[4];
		// A counted event (core::EventReset) that the update task signals
		int event[2];
		unsigned char unknown2C[4];
		// The task that runs UpdateParticles (0x107A0310)
		core::AsyncTaskJob job;
		unsigned char unknown78[0xC];
		// 1 - 5: the generator is a point, plane, sphere, grid or mesh generator
		int generatorType;
		unsigned char unknown88[4];
		float unknown8C;
		float unknown90;
		float unknown94;
		bool unknown98;
		bool unknown99;
		unsigned char unknown9A[6];
		unsigned __int64 unknownA0;
		int unknownA8;
		unsigned int unknownAC;
		int unknownB0;
		int unknownB4;
		int unknownB8;
		math::Vector unknownBC;
		unsigned char unknownC8[4];
		int heap;
		unsigned char unknownD0[0x10];
		// Set by CountParticles
		unsigned int liveCount;
		unsigned char unknownE4[0x1D0];
		// The block of particle data: the tables give the offsets of the attributes in it
		unsigned char* block;
		unsigned char unknown2B8[8];
		ParticleAttributeTable* attributes2C0;
		unsigned char unknown2C4[0xC];
		ParticleAttributeTable* attributes2D0;
		unsigned char unknown2D4[4];
		ParticleAttributeTable* attributes2D8;
		unsigned char unknown2DC[4];
		float unknown2E0;
		float unknown2E4;
		float unknown2E8;
		float unknown2EC;
		float unknown2F0;
		float unknown2F4;
		unsigned char unknown2F8[0x10];
		math::Vector unknown308;
		math::Vector unknown314;
		math::Vector unknown320;
		math::Matrix unknown32C;
		math::Matrix unknown36C;
		// Indexed by the colour parameter (the members after the first colour are not colours)
		math::pddiColour biasColours[1];
		unsigned int particleCount;
		unsigned char unknown3B4[4];
		SharedDetails* shared;
		ParticleGenerator* generator;
		unsigned char unknown3C0[0x30];
		RefCountedBoolChannel* unknown3F0;
		bool unknown3F4;
		unsigned char unknown3F5[3];
		FrameController* unknown3F8;
		FrameController* unknown3FC;
		RefCountedFloat1Channel* unknown400;
		RefCountedFloat1Channel* unknown404;
		RefCountedVectorChannel* unknown408;
		float bias40C;
		float bias410;
		float override414;
		float override418;
		// The box around the particles (UpdateBounds) and the emitter transform
		math::AABB bounds;
		math::Matrix transform;
		unsigned char unknown474[0x1C];
		bool unknown490;
		unsigned char unknown491[0xB];
		float unknown49C;
		float unknown4A0;
		float unknown4A4;
		float unknown4A8;
		unsigned char unknown4AC[8];
		int unknown4B4;
		bool unknown4B8;
		unsigned char unknown4B9[3];
		bool unknown4BC;
		bool inheritUnknown4BC;
		unsigned char unknown4BE[2];
		// The state this one was made from
		ParticleSystemState* parent;
	};
}

#endif
