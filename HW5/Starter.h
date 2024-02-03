#ifndef STARTER_H
#define Starter_H
#include <MenuItem.h>

class Starter : public MenuItem
{
private:
    bool isHot;
public:
    Starter();
    Starter(std::string name, int price, TasteBalance tasteBalance, bool isHot = false);
    bool getIsHot();
    void setIsHot(bool isHot);
    void print();
};

#endif