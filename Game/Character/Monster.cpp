
class Monster{
    float strength;
    float mana;
    float health;

    Armor armor;

    int posX;
    int posY;

public:

    /*! Assignment operator for the Monster class*/
    Monster& operator=(const Monster& other){
        if(this != &other){
            this->strength = other.strength;
            this->mana = other.mana;
            this->health = other.health;
            this->armor = other.armor;
            this->posX = other.posX;
            this->posY = other.posY;
        }
        return *this;
    };

};
