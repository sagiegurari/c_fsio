#ifndef __FSIO_H__
#define __FSIO_H__

#include <stdbool.h>
#include <sys/types.h>

/**
 * Returns the basename from the provided path.
 * If the path ends with a path separator, this function will return an empty string.
 * The output must be freed once no longer needed.
 */
char *fsio_basename(char * /* path */);

/**
 * Returns the dirname from the provided path.
 * If the path defines a file with no parent, a '/' value will be returned.
 * The output must be freed once no longer needed.
 */
char *fsio_dirname(char * /* path */);

/**
 * Writes the provided text into the file, deleting any previous content.
 * In case of any error or invalid input, this function will return false.
 * If parent directories do not exist, they will be created.
 */
bool fsio_write_text_file(char * /* file */, char * /* text */);

/**
 * Writes the provided text into the file, appending if file already exists.
 * In case of any error or invalid input, this function will return false.
 * If parent directories do not exist, they will be created.
 */
bool fsio_append_text_file(char * /* file */, char * /* text */);

/**
 * Reads and returns the text from the provided file.
 * In case of any error or invalid input, this function will return NULL.
 */
char *fsio_read_text_file(char * /* file */);

/**
 * Creates an empty file for the provided path.
 * If a file exists in that path, it will be truncated.
 */
bool fsio_create_empty_file(char * /* file */);

/**
 * Copies the source file content to the target file, deleting any previous
 * content in the target file.
 * In case of an error, this function will return false.
 */
bool fsio_copy_file(char * /* source */, char * /* target */);

/**
 * Returns true if the provided path exists.
 */
bool fsio_path_exists(char * /* path */);

/**
 * Returns true if the provided path exists and is a regular file.
 */
bool fsio_file_exists(char * /* path */);

/**
 * Returns true if the provided path exists and is a directory.
 */
bool fsio_dir_exists(char * /* path */);

/**
 * Creates a new directory.
 * This function will return true if the directory was created or
 * if it already exists.
 */
bool fsio_mkdir(char * /* directory */, mode_t /* mode */);

/**
 * Creates a new directory, including any needed parent directory.
 * This function will return true if the directory was created or
 * if it already exists.
 */
bool fsio_mkdirs(char * /* directory */, mode_t /* mode */);

/**
 * Creates a new directory for the parent path of the provided file path.
 * If the provided path defined a directory (ends with /) it will create it as well.
 * This function will return true if the directory was created or
 * if it already exists.
 */
bool fsio_mkdirs_parent(char * /* path */, mode_t /* mode */);

/**
 * Removes file or directory for the provided path.
 * If the path points to an non empty directory, it will delete its content as well.
 */
bool fsio_remove(char * /* path */);

#endif

