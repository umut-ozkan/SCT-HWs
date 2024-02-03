#include <TasteBalance.h>

TasteBalance::TasteBalance(int sweet, int sour, int bitter, int salty, int savory){
    this->sweet = sweet;
    this->sour = sour;
    this->bitter = bitter;
    this->salty = salty;
    this->savory = savory;
}

TasteBalance::TasteBalance(){
    this->sweet = 0;
    this->sour = 0;
    this->bitter = 0;
    this->salty = 0;
    this->savory = 0;
}