#include "Map.h"
#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for seeding random generator
using namespace std;

// Constructor
Map::Map(Inventory* invPtr, Player* playerPtr, LegendOfValor* gamePtr) {
    inventory = invPtr;
    player = playerPtr;
    game = gamePtr;
    srand(time(0));

    // Initialize map with empty ground
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            map[i][j] = '.';
        }
    }

    // Place player at top-left
    pos.x = 0;
    pos.y = 0;
    map[pos.x][pos.y] = 'P';

    // Lambda to place special symbols
    auto placeRandom = [&](char symbol, int count) {
        while (count > 0) {
            int x = rand() % rows;
            int y = rand() % cols;

            if (map[x][y] == '.') {
                map[x][y] = symbol;
                count--;
            }
        }
        };

    placeRandom('E', 5); // Enemies
    placeRandom('T', 5); // Treasures
    placeRandom('S', 3); // Safe Zones
    placeRandom('L', 2); // Locked Areas
}

void Map::displayMap() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << " " << map[i][j] << " ";
        }
        cout << endl;
    }
}

bool Map::movePlayer(char direction) {
    int oldx = pos.x;
    int oldy = pos.y;
    int newx = pos.x;
    int newy = pos.y;

    if (direction == 'w' || direction == 'W') {
        if (newx > 0) 
            newx--;
        else {
            cout << "Cannot move up, boundary reached!\n";
            system("pause");
            return false;
        }
    }
    else if (direction == 's' || direction == 'S') {
        if (newx < rows - 1) 
            newx++;
        else {
            cout << "Cannot move down, boundary reached!\n";
            system("pause");
            return false;
        }
    }
    else if (direction == 'a' || direction == 'A') {
        if (newy > 0) 
            newy--;
        else {
            cout << "Cannot move left, boundary reached!\n";
            system("pause");
            return false;
        }
    }
    else if (direction == 'd' || direction == 'D') {
        if (newy < cols - 1) 
            newy++;
        else {
            cout << "Cannot move right, boundary reached!\n";
            system("pause");
            return false;
        }
    }
    else {
        cout << "Invalid move! Use W/A/S/D keys only.\n";
        system("pause");
        return false;
    }

    // Check cell interaction (enemies, locked, etc.)
    if (!checkCurrentCell(newx, newy)) {
        cout << "Movement blocked.\n";
        system("pause");
        return false;
    }

    // Update player position
    map[oldx][oldy] = '.';
    pos.x = newx;
    pos.y = newy;
    map[pos.x][pos.y] = 'P';
    return true;
}

bool Map::checkCurrentCell(int x, int y) {
    char currentCell = map[x][y];

    switch (currentCell) {
    case 'E': {
        cout << "\nYou encountered an Enemy! Prepare to fight!\n";
        
        Enemy enemy("Goblin", 30, 10, 2);
        game->battle(enemy);
        map[x][y] = '.';
        system("pause");
        return true;
    }

    case 'T': {
        cout << "\nYou found a Treasure!\n";
        giveRandomItem();
        map[x][y] = '.';
        system("pause");
        return true;
    }

    case 'S': {
        cout << "\nYou found a Safe Zone! Healing some health.\n";
      
        map[x][y] = '.';
        player->heal(30);
        system("pause");
        return true;
    }

    case 'L': {
        cout << "\nThis area is Locked! ";

        // Check inventory for "Silver Key"
        bool hasKey = false;
        for (int i = 0; i < 10; ++i) {
            if (inventory->getItemName(i) == "Silver Key") {
                hasKey = true;
                inventory->removeItem(i); // remove key
                break;
            }
        }

        if (hasKey) {
            cout << "You used the Silver Key to unlock it!\n";
            map[x][y] = '.';  // unlock
            system("pause");
            return true;
        }
        else {
            cout << "You don't have a key.\n";
            system("pause");
            return false;
        }
    }

    case '.':
        return true;

    default:
        cout << "\nUnknown location.\n";
        return true;
    }
}

void Map::giveRandomItem() {
    int type = rand() % 5;
    Item* item = nullptr;

    switch (type) {
    case 0:
        item = new Potion("Health Potion", "Restores 50 HP");
        break;
    case 1:
        item = new Weapon("Steel Sword", "A strong melee weapon");
        break;
    case 2:
        item = new Armor("Iron Armor", "Reduces damage");
        break;
    case 3:
        item = new Potion("Silver Key", "Opens a locked area", true); // Quest item
        break;
    case 4:
        item = new BuffItem("Strength Potion", "Boosts your attack for the next battle");   
        break;

    }

    if (item) {
        inventory->addItem(item);
    }
}
