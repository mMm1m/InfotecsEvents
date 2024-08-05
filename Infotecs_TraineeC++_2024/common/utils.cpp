#include "utils.h"

namespace golchanskiy {
  template< class UnaryPred >
  std::string replace_if_custom(std::string& input_string, UnaryPred p, const std::string& replacement, size_t evenCount)
  {
    std::string modified_string;
    modified_string.reserve(input_string.size()+evenCount);
    std::for_each(input_string.begin(), input_string.end(), [&](char c) {
      std::string tmp_string = !p(c) ? std::to_string(c-'0') : replacement;
      modified_string += tmp_string;
    });
    return modified_string;
  }

  bool isEven(char c)
  {
    return ((c - '0') & 1) == 0;
  }

  bool checkInput(const std::string& str)
  {
    for(auto& a : str){
      if(!isdigit(a)){
        return false;
      }
    }
    return true;
  }

  int digitsCount(int number){
    int symCount = 0;
    while (number > 0)
    {
      ++symCount;
      number /= 10;
    }
    return symCount;
  }
  int exp(int a, int b){
    if(b == 1) return a;
    if(b%2 == 0) return ((exp(a,b/2))*(exp(a,b/2)));
    return (a*(exp(a,b-1)));
  }

  void toByteArray(short* arr, int number){
    int start = 30;
    while(start > 0){
      if(exp(2,start) > number){
        arr[start] = 0;
      }
      else{
        arr[start] = 1;
        number -= exp(2,start);
      }
      --start;
    }
    if(number == 1) arr[0] = 1;
  }

  int fromByteArray(const short* arr, size_t size)
  {
    int number = 0;
    for (int i = 0; i < size; ++i) {
      number += (arr[i] * golchanskiy::exp(2, i));
    }
    return number;
  }
}
