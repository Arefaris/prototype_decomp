// proto::ParkedCarCloudManager (RTTI name; the manager's vtable is 0x10E1B954 and its singleton sits at 0x1126F15C).
// The original's chain is ParkedCarCloudManager : CloudManager : ...; that base is not reconstructed, so only the members
// the two functions below touch are declared here, at the offsets their disassembly shows. Everything is a guess except
// the offsets.
#ifndef PROTO_AI_AMBIENTMANAGER_PARKEDCARCLOUDMANAGER_H
#define PROTO_AI_AMBIENTMANAGER_PARKEDCARCLOUDMANAGER_H

#include "code/container/slist.h"
#include "code/proto/cloudspawnerbase.h"

namespace proto
{
	struct CloudConfig;

	// The manager the two functions below belong to (the RTTI class of the singleton 0x1126F15C)
	class ParkedCarCloudManager
	{
	public:
		// 0x104EF830
		explicit ParkedCarCloudManager(const CloudConfig* config);
		// 0x104EB720: hands the spawners the positions they rank against (the camera-relative ranking of section
		// 2.1: one pass over the list at 0xe8, at most 0x0c of it per call)
		void RankSpawners();
		// 0x104ECBB0: the per-frame update of the manager; it picks the player, the camera and the streaming state
		// and gives every spawner its ranking input, then drops the cars the spawners refuse
		void Update();

		unsigned char unknown0[0xc];
		int limitC;                 // +0x0c: how many spawners one call of RankSpawners handles
		unsigned char unknown10[0x1c - 0x10];
		float table1C[(0x48 - 0x1c) / 4]; // +0x1c: indexed by the spawner's kind (flagsB9 >> 4)
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
		unsigned char unknownFD[11];
	};
}

#endif
