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
      printf("\tItem Value: %i\n", m_Value);
      break;
    }
    case PRINTROBUSTNESS::FULL_DESCRIPTION:
    {
      printf("Name: %s\n", m_Name.c_str());
      printf("\tDescription: %s\n", m_Description.c_str());
      printf("\tItem Value: %f\n", m_Value);
      printf("\tDimension Width: %i \n", m_Width);
      printf("\tDimension Height: %i \n", m_Height);
      break;
    }
  }
}
