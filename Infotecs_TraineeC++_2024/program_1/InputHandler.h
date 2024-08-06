#include <string>

#ifndef INFOTECSEVENTS_INPUTHANDLER_H
#define INFOTECSEVENTS_INPUTHANDLER_H

namespace handler {
  class InputHandler {
    public:
     std::string getInput();
    private:
     bool checkInput(const std::string&);
  };
}

#endif
