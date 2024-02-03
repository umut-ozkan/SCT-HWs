#include <Salad.h>
#include <iostream>

Salad::Salad() : MenuItem() {
    noOfExtraIngredients = 0; // default value
};

Salad::Salad(std::string name, int price, TasteBalance tasteBalance, int noOfExtraIngredients) : MenuItem(name, price, tasteBalance) {
    this->noOfExtraIngredients = noOfExtraIngredients;
    this->setPrice(this->getPrice() + (noOfExtraIngredients * 2.25));
};

int Salad::getNoOfExtraIngredients(){
    return noOfExtraIngredients;
};

void Salad::setNoOfExtraIngredients(int noOfExtraIngredients){
    int difference = noOfExtraIngredients - this->noOfExtraIngredients;
    this->noOfExtraIngredients = noOfExtraIngredients;
    this->setPrice(this->getPrice() + (difference * 2.25));
};

void Salad::print() {
    MenuItem::print();
    std::cout << "No of Extra Ingredients: " << noOfExtraIngredients << std::endl;
};
