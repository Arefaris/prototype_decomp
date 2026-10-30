// pure3d::Drawable (RTTI name; bases pure3d::Entity, pure3d::RefCounted, core::IRefCount; 0x108 bytes, vftable
// 0x10E55238): an instance of a drawable model, a list of parts (0x12C bytes each), every part a pure3d primitive,
// its per-instance state, its world matrices and its visibility client, plus the skeleton pose, the animation
// controllers and the bounds of the whole. The unit is code/pure3d/src/drawable.cpp (0x106DE950 - 0x106E28F0, file
// name guessed from the class). Member and method names are guesses unless noted; methods not reconstructed yet
// are named after the field they touch or their address.
#ifndef PURE3D_DRAWABLE_H
#define PURE3D_DRAWABLE_H

#include "code/container/arraydynamic.h"
#include "code/core/bitfield.h"
#include "code/core/name.h"
#include "code/math/aabb.h"
#include "code/math/matrix.h"
#include "code/math/pddicolour.h"
#include "code/math/sphere.h"
#include "code/math/vector4.h"
#include "code/pure3d/entity.h"
#include "code/pure3d/pose.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/visibility.h"

namespace pure3d
{
	class Drawable;

	// A segment of a drawable: a named group of consecutive parts
	struct DrawableSegment
	{
		core::Name<core::CaseSensitiveKey> name;
		unsigned int firstPart;
		unsigned int partCount;
	};

	// 0x106DF480: the frame number drawables mark their updates with
	unsigned int GetCurrentFrame();

	class dxShader;
	class DrawablePart;

	// A part's binding (a 0x30-byte object made by 0x10706550): its shader parameters and, at +0x28, the flags
	// the part's render state follows
	class PartBinding
	{
	public:
		unsigned char unknown0[0x10];
		// the shader the part is drawn with; its inputs take the part's parameters
		dxShader* shader;
		unsigned char unknown14[0xC];
		// How many parts use the binding
		int users;
		unsigned char unknown24[4];
		core::BitField<unsigned int> flags;

		// 0x10704AF0 / 0x10704B00: a part takes the binding / lets go of it (the count is left alone without a part;
		// names guessed)
		void Attach(DrawablePart* part);
		void Detach(DrawablePart* part);
	};

	// The data the device draws a part with (0x2C bytes; the second word is part of the sort key)
	struct PartBatch
	{
		unsigned int unknown0;
		unsigned int sortKey;
		unsigned char unknown8[0x24];
	};

	// The shader a part draws with (its object is another unit's; slot 4 answers the number the parts are sorted by)
	class PartShader
	{
	public:
		virtual ~PartShader();
		virtual void Unknown1();
		virtual void Unknown2();
		virtual void Unknown3();
		virtual int GetSortKey();
	};

	// What a part's binding comes from
	class PartBindingSource
	{
	public:
		// 0x10706550
		PartBinding* CreateBinding();

		unsigned char unknown0[0x10];
		PartShader* shader;
		// The draw parameters of the shader (what the passes hand the primitive)
		PrimStreamParameters parameters;
	};

	// A part of a drawable (0x12C bytes)
	class DrawablePart
	{
	public:
		// 0x106DF020: an empty part that takes references to the primitive and its state
		DrawablePart(Primitive* newPrimitive, PrimitiveState* newState);
		// 0x106DF110
		DrawablePart(const DrawablePart& other);
		// 0x106DF340: releases the primitive, the state and the shader
		~DrawablePart();

		// 0x102D3D30: the binding, else the state's or primitive's binding source (another unit's out-of-line
		// copy)
		PartBindingSource* GetBindingSource();
		// 0x106DE950: the binding at +0x98 (reference counted)
		void SetBinding(PartBinding* binding);
		// 0x106DEEC0: the primitive at +0x90 (reference counted); render bit 9 is set (name guess)
		void SetPrimitive(Primitive* newPrimitive);
		// 0x106DEEF0: the state at +0x94 (reference counted); render bit 9 is set
		void SetState(PrimitiveState* newState);
		// 0x106E13C0: the world matrix, marked as not the identity
		math::Matrix* GetWorldMatrix();
		// 0x10761750: draws the part with the shader of that name (the batch or the primitive, by render bit 9)
		void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, const PrimStreamParameters* parameters);
		// 0x106DEF20: lets the primitive fill the batch (the data the device draws the part with); the answer says
		// whether it did (render bit 9). Answers the primitive's own flag.
		bool UpdateBatch();

		// The binding whose flags the part follows: the part's own, else the state's, else the primitive's
		PartBinding* GetRenderBinding()
		{
			if (binding)
			{
				return binding;
			}
			if (state && state->GetBindingSource())
			{
				return (PartBinding*)state->GetBindingSource();
			}
			if (primitive && primitive->unknown18)
			{
				return (PartBinding*)primitive->unknown18;
			}
			return 0;
		}

		unsigned char* flags;
		unsigned char unknown4[0x14];
		float unknown18;
		float unknown1C;
		visibility::Client client;
		float unknown2C;
		unsigned char unknown30[0x20];
		// The joint matrix the part follows (identity when it has none)
		math::Matrix jointMatrix;
		Primitive* primitive;
		PrimitiveState* state;
		PartBinding* binding;
		unsigned char unknown9C[4];
		// What the device draws the part with when render bit 9 is set (0x2C bytes)
		PartBatch batch;
		// The part's world matrix (render bit 10 says whether it is the identity)
		math::Matrix worldMatrix;
		PartShader* unknown10C;
		unsigned char unknown110[0x18];
		// The render state bits (1 - 5 from the binding's flags, 7 from the primitive, 10: identity world matrix)
		core::BitField<unsigned short> renderBits;
		unsigned char unknown12A;
		unsigned char unknownIndex : 4;
		unsigned char unknown12B : 4;
	};

	// A part by drawable and index
	class PartRef
	{
	public:
		// 0x106DF4B0
		PartRef(Drawable* owner, int index);
		DrawablePart* Get() const;
		// 0x106DFE00 / 0x106DFDE0: the binding of the part and putting one on it (out-of-line copies)
		PartBinding* GetBinding() const;
		void SetBinding(PartBinding* binding);
		DrawablePart* operator->() const
		{
			return Get();
		}
		// 0x106E14B0
		void Unknown106E14B0(bool value);
		// 0x106DFD70, 0x106DFE20
		void Unknown106DFD70();
		FrameController* Unknown106DFE20();

		Drawable* owner;
		int index;
	};

	class Drawable : public Entity
	{
	public:
		// How an instance of a drawable is made (the render side's copy of engine::render::Drawable::InstanceOptions)
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
			Drawable* instanceOf;
			math::Vector4 colour;
			float unknown1C;
			float unknown20;
			float unknown24;
		};

		// 0x106E1F40: a drawable of the parts in the array (their state is taken over); the name is the text of its
		// entity
		Drawable(const char* name, container::ArrayDynamic<DrawablePart, container::AllocatorNew>& newParts,
			bool unknown);

		// 0x106E2890: a new drawable made from this one (0x108 bytes, constructor 0x106E21B0)
		Drawable* CreateInstance(const CreateOptions& options);

		// 0x106DF4F0: false when poses are checked per frame and this one's was not marked this frame
		bool IsPoseCurrent();
		// 0x106DF520: flag 0x100 bit 0
		bool IsCyclic();
		// 0x106DF5E0 / 0x106DF5F0: flag 0x100 bit 4 (the drawable is not animated)
		void SetFlag10();
		void ClearFlag10();
		// 0x106DF610, 0x106DF620, 0x106DF630, 0x106DF650, 0x106DF640, 0x106DFF80
		Skeleton* GetSkeleton();
		Pose* GetPose();
		FrameController* GetUnknown78();
		FrameController* GetUnknown7C();
		VertexOffsetExpressionMixer* GetExpressionMixer();
		FrameController* GetUnknown80();
		// 0x106DF680: flag 0x101 bit 1
		void SetFlag101Bit1(bool value);
		// 0x106DFFD0: advances the controllers, the expressions and the particle states by dt
		void Update(float dt);
		// 0x106E02C0: vftable slot 5 of every part's state, slot 0x15 of +0x78 and +0x7C
		void Unknown106E02C0();
		// 0x106E0340: every part has finished
		bool IsFinished();
		// 0x106E03E0, 0x106E0490
		void Unknown106E03E0();
		void Unknown106E0490();
		// 0x106E0540: copies the matrix to +0x14 when it differs and marks the transform dirty
		void SetTransform(const math::Matrix& transform);
		// 0x106E0580: the skeleton at +0x64 (reference counted)
		void SetSkeleton(Skeleton* newSkeleton);
		// 0x106E05A0 / 0x106E06A0 (reference-counted pointers at +0x68 / +0x78)
		void SetPose(Pose* object);
		void SetUnknown78(FrameController* controller);
		// 0x106E0680: marks the pose dirty
		void MarkPoseDirty();
		// 0x106DF6C0: flag 0x100 bit 3
		void SetFlag100Bit3(bool value);
		// 0x106E0760: the controller at +0x7C (reference counted; it is told about the drawable)
		void SetUnknown7C(FrameController* controller);
		// 0x106E06E0: the source the parts' expressions follow (the mixer at +0x84, reference counted)
		void SetExpressionSource(Entity* source);
		// 0x106E0810: the joint of a part
		void SetPartJoint(unsigned int part, unsigned short joint);
		// 0x106E1F10: takes a copy of the segments (the array at +0xA4)
		void SetSegments(const container::ArrayDynamic<DrawableSegment, container::AllocatorNew>& newSegments);
		// 0x106E0910: the float at +0xB4 and its index at +0xB8
		void SetUnknownFloat(int index, float value);
		// 0x106E09A0
		void Unknown106E09A0(Drawable* other);
		// 0x106E0A40 / 0x106E0AA0: the index of the named segment (0xFFFF when there is none)
		unsigned short FindSegment(const core::Name<core::CaseSensitiveKey>& name);
		unsigned short FindSegment(unsigned __int64 name);
		// 0x106E0BB0
		void SetSegmentVisible(unsigned short segment, bool visible);
		// 0x106E0B30: the first part and the part count of a segment (both 0 for a bad index)
		void GetSegmentParts(unsigned short segment, unsigned int* first, unsigned int* count);
		// 0x106E0D60: the box and sphere around every part (when the transform changed, or always with force)
		void UpdateBounds(bool force);
		// 0x106E11F0: the value at +0xCC, handed to every part's primitive
		void SetUnknownCC(int value);
		// 0x106E0950: the float at +0xBC (clamped to 0 - 1)
		void SetUnknownBC(float value);
		// 0x106E1260: the part's float at +0x2C
		void SetPartUnknown2C(int part, float value);
		// 0x106E1250, 0x106E0830
		void Unknown106E1250(const core::Name<core::CaseSensitiveKey>& name);
		void Unknown106E0830(int value);
		// 0x106E14E0: the part's world matrix and render bits from the drawable's state
		void UpdatePart(unsigned int index);
		// 0x106E18A0: UpdatePart for every part when the parts are dirty
		void UpdateParts();

		// The parts and bounds need updating
		void MarkTransformDirty()
		{
			partsDirty = true;
			boundsDirty = true;
			dirty.SetMask(4);
		}

		// 0x107E8050 is an out-of-line copy
		bool IsRegistered() const
		{
			return registered;
		}

		unsigned char unknown10[4];
		math::Matrix transform;
		container::ArrayDynamic<DrawablePart, container::AllocatorNew> parts;
		unsigned char unknown60[4];
		Skeleton* skeleton;
		Pose* pose;
		// The joint of every part (0xFFFF for none)
		container::ArrayDynamic<unsigned short, container::AllocatorNew> partJoints;
		FrameController* unknown78;
		FrameController* unknown7C;
		FrameController* unknown80;
		VertexOffsetExpressionMixer* expressionMixer;
		// Bit 0: unknownB8 changed, bit 2: transforms changed, bit 3: unknownBC changed
		core::BitField<unsigned int> dirty;
		core::BitField<unsigned int> unknown8C;
		unsigned char unknown90[4];
		// Per part: bit 1 the state is updated, bits 2 - 4 render flags
		container::ArrayDynamic<unsigned char, container::AllocatorNew> partFlags;
		unsigned char unknownA0[0x14];
		float unknownB4;
		int unknownB8;
		float unknownBC;
		// The frames the drawable and its pose were last marked in
		unsigned int frameC0;
		unsigned int poseFrame;
		unsigned char unknownC8[4];
		int unknownCC;
		math::AABB bounds;
		math::Sphere sphere;
		core::Name<core::CaseSensitiveKey> unknownF8;
		// +0x100: bit 0 cyclic, bit 4 set by SetFlag10, bit 5 the parts are dirty, bit 6 the bounds are dirty, bit
		// 7 in the render list
		unsigned char cyclic : 1;
		unsigned char flag02 : 1;
		unsigned char flag04 : 1;
		unsigned char flag08 : 1;
		unsigned char flag10 : 1;
		unsigned char partsDirty : 1;
		unsigned char boundsDirty : 1;
		unsigned char registered : 1;
		// +0x101: bit 0 forces the update, bit 1 updates only on visibility
		unsigned char forceUpdate : 1;
		unsigned char updateWhenVisible : 1;
		unsigned char flags101 : 6;
		unsigned char unknown102[6];
	};

	inline DrawablePart* PartRef::Get() const
	{
		return &owner->parts.begin[index];
	}
}

#endif
