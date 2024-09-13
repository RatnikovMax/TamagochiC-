#pragma once
#include <string>
#include <iostream>
class Clients
{
	friend class Reader;
	friend std::ostream& operator<<(std::ostream& os, Clients& mem);

public:
	Clients();
	Clients(unsigned i, std::string n, std::string p, double bn, bool st);

	unsigned getId()			   const;
	std::string getName()          const;
	std::string getPassword()      const;
	double getBalance()            const;
	bool getStatus()               const;
	void SetBalance(double cost);

private:
	unsigned	  id{};
	std::string   name{};
	std::string   password{};
	double        balance{};
	bool          status{};
};