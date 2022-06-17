#include <iostream>
#include <string.h>
#include <fstream>

#include "Game/Console/ConsoleHandler.cpp"


using namespace std;

int main(int argc, char** argv){
    GameController gameController = GameController();
    gameController.loadFromFile("Level1_map.txt");

    cout<<gameController;

}
