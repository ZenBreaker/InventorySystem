#include "Item.h"

void Item::Print(PRINTROBUSTNESS robustness) const
{
  switch (robustness)
  {
    case PRINTROBUSTNESS::NAMES:
    {
      printf("Name: %s\n", m_Name.c_str());
      break;
    }
    case PRINTROBUSTNESS::BRIEF:
    {
      printf("Name: %s\n", m_Name.c_str());
      break;
    }
    case PRINTROBUSTNESS::FULL_DESCRIPTION:
    {
      printf("Name: %s\n", m_Name.c_str());
      printf("\tDimension Width: %i \n", m_Width);
      printf("\tDimension Height: %i \n", m_Height);
      break;
    }
  }
}
