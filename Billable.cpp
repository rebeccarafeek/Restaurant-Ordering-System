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
#include "Billable.h"
#include "Utils.h"
using namespace std;
namespace seneca {

void Billable::price(double value){
    m_price = value;
}

 //sets the item's name with DMA
void Billable::name(const char* name){
delete[] m_name;
if(name){
    m_name = ut.alocpy(name);
} else {
    m_name = nullptr;
}
}

Billable::Billable(): m_name(nullptr), m_price(0.0) {}

Billable::Billable(const Billable& other) : m_name(nullptr), m_price(other.m_price){
   if(other.m_name){
    m_name = new char [ut.strlen(other.m_name) + 1];
    ut.alocpy(m_name, other.m_name);
   }
}


Billable& Billable::operator=(const Billable& other){
    if (this != &other) {
            name(other.m_name);
            m_price = other.m_price;
         }
         return *this;
}

Billable::~Billable(){
delete[] m_name;
   }
  
  Billable::operator const char*() const{
    return m_name;
  }

// returns the item’s price, allowing derived classes to override if needed.
 double Billable::price() const{
   return m_price; 
   }

   //pure virtual methods
   std::ostream& Billable::print(std::ostream& ostr)const{
    return ostr;
   } 
 bool Billable::order(){
    return false;
 }

   bool Billable::ordered()const{
    return false;
   }

   std::ifstream& Billable::read(std::ifstream& file){
    return file;
   }

   double operator+(double money, const Billable& B){
    return money + B.price();
   }

   double& operator+=(double& money, const Billable& B){
    money += B.price();
    return money;
   }

}
