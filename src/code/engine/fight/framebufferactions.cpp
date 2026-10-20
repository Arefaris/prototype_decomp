// The actions of the frame buffer tracks (tone mapping, fades, depth of field, colour matrices, scatter, letterbox and bloom; unit 0x108BB810 - 0x108BC250, no assert path; file name guessed). The tracks are in framebuffertracks.cpp.
#include "code/engine/fight/framebufferactions.h"

namespace engine
{
	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBC40
		BloomAction::BloomAction(BloomTrack* newTrack)
			: fight::Action(0x600), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB810
		BloomAction::~BloomAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC100
		fight::Action* BloomTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new BloomAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBD00
		ToneMapAction::ToneMapAction(ToneMapTrack* newTrack)
			: fight::Action(0x200), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB850
		ToneMapAction::~ToneMapAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC130
		fight::Action* ToneMapTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new ToneMapAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBDA0
		ScatterAction::ScatterAction(ScatterTrack* newTrack)
			: fight::Action(0x200), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB890
		ScatterAction::~ScatterAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC160
		fight::Action* ScatterTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new ScatterAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBE20
		DepthOfFieldAction::DepthOfFieldAction(DepthOfFieldTrack* newTrack)
			: fight::Action(0x200), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB8D0
		DepthOfFieldAction::~DepthOfFieldAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC190
		fight::Action* DepthOfFieldTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new DepthOfFieldAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBEC0
		ColourMatrixAction::ColourMatrixAction(ColourMatrixTrack* newTrack)
			: fight::Action(0x200), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB910
		ColourMatrixAction::~ColourMatrixAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC1C0
		fight::Action* ColourMatrixTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new ColourMatrixAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBF60
		FadeAction::FadeAction(FadeTrack* newTrack)
			: fight::Action(0xA00), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB950
		FadeAction::~FadeAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC1F0
		fight::Action* FadeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new FadeAction(this);
		}

	}

	namespace framebufferfx
	{
		// FUNCTION: ENGINE 0x108BBFF0
		LetterboxAction::LetterboxAction(LetterboxTrack* newTrack)
			: fight::Action(0x600), link(newTrack)
		{
		}

		// FUNCTION: ENGINE 0x108BB990
		LetterboxAction::~LetterboxAction()
		{
		}

		// FUNCTION: ENGINE 0x108BC220
		fight::Action* LetterboxTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			return new LetterboxAction(this);
		}

	}

}
