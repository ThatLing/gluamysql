#pragma once
#include "lua.hpp"
#include "luapromise.h"
#include "mysql.h"
#include "luadatabase.h"

namespace gluamysql {
	class LuaAction : public LuaPromise {
	public:
		LuaAction(lua_State* L) : LuaPromise{ L } {

		}

		virtual bool Query(lua_State *L, LuaDatabase *db) = 0;
		virtual void Finish(lua_State *L, LuaDatabase *db) = 0;

		void Free(lua_State *L) override {
			LuaPromise::Free(L);
		}

		void Reject(lua_State *L, LuaDatabase* db) {
			PushReject(L);
			lua_pushstring(L, mysql_error(db->instance));
			lua_call(L, 1, 0);
		}
	};
}