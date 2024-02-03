#ifndef MAINCOURSE_H
#define MAINCOURSE_H
#include <MenuItem.h>

class MainCourse : public MenuItem
{
private:
    bool isVegetarian;
public:
    MainCourse();
    MainCourse(std::string name, int price, TasteBalance tasteBalance, bool isVegetarian=0);
    bool getIsVegetarian();
    void setIsVegetarian(bool isVegetarian);
    void print();
};

#endif