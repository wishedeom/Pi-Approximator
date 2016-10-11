/*
 *  Assignment 1 - Monte Carlo Pi Approximation
 *  COMP 428 - Parallel Programming
 *  Concordia University
 *
 *  PARALLEL VERSION
 *
 *  This program approximates pi by generating random points in a 1 x 1 square and comparing
 *  how many points are in a circle of radius 1/2 to the total number of points.
 */

// Libraries
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/time.h>


// Global constants
const int total_points = 1000000;
const int master = 0;


// Function prototypes
double approx_pi(int inside, int total);
struct timeval current_timeval(void);
long timeval_diff_us(struct timeval *begin, struct timeval *end);
double rand_coord(void);


// Program entry point
int main(int argc, char *argv[])
{
    int rank,       // 0 for master, other for worker
        num_tasks;

    MPI_Init(&argc, &argv);
    MPI_Comm everyone;
    MPI_Comm_spawn(argv[0], MPI_ARGV_NULL, 10, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &everyone, MPI_ERRCODES_IGNORE);
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(rank | time(NULL));
   
    int num_workers = num_tasks == 1 ? 1 : (num_tasks - 1);
    int points = total_points / num_workers;
    int count = 0;
    int total_count;
    
    struct timeval begin;
    if (rank == master)
    {
        begin = current_timeval();
    }
    else if (rank != master || num_tasks == 1)
    {
        if (rank == 1 || num_tasks == 1)
        {
            points += total_points % num_workers;
        }
        
        for (int i = 1; i <= points; i++)
        {
            double x = rand_coord();
            double y = rand_coord();
            count += x * x + y * y <= 0.25;
        }    
    }
    
    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, master, MPI_COMM_WORLD);
    
    if (num_tasks == 1)
    {
        total_count = count;
    }

    if (rank == master)
    {
        struct timeval end = current_timeval();
        printf("With %d processes pi ~ %f in %ld \u03BCs\n", num_tasks,
                approx_pi(total_count, total_points), timeval_diff_us(&end, &begin));
    }

    MPI_Finalize();

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

