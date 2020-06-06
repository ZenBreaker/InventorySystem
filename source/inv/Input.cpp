#include "Input.h"


#include <iostream>
#include <vector>

#include "Inventory.h"
#include "Item.h"
#include "Sword.h"

void Test()
{
  Item* item0 = new Item();
  Item* item1 = new Item("Scroll", "This is a scroll");
  Item* item2 = new Item("Health Pot", "This is a Health Potion", 1, 1, 2);
  Sword* item3 = new Sword("Dagger", "This is the first Sword", 4);

  std::vector<Item*>itemset0;
  itemset0.emplace_back(item1);
  itemset0.emplace_back(item2);
  itemset0.emplace_back(item3);

  printf("printing item 0... (default constructor)\n");
  item0->Print(PRINTROBUSTNESS::FULL_DESCRIPTION);

  printf("\nprinting item 1... (name)\n");
  item1->Print(PRINTROBUSTNESS::NAMES);

  printf("\nprinting item 2... (name, Description, width, height, value) \n");
  item2->Print(PRINTROBUSTNESS::BRIEF);

  printf("\nprinting item 3... (name, Description, value) \n");
  item3->Print(PRINTROBUSTNESS::FULL_DESCRIPTION);

  printf("\nprinting inventory 0... ((row, col) constructor)\n");
  Inventory inv0(10, 10);
  inv0.PrintFullInventory();

  printf("\nprinting inventory 1... ((items, row, col) constructor)\n");
  Inventory inv1(itemset0, 10, 10);
  inv1.PrintFullInventory();
  inv1.PrintItemsWithString("L");

  printf("\nprinting inventory 2... ((row, col) constructor)\n");
  Inventory inv2(10, 10);
  inv2.PrintFullInventory();

  Sword* item4 = new Sword("Excalibur", "This is the second Sword", 9);
  printf("\nprinting item 4... (name, Description, value) \n");
  item4->Print(PRINTROBUSTNESS::FULL_DESCRIPTION);
  Item* item5 = new Item("Scroll", "This is the second Scroll", 1);
  printf("\nprinting item 5... (name, Description, value) \n");
  item5->Print(PRINTROBUSTNESS::FULL_DESCRIPTION);
  Sword* item6 = new Sword("Excalibur", "This is the third Sword", 1);
  printf("\nprinting item 6... (name, Description, value) \n");
  item6->Print(PRINTROBUSTNESS::FULL_DESCRIPTION);

  printf("\nprinting inventory 2... (add item) x 3\n");
  inv2.AddItem(item4);
  inv2.AddItem(item5);
  inv2.AddItem(item6);

  inv2.PrintFullInventory();
  inv2.PrintFullInventory(PRINTSTYLE::INDEX);
  inv2.PrintItemsWithString("S");

  printf("\nprinting inventory 2... (remove item)\n");
  inv2.RemoveItem(1);
  inv2.PrintFullInventory();
  inv2.PrintFullInventory(PRINTSTYLE::INDEX);
  inv2.PrintIndexItems();
}

void InputRemoveItem(Inventory& inventory)
{
  printf("\nWhich item would you like to remove?\n");

  inventory.PrintIndexItems();

  int input;
  std::cin >> input;

  if(input >= 0 && input < inventory.NumberOfItems())
  {
    inventory.RemoveItem(input);

    inventory.PrintFullInventory(NAME);
  }
  else
  {
    printf("\nInvalid item index\n");
  }
}


void InputPrintInventory(Inventory& inventory)
{
  printf("\nHow would you like the items printed?\n");
  printf("\t0: Names\n");
  printf("\t1: Index\n");

  int input;
  std::cin >> input;

  PRINTSTYLE robust = NAME;

  switch (input)
  {
  case 0:
  {
    robust = NAME;
    break;
  }
  case 1:
  {
    robust = INDEX;
    break;
  }
  }

  inventory.PrintFullInventory(robust);
}

void InputPrintItems(Inventory& inventory)
{
  printf("\nWhat would you like to look for?\n");
  std::string searchString;
  std::cin >> searchString;

  printf("\nHow would you like the items printed?\n");
  printf("\t0: Names\n");
  printf("\t1: Brief\n");
  printf("\t2: Full Descriptions\n");

  int input;
  std::cin >> input;

  PRINTROBUSTNESS robust;

  switch (input)
  {
    case 0:
    {
      robust = NAMES;
      break;
    }
    case 1:
    {
      robust = BRIEF;
      break;
    }
    case 2:
    {
      robust = FULL_DESCRIPTION;
      break;
    }
  }

  inventory.PrintItemsWithString(searchString, robust);

}

void InputAddSword(Inventory& inventory)
{
  printf("\nPlease Following Format: (name description value)\n");
  printf("Space Separated\n");

  std::string name;
  std::cin >> name;

  std::string description;
  std::cin >> description;

  float value;
  std::cin >> value;

  inventory.AddItem(new Sword(name, description, value));
}

void InputAddGenericItem(Inventory& inventory)
{
  printf("\nPlease Following Format: (name description width height value)\n");
  printf("Space Separated\n");
  
  std::string name;
  std::cin >> name;

  std::string description;
  std::cin >> description;

  int width;
  std::cin >> width;

  int height;
  std::cin >> height;

  float value;
  std::cin >> value;

  inventory.AddItem(new Item(name, description, width, height, value));
}

void InputAddItem(Inventory & inventory)
{
  printf("\nAdding new Item:\n");
  printf("\t0: Add Generic Item\n");
  printf("\t1: Add Sword\n");

  int input;
  std::cin >> input;

  switch (input)
  {
    case 0:
    {
      InputAddGenericItem(inventory);
      break;
    }
    case 1:
    {
      InputAddSword(inventory);
      break;
    }
    case 2:
    {
      break;
    }
    default:
    {
      printf("\nInvalid Input\n");
      break;
    }
  }

  inventory.PrintFullInventory(NAME);
}

void InputRun()
{
  printf("\nThere is very minimal error checking\n");

  printf("\nWhat would you like to do?\n");
  printf("\t0: Independent Test\n");
  printf("\t1: Create Your Inventory\n");

  int input;
  std::cin >> input;

  switch (input)
  {
    case 0:
    {
      Test();

      printf("\nEnter any character to continue\n");
      std::cin >> input;
      break;
    }
    case 1:
    {
      printf("\nInput How Big of an inventory: (rows, columns)\n");
      printf("(Please use a relatively low number)\n");

      int row;
      std::cin >> row;

      int col;
      std::cin >> col;

      Inventory inventory(row, col);

      bool IsRunning = true;

      do
      {
        printf("\nInput From the Following:\n");
        printf("\t0: Add Item\n");
        printf("\t1: Remove Item\n");
        printf("\t2: Print Inventory\n");
        printf("\t3: Search For Item\n");
        printf("\t4: Exit Program\n");

        std::cin >> input;

        switch (input)
        {
        case 0:
        {
          InputAddItem(inventory);
          break;
        }
        case 1:
        {
          InputRemoveItem(inventory);
          break;
        }
        case 2:
        {
          InputPrintInventory(inventory);
          break;
        }
        case 3:
        {
          InputPrintItems(inventory);
          break;
        }
        case 4:
        {
          IsRunning = false;
          break;
        }
        default:
        {
          printf("\nInvalid Input Retry Again\n");
          getchar();
        }
        }

      } while (IsRunning);
      break;
    }
  }
}
