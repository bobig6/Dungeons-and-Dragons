#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

/*! This is a common class for all the items*/
class Item{
protected:
     /*! The name of the item. Its common for all items*/
     string name;
     /*! Description of the item*/
     string description;
     /*! The percent of the effect that it does.*/
     float percent;
public:

    /*! This is the default effect function. Its virtual and it is supposed to be overrode. By default returns the object that is given */
    virtual float effect(float obj){
        cout<<"Default effect called. No change was made"<<endl;
        return obj;
    }

    void save(ostream& os){
        os<<name<<endl;
        os<<description<<endl;
        os<<percent<<endl;
    }

    void clear(){
        name.clear();
        description.clear();
    }

    // SECTION: CONSTRUCTORS---------------------------------------------------------------------------------------------
    Item(){
        name = "Default item";
        description = "This is the default item.";
        percent = 0;
    }

    /*! Constructor for the Item object*/
    Item(const string &name, const string &description, float percent) :percent(percent) {
        this->name = name;
        this->description = description;
    }

    Item(const Item& other) : Item(other.name, other.description, other.percent){}

    Item& operator=(const Item& other){
        if(this != &other){
            this->name = other.name;
            this->description = other.description;
            this->percent = other.percent;
        }
        return *this;
    };


    // SECTION: GETTERS AND SETTERS--------------------------------------------------------------------------------------
    const string &getName() const {
        return name;
    }

    void setName(const string &newName) {
        Item::name = newName;
    }

    const string &getDescription() const {
        return description;
    }

    void setDescription(const string &newDescription) {
        Item::description = newDescription;
    }

    float getPercent() const {
        return percent;
    }

    void setPercent(float newPercent) {
        Item::percent = newPercent;
    }

    string getPercentAsString(){
        string str = to_string(percent);
        // Find the decimal point;
        int i = 0;
        while (i < str.size()) {
            i++;
            if (str[i] == '.') break;
        }

        // Remove everything that is 2 symbols after the decimal point;
        if(i < str.size() - 3 ){
            i += 3;
        }
        str.erase(i, str.size()-1);
        return str;
    }

    /*! Returns the Item as string in format: Name: {Name} | {Description} | Effect: {Percent}%  */
    string getAsString(){
        return "Name: " + name + " | " + description + " | Effect: " + getPercentAsString() + "%";
    }

    // SECTION: OPERATORS------------------------------------------------------------------------------


    bool operator==(const Item &rhs) const {
        return name == rhs.name &&
               description == rhs.description &&
               percent == rhs.percent;
    }

    bool operator!=(const Item &rhs) const {
        return !(rhs == *this);
    }


    /*! Compares two items by their percent of effect*/
    bool operator<(const Item &rhs) const {
        return percent < rhs.percent;
    }

    /*! Compares two items by their percent of effect*/
    bool operator>(const Item &rhs) const {
        return rhs < *this;
    }

    /*! Compares two items by their percent of effect*/
    bool operator<=(const Item &rhs) const {
        return !(rhs < *this);
    }

    /*! Compares two items by their percent of effect*/
    bool operator>=(const Item &rhs) const {
        return !(*this < rhs);
    }

    friend ostream& operator<<(ostream& os, Item& item);
    friend istream& operator>> (istream& is, Item& item);


};

ostream& operator<<(ostream& os, Item& item)
{
    os << item.getAsString();
    return os;
}

istream& operator>> (istream& is, Item& item)
{
    getline(is, item.name);
    getline(is, item.description);
    is >> item.percent;

    return is;
}
