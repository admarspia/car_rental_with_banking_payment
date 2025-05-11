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

/*ASTER*/
  
  
//BEREKET
  int rentCar(){
   try {
    std::string name;
    std::string email;
    std::string made;
    std::string model;
    int affectedRows;
    int year;
     
    std::cout << "\nEnter your name: ";
    std::getline(std::cin,name);
    std::cout << "\nEnter your email: ";
    std::getline(std::cin, email);
    std::cout << "\nEnter Car Brand: ";
    std::getline(std::cin, made);
    std::cout << "\nEnter The Model of the the Car " << made << ": ";
    std::getline(std::cin, model);
    std::cout << "\nEnter manufacture Year For car " << made << " " << model << ": " ;
    std::cin>> year;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    
    std::unique_ptr<PreparedStatement> pstmt(conn->prepareStatement("SELECT id FROM Customers WHERE name= ? AND email = ? "));
    pstmt->setString(1,name);
    pstmt-> setString(2,email);
    std::unique_ptr<ResultSet> res (pstmt->executeQuery());
    int userId;
    
    if (res->next()){
     userId = res->getInt("id");
     } else {
     std::cout << "\nNo User With a given username and email. Please goto registration page.\n";
     return 0;
    }
   
    pstmt.reset(conn->prepareStatement("SELECT id FROM Cars WHERE made = ? AND model = ? AND year = ? AND isAvaileble = 1"));
    pstmt->setString(1,made);
    pstmt->setString(2,model);
    pstmt->setInt(3,year);
    res.reset(pstmt->executeQuery());
    int carId;
    
    if (res->next()){
     carId = res->getInt("id");
    }else{
    std::cout << "The car with the given atributes doesnt exist please check out list of available cars!\n" <<std::endl;
    affectedRows =0;
    return 0;
    
    }
  
   pstmt.reset(conn->prepareStatement("UPDATE Cars SET rentedBy = ? ,rental_date = CURRENT_TIMESTAMP ,isAvaileble = 0 WHERE id = ?"));
   pstmt->setInt(1,userId);
   pstmt->setInt(2,carId);
   affectedRows = pstmt->executeUpdate();
   std::cout << (affectedRows > 0? "You have successfuly rented the car !\n" : "Someting goes wrong while updateing the car date!\n"); 
   }catch (SQLException &e){
   std::cout << "Error: " << e.what() << std::endl;
  } 
  return 0;
  
  }
  
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
