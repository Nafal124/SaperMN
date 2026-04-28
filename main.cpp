#include <cassert>
#include <ctime>
#include <stdlib.h>

#include "TESTY.h"
#include "FULLGAME.h"

int main() {
    srand(time(nullptr));
    TESTY testy;
    FULLGAME Game;
    Game.GAME();
    return 0;
}
