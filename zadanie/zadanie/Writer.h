#pragma once
#include <iostream>
#include "Auto.h"
#include "Clients.h"
#include <vector>
#include <fstream>

class Writer {
public:
	Writer() = default;

	void writeClient(std::vector<Clients>& client) {
		if (auto f = std::ofstream("Clients.txt"))
		{
			for (std::vector<Clients>::iterator itr = client.begin(); itr != client.end(); ++itr) {
				f << itr->getId() << ' '
				  << itr->getName() << ' '
				  << itr->getPassword() << ' '
				  << itr->getBalance() << ' '
				  << itr->getStatus() << '\n';
			}
		}
		for (auto m : client) {
			std::cout << m.getId() << " " << m.getName() << " " << m.getPassword() << " " << m.getBalance() << " " << m.getStatus() << std::endl;
		}
	}

	void writeAuto(std::vector<Auto>& autom) {
		if (auto f = std::ofstream("Auto.txt"))
		{
			for (std::vector<Auto>::iterator itr = autom.begin(); itr != autom.end(); ++itr) {
				f << itr->getId() << ' '
					<< itr->getModel() << ' '
					<< itr->getPrice() << ' '
					<< itr->getStatus() << '\n';
			}
		}
		for (auto m : autom) {
			std::cout << m.getId() << " " << m.getModel() << " " << m.getPrice() << " " << m.getStatus() << std::endl;
	
		}
	}
};