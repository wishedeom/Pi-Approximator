/*
 *  Assignment 1 - Monte Carlo Pi Approximation
 *  COMP 428 - Parallel Programming
 *  Concordia University
 *
 *  SERIAL VERSION
 *
 *  This program approximates pi by generating random points in a 1 x 1 square and comparing
 *  how many points are in a circle of radius 1/2 to the total number of points.
 */

// Libraries
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/time.h>


// Global constants
const int total_points = 1000000;

// Function prototypes
double approx_pi(int inside, int total);
struct timeval current_timeval(void);
long timeval_diff_us(struct timeval *begin, struct timeval *end);
double rand_coord(void);


// Program entry point
int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int count = 0;
    
    struct timeval begin;
    begin = current_timeval();
    for (int i = 1; i <= total_points; i++)
    {
        double x = rand_coord();
        double y = rand_coord();
        count += x * x + y * y <= 0.25;
    }    

    struct timeval end = current_timeval();
    printf("pi ~ %f in %ld \u03BCs\n", approx_pi(count, total_points), timeval_diff_us(&end, &begin));

    return 0;
}


// Given a number of points inside a square and the number of points that
// land inside an inscribed circle, approximates the value of pi
double approx_pi(int inside, int total)
{
    return 4.0 * inside / total;
}


// Returns a timeval struct representing the current time since the epoch
struct timeval current_timeval(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t;
}

// Computes the difference between two timeval structs in microseconds
long timeval_diff_us(struct timeval *end, struct timeval *begin)
{
    return (end->tv_sec - begin->tv_sec) * 1000000 + end->tv_usec - begin->tv_usec;
}

// Generates a (uniformly distributed) random floating-point number
// in the interval [-0.5, 0.5]
double rand_coord(void)
{
    return ((double)rand()) / RAND_MAX - 0.5;
}

