#include <iostream>
#include <MenuItem.h>
#include <TasteBalance.h>

MenuItem::MenuItem() {
    name = "";
    price = 0;
    tasteBalance = TasteBalance();
};

MenuItem::MenuItem(std::string name, double price, TasteBalance tasteBalance) {
    this->name = name;
    this->price = price;
    this->tasteBalance = tasteBalance;
};

std::string MenuItem::getName() {
    return name;
};

double MenuItem::getPrice() {
    return price;
};

TasteBalance MenuItem::getTasteBalance() {
    return tasteBalance;
};

void MenuItem::setName(std::string name) {
    this->name = name;
};

void MenuItem::setPrice(double price) {
    this->price = price;
};

void MenuItem::setTasteBalance(TasteBalance tasteBalance) {
    this->tasteBalance = tasteBalance;
};

void MenuItem::print() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Price: " << price << std::endl;
    std::cout << "Taste Balance: " << std::endl;
    std::cout << "Sweet: " << tasteBalance.sweet << std::endl;
    std::cout << "Sour: " << tasteBalance.sour << std::endl;
    std::cout << "Bitter: " << tasteBalance.bitter << std::endl;
    std::cout << "Salty: " << tasteBalance.salty << std::endl;
    std::cout << "Savory: " << tasteBalance.savory << std::endl;
};
