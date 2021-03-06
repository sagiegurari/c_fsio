## CHANGELOG

### v0.1.7

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
