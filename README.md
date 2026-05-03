*This project has been created as part of the 42 curriculum by ilcelik.*

# get_next_line

## Description

`get_next_line` is a C function that reads and returns one line at a time from a given file descriptor. Each successive call to the function picks up where the last one left off, making it easy to iterate through a file or standard input line by line without loading the entire content into memory at once.

The function handles any buffer size (defined at compile time via `-D BUFFER_SIZE=n`), works correctly on both regular files and standard input, and preserves the terminating `\n` character in the returned line — except when the end of the file is reached without a trailing newline.

The project's secondary goal is to teach the use of **static variables** in C, which are essential for retaining state between function calls without using global variables.

---

## Instructions

### Compilation

The project must be compiled with the standard flags, and optionally with a custom `BUFFER_SIZE`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

You may substitute `42` with any positive integer. The code also compiles without the flag, in which case the default value defined in the header (`42`) is used.

### Files

| File | Description |
|---|---|
| `get_next_line.c` | Core function implementation |
| `get_next_line_utils.c` | Helper functions (strlen, strchr, strjoin, substr) |
| `get_next_line.h` | Header file with prototypes and BUFFER_SIZE definition |

### Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Return Values

- Returns the next line read from the file descriptor (including `\n` if present).
- Returns `NULL` when there is nothing left to read or when an error occurs.

---

## Algorithm

### Approach: Static Stash Buffer

The core idea is to maintain a **persistent buffer (stash)** across calls using a `static` variable. This is necessary because `read()` reads in fixed-size chunks (BUFFER_SIZE), which rarely align perfectly with actual line boundaries.

The function works in three phases on each call:

1. **Read & accumulate (`read_and_stash`):** Reads from the file descriptor in chunks of `BUFFER_SIZE` bytes, appending each chunk to the static stash string — until a newline character is found in the stash or EOF is reached. This ensures we never read more than necessary.

2. **Extract the line (`extract_line`):** Scans the stash for the first `\n` (or end of string), then returns a substring from the beginning of the stash up to and including that newline.

3. **Update the stash (`update_stash`):** Trims the returned line off the front of the stash, keeping only the remainder for the next call. If nothing remains, the stash is freed and set to NULL.

### Why this approach?

- **Memory efficient:** Only reads as many bytes as needed to find the next newline, rather than loading the whole file.
- **Correct across any BUFFER_SIZE:** Works whether BUFFER_SIZE is 1 or 1,000,000, because leftover data is always preserved in the stash.
- **No global variables:** State is maintained with a single `static` local variable, satisfying the project constraints.
- **Clean separation of concerns:** Each sub-function has a single, well-defined responsibility, making the code readable and easy to debug.

---

## Resources

- [The C Programming Language – Kernighan & Ritchie](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [Static variables in C – GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [`read()` man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [File descriptors explained](https://www.bottomupcs.com/file_descriptors.xhtml)
- [Memory management in C – malloc/free](https://www.gnu.org/software/libc/manual/html_node/Basic-Allocation.html)

### AI Usage

AI was used exclusively to help generate documentation based on the existing source code and project PDF. No AI assistance was used in writing or debugging the actual C implementation. The algorithm design, logic, and code were developed independently.
