#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
  const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  DailySchedule& sched,
  int day,
  int worker_num
);

bool isValid(
  DailySchedule& sched, 
  size_t maxShifts,
  int day, 
  Worker_T worker
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
  const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  DailySchedule& sched
)
{
  if(avail.size() == 0U){
      return false;
  }
  sched.clear();
  // Add your code below
  sched = vector<vector<Worker_T>> (avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
  scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0);

}

bool isValid(
  DailySchedule& sched, 
  size_t maxShifts,
  int day, 
  Worker_T worker
)
{
  int day_count = 0;

  for(int i = 0; i <= day; i++) {
    int inner_count = 0;
    for(int j = 0; j < sched[0].size(); j++) {
      if(sched[i][j] == worker) {
        day_count++;
        inner_count++;
      }
    }
    if(inner_count > 1) {
      return false;
    }
  }
  if(day_count > maxShifts) {
    return false;
  }
  return true;
}

bool scheduleHelper(
  const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  DailySchedule& sched,
  int day,
  int worker_num
  ) 
{
  int total_workers = avail[0].size();
  if(day == avail.size()) {
    return true;
  }
  for(int i = 0; i < total_workers; i++) {
    if(avail[day][i] == true) {
      sched[day][worker_num] = i;
      if(isValid(sched, maxShifts, day, i)) {
        if(worker_num == dailyNeed - 1) {
          if(scheduleHelper(avail, dailyNeed, maxShifts, sched, day + 1, 0)) {
            return true;
          }
          else {
            sched[day][worker_num] = INVALID_ID;
          }
        }
        else {
          if(scheduleHelper(avail, dailyNeed, maxShifts, sched, day, worker_num + 1)) {
            return true;
          }
          else {
            sched[day][worker_num] = INVALID_ID;
          }
        }
      }
      else {
        sched[day][worker_num] = INVALID_ID;
      }
    }
  }
  return false;

}

