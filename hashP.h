#ifndef PARSECONFIG
#define PARSECONFIG
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sodium.h>

std::string hashPassword(const std::string& password){
 char hashed[crypto_pwhash_STRBYTES];
 if(crypto_pwhash_str(
  hashed,
  password.c_str(),
  password.length(),
  crypto_pwhash_OPSLIMIT_INTERACTIVE,
  crypto_pwhash_MEMLIMIT_INTERACTIVE)!=0){
  
  std::cerr << "Out of memory." << std::endl;
   return 0;
  }
  return std::string(hashed);
}
bool isValid;
bool validatePassword(const std::string hashed,std::string epassword){

 if (crypto_pwhash_str_verify(hashed.c_str(),epassword.c_str(),epassword.length()) == 0){
  isValid = true;
 }else {
  isValid = false;
 }
 return isValid;
}


#endif


