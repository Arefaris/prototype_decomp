// The effect manager (see effectmanager.h).
#include "code/engine/render/effectmanager.h"
#include <math.h>
#include <new>
#include "code/engine/camera/director.h"
#include "code/engine/fight/effecttrack.h"

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
		// EQUIVALENT: the same walk over the table and its lists with the same tests and calls; the compiler threads the
		// jump of the empty end of the inlined step to the exit and merges the three exits, the engine goes through a
		// result register first (see the percentage)
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
		// EQUIVALENT: as FindInstance, which it follows with the name of the instance as the test
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
		// loop and stores the empty ring pointer it ends with, ours keeps it in a register (64.2 %)
		void EffectManager::ReleaseAttached()
		{
			HashIterator<AttachedRing>& iterator = attachedRings;
			iterator.index = 0xffffffff;
			AttachedRing* ring = iterator.NextCalled();
			if (ring == 0)
			{
				unknownFC = 0;
				return;
			}
			do
			{
				for (unsigned int i = 0; i < ring->Size(); i++)
				{
					Drawable::Destroy(&ring->At(i).drawable, 0);
				}
				ring->head = ring->begin;
				ring->tail = ring->begin;
				ring = iterator.Next();
			}
			while (ring != 0);
			unknownFC = 0;
		}

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
