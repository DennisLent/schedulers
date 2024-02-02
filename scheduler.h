#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "tasks.h"
#include <stdbool.h>

// RMS functions
void priority_management(Task *tasks, int n);
void check(Task *tasks, int n, int time);
void swap(Task *a, Task *b);
void sort_tasks(Task tasks[], int size);
void rate_monotonic(Task *tasks, int n, int max_time);

// EDF functions
void sort_tasks_edf(Task tasks[], int size);
void priority_management_edf(Task *tasks, int n);
void check_edf(Task *tasks, int n, int time);
void earliest_deadline_first(Task *tasks, int n, int max_time);

#endif 