#include "MineSweeperBoard.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

MineSweeperBoard::MineSweeperBoard() {

    width = 10;
    height = 10;

    ClearBoard();
    SetStart();

}

MineSweeperBoard::MineSweeperBoard(int w, int h, GameMode mode) : width(w), height(h) {

    SetStartWhichDependsOnGameMode(mode);

}

GameState MineSweeperBoard::GetGameState() const {

    GameState State=RUNNING;

    int BombCounter = GetHowManyMines();
    int RevealedFieldsCounterWithoutBombs = 0;
    int AllFieldsWhichCanBeRevealedLegally = height * width - BombCounter;

    for (int nrow = 0; nrow < height; ++nrow) {
        for (int ncol = 0; ncol < width; ++ncol) {

            if (FieldBoard[nrow][ncol].hasMine and FieldBoard[nrow][ncol].isRevealed) {

                return FINISHED_LOSS;

            }

            if (!FieldBoard[nrow][ncol].hasMine and FieldBoard[nrow][ncol].isRevealed) {

                RevealedFieldsCounterWithoutBombs++;

                if (RevealedFieldsCounterWithoutBombs == AllFieldsWhichCanBeRevealedLegally) {

                    return FINISHED_WIN;

                }
            }

            if (!FieldBoard[nrow][ncol].isRevealed) {

                State = RUNNING;

            }
        }
    }

    return State;
}

void MineSweeperBoard::SetStartWhichDependsOnGameMode(const GameMode &mode) {

    /*************************************************
    *                  TRYB DEBUG                    *
    *                                               *
    * 1.wszystkie pola na przekątnej mają minę       *
    * 2.wszystkie pola w pierwszym wierszu mają minę *
    * 3.co drugie pole w pierwszej kolumnie ma minę  *
    *************************************************/

    ClearBoard();

    if (mode == DEBUG) {

        for (int nrow = 0; nrow < height; nrow++) {
            for (int ncol = 0; ncol < width; ncol++) {

                if (nrow == ncol) {

                    FieldBoard[nrow][ncol].hasMine = true;

                }
            }
        }

        for (int nrow = 0; nrow < height; nrow = nrow + 2) {

            FieldBoard[nrow][0].hasMine = true;

        }

        for (int ncol = 0; ncol < width; ncol++) {

            FieldBoard[0][ncol].hasMine = true;

        }
    }

    if (mode == EASY) {

        int nrow, ncol;

        for (int i = 0; i < std::ceil(height * width * 0.1); ++i) {

            do {

                ncol = rand() % width;
                nrow = rand() % height;

            } while (FieldBoard[nrow][ncol].hasMine);

            FieldBoard[nrow][ncol].hasMine = true;

        }
    }

    if (mode == NORMAL) {

        int nrow, ncol;

        for (int i = 0; i < std::ceil(height * width * 0.2); ++i) {

            do {

                ncol = rand() % width;
                nrow = rand() % height;

            } while (FieldBoard[nrow][ncol].hasMine);

            FieldBoard[nrow][ncol].hasMine = true;

        }
    }

    if (mode == HARD) {

        int nrow, ncol;

        for (int i = 0; i < std::ceil(height * width * 0.3); ++i) {

            do {

                ncol = rand() % width;
                nrow = rand() % height;

            } while (FieldBoard[nrow][ncol].hasMine);

            FieldBoard[nrow][ncol].hasMine = true;

        }
    }
}

void MineSweeperBoard::ClearBoard() {

    for (int nrow = 0; nrow < height; nrow++) {
        for (int ncol = 0; ncol < width; ncol++) {

            FieldBoard[nrow][ncol] = {false, false, false};

        }
    }
}

void MineSweeperBoard::SetStart() {

    FieldBoard[0][0] = {true, false, false};
    FieldBoard[1][1] = {false, false, true};
    FieldBoard[0][2] = {true, true, false};

}

bool MineSweeperBoard::CheckIfTheFieldIsInTheBoard(int row, int col) const {

    if (row < 0 or row >= height) {

        return false;
    }

    if (col < 0 or col >= width) {

        return false;
    }

    return true;
}

void MineSweeperBoard::debug_display() const {
    std::string mine;
    std::string flag;
    std::string reveal;

    std::cout << "PLANSZA W TRYBIE DEBUGOWANIA!" << std::endl;
    std::cout << " ";

    for (int ncol = 0; ncol < width; ncol++) {

        std::cout <<std::setw(5) << ncol;

    }

    std::cout << std::endl;

    for (int nrow = 0; nrow < height; nrow++) {

        std::cout <<std::setw(2) <<nrow<<" ";

        for (int ncol = 0; ncol < width; ncol++) {

            if (FieldBoard[nrow][ncol].hasMine == 1) {

                mine = "M";

            } else {

                mine = ".";

            }

            if (FieldBoard[nrow][ncol].isRevealed == 1) {

                reveal = "o";

            } else {

                reveal = ".";

            }

            if (FieldBoard[nrow][ncol].hasFlag == 1) {

                flag = "f";

            } else {

                flag = ".";

            }

            if (FieldBoard[nrow][ncol].hasMine and FieldBoard[nrow][ncol].isRevealed) {

                std::cout << "[!!!]";

            }

            else {
                std::cout << "[" << mine << reveal << flag << "]";
            }
        }

        std::cout << std::endl;

    }
}

int MineSweeperBoard::GetBoardWidth() const {

    return width;
}

int MineSweeperBoard::GetBoardHeight() const {

    return height;
}

int MineSweeperBoard::GetHowManyMines() const {

    int MinesCounter = 0;

    for (int nrow = 0; nrow < height; nrow++) {
        for (int ncol = 0; ncol < width; ncol++) {

            if (FieldBoard[nrow][ncol].hasMine) {

                MinesCounter++;

            }
        }
    }
    return MinesCounter;
}

int MineSweeperBoard::GetHowManyFieldsAreRevealed() const {

    int RevealedFieldsCounter = 0;

    for (int nrow = 0; nrow < height; nrow++) {
        for (int ncol = 0; ncol < width; ncol++) {

            if (FieldBoard[nrow][ncol].isRevealed) {

                RevealedFieldsCounter++;

            }
        }
    }
    return RevealedFieldsCounter;
}

int MineSweeperBoard::CountMinesAround(int row, int col) const {
    int MinesAroundCounter=0;

    if (!CheckIfTheFieldIsInTheBoard(row, col)){

        return -1;
    }

    if (!FieldBoard[row][col].isRevealed){

        return -1;
    }

    else {

        std::vector<int> nRow = {row + 1, row + 1, row + 1, row, row, row - 1, row - 1, row - 1};
        std::vector<int> nCol = {col - 1, col, col + 1, col - 1, col + 1, col - 1, col, col + 1};

        for (int index = 0; index < 8; index++) {
            if (CheckIfTheFieldIsInTheBoard(nRow[index], nCol[index])) {
                if (FieldBoard[nRow[index]][nCol[index]].hasMine) {

                    MinesAroundCounter++;

                }
            }
        }
    }

    return MinesAroundCounter;
}

// return true if the field at (row,col) position was marked with flag
// return false if any of the following is true:
// - row or col is outside board
// - there is no flag on the field
// - field was already revealed

bool MineSweeperBoard::HasFlag(int row, int col) const {

    if (CheckIfTheFieldIsInTheBoard(row, col)) {
        if (!FieldBoard[row][col].isRevealed) {
            if (FieldBoard[row][col].hasFlag) {

                return true;

            } else {

                return false;
            }
        } else {

            return false;
        }
    } else {

        return false;
    }
}

// if the field at (row,col) was not revealed - change flag status for this field
// Do nothing if any of the following is true
// - field was already revealed
// - either row or col is outside board
// - game is already finished

void MineSweeperBoard::ToggleFlag(int row, int col) {

    if (GetGameState() != RUNNING) {
        return;
    }
    if (!CheckIfTheFieldIsInTheBoard(row, col)) {
        return;
    }

    if (!FieldBoard[row][col].isRevealed) {
        if (!FieldBoard[row][col].hasFlag) {

            FieldBoard[row][col].hasFlag = true;
        } else {

            FieldBoard[row][col].hasFlag = false;
        }
    }
}

auto MineSweeperBoard::RevealZeros(int row, int col) -> void {

    if (!CheckIfTheFieldIsInTheBoard(row, col)) {

        return;
    }

    if (IsRevealed(row, col)) {

        return;
    }

    FieldBoard[row][col].isRevealed = true;

    if (CountMinesAround(row, col) != 0) {

        return;
    }
    if (FieldBoard[row][col].hasMine) {

        return;
    }
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i * j + i + j != 0) {
                if (CheckIfTheFieldIsInTheBoard(row + i, col + j)) {
                    if (!IsRevealed(row + i, col + j)) {

                        RevealZeros(row + i, col + j);
                    }
                }
            }
        }
    }
}

void MineSweeperBoard::RevealField(int row, int col) {
    if (GetGameState() != RUNNING) {
        return;
    }
    if (!CheckIfTheFieldIsInTheBoard(row, col)) {
        return;
    }
    if (!FieldBoard[row][col].hasFlag) {
        if (!FieldBoard[row][col].isRevealed) {
            if (!FieldBoard[row][col].hasMine) {

                //FieldBoard[row][col].isRevealed = true;
                RevealZeros(row, col);

            } else {
                if (GetHowManyFieldsAreRevealed() ==
                    0) { //Jezeli to pierwszy ruch to przesuwa bombe w inne puste miejsce.

                    int nrow, ncol;

                    do {

                        nrow = rand() % height;
                        ncol = rand() % width;

                    } while (FieldBoard[nrow][ncol].hasMine);

                    FieldBoard[row][col].hasMine = false;

                    FieldBoard[nrow][ncol].hasMine = true;
                    //FieldBoard[row][col].isRevealed = true;
                    RevealZeros(row, col);
                } else {

                    FieldBoard[row][col].isRevealed = true;

                }
            }
        }
    }
}

bool MineSweeperBoard::IsRevealed(int row, int col) const {

    if (CheckIfTheFieldIsInTheBoard(row, col)) {
        if (FieldBoard[row][col].isRevealed) {

            return true;
        } else {

            return false;
        }
    } else {

        return false;
    }
}

char MineSweeperBoard::GetInfoAboutTheField(int row, int col) const {

    char Info = '0';

    if (!CheckIfTheFieldIsInTheBoard(row, col)) {

        Info = '#';
    }

    if (!FieldBoard[row][col].isRevealed and FieldBoard[row][col].hasFlag) {

        Info = 'F';
    }

    if (!FieldBoard[row][col].isRevealed and !FieldBoard[row][col].hasFlag) {

        Info = '_';
    }

    if (FieldBoard[row][col].isRevealed and FieldBoard[row][col].hasMine) {

        Info = 'X';
    }

    if (FieldBoard[row][col].isRevealed and !FieldBoard[row][col].hasMine and CountMinesAround(row, col) >= 0 and
        CountMinesAround(row, col) <= 82) {

        if (CountMinesAround(row, col) == 0) {
            Info = '0';
        }

        if (CountMinesAround(row, col) == 1) {
            Info = '1';
        }
        if (CountMinesAround(row, col) == 2) {
            Info = '2';
        }
        if (CountMinesAround(row, col) == 3) {
            Info = '3';
        }
        if (CountMinesAround(row, col) == 4) {
            Info = '4';
        }
        if (CountMinesAround(row, col) == 5) {
            Info = '5';
        }
        if (CountMinesAround(row, col) == 6) {
            Info = '6';
        }
        if (CountMinesAround(row, col) == 7) {
            Info = '7';
        }
        if (CountMinesAround(row, col) == 8) {
            Info = '8';
        }
    }
    return Info;
}