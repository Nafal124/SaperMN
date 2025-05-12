#include "MSMenu.h"

#include <iostream>
#include <SFML/Graphics.hpp>

GameMode MSMenu::Menu(sf::RenderWindow &window) {

    GameMode Mode = DEBUG;

    sf::Texture EASY;
    if (!EASY.loadFromFile("../jpegs/easy.jpeg")) {
        exit(-1);
    }
    sf::Texture NORMAL;
    if (!NORMAL.loadFromFile("../jpegs/normal.jpeg")) {
        exit(-1);
    }
    sf::Texture HARD;
    if (!HARD.loadFromFile("../jpegs/hard.jpeg")) {
        exit(-1);
    }


    while (window.isOpen()) {

        sf::RectangleShape Choice_EASY(
                sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) / 3));
        Choice_EASY.setPosition(0, 0);
        Choice_EASY.setTexture(&EASY);
        sf::RectangleShape Choice_NORMAL(
                sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) / 3));
        Choice_NORMAL.setPosition(0, static_cast<float>(window.getSize().y) / 3);
        Choice_NORMAL.setTexture(&NORMAL);
        sf::RectangleShape Choice_HARD(
                sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) / 3));
        Choice_HARD.setPosition(0, static_cast<float>(2 * window.getSize().y) / 3);
        Choice_HARD.setTexture(&HARD);

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed or
                (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)) {

                window.close();
                exit(-1);

            }

            if (event.type == sf::Event::Resized) {

                sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width),
                                          static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if (event.mouseButton.y >= 0 and
                        event.mouseButton.y < static_cast<signed int>(window.getSize().y / 3)) {

                        Mode = GameMode::EASY;
                        return Mode;

                    }

                    if (event.mouseButton.y >= static_cast<signed int>(window.getSize().y / 3) and
                        event.mouseButton.y < static_cast<signed int>(2 * window.getSize().y / 3)) {

                        Mode = GameMode::NORMAL;
                        return Mode;

                    }

                    if (event.mouseButton.y >= static_cast<signed int>(2 * window.getSize().y / 3) and
                        event.mouseButton.y <= static_cast<signed int>(window.getSize().y)) {

                        Mode = GameMode::HARD;
                        return Mode;

                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

                Mode = GameMode::DEBUG;
                return Mode;

            }
        }

        window.clear();
        window.draw(Choice_EASY);
        window.draw(Choice_NORMAL);
        window.draw(Choice_HARD);
        window.display();

    }

    return Mode;
}