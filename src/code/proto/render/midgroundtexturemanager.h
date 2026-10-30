// proto::MidgroundTextureManager (RTTI 0x110ACA3C, vftable 0x10E24538, one slot): the texture half of the midground
// renderer, the one object the script native world_SetMidgroundTexture works on (0x112730BC). It holds the episode whose
// midground texture is wanted and loads that texture on the render thread. The file name, the layout and the member
// names are guesses.
#ifndef PROTO_RENDER_MIDGROUNDTEXTUREMANAGER_H
#define PROTO_RENDER_MIDGROUNDTEXTUREMANAGER_H

namespace pure3d
{
	class Texture;
}

namespace proto
{
	class MidgroundTextureManager
	{
	public:
		// 0x10567CB0: registers the script native
		MidgroundTextureManager();
		// 0x105676F0
		virtual ~MidgroundTextureManager();

		// 0x10567690: wants the texture of an episode (1 - 7), when it is not the current one
		void SetEpisode(int newEpisode);
		// 0x10567C30: loads the wanted texture (the time is not read)
		void Update(float deltaTime);
		// 0x10567A40 (not reconstructed): reads the texture of the episode in and queues its upload
		void LoadTexture();
		// 0x10567710: on the render thread, parses the image in memory into the texture and frees the memory
		void UploadTexture(unsigned char* data, unsigned int size, pure3d::Texture* texture);
		// 0x10567C50: binds the script native
		void RegisterScript();
		// 0x10567670: takes the object back out of the script manager
		void ReleaseScript();

		int state;  // +4: 0 idle, 1 a texture is wanted, 2 loading
		int episode;  // +8
		unsigned char unknownC[0x1C];
	};

	// 0x112730BC: the one midground texture manager (null: none)
	extern MidgroundTextureManager* gMidgroundTextureManager;
}

#endif
