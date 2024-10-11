#ifndef __SRC_DISCOVERY_H__
#define __SRC_DISCOVERY_H__

/*
 * @brief Gets all files in `src_dirs` with extension `src_extension`
 * @param `src_dirs` The directories to search in
 * @param `src_extension` The extension of the files to search for
 * @return An array of strings containing the paths of the files
*/
char** get_files(char** src_dirs,char* src_extension);

#endif // __SRC_DISCOVERY_H__