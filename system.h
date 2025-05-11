#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
#include <mariadb/conncpp.hpp>
#include <memory>
#include <string>
#include <limits>
#include <iomanip>
#include <regex>
#include "banksystem.h"



using namespace sql;


class System {
 private:
  std::unique_ptr<Connection> conn;
 public:
  System () {
  try {
    std::string db_url = config["cardb"]["url"] ;
    std::string db_user  = config["cardb"]["user"];
    std::string db_password = config["cardb"]["password"];

   Driver* driver = sql::mariadb::get_driver_instance();
   conn = std::unique_ptr<Connection> (driver->connect(db_url,db_user,db_password));
   } catch (SQLException & e) {
   std::cout << "ERROR: " << e.what() << std::endl;
  }
 }

 
/*ABENEZER*/

  /*AHADU*/

void addUser(){
  try {
 
   std::string name;
   std::string email;
   std::string phone;
   double bill;
   bool rentedcar;
   std::string address;
  
  
   std::cout << "\nEnter your name: ";
   std::getline(std::cin,name);
   std::cout << "\nEnter your email: ";
   std::getline(std::cin, email);
   while (!validateEmail(email)){
    std::cout<< "Your Email is not valid. please try again!: ";
    std::getline(std::cin, email);
    }
   
   
   std::cout << "\nEnter your phone number: ";
   std::getline(std::cin, phone);
   while (phone.length() != 10){
    std:: cout << "phone must be length of  10" << std::endl;
    std::getline(std::cin, phone);
   }
   
   std::cout<< "\nEnter an Address.";
   std::getline(std::cin, address);
  
   std::unique_ptr<PreparedStatement> pstmt (conn->prepareStatement("INSERT INTO Customers (name,email,phone,address) VALUES (?,?,?,?)"));
   pstmt->setString(1,name);
   pstmt->setString(2,email);
   
   pstmt->setString(3,phone);
   pstmt->setString(4,address);
   int affectedRows = pstmt->executeUpdate(); 
   std::cout << (affectedRows > 0? "User added Successfuly!\n" : "Something went wrong. User Not added!\n");
   }
   
   catch(SQLException & e ){
    std::cout<<"Error: " << e.what() <<std::endl;
   }
  }
  
  
  /*BEREKET*/
  
 /*DAGMAWI*/

 int payWithBank(){
 try{
  BankSystem  bs;
  std::string name;
  std::string email;
  std::string address;
  std::string phone;
  double bill;
  

  std::cout <<"Enter user name: " ;
  std::getline(std::cin,name);
  std::cout <<"Enter your Email: ";
  std::getline(std::cin,email);
  
  std::unique_ptr<PreparedStatement> pstmt(conn->prepareStatement("SELECT phone, address, bill FROM Customers WHERE name = ? AND email = ?"));
  pstmt->setString(1,name);
  pstmt->setString(2,email);
  std::unique_ptr<ResultSet> res(pstmt->executeQuery());
  if (res->next()){
   address = res->getString("address");
   phone = res->getString("phone");
   bill =  res->getDouble("bill");
  } else {
   std::cout << "No user with the provided information. please check out and try agian!\n"<< std::endl;
   return 0;
  }
  bs.payothers(bill);
  
  }catch(SQLException &e){
   std::cout << "Error: " << e.what()<< std::endl;
  }
  return 0;
 }
 
 int showProfile(){
  std::string name;
  std::string email;
  std::string address;
  std::string phone;
  double bill;
  

  std::cout <<"Enter user name: " ;
  std::getline(std::cin,name);
  std::cout <<"Enter your Email: ";
  std::getline(std::cin,email);
  
  std::unique_ptr<PreparedStatement> pstmt(conn->prepareStatement("SELECT phone, address, bill FROM Customers WHERE name = ? AND email = ?"));
  pstmt->setString(1,name);
  pstmt->setString(2,email);
  std::unique_ptr<ResultSet> res(pstmt->executeQuery());
  if (res->next()){
   address = res->getString("address");
   phone = res->getString("phone");
   bill =  res->getDouble("bill");
  } else {
   std::cout << "No user with the provided information. please check out and try agian!\n"<< std::endl;
   return 0;
  }
  std::cout << std::left;
  std::cout << std::setw(30) << "name" << std::setw(30) << "email" << std::setw(30)  << "address" << std::setw(15) <<"phone" << std::setw(20) << "bill" << std::endl;
  std::cout << std::setw(30) << name << std::setw(30) << email << std::setw(30) << address << std::setw(15) << phone << std::setw(20) << bill << std::endl;
  return 0;
 }

  
};
