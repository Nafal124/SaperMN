#include <iostream>
#include <iomanip>

#include "MSBoardTextView.h"
#include "MineSweeperBoard.h"

MSBoardTextView::MSBoardTextView(MineSweeperBoard &msboard) : msb(msboard) {

}

void MSBoardTextView::display() const {

    std::cout<<"  ";
    for (int ncol=0;ncol<msb.GetBoardWidth();ncol++){

        std::cout<<" ";
        std::cout<<std::setw(2)<<ncol;

    }
    std::cout<<std::endl;

    for (int nrow=0; nrow<msb.GetBoardHeight(); ++nrow){

        std::cout<<std::setw(2)<<nrow<<" ";

        for (int ncol=0; ncol<msb.GetBoardWidth(); ncol++){

            std::cout<<"["<<msb.GetInfoAboutTheField(nrow, ncol)<<"]";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}