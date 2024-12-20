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
#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"
namespace seneca {
   class Menu;
   class MenuItem {
      friend class Menu;
      char* m_content{};
      int m_numIndents;
      int m_indentSize;
      int m_numRow;
      bool isEmpty()const;
      void setEmpty();

   MenuItem(const char* content, int numIndents, int indentSize, int numRow);
    virtual ~MenuItem();                   
    MenuItem(const MenuItem&) = delete;            // deletes copy constructor
    MenuItem& operator=(const MenuItem&) = delete; // deletes copy assignment (copy assignment returns reference of object)
    operator bool() const;
    std::ostream& display(std::ostream& ostr = std::cout) const;
   };
   
   class Menu {
      int m_indentNum{};
      int m_indentationSize{};
      int m_numItems{};
      MenuItem m_title;
      MenuItem* m_menuItems[MaximumNumberOfMenuItems]{}; 
      MenuItem m_exitOption;
      MenuItem m_entryPrompt;
      
    public: 
    //constructor
     Menu(const char* title, const char* exitOption = "Exit", int indentNum = 0, int indentationSize = 3);
      virtual ~Menu();
      // Operator overload for adding MenuItem
      Menu& operator<<(const char* menuItemContent);
      // prevent copy constructions
      Menu(const Menu&) = delete; 
      //prevents copy assignments
      Menu& operator=(const Menu&) = delete; 
      int select() const;     
};
int operator<<(std::ostream& ostr, const Menu& m);

}
#endif // !SENECA_MENU_H


