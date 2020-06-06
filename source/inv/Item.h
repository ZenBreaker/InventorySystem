#ifndef ITEM_H
#define ITEM_H

#include <string>

enum PRINTROBUSTNESS
{
  NAMES = 0,
  BRIEF,
  FULL_DESCRIPTION
};

class Item
{
public:
  Item(std::string name = "", std::string description = "", int width = 1, int height = 1, float value = 0) :
    m_Name(name),
    m_Description(description),
    m_Height(height),
    m_Width(width),
    m_Value(value)
  {}

  Item(const Item& other) = default;

  virtual ~Item() = default;

  std::string& Name() { return m_Name; }
  std::string const& Name() const { return m_Name; }
  std::string& Description() { return m_Description; }
  std::string const& Description() const { return m_Description; }
  int& Height() { return m_Height; }
  const int& Height() const { return m_Height; }
  int& Width() { return m_Width; }
  const int& Width() const { return m_Width; }
  float& Value() { return m_Value; }
  const float& Value() const { return m_Value; }

  virtual void Print(PRINTROBUSTNESS robustness = NAMES) const;
private:
  std::string m_Name;
  std::string m_Description;
  int m_Height;
  int m_Width;
  float m_Value;
};

#endif /* ITEM_H */