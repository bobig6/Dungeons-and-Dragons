#include <iostream>
#include <string.h>
#include <fstream>

#include "Game/Console/ConsoleHandler.cpp"


using namespace std;

int main(int argc, char** argv){
    GameController gameController = GameController();
    gameController.loadFromFile("Level1_map.txt");


    ConsoleHandler ch = ConsoleHandler(gameController);
//
//    ch.printMap();
//    ch.delimiter(100);
    ch.move();
}
