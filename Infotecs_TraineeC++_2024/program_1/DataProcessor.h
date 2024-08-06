#include <string>

#ifndef INFOTECSEVENTS_DATAPROCESSOR_H
#define INFOTECSEVENTS_DATAPROCESSOR_H

namespace processor {
  class DataProcessor {
    public:
     std::string processData(std::string&);
  };
  namespace util{
    bool isEven(char);

    template< class UnaryPred>
    std::string replace_if_custom(const std::string&, UnaryPred, const std::string&, size_t);
  }
}

#endif
