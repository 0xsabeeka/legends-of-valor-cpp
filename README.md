# Legends of Valor C++

A C++ Object-Oriented Programming project that simulates a console-based RPG game.

This project demonstrates core OOP concepts through a role-playing game where the player can choose a class, move around a map, fight enemies, collect items, manage inventory, and save or load game progress.

## Project Overview

Legends of Valor is a text-based RPG game built in C++. The player can start a new game, choose a character class, explore a map, encounter enemies, collect treasures, use items, and save or load progress.

The game uses multiple classes to represent the player, enemies, inventory system, items, map, and battle system.

## Features

* Main menu system
* New game and load game options
* Character class selection
* Player classes: Warrior, Mage, and Rogue
* Map-based movement using W, A, S, D keys
* Enemy encounters
* Turn-based battle system
* Inventory management
* Item system with potions, weapons, armor, quest items, and buff items
* Treasure and safe zone events
* Locked areas requiring a key
* Save and load game functionality
* Shop menu for buying items

## OOP Concepts Used

* Classes and objects
* Inheritance
* Polymorphism
* Abstract classes
* Virtual functions
* Function overriding
* Encapsulation
* Composition
* Dynamic memory allocation
* Constructors and destructors
* Copy constructor
* Operator overloading
* File handling

## Technologies Used

* C++
* Visual Studio
* Console-based interface

## Project Structure

```text
legends-of-valor-cpp/
│
├── battle.cpp
├── battle.h
├── enemy.cpp
├── enemy.h
├── inventory.cpp
├── inventory.h
├── main.cpp
├── map.cpp
├── map.h
├── player.cpp
├── player.h
└── README.md
```

## How to Run

### Using Visual Studio

1. Open Visual Studio.
2. Create a new C++ Console project.
3. Add all `.cpp` and `.h` files to the project.
4. Build and run the project.

### Using g++

If using a compiler like g++, compile the files together:

```bash
g++ main.cpp battle.cpp enemy.cpp inventory.cpp map.cpp player.cpp -o legends_of_valor
```

Then run:

```bash
./legends_of_valor
```

## Controls

| Key | Action            |
| --- | ----------------- |
| W   | Move up           |
| A   | Move left         |
| S   | Move down         |
| D   | Move right        |
| I   | View inventory    |
| Q   | Quit current game |

## Note

This project uses console input/output and may require small changes depending on the compiler or operating system, especially because it uses console-specific functions such as `_getche()` and `system("pause")`.
