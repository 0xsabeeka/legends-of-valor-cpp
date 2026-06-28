#include "Enemy.h"
#include <iostream>

Enemy::Enemy(string n, int h, int ap, int def) {
    name = n;
    health = h;
    attackPower = ap;
    defense = def;
}


void Enemy::attack() const {
    cout << name << " attacks fiercely!\n";
}

void Enemy::takeDamage(int dmg) {
    int actualDamage = dmg - defense;
    if (actualDamage < 0) 
        actualDamage = 0;

    health -= actualDamage;

    cout << name << " took " << actualDamage << " damage! (Remaining HP: " << health << ")\n";
}

int Enemy::getHealth() const {
    return health;
}

bool Enemy::isAlive() const {
    return health > 0;
}

string Enemy::getName() const {
    return name;
}

int Enemy::getAttackPower() const {
    return attackPower;
}
