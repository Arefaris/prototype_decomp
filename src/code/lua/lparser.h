// Lua 5.1.1, lparser.h: Lua parser.
#ifndef LUA_LPARSER_H
#define LUA_LPARSER_H

#include "code/lua/llimits.h"
#include "code/lua/lobject.h"
#include "code/lua/lzio.h"

Proto* luaY_parser(lua_State* L, ZIO* z, Mbuffer* buff, const char* name);

#endif
