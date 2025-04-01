# Tetris Game in C++

## Description
This is a simple Tetris game implemented in C++ using the Windows API for handling input. The game features classic Tetris mechanics, including rotation, movement, and line clearing. A score system is also implemented, along with a high-score tracker.

## Features
- Seven standard Tetris pieces (I, O, T, L, J, S, Z)
- Basic game mechanics: move left, move right, soft drop, hard drop, and rotation
- Line clearing and score tracking
- Speed increases based on score
- Game over detection
- High-score tracking
- Option to restart or quit after game over

## Controls
- `Left Arrow (←)`: Move piece left
- `Right Arrow (→)`: Move piece right
- `Down Arrow (↓)`: Soft drop
- `Up Arrow (↑)`: Rotate piece
- `Spacebar`: Hard drop
- `R`: Restart after game over
- `Q`: Quit after game over

## How to Run
### Requirements:
- A Windows operating system
- A C++ compiler that supports Windows API functions (e.g., MinGW, MSVC)

### Steps:
1. Compile the program using a C++ compiler.
   ```sh
   g++ tetris.cpp -o tetris.exe
   ```
2. Run the executable:
   ```sh
   tetris.exe
   ```

## Code Structure
### Classes:
1. **board**: Handles the game grid, clearing full lines, and tracking the score.
2. **tetrominoes**: Stores the predefined Tetris shapes.
3. **game**: Manages the gameplay loop, input handling, and rendering.

## Notes
- The game is cleared using `system("cls")`, which may not work in all environments.
- Uses `Sleep(speed);` for delay control, which is Windows-specific.
- The game currently does not support ghost pieces or hold functionality.

## Future Improvements
- Add color support for different Tetris pieces
- Implement a graphical interface using a game library
- Save and load high scores to a file
- Improve piece spawning and randomization algorithm

## License
This project is open-source and can be modified or distributed freely.
