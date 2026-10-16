// proto::MidgroundTextureManager (RTTI 0x110ACA3C, vftable 0x10E24538, one slot): the texture half of the midground
// renderer, the one object the script native d_SetMidgroundTexture works on (0x112730BC). Only the destructor, its
// script release and the scalar deleting destructor are reconstructed; the rest of the unit (0x1056xxx) is not
// started, so the file name, the layout and the member names are guesses.
#ifndef PROTO_RENDER_MIDGROUNDTEXTUREMANAGER_H
#define PROTO_RENDER_MIDGROUNDTEXTUREMANAGER_H

namespace proto
{
	class MidgroundTextureManager
	{
	public:
		// 0x105676F0
		virtual ~MidgroundTextureManager();

		// 0x10567670: takes the object back out of the script manager
		void ReleaseScript();

		unsigned char unknown4[0x20];
	};

	// 0x112730BC: the one midground texture manager (null: none)
	extern MidgroundTextureManager* gMidgroundTextureManager;
}

#endif
