#include <utility>

#include "../Character/Hero.cpp"
#include "../Map/Map.cpp"
#include "InputMode.cpp"
#include "../Character/Monster.cpp"
#include "../GameController.cpp"

#include "BufferToogle.cpp"

class ConsoleHandler{
    string fileName;
    InputMode inputMode;
    GameController gameController;



public:
    ConsoleHandler() : gameController(){
        fileName = "Default.txt";
        inputMode = GAME_START;
    };

    explicit ConsoleHandler(const GameController &gameController) : gameController(gameController) {
        inputMode = GAME_START;
        fileName = "Default.txt";
    }

    explicit ConsoleHandler(string filename){
        inputMode = GAME_START;
        gameController = GameController();
        gameController.loadFromFile(std::move(filename));
    }

    // SECTION: PRINTERS-----------------------------------------------------------------------------------------
    void printMap(){
        cout<<"Level "<<gameController.level<<endl;
        cout<<gameController.map;
    }

    void printHeroStats(){
        cout<<gameController.hero;
    }

    void delimiter(int size){
        for (int i = 0; i < size; ++i) {
            cout<<'-';
        }
        cout<<endl;
    }



    // SECTION: COMMANDS-----------------------------------------------------------------------------------------
    /*! Saves the game at current file*/
    void save(){
        saveAs(fileName);
    }


    void close(){}

    /*! Saves the game in a file with a given name*/
    void saveAs(const string& name){
        // Opening the file
        ofstream out;
        out.open(name, ios::out);
        if(!out){
            throw invalid_argument("Couldn't open file");
        }

        gameController.save(out);

        out.close();
    }
    void help(){}
    void exit(){}
    void open(){

    }
    void newGame(){}

    /*! In this mode the player uses W,A,S,D to move in the map. To end the move you press q*/
    void move(){
        // Refresh the screen
        refresh();

        char c;

        // Set the terminal to raw mode
        BufferToggle bf{};
        bf.off();

        while(true) {
            c = (char)std::getchar();
            // terminate when "q" is pressed
            if(c == 'q') {
                break;
            }
            std::cout << "\b \b";
            char last_char = ' ';

            // check the input
            switch (c) {
                case 'w':
                    last_char = gameController.map.moveUp();
                    refresh();
                    break;
                case 'a':
                    last_char = gameController.map.moveLeft();
                    refresh();
                    break;
                case 's':
                    last_char = gameController.map.moveDown();
                    refresh();
                    break;
                case 'd':
                    last_char = gameController.map.moveRight();
                    refresh();
                    break;
            }

            // Checking what is the player stepped onto
            if(last_char == 'M') fight();
            if(last_char == 'T') foundTreasure();
            if(last_char == '0') levelCompleted();
        }
        bf.on();
    }

    // SECTION: EVENTS-------------------------------------------------------------------------------------------
    void foundTreasure(){}
    void fight(){}
    void gameOver(){}
    void levelCompleted(){
        gameController.level++;
    }

    /*! Clears the screen and then prints the map and the hero stats*/
    void refresh(){
        std::system("clear");
        delimiter(0);
        printMap();
        printHeroStats();
        delimiter(100);
    }

    InputMode getInputMode() const {
        return inputMode;
    }

    void setInputMode(InputMode newInputMode) {
        ConsoleHandler::inputMode = newInputMode;
    }

};