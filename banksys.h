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

 

//BEREKET
 void changePassword(){
    try {
   std::string opassword;
   std::string npassword;
   std::string hashed;
   int affectedRows;
   int account;
   double balance;

   std::cout<< "Enter your account number: ";
   std::cin>>account;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
   std::cout <<"Enter Password : ";
   std::getline(std::cin,opassword);
   
   std::unique_ptr<PreparedStatement> pstmt(conn->prepareStatement("SELECT password FROM users WHERE acount_number = ? "));
   pstmt->setInt(1,account);
   
   std::unique_ptr<ResultSet> res(pstmt->executeQuery());
   
   if (res->next()){
    hashed = res->getString("password");
   }else{
    std::cout<< "Account  Not Found!\n";
    return ;
   }
   
   if (!validatePassword(hashed,opassword)) { 
    std::cout<< "Incorrect Password!" <<std::endl;
    return ;
   }
   std::cout <<"Enter New Password : ";
   std::getline(std::cin,npassword);
   
   
   std::string newhash = hashPassword(npassword);
   
   pstmt.reset(conn->prepareStatement("Update users SET password = ? WHERE acount_number = ?"));

   pstmt->setString(1,newhash);
   pstmt->setInt(2,account);
   
   affectedRows = pstmt->executeUpdate();
   std::cout<< (affectedRows !=0? "password changed!\n":"Something went Wrong!\n");
    
  } catch (SQLException & e){
     std::cout<< "Error: " <<  e.what() << std::endl;
  } 
 }


 /*DAGMAWI*/
 int payothers(double amount){
   try {
   int accofsender;
   double senderbalance;

   int affectedRows;
   std::string hashed;
   std::string password;
   
   std::cout<< "Enter your account number: ";
   std::cin>>accofsender;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
 
   std::cout <<"Enter Password : ";
   std::getline(std::cin,password);
   
   std::unique_ptr<PreparedStatement> pstmt(conn->prepareStatement("SELECT password, balance FROM users WHERE acount_number= ? "));
   pstmt->setInt(1,accofsender);
   
   std::unique_ptr<ResultSet> res(pstmt->executeQuery());

   if  (res->next()){
    senderbalance = res->getDouble("balance");
    hashed = res->getString("password");
   }
   
   if (!validatePassword(hashed,password)) { 
    std::cout<< "Incorrect Password!" <<std::endl;
    return 0;
   }

   std::cout << senderbalance  << "  " << amount;
   if (senderbalance >= amount){
    senderbalance -= amount;

   }else {
    std::cout << "inseficent balance!.\n";
    return 0;
   }
  
   pstmt.reset(conn->prepareStatement("UPDATE users SET balance = ? WHERE  acount_number = ?"));
   pstmt->setDouble(1,senderbalance);
   pstmt->setInt(2,accofsender);
   affectedRows = pstmt->executeUpdate();
   
   if (affectedRows != 0){
   pstmt.reset(conn->prepareStatement("INSERT INTO Transaction (user_id,transaction_type,amount) VALUES(?,?,?)"));
   pstmt->setInt(1,accofsender);
   pstmt->setString(2,"payed");
   pstmt->setDouble(3,amount);
   affectedRows = pstmt->executeUpdate();

   
   std::cout<< (affectedRows !=0? "Done!.\n":"Something went Wrong! recording the transaction.\n") ;
   std::cout << "Paymet  Succeeded!.\n";
   } else {
       std::cout<< "Something went Wrong!.\n" ;
   }
  
  } catch (SQLException & e){
     std::cout<< "Error: " <<  e.what() << std::endl;
  } 
 
 return 0;
 }

};

#endif
