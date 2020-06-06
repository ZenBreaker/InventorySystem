#ifndef ITEM_H
#define ITEM_H

#include <string>

enum PRINTROBUSTNESS
{
  NAMES = 0,
  BRIEF,
  FULL_DESCRIPTION
};

enum ItemMasks
{
  Weapon = 0x8,
  Helm = 0x4, 
  Chest = 0x2, 
  Legs = 0x1,
  None = 0x0
};

class Item
{
public:
  Item(std::string name = "", int width = 1, int height = 1) :
    m_Name(name),
    m_Height(height),
    m_Width(width),
    m_Mask(ItemMasks::None)
  {}

  Item(const Item& other) = default;

  virtual ~Item() = default;

  std::string& Name() { return m_Name; }
  std::string const& Name() const { return m_Name; }
  int& Height() { return m_Height; }
  const int& Height() const { return m_Height; }
  int& Width() { return m_Width; }
  const int& Width() const { return m_Width; }
  ItemMasks& Mask() { return m_Mask; }
  const ItemMasks& Mask() const { return m_Mask; }

  virtual void Print(PRINTROBUSTNESS robustness = NAMES) const;
private:
  std::string m_Name;
  int m_Height;
  int m_Width;
  ItemMasks m_Mask;
};

#endif /* ITEM_H */