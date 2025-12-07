#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<std::vector<char>> connectFourBoard = {
        {' ', ' ', 'O', ' ', ' ', 'O', ' '},
        {' ', 'X', ' ', ' ', 'X', 'X', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'X', ' ', ' ', ' ', ' ', ' ', ' '}
    };

void printBoard(const std::vector<std::vector<char>>& board) {
    std::cout << " 1 2 3 4 5 6 7 \n" ;
    for (const std::vector<char>& row : board) {
        std::cout << "|";
        for (const char cell : row) {
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

void makeMove(const int column, const bool isPlayer1, std::vector<std::vector<char>>& board, int amountFilled) {
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
        } else {
            if (isPlayer1) {
                board[i][column] = 'X';
            } else {
                board[i][column] = 'O';
            }
        }
    }

}


int main() {
    std::unordered_map<int, int> colsFilled = {
        { 0, 0 },
        { 1, 0 },
        { 2, 0 },
        { 3, 0 },
        { 4, 0 },
        { 5, 0 },
        { 6, 0 },
    };
    // makeMove(0, true, connectFourBoard, colsFilled[0]);
    // printBoard(connectFourBoard);
    // std::cout.write(&connectFourBoard[0][0], connectFourBoard.size());
    // std::cout.write(&connectFourBoard[0][1], connectFourBoard.size());
    // std::cout << "Jello, world!" << std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // // std::cout << "\033[1A";  // Move cursor up one line
    // std::cout << "Hello, world!" << std::endl;
    std::cout << "Hello there";
}
