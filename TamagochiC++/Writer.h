#pragma once
#include <iostream>
#include "Animal.h"
#include "Users.h"
#include <vector>
#include <fstream>

class Writer {
public:
	Writer() = default;

	void writeUsers(std::vector<Users>& users) {
		if (auto f = std::ofstream("Users.txt"))
		{
			for (std::vector<Users>::iterator itr = users.begin(); itr != users.end(); ++itr) {
				if (itr != users.begin()) {
					f << '\n'; 
				}
				f << itr->getId() << ' '
					<< itr->getName() << ' '
					<< itr->getPassword() << ' '
					<< itr->getIdAnimal() << ' '
					<< itr->getStatusGame() << ' '
					<< itr->getValue();
			}
		}
		for (auto m : users) {
			std::cout << m.getId() << " " << m.getName() << " " << m.getPassword() << " " << m.getIdAnimal() << " " << m.getStatusGame() << " " << m.getValue() << std::endl;
		}
	}

	void writeNewGame(int type, int id, std::vector<Animal>& animal) {
		std::fstream f("Game.txt", std::ios::in | std::ios::out | std::ios::app);

		if (f) {
			auto foundAnimal = std::find_if(animal.begin(), animal.end(),
				[&](Animal& animal) { return animal.getId() == type; });

			f.seekg(0, std::ios::end);

			if (f.tellg() > 0) {
				f << '\n';
			}

			Game game;
			f << game.getCountGame() + 1 << ' '
				<< id << ' '
				<< foundAnimal->getId() << ' '
				<< foundAnimal->getName() << ' '
				<< foundAnimal->getCheerfulness() << ' '
				<< foundAnimal->getEnergy() << ' '
				<< foundAnimal->getHunger() << ' '
				<< foundAnimal->getUniqueNeed() << ' '
				<< foundAnimal->getUniqueNeedName(); 
		}
	}

	void writeGame(std::vector<Game>& game) {
		if (auto f = std::ofstream("Game.txt"))
		{
			for (std::vector<Game>::iterator itr = game.begin(); itr != game.end(); ++itr) {
				if (itr != game.begin()) {
					f << '\n';
				}
				f << itr->getIdGame() << ' '
					<< itr->getIdUser() << ' '
					<< itr->getIdAnimal() << ' '
					<< itr->getNameAnimal() << ' '
					<< itr->getCheerfulness() << ' '
					<< itr->getEnergy() << ' '
					<< itr->getHunger() << ' '
					<< itr->getUniqueNeed() << ' '
					<< itr->getUniqueNeedName();
			}
		}
	}
};