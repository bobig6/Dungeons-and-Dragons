#include "Race.cpp"
#include "../Items/Weapon.cpp"
#include "../Items/Armor.cpp"
#include "../Items/Spell.cpp"


class Hero{
    Race race;
    float strength;
    float mana;
    float health;

    Weapon weapon;
    Armor armor;
    Spell spell;

public:

    /*! Default constructor creates a Hero with race Human and no items*/
    Hero(){
        race = Race::Human;
        strength = 30;
        mana = 20;
        health = 50;
        weapon = Weapon();
        armor = Armor();
        spell = Spell();
    }

    /*! Assignment operator for the Hero class*/
    Hero& operator=(const Hero& other){
        if(this != &other){
            this->race = other.race;
            this->strength = other.strength;
            this->mana = other.mana;
            this->health = other.health;
            this->weapon = other.weapon;
            this->armor = other.armor;
            this->spell = other.spell;
        }
        return *this;
    };

    friend ostream& operator<<(ostream& os, Hero& hero);
};

ostream& operator<<(ostream& os, Hero& hero)
{
    os<<"Hero(";

    switch (hero.race) {
        case Human:
            os<<"Human";
            break;
        case Mage:
            os<<"Mage";
            break;
        case Warrior:
            os<<"Warrior";
            break;
    }

    os<<"):"<<endl;
    os<<"strength: "<<hero.strength << " | mana: " << hero.mana << " | health: " << hero.health << endl;
    os<<"Weapon: " << hero.weapon << endl;
    os<<"Armor: " << hero.armor << endl;
    os<<"Spell: " << hero.spell << endl;

    return os;
}
