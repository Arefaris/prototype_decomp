// pure3d::visibility (RTTI names pure3d::visibility::Server, Server::BitFieldStack, Client and
// VisibilityTestTaskCallBack): the visibility server keeps a bounding box and sphere per registered client and runs
// frustum tests on them as asynchronous tasks; a client is the handle a drawable part keeps (its server and its index
// there). Member names are guesses; only what the reconstructed code uses is declared.
#ifndef PURE3D_VISIBILITY_H
#define PURE3D_VISIBILITY_H

#include "code/core/bitfield.h"
#include "code/math/aabb.h"
#include "code/math/sphere.h"
#include "code/math/vector.h"

namespace pure3d
{
	// The flags of a part's visibility state and of a shader: a core::BitField<unsigned int> (the engine's copies of its
	// constructor, Set and Test are 0x102E8920, 0x102E8B80 and 0x106DEA40)
	typedef core::BitField<unsigned int> PartAnimationFlags;

	struct PartAnimationState
	{
		PartAnimationState() : unknown18(0.0f, 0.0f, 0.0f)
		{
		}

		// The box and sphere the server tests (the sphere's centre and radius), then the part's flags
		math::AABB bounds;
		math::Vector unknown18;
		float unknown24;
		PartAnimationFlags unknown28;
	};

	// 0x112817DC: the state a client is given when it leaves the server (name guess)
	extern PartAnimationState gDefaultPartAnimationState;

	namespace visibility
	{
		class Server;

		// A frustum test of the server's boxes (0xE0 bytes, one per task slot from Server +0x4A0): the boxes whose
		// bit is set in the input bits and that lie inside every plane and are large enough get their bit set in
		// the output bits
		struct Test
		{
			unsigned int slot;
			unsigned int unknown4;
			const unsigned int* inputBits;
			unsigned int* outputBits;
			const math::AABB* boxes;
			unsigned int boxCount;
			// The planes: normal and distance (a point is outside when normal . p > -distance)
			struct Plane
			{
				math::Vector normal;
				float distance;
			} planes[9];
			unsigned int planeCount;
			// Boxes whose diagonal is shorter than sqrt(12) * this are skipped
			float minimumSize;
			unsigned char unknownB0[0x30];
		};

		// A set of bits as the server keeps them (16 bytes: the words are at +8)
		struct BitSet
		{
			int unknown0;
			int unknown4;
			unsigned int* words;
			int unknownC;
		};

		// RTTI pure3d::visibility::Server::BitFieldStack: the result sets of the tests (5) and then the flag sets
		struct BitFieldStack
		{
			BitSet results[5];
			BitSet flags[1];
		};

		// The bounds and bits of the clients (layout partial; the rest of the class lives in the server's unit)
		class Server
		{
		public:
			// 0x10726590: how many flag sets there are
			unsigned int GetFlagSetCount();
			// 0x10728350: waits until the test of a task slot is done and marks the slot free (nothing for -1; name guess)
			void FinishTest(int slot);

			unsigned char unknown0[0x18];
			math::AABB* boxes;
			unsigned char unknown1C[8];
			math::Sphere* spheres;
			unsigned char unknown28[8];
			void** userData;
			unsigned char unknown34[0x14];
			BitFieldStack* bits;
			unsigned char unknown4C[0xF4];
			// How many clients each region holds, and where each region starts in the slots
			int counts[28];
			int offsets[14];
			unsigned int flagSetCount;
			float unknown1EC;
			int unknown1F0;
			// Whether the test of each task slot is running (+0x1F4), the lock that guards it (+0x1FC) and the events
			// that tell the test of a slot is done (+0xC04, 0xC bytes each)
			unsigned char slotBusy[8];
			unsigned char lock[0xA08];
			unsigned char events[1];
		};

		class Client
		{
		public:
			virtual ~Client();

			// 0x1071A720 / 0x1071A740: the region of the client's index (its top four bits) and its place in the region
			unsigned int GetRegion() const;
			unsigned int GetSlot() const;

			// 0x1071AD50 / 0x1071A930
			void GetState(PartAnimationState* state);
			void SetState(const PartAnimationState* state);
			// 0x1071AAA0 / 0x1071AAE0: the bounds the server tests
			void GetBox(math::AABB* box);
			void GetSphere(math::Sphere* sphere);
			// 0x1071A900 / 0x1071A920: the word the owner keeps with the client
			void SetUserData(void* data);
			void* GetUserData();
			// 0x1071A8A0: whether the client is registered and its bit is set in the first result set
			int IsActive();
			// 0x1071A8E0: the client's place in its region
			unsigned int GetRegionIndex() const;
			// 0x1071A820: takes the client out of the server (name guess)
			void Unregister();
			// 0x1071AC60: gives the client the default state and clears its user data and its bits in the result sets
			// after the first (name guess)
			void Reset();
			// 0x1071ACE0: marks the client as registered, optionally resetting it (name guess)
			void Register(bool reset);
			// 0x1071AC20: the client's bit in result set `set` (the last visibility test)
			bool GetResult(int set);
			// 0x1071ABA0 / 0x1071ABE0: the client's bit in flag set `flag`
			void SetFlag(unsigned char flag, bool value);
			bool GetFlag(int flag);
			// 0x1071AA20 / 0x1071AA60: the bounds the server tests
			void SetBox(const math::AABB& box);
			void SetSphere(math::Sphere sphere);

			bool IsRegistered() const
			{
				return index != -1 || server != 0;
			}

			int index;
			Server* server;
		};
	}
}

#endif
