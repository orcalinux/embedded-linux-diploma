# Building Qt Applications with VSCode and Makefile (No IDE Required)

**Description**
A step-by-step guide to set up, write, build, and run Qt applications using Visual Studio Code and a hand-crafted Makefile, without relying on an IDE like Qt Creator.

---

## Table of Contents

- [Building Qt Applications with VSCode and Makefile (No IDE Required)](#building-qt-applications-with-vscode-and-makefile-no-ide-required)
  - [Table of Contents](#table-of-contents)
  - [1. Prerequisites ](#1-prerequisites-)
  - [2. Installing Qt Libraries and Tools ](#2-installing-qt-libraries-and-tools-)
  - [3. Installing and Configuring VSCode ](#3-installing-and-configuring-vscode-)
  - [4. Creating the Project Structure ](#4-creating-the-project-structure-)
  - [5. Writing Your First Qt Application ](#5-writing-your-first-qt-application-)
  - [6. Creating the Makefile ](#6-creating-the-makefile-)
  - [7. Building and Running ](#7-building-and-running-)
  - [8. Debugging in VSCode ](#8-debugging-in-vscode-)
  - [9. Adding Resources (UI, Images, etc.) ](#9-adding-resources-ui-images-etc-)
  - [10. Using Additional Qt Modules ](#10-using-additional-qt-modules-)
  - [11. Tips \& Best Practices ](#11-tips--best-practices-)

---

## 1. Prerequisites <a name="prerequisites"></a>

- A Unix-like system (Linux or macOS) or Windows with MSYS2 / MinGW
- Command-line tools: `gcc`/`g++`, `make`, `bash`
- Internet connection to download Qt and extensions

---

## 2. Installing Qt Libraries and Tools <a name="installing-qt"></a>

1. **Linux (Ubuntu/Debian):**

   ```bash
   sudo apt update
   sudo apt install qt6-base-dev qt6-base-dev-tools qt6-tools-dev
   ```

   > For networking and other modules:

   ```bash
   sudo apt install qt6-network-dev qt6-multimedia-dev qt6-serialport-dev qt6-websockets-dev
   ```

2. **macOS (Homebrew):**

   ```bash
   brew update
   brew install qt
   ```

3. **Windows (MSYS2):**

   ```bash
   pacman -Syu
   pacman -S mingw-w64-x86_64-qt6-base \
                mingw-w64-x86_64-qt6-network \
                mingw-w64-x86_64-qt6-multimedia \
                mingw-w64-x86_64-qt6-serialport \
                mingw-w64-x86_64-qt6-websockets
   ```

> Ensure `qmake`, `moc`, `uic`, and `rcc` are in your `PATH`. You can verify by:

```bash
qmake --version
moc --version
```

---

## 3. Installing and Configuring VSCode <a name="installing-vscode"></a>

1. **Install VSCode** from [https://code.visualstudio.com/](https://code.visualstudio.com/).

2. **Extensions**: Open VSCode and install:

   - **C/C++** (Microsoft)
   - **Qt for VSCode** (felixrieseberg) _optional for better syntax highlighting_

3. **Configure Include Paths**:
   Create or update `.vscode/c_cpp_properties.json`:

   ```json
   {
     "configurations": [
       {
         "name": "Qt",
         "includePath": [
           "${workspaceFolder}/**",
           "/usr/include/qt6",
           "/usr/include/qt6/QtWidgets",
           "/usr/include/qt6/QtCore",
           "/usr/include/qt6/QtGui",
           "/usr/include/qt6/QtNetwork" // Add other modules as needed
         ],
         "defines": [],
         "compilerPath": "/usr/bin/g++",
         "cStandard": "c11",
         "cppStandard": "c++17",
         "intelliSenseMode": "linux-gcc-x64"
       }
     ],
     "version": 4
   }
   ```

---

## 4. Creating the Project Structure <a name="project-structure"></a>

```text
my_qt_app/
├── src/
│   ├── main.cpp
│   └── MainWindow.h
│   └── MainWindow.cpp
├── include/                  # (optional) for headers
├── resources/                # icons, images, UI files
│   └── mainwindow.ui         # if using Qt Designer
└── Makefile
```

---

## 5. Writing Your First Qt Application <a name="writing-application"></a>

1. **main.cpp**:

   ```cpp
   #include <QApplication>
   #include "MainWindow.h"

   int main(int argc, char *argv[]) {
       QApplication app(argc, argv);
       MainWindow window;
       window.show();
       return app.exec();
   }
   ```

2. **MainWindow\.h**:

   ```cpp
   #ifndef MAINWINDOW_H
   #define MAINWINDOW_H

   #include <QMainWindow>

   class MainWindow : public QMainWindow {
       Q_OBJECT
   public:
       explicit MainWindow(QWidget *parent = nullptr);
   };

   #endif // MAINWINDOW_H
   ```

3. **MainWindow\.cpp**:

   ```cpp
   #include "MainWindow.h"
   #include <QMenuBar>

   MainWindow::MainWindow(QWidget *parent)
       : QMainWindow(parent) {
       setWindowTitle("My Qt App");
       resize(800, 600);

       // Example menu
       QMenu *fileMenu = menuBar()->addMenu("File");
       fileMenu->addAction("Exit", this, &QWidget::close);
   }
   ```

---

## 6. Creating the Makefile <a name="makefile"></a>

```makefile
# --- Config ---
QT_LIBS = Qt6Widgets Qt6Core Qt6Gui Qt6Network
CXX = g++
CXXFLAGS = -std=c++17 -I/usr/include/qt6 -I/usr/include/qt6/QtWidgets -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtGui -I/usr/include/qt6/QtNetwork
LDFLAGS = $(foreach lib,$(QT_LIBS), -l$(lib))

SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = my_qt_app

# --- Rules ---
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
```

---

## 7. Building and Running <a name="build-and-run"></a>

1. **In terminal**:

   ```bash
   cd my_qt_app
   make
   ./my_qt_app
   ```

2. **In VSCode**: You can open a terminal (`Ctrl+\`), run `make` and `./my_qt_app`.

---

## 8. Debugging in VSCode <a name="debugging"></a>

1. Install the **C/C++** extension (if not already).
2. Create `.vscode/launch.json`:

   ```json
   {
     "version": "0.2.0",
     "configurations": [
       {
         "name": "Launch Qt App",
         "type": "cppdbg",
         "request": "launch",
         "program": "${workspaceFolder}/${workspaceFolderBasename}",
         "args": [],
         "stopAtEntry": false,
         "cwd": "${workspaceFolder}",
         "environment": [],
         "externalConsole": false,
         "MIMode": "gdb",
         "setupCommands": [{ "text": "-enable-pretty-printing" }]
       }
     ]
   }
   ```

3. Place breakpoints and press `F5` to start debugging.

---

## 9. Adding Resources (UI, Images, etc.) <a name="resources"></a>

- If using `.ui` files (from Qt Designer), run:

  ```bash
  uic resources/mainwindow.ui -o src/ui_mainwindow.h
  ```

  Then include `ui_mainwindow.h` in your `.cpp` and update Makefile to depend on generated headers.

- For icons/images, compile them into a Qt resource file `.qrc` and run:

  ```bash
  rcc resources.qrc -o src/qrc_resources.cpp
  ```

  Add `src/qrc_resources.cpp` to your sources list in Makefile.

---

## 10. Using Additional Qt Modules <a name="additional-modules"></a>

If you plan to use features beyond widgets (like networking, serial communication, multimedia, etc.), make sure to:

1. Install the respective Qt development packages as shown in [Section 2](#installing-qt).
2. Add the appropriate modules to your `QT_LIBS` in the Makefile, such as:

   - `Qt6Network` for networking (`QTcpSocket`, `QNetworkAccessManager`)
   - `Qt6SerialPort` for serial communication
   - `Qt6Multimedia` for audio/video support
   - `Qt6WebSockets` for WebSocket communication

3. Include the corresponding headers and update your `CXXFLAGS` and `LDFLAGS` accordingly.

---

## 11. Tips & Best Practices <a name="tips"></a>

- Keep your Makefile DRY: use variables for paths and flags.
- Use `-Wall -Wextra` in `CXXFLAGS` to catch warnings early.
- Organize headers in an `include/` folder and add `-Iinclude`.
- For larger projects, consider transitioning to **CMake** for easier cross-platform builds.
- Regularly run `make clean` to avoid stale object files.
