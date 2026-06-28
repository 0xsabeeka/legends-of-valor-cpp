#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Inventory.h"
#include "battle.h"
#include <string>
using namespace std;

class LegendOfValor; // forward declaration
struct Position {
    int x, y;
};

class Map {
private:
    static const int rows = 10;
    static const int cols = 10;
    char map[rows][cols];
    Position pos;
    Inventory* inventory;
    Player* player;
    LegendOfValor* game;
public:
    Map(Inventory* invPtr, Player* playerPtr, LegendOfValor* gamePtr);;
    void displayMap() const;
    bool movePlayer(char direction);
    bool checkCurrentCell(int x, int y);
    void giveRandomItem();
};
