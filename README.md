# Database Assignments Repository

This repository contains four programming assignments focused on building a database system with key components like a buffer pool, heap file, and B+ tree indexing, and implementing query execution operations such as joins, aggregations, and insertions.

## Project Structure


```
├── PA-3 Writeups/                 # Writeups for Programming Assignment 3
├── PA-4 WriteUp/                  # Writeups for Programming Assignment 4
├── db/                            # Main codebase for the assignments
│   ├── BufferPool.cpp             # Buffer pool implementation (PA2)
│   ├── Catalog.cpp                # Catalog implementation (PA1)
│   ├── HeapFile.cpp               # Heap file access method (PA1)
│   ├── BTreeFile.cpp              # B+ Tree access method (PA2)
│   ├── Filter.cpp                 # Relational algebra operator: Filter (PA3)
│   ├── Join.cpp                   # Relational algebra operator: Join (PA3)
│   └── ...                        # Other files
├── include/db/                    # Header files for the codebase
├── docs/                          # Documentation for the assignments
├── examples/                      # Example tests and usage for PA4
├── img/                           # Images used in the documentation
├── tests/                         # Test cases for the assignments
├── .gitignore                     # Gitignore file
├── CMakeLists.txt                 # Build configuration for the project
├── README.md                      # General description of the project (this file)
├── heapfile.dat                   # Heap file for testing purposes
└── table.dat                      # Table file for testing purposes
```



# Assignments
- [Introduction](docs/README.md)
- [Assignment 1](docs/pa1.md)
- [Assignment 2](docs/pa2.md)
- [Assignment 3](docs/pa3.md)
- [Assignment 4](docs/pa4.md)

# Development Environment Setup

We are grading your solutions on Linux, so we suggest that you implement the assignments on Linux.
That being said you should be able to use any OS of your choice if you follow these instructions.

## CLion Instructions (recommended)

We highly recommend using an IDE such as [CLion](https://www.jetbrains.com/clion/) as it comes with the tools you need to complete your assignment. You will need a **free** license for CLion, which you can get by following the instructions [here](https://www.jetbrains.com/shop/eform/students).

### Windows

Windows are supported through [WSL](https://learn.microsoft.com/en-us/windows/wsl/install).

### Linux

No need for any steps further.

### MacOS

No need for any steps further.

## VS Code Instructions

As an alternative, you can use a source code editor such as [VS Code](https://code.visualstudio.com/). This tool needs a few more steps to configure it properly.

Install the following extensions:
- [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)

### Windows

Windows are supported through [WSL](https://learn.microsoft.com/en-us/windows/wsl/install).
After installing WSL you can follow the [Linux](#linux-1) instructions.

### Linux

Run the following commands:
```bash
sudo apt update
sudo apt upgrade -y
sudo apt install -y gcc g++ build-essential gdb make cmake valgrind
```

### MacOS

Clang may already be installed on your Mac. To verify that it is, open a macOS Terminal window and enter the following command:
```zsh
clang --version
```
If Clang isn't installed, enter the following command to install the command line developer tools:
```zsh
xcode-select --install
```
