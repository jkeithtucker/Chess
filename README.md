# Chess Project
Chess game with all rules implemented. Written in C++.

## Application Information
-CMake used in conjunction with JSON settings (as per MSVS CMake project default).
-External library SFML 2.6.1 for GUI. Installed using vcpkg.
-Built for x86/32-bit Release as the program only uses ~4.58KB at runtime.
-Of this memory, 4.22KB is allocated on the heap (likely to shift towards full stack allocation).
-OS reclamation of heap allocated memory, after application exit, is faster than manual memory deletion. 
-As such, this small amount of heap memory is reclaimed by the OS - by design; not by any resource manager.
-All cpp & hpp files are stored in the source directory.

## User Information
Chess board orientation is from White's perspective A->H 1->8.
The starting position is the 'standard/default'.
This can be changed through FEN strings - more documentation found in fen.hpp & fen.cpp.
Pieces are clicked, dragged, and dropped.
The user plays for both colours (awaiting computer opposition/engine).
The result of the game (DRAW, WHITE MATED, BLACK MATED) is displayed in the terminal window.
