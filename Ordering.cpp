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
#define _CRT_SECURE_NO_WARNINGS
#include "Drink.h"
#include "Food.h"
#include "Billable.h"
#include "Ordering.h"
#include "constants.h"
#include "Menu.h"
#include "Utils.h"
#include <cstdio>
#include <fstream>
using namespace std;
namespace seneca {
   size_t Ordering::countRecords(const char* thefile)const {
    size_t newlineCount = 0;
    std::ifstream inFile(thefile);
    char ch;

    while(inFile) {
        inFile.get(ch);
        if(inFile && ch == '\n') {
            newlineCount++;
        }
    }

    return newlineCount;

   }

   std::ostream& Ordering::billTitlePrint(std::ostream& ostr) const{
       ostr << "Bill # " << std::setw(3) << std::setfill('0') << billNo 
         << " =============================" << std::endl;
    return ostr;
}

std::ostream& Ordering::printTotals(std::ostream& ostr, double value)const{
    double taxAmt = value * Tax;
    double withTax = value + taxAmt;
    ostr.width(21);
    ostr << " ";
    ostr.setf(ios::left);
    ostr << "Total:";
    ostr.unsetf(ios::left);
    ostr.precision(2);
    ostr.width(13);
    ostr.setf(ios::right);
    ostr << value << endl;
    ostr.unsetf(ios::right);

    ostr.width(21);
    ostr << " ";
    ostr.precision(2);
    ostr.setf(ios::left);
    ostr << "Tax:";
    ostr.unsetf(ios::left);
    ostr.width(15);
    ostr.precision(2);
    ostr.setf(ios::right);
    ostr << taxAmt << endl;
    ostr.unsetf(ios::right);
    
    ostr.width(21);
    ostr << " ";
    ostr.setf(ios::left);
    ostr << "Total+Tax:";
    ostr.unsetf(ios::left);
    ostr.width(9);
    ostr.precision(2);
    ostr.setf(ios::right);
    ostr << withTax << endl;

    ostr << "========================================" << endl;
   //  ostr.unsetf(ios::right);

   //  ostr << std::right << std::setfill(' ')
   //       << std::setw(29) << "Total: " 
   //       << std::setw(10) << std::fixed << std::setprecision(2) << value << std::endl
   //       << std::setw(29) << "Tax: " 
   //       << std::setw(10) << tax << std::endl
   //       << std::setw(29) << "Total+Tax: " 
   //       << std::setw(10) << withTax << std::endl
   //       << "========================================" << std::endl;
    
    return ostr;
}

   Ordering::Ordering(const char* drinkFileN, const char* foodFileN) : foodCount(0), drinkCount(0), billableCount(0), billNo(1), foodItems(nullptr), drinkItems(nullptr){
     //sets each billItem to nullptr
     int drinkReadCount = 0;
     int foodReadCount = 0;

      for(size_t i =0; i < MaximumNumberOfBillItems; i++){
         billItems[i] = nullptr;
      }

      //counts records
      int noDrinks = countRecords(drinkFileN);
      int noFoods = countRecords(foodFileN);

      std::ifstream drinkFile(drinkFileN);
      std::ifstream foodFile(foodFileN);

      if(drinkFile && foodFile){
         drinkItems = new Drink[noDrinks];
         foodItems = new Food[noFoods];

         //reads drink records
         for(int i =0; i < noDrinks && drinkFile; i++){
            if(drinkItems[i].read(drinkFile)){
               drinkReadCount++;
            }
         }

         //reads food records
         for(int i =0; i < noFoods && foodFile; i++){
            if(foodItems[i].read(foodFile)){
               foodReadCount++;
            }
         }

         //validates read
         if(drinkReadCount != noDrinks || foodReadCount != noFoods) {
            delete[] drinkItems;
            delete[] foodItems;
        } else {
            drinkCount = (size_t)drinkReadCount;
            foodCount = (size_t)foodReadCount;
        }
    }
}

//Destructor
Ordering::~Ordering(){
   delete[] drinkItems;
   delete[] foodItems;

   for(size_t i =0; i < billableCount; i++){
      delete billItems[i];
   }
}

//boolean conversion operator returns true if the food and drink arrays are not nullptr
Ordering::operator bool()const{
return drinkItems != nullptr && foodItems != nullptr;
}

//returns no of bill items
size_t Ordering::noOfBillItems() const{
   return billableCount;
}

//returns true if no of bill items is more than 0
bool Ordering::hasUnsavedBill() const{
return billableCount > 0;
}

//prints list of food items
std::ostream& Ordering::listFoods(std::ostream& ostr)const{
   ostr << "List Of Avaiable Meals" << endl;
   ostr << "========================================" << endl;
//loops through the food array to print each item
for(size_t i =0; i < foodCount; i++ ){
   foodItems[i].print(ostr) << endl;
}
ostr << "========================================" << endl;
return ostr;
}

//prints list of drink items
std::ostream& Ordering::ListDrinks(std::ostream& ostr)const{
 ostr << "List Of Avaiable Drinks" << endl;
   ostr << "========================================" << endl;
//loops through the food array to print each item
for(size_t i =0; i < drinkCount; i++ ){
   drinkItems[i].print(ostr) << endl;
}
ostr << "========================================" << endl;
return ostr;
}

bool Ordering::orderFood(){
   int selection;
   bool status = false;
   Menu foodMenu("Food Menu", "Back to Order", 2); //creates Menu object

   //adds food items to object
   for(size_t i =0; i < foodCount; i++){
      foodMenu << foodItems[i];
   }
   
   selection = foodMenu.select();

   if(selection !=0 && billableCount < MaximumNumberOfBillItems){
      //creates dynamic copy of food
      billItems[billableCount] = new Food(foodItems[selection -1]);

      if(billItems[billableCount]->order()){
         billableCount++;
         status = true;
      } else{
         delete billItems[billableCount];
      }
   }
return status;
}

bool Ordering::orderDrink(){
   int selection;
   bool status = false;
   Menu drinkMenu("Drink Menu", "Back to Order", 2); //creates Menu object

   //adds drink items to object
   for(size_t i =0; i < drinkCount; i++){
      drinkMenu << drinkItems[i];
   }
   
   selection = drinkMenu.select();

   if(selection !=0 && billableCount < MaximumNumberOfBillItems){
      //creates dynamic copy of drink
      billItems[billableCount] = new Drink(drinkItems[selection -1]);

      if(billItems[billableCount]->order()){
         billableCount++;
         status = true;
      } else{
         delete billItems[billableCount];
      }
   }
return status;
}
std::ostream& Ordering::printBill(std::ostream& ostr) const{
   double total = 0;
   
   billTitlePrint(ostr);

   for(size_t i =0; i < billableCount; i++){
      billItems[i]->print(ostr) << endl;
      total += billItems[i]->price();
   }

   printTotals(ostr, total);
   return ostr;
}
//resets bill
void Ordering::resetBill() {
    char filename[256];
    ut.makeBillFileName(filename, billNo);
    
    std::ofstream file(filename);
    printBill(file);
    
    cout << "Saved bill number " << billNo << endl;
    cout << "Starting bill number " << billNo + 1 << endl;
    
    // deletes all bill items
    for(size_t i = 0; i < billableCount; i++) {
        delete billItems[i];
    }
    
    // update counters
    billNo++;
    billableCount = 0;
}
}



