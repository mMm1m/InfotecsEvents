#include <iostream>

#include "InputHandler.h"

std::string handler_program_1::InputHandler::getInput() {
  std::string str;
  std::getline(std::cin, str);
  if(!handler_program_1::InputHandler::checkInput(str) || str.empty()){
    std::cerr << "\nIncorrect input string\n";
    return "";
  }
  return str;
}

bool handler_program_1::InputHandler::checkInput(const std::string& str) const {
  if(str.empty()){
    return false;
  }
  for(auto& a : str){
    if(!isdigit(a)){
      return false;
    }
  }
  return str.size() < 64;
}