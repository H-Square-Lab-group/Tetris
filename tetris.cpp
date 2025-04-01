#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

enum Direction { ROTATE, DOWN, RIGHT, LEFT };

class board {
public:
    int highScore;
    char grid[20][10];  // Game board
    int score;
    bool gameIsOver;

    board() {
        gameIsOver = false;
        score = 0;
        highScore = 0;
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 10; j++)
                grid[i][j] = '.';
    }

    void clearFullLines() {
        for (int row = 19; row >= 0; row--) {
            bool full = true;
            for (int col = 0; col < 10; col++) {
                if (grid[row][col] != 'o') {
                    full = false;
                    break;
                }
            }
            if (full) {
                for (int r = row; r > 0; r--)
                    for (int col = 0; col < 10; col++)
                        grid[r][col] = grid[r - 1][col];

                for (int col = 0; col < 10; col++)
                    grid[0][col] = '.';

                score += 100;
                row++; // Recheck row after shifting
            }
        }
    }
    void reset() {
        gameIsOver = false;
        score = 0;
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 10; j++)
                grid[i][j] = '.';
    }
    
};

class tetrominoes {
public:
    int shapes[7][4][4]; 

    tetrominoes() {
        int tempShapes[7][4][4] = {
            // I piece
            {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
            // O piece
            {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
            // T piece
            {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
            // L piece
            {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
            // J piece
            {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
            // S piece
            {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
            // Z piece
            {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
        };
        memcpy(shapes, tempShapes, sizeof(tempShapes));
    }
};

class game {
private:
    board gameBoard;
    tetrominoes tetro;
    int posX, posY;
    int shape[4][4];
    int speed;

    bool canMove(int newX, int newY, int newShape[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (newShape[i][j] == 1) {
                    int newRow = newY + i;
                    int newCol = newX + j;

                    if (newRow >= 20 || newCol < 0 || newCol >= 10)
                        return false;

                    if (gameBoard.grid[newRow][newCol] == 'o')
                        return false;
                }
            }
        }
        return true;
    }
    

    void rotateShape() {
        int rotated[4][4] = {0};
    
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rotated[j][3 - i] = shape[i][j];
    
        if (canMove(posX, posY, rotated)) {
            memcpy(shape, rotated, sizeof(rotated));
        }
    }
    
public:
game() {
    srand(time(0));
    posX = 3;
    posY = -1;  
    memcpy(shape, tetro.shapes[rand() % 7], sizeof(shape));
    speed = 500;
}

    void handleInput() {
        int newX = posX, newY = posY;
        int newShape[4][4];

        memcpy(newShape, shape, sizeof(shape)); // Copy current shape

        if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Move left
            newX--;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Move right
            newX++;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Soft drop
            newY++;
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) { // Rotate piece
            rotateShape();
            return;
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // Hard drop
            while (canMove(posX, posY + 1, shape)) {
                posY++;
            }
            update();
            return;
        }
        

        if (canMove(newX, newY, shape)) {
            posX = newX;
            posY = newY;
        }
    }

    void update() {
        int newY = posY + 1;

        if (canMove(posX, newY, shape)) {
            posY = newY;
        } else {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (shape[i][j] == 1)
                        gameBoard.grid[posY + i][posX + j] = 'o';

            gameBoard.clearFullLines();

            posX = 3; posY = 0;
            memcpy(shape, tetro.shapes[rand() % 7], sizeof(shape));

            if (!canMove(posX, posY, shape))
                gameBoard.gameIsOver = true;
        }
        if (gameBoard.score > gameBoard.highScore) {
            gameBoard.highScore = gameBoard.score;}

        speed = max(50, 500 - (gameBoard.score / 500) * 30);
    }

    void render() {
        system("cls");

        char tempGrid[20][10];
        memcpy(tempGrid, gameBoard.grid, sizeof(gameBoard.grid));

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (shape[i][j] == 1)
                    tempGrid[posY + i][posX + j] = 'o';  

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++)
                cout << tempGrid[i][j] << " ";
            cout << endl;
        }

        cout << "Score: " << gameBoard.score << endl;
        cout <<"High Score: " << gameBoard.highScore << endl;

    }

    void reset() {
        gameBoard.reset();
        posX = 3;
        posY = -1;
        memcpy(shape, tetro.shapes[rand() % 7], sizeof(shape));
        speed = 500;
        gameBoard.score = 0;
    }

    void run() {
    while (true) {
        while (!gameBoard.gameIsOver) {
            handleInput();
            update();
            render();
            Sleep(speed);
        }
        cout << "Game Over! Press 'R' to restart or 'Q' to quit." << endl;
        while (true) {
            if (GetAsyncKeyState('R') & 0x8000) {
                reset();
                break;
            }
            if (GetAsyncKeyState('Q') & 0x8000) return;
        }
    }
}
};

int main() {  
    game tetrisGame;
    tetrisGame.run();
    return 0;
}