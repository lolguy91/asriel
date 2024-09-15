#include <luaconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "logger.h"

void get_lua_location(lua_State* L, char* buffer, size_t buffer_size) {
    lua_Debug ar;
    if (lua_getstack(L, 1, &ar)) {
        lua_getinfo(L, "Sln", &ar); 
        snprintf(buffer, buffer_size, "%s:%d", ar.short_src, ar.currentline);
    } else {
        snprintf(buffer, buffer_size, "Unknown");
    }
}

int lua_log_info(lua_State* state){
    const char* message = lua_tostring(state, 1);
    char location[100];
    get_lua_location(state, location, 100);

    log_info(message, location);
    
    return 0;
}

int lua_log_err(lua_State* state){
    const char* message = lua_tostring(state, 1);
    char location[100];
    get_lua_location(state, location, 100);

    log_err(message, location);

    return 0;
}

bool ab_runscript(const char* path){
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);

    lua_pushcfunction(L, lua_log_info);
    lua_setfield(L, -2, "log_info");

    lua_pushcfunction(L, lua_log_err);
    lua_setfield(L, -2, "log_err");

    // Set 'ab' table as a global object in Lua
    lua_setglobal(L, "ab");

    if (luaL_dofile(L, path) != LUA_OK) {
        const char* old = lua_tostring(L, -1);
        const char* raw = strdup(old);

        char* colon = strchr(strchr(raw,':')+1,':');
        *colon = 0;

        log_err(colon+2, raw);

        free(raw);
        return false;
    }

    lua_close(L);
    return true;
}