#include "Item.cpp"

/*! This class holds the information for the weapon of the player. It increases the attack
 * by certain percent */
class Weapon : public Item{
public:
    /*! Constructor with name, description and percent */
    Weapon(const string &name, const string &description, float percent, ItemType type) : Item(name, description, percent, type) {}

    /*! Default constructor. Creates empty object */
    Weapon() : Item(ItemType::WeaponType) {}

    /*! Copy constructor*/
    explicit Weapon(const Item &other) : Item(other.name, other.description, other.percent, other.type){}

    /*! This function increases the attack of the hero by certain percent. The idea is that if the player choses to use attack,
     * the damage dealt is strength + (weaponPercent)*strength. That way if the player is a warrior his strength will be bigger and
     * it will make more sense to use his attack*/
    float effect(float obj) override{
        obj = obj + (percent/100)*obj;
        return obj;
    }
};
