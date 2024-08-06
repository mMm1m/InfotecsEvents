#ifndef INFOTECSEVENTS_DATAHANDLER_H
#define INFOTECSEVENTS_DATAHANDLER_H

#include <string>

namespace handler {
  class DataHandler {
    public:
     void handleData(char*, int);
     void parseInput(const std::string&);
  };
  namespace util{
    int digitsCount(int);
  }
}

#endif //INFOTECSEVENTS_DATAHANDLER_H
