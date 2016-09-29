/*
 *  Assignment 1 - Monte Carlo Pi Approximation
 *  COMP 428 - Parallel Programming
 *  Concordia University
 *
 *  This program approximates pi by generating random points in a 1 x 1 square and comparing
 *  how many points are in a circle of radius 1/2 to the total number of points.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int num_threads = 10;
const int points_per_thread = 1000000;

double approx_pi(int inside, int total);
double rand_norm(void);
void *throw_darts(void *count);
void print_counts(int counts[], int n);

int main(int argc, char* argv[])
{
    srand((unsigned int) time(NULL));
    pthread_t threads[num_threads];

    int counts[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        counts[i] = 0;
        pthread_create(&threads[i], NULL, throw_darts, &counts[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    int total_count = 0;
    for (int i = 0; i < num_threads; i++)
    {
        total_count += counts[i];
    }
 
    double pi = approx_pi(total_count, points_per_thread * num_threads);
    printf("pi ~ %f\n\n", pi);

    print_counts(counts, num_threads);

    return 0;
}

double approx_pi(int inside, int total)
{
    return 4.0 * inside / total;
}

double rand_norm(void)
{
    return ((double)rand()) / RAND_MAX;
}

void *throw_darts(void *count)
{
    int *icount = (int*) count;
    for (int i = 0; i < points_per_thread; i++)
    {
        double x = rand_norm() - 0.5;
        double y = rand_norm() - 0.5;
        *icount += x * x + y * y <= 0.25;
    }

    return NULL;
}

void print_counts(int counts[], int n)
{
    printf("Thread\tCount\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\n", i, *(counts + i));
    }
}

