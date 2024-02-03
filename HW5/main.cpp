#include <Interface.h>

using json = nlohmann::json;

int main(int argc, char const *argv[])
{
    std::vector<std::shared_ptr<MenuItem>> availableMenuItems;
    try {
        availableMenuItems = Interface::getItemsFromJson("menu.json");
    }
    catch (const std::exception& e) {
        std::cout << "Cant parse JSON. Error: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "Welcome to the menu program!" << std::endl;
    std::cout << "Please enter your first name: ";
    std::string firstName;
    std::cin >> firstName;
    std::cout << "Please enter your last name: ";
    std::string lastName;
    std::cin >> lastName;
    std::cout << "Please select your gender to address you by: \n1. MR\n2.MRS" << std::endl;
    int choice;
    bool genderToAddress;
    std::cin >> choice;
    if (choice == 1) genderToAddress = User::Gender::MR;
    else if (choice == 2) genderToAddress = User::Gender::MRS;
    else std::cout << "Invalid input. Default value (Mr) assigned" << std::endl;
    User user(firstName, lastName, genderToAddress, std::shared_ptr<Menu>(new Menu()));
    sleep(0.5);

    while(true){
        system("clear");
        std::cout << "Welcome "   << (user.getGenderToAddress()==User::Gender::MR ? "MR " : "MRS ") << user.getFirstName() << " " << user.getLastName() << std::endl;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. Add item to menu" << std::endl;
        std::cout << "2. Remove item from menu" << std::endl;
        std::cout << "3. Modify menu item price" << std::endl;
        std::cout << "4. Print full menu" << std::endl;
        std::cout << "5. Get Menu Item Suggestion" << std::endl;
        std::cout << "6. Get full menu suggestion" << std::endl;
        std::cout << "7. Exit" << std::endl;

        int choice;
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Which item would you like to add?" << std::endl;
            int index = 1;
            for(const auto& item : availableMenuItems) {
                std::cout << index << ". " << item->getName() << " - " << item->getPrice() << std::endl;
                index++;
            }
            std::cin >> choice;
            user.getMenu()->addMenuItem(availableMenuItems[choice - 1]);
            std::cout << "Item added" << std::endl;
            std::cout << "Press enter to continue" << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
        else if (choice == 2) {
            std::cout << "Which item would you like to remove?" << std::endl;
            int index = 1;
            for(const auto& item : user.getMenu()->getMenuItems()){
                std::cout << index << ". " << item->getName() << " - " << item->getPrice() << std::endl;
                index++;
            }
            std::cin >> choice;
            user.getMenu()->removeMenuItem(user.getMenu()->getMenuItems()[choice - 1]->getName());
            std::cout << "Item removed" << std::endl;
        }
        else if (choice == 3) {
            std::cout << "Which item would you like to modify?" << std::endl;
            int index = 1;
            for(const auto& item : user.getMenu()->getMenuItems()){
                std::cout << index << ". " << item->getName() << " - " << item->getPrice() << std::endl;
                index++;
            }
            std::cin >> choice;
            std::cout << "What would you like to change the price to?" << std::endl;
            double price;
            std::cin >> price;
            user.getMenu()->getMenuItems()[choice - 1]->setPrice(price);
            user.getMenu()->updateTasteBalanceAndCost();
            std::cout << "Price changed to " << price << std::endl;
        }
        else if (choice == 4) {
            system("clear");
            user.getMenu()->printMenu(); 
            std::cout << "Press enter to continue" << std::endl;
            std::cin.ignore();
            std::cin.get();

        }
        else if (choice == 5) {
            std::cout << "Please enter your taste balance" << std::endl;
            std::cout << "Sweet: ";
            int sweet;
            std::cin >> sweet;
            std::cout << "Sour: ";
            int sour;
            std::cin >> sour;
            std::cout << "Bitter: ";
            int bitter;
            std::cin >> bitter;
            std::cout << "Salty: ";
            int salty;
            std::cin >> salty;
            std::cout << "Savory: ";
            int savory;
            std::cin >> savory;
            TasteBalance tasteBalance(sweet, sour, bitter, salty, savory);
            std::shared_ptr<MenuItem> menuItem = Interface::suggestMenuItem(availableMenuItems, tasteBalance);
            std::cout << "We suggest: " << menuItem->getName() << std::endl;
            std::cout << "Would you like to add this item to your menu? (y/n)" << std::endl;
            char choice;
            std::cin >> choice;
            if (choice == 'y') {
                user.getMenu()->addMenuItem(menuItem);
                std::cout << "Item added" << std::endl;
            }
            else if (choice == 'n') {
                std::cout << "Item not added" << std::endl;
            }
            else {
                std::cout << "Invalid input. Item not added" << std::endl;
            }
            std::cout << "Press enter to continue" << std::endl;
            std::cin.ignore();
            std::cin.get();

        }
        else if(choice == 6) {
            std::cout << "Please enter your taste balance" << std::endl;
            std::cout << "Sweet: ";
            int sweet;
            std::cin >> sweet;
            std::cout << "Sour: ";
            int sour;
            std::cin >> sour;
            std::cout << "Bitter: ";
            int bitter;
            std::cin >> bitter;
            std::cout << "Salty: ";
            int salty;
            std::cin >> salty;
            std::cout << "Savory: ";
            int savory;
            std::cin >> savory;
            TasteBalance tasteBalance(sweet, sour, bitter, salty, savory);
            Menu suggestedMenu = Interface::suggestFullMenu(availableMenuItems, tasteBalance);
            std::cout << "We suggest: " << std::endl;
            suggestedMenu.printMenu();
            std::cout << "Would you like to add this menu to your menu? (y/n)" << std::endl;
            char choice;
            std::cin >> choice;
            if (choice == 'y') {
                user.setMenu(std::shared_ptr<Menu>(new Menu(suggestedMenu.getMenuItems())));
                std::cout << "Menu added" << std::endl;
            }
            else if (choice == 'n') {
                std::cout << "Menu not added" << std::endl;
            }
            else {
                std::cout << "Invalid input. Menu not added" << std::endl;
            }
            std::cout << "Press enter to continue" << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
        else if (choice == 7) {
            std::cout << "Goodbye!" << std::endl;
            return 0;
        }
        else {
            std::cout << "Invalid input please try again" << std::endl;
            sleep(1);
        }

    }

  return 0;
}
