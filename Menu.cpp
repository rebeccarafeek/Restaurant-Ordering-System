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
#include <iostream>
#include "Menu.h"
#include  "Utils.h"
#include "constants.h"
using namespace std;
namespace seneca {
MenuItem::MenuItem(const char* content, int numIndents, int indentSize, int numRow) {
    // checks if content is null, empty or only whitespace using Utils::isspace
    if (content == nullptr || ut.strlen(content) == 0 || ut.isspace(content) ||
        numIndents > 4 || indentSize > 4 || numRow > MaximumNumberOfMenuItems) 
    {
        setEmpty();
    } 
    else {
        // allocates and copies content
        m_content = new char[ut.strlen(content) + 1];
        ut.strcpy(m_content, content);
        m_numIndents = numIndents;
        m_indentSize = indentSize;
        m_numRow = numRow;
    }
}

void MenuItem::setEmpty() { 
      m_content = nullptr;
      m_numIndents = 0;
      m_indentSize = 0;
      m_numRow = 0;
   }

   MenuItem::~MenuItem() {
    delete[] m_content;
}
//returns false if it is in a safe empty state and true if it is a valid MenuItem.
MenuItem::operator bool() const {
    return m_content != nullptr;
}
std::ostream& MenuItem::display(std::ostream& ostr) const {
    
   if (m_content && *m_content) {  // checks if m_content is valid and not empty
        // adds indentation based on numIndents and indentSize
        for (int i = 0; i < m_numIndents * m_indentSize; i++) {
            ostr << ' ';
        }

        // displays the row number if positive num
        if (m_numRow >= 0) {
            ostr << (m_numRow < 10 ? " " : "") << m_numRow << "- ";
         } 

        // skips leading whitespace in content using Utils::isspace
        const char* contentPtr = m_content;
        while (*contentPtr && ut.isspace(*contentPtr)) {
            contentPtr++;
        }

        // displays the trimmed content
        ostr << contentPtr;
    } else {
        // displays ?? if rowNum is positive and invalid or empty MenuItem
         if (m_numRow >= 0) {
        ostr << "??????????";
         }
        }
return ostr;
}

Menu::Menu(const char* title, 
         const char* exitOption, 
         int indentNum, 
         int indentationSize): m_indentNum(indentNum), m_indentationSize(indentationSize), m_numItems(0),
         m_title(title, indentNum, indentationSize, -1), // initializes MenuItem title
         m_exitOption(exitOption, indentNum, indentationSize, 0), // initializes MenuItem exit
         m_entryPrompt("> ", indentNum, indentationSize, -1) // initializes MenuItem entry prompt
      {
      // initializes all elements of the pointer array to nullptr
        for (int i = 0; i < MaximumNumberOfMenuItems; i++) {
            m_menuItems[i] = nullptr;
        }
}
Menu::~Menu(){
    for(int i = 0; i < m_numItems; i++){
         if(m_menuItems[i] != nullptr){
           delete m_menuItems[i];
    }
    }
}

Menu& Menu::operator<<(const char* menuItemContent){
    // checks if there's space for a new MenuItem
    if (m_numItems < MaximumNumberOfMenuItems) {
        // dynamically creates a new MenuItem
        m_menuItems[m_numItems] = new MenuItem(menuItemContent, m_indentNum, m_indentationSize, m_numItems + 1);
        // Increment the count of menu items
       m_numItems++;
    }
    return *this;
}
int Menu::select() const{
    int input;
    if(m_title){
         m_title.display(cout);
         cout << endl;
    }
    //display menu items using MenuItem display function
    for(int i = 0; i < m_numItems; i++){
    if(m_menuItems[i]){
        m_menuItems[i]->display(cout);
        cout << endl;
    }
    }
    if(m_exitOption){
        m_exitOption.display(cout);
        cout << endl;
    }
    if(m_entryPrompt){
       //cout << "> ";
        m_entryPrompt.display(cout);
        // cout << endl;
    }

    input = ut.getInt(0, m_numItems);
return input;
}

int operator<<(std::ostream& ostr, const Menu& m){
    //checks if ostream is cout
     if (&ostr == &cout) {
            // calls the select method and returns value 
            return m.select();
        }
         //if the ostream is not std::cout, return 0
        return 0;
    }

}
