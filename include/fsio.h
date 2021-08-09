#ifndef __FSIO_H__
#define __FSIO_H__

#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

enum FsIOError
{
  FSIO_ERROR_INVALID_INPUT,
  FSIO_ERROR_PATH_NOT_FOUND,
  FSIO_ERROR_COPY_FAILED,
};

struct FsIOResult
{
  // True if valid result, false for error
  bool done;
  // 0 for no error, otherwise the error number
  int  error;
  // If true, error points to FsIOErrors, otherwise C errors
  bool fsio_error;
};

struct FsIORecursiveCallbackInfo
{
  void *context;
  char *path;
  bool is_file;
};

struct FsIOReadTextFileOptions
{
  // the limit to read. 0 or negative value for no limit.
  long max_read_limit;
  // if limit is set, if true, read from end, else read from start.
  bool tail;
};

struct FsIOCopyFileOptions
{
  // amount of additional retries in case of write error
  unsigned int write_retries;
  unsigned int retry_interval_seconds;
};

struct FsIOMoveFileOptions
{
  // True to force move via file copy instead of rename
  bool         force_copy;
  // amount of additional retries in case of write error
  unsigned int write_retries;
  unsigned int retry_interval_seconds;
};

/**
 * A 777 permission mode defined as S_IRWXU | S_IRWXG | S_IRWXO
 */
extern const mode_t FSIO_MODE_ALL;

/**
 * Returns the file size.
 * If no input provided, file is not found or path does not point to a file,
 * -1 will be returned.
 */
long fsio_file_size(char * /* file */);

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
 * Reads and returns the text from the provided file.
 * In case of any error or invalid input, this function will return NULL.
 */
char *fsio_read_text_file_with_options(char * /* file */, struct FsIOReadTextFileOptions);

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
 * Copies the source file content to the target file, deleting any previous
 * content in the target file.
 * In case of an error, this function will return false.
 */
bool fsio_copy_file_with_options(char * /* source */, char * /* target */, struct FsIOCopyFileOptions);

/**
 * Moves the source file content to the target file, deleting any previous
 * content in the target file.
 * In case of an error, this function will return false.
 * In case of file move via copy (in case of different file systems) the
 * new file will have current user owner and group and default permissions.
 */
bool fsio_move_file(char * /* source */, char * /* target */);

/**
 * Moves the source file content to the target file, deleting any previous
 * content in the target file.
 * In case of an error, this function will return the error code, otherwise it will return done=true.
 * In case of file move via copy (in case of different file systems) the
 * new file will have current user owner and group and default permissions.
 */
struct FsIOResult fsio_move_file_with_options(char * /* source */, char * /* target */, struct FsIOMoveFileOptions);

/**
 * Will join the provided paths and return a new allocated string with
 * the result.
 * If needed, a unix style separator will be added.
 */
char *fsio_join_paths(char *, char *);

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
 * This function will return true if the directory was created or
 * if it already exists.
 */
bool fsio_mkdirs_parent(char * /* path */, mode_t /* mode */);

/**
 * Removes file or directory for the provided path.
 * If the path points to an non empty directory, it will delete its content as well.
 */
bool fsio_remove(char * /* path */);

/**
 * Runs change mode for all files and directories from the provided path.
 */
bool fsio_chmod_recursive(char * /* path */, mode_t /* mode */);

/**
 * Runs recursively on the provided path and for each file/directory it will call the provided
 * callback with the info struct.
 * The callback will return true (to continue) or false (to stop and exit the flow).
 * The info struct should not be modified by the callback.
 */
bool fsio_recursive_operation(char * /* path */, bool (*callback)(struct FsIORecursiveCallbackInfo), void * /* context */);

#endif

