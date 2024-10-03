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
/*
 * @brief Gets the current location of the Lua script
 * @param `L` The Lua state
 * @param `buffer` The buffer to store the location in
 * @param `buffer_size` The size of the buffer
*/
void get_lua_location(lua_State* L, char* buffer, size_t buffer_size) {
    lua_Debug ar;
    if (lua_getstack(L, 1, &ar)) {
        lua_getinfo(L, "Sln", &ar); 
        snprintf(buffer, buffer_size, "%s:%d", ar.short_src, ar.currentline);
    } else {
        snprintf(buffer, buffer_size, "Unknown");
    }
}

/*
 * @brief Lua API function for logging info
 * @param `state` The Lua state
 * @param `message` (From Lua) The message to log
*/
int api_log_info(lua_State* state){
    const char* message = lua_tostring(state, 1);
    char location[100];
    get_lua_location(state, location, 100);

    log_info(message, location);

    return 0;
}

/*
 * @brief Lua API function for logging errors
 * @param `state` The Lua state
 * @param `message` (From Lua) The message to log
*/
int api_log_err(lua_State* state){
    const char* message = lua_tostring(state, 1);
    char location[100];
    get_lua_location(state, location, 100);

    log_err(message, location);

    return 0;
}
/*
 * @brief Lua API function for building a recipe
 * @param `state` The Lua state
 * @param `self` (From Lua) The recipe to call on
*/
int recipe_build_func(lua_State* state) {
    if (lua_gettop(state) != 1) {
        return luaL_error(state, "too many arguments");
    }
    luaL_checktype(state, -1, LUA_TTABLE);

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

/*
 * @brief Lua API function for adding a source directory
 * @param `state` The Lua state
 * @param `self` (From Lua) The recipe to call on
 * @param `src_dir` (From Lua) The source directory to add
*/
int recipe_add_src_dir(lua_State* state) {
    if (lua_gettop(state) != 2) {
        return luaL_error(state, "no path or called with \".\" instead of \":\"");
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
/*
 * @brief Lua API function for setting the compiler
 * @param `state` The Lua state
 * @param `self` (From Lua) The recipe to call on
 * @param `compiler` (From Lua) The compiler to set
*/
int recipe_set_compiler(lua_State* state) {
    if (lua_gettop(state) != 2) {
        return luaL_error(state, "no path or called with \".\" instead of \":\"");
    }

    luaL_checktype(state, 1, LUA_TTABLE);
    luaL_checktype(state, 2, LUA_TSTRING);

    lua_pushstring(state, "compiler");
    lua_pushvalue(state, 2);
    lua_settable(state, 1);

    lua_pop(state, 1);

    return 0;
}
/*
 * @brief Lua API function for setting the linker
 * @param `state` The Lua state
 * @param `self` (From Lua) The recipe to call on
 * @param `linker` (From Lua) The linker to set
*/
int recipe_set_linker(lua_State* state) {
    if (lua_gettop(state) != 2) {
        return luaL_error(state, "no path or called with \".\" instead of \":\"");
    }

    luaL_checktype(state, 1, LUA_TTABLE);
    luaL_checktype(state, 2, LUA_TSTRING);

    lua_pushstring(state, "linker");
    lua_pushvalue(state, 2);
    lua_settable(state, 1);

    lua_pop(state, 1);

    return 0;
}
/*
 * @brief Lua API function for setting the source extension
 * @param `state` The Lua state
 * @param `self` (From Lua) The recipe to call on
 * @param `src_ext` (From Lua) The source extension to set
*/
int recipe_set_extension(lua_State* state) {
    if (lua_gettop(state) != 2) {
        return luaL_error(state, "no path or called with \".\" instead of \":\"");
    }

    luaL_checktype(state, 1, LUA_TTABLE);
    luaL_checktype(state, 2, LUA_TSTRING);

    lua_pushstring(state, "src_ext");
    lua_pushvalue(state, 2);
    lua_settable(state, 1);

    lua_pop(state, 1);

    return 0;
}
/*
 * @brief Lua API function for creating a new recipe
 * @param `state` The Lua state
 * @return `self` (In Lua) The new recipe
*/
int api_new_recipe(lua_State* state) {
    lua_newtable(state);

    lua_pushstring(state, "compiler");
    lua_pushnil(state);
    lua_settable(state, -3);

    lua_pushstring(state, "linker");
    lua_pushnil(state);
    lua_settable(state, -3);

    lua_pushstring(state, "src_ext");
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

    lua_pushstring(state, "add_src_dir");
    lua_pushcfunction(state, recipe_add_src_dir);
    lua_settable(state, -3);

    lua_pushstring(state, "set_compiler");
    lua_pushcfunction(state, recipe_set_compiler);
    lua_settable(state, -3);

    lua_pushstring(state, "set_linker");
    lua_pushcfunction(state, recipe_set_linker);
    lua_settable(state, -3);

    lua_pushstring(state, "set_extension");
    lua_pushcfunction(state, recipe_set_extension);
    lua_settable(state, -3);

    // the table is already on top of the stack
    return 1;
}

/*
 * @brief Lua API function for using a template
 * @param `state` The Lua state
 * @param `recipe` (In Lua) The recipe ID to get
 * @return `self` (In Lua) The new recipe
*/
int api_use_template(lua_State* state){
    char location[100];
    get_lua_location(state, location, 100);

    log_info("called ab.use_template",location);
    return 0;
}

/*
 * @brief Runs a build script
 * @param `path` The path to the script
 * @param `argc` The number of arguments
 * @param `argv` The arguments
*/
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