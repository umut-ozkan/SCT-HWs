#include <Starter.h>
#include <iostream>

Starter::Starter() : MenuItem() {
    isHot = false; // default value
};

Starter::Starter(std::string name, int price, TasteBalance tasteBalance, bool isHot) : MenuItem(name, price, tasteBalance) {
    this->isHot = isHot;
};

bool Starter::getIsHot() {
    return isHot;
};

void Starter::setIsHot(bool isHot) {
    this->isHot = isHot;
};

void Starter::print() {
    MenuItem::print();
    std::cout << "Is Hot: " << isHot << std::endl;
};