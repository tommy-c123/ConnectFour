#include <iostream>
#include <limits>
#include <vector>
#include <unordered_map>

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
constexpr int totalPieces = 42;

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

// ensure the user enters a valid column number, if not, keep prompting them until they do
int inputValidator() {
    int column = 0;
    while (!(std::cin >> column) || !((1 <= column) && (column <= 7))) {
        std::cout << "Invalid input. Please enter a column number (1-7): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return column;
}

// this function counts consecutive identical pieces, and has bounds checking for the size of the board
int countConsecutivePieces(int row, int column, const int rowDelta, const int columnDelta, const std::vector<std::vector<char>>& board) {
    int count = 0;
    const char currentPiece = board[row][column];
    constexpr int rows = 6;
    constexpr int columns = 7;

    while (row >= 0 && row < rows && column >= 0 && column < columns && board[row][column] == currentPiece) {
        count++;
        row += rowDelta;
        column += columnDelta;
    }
    return count;
}

// see if the last played piece makes a vertical win (|)
bool checkVertical(const int column, std::vector<std::vector<char>>& board) {
    const int row = 6 - colsFilled[column];

    if (countConsecutivePieces(row, column, 1, 0, board) >= 4) {
        return true;
    }
    return false;
}

// see if the last played piece makes a horizontal win (-)
bool checkHorizontal(const int column, std::vector<std::vector<char>>& board) {
    const int row = 6 - colsFilled[column];

    if (countConsecutivePieces(row, column, 0, -1, board) + countConsecutivePieces(row, column, 0, 1, board) - 1 >= 4) {
        return true;
    }
    return false;
}

// see if the last played piece makes a diagonal win (\ or /)
bool checkDiagonal(const int column, std::vector<std::vector<char>>& board) {
    const int row = 6 - colsFilled[column];

    // check for \ diagonal
    if (countConsecutivePieces(row, column, -1, -1, board) + countConsecutivePieces(row, column, 1, 1, board) - 1 >= 4) {
        return true;
    }

    // check for / diagonal
    if (countConsecutivePieces(row, column, -1, 1, board) + countConsecutivePieces(row, column, 1, -1, board) - 1 >= 4) {
        return true;
    }

    return false;
}

// check for every type of win
bool checkWin(const int column, std::vector<std::vector<char>>& board) {
    return checkHorizontal(column, board) || checkVertical(column, board) || checkDiagonal(column, board);
}

// print the connect four board, adding column numbers, colouring, and lines in between columns with the | character
void printBoard(const std::vector<std::vector<char>>& board) {
    std::cout << " 1 2 3 4 5 6 7 \n" ;
    for (const std::vector<char>& row : board) {
        std::cout << "|";
        for (const char cell : row) {
            if (cell == 'X') {
                // \x1b[31m = ANSI escape code for red foreground, \x1b[0m resets
                std::cout << "\x1b[31m" << cell << "\x1b[0m|";
            } else if (cell == 'O') {
                // \x1b[33m = ANSI escape code for yellow foreground, \x1b[0m resets
                std::cout << "\x1b[33m" << cell << "\x1b[0m|";
            } else {
                std::cout << cell << "|";
            }
        }
        std::cout << "\n";
    }
    std::cout << "---------------\n" ;
}

// function to add a piece to the board
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
    // ANSI escape code to clear the console and return the cursor to the top left
    std::cout << "\033[2J\033[1;1H";
    printBoard(board);
    colsFilled[column]++;
    piecesPlayed++;
}


int main() {
    char continueGame = 'y';

    // this while loop allows the user to play again if they enter "y"
    while (continueGame == 'y') {
        printBoard(connectFourBoard);
        bool isPlayer1 = true;
        // this while loop continues until the board is full, in which case it is a draw
        while (piecesPlayed < totalPieces) {
            int selectedColumn = 0;
            if (isPlayer1) {
                std::cout << "Player 1's turn, enter a column number: ";
                selectedColumn = inputValidator();
                makeMove(selectedColumn - 1, isPlayer1, connectFourBoard);

                if (checkWin(selectedColumn - 1, connectFourBoard)) {
                    std::cout << "Player 1 wins!\n";
                    break;
                }

                isPlayer1 = false;
            } else {
                std::cout << "Player 2's turn, enter a column number: ";
                selectedColumn = inputValidator();
                makeMove(selectedColumn - 1, isPlayer1, connectFourBoard);

                if (checkWin(selectedColumn - 1, connectFourBoard)) {
                    std::cout << "Player 2 wins!\n";
                    break;
                }

                isPlayer1 = true;
            }
        }
        // reset the board
        clearBoard(connectFourBoard, colsFilled);
        std::cout << "Would you like to play again? (y/n) ";
        std::cin >> continueGame;
        if (piecesPlayed == totalPieces) {
            std::cout << "The game was a draw!";
        }
    }
}
