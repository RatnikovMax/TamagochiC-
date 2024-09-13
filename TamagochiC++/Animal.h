#pragma once
#include <string>
#include <iostream>
class Animal
{
	friend class Reader;
	friend std::ostream& operator<<(std::ostream& os, Animal& mem);

public:
	Animal();
	Animal(unsigned i, std::string n, unsigned ch, unsigned en, unsigned hu, unsigned un, std::string unN);

	unsigned getId()					const;
	std::string getName()				const;
	unsigned getCheerfulness()			const;
	unsigned getEnergy()				const;
	unsigned getHunger()				const;
	unsigned getUniqueNeed()			const;
	std::string getUniqueNeedName()		const;
	void setCheerfulness(unsigned ch);
	void setEnergy(unsigned en);
	void setHunger(unsigned hu);
	void showStatus() const;

private:
	unsigned	  id{};
	std::string   name{};
	unsigned	  ñheerfulness{};
	unsigned	  energy{};
	unsigned      hunger{};
	unsigned	  uniqueNeed{};
	std::string   uniqueNeedName{};
};