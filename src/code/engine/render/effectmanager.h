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
			~EffectInstance();

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
			unsigned char unknown74[0x9C - 0x74];
			// bit 0: the transform changed, bit 1: fading out
			unsigned char flags;  // +0x9C
			unsigned char unknown9D[0xA8 - 0x9D];
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
		// place and the address of the table's last member for a removed one
		template<class Value> struct HashTable
		{
			unsigned int slotCount;  // +0x00
			unsigned int count;  // +0x04
			unsigned int removed;  // +0x08
			bool unknownC;
			unsigned int unknown10;
			unsigned int maxLoad;  // +0x14
			int heap;  // +0x18
			Value** slots;  // +0x1C
			unsigned int* keys;  // +0x20
			unsigned char removedMarker[4];  // +0x24
		};

		// Where a loop over a table stands (the table and the slot it is at)
		template<class Value> struct HashIterator
		{
			// Steps to the next used slot and answers its value, null at the end
			Value* Next()
			{
				HashTable<Value>* source = table;
				unsigned int slot = index;
				Value* value;
				do
				{
					slot++;
					if (slot >= source->slotCount)
					{
						break;
					}
					value = source->slots[slot];
				}
				while (value == 0 || (void*)value == (void*)source->removedMarker);
				index = slot;
				return slot >= source->slotCount ? 0 : source->slots[slot];
			}
			// The same step as a call (the engine's copy at 0x10819A40)
			Value* NextCalled();

			HashTable<Value>* table;
			unsigned int index;
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

			// 0x1081ABA0: whether a light at a transform is not worth making (it is out of the camera's view or farther
			// from it than the distance whose square is given; the object is not used)
			bool IsOutOfRange(const EffectLightSetup* setup, float radius, float maxDistanceSquared);

			// 0x1081ADC0: makes a light from a setup (switched off; the controller handle of the setup's light is kept)
			void AddLight(const EffectLightSetup* setup);

			// 0x1081A2A0: switches the particle systems of the stores on while they have users and off again when they
			// have not had one for a while
			void UpdateStores(float timeStep);

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
			unsigned char unknown14[0x40];
			// Where the loops over the effects of every name stand
			HashIterator<EffectInstanceList> instanceLists;  // +0x54
			// The drawables of effects that are waiting for their end
			DrawableRing waiting;  // +0x5C
			unsigned char unknown6C[0x2C];
			// Where the loops over the rings of attached drawables stand
			HashIterator<AttachedRing> attachedRings;  // +0x98
			unsigned char unknownA0[0x34];
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
