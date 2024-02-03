#ifndef DESSERT_H
#define DESSERT_H
#include <MenuItem.h>

class Dessert : public MenuItem
{
private:
    bool extraChocolate;
public:
    Dessert();
    Dessert(std::string name, int price, TasteBalance tasteBalance, bool extraChocolate=0);
    bool getExtraChocolate();
    void setExtraChocolate(bool extraChocolate);
    void print();
};

#endif