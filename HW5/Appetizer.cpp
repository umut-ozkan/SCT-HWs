#include <Appetizer.h>
#include <iostream>

Appetizer::Appetizer() : MenuItem() {
    serveTime = Appetizer::ServeTime::BEFORE_MAIN_COURSE; // default value
};

Appetizer::Appetizer(std::string name, int price, TasteBalance tasteBalance, bool serveTime) : MenuItem(name, price, tasteBalance) {
    this->serveTime = serveTime ? Appetizer::ServeTime::BEFORE_MAIN_COURSE : Appetizer::ServeTime::AFTER_MAIN_COURSE;
};

bool Appetizer::getServeTime() {
    return serveTime;
};

void Appetizer::setServeTime(bool serveTime) {
    this->serveTime = serveTime;
};

void Appetizer::print() {
    MenuItem::print();
    std::cout << "Serve Time: " << (serveTime == Appetizer::ServeTime::BEFORE_MAIN_COURSE ? "Before Main Course" : "After Main Course") << std::endl;
};

