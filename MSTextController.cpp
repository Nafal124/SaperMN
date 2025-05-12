#include <iostream>
#include <algorithm>


#include "MSTextController.h"

MSTextController::MSTextController(MineSweeperBoard &msboard, MSBoardTextView &msboardview) : msb(msboard), msbtv(msboardview) {

}

void MSTextController::play() const {

    std::string input;
    char choice;
    int row, col;
    std::string rows_data, cols_data;


    while (msb.GetGameState() == RUNNING) {

        msbtv.display();
        std::cout << "What's your choice? f/F - toogle flag, r/R - reveal field or X to leave game." << std::endl;

        std::getline(std::cin, input);

        choice = input[0];


        switch (choice) {

            case 'f' :
            case 'F' :

                std::cout << "Which field do you wanna mark with flag? (row col)" << std::endl;

                while (true) {

                    std::cin >> rows_data;
                    std::cin >> cols_data;

                    if (std::all_of(rows_data.begin(), rows_data.end(), ::isdigit) and
                        std::all_of(cols_data.begin(), cols_data.end(), ::isdigit)) {

                        row = std::stoi(rows_data);
                        col = std::stoi(cols_data);
                        break;

                    }
                }

                msb.ToggleFlag(row, col);

                break;

            case 'r' :
            case 'R' :

                std::cout << "Which field do you wanna reveal? (row col)" << std::endl;

                while (true) {

                    std::cin >> rows_data;
                    std::cin >> cols_data;

                    if (std::all_of(rows_data.begin(), rows_data.end(), ::isdigit) and
                        std::all_of(cols_data.begin(), cols_data.end(), ::isdigit)) {

                        row = std::stoi(rows_data);
                        col = std::stoi(cols_data);
                        break;

                    }
                }

                msb.RevealField(row, col);

                break;

            case 'X' :

                std::cout << "You left the game" << std::endl;
                msb.debug_display();
                exit(-1);

            default :

                break;

        }
    }

    if (msb.GetGameState() == FINISHED_LOSS) {

        std::cout << "You lost GAMEOVER!" << std::endl;
    }

    if (msb.GetGameState() == FINISHED_WIN) {

        std::cout << "You won! Congrats!" << std::endl;
    }
}