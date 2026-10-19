// Lua 5.1.1 (the version the engine links), llimits.h and the parts of luaconf.h the library's sources use. The
// engine's build uses float numbers (lua_Number) and 8-byte stack values.
#ifndef LUA_LLIMITS_H
#define LUA_LLIMITS_H

#include <limits.h>
#include <stddef.h>
#include <float.h>
#include <math.h>

#include "code/lua/lua.h"

#ifdef __cplusplus
#define LUAI_EXTERN_C_BEGIN extern "C" {
#define LUAI_EXTERN_C_END }
#else
#define LUAI_EXTERN_C_BEGIN
#define LUAI_EXTERN_C_END
#endif

typedef unsigned int lu_int32;
typedef size_t lu_mem;
typedef ptrdiff_t l_mem;
typedef unsigned char lu_byte;

#define MAX_SIZET ((size_t)(~(size_t)0) - 2)
#define MAX_LUMEM ((lu_mem)(~(lu_mem)0) - 2)
#define MAX_INT (INT_MAX - 2)
#define IntPoint(p) ((unsigned int)(lu_mem)(p))

typedef union { lua_Number u; void* s; long l; } L_Umaxalign;
typedef double l_uacNumber;

#define lua_assert(c) ((void)0)
#define check_exp(c, e) (e)
#define checkliveness(g, obj) ((void)0)
#define api_check(L, e) ((void)0)
#define UNUSED(x) ((void)(x))
#define cast(t, exp) ((t)(exp))
#define cast_byte(i) cast(lu_byte, (i))
#define cast_num(i) cast(lua_Number, (i))
#define cast_int(i) cast(int, (i))

typedef lu_int32 Instruction;

#define MAXUPVAL 255
#define MAXSTACK 250
#define MINSTRTABSIZE 32
#define LUAI_MAXCCALLS 200
#define LUAI_MAXCSTACK 2048
#define LUAI_MAXCALLS 20000
#define LUAI_MAXVARS 200
#define LUAI_MAXUPVALUES 60
#define LUAL_BUFFERSIZE 512
#define LUA_IDSIZE 200
#define LUAI_GCPAUSE 200
#define LUAI_GCMUL 200
#define LUA_MINBUFFER 32
#define LUAI_EXTRASPACE 0
#define LUA_MAXCAPTURES 32

#define lua_lock(L) ((void)0)
#define lua_unlock(L) ((void)0)
#define luai_threadyield(L) { lua_unlock(L); lua_lock(L); }
#define condhardstacktests(x) ((void)0)
#define luai_userstateopen(L) ((void)L)
#define luai_userstateclose(L) ((void)L)
#define luai_userstatethread(L, L1) ((void)L)
#define luai_userstatefree(L) ((void)L)
#define luai_userstateresume(L, n) ((void)L)
#define luai_userstateyield(L, n) ((void)L)

#define luai_numadd(a, b) ((a) + (b))
#define luai_numsub(a, b) ((a) - (b))
#define luai_nummul(a, b) ((a) * (b))
#define luai_numdiv(a, b) ((a) / (b))
#define luai_nummod(a, b) ((a) - (float)floor((a) / (b)) * (b))
#define luai_numpow(a, b) (pow(a, b))
#define luai_numunm(a) (-(a))
#define luai_numeq(a, b) ((a) == (b))
#define luai_numlt(a, b) ((a) < (b))
#define luai_numle(a, b) ((a) <= (b))
#define luai_numisnan(a) _isnan(a)

#define lua_number2int(i, d) ((i) = (int)(d))
#define lua_number2integer(i, d) ((i) = (lua_Integer)(d))
#define lua_str2number(s, p) strtod((s), (p))
#define LUA_NUMBER_FMT "%.7g"
#define LUAI_MAXNUMBER2STR 16
#define lua_number2str(s, n) sprintf((s), LUA_NUMBER_FMT, (n))

#endif
