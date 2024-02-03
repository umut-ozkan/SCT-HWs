#ifndef USER_H
#define USER_H

#include <Menu.h>
#include <string>
#include <memory>

class User
{
private:
    std::string firstName;
    std::string lastName;
    bool genderToAddress;
    std::shared_ptr<Menu> menu;
public:
    enum Gender {MR, MRS};
    User();
    User(std::string firstName, std::string lastName, bool genderToAddress, std::shared_ptr<Menu> menu);
    std::string getFirstName();
    std::string getLastName();
    bool getGenderToAddress();
    std::shared_ptr<Menu> getMenu();
    void setFirstName(std::string firstName);
    void setLastName(std::string lastName);
    void setGenderToAddress(bool genderToAddress);
    void setMenu(std::shared_ptr<Menu> menu);
};
#endif