#include <cstring>
#include <assert.h>

#include "DataHandler.h"

namespace {
  int digitsCount(int number)
  {
    assert(number >= 0);
    int symCount = 0;
    if (number == 0) return 1;
    while (number > 0) {
      ++symCount;
      number /= 10;
    }
    return symCount;
  }
}

void handler_program_2::DataHandler::handleData(char* ans, int sum) const noexcept {
  if(sum > 99 && ((sum&31) == 0)){
    sprintf(ans, "Received value is %d , amount of symbols is %d\n", sum, digitsCount(sum));
  } else{
    strcpy(ans , "Invalid output data\n");
  }
}