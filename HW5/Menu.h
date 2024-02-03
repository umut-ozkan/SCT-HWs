#ifndef MENU_H
#define MENU_H
#include <vector>
#include <MenuItem.h>
#include <TasteBalance.h>
#include <memory>

class Menu {
  private:
    std::vector<std::shared_ptr<MenuItem>> menuItems;
    TasteBalance overallTasteBalance;
    double totalCost;
  public:
    Menu();
    Menu(std::vector<std::shared_ptr<MenuItem>> menuItems);
    void updateTasteBalanceAndCost();
    std::vector<std::shared_ptr<MenuItem>> getMenuItems();
    void addMenuItem(std::shared_ptr<MenuItem> menuItem);
    void removeMenuItem(std::string name);
    TasteBalance getOverallTasteBalance();
    double getTotalCost();
    void setMenuItems(std::vector<std::shared_ptr<MenuItem>> menuItems);
    void printMenu();
};
#endif