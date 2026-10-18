# WindowsShell
WindowsShell — A lightweight, Linux-like custom command-line interface for Windows built with C++ and Windows API.



# WindowsShell

A lightweight, custom command-line interface for Windows written in C++ and Win32 API. It brings a basic Linux-like CLI experience natively to Windows, featuring file utilities, system diagnostics, and a micro text editor.

## Features

* **File System:** Custom implementations of `ls`, `pwd`, `touch`, and `cat`.
* **NEO Text Editor:** Micro editor with hotkeys (`Ctrl+S` to save, `Esc` to exit).
* **Fastfetch:** Hardware and environment diagnostics with structured layout.
* **Power Management:** System controls for `shutdown`, `restart`, and `sleep`.
* **Audio Utility:** Native `beep` tool interfacing with the internal motherboard speaker.


## Compilation

### Using Visual Studio<img width="957" height="555" alt="Снимок экрана 2026-10-18 133531" src="https://github.com/user-attachments/assets/d0fd6765-4dce-461a-9f2f-ec171e8a7907" />

1. Open `WindowsShell.vcxproj` in Visual Studio.
2. Set build to Release and target to x64.
3. Press `Ctrl + Shift + B` to build. Output is located in `x64/Release/`.

### Using Command Line (g++)
```bash
g++ -std=c++17 src/*.cpp -I include -o WindowsShell.exe -luser32 -lkernel32
```

## Security and False Positives

Because this application uses low-level Windows APIs and lacks a commercial digital signature, Windows SmartScreen will flag the executable. This is normal behavior for binaries built from source. To run it, select More info inside the SmartScreen prompt, then click Run anyway.

## Supported Commands

`help`, `ls`, `pwd`, `touch`, `cat`, `neo`, `fastfetch`, `beep`, `clear`, `exit`.
