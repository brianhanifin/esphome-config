#include "esphome.h"

std::string update_next_runtime(std::string time_list) {
  // Initialize variables.
  std::vector<std::string> times;
  char * token;
  token = strtok(&time_list[0], ",");

  // Split the list of run times into an array.
  while (token != NULL) {
    times.push_back(token);
    token = strtok(NULL, ",");
  }

  // Retrieve the current time.
  auto time_now = id(homeassistant_time).now();
  int time_hour = time_now.hour;
  //int time_minute = time_now.minute;

  // Initialize variables.
  std::vector<std::string> next_time;
  int next_hour = 0;
  //int next_minute = 0;
  int index = 0;
  int loop_count = 0;
  int time_count = times.size()-1;

  // Compare the list of times with the current time, and return the next in the list.
  //ESP_LOGD("IrrigationNextRuntime", "now: %i:%i", hour, minute);
  for (std::string time : times) {
    // Split the hour and minutes.
    token = strtok(&time[0], ":");
    while (token != NULL) {
      next_time.push_back(token);
      token = strtok(NULL, ":");
    }

    // Retrieve the next hour from the list.
    next_hour = std::atoi(next_time[index].c_str());
    //next_minute = std::atoi(next_time[index+1].c_str());

    //ESP_LOGD("IrrigationNextRuntime", "next_hour: %s", time.c_str());
    if (time_hour < next_hour) {
      // Return this time if the next hour is greater than the current hour.
      return time.c_str();
      break;
    }

    // When we reach the end of our schedule for the day, return the first time of tomorrow.
    //ESP_LOGD("IrrigationNextRuntime", "loop_count: %i, time_count: %i", loop_count, time_count);
    if (time_count == loop_count) {
      //return next_time[0].c_str() + std::string(":") + next_time[1].c_str();
      return times[0].c_str();
      break;
    }

    // Increment the loop counter and array index.
    loop_count += 1;
    index += 2;
  }

  return "unknown";
}
