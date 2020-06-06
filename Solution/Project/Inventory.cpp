#include "Inventory.h"
#include <algorithm>

Inventory::Inventory(int row, int col)
{
  m_Slots.resize(row);

  for(int i = 0; i < col; ++i)
  {
    m_Slots[i].resize(col, -1);
  }

  m_Items.reserve(row * col);
}

/* This broken because when copying items over to the next inventory, I
 * couldn't tell what type of item i'm making a new instance of
Inventory::Inventory(const Inventory & other)
{
  m_Slots.resize(other.m_Slots.size());

  for (int i = 0; i < m_Slots.size(); ++i)
  {
    m_Slots[i].resize(other.m_Slots[i].size(),-1);
  }

  m_Items.reserve(m_Slots.size() * m_Slots[0].size());

  // each item
  for(Item *item : other.m_Items)
  {
    // find space
    int row, col;
    if (FindSpace(*item, row, col))
    {
      // for each space set the index
      for (int rowItem = row; rowItem < row + item->Height(); ++rowItem)
      {
        for (int colItem = col; colItem < col + item->Width(); ++colItem)
        {
          m_Slots[rowItem][colItem] = m_Items.size();
        }
      }

      // emplace item
      m_Items.emplace_back(new Item(*item));
    }
  }
}
*/

Inventory::Inventory(const std::vector<Item*>& items, int row, int col)
{
  m_Slots.resize(row);

  for (int i = 0; i < m_Slots.size(); ++i)
  {
    m_Slots[i].resize(col, -1);
  }

  m_Items.reserve(m_Slots.size() * m_Slots[0].size());

  // each item
  for (Item * item : items)
  {
    // find space
    int row, col;
    if (FindSpace(*item, row, col))
    {
      // for each space set the address
      for (int rowItem = row; rowItem < row + item->Height(); ++rowItem)
      {
        for (int colItem = col; colItem < col + item->Width(); ++colItem)
        {
          m_Slots[rowItem][colItem] = m_Items.size();
        }
      }

      // emplace item
      m_Items.emplace_back(item);
    }
  }
}

Inventory::~Inventory()
{
}

bool Inventory::AddItem(Item* item)
{
  // find space
  int row, col;
  if (FindSpace(*item, row, col))
  {
    // for each space set the address
    for (int rowItem = row; rowItem < row + item->Height(); ++rowItem)
    {
      for (int colItem = col; colItem <  col + item->Width(); ++colItem)
      {
        m_Slots[rowItem][colItem] = m_Items.size();
      }
    }

    // emplace item
    m_Items.emplace_back(item);

    return true;
  }

  return false;
}

void Inventory::RemoveItem(unsigned index)
{
  for (int row = 0; row < m_Slots.size(); ++row)
  {
    for (int col = 0; col < m_Slots[row].size(); ++col)
    {
      if(m_Slots[row][col] == index)
      {
        m_Slots[row][col] = -1;
      }
    }
  }

  delete m_Items[index];
  m_Items.erase(m_Items.begin() + index);

  for (int row = 0; row < m_Slots.size(); ++row)
  {
    for (int col = 0; col < m_Slots[row].size(); ++col)
    {
      if (m_Slots[row][col] > index)
      {
        m_Slots[row][col] -= 1;
      }
    }
  }
}

bool Inventory::FindSpace(const Item& item, int& rowReturn, int& colReturn) const
{
  for(int row = 0; row < m_Slots.size(); ++row)
  {
    for(int col = 0; col < m_Slots[row].size(); ++col)
    {
      // early out
      if (row + item.Height() > m_Slots.size()  || col + item.Width() > m_Slots[row].size())
      {
        continue;
      }

      // check if empty
      if(IsEmpty(row, col))
      {
        bool empty = true;

        // check for space
        for(int itemRow = row; itemRow < row + item.Height() && empty; ++itemRow)
        {
          for (int itemCol = col; itemCol < col + item.Width() && empty; ++itemCol)
          {
            if(!IsEmpty(itemRow, itemCol))
            {
              empty = false;
            }
          }
        }

        if(empty)
        {
          rowReturn = row;
          colReturn = col;
          return true;
        }
      }
    }
  }
  return false;
}

void Inventory::PrintFullInventory(PRINTSTYLE style) const
{
  int longestString = 4;

  for(const Item * item : m_Items)
  {
    if(longestString < item->Name().size())
    {
      longestString = item->Name().size();
    }
  }

  printf("Inventory: \n");
  printf("Column:");

  for (int col = 0; col < m_Slots[0].size(); ++col)
  {
    printf(" %.*i", longestString, col);
  }
  printf("\n");


  for(int row = 0; row < m_Slots.size(); ++row)
  {
    printf("Row %2i:", row);

    for(int col = 0; col < m_Slots.size(); ++col)
    {
      if(IsEmpty(row, col))
      {
        switch (style)
        {
          case PRINTSTYLE::NAME:
          {
            printf(" %*s", longestString, "null");
            break;
          }
          case PRINTSTYLE::INDEX:
          {
            printf(" %*i", longestString, -1);
            break;
          }
        }
      }
      else
      {
        switch (style)
        {
          case PRINTSTYLE::NAME:
          {
            printf(" %*s", longestString, m_Items[m_Slots[row][col]]->Name().c_str());
            break;
          }
          case PRINTSTYLE::INDEX:
          {
            printf(" %*i", longestString, m_Slots[row][col]);
          }
        }
      }

    }

    printf("\n");
  }

  printf("\n");
}

void Inventory::PrintItemsWithString(const std::string& string, PRINTROBUSTNESS robustness) const
{
  std::string tempSearch(string);

  for(std::string::iterator it = tempSearch.begin(); it != tempSearch.end(); ++it)
  {
    *it = std::tolower(*it);
  }

  printf("List of Items with the String \"%s\""":\n", tempSearch.c_str());

  for (const Item * item : m_Items)
  {
    // early out
    if(item->Name().size() < tempSearch.size())
    {
      continue;
    }

    std::string tempWord(item->Name());
    for (std::string::iterator it = tempWord.begin(); it != tempWord.end(); ++it)
    {
      *it = std::tolower(*it);
    }

    if(tempWord.find(tempSearch) != std::string::npos)
    {
      item->Print(robustness);
    }
  }

  printf("\n");
}

void Inventory::PrintIndexItems() const
{
  printf("\nIndex Items size: %i\n", m_Items.size());
  for(int i = 0; i < m_Items.size(); ++i)
  {
    printf("\t%i: %s\n", i, m_Items[i]->Name().c_str());
  }
}

bool Inventory::IsEmpty(int row, int col) const 
{
  return m_Slots[row][col] < 0;
}
