#include "inventory.h"
#include <iostream>
using namespace std;

//item class definitions
Item::Item(string n, string d, bool q) {
	name = n;
	description = d;
	quest = q;
}
Item::~Item() {

}
string Item::getName() const {
	return name;
}

string Item::getDescription() const {
	return description;
}

bool Item::isQuestItem()const {
	return quest;
}

//Potion class definitions
Potion::Potion(string n, string d, bool quest) : Item(n, d, quest) {}
void Potion::useItem() {
	cout << "You used " << name << "! " << description << endl;
}



//Weapon class Definitions
Weapon::Weapon(string n, string d, bool quest) : Item(n, d, quest) {}

void Weapon::useItem() {
	cout << "You equipped " << name << "! " << description << endl;
}


//Armor Definitions
Armor::Armor(string n, string d, bool quest) : Item(n, d, quest) {}

void Armor::useItem() {
	cout << "You wore " << name << "! " << description << endl;
}


//inventory class definitions
Inventory::Inventory() {
	itemCount = 0;
	for (int i = 0; i < maxItems; i++) {
		items[i] = nullptr;
	}
}

Inventory::~Inventory() {
	for (int i = 0; i < maxItems; i++) {
		if (items[i] != nullptr) {
			delete items[i];
			items[i] = nullptr;
		}
	}
}

void Inventory::addItem(Item* newItem) {
	// Check for duplicates by name
	for (int i = 0; i < itemCount; i++) {
		if (items[i]->getName() == newItem->getName()) {
			cout << "Item '" << newItem->getName() << "' is already in your inventory. Cannot add duplicate.\n";
			delete newItem; // Prevent memory leak
			return;
		}
	}

	if (itemCount >= maxItems) {
		cout << "Inventory is full! Cannot add more items\n";
		return;
	}
	items[itemCount] = newItem;
	itemCount++;
	cout << "Added " << newItem->getName() << " to inventory\n";
}

void Inventory::removeItem(int index) {
	if (index < 0 || index >= itemCount) {
		cout << "Invalid Item Number\n";
		return;
	}

	if (items[index]->isQuestItem()) {
		cout << "Cannot remove '" << items[index]->getName() << "'. It is a quest item!\n";
		return;
	}

	cout << "Removing " << items[index]->getName() << " from inventory\n";
	delete items[index];

	for (int i = index; i < itemCount - 1; i++) {
		items[i] = items[i + 1];
	}

	items[itemCount - 1] = nullptr;
	itemCount--;
}



void Inventory::showInventory() const {
	cout << "\n\tINVENTORY\n";
	cout << "-----------------------------------------\n";
	if (itemCount == 0) {
		cout << "Inventory is empty.\n";
	}
	else {
		for (int i = 0; i < itemCount; i++) {
			cout << i + 1 << ". " << items[i]->getName()<< " - " << items[i]->getDescription() << endl;
		}
	}
	cout << "-----------------------------------------\n";
	cout << "Total Items: " << itemCount << " / "<<maxItems<<"\n";
}

void Inventory::useItem(int index) {
	if (index < 0 || index >= itemCount) {
		cout << "Invalid item number!\n";
		return;
	}

	items[index]->useItem();

	if (!items[index]->isQuestItem()) {
		removeItem(index);
	}
	else {
		cout << "Quest item was used, but it cannot be removed.\n";
	}
}

string Inventory::getItemName(int index) const {
	if (index < 0 || index >= itemCount || items[index] == nullptr)
		return "";
	return items[index]->getName();
}


// BuffItem class definitions
BuffItem::BuffItem(string n, string d, bool quest) : Item(n, d, quest) {}

void BuffItem::useItem() {
	cout << "You used " << name << "! " << description << endl;
	cout << "Temporary buff applied! (e.g., Attack increased by 10)\n";
}
