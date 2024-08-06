#ifndef INFOTECSEVENTS_DATAHANDLER_H
#define INFOTECSEVENTS_DATAHANDLER_H

namespace handler {
  class DataHandler {
    public:
     void handleData(char*, int);
  };
  namespace util{
    int digitsCount(int);
  }
}

#endif //INFOTECSEVENTS_DATAHANDLER_H
