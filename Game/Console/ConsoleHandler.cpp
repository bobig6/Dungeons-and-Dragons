#include <utility>

#include "../Character/Hero.cpp"
#include "../Map/Map.cpp"
#include "../Character/Monster.cpp"
#include "../GameController.cpp"

#include "BufferToogle.cpp"

#include <random>

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
            gameController.map.deleteField();
            delete [] gameController.treasures;
            gameController.hero.clear();
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
            bool isGameOver = false;
            string current_command;
            getline(cin, current_command);
            if(current_command == "open"){
                string file;
                cout<<"Name of the file: ";
                getline(cin, file);
                bool isOpened = open(file);
                if(isOpened) isGameOver = gameStart();
            }
            else if(current_command == "new game"){
                string file;
                cout<<"Name of the file: ";
                getline(cin, file);
                bool isOpened = newGame(file);
                if(isOpened) isGameOver = gameStart();
            }
            else if(current_command == "exit"){
                cout<<"Exiting program...";
                return;
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
            if(isGameOver) return;
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
    bool gameStart(){
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
                if(isSaved){
                    return true;
                }
                else{
                    if(fileName == " ") {
                        return true;
                    }
                    else{
                        cout<<"You have an open file with unsaved changes, please select close or save first."<<endl;
                    }
                }
            }
            else if(current_command == "help"){
                helpGameStart();
            }
            else if(current_command == "move"){
                if(!move()){
                    return false;
                }
                system("clear");
            }
            else{
                cout<<"Command not recognized."<<endl;
            }

        }
        return false;
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
            getline(cin, race);
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
    bool move(){
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
            if(last_char == 'M') {
                if(!fight()) {
                    bf.on();
                    return false;
                }
            }
            if(last_char == 'T') foundTreasure();
            if(last_char == '0') levelCompleted();
        }
        bf.on();
        return true;
    }

    // SECTION: EVENTS-------------------------------------------------------------------------------------------

    void foundTreasure(){
        isSaved = false;
        system("clear");
        cout << "You have found a treasure!!!" << endl;

        // Picking random item from the list
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, gameController.tr_size-1); // define the range

        int tr_index = distr(gen);

        cout << gameController.treasures[tr_index];

        bool equip = false;
        while(true){
            cout << endl << "Do you want to equip it(yes/no): ";
            string decision;
            getline(cin, decision);
            if(decision == "yes"){
                equip = true;
                break;
            } else if(decision == "no"){
                equip = false;
                break;
            }else{
                cout<<"Answer not recognized. Try again: ";
            }
        }
        if(!equip){
            refresh();
            return;
        }

        switch (gameController.treasures[tr_index].getType()) {
            case WeaponType:
                gameController.hero.setWeapon(Weapon(gameController.treasures[tr_index]));
                break;
            case ArmorType:
                gameController.hero.setArmor(Armor(gameController.treasures[tr_index]));
                break;
            case SpellType:
                gameController.hero.setSpell(Spell(gameController.treasures[tr_index]));
                break;
        }
        refresh();

    }


    /*! This function is called when a player meets a monster. For a better game experience I decided to make the monsters not spawn randomly, but instead to be
     * placed on the map by the game designer. */
    bool fight(){
        isSaved = false;
        cout << "You have met a Monster. A fight has begun:" << endl;
        // Create the monster
        Monster enemy = Monster();
        enemy.levelUp((float)gameController.level);

        float heroHealth = gameController.hero.getHealth();

        // Random pick who is first
        bool heroTurn = false;
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 100); // define the range
        int rando = distr(gen);
        if(rando < 50) heroTurn = true;
        cout << "Your stats: "<<endl;
        printHeroStats();
        delimiter(100);
        cout << enemy;
        delimiter(100);


        while (true) {
            // Hero's turn
            if(heroTurn){
                float total_attack = 0;
                cout << "Your turn:" << endl;
                while(true) {
                    string decision;
                    cout << "Chose what to do (attack/spell): " << endl; getline(cin, decision);
                    if(decision == "attack"){
                        total_attack = gameController.hero.useAttack();
                        break;
                    }else if(decision == "spell"){
                        total_attack = gameController.hero.useSpell();
                        break;
                    }else{
                        cout << "Invalid command. Try again: " << endl;
                    }
                }

                enemy.dealDamage(total_attack);
                heroTurn = false;
            }
            // Monster's turn
            else{
                cout << "Enemy's turn:" << endl;
                float total_attack = 0;
                rando = distr(gen);
                if(rando < 50) {
                    // Monster calls Attack
                    total_attack = enemy.getStrength();
                    cout << "Monster chose to attack you" << endl;
                }else{
                    // Monster calls Spell
                    total_attack = enemy.getMana();
                    cout << "Monster chose to use a spell on you" << endl;
                }

                gameController.hero.dealDamage(total_attack);

                heroTurn = true;
            }

            string c;
            cout<< "Type anything to continue: "; cin>>c;

            // Refresh the screen
            system("clear");
            cout << "Your stats: "<<endl;
            printHeroStats();
            delimiter(100);
            cout << enemy;
            delimiter(100);

            if(gameController.hero.getHealth() <= 0){
                cout << "You died! You will be redirected to the Main Menu. You can load your last save." << endl;
                return false;
            }
            if(enemy.getHealth() <= 0){
                break;
            }

        }

        cout<<"You won!!!" << endl;
        if(gameController.hero.getHealth() < 0.5 * heroHealth){
            gameController.hero.setHealth(0.5f * heroHealth);
            cout << "You've taken too much damage. It's time to heal... Your health is restored to 50% of it's original state: " << gameController.hero.getHealth() << " points" << endl;
        }

        string c;
        cout<< "Type anything to continue: "; cin>>c;
        refresh();
        return true;
    }

    /*! This function is called when the level is complete.
     * It gives the player the opportunity to increase his stats by 30 points
     * When he does it tries to find a file for the next level. If it can't it asks for a filename for the next level*/
    void levelCompleted(){
        // Increases the level number and clears the screen
        isSaved = false;
        gameController.level++;
        system("clear");

        // Prints stats
        cout<<"Congratulations!!! You have completed this level"<<endl;
        cout<<"You have 30 bonus points to your skills:"<<endl;
        cout<<gameController.hero;

        int bonus = 30;
        int strBonus = 0;
        int manaBonus = 0;

        // This loop is for input of the bonus points
        while(true){
            bonus = 30;
            strBonus = 0;
            manaBonus = 0;


            while (true) {
                cout << "Give strength: ";
                string str;
                getline(cin, str);
                strBonus = stoi(str);
                if (strBonus > bonus || strBonus < 0) {
                    cout << "Invalid value. Try again" << endl;
                } else {
                    bonus -= strBonus;
                    break;
                }
            }

            cout << "You have " << bonus << " points left" << endl;
            while (true) {
                cout << "Give mana: ";
                string str;
                getline(cin, str);
                manaBonus = stoi(str);
                if (manaBonus > bonus || manaBonus < 0) {
                    cout << "Invalid value. Try again" << endl;
                } else {
                    bonus -= manaBonus;
                    break;
                }
            }

            cout << "Points left for health: " << bonus << endl;
            cout << "Do you want to save those points (y/n): " << endl;
            char res;
            cin>>res;
            if(res == 'y'){
                break;
            }
        }


        // Sets the bonus points
        gameController.hero.setStrength(gameController.hero.getStrength() + (float)strBonus);
        gameController.hero.setMana(gameController.hero.getMana() + (float)manaBonus);
        gameController.hero.setHealth(gameController.hero.getHealth() + (float)bonus);

        // Trying to load the next level
        cout<<endl<<"Loading next level...."<<endl;
        string next = "Level" + to_string(gameController.level) + ".txt";
        cout<<"Opening file: " << next << endl;

        bool isOpened = gameController.loadMapFromFile(next);
        if(!isOpened) {

            // If it doesn't find a file with that name it asks for a name for the next level
            cout << "The next level seems to be missing." << endl;

            while (true) {
                string name;
                cout << "Type the file name of the next level: ";
                getline(cin, name);
                // Checks if there is a valid file with that name
                if(gameController.loadMapFromFile(name)){
                    break;
                }
            }
        };
        cout<<"File opened successfully"<<endl;
        refresh();
        // Returns to move()
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