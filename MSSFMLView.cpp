#include "MSSFMLView.h"

MSSFMLView::MSSFMLView(MineSweeperBoard &msboard) : msb(msboard) {

}

void MSSFMLView::DrawOnWindow(sf::RenderWindow &window) const {
    sf::Texture square;
    if (!square.loadFromFile("../jpegs/square.jpeg")) {
        exit(-1);
    }
    sf::Texture blank;
    if (!blank.loadFromFile("../jpegs/blank.jpeg")) {
        exit(-1);
    }
    sf::Texture one;
    if (!one.loadFromFile("../jpegs/1.jpeg")) {
        exit(-1);
    }
    sf::Texture two;
    if (!two.loadFromFile("../jpegs/2.jpeg")) {
        exit(-1);
    }
    sf::Texture three;
    if (!three.loadFromFile("../jpegs/3.jpeg")) {
        exit(-1);
    }
    sf::Texture four;
    if (!four.loadFromFile("../jpegs/4.jpeg")) {
        exit(-1);
    }
    sf::Texture five;
    if (!five.loadFromFile("../jpegs/5.jpeg")) {
        exit(-1);
    }
    sf::Texture six;
    if (!six.loadFromFile("../jpegs/6.jpeg")) {
        exit(-1);
    }
    sf::Texture seven;
    if (!seven.loadFromFile("../jpegs/7.jpeg")) {
        exit(-1);
    }
    sf::Texture eight;
    if (!eight.loadFromFile("../jpegs/8.jpeg")) {
        exit(-1);
    }
    sf::Texture flag;
    if (!flag.loadFromFile("../jpegs/flag.jpeg")) {
        exit(-1);
    }
    sf::Texture mine;
    if (!mine.loadFromFile("../jpegs/explode.jpeg")) {
        exit(-1);
    }

    for (int nrow = 0; nrow < msb.GetBoardHeight(); nrow++) {
        for (int ncol = 0; ncol < msb.GetBoardWidth(); ncol++) {

            sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(window.getSize().x) / static_cast<float>(msb.GetBoardWidth()), static_cast<float>(window.getSize().y) / static_cast<float>(msb.GetBoardHeight())));
            rectangle.setPosition(static_cast<float>(ncol * window.getSize().x) / static_cast<float>(msb.GetBoardWidth()),static_cast<float>(nrow * window.getSize().y) / static_cast<float>(msb.GetBoardHeight()));

            if (msb.GetInfoAboutTheField(nrow, ncol) == '_')
                rectangle.setTexture(&square);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == 'F')
                rectangle.setTexture(&flag);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == 'X')
                rectangle.setTexture(&mine);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == '0')
                rectangle.setTexture(&blank);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == '1')
                rectangle.setTexture(&one);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == '2')
                rectangle.setTexture(&two);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == '3')
                rectangle.setTexture(&three);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == '4')
                rectangle.setTexture(&four);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == '5')
                rectangle.setTexture(&five);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == '6')
                rectangle.setTexture(&six);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == '7')
                rectangle.setTexture(&seven);

            else if (msb.GetInfoAboutTheField(nrow, ncol) == '8')
                rectangle.setTexture(&eight);

            else
                rectangle.setFillColor(sf::Color::White);

            window.draw(rectangle);
        }
    }
}
