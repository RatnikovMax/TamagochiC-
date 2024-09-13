#pragma once
#include <iostream>
#include "Auto.h"
#include "Clients.h"
#include <chrono>
#include <map>

struct rentConnection {
	int autoId = 0;
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
};

class Watcher{
public:
	Watcher() = default;
	std::map<int, int> getListRent()
	{
		std::map<int, int> result;
		for (auto &&elem : rentBindings)
		{
			result.emplace(elem.first, elem.second.autoId);
		}
		return result;
	}

	int getCarIdRentByUser(int clientId)
	{
		auto found = rentBindings.find(clientId);
		if (found == rentBindings.end()) { return 0; }
		return found->second.autoId;
	}

	auto rentCarByUser(int clientId, int carId)
	{
		rentConnection r;
		r.autoId = carId;
		auto [_, inserted] = rentBindings.emplace(clientId, r);
		return inserted;
	}


	std::pair<bool, std::chrono::duration<double>> deleteRentCarByUser(int clientId) {
		auto it = rentBindings.find(clientId);
		if (it == rentBindings.end()) {
			return std::pair<bool, std::chrono::duration<double>>(false, std::chrono::duration<double>());
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> seconds{ end - it->second.start };
		return std::pair<bool, std::chrono::duration<double>>(rentBindings.erase(clientId), seconds);
	}

private:
	std::map<int, rentConnection> rentBindings;
};