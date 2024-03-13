# Bash text utilities

Development of Bash text utilities: cat, grep.

## Usage of cat

`cat [OPTION] [FILE]...`

### cat options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $  |
| 3 | -n (GNU: --number) | number all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also display tabs as ^I  |
| 6 | "-" (instead of file) | reads standard input from terminal  |

## Usage of grep 

`grep [options] template [file_name]`

### grep options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore uppercase vs. lowercase.  |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output matching files only.  |
| 6 | -n | Precede each matching line with a line number. |
| 7 | -h | Output matching lines without preceding them by file names. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Take regexes from a file. |
| 10 | -o | Output the matched parts of a matching line. |
| 11 | "-" (instead of file) | Reads standard input from terminal |

## Specification

- The programs is developed in C language of C11 standard using gcc compiler.
- The program code of the cat and grep is located on the develop branch in the src/cat/ and src/grep/ folders
- Integration tests cover all flag variants and input values, based on a comparison with the behavior of real Bash utilities
- Input via stdin is supported
- Regular expressions are supported for grep
- Support of all flags (listed above), including their pair/triples etc. combinations (e.g. -iv, -in)
- Developed utilities mainly support Linux OS, but can be run on MacOS.

## Build

### Cat

1. go to `src/cat` folder  
2. run make (use just `make` or `make cat`)  
3. now you can run `./cat` with any file and flags specified above

### Grep

1. go to `src/grep` folder  
2. run make (use just `make` or `make grep`)  
3. now you can run `./grep` with any file and flags specified above

## Integration tests

Tests cover different cases including all flags and their combinations.  
Tests are written as bash scripts and located in correpsonding tests/ folders.  

To run tests:
1. go to `src/cat(grep)` folder  
2. run `make test`  
3. you will receive tests result to terminal