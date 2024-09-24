# UnixLite Shell: A Custom UNIX-like Command Line Interface

Welcome to my UnixLite Shell project! This project showcases my skills in system-level programming, focusing on the implementation of core Unix-like shell functionalities using Linux system calls. I developed this project as part of an operating systems course, but its primary purpose is to demonstrate my proficiency in building robust, low-level software solutions.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Technical Highlights](#technical-highlights)
- [System Architecture](#system-architecture)
- [Installation and Usage](#installation-and-usage)
- [Error Handling](#error-handling)
- [Memory Management](#memory-management)
- [Challenges and Future Improvements](#challenges-and-future-improvements)

## Introduction

The UnixLite Shell is a single-threaded, synchronous command-line interface (CLI) that mimics the behavior of a Unix shell. It supports basic file and directory manipulation commands such as `ls`, `cd`, `cp`, `mv`, `rm`, and `cat`, allowing users to interact with the file system through a text-based interface. This shell also includes advanced features like error handling and command execution in batch mode.

### Purpose
This project allowed me to deepen my understanding of **operating systems**, particularly the mechanics behind **system calls**, **process management**, and **file I/O**. Through this project, I also honed my skills in **memory management** and **error handling**, ensuring the shell operates reliably under various edge cases.

## Features

- **Interactive Mode**: Users can enter commands interactively, simulating the behavior of a traditional shell.
- **File Mode**: The shell can execute commands from a batch file, with outputs written to an output file.
- **Core Unix Commands**: 
  - `ls`: List files and directories.
  - `pwd`: Show the current working directory.
  - `mkdir`: Create directories.
  - `cd`: Change the current directory.
  - `cp`: Copy files.
  - `mv`: Move files.
  - `rm`: Remove files.
  - `cat`: Display file contents.
  - `exit`: Terminate the shell session.
- **Error Handling**: Robust handling of command syntax errors, incorrect parameters, and missing commands.
- **Batch Processing**: Automates command execution from a file with results stored in an output file.

## Technical Highlights

### System Calls
The project strictly uses **Linux system calls** to implement all commands. This demonstrates my ability to work with low-level system APIs to interact with the operating system directly, bypassing higher-level libraries such as `fopen()` or `moveDir()`.

Key system calls used:
- `open()`, `read()`, `write()` for file I/O operations.
- `fork()`, `exec()` for process creation and execution.
- `chdir()`, `mkdir()`, `unlink()` for file system navigation and manipulation.

### Command Parsing
Implemented a **custom command parser** that uses `getline()` and tokenization techniques (`strtok()`) to process user input. This parser supports:
- Multiple command execution on a single line using `;`.
- Correctly passing arguments and handling various command syntax.

### Interactive and File Mode
The shell can run in two modes:
- **Interactive Mode**: Accepts commands in real-time, mimicking standard shell behavior.
- **File Mode**: Reads commands from a file and generates output in a text file. This functionality required careful management of input/output streams and dynamic memory allocation.

## System Architecture

The project is modularized into several components:
1. **main.c**: Handles input parsing and mode selection (interactive or file mode).
2. **command.c**: Implements the core Unix-like commands using system calls.
3. **string_parser.c**: Responsible for parsing the command line and handling tokens.
4. **Makefile**: Automates the build process to compile the program.

All dynamic memory allocations are carefully tracked and freed, ensuring no memory leaks.

## Installation and Usage

### Compilation
To compile the project, simply run:
```bash
make
```

### Running the Shell
- **Interactive Mode**: 
  ```bash
  ./unixlite
  ```
- **File Mode**:
  ```bash
  ./unixlite -f <filename>
  ```
  Where `<filename>` is the name of the batch file containing commands. Output will be saved in `output.txt`.

## Error Handling

One of the critical aspects of this project is its **robust error handling**. The shell can detect and properly handle:
- **Incorrect command syntax**: Missing or too many parameters.
- **Invalid commands**: Commands not supported by the shell are gracefully handled with error messages.
- **Parameter handling**: Ensures that the correct number of arguments is passed to each command, e.g., `cp` requires two parameters, whereas `pwd` requires none.

These error-handling mechanisms ensure that the shell operates smoothly without crashing or producing undefined behavior.

## Memory Management

The project uses dynamic memory allocation through `malloc()` and `free()`, ensuring that memory is efficiently allocated and deallocated. I rigorously tested the program with **Valgrind** to ensure no memory leaks or errors occur, which is essential for building scalable and efficient system-level software.

## Challenges and Future Improvements

### Challenges
- **System Call Usage**: Implementing commands purely with system calls posed challenges, particularly with managing file descriptors and handling various edge cases for file operations.
- **Command Parsing**: Tokenizing user input while allowing for flexibility in spacing and handling multiple commands on one line required a robust parsing algorithm.
- **Memory Management**: Ensuring all dynamically allocated memory was properly freed, especially in the presence of errors, was a challenge, but I overcame this using tools like Valgrind.

### Future Improvements
- **Directory Support for cp/mv**: Currently, the `cp` and `mv` commands only support files. Extending functionality to handle directories would be a valuable improvement.
- **Concurrency**: Adding support for background execution of commands would enhance the shell’s capability to manage multiple tasks simultaneously.
- **Built-in History**: Implementing a history feature to track previous commands could make the shell more user-friendly.

## Conclusion

This project highlights my ability to design and implement low-level system software, working directly with system calls to build a functioning shell interface. It also demonstrates my understanding of operating systems, error handling, memory management, and process control. I am excited to further apply these skills in real-world projects.

---

**Thank you for reviewing this project! If you have any questions or would like to discuss my work, feel free to reach out!**

