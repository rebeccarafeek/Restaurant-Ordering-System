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
#include "Drink.h"
#include "Menu.h"
#include "Utils.h"
#include <iomanip>
#include <fstream>

using namespace std;
namespace seneca {
    //constructor which sets m_size to safe empty state
    Drink::Drink(): m_size('\0'){}

//prints the order by overriding Billable's print
std::ostream& Drink::print(std::ostream& ostr) const{
    char buffer[26];
    const char* name = *this;
    ut.strcpy(buffer, name, 25);

    ostr.width(28);
    ostr.fill('.');
    ostr.setf(ios::left);
    ostr << buffer;
    ostr.unsetf(ios::left);

    if (ordered()) {
        switch(m_size) {
            case 'S': ostr << "SML.."; break;
            case 'M': ostr << "MID.."; break;
            case 'L': ostr << "LRG.."; break;
            case 'X': ostr << "XLR.."; break;
        }
    } else {
        ostr << ".....";
    }

    ostr.fill(' ');    
    ostr.width(3);     // adds 3 spaces before the price
    ostr << "";        //  empty string to add spaces
    
    ostr.setf(ios::fixed);
    ostr << setprecision(2) << price();


    return ostr;
}

bool Drink::order(){
    int selection;
    bool status = false;
    Menu sizeMenu("Drink Size Selection", "Back", 3);

     sizeMenu << "Small" << "Medium" << "Larg" << "Extra Large";
     selection = sizeMenu.select();

    if(selection !=0){

      switch (selection) {

      case 1: m_size = 'S'; 
      break;

      case 2: m_size = 'M'; 
      break;

      case 3: m_size = 'L'; 
      break;

      case 4: m_size = 'X'; 
      break;
      }
      status = true;

     } else{
        m_size = '\0';
      }
return status;
}

bool Drink::ordered() const{
    //returns true if size is selected
    return m_size == 'S' || m_size == 'M' || m_size == 'L' || m_size == 'X';
}


std::ifstream& Drink::read(std::ifstream& file){
char temp[250];
double tempPrice;
      
    if (file){
        file.getline(temp, 250, ',');
        file >> tempPrice;
        file.ignore(1000, '\n');

        if(file){
            name(temp);
            Billable::price(tempPrice);
            m_size = 0;
        }
    }
    return file;
}

double Drink::price() const{
    double basePrice = Billable::price(); // calls base class price
      switch (m_size) {
      case 'S': return basePrice * 0.5;
      case 'M': return basePrice * 0.75;
      case 'L': return basePrice; 
      case 'X': return basePrice * 1.5;
      default: return basePrice; // If size is unset
      }
}
}