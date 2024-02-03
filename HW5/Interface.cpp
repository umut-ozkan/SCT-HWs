#include <Interface.h>


using json = nlohmann::json;
namespace Interface{
    std::vector<std::shared_ptr<MenuItem>> getItemsFromJson(const std::string& json_data) {
        std::ifstream f(json_data);
        json menu_data = json::parse(f);
        std::vector<std::shared_ptr<MenuItem>> menuItems;

        for (const std::string category : {"starters", "salads", "main_courses", "drinks", "appetizers", "desserts"}) {
            for (const auto& item : menu_data[category]) {
                json taste_balance = item["taste_balance"];
                int sweet = taste_balance["sweet"];
                int sour = taste_balance["sour"];
                int bitter = taste_balance["bitter"];
                int salty = taste_balance["salty"];
                int savory = taste_balance["savory"];
                TasteBalance tasteBalance(sweet, sour, bitter, salty, savory);
                if (category == "starters"){
                    std::shared_ptr<Starter> menuItem = std::make_shared<Starter>(item["name"], item["price"], tasteBalance);
                    menuItems.push_back(menuItem);
                }
                else if (category == "salads"){
                    std::shared_ptr<Salad> menuItem = std::make_shared<Salad>(item["name"], item["price"], tasteBalance);
                    menuItems.push_back(menuItem);
                }
                else if(category == "main_courses"){
                    std::shared_ptr<MainCourse> menuItem = std::make_shared<MainCourse>(item["name"], item["price"], tasteBalance);   
                    menuItems.push_back(menuItem);
                }
                else if(category == "drinks"){
                    std::shared_ptr<Drink> menuItem = std::make_shared<Drink>(item["name"], item["price"], tasteBalance);
                    menuItems.push_back(menuItem);
                }
                else if(category == "appetizers"){
                    std::shared_ptr<Appetizer> menuItem = std::make_shared<Appetizer>(item["name"], item["price"], tasteBalance);
                    menuItems.push_back(menuItem);
                }
                else if(category == "desserts"){
                    std::shared_ptr<Dessert> menuItem = std::make_shared<Dessert>(item["name"], item["price"], tasteBalance);
                    menuItems.push_back(menuItem);
                }
            }
        }
        return menuItems;
    }

    std::shared_ptr<MenuItem> suggestMenuItem(const std::vector<std::shared_ptr<MenuItem>>& menuItems, const TasteBalance& tasteBalance) {
        double minMSE = 99999999;
        std::shared_ptr<MenuItem> minMSEItem;
        for (const auto& item : menuItems) {
            double mse = pow(item->getTasteBalance().sweet - tasteBalance.sweet, 2) +
                        pow(item->getTasteBalance().sour - tasteBalance.sour, 2) +
                        pow(item->getTasteBalance().bitter - tasteBalance.bitter, 2) +
                        pow(item->getTasteBalance().salty - tasteBalance.salty, 2) +
                        pow(item->getTasteBalance().savory - tasteBalance.savory, 2);
            if (mse < minMSE) { 
                minMSE = mse;
                minMSEItem = item;
            }
        }
        return minMSEItem;
    }

    std::shared_ptr<MenuItem> suggestMenuItem(const std::vector<std::shared_ptr<MenuItem>>& menuItems, const TasteBalance& tasteBalance, const std::type_info& type) {
        double minMSE = 99999999;
        std::shared_ptr<MenuItem> minMSEItem = nullptr;
        for (const auto& item : menuItems) {
            double mse = pow(item->getTasteBalance().sweet - tasteBalance.sweet, 2) +
                        pow(item->getTasteBalance().sour - tasteBalance.sour, 2) +
                        pow(item->getTasteBalance().bitter - tasteBalance.bitter, 2) +
                        pow(item->getTasteBalance().salty - tasteBalance.salty, 2) +
                        pow(item->getTasteBalance().savory - tasteBalance.savory, 2);
            if (mse < minMSE && typeid(*item) == type) { 
                minMSE = mse;
                minMSEItem = item;
            }
        }
        return minMSEItem;
    }

    Menu suggestFullMenu(std::vector<std::shared_ptr<MenuItem>>& fullMenu, const TasteBalance& tasteBalance) {
        std::vector<std::shared_ptr<MenuItem>> saladsAvailable;
        std::vector<std::shared_ptr<MenuItem>> mainCoursesAvailable;
        std::vector<std::shared_ptr<MenuItem>> drinksAvailable;
        std::vector<std::shared_ptr<MenuItem>> appetizersAvailable;
        std::vector<std::shared_ptr<MenuItem>> dessertsAvailable;
        std::vector<std::shared_ptr<MenuItem>> startersAvailable;
        for (const auto& item : fullMenu) {
            if(typeid(*item) == typeid(Salad)) saladsAvailable.push_back(item);
            else if(typeid(*item) == typeid(MainCourse)) mainCoursesAvailable.push_back(item);
            else if(typeid(*item) == typeid(Drink)) drinksAvailable.push_back(item);
            else if(typeid(*item) == typeid(Appetizer)) appetizersAvailable.push_back(item);
            else if(typeid(*item) == typeid(Dessert)) dessertsAvailable.push_back(item);
            else if(typeid(*item) == typeid(Starter)) startersAvailable.push_back(item);
        }

        srand(time(0));
        std::shared_ptr<MenuItem> salad = saladsAvailable[rand() % saladsAvailable.size()];
        std::shared_ptr<MenuItem> mainCourse = mainCoursesAvailable[rand() % mainCoursesAvailable.size()];
        std::shared_ptr<MenuItem> drink = drinksAvailable[rand() % drinksAvailable.size()]; 
        std::shared_ptr<MenuItem> appetizer = appetizersAvailable[rand() % appetizersAvailable.size()];
        std::shared_ptr<MenuItem> dessert = dessertsAvailable[rand() % dessertsAvailable.size()];
        std::shared_ptr<MenuItem> starter = startersAvailable[rand() % startersAvailable.size()];
        std::vector<std::shared_ptr<MenuItem>> suggestedMenuItems = {salad, mainCourse, drink, appetizer, dessert, starter};
        double mse = 9999;
        double lastMse = mse;
        double ovrSweet, ovrSour, ovrBitter, ovrSalty, ovrSavory = 0;
        while (mse > 15){
            for(int i=0; i<6; i++){
                ovrSweet += suggestedMenuItems[i]->getTasteBalance().sweet;
                ovrSour += suggestedMenuItems[i]->getTasteBalance().sour;
                ovrBitter += suggestedMenuItems[i]->getTasteBalance().bitter;
                ovrSalty += suggestedMenuItems[i]->getTasteBalance().salty;
                ovrSavory += suggestedMenuItems[i]->getTasteBalance().savory;
            }
            TasteBalance ovrTasteBalance(ovrSweet/6, ovrSour/6, ovrBitter/6, ovrSalty/6, ovrSavory/6);
        
            double lowestMSE = mse;
            std::shared_ptr<MenuItem> lowestMSEItem;
            int lowestMSEIndex;
            for(int i=0; i<6; i++){
                double curOvrSweet, curOvrSour, curOvrBitter, curOvrSalty, curOvrSavory;
                curOvrSweet = 0;
                curOvrSour = 0;
                curOvrBitter = 0;
                curOvrSalty = 0;
                curOvrSavory = 0;
                for(int j=0; j<6; j++){
                    if(j!=i){
                        curOvrSweet += suggestedMenuItems[j]->getTasteBalance().sweet;
                        curOvrSour += suggestedMenuItems[j]->getTasteBalance().sour;
                        curOvrBitter += suggestedMenuItems[j]->getTasteBalance().bitter;
                        curOvrSalty += suggestedMenuItems[j]->getTasteBalance().salty;
                        curOvrSavory += suggestedMenuItems[j]->getTasteBalance().savory;
                    }
                }
                    double difSweet = tasteBalance.sweet*6 - curOvrSweet; 
                    double difSour = tasteBalance.sour*6 - curOvrSour;
                    double difBitter = tasteBalance.bitter*6 - curOvrBitter;
                    double difSalty = tasteBalance.salty*6 - curOvrSalty;
                    double difSavory = tasteBalance.savory*6 - curOvrSavory;
                    std::shared_ptr<MenuItem> suggested;
                    if(i == 0){
                        suggested = suggestMenuItem(saladsAvailable, TasteBalance(difSweet, difSour, difBitter, difSalty, difSavory), typeid(Salad));
                        TasteBalance newOvrTasteBalance = getOverallTasteBalance({suggested, mainCourse, drink, appetizer, dessert, starter});
                        double newMSE = pow(newOvrTasteBalance.sweet - tasteBalance.sweet, 2) +
                                        pow(newOvrTasteBalance.sour - tasteBalance.sour, 2) +
                                        pow(newOvrTasteBalance.bitter - tasteBalance.bitter, 2) +
                                        pow(newOvrTasteBalance.salty - tasteBalance.salty, 2) +
                                        pow(newOvrTasteBalance.savory - tasteBalance.savory, 2);
                        if(newMSE < lowestMSE){
                            lowestMSE = newMSE;
                            lowestMSEItem = suggested;
                            lowestMSEIndex = i;
                        }
                    }
                    if(i == 1){
                        suggested = suggestMenuItem(mainCoursesAvailable, TasteBalance(difSweet, difSour, difBitter, difSalty, difSavory), typeid(MainCourse));
                        TasteBalance newOvrTasteBalance = getOverallTasteBalance({salad, suggested, drink, appetizer, dessert, starter});
                        double newMSE = pow(newOvrTasteBalance.sweet - tasteBalance.sweet, 2) +
                                        pow(newOvrTasteBalance.sour - tasteBalance.sour, 2) +
                                        pow(newOvrTasteBalance.bitter - tasteBalance.bitter, 2) +
                                        pow(newOvrTasteBalance.salty - tasteBalance.salty, 2) +
                                        pow(newOvrTasteBalance.savory - tasteBalance.savory, 2);
                        if(newMSE < lowestMSE){
                            lowestMSE = newMSE;
                            lowestMSEItem = suggested;
                            lowestMSEIndex = i;
                        }
                    }
                    if(i == 2){
                        suggested = suggestMenuItem(drinksAvailable, TasteBalance(difSweet, difSour, difBitter, difSalty, difSavory), typeid(Drink));
                        TasteBalance newOvrTasteBalance = getOverallTasteBalance({salad, mainCourse, suggested, appetizer, dessert, starter});
                        double newMSE = pow(newOvrTasteBalance.sweet - tasteBalance.sweet, 2) +
                                        pow(newOvrTasteBalance.sour - tasteBalance.sour, 2) +
                                        pow(newOvrTasteBalance.bitter - tasteBalance.bitter, 2) +
                                        pow(newOvrTasteBalance.salty - tasteBalance.salty, 2) +
                                        pow(newOvrTasteBalance.savory - tasteBalance.savory, 2);
                        if(newMSE < lowestMSE){
                            lowestMSE = newMSE;
                            lowestMSEItem = suggested;
                            lowestMSEIndex = i;
                        }
                    }
                    if(i == 3){
                        suggested = suggestMenuItem(appetizersAvailable, TasteBalance(difSweet, difSour, difBitter, difSalty, difSavory), typeid(Appetizer));
                        TasteBalance newOvrTasteBalance = getOverallTasteBalance({salad, mainCourse, drink, suggested, dessert, starter});
                        double newMSE = pow(newOvrTasteBalance.sweet - tasteBalance.sweet, 2) +
                                        pow(newOvrTasteBalance.sour - tasteBalance.sour, 2) +
                                        pow(newOvrTasteBalance.bitter - tasteBalance.bitter, 2) +
                                        pow(newOvrTasteBalance.salty - tasteBalance.salty, 2) +
                                        pow(newOvrTasteBalance.savory - tasteBalance.savory, 2);
                        if(newMSE < lowestMSE){
                            lowestMSE = newMSE;
                            lowestMSEItem = suggested;
                            lowestMSEIndex = i;
                        }
                    }
                    if(i == 4){
                        suggested = suggestMenuItem(dessertsAvailable, TasteBalance(difSweet, difSour, difBitter, difSalty, difSavory), typeid(Dessert));
                        TasteBalance newOvrTasteBalance = getOverallTasteBalance({salad, mainCourse, drink, appetizer, suggested, starter});
                        double newMSE = pow(newOvrTasteBalance.sweet - tasteBalance.sweet, 2) +
                                        pow(newOvrTasteBalance.sour - tasteBalance.sour, 2) +
                                        pow(newOvrTasteBalance.bitter - tasteBalance.bitter, 2) +
                                        pow(newOvrTasteBalance.salty - tasteBalance.salty, 2) +
                                        pow(newOvrTasteBalance.savory - tasteBalance.savory, 2);
                        if(newMSE < lowestMSE){
                            lowestMSE = newMSE;
                            lowestMSEItem = suggested;
                            lowestMSEIndex = i;
                        }
                    }
                    if(i == 5){
                        suggested = suggestMenuItem(startersAvailable, TasteBalance(difSweet, difSour, difBitter, difSalty, difSavory), typeid(Starter));
                        TasteBalance newOvrTasteBalance = getOverallTasteBalance({salad, mainCourse, drink, appetizer, dessert, suggested});
                        double newMSE = pow(newOvrTasteBalance.sweet - tasteBalance.sweet, 2) +
                                        pow(newOvrTasteBalance.sour - tasteBalance.sour, 2) +
                                        pow(newOvrTasteBalance.bitter - tasteBalance.bitter, 2) +
                                        pow(newOvrTasteBalance.salty - tasteBalance.salty, 2) +
                                        pow(newOvrTasteBalance.savory - tasteBalance.savory, 2);
                        if(newMSE < lowestMSE){
                            lowestMSE = newMSE;
                            lowestMSEItem = suggested;
                            lowestMSEIndex = i;
                        }
                    }
            }
            if(lowestMSEItem == nullptr){
                break;
            }
            suggestedMenuItems[lowestMSEIndex] = lowestMSEItem;
            lastMse = mse;
            mse = lowestMSE;
            if(lastMse == mse){
                break;
            }
            
        }
        return Menu(suggestedMenuItems);
    }

    /*
    Menu suggestFullMenu(Menu fullMenu, const TasteBalance& tasteBalance) {
        double minMse = 99999999;
        std::vector<std::shared_ptr<MenuItem>> minMseMenu;
        std::vector<std::shared_ptr<MenuItem>> saladsAvailable;
        std::vector<std::shared_ptr<MenuItem>> mainCoursesAvailable;
        std::vector<std::shared_ptr<MenuItem>> drinksAvailable;
        std::vector<std::shared_ptr<MenuItem>> appetizersAvailable;
        std::vector<std::shared_ptr<MenuItem>> dessertsAvailable;
        std::vector<std::shared_ptr<MenuItem>> startersAvailable;
        for (const auto& item : fullMenu.getMenuItems()) {
            if(typeid(*item) == typeid(Salad)) saladsAvailable.push_back(item);
            else if(typeid(*item) == typeid(MainCourse)) mainCoursesAvailable.push_back(item);
            else if(typeid(*item) == typeid(Drink)) drinksAvailable.push_back(item);
            else if(typeid(*item) == typeid(Appetizer)) appetizersAvailable.push_back(item);
            else if(typeid(*item) == typeid(Dessert)) dessertsAvailable.push_back(item);
            else if(typeid(*item) == typeid(Starter)) startersAvailable.push_back(item);
        }
        for(std::shared_ptr<MenuItem> salad : saladsAvailable){
            for(std::shared_ptr<MenuItem> mainCourse : mainCoursesAvailable){
                for(std::shared_ptr<MenuItem> drink : drinksAvailable){
                    for(std::shared_ptr<MenuItem> appetizer : appetizersAvailable){
                        for(std::shared_ptr<MenuItem> dessert : dessertsAvailable){
                            for(std::shared_ptr<MenuItem> starter : startersAvailable){
                                std::vector<std::shared_ptr<MenuItem>> menuItems = {salad, mainCourse, drink, appetizer, dessert, starter};
                                double mse = calculateMse(menuItems, tasteBalance);
                                if(mse < minMse){
                                    minMse = mse;
                                    minMseMenu = menuItems;
                                }
                            }
                        }
                    }
                }
            }
        }
        std::cout << "MSE: " << minMse << std::endl;
        Menu menu(minMseMenu);
        menu.printMenu();
        return Menu(minMseMenu);
    }
    */
    double calculateMse(std::vector<std::shared_ptr<MenuItem>> menuItems, TasteBalance tasteBalance){
        double mse = 0;
        TasteBalance overall = getOverallTasteBalance(menuItems);
        mse += pow(overall.sweet - tasteBalance.sweet, 2);
        mse += pow(overall.sour - tasteBalance.sour, 2);
        mse += pow(overall.bitter - tasteBalance.bitter, 2);
        mse += pow(overall.salty - tasteBalance.salty, 2);
        mse += pow(overall.savory - tasteBalance.savory, 2);
        
        return mse;   
    }
    TasteBalance getOverallTasteBalance(const std::vector<std::shared_ptr<MenuItem>>& menuItems) {
        double ovrSweet, ovrSour, ovrBitter, ovrSalty, ovrSavory = 0;
        for (std::shared_ptr<MenuItem> item : menuItems) {
            if(item == nullptr) return TasteBalance(0,0,0,0,0);
            ovrSweet += item->getTasteBalance().sweet;
            ovrSour += item->getTasteBalance().sour;
            ovrBitter += item->getTasteBalance().bitter;
            ovrSalty += item->getTasteBalance().salty;
            ovrSavory += item->getTasteBalance().savory;
        }
        return TasteBalance(ovrSweet/menuItems.size(), ovrSour/menuItems.size(), ovrBitter/menuItems.size(), ovrSalty/menuItems.size(), ovrSavory/menuItems.size());
    }
}