#ifndef MERGE_H
#define MERGE_H

void merge(Task tasks[], int left, int mid, int right);
void mergeSort(Task tasks[], int left, int right);
int compareTasks(const void *a, const void *b);

#endif