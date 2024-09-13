#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <chrono>
#include <cctype>
#include <set>
#include "Users.h"
#include <vector>
#include <tuple>
#include "Reader.h"
#include "Writer.h"
#include "Shop.h"
#include <thread> 
#include <chrono> 

std::vector<Users>& UsersList()
{
	static std::vector<Users> users;
	return users;
}

std::vector<Animal>& AnimalList()
{
	static std::vector<Animal> animal;
	return animal;
}

std::vector<Game>& GameList()
{
	static std::vector<Game> game;
	return game;
}


auto FoundIdUser(int id) {
	return std::find_if(UsersList().begin(), UsersList().end(), 
		[&](Users& type) 
		{ return type.getId() == id; });
}

auto TryReadCredentials() {
	try {
		std::string name{}, password{};
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "Enter name: "; std::cin >> name;
		std::cout << "Enter password: "; std::cin >> password;
		std::cout << "-------------------------------------------" << std::endl;
		for (int i = 0; i != name.length(); i++) {
			if (!isalnum(name[i])) {
				throw std::string{ "No correct login or password" };
			}
		}
		for (int i = 0; i != password.length(); i++) {
			if (!isalnum(password[i])) {
				throw std::string{ "No correct login or password" };
			}
		}
		return std::tuple{ name, password };
	}
	catch (const std::string& error_message) {
		std::cout << error_message << std::endl;
	}
}

int LogIn(std::string name, std::string password)
{
    auto&& users = UsersList();

    auto foundUsers = std::find_if(users.begin(), users.end(),
        [name = name, password = password](Users& users)
        {
            return name == users.getName() && password == users.getPassword();
        });

    if (foundUsers == users.end()) { std::cout << "No found User" << std::endl; return 0; }

    std::cout << "You are logged in" << std::endl;
    return 1;
}

void UserPanel(std::tuple<std::string, std::string> data) {
    Writer writer;
    Reader reader;
    Shop shop;
    auto foundClient = std::find_if(UsersList().begin(), UsersList().end(),
        [&](Users& user) {
            return user.getName() == std::get<0>(data);
        });

    if (!foundClient->getStatusGame())
    {
        std::cout << "No animal, select animal:" << std::endl
            << "1. Dragon" << std::endl
            << "2. Unicorn" << std::endl;
        char manage{};
        std::cin >> manage;
        switch (manage)
        {
        case '1':
        {
            writer.writeNewGame(1, foundClient->getId(), AnimalList());
            foundClient->setStatusGame(true);
            reader.readGame(GameList(), "Game.txt");
            writer.writeUsers(UsersList());
            break;
        }
        case '2':
        {
            writer.writeNewGame(2, foundClient->getId(), AnimalList());
            foundClient->setStatusGame(true);
            reader.readGame(GameList(), "Game.txt");
            writer.writeUsers(UsersList());
            break;
        }
        }
    }

    auto clientName = foundClient->getName();
    std::cout << "Welcome " << clientName << std::endl;

    auto findGame = std::find_if(GameList().begin(), GameList().end(),
        [&](Game& game) {
            return game.getIdUser() == foundClient->getId();
        });

    std::cout << "Your tamagotchi: " << std::endl;
    findGame->showStatus();

    bool gameRunning = true;
    auto lastDecreaseTime = std::chrono::steady_clock::now();
    const auto interval = std::chrono::seconds(5);  

    while (gameRunning) {
        std::cout << "Choose an action:" << std::endl;
        std::cout << "1. Feed your pet" << std::endl;
        std::cout << "2. Satisfy unique need" << std::endl;
        std::cout << "3. Show pet's status" << std::endl;
        std::cout << "4. Visit the shop" << std::endl;
        std::cout << "5. Put your pet to sleep (restore energy)" << std::endl;
        std::cout << "6. Save game" << std::endl;
        std::cout << "7. Exit game" << std::endl;

        char choice;
        std::cin >> choice;

        switch (choice) {
        case '1':
            findGame->feed();
            break;
        case '2':
            findGame->satisfyUniqueNeed();
            break;
        case '3':
            findGame->showStatus();
            break;
        case '4': {
            shop.showItems();
            std::cout << "Enter the name of the item to use: ";
            std::string itemName;
            std::cin.ignore();
            std::getline(std::cin, itemName);
            shop.useItem(*findGame, itemName);
            break;
        }
        case '5':
            std::cout << "Your pet is sleeping... Please wait." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5)); 
            findGame->sleep();
            break;
        case '6':
            writer.writeGame(GameList());
            std::cout << "Game saved!" << std::endl;
            break;
        case '7':
            gameRunning = false;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
        }

        auto currentTime = std::chrono::steady_clock::now();
        if (currentTime - lastDecreaseTime >= interval) {
            findGame->decreaseNeedsOverTime();
            lastDecreaseTime = currentTime;
            findGame->showStatus();
        }

        if (findGame->isGameOver()) {
            std::cout << "Your tamagotchi has run away!" << std::endl;
            GameList().erase(findGame);
            foundClient->setStatusGame(false);
            writer.writeUsers(UsersList());
            writer.writeGame(GameList());
            gameRunning = false;
        }
    }

}

int main() {
    std::cout << "Data load..." << std::endl;

    Reader reader;
    Writer writer;

    reader.readUsers(UsersList(), "Users.txt");
    reader.readAnimal(AnimalList(), "Animal.txt");
    reader.readGame(GameList(), "Game.txt");

    bool exitProgram = false;
    while (!exitProgram) {
        bool loggedIn = false;

        while (!loggedIn) {
            auto data = TryReadCredentials();
            int loginResult = LogIn(std::get<0>(data), std::get<1>(data));
            if (loginResult == 1) {
                loggedIn = true;
                UserPanel(data); 
            }
            else {
                std::cout << "Try again or press 'q' to quit." << std::endl;
                char choice;
                std::cin >> choice;
                if (choice == 'q' || choice == 'Q') {
                    exitProgram = true;
                    break;
                }
            }
        }
    }

    std::cout << "Exiting program..." << std::endl;
    return 0;
}