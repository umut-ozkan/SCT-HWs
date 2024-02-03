#include <User.h>
#include <iostream>
#include <string>

User::User() {
    this->firstName = "";
    this->lastName = "";
    this->genderToAddress = false;
    this->menu = std::shared_ptr<Menu>(new Menu());
}


User::User(std::string firstName, std::string lastName, bool genderToAddress = Gender::MR, std::shared_ptr<Menu> menu = std::shared_ptr<Menu>(new Menu())) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->genderToAddress = genderToAddress;
    this->menu = menu;
}

std::string User::getFirstName() {
    return this->firstName;
}

std::string User::getLastName() {
    return this->lastName;
}

bool User::getGenderToAddress() {
    return this->genderToAddress;
}

std::shared_ptr<Menu> User::getMenu() {
    return this->menu;
}

void User::setFirstName(std::string firstName) {
    this->firstName = firstName;
}

void User::setLastName(std::string lastName) {
    this->lastName = lastName;
}

void User::setGenderToAddress(bool genderToAddress) {
    this->genderToAddress = genderToAddress;
}

void User::setMenu(std::shared_ptr<Menu> menu) {
    this->menu = menu;
}
