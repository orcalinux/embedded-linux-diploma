# Setting Up VSCode for a Multi-File C++ Project

In this guide, you’ll learn how to configure Visual Studio Code (VSCode) to build, clean, run, and debug a larger C++ project that uses separate directories for source and header files. We assume you have a directory structure like this:

```
my_cpp_project/
├── include/        // Header files (*.h, *.hpp)
├── src/            // Source files (*.cpp)
├── build/          // Output directory for executables
└── .vscode/
    ├── tasks.json
    ├── launch.json
    └── c_cpp_properties.json
```

Make sure you have a C++ compiler installed (like `g++` or `clang++`) and the **C/C++ extension by Microsoft** installed in VSCode.

---

## Table of Contents

- [Setting Up VSCode for a Multi-File C++ Project](#setting-up-vscode-for-a-multi-file-c-project)
  - [Table of Contents](#table-of-contents)
  - [1. Directory Structure](#1-directory-structure)
  - [2. Configuring Build, Clean, and Run Tasks (tasks.json)](#2-configuring-build-clean-and-run-tasks-tasksjson)
  - [3. Setting Up Debugging (launch.json)](#3-setting-up-debugging-launchjson)
  - [4. Configuring IntelliSense (c\_cpp\_properties.json)](#4-configuring-intellisense-c_cpp_propertiesjson)
  - [5. Additional Tips](#5-additional-tips)
  - [6. Running \& Debugging](#6-running--debugging)
    - [Building the Project](#building-the-project)
    - [Cleaning the Project](#cleaning-the-project)
    - [Running the Project](#running-the-project)
    - [Debugging the Project](#debugging-the-project)

---

## 1. Directory Structure

Organize your project files as follows:

- **`include/`** – Contains all header files.
- **`src/`** – Contains all source files.
- **`build/`** – The directory where the executable is generated.

This structure keeps your project organized, simplifies header inclusion, and makes configuring build tasks easier.

---

## 2. Configuring Build, Clean, and Run Tasks (tasks.json)

To build your project and execute additional tasks such as cleaning and running, create or update the `.vscode/tasks.json` file:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build",
      "type": "shell",
      "command": "g++",
      "args": [
        "-g", // Enable debug symbols
        "${workspaceFolder}/src/*.cpp", // Compile all source files in src/
        "-I",
        "${workspaceFolder}/include", // Include directory for header files
        "-o",
        "${workspaceFolder}/build/main" // Output executable in build/
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    },
    {
      "label": "clean",
      "type": "shell",
      "command": "rm",
      "args": [
        "-f",
        "${workspaceFolder}/build/main" // Remove the executable file
      ],
      "problemMatcher": []
    },
    {
      "label": "run",
      "type": "shell",
      "command": "${workspaceFolder}/build/main", // Run the compiled executable
      "args": [],
      "presentation": {
        "echo": true,
        "reveal": "always",
        "focus": false,
        "panel": "shared"
      },
      "problemMatcher": []
    }
  ]
}
```

**Key Points:**

- **Build Task:**

  - Uses the `-I` flag to include header files.
  - The `${workspaceFolder}` variable refers to your project root.
  - The `-g` flag generates debug symbols for later use with the debugger.
  - The build task is labeled `"build"` and set as the default build task.

- **Clean Task:**

  - Uses the `rm -f` command (for Linux/macOS) to remove the executable from the `build` directory.
  - On Windows, consider replacing the `rm` command with an appropriate command (like `del` or a PowerShell script).

- **Run Task:**
  - Executes the generated executable.
  - The `"presentation"` field controls the terminal’s appearance, ensuring you see the program’s output.

---

## 3. Setting Up Debugging (launch.json)

For debugging your project, create or update the `.vscode/launch.json` file with the following configuration:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Launch Debug",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/build/main",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "/usr/bin/gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "build"
    }
  ]
}
```

**Key Points:**

- `"program"` points to your built executable.
- The debugger will run the `"build"` task (via `"preLaunchTask"`) before starting.
- Adjust `"MIMode"` and `"miDebuggerPath"` based on your system and installed debugger.
- Set `"cwd"` to your project root directory.

---

## 4. Configuring IntelliSense (c_cpp_properties.json)

To ensure VSCode can find your header files and provide proper code completion, create or update `.vscode/c_cpp_properties.json`:

```json
{
  "configurations": [
    {
      "name": "Linux",
      "includePath": [
        "${workspaceFolder}/include",
        "${workspaceFolder}/src",
        "/usr/include",
        "/usr/local/include"
      ],
      "defines": [],
      "compilerPath": "/usr/bin/g++",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "intelliSenseMode": "gcc-x64"
    }
  ],
  "version": 4
}
```

**Key Points:**

- `"includePath"` ensures VSCode searches for headers in your `include` and `src` directories.
- Adjust `"compilerPath"`, `"cStandard"`, and `"cppStandard"` to suit your environment and project.
- `"intelliSenseMode"` should match your compiler and target platform.

---

## 5. Additional Tips

- **UTF-8 Locale:**  
  If your project uses wide characters or Unicode, add `std::setlocale(LC_ALL, "");` at the beginning of your `main()` function.

- **Consistent File Formats:**  
  Ensure your source files use the correct extensions (e.g., `.cpp`, `.h`, `.hpp`) and that your tasks match your folder structure.

- **Multiple Files Issues:**  
  If you encounter errors when using multiple files, verify header includes and that your include paths in both `tasks.json` and `c_cpp_properties.json` are set correctly.

- **Terminal & Console Settings:**  
  Adjust terminal or debug console settings in VSCode if you experience issues with output presentation.

---

## 6. Running & Debugging

### Building the Project

- Open the Command Palette (`Ctrl+Shift+P` or `Cmd+Shift+P`), then run **Tasks: Run Build Task**.
- Alternatively, use the shortcut (commonly `Ctrl+Shift+B`).

### Cleaning the Project

- Open the Command Palette (`Ctrl+Shift+P`), then select **Tasks: Run Task**.
- Choose the **clean** task.

### Running the Project

- Open the Command Palette and run **Tasks: Run Task**.
- Choose the **run** task to execute your application.

### Debugging the Project

- Press `F5` or click the Run and Debug icon in the Activity Bar.
- VSCode will run the build task (thanks to `"preLaunchTask": "build"`) and then start the debugger using the "Launch Debug" configuration.
