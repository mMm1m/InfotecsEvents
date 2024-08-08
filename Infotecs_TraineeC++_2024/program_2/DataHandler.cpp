#include <cstring>
#include "assert.h"

#include "DataHandler.h"

void handler_program_2::DataHandler::handleData(char* ans, int sum) const{
  if(sum > 99 && ((sum&31) == 0)){
    sprintf(ans, "Received value is %d , amount of symbols is %d\n", sum, handler_program_2::util::digitsCount(sum));
  }
  else{
    strcpy(ans , "Invalid output data\n");
  }
}

int handler_program_2::util::digitsCount(int number){
  assert(number >= 0);
  int symCount = 0;
  while (number > 0)
  {
    ++symCount;
    number /= 10;
  }
  return symCount;
}