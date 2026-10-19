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

		unsigned char unknown0[0x18];
		math::Vector unknown18;
		int unknown24;
		PartAnimationFlags unknown28;
	};

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

		class Client
		{
		public:
			virtual ~Client();

			// 0x1071AD50 / 0x1071A930
			void GetState(PartAnimationState* state);
			void SetState(const PartAnimationState* state);
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
