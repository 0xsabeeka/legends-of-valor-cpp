#pragma once
#include <string>
using namespace std;

class Enemy {
private:
    string name;
    int health;
    int attackPower;
    int defense;

public:
    Enemy(string n, int h, int ap, int def);
    void attack() const;
    void takeDamage(int dmg);
    int getHealth() const;
    bool isAlive() const;
    string getName() const;
    int getAttackPower() const;
};
