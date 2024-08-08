#ifndef INFOTECSEVENTS_DATAHANDLER_H
#define INFOTECSEVENTS_DATAHANDLER_H

#include <string>

namespace handler_program_2 {
  class DataHandler {
    public:
     DataHandler() = default;
     DataHandler(const DataHandler& other) = delete;
     DataHandler(DataHandler&& other) = default;
     ~DataHandler() = default;
     DataHandler& operator=(const DataHandler& other) = delete;
     DataHandler& operator=(DataHandler&& other) = delete;
     void handleData(char*, int) const;
  };
  namespace util{
    int digitsCount(int);
  }
}

#endif