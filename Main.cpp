#include <iostream>
#include <string.h>
#include <fstream>

#include "Game/Console/ConsoleHandler.cpp"

/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is a recreation of the famous game Dungeons and Dragons for OOP class in FMI
 *
 * \section repo_sec Repo
 *
 * \subsection rep https://github.com/bobig6/Dungeons-and-Dragons
 *
 */

using namespace std;

int main(int argc, char** argv){
    ConsoleHandler ch = ConsoleHandler();
    ch.main();
}
