
/*! This class holds information about the spell of the player. It can be used to increase the
 * strength of the next  attack by a certain percent*/
class Spell : public Item{
public:

    /*! Constructor with name, description and percent */
    Spell(const string &name, const string &description, float percent, ItemType type) : Item(name, description, percent, type) {}

    /*! Default constructor. Creates empty object */
    Spell() : Item(ItemType::SpellType){}

    /*! Copy constructor*/
    explicit Spell(const Item &other) : Item(other.name, other.description, other.percent, other.type) {}


    /*! Adds percent to the mana that is given. My idea is that if you use the spell the attack of the mana gets increased by the percent
     * of the spell. So if you are a mage and your mana is bigger it will be more efficient to use the spell. */
    float effect(float obj) override{
        return obj + (percent/100)*obj;
    }

};
