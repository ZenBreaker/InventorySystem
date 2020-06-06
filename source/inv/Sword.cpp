#include "Sword.h"

void Sword::Print(PRINTROBUSTNESS robustness) const
{
  switch (robustness)
  {
    case PRINTROBUSTNESS::NAMES:
    {
      printf("Name: %s\n", Name().c_str());
      break;
    }
    case PRINTROBUSTNESS::BRIEF:
    {
      printf("Name: %s\n", Name().c_str());
      printf("\tItem Value: %i\n", Value());
      break;
    }
    case PRINTROBUSTNESS::FULL_DESCRIPTION:
    {
      printf("Name: %s\n", Name().c_str());
      printf("\tDescription: %s\n", Description().c_str());
      printf("\tItem Value: %i\n", Value());
      printf("\tDimension Width: %i \n", Width());
      printf("\tDimension Height: %i \n", Height());

      printf("\tPicture:\n");
      printf("\t\t*************^*************\n");
      printf("\t\t************/*\\************\n");
      printf("\t\t***********/***\\***********\n");
      printf("\t\t**********/*****\\**********\n");
      printf("\t\t*********|*******|*********\n");
      printf("\t\t*********|*******|*********\n");
      printf("\t\t*********|*******|*********\n");
      printf("\t\t*********|*******|*********\n");
      printf("\t\t*********|*******|*********\n");
      printf("\t\t*********|*******|*********\n");
      printf("\t\t*********|*******|*********\n");
      printf("\t\t*********|*******|*********\n");
      printf("\t\t**-----------------------**\n");
      printf("\t\t************|*|************\n");
      printf("\t\t************|*|************\n");
      printf("\t\t************\\*/************\n");
      printf("\t\t*************O*************\n");
      break;
    }
  }
}
