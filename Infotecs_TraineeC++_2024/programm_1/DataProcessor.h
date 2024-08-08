#ifndef INFOTECSEVENTS_DATAPROCESSOR_H
#define INFOTECSEVENTS_DATAPROCESSOR_H

#include <string>

namespace processor_programm_1 {
  class DataProcessor {
    public:
     DataProcessor() = default;
     DataProcessor(const DataProcessor& other) = delete;
     DataProcessor(DataProcessor&& other) = delete;
     ~DataProcessor() = default;
     DataProcessor& operator=(const DataProcessor& other) = delete;
     DataProcessor& operator=(DataProcessor&& other) = delete;
     std::string processData(std::string&) const;
  };
}

#endif