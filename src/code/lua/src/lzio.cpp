// CFLAGS: /TC !/arch
// Lua 5.1.1 lzio.c (a generic input stream interface; unit 0x10633940 - 0x10633A9F). The library is compiled as C.
#include <string.h>

#include "code/lua/lua.h"
#include "code/lua/llimits.h"
#include "code/lua/lmem.h"
#include "code/lua/lstate.h"
#include "code/lua/lzio.h"

// FUNCTION: ENGINE 0x10633940
int luaZ_fill(ZIO* z)
{
	size_t size;
	lua_State* L = z->L;
	const char* buff;
	lua_unlock(L);
	buff = z->reader(L, z->data, &size);
	lua_lock(L);
	if (buff == NULL || size == 0)
	{
		return EOZ;
	}
	z->n = size - 1;
	z->p = buff;
	return char2int(*(z->p++));
}

// FUNCTION: ENGINE 0x10633980
int luaZ_lookahead(ZIO* z)
{
	if (z->n == 0)
	{
		if (luaZ_fill(z) == EOZ)
		{
			return EOZ;
		}
		else
		{
			z->n++; // luaZ_fill removed first byte; put back it
			z->p--;
		}
	}
	return char2int(*z->p);
}

// FUNCTION: ENGINE 0x106339B0
void luaZ_init(lua_State* L, ZIO* z, lua_Reader reader, void* data)
{
	z->L = L;
	z->reader = reader;
	z->data = data;
	z->n = 0;
	z->p = NULL;
}

// read
// FUNCTION: ENGINE 0x106339E0
size_t luaZ_read(ZIO* z, void* b, size_t n)
{
	while (n)
	{
		size_t m;
		if (luaZ_lookahead(z) == EOZ)
		{
			return n; // return number of missing bytes
		}
		m = (n <= z->n) ? n : z->n; // min. between n and z->n
		memcpy(b, z->p, m);
		z->n -= m;
		z->p += m;
		b = (char*)b + m;
		n -= m;
	}
	return 0;
}

// FUNCTION: ENGINE 0x10633A40
char* luaZ_openspace(lua_State* L, Mbuffer* buff, size_t n)
{
	if (n > buff->buffsize)
	{
		if (n < LUA_MINBUFFER)
		{
			n = LUA_MINBUFFER;
		}
		luaZ_resizebuffer(L, buff, n);
	}
	return buff->buffer;
}
