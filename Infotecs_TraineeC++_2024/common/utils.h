#ifndef INFOTECSEVENTS_UTILS_H
#define INFOTECSEVENTS_UTILS_H
#include <bits/stdc++.h>

namespace golchanskiy{

  template< class UnaryPred >
  std::string replace_if_custom(std::string& input_string, UnaryPred p, const std::string& replacement, size_t evenCount);

  bool isEven(char c);

  bool checkInput(const std::string& str);

  int digitsCount(int number);

  int exp(int a, int b);

  void toByteArray(short* arr, int number);

  int fromByteArray(const short* arr, size_t size);
}


#endif //INFOTECSEVENTS_UTILS_H
