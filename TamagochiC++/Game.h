#pragma once
class Game
{
	friend class Reader;

public:
	Game() = default;
	Game(unsigned idG, unsigned idU, unsigned idA, std::string n, unsigned ch, unsigned en, unsigned hu, unsigned un, std::string unN) : 
		idGame(idG), idUser(idU), idAnimal(idA), nameAnimal(n), ñheerfulness(ch), energy(en), hunger(hu), uniqueNeed(un), uniqueNeedName(unN) {}

    unsigned getIdGame() const { return idGame; }
    unsigned getIdUser() const { return idUser; }
    unsigned getIdAnimal() const { return idAnimal; }
    std::string getNameAnimal() const { return nameAnimal; }
    unsigned getCheerfulness() const { return ñheerfulness; }
    unsigned getEnergy() const { return energy; }
    unsigned getHunger() const { return hunger; }
    unsigned getUniqueNeed() const { return uniqueNeed; }
    std::string getUniqueNeedName() const { return uniqueNeedName; }
    auto getCountGame() {
        auto count = 0;
        count += idGame;
        return count;
    }
    void setCheerfulness(unsigned ch) { ñheerfulness = ch; }
    void setEnergy(unsigned en) { energy = en; }
    void setHunger(unsigned hu) { hunger = hu; }
    void setUniqueNeed(unsigned un) { uniqueNeed = un; }

    void sleep() {
        if (energy < 100) {
            energy += 20; 
            if (energy > 100) energy = 100;
            std::cout << "Your pet is sleeping. Energy is now: " << energy << std::endl;
        }
        else {
            std::cout << "Your pet is fully rested!" << std::endl;
        }
    }

    void showStatus() const {
        std::cout << "ID: " << getIdUser() << std::endl
            << "Name animal: " << getNameAnimal() << std::endl
            << "Cheerfulness: " << getCheerfulness() << std::endl
            << "Energy: " << getEnergy() << std::endl
            << "Hunger: " << getHunger() << std::endl
            << "Unique Need: " << getUniqueNeed() << std::endl
            << "Unique Need Name: " << getUniqueNeedName() << std::endl;
    }

    void feed() {
        if (hunger < 100) {
            hunger += 10;
            if (hunger > 100) hunger = 100;
            std::cout << "You have fed your pet. Hunger is now: " << hunger << std::endl;
        }
        else {
            std::cout << "Your pet is already full!" << std::endl;
        }
    }

    void satisfyUniqueNeed() {
        if (uniqueNeed < 100) {
            uniqueNeed += 10;
            if (uniqueNeed > 100) uniqueNeed = 100;
            std::cout << "You have satisfied your pet's unique need (" << uniqueNeedName << "). It's now: " << uniqueNeed << std::endl;
        }
        else {
            std::cout << "Your pet's unique need is fully satisfied!" << std::endl;
        }
    }

    void decreaseNeedsOverTime() {
        if (ñheerfulness > 0) {
            ñheerfulness -= 2;
            if (ñheerfulness > 100) { 
                ñheerfulness = 0;
            }
        }
        if (energy > 0) {
            energy--;
            if (energy > 100) {
                energy = 0;
            }
        }
        if (hunger > 0) {
            hunger -= 3;
            if (hunger > 100) {
                hunger = 0;
            }
        }
        if (uniqueNeed > 0) {
            uniqueNeed--;
            if (uniqueNeed > 100) {
                uniqueNeed = 0;
            }
        }
    }

    bool isGameOver() const {
        int zeroCount = 0;

        if (ñheerfulness == 0) zeroCount++;
        if (energy == 0) zeroCount++;
        if (hunger == 0) zeroCount++;
        if (uniqueNeed == 0) zeroCount++; 

        return zeroCount >= 3; 
    }

    friend std::ostream& operator<<(std::ostream& os, Game& mem)
    {
        os << mem.getIdGame() << " " << mem.getIdUser() << " " << mem.getIdAnimal() << " " << mem.getNameAnimal() << " " << mem.getCheerfulness() << " " << mem.getEnergy() << " " << mem.getHunger() << " " << mem.getUniqueNeed() << " " << mem.getUniqueNeedName() << std::endl;
        return os;
    }

private:
	unsigned	  idGame{};
	unsigned	  idUser{};
	unsigned	  idAnimal{};
	std::string   nameAnimal{};
	unsigned	  ñheerfulness{};
	unsigned	  energy{};
	unsigned      hunger{};
	unsigned	  uniqueNeed{};
	std::string   uniqueNeedName{};
};