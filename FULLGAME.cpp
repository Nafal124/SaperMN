#include <iostream>
#include <sstream>

#include "FULLGAME.h"
#include "MineSweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"
#include "MSSFMLView.h"
#include "MSSFMLController.h"
#include "MSMenu.h"

void FULLGAME::TEXT_Game() {

    int rows, cols;
    int counter = 0;
    GameMode Mode;
    int ModeChoice;
    std::string input;

    do {

        if (counter != 0) {

            std::cout << "Wrong size! Rows and columns have to be greater than 1 and less than 39!" << std::endl;
        }

        if (counter > 5) {

            exit(-1);
        }

        counter++;

        std::cout << "Enter amount of rows and columns for your board. Enter them in the form - [Rows Columns] or [exit]/[quit] to leave." << std::endl;
        std::getline(std::cin, input);

        if ((input[0]=='q' and input[1]=='u' and input[2]=='i' and input[3]=='t') or (input[0]=='e' and input[1]=='x' and input[2]=='i' and input[3]=='t')) {

            exit (-1);
        }

        std::istringstream iss(input);
        iss >> rows >> cols;

    } while (rows <= 1 or cols <= 1 or rows > 38 or cols > 38);

    counter = 0;

    do {

        if (counter > 5) {

            exit(-1);
        }
        counter++;

        std::cout << "Choose level of difficulty. 1 - easy, 2 - normal, 3 - hard or [quit]/[exit] to leave." << std::endl;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> ModeChoice;

        if ((input[0]=='q' and input[1]=='u' and input[2]=='i' and input[3]=='t') or (input[0]=='e' and input[1]=='x' and input[2]=='i' and input[3]=='t')) {

            exit (-1);
        }

    } while (ModeChoice < 1 or ModeChoice > 3);

    if (ModeChoice == 1) {

        Mode = EASY;
    }

    if (ModeChoice == 2) {

        Mode = NORMAL;
    }

    if (ModeChoice == 3) {

        Mode = HARD;
    }

    MineSweeperBoard game(rows, cols, Mode);
    MSBoardTextView view(game);
    MSTextController ctrl(game, view);

    ctrl.play();
    game.debug_display();


}

void FULLGAME::SFML_Game() {

    int rows, cols;
    int counter = 0;
    std::string input;

    do {

        if (counter != 0) {

            std::cout << "Wrong size! Rows and columns have to be greater than 1 and less than 101!" << std::endl;
        }

        if (counter > 5) {

            exit(-1);
        }

        counter++;

        std::cout << "Enter amount of rows and columns for your board. Enter them in the form - [Rows Columns] or [exit]/[quit] to leave." << std::endl;
        std::getline(std::cin, input);

        if ((input[0]=='q' and input[1]=='u' and input[2]=='i' and input[3]=='t') or (input[0]=='e' and input[1]=='x' and input[2]=='i' and input[3]=='t')) {

            exit (-1);
        }

        std::istringstream iss(input);
        iss >> rows >> cols;

    } while (rows <= 1 or cols <= 1 or rows > 100 or cols > 100);

    std::cout << "Choose level of difficulty." << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 800), "MiNe sweeper!");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    sf::Image logo;

    if (!logo.loadFromFile("../jpegs/logo.jpeg")) {

        exit(-1);
    }

    window.setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());

    MSMenu Menu;
    GameMode Mode = Menu.Menu(window);
    MineSweeperBoard board(cols, rows, Mode);
    MSSFMLView view(board);
    MSSFMLController game_controller(board, view);

    game_controller.play(window);
    board.debug_display();

}

void FULLGAME::GAME() {

    int choice;
    int counter = 0;
    std::string input;
    int play_again=0;

    do {

        if (counter > 5) {

            exit(-1);
        }

        std::cout << "W jakiej wersji uruchamiasz program - tekstowej - 1 czy graficznej - 2?" << std::endl;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> choice;

        counter++;

    } while (choice < 1 or choice > 2);

    switch (choice) {

        case 1 :

            TEXT_Game();
            break;

        case 2 :

            while (play_again!=100) {
                SFML_Game();
                play_again++;
            }
            break;

        default :

            break;

    }
}
