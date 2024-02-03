#include <Drink.h>
#include <iostream>

Drink::Drink() : MenuItem() {
    isCarbonated = false; // default value
    noOfAdditionalAlcoholicShots = 0; // default value
};


Drink::Drink(std::string name, int price, TasteBalance tasteBalance, bool isCarbonated, int noOfAdditionalAlcoholicShots) : MenuItem(name, price, tasteBalance) {
    this->isCarbonated = isCarbonated;
    this->noOfAdditionalAlcoholicShots = noOfAdditionalAlcoholicShots;
    this->setPrice(this->getPrice() + (noOfAdditionalAlcoholicShots * 3.50));
    if(isCarbonated) {
        this->setPrice(this->getPrice() + 0.50);
    }
    this->setPrice(this->getPrice() + (noOfAdditionalAlcoholicShots * 2.50));
};

bool Drink::getIsCarbonated() {
    return isCarbonated;
};

int Drink::getNoOfAdditionalAlcoholicShots() {
    return noOfAdditionalAlcoholicShots;
};

void Drink::setIsCarbonated(bool isCarbonated) {
    this->isCarbonated = isCarbonated;
    if(isCarbonated) {
        this->setPrice(this->getPrice() + 0.50);
    }
};

void Drink::setNoOfAdditionalAlcoholicShots(int noOfAdditionalAlcoholicShots) {
    int difference = noOfAdditionalAlcoholicShots - this->noOfAdditionalAlcoholicShots;
    this->noOfAdditionalAlcoholicShots = noOfAdditionalAlcoholicShots;
    this->setPrice(this->getPrice() + (difference * 2.50));
    
};

void Drink::print(){
    MenuItem::print();
    std::cout << "Is Carbonated: " << isCarbonated << std::endl;
    std::cout << "Number of Additional Alcohol Shots: " << noOfAdditionalAlcoholicShots << std::endl;

}