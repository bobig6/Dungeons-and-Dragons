
/*! This class holds information for the armor of the player. It decreases the damage
 * dealt to the player by a certain percent*/
class Armor : public Item{
public:

    /*! Constructor with name, description and percent */
    Armor(const string &name, const string &description, float percent) : Item(name, description, percent) {}

    /*! Default constructor. Creates empty object */
    Armor() : Item(){}

    /*! Copy constructor*/
    Armor(const Armor &other) : Item(other.name, other.description, other.percent) {}

    /*! Decreases the damage dealt and returns the new damage */
    float effect(float obj) override{
        obj = obj - (percent/100)*obj;
        return obj;
    }
};
