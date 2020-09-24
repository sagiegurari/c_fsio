#ifndef __FSIO_H__
#define __FSIO_H__

#include <stdbool.h>

/**
 * Writes the provided text into the file, deleting any previous content.
 * In case of any error or invalid input, this function will return false.
 */
bool fsio_write_text_file(char * /* file */, char * /* text */);

/**
 * Reads and returns the text from the provided file.
 * In case of any error or invalid input, this function will return NULL.
 */
char *fsio_read_text_file(char * /*file*/);

#endif

