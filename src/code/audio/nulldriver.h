// The driver that renders to no device (RTTI: audio::NullRendererDriver, its model and its thread): a thread paces the
// mixer by the clock and hands it the blocks of samples a sound card would have asked for.
#ifndef AUDIO_NULLDRIVER_H
#define AUDIO_NULLDRIVER_H

#include "code/audio/rendererdrivermodel.h"
#include "code/om/thread.h"

namespace audio
{
	// What the driver's user data points at: the mixer, asked for a block of samples (name and signature guessed)
	class RendererUser
	{
	public:
		virtual void Render(void* channels, unsigned int count) = 0;
	};

	class NullRendererDriver : public RendererDriver
	{
	public:
		// The thread that paces the driver
		class RendererThread : public om::Thread
		{
		public:
			// 0x10AB7410
			explicit RendererThread(NullRendererDriver* newDriver);
			// Slot 0 (0x10AB7450)
			virtual void Run();

			NullRendererDriver* driver;  // 0xCC
		};

		// 0x10AB7590
		NullRendererDriver();
		virtual ~NullRendererDriver();
		virtual const char* Slot1();
		// Slots 3, 4 and 5 (0x10AB7380 / 0x10AB73E0 / 0x10AB7400): start and stop the thread
		virtual void SetUserData(unsigned int newUserData);
		virtual void ClearUserData();
		virtual bool Slot5();
		OM_ALLOCATION(NullRendererDriver);

		char unknown7C[0x10];
		unsigned char buffer[0x5000];  // 0x8C
		unsigned char* alignedBuffer;  // 0x508C
		unsigned char* channels[8];  // 0x5090
		RendererThread thread;  // 0x50B0
	};

	class NullRendererDriverModel : public RendererDriverModel
	{
	public:
		// 0x10AB72B0
		NullRendererDriverModel();
		virtual void CreateDriver(RenderDriverModelHarness* harness);
		virtual void Slot1();
	};
}

#endif
