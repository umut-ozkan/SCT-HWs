#include <Dessert.h>
#include <iostream>

Dessert::Dessert() : MenuItem() {
    extraChocolate = false; // default value
};

Dessert::Dessert(std::string name, int price, TasteBalance tasteBalance, bool extraChocolate) : MenuItem(name, price, tasteBalance) {
    this->extraChocolate = extraChocolate;
    if(extraChocolate){
        this->setPrice(this->getPrice() + 1.5);
    }
};

bool Dessert::getExtraChocolate() {
    return extraChocolate;
};

void Dessert::setExtraChocolate(bool extraChocolate) {
    if(extraChocolate && this->extraChocolate == false){
        this->setPrice(this->getPrice() + 1.5);
    }
    else if(this->extraChocolate && extraChocolate == false){
        this->setPrice(this->getPrice() - 1.5);
    }
    this->extraChocolate = extraChocolate;
};

void Dessert::print() {
    MenuItem::print();
    std::cout << "Extra Chocolate: " << extraChocolate << std::endl;
};
