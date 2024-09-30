#include <luaconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//this is here cuz IDK how to properly configure clangd for vscode
#include <luajit-2.1/lua.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "logger.h"
#include "util.h"

void get_lua_location(lua_State* L, char* buffer, size_t buffer_size) {
    lua_Debug ar;
    if (lua_getstack(L, 1, &ar)) {
        lua_getinfo(L, "Sln", &ar); 
        snprintf(buffer, buffer_size, "%s:%d", ar.short_src, ar.currentline);
    } else {
        snprintf(buffer, buffer_size, "Unknown");
    }
}

int api_log_info(lua_State* state){
    const char* message = lua_tostring(state, 1);
    char location[100];
    get_lua_location(state, location, 100);

    log_info(message, location);

    return 0;
}

int api_log_err(lua_State* state){
    const char* message = lua_tostring(state, 1);
    char location[100];
    get_lua_location(state, location, 100);

    log_err(message, location);

    return 0;
}

int recipe_build_func(lua_State* state) {
    if (!lua_istable(state, 1)) {
        return luaL_error(state, "Recipe not a table or called with a . not a :");
    }

    lua_getfield(state, 1, "compiler");
    if (lua_isnil(state, -1)) {
        goto error;
    }
    lua_pop(state, 1);


    lua_getfield(state, 1, "linker");
    if (lua_isnil(state, -1)) {
        goto error;
    }
    lua_pop(state, 1);


    lua_getfield(state, 1, "src_dirs");
    if (!lua_istable(state, -1)) {
        goto error;
    }
    if (lua_objlen(state, -1) == 0) {
        goto error;
    }

    return 0;

    error:
        lua_pop(state, 1);
        return luaL_error(state, "Recipe is not properly filled out");
}

int api_new_recipe(lua_State* state) {
    lua_newtable(state);

    lua_pushstring(state, "compiler");
    lua_pushnil(state);
    lua_settable(state, -3);

    lua_pushstring(state, "linker");
    lua_pushnil(state);
    lua_settable(state, -3);

    lua_pushstring(state, "inc_dirs");
    lua_newtable(state);
    lua_settable(state, -3);

    lua_pushstring(state, "lib_dirs");
    lua_newtable(state);
    lua_settable(state, -3);

    lua_pushstring(state, "src_dirs");
    lua_newtable(state);
    lua_settable(state, -3);

    lua_pushstring(state, "comp_flags");
    lua_newtable(state);
    lua_settable(state, -3);

    lua_pushstring(state, "link_flags");
    lua_newtable(state);
    lua_settable(state, -3);

    lua_pushstring(state, "build_func");
    lua_pushcfunction(state, recipe_build_func);
    lua_settable(state, -3);

    // the table is already on top of the stack
    return 1;
}


int api_use_template(lua_State* state){
    char location[100];
    get_lua_location(state, location, 100);

    log_info("called ab.use_template",location);
    return 0;
}

int api_add_src_dir(lua_State* state) {
    if (lua_gettop(state) != 2) {
        return luaL_error(state, "Expected 2 arguments: recipe and path");
    }
    luaL_checktype(state, -2, LUA_TTABLE);
    luaL_checktype(state, -1, LUA_TSTRING);

    lua_getfield(state, 1, "src_dirs");

    if (!lua_istable(state, -1)) {
        return luaL_error(state, "recipe.src_dirs must be a table");
    }

    size_t len = lua_objlen(state, -1);

    lua_pushvalue(state, 2);
    lua_rawseti(state, -2, len + 1);


    // Clean up by popping the src_dirs table from the stack
    lua_pop(state, 1);

    return 0;  // Return 0 values to Lua
}


bool ab_runscript(const char* path,int argc,const char** argv){
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);

    lua_pushcfunction(L, api_log_info);
    lua_setfield(L, -2, "log_info");

    lua_pushcfunction(L, api_log_err);
    lua_setfield(L, -2, "log_err");

    lua_pushcfunction(L, api_new_recipe);
    lua_setfield(L, -2, "new_recipe");

    lua_pushcfunction(L, api_use_template);
    lua_setfield(L, -2, "use_template");

    lua_pushcfunction(L, api_add_src_dir);
    lua_setfield(L, -2, "add_src_dir");

    // Set 'ab' table as a global object in Lua
    lua_setglobal(L, "ab");

    if (luaL_dofile(L, path) != LUA_OK) {
        const char* old = lua_tostring(L, -1);
        const char* raw = strdup(old);

        char* colon = strchr(strchr(raw,':')+1,':');
        if(colon == NULL){
            log_err(raw, __CUR_LOC);
            free(raw);
            lua_close(L);
            return false;
        }
        *colon = 0;

        log_err(colon+2, raw);

        free(raw);
        lua_close(L);
        return false;
    }

    lua_getglobal(L, "_default");

    if(!lua_isfunction(L, -1)){
        log_err("_default does not exist",__CUR_LOC);
        lua_close(L);
        return false;
    }

    if (lua_pcall(L,0,0,0) != LUA_OK) {
        const char* old = lua_tostring(L, -1);
        const char* raw = strdup(old);

        char* colon = strchr(strchr(raw,':')+1,':');
        if(colon == NULL){
            log_err(raw, __CUR_LOC);
            free(raw);
            lua_close(L);
            return false;
        }
        *colon = 0;

        log_err(colon+2, raw);

        free(raw);
        lua_close(L);
        return false;
    }

    lua_close(L);
    return true;
}