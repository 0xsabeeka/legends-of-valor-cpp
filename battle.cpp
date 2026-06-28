#include "battle.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <conio.h>  //for _getche
using namespace std;
void input(int& inpt, int min = INT_MIN, int max = INT_MAX);
void inputs(string& str, size_t minLen = 1, size_t maxLen = 100);
// Constructor
LegendOfValor::LegendOfValor() {
    player = nullptr;
    map = nullptr;
    isRunning = false;
    logIndex = 0; 
}


// Destructor
LegendOfValor::~LegendOfValor() {
    delete player;
    delete map;
}

// Starts new game
void LegendOfValor::startNewGame() {
    string name;
    int ch;

    cout << "\n===== New Game =====\n";
    cout << "Enter your name: ";
    inputs(name);

    cout << "\nChoose your class:\n";
    cout << "1. Warrior\n";
    cout << "2. Mage\n";
    cout << "3. Rogue\n";
    input(ch, 1, 3);

    switch (ch) {
    case 1:
        player = new Warrior(name);
        playerClassName = "Warrior";
        break;
    case 2:
        player = new Mage(name);
        playerClassName = "Mage";
        break;
    case 3:
        player = new Rogue(name);
        playerClassName = "Rogue";
        break;
    }


    map = new Map(&inventory, player, this);
    isRunning = true;

    cout << "\nWelcome " << player->getName() << "! Your journey begins...\n";
    play();
}

// Main menu loop
void LegendOfValor::mainMenu() {
    int choice;

    while (true) {
        system("CLS");
        cout << "===== Legends of Valor =====\n";
        cout << "1. Start New Game\n";
        cout << "2. Load Game\n";
        cout << "3. Shop (Buy Item)\n";
        cout << "4. View Player Stats\n";
        cout << "5. View Inventory\n";
        cout << "6. Quit\n";
        cout << "Enter choice: ";
        input(choice, 1, 6);

        switch (choice) {
        case 1:
            startNewGame();
            break;
        case 2:
            loadGame();
            break;
        case 3:
            shopMenu();
            break;
        case 4:{
            if (player != nullptr) {
                player->displayStats();
            }
            else {
                cout << "No player created or loaded yet.\n";
            }
            break;
        }
        case 5:
            if (player != nullptr) {
                inventory.showInventory();
            }
            else {
                cout << "No player created or loaded yet.\n";
            }
            break;
        case 6: 
            quit(); 
            return;
        }
        system("pause");
    }
}

// Game loop
void LegendOfValor::play() {
    char move;
    while (isRunning) {
        system("CLS");
        map->displayMap();
        cout << "\nUse W A S D to move, I to view inventory, Q to quit.";
        move = _getche();
        cout << endl;


        if (move == 'q' || move == 'Q') {
            cout << "Do you want to save your game before quitting? (y/n): ";
            char save;
            cin >> save;
            if (save == 'y' || save == 'Y') 
                saveGame();
            system("pause");
            isRunning = false;
            break;
        }
        if (move == 'i' || move == 'I') {
            inventory.showInventory();
            system("pause");
            continue;
        }


        map->movePlayer(move);  // Events are handled inside map
        
    }
}


// Battle logic
void LegendOfValor::battle(Enemy& enemy) {
    cout << "\nBattle Started: " << player->getName() << " vs " << enemy.getName() << "!\n";
    logIndex = 0; // Start fresh

    bool defending = false;

    while (player->getHealth() > 0 && enemy.isAlive()) {
        cout << "\nYour Turn - Choose Action:\n";
        cout << "1. Attack\n";
        cout << "2. Use Skill\n";
        cout << "3. Defend\n";
        cout << "4. Use Item\n";
        cout << "Choice: ";
        int choice;
        input(choice, 1, 4);

        switch (choice) {
        case 1:
            player->attack();
            enemy.takeDamage(10);
            battleLog[logIndex++] = "Player attacked enemy for 10 damage.";
            defending = false;
            break;
        case 2:
            player->useSkill();
            enemy.takeDamage(15);
            battleLog[logIndex++] = "Player used skill and dealt 15 damage.";
            defending = false;
            break;
        case 3:
            cout << player->getName() << " takes a defensive stance!\n";
            battleLog[logIndex++] = "Player is defending.";
            defending = true;
            break;
        case 4:
            inventory.showInventory();
            cout << "Enter item number to use: ";
            int itemChoice;
            input(itemChoice, 1, 10);
            inventory.useItem(itemChoice - 1);
            battleLog[logIndex++] = "Player used an item from inventory.";
            defending = false;
            break;
        }

        if (!enemy.isAlive()) {
            cout << "\nYou defeated " << enemy.getName() << "!\n";
            battleLog[logIndex++] = "Enemy was defeated.";
            *player = *player + 20; //using overloaded + (adding xp)
            player->levelUp();  //level up after defating enemy ////////////
            break;
        }

        enemy.attack();
        int damage = enemy.getAttackPower();
        if (defending) {
            damage /= 2;
            cout << "(Defending! Damage reduced to " << damage << ")\n";
        }

        player->takeDamage(damage);
        battleLog[logIndex++] = "Enemy attacked player for " + to_string(damage) + " damage.";

        if (player->getHealth() <= 0) {
            cout << player->getName() << " was defeated!\n";
            battleLog[logIndex++] = "Player was defeated by the enemy.";
            isRunning = false;
            break;
        }
    }

    //show battle history after fight ends
    cout << "\n\tBATTLE HISTORY\n";
    for (int i = 0; i < logIndex; i++) {
        cout << "- " << battleLog[i] << endl;
    }
    logIndex = 0; // Clear log for next fight
}


// Save game
void LegendOfValor::saveGame() {
    ofstream file("save.txt"); // create the file
    if (!file) {
        cout << "Error: Could not open file to save.\n";
        return;
    }

    // Save basic player info
    file << player->getName() << endl;
    file << player->getHealth() << endl;
    file << player->getXP() << endl;
    file << playerClassName << endl;

    // Save inventory item names
    for (int i = 0; i < 10; i++) {
        string itemName = inventory.getItemName(i);
        if (!itemName.empty()) {
            file << "ITEM:" << itemName << endl;
        }
    }

    file.close();
    cout << "Game saved successfully!\n";
}


// Load game
void LegendOfValor::loadGame() {
    ifstream file("save.txt");
    if (!file) {
        cout << "No saved game found.\n";
        return;
    }

    string name, className, line;
    int health, xp;

    // Read player info
    getline(file, name);
    file >> health;
    file >> xp;
    file.ignore(); // move to next line
    getline(file, className); // get class name line

    // Create correct player based on class
    if (className == "Warrior") {
        player = new Warrior(name);
    }
    else if (className == "Mage") {
        player = new Mage(name);
    }
    else if (className == "Rogue") {
        player = new Rogue(name);
    }
    else {
        cout << "Error: Invalid class in save file.\n";
        return;
    }

    playerClassName = className;
    player->setHealth(health);
    player->setXP(xp);

    // Load inventory items
    while (getline(file, line)) {
        if (line.rfind("ITEM:", 0) == 0) {  //checks if the line starts with the word "ITEM:"
            string itemName = line.substr(5);   //starts from the 5th character
            Item* newItem = nullptr;

            // Match by name — create correct item type
            if (itemName == "Health Potion") {
                newItem = new Potion(itemName, "Restores 50 HP");
            }
            else if (itemName == "Steel Sword") {
                newItem = new Weapon(itemName, "A strong melee weapon");
            }
            else if (itemName == "Iron Armor") {
                newItem = new Armor(itemName, "Reduces incoming damage");
            }
            else if (itemName == "Strength Potion") {
                newItem = new BuffItem(itemName, "Boosts attack temporarily");
            }
            else if (itemName == "Silver Key") {
                newItem = new Potion(itemName, "Opens locked areas", true); // Quest item
            }
            else {
                newItem = new Potion(itemName, "Generic loaded item"); // fallback
            }

            inventory.addItem(newItem);
        }
    }

    file.close();

    cout << "\nGame loaded successfully!\n";
    cout << "Player: " << name << " (" << className << ")\n";

    // Re-create map and start playing again
    map = new Map(&inventory, player, this);
    isRunning = true;
    play();
}


// Quit and cleanup
void LegendOfValor::quit() {
    delete player;
    delete map;
    player = nullptr;
    map = nullptr;
    isRunning = false;

    cout << "Thanks for playing Legends of Valor!\n";
}


void LegendOfValor::shopMenu() {
    int choice;
    Item* newItem = nullptr;

    cout << "\n===== SHOP MENU =====\n";
    cout << "1. Health Potion - Free\n";
    cout << "2. Steel Sword - Free\n";
    cout << "3. Exit Shop\n";
    cout << "Enter your choice: ";
    input(choice, 1, 3);

    switch (choice) {
    case 1:
        newItem = new Potion("Health Potion", "Restores 50 HP");
        break;
    case 2:
        newItem = new Weapon("Steel Sword", "A strong melee weapon");
        break;
    case 3:
        cout << "Leaving shop...\n";
        return;
    }

    if (newItem) {
        inventory.addItem(newItem);
    }

    system("pause");
}

