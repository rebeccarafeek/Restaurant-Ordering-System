/* Citation and Sources...
Milestone 4
Module:Menu
Filename: Menu.cpp
Version 1.0
Author    Rebecca Rafeek
Revision History
-----------------------------------------------------------
Date     
2024/nov/29  Preliminary release
2024/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include "Food.h"
#include "Drink.h"
#include "Billable.h"
#include "constants.h"
#include <iostream>
namespace seneca {
   class Ordering {
      size_t foodCount;
      size_t drinkCount;
      size_t billableCount;
      size_t billNo;
      Food* foodItems;
      Drink* drinkItems;
      Billable* billItems[MaximumNumberOfBillItems];

      std::ostream& billTitlePrint(std::ostream& ostr)const;
      std::ostream& printTotals(std::ostream& ostr, double value)const;
      size_t countRecords(const char* file)const;

   public:
   //constructor using c-strings that represent the drinks and food data file names
   Ordering(const char* drinksFile, const char* foodFile); 
   virtual ~Ordering();
   //Queries
   operator bool() const; //returns true if the food and drink arrays are not nullptr
   size_t noOfBillItems()const; //returns the no of items currently in the bill
   bool hasUnsavedBill()const; //returns true if the no of bill items is > 0

   std::ostream& listFoods(std::ostream& ostr = std::cout)const;
   std::ostream& ListDrinks(std::ostream& ostr = std::cout)const;
   bool orderFood();
   bool orderDrink();
   std::ostream& printBill(std::ostream& ostr = std::cout)const;
   void resetBill();
   };
}
#endif // !SENECA_ORDERING_H


