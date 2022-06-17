#include "../Character/Hero.cpp"
#include "../Map/Map.cpp"
#include "InputMode.cpp"
#include "../Character/Monster.cpp"
#include "../GameController.cpp"

class ConsoleHandler{
    InputMode inputMode;
    GameController gameController;



public:
    ConsoleHandler() : gameController(){
        inputMode = GAME_START;
    };

    explicit ConsoleHandler(const GameController &gameController) : gameController(gameController) {
        inputMode = GAME_START;
    }

    // SECTION: PRINTERS-----------------------------------------------------------------------------------------
    void printMap(){

    }
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
    void move(){}

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