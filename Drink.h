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
#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H
#include "Billable.h"
#include <iomanip>
#include <fstream>
namespace seneca {
   class Drink: public Billable{
      char m_size{};

      public:
      Drink();
      //virtual ~Drink();
      std::ostream& print(std::ostream& ostr = std::cout) const;
      bool order();
      bool ordered()const;
      std::ifstream& read(std::ifstream& file);
      double price()const ;
   };
}
#endif // !SENECA_DRINK_H


