#ifndef SAPER_MINESWEEPERBOARD_H
#define SAPER_MINESWEEPERBOARD_H

struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

enum GameMode {DEBUG, EASY, NORMAL, HARD};

enum GameState {RUNNING, FINISHED_WIN, FINISHED_LOSS};

class MineSweeperBoard {

    int width;
    int height;
    Field FieldBoard[100][100]{};

    void ClearBoard();
    void SetStart();
    void SetStartWhichDependsOnGameMode(const GameMode &mode);

    void RevealZeros(int row, int col);

public:
    //konstruktory

    MineSweeperBoard();
    MineSweeperBoard(int w, int h, GameMode mode);

    int GetBoardWidth() const;
    int GetBoardHeight() const;
    int GetHowManyMines() const;
    int GetHowManyFieldsAreRevealed() const;
    GameState GetGameState() const;
    char GetInfoAboutTheField(int row, int col) const;
    int CountMinesAround(int row, int col) const;

    bool CheckIfTheFieldIsInTheBoard(int row, int col) const;

    bool HasFlag(int row, int col) const;
    bool IsRevealed(int row, int col) const;

    void ToggleFlag(int row, int col);
    void RevealField(int row, int col);

    //wyswietla plansze w debugerze.

    void debug_display() const;

};


#endif //SAPER_MINESWEEPERBOARD_H
