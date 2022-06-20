
/*! This class holds information for the armor of the player. It decreases the damage
 * dealt to the player by a certain percent*/
class Armor : public Item{
public:

    /*! Constructor with name, description and percent */
    Armor(const string &name, const string &description, float percent, ItemType type) : Item(name, description, percent, type) {}

    /*! Default constructor. Creates empty object */
    Armor() : Item(ItemType::ArmorType){}

    /*! Copy constructor*/
    explicit Armor(const Item &other) : Item(other.name, other.description, other.percent, other.type) {}

    /*! Decreases the damage dealt and returns the new damage */
    float effect(float obj) override{
        obj = obj - (percent/100)*obj;
        return obj;
    }
};
