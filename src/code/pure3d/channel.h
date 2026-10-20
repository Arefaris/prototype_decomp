// pure3d animation channels (RTTI names pure3d::Channel, Float1Channel and the other channel types) and the key
// readers they evaluate through (no names survive for those; their copies sit in the animation unit,
// 0x106E2FE0 - 0x106E7BE0). Layouts partial; names are guesses.
#ifndef PURE3D_CHANNEL_H
#define PURE3D_CHANNEL_H

#include "code/content/chunkhandler.h"
#include "code/core/name.h"
#include "code/math/compressedquaternion.h"
#include "code/math/quaternion.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"
#include "code/pure3d/animation.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	// A time in an animation: the frame number and the exact time (8 bytes, passed by value)
	struct FrameTime
	{
		// 0x106E2FE0
		FrameTime();
		// 0x106E3010
		FrameTime(float time);
		// 0x106E3030: sets the frame and the time that goes with it
		void SetFrame(short frame);
		// 0x106E3050: sets the time and the frame that goes with it
		void SetTime(float newTime);
		// The exact time (inline in the engine)
		float GetFloat() const
		{
			return time;
		}

		short frame;
		float time;
	};

	// The keys of a channel: whether to interpolate, the number of keys and their frame numbers
	class ChannelKeysBase
	{
	public:
		// 0x106E3070 / 0x106E3080
		void SetMode(unsigned int mode);
		void Set(unsigned int mode, unsigned int count, const short* frames);
		// 0x106E3440: the keys around a frame (indices only); false when the frame is outside the keys
		bool FindKeys(float frame, unsigned int* index0, unsigned int* index1);
		// 0x106E34E0: finds the keys around a time (a binary search); false when the time is before the first or
		// after the last key, where both keys are that one
		bool FindKeys(FrameTime time, unsigned int* index0, unsigned int* index1, short* frame0, short* frame1);

		unsigned int mode;
		unsigned int count;
		const short* frames;
	};

	// What a key type evaluates to (the compressed quaternions evaluate to a Quaternion)
	template<class T> struct KeyValue
	{
		typedef T Type;
	};
	template<> struct KeyValue<math::CompressedQuaternion8>
	{
		typedef math::Quaternion Type;
	};
	template<> struct KeyValue<math::CompressedQuaternion6>
	{
		typedef math::Quaternion Type;
	};
	template<> struct KeyValue<math::CompressedQuaternion4>
	{
		typedef math::Quaternion Type;
	};
	template<> struct KeyValue<math::CompressedQuaternion3>
	{
		typedef math::Quaternion Type;
	};

	// The keys of rotations have a base of their own: the rotation unit holds its own copy of the setter (0x106E3240)
	class RotationKeysBase : public ChannelKeysBase
	{
	public:
		void Set(unsigned int mode, unsigned int count, const short* frames);
	};

	template<class T> struct KeysBase
	{
		typedef ChannelKeysBase Type;
	};
	template<> struct KeysBase<math::Quaternion>
	{
		typedef RotationKeysBase Type;
	};
	template<> struct KeysBase<math::CompressedQuaternion8>
	{
		typedef RotationKeysBase Type;
	};
	template<> struct KeysBase<math::CompressedQuaternion6>
	{
		typedef RotationKeysBase Type;
	};
	template<> struct KeysBase<math::CompressedQuaternion4>
	{
		typedef RotationKeysBase Type;
	};
	template<> struct KeysBase<math::CompressedQuaternion3>
	{
		typedef RotationKeysBase Type;
	};

	// Two floats and two or three shorts a key (plain structs: the channels allocate their values without constructors)
	struct Float2
	{
		float x;
		float y;
	};

	struct Short2
	{
		short x;
		short y;
	};

	struct Short3
	{
		short x;
		short y;
		short z;
	};

	// Typed keys (0x106E30A0, 0x106E30C0 and 0x106E30E0 are three instances of Set; 0x106E41C0 is the float
	// instance of Evaluate, 0x106E6350 and 0x106E69B0 those of the two compressed quaternions)
	template<class T> class ChannelKeys : public KeysBase<T>::Type
	{
	public:
		void Set(unsigned int mode, unsigned int count, const short* frames, const T* values);
		void Evaluate(FrameTime time, typename KeyValue<T>::Type* out);
		// The cheaper lookup of a key of the time's frame (no interpolation); 0x106E4020, 0x106E4180, 0x106E42E0
		void EvaluateFrame(FrameTime time, typename KeyValue<T>::Type* out);
		// 0x106E35B0 (float): the change of the value between two times, the span of a cycle and whether it wraps
		void GetDelta(float previousTime, float time, typename KeyValue<T>::Type* out, float length, bool cycle);

		const T* values;
	};

	// The keys of a vector channel that animates one or two axes through a constant vector and a value a key
	// (0x106E3110, 0x106E3160 and 0x106E31B0 are the instances of Set)
	template<class T> class DOFKeys : public ChannelKeysBase
	{
	public:
		void Set(unsigned int mode, unsigned int count, const short* frames, int axis, math::Vector constant,
			const T* values);

		int axis;
		math::Vector constant;
		const T* values;
	};

	// The rotation keys of a channel in one of its stored forms: a tag, then the keys of that form (the compressed
	// ones among them); the evaluation dispatches on the tag
	class RotationKeys
	{
	public:
		// 0x106E3340: no keys
		RotationKeys();
		// 0x106E3350: uncompressed quaternions, 0x106E3380, 0x106E33B0, 0x106E33E0 and 0x106E3410: the compressed forms
		void Set(ChannelKeys<math::Quaternion> newKeys);
		void Set(ChannelKeys<math::CompressedQuaternion8> newKeys);
		void Set(ChannelKeys<math::CompressedQuaternion6> newKeys);
		void Set(ChannelKeys<math::CompressedQuaternion4> newKeys);
		void Set(ChannelKeys<math::CompressedQuaternion3> newKeys);
		// 0x106E6D70
		void Evaluate(FrameTime time, math::Quaternion* out);
		// 0x106E6FC0: the rotation that takes the value at the first time to the one at the second
		void GetDelta(FrameTime from, FrameTime to, math::Quaternion* out);
		// 0x10734E40: the same for two times given as numbers
		void GetDelta(float previousTime, float time, math::Quaternion* out);

		int type;
		ChannelKeys<math::Quaternion> keys;
	};

	// The same for three-component values (translations, scales): the tag, then the keys of the form
	class VectorKeys
	{
	public:
		// 0x106E3270: no keys
		VectorKeys();
		// 0x106E3280, 0x106E32A0, 0x106E32F0: one or two axes
		void Set(const DOFKeys<float>& newKeys);
		void Set(const DOFKeys<Float2>& newKeys);
		void Set(const DOFKeys<Short2>& newKeys);
		// 0x106E32C0, 0x106E3310: all three axes
		void Set(const ChannelKeys<math::Vector>& newKeys);
		void Set(const ChannelKeys<Short3>& newKeys);
		// 0x106E5CC0
		void Evaluate(FrameTime time, math::Vector* out);
		// 0x106E5D70: the change of the value between two times
		void GetDelta(FrameTime from, FrameTime to, math::Vector* out);

		int type;
		unsigned char keys[0x20];
	};

	// pure3d::Channel (RTTI: vftable 0x10E5D7C8, 4 slots) and the channels derived from it: the animated values of one
	// animation, a name, the keys' frames and the values. Member and method names are guesses.
	class Channel
	{
	public:
		// 0x10736110
		Channel();
		// 0x10736640; the scalar deleting destructor is 0x107384A0
		virtual ~Channel();
		// 0x10736150: forgets the name
		virtual void Clear();
		// 0x10736140: moves the pointers a loaded channel keeps as offsets from the start of its block
		virtual void Relocate(int base);
		// The four letters of the kind of values the channel keeps (as the chunk file names them)
		virtual unsigned int GetType() = 0;

		// The interpolation mode of the keys
		unsigned int mode;
		unsigned int unknown8;
		core::Name<core::CaseInsensitiveKey32> name;
	};

	// A channel with one value per key: the frames sit in an array of shorts; the memory comes from a block of the
	// animation (an offset into it while the channel is loaded from a file) or from the heap
	class SimpleChannel : public Channel
	{
	public:
		// An empty channel (inline; the engine keeps a copy at 0x107383E0)
		SimpleChannel()
		{
		}
		// 0x10736650: room for count keys' frames
		SimpleChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x107366D0; the scalar deleting destructor is 0x10738400
		virtual ~SimpleChannel();
		// 0x10736160
		virtual void Clear();
		// 0x10734F00
		virtual void Relocate(int base);

		// 0x10734F20: the keys around a frame (see ChannelKeysBase::FindKeys)
		bool FindKeys(float frame, unsigned int* index0, unsigned int* index1);

		AnimationMemoryBlock* block;
		unsigned int count;
		short* frames;
		int offset;
	};

	class IntChannel : public SimpleChannel
	{
	public:
		// 0x107366F0
		IntChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10736760; the scalar deleting destructor is 0x107384C0
		virtual ~IntChannel();
		// 0x107361A0
		virtual void Clear();
		// 0x10734F60
		virtual void Relocate(int base);
		// 0x10734F90: "INT"
		virtual unsigned int GetType();

		// 0x10734FA0 / 0x10734FE0: the value at a frame, and at a time
		void GetValue(FrameTime time, int* out);
		void GetValue(float time, int* out);

		int* values;
	};

	class Float1Channel : public SimpleChannel
	{
	public:
		// 0x10736780
		Float1Channel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10738500: a copy on the heap
		Float1Channel(const Float1Channel& other);
		// 0x107367F0; the scalar deleting destructor is 0x107384E0
		virtual ~Float1Channel();
		// 0x107361D0
		virtual void Clear();
		// 0x10735030
		virtual void Relocate(int base);
		// 0x10735060: "FLT1"
		virtual unsigned int GetType();

		// 0x10735070 / 0x107350B0: the value at a frame, and at a time; 0x10735100: the change over a span of time
		void GetValue(FrameTime time, float* out);
		void GetValue(float time, float* out);
		void GetDelta(float previousTime, float time, float* out, float length, bool cycle);

		float* values;
	};

	class Float2Channel : public SimpleChannel
	{
	public:
		// 0x10736810
		Float2Channel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10736880; the scalar deleting destructor is 0x107385B0
		virtual ~Float2Channel();
		// 0x10736200
		virtual void Clear();
		// 0x10735150
		virtual void Relocate(int base);
		// 0x10735180: "FLT2"
		virtual unsigned int GetType();

		// 0x10735190 / 0x107351D0
		void GetValue(FrameTime time, Float2* out);
		void GetValue(float time, Float2* out);

		Float2* values;
	};

	class BoolChannel : public SimpleChannel
	{
	public:
		// 0x10736F00
		BoolChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10738CE0: a copy on the heap
		BoolChannel(const BoolChannel& other);
		// 0x10736F80; the scalar deleting destructor is 0x10738CC0
		virtual ~BoolChannel();
		// 0x107363D0
		virtual void Clear();
		// 0x10735670: "BOOL"
		virtual unsigned int GetType();

		// 0x10735680 / 0x107356D0: the value of a key and at a time
		void GetKey(unsigned int index, float* frame, bool* out);
		void GetValue(float time, bool* out);

		// One bit a key
		unsigned int* values;
	};

	class ColourChannel : public SimpleChannel
	{
	public:
		// 0x10736FA0
		ColourChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10737010; the scalar deleting destructor is 0x10738D90
		virtual ~ColourChannel();
		// 0x10736400
		virtual void Clear();
		// 0x10735720
		virtual void Relocate(int base);
		// 0x10735750: "CLR"
		virtual unsigned int GetType();

		// 0x10735760 / 0x107358F0
		void GetKey(int index, float* frame, unsigned int* out);
		void GetValue(float time, unsigned int* out);

		unsigned int* values;
	};

	class EntityChannel : public SimpleChannel
	{
	public:
		// 0x10736E70
		EntityChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10736EE0; the scalar deleting destructor is 0x10738CA0
		virtual ~EntityChannel();
		// 0x10736380
		virtual void Clear();
		// 0x107355F0: "ENT"
		virtual unsigned int GetType();

		// 0x10735600 / 0x10735630
		void GetKey(int index, float* frame, Entity** out);
		void GetValue(float time, Entity** out);

		Entity** values;
	};

	class StringChannel : public SimpleChannel
	{
	public:
		// 0x10736DA0
		StringChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10736E50; the scalar deleting destructor is 0x10738C80
		virtual ~StringChannel();
		// 0x10736350
		virtual void Clear();
		// 0x10735570: "STR"
		virtual unsigned int GetType();

		// 0x10735580 / 0x107355B0
		void GetKey(int index, float* frame, core::Name<core::CaseSensitiveKey>** out);
		void GetValue(float time, core::Name<core::CaseSensitiveKey>** out);

		core::Name<core::CaseSensitiveKey>* values;
	};

	// The channel of three-component values: the keys sit in the tagged object at +0x20
	class VectorChannel : public SimpleChannel
	{
	public:
		// An empty channel (inline; the engine keeps a copy at 0x10738420)
		VectorChannel()
		{
		}
		// 0x107368A0
		VectorChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x107368D0; the scalar deleting destructor is 0x10738440
		virtual ~VectorChannel();
		// 0x10735220: "VECT"
		virtual unsigned int GetType();
		// 0x10735230: the change of the value from previousTime to time
		virtual void GetDelta(float previousTime, float time, math::Vector* out);

		VectorKeys mKeys;
	};

	// One axis through a constant vector (the values at +0x54, the axis and the vector in front of them)
	class Vector1DOFChannel : public VectorChannel
	{
	public:
		// 0x107368F0
		Vector1DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x107385F0: a copy on the heap
		Vector1DOFChannel(const Vector1DOFChannel& other);
		// 0x107369B0; the scalar deleting destructor is 0x107385D0
		virtual ~Vector1DOFChannel();
		// 0x10736230
		virtual void Clear();
		// 0x10735290
		virtual void Relocate(int base);

		int axis;
		math::Vector constant;
		float* values;
	};

	class Vector2DOFChannel : public VectorChannel
	{
	public:
		// 0x107369D0
		Vector2DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10738720: a copy on the heap
		Vector2DOFChannel(const Vector2DOFChannel& other);
		// 0x10736A90; the scalar deleting destructor is 0x10738700
		virtual ~Vector2DOFChannel();
		// 0x10736260
		virtual void Clear();
		// 0x10735300
		virtual void Relocate(int base);

		int axis;
		math::Vector constant;
		Float2* values;
	};

	class CompressedVector2DOFChannel : public VectorChannel
	{
	public:
		// 0x10736AB0
		CompressedVector2DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10738870: a copy on the heap
		CompressedVector2DOFChannel(const CompressedVector2DOFChannel& other);
		// 0x10736B30; the scalar deleting destructor is 0x10738850
		virtual ~CompressedVector2DOFChannel();
		// 0x10736290
		virtual void Clear();
		// 0x10735370
		virtual void Relocate(int base);

		int axis;
		math::Vector constant;
		Short2* values;
	};

	class Vector3DOFChannel : public VectorChannel
	{
	public:
		// 0x10736B50
		Vector3DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10738960: a copy on the heap
		Vector3DOFChannel(const Vector3DOFChannel& other);
		// 0x10736BE0; the scalar deleting destructor is 0x10738940
		virtual ~Vector3DOFChannel();
		// 0x107362C0
		virtual void Clear();
		// 0x107353E0
		virtual void Relocate(int base);

		math::Vector* values;
	};

	class CompressedVector3DOFChannel : public VectorChannel
	{
	public:
		// 0x10736C00
		CompressedVector3DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10738A80: a copy on the heap
		CompressedVector3DOFChannel(const CompressedVector3DOFChannel& other);
		// 0x10736C70; the scalar deleting destructor is 0x10738A60
		virtual ~CompressedVector3DOFChannel();
		// 0x107362F0
		virtual void Clear();
		// 0x10735440
		virtual void Relocate(int base);

		Short3* values;
	};

	// The channel of rotations: the keys sit in the tagged object at +0x20
	class RotationChannel : public SimpleChannel
	{
	public:
		// An empty channel (inline; the engine keeps a copy at 0x10738460)
		RotationChannel()
		{
		}
		// 0x10736C90
		RotationChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10736CC0; the scalar deleting destructor is 0x10738480
		virtual ~RotationChannel();
		// 0x107354A0: "ROT"
		virtual unsigned int GetType();

		RotationKeys mKeys;
	};

	class QuaternionChannel : public RotationChannel
	{
	public:
		// 0x10736CE0
		QuaternionChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		// 0x10738B60: a copy on the heap
		QuaternionChannel(const QuaternionChannel& other);
		// 0x10736D80; the scalar deleting destructor is 0x10738B40
		virtual ~QuaternionChannel();
		// 0x10736320
		virtual void Clear();
		// 0x10735500
		virtual void Relocate(int base);

		// 0x107354B0: the rotation that takes the value at previousTime to the one at time
		void GetDelta(float previousTime, float time, math::Quaternion* out);

		math::Quaternion* values;
	};

	// pure3d::CompressedQuaternionChannel<T> (RTTI: the four key types CompressedQuaternion8, 6, 4 and 3, whose numbers
	// are the sizes of a key in bytes): a rotation channel whose keys are stored compressed
	template<class T> class CompressedQuaternionChannel : public RotationChannel
	{
	public:
		CompressedQuaternionChannel(unsigned int newCount, AnimationMemoryBlock* newBlock);
		virtual ~CompressedQuaternionChannel();
		virtual void Clear();
		virtual void Relocate(int base);

		T* values;
	};

	// A colour as the colour channels keep it: four bytes (the bit fields make the engine's code insert each into the word)
	struct Colour
	{
		unsigned int b : 8;
		unsigned int g : 8;
		unsigned int r : 8;
		unsigned int a : 8;
	};

	// 0x10735790: blends two colours byte by byte (name guess)
	void BlendColour(Colour* out, const Colour* from, const Colour* to, float t);
	// 0x10735CD0, 0x10735D20, 0x10735D70, 0x10735E60, 0x10735F20, 0x10735FA0: the value between those of two channels at
	// a time (the delta version for the floats); t is how far from the first to the second (names guessed)
	int BlendInt(IntChannel* from, IntChannel* to, float t, float time);
	float BlendFloat(Float1Channel* from, Float1Channel* to, float t, float time);
	float BlendFloatDelta(Float1Channel* from, Float1Channel* to, float t, float previousTime, float time);
	math::Vector* BlendVector(math::Vector* out, VectorChannel* from, VectorChannel* to, float t, float time);
	math::Quaternion* BlendQuaternion(math::Quaternion* out, RotationChannel* from, RotationChannel* to, float t, float time);
	unsigned int* BlendColourValue(unsigned int* out, ColourChannel* from, ColourChannel* to, float t, float time);

	// pure3d::ChannelHandler (RTTI: base RefCounted, 6 slots): reads the channels of the chunk ids it supports out of
	// a chunk file (names guessed)
	class ChannelHandler : public RefCounted
	{
	public:
		ChannelHandler()
		{
		}
		virtual ~ChannelHandler()
		{
		}
		// Whether the handler loads the channels of that chunk id
		virtual bool IsSupported(unsigned int chunkId) = 0;
		// Reads the channel the reader sits in; a channel is made from the block's memory (or from the heap without
		// one), the inventory is where the entities of an entity channel come from
		virtual Channel* Load(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block) = 0;
		// How many bytes a channel of a kind and of count keys takes in the block: the object and its arrays
		virtual void GetSize(unsigned int* objectSize, unsigned int* dataSize, unsigned int chunkId,
			unsigned short count) = 0;
	};

	// The handler of the channel kinds above (RTTI: DefaultChannelHandler, 6 slots, 8 bytes)
	class DefaultChannelHandler : public ChannelHandler
	{
	public:
		DefaultChannelHandler()
		{
		}
		// 0x107359B0
		virtual bool IsSupported(unsigned int chunkId);
		// 0x107397A0: picks the loader of the chunk's kind
		virtual Channel* Load(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
		// 0x10735A00
		virtual void GetSize(unsigned int* objectSize, unsigned int* dataSize, unsigned int chunkId,
			unsigned short count);

		// 0x10736430: the chunks inside a channel's chunk (the mode, the name, the key count and the offset)
		void ReadChunks(SimpleChannel* channel, content::ChunkReader* reader);
		// 0x10737030, 0x10737110, 0x107371F0, 0x10737C10, 0x10737AE0, 0x107379B0, 0x107395B0
		IntChannel* LoadInt(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
		Float1Channel* LoadFloat1(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
		Float2Channel* LoadFloat2(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
		ColourChannel* LoadColour(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
		BoolChannel* LoadBool(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
		StringChannel* LoadString(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
		EntityChannel* LoadEntity(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
		// 0x107372D0: the vector channels (chunk ids 0x121102 - 0x121104, 0x121118, 0x121119); 0x10738DB0: the
		// rotation channels (0x121105, 0x121111 - 0x121114)
		Channel* LoadVector(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
		Channel* LoadRotation(content::ChunkReader* reader, content::LoadInventory* inventory,
			AnimationMemoryBlock* block);
	};

	// pure3d::ChannelLoader (RTTI: base RefCounted, 3 slots; 0x84 bytes): the handlers a chunk file's channels are
	// read with, newest first; the first thing it makes is the default handler
	class ChannelLoader : public RefCounted
	{
	public:
		// 0x10739730
		ChannelLoader();
		// 0x107365D0; the scalar deleting destructor is 0x10737CF0
		virtual ~ChannelLoader();

		// 0x10735BB0: puts a handler in front of the others
		void AddHandler(ChannelHandler* handler);
		// 0x10735BF0: the first handler that loads a chunk id
		ChannelHandler* FindHandler(unsigned int chunkId);
		// 0x10735C40
		bool HasHandler(unsigned int chunkId);
		// 0x10735C80: loads the channel the reader sits in with the handler of its chunk id
		Channel* Load(content::ChunkReader* reader, content::LoadInventory* inventory, AnimationMemoryBlock* block);

		int count;
		ChannelHandler* handlers[32];
	};

	// The channels that animate one joint, in the order of the pose's arrays; a channel is null when the animation
	// does not animate that kind of value of the joint
	struct JointChannels
	{
		QuaternionChannel* rotation;
		VectorChannel* translation;
		VectorChannel* unknown10;
		VectorChannel* scale;
		VectorChannel* unknown14;
		VectorChannel* unknown1C;
	};
}

#endif
