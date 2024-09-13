#include "Clients.h"

#pragma once

Clients::Clients() {
	std::string   name{};
	std::string   password{};
	double        balance{};
	unsigned      id{};
	bool          status{};
}

Clients::Clients(unsigned i, std::string n, std::string p, double bn, bool st) : id(i), name(n), password(p), balance(bn), status(st) {}

unsigned Clients::getId() const
{
	return id;
}

std::string Clients::getName() const 
{
	return name;
}

std::string Clients::getPassword() const 
{
	return password;
}

double Clients::getBalance() const 
{
	return balance;
}

bool Clients::getStatus() const 
{
	return status;
}

void Clients::SetBalance(double cost) 
{
	balance -= cost;
}

std::ostream& operator<<(std::ostream& os, Clients& mem) {
	os << mem.getId() << " " << mem.getName() << " " << mem.getPassword() << " " << mem.getBalance() << " " << mem.getStatus() << std::endl;
	return os;
}
