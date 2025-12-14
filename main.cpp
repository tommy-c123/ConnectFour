#include <iostream>
#include <vector>
#include <unordered_map>


std::vector<std::vector<char>> connectFourBoard = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'O', ' ', ' ', ' ', ' ', ' ', ' '},
        {'O', ' ', ' ', ' ', ' ', ' ', ' '},
        {'O', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'X', 'X', 'X', 'X', ' ', ' '}
    };

std::unordered_map<int, int> colsFilled = {
    { 0, 4 },
    { 1, 0 },
    { 2, 0 },
    { 3, 1 },
    { 4, 1 },
    { 5, 1 },
    { 6, 1 },
};

bool checkVertical(const int column, std::vector<std::vector<char>>& board) {
    int count = 1;

    const int row = colsFilled[column];
    if (row > 3) {
        for (int i = 0; i < 4; i++) {
            if (board[row][column] == board[row - i][column]) {
                count++;
            } else {
                break;
            }
        }
    }
    if (count == 4) {
        return true;
    }
    return false;
}

bool checkHorizontal(const int column, std::vector<std::vector<char>>& board) {
    int count = 0;

    const int row = 6 - colsFilled[column];

    if (column < 3) {
        for (int i = 0; i < 4; i++) {
            if (board[row][column] == board[row][column + i]) {
                count++;
            } else {
                break;
            }
        }
    } else if (column > 3) {
        for (int i = 0; i < 4; i++) {
            if (board[row][column] == board[row][column - i]) {
                count++;
            } else {
                break;
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            if (board[row][column] == board[row][column - i] || board[row][column] == board[row][column + i]) {
                count++;
            } else {
                break;
            }
        }
    }

    if (count == 4) {
        return true;
    }
    return false;
}

// bool checkWin(std::vector<std::vector<char>>& board, int column) {
//     // vertical
//     while (true) {
//         if (board[colsFilled[column]][column] == ) {}
//     }

//     return true;
// }

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

void makeMove(const int column, const bool isPlayer1, std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 6 - colsFilled[column]; i++) {
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
    colsFilled[column]++;
}


int main() {
    // char continueGame = 'y';
    // while (continueGame == 'y') {
    //
    //
    //
    //     std::cout << "Would you like to play again? (y/n) ";
    //     std::cin >> continueGame;
    // }

    // while(checkWin(connectFourBoard, 0)) {

    // }
    // makeMove(0, false, connectFourBoard);
    printBoard(connectFourBoard);

    // if (checkVertical(0, connectFourBoard)) {
    //     std::cout << "Win vertical";
    // } else {
    //     std::cout << "Lose vertical";
    // }

    std::cout << std::endl;
    if (checkHorizontal(3, connectFourBoard)) {
        std::cout << "Win horizontal ";
    } else {
        std::cout << "Lose horizontal";
    }
}
