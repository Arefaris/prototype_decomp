// The actions of the frame buffer tracks (tone mapping, fades, depth of field, colour matrices, scatter, letterbox and bloom; unit 0x108BB810 - 0x108BC250, no assert path; file name guessed). The tracks are in framebuffertracks.cpp.
#ifndef ENGINE_FIGHT_FRAMEBUFFERACTIONS_H
#define ENGINE_FIGHT_FRAMEBUFFERACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/framebuffertracks.h"

namespace engine
{
	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::BloomAction (9 vftable slots, size 0x28)
		class BloomAction : public fight::Action
		{
		public:
			// 0x108BBC40
			BloomAction(BloomTrack* newTrack);
			// 0x108BB810
			virtual ~BloomAction();

			// vftable slot 5 (0x108BBCB0)
			virtual bool Slot5(int arg, float value);
			// vftable slot 6 (0x108BBCE0)
			virtual void Slot6();

			core::Link<BloomTrack> link;  // +0x1C
		};

	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::ToneMapAction (9 vftable slots, size 0x28)
		class ToneMapAction : public fight::Action
		{
		public:
			// 0x108BBD00
			ToneMapAction(ToneMapTrack* newTrack);
			// 0x108BB850
			virtual ~ToneMapAction();

			// vftable slot 5 (0x108BBD70)
			virtual bool Slot5(int arg, float value);

			core::Link<ToneMapTrack> link;  // +0x1C
		};

	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::ScatterAction (9 vftable slots, size 0x28)
		class ScatterAction : public fight::Action
		{
		public:
			// 0x108BBDA0
			ScatterAction(ScatterTrack* newTrack);
			// 0x108BB890
			virtual ~ScatterAction();

			// vftable slot 5 (0x108BBE10)
			virtual bool Slot5(int arg, float value);

			core::Link<ScatterTrack> link;  // +0x1C
		};

	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::DepthOfFieldAction (9 vftable slots, size 0x28)
		class DepthOfFieldAction : public fight::Action
		{
		public:
			// 0x108BBE20
			DepthOfFieldAction(DepthOfFieldTrack* newTrack);
			// 0x108BB8D0
			virtual ~DepthOfFieldAction();

			// vftable slot 5 (0x108BBE90)
			virtual bool Slot5(int arg, float value);

			core::Link<DepthOfFieldTrack> link;  // +0x1C
		};

	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::ColourMatrixAction (9 vftable slots, size 0x28)
		class ColourMatrixAction : public fight::Action
		{
		public:
			// 0x108BBEC0
			ColourMatrixAction(ColourMatrixTrack* newTrack);
			// 0x108BB910
			virtual ~ColourMatrixAction();

			// vftable slot 5 (0x108BBF30)
			virtual bool Slot5(int arg, float value);

			core::Link<ColourMatrixTrack> link;  // +0x1C
		};

	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::FadeAction (9 vftable slots, size 0x28)
		class FadeAction : public fight::Action
		{
		public:
			// 0x108BBF60
			FadeAction(FadeTrack* newTrack);
			// 0x108BB950
			virtual ~FadeAction();

			// vftable slot 5 (0x108BBFD0)
			virtual bool Slot5(int arg, float value);
			// vftable slot 7 (0x108BAE40)
			virtual bool Slot7(int arg, float value);

			core::Link<FadeTrack> link;  // +0x1C
		};

	}

	namespace framebufferfx
	{
		// RTTI: engine::framebufferfx::LetterboxAction (9 vftable slots, size 0x28)
		class LetterboxAction : public fight::Action
		{
		public:
			// 0x108BBFF0
			LetterboxAction(LetterboxTrack* newTrack);
			// 0x108BB990
			virtual ~LetterboxAction();

			// vftable slot 5 (0x108BC060)
			virtual bool Slot5(int arg, float value);
			// vftable slot 6 (0x108BC0C0)
			virtual void Slot6();

			core::Link<LetterboxTrack> link;  // +0x1C
		};

	}

}

#endif
