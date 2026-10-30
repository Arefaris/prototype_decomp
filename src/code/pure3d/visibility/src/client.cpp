// pure3d::visibility::Client (0x1071A720 - 0x1071AC20; the path is guessed from the namespace): the handle a drawable
// part keeps into the visibility server. Names are guesses.
#include "code/pure3d/visibility.h"

namespace pure3d
{
	namespace visibility
	{
		// FUNCTION: ENGINE 0x1071A720
		unsigned int Client::GetRegion() const
		{
			return (unsigned int)index >> 28;
		}

		// FUNCTION: ENGINE 0x1071A740
		unsigned int Client::GetSlot() const
		{
			return index & 0xFFFFFFF;
		}

		// FUNCTION: ENGINE 0x1071A820
		void Client::Unregister()
		{
			if (index != -1 || server != 0)
			{
				unsigned int slot = GetSlot();
				unsigned int region = GetRegion();
				unsigned int* first = &server->bits->results[0].words[slot >> 5];
				unsigned int mask = ~(1 << (slot & 0x1F));
				unsigned int* second;
				*first &= mask;
				second = &server->bits->results[1].words[slot >> 5];
				*second &= mask;
				server->userData[GetSlot()] = 0;
				server->counts[region]--;
			}
		}

		// FUNCTION: ENGINE 0x1071A8A0
		int Client::IsActive()
		{
			if (index != -1 || server != 0)
			{
				unsigned int slot = GetSlot();
				if (server->bits->results[0].words[slot >> 5] & (1 << (slot & 0x1F)))
				{
					return 1;
				}
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x1071A8E0
		unsigned int Client::GetRegionIndex() const
		{
			Server* owner = server;
			unsigned int region = GetRegion();
			return GetSlot() - owner->offsets[region];
		}

		// FUNCTION: ENGINE 0x1071A900
		void Client::SetUserData(void* data)
		{
			server->userData[GetSlot()] = data;
		}

		// FUNCTION: ENGINE 0x1071A920
		void* Client::GetUserData()
		{
			return server->userData[GetSlot()];
		}

		// FUNCTION: ENGINE 0x1071AC60
		void Client::Reset()
		{
			unsigned int slot = GetSlot();
			SetState(&gDefaultPartAnimationState);
			server->userData[GetSlot()] = 0;
			unsigned int* word = &server->bits->results[1].words[slot >> 5];
			unsigned int mask = ~(1 << (slot & 0x1F));
			*word &= mask;
			word = &server->bits->results[2].words[slot >> 5];
			*word &= mask;
			word = &server->bits->results[3].words[slot >> 5];
			*word &= mask;
			word = &server->bits->results[4].words[slot >> 5];
			*word &= mask;
		}

		// FUNCTION: ENGINE 0x1071ACE0
		void Client::Register(bool reset)
		{
			unsigned int slot = GetSlot();
			unsigned int region = GetRegion();
			unsigned int* word = &server->bits->results[0].words[slot >> 5];
			unsigned int mask = 1 << (slot & 0x1F);
			*word |= mask;
			server->counts[region]++;
			if (reset)
			{
				Reset();
			}
			word = &server->bits->results[1].words[slot >> 5];
			*word |= mask;
		}

		// FUNCTION: ENGINE 0x1071A930
		// EQUIVALENT: register allocation (the engine counts the flag sets in the stack slot of its argument and keeps the
		// mask and the word offset in registers across the calls; 11.5 %)
		void Client::SetState(const PartAnimationState* state)
		{
			unsigned int slot = GetSlot();
			math::AABB* box = &server->boxes[slot];
			box->max.x = state->bounds.max.x;
			box->max.y = state->bounds.max.y;
			box->max.z = state->bounds.max.z;
			box->min.x = state->bounds.min.x;
			box->min.y = state->bounds.min.y;
			box->min.z = state->bounds.min.z;
			math::Sphere* sphere = &server->spheres[slot];
			sphere->centre.x = state->unknown18.x;
			sphere->centre.y = state->unknown18.y;
			sphere->centre.z = state->unknown18.z;
			sphere->radius = state->unknown24;
			unsigned int count = server->GetFlagSetCount();
			for (unsigned int i = 0; i < count; i++)
			{
				unsigned int mask = 1 << (slot & 0x1F);
				unsigned int* word = &server->bits->flags[i].words[slot >> 5];
				if (state->unknown28.Test(i))
				{
					*word |= mask;
				}
				else
				{
					*word &= ~mask;
				}
			}
		}

		// FUNCTION: ENGINE 0x1071AD50
		// EQUIVALENT: scheduling (the engine loads the state argument before the server's box array; 97.2 %)
		void Client::GetState(PartAnimationState* state)
		{
			unsigned int slot = GetSlot();
			math::AABB* box = &server->boxes[slot];
			state->bounds.max.x = box->max.x;
			state->bounds.max.y = box->max.y;
			state->bounds.max.z = box->max.z;
			state->bounds.min.x = box->min.x;
			state->bounds.min.y = box->min.y;
			state->bounds.min.z = box->min.z;
			math::Sphere* sphere = &server->spheres[slot];
			state->unknown18.x = sphere->centre.x;
			state->unknown18.y = sphere->centre.y;
			state->unknown18.z = sphere->centre.z;
			state->unknown24 = sphere->radius;
			unsigned int count = server->GetFlagSetCount();
			for (unsigned int i = 0; i < count; i++)
			{
				unsigned int mask = 1 << (slot & 0x1F);
				state->unknown28.Set(i, (server->bits->flags[i].words[slot >> 5] & mask) != 0);
			}
		}

		// FUNCTION: ENGINE 0x1071AA20
		void Client::SetBox(const math::AABB& box)
		{
			unsigned int slot = GetSlot();
			math::AABB* target = &server->boxes[slot];
			target->max.x = box.max.x;
			target->max.y = box.max.y;
			target->max.z = box.max.z;
			target->min.x = box.min.x;
			target->min.y = box.min.y;
			target->min.z = box.min.z;
		}

		// FUNCTION: ENGINE 0x1071AA60
		void Client::SetSphere(math::Sphere sphere)
		{
			unsigned int slot = GetSlot();
			math::Sphere* target = &server->spheres[slot];
			target->centre.x = sphere.centre.x;
			target->centre.y = sphere.centre.y;
			target->centre.z = sphere.centre.z;
			target->radius = sphere.radius;
		}

		// FUNCTION: ENGINE 0x1071AAA0
		void Client::GetBox(math::AABB* box)
		{
			math::AABB* source = &server->boxes[GetSlot()];
			box->max.x = source->max.x;
			box->max.y = source->max.y;
			box->max.z = source->max.z;
			box->min.x = source->min.x;
			box->min.y = source->min.y;
			box->min.z = source->min.z;
		}

		// FUNCTION: ENGINE 0x1071AAE0
		void Client::GetSphere(math::Sphere* sphere)
		{
			math::Sphere* source = &server->spheres[GetSlot()];
			sphere->centre.x = source->centre.x;
			sphere->centre.y = source->centre.y;
			sphere->centre.z = source->centre.z;
			sphere->radius = source->radius;
		}

		// FUNCTION: ENGINE 0x1071ABA0
		void Client::SetFlag(unsigned char flag, bool value)
		{
			unsigned int slot = GetSlot();
			unsigned int* word = &server->bits->flags[flag].words[slot >> 5];
			unsigned int mask = 1 << (slot & 0x1F);
			if (value)
			{
				*word |= mask;
			}
			else
			{
				*word &= ~mask;
			}
		}

		// FUNCTION: ENGINE 0x1071ABE0
		bool Client::GetFlag(int flag)
		{
			unsigned int slot = GetSlot();
			return (server->bits->flags[flag].words[slot >> 5] & (1 << (slot & 0x1F))) != 0;
		}

		// FUNCTION: ENGINE 0x1071AC20
		bool Client::GetResult(int set)
		{
			unsigned int slot = GetSlot();
			return (server->bits->results[set].words[slot >> 5] & (1 << (slot & 0x1F))) != 0;
		}
	}
}
