#ifndef INTERFACE_H
#define INTERFACE_H
#include <User.h>
#include <Menu.h>
#include <MenuItem.h>
#include <TasteBalance.h>
#include <Appetizer.h>
#include <Dessert.h>
#include <Drink.h>
#include <MainCourse.h>
#include <Salad.h>
#include <Starter.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <memory>

namespace Interface {

    std::vector<std::shared_ptr<MenuItem>> getItemsFromJson(const std::string& json_data);
    std::shared_ptr<MenuItem> suggestMenuItem(const std::vector<std::shared_ptr<MenuItem>>& menuItems, const TasteBalance& tasteBalance);
    std::shared_ptr<MenuItem> suggestMenuItem(const std::vector<std::shared_ptr<MenuItem>>& menuItems, const TasteBalance& tasteBalance, const std::type_info& type);
    Menu suggestFullMenu(std::vector<std::shared_ptr<MenuItem>>& menuItems, const TasteBalance& tasteBalance);
    TasteBalance getOverallTasteBalance(const std::vector<std::shared_ptr<MenuItem>>& menuItems);
    double calculateMse(std::vector<std::shared_ptr<MenuItem>> menuItems, TasteBalance tasteBalance);


}
#endif