#ifndef INFOTECSEVENTS_INPUTHANDLER_H
#define INFOTECSEVENTS_INPUTHANDLER_H

#include <string>

namespace handler_program_1 {
  class InputHandler {
    public:
     InputHandler() = default;
     InputHandler(const InputHandler& other) = delete;
     InputHandler(InputHandler&& other) = delete;
     ~InputHandler() = default;
     InputHandler& operator=(const InputHandler& other) = delete;
     InputHandler& operator=(InputHandler&& other) = delete;

     std::string getInput();
    private:
     bool checkInput(const std::string&) const;
  };
}

#endif