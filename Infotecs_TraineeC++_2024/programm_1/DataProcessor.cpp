#include <algorithm>
#include <assert.h>

#include "DataProcessor.h"

using cstr = const std::string;

namespace {
  bool isEven(char c){
    return ((c - '0') & 1) == 0;
  }

  template<typename Pred>
  std::string replace_if_custom(cstr& input_string, Pred p, cstr & replacement, size_t evenCount){
    assert(evenCount >=0 );
    std::string modified_string;
    modified_string.reserve(input_string.size()+evenCount);
    std::for_each(input_string.begin(), input_string.end(), [&](char c) {
      std::string tmp_string = !p(c) ? std::to_string(c-'0') : replacement;
      modified_string += tmp_string;
    });
    return modified_string;
  }
}

std::string processor_programm_1::DataProcessor::processData(std::string& str) const{
  std::sort(str.rbegin(), str.rend());
  size_t evenCount = std::count_if(str.begin(), str.end(), isEven);
  std::string output_string = replace_if_custom(str,isEven,"KB", evenCount);
  return output_string;
}