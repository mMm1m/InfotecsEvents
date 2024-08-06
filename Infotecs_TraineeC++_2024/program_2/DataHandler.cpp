#include <cstring>
#include <iostream>

#include "DataHandler.h"

void handler::DataHandler::handleData(char* ans, int sum){
  if(sum > 99 && ((sum&31) == 0)){
    sprintf(ans, "Received value is %d , amount of symbols is %d\n", sum, handler::util::digitsCount(sum));
  }
  else{
    strcpy(ans , "Invalid output data\n");
  }
}

int handler::util::digitsCount(int number){
  int symCount = 0;
  while (number > 0)
  {
    ++symCount;
    number /= 10;
  }
  return symCount;
}