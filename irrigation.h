#include "esphome.h"

std::vector<std::string> split(std::string list, const char* delmiter) {
  std::vector<std::string> result;
  char * token;

  token = strtok(&list[0], delmiter);
  while (token != NULL) {
    result.push_back(token);
    token = strtok(NULL, delmiter);
  }
  return result;
}


//void schedule_run(auto relay, std::string time) {
void scheduler() {
  // Retrieve the current time.
  auto time_now = id(homeassistant_time).now();
  int time_hour = time_now.hour;
  int time_minute = time_now.minute;

  // Initialize variables.
  std::vector<std::string> next_time;
  int next_hour = 0;
  int next_minute = 0;

  // Split the hour and minutes.
  next_time = split(id(irrigation_zone1_next).state, ":");

  // Retrieve the next hour from the list.
  next_hour = std::atoi(next_time[0].c_str());
  next_minute = std::atoi(next_time[1].c_str());

  //ESP_LOGD("scheduler", "next_time: %i:%2i", next_hour, next_minute);
  if (time_hour == next_hour && time_minute == next_minute) {
    id(irrigation_zone1).turn_on();
  }
}


std::string update_next_runtime(std::string time_list) {
  // Initialize variables.
  std::vector<std::string> times;

  // Split the list of run times into an array.
  //times = split(time_list, ":");
  char * token;
  token = strtok(&time_list[0], ",");
  while (token != NULL) {
    times.push_back(token);
    token = strtok(NULL, ",");
  }

  // Stop now if the list does not contain more than one time.
  if (times.size() <= 1) {
    return time_list;
  }

  // Retrieve the current time.
  auto time_now = id(homeassistant_time).now();
  int time_hour = time_now.hour;
  int time_minute = time_now.minute;

  // Initialize variables.
  std::vector<std::string> next_time;
  int next_hour = 0;
  int next_minute = 0;
  int index = 0;
  int loop_count = 0;
  int time_count = times.size()-1;

  // Compare the list of times with the current time, and return the next in the list.
  //ESP_LOGD("update_next_runtime", "now: %i:%i", hour, minute);
  for (std::string time : times) {
    // Split the hour and minutes.
    //next_time = split(time, ":");
    token = strtok(&time[0], ":");
    while (token != NULL) {
      next_time.push_back(token);
      token = strtok(NULL, ":");
    }

    // Retrieve the next hour from the list.
    next_hour = std::atoi(next_time[index].c_str());
    next_minute = std::atoi(next_time[index+1].c_str());

    //ESP_LOGD("update_next_runtime", "next_hour: %s", time.c_str());
    if (time_hour < next_hour || (time_hour == next_hour && time_minute < next_minute)) {
      // Return this time if the next hour is greater than the current hour.
      return times[loop_count].c_str();
      break;
    // When we reach the end of our schedule for the day, return the first time of tomorrow.
    } else if (time_count == loop_count) {
      return times[0].c_str();
      break;
    }

    // Increment the loop counter and array index.
    loop_count += 1;
    index += 2;
  }

  return "unknown";
}
