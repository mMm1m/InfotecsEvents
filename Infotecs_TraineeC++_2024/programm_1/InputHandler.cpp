#include <iostream>

#include "../common/handler.h"

std::string handler::InputHandler::getInput() {
  std::string str;
  std::getline(std::cin, str);
  if(!handler::InputHandler::checkInput(str)){
    std::cerr << "Incorrect input string\n";
    return "";
  }
  return str;
}

bool handler::InputHandler::checkInput(const std::string& str) const {
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