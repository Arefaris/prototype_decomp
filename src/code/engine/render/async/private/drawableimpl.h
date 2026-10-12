// What drawable.cpp needs of the render thread's side: the drawable table's slots (renderglobals.cpp) and the render
// module's drawable object (0x106Dxxxx - 0x106Exxxx, no RTTI, no names: called DrawableImpl here; it is a
// pure3d::Entity, reference counted through its vftable). A drawable is a list of parts (0x12C bytes each), every
// part a pure3d primitive and its per-instance state. Only what the async units call is declared; methods whose
// purpose is not evident are named after the field they touch or their address. All of these are in other units.
#ifndef ENGINE_RENDER_ASYNC_PRIVATE_DRAWABLEIMPL_H
#define ENGINE_RENDER_ASYNC_PRIVATE_DRAWABLEIMPL_H

#include "code/container/arraydynamic.h"
#include "code/core/name.h"
#include "code/engine/render/async/drawable.h"
#include "code/math/matrix.h"
#include "code/math/pddicolour.h"
#include "code/math/vector4.h"
#include "code/pure3d/entity.h"
#include "code/pure3d/pose.h"
#include "code/pure3d/primitive.h"

namespace engine
{
	namespace render
	{
		class DrawableImpl;

		// The shader parameters of a part's binding (0x106140C0, 0x10614050, 0x10613F90, 0x10613EC0)
		class BindingParameters
		{
		public:
			void SetVector4(const core::Name<core::CaseInsensitiveKey32>& name, const math::Vector4& value);
			void SetVector(const core::Name<core::CaseInsensitiveKey32>& name, const math::Vector& value);
			void SetFloat(const core::Name<core::CaseInsensitiveKey32>& name, float value);
			void SetBool(const core::Name<core::CaseInsensitiveKey32>& name, bool value);
		};

		// A part's binding (a 0x30-byte object made by 0x10706550; its meaning is unknown beyond the parameters)
		class PartBinding
		{
		public:
			unsigned char unknown0[0x10];
			BindingParameters* parameters;
		};

		// What a part's binding comes from
		class PartBindingSource
		{
		public:
			// 0x10706550
			PartBinding* CreateBinding();
		};

		// What a part's animation state is read into and written from (0x2C bytes; names guessed)
		class PartAnimationFlags
		{
		public:
			// 0x102E8920, 0x102E8B80 (another unit's out-of-line copies)
			PartAnimationFlags();
			void Set(int a, bool b);

			int unknown0;
		};

		struct PartAnimationState
		{
			PartAnimationState() : unknown18(0.0f, 0.0f, 0.0f)
			{
			}

			unsigned char unknown0[0x18];
			math::Vector unknown18;
			int unknown24;
			PartAnimationFlags unknown28;
		};

		// A part's animation (at +0x20 of the part; 0x1071AD50 / 0x1071A930 read and write its state)
		class PartAnimation
		{
		public:
			void GetState(PartAnimationState* state);
			void SetState(const PartAnimationState* state);

			int unknown0;
			int unknown4;
			int unknown8;
		};

		// A part of a drawable (0x12C bytes)
		class DrawablePart
		{
		public:
			// 0x102D3D30: the binding, else the state's or primitive's binding source (another unit's out-of-line
			// copy)
			PartBindingSource* GetBindingSource();
			// 0x106DE950: the binding at +0x98 (reference counted)
			void SetBinding(PartBinding* binding);

			unsigned char unknown0[0x20];
			PartAnimation animation;
			float unknown2C;
			unsigned char unknown30[0x60];
			pure3d::Primitive* primitive;
			pure3d::PrimitiveState* state;
			PartBinding* binding;
			unsigned char unknown9C[0x8E];
			unsigned char unknown12A;
			unsigned char unknown12B;
		};

		// A part by drawable and index
		class PartRef
		{
		public:
			// 0x106DF4B0
			PartRef(DrawableImpl* owner, int index);
			DrawablePart* Get() const;
			DrawablePart* operator->() const
			{
				return Get();
			}
			// 0x106E14B0
			void Unknown106E14B0(int value);
			// 0x106DFD70, 0x106DFE20
			void Unknown106DFD70();
			pure3d::FrameController* Unknown106DFE20();

			DrawableImpl* owner;
			int index;
		};

		class DrawableImpl : public pure3d::Entity
		{
		public:
			// How an instance of a render object is made (the render side's copy of Drawable::InstanceOptions)
			struct CreateOptions
			{
				// 0x106E1400
				CreateOptions();
				explicit CreateOptions(bool b2)
				{
					colour.x = math::pddiColour::WHITE.r * (1.0f / 255.0f);
					colour.y = math::pddiColour::WHITE.g * (1.0f / 255.0f);
					colour.z = math::pddiColour::WHITE.b * (1.0f / 255.0f);
					colour.w = math::pddiColour::WHITE.a * (1.0f / 255.0f);
					unknown1C = 1.0f;
					unknown20 = -1.0f;
					unknown24 = -1.0f;
					b0 = false;
					b1 = true;
					b3 = false;
					b4 = false;
					b5 = false;
					instanceOf = 0;
					this->b2 = b2;
				}

				bool b0;
				bool b1;
				bool b2;
				bool b3;
				bool b4;
				bool b5;
				DrawableImpl* instanceOf;
				math::Vector4 colour;
				float unknown1C;
				float unknown20;
				float unknown24;
			};

			// 0x106E2890: a new render object made from this one (0x108 bytes, constructor 0x106E21B0)
			DrawableImpl* CreateInstance(const CreateOptions& options);

			// 0x106DF520: flag 0x100 bit 0
			bool IsCyclic();
			// 0x106DF5E0 / 0x106DF5F0: flag 0x100 bit 4
			void SetFlag10();
			void ClearFlag10();
			// 0x106DF610, 0x106DF620, 0x106DF630, 0x106DF650, 0x106DF640, 0x106DFF80
			pure3d::Skeleton* GetSkeleton();
			pure3d::Pose* GetPose();
			pure3d::FrameController* GetUnknown78();
			pure3d::FrameController* GetUnknown7C();
			pure3d::VertexOffsetExpressionMixer* GetExpressionMixer();
			pure3d::FrameController* GetUnknown80();
			// 0x106DF680: flag 0x101 bit 1
			void SetFlag101Bit1(bool value);
			// 0x106E02C0: vftable slot 5 of every part's state, slot 0x15 of +0x78 and +0x7C
			void Unknown106E02C0();
			// 0x106E0340: every part has finished
			bool IsFinished();
			// 0x106E03E0, 0x106E0490
			void Unknown106E03E0();
			void Unknown106E0490();
			// 0x106E0540: copies the matrix to +0x14 when it differs and marks the transform dirty
			void SetTransform(const math::Matrix& transform);
			// 0x106E05A0 / 0x106E06A0 (reference-counted pointers at +0x68 / +0x78)
			void SetPose(pure3d::Pose* object);
			void SetUnknown78(pure3d::FrameController* controller);
			// 0x106E0680: marks the pose dirty
			void MarkPoseDirty();
			// 0x106E0910: the float at +0xB4 and its index at +0xB8
			void SetUnknownFloat(int index, float value);
			// 0x106E09A0
			void Unknown106E09A0(DrawableImpl* other);
			// 0x106E0A40 / 0x106E0AA0: the index of the named segment (0xFFFF when there is none)
			unsigned short FindSegment(const core::Name<core::CaseSensitiveKey>& name);
			unsigned short FindSegment(unsigned __int64 name);
			// 0x106E0BB0
			void SetSegmentVisible(unsigned short segment, bool visible);
			// 0x106E0B30: the first part and the part count of a segment (both 0 for a bad index)
			void GetSegmentParts(unsigned short segment, unsigned int* first, unsigned int* count);
			// 0x106E0D60
			void Unknown106E0D60(int value);
			// 0x106E11F0: the value at +0xCC, handed to every part's primitive
			void SetUnknownCC(int value);
			// 0x106E0950: the float at +0xBC (clamped to 0 - 1)
			void SetUnknownBC(float value);
			// 0x106E1260: the part's float at +0x2C
			void SetPartUnknown2C(int part, float value);
			// 0x106E1250, 0x106E0830
			void Unknown106E1250(const core::Name<core::CaseSensitiveKey>& name);
			void Unknown106E0830(int value);

			// 0x107E8050 is an out-of-line copy
			bool IsRegistered() const
			{
				return registered;
			}

			unsigned char unknown10[4];
			math::Matrix transform;
			container::ArrayDynamic<DrawablePart, container::AllocatorNew> parts;
			unsigned char unknown60[0xA0];
			// +0x100: bit 0 cyclic, bit 4 set by SetFlag10, bits 5 and 6 dirty marks, bit 7 in the render list
			unsigned char cyclic : 1;
			unsigned char flag02 : 1;
			unsigned char flag04 : 1;
			unsigned char flag08 : 1;
			unsigned char flag10 : 1;
			unsigned char flag20 : 1;
			unsigned char flag40 : 1;
			unsigned char registered : 1;
		};

		inline DrawablePart* PartRef::Get() const
		{
			return &owner->parts.begin[index];
		}

		// The object a drawable was instanced from (its unit is around 0x10825xxx; called a source drawable by
		// renderglobals.cpp's assert "0 == drawableData->sourceDrawable")
		class SourceDrawable
		{
		public:
			// 0x108258E0: vftable slot 0x17 of the drawable's +0x78 object
			void* GetParameters();

			int unknown0;
			int unknown4;
			DrawableImpl* drawable;
			unsigned char unknownC[0x18];
			unsigned char flags24;
		};

		// A slot of the drawable table (16 bytes)
		struct DrawableData
		{
			DrawableImpl* drawable;
			pure3d::FrameController* unknown4;
			bool unknown8;
			// In the render list
			bool registered;
			// Put in the render list when created
			bool registerOnCreate;
			bool created;
			SourceDrawable* sourceDrawable;
		};

		// The list the render thread draws (0x1130CCC0; 0x10817B10 returns it)
		class RenderList
		{
		public:
			virtual void Add(DrawableImpl* drawable, int unknown) = 0;
			virtual void Remove(DrawableImpl* drawable) = 0;

			// 0x10712300
			void Refresh(DrawableImpl* drawable);
		};

		// 0x1128186A: passed to the texture uploader (another unit)
		extern bool gTextureLoadFlag;

		// renderglobals.cpp
		// 0x10818920: the slot of a handle, null when the handle is stale
		DrawableData* GetDrawableData(const Drawable& drawable);
		// 0x10818260
		bool IsValidDrawable(const Drawable& drawable);
		// 0x10817B10
		RenderList* GetRenderList();
		// 0x10817B40: deletes the entity once the render thread is done with it
		void DeferDelete(pure3d::Entity* entity);
		// 0x10818790 / 0x10818850
		Drawable AllocateDrawable(SourceDrawable* source, bool registerOnCreate);
		void FreeDrawable(Drawable drawable, DestroyMode mode);


		// What makes the render object of a drawable (RTTI name engine::render::DrawableCreator, one virtual)
		class DrawableCreator
		{
		public:
			virtual DrawableImpl* Create() = 0;
		};

		// Changes a render object (RTTI name engine::render::DrawableModifier, one virtual; called with null
		// for a drawable that no longer exists)
		class DrawableModifier
		{
		public:
			virtual void Apply(DrawableImpl* drawable) = 0;
		};

		// The particle overrides: 16 parameters of the particle system state and 8 of its generator
		struct EffectOverrides
		{
			float values[24];
		};

		// 34 floats; the copy constructor is out of line (0x107E85E0)
		struct EffectBiases
		{
			EffectBiases(const EffectBiases& other);

			float values[34];
		};
	}
}

#endif
