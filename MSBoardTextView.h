#ifndef SAPER_MSBOARDTEXTVIEW_H
#define SAPER_MSBOARDTEXTVIEW_H

#include "MineSweeperBoard.h"


class MSBoardTextView {

    MineSweeperBoard &msb;

public:

    void display() const;

    explicit MSBoardTextView(MineSweeperBoard &msboard);

};


#endif //SAPER_MSBOARDTEXTVIEW_H
