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
#include "Food.h"
#include "Utils.h"
#include "Billable.h"
#include "Menu.h"
#include <iomanip>
#include <fstream>
using namespace std;
namespace seneca {
    Food::Food() : m_ordered(false), m_child(false), m_customize(nullptr) {}

     // Copy constructor
   Food::Food(const Food& other) : Billable(other) {
     m_ordered = other.m_ordered;
        m_child = other.m_child;
        m_customize = nullptr;
        if (other.m_customize) {
            m_customize = ut.alocpy(other.m_customize);
        }
   }

   //copy assignment
Food& Food::operator=(const Food& other){
    if (this != &other){
        Billable::operator=(other);
        m_ordered = other.m_ordered;
        m_child = other.m_child;

        delete[] m_customize;
        if(other.m_customize){
        m_customize = ut.alocpy(other.m_customize);
    } 
} 
return *this;
}

Food::~Food(){
    delete [] m_customize;
}

//print method
std::ostream& Food::print(std::ostream& ostr) const {
    char buffer[26];
    const char* name = *this;
    ut.strcpy(buffer, name, 25);

    ostr.width(28);
    ostr.fill('.');
    ostr.setf(ios::left);
    ostr << buffer;
    ostr.unsetf(ios::left);

    if (ordered()) {
        ostr << (m_child ? "Child" : "Adult");
    } else {
        ostr << ".....";
    }
   
    ostr.fill(' ');    
    ostr.width(1);     // space before the price
    ostr << "";        
    
    ostr.setf(ios::fixed);
    ostr.width(6);     // width for the price 
    ostr << setprecision(2) << price();

    if (m_customize && &ostr == &cout) {
        ostr << " >> " << m_customize;
    }

    return ostr;
}
// order method
bool Food::order() {
    bool status = false;
    Menu portionMenu("Food Size Selection", "Back", 3);
    portionMenu << "Adult" << "Child";
    
    size_t selection = portionMenu.select();
    if (selection != 0) {
        m_ordered = true;
        m_child = (selection == 2);
        
        cout << "Special instructions\n> ";
        
        delete[] m_customize;
        m_customize = nullptr;
        
        char temp[1024] = {};
        cin.getline(temp, 1024);
        
        if (temp[0] != '\0' && !ut.isspace(temp)) {
            m_customize = ut.alocpy(temp);
        }
        
        status = true;
    } else {
        m_ordered = false;
        delete[] m_customize;
       // m_customize = nullptr;
    }
    
    return status;
}

// ordered query
bool Food::ordered() const {
    return m_ordered;
}

//read method
std::ifstream& Food::read(std::ifstream& file) {
    char temp[256]{};
     double tempPrice = 0.0;
    if (file) {
        file.getline(temp, 256, ',');
        file >> tempPrice;
        file.ignore(1000, '\n');
        
        if (file) {
            name(temp);
            Billable::price(tempPrice);
            m_ordered = false;
            m_child = false;
            delete[] m_customize;
           // m_customize = nullptr;
        }
    }
    return file;
}

// price calculation method
double Food::price() const {
    if (ordered() && m_child) {
        return Billable::price() / 2.0;  // half price for child portion
    }
    return Billable::price();
}
}

