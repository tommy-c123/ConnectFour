#include <iostream>
#include <limits>
#include <vector>
#include <unordered_map>

// test comment

// store the board in a vector of vectors of chars, X is player 1, O is player 2.
std::vector<std::vector<char>> connectFourBoard = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

// store how many pieces are in each column, to decide where to put pieces, and used for the checkWin function
std::unordered_map<int, int> colsFilled = {
    { 0, 0 },
    { 1, 0 },
    { 2, 0 },
    { 3, 0 },
    { 4, 0 },
    { 5, 0 },
    { 6, 0 },
};

// total number of pieces, used to check for draw
int piecesPlayed = 0;
int totalPieces = 42;

// reset the board to play again
void clearBoard(std::vector<std::vector<char>>& board, std::unordered_map<int, int>& filled) {
    board = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    filled = {
        { 0, 0 },
        { 1, 0 },
        { 2, 0 },
        { 3, 0 },
        { 4, 0 },
        { 5, 0 },
        { 6, 0 },
    };
}

int inputValidator() {
    int column = 0;
    while (!(std::cin >> column) || !((1 <= column) && (column <= 7))) {
        std::cout << "Invalid input. Please enter an integer (1-7): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return column;
}


int countPieces(int row, int column, int rowDelta, int columnDelta, const std::vector<std::vector<char>>& board) {
    int count = 0;
    char currentPiece = board[row][column];
    int rows = 6;
    int columns = 7;

    while (row >= 0 && row < rows && column >= 0 && column < columns && board[row][column] == currentPiece) {
        count++;
        row += rowDelta;
        column += columnDelta;
    }
    return count;
}

bool checkVertical(const int column, std::vector<std::vector<char>>& board) {
    const int row = 6 - colsFilled[column];

    if (countPieces(row, column, 1, 0, board) >= 4) {
        return true;
    }
    return false;
}

bool checkHorizontal(const int column, std::vector<std::vector<char>>& board) {
    const int row = 6 - colsFilled[column];

    if (countPieces(row, column, 0, -1, board) + countPieces(row, column, 0, 1, board) - 1 >= 4) {
        return true;
    }
    return false;
}

bool checkDiagonal(const int column, std::vector<std::vector<char>>& board) {
    const int row = 6 - colsFilled[column];

    if (countPieces(row, column, -1, -1, board) + countPieces(row, column, 1, 1, board) - 1 >= 4) {
        return true;
    }

    if (countPieces(row, column, -1, 1, board) + countPieces(row, column, 1, -1, board) - 1 >= 4) {
        return true;
    }

    return false;
}

bool checkWin(int column, std::vector<std::vector<char>>& board) {
    return checkHorizontal(column, board) || checkVertical(column, board) || checkDiagonal(column, board);
}

void printBoard(const std::vector<std::vector<char>>& board) {
    std::cout << " 1 2 3 4 5 6 7 \n" ;
    for (const std::vector<char>& row : board) {
        std::cout << "|";
        for (const char cell : row) {
            if (cell == 'X') {
                std::cout << "\x1b[31m" << cell << "\x1b[0m|";
            } else if (cell == 'O') {
                std::cout << "\x1b[33m" << cell << "\x1b[0m|";
            } else {
                std::cout << cell << "|";
            }
        }
        std::cout << "\n";
    }
    std::cout << "---------------\n" ;
}

void makeMove(const int column, const bool isPlayer1, std::vector<std::vector<char>>& board) {
    const int rowToChange = 5 - colsFilled[column];

    // Do not allow adding to an already full column
    if (rowToChange == -1) {
        std::cout << "This column is already full!";
        return;
    }

    if (isPlayer1) {
        board[rowToChange][column] = 'X';
    } else {
        board[rowToChange][column] = 'O';
    }
    printBoard(board);
    // ANSI escape code to clear the console and return the cursor to the top left
    std::cout << "\x1b[2J\033[1A";

    colsFilled[column]++;
    piecesPlayed++;
}


int main() {
    bool isPlayer1 = true;
    char continueGame = 'y';
    while (continueGame == 'y') {
        printBoard(connectFourBoard);
        isPlayer1 = true;
        while (piecesPlayed < totalPieces) {
            int selectedColumn = 0;
            if (isPlayer1) {
                std::cout << "Player 1's turn, enter a column number: ";
                selectedColumn = inputValidator();
                makeMove(selectedColumn - 1, isPlayer1, connectFourBoard);

                if (checkWin(selectedColumn - 1, connectFourBoard)) {
                    std::cout << "Player 1 wins!";
                    break;
                }

                isPlayer1 = false;
            } else {
                std::cout << "Player 2's turn, enter a column number: ";
                selectedColumn = inputValidator();
                makeMove(selectedColumn - 1, isPlayer1, connectFourBoard);

                if (checkWin(selectedColumn - 1, connectFourBoard)) {
                    std::cout << "Player 2 wins!";
                    break;
                }

                isPlayer1 = true;
            }
        }
        clearBoard(connectFourBoard, colsFilled);
        std::cout << "Would you like to play again? (y/n) ";
        std::cin >> continueGame;
        if (piecesPlayed == totalPieces) {
            std::cout << "The game was a draw!";
        }
    }


    // makeMove(0, false, connectFourBoard);
    // makeMove(4, true, connectFourBoard);
    // printBoard(connectFourBoard);
    //
    // if (checkVertical(4, connectFourBoard)) {
    //     std::cout << "Win vertical";
    // } else {
    //     std::cout << "Lose vertical";
    // }
    // if (checkHorizontal(0, connectFourBoard)) {
    //     std::cout << "Win horizontal";
    // } else {
    //     std::cout << "Lose horizontal";
    // }
    //
    // std::cout << std::endl;
    // if (checkDiagonal(2, connectFourBoard)) {
    //     std::cout << "Win diagonal ";
    // } else {
    //     std::cout << "Lose diagonal";
    // }
}
