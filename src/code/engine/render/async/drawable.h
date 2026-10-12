// engine::render::Drawable (RTTI name, from the RenderEventN template arguments): the game thread's handle to a
// drawable of the render thread. The handle is a 16-bit slot index into the drawable table (renderglobals.cpp) and
// the slot's 16-bit serial. Its methods either read the render-thread object directly or queue a render event that
// calls one of drawable.cpp's static functions on the render thread. Method names are guesses unless noted.
#ifndef ENGINE_RENDER_ASYNC_DRAWABLE_H
#define ENGINE_RENDER_ASYNC_DRAWABLE_H

#include "code/core/name.h"
#include "code/engine/message.h"
#include "code/math/vector4.h"

namespace math
{
	class Matrix;
}

namespace pure3d
{
	class Pose;
	class Skeleton;
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
			// The +0x10 field of the render object's expression mixer (of the source's when it has none)
			void* GetExpressionData() const;
			// Copies up to count matrices into the pose's joints
			void SetJointMatrices(const JointMatrix* matrices, unsigned int count) const;
			// Slot 20 of the first skin part's first controller (true without one)
			bool IsSkinAnimationUnknown() const;

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
	};
}

#endif
