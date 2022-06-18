#include <utility>

#include "../Character/Hero.cpp"
#include "../Map/Map.cpp"
#include "../Character/Monster.cpp"
#include "../GameController.cpp"

#include "BufferToogle.cpp"

class ConsoleHandler{
    string fileName;
    GameController gameController;
    bool isSaved = true;



public:
    ConsoleHandler() : gameController(){
        fileName = "Default.txt";
    };

    explicit ConsoleHandler(const GameController &gameController) : gameController(gameController) {
        fileName = "Default.txt";
    }

    explicit ConsoleHandler(string filename){
        gameController = GameController();
        bool isOpened = gameController.loadFromFile(std::move(filename));
        if(!isOpened){
            cout<<"Trying to open file with constructor failed";
            std::exit(1);
        }
    }
    // SECTION: MAIN---------------------------------------------------------------------------------------------


    /*! This is the main menu mode in the game. It supports the following commands:
     *      - open
     *      - ls
     *      - help
     *      - new game
     *      - exit
     */
    void main(){

        while(true){
            string current_command;
            getline(cin, current_command);
            if(current_command == "open"){
                string file;
                cout<<"Name of the file: ";
                getline(cin, file);
                bool isOpened = open(file);
                if(isOpened) gameStart();
            }
            else if(current_command == "new game"){
                string file;
                cout<<"Name of the file: ";
                getline(cin, file);
                bool isOpened = newGame(file);
                if(isOpened) gameStart();
            }
            else if(current_command == "exit"){
                exit();
                break;
            }
            else if(current_command == "help"){
                help();
            }
            else if(current_command == "ls"){
                system("ls");
            }
            else{
                cout<<"Command not recognized."<<endl;
            }

        }
    }


    /*! This is the game mode. It allows the player to work with an opened file. The following commands are supported:
     *      - save
     *      - close
     *      - saveAs
     *      - move
     *      - help
     *      - exit
     */
    void gameStart(){
        while(true){
            string current_command;
            getline(cin, current_command);
            if(current_command == "save"){
                save();
            }
            else if(current_command == "saveAs"){
                string file;
                cout<<"Name of the file you want to save to: ";
                getline(cin, file);
                saveAs(file);
            }
            else if(current_command == "close"){
                close();
                break;
            }
            else if(current_command == "exit"){
                exit();
            }
            else if(current_command == "help"){
                helpGameStart();
            }
            else if(current_command == "move"){
                move();
                system("clear");
            }
            else{
                cout<<"Command not recognized."<<endl;
            }

        }
    }


    // SECTION: PRINTERS-----------------------------------------------------------------------------------------
    void printMap(){
        cout<<"Level "<<gameController.level<<endl;
        cout<<gameController.map;
    }

    void printHeroStats(){
        cout<<gameController.hero;
    }

    /*! Creates a delimiter with a given size*/
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

    /*! Closes the current file without saving and sets the filename to " "*/
    void close(){
        cout<<"Successfully closed "<<fileName<<endl;
        fileName = " ";
    }

    /*! Saves the game in a file with a given name*/
    void saveAs(const string& name){
        // Opening the file
        ofstream out;
        out.open(name, ios::out);
        if(!out){
            cout << "Couldn't open file: " << name<<endl;
            return;
        }

        gameController.save(out);
        cout << "Successfully saved file" << endl;
        isSaved = true;
        out.close();
    }

    /*! Prints info in main mode*/
    void help(){
        cout<<"The following commands are supported in main mode: "<<endl;
        cout<<"open                  opens a currently existing game file"<<endl;
        cout<<"new game              creates new game with a given name"<<endl;
        cout<<"help                  prints this information"<<endl;
        cout<<"ls                    prints all the files in the current folder"<<endl;
        cout<<"exit                  exits the program"<<endl;
    }

    /*! Prints info in game mode*/
    void helpGameStart() {
        cout<<"The following commands are supported in game mode: "<<endl;
        cout<<"save                  saves the game in the currently loaded file"<<endl;
        cout<<"saveAs                saves the game in a new file"<<endl;
        cout<<"move                  starts the game. To exit the game enter q"<<endl;
        cout<<"help                  prints this information"<<endl;
        cout<<"close                 closes the file without saving"<<endl;
        cout<<"exit                  exits the program"<<endl;
    }

    /*! This function handles the exit command.
     * If a file is opened and not saved it prints a warning message. Else it just closes the program*/
    void exit(){
        if(isSaved){
            cout<<"Exiting program...";
            std::exit(0);
        }
        else{
            if(fileName == " ") {
                cout<<"Exiting program...";
                std::exit(0);
            }
            else{
                cout<<"You have an open file with unsaved changes, please select close or save first."<<endl;
            }
        }
    }

    /*! Opens file with a given name. Returns false if unsuccessfull*/
    bool open(string name){
        fileName = name;
        gameController = GameController();
        bool isOpened = gameController.loadFromFile(std::move(name));
        if(!isOpened) return false;
        cout<<"Successfully opened "<< fileName <<endl;

    }
    /*! Creates a new game with a given name. It gives the player the opportunity to choose a race.
     * Then it creates a new game with those parameters BUT DOESNT SAVE IT!!!*/
    bool newGame(string new_name){
        fileName = std::move(new_name);

        while(true){
            // Get the race
            string race;
            cout << "Select race (Human | Mage | Warrior): ";
            cin>>race;
            //Determining the race
            if(race == "Human"){
                gameController = GameController(Human);
                break;
            } else if(race == "Mage"){
                gameController = GameController(Mage);
                break;
            } else if(race == "Warrior"){
                gameController = GameController(Warrior);
                break;
            }else{
                cout << "Couldn't recognise this race. Try again." << endl;
            }
        }

        bool isOpened = gameController.loadMapFromFile("Level1.txt");
        if(!isOpened) return false;
        cout<<"Successfully created new game with name: "<< fileName <<endl;
        return true;
    }

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
    void foundTreasure(){
        isSaved = false;
    }
    void fight(){
        isSaved = false;
    }
    void gameOver(){
        isSaved = false;
    }
    void levelCompleted(){
        isSaved = false;
        gameController.level++;
    }

    /*! Clears the screen and then prints the map and the hero stats*/
    void refresh(){
        std::system("clear");
        delimiter(0);
        printMap();
        printHeroStats();
        delimiter(100);
        isSaved = false;
    }

};