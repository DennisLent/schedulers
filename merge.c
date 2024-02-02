#include <stdio.h>
#include "tasks.h"

// Merge function to merge two subarrays
void merge(Task tasks[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    Task Left[n1], Right[n2];

    // Copy data to temporary arrays Left[] and Right[]
    for (i = 0; i < n1; i++)
        Left[i] = tasks[left + i];
    for (j = 0; j < n2; j++)
        Right[j] = tasks[mid + 1 + j];

    // Merge the temporary arrays back into tasks[left..right]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (Left[i].period <= Right[j].period) {
            tasks[k] = Left[i];
            i++;
        } else {
            tasks[k] = Right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of Left[], if any
    while (i < n1) {
        tasks[k] = Left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of Right[], if any
    while (j < n2) {
        tasks[k] = Right[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergeSort(Task tasks[], int left, int right) {
    
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(tasks, left, mid);
        mergeSort(tasks, mid + 1, right);

        // Merge the sorted halves
        merge(tasks, left, mid, right);
    }
}

int compareTasks(const void *a, const void *b) {
    const Task *taskA = (const Task *)a;
    const Task *taskB = (const Task *)b;

    return (taskA->period - taskB->period);
}