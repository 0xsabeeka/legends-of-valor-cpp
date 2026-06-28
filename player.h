#pragma once
#include <string>
using namespace std;

// Base Player class (abstract)
class Player {
protected:
    string name;
    int health, mana, attackPower, defense, level, xp;
    static int playerCount;
public:
    Player(string);
    Player(const Player& other); // Copy Constructor
    virtual ~Player();
    virtual void displayStats() const = 0;
    virtual void attack() = 0;
    virtual void useSkill() = 0;
    virtual void takeDamage(int dmg) = 0;

    void addXP(int amount);
    void levelUp();
    void heal(int amount);

    void setHealth(int h);
    void setXP(int x);

    string getName() const;
    int getHealth() const;
    int getXP()const;
    static int getPlayerCount();

    Player& operator+(int amount);  //operator overload

};


// Derived classes
class Mage : public Player {
public:
    Mage(string);
    void displayStats() const override;
    void attack() override;
    void useSkill() override;
    void takeDamage(int)override;
};

class Warrior : public Player {
public:
    Warrior(string);
    void displayStats() const override;
    void attack() override;
    void useSkill() override;
    void takeDamage(int)override;
};

class Rogue : public Player {
public:
    Rogue(string);
    void displayStats() const override;
    void attack() override;
    void useSkill() override;
    void takeDamage(int)override;
};
