// The audio renderer (RTTI: audio::Renderer, the interface of audio::RendererImpl). Only what the reflection
// templates need so far.
#ifndef AUDIO_RENDERER_H
#define AUDIO_RENDERER_H

namespace audio
{
	class RendererDriver;

	class Renderer
	{
	public:
		// 0x105D10E0 (name guessed): the driver the renderer uses, null when there is none
		RendererDriver* GetDriver();
	};
	// The instance (0x11276854)
	extern Renderer* gRenderer;
}

#endif
