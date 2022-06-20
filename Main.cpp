#include <iostream>
#include <string.h>
#include <fstream>

#include "Game/Console/ConsoleHandler.cpp"


using namespace std;

int main(int argc, char** argv){
    ConsoleHandler ch = ConsoleHandler();
    ch.main();
}
