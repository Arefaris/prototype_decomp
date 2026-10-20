// The manager of the effects the fight tracks start (the engine's global at 0x1130CCE0, read through 0x108193A0; no
// RTTI, so class and member names are guesses). It starts and stops the effect drawables and the motion trails the
// effect and motion trail actions ask for, keeps the effects it started per slot and fades the timed lights
// effects carry. The unit runs from 0x10819430 to the effect LOD classes at 0x1081EC30 - 0x1081FF60 (no assert path;
// the file name is a guess). Layouts are read off the code; the container classes of the engine's library are only
// declared with the members this unit calls (their bodies are other units' template instances).
#ifndef ENGINE_RENDER_EFFECTMANAGER_H
#define ENGINE_RENDER_EFFECTMANAGER_H

#include "code/core/name.h"
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

			DrawableLink* head;
			DrawableLink* tail;
			DrawableLink* begin;
			DrawableLink* end;
		};

		// A playing effect (0xA8 bytes; its constructors and destructor are another unit's 0x10820CF0 - 0x108213D0)
		struct EffectInstance
		{
			EffectInstance();
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

			int unknown0;
			math::Matrix transform;  // +0x04
			math::Vector position;  // +0x44
			Drawable drawable;  // +0x50
			unsigned char unknown54[0xC];
			EffectName name;  // +0x60
			unsigned char unknown68[4];
			// 1000 for a spanned effect
			float unknown6C;
			float fadeTime;  // +0x70
			// The time the effect has left (the largest float once it is killed)
			float timeLeft;  // +0x74
			unsigned char unknown78[0x9C - 0x78];
			// bit 0: the transform changed, bit 1: fading out, bit 5: counted as a user of the store it names, bit 6: made
			// from a store (the effect keeps the store alive)
			unsigned char flags;  // +0x9C
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
			void SetEffectSpan(unsigned int effect, const math::Vector* from, const math::Vector* to, int unused);

			// 0x1081A000: forgets a light that is about to go away in the lights that follow it
			void ClearLightReferences(Light light);

			unsigned char unknown0[0xC];
			// The time the manager has run for
			float time;  // +0xC
			// The heap the manager allocates its records from
			int heap;  // +0x10
			int unknown14;
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
			int unknownF8;
			unsigned int unknownFC;
		};

		// 0x108193A0: the global manager
		EffectManager* GetEffectManager();
		// 0x108193D0: the camera of the first player that is active, null without a camera director
		camera::Camera* GetActiveCamera();
	}
}

#endif
