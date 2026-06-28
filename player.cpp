#include "Player.h"
#include <iostream>
using namespace std;

// Player class definitions
int Player::playerCount = 0;

Player::Player(string n) : name(n), level(1), xp(0) {
    
    health = mana = attackPower = defense=0;
    playerCount++;
}

Player::~Player() {
    playerCount--;
}

Player::Player(const Player& other) 
    : name(other.name), health(other.health), mana(other.mana),
    attackPower(other.attackPower), defense(other.defense),
    level(other.level), xp(other.xp) {
    playerCount++;
    cout << "Player '" << name << "' copied successfully.\n";
}


string Player::getName() const {
    return name;
}

int Player::getHealth() const {
    return health;
}

int Player::getPlayerCount() {
    return playerCount;
}

int Player::getXP()const {
    return xp;
}

void Player::addXP(int amount) {
    xp += amount;
    cout << name << " gained " << amount << " XP! (Total XP: " << xp << ")\n";

    if (xp >= 100) {
        levelUp();
        xp = 0; // reset XP after leveling up
    }
}

void Player::setHealth(int h) {
    health = h;
}

void Player::setXP(int x) {
    xp = x;
}

void Player::levelUp() {
    level++;
    health += 20;
    mana += 10;
    attackPower += 5;
    defense += 2;

    cout << "\n*** " << name << " leveled up to Level " << level << "! ***\n";
    cout << "Stats improved: +20 HP, +10 Mana, +5 Attack, +2 Defense\n";
}

void Player::heal(int amount) {
    health += amount;
    if (health > 200)
        health = 200;
    cout << name << " healed by " << amount << " HP! (Current HP: " << health << ")\n";
}

Player& Player::operator+(int xp) {
    this->addXP(xp); 
    return *this;
}





// Mage class defintions
Mage::Mage(string n) : Player(n) {
    health = 100;
    mana = 120;
    attackPower = 10;
    defense = 5;
}

void Mage::displayStats() const {
    cout << "\n\tPLAYER STATS\n";
    cout << "________________________\n";
    cout << "Class: Mage\n";
    cout << "Name: " << name << endl;
    cout << "Health: " << health << "\tMana: " << mana << endl;
    cout << "Attack: " << attackPower << "\tDefense: " << defense << endl;
    cout << "Level: " << level << "\tXP: " << xp << endl;
    cout << "_________________________\n";
}

void Mage::attack() {
    cout << name << " casts a basic firebolt!\n";
}

void Mage::useSkill() {
    if (mana >= 20) {
        mana -= 20;
        cout << name << " uses Fireball! (Mana left: " << mana << ")\n";
    }
    else {
        cout << name << " doesn't have enough mana to use Fireball!\n";
    }
}

void Mage::takeDamage(int dmg) {
    int actual = dmg - defense;
    if (actual < 0) 
        actual = 0;
    health -= actual;
    if (health < 0) 
        health = 0;
    cout << name << " took " << actual << " damage! (Remaining HP: " << health << ")\n";
}




// Warrior class definitions
Warrior::Warrior(string n) : Player(n) {
    health = 150;
    mana = 50;
    attackPower = 20;
    defense = 15;
}

void Warrior::displayStats() const {
    cout << "\n\tPLAYER STATS\n";
    cout << "_________________________\n";
    cout << "Class: Warrior\n";
    cout << "Name: " << name << endl;
    cout << "Health: " << health << "\tMana: " << mana << endl;
    cout << "Attack: " << attackPower << "\tDefense: " << defense << endl;
    cout << "Level: " << level << "\tXP: " << xp << endl;
    cout << "_________________________\n";
}

void Warrior::attack() {
    cout << name << " swings a heavy sword!\n";
}

void Warrior::useSkill() {
    if (mana >= 10) {
        mana -= 10;
        cout << name << " uses Shield Bash! (Mana left: " << mana << ")\n";
    }
    else {
        cout << name << " doesn't have enough mana to use Shield Bash!\n";
    }
}

void Warrior::takeDamage(int dmg) {
    int actual = dmg - defense;
    if (actual < 0)
        actual = 0;
    health -= actual;
    if (health < 0)
        health = 0;
    cout << name << " took " << actual << " damage! (Remaining HP: " << health << ")\n";
}



// Rogue class definitions
Rogue::Rogue(string n) : Player(n) {
    health = 120;
    mana = 60;
    attackPower = 15;
    defense = 10;
}

void Rogue::displayStats() const {
    cout << "\n\tPLAYER STATS\n";
    cout << "_________________________\n";
    cout << "Class: Rogue\n";
    cout << "Name: " << name << endl;
    cout << "Health: " << health << "\tMana: " << mana << endl;
    cout << "Attack: " << attackPower << "\tDefense: " << defense << endl;
    cout << "Level: " << level << "\tXP: " << xp << endl;
    cout << "_________________________\n";
}

void Rogue::attack() {
    cout << name << " quickly strikes with daggers!\n";
}

void Rogue::useSkill() {
    if (mana >= 15) {
        mana -= 15;
        cout << name << " uses Shadow Strike! (Mana left: " << mana << ")\n";
    }
    else {
        cout << name << " doesn't have enough mana to use Shadow Strike!\n";
    }
}

void Rogue::takeDamage(int dmg) {
    int actual = dmg - defense;
    if (actual < 0)
        actual = 0;
    health -= actual;
    if (health < 0)
        health = 0;
    cout << name << " took " << actual << " damage! (Remaining HP: " << health << ")\n";
}