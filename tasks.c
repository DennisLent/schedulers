#include "stdbool.h"

typedef struct {
    int task_id;
    int execution_time;
    int period;
    int priority;
    int pending;
    int relative_deadline;

    int absolute_deadline;
    
    bool in_progress;
    bool halt_progress;

    int time_left;

    int last_executed;

    int cycle;

} Task;

Task spawn_task(int execution_time, int period) {
    Task task;

    task.execution_time = execution_time;
    task.period = period;
    
    return task;
}

void print_task(Task task){
    printf("Task | Execution time: %d [ms] | Period: %d [ms] | Priority: %d \n", task.execution_time, task.period, task.priority);
}