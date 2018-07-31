/*customer.h*/

//
// Customer class for banking program in modern C++.
//
// << Christian Dominguez >>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//

#pragma once

#include <iostream>
#include <string>

using namespace std;


class Customer
{
  private:
    string Name;
    int ID;
    double Balance;
  
  public:
    Customer(string name, int id, double bal)
     : Name(name), ID(id), Balance(bal)
    {} 
    
    string getName(){
      return Name;
    }//End of getName()
    
    int getID(){
      return ID;
    }//End of getID()
    
    double getOldBalance(){
      return Balance;
    }//End of getOldBalance()
    
    void updateBalance(double amt){
      Balance = Balance + amt;
    }//End of updateBalance()
    
};//End of Customer class

class Transaction
{
  private:
    int ID;
    double Amount;
    
  public:
    Transaction(int id, double amnt)
      : ID(id), Amount(amnt)
    {}
    
    int getID2(){
      return ID;
    }//End of getID2()
    
    double getTransaction(){
      return Amount;
    }//End of getTransaction()
    
};//End of Transaction class
