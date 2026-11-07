#include "code/proto/bulletmanager.h"
#include <new>

namespace proto
{
	BulletManager* gBulletManager;  // 0x11269318

	// FUNCTION: ENGINE 0x10463A10
	BulletManager::BulletManager()
	{
		begin = new unsigned char[8000];
		if (begin != 0)
		{
			end = begin;
			blockEnd = begin + 8000;
		}
		else
		{
			end = 0;
			blockEnd = 0;
		}
		gBulletManager = this;
	}

	// FUNCTION: ENGINE 0x10463A70
	BulletManager::~BulletManager()
	{
		gBulletManager = 0;
		end = begin;
		if (begin != 0)
		{
			delete[] begin;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10464630
