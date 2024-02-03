#include <MainCourse.h>
#include <iostream>

MainCourse::MainCourse() : MenuItem() {
    isVegetarian = false; // default value
};

MainCourse::MainCourse(std::string name, int price, TasteBalance tasteBalance, bool isVegetarian) : MenuItem(name, price, tasteBalance) {
    this->isVegetarian = isVegetarian;
};

bool MainCourse::getIsVegetarian() {
    return isVegetarian;
};

void MainCourse::setIsVegetarian(bool isVegetarian) {
    this->isVegetarian = isVegetarian;
};

void MainCourse::print() {
    MenuItem::print();
    std::cout << "Is Vegetarian: " << isVegetarian << std::endl;
};