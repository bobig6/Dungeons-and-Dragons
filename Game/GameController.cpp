#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

class GameController{
public:
    /*! This contains the map of the current game*/
    Map map;
    /*! This is the main player's hero*/
    Hero hero;
    /*! A list with all the items on the map*/
    Item* treasures;
    /*! The number of treasures on the map*/
    int tr_size;

    /*! The current level number*/
    int level;
    // SECTION: HELPER FUNCTIONS--------------------------------------------------------------------------


    void loadFromFile(string fileName){
        // Opening the file
        ifstream in;
        in.open(fileName, ios::in);
        if(!in){
            throw invalid_argument("Couldn't open file");
        }

        load(in);

        in.close();
    }


    /*! This function loads the map and the treasure list from a file. The file has to have:
     *      - level
     *      - width of the map
     *      - height of the map
     *      - the map itself in a hxw char matrix
     *      - Hero (look at his operator >> for more details)
     *      - number of treasures
     *      - list of all the treasures with:
     *          - name
     *          - description
     *          - percent
     */
    void load(ifstream& in){
        in>>level;
        // Reading the width and the height of the map
        int width = 0;
        in>>width;
        int height = 0;
        in>>height;

        // Resizing the map
        map.resize(width, height);

        // This segment skips to the next line
        char next;
        while(in.get(next)) if (next == '\n')  break;

        // Reading the map
        map.load(in);

        //Reading the Hero
        in>>hero;

        // Reading number of treasures
        in>>tr_size;

        // Skip line
        while(in.get(next)) if (next == '\n')  break;

        // Reads all the treasures
        for (int i = 0; i < tr_size; ++i) {
            in>>treasures[i];
            // Skip line
            while(in.get(next)) if (next == '\n')  break;
        }

    }

    /*! Saves the GameController in this format:
     *      - level
     *      - map width
     *      - map height
     *      - map
     *      - hero
     *      - tr_size
     *      - list of all treasures*/
    void save(ofstream& out){
        out<<level<<endl;
        out<<map.getWight()<<endl;
        out<<map.getHeight()<<endl;
        map.save(out);
        hero.save(out);

        out<<tr_size<<endl;

        for (int i = 0; i < tr_size; ++i) {
            treasures[i].save(out);
        }
    }

    // SECTION: CONSTRUCTORS--------------------------------------------------------------------------------------------

    /*! Default constructor creates empty map with default hero and 2 empty treasures and 2 empty monsters, all at level 1*/
    GameController(){
        map = Map();
        hero = Hero();

        tr_size = 2;
        treasures = new Item[tr_size];
        for (int i = 0; i < tr_size; ++i) {
            treasures[i] = Item();
        }

        level = 1;
    }

    /*! Constructor for GameController sets level to 1*/
    GameController(const Map &map, const Hero &hero, Item *treasures, int tr_size){
        this->map = map;
        this->hero = hero;
        this->tr_size = tr_size;

        this->treasures = new Item[tr_size];

        setTreasures(treasures);


        this->level = 1;

    }

    /*! Copy constructor for GameController*/
    GameController(const GameController &other) : GameController(other.map, other.hero, other.treasures, other.tr_size){
        this->level = other.level;
    }

    virtual ~GameController(){
        delete [] treasures;
    }



    // SECTION: OPERATORS---------------------------------------------------------------------------------
    /*! Assignment operator*/
    GameController& operator=(const GameController& other){
        if(this != &other){
            this->map = other.map;
            this->hero = other.hero;
            this->tr_size = other.tr_size;
            this->level = other.level;
            setTreasures(other.treasures);
        }
        return *this;
    };


    friend ostream& operator<<(ostream& os, GameController& gameController);

    //SECTION: GETTERS AND SETTERS-----------------------------------------------------------------------

    void setTreasures(Item *newTreasures) {
        delete [] treasures;
        treasures = new Item[tr_size];
        for (int i = 0; i < tr_size; ++i) {
            treasures[i] = newTreasures[i];
        }
    }

};


ostream& operator<<(ostream& os, GameController& gameController)
{
    os<<gameController.map<<endl;

    os<<gameController.hero<<endl;


    os<<"Treasures: "<<endl;
    for (int i = 0; i < gameController.tr_size; ++i) {
        os<<gameController.treasures[i]<<endl;
    }
    return os;
}





