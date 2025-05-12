#ifndef SAPER_MSTEXTCONTROLLER_H
#define SAPER_MSTEXTCONTROLLER_H

#include "MineSweeperBoard.h"
#include "MSBoardTextView.h"

class MSTextController {

    MineSweeperBoard &msb;
    MSBoardTextView &msbtv;

public:

    void play() const;

    MSTextController(MineSweeperBoard &msboard, MSBoardTextView &msboardview);

};

#endif //SAPER_MSTEXTCONTROLLER_H
