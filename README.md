# Task Manager by CPP

An implementation of a task manager in C++ that lists and manages processes on Windows and Linux platforms.

## Description

This project provides a simple task manager that can display and manage processes. It includes functionality to list processes, sort them by name, PID, and memory usage, and retrieve detailed process information depending on the operating system.

### Files

- `cmake-build-debug/`: Build directory.
- `CMakeLists.txt`: CMake configuration file.
- `Task Manager.cpp`: Main source file containing the implementation of the task manager.

## Usage

To compile and run the task manager:

1. Ensure you have C++ compiler and CMake installed.
2. Clone the repository.
3. Navigate to the repository directory and create a build directory:
   ```bash
   mkdir build
   cd build
   ```
4. Generate the build system using CMake:
    ```bash
    cmake ..
    ```
5. Build the project:
    ```bash
    cmake --build .
    ```
6. Run the executable:
    ```bash
    ./Task Manager
    ```

## Features

- List processes and display basic information.
- Sort processes by name, PID, and memory usage.
- Retrieve and display detailed process information based on the operating system.

## Example Output

Here's a snippet of example output from the task manager:
```plaintext
Unsorted List:
Name : cProcess1          PID : 1234          MemoryUsage : 1024 k
Name : bProcess2          PID : 5678          MemoryUsage : 208 k
Name : aProcess3          PID : 11            MemoryUsage : 4096 k

Sorted by Name:
Name : aProcess3          PID : 11            MemoryUsage : 4096 k
Name : bProcess2          PID : 5678          MemoryUsage : 208 k
Name : cProcess1          PID : 1234          MemoryUsage : 1024 k

Sorted by PID:
Name : aProcess3          PID : 11            MemoryUsage : 4096 k
Name : cProcess1          PID : 1234          MemoryUsage : 1024 k
Name : bProcess2          PID : 5678          MemoryUsage : 208 k

Sorted by Memory Usage:
Name : bProcess2          PID : 5678          MemoryUsage : 208 k
Name : cProcess1          PID : 1234          MemoryUsage : 1024 k
Name : aProcess3          PID : 11            MemoryUsage : 4096 k
```

## Contact

For questions or feedback regarding the Task Manager by CPP, feel free to contact the author:

- Email: [yassinalilearning77076@gmail.com](mailto:yassinalilearning77076@gmail.com)
- GitHub Issues: [Project Issues](https://github.com/YassenAli/Task-Manager-by-CPP/issues)
