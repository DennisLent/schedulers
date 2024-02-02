#include <math.h>
#include "tasks.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include "merge.h"

static int smallest_period;
int start_time = 0;
int current_time = 0;

void priority_management(Task *tasks, int n){

    sort_tasks(tasks, n);

    int smallest = tasks[0].period;
    smallest_period = smallest;


    // Assign priorities based off of smallest period
    // Assign time left to be the execution time
    // Set pending to true
    // Set last execution time to infinity
    for (int i = 0; i < n; i++){
        //printf("i = %d \n", i);
        tasks[i].priority = n - i;
        //printf("Task[%d].priority = %d \n", i, tasks[i].priority);
        tasks[i].time_left = tasks[i].execution_time;
        tasks[i].pending = true;
        tasks[i].last_executed = INT_MAX;
    }
}

void check(Task *tasks, int n, int time){
    for (int i = 0; i < n; i++){
        //if task has been run, but last run is now past the period set it to pending again
        //reset time_left to execution time
        //reset last_executed time
        if (tasks[i].pending == false && (time - tasks[i].last_executed) >= tasks[i].period){
            printf("Task %d has to be set to pending again \n", i);
            tasks[i].pending = true;
            tasks[i].time_left = tasks[i].execution_time;
            tasks[i].last_executed = INT_MAX;
        }
    }
}

void set_active(int i){
    printf("ACTIVATE: Task %d \n", i);
}

void set_idle(){
    printf("IDLE \n");
}

void swap(Task *a, Task *b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

/// @brief Function to sort tasks based on their periods in case not in order
/// @param tasks list of tasks
/// @param size amount of tasks in the list
void sort_tasks(Task tasks[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (tasks[j].period > tasks[j + 1].period) {
                swap(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}

void rate_monotonic(Task *tasks, int n, int max_time){
    int time = -1;
    while (time < max_time){
        printf("---- T = %d ms ---- \n", time);

        if (time == -1) {
        time = 0;
        printf("---- running priority management ---- \n");
        priority_management(tasks, n);
        for (int i = 0; i < n; i++){
            print_task(tasks[i]);
        }
        }

        //check to see if a task needs to be set active again
        check(tasks, n, time);

        //select a task
        int task_id = -1;
        int highest_priority = 0;
        for (int i = 0; i < n; i++){
            if (tasks[i].priority > highest_priority && tasks[i].pending){
                highest_priority = tasks[i].priority;
                task_id = i;
            }
        }

        //set task to run
        if (task_id != -1){

            //save last executed time
            //use the lowest time
            //we set +inf by default to get the real actual time that it was last started
            //if a task is rerun then we can still use that time
            if (time < tasks[task_id].last_executed){
                tasks[task_id].last_executed = time;
            }
            
            //next update time calcualted by using the smallest period
            int next_update_time = ((time / smallest_period) + 1) * smallest_period;
            //printf("Next update at: %d ms \n", next_update_time);

            //the task will finish within the given time frame so no issue
            //set task to not pending anymore
            //run task and delay until task is finished
            if ((time + tasks[task_id].time_left) <= next_update_time){
                printf("Task %d will finish in time \n", task_id);
                tasks[task_id].pending = false;
                set_active(task_id);
                time += tasks[task_id].time_left;
            }

            //the task won't be able to finish
            //do not set pending to false though, still has to finish running
            //run it until next update time
            //update remaining time
            else{
                int remainder = (time + tasks[task_id].time_left) - next_update_time;
                int run_time = (next_update_time - time);
                tasks[task_id].time_left = remainder;
                printf("Task %d will not finish in time | running for %d ms with %d ms left \n", task_id, run_time, tasks[task_id].time_left);
                set_active(task_id);

                time += run_time;
            }
        
        
        }
        //there are no tasks to run
        else{
            set_idle();
            time++;
        }
        
    }
}

void sort_tasks_edf(Task tasks[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (tasks[j].absolute_deadline > tasks[j + 1].absolute_deadline && (tasks[j].pending && tasks[j+1].pending)) {
                swap(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}

//function to set priorities for the monotonic scheduler
//higher priority means it has one up
//functions in task list are ordered based on period and lower period has higher priority
//set all priorities accordingly and set all tasks to pending
void priority_management_edf(Task *tasks, int n, int time){

    for (int i = 0; i < n; i++) {
        tasks[i].relative_deadline = tasks[i].period;
        tasks[i].absolute_deadline = time + tasks[i].relative_deadline;
    }

    sort_tasks_edf(tasks, n);

    int smallest = tasks[0].period;
    smallest_period = smallest;


    // Assign priorities based off of smallest period
    // Assign time left to be the execution time
    // Set pending to true
    // Set last execution time to infinity
    for (int i = 0; i < n; i++){
        tasks[i].priority = n - i;
        tasks[i].time_left = tasks[i].execution_time;
        tasks[i].pending = true;
        tasks[i].last_executed = INT_MAX;
        tasks[i].cycle = 0;
    }
}

//helper function to reset tasks to be run again
void check_edf(Task *tasks, int n, int time){
    printf("---------CHECK----------- \n");
    bool re_prioritize = false;
    for (int i = 0; i < n; i++){
        //if task has been run, but last run is now past the period set it to pending again
        //reset time_left to execution time
        //reset last_executed time
        if (tasks[i].pending == false && ((time - start_time) / tasks[i].period  == tasks[i].cycle)){
            printf("Task %d has to be set to pending again \n", i);
            tasks[i].pending = true;
            tasks[i].time_left = tasks[i].execution_time;
            tasks[i].last_executed = INT_MAX;
            tasks[i].absolute_deadline = time + tasks[i].relative_deadline;
            re_prioritize = true;
        }
    }

    // for (int i = 0; i < n; i++) {
    //     printf("task: %d | pending: %d | current time: %d | start time: %d | period: %d | cycle: %d | priority: %d | deadline: %d \n", i, tasks[i].pending, 
    //                                 time, start_time, tasks[i].period, tasks[i].cycle, tasks[i].priority, tasks[i].absolute_deadline);
    // }

    printf("-----------------------------\n");

    if (re_prioritize) {
        sort_tasks_edf(tasks, n);
        for (int i = 0; i < n; i++) {
            tasks[i].priority = n - i;
            // printf("task: %d | pending: %d | current time: %d | start time: %d | period: %d | cycle: %d | priority: %d | deadline: %d \n", i, tasks[i].pending, 
            //                         time, start_time, tasks[i].period, tasks[i].cycle, tasks[i].priority, tasks[i].absolute_deadline);
        }   
    }
    
}



/// In this function you should write an earliest deadline first scheduler.
/// Read the description of the `schedule` function below to read about the properties of this function.
void earliest_deadline_first(Task *tasks, int n, int max_time) {
    // You can initialize the new fields of your tasks here. This only runs the first time.
    int time = -1;
    int L_max = 0;
    while (time < max_time){
    printf("---- T = %d ms ---- \n", time);
    if (time == -1) {
        time = 0;
        priority_management_edf(tasks, n, time);
        for (int i = 0; i < n; i++){
            print_task(tasks[i]);
        }
    }

    // Check to see if a task needs to be set active again and re-prioritize tasks
    int current_time = time;
    check_edf(tasks, n, current_time);

    // Select a task
    int task_id = -1;
    int highest_priority = 0;
    for (int i = 0; i < n; i++){
        if (tasks[i].priority > highest_priority && tasks[i].pending){
            highest_priority = tasks[i].priority;
            task_id = i;
        }
    }

    int min_update_time = INT_MAX;
    current_time = time;
    for (int i = 0; i < n; i++) {
        int update_time = ((current_time / tasks[i].period) + 1) * tasks[i].period;
        if (update_time < min_update_time) {
            min_update_time = update_time;
        }
    }

    // Set task to run
    if (task_id != -1){

        if (time < tasks[task_id].last_executed){
            tasks[task_id].last_executed = time;
        }

        // next update time calculated by using the smallest period
        int next_update_time = min_update_time;

        // the task will finish within the given time frame so no issue
        // set task to not pending anymore
        // run task and delay until task is finished
        if ((time + tasks[task_id].time_left) <= next_update_time){
            printf("Task %d will finish in time \n", task_id);
            tasks[task_id].pending = false;
            tasks[task_id].cycle++;
            printf("Task period: %d \n", tasks[task_id].period);
            set_active(task_id);
            time += tasks[task_id].time_left;
            L_max += time - tasks[task_id].absolute_deadline;
        }

            // the task won't be able to finish
            // do not set pending to false though, still has to finish running
            // run it until next update time
            // update remaining time
        else{
            int remainder = (time + tasks[task_id].time_left) - next_update_time;
            int run_time = (next_update_time - time);
            tasks[task_id].time_left = remainder;
            printf("Task %d will not finish in time | running for %d ms with %d ms left \n", task_id, run_time, tasks[task_id].time_left);
            printf("Task period: %d \n", tasks[task_id].period);
            set_active(task_id);
            time += run_time;
        }


    }
        //there are no tasks to run
        //comment for pushin
    else{
        set_idle();
        time++;
    }
    }

    printf("total lateness: %d \n", L_max);
}


