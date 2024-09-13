#pragma once
#include <string>

class Auto{
private:
	const int id{};
	std::string model = "";
	double price{};
	bool status{};


public:
	Auto() = default;
	Auto(int ids, std::string mdl, double pr, bool sts) : id(ids), model(mdl), price(pr), status(sts) {}

	auto getId() {
		return id;
	}
	auto getModel(){
		return model;
	}
	auto getPrice() {
		return price;
	}
	auto getStatus() {
		return status;
	}
	void setStatus(bool cond) {
		status = cond;
	}

	friend std::ostream& operator<<(std::ostream& os, Auto& mem) {
		os << mem.getId() << " " << mem.getModel() << " " << mem.getPrice() << " " << mem.getStatus() << std::endl;
		return os;
	}
};