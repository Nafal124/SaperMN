#ifndef SAPER_MSSFMLVIEW_H
#define SAPER_MSSFMLVIEW_H

#include <SFML/Graphics.hpp>

#include "MineSweeperBoard.h"

class MSSFMLView {

    MineSweeperBoard &msb;

public:

    explicit MSSFMLView(MineSweeperBoard &msboard);

    void DrawOnWindow(sf::RenderWindow &window) const;
};


#endif //SAPER_MSSFMLVIEW_H
