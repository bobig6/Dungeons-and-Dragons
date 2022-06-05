#include "Item.cpp"

/*! This class holds the information for the weapon of the player. It increases the attack
 * by certain percent */
class Weapon : public Item{
public:
    /*! Constructor with name, description and percent */
    Weapon(const string &name, const string &description, float percent) : Item(name, description, percent) {}

    /*! Default constructor. Creates empty object */
    Weapon() : Item() {}

    /*! Copy constructor*/
    Weapon(const Weapon &other) : Item(other.name, other.description, other.percent){}

    /*! This function increases the attack of the hero by certain percent*/
    float effect(float obj) override{
        obj = obj + (percent/100)*obj;
        return obj;
    }
};
