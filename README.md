# CLIT

**Command Line Interface Toolchain**

CLIT is a collection of small command-line utilities designed to make common terminal tasks simpler and faster.

## Commands

| Command      | Description                              |
| ------------ | ---------------------------------------- |
| `clit fetch` | Download files from URLs                 |
| `clit mkcd`  | Create a directory and enter it          |
| `clit crun`  | Compile and run a C file                 |
| `clit nfile` | Create multiline files from the terminal |
| `clit -h`    | Show help                                |
| `clit -v`    | Show version                             |

## Installation

Clone the repository:

```sh
git clone https://github.com/EdennsAltacc/clit.git
cd clit
```

Build CLIT with GCC:

```sh
gcc src/clit.c -o build/clit -lcurl
```

To make `clit` available system-wide on Unix-like systems:

```sh
sudo mv build/clit /usr/local/bin/clit
```

## Examples

### Fetch

```sh
clit fetch -u https://example.com/file.txt -o file.txt
```

### MKCD

```sh
clit mkcd my-project
```

### CRUN

```sh
clit crun main.c
```

### NFILE

Create a file directly from the terminal:

```sh
clit nfile -f HelloWorld.cpp
```

Enter the file contents line by line and finish with:

```text
!<EOF>
```

Example:

```text
#include <iostream>

int main() {
    std::cout << "Hello world!\n";
    return 0;
}
!<EOF>
```

## Short Alias

For faster usage, CLIT can be aliased:

```sh
alias cl=clit
```

Then:

```sh
cl fetch ...
cl mkcd project
cl crun main.c
cl nfile -f HelloWorld.cpp
```

## Requirements

* GCC or another C compiler
* libcurl
* A supported operating system

## License

CLIT is licensed under the MIT License.

See [License](License) for more information.
