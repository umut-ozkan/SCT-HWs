#ifndef DRINK_H
#define DRINK_H
#include <MenuItem.h>

class Drink : public MenuItem
{
private:
    bool isCarbonated;
    int noOfAdditionalAlcoholicShots;
public:
    Drink();
    Drink(std::string name, int price, TasteBalance tasteBalance, bool isCarbonated=0, int noOfAdditionalAlcoholicShots=0);
    bool getIsCarbonated();
    int getNoOfAdditionalAlcoholicShots();
    void setIsCarbonated(bool isCarbonated);
    void setNoOfAdditionalAlcoholicShots(int noOfAdditionalAlcoholicShots);
    void print();
};

#endif