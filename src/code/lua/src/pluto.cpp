// CFLAGS: !/arch !/O2 !/Ob1 /Od
// Pluto (persistence of Lua data, by Ben Sunshine-Hill) in the engine's build with float numbers and Lua 5.1.1, unit 0x10B77640 - 0x10B7A0C0. The
// engine wraps it in engine::LuaSerialize and engine::LuaDeserialize (a writer or a reader function and its data are passed as integers) and
// compiles the unit without optimisation. The functions are internal to the unit (names guessed from the library's).
#include <string.h>

#include "code/lua/lua.h"
#include "code/lua/lauxlib.h"
#include "code/lua/lapi.h"
#include "code/lua/ldo.h"
#include "code/lua/lfunc.h"
#include "code/lua/lgc.h"
#include "code/lua/lmem.h"
#include "code/lua/lobject.h"
#include "code/lua/lopcodes.h"
#include "code/lua/lstate.h"
#include "code/lua/lstring.h"
#include "code/lua/lzio.h"

#define verify(x) \
	{ \
		int v = (int)(x); \
		v = v; \
	}

// Like the library's macros for the other collectable values, for the upvalues the persistence also writes
#define setupvalue(L, obj, x) 	{ 		TValue* i_o = (obj); 		i_o->value.gc = cast(GCObject*, (x)); 		i_o->tt = LUA_TUPVAL; 		checkliveness(G(L), i_o); 	}

namespace engine
{
	// What persisting a value needs: the state, the number of the next object, and where the bytes go
	struct PersistInfo
	{
		lua_State* L;
		int counter;
		lua_Writer writer;
		void* ud;
	};

	// What unpersisting a value needs: the state and the stream the bytes come from
	struct UnpersistInfo
	{
		lua_State* L;
		ZIO zio;
	};

	static void persist(PersistInfo* pi);
	static void persisttable(PersistInfo* pi);
	static void persistfunction(PersistInfo* pi);
	static void persistuserdata(PersistInfo* pi);
	static void persistthread(PersistInfo* pi);
	static void persistproto(PersistInfo* pi);
	static void persistupval(PersistInfo* pi);
	static void persistboolean(PersistInfo* pi);
	static void persistlightuserdata(PersistInfo* pi);
	static void persistnumber(PersistInfo* pi);
	static void persiststring(PersistInfo* pi);
	static void unpersist(UnpersistInfo* upi);
	static void registerobject(int ref, UnpersistInfo* upi);
	static void unpersistboolean(UnpersistInfo* upi);
	static void unpersistlightuserdata(UnpersistInfo* upi);
	static void unpersistnumber(UnpersistInfo* upi);
	static void unpersiststring(UnpersistInfo* upi);
	static void unpersisttable(int ref, UnpersistInfo* upi);
	static void unpersistfunction(int ref, UnpersistInfo* upi);
	static void unpersistuserdata(int ref, UnpersistInfo* upi);
	static void unpersistthread(int ref, UnpersistInfo* upi);
	static void unpersistproto(int ref, UnpersistInfo* upi);
	static void unpersistupval(int ref, UnpersistInfo* upi);
	static void unpersistpermanent(int ref, UnpersistInfo* upi);

	// FUNCTION: ENGINE 0x10B77640
	void LuaSerialize(lua_State* L, int writer, int ud)
	{
		PersistInfo pi;
		pi.counter = 0;
		pi.L = L;
		pi.writer = (lua_Writer)writer;
		pi.ud = (void*)ud;
		lua_newtable(L);
		lua_newtable(L);
		lua_pushstring(L, "__mode");
		lua_pushstring(L, "k");
		lua_settable(L, 4);
		lua_setmetatable(L, 3);
		lua_insert(L, 2);
		persist(&pi);
		lua_remove(L, 2);
	}

	// FUNCTION: ENGINE 0x10B776F0
	static void persist(PersistInfo* pi)
	{
		lua_pushvalue(pi->L, -1);
		lua_rawget(pi->L, 2);
		if (lua_type(pi->L, -1) != LUA_TNIL)
		{
			int zero = 0;
			void* ref = lua_touserdata(pi->L, -1);
			pi->writer(pi->L, &zero, sizeof(int), pi->ud);
			pi->writer(pi->L, &ref, sizeof(void*), pi->ud);
			lua_pop(pi->L, 1);
		}
		else
		{
			lua_pop(pi->L, 1);
			if (lua_type(pi->L, -1) == LUA_TNIL)
			{
				int zero = 0;
				pi->writer(pi->L, &zero, sizeof(int), pi->ud);
				pi->writer(pi->L, &zero, sizeof(int), pi->ud);
			}
			else
			{
				int one = 1;
				pi->writer(pi->L, &one, sizeof(int), pi->ud);
				lua_pushvalue(pi->L, -1);
				pi->counter++;
				lua_pushlightuserdata(pi->L, (void*)pi->counter);
				lua_rawset(pi->L, 2);
				pi->writer(pi->L, &pi->counter, sizeof(int), pi->ud);
				lua_pushvalue(pi->L, -1);
				lua_gettable(pi->L, 1);
				if (lua_type(pi->L, -1) != LUA_TNIL)
				{
					int permanent = 101;
					pi->writer(pi->L, &permanent, sizeof(int), pi->ud);
					persist(pi);
					lua_pop(pi->L, 1);
					return;
				}
				else
				{
					lua_pop(pi->L, 1);
				}
				{
					int type = lua_type(pi->L, -1);
					pi->writer(pi->L, &type, sizeof(int), pi->ud);
					switch (lua_type(pi->L, -1))
					{
					case LUA_TBOOLEAN:
						persistboolean(pi);
						break;
					case LUA_TLIGHTUSERDATA:
						persistlightuserdata(pi);
						break;
					case LUA_TNUMBER:
						persistnumber(pi);
						break;
					case LUA_TSTRING:
						persiststring(pi);
						break;
					case LUA_TTABLE:
						persisttable(pi);
						break;
					case LUA_TFUNCTION:
						persistfunction(pi);
						break;
					case LUA_TTHREAD:
						persistthread(pi);
						break;
					case LUA_TPROTO:
						persistproto(pi);
						break;
					case LUA_TUPVAL:
						persistupval(pi);
						break;
					case LUA_TUSERDATA:
						persistuserdata(pi);
						break;
					}
				}
			}
		}
	}

	// A copy of the library's index lookup that does not support the globals, the registry and the upvalues
	static StkId getobject(lua_State* L, int stackpos);

	// Chooses between the literal and the special persistence of an object by its metatable; pushes nothing and returns 1 when the
	// special persistence (a function the metatable's __persist makes) was used
	// FUNCTION: ENGINE 0x10B77B20
	static int persistspecialobject(PersistInfo* pi, int defaction)
	{
		if (!lua_getmetatable(pi->L, -1))
		{
			if (defaction)
			{
				int zero = 0;
				pi->writer(pi->L, &zero, sizeof(int), pi->ud);
				return 0;
			}
			else
			{
				lua_pushstring(pi->L, "Type not literally persistable by default");
				lua_error(pi->L);
			}
		}
		lua_pushstring(pi->L, "__persist");
		lua_rawget(pi->L, -2);
		if (lua_type(pi->L, -1) == LUA_TNIL)
		{
			lua_pop(pi->L, 2);
			if (defaction)
			{
				int zero = 0;
				pi->writer(pi->L, &zero, sizeof(int), pi->ud);
				return 0;
			}
			else
			{
				lua_pushstring(pi->L, "Type not literally persistable by default");
				lua_error(pi->L);
				return 0;
			}
		}
		else if (lua_type(pi->L, -1) == LUA_TBOOLEAN)
		{
			if (lua_toboolean(pi->L, -1))
			{
				int zero;
				lua_pop(pi->L, 2);
				zero = 0;
				pi->writer(pi->L, &zero, sizeof(int), pi->ud);
				return 0;
			}
			else
			{
				lua_pushstring(pi->L, "Metatable forbade persistence");
				lua_error(pi->L);
				return 0;
			}
		}
		else
		{
			if (lua_type(pi->L, -1) != LUA_TFUNCTION)
			{
				lua_pushstring(pi->L, "__persist not nil, boolean, or function");
				lua_error(pi->L);
			}
		}
		lua_pushvalue(pi->L, -3);
		lua_call(pi->L, 1, 1);
		if (lua_type(pi->L, -1) != LUA_TFUNCTION)
		{
			lua_pushstring(pi->L, "__persist function did not return a function");
			lua_error(pi->L);
		}
		{
			int one = 1;
			pi->writer(pi->L, &one, sizeof(int), pi->ud);
			persist(pi);
			lua_pop(pi->L, 2);
			return 1;
		}
	}

	// FUNCTION: ENGINE 0x10B77A30
	static void persisttable(PersistInfo* pi)
	{
		if (persistspecialobject(pi, 1))
		{
		}
		else
		{
			if (!lua_getmetatable(pi->L, -1))
			{
				lua_pushnil(pi->L);
			}
			persist(pi);
			lua_pop(pi->L, 1);
			lua_pushnil(pi->L);
			while (lua_next(pi->L, -2))
			{
				lua_pushvalue(pi->L, -2);
				persist(pi);
				lua_pop(pi->L, 1);
				persist(pi);
				lua_pop(pi->L, 1);
			}
			lua_pushnil(pi->L);
			persist(pi);
			lua_pop(pi->L, 1);
		}
	}

	// FUNCTION: ENGINE 0x10B77DA0
	static void persistuserdata(PersistInfo* pi)
	{
		if (persistspecialobject(pi, 0))
		{
			return;
		}
		else
		{
			size_t length = uvalue(getobject(pi->L, -1))->len;
			pi->writer(pi->L, &length, sizeof(size_t), pi->ud);
			pi->writer(pi->L, lua_touserdata(pi->L, -1), length, pi->ud);
			if (!lua_getmetatable(pi->L, -1))
			{
				lua_pushnil(pi->L);
			}
			persist(pi);
			lua_pop(pi->L, 1);
		}
	}

	// FUNCTION: ENGINE 0x10B77E70
	static StkId getobject(lua_State* L, int stackpos)
	{
		if (stackpos > 0)
		{
			return L->base + stackpos - 1;
		}
		else
		{
			return L->top + stackpos;
		}
	}

	static void pushproto(lua_State* L, Proto* proto);
	static void pushupval(lua_State* L, UpVal* upval);

	// FUNCTION: ENGINE 0x10B77EA0
	static void persistfunction(PersistInfo* pi)
	{
		Closure* cl = clvalue(getobject(pi->L, -1));
		if (cl->c.isC)
		{
			lua_pushstring(pi->L, "Attempt to persist a C function");
			lua_error(pi->L);
		}
		else
		{
			pi->writer(pi->L, &cl->l.p->nups, sizeof(lu_byte), pi->ud);
			pushproto(pi->L, cl->l.p);
			persist(pi);
			lua_pop(pi->L, 1);
			{
				int i;
				for (i = 0; i < cl->l.p->nups; i++)
				{
					pushupval(pi->L, cl->l.upvals[i]);
					persist(pi);
					lua_pop(pi->L, 1);
				}
			}
			lua_getfenv(pi->L, -1);
			if (lua_equal(pi->L, -1, LUA_GLOBALSINDEX))
			{
				lua_pop(pi->L, 1);
				lua_pushnil(pi->L);
			}
			persist(pi);
			lua_pop(pi->L, 1);
		}
	}

	// FUNCTION: ENGINE 0x10B78000
	static void pushproto(lua_State* L, Proto* proto)
	{
		TValue o;
		setptvalue(L, &o, proto);
		luaA_pushobject(L, &o);
	}

	// FUNCTION: ENGINE 0x10B78040
	static void pushupval(lua_State* L, UpVal* upval)
	{
		TValue o;
		setupvalue(L, &o, upval);
		luaA_pushobject(L, &o);
	}

	static UpVal* toupval(lua_State* L, int stackpos);

	// FUNCTION: ENGINE 0x10B78080
	static void persistupval(PersistInfo* pi)
	{
		UpVal* uv = toupval(pi->L, -1);
		lua_pop(pi->L, 1);
		luaA_pushobject(pi->L, uv->v);
		persist(pi);
	}

	// FUNCTION: ENGINE 0x10B780D0
	static UpVal* toupval(lua_State* L, int stackpos)
	{
		return (UpVal*)getobject(L, stackpos)->value.gc;
	}

	static Proto* toproto(lua_State* L, int stackpos);

	// FUNCTION: ENGINE 0x10B780F0
	static void persistproto(PersistInfo* pi)
	{
		Proto* p = toproto(pi->L, -1);
		int i;
		int j;
		pi->writer(pi->L, &p->sizek, sizeof(int), pi->ud);
		for (i = 0; i < p->sizek; i++)
		{
			luaA_pushobject(pi->L, &p->k[i]);
			persist(pi);
			lua_pop(pi->L, 1);
		}
		pi->writer(pi->L, &p->sizep, sizeof(int), pi->ud);
		for (j = 0; j < p->sizep; j++)
		{
			pushproto(pi->L, p->p[j]);
			persist(pi);
			lua_pop(pi->L, 1);
		}
		pi->writer(pi->L, &p->sizecode, sizeof(int), pi->ud);
		pi->writer(pi->L, p->code, sizeof(Instruction) * p->sizecode, pi->ud);
		pi->writer(pi->L, &p->nups, sizeof(lu_byte), pi->ud);
		pi->writer(pi->L, &p->numparams, sizeof(lu_byte), pi->ud);
		pi->writer(pi->L, &p->is_vararg, sizeof(lu_byte), pi->ud);
		pi->writer(pi->L, &p->maxstacksize, sizeof(lu_byte), pi->ud);
	}

	// FUNCTION: ENGINE 0x10B782D0
	static Proto* toproto(lua_State* L, int stackpos)
	{
		return (Proto*)getobject(L, stackpos)->value.gc;
	}

	static int pushstack(lua_State* L2, lua_State* L);

	// FUNCTION: ENGINE 0x10B782F0
	static void persistthread(PersistInfo* pi)
	{
		unsigned int stackpos;
		lua_State* L2 = lua_tothread(pi->L, -1);
		if (pi->L == L2)
		{
			lua_pushstring(pi->L, "Can't persist currently running thread");
			lua_error(pi->L);
		}
		else
		{
			unsigned int numframes;
			unsigned int i;
			stackpos = pushstack(L2, pi->L);
			pi->writer(pi->L, &stackpos, sizeof(int), pi->ud);
			for (; stackpos > 0; stackpos--)
			{
				persist(pi);
				lua_pop(pi->L, 1);
			}
			numframes = (L2->ci - L2->base_ci) + 1;
			pi->writer(pi->L, &numframes, sizeof(int), pi->ud);
			for (i = 0; i < numframes; i++)
			{
				int stackbase;
				CallInfo* callinfo;
				int f;
				int toppos;
				int codepos;
				callinfo = L2->base_ci + i;
				stackbase = callinfo->base - L2->stack;
				f = callinfo->func - L2->stack;
				toppos = callinfo->top - L2->stack;
				codepos = (callinfo != L2->base_ci) ? callinfo->savedpc - clvalue(callinfo->func)->l.p->code : 0;
				pi->writer(pi->L, &stackbase, sizeof(int), pi->ud);
				pi->writer(pi->L, &f, sizeof(int), pi->ud);
				pi->writer(pi->L, &toppos, sizeof(int), pi->ud);
				pi->writer(pi->L, &callinfo->nresults, sizeof(int), pi->ud);
				pi->writer(pi->L, &codepos, sizeof(int), pi->ud);
			}
			{
				int lbase = L2->base - L2->stack;
				int top2 = L2->top - L2->stack;
				UpVal* openup;
				UpVal* upv;
				pi->writer(pi->L, &L2->status, sizeof(lu_byte), pi->ud);
				pi->writer(pi->L, &lbase, sizeof(int), pi->ud);
				pi->writer(pi->L, &top2, sizeof(int), pi->ud);
				pi->writer(pi->L, &L2->errfunc, sizeof(int), pi->ud);
				for (openup = (UpVal*)L2->openupval; openup != NULL; openup = (UpVal*)upv->next)
				{
					int offset;
					upv = openup;
					pushupval(pi->L, upv);
					persist(pi);
					lua_pop(pi->L, 1);
					offset = upv->v - L2->stack;
					pi->writer(pi->L, &offset, sizeof(int), pi->ud);
				}
				lua_pushnil(pi->L);
				persist(pi);
				lua_pop(pi->L, 1);
			}
		}
	}

	// FUNCTION: ENGINE 0x10B78660
	static int pushstack(lua_State* L2, lua_State* L)
	{
		StkId o;
		for (o = L2->top - 1; o >= L2->stack; o--)
		{
			setobj2s(L, L->top, o);
			L->top++;
		}
		return L2->top - L2->stack;
	}

	// FUNCTION: ENGINE 0x10B786E0
	static void persistboolean(PersistInfo* pi)
	{
		int b = lua_toboolean(pi->L, -1);
		pi->writer(pi->L, &b, sizeof(int), pi->ud);
	}

	// FUNCTION: ENGINE 0x10B78720
	static void persistlightuserdata(PersistInfo* pi)
	{
		if (persistspecialobject(pi, 1))
		{
			return;
		}
		else
		{
			void* p = lua_touserdata(pi->L, -1);
			pi->writer(pi->L, &p, sizeof(void*), pi->ud);
		}
	}

	// FUNCTION: ENGINE 0x10B78770
	static void persistnumber(PersistInfo* pi)
	{
		lua_Number n = lua_tonumber(pi->L, -1);
		pi->writer(pi->L, &n, sizeof(lua_Number), pi->ud);
	}

	// FUNCTION: ENGINE 0x10B787B0
	static void persiststring(PersistInfo* pi)
	{
		int length = lua_strlen(pi->L, -1);
		pi->writer(pi->L, &length, sizeof(int), pi->ud);
		pi->writer(pi->L, (char*)lua_tostring(pi->L, -1), length, pi->ud);
	}

	// What the Lua function persist writes into: a block that grows
	struct Buffer
	{
		char* data;
		int length;
	};

	static int bufwriter(lua_State* L, const void* p, size_t sz, void* ud);

	// FUNCTION: ENGINE 0x10B78820
	static int pluto_persist(lua_State* L)
	{
		Buffer buf;
		buf.data = NULL;
		buf.length = 0;
		lua_settop(L, 2);
		luaL_checktype(L, 1, LUA_TTABLE);
		luaL_checktype(L, 1, LUA_TTABLE);
		LuaSerialize(L, (int)bufwriter, (int)&buf);
		lua_settop(L, 0);
		lua_pushlstring(L, buf.data, buf.length);
		luaM_freearray(L, buf.data, buf.length, char);
		return 1;
	}

	// FUNCTION: ENGINE 0x10B788E0
	static int bufwriter(lua_State* L, const void* p, size_t sz, void* ud)
	{
		const char* src = (const char*)p;
		Buffer* buf = (Buffer*)ud;
		luaM_reallocvector(L, buf->data, buf->length, buf->length + sz, char);
		while (sz != 0)
		{
			buf->data[buf->length] = *src;
			buf->length++;
			src++;
			sz--;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10B78990
	void LuaDeserialize(lua_State* L, int reader, int ud)
	{
		UnpersistInfo upi;
		upi.L = L;
		luaZ_init(L, &upi.zio, (lua_Reader)reader, (void*)ud);
		lua_newtable(L);
		lua_gc(L, LUA_GCSTOP, 0);
		unpersist(&upi);
		lua_gc(L, LUA_GCRESTART, 0);
		lua_replace(L, 2);
	}

	// FUNCTION: ENGINE 0x10B78A10
	static void unpersist(UnpersistInfo* upi)
	{
		int first;
		int stacktop = lua_gettop(upi->L);
		int type;
		int ref;
		stacktop = stacktop;
		luaZ_read(&upi->zio, &first, sizeof(int));
		if (first)
		{
			luaZ_read(&upi->zio, &ref, sizeof(int));
			luaZ_read(&upi->zio, &type, sizeof(int));
			switch (type)
			{
			case LUA_TBOOLEAN:
				unpersistboolean(upi);
				break;
			case LUA_TLIGHTUSERDATA:
				unpersistlightuserdata(upi);
				break;
			case LUA_TNUMBER:
				unpersistnumber(upi);
				break;
			case LUA_TSTRING:
				unpersiststring(upi);
				break;
			case LUA_TTABLE:
				unpersisttable(ref, upi);
				break;
			case LUA_TFUNCTION:
				unpersistfunction(ref, upi);
				break;
			case LUA_TTHREAD:
				unpersistthread(ref, upi);
				break;
			case LUA_TPROTO:
				unpersistproto(ref, upi);
				break;
			case LUA_TUPVAL:
				unpersistupval(ref, upi);
				break;
			case LUA_TUSERDATA:
				unpersistuserdata(ref, upi);
				break;
			case 101:
				unpersistpermanent(ref, upi);
				break;
			}
			registerobject(ref, upi);
		}
		else
		{
			int reference;
			luaZ_read(&upi->zio, &reference, sizeof(int));
			if (reference == 0)
			{
				lua_pushnil(upi->L);
			}
			else
			{
				lua_pushlightuserdata(upi->L, (void*)reference);
				lua_gettable(upi->L, 2);
			}
		}
	}

	// FUNCTION: ENGINE 0x10B78C60
	static void registerobject(int ref, UnpersistInfo* upi)
	{
		lua_pushlightuserdata(upi->L, (void*)ref);
		lua_pushvalue(upi->L, -2);
		lua_settable(upi->L, 2);
	}

	// FUNCTION: ENGINE 0x10B78CA0
	static void unpersistboolean(UnpersistInfo* upi)
	{
		int b;
		verify(luaZ_read(&upi->zio, &b, sizeof(int)) == 0);
		lua_pushboolean(upi->L, b);
	}

	// FUNCTION: ENGINE 0x10B78CF0
	static void unpersistlightuserdata(UnpersistInfo* upi)
	{
		int special;
		verify(luaZ_read(&upi->zio, &special, sizeof(int)) == 0);
		if (special)
		{
			unpersist(upi);
			lua_call(upi->L, 0, 1);
		}
		else
		{
			void* p;
			verify(luaZ_read(&upi->zio, &p, sizeof(void*)) == 0);
			lua_pushlightuserdata(upi->L, p);
		}
	}

	// FUNCTION: ENGINE 0x10B78D80
	static void unpersistnumber(UnpersistInfo* upi)
	{
		lua_Number n;
		verify(luaZ_read(&upi->zio, &n, sizeof(lua_Number)) == 0);
		lua_pushnumber(upi->L, n);
	}

	// FUNCTION: ENGINE 0x10B78DD0
	static void unpersiststring(UnpersistInfo* upi)
	{
		int length;
		char* string;
		verify(luaZ_read(&upi->zio, &length, sizeof(int)) == 0);
		string = luaM_newvector(upi->L, length, char);
		verify(luaZ_read(&upi->zio, string, length) == 0);
		lua_pushlstring(upi->L, string, length);
		luaM_freearray(upi->L, string, length, char);
	}

	static void unpersistliteraltable(int ref, UnpersistInfo* upi);
	static void unpersistspecialtable(int ref, UnpersistInfo* upi);

	// FUNCTION: ENGINE 0x10B78EB0
	static void unpersisttable(int ref, UnpersistInfo* upi)
	{
		int special;
		verify(luaZ_read(&upi->zio, &special, sizeof(int)) == 0);
		if (special)
		{
			unpersistspecialtable(ref, upi);
		}
		else
		{
			unpersistliteraltable(ref, upi);
		}
	}

	// FUNCTION: ENGINE 0x10B78F10
	static void unpersistspecialtable(int ref, UnpersistInfo* upi)
	{
		unpersist(upi);
		lua_call(upi->L, 0, 1);
	}

	// FUNCTION: ENGINE 0x10B78F40
	static void unpersistliteraltable(int ref, UnpersistInfo* upi)
	{
		lua_newtable(upi->L);
		registerobject(ref, upi);
		unpersist(upi);
		if (lua_type(upi->L, -1) == LUA_TTABLE)
		{
			lua_setmetatable(upi->L, -2);
		}
		else
		{
			lua_pop(upi->L, 1);
		}
		while (1)
		{
			unpersist(upi);
			if (lua_type(upi->L, -1) == LUA_TNIL)
			{
				lua_pop(upi->L, 1);
				break;
			}
			unpersist(upi);
			lua_rawset(upi->L, -3);
		}
	}

	static void pushclosure(lua_State* L, Closure* cl);
	static UpVal* boxupval(lua_State* L, int stackpos);
	static Proto* makefakeproto(lua_State* L, lu_byte nups);
	static void unboxupval(lua_State* L);

	// FUNCTION: ENGINE 0x10B79010
	static void unpersistfunction(int ref, UnpersistInfo* upi)
	{
		lu_byte nupvalues;
		Closure* cl;
		int i;
		verify(luaZ_read(&upi->zio, &nupvalues, sizeof(lu_byte)) == 0);
		cl = luaF_newLclosure(upi->L, nupvalues, hvalue(gt(upi->L)));
		pushclosure(upi->L, cl);
		cl->l.p = makefakeproto(upi->L, nupvalues);
		lua_pushnil(upi->L);
		for (i = 0; i < nupvalues; i++)
		{
			cl->l.upvals[i] = boxupval(upi->L, -1);
		}
		lua_pop(upi->L, 1);
		registerobject(ref, upi);
		unpersist(upi);
		cl->l.p = toproto(upi->L, -1);
		lua_pop(upi->L, 1);
		for (i = 0; i < nupvalues; i++)
		{
			unpersist(upi);
			unboxupval(upi->L);
			cl->l.upvals[i] = toupval(upi->L, -1);
			lua_pop(upi->L, 1);
		}
		unpersist(upi);
		if (lua_type(upi->L, -1) != LUA_TNIL)
		{
			lua_setfenv(upi->L, -2);
		}
		else
		{
			lua_pop(upi->L, 1);
		}
	}

	// FUNCTION: ENGINE 0x10B791D0
	static void pushclosure(lua_State* L, Closure* cl)
	{
		TValue o;
		setclvalue(L, &o, cl);
		luaA_pushobject(L, &o);
	}

	// FUNCTION: ENGINE 0x10B79210
	static UpVal* boxupval(lua_State* L, int stackpos)
	{
		UpVal* uv = luaM_new(L, UpVal);
		luaC_link(L, obj2gco(uv), LUA_TUPVAL);
		uv->tt = LUA_TUPVAL;
		uv->v = &uv->u.value;
		uv->u.value.value.gc = NULL;
		uv->u.value.tt = LUA_TNIL;
		setobj(L, uv->v, getobject(L, stackpos));
		return uv;
	}

	// FUNCTION: ENGINE 0x10B792A0
	static Proto* makefakeproto(lua_State* L, lu_byte nups)
	{
		Proto* p = luaF_newproto(L);
		p->sizelineinfo = 1;
		p->lineinfo = luaM_newvector(L, 1, int);
		p->lineinfo[0] = 1;
		p->sizecode = 1;
		p->code = luaM_newvector(L, 1, Instruction);
		p->code[0] = CREATE_ABC(OP_RETURN, 0, 1, 0);
		p->source = luaS_newlstr(L, "", 0);
		p->maxstacksize = 2;
		p->nups = nups;
		p->sizek = 0;
		p->sizep = 0;
		return p;
	}

	// FUNCTION: ENGINE 0x10B793A0
	static void unboxupval(lua_State* L)
	{
		Closure* cl = clvalue(getobject(L, -1));
		UpVal* uv = cl->l.upvals[0];
		lua_pop(L, 1);
		pushupval(L, uv);
	}

	static void makeupvalclosure(lua_State* L);
	static void fillupvalclosure(lua_State* L);

	// FUNCTION: ENGINE 0x10B793F0
	static void unpersistupval(int ref, UnpersistInfo* upi)
	{
		UpVal* uv;
		makeupvalclosure(upi->L);
		registerobject(ref, upi);
		unpersist(upi);
		uv = boxupval(upi->L, -1);
		lua_pop(upi->L, 1);
		pushupval(upi->L, uv);
		fillupvalclosure(upi->L);
	}

	// FUNCTION: ENGINE 0x10B79470
	static void makeupvalclosure(lua_State* L)
	{
		Closure* cl = luaF_newLclosure(L, 1, hvalue(gt(L)));
		pushclosure(L, cl);
		cl->l.p = makefakeproto(L, 1);
		lua_pushnil(L);
		cl->l.upvals[0] = boxupval(L, -1);
		lua_pop(L, 1);
	}

	// FUNCTION: ENGINE 0x10B794F0
	static void fillupvalclosure(lua_State* L)
	{
		Closure* cl = clvalue(getobject(L, -2));
		UpVal* uv = toupval(L, -1);
		lua_pop(L, 1);
		cl->l.p->nups = 1;
		cl->l.upvals[0] = uv;
	}

	static void unlinkobject(lua_State* L, GCObject* o);

	// FUNCTION: ENGINE 0x10B79540
	static void unpersistproto(int ref, UnpersistInfo* upi)
	{
		TString* source = luaS_newlstr(upi->L, "", 0);
		Proto* p = luaF_newproto(upi->L);
		int i;
		int sizek;
		int sizep;
		p->source = source;
		p->sizecode = 1;
		p->code = luaM_newvector(upi->L, 1, Instruction);
		p->code[0] = CREATE_ABC(OP_RETURN, 0, 1, 0);
		p->maxstacksize = 2;
		p->sizek = 0;
		p->sizep = 0;
		pushproto(upi->L, p);
		verify(luaZ_read(&upi->zio, &sizek, sizeof(int)) == 0);
		luaM_reallocvector(upi->L, p->k, 0, sizek, TValue);
		for (i = 0; i < sizek; i++)
		{
			unpersist(upi);
			setobj2s(upi->L, &p->k[i], getobject(upi->L, -1));
			p->sizek++;
			lua_pop(upi->L, 1);
		}
		verify(luaZ_read(&upi->zio, &sizep, sizeof(int)) == 0);
		luaM_reallocvector(upi->L, p->p, 0, sizep, Proto*);
		for (i = 0; i < sizep; i++)
		{
			unpersist(upi);
			p->p[i] = toproto(upi->L, -1);
			p->sizep++;
			lua_pop(upi->L, 1);
		}
		verify(luaZ_read(&upi->zio, &p->sizecode, sizeof(int)) == 0);
		luaM_reallocvector(upi->L, p->code, 1, p->sizecode, Instruction);
		verify(luaZ_read(&upi->zio, p->code, sizeof(Instruction) * p->sizecode) == 0);
		verify(luaZ_read(&upi->zio, &p->nups, sizeof(lu_byte)) == 0);
		verify(luaZ_read(&upi->zio, &p->numparams, sizeof(lu_byte)) == 0);
		verify(luaZ_read(&upi->zio, &p->is_vararg, sizeof(lu_byte)) == 0);
		verify(luaZ_read(&upi->zio, &p->maxstacksize, sizeof(lu_byte)) == 0);
	}

	// FUNCTION: ENGINE 0x10B79910
	static void unpersistthread(int ref, UnpersistInfo* upi)
	{
		int highest = 0;
		lua_State* thread = lua_newthread(upi->L);
		unsigned int i;
		unsigned int size;
		registerobject(ref, upi);
		verify(luaZ_read(&upi->zio, &size, sizeof(int)) == 0);
		luaD_growstack(thread, size);
		thread->top--;
		for (i = 0; i < size; i++)
		{
			unpersist(upi);
		}
		lua_xmove(upi->L, thread, size);
		{
			unsigned int k2;
			unsigned int numci;
			verify(luaZ_read(&upi->zio, &numci, sizeof(int)) == 0);
			luaD_reallocCI(thread, numci * 2);
			for (k2 = 0; k2 < numci; k2++)
			{
				int basepos;
				CallInfo* callinfo;
				int stackfunc;
				unsigned int stacktop;
				int codepos;
				callinfo = thread->base_ci + k2;
				verify(luaZ_read(&upi->zio, &basepos, sizeof(int)) == 0);
				verify(luaZ_read(&upi->zio, &stackfunc, sizeof(int)) == 0);
				verify(luaZ_read(&upi->zio, &stacktop, sizeof(int)) == 0);
				verify(luaZ_read(&upi->zio, &callinfo->nresults, sizeof(int)) == 0);
				verify(luaZ_read(&upi->zio, &codepos, sizeof(int)) == 0);
				if (highest < stacktop)
				{
					highest = stacktop;
				}
				callinfo->base = thread->stack + basepos;
				callinfo->func = thread->stack + stackfunc;
				callinfo->top = thread->stack + stacktop;
				callinfo->savedpc = (callinfo != thread->base_ci) ? clvalue(callinfo->func)->l.p->code + codepos : 0;
				callinfo->tailcalls = 0;
				thread->ci = callinfo;
			}
		}
		thread->savedpc = thread->ci->savedpc;
		{
			int lbase;
			int top2;
			verify(luaZ_read(&upi->zio, &thread->status, sizeof(lu_byte)) == 0);
			verify(luaZ_read(&upi->zio, &lbase, sizeof(int)) == 0);
			verify(luaZ_read(&upi->zio, &top2, sizeof(int)) == 0);
			verify(luaZ_read(&upi->zio, &thread->errfunc, sizeof(int)) == 0);
			thread->base = thread->stack + lbase;
			thread->top = thread->stack + top2;
			{
				GCObject** prev = (GCObject**)&thread->openupval;
				global_State* glob = G(thread);
				UpVal* uv;
				while (1)
				{
					unpersist(upi);
					if (lua_type(upi->L, -1) == LUA_TNIL)
					{
						lua_pop(upi->L, 1);
						break;
					}
					unboxupval(upi->L);
					uv = toupval(upi->L, -1);
					lua_pop(upi->L, 1);
					{
						int upvaltop;
						verify(luaZ_read(&upi->zio, &upvaltop, sizeof(int)) == 0);
						uv->v = thread->stack + upvaltop;
						unlinkobject(upi->L, obj2gco(uv));
						uv->marked = luaC_white(glob);
						*prev = obj2gco(uv);
						prev = &uv->next;
						uv->u.l.prev = &G(thread)->uvhead;
						uv->u.l.next = G(thread)->uvhead.u.l.next;
						uv->u.l.next->u.l.prev = uv;
						G(thread)->uvhead.u.l.next = uv;
					}
				}
				*prev = NULL;
			}
			luaD_checkstack(thread, highest);
			{
				StkId o;
				for (o = thread->top; o <= thread->top + highest; o++)
				{
					setnilvalue(o);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10B79DD0
	static void unlinkobject(lua_State* L, GCObject* o)
	{
		if (G(L)->rootgc == o)
		{
			G(L)->rootgc = G(L)->rootgc->gch.next;
		}
		else
		{
			GCObject* p = G(L)->rootgc;
			while (p->gch.next != o)
			{
				p = p->gch.next;
			}
			p->gch.next = p->gch.next->gch.next;
		}
	}

	// FUNCTION: ENGINE 0x10B79E30
	static void unpersistuserdata(int ref, UnpersistInfo* upi)
	{
		int special;
		verify(luaZ_read(&upi->zio, &special, sizeof(int)) == 0);
		if (special)
		{
			unpersist(upi);
			lua_call(upi->L, 0, 1);
		}
		else
		{
			size_t length;
			verify(luaZ_read(&upi->zio, &length, sizeof(size_t)) == 0);
			lua_newuserdata(upi->L, length);
			registerobject(ref, upi);
			verify(luaZ_read(&upi->zio, lua_touserdata(upi->L, -1), length) == 0);
			unpersist(upi);
			lua_setmetatable(upi->L, -2);
		}
	}

	// FUNCTION: ENGINE 0x10B79F20
	static void unpersistpermanent(int ref, UnpersistInfo* upi)
	{
		unpersist(upi);
		lua_gettable(upi->L, 1);
	}

	static const char* bufreader(lua_State* L, void* ud, size_t* sz);

	// FUNCTION: ENGINE 0x10B79F50
	static int pluto_unpersist(lua_State* L)
	{
		const char* s;
		size_t len;
		char* copy;
		Buffer buffer;
		lua_settop(L, 2);
		s = luaL_checklstring(L, 2, &len);
		copy = luaM_newvector(L, len, char);
		memcpy(copy, s, len);
		buffer.data = copy;
		buffer.length = len;
		lua_pop(L, 1);
		luaL_checktype(L, 1, LUA_TTABLE);
		LuaDeserialize(L, (int)bufreader, (int)&buffer);
		luaM_freearray(L, copy, len, char);
		return 1;
	}

	// FUNCTION: ENGINE 0x10B7A050
	static const char* bufreader(lua_State* L, void* ud, size_t* sz)
	{
		Buffer* buf = (Buffer*)ud;
		if (buf->length == 0)
		{
			return NULL;
		}
		*sz = buf->length;
		buf->length = 0;
		return buf->data;
	}

	static const luaL_Reg pluto_funcs[] = {
		{"persist", pluto_persist},
		{"unpersist", pluto_unpersist},
		{NULL, NULL}};

	// FUNCTION: ENGINE 0x10B7A090
	int luaopen_pluto(lua_State* L)
	{
		luaI_openlib(L, "pluto", pluto_funcs, 0);
		return 1;
	}
}
