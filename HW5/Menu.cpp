#include <Menu.h>
#include <iostream>


Menu::Menu() {
    this->menuItems = std::vector<std::shared_ptr<MenuItem>>();
    this->overallTasteBalance = TasteBalance();
    this->totalCost = 0;
}

Menu::Menu(std::vector<std::shared_ptr<MenuItem>> menuItems) {
    this->menuItems = menuItems;
    updateTasteBalanceAndCost();
}

TasteBalance Menu::getOverallTasteBalance() {
    return this->overallTasteBalance;
}

double Menu::getTotalCost() {
    return this->totalCost;
}

std::vector<std::shared_ptr<MenuItem>> Menu::getMenuItems() {
    return this->menuItems;
}

void Menu::setMenuItems(std::vector<std::shared_ptr<MenuItem>> menuItems) {
    this->menuItems = menuItems;
    updateTasteBalanceAndCost();
}

void Menu::addMenuItem(std::shared_ptr<MenuItem> menuItem) {
    if(menuItem == nullptr) {
        std::cout << "Menu item is null" << std::endl;
        return;
    }
    for(const auto& item : this->menuItems) {
        if(item->getName() == menuItem->getName()) {
            std::cout << "Menu item already exists" << std::endl;
            return;
        }
    }
    this->menuItems.push_back(menuItem);
    updateTasteBalanceAndCost();
}

void Menu::removeMenuItem(std::string name) {
    for(unsigned int i = 0; i < this->menuItems.size(); i++) {
        if(this->menuItems[i]->getName() == name) {
            this->menuItems.erase(this->menuItems.begin() + i);
            updateTasteBalanceAndCost();
            return;
        }
    }
    std::cout << "Menu item does not exist" << std::endl;
}

void Menu::updateTasteBalanceAndCost() {
    this->totalCost = 0;
    double sweet,sour,bitter,salty,savory;
    for(const auto& menuItem : menuItems) {
        sweet += menuItem->getTasteBalance().sweet;
        sour += menuItem->getTasteBalance().sour;
        bitter += menuItem->getTasteBalance().bitter;
        salty += menuItem->getTasteBalance().salty;
        savory += menuItem->getTasteBalance().savory;
        this->totalCost += menuItem->getPrice();
    }
    int size = menuItems.size();
    this->overallTasteBalance = TasteBalance(sweet/size, sour/size, bitter/size, salty/size, savory/size);
}

void Menu::printMenu(){
    if (this->menuItems.size() == 0) {
        std::cout << "Menu is empty" << std::endl;
        return;
    }
    std::cout << "Menu items: " << std::endl;
    for(const auto& menuItem : this->menuItems) {
        std::cout << menuItem->getName() << " - " << menuItem->getPrice() << std::endl;
    }
    std::cout << "Overall taste balance: " << std::endl;
    std::cout << "Sweet: " << this->overallTasteBalance.sweet << std::endl;
    std::cout << "Sour: " << this->overallTasteBalance.sour << std::endl;
    std::cout << "Bitter: " << this->overallTasteBalance.bitter << std::endl;
    std::cout << "Salty: " << this->overallTasteBalance.salty << std::endl;
    std::cout << "Savory: " << this->overallTasteBalance.savory << std::endl;
    std::cout << "Total cost: " << this->totalCost << std::endl;
}