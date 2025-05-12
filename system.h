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
  void addCars(){
   try{
    std::string made;
    std::string model;
    int year;
    double paymentpersecond;
    
    std::cout << "\nEnter car Made: ";
    std::getline(std::cin,made);
    std::cout << "\nEnter car Model: ";
    std::getline(std::cin, model);
    std::cout<< "\nEnter manu Year  for the car.";
    std::cin>> year;
    std::cout<< "\nEnter paymentpersecond.";
    std::cin>>paymentpersecond;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    
    std::unique_ptr<PreparedStatement> pstmt (conn->prepareStatement("INSERT INTO Cars (made, model, year,paymentpersecond) VALUES (?,?,?,?)"));
    pstmt->setString(1,made);
    pstmt->setString(2,model);
    pstmt->setInt(3,year);
    pstmt->setDouble(4,paymentpersecond);
    int affectedRows = pstmt->executeUpdate();
    std::cout << (affectedRows > 0? "Car added successffuly!\n" : "Someting went wrong while adding the car!\n"); 
   }catch (SQLException & e){
    std::cout << "Error: " << e.what() << std::endl;
   }
 }
 

/*ABENEZER*/
//ABENEZER
  void addCars(){
   try{
    std::string made;
    std::string model;
    int year;
    double paymentpersecond;
    
    std::cout << "\nEnter car Made: ";
    std::getline(std::cin,made);
    std::cout << "\nEnter car Model: ";
    std::getline(std::cin, model);
    std::cout<< "\nEnter manu Year  for the car.";
    std::cin>> year;
    std::cout<< "\nEnter paymentpersecond.";
    std::cin>>paymentpersecond;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    
    std::unique_ptr<PreparedStatement> pstmt (conn->prepareStatement("INSERT INTO Cars (made, model, year,paymentpersecond) VALUES (?,?,?,?)"));
    pstmt->setString(1,made);
    pstmt->setString(2,model);
    pstmt->setInt(3,year);
    pstmt->setDouble(4,paymentpersecond);
    int affectedRows = pstmt->executeUpdate();
    std::cout << (affectedRows > 0? "Car added successffuly!\n" : "Someting went wrong while adding the car!\n"); 
   }catch (SQLException & e){
    std::cout << "Error: " << e.what() << std::endl;
   }
 }


  /*AHADU*/
  void availebleCars(){
   try {
   std::unique_ptr<PreparedStatement> pstmt (conn->prepareStatement("SELECT * FROM Cars WHERE isAvaileble = 1 "));
   std::unique_ptr<ResultSet> res(pstmt->executeQuery());
   std::cout << std::left;
   std::cout << std::setw(35) << "Brand" << std::setw(35) << "Model" << std::setw(10)  << "Year"  << std::endl;
    while (res->next()){
    std::cout << std::left;
    std::cout << std::setw(35) << res->getString("made")  << std::setw(35) << res->getString("model") << std::setw(10) << res->getInt("year") << std::endl; 
    }
   
  } catch (SQLException & e) {
   std::cout << "ERROR: " << e.what() << std::endl;
  }
   
  }
  
  //helper function for validation and error logging
  bool validateEmail(std::string email){
   std::regex pattern(R"(^[a-zA-Z0-9._+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,7}$)");
   bool isMatch;
   isMatch  = std::regex_match(email,pattern);
   return isMatch;
  }


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

 int returnCar(){
   try {
    std::string name;
    std::string email;
    std::string made;
    std::string model;
    int selectedCarId;
    int duration;
    int affectedRows;
    int year;
    int userId;
    int rentedCarsByUser;
    double paymentpersecond;
    double bill;


     
    std::cout << "\nEnter your name: ";
    std::getline(std::cin,name);
    std::cout << "\nEnter your email: ";
    std::getline(std::cin, email);
    
    std::unique_ptr<PreparedStatement> pstmt(conn->prepareStatement("SELECT id,bill FROM Customers WHERE name= ? AND email = ? "));
    pstmt->setString(1,name);
    pstmt-> setString(2,email);
    std::unique_ptr<ResultSet> res (pstmt->executeQuery());
    
    if (res->next()){
     userId = res->getInt("id");
     bill = res->getDouble("bill");
     } else {
     std::cout << "\nNo User With a given username and email. Please goto registration page.\n";
     return 0;
    }
    pstmt.reset(conn->prepareStatement("SELECT COUNT(*) FROM Cars WHERE rentedby = ?"));
    pstmt->setInt(1,userId);
    res.reset(pstmt->executeQuery());
    if (res->next()){
     rentedCarsByUser = res->getInt(1);
    } else {
     std::cout << "\nNo Cars rented by a user!" << std::endl;
     return 0;
    }
    
    if (rentedCarsByUser > 1){
     std::cout << "\nEnter The Model of the the Car you want to return";
     std::getline(std::cin, model);
     std::cout << "\nEnter manufacture Year For car " << model << ": " ;
     std::cin>> year;
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
     
     pstmt.reset(conn->prepareStatement("SELECT id,paymentpersecond FROM Cars WHERE model = ? AND year = ?"));
     pstmt->setString(1,model);
     pstmt->setInt(2,year);
     res.reset(pstmt->executeQuery());
     if (res->next()){
      selectedCarId = res->getInt("id");
      paymentpersecond = res->getDouble("paymentpersecond");
     }else{
      std::cout << "\nNo car with this model and year Rented by a user." << std::endl;
      return 0;
     }

     pstmt.reset(conn->prepareStatement("SELECT TIMESTAMPDIFF(SECOND, rental_date,CURRENT_TIMESTAMP) FROM Cars WHERE id = ?"));
     pstmt->setInt(1,selectedCarId);
     res.reset(pstmt->executeQuery());
     if (res->next()){
      duration = res->getDouble(1);
     }else {
      std::cout << "Something goes wrong wile calculating the bill\n" << std::endl; 
     }
     bill  += duration * paymentpersecond;
     
     pstmt.reset(conn->prepareStatement("UPDATE Customers SET bill = ? WHERE id = ?"));
     pstmt->setDouble(1,bill);
     pstmt->setInt(2,userId);
     pstmt->executeUpdate();
     
     pstmt.reset(conn->prepareStatement("UPDATE Cars SET rentedBy = NULL ,rental_date = NULL ,isAvaileble = 1 WHERE id = ?"));
     pstmt->setInt(1,selectedCarId);
     affectedRows = pstmt->executeUpdate();
     std::cout << (affectedRows> 0? "\nYou have returned the car Successfuly!\n": "\nSomething gose rong while returnig the car please try Again letter.\n");
     }else if  (rentedCarsByUser == 1){
     
     pstmt.reset(conn->prepareStatement("SELECT id,paymentpersecond FROM Cars WHERE  rentedby = ?"));
     pstmt->setInt(1,userId);
     res.reset(pstmt->executeQuery());
     if (res->next()){
      selectedCarId = res->getInt("id");
      paymentpersecond = res->getDouble("paymentpersecond");
     }

     
    std::cout << "\nEnter your name: ";
    std::getline(std::cin,name);
    std::cout << "\nEnter your email: ";
    std::getline(std::cin, email);
    
    std::unique_ptr<PreparedStatement> pstmt(conn->prepareStatement("SELECT id,bill FROM Customers WHERE name= ? AND email = ? "));
    pstmt->setString(1,name);
    pstmt-> setString(2,email);
    std::unique_ptr<ResultSet> res (pstmt->executeQuery());
    
    if (res->next()){
     userId = res->getInt("id");
     bill = res->getDouble("bill");
     } else {
     std::cout << "\nNo User With a given username and email. Please goto registration page.\n";
     return 0;
    }
    pstmt.reset(conn->prepareStatement("SELECT COUNT(*) FROM Cars WHERE rentedby = ?"));
    pstmt->setInt(1,userId);
    res.reset(pstmt->executeQuery());
    if (res->next()){
     rentedCarsByUser = res->getInt(1);
    } else {
     std::cout << "\nNo Cars rented by a user!" << std::endl;
     return 0;
    }
    
    if (rentedCarsByUser > 1){
     std::cout << "\nEnter The Model of the the Car you want to return";
     std::getline(std::cin, model);
     std::cout << "\nEnter manufacture Year For car " << model << ": " ;
     std::cin>> year;
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
     
     pstmt.reset(conn->prepareStatement("SELECT id,paymentpersecond FROM Cars WHERE model = ? AND year = ?"));
     pstmt->setString(1,model);
     pstmt->setInt(2,year);
     res.reset(pstmt->executeQuery());
     if (res->next()){
      selectedCarId = res->getInt("id");
      paymentpersecond = res->getDouble("paymentpersecond");
     }else{
      std::cout << "\nNo car with this model and year Rented by a user." << std::endl;
      return 0;
     }

     pstmt.reset(conn->prepareStatement("SELECT TIMESTAMPDIFF(SECOND, rental_date,CURRENT_TIMESTAMP) FROM Cars WHERE id = ?"));
     pstmt->setInt(1,selectedCarId);
     res.reset(pstmt->executeQuery());
     if (res->next()){
      duration = res->getDouble(1);
     }else {
      std::cout << "Something goes wrong wile calculating the bill\n" << std::endl; 
     }
     bill  += duration * paymentpersecond;
     
     pstmt.reset(conn->prepareStatement("UPDATE Customers SET bill = ? WHERE id = ?"));
     pstmt->setDouble(1,bill);
     pstmt->setInt(2,userId);
     pstmt->executeUpdate();
     
     pstmt.reset(conn->prepareStatement("UPDATE Cars SET rentedBy = NULL ,rental_date = NULL ,isAvaileble = 1 WHERE id = ?"));
     pstmt->setInt(1,selectedCarId);
     affectedRows = pstmt->executeUpdate();
     std::cout << (affectedRows> 0? "\nYou have returned the car Successfuly!\n": "\nSomething gose rong while returnig the car please try Again letter.\n");
     }else if  (rentedCarsByUser == 1){
     
     pstmt.reset(conn->prepareStatement("SELECT id,paymentpersecond FROM Cars WHERE  rentedby = ?"));
     pstmt->setInt(1,userId);
     res.reset(pstmt->executeQuery());
     if (res->next()){
      selectedCarId = res->getInt("id");
      paymentpersecond = res->getDouble("paymentpersecond");
     }
pstmt.reset(conn->prepareStatement("SELECT TIMESTAMPDIFF(SECOND, rental_date,CURRENT_TIMESTAMP) FROM Cars WHERE id = ?"));
     pstmt->setInt(1,selectedCarId);
     res.reset(pstmt->executeQuery());
     if (res->next()){
      duration = res->getInt(1);
     }else {
      std::cout << "\nSomething goes wrong wile calculating the bill\n" << std::endl; 
     }
     bill  += duration * paymentpersecond;
     
     pstmt.reset(conn->prepareStatement("UPDATE Customers SET bill = ? WHERE id = ?"));
     pstmt->setDouble(1,bill);
     pstmt->setInt(2,userId);
     pstmt->executeUpdate();
     
     pstmt.reset(conn->prepareStatement("UPDATE Cars SET rentedBy = NULL ,rental_date = NULL ,isAvaileble = 1 WHERE id = ?"));
     pstmt->setInt(1,selectedCarId);
     affectedRows = pstmt->executeUpdate();

     std::cout << (affectedRows> 0? "\nYou have returned the car Successfuly!\n": "\nSomething went wrong while returnig the car please try Again letter.\n");
    
     }else {
     std::cout << "\nNo cars rented by a user.\n" << std::endl;
     }
   
   }catch (SQLException &e){
    std::cout << "Error: " << e.what() <<std::endl;
   }
   return 0;
 }

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
