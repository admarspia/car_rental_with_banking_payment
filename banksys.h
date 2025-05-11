#ifndef BANK_SYSTEM
#define BANK_SYSTEM
#include <iostream>
#include <mariadb/conncpp.hpp>
#include <memory>
#include <cstdint> 
#include <string>
#include <ctime> 
#include <limits>
#include <iomanip>
#include "hashP.h"

using namespace sql;



class BankSystem {
 private:
  std::unique_ptr<Connection> conn;
 public:

 
  BankSystem() {
   std::map<std::string,std::map<std::string, std::string>> config;
   config = loadIniConfig("config.ini");
   
   try {
    std::string db_url = config["bankdb"]["url"] ;
    std::string db_user  = config["bankdb"]["user"];
    std::string db_password = config["bankdb"]["password"];
    Driver* driver = mariadb::get_driver_instance();
    conn  = std::unique_ptr<Connection>  (driver->connect(db_url,db_user, db_password));
   }catch(SQLException &e) {
     std::cout<< "Error: " << e.what() << std::endl;
   }
  }
  
  void adduser(){
  try {
   std::string password;
   std::string firstname;
   std::string lastname;
   std::string phone_number;
   double balance;
   uint32_t account_number = randombytes_uniform(900000)+100000;
   int NPIDN;
   int affectedRows;
   
   std::cout<< "Enter your first name. ";
   std::getline(std::cin,firstname);
   std::cout << "Enter your last name. ";
   std::getline(std::cin, lastname);
   std::cout << "Enter your password. ";
   std::getline(std::cin, password);
   
   while (password.length() <8){
    std::cout << "Password Length must be greater than 8" <<std::endl;
    std::cout << "Enter your password. ";
    std::getline(std::cin, password);
   }
   
   std::cout<<"Enter phone number: ";
   std::getline(std::cin,phone_number);
   std::cout<<"Enter start up deposete: ";
   std::cin>> balance;
   std::cout<< "Ener Your national personal identification number: ";
   std::cin >> NPIDN;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
   
   std::string hashed = hashPassword(password);
   
   
   
   std::unique_ptr<PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO users VALUES (?,?,?,?,?,?,?)"));
   pstmt->setInt(1,account_number);
   pstmt->setString(2,firstname);
   pstmt->setString(3,lastname);
   pstmt->setDouble(4,balance);
   pstmt->setString(5,phone_number);
   pstmt->setInt(6,NPIDN);
   pstmt->setString(7,hashed);
   
   affectedRows = pstmt->executeUpdate();
   std::cout<< (affectedRows !=0? "Your accuont has been created Successflly!\n":"Something went Wrong!\n");
  } catch (SQLException & e){
     std::cout<< "Error: " <<  e.what() << std::endl;
  } 
 }
 
 /*AHADU*/

 

 /*ABENEZER*/

 

 /*ASTER*/

 

 /*BEREKET*/


 /*DAGMAWI*/

};

#endif
