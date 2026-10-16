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
#include "code/math/matrix.h"
#include "code/pure3d/animation.h"
#include "code/math/vector.h"
#include "code/pure3d/effects/particledata.h"
#include "code/pure3d/entity.h"
#include "code/pure3d/pose.h"

namespace pure3d
{
	class PartBinding;
	class Shader;
	class PrimitiveState;
	struct PrimStreamParameters;

	// What a texture keeps at +0x10: the reference-counted description of the image the loaders fill and the device
	// upload reads (the int at +0x20 is handed to the loader, the pointer at +0x44 to its array of levels)
	struct TextureInfo : public core::IRefCount
	{
		unsigned int unknown4;
		// Which upload path the loader takes: 1 the levels the file names, 2 its mip chain, 3 a single surface
		unsigned int kind;
		unsigned int unknownC;
		unsigned int unknown10;
		unsigned int unknown14;
		unsigned int unknown18;
		unsigned int unknown1C;
		int unknown20;
		unsigned char unknown24[0x20];
		// The levels of the image: pairs of a count and the pointer to upload them from
		unsigned char* levels;
	};

	class Texture : public Entity
	{
	public:
		// 0x10729AE0 / 0x1072A0E0
		Texture();
		virtual ~Texture();

		TextureInfo* info;
	};

	// The description of a shader's inputs (8 bytes, copied and destroyed out of line: 0x10612A70 / 0x10613840)
	class pddiShaderInputInitData
	{
	public:
		pddiShaderInputInitData(const pddiShaderInputInitData& other);
		~pddiShaderInputInitData();

		void* unknown0;
		int unknown4;
	};

	class Expression;
	class ExpressionState;

	class VertexOffsetExpressionMixer : public Entity
	{
	public:
		// 0x107316F0: recomputes the mix when it changed
		void Update();
		// 0x10731700: prepares the expression and mixes the state into it
		void Apply(Expression* expression, ExpressionState* state);
		// 0x10731630
		void Mix(Expression* expression, ExpressionState* state);

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

		// 0x1072E610
		void SetBindingSource(void* source);
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

	class VertexRegionAnimController : public FrameController
	{
	public:
		// 0x1072F8C0
		void SetRegion(VertexDeformRegion* region);
		// 0x1072ED10: the region's transform (+0x98, kept inverted)
		void SetTransform(const math::Matrix& transform);
	};

	// A primitive's flags (+0xC) and type (+0x14); slot 5 is its bounding box
	class Primitive : public LockableRefCounted
	{
	public:
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
		unsigned int unknown10;
		int type;
		void* unknown18;
	};

	// Slot 4 advances the state by a time step, slot 7 is its bounding box
	class PrimitiveState : public RefCounted
	{
	public:
		virtual ~PrimitiveState();
		virtual void Unknown3();
		virtual void Update(float dt);
		virtual void Unknown5();
		virtual void Unknown6();
		virtual void GetBoundingBox(math::AABB* box);
		virtual void Unknown8();
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
		// 0x106EDC90 / 0x106EDCA0
		bool HasUnknown1A0();
		unsigned __int64 GetUnknown1B0();

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
		// 0x10707660, 0x10707670, 0x10707680
		FrameController* GetController1();
		FrameController* GetController2();
		FrameController* GetController3();

		unsigned char unknown10[0xC];
		FrameController* controller1;
		int unknown20;
		FrameController* controller2;
		FrameController* controller3;
	};

	class SkinState : public PrimitiveState
	{
	public:
		// 0x1071B200, 0x1071B210: the expression and its state at +0x74 / +0x78
		Expression* GetExpression();
		ExpressionState* GetExpressionState();
		// 0x1071B220, 0x1071B230
		FrameController* GetController1();
		FrameController* GetController2();

		unsigned char unknown10[0x64];
		Expression* expression;
		ExpressionState* expressionState;
	};

	class GpuSkinState : public PrimitiveState
	{
	public:
		// 0x10B87040, 0x10B87050
		FrameController* GetController();
		void Unknown10B87050(float value);
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
