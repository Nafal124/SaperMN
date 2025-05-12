#ifndef SAPER_MSSFMLCONTROLLER_H
#define SAPER_MSSFMLCONTROLLER_H


#include "MineSweeperBoard.h"
#include "MSSFMLView.h"

class MSSFMLController {

    MineSweeperBoard &msb;
    MSSFMLView &msbsfml;

public:

    void play(sf::RenderWindow &window) const;

    MSSFMLController(MineSweeperBoard &msboard, MSSFMLView &msboardview);

};


#endif //SAPER_MSSFMLCONTROLLER_H
