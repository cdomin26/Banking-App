/*main.cpp*/

//
// Banking program in modern C++.
//
// <<Christian Dominguez>>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "customer.h"

using namespace std;

void customersBefore(vector<Customer> &C){
  cout << std::fixed;
  cout << std::setprecision(2);
  cout << "\n";
  cout << ">> Customers before:" << endl;
  
  //Sorting by ascending name order
  sort(C.begin(), C.end(),
    [](Customer c1, Customer c2)
      {
        if(c1.getName() < c2.getName()){
          return true;
        }
        else{
          return false;
        }
      }
  );//End of sort function
  
  for(auto &x : C){
    cout << ' ' << x.getName() << " (" << x.getID() << ')' << ": " << "$" << x.getOldBalance() << endl; 
  }
    
    cout << "\n";
}//End of customersBefore()

void proccessTransaction(vector<Customer> &customers, int Id, double amt){
    
  auto C = find_if(customers.begin(),
                   customers.end(),
                   [=](Customer &c)
                   {
                     return (c.getID() == Id);
                   });
                   
  if(C == customers.end()){
    cout << " **Invalid Tx: " << Id << ',' << amt << endl;
  }
  else{
    if(C->getOldBalance() + amt < 0.0){
      cout << " **Rejected Tx: " << Id << ',' << amt << endl;
    }
    else{
      C->updateBalance(amt);
    }
  }
  
}//End of processTransaction()

void customersAfter(vector<Customer> &C){
  cout << std::fixed;
  cout << std::setprecision(2);
  cout << "\n";
  cout << ">> Customers after:" << endl;
  
  sort(C.begin(), C.end(),
    [](Customer c1, Customer c2)
    {
     if(c1.getOldBalance() > c2.getOldBalance()){
       return true;
     }
     else if(c1.getOldBalance() < c2.getOldBalance()){
       return false;
     }
     else{
       if(c1.getName() < c2.getName()){
         return true;
       }
       else{
         return false;
       }
     }
    }//End of lambda expression
  );//End of sort function
  
  for(auto &x : C){
    cout << ' ' << x.getName() << " (" << x.getID() << ')' << ": " << "$" << x.getOldBalance() << endl; 
  }
    
    cout << "\n";
}//End of customersAfter()

int main()
{
  string  customerFilename, transactionsFilename;

  cin >> customerFilename;
  cout << customerFilename << endl;
  
  cin >> transactionsFilename;
  cout << transactionsFilename << endl;

  ifstream  custFile(customerFilename);
  ifstream  txFile(transactionsFilename);
  
  string line, name, id, balance;
  string id2, transaction;

  cout << std::fixed;
  cout << std::setprecision(2);

  if (!custFile.good())
  {
    cout << "**ERROR: cannot open customers file: '" << customerFilename << "'" << endl;
    return -1;
  }
  if (!txFile.good())
  {
    cout << "**ERROR: cannot open transactions file: '" << transactionsFilename << "'" << endl;
    return -1;
  }
    
  vector<Customer> customers;
  vector<Transaction> transactions;
  
  //Getting the input from the customer information file
  while(getline(custFile,line)){
    stringstream ss(line);
    
    //Parsing the input
    getline(ss, name, ',');
    getline(ss, id, ',');
    getline(ss, balance);
    
    Customer C(name, stoi(id), stod(balance));
    
    //Inserting customer at the end of the vector
    customers.push_back(C);
    
  }//End of customer information while loop
  
  //Getting the input from the transaction file
  while(getline(txFile,line)){
    stringstream ss(line);
    
    //parse line
    getline(ss, id2, ',');
    getline(ss, transaction);
    
    Transaction T(stoi(id2), stod(transaction));
    
    //Inserting transaction
    transactions.push_back(T);
    
  }//End of transaction file loop
  
  //Printing out the customer information prior to transactions
  customersBefore(customers);
  
  cout << ">> Processing..." << endl;
  
  //Processing the transactions
  for(auto &x : transactions){
    int ID = x.getID2();
    double amt = x.getTransaction();
    
    proccessTransaction(customers, ID, amt);
  }
  
  //Printing out the customer information after the transactions
  customersAfter(customers);
  
   return 0;
}//End of main()
