#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class Map{
    /*! This holds the map that the player can move in*/
    char** field;
    /*! The width of the map*/
    int width;
    /*! The height of the map*/
    int height;

    /*! Current position of the player on the X axis*/
    int currentX;
    /*! Current position of the player on the Y axis*/
    int currentY;

public:
    // SECTION: HELPER FUNCTiONS

    //! This function deletes the whole field and deallocates the memory
    void deleteField(){
        // Delete the current value of the field object
        for (int i = 0; i < height; ++i) {
            delete [] field[i];
        }
        delete [] field;
    }

    /*! Allocates a field with current width and height */
    void allocField(){
        field = new char*[height];
        for (int i = 0; i < height; ++i) {
            field[i] = new char[width];
        }
    }

    /*! A function to save the map into a text file*/
    void save(ofstream& os){
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                os<<field[i][j];
            }
            os<<"\n";
        }
    }

    /*! A function to load the map from a text file*/
    void load(ifstream& file){
        file>>(*this);
    }

    /*! This function finds and sets the current hero position. It returns true if it finds it.
     * If it doesnt find anything it sets the current position to (0,0), overrides the map and returns false*/
    bool findCurrentHeroPosition(){
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if(field[i][j] == 'H'){
                    currentY = i;
                    currentX = j;
                    return true;
                }
            }
        }
        cout << "This map doesnt have a hero in it. Putting the hero in (0,0) position"<<endl;
        currentX = 0;
        currentY = 0;
        field[0][0] = 'H';
        return false;
    }

    // SECTION: CONSTRUCTORS-------------------------------------------------------------------------------------------

    /*! Default constructor. Creates 10x10 matrix filled with [#] */
    Map(){
        currentY = 0;
        currentX = 0;
        width = 10;
        height = 10;

        // Creating new field with width 10 and height 10 and only filled with *
        field = new char*[height];
        allocField();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                field[i][j] = '#';
            }
        }

    }

    /*! Constructor for Map class with only height and width. Creates field with all # */
    Map(int width, int height) : width(width), height(height) {
        currentX = 0;
        currentY = 0;
        field = new char*[height];
        allocField();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                field[i][j] = '#';
            }
        }
    }

    /*! Constructor for Map class. Creates new char** and calls the setter */
    Map(char **new_field, int width, int height) : width(width), height(height) {
        currentX = 0;
        currentY = 0;
        field = new char*[height];
        allocField();
        setField(new_field, width, height);
    }

    Map(const Map &other) : Map(other.field, other.width, other.height){}

    virtual ~Map() {
        deleteField();
    }

    // SECTION: OPERATORS-------------------------------------------------------------------------------------------

    Map& operator=(const Map& other){
        if(this != &other){
            this->currentX = other.currentX;
            this->currentY = other.currentY;
            this->width = other.width;
            this->height = other.height;
            setField(other.field, other.width, other.height);
        }
        return *this;
    };


    friend ostream& operator<<(ostream& os, Map& map);
    friend istream& operator>> (istream& is, Map& map);

    // SECTION: MOVEMENT---------------------------------------------------------------------------------------------

    /*! This function moves the player left by 1 character and returns the value of the new position
     * If the player is at the corner or next to a wall it returns ' ' as the value which is an error state
     * Else it moves the character by 1 char and returns the value of the new position
     * At the old position it puts '.', which means that we can visit only once items and monsters*/
    char moveRight(){
        if(currentX+1 >= width || field[currentY][currentX+1] == '#') return ' ';
        field[currentY][currentX] = '.';
        currentX++;
        char prev = field[currentY][currentX];
        field[currentY][currentX] = 'H';
        return prev;
    }

    /*! This function moves the player right by 1 character and returns the value of the new position
     * If the player is at the corner or next to a wall it returns ' ' as the value which is an error state
     * Else it moves the character by 1 char and returns the value of the new position
     * At the old position it puts '.', which means that we can visit only once items and monsters*/
    char moveLeft(){
        if(currentX-1 < 0 || field[currentY][currentX-1] == '#') return ' ';
        field[currentY][currentX] = '.';
        currentX--;
        char prev = field[currentY][currentX];
        field[currentY][currentX] = 'H';
        return prev;
    }

    /*! This function moves the player up by 1 character and returns the value of the new position
     * If the player is at the corner or next to a wall it returns ' ' as the value which is an error state
     * Else it moves the character by 1 char and returns the value of the new position
     * At the old position it puts '.', which means that we can visit only once items and monsters*/
    char moveUp(){
        if(currentY-1 < 0 || field[currentY-1][currentX] == '#') return ' ';
        field[currentY][currentX] = '.';
        currentY--;
        char prev = field[currentY][currentX];
        field[currentY][currentX] = 'H';
        return prev;
    }

    /*! This function moves the player down by 1 character and returns the value of the new position
     * If the player is at the corner or next to a wall it returns ' ' as the value which is an error state
     * Else it moves the character by 1 char and returns the value of the new position
     * At the old position it puts '.', which means that we can visit only once items and monsters*/
    char moveDown(){
        if(currentY+1 >= height || field[currentY+1][currentX] == '#') return ' ';
        field[currentY][currentX] = '.';
        currentY++;
        char prev = field[currentY][currentX];
        field[currentY][currentX] = 'H';
        return prev;
    }

    // SECTION: GETTERS AND SETTERS------------------------------------------------------------------------------------
    char **getField() const {
        return field;
    }

    void setField(char **new_field, int new_width, int new_height) {
        setHeight(new_height);
        setWight(new_width);

        deleteField();

        // Resizing the field and putting the new values in
        allocField();
        for (int i = 0; i < new_height; ++i) {
            for (int j = 0; j < new_width; ++j) {
                field[i][j] = new_field[i][j];
            }
        }
        findCurrentHeroPosition();
    }

    int getWight() const {
        return width;
    }

    void setWight(int new_width) {
        Map::width = new_width;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int new_height) {
        Map::height = new_height;
    }

    int getCurrentX() const {
        return currentX;
    }

    void setCurrentX(int new_currentX) {
        Map::currentX = new_currentX;
    }

    int getCurrentY() const {
        return currentY;
    }

    void setCurrentY(int new_currentY) {
        Map::currentY = new_currentY;
    }

};

ostream& operator<<(ostream& os, Map& map)
{
    for (int i = 0; i < map.height; ++i) {
        for (int j = 0; j < map.width; ++j) {
            os<<map.field[i][j];
            os<<" ";
        }
        os<<"\n";
    }
    return os;
}

istream& operator>> (istream& is, Map& map)
{
    for (int i = 0; i < map.height; ++i) {
        string buff;
        getline(is, buff);
        for (int j = 0; j < map.width; ++j) {
            map.field[i][j] = buff[j];
        }
    }
    map.findCurrentHeroPosition();
    return is;
}
