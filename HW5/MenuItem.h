#ifndef MENUITEM_H
#define MENUITEM_H
#include <string>
#include <TasteBalance.h>

class MenuItem
{
private:
    std::string name;
    double price;
    TasteBalance tasteBalance;  
public:
    MenuItem();
    MenuItem(std::string name, double price, TasteBalance tasteBalance);
  
    std::string getName();
    double getPrice();
    TasteBalance getTasteBalance();
    void setName(std::string name);
    void setPrice(double price);
    void setTasteBalance(TasteBalance tasteBalance);
    virtual void print();
};

#endif
