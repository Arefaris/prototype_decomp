// The manager of the effects the fight tracks start (the engine's global at 0x1130CCE0, read through 0x108193A0; no
// RTTI, so class and member names are guesses). It starts and stops the effect drawables and the motion trails the
// effect and motion trail actions ask for, keeps the effects it started per slot and fades the timed lights
// effects carry. The unit runs from 0x10819430 to the effect LOD classes at 0x1081EC30 - 0x1081FF60 (no assert path;
// the file name is a guess). Layouts are read off the code; the container classes of the engine's library are only
// declared with the members this unit calls (their bodies are other units' template instances).
#ifndef ENGINE_RENDER_EFFECTMANAGER_H
#define ENGINE_RENDER_EFFECTMANAGER_H

#include "code/content/loadinventory.h"
#include "code/core/name.h"
#include "code/engine/render/effectlod.h"
#include "code/engine/camera/camera.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/render/async/drawable.h"
#include "code/engine/render/async/light.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"

namespace proto
{
	struct PartLookup;
}

namespace pure3d
{
	class Shader;
}

namespace engine
{
	namespace render
	{
		typedef core::Name<core::CaseSensitiveKey> EffectName;

		// A light the manager fades in and out, flickers and destroys when its time is up or the object it hangs on is
		// gone (0xA8 bytes; the light handle comes first, -1 while it has none)
		struct EffectLight
		{
			// 0x1081A120
			EffectLight();
			// 0x10819430
			EffectLight& operator=(const EffectLight& other);

			// The light's controller handle (starts as -1) and two colours (all four channels 1 to begin with)
			Light light;  // +0x00
			math::Vector4 colour;  // +0x04
			math::Vector4 secondColour;  // +0x14
			float unknown24;
			// How long the light waits before it starts, how long it stays at full strength, how long it takes to fade
			// out and to fade in (the times of the setup, in that order of the setup's fields) and the time that is left
			float delay;  // +0x28
			float holdTime;  // +0x2C
			float fallTime;  // +0x30
			float riseTime;  // +0x34
			float age;  // +0x38
			float unknown3C;
			float flickerAmount;  // +0x40
			float unknown44;
			float unknown48;
			float unknown4C;
			float unknown50;
			float unknown54;
			float unknown58;
			// The game object the light hangs on and the joint of it
			GameObjectHandle target;  // +0x5C
			int joint;  // +0x60
			math::Matrix offset;  // +0x64
			bool attached : 1;  // +0xA4
		};

		// Where an effect light goes (0x1081EE00; 0x50 bytes): a transform, the name of the part of the game object it hangs
		// on and the game object
		struct EffectPlacement
		{
			EffectPlacement();

			math::Matrix transform;  // +0x00
			EffectName partName;  // +0x40
			GameObjectHandle target;  // +0x48
			int unknown4C;
		};

		// What a drawable effect is made from (the part the manager reads; the engine's records are larger): the placement,
		// the key of the list it goes in, the values the drawable is made with and the name of the shared drawable
		struct EffectSetup : public EffectPlacement
		{
			float unknown50;
			int unknown54;
			unsigned int key;  // +0x58
			float unknown5C;
			float unknown60;
			// The three values the drawable's options take (what they mean is unknown)
			float optionsA;  // +0x64
			float optionsB;  // +0x68
			float optionsC;  // +0x6C
			// The effect is made from a drawable it shares with others
			bool useStore;  // +0x70
			unsigned char unknown71[7];
			EffectName storeName;  // +0x78
			// The colour of the drawable
			math::Vector4 colour;  // +0x80
		};

		// What a light is made from (0x1081B040; 0xA8 bytes): where it goes, its light and colours, the times and the
		// values the flicker uses
		struct EffectLightSetup : public EffectPlacement
		{
			EffectLightSetup();

			Light light;  // +0x50
			math::Vector4 colour;  // +0x54
			math::Vector4 secondColour;  // +0x64
			float unknown74;
			float delay;  // +0x78
			float riseTime;  // +0x7C
			float holdTime;  // +0x80
			float fallTime;  // +0x84
			float unknown88;
			float unknown8C;
			float unknown90;
			float unknown94;
			float unknown98;
			float unknown9C;
			float unknownA0;
			float unknownA4;
		};

		// An effect's drawable and the drawable it hangs on (8 bytes; both start as -1)
		struct DrawableLink
		{
			// 0x10819550
			DrawableLink();

			Drawable drawable;  // +0x00
			Drawable owner;  // +0x04
		};

		// A ring of drawable links over one block (head, tail, the block's start and end); it is full one entry
		// before the head, which is why the size wraps around the end of the block
		class DrawableRing
		{
		public:
			unsigned int Size() const
			{
				if (head <= tail)
				{
					return tail - head;
				}
				return (tail - begin) + (end - head);
			}
			DrawableLink& At(unsigned int index)
			{
				int firstPart = end - head;
				if ((int)index < firstPart)
				{
					return head[index];
				}
				return begin[index - firstPart];
			}
			// Whether every place of the block is taken
			bool IsFull() const
			{
				return (int)Size() == end - begin;
			}
			// Takes the first link out of the ring and answers its drawable
			Drawable PopFront()
			{
				Drawable first = head->drawable;
				if (!(tail < end))
				{
					tail = head;
				}
				head++;
				if (head == end)
				{
					head = begin;
				}
				return first;
			}
			// Puts a link at the end (nothing when the block is used up)
			void PushBack(Drawable drawable, Drawable owner)
			{
				if (tail < end)
				{
					if (tail != 0)
					{
						tail->drawable = drawable;
						tail->owner = owner;
					}
					tail++;
					if (tail == end)
					{
						tail = begin;
					}
					if (head == tail)
					{
						tail += end - begin;
					}
				}
			}

			DrawableLink* head;
			DrawableLink* tail;
			DrawableLink* begin;
			DrawableLink* end;
		};

		// A playing effect (0xA8 bytes; its constructors and destructor are another unit's 0x10820CF0 - 0x108213D0)
		struct EffectInstance
		{
			// 0x10820CF0 / 0x10820EB0 (from a drawable and the setup it is made from) / 0x10821230 (another unit)
			EffectInstance();
			EffectInstance(unsigned int newDrawable, const EffectSetup* setup);
			EffectInstance(const EffectInstance& other);
			// 0x10820620
			EffectInstance& operator=(const EffectInstance& other);
			~EffectInstance();

			// 0x10820830 (another unit): advances the effect; true when it has finished and goes away
			bool Advance(float timeStep, const math::Vector* cameraPosition);
			// 0x1081EAC0: destroys the drawable and marks the effect as fading out for good
			void Kill();
			// 0x1081EEF0: starts fading the effect out over the time at +0x70 (unless it already does)
			void StartFade();
			// 0x1081EAB0: whether the particles are not off
			bool IsEmitting() const;
			// 0x1081EB10: switches the particles on or off, at once or over a time
			void SetEmitting(bool emitting, float fadeTime);
			// 0x1081EC00: the drawable of the store the effect is made from; the effect counts as its user when it exists
			void SetStoreDrawable(const Drawable* store);

			int unknown0;
			math::Matrix transform;  // +0x04
			math::Vector position;  // +0x44
			Drawable drawable;  // +0x50
			// The drawable of the store the effect came from
			Drawable storeDrawable;  // +0x54
			unsigned char unknown58[8];
			EffectName name;  // +0x60
			int unknown68;
			// 1000 for a spanned effect
			float unknown6C;
			float fadeTime;  // +0x70
			// The time the effect has left (the largest float once it is killed)
			float timeLeft;  // +0x74
			// The level-of-detail records of the effect (a vector of pointers, begin / end / end of storage, and the count)
			EffectLOD** lodsBegin;  // +0x78
			EffectLOD** lodsEnd;  // +0x7C
			EffectLOD** lodsCapacity;  // +0x80
			int unknown84;
			int lodCount;  // +0x88
			int unknown8C;
			// How the particles stand: 0 off, 1 about to go off, 2 on, 3 about to come on (see SetEmitting)
			int emitState;  // +0x90
			float emitTime;  // +0x94
			float emitLeft;  // +0x98
			// bit 0: the transform changed, bit 1: fading out, bit 5: counted as a user of the store it names, bit 6: made
			// from a store (the effect keeps the store alive)
			union
			{
				unsigned char flags;  // +0x9C
				struct
				{
					unsigned char transformChanged : 1;
					unsigned char fadingOut : 1;
					unsigned char unknownBit2 : 1;
					unsigned char unknownBit3 : 1;
					unsigned char unknownBit4 : 1;
					unsigned char usesStore : 1;
					unsigned char fromStore : 1;
					unsigned char unknownBit7 : 1;
				};
			};
			unsigned char unknown9D[3];
			// The name of the store the effect belongs to
			EffectName storeName;  // +0xA0
		};

		// The effects playing under one name: a vector of instances (begin, end, end of storage)
		struct EffectInstanceList
		{
			unsigned int Size() const
			{
				return end - begin;
			}
			// Whether another effect fits without growing
			bool HasRoom() const
			{
				return end != capacity;
			}

			EffectInstance* begin;
			EffectInstance* end;
			EffectInstance* capacity;
			int unknownC;
		};

		// An open-addressing table of 32-bit keys with pointers as values (0x28 bytes): the slots hold a null for an empty
		// place and the address of the table's last member for a removed one. The engine's copy works on untyped
		// pointers (one copy of every function serves the tables of all the manager's record types).
		struct HashTable
		{
			// 0x1081D170: a table of that many slots (rounded up to a power of two), the load in percent it grows at
			// and the number of removed places it tolerates
			HashTable(unsigned int newSlotCount, unsigned int newMaxLoad, unsigned int newMaxRemoved);
			// 0x1081C6C0: moves everything into a table of that many slots
			void Rehash(unsigned int newSlotCount);
			// 0x1081C620: puts a value under a key (the key must not be in the table)
			void Insert(const unsigned int* newKey, void* value);

			unsigned int slotCount;  // +0x00
			unsigned int count;  // +0x04
			unsigned int removed;  // +0x08
			bool compactWhenRemoved;  // +0x0C
			unsigned int maxRemoved;  // +0x10
			unsigned int maxLoad;  // +0x14
			int heap;  // +0x18
			void** slots;  // +0x1C
			unsigned int* keys;  // +0x20
			unsigned char removedMarker[4];  // +0x24
		};

		// A probe through a table for a key (20 bytes): the table, the key, the slot it started at, the slot it is at and the
		// step between slots
		struct HashLookup
		{
			explicit HashLookup(HashTable* newTable)
				: table(newTable), key(0), start(0), slot(0), step(0)
			{
			}
			// 0x1081A890: the value of the key, null when the table has none
			void* Find(const unsigned int* newKey);
			// 0x1081A910: the first place that is empty, removed or holds the key
			void* FindForInsert(const unsigned int* newKey);
			// 0x10819C30: the next place of the probe
			void* Next();

			HashTable* table;
			unsigned int key;
			unsigned int start;
			unsigned int slot;
			unsigned int step;
		};

		// Where a loop over a table stands (the table and the slot it is at)
		struct HashIteratorBase
		{
			// Steps to the next used slot and answers its value, null at the end
			void* Next()
			{
				HashTable* source = table;
				unsigned int slot = index;
				void* value;
				do
				{
					slot++;
					if (slot >= source->slotCount)
					{
						break;
					}
					value = source->slots[slot];
				}
				while (value == 0 || value == (void*)source->removedMarker);
				index = slot;
				void* result = slot >= source->slotCount ? 0 : source->slots[slot];
				return result;
			}
			// The same step as a call (the engine's copy at 0x10819A40)
			void* NextCalled();

			HashTable* table;
			unsigned int index;
		};

		// The loop over the records of a table
		template<class Value> struct HashIterator : HashIteratorBase
		{
			Value* Next()
			{
				return (Value*)HashIteratorBase::Next();
			}
			Value* NextCalled()
			{
				return (Value*)HashIteratorBase::NextCalled();
			}
		};

		// An effect drawable kept ready by name: how many uses it has and when it was last used (0x20 bytes)
		struct EffectStore
		{
			Drawable drawable;  // +0x00
			int unknown4;
			EffectName name;  // +0x08
			int users;  // +0x10
			float lastUsed;  // +0x14
			bool active;  // +0x18
			int unknown1C;
		};

		// An effect started on a named slot (16 bytes)
		struct SlotEffect
		{
			Drawable drawable;  // +0x00
			int unknown4;
			EffectName slot;  // +0x08
		};

		// What an attached drawable (one that follows a game object) is made from (0x44 bytes): the name of its shader, the
		// values it is made with, the game object and the key of the ring it goes in
		struct AttachedEffectSetup
		{
			EffectName shader;  // +0x00
			int unknown8;
			math::Vector position;  // +0x0C
			math::Vector unknown18;
			float unknown24[2];
			GameObjectHandle owner;  // +0x2C
			float unknown30;
			float unknown34;
			float unknown38;
			unsigned int key;  // +0x3C
			// Only started when the camera can see its position
			bool needsView;  // +0x40
		};

		// A drawable that follows a game object (8 bytes)
		struct AttachedDrawable
		{
			// 0x10819500
			AttachedDrawable();

			Drawable drawable;  // +0x00
			GameObjectHandle owner;  // +0x04
		};

		// A ring of attached drawables (0x14 bytes); its size is the engine's out-of-line copy
		struct AttachedRing
		{
			// 0x10819670
			unsigned int Size() const;
			// 0x1081A560: puts a drawable at the end; false when the block is used up
			bool PushBack(const AttachedDrawable* item);
			AttachedDrawable& At(unsigned int index)
			{
				int firstPart = end - head;
				if ((int)index < firstPart)
				{
					return head[index];
				}
				return begin[index - firstPart];
			}

			AttachedDrawable* head;
			AttachedDrawable* tail;
			AttachedDrawable* begin;
			AttachedDrawable* end;
			int unknown10;
		};

		class EffectManager
		{
		public:
			// 0x10819560: releases a drawable the manager made
			void ReleaseDrawable(Drawable* drawable);
			// 0x10819520: releases an attached drawable (given by value)
			void ReleaseAttachedDrawable(AttachedDrawable attached);
			// 0x1081B730: fades out the effect of a handle over a time and stops it
			void StopEffect(int effect, float fadeTime);
			// 0x1081BA90: starts a motion trail on a drawable between the joints of its part lookup; the trail comes back
			// as a drawable (the object's drawable and part lookup, the times, the names of the joints and the offsets
			// on them, the shrink and the texture values)
			Drawable CreateMotionTrail(Drawable drawable, proto::PartLookup* lookup, float generateTime, float fadeInTime,
				float fadeOutTime, const EffectName* shader, const EffectName* joints, const math::Vector* offsets,
				int numJoints, const EffectName* shrinkJoint, math::Vector shrinkOffset, float shrinkTime, float fadeTime,
				float fadeInTrailTime, float textureTime, bool dragged);
			// 0x1081E260: stops the effects started on a slot, fading them out when allowed
			void AbortSlot(const EffectName* slot, bool allowFade, float fadeTime);
			// 0x1081E320: ends every playing effect of a name, at once or by fading it out over a time
			void StopEffectsNamed(const EffectName& name, bool immediately, float fadeTime);
			// 0x1081D540: advances every playing effect and takes the finished ones out of their lists; the effects made
			// from a store that has not been used for a minute start fading
			void UpdateInstances(float timeStep);
			// 0x1081E1C0: ends the effects of a list whose position the camera cannot see (within the radius)
			void RemoveInvisible(EffectInstanceList* list, float radius);

			// 0x1081ABA0: whether a light at a transform is not worth making (it is out of the camera's view or farther
			// from it than the distance whose square is given; the object is not used)
			bool IsOutOfRange(const EffectLightSetup* setup, float radius, float maxDistanceSquared);

			// 0x1081ADC0: makes a light from a setup (switched off; the controller handle of the setup's light is kept)
			void AddLight(const EffectLightSetup* setup);

			// 0x1081A2A0: switches the particle systems of the stores on while they have users and off again when they
			// have not had one for a while
			void UpdateStores(float timeStep);

			// 0x1081CDE0: takes the store of a name out of the vector (the last one moves into its place)
			bool ReleaseStore(EffectName name);
			// 0x1081D790: ends an effect of a list: its store loses a user (or goes), the drawable is killed and the last
			// effect of the list takes its place
			void RemoveInstance(EffectInstance* instance, EffectInstanceList* list);

			// The list of playing effects of a key (an inline member; the engine's copy of Find is the lookup's)
			EffectInstanceList* GetList(const unsigned int* key);
			// 0x1081DC30: puts a new effect with a drawable in the list of its key (making room first)
			void AddInstance(unsigned int drawable, const EffectSetup* setup);
			// 0x1081E2F0: the same in the manager's heap
			void AddInstanceInHeap(unsigned int drawable, const EffectSetup* setup);
			// 0x1081CE70: makes an effect that is stretched between two points and adds it (when its list has room)
			Drawable CreateSpanEffect(SourceDrawable* source, const math::Vector* from, const math::Vector* to, float unused,
				unsigned int key);
			// 0x1081D470: the same for the drawable archetype of a name
			Drawable CreateSpanEffectNamed(const EffectName* archetype, const math::Vector* from, const math::Vector* to,
				float unused, unsigned int key);
			// 0x1081E390: makes the drawable of an effect from a source drawable and adds the effect
			Drawable CreateEffect(SourceDrawable* source, const EffectSetup* setup);
			// 0x1081DAF0: makes the drawable of an effect as an instance of the shared drawable of its store
			Drawable CreateEffectFromStore(SourceDrawable* source, Drawable store, const EffectSetup* setup);

			// 0x1081D850: ends the effect of a list that has run longest, one that was made from a store only when it
			// has no other; false when the list has none to end
			bool RemoveOldest(EffectInstanceList* list);
			// 0x1081DA10: ends the effect of the store that was used least recently
			void RemoveOldestStore();

			// 0x10819410: whether a feature of the manager is switched on (always)
			bool IsFeatureEnabled(int features);
			// 0x1081E5A0: the frame update (the two leading arguments are unused)
			void Update(int unused1, int unused2, float timeStep);
			// 0x1081E460: counts up the timers of the manager's name table and drops the ones that ran out
			void UpdateTimers(float timeStep);

			// 0x1081C8D0: destroys every light, drawable and effect the manager holds
			void Reset();

			// 0x1081B9B0: lets go of every attached drawable
			void ReleaseAttached();
			// 0x1081C260: moves the attached drawables to their game objects
			void UpdateAttachedTransforms(float timeStep);

			// 0x1081BCE0: ages the lights, fades and flickers them and moves them to their objects; a light whose time
			// is up or whose object is gone is destroyed
			void UpdateLights(float timeStep);

			// 0x1081AF90: lets go of the waiting drawables that are finished or whose owner is gone
			void ReleaseFinishedWaiting(float timeStep);

			// 0x1081B3F0: the playing effect of a drawable, with the list it is in
			EffectInstance* FindInstance(unsigned int drawable, EffectInstanceList** list);

			// 0x1081B4E0: the playing effect of a name
			EffectInstance* FindInstanceByName(const EffectName& name, EffectInstanceList** list);

			// The public calls on a playing effect by the handle of its drawable (0x1081B700 - 0x1081B990)
			bool SetEffectName(unsigned int effect, const EffectName& name);
			void SetParticleBias(unsigned int effect, core::Name<core::CaseInsensitiveKey32> name, float value);
			void SetParticleFloat(unsigned int effect, core::Name<core::CaseInsensitiveKey32> name, float value);
			void SetGeneratorFloat2(unsigned int effect, core::Name<core::CaseInsensitiveKey32> name, float value);
			void SetGeneratorFloat3(unsigned int effect, core::Name<core::CaseInsensitiveKey32> name, float value);
			void SetParticleUnknownE50(unsigned int effect, float value);
			void SetParticleUnknownE70(unsigned int effect, float value);
			void SetParticleUnknownE40(unsigned int effect, bool value);
			void SetParticleUnknown49C(unsigned int effect, float value);
			void SetEffectTransform(unsigned int effect, const math::Matrix& transform);
			void SetEffectPosition(unsigned int effect, const math::Vector& position);
			// 0x1081B5D0: stretches the effect between two points (z of its transform runs from the first to the second)
			void SetEffectSpan(unsigned int effect, const math::Vector* from, const math::Vector* to, float unused);

			// 0x1081CBB0: starts a drawable that follows a game object (nothing when the camera cannot see it or too many
			// were started this frame)
			Drawable CreateAttached(const AttachedEffectSetup* setup);

			// 0x1081A000: forgets a light that is about to go away in the lights that follow it
			void ClearLightReferences(Light light);

			// The inventories the manager finds shaders in, and the shader it falls back on
			content::LoadInventory* inventory;  // +0x00
			content::LoadInventory* secondInventory;  // +0x04
			pure3d::Shader* defaultShader;  // +0x08
			// The time the manager has run for
			float time;  // +0xC
			// The heap the manager allocates its records from
			int heap;  // +0x10
			// The heap the attached drawables are made in
			int attachedHeap;  // +0x14
			// A function the manager calls (with its argument) when it is reset
			void (*resetCallback)(int);  // +0x18
			int resetCallbackArgument;  // +0x1C
			// A function the manager calls with the handle and the setup of an effect it has started
			void (*startCallback)(unsigned int, void*);  // +0x20
			int unknown24;
			bool unknown28;
			unsigned char unknown29[3];
			// The lists of playing effects by the key of their kind
			HashTable instanceTable;  // +0x2C
			// Where the loops over the effects of every name stand
			HashIterator<EffectInstanceList> instanceLists;  // +0x54
			// The drawables of effects that are waiting for their end
			DrawableRing waiting;  // +0x5C
			int unknown6C;
			// The rings of attached drawables by the key of their owner
			HashTable attachedTable;  // +0x70
			// Where the loops over the rings of attached drawables stand
			HashIterator<AttachedRing> attachedRings;  // +0x98
			unsigned char unknownA0[0x28];
			// The effects started on slots: a vector of records (begin, end, end of storage)
			SlotEffect* slotsBegin;  // +0xC8
			SlotEffect* slotsEnd;  // +0xCC
			SlotEffect* slotsCapacity;  // +0xD0
			// The stores of ready effects (a vector: begin, end, end of storage) and the one the loops are at
			EffectStore* storesBegin;  // +0xD4
			EffectStore* storesEnd;  // +0xD8
			EffectStore* storesCapacity;  // +0xDC
			int unknownE0;
			EffectStore* storeCursor;  // +0xE4
			// The lights the manager keeps (a vector: begin, end, end of storage)
			EffectLight* lightsBegin;  // +0xE8
			EffectLight* lightsEnd;  // +0xEC
			EffectLight* lightsCapacity;  // +0xF0
			int unknownF4;
			// How many attached drawables may be started in a frame, and how many have been
			unsigned int startLimit;  // +0xF8
			unsigned int startedThisFrame;  // +0xFC
		};

		// 0x108BE4A0 (the motion trail unit): makes the drawable of a trail (the drawable it follows, the times, the shader,
		// the joint indices of the part lookup, their offsets and their number, the index of the shrink joint and
		// its offset, and the shrink, fade, texture times and the dragging flag)
		Drawable CreateTrail(Drawable drawable, float generateTime, float fadeInTime, float fadeOutTime,
			pure3d::Shader* shader, const int* joints, const math::Vector* offsets, int numJoints, int shrinkJoint,
			math::Vector shrinkOffset, float shrinkTime, float fadeTime, float fadeInTrailTime, float textureTime,
			bool dragged);

		// 0x1084A770 (another unit): makes the drawable of an attached effect (the shader, the values of the setup and the
		// drawable of the object it follows)
		Drawable CreateAttachedDrawable(pure3d::Shader* shader, int unknown8, const math::Vector* position,
			const math::Vector* unknown18, const float* unknown24, float unknown30, Drawable owner, float unknown34,
			float unknown38);

		// 0x108193A0: the global manager
		EffectManager* GetEffectManager();
		// 0x108193D0: the camera of the first player that is active, null without a camera director
		camera::Camera* GetActiveCamera();
	}
}

#endif
