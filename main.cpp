#include <iostream>
#include <vector>

std::vector<std::vector<char>> connectFourBoard = {
        {' ', 'O', ' ', ' ', ' ', ' ', ' '},
        {' ', 'X', ' ', ' ', 'O', 'O', ' '},
        {' ', ' ', 'O', ' ', ' ', 'O', ' '},
        {'O', ' ', ' ', 'X', ' ', ' ', ' '},
        {' ', 'X', ' ', ' ', 'X', ' ', ' '},
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
    std::cout << "---------------" ;
}



int main() {
    printBoard(connectFourBoard);
}