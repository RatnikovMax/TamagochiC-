#pragma once
#include <string>
#include <iostream>
class Users
{
	friend class Reader;
	friend std::ostream& operator<<(std::ostream& os, Users& mem);

public:
	Users();
	Users(unsigned i, std::string n, std::string p, unsigned idA, bool st, unsigned v);

	unsigned getId()			   const;
	std::string getName()          const;
	std::string getPassword()      const;
	unsigned getIdAnimal()         const;
	bool getStatusGame()           const;
	unsigned getValue()			   const;
	void setIdAnimal(unsigned idA);
	void setStatusGame(bool st);
	void setValue(unsigned v);

private:
	unsigned	  id{};
	std::string   name{};
	std::string   password{};
	unsigned	  idAnimal{};
	bool          statusGame{};
	unsigned	  value{};
};