#include "esphome.h"
using namespace std;

// Declare functions before calling them.
bool scheduled_runtime(string);
string update_next_runtime(string);

bool scheduled_runtime(string time) {
  // Retrieve the current time.
  auto time_now = id(homeassistant_time).now();
  int time_hour = time_now.hour;
  int time_minute = time_now.minute;

  // Split the hour and minutes.
  int next_hour = atoi(time.substr(0,2).c_str());
  int next_minute = atoi(time.substr(3,2).c_str());

  //ESP_LOGD("scheduled_runtime()", "now: %i:%i", next_hour, next_minute);
  return (time_hour == next_hour && time_minute == next_minute);
}

string update_next_runtime(string time_list) {
  // Initialize variables.
  vector<string> times;
  vector<string> next_time;
  char * token;

  // Split the list of run times into an array.
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
  int next_hour = 0;
  int next_minute = 0;
  int index = 0;
  int loop_count = 0;
  int time_count = times.size()-1;

  // Compare the list of times with the current time, and return the next in the list.
  //ESP_LOGD("update_next_runtime", "now: %i:%i", hour, minute);
  for (string time : times) {
    // Retrieve the next scheduled time from the list.
    next_hour = atoi(time.substr(0,2).c_str());
    next_minute = atoi(time.substr(3,2).c_str());

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
