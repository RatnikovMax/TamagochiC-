#pragma once
#include "Animal.h"

Animal::Animal() {
	unsigned	  id{};
	std::string   name{};
	std::string   password{};
	unsigned	  ñheerfulness{};
	unsigned	  energy{};
	unsigned      hunger{};
	unsigned	  uniqueNeed{};
	std::string   uniqueNeedName{};
}

Animal::Animal(unsigned i, std::string n, unsigned ch, unsigned en, unsigned hu, unsigned un, std::string unN) : 
	id(i), name(n), ñheerfulness(ch), energy(en), hunger(hu), uniqueNeed(un), uniqueNeedName(unN){}

unsigned Animal::getId() const
{
	return id;
}

std::string Animal::getName() const
{
	return name;
}

unsigned Animal::getCheerfulness() const
{
	return ñheerfulness;
}

unsigned Animal::getEnergy() const
{
	return energy;
}

unsigned Animal::getHunger() const
{
	return hunger;
}

unsigned Animal::getUniqueNeed()     const
{
	return uniqueNeed;
}
std::string Animal::getUniqueNeedName()		const
{
	return uniqueNeedName;
}

void Animal::setCheerfulness(unsigned ch) 
{
	ñheerfulness = ch;
}
void Animal::setEnergy(unsigned en)
{
	energy = en;
}

void Animal::setHunger(unsigned hu)
{
	hunger = hu;
}

void Animal::showStatus() const {
	std::cout << "ID: " << getId() << std::endl
		<< "Name: " << getName() << std::endl
		<< "Cheerfulness: " << getCheerfulness() << std::endl
		<< "Energy: " << getEnergy() << std::endl
		<< "Hunger: " << getHunger() << std::endl
		<< "Unique Need: " << getUniqueNeed() << std::endl
		<< "Unique Need Name: " << getUniqueNeedName() << std::endl;
}

std::ostream& operator<<(std::ostream& os, Animal& mem) 
{
	os << mem.getId() << " " << mem.getName() << " " << mem.getCheerfulness() << " " << mem.getEnergy() << " " << mem.getHunger() << " " << mem.getUniqueNeed() << " " << mem.getUniqueNeedName() << std::endl;
	return os;
}