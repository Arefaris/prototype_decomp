// The effect manager (see effectmanager.h).
#include "code/engine/render/effectmanager.h"
#include <float.h>
#include <math.h>
#include <new>
#include "code/engine/camera/cinematographer.h"
#include "code/engine/camera/director.h"
#include "code/pure3d/primitive.h"
#include "code/engine/fight/effecttrack.h"
#include "code/core/heap.h"
#include "code/math/colour128.h"
#include "code/math/mathutils.h"
#include "code/math/noise.h"

namespace engine
{
	namespace render
	{
		// The global manager (0x1130CCE0)
		extern EffectManager* gEffectManager;

		// FUNCTION: ENGINE 0x108193A0
		EffectManager* GetEffectManager()
		{
			return gEffectManager;
		}

		// FUNCTION: ENGINE 0x1081A120
		EffectLight::EffectLight()
			: light(Light::NoLight()), colour(1.0f, 1.0f, 1.0f, 1.0f), secondColour(1.0f, 1.0f, 1.0f, 1.0f), unknown24(0.0f), delay(0.0f), holdTime(0.0f), fallTime(0.0f), riseTime(0.0f),
			age(0.0f), unknown3C(0.0f), flickerAmount(0.0f), unknown44(0.0f), unknown48(0.0f), unknown4C(0.0f),
			unknown50(0.0f), unknown54(0.0f), unknown58(0.0f), offset(math::Matrix::IDENTITY)
		{
			attached = false;
		}

		// FUNCTION: ENGINE 0x10819430
		EffectLight& EffectLight::operator=(const EffectLight& other)
		{
			light = other.light;
			colour = other.colour;
			secondColour = other.secondColour;
			unknown24 = other.unknown24;
			delay = other.delay;
			holdTime = other.holdTime;
			fallTime = other.fallTime;
			riseTime = other.riseTime;
			age = other.age;
			unknown3C = other.unknown3C;
			flickerAmount = other.flickerAmount;
			unknown44 = other.unknown44;
			unknown48 = other.unknown48;
			unknown4C = other.unknown4C;
			unknown50 = other.unknown50;
			unknown54 = other.unknown54;
			unknown58 = other.unknown58;
			target = other.target;
			joint = other.joint;
			offset = other.offset;
			attached = other.attached;
			return *this;
		}
		// FUNCTION: ENGINE 0x1081A2A0
		void EffectManager::UpdateStores(float timeStep)
		{
			storeCursor = storesBegin;
			if (storesBegin != storesEnd)
			{
				do
				{
					EffectStore* store = storeCursor;
					if (store->users != 0)
					{
						if (!store->active)
						{
							store->drawable.SetParticleUnknown4B8(true);
							store->active = true;
						}
						store->lastUsed = time;
					}
					else if (store->active && time - store->lastUsed > 5.0f)
					{
						store->drawable.SetParticleUnknown4B8(false);
						store->active = false;
					}
					storeCursor = storeCursor + 1;
				}
				while (storeCursor != storesEnd);
			}
		}

		// FUNCTION: ENGINE 0x1081A000
		// EQUIVALENT: the same loop over the lights (unrolled by four) with the same tests and stores; the engine keeps the
		// index in ebx and a spilled count in another stack slot (82.4 %)
		void EffectManager::ClearLightReferences(Light light)
		{
			if (light.IsValid())
			{
				int count = lightsEnd - lightsBegin;
				for (unsigned int i = 0; i < count; i++)
				{
					EffectLight* item = &lightsBegin[i];
					if (item->light.handle.mHandle == light.handle.mHandle)
					{
						item->age = 0.0f;
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x108193D0
		camera::Camera* GetActiveCamera()
		{
			camera::Director* director = camera::Director::Get();
			if (director == 0)
			{
				return 0;
			}
			int index = director->playerCamera[0];
			if (index < 0)
			{
				if (!director->NextActiveCamera(&index, 0))
				{
					return 0;
				}
			}
			return (camera::Camera*)director->GetCameraUnknown40(index, 0);
		}

		// FUNCTION: ENGINE 0x1081ABA0
		bool EffectManager::IsOutOfRange(const EffectLightSetup* setup, float radius, float maxDistanceSquared)
		{
			camera::Camera* camera = GetActiveCamera();
			if (camera != 0)
			{
				math::Matrix matrix(setup->transform);
				if (setup->target.IsValid())
				{
					GameObject* object = setup->target.Get();
					if (object != 0)
					{
						if (!setup->partName.IsEmpty())
						{
							AttributePtr<proto::PartLookup*> attribute = object->GetAttributePtr<proto::PartLookup*>(proto::gDrawableAttributeName);
							if (attribute.value != 0)
							{
								proto::PartLookup* lookup = *attribute.value;
								if (lookup != 0)
								{
									int part = lookup->FindPart(setup->partName);
									matrix.Multiply(matrix, lookup->matrices[part]);
								}
							}
						}
						matrix.Multiply(matrix, object->transform->value);
					}
				}
				math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
				if (!camera->IsPointVisible(&position, radius))
				{
					return true;
				}
				math::Vector cameraPosition = camera->position;
				math::Vector delta;
				delta.Sub(position, cameraPosition);
				if (delta.Dot(delta) > maxDistanceSquared)
				{
					return true;
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x1081ADC0
		void EffectManager::AddLight(const EffectLightSetup* setup)
		{
			core::HeapScope scope(heap);
			EffectLight* light;
			if (lightsEnd < lightsCapacity)
			{
				EffectLight* slot = lightsEnd++;
				if (slot != 0)
				{
					light = new (slot) EffectLight();
				}
				else
				{
					light = 0;
				}
			}
			else
			{
				light = 0;
			}
			light->light = setup->light;
			light->holdTime = setup->holdTime;
			light->delay = setup->delay;
			light->fallTime = setup->fallTime;
			light->riseTime = setup->riseTime;
			light->age = setup->fallTime + setup->delay + setup->holdTime + setup->riseTime;
			light->colour = setup->colour;
			light->secondColour = setup->secondColour;
			light->unknown24 = setup->unknown74;
			light->unknown3C = setup->unknown88;
			light->flickerAmount = setup->unknown8C;
			light->unknown44 = setup->unknown90;
			light->unknown48 = setup->unknown94;
			light->unknown4C = setup->unknown98;
			light->unknown50 = setup->unknown9C;
			light->unknown54 = setup->unknownA0;
			light->unknown58 = setup->unknownA4;
			light->target = setup->target;
			light->joint = 0xffff;
			if (!setup->partName.IsEmpty())
			{
				GameObject* object = light->target.Get();
				if (object != 0)
				{
					Attribute<proto::PartLookup*>* attribute = (Attribute<proto::PartLookup*>*)object->FindAttribute(proto::gDrawableAttributeName);
					if (attribute != 0)
					{
						proto::PartLookup** parts = &attribute->value;
						if (parts != 0 && *parts != 0)
						{
							light->joint = (*parts)->FindPart(setup->partName);
						}
					}
				}
			}
			light->offset = setup->transform;
			light->attached = setup->target.Get() != 0;
			light->light.SetActive(false);
		}

		// FUNCTION: ENGINE 0x10819550
		DrawableLink::DrawableLink()
		{
		}

		// FUNCTION: ENGINE 0x1081AF90
		void EffectManager::ReleaseFinishedWaiting(float timeStep)
		{
			for (unsigned int i = 0; i < waiting.Size(); i++)
			{
				Drawable drawable = waiting.At(i).drawable;
				if (drawable.IsValid())
				{
					if (drawable.IsFinished() || !waiting.At(i).owner.IsValid())
					{
						Drawable::Destroy(&drawable, 0);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x1081B3F0
		EffectInstance* EffectManager::FindInstance(unsigned int drawable, EffectInstanceList** list)
		{
			HashIterator<EffectInstanceList>& iterator = instanceLists;
			iterator.index = 0xffffffff;
			EffectInstanceList* current = iterator.NextCalled();
			while (current != 0)
			{
				for (unsigned int i = 0; i < current->Size(); i++)
				{
					EffectInstance* instance = &current->begin[i];
					if (instance->drawable.mHandle == drawable && instance->drawable.IsValid())					{
						if (list != 0)
						{
							*list = current;
						}
						return instance;
					}
				}
				current = iterator.Next();
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1081B4E0
		EffectInstance* EffectManager::FindInstanceByName(const EffectName& name, EffectInstanceList** list)
		{
			HashIterator<EffectInstanceList>& iterator = instanceLists;
			iterator.index = 0xffffffff;
			EffectInstanceList* current = iterator.NextCalled();
			while (current != 0)
			{
				for (unsigned int i = 0; i < current->Size(); i++)
				{
					EffectInstance* instance = &current->begin[i];
					if (instance->name == name && instance->drawable.IsValid())
					{
						if (list != 0)
						{
							*list = current;
						}
						return instance;
					}
				}
				current = iterator.Next();
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1081B5D0
		// EQUIVALENT: the same differences, the same sum of squares ((x * x + y * y) + z * z; the first two terms swap) and the
		// same calls; the engine schedules the loads and the first products differently (87.0 %)
		void EffectManager::SetEffectSpan(unsigned int effect, const math::Vector* from, const math::Vector* to, int unused)
		{
			EffectInstance* instance = FindInstance(effect, 0);
			if (instance != 0)
			{
				math::Vector direction;
				direction.Sub(*to, *from);
				float lengthSquared = (direction.x * direction.x + direction.y * direction.y) + direction.z * direction.z;
				direction.NormalizeFast();
				math::Matrix basis;
				basis.Identity();
				math::Vector up(0.0f, 1.0f, 0.0f);
				basis.SetBasis(direction, up);
				basis.SetTranslation(*from);
				math::Matrix scale;
				scale.Identity();
				scale.Scale(1.0f, 1.0f, sqrtf(lengthSquared));
				scale.Multiply(scale, basis);
				instance->transform = scale;
				instance->flags |= 1;
				instance->unknown6C = 1000.0f;
			}
		}

		// FUNCTION: ENGINE 0x1081B700
		bool EffectManager::SetEffectName(unsigned int effect, const EffectName& name)
		{
			EffectInstance* instance = FindInstance(effect, 0);
			if (instance != 0)
			{
				instance->name = name;
				return true;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x1081B730
		void EffectManager::StopEffect(int effect, float fadeTime)
		{
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(effect, &list);
			if (instance != 0)
			{
				instance->fadeTime = fadeTime;
				instance->StartFade();
			}
		}

		// FUNCTION: ENGINE 0x1081B760
		void EffectManager::SetParticleBias(unsigned int effect, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(effect, &list);
			if (instance != 0)
			{
				instance->drawable.SetParticleBias(name, value);
			}
		}

		// FUNCTION: ENGINE 0x1081B7A0
		void EffectManager::SetParticleFloat(unsigned int effect, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(effect, &list);
			if (instance != 0)
			{
				instance->drawable.SetParticleFloat(name, value);
			}
		}

		// FUNCTION: ENGINE 0x1081B7E0
		void EffectManager::SetGeneratorFloat2(unsigned int effect, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(effect, &list);
			if (instance != 0)
			{
				instance->drawable.SetGeneratorFloat2(name, value);
			}
		}

		// FUNCTION: ENGINE 0x1081B820
		void EffectManager::SetGeneratorFloat3(unsigned int effect, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(effect, &list);
			if (instance != 0)
			{
				instance->drawable.SetGeneratorFloat3(name, value);
			}
		}

		// FUNCTION: ENGINE 0x1081B860
		void EffectManager::SetParticleUnknownE50(unsigned int effect, float value)
		{
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(effect, &list);
			if (instance != 0)
			{
				instance->drawable.SetParticleUnknownE50(value);
			}
		}

		// FUNCTION: ENGINE 0x1081B890
		void EffectManager::SetParticleUnknownE70(unsigned int effect, float value)
		{
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(effect, &list);
			if (instance != 0)
			{
				instance->drawable.SetParticleUnknownE70(value);
			}
		}

		// FUNCTION: ENGINE 0x1081B8C0
		void EffectManager::SetParticleUnknownE40(unsigned int effect, bool value)
		{
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(effect, &list);
			if (instance != 0)
			{
				instance->drawable.SetParticleUnknownE40(value);
			}
		}

		// FUNCTION: ENGINE 0x1081B8F0
		void EffectManager::SetParticleUnknown49C(unsigned int effect, float value)
		{
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(effect, &list);
			if (instance != 0)
			{
				instance->drawable.SetParticleUnknown49C(value);
			}
		}

		// FUNCTION: ENGINE 0x1081B920
		void EffectManager::SetEffectTransform(unsigned int effect, const math::Matrix& transform)
		{
			EffectInstance* instance = FindInstance(effect, 0);
			if (instance != 0)
			{
				instance->transform = transform;
				math::Vector translation;
				transform.GetTranslation(translation);
				instance->position.Set(translation.x, translation.y, translation.z);
				instance->flags |= 1;
			}
		}

		// FUNCTION: ENGINE 0x1081B970
		// EQUIVALENT: the same stores in the same order; the engine finishes the last coordinate's store after the flag's
		// or (82.3 %)
		void EffectManager::SetEffectPosition(unsigned int effect, const math::Vector& position)
		{
			EffectInstance* instance = FindInstance(effect, 0);
			if (instance != 0)
			{
				instance->transform.SetTranslation(position);
				instance->position.x = position.x;
				instance->position.y = position.y;
				instance->position.z = position.z;
				instance->flags |= 1;
			}
		}

		// FUNCTION: ENGINE 0x10819500
		AttachedDrawable::AttachedDrawable()
		{
		}

		// FUNCTION: ENGINE 0x1081B9B0
		// EQUIVALENT: the same walk, the same destroys and stores; the engine keeps the manager in a stack slot over the
		// loop and stores the empty ring pointer it ends with, ours keeps it in a register (78.5 %)
		void EffectManager::ReleaseAttached()
		{
			HashIterator<AttachedRing>& iterator = attachedRings;
			iterator.index = 0xffffffff;
			AttachedRing* ring = iterator.NextCalled();
			while (ring != 0)
			{
				for (unsigned int i = 0; i < ring->Size(); i++)
				{
					Drawable::Destroy(&ring->At(i).drawable, 0);
				}
				ring->head = ring->begin;
				ring->tail = ring->begin;
				ring = iterator.Next();
			}
			unknownFC = 0;
		}

		// FUNCTION: ENGINE 0x10819520
		void EffectManager::ReleaseAttachedDrawable(AttachedDrawable attached)
		{
			Drawable::Destroy(&attached.drawable, 0);
		}

		// FUNCTION: ENGINE 0x1081EAC0
		void EffectInstance::Kill()
		{
			Drawable::Destroy(&drawable, 4);
			flags |= 2;
			timeLeft = FLT_MAX;
		}

		// FUNCTION: ENGINE 0x10819A40
		void* HashIteratorBase::NextCalled()
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

		// FUNCTION: ENGINE 0x1081A890
		void* HashLookup::Find(const unsigned int* newKey)
		{
			key = *newKey;
			HashTable* source = table;
			unsigned __int64 wide = *newKey;
			unsigned int mask = source->slotCount - 1;
			unsigned int current = (unsigned int)wide & mask;
			unsigned int increment = ((unsigned int)(wide >> 9) & 0xfe) | 1;
			start = current;
			step = increment;
			void* value;
			while (value = source->slots[current], (value != 0 && source->keys[current] != key) || value == (void*)source->removedMarker)
			{
				current = (current + increment) & (source->slotCount - 1);
				if (current == start)
				{
					slot = current;
					return 0;
				}
			}
			slot = current;
			return source->slots[current];
		}

		// FUNCTION: ENGINE 0x1081A910
		// EQUIVALENT: the same probe, tests and stores; the engine reads the table's slot array again for the loop test, ours
		// keeps the pointer it loaded before (71.1 %)
		void* HashLookup::FindForInsert(const unsigned int* newKey)
		{
			key = *newKey;
			HashTable* source = table;
			unsigned __int64 wide = *newKey;
			unsigned int mask = source->slotCount - 1;
			unsigned int current = (unsigned int)wide & mask;
			unsigned int increment = ((unsigned int)(wide >> 9) & 0xfe) | 1;
			start = current;
			step = increment;
			void** values = source->slots;
			if (values[current] != 0)
			{
				do
				{
					if (source->keys[current] == key || values[current] == (void*)source->removedMarker)
					{
						break;
					}
					current = (current + increment) & (source->slotCount - 1);
					if (current == start)
					{
						slot = current;
						return 0;
					}
				}
				while (source->slots[current] != 0);
			}
			slot = current;
			return source->slots[current];
		}

		// FUNCTION: ENGINE 0x10819C30
		// EQUIVALENT: the same probe; the engine keeps the table's mask in edi and the slot array in ebx, ours spills the mask
		// and reloads the slot value into another register (16.8 %)
		void* HashLookup::Next()
		{
			HashTable* source = table;
			unsigned int mask = source->slotCount - 1;
			unsigned int current = (slot + step) & mask;
			while (source->slots[current] != 0 && source->keys[current] != key && source->slots[current] != (void*)source->removedMarker)
			{
				if (current == start)
				{
					slot = current;
					return 0;
				}
				current = (current + step) & (source->slotCount - 1);
			}
			slot = current;
			return source->slots[current];
		}

		// FUNCTION: ENGINE 0x1081C620
		// EQUIVALENT: the same lookup, stores and growth test; the engine reaches the slot address with one lea and keeps
		// the key pointer in ebx, ours adds the index twice (51.7 %)
		void HashTable::Insert(const unsigned int* newKey, void* value)
		{
			HashLookup lookup(this);
			void* found = lookup.FindForInsert(newKey);
			while (found != 0 && found != (void*)lookup.table->removedMarker)
			{
				found = lookup.Next();
			}
			unsigned int slot = lookup.slot;
			void** place = &slots[slot];
			if (*place == (void*)removedMarker)
			{
				removed--;
			}
			*place = value;
			keys[slot] = *newKey;
			count++;
			if (count * 100 / slotCount > maxLoad)
			{
				Rehash(slotCount * 2);
			}
		}

		// FUNCTION: ENGINE 0x1081C6C0
		void HashTable::Rehash(unsigned int newSlotCount)
		{
			core::HeapScope scope(heap);
			unsigned int oldCount = slotCount;
			void** oldSlots = slots;
			unsigned int* oldKeys = keys;
			slotCount = newSlotCount;
			slots = new void*[slotCount];
			keys = new unsigned int[slotCount];
			removed = 0;
			count = 0;
			for (unsigned int i = 0; i < slotCount; i++)
			{
				slots[i] = 0;
				keys[i] = 0;
			}
			if (oldSlots != 0)
			{
				for (unsigned int i = 0; i < oldCount; i++)
				{
					if (oldSlots[i] != 0 && oldSlots[i] != (void*)removedMarker)
					{
						Insert(&oldKeys[i], oldSlots[i]);
					}
				}
				delete[] oldSlots;
				delete[] oldKeys;
			}
		}

		// FUNCTION: ENGINE 0x1081D170
		// EQUIVALENT: the same stores and rounding; the engine materialises the power-of-two test as a byte first (51.5 %)
		HashTable::HashTable(unsigned int newSlotCount, unsigned int newMaxLoad, unsigned int newMaxRemoved)
		{
			maxRemoved = newMaxRemoved;
			slotCount = newSlotCount;
			count = 0;
			removed = 0;
			compactWhenRemoved = false;
			maxLoad = newMaxLoad;
			slots = 0;
			keys = 0;
			*(unsigned int*)removedMarker = 0;
			if (newSlotCount > 0)
			{
				bool isPowerOfTwo = (newSlotCount & (newSlotCount - 1)) == 0;
				if (isPowerOfTwo == false)
				{
					newSlotCount = 1 << (math::Log2(newSlotCount) + 1);
				}
				slotCount = newSlotCount;
			}
			heap = core::GetCurrentHeap();
			Rehash(slotCount);
		}

		// FUNCTION: ENGINE 0x1081CDE0
		// EQUIVALENT: the same walk, comparison and field copies in the same order; the engine keeps the cursor in edi and
		// stores it before the end test, and schedules the drawable copy after the name's address (47.4 %)
		bool EffectManager::ReleaseStore(EffectName name)
		{
			storeCursor = storesBegin;
			if (storesBegin != storesEnd)
			{
				do
				{
					EffectStore* store = storeCursor;
					if (name == store->name)
					{
						storesEnd--;
						EffectStore* last = storesEnd;
						if (store < last)
						{
							store->drawable = last->drawable;
							store->name = last->name;
							store->users = last->users;
							store->lastUsed = last->lastUsed;
							store->active = last->active;
						}
						return true;
					}
					storeCursor = store + 1;
				}
				while (storeCursor != storesEnd);
			}
			return false;
		}

		// FUNCTION: ENGINE 0x1081D790
		// EQUIVALENT: the same walk, calls and stores; the engine keeps the store cursor in edi and stores it before the end
		// test, ours computes the next address first (57.7 %)
		void EffectManager::RemoveInstance(EffectInstance* instance, EffectInstanceList* list)
		{
			if ((instance->flags & 0x20) != 0)
			{
				storeCursor = storesBegin;
				if (storesBegin != storesEnd)
				{
					do
					{
						EffectStore* store = storeCursor;
						EffectName key(instance->storeName);
						if (key == store->name)
						{
							store->users--;
							break;
						}
						storeCursor = store + 1;
					}
					while (storeCursor != storesEnd);
				}
			}
			else if ((instance->flags & 0x40) != 0)
			{
				ReleaseStore(EffectName(instance->storeName));
			}
			instance->Kill();
			list->end--;
			if (instance < list->end)
			{
				*instance = *list->end;
			}
			list->end->~EffectInstance();
		}

		// FUNCTION: ENGINE 0x1081D850
		// EQUIVALENT: the same loop (unrolled by four) with the same tests, stores and calls; the engine walks one pointer
		// over the unrolled body and keeps the two indices in registers, ours keeps two pointers and spills the stored
		// index (22.4 %)
		bool EffectManager::RemoveOldest(EffectInstanceList* list)
		{
			float oldestPlain = 0.0f;
			unsigned int plainIndex = 0xffffffff;
			unsigned int storedIndex = 0;
			float oldestStored = 0.0f;
			unsigned int count = list->Size();
			for (unsigned int i = 0; i < count; i++)
			{
				float timeLeft = list->begin[i].timeLeft;
				EffectInstance* instance = &list->begin[i];
				if ((instance->flags & 0x40) != 0)
				{
					if (timeLeft > oldestStored)
					{
						storedIndex = i;
						oldestStored = timeLeft;
					}
				}
				else if (timeLeft > oldestPlain)
				{
					plainIndex = i;
					oldestPlain = timeLeft;
				}
			}
			if (plainIndex == 0xffffffff)
			{
				EffectInstance* instance = &list->begin[storedIndex];
				if (instance->drawable.IsValid())
				{
					RemoveInstance(instance, list);
					return true;
				}
			}
			else
			{
				EffectInstance* instance = &list->begin[plainIndex];
				if (instance->drawable.IsValid())
				{
					RemoveInstance(instance, list);
					return true;
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x1081DA10
		// EQUIVALENT: the same two scans, tests and calls; the engine reads the end of the vector again in every loop test
		// and keeps the counts in registers, ours reads it once (13.6 %)
		void EffectManager::RemoveOldestStore()
		{
			float oldest = time;
			unsigned int index = 0;
			int ties = 0;
			unsigned int i = 0;
			if (storesEnd - storesBegin != 0)
			{
				EffectStore* first = storesBegin;
				do
				{
					float lastUsed = first[i].lastUsed;
					if (lastUsed < oldest)
					{
						ties = 0;
						index = i;
						oldest = lastUsed;
					}
					else if (lastUsed == oldest)
					{
						ties++;
					}
					i++;
				}
				while (i < (unsigned int)(storesEnd - first));
				if (ties != 0)
				{
					i = 0;
					if (storesEnd - first != 0)
					{
						do
						{
							if (first[i].lastUsed == oldest && first[i].users != 0xffffffff)
							{
								index = i;
							}
							i++;
						}
						while (i < (unsigned int)(storesEnd - first));
					}
				}
			}
			EffectInstanceList* list;
			EffectInstance* instance = FindInstance(storesBegin[index].drawable.mHandle, &list);
			if (instance != 0)
			{
				RemoveInstance(instance, list);
			}
		}

		// FUNCTION: ENGINE 0x1081EAB0
		bool EffectInstance::IsEmitting() const
		{
			return emitState != 0;
		}

		// FUNCTION: ENGINE 0x1081EB10
		// EQUIVALENT: the same state tests, stores and calls; the engine joins the two early exits of the state test at one
		// return, ours returns at each (24.8 %)
		void EffectInstance::SetEmitting(bool emitting, float fadeTime)
		{
			bool done;
			if (emitting)
			{
				done = emitState == 2 || emitState == 3;
			}
			else
			{
				done = emitState == 0 || emitState == 1;
			}
			if (!done)
			{
				emitTime = fadeTime;
				emitLeft = fadeTime - emitLeft;
				if (fadeTime == 0.0f)
				{
					emitState = emitting ? 2 : 0;
					drawable.SetParticleUnknown4B8(emitting);
					drawable.SetParticleFade(emitting ? 1.0f : 0.0f);
					emitLeft = 0.0f;
					emitTime = 0.0f;
				}
				else if (emitting)
				{
					emitState = 3;
					drawable.SetParticleUnknown4B8(true);
				}
				else
				{
					emitState = 1;
				}
			}
		}

		// FUNCTION: ENGINE 0x1081EC00
		void EffectInstance::SetStoreDrawable(const Drawable* store)
		{
			storeDrawable = *store;
			usesStore = store->IsValid();
		}

		// FUNCTION: ENGINE 0x1081EEF0
		// EQUIVALENT: the same tests, calls and scan of the records; the engine keeps the constant 2 of the flag test in ebx and
		// loads the effect handle before the stack argument is reserved (38.7 %)
		void EffectInstance::StartFade()
		{
			if ((flags & 2) == 0)
			{
				if (drawable.IsValid())
				{
					drawable.ResetParticles();
				}
				unknown6C = fadeTime;
				flags |= 2;
				EffectManager* manager = GetEffectManager();
				for (int i = 0; i < lodCount; i++)
				{
					if (lodsBegin[i]->kind == EFFECT_LOD_SWITCH)
					{
						manager->StopEffect(((EffectLODSwitch*)lodsBegin[i])->effect, 0.0f);
						break;
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x1081D540
		// EQUIVALENT: the same walks, tests, calls and stores; the engine keeps the loop's offset and counter in other stack
		// slots and the store cursor in a register over the loops (52.2 %)
		void EffectManager::UpdateInstances(float timeStep)
		{
			camera::Camera* camera = GetActiveCamera();
			if (camera == 0)
			{
				return;
			}
			math::Vector cameraPosition;
			cameraPosition.Set(camera->position.x, camera->position.y, camera->position.z);
			HashIterator<EffectInstanceList>& iterator = instanceLists;
			iterator.index = 0xffffffff;
			EffectInstanceList* list = iterator.NextCalled();
			while (list != 0)
			{
				for (unsigned int i = 0; i < list->Size(); i++)
				{
					EffectInstance* instance = &list->begin[i];
					if ((instance->flags & 0x40) != 0)
					{
						storeCursor = storesBegin;
						if (storesBegin != storesEnd)
						{
							do
							{
								EffectName key(instance->storeName);
								if (key == storeCursor->name)
								{
									if (time - storeCursor->lastUsed > 60.0f)
									{
										instance->StartFade();
									}
								}
								storeCursor++;
							}
							while (storeCursor != storesEnd);
						}
					}
					if (instance->Advance(timeStep, &cameraPosition))
					{
						if ((instance->flags & 0x20) != 0)
						{
							storeCursor = storesBegin;
							if (storesBegin != storesEnd)
							{
								do
								{
									EffectStore* store = storeCursor;
									EffectName key(instance->storeName);
									if (key == store->name)
									{
										store->users--;
										break;
									}
									storeCursor = store + 1;
								}
								while (storeCursor != storesEnd);
							}
						}
						else if ((instance->flags & 0x40) != 0)
						{
							ReleaseStore(EffectName(instance->storeName));
						}
						list->end--;
						if (instance < list->end)
						{
							*instance = *list->end;
						}
						list->end->~EffectInstance();
						i--;
					}
				}
				list = iterator.Next();
			}
		}

		// FUNCTION: ENGINE 0x10819410
		bool EffectManager::IsFeatureEnabled(int features)
		{
			return true;
		}

		// FUNCTION: ENGINE 0x1081E5A0
		void EffectManager::Update(int unused1, int unused2, float timeStep)
		{
			unknownFC = 0;
			time += timeStep;
			unknown28 = IsFeatureEnabled(0x40000) == false;
			pure3d::GetParticleManager()->SetUnknown19C(4.0f);
			camera::Director* director = camera::Director::Get();
			if (director != 0)
			{
				camera::Cinematographer* controller = director->GetCameraController(0, 0);
				if (controller != 0)
				{
					pure3d::GetParticleManager()->SetUnknown19C(*(float*)&controller->unknown28);
				}
			}
			unsigned int key = 6;
			HashLookup lookup(&instanceTable);
			RemoveInvisible((EffectInstanceList*)lookup.Find(&key), 1.0f);
			UpdateInstances(timeStep);
			ReleaseFinishedWaiting(timeStep);
			UpdateAttachedTransforms(timeStep);
			UpdateLights(timeStep);
			UpdateStores(timeStep);
			UpdateTimers(timeStep);
		}

		// FUNCTION: ENGINE 0x1081E1C0
		void EffectManager::RemoveInvisible(EffectInstanceList* list, float radius)
		{
			camera::Camera* camera = GetActiveCamera();
			if (camera != 0)
			{
				for (unsigned int i = 0; i < list->Size(); i++)
				{
					EffectInstance* instance = &list->begin[i];
					if (!camera->IsPointVisible(&instance->position, radius))
					{
						RemoveInstance(instance, list);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x1081E260
		void EffectManager::AbortSlot(const EffectName* slot, bool allowFade, float fadeTime)
		{
			for (SlotEffect* effect = slotsBegin; effect != slotsEnd; effect++)
			{
				if (effect->drawable.IsValid() && effect->slot == *slot)
				{
					EffectInstanceList* list;
					EffectInstance* instance = FindInstance(effect->drawable.mHandle, &list);
					if (instance != 0)
					{
						if (allowFade)
						{
							StopEffect(effect->drawable.mHandle, fadeTime);
						}
						else
						{
							RemoveInstance(instance, list);
						}
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x1081E320
		void EffectManager::StopEffectsNamed(const EffectName& name, bool immediately, float fadeTime)
		{
			EffectInstanceList* list = 0;
			EffectInstance* instance = FindInstanceByName(name, &list);
			while (instance != 0)
			{
				if (immediately)
				{
					RemoveInstance(instance, list);
				}
				else
				{
					instance->fadeTime = fadeTime;
					instance->StartFade();
				}
				instance = FindInstanceByName(name, &list);
			}
		}

		// FUNCTION: ENGINE 0x1081C8D0
		// EQUIVALENT: the same loops, destroys and stores; the engine also loads the waiting ring's tail into a spare stack slot
		// that nothing reads (76.8 % with a volatile local that does the same, 39.3 % as written: two bytes shift the rest)
		void EffectManager::Reset()
		{
			for (unsigned int i = 0; i < (unsigned int)(lightsEnd - lightsBegin); i++)
			{
				Light::Destroy(&lightsBegin[i].light);
			}
			lightsEnd = lightsBegin;
			for (unsigned int i = 0; i < waiting.Size(); i++)
			{
				ReleaseDrawable(&waiting.At(i).drawable);
			}
			waiting.head = waiting.begin;
			waiting.tail = waiting.begin;
			HashIterator<AttachedRing>& rings = attachedRings;
			rings.index = 0xffffffff;
			AttachedRing* ring = rings.Next();
			while (ring != 0)
			{
				for (unsigned int i = 0; i < ring->Size(); i++)
				{
					ReleaseAttachedDrawable(ring->At(i));
				}
				ring->head = ring->begin;
				ring->tail = ring->begin;
				ring = rings.Next();
			}
			HashIterator<EffectInstanceList>& lists = instanceLists;
			lists.index = 0xffffffff;
			EffectInstanceList* list = lists.Next();
			while (list != 0)
			{
				for (unsigned int i = 0; i < list->Size(); i++)
				{
					list->begin[i].Kill();
				}
				EffectInstance* end = list->end;
				for (EffectInstance* instance = list->begin; instance != end; instance++)
				{
					instance->~EffectInstance();
				}
				list->end = list->begin;
				list = lists.Next();
			}
			unknownFC = 0;
			storesEnd = storesBegin;
			if (resetCallback != 0)
			{
				resetCallback(resetCallbackArgument);
			}
			unknown28 = false;
		}

		// FUNCTION: ENGINE 0x1081BCE0
		// NONMATCHING: the same calls and branches in the same order; the matrix copy is a four-times loop in the engine
		// (ours unrolls it, 24.8 %), the colour blend is scheduled as three passes over the four channels, the decay range
		// multiplies 0.5 into the wave before the amplitude, and the destroy test is kept as values (best 24.8 %)
#ifdef NONMATCHING
		void EffectManager::UpdateLights(float timeStep)
		{
			for (unsigned int i = 0; i < (unsigned int)(lightsEnd - lightsBegin); i++)
			{
				EffectLight* light = &lightsBegin[i];
				if (!light->light.IsValid())
				{
					continue;
				}
				float age = light->age - timeStep;
				light->age = age;
				bool expired = age <= 0.0f;
				expired |= light->attached && light->target.Get() == 0;
				bool inactive = light->attached && light->target.Get() != 0 && !light->target.Get()->behaviours.IsActive();
				if (inactive || expired)
				{
					Light::Destroy(&light->light);
					lightsEnd--;
					if (&lightsBegin[i] < lightsEnd)
					{
						lightsBegin[i] = *lightsEnd;
					}
					i--;
				}
				else if (age < light->holdTime + light->fallTime + light->riseTime)
				{
					math::Matrix transform;
					float strength;
					if (age < light->holdTime + light->fallTime)
					{
						strength = math::Clamp(age / light->fallTime, 0.0f, 1.0f);
					}
					else
					{
						strength = 1.0f - math::Clamp((age - (light->holdTime + light->fallTime)) / light->riseTime, 0.0f, 1.0f);
					}
					if (light->flickerAmount != 0.0f)
					{
						math::Noise noise;
						noise.SetSeed(0xdead);
						noise.SetOctaves(4);
						noise.SetFrequency(light->unknown4C, 1.0f, 1.0f);
						noise.SetPersistence(0.25f);
						float time = light->age;
						float noiseValue = noise.Evaluate(time, 1.0f, 1.0f) * light->unknown50;
						strength = (noiseValue + (sinf(light->unknown3C * time * 6.2831855f) + 1.0f) * 0.5f * light->flickerAmount) * strength;
					}
					if (light->unknown48 != 0.0f)
					{
						math::Noise noise;
						noise.SetSeed(0xf00d);
						noise.SetOctaves(4);
						noise.SetFrequency(light->unknown54, 1.0f, 1.0f);
						noise.SetPersistence(0.25f);
						float time = light->age;
						float noiseValue = noise.Evaluate(time, 1.0f, 1.0f) * light->unknown58;
						float range = noiseValue + (sinf(light->unknown44 * time * 6.2831855f) + 1.0f) * 0.5f * light->unknown48 + light->unknown24;
						light->light.SetDecayRanges(range * 0.5f, range);
					}
					float blend = light->age / (light->fallTime + light->riseTime + light->holdTime);
					math::Vector4 mixed((light->colour.x - light->secondColour.x) * blend + light->secondColour.x,
						(light->colour.y - light->secondColour.y) * blend + light->secondColour.y,
						(light->colour.z - light->secondColour.z) * blend + light->secondColour.z,
						(light->colour.w - light->secondColour.w) * blend + light->secondColour.w);
					light->light.SetActive(true);
					math::Colour128 colour(mixed.x * strength, mixed.y * strength, mixed.z * strength, mixed.w * strength);
					light->light.SetColour(colour);
					GameObject* owner = light->target.Get();
					for (int row = 0; row < 4; row++)
					{
						for (int column = 0; column < 4; column++)
						{
							transform.m[row][column] = light->offset.m[row][column];
						}
					}
					if (light->joint != 0xffff)
					{
						Attribute<proto::PartLookup*>* attribute = (Attribute<proto::PartLookup*>*)owner->FindAttribute(proto::gDrawableAttributeName);
						if (attribute != 0)
						{
							proto::PartLookup** parts = &attribute->value;
							if (parts != 0 && *parts != 0)
							{
								transform.Multiply(transform, (*parts)->matrices[light->joint]);
							}
						}
					}
					if (light->attached)
					{
						transform.Multiply(transform, owner->transform->value);
					}
					light->light.SetTransform(transform);
				}
				else
				{
					light->light.SetActive(false);
				}
			}
		}
#endif

		// FUNCTION: ENGINE 0x1081C260
		// NONMATCHING: the same walk and calls; the engine loads the master table once before the loop and again after
		// the queued call, ours inside the checks of every ring entry, 23.8 %
#ifdef NONMATCHING
		void EffectManager::UpdateAttachedTransforms(float timeStep)
		{
			HashIterator<AttachedRing>& iterator = attachedRings;
			iterator.index = 0xffffffff;
			AttachedRing* ring = iterator.NextCalled();
			while (ring != 0)
			{
				for (unsigned int i = 0; i < ring->Size(); i++)
				{
					AttachedDrawable& attached = ring->At(i);
					if (attached.owner.IsValid())
					{
						GameObject* object = attached.owner.Get();
						attached.drawable.SetTransformQueued(object->transform->value);
					}
				}
				ring = iterator.Next();
			}
		}
#endif

		// FUNCTION: ENGINE 0x1081B040
		EffectLightSetup::EffectLightSetup()
			: colour(1.0f, 1.0f, 1.0f, 1.0f), secondColour(1.0f, 1.0f, 1.0f, 1.0f), light(Light::NoLight()), unknown74(0.0f), delay(0.0f),
			riseTime(0.0f), holdTime(0.0f), fallTime(0.0f), unknown88(0.0f), unknown8C(0.0f), unknown90(0.0f), unknown94(0.0f),
			unknown98(0.0f), unknown9C(0.0f), unknownA0(0.0f), unknownA4(0.0f)
		{
		}

		// FUNCTION: ENGINE 0x1081EE00
		EffectPlacement::EffectPlacement() : transform(math::Matrix::IDENTITY)
		{
		}

	}
}
