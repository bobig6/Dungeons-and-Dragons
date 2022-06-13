#include "../Character/Hero.cpp"
#include "../Map/Map.cpp"
#include "InputMode.cpp"
#include "../Character/Monster.cpp"

class ConsoleHandler{
    InputMode inputMode;
    Map map;
    Hero hero;
    Item* treasures;
    Monster* monsters;

public:
    // SECTION: PRINTERS-----------------------------------------------------------------------------------------
    void printMap(){}
    void printHeroStats(){}
    void delimiter(){}

    // SECTION: COMMANDS-----------------------------------------------------------------------------------------
    void save(){}
    void close(){}
    void saveAs(){}
    void help(){}
    void exit(){}
    void open(){}
    void newGame(){}

    // SECTION: EVENTS-------------------------------------------------------------------------------------------
    void foundTreasure(){}
    void fight(){}
    void gameOver(){}
    void levelCompleted(){}

    void refresh(){

    }

    InputMode getInputMode() const {
        return inputMode;
    }

    void setInputMode(InputMode newInputMode) {
        ConsoleHandler::inputMode = newInputMode;
    }

};