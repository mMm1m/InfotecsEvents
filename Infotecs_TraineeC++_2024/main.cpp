#include <bits/stdc++.h>

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
}

int main() {
  std::string buffer;
  bool bufferIsNotEmpty = false;

  // p1 thread 1
  std::string str;
  std::getline(std::cin, str);
  if(str.size() > 64 || !golchanskiy::checkInput(str)){
    std::cerr << "Incorrect input string";
    return  0;
  }
  size_t evenCount = std::count_if(str.begin(), str.end(), golchanskiy::isEven);
  std::sort(str.begin(), str.end(), std::greater<>());
  std::string output_string = golchanskiy::replace_if_custom(str,golchanskiy::isEven,"KB", evenCount);

  buffer = output_string;
  bufferIsNotEmpty = true;

  // p1 thread 2
  int sum = std::accumulate(buffer.begin(), buffer.end(), 0,[](int a, char b){return std::isdigit(b) ? a+(b-'0'): a;});
  buffer = "";
  bufferIsNotEmpty = false;

  // p2
  //std::cout << (sum^32) << '\n';
  if(sum > 99 && ((sum&31) == 0)){
    printf("Received value is %d , amount of symbols is %d", sum, golchanskiy::digitsCount(sum));
  }
  else{
    std::cerr << "Invalid data" << '\n';
    return 0;
  }
}