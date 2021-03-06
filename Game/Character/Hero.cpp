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

    // SECTION: HELPER FUNCTIONS-------------------------------------------------------------------------

    /*! Saves the human in this format:
     *      - Race
     *      - strength
     *      - mana
     *      - health
     *      - weapon
     *      - armor
     *      - spell
     */
    void save(ostream& os){
        switch (race) {
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
        os<<endl<<strength<<endl;
        os<<mana<<endl;
        os<<health<<endl;
        weapon.save(os);
        armor.save(os);
        spell.save(os);
    }

    //! This method is used to clear the items of the hero
    void clear(){
        weapon.clear();
        armor.clear();
        spell.clear();
    }


    /*! Reduces the damage to the player by the armor percent and then deals the remaining damage*/
    void dealDamage(float damage){
        // Reduce damage by armor
        damage = armor.effect(damage);
        health -= damage;
    }

    /*! Applies the effect of the weapon to the strength of the player*/
    float useAttack(){
        return weapon.effect(strength);
    }

    /*! Applies the effect of the spell to the mana of the player*/
    float useSpell(){
        return spell.effect(mana);
    }

    // SECTION: CONSTRUCTORS------------------------------------------------------------------------------

    /*! Default constructor creates a Hero with race Human and no items*/
    Hero(): Hero(Race::Human){}

    /*! Constructor for hero gives default items and stats according to the race*/
    explicit Hero(Race race){
        this-> race = race;
        switch (race) {
            case Human:
                strength = 30;
                mana = 20;
                health = 50;
                break;
            case Mage:
                strength = 10;
                mana = 40;
                health = 50;
                break;
            case Warrior:
                strength = 40;
                mana = 10;
                health = 50;
                break;
        }
        weapon = Weapon("Basic Sword", "This is a basic steel sword", 20, WeaponType);
        armor = Armor();
        spell = Spell("Fire Ball", "The fireball is the default spell of the player", 20, SpellType);
    }

    Hero(Race race, float strength, float mana, float health, const Weapon& weapon, const Armor& armor, const Spell& spell){
        this->race = race;
        this->strength = strength;
        this->mana = mana;
        this->health = health;
        this->weapon = weapon;
        this->armor = armor;
        this->spell = spell;
    }

    Hero(const Hero &other) : Hero(other.race, other.strength, other.mana, other.health, other.weapon, other.armor, other.spell){}


    // SECTION: OPERATORS---------------------------------------------------------------------------------

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
    friend std::istream& operator >> (std::istream& in,  Hero& cl);


    // SECTION: GETTERS AND SETTERS

    Race getRace() const {
        return race;
    }

    void setRace(Race newRace) {
        Hero::race = newRace;
    }

    float getStrength() const {
        return strength;
    }

    void setStrength(float newStrength) {
        Hero::strength = newStrength;
    }

    float getMana() const {
        return mana;
    }

    void setMana(float newMana) {
        Hero::mana = newMana;
    }

    float getHealth() const {
        return health;
    }

    void setHealth(float newHealth) {
        Hero::health = newHealth;
    }

    const Weapon &getWeapon() const {
        return weapon;
    }

    void setWeapon(const Weapon &newWeapon) {
        Hero::weapon = newWeapon;
    }


    const Armor &getArmor() const {
        return armor;
    }

    void setArmor(const Armor &newArmor) {
        Hero::armor = newArmor;
    }

    const Spell &getSpell() const {
        return spell;
    }

    void setSpell(const Spell &newSpell) {
        Hero::spell = newSpell;
    }


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

/* This accepts input from istream in format:
 *      - Race
 *      - strength
 *      - mana
 *      - health
 *      - Weapon
 *      - Armor
 *      - Spell
 */
std::istream& operator >> (std::istream& in, Hero& cl){
    string race;

    getline(in, race);

    if(race == "Human") cl.race = Human;
    else if(race == "Mage") cl.race = Mage;
    else if(race == "Warrior") cl.race = Warrior;
    else throw std::invalid_argument( "File does not provide a valid race for the player" );

    in>>cl.strength;
    in>>cl.mana;
    in>>cl.health;

    // Skip line
    char next;
    while(in.get(next)) if (next == '\n')  break;
    in>>cl.weapon;
    while(in.get(next)) if (next == '\n')  break;
    in>>cl.armor;
    while(in.get(next)) if (next == '\n')  break;
    in>>cl.spell;

    return in;
}
