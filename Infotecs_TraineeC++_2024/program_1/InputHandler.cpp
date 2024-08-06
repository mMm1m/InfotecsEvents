#include <iostream>
#include "InputHandler.h"

std::string handler::InputHandler::getInput(){
  std::string str;
  std::getline(std::cin, str);
  if(!handler::InputHandler::checkInput(str)){
    std::cerr << "\nIncorrect input string\n";
    return "";
  }
  return str;
}

bool handler::InputHandler::checkInput(const std::string& str)
{
  for(auto& a : str){
    if(!isdigit(a)){
      return false;
    }
  }
  return str.size() < 64;
}

