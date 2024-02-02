#include "scheduler.h"
#include "tasks.h"


Task tasks[5];

void initialize_tasks(){
    tasks[0] = spawn_task(2, 10);
    tasks[1] = spawn_task(4, 20);
    tasks[2] = spawn_task(6, 30);
    tasks[3] = spawn_task(8, 40);
    tasks[4] = spawn_task(12, 60);
}

int main(){
    initialize_tasks();

    int n = sizeof(tasks)/sizeof(tasks[0]);

    printf("number of tasks: %d \n", n);

    earliest_deadline_first(&tasks, n, 120);

    float U = 0.0;
    for(int i = 0; i < n; i++){
        U += (float) tasks[i].execution_time / (float) tasks[i].period;
    }
    printf("Total U = %2.3f \n", U);

    return 0;
}
