#include <algorithm>

#include "DataProcessor.h"

std::string processor::DataProcessor::processData(const std::string& str){
  size_t evenCount = std::count_if(str.begin(), str.end(), processor::util::isEven);
  std::string output_string = processor::util::replace_if_custom(str,processor::util::isEven,"KB", evenCount);
  return output_string;
}

bool processor::util::isEven(char c){
  return ((c - '0') & 1) == 0;
}

template<class UnaryPred>
std::string processor::util::replace_if_custom(const std::string& input_string, UnaryPred p, const std::string& replacement, size_t evenCount){
  std::string modified_string;
  modified_string.reserve(input_string.size()+evenCount);
  std::for_each(input_string.begin(), input_string.end(), [&](char c) {
    std::string tmp_string = !p(c) ? std::to_string(c-'0') : replacement;
    modified_string += tmp_string;
  });
  return modified_string;
}