# fsio

[![CI](https://github.com/sagiegurari/c_fsio/workflows/CI/badge.svg?branch=master)](https://github.com/sagiegurari/c_fsio/actions)
[![Release](https://img.shields.io/github/v/release/sagiegurari/c_fsio)](https://github.com/sagiegurari/c_fsio/releases)
[![license](https://img.shields.io/github/license/sagiegurari/c_fsio)](https://github.com/sagiegurari/c_fsio/blob/master/LICENSE)

> File System functions and utilities.

* [Overview](#overview)
* [Usage](#usage)
* [Contributing](.github/CONTRIBUTING.md)
* [Release History](CHANGELOG.md)
* [License](#license)

<a name="overview"></a>
## Overview
This library provides a set of utility functions to work with the file system.<br>
This includes writing/append text files with automatic directory creation, creating full directory path and more.

<a name="usage"></a>
## Usage

```c
#include "fsio.h"
#include <stdbool.h>
#include <stdio.h>


int main()
{
  // simple examples of writing/appending/reading text files
  char *file = "./somedir/myfile.txt";
  bool done  = fsio_write_text_file(file, "some text\n");

  printf("Text file written: %d\n", done);
  done = fsio_append_text_file(file, "more text\n");
  printf("Text file appended: %d\n", done);
  char *text = fsio_read_text_file(file);
  printf("Read text:\n%s\n", text);

  // creating a full directory path
  done = fsio_mkdirs("./somedir/dir1/dir2/dir3", FSIO_MODE_ALL);
  printf("Created directories: %d\n", done);

  // chmod to all permissions recursively
  done = fsio_chmod_recursive("./somedir/", FSIO_MODE_ALL);
  printf("Chmod done: %d\n", done);

  // recursive delete or files and directories
  done = fsio_remove("./somedir");
  printf("Deleted somedir and all content.\n");
}
```

## Contributing
See [contributing guide](.github/CONTRIBUTING.md)

<a name="history"></a>
## Release History

See [Changelog](CHANGELOG.md)

<a name="license"></a>
## License
Developed by Sagie Gur-Ari and licensed under the Apache 2 open source license.
