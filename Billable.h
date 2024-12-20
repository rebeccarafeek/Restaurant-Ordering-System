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
#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H
#include <iostream>
namespace seneca {
   class Billable {
      char* m_name{}; //holds the name or description of the item.
      double m_price{}; //the base price of the item

   protected:
   //Sets the item’s price.
   void price(double value);
   void name(const char* name); //sets the item's name with DMA

   public:
   Billable();
   Billable(const Billable&); //copy constructor
   Billable& operator=(const Billable&); // copy assignment
   virtual ~Billable();
   //Conversion Operator Provides access to the name for display or comparison.
   virtual operator const char*() const;
   virtual double price() const;// returns the item’s price, allowing derived classes to override if needed.
   //pure virtual methods
   virtual std::ostream& print(std::ostream& ostr=std::cout)const = 0; 
   virtual bool order() = 0;
   virtual bool ordered()const = 0;
   virtual std::ifstream& read(std::ifstream& file) = 0;
   };

   double operator+(double money, const Billable& B);
   double& operator+=(double& money, const Billable& B);
}
#endif // !SENECA_BILLABLE_H
