#include "TESTY.h"
#include "MineSweeperBoard.h"
//#include "MSBoardTextView.h"

#include <cassert>
#include <cmath>
/*
 *
 *
 *Funkcje sprawdzajace ilosc odkrytych pol zostaly zakryte po dodaniu opcji odkrywania pol planszy wokol ktorych jest 0 min rekurencyjnie.
 *
 *
 */

void TESTY::test_ilosci(){

    MineSweeperBoard gra1(7,7,EASY);
    assert(gra1.GetHowManyMines()==std::ceil(gra1.GetBoardHeight()*gra1.GetBoardWidth()*0.1));
    MineSweeperBoard gra2(13,7,NORMAL);
    assert(gra2.GetHowManyMines()==std::ceil(gra2.GetBoardHeight()*gra2.GetBoardWidth()*0.2));
    MineSweeperBoard gra3(45,3,HARD);
    assert(gra3.GetHowManyMines()==std::ceil(gra3.GetBoardHeight()*gra3.GetBoardWidth()*0.3));

}

void TESTY::test_ilosci_bomb_wokol(){

    MineSweeperBoard gra(10, 10, DEBUG);

    assert(gra.GetHowManyFieldsAreRevealed()==0);
    gra.RevealField(1,0);
    gra.RevealField(2,9);
    gra.RevealField(2,1);
    gra.RevealField(6,7);
    //assert(gra.GetHowManyFieldsAreRevealed()==4);

    assert(gra.CountMinesAround(1,0)==4);
    assert(gra.CountMinesAround(2,9)==0);
    assert(gra.CountMinesAround(2,1)==3);
    assert(gra.CountMinesAround(6,7)==2);

}

void TESTY::test_flag(){

    MineSweeperBoard gierka (10, 10, DEBUG);


    gierka.ToggleFlag(5,7);
    assert(gierka.HasFlag(5,7)==true);
    gierka.ToggleFlag(5,7);
    assert(gierka.HasFlag(5,7)==false);
    gierka.ToggleFlag(5,7);
    assert(gierka.HasFlag(5,7)==true);

}

void TESTY::test_ujawnianiapol(){

    MineSweeperBoard gierka (10, 10, DEBUG);

    assert(gierka.GetHowManyFieldsAreRevealed()==0);
    gierka.RevealField(1,0);
    assert(gierka.GetHowManyFieldsAreRevealed()==1);

    assert(gierka.IsRevealed(1,0)==true);
    assert(gierka.GetInfoAboutTheField(1,0)=='4');
    assert(gierka.GetInfoAboutTheField(8,3)=='_');
    gierka.ToggleFlag(8,3);
    gierka.ToggleFlag(8,3);
    assert(gierka.GetInfoAboutTheField(8,3)=='_');
    gierka.RevealField(8, 3);
    //assert(gierka.GetHowManyFieldsAreRevealed()==2);
    assert(gierka.GetInfoAboutTheField(8,3)=='0');

    assert(gierka.GetGameState()==RUNNING);

    //gierka.debug_display();

}

void TESTY::test_czy_gra_trwa_po_odkryciu_miny() {

    MineSweeperBoard gra(10,10,DEBUG);
    assert(gra.GetGameState()==RUNNING);
    gra.RevealField(0,0);
    assert(gra.GetGameState()==RUNNING);
    assert(gra.GetInfoAboutTheField(0,0)=='2' or gra.GetInfoAboutTheField(0,0)=='3');
    gra.ToggleFlag(0,0);
    assert(gra.HasFlag(0,0)==false);
    gra.RevealField(0,1);
    assert(gra.GetInfoAboutTheField(0,1)=='X');
    assert(gra.GetGameState()==FINISHED_LOSS);
    gra.RevealField(0,2); //Sprawdzic czy kolejne pola mozna odkryc gdy gra jest juz przegrana!
    gra.RevealField(0,3);
    assert(gra.IsRevealed(0,2)==false and gra.IsRevealed(0,3)==false);

    //gra.debug_display();
}

void TESTY::test_wygranej() {

    MineSweeperBoard gra(2,2, DEBUG);

    gra.RevealField(1,0);
    assert(gra.GetGameState()==FINISHED_WIN);
    gra.RevealField(0,0);
    gra.RevealField(0,1);
    gra.RevealField(1,1);
    assert(gra.IsRevealed(0,0)==false and gra.IsRevealed(0,1)==false and gra.IsRevealed(1,1)==false);
    
}

void TESTY::test_klasy_msboardtextview(){

    MineSweeperBoard gra (10, 10, DEBUG);
    //MSBoardTextView view (gra);
    //view.display();
    gra.RevealField(1,1);
    //view.display();
    gra.RevealField(1,0);
    //view.display();
    gra.RevealField(0,0);
    //view.display();
    gra.RevealField(2,2);
    //view.display();
    assert(gra.GetGameState()==FINISHED_LOSS);

}

TESTY::TESTY(){

    test_ilosci();
    test_ilosci_bomb_wokol();
    test_flag();
    test_ujawnianiapol();
    test_czy_gra_trwa_po_odkryciu_miny();
    test_wygranej();
    test_klasy_msboardtextview();
}