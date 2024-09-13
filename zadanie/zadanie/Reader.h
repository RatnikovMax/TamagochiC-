#pragma once
#include <iostream>
#include "Auto.h"
#include "Clients.h"
#include <vector>
#include <fstream>
#include <set>


class Reader {
public:
	Reader() = default;

	void readClient(std::vector<Clients> &clients, std::string path) {
		std::ifstream f(path);
		while (f && !f.eof()) {
			Clients client;
			f >> client.id >> client.name >> client.password >> client.balance >> client.status;
			clients.push_back(Clients(client.id, client.name, client.password, client.balance, client.status));
		}
		f.close();
		for (auto m : clients) {
			std::cout << m;
		}
	}

	void readAuto(std::vector<Auto> &autom) {
		int id{};
		std::string model = "";
		double price{};
		bool status{};
		std::ifstream f("Auto.txt");
		while (f && !f.eof()) {
			f >> id;
			f >> model;
			f >> price;
			f >> status;
			autom.push_back(Auto(id, model, price, status));
		}
		f.close();
		for (auto m : autom) {
			std::cout << m;
		}
	}



};