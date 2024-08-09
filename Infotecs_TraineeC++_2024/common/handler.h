#ifndef INFOTECSEVENTS_HANDLER_H
#define INFOTECSEVENTS_HANDLER_H

#include <string>

namespace handler {
  class InputHandler {
    public:
     InputHandler() = default;
     InputHandler(const InputHandler& other) = delete;
     InputHandler(InputHandler&& other) = default;
     ~InputHandler() = default;
     InputHandler& operator=(const InputHandler& other) = delete;
     InputHandler& operator=(InputHandler&& other) = delete;
     std::string getInput();
    private:
     bool checkInput(const std::string&) const;
  };

  class DataHandler {
    public:
     DataHandler() = default;
     DataHandler(const DataHandler& other) = delete;
     DataHandler(DataHandler&& other) = default;
     ~DataHandler() = default;
     DataHandler& operator=(const DataHandler& other) = delete;
     DataHandler& operator=(DataHandler&& other) = delete;
     void handleData(char*, int) const noexcept;
  };
}

#endif