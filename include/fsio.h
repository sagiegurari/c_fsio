#ifndef __FSIO_H__
#define __FSIO_H__

#include <stdbool.h>
#include <sys/types.h>

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
bool fsio_mkdir(char * /* directory */, mode_t /*mode*/);

/**
 * Creates a new directory, including any needed parent directory.
 * This function will return true if the directory was created or
 * if it already exists.
 */
bool fsio_mkdirs(char * /* directory */, mode_t /*mode*/);


#endif

