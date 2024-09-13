#pragma once
#include <iostream>
#include "Animal.h"
#include "Users.h"
#include <vector>
#include <fstream>
#include <set>
#include "Game.h"

class Reader {
public:
	Reader() = default;

	void readUsers(std::vector<Users>& UsersList, std::string path) {
		std::ifstream f(path);
		while (f && !f.eof()) {
			Users users;
			f >> users.id >> users.name >> users.password >> users.idAnimal >> users.statusGame >> users.value;
			UsersList.push_back(users);
		}
		f.close();
		for (auto m : UsersList) {
			std::cout << m;
		}
	}

	void readAnimal(std::vector<Animal>& AnimalList, std::string path) {
		std::ifstream f(path);
		while (f && !f.eof()) {
			Animal animal;
			f >> animal.id >> animal.name >> animal.ñheerfulness >> animal.energy >> animal.hunger >> animal.uniqueNeed >> animal.uniqueNeedName;
			AnimalList.push_back(animal);
		}
		f.close();
		for (auto m : AnimalList) {
			std::cout << m;
		}
	}

	void readGame(std::vector<Game>& GameList, std::string path) {
		std::ifstream f(path);
		std::string line;

		while (std::getline(f, line)) {
			std::istringstream iss(line);
			Game game;

			if (!(iss >> game.idGame >> game.idUser >> game.idAnimal >> game.nameAnimal
				>> game.ñheerfulness >> game.energy >> game.hunger
				>> game.uniqueNeed >> game.uniqueNeedName)) {
				continue;
			}
			GameList.push_back(game);
		}

		f.close();
		for (auto m : GameList) {
			std::cout << m;
		}
	}


};