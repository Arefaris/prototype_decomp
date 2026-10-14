// proto::CloudSpawnerBase and proto::ParkedCarCloudManager (RTTI names; the manager's vtable is 0x10E1B954 and its
// singleton sits at 0x1126F15C). The original's chains are
// ParkedCarCloudManager : CloudManager : ... and CloudSpawnerBase : engine::PropSpawner : engine::GameObjectSpawner :
// content::MetaLoadObject; those bases are not reconstructed, so only the members the two functions below touch are
// declared here, at the offsets their disassembly shows. Everything is a guess except the offsets.
#ifndef PROTO_AI_AMBIENTMANAGER_PARKEDCARCLOUDMANAGER_H
#define PROTO_AI_AMBIENTMANAGER_PARKEDCARCLOUDMANAGER_H

#include "code/container/slist.h"

namespace proto
{
	// One parked-car spawner, as the ranking test (0x104F1DC0) sees it
	class CloudSpawnerBase
	{
	public:
		// 0x104F1DC0 (another unit): decides whether this spawner may make or drop a car. It answers in the three
		// bytes of its last argument (may create, may recycle, may remove) and takes the manager, the two positions,
		// a four-float record, a flag word, the "paused" byte and that answer (`ret 0x28`).
		void Rank(void* context, const float* position, const float* other, float distance, float nearDistance,
			float farDistance, float margin, unsigned int flags, unsigned char pausedByte, unsigned char* answer);

		unsigned char unknown0[0x3c];
		float position3C[3];       // +0x3c: a position
		unsigned char unknown48[0x4c - 0x48];
		unsigned short handle4C;   // +0x4c / +0x4e: a game object handle
		unsigned short handle4E;
		unsigned char unknown50[0xb9 - 0x50];
		unsigned char flagsB9;     // +0xb9: the spawner's kind in the high nibble (Rank switches on it)
		unsigned char flagsBA;     // +0xba: bit 3 visible, bits 4-6 a 7-step hysteresis counter, bit 7 set
		unsigned char flagsBB;     // +0xbb: bit 6
	};

	// The manager the two functions below belong to (the RTTI class of the singleton 0x1126F15C)
	class ParkedCarCloudManager
	{
	public:
		// 0x104EB720: hands the spawners the positions they rank against (the camera-relative ranking of section
		// 2.1: one pass over the list at 0xe8, at most 0x0c of it per call)
		void RankSpawners();
		// 0x104ECBB0: the per-frame update of the manager; it picks the player, the camera and the streaming state
		// and gives every spawner its ranking input, then drops the cars the spawners refuse
		void Update();

		unsigned char unknown0[0xc];
		int limitC;                 // +0x0c: how many spawners one call of RankSpawners handles
		unsigned char unknown10[0x1c - 0x10];
		float table1C[0x48 - 0x1c]; // +0x1c: indexed by the spawner's kind (flagsB9 >> 4)
		float distance48;           // +0x48
		float distance4C;           // +0x4c
		unsigned char unknown50[0x60 - 0x50];
		float distance60;           // +0x60
		unsigned int cursor64;      // +0x64: where the next call of RankSpawners starts
		float unknown68;
		void* list6C;               // +0x6c .. +0x74: the spawners the ranking accepted
		void* end70;
		void* capacity74;
		unsigned char unknown78[0x8c - 0x78];
		void* list8C;               // +0x8c .. +0x94: a list of spawners (begin / end / capacity)
		void* end90;
		void* capacity94;
		unsigned char unknown98[4];
		void* list9C;               // +0x9c .. +0xa0: the spawners processed this frame
		void* endA0;
		unsigned char unknownA4[0xac - 0xa4];
		void* listAC;               // +0xac .. +0xb4: two more spawner lists the ranking fills
		void* endB0;
		void* capacityB4;
		void* listBC;               // +0xbc .. +0xc4
		void* endC0;
		void* capacityC4;
		bool pausedCC;              // +0xcc: rank every spawner when set
		unsigned char pausedByte;   // +0xcd, passed to the ranking test
		unsigned char unknownCE[0xd0 - 0xce];
		float positionD0[3];        // +0xd0
		float positionDC[3];        // +0xdc
		unsigned char unknownE4[0xe8 - 0xe4];
		void* contextE8;            // +0xe8: the first argument of the ranking test
		unsigned int unknownEC;     // +0xec
		unsigned int unknownF0;
		unsigned int rankedF4;      // +0xf4: the 0xec value the last ranking ran for
		unsigned int unknownF8;
		unsigned char unknownFC;
	};
}

#endif
