// CFLAGS: !/arch
// Lua 5.1.1 lmem.c (Interface to Memory Manager; unit 0x10633DE0 - 0x10633ED0). The library is compiled as C++ with C linkage.
#include <stddef.h>

#include "code/lua/lua.h"
#include "code/lua/ldebug.h"
#include "code/lua/ldo.h"
#include "code/lua/lmem.h"
#include "code/lua/lobject.h"
#include "code/lua/lstate.h"

extern "C"
{

// About the realloc function:
// void* frealloc (void *ud, void *ptr, size_t osize, size_t nsize);
// (`osize' is the old size, `nsize' is the new size)
//
// Lua ensures that (ptr == NULL) iff (osize == 0).
//
// * frealloc(ud, NULL, 0, x) creates a new block of size `x'
//
// * frealloc(ud, p, x, 0) frees the block `p' (when this function is called, the allocator must free the block).
//
// * frealloc(ud, p, x, y) reallocates the block `p' from size `x' to size `y'.

#define MINSIZEARRAY 4

// FUNCTION: ENGINE 0x10633E50
void* luaM_growaux_(lua_State* L, void* block, int* size, size_t size_elems, int limit, const char* errormsg)
{
	void* newblock;
	int newsize;
	if (*size >= limit / 2)
	{
		// cannot double it?
		if (*size >= limit)
		{
			// cannot grow even a little?
			luaG_runerror(L, errormsg);
		}
		newsize = limit; // still have at least one free place
	}
	else
	{
		newsize = (*size) * 2;
		if (newsize < MINSIZEARRAY)
		{
			newsize = MINSIZEARRAY; // minimum size
		}
	}
	newblock = luaM_reallocv(L, block, *size, newsize, size_elems);
	*size = newsize; // update only when everything else is OK
	return newblock;
}

// FUNCTION: ENGINE 0x10633DE0
void* luaM_toobig(lua_State* L)
{
	luaG_runerror(L, "memory allocation error: block too big");
	return NULL; // to avoid warnings
}

// generic allocation routine.
// FUNCTION: ENGINE 0x10633E00
void* luaM_realloc_(lua_State* L, void* block, size_t osize, size_t nsize)
{
	global_State* g = G(L);
	lua_assert((osize == 0) == (block == NULL));
	block = (*g->frealloc)(g->ud, block, osize, nsize);
	if (block == NULL && nsize > 0)
	{
		luaD_throw(L, LUA_ERRMEM);
	}
	lua_assert((nsize == 0) == (block == NULL));
	g->totalbytes = (g->totalbytes - osize) + nsize;
	return block;
}
}
