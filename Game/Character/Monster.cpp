
class Monster{
    float strength;
    float mana;
    float health;

    Armor armor;

public:
    // SECTION: HELPER FUNCTIONS--------------------------------------------------------------------------

    void save(ostream& os){
        os<<strength;
        os<<mana;
        os<<health;
        armor.save(os);
    }

    /*! Levels up the monster by increasing every stat by 10 for every level and armor by 5 for every level*/
    void levelUp(float level){
        strength += level*10;
        mana += level*10;
        health += level*10;
        armor.setPercent(armor.getPercent()+level*5);
    }


    // SECTION: CONSTRUCTORS-------------------------------------------------------------------------------
    Monster() {
        strength = 25;
        mana = 25;
        health = 50;

        armor = Armor("Dragon Scales", "The dragon scales decrease the damage done by 15%", 15);
    }

    Monster(float strength, float mana, float health, const Armor &armor) : strength(strength), mana(mana),
                                                                            health(health), armor(armor) {}

    Monster(const Monster &other) : Monster(other.strength, other.mana, other.health, other.armor){}


    // SECTION: OPERATORS---------------------------------------------------------------------------------
    /*! Assignment operator for the Monster class*/
    Monster& operator=(const Monster& other){
        if(this != &other){
            this->strength = other.strength;
            this->mana = other.mana;
            this->health = other.health;
            this->armor = other.armor;
        }
        return *this;
    };

    friend ostream& operator<<(ostream& os, Monster& cl);
    friend istream& operator>>(std::istream& in,  Monster& cl);


    //SECTION: GETTERS AND SETTERS------------------------------------------------------------------------



    float getStrength() const {
        return strength;
    }

    void setStrength(float newStrength) {
        Monster::strength = newStrength;
    }

    float getMana() const {
        return mana;
    }

    void setMana(float newMana) {
        Monster::mana = newMana;
    }

    float getHealth() const {
        return health;
    }

    void setHealth(float newHealth) {
        Monster::health = newHealth;
    }

    const Armor &getArmor() const {
        return armor;
    }

    void setArmor(const Armor &newArmor) {
        Monster::armor = newArmor;
    }

};

/*! Outputs information about monster to ostream*/
ostream& operator<<(ostream& os, Monster& cl){
    os<<"Monster: "<<endl;

    os<<"strength: "<<cl.strength << " | mana: " << cl.mana << " | health: " << cl.health << endl;
    os<<"Armor: " << cl.armor << endl;
    return os;
}

/*! Inputs info about Monster in format:
 *      - strength
 *      - mana
 *      - health
 *      - Armor:
 *          - name
 *          - description
 *          - percent
 */
std::istream& operator >> (std::istream& in, Monster& cl){
    in>>cl.strength;
    in>>cl.mana;
    in>>cl.health;

    // Skip line
    char next;
    while(in.get(next)) if (next == '\n')  break;

    in>>cl.armor;

    return in;
}