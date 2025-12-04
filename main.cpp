#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>
#include <chrono>

std::vector<std::vector<char>> connectFourBoard = {
        {'X', ' ', 'O', ' ', ' ', 'O', ' '},
        {' ', 'X', ' ', ' ', 'X', 'X', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

void printBoard(std::vector<std::vector<char>> board) {
    std::cout << " 1 2 3 4 5 6 7 \n" ;
    for (std::vector<char> row : board) {
        std::cout << "|";
        for (char cell : row) {
            if (cell == 'X') {
                std::cout << "\x1b[31m" << cell << "\x1b[0m|";
            } else if (cell == 'O') {
                std::cout << "\x1b[34m" << cell << "\x1b[0m|";
            } else {
                std::cout << cell << "|";
            }
        }
        std::cout << "\n";
    }
    std::cout << "---------------\n" ;
}

void makeMove(int column, bool isPlayer1, std::vector<std::vector<char>>& board) {
    
    for (int i = 0; i < 6; i++) {
        std::cout << "\x1b[2J\033[1A";
        if (i > 0) {
            if (isPlayer1) {
                board[i-1][column] = ' ';
                board[i][column] = 'X';
            } else {
                board[i-1][column] = ' ';
                board[i][column] = 'O';
            }
            printBoard(board);
            Sleep(500);
            // std::cout << "\x1b[2J\033[1A";
        } else {
            if (isPlayer1) {
                board[i][column] = 'X';
            } else {
                board[i][column] = 'O';
            }
            printBoard(board);
            Sleep(500);
            // Clear terminal
            //system("cls");
        }
    }
}


int main() {
    makeMove(0, true, connectFourBoard);
    printBoard(connectFourBoard);
    // std::cout.write(&connectFourBoard[0][0], connectFourBoard.size());
    // std::cout.write(&connectFourBoard[0][1], connectFourBoard.size());
    // std::cout << "Jello, world!" << std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    // std::cout << "\033[1A";  // Move cursor up one line
    // std::cout << "Hello, world!" << std::endl;
}