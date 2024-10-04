#ifndef __SCRIPT_H__
#define __SCRIPT_H__
#include <stdint.h>
#include <stdbool.h>


/*
 * @brief Runs a build script
 * @param `path` The path to the script
 * @param `argc` The number of arguments
 * @param `argv` The arguments
*/
bool ab_runscript(const char* path,int argc,char** argv);

#endif // __SCRIPT_H__