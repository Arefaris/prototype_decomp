// The lights selected for the object being drawn (the global at 0x112817D8, methods 0x10717920 - 0x10718DB9; the
// constructor makes three lists of 1024 lights). The class name and the member names are guesses: no RTTI survives
// for it. The fill (0x10718B30) gathers the render lights that touch the object into the first list, builds the
// active list (second: spots, lights without a range and ambient lights first, then the point lights) and the vertex
// list (third: the point lights meant for the vertex lighting, nearest first); the lit passes upload from them.
#ifndef PURE3D_LIGHTSELECTION_H
#define PURE3D_LIGHTSELECTION_H

#include <new>

namespace pure3d
{
	class Light;
	class PassContext;

	// A list of lights (16 bytes: begin, end, capacity and the allocator word)
	struct LightList
	{
		// 0x10718830 makes the three lists of the selection: room for 1024 lights each
		LightList()
		{
			begin = new Light*[1024];
			if (begin != 0)
			{
				end = begin;
				capacity = begin + 1024;
			}
			else
			{
				end = 0;
				capacity = 0;
			}
		}
		~LightList()
		{
			end = begin;
			if (begin != 0)
			{
				delete[] begin;
			}
		}

		Light** begin;
		Light** end;
		Light** capacity;
		int unknownC;

		// Puts the light behind the last one when there is room
		void PushBack(Light* light)
		{
			if (end < capacity)
			{
				new (end++) Light*(light);
			}
		}
	};

	class LightSelection
	{
	public:
		// 0x10718830 / 0x107188C0: three lists of 1024 lights
		LightSelection();
		~LightSelection();
		// 0x10718900 / 0x107189C0: make and delete the global selection
		static void Start();
		static void Stop();
		// 0x10717920
		static LightSelection* Get();
		// 0x10718B30: picks the lights the pass context's scene lights up (see the lists below)
		void Fill(PassContext* context);
		// 0x10717930: mode 1 becomes 3 while the vertex lighting flag is set
		void SetMode(int newMode);
		// 0x10717950
		int GetMode();
		// 0x10717960 / 0x10717970
		LightList* GetActiveLights();
		LightList* GetVertexLights();
		// 0x10717980
		void SetUnknown34(bool value);
		// 0x10717990: the user data's range scale of a light (1 without user data)
		float GetRangeScale(Light* light);
		// 0x107179D0: one of the user data's two intensity scales (mode 0 or 1; 1 without user data)
		float GetIntensityScale(Light* light, int scaleMode);
		// 0x10718170: uploads the five nearest vertex lights (and clears the others)
		void UploadVertexLights();
		// 0x10717C60 (646 bytes): puts the light, or the default for none, into the constants of a vertex light slot
		// (name guess)
		void UploadLight(Light* light, unsigned int slot, int unknown);

		int mode;
		LightList candidates;
		LightList active;
		LightList vertex;
		bool unknown34;
	};

	// 0x112817D8
	extern LightSelection* gLightSelection;
}

#endif
