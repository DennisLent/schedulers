#include "stdbool.h"

#ifndef TASKS_H
#define TASKS_H

typedef struct {
    /// The id assigned to this task 
    int task_id;
    /// The maximal time the task will take to execute 
    int execution_time;
    /// The scheduler should aim to execute this task every `period`
    int period;
    //priority assigned to a task
    int priority;
    //if the task still needs to be run
    int pending;
    //for EDF
    int relative_deadline;

    int absolute_deadline;
    
    bool in_progress;
    bool halt_progress;

    int time_left;

    int last_executed;

    int cycle;

} Task;

Task spawn_task(int execution_time, int period);

void print_task(Task task);

extern Task tasks[]; // Declare tasks as an external array

#endif 