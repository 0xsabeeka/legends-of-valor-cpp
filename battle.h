#pragma once
#include "Player.h"
#include "Inventory.h"
#include "Enemy.h"
#include <string>

class Map;  //forward declaration

class LegendOfValor {
private:
    Player* player;
    Inventory inventory;
    Map* map;
    bool isRunning;
    string playerClassName;
    //Battle history
    string battleLog[100];
    int logIndex;

public:
    LegendOfValor();
    ~LegendOfValor();

    void battle(Enemy& enemy);
    void startNewGame();
    void mainMenu();
    void play();
    void saveGame();
    void loadGame();
    void quit();
    void shopMenu();


};
