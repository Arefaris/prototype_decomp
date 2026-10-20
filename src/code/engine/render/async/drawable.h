// engine::render::Drawable (RTTI name, from the RenderEventN template arguments): the game thread's handle to a
// drawable of the render thread. The handle is a 16-bit slot index into the drawable table (renderglobals.cpp) and
// the slot's 16-bit serial. Its methods either read the render-thread object directly or queue a render event that
// calls one of drawable.cpp's static functions on the render thread. Method names are guesses unless noted.
#ifndef ENGINE_RENDER_ASYNC_DRAWABLE_H
#define ENGINE_RENDER_ASYNC_DRAWABLE_H

#include "code/core/name.h"
#include "code/engine/message.h"
#include "code/math/vector4.h"
#include "code/pure3d/animation.h"

namespace math
{
	class Matrix;
}

namespace pure3d
{
	class ExpressionPose;
	class Pose;
	class Shader;
	class Skeleton;
	class Texture;
	class VertexDeformRegion;
	class pddiShaderInputInitData;
}

namespace engine
{
	class GameObject;

	// A segment's visibility for Drawable::SetSegmentVisibilities (RTTI type argument
	// struct engine::DrawableSegmentVisibility *): the segment name's 64-bit hash and the flag
	struct DrawableSegmentVisibility
	{
		unsigned __int64 name;
		bool visible;
	};

	namespace render
	{
		class DrawableCreator;
		class DrawableModifier;
		class ParameterSet;
		class SourceDrawable;
		struct EffectBiases;
		struct EffectOverrides;

		// How a drawable goes away (RTTI name engine::render::DestroyMode; the values are unknown except that 4 also
		// hands the render object to the deferred deletion list)
		enum DestroyMode
		{
			DESTROY_MODE_DEFERRED = 4
		};

		class Drawable
		{
		public:
			// How Drawable::CreateInstance makes the render object (RTTI name
			// struct engine::render::Drawable::InstanceOptions; the flags' meanings are unknown except shareSource,
			// which shares the source's render object instead of making an instance)
			struct InstanceOptions
			{
				InstanceOptions(const InstanceOptions& other);

				bool b0;
				bool b1;
				bool b2;
				bool b3;
				bool b4;
				bool b5;
				bool shareSource;
				// The drawable to make the instance of (a handle)
				unsigned int instanceOf;
				math::Vector4 colour;
				float unknown1C;
				float unknown20;
				float unknown24;
			};

			// A joint transform (copied float by float)
			struct JointMatrix
			{
				JointMatrix& operator=(const JointMatrix& other)
				{
					m[0] = other.m[0];
					m[1] = other.m[1];
					m[2] = other.m[2];
					m[3] = other.m[3];
					m[4] = other.m[4];
					m[5] = other.m[5];
					m[6] = other.m[6];
					m[7] = other.m[7];
					m[8] = other.m[8];
					m[9] = other.m[9];
					m[10] = other.m[10];
					m[11] = other.m[11];
					m[12] = other.m[12];
					m[13] = other.m[13];
					m[14] = other.m[14];
					m[15] = other.m[15];
					return *this;
				}

				float m[16];
			};

			Drawable() : mHandle(0xffffffff)
			{
			}
			explicit Drawable(GameObject* object);

			// The render-thread object exists and is still the slot's (the table's check)
			bool IsValid() const;
			void SetTransform(const math::Matrix& transform) const;
			// Takes over another state object's state into the render object's +0x68 object
			void CopyPoseStateFrom(pure3d::Pose* other) const;
			// The render object's flag 0x100 bit 0 (a particle system is cyclic)
			bool IsCyclic() const;
			// True when every part has finished (also for a drawable that no longer exists)
			bool IsFinished() const;
			void SetUnknownFloat(int index, float value) const;
			bool ReturnsTrue() const;
			// A new instance of the +0x68 object (of the source drawable's when there is one)
			pure3d::Pose* CreatePoseInstance() const;
			pure3d::Pose* CreatePose(int a, int b) const;
			pure3d::Skeleton* GetSkeleton() const;
			// The object at the slot's +0xC (the source the drawable was instanced from)
			ParameterSet* GetSourceDrawable() const;
			// The source's parameters (0x108258E0), null without a source
			void* GetSourceParameters() const;
			// The slot's +8 flag (true for a drawable that no longer exists)
			bool IsUnknown8() const;
			// Hands the render object's 0x106E0830 an integer
			void Method106E0830(int value) const;
			// The +0x10 field of the render object's expression mixer (of the source's when it has none)
			void* GetExpressionData() const;
			// Copies up to count matrices into the pose's joints
			void SetJointMatrices(const JointMatrix* matrices, unsigned int count) const;
			// Slot 20 of the first skin part's first controller (true without one)
			bool IsSkinAnimationUnknown() const;

			// The factories make a handle (0x10818790) and queue the creation of the render object. The heap the
			// render thread allocates from is the current one, or the game object heap when the allocator says so.
			// A drawable that is an instance of a source drawable (the flag is passed on to the render side)
			static Drawable CreateInstance(SourceDrawable* source, bool registerOnCreate, bool flag);
			static Drawable CreateInstance(SourceDrawable* source, const InstanceOptions& options,
				bool registerOnCreate);
			// A drawable whose render object the creator makes
			static Drawable Create(DrawableCreator* creator, bool registerOnCreate);
			// A new instance of the same source as another drawable
			static Drawable CreateInstanceOf(Drawable other);
			// A handle without a render object
			static Drawable Allocate(SourceDrawable* source);
			// Queues the destruction and clears the handle
			static void Destroy(Drawable* drawable);
			// The engine's callers also push a second word (0 or 4); the function ignores it (the same code, 0x107ED750)
			static void Destroy(Drawable* drawable, int mode);
			// A second drawable that takes over the first one's state
			Drawable Clone() const;

			// What the render thread does with the drawable, queued as render events
			void ApplyModifier(DrawableModifier* modifier) const;
			void ApplyModifierAgain(DrawableModifier* modifier) const;
			void SetRegistered(bool registered) const;
			void Method106E02C0() const;
			void SetFlag10() const;
			void ClearFlag10() const;
			void SetSegmentVisible(const core::Name<core::CaseSensitiveKey>& segment, bool visible) const;
			void SetSegmentVisibilities(const DrawableSegmentVisibility* visibilities, unsigned int count) const;
			void SetPartsUnknown(bool value) const;
			void Play(float start, float end, float speed, pure3d::Animation::CycleMode mode,
				unsigned int cycles) const;
			void SetName(const core::Name<core::CaseSensitiveKey>& name) const;
			void SetUnknownCC(unsigned int value) const;
			void SetTransformQueued(const math::Matrix& transform) const;
			void FindBindingSource(Drawable other) const;
			void ShareBindings(Drawable other) const;
			void SharePose(Drawable other) const;
			void CopyPoseState(Drawable other) const;
			void SetPose(pure3d::Pose* pose) const;
			void CreateBindings(const pure3d::pddiShaderInputInitData& init) const;
			void SetBindingVector4(const core::Name<core::CaseInsensitiveKey32>& name, float x, float y, float z,
				float w) const;
			void SetBindingVector(const core::Name<core::CaseInsensitiveKey32>& name, float x, float y,
				float z) const;
			void SetBindingVector2(const core::Name<core::CaseInsensitiveKey32>& name, float x, float y) const;
			void SetBindingFloat(const core::Name<core::CaseInsensitiveKey32>& name, float value) const;
			void SetBindingBool(const core::Name<core::CaseInsensitiveKey32>& name, bool value) const;
			void SetShader(pure3d::Shader* shader, bool enable) const;
			void ResetStates() const;
			void PlayAnimation(pure3d::Animation* animation, float speed, float frame, float start, float end,
				pure3d::Animation::CycleMode mode) const;
			// Marks the slot (the animation is stopped) and queues the clearing of the render object's controller
			void StopAnimation() const;
			void ApplyExpressionPose(pure3d::ExpressionPose* pose) const;
			void PlaySkinAnimation(pure3d::Animation* animation, float speed, float frame, float start, float end,
				pure3d::Animation::CycleMode mode) const;
			void PlayPartAnimation(pure3d::Animation* animation, float speed, float frame, float start,
				float end, pure3d::Animation::CycleMode mode) const;
			void Method106E0490() const;
			void Method106E03E0() const;
			void SetVertexDeformRegion(pure3d::VertexDeformRegion* region) const;
			void SetUnknownBC(float value) const;
			void SetPartsUnknown2C(float value) const;
			void SetSegmentUnknown2C(const core::Name<core::CaseSensitiveKey>& segment, float value) const;
			void SetFlag101Bit1(bool value) const;
			void SetPartAnimations(int a, bool b) const;
			void ResetParticles() const;
			void SetBiasUnknown(float value) const;
			void SetEffectBiases(EffectBiases biases) const;
			void SetEffectOverrides(EffectOverrides overrides) const;
			void SetParticleBias(core::Name<core::CaseInsensitiveKey32> name, float value) const;
			void SetGeneratorVector(core::Name<core::CaseInsensitiveKey32> name, float x, float y, float z) const;
			void SetGeneratorFloat2(core::Name<core::CaseInsensitiveKey32> name, float value) const;
			void SetParticleFloat(core::Name<core::CaseInsensitiveKey32> name, float value) const;
			void SetGeneratorFloat3(core::Name<core::CaseInsensitiveKey32> name, float value) const;
			void SetParticleUnknownE70(float value) const;
			void SetParticleUnknownE50(float value) const;
			void SetParticleUnknownE40(bool value) const;
			void SetParticleUnknownCC0(bool value) const;
			void SetParticleUnknown49C(float value) const;
			void SetParticleUnknown4A8(float value) const;
			void SetParticleUnknown4B8(bool value) const;
			void SetParticleFade(float value) const;
			void ParticleUnknownCD0() const;
			void Method106E1250(const core::Name<core::CaseSensitiveKey>& name) const;
			// Asks the render thread to load a texture from the file of that name (a file system request; the
			// data is handed to the render thread when it has been read). The two integers go to the uploader.
			static void LoadTexture(const char* name, int unknown, unsigned int a, unsigned int b);
			// Queues the deferred deletion of what the render thread frees in this frame; the number of the frame
			static int QueueDeferredDeletion();

			unsigned int mHandle;
		};
	}

	// Asks a game object for its drawable (RTTI name engine::GetCurrentDrawable; message type 7, id 2; the name
	// and the flag after the drawable are unknown)
	struct GetCurrentDrawable : public IntrusiveMessage
	{
		GetCurrentDrawable() : IntrusiveMessage(7, 2)
		{
			unknown18 = false;
		}

		render::Drawable drawable;
		core::Name<core::CaseSensitiveKey> name;
		bool unknown18;
		// The object is 0x20 bytes
		int unknown1C;
	};
}

#endif
