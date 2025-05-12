#include <iostream>
#include <SFML/Audio.hpp>
#include "MSSFMLController.h"

MSSFMLController::MSSFMLController(MineSweeperBoard &msboard, MSSFMLView &msboardview) : msb(msboard), msbsfml(msboardview) {

}

void MSSFMLController::play(sf::RenderWindow &window) const {

    while (window.isOpen()) {

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

            if (msb.GetGameState() == RUNNING) {

                if (event.type == sf::Event::MouseButtonPressed) {

                    int wiersz = static_cast<int>(event.mouseButton.y * msb.GetBoardHeight() / window.getSize().y);
                    int kolumna = static_cast<int>(event.mouseButton.x * msb.GetBoardWidth() / window.getSize().x);

                    if (event.mouseButton.button == sf::Mouse::Left) {

                        msb.RevealField(wiersz, kolumna);

                    }

                    if (event.mouseButton.button == sf::Mouse::Right) {

                        msb.ToggleFlag(wiersz, kolumna);
                    }
                }

                //reset gry

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) and sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

                    return;

                }
            }
        }

        window.clear();
        msbsfml.DrawOnWindow(window);
        window.display();

        if (msb.GetGameState() == FINISHED_LOSS) {

            sf::SoundBuffer buffer;
            if (!buffer.loadFromFile("../sounds/boom.wav")) {

                exit(-1);
            }

            sf::Sound sound;
            sound.setBuffer(buffer);
            sound.play();

            sf::Text text;
            sf::Font font;
            if (!font.loadFromFile("../czcionka/arial.ttf")) {
                exit(-1);
            }

            text.setFont(font);
            text.setString("YOU LOST!");
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Red);

            text.setCharacterSize(window.getSize().y / 10);
            text.setPosition(static_cast<float>(window.getSize().x) / 2 - text.getGlobalBounds().width / 2,
                             static_cast<float>(window.getSize().y) / 2 - text.getGlobalBounds().height / 2);

            sf::sleep(sf::milliseconds(1000));

            window.clear();
            window.draw(text);
            window.display();

            while (sound.getStatus() == sf::Sound::Playing) {

                sf::sleep(sf::milliseconds(100));

            }

            window.close();
        }

        if (msb.GetGameState() == FINISHED_WIN) {

            sf::SoundBuffer buffer;
            if (!buffer.loadFromFile("../sounds/congrats.wav")) {

                exit(-1);
            }

            sf::Sound sound;
            sound.setBuffer(buffer);
            sound.play();

            sf::Text text;
            sf::Font font;
            if (!font.loadFromFile("../czcionka/arial.ttf")) {
                exit(-1);
            }

            text.setFont(font);
            text.setString("WON!");
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Green);

            text.setCharacterSize(window.getSize().y / 10);
            text.setPosition(static_cast<float>(window.getSize().x) / 2 - text.getGlobalBounds().width / 2,
                             static_cast<float>(window.getSize().y) / 2 - text.getGlobalBounds().height / 2);

            sf::sleep(sf::milliseconds(1000));

            window.clear();
            window.draw(text);
            window.display();

            while (sound.getStatus() == sf::Sound::Playing) {

                sf::sleep(sf::milliseconds(100));

            }

            window.close();
        }
    }
}