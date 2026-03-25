# ZumbroIDE

ZumbroIDE is a lightweight, terminal-based code editor written in C.
The goal of this project is to provide a fast, minimal, extensible editor that helps developers understand how text editors work under the hood, from raw input handling to syntax highlighting and file I/O.

ZumbroIDE focuses on performance, simplicity, and hackability.

## Features

- Fast terminal rendering using raw mode and efficient screen refresh logic
- Syntax highlighting for C and Zumbra (experimental)
- Search with live highlight
- Line numbers (optional)
- Incremental file saving
- Cross-platform support (Linux, macOS, WSL2)
- Clean modular architecture
- Zero external dependencies, pure ANSI C
- Extremely small binary size

## Build & Run
### Requirements

GCC or Clang

A POSIX-compatible terminal

Make (optional)

### Compile manually
```
gcc -Wall -Wextra -pedantic src/*.c -o zumbroide

./zumbroide file.txt
```

### Using Make
```
make

./zumbroide
```

## Keybindings
 - Action	        | Key
 - Move cursor	    | Arrow keys
 - Save file	    | Ctrl + S
 - Quit	            | Ctrl + Q
 - Search	        | Ctrl + F
 - Delete char	    | Backspace / Delete
 - New line	        | Enter
 - Page up/down	    | PgUp / PgDown
 - Go to start/end of line	| Home / End

## Syntax Highlighting

### ZumbroIDE currently supports:

 - C (full)
 - Zumbra (custom language)
 - Keywords
 - Strings
 - Comments
 - Numbers

You can extend syntax definitions easily via the HLDB[] table in syntax.c.

## Why ZumbroIDE?

This project is both a learning tool and a functional mini-IDE.
It helps you understand:

 - How terminals work in raw mode
 - How editors manage rows, buffers, and cursor states
 - How syntax parsing works
 - How to efficiently repaint the screen
 - How event loops and input handling operate
 - How to structure a medium-sized C system cleanly

ZumbroIDE is perfect for anyone who wants to write OS-level tools, compilers, interpreters, or build their own full IDE.

## 🤝 Contributing

Pull requests are welcome!
If you want to add new language highlighting, improve scrolling, or optimize performance, feel free to contribute.

## Author

José Lucas – “joselucasapp”
Creator of ZumbroIDE and the Zumbra Language.