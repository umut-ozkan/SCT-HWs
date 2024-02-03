#ifndef APPETIZER_H
#define APPETIZER_H
#include <MenuItem.h>

class Appetizer : public MenuItem
{
private:
    bool serveTime;
public:
    enum ServeTime {BEFORE_MAIN_COURSE, AFTER_MAIN_COURSE};
    Appetizer();
    Appetizer(std::string name, int price, TasteBalance tasteBalance, bool serveTime=0);
    bool getServeTime();
    void setServeTime(bool serveTime);
    void print();
};

#endif