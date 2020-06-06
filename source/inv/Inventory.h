#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include "Item.h"

enum PRINTSTYLE
{
  NAME,
  INDEX
};

class Inventory
{
public:
  Inventory(int row, int col);
  Inventory(const Inventory& other) = delete;
  Inventory(const std::vector<Item*>& items, int row = 1, int col = 1);
  ~Inventory();
  bool AddItem(Item * item);
  void RemoveItem(unsigned index);
  bool FindSpace(const Item & item, int& rowReturn, int& colReturn) const;
  void PrintFullInventory(PRINTSTYLE style = NAME) const;
  void PrintItemsWithString(const std::string& string, PRINTROBUSTNESS robustness = NAMES) const;
  void PrintIndexItems() const;
  int NumberOfItems()const { return m_Items.size(); };
private:
  bool IsEmpty(int row, int col) const;
  std::vector<std::vector<int>> m_Slots;
  std::vector<Item*> m_Items;
};

#endif /* INVENTORY_H */