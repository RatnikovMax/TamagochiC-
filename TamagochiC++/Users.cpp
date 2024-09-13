#include "Users.h"

#pragma once

Users::Users() {
	unsigned      id{};
	std::string   name{};
	std::string   password{};
	unsigned      idAnimal{};
	bool          statusGame{};
	unsigned	  value{};
}

Users::Users(unsigned i, std::string n, std::string p, unsigned idA, bool st, unsigned v) : id(i), name(n), password(p), idAnimal(idA), statusGame(st), value(v) {}

unsigned Users::getId() const
{
	return id;
}

std::string Users::getName() const
{
	return name;
}

std::string Users::getPassword() const
{
	return password;
}

unsigned Users::getIdAnimal() const
{
	return idAnimal;
}

bool Users::getStatusGame() const
{
	return statusGame;
}

unsigned Users::getValue() const
{
	return value;
}

void Users::setIdAnimal(unsigned idA)
{
	idAnimal = idA;
}
	
void Users::setStatusGame(bool st)
{
	statusGame = st;
}

void Users::setValue(unsigned v)
{
	value = v;
}

std::ostream& operator<<(std::ostream& os, Users& mem) {
	os << mem.getId() << " " << mem.getName() << " " << mem.getPassword() << " " << mem.getIdAnimal() << " " << mem.getStatusGame() << " " << mem.getValue() << std::endl;
	return os;
}
