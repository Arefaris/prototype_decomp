// The propaganda manager (RTTI proto::PropagandaManager, vftable 0x10E24BF8, one slot): the billboard textures of the
// propaganda posters, one set per level of the script native world_SetPropagandaLevel (0x112735A8 is the one manager).
// Like the midground texture manager it reads the textures in and uploads them on the render thread. The layout and the
// member names are guesses.
#ifndef PROTO_PROPAGANDAMANAGER_H
#define PROTO_PROPAGANDAMANAGER_H

namespace pure3d
{
	class Texture;
}

namespace proto
{
	// RTTI: proto::PropagandaManager
	class PropagandaManager
	{
	public:
		// 0x1056F540: registers the script native
		PropagandaManager();
		// 0x1056EF20
		virtual ~PropagandaManager();

		// 0x1056EEF0: wants the textures of a level (0 - 2), when it is not the current one
		void SetLevel(int newLevel);
		// 0x1056F4C0: loads the wanted textures (the time is not read)
		void Update(float deltaTime);
		// 0x1056F2A0 (not reconstructed): reads the textures of the level in and queues their uploads
		void LoadTextures();
		// 0x1056EF40: on the render thread, parses one image in memory into a texture and frees the memory
		void UploadTexture(unsigned char* data, unsigned int size, pure3d::Texture* texture);
		// 0x1056F4E0: binds the script native
		void RegisterScript();
		// 0x1056EED0: takes the object back out of the script manager
		void ReleaseScript();

		int level;  // +4
		int state;  // +8: 1 when textures are wanted
		int textureCount;  // +0xC
		int uploaded;  // +0x10
		int unknown14;
		int unknown18;
	};

	// 0x112735A8: the one propaganda manager (null: none)
	extern PropagandaManager* gPropagandaManager;
}

#endif
