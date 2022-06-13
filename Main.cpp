#include <iostream>
#include <string.h>
#include <fstream>

#include "Game/GameController.cpp"


using namespace std;

int main(int argc, char** argv){
    ifstream file("Level1_map.txt", ios::out);
    if(!file){
        throw invalid_argument("Couldn't open file");
    }

    Map map = Map(11, 11);
    map.load(file);

    file.close();
    cout<<map;
    cout<<"Hero at: (" << map.getCurrentX()<<","<<map.getCurrentY()<<") \n";

    map.moveRight();
    map.moveRight();
    map.moveDown();
    map.moveRight();
    map.moveDown();
    map.moveLeft();


    cout<<map;
    cout<<"Hero at: (" << map.getCurrentX()<<","<<map.getCurrentY()<<") \n";
}
