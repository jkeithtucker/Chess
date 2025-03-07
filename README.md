# Chess Project
Chess game with all rules implemented. Written in C/C++.

## Installation

### Requirements
For the compilation of the project you will need:
- SFML 2.6.1 (32-bit) VERSION MUST MATCH FOR COMPILATION
- CMake (3.8 or later)

### Example for Windows with Git, CMake GUI & VS

#### Step 1:
![ScreenHunter 411](https://github.com/user-attachments/assets/205ce1ce-1c7f-4ee8-9141-18835186d745)

Copy the repo URL.

#### Step 2:
![ScreenHunter 412](https://github.com/user-attachments/assets/db0b4f6b-6d45-453c-b535-edd11ae92f08)

Find a directory to clone the repo (example in PowerShell): git clone https://github.com/jkeithtucker/Chess.git

#### Step 3:
![ScreenHunter 413](https://github.com/user-attachments/assets/92b87726-1e91-4746-9b0e-8847e32d6571)

Using CMake GUI set your source code directory and the binary build directory.

#### Step 4:
![ScreenHunter 414](https://github.com/user-attachments/assets/a1cfe423-051a-41e7-b5b5-309861836e89)

You may need to add the SFML_DIR to your environmental variables. To do this copy the location of your 
SFMLConfig.cmake and add it to your environmental variables in CMake GUI.

![ScreenHunter 415](https://github.com/user-attachments/assets/3dd596ec-a5be-43a2-bbe6-b105fe0da2ac)

#### Step 5:
Click Config in your CMake GUI and accept the creation request for the \build directory.

![ScreenHunter 416](https://github.com/user-attachments/assets/43ef2c19-9c5e-40e9-8ddb-6f49da149e5f)

Use the following configuration settings as below:

![ScreenHunter 417](https://github.com/user-attachments/assets/98ba7edd-afc5-4129-b5b5-e3b1683dfc88)

After configuration, generate the project.

#### Step 6:
![ScreenHunter 418](https://github.com/user-attachments/assets/8f49b0b5-ec15-4c11-8439-63b3cc1b5176)

The \build directory should now have been created with the ChessApplication.sln file.
Open the file with VS.

#### Step 7:
![ScreenHunter 419](https://github.com/user-attachments/assets/83efe108-7609-47de-b9a9-b494c326445c)

Open CMakeLists.txt, set solution configuration to Release and Win32. Then build the solution.

#### Step 8:
![ScreenHunter 420](https://github.com/user-attachments/assets/47aa1543-552f-4733-b9dc-d057c2f0983c)

Finally, copy the SFML .dlls from Chess\lib\Release\ to Chess\build\Release\

![ScreenHunter 421](https://github.com/user-attachments/assets/ef7c2687-d293-4625-9c66-8a0c0a7f7d3e)

Run the .exe

## User Information
Chess board orientation is from White's perspective A->H 1->8.

The starting position is the 'standard/default'.

This can be changed through FEN strings - more documentation found in fen.hpp & fen.cpp.

Pieces are clicked, dragged, and dropped.

The user plays for both colours (awaiting computer opposition/engine).

The result of the game (DRAW, WHITE MATED, BLACK MATED) is displayed in the terminal window.

## Application Information
Git used for version control.

CMake used in conjunction with JSON presets.

External library SFML 2.6.1 (32-bit) for GUI.

Built for x86/32-bit Release as the program only uses ~4.58KB at runtime.

Of this memory, 4.22KB is allocated on the heap (likely to shift towards full stack allocation).

OS reclamation of heap allocated memory, after application exit, is faster than manual memory deletion. 

As such, this small amount of heap memory is reclaimed by the OS - by design; not by any resource manager.

This may change in future updates.

All cpp & hpp files are stored in the source directory.
