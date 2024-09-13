#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Game.h"

class Item {
public:
    Item(std::string n, std::string type, unsigned points)
        : name(n), needType(type), needPoints(points) {}

    std::string getName() const { return name; }
    std::string getNeedType() const { return needType; }
    unsigned getNeedPoints() const { return needPoints; }

    void showItemInfo() const {
        std::cout << "Item: " << name << " | Increases: " << needType << " by " << needPoints << " points." << std::endl;
    }

private:
    std::string name;      
    std::string needType;  
    unsigned needPoints;  
};


class Shop {
public:
    Shop() {
        items.emplace_back("Food", "hunger", 20);
        items.emplace_back("Toy", "cheerfulness", 15);
        items.emplace_back("Energy Drink", "energy", 25);
        items.emplace_back("Special Treat", "uniqueNeed", 30);
    }

    void showItems() const {
        std::cout << "Welcome to the Shop! Here are the available items:" << std::endl;
        for (const auto& item : items) {
            item.showItemInfo();
        }
    }

    bool useItem(Game& game, const std::string& itemName) {
        for (const auto& item : items) {
            if (item.getName() == itemName) {
                applyItemToGame(game, item);
                return true;
            }
        }
        std::cout << "Item not found!" << std::endl;
        return false;
    }

private:
    std::vector<Item> items; 

    // Применение предмета к игре
    void applyItemToGame(Game& game, const Item& item) {
        if (item.getNeedType() == "hunger") {
            game.setHunger(game.getHunger() + item.getNeedPoints());
            if (game.getHunger() > 100) game.setHunger(100);
            std::cout << "Hunger increased by " << item.getNeedPoints() << std::endl;
        }
        else if (item.getNeedType() == "cheerfulness") {
            game.setCheerfulness(game.getCheerfulness() + item.getNeedPoints());
            if (game.getCheerfulness() > 100) game.setCheerfulness(100);
            std::cout << "Cheerfulness increased by " << item.getNeedPoints() << std::endl;
        }
        else if (item.getNeedType() == "energy") {
            game.setEnergy(game.getEnergy() + item.getNeedPoints());
            if (game.getEnergy() > 100) game.setEnergy(100);
            std::cout << "Energy increased by " << item.getNeedPoints() << std::endl;
        }
        else if (item.getNeedType() == "uniqueNeed") {
            game.setUniqueNeed(game.getUniqueNeed() + item.getNeedPoints());
            if (game.getUniqueNeed() > 100) game.setUniqueNeed(100);
            std::cout << item.getNeedType() << " increased by " << item.getNeedPoints() << std::endl;
        }
    }
};