// The models of the audio renderer drivers (RTTI: audio::RendererDriverModel and the models derived from it, one for each
// kind of driver): a model has a name and makes a driver of its kind on request. The harness it hands the driver to is
// the part of the renderer that lists the drivers (RTTI: audio::RenderDriverModelHarness).
#ifndef AUDIO_RENDERERDRIVERMODEL_H
#define AUDIO_RENDERERDRIVERMODEL_H

#include "code/audio/rendererdriver.h"

namespace audio
{
	class RenderDriverModelHarness
	{
	public:
		// Slot 0: takes a driver the model made (name guessed)
		virtual void AddDriver(RendererDriver* driver) = 0;
	};

	class RendererDriverModel
	{
	public:
		// 0x105E4E30
		explicit RendererDriverModel(const om::String& newName);
		// Slot 0: makes a driver and hands it to the harness (name guessed)
		virtual void CreateDriver(RenderDriverModelHarness* harness) = 0;
		virtual void Slot1() = 0;

		om::String name;  // 4
	};
}

#endif
