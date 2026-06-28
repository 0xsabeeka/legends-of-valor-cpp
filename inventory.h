#pragma once
#include <string>
using namespace std;

//base abstract class of item
class Item {
protected:
	string name, description;
	bool quest;
public:
	Item(string n, string d, bool q = false);
	virtual ~Item();
	virtual void useItem() = 0;

	//getters
	string getName() const;
	string getDescription() const;
	bool isQuestItem()const;
};


//derived item class: potion
class Potion :public Item {
public:
	Potion(string n, string d, bool=false);
	void useItem() override;
};


// derived item class: Weapon 
class Weapon : public Item {
public:
	Weapon(string n, string d, bool=false);
	void useItem() override;
};



// derived item class: Armor 
class Armor : public Item {
public:
	Armor(string n, string d, bool=false);
	void useItem() override;
};


//inventory class to contain items
class Inventory {
private:
	static const int maxItems = 10;
	Item* items[maxItems];
	int itemCount;
public:
	Inventory();
	~Inventory();

	void addItem(Item* newItem);
	void removeItem(int index);
	void showInventory()const;
	void useItem(int index);
	string getItemName(int index) const;


};



// derived item class: BuffItem
class BuffItem : public Item {
public:
	BuffItem(string n, string d, bool quest = false);
	void useItem() override;
};
