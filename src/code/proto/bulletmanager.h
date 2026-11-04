// proto::BulletManager (RTTI name, one vftable slot): the pool the bullet tracers live in, a block of 8000 bytes (one
// tracer is 0x50 bytes long) made when the manager is; the instance made last is kept in gBulletManager. Unit
// 0x10463A10 - 0x10464B20 (no assert path; the file name is a guess); only the construction and the destruction are
// reconstructed.
#ifndef PROTO_BULLETMANAGER_H
#define PROTO_BULLETMANAGER_H

namespace proto
{
	class BulletManager
	{
	public:
		// 0x10463A10
		BulletManager();
		// 0x10463A70 (the deleting destructor is 0x10464630)
		virtual ~BulletManager();

		unsigned char* begin;  // +4: the block
		unsigned char* end;  // +8: the end of the bullets in it
		unsigned char* blockEnd;  // +0xC
	};

	// 0x11269318
	extern BulletManager* gBulletManager;
}

#endif
