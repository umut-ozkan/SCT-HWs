#ifndef SALAD_H
#define SALAD_H
#include <MenuItem.h>
class Salad : public MenuItem
{
private:
    int noOfExtraIngredients;
public:
    Salad();
    Salad(std::string name, int price, TasteBalance tasteBalance, int noOfExtraIngredients=0);
    int getNoOfExtraIngredients();
    void setNoOfExtraIngredients(int noOfExtraIngredients);
    void print();
};





#endif