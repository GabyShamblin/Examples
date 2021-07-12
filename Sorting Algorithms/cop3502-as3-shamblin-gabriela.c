// all-monster-sorts.c - Sort monsters by name and weight.

/* The idea of sorting is simple: take unordered objects, and arrange them in an
   order.  It has a lot of uses, so there's been a lot of work done with it.  Here,
   we're going to demonstrate a few of the simpler, more classic sorting techniques.
   */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include "leak_detector_c.h"

/// Monster structure and helper functions - DO NOT MODIFY THESE.
typedef struct monster {
	int id;
	char name[64];
	char element[64];
	int population;
	double weight;
} monster;

monster *make_some_monsters(int n)
{
    monster *monsters = malloc(sizeof(monster) * n);

    time_t t;

    srand((unsigned) time(&t));

    for(int i = 0; i < n; i++)
    {
        monsters[i].id = i;
        sprintf(monsters[i].name, "Monster #%d", rand());
        sprintf(monsters[i].element, "Element #%d", rand());
        monsters[i].population = rand();
        monsters[i].weight = 500.0 * ((double) rand() / (double) RAND_MAX);
    }

    return monsters;
}

void output_monster_list(monster *list, int n, char *title) {
    printf("List %s:\n", title);
    for(int i = 0; i < n; i++) {
        printf("  Monster %d: %s %lf\n", i, list[i].name, list[i].weight);
        //printf("  Monster %d: %s %s %d %lf\n", i, list[i].name, list[i].element, list[i].population, list[i].weight);
    }
    printf("\n");
}

void print_clocks(clock_t clocks) {
    printf("  %lfs CPU time used\n", ((double) clocks) / CLOCKS_PER_SEC);
}

void swap_monsters(monster *list, int i, int j)
{
    monster temp;

    memcpy(&temp, list + i, sizeof(monster));
    memcpy(list + i, list + j, sizeof(monster));
    memcpy(list + j, &temp, sizeof(monster));
}

/* The core comparison function. */
int compare_monsters(monster *m1, monster *m2, int use_name, int use_weight)
{
    int m1_num;
    int m2_num;

    if(use_name > 0)
    {
        m1_num = name_to_num(m1);
        m2_num = name_to_num(m2);
    }
    else if(use_weight > 0)
    {
        m1_num = m1->weight;
        m2_num = m2->weight;
    }

    if(m1_num > m2_num)
    {
        return 1;
    }
    return 0;
}

void check_monster_sort(monster *list, int n, int use_name, int use_weight)
{
    for(int i = 1; i < n; i++) {
        if(compare_monsters(list + i - 1, list + i, use_name, use_weight) > 0) {
            printf("*** The list is NOT sorted.\n\n");
            return;
        }
    }
    printf("The list is sorted.\n\n");
}



//  Change the monster name to an int
int name_to_num(monster *m)
{
    char num_name[64];
    int num;

    strcpy(num_name, &m->name[9]);
    num = atoi(num_name);

    return num;
}



/// Quick Sort
/* Implement ascending quick sort. */
int repartition(monster *list, int low_index, int high_index, int *comparisons, int *swaps,
                int use_name, int use_weight)
{
    double pivot_value;
    if(use_name > 0)
    {
        pivot_value = (double)name_to_num(&list[high_index]);
    }
    else if(use_weight > 0)
    {
        pivot_value = list[high_index].weight;
    }

    int i = low_index;
    for(int j = low_index; j < high_index; j++)
    {
        double compare;
        if(use_name > 0)
        {
            compare = (double)name_to_num(&list[j]);
        }
        else if(use_weight > 0)
        {
            compare = list[j].weight;
        }

        (*comparisons)++;
        if(compare < pivot_value) {
            (*swaps)++;
            swap_monsters(list, i, j);
            i++;
        }
    }

    swaps++;
    swap_monsters(list, i, high_index);
    return i;
}

/* Recursive function for quick sort. */
void quick_sort_recursive(monster *list, int low_index, int high_index, int *comparisons, int *swaps,
                          int use_name, int use_weight)
{
    int pivot_index = repartition(list, low_index, high_index, comparisons, swaps, use_name, use_weight);   // Infinite loop
    // Coming out of repartition, our pivot_index must already be in the right position.
    if(pivot_index - 1 > low_index)
    {
        quick_sort_recursive(list, low_index, pivot_index - 1, comparisons, swaps, use_name, use_weight);
    }
    if(high_index > pivot_index + 1)
    {
        quick_sort_recursive(list, pivot_index + 1, high_index, comparisons, swaps, use_name, use_weight);
    }
}

/* Shell function for quick sort. */
void quick_sort(monster *list, int n, int use_name, int use_weight)
{
    int comparisons = 0;
    int swaps = 0;
    clock_t start_cpu, end_cpu;

    printf("Quick sort %d monsters by %s...\n", n, use_name ? "name" : "weight");

    start_cpu = clock();
    quick_sort_recursive(list, 0, n-1, &comparisons, &swaps, use_name, use_weight);
    end_cpu = clock();

    printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
    print_clocks(end_cpu - start_cpu);
}



/// Bubble Sort
/* Implement ascending bubble sort. */
void bubble_sort(monster *list, int n, int use_name, int use_weight)
{
    int i;
    int j;
    int temp;
    int comparisons = 0;
    int swaps = 0;
    clock_t start_cpu, end_cpu;

    printf("Bubble sort %d monsters by %s...\n", n, use_name ? "name" : "weight");

    start_cpu = clock();

    for(i = n-1; i >= 0; i--)
    {
        for(j = 0; j < i; j++)
        {
            double compare1, compare2;
            if(use_name > 0)
            {
                compare1 = (double)name_to_num(&list[j]);
                compare2 = (double)name_to_num(&list[j+1]);
            }
            else if(use_weight > 0)
            {
                compare1 = list[j].weight;
                compare2 = list[j+1].weight;
            }

            comparisons++;
            if(compare1 > compare2) // Are our elements out of order?
            {
                swaps++;
                swap_monsters(list, j, j+1);
            }
        }
    }

  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}



/// Selection Sort
/* Highest-value finder for selection sort. */
int find_highest(monster *list, int n, int *comparisons, int use_name, int use_weight)
{
    int highest_val = INT_MIN;
    int highest_loc = -1;
    int i;


    for(i = 0; i <= n; i++)
    {
        double compare;
        if(use_name > 0)
        {
            compare = (double)name_to_num(&list[i]);
        }
        else if(use_weight > 0)
        {
            compare = list[i].weight;
        }

        (*comparisons)++;
        if(compare > highest_val)
        {
            highest_loc = i;
            highest_val = compare;
        }
    }

    return highest_loc;
}

/* Implement ascending selection sort. */
void selection_sort(monster *list, int n, int use_name, int use_weight)
{
    int i;
    int highest;
    int comparisons = 0;
    int swaps = 0;
    clock_t start_cpu, end_cpu;

    printf("Selection sort %d monsters by %s...\n", n, use_name ? "name" : "weight");
    start_cpu = clock();

    for(i = n-1; i > 0; i--)
    {
        highest = find_highest(list, i, &comparisons, use_name, use_weight);
        if(highest != i)
        {
            swaps++;
            swap_monsters(list, highest, i);
        }
    }

  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}



/// Insertion Sort
/* Find position for insertion sort. */
int insertion_sort_find_position(monster *list, int low_index, int high_index, monster *k, int *comparisons, int use_name, int use_weight)
{
    // Iterate j from the front of the list until you reach an element with a higher value or i
    for(int j = low_index; j < high_index; j++)
    {
        double compare1, compare2;
        if(use_name > 0)
        {
            compare1 = (double)name_to_num(&list[j]);
            compare2 = (double)name_to_num(k);
        }
        else if(use_weight > 0)
        {
            compare1 = list[j].weight;
            compare2 = k->weight;
        }

        *comparisons += 1;
        if((int)compare1 > (int)compare2)
        {
            return j;
        }
    }
    return -1;
}

/* Implement insertion sort. */
void insertion_sort_internal(monster *list, int n, int *comparisons, int *copies, int *block_copies, int use_name, int use_weight)
{
    // Iterate i from the second element to the last element
    // Grab element (list[1])
    for(int i = 1; i < n; i++)
    {
        monster copied = list[i];
        *copies += 1;

        int position = insertion_sort_find_position(list, 0, i, &copied, comparisons, use_name, use_weight);

        if(position != -1)
        {
            for(int k = i; k > position; k--)
            {
                list[k] = list[k-1];
                *copies += 1;
            }
            list[position] = copied;
        }
        // Increment and keep going
    }
}

/* Shell for insertion sort. */
void insertion_sort(monster *list, int n, int use_name, int use_weight)
{
    int comparisons = 0;
    int block_copies = 0;
    int total_copies = 0;
    clock_t start_cpu, end_cpu;
    printf("Insertion sort %d monsters by %s...\n", n, use_name ? "name" : "weight");
    start_cpu = clock();

    insertion_sort_internal(list, n, &comparisons, &total_copies, &block_copies, use_name, use_weight);

    end_cpu = clock();
    printf("Sort complete with %d comparisons and %d block copies (%d total copies).\n", comparisons, block_copies, total_copies);
    print_clocks(end_cpu - start_cpu);
    return;
}



/// Merge Sort
/* Merge function for merge sort.  Merges sub-arrays [l1..h1] and [l2..h2].
   Must have l2 = l1 + 1 or bad things will happen. */
void merge_sort_merge(monster *list, int l1, int h1, int l2, int h2,
                      int *comparisons, int *copies, int *block_copies, int *mallocs,
                      int use_name, int use_weight)
{
    int size1 = h1 - l1 + 1;
    int size2 = h2 - l2 + 1;

    monster *sublist1 = calloc(sizeof(monster), size1);
    monster *sublist2 = calloc(sizeof(monster), size2);
    *mallocs += 2;

    // Put list values into both sublists
    memmove(sublist1, list + l1, sizeof(*sublist1) * size1);
    memmove(sublist2, list + l2, sizeof(*sublist2) * size2);
    *block_copies += 2;

    int i = 0;  // Increments through sublist 1 values
    int j = 0;  // Increments through sublist 2 values
    int k = l1; // Increments through the temp list

    // Merge sublists back into the main list
    while((i < size1) && (j < size2))
    {
        double compare1, compare2;
        if(use_name > 0)
        {
            compare1 = (double)name_to_num(&sublist1[i]);
            compare2 = (double)name_to_num(&sublist2[j]);
        }
        else if(use_weight > 0)
        {
            compare1 = sublist1[i].weight;
            compare2 = sublist2[j].weight;
        }

        *comparisons += 1;
        if(compare1 <= compare2)
        {
            list[k] = sublist1[i];
            *copies += 1;
            i++;
        }
        else
        {
            list[k] = sublist2[j];
            *copies += 1;
            j++;
        }
        k++;
    }

    // Put remaining values into main list
    while(i < size1)
    {
        list[k] = sublist1[i];
        *copies += 1;
        i++;
        k++;
    }

    while(j < size2)
    {
        list[k] = sublist2[j];
        *copies += 1;
        j++;
        k++;
    }

    free(sublist1);
    free(sublist2);
}

/* Recursive function for merge sort. */
void merge_sort_recursive(monster *list, int low_index, int high_index,
                          int *comparisons, int *copies, int *block_copies, int *mallocs,
                          int use_name, int use_weight)
{
    // If only one item, stop recursion
    if(low_index == high_index)
    {
        return;
    }

    int middle = (high_index + low_index) / 2;

    merge_sort_recursive(list, low_index, middle, comparisons, copies, block_copies, mallocs, use_name, use_weight);
    merge_sort_recursive(list, middle + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);

    merge_sort_merge(list, low_index, middle, middle + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);
}

/* Implement merge sort. */
void merge_sort(monster *list, int n, int use_name, int use_weight)
{
    int comparisons = 0;
    int copies = 0;
    int block_copies = 0;
    int mallocs = 0;
    clock_t start_cpu, end_cpu;

    printf("Merge sort %d monsters...\n", n);

    start_cpu = clock();
    merge_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs,
                       use_name, use_weight);
    end_cpu = clock();

    printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
    print_clocks(end_cpu - start_cpu);
}



/// Merge Insertion Sort
/* Recursive function for merge-insertion sort. */
void merge_insertion_sort_recursive(monster *list, int low_index, int high_index,
                                    int *comparisons, int *copies, int *block_copies, int *mallocs,
                                    int use_name, int use_weight)
{
    if((high_index - low_index + 1) <= 25)
    {
        insertion_sort_internal(list, high_index - low_index + 1, comparisons, copies, block_copies, use_name, use_weight);
    }
    else
    {
        int middle = (high_index + low_index) / 2;

        merge_sort_recursive(list, low_index, middle, comparisons, copies, block_copies, mallocs, use_name, use_weight);
        merge_sort_recursive(list, middle + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);

        merge_sort_merge(list, low_index, middle, middle + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);
    }
}

/* Implement merge sort. */
void merge_insertion_sort(monster *list, int n, int use_name, int use_weight)
{
  int comparisons = 0;
  int copies = 0;
  int block_copies = 0;
  int mallocs = 0;
  clock_t start_cpu, end_cpu;

  printf("Merge-insertion sort %d monsters...\n", n);

  start_cpu = clock();
  merge_insertion_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs,
                                 use_name, use_weight);
  end_cpu = clock();

  printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
  print_clocks(end_cpu - start_cpu);
}



/// Main Program
void run_all_sorts(int n, int only_fast, int use_name, int use_weight) {
    monster *our_list = make_some_monsters(n);
    monster *our_unsorted_list = malloc(sizeof(monster) * n);

    //output_monster_list(our_list, n, "Unsorted List");
    printf("SORT SET: n = %d, %s, by %s\n\n", n, only_fast ? "fast sorts only" : "all sorts", use_name ? "name" : "weight");

    if(only_fast == 0) {
        memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
        bubble_sort(our_unsorted_list, n, use_name, use_weight);
        check_monster_sort(our_unsorted_list, n, use_name, use_weight);
        //output_monster_list(our_unsorted_list, n, "Bubble Sorted");

        memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
        selection_sort(our_unsorted_list, n, use_name, use_weight);
        check_monster_sort(our_unsorted_list, n, use_name, use_weight);
        //output_monster_list(our_unsorted_list, n, "Selection Sorted");

        memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
        insertion_sort(our_unsorted_list, n, use_name, use_weight);
        check_monster_sort(our_unsorted_list, n, use_name, use_weight);
        //output_monster_list(our_unsorted_list, n, "Insertion Sorted");
    }

    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    quick_sort(our_unsorted_list, n, use_name, use_weight);
        check_monster_sort(our_unsorted_list, n, use_name, use_weight);
    //output_monster_list(our_unsorted_list, n, "Quick Sorted");

    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    merge_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);
    //output_monster_list(our_unsorted_list, n, "Merge Sorted");

    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    merge_insertion_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);
    //output_monster_list(our_unsorted_list, n, "Merge Insertion Sorted");

    printf("SORT SET COMPLETE\n\n");

    free(our_list);
    free(our_unsorted_list);
}

int main(void) {
    //atexit(report_mem_leak);

    run_all_sorts(50, 0, 0, 1);
    //run_all_sorts(50, 0, 1, 0);
    run_all_sorts(500, 0, 0, 1);
    //run_all_sorts(500, 0, 1, 0);
    //run_all_sorts(5000, 0, 0, 1);
    //run_all_sorts(5000, 0, 1, 0);
    //run_all_sorts(50000, 1, 0, 1);
    //run_all_sorts(50000, 1, 1, 0);
    //run_all_sorts(500000, 1, 0, 1);
    //run_all_sorts(500000, 1, 1, 0);
}
