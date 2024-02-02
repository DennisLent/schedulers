# Scheduling Algorithms

This repository contains a simulator for simulating the behavior of a Rate Monotonic (RM) scheduler and an Earliest Deadline First (EDF) scheduler. The simulator can be used to analyze and compare the performance of these scheduling algorithms for real-time systems.

## Rate Monotonic (RM) Scheduler
The Rate Monotonic scheduling algorithm is a priority-based schedulier. It assigns priorities to tasks based on their periods, where shorter periods receive a higher priority. This means that tasks with shorter deadlines are scheduled before tasks with longer deadlines. RM is known for its simplicity and optimality under certain conditions.

## Earliest Deadline First (EDF) Scheduler
The Earliest Deadline First scheduling algorithm prioritizes tasks based on their absolute deadlines. The task with the earliest deadline is scheduled first, regardless of its period. EDF is a dynamic scheduling algorithm that adapts to changing workload. It is known for its ability to handle tasks with arbitrary deadlines and is considered optimal for preemptive task sets.

## Usage
Create a folder for the build and go into it
```mkdir build```
```cd build```

Build the project
```cmake ..```

The scheduling algorithm to be used can be set in main.c on line 22, as an example:
```C
rate_monotonic(Task *tasks, int n, int max_time)
earliest_deadline_first(Task *tasks, int n, int max_time)
```

You can also set your own task sets:
```C
void initialize_tasks(){
    tasks[0] = spawn_task(int execution_time, int period);
    tasks[1] = spawn_task(int execution_time, int period);
    tasks[2] = spawn_task(int execution_time, int period);
}
```