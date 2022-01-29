## CHANGELOG

### v0.5.3

* Added static to internal functions

### v0.5.2 (2021-10-23)

* Enhancement: improve copy file performance.

### v0.5.1 (2021-09-26)

* Enhancement: New fsio_file_extension function.

### v0.5.0 (2021-09-24)

* Enhancement: Updated binary file operations.

### v0.4.0 (2021-09-24)

* Enhancement: New binary file operations.

### v0.3.0 (2021-08-09)

* Enhancement: fsio_move_file_with_options will return the error number enum instead of struct.

### v0.2.0 (2021-08-09)

* Enhancement: fsio_move_file_with_options will return the error number struct instead of true/false.

### v0.1.7 (2021-07-31)

* New fsio_join_paths function.
* New fsio_file_size function.
* New fsio_read_text_file_with_options function.
* Improved input validation for more stable API.
* Added cargo-make makefile for simpler sharing of optional development build instructions.

### v0.1.6 (2020-12-27)

* New fsio_move_file function.
* New fsio_move_file_with_options function.
* New fsio_copy_file_with_options function.

### v0.1.5 (2020-12-16)

* New fsio_chmod_recursive function.
* New fsio_recursive_operation function which enables to recursively invoke an operation on all files/directories.
* New FSIO_MODE_ALL global constant which defines an all permissions (777) mode_t value.

### v0.1.4 (2020-12-09)

* Fixed root path mkdirs invocation.
* Fixed existing directory error detection.

### v0.1.3 (2020-11-27)

* New fsio_remove function.
* New fsio_copy_file functions.
* New fsio_path_exists function.
* New fsio_file_exists function.
* New fsio_create_empty_file function.
* New fsio_mkdirs_parent function.
* Free all memory in tests
* Test memory leaks in CI

### v0.1.2 (2020-11-12)

* Flush file before closing after write operation.

### v0.1.1 (2020-11-07)

* Internal functions are now namespaced with _fsio prefix.
* c_string_buffer upgraded to 0.1.4
* Improved build setup (no need to list test names).

### v0.1.0 (2020-09-25)

* Initial release
