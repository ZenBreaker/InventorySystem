#ifndef SWORD_H
#define SWORD_H

#include "Item.h"
class Sword : public Item
{
public:
  Sword(std::string name, std::string description, float value) :
  Item{name, description, 2, 3, value}
  {
  }

  void Print(PRINTROBUSTNESS robustness = NAMES) const override;
};

#endif
