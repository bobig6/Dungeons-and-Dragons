
/*! This class holds information about the spell of the player. It can be used to increase the
 * strength of the next  attack by a certain percent*/
class Spell : public Item{
public:
    /*! Indicates when the spell is activated*/
    bool isActivated = false;
    /*! Holds the number by which the attack increases, so later it can be decreased*/
    float effectBoost = 0;

    /*! Constructor with name, description and percent */
    Spell(const string &name, const string &description, float percent) : Item(name, description, percent) {}

    /*! Default constructor. Creates empty object */
    Spell() : Item(){}

    /*! Copy constructor*/
    Spell(const Spell &other) : Item(other.name, other.description, other.percent) {}


    /*! Adds percent to the attack that is given*/
    float effect(float obj) override{
        effectBoost = (percent/100)*obj;
        isActivated = true;
        obj = obj + effectBoost;
        return obj;
    }

    /*! Deactivates the effect of the spell and returns the attack to default value*/
    float deactivate(float obj){
        isActivated = false;
        obj = obj - effectBoost;
        effectBoost = 0;
        return obj;
    }
};
