#include <iostream>
#include <fstream>
#include "Auto.h"
#include "Clients.h"
#include "Reader.h"
#include <algorithm>
#include <map>
#include "Watcher.h"
#include <chrono>
#include "Writer.h"
#include <cctype>
#include <set>
#include <map>
#include "Clients.h"
#include "Reader.h"

std::vector<Clients>& ClientsVec()
{
	static std::vector<Clients> clients;
	return clients;
}

std::vector<Auto>& Autom()
{
	static std::vector<Auto> autom;
	return autom;
}

//template<typename T>
//constexpr bool check = std::is_same_v<T, Clients> || std::is_same_v<T, Auto>;
//
//template<typename T>
//auto FoundIdClientOrAuto(int id) {
//	if constexpr (std::is_same_v<T, Clients>) 
//		return std::find_if(ClientsVec().begin(), ClientsVec().end(), [&](Clients& type) { return type.getId() == id; });
//	if constexpr (std::is_same_v<T, Auto>)
//		return std::find_if(Autom().begin(), Autom().end(), [&](Auto& type) { return type.getId() == id; });
//	else
//		static_assert(check<T>);
//}

auto FoundIdClient(int id) {
	return std::find_if(ClientsVec().begin(), ClientsVec().end(), [&](Clients& type) { return type.getId() == id; });
}

auto FoundIdAuto(int id) {
	return std::find_if(Autom().begin(), Autom().end(), [&](Auto& type) { return type.getId() == id; });
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
	if (name == "Admin" && password == "qwerty") { return 2; }

	auto &&clients = ClientsVec();

	auto foundClient = std::find_if(clients.begin(), clients.end(),
		                            [name=name, password=password](Clients& clients)
		                            {
			                          return name == clients.getName() && password == clients.getPassword();
		                            });

	if (foundClient == clients.end()) { return 0; }

	std::cout << "You are logged into the car rental system" << std::endl;
	return 1;
}

void AdminPanel(Watcher& watcher) {
	auto flag = true;
	while (flag) {
		std::cout << "Select to action" << std::endl
			<< "1. Does the user have an active car rental" << std::endl
			<< "2. Create a new car rental relationship" << std::endl
			<< "3. Delete the car rental link" << std::endl
			<< "4. List of active car rental relationships" << std::endl
			<< "5. Exit from admin panel" << std::endl
			<< "Enter a number: "; char manage{}; std::cin >> manage;
		switch (manage)
		{
		case '1':
		{
			std::cout << "Enter the user ID: " << std::endl; int clientId{}; std::cin >> clientId;
			int autoId = watcher.getCarIdRentByUser(clientId);
			autoId != 0 ? std::cout << "User ID" << clientId << " rents a car ID" << autoId << std::endl : std::cout << "User ID" << clientId << " NO rents a car" << std::endl;
			break;
		}
		case '2':
		{
			std::cout << "Enter the user ID: " << std::endl; int clientId{}; std::cin >> clientId;
			std::cout << "Enter the the auto ID: " << std::endl; int autoId{}; std::cin >> autoId;
			auto foundClient = FoundIdClient(clientId);
			auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == autoId; });
			if (watcher.rentCarByUser(clientId, autoId)) {
				foundAuto->setStatus(false);
				std::cout << "The connection between the user with Name " << foundClient->getName() << " and the machine ID " << autoId << " has been created" << std::endl;
			}
			else {
				std::cout << "The connection between the user with Name " << foundClient->getName() << " and the machine ID " << autoId << " already exists" << std::endl;
			}
			break;
		}
		case '3':
		{
			std::cout << "Enter the user ID: " << std::endl; int clientId{}; std::cin >> clientId;
			auto foundClient = std::find_if(ClientsVec().begin(), ClientsVec().end(), [&](Clients& client) { return client.getId() == clientId; });
			std::cout << "Delete" << std::endl;
			auto autoId = watcher.getCarIdRentByUser(clientId);
			auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == autoId; });
			auto [flag, sec] = watcher.deleteRentCarByUser(clientId);
			if (flag) {
				std::cout << "The lease is completed for the user Name " << foundClient->getName() << std::endl;
				foundClient->SetBalance(sec.count() * (foundAuto->getPrice() / 60.0));
				std::cout << foundClient->getBalance() << std::endl;
				foundAuto->setStatus(true);
				//wr.writeClient(Clients());
			}
			else {
				std::cout << "The user has no active connections" << std::endl;
			}
			break;
		}
		case '4':
		{
			for (auto elem : watcher.getListRent()) {
				auto foundClient = std::find_if(ClientsVec().begin(), ClientsVec().end(), [&](Clients& client) { return client.getId() == elem.first; });
				auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == elem.second; });
				std::cout << foundClient->getName() << " - " << foundAuto->getModel() << std::endl;
			}
			break;
		}
		case '5':
			flag = false;
		}
	}
	std::cout << "Exit" << std::endl;
}

void UserPanel(Watcher& watcher, std::tuple<std::string, std::string> data) {
	std::cout << "You are logged UserPanel" << std::endl;
	auto foundClient = std::find_if(ClientsVec().begin(), ClientsVec().end(), [&](Clients& client) { return client.getName() == std::get<0>(data); });
	auto clientName = foundClient->getName(); std::cout << clientName << std::endl << foundClient->getBalance() << std::endl;
	auto flag = true;
	while (flag) {
		std::cout << "Select to action: " << std::endl
			<< "1. List of available cars" << std::endl
			<< "2. Rent a car" << std::endl
			<< "3. Complete the car rental" << std::endl
			<< "4. Exit" << std::endl
			<< "Enter a number: "; char manage{}; std::cin >> manage;
		switch (manage) {
		case '1':
		{
			std::cout << "List of Available cars" << std::endl;
			for (auto autom : Autom()) {
				if (autom.getStatus() == true) {
					std::cout << "ID: " << autom.getId() << " - " << autom.getModel() << " | Price per minute: " << autom.getPrice() << std::endl;
				}
			}
			break;
		}
		case '2':
		{
			std::cout << "Enter the the auto ID: " << std::endl; int autoId{}; std::cin >> autoId;
			auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == autoId; });
			if (watcher.rentCarByUser(foundClient->getId(), autoId)) {
				foundAuto->setStatus(false);
				std::cout << "The connection between the user with Name " << clientName << " and the machine ID " << autoId << " has been created" << std::endl;
			}
			else {
				std::cout << "The connection between the user with Name " << clientName << " and the machine ID " << autoId << " already exists" << std::endl;
			}
			break;
		}
		case '3':
		{
			auto autoId = watcher.getCarIdRentByUser(foundClient->getId());
			auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == autoId; });
			auto [flag, sec] = watcher.deleteRentCarByUser(foundClient->getId());
			if (flag) {
				std::cout << "The lease is completed for the user Name " << clientName << std::endl;
				foundClient->SetBalance(sec.count() * (foundAuto->getPrice() / 60.0));
				std::cout << foundClient->getBalance() << std::endl;
				foundAuto->setStatus(true);
				//wr.writeClient(Clients());
			}
			else {
				std::cout << "The user has no active connections" << std::endl;
			}

			break;
		}
		case '4':
			flag = false;
		}
	}
}








int main()
{
	std::cout << "Data load..." << std::endl;
	//declaration block
	Reader reader;
	Watcher watcher;
	Writer writer;
	reader.readClient(ClientsVec(), "Clients.txt");
	
	

	//LogIn
	while (true) {
		auto data = TryReadCredentials();
		int type = LogIn(std::get<0>(data), std::get<1>(data));
		switch (type) {
		case 1:
			UserPanel(watcher, data);
			break;
		case 2:
			AdminPanel(watcher);
			break;
		case 0:
			break;
		}
		break;
	}
}




	//std::cout << "To exit, enter '1' in the name" << std::endl;
	//while (true) {
	//	std::string name{}, password{};
	//	std::cout << "-------------------------------------------" << std::endl;
	//	std::cout << "Enter name: "; std::cin >> name;
	//	if (name == "1") {
	//		break;
	//	}
	//	std::cout << "Enter password: "; std::cin >> password;
	//	std::cout << "-------------------------------------------" << std::endl;



	//	//Admin panel
	//	if (name == "Admin" && password == "qwerty") {
	//		std::cout << "You are logged into the admin panel" << std::endl;
	//		auto flag = true;
	//		while (flag) {
	//			std::cout << "Select to action" << std::endl
	//				<< "1. Does the user have an active car rental" << std::endl
	//				<< "2. Create a new car rental relationship" << std::endl
	//				<< "3. Delete the car rental link" << std::endl
	//				<< "4. List of active car rental relationships" << std::endl
	//				<< "5. Exit from admin panel" << std::endl
	//				<< "Enter a number: "; char manage{}; std::cin >> manage;
	//			switch (manage)
	//			{
	//			case '1':
	//			{
	//				std::cout << "Enter the user ID: " << std::endl; int clientId{}; std::cin >> clientId;
	//				int autoId = watcher.getCarIdRentByUser(clientId);
	//				autoId != 0 ? std::cout << "User ID" << clientId << " rents a car ID" << autoId << std::endl : std::cout << "User ID" << clientId << " NO rents a car" << std::endl;
	//				break;
	//			}
	//			case '2':
	//			{
	//				std::cout << "Enter the user ID: " << std::endl; int clientId{}; std::cin >> clientId;
	//				std::cout << "Enter the the auto ID: " << std::endl; int autoId{}; std::cin >> autoId;
	//				auto x = FoundIdClientOrAuto<Client>(clientId);
	//				auto foundClient = FoundIdClient(clientId);
	//				auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == autoId; });
	//				if (watcher.rentCarByUser(clientId, autoId)) {
	//					foundAuto->setStatus(false);
	//					std::cout << "The connection between the user with Name " << foundClient->getName() << " and the machine ID " << autoId << " has been created" << std::endl;
	//				}
	//				else {
	//					std::cout << "The connection between the user with Name " << foundClient->getName() << " and the machine ID " << autoId << " already exists" << std::endl;
	//				}
	//				break;
	//			}
	//			case '3':
	//			{
	//				std::cout << "Enter the user ID: " << std::endl; int clientId{}; std::cin >> clientId;
	//				auto foundClient = std::find_if(Clients().begin(), Clients().end(), [&](Client& client) { return client.getId() == clientId; });
	//				std::cout << "Delete" << std::endl;
	//				auto autoId = watcher.getCarIdRentByUser(clientId);
	//				auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == autoId; });
	//				auto [flag, sec] = watcher.deleteRentCarByUser(clientId);
	//				if (flag) {
	//					std::cout << "The lease is completed for the user Name " << foundClient->getName() << std::endl;
	//					foundClient->SetBalance(sec.count() * (foundAuto->getPrice() / 60.0));
	//					std::cout << foundClient->getBalance() << std::endl;
	//					foundAuto->setStatus(true);
	//					//wr.writeClient(Clients());
	//				}
	//				else {
	//					std::cout << "The user has no active connections" << std::endl;
	//				}
	//				break;
	//			}
	//			case '4':
	//			{
	//				for (auto elem : watcher.getListRent()) {
	//					auto foundClient = std::find_if(Clients().begin(), Clients().end(), [&](Client& client) { return client.getId() == elem.first; });
	//					auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == elem.second; });
	//					std::cout << foundClient->getName() << " - " << foundAuto->getModel() << std::endl;
	//				}
	//				break;
	//			}
	//			case '5':
	//				flag = false;
	//			}
	//		}
	//		std::cout << "Exit" << std::endl;
	//	}

		//Clients panel
	//	auto foundClient = std::find_if(Clients().begin(), Clients().end(), [&](Client& client) { return client.getName() == name && client.getPassword() == password; });
	//	if (foundClient != Clients().end()) {
	//		std::cout << "You are logged into the car rental system" << std::endl;
	//		auto clientName = foundClient->getName(); std::cout << clientName << std::endl << foundClient->getBalance() << std::endl;
	//		auto flag = true;
	//		while (flag) {
	//			std::cout << "Select to action: " << std::endl
	//				<< "1. List of available cars" << std::endl
	//				<< "2. Rent a car" << std::endl
	//				<< "3. Complete the car rental" << std::endl
	//				<< "4. Exit" << std::endl
	//				<< "Enter a number: "; char manage{}; std::cin >> manage;
	//			switch (manage) {
	//			case '1':
	//			{
	//				std::cout << "List of Available cars" << std::endl;
	//				for (auto autom : Autom()) {
	//					if (autom.getStatus() == true) {
	//						std::cout << "ID: " << autom.getId() << " - " << autom.getModel() << " | Price per minute: " << autom.getPrice() << std::endl;
	//					}
	//				}
	//				break;
	//			}
	//			case '2':
	//			{
	//				std::cout << "Enter the the auto ID: " << std::endl; int autoId{}; std::cin >> autoId;
	//				auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == autoId; });
	//				if (watcher.rentCarByUser(foundClient->getId(), autoId)) {
	//					foundAuto->setStatus(false);
	//					std::cout << "The connection between the user with Name " << clientName << " and the machine ID " << autoId << " has been created" << std::endl;
	//				}
	//				else {
	//					std::cout << "The connection between the user with Name " << clientName << " and the machine ID " << autoId << " already exists" << std::endl;
	//				}
	//				break;
	//			}
	//			case '3':
	//			{
	//				auto autoId = watcher.getCarIdRentByUser(foundClient->getId());
	//				auto foundAuto = std::find_if(Autom().begin(), Autom().end(), [&](Auto& autom) { return autom.getId() == autoId; });
	//				auto [flag, sec] = watcher.deleteRentCarByUser(foundClient->getId());
	//				if (flag) {
	//					std::cout << "The lease is completed for the user Name " << clientName << std::endl;
	//					foundClient->SetBalance(sec.count() * (foundAuto->getPrice() / 60.0));
	//					std::cout << foundClient->getBalance() << std::endl;
	//					foundAuto->setStatus(true);
	//					//wr.writeClient(Clients());
	//				}
	//				else {
	//					std::cout << "The user has no active connections" << std::endl;
	//				}

	//				break;
	//			}
	//			case '4':
	//				flag = false;
	//			}
	//		}
	//	}
	//	else {
	//		std::cout << "The user was not found" << std::endl;
	//	}
	//}
