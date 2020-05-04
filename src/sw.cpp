/*
 *   Sieve of Eratosthenes
 *
 *   Programmed by Michael J. Quinn
 *
 *   Last modification: 7 September 2001
 */

#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) ((a)<(b)?(a):(b))

int main(int argc, char *argv[])
{
  int   count;        /* Local prime count */
   double elapsed_time; /* Parallel execution time */
   long    first;        /* Index of first multiple */
   int    global_count; /* Global prime count */
   long    high_value;   /* Highest value on this proc */
   long    i;
   int   id;           /* Process ID number */
  int  index;        /* Index of current prime */
   long    low_value;    /* Lowest value on this proc */
   char  *marked;       /* Portion of 2,...,'n' */
  long    n;            /* Sieving from 2, ..., 'n' */
   int    p;            /* Number of processes */
   long    proc0_size;   /* Size of proc 0's subarray */
   int    prime;        /* Current prime */
  unsigned int    size;         /* Elements in 'marked' */

   MPI_Init(&argc, &argv);

   /* Start the timer */

   MPI_Comm_rank(MPI_COMM_WORLD, &id);
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   MPI_Barrier(MPI_COMM_WORLD);
   elapsed_time = -MPI_Wtime();

   if (argc != 2) {
      if (!id) printf("Command line: %s <m>\n", argv[0]);
      MPI_Finalize();
      exit(1);
   }

   n = atol(argv[1]);

   /* Figure out this process's share of the array, as
      well as the integers represented by the first and
      last array elements */

   low_value = 2 + id*((n-1)/p);
   high_value = 1 + (id+1)*((n-1)/p);
   size = high_value - low_value + 1;


   /* Bail out if all the primes used for sieving are
      not all held by process 0 */

   proc0_size = (n-1)/p;
   printf("%ld , %ld , %ld ,%ld,%d,%d,size:%d\n", proc0_size,n,low_value,high_value,id,p,size);


   if ((2 + proc0_size) < (int) sqrt((double) n)) {
      if (!id) printf("Too many processes\n");
      MPI_Finalize();
      exit(1);
   }

   /* Allocate this process's share of the array. */

   marked = (char *) malloc(size);
   printf("neicun fenpei wan cheng : id :%d\n", id);
   if (marked == NULL) {
      printf("Cannot allocate enough memory\n");
      MPI_Finalize();
      exit(1);
   }

   for (i = 0; i < size; i++) marked[i] = 0;
   printf("jin ru xun huan zhi qian : id :%d\n", id);


   if (!id) index = 0;
   prime = 3;
   do {
      if (prime * prime > low_value)
        first = (prime * prime - low_value);
      else {
         if (!(low_value % prime)) first = 0;
         else first = (prime - (low_value % prime));
      }
      if (first%2) first+=prime;
      first=first>>1;
      for (i = first; i < size; i += prime) marked[i] = 1;
      if (!id) {
         while (marked[++index]);
         prime = (index+1)*2+1;
      }
      if (p > 1) MPI_Bcast(&prime,  1, MPI_INT, 0, MPI_COMM_WORLD);
   } while(prime * prime <= n);

   printf("xunhuan jieshu  : id :%d\n", id);
   count = 0;
   for (i = 0; i < size; i++)
      if (!marked[i]) count++;
   if (p > 1) MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM,
      0, MPI_COMM_WORLD);

   /* Stop the timer */

   elapsed_time += MPI_Wtime();


   /* Print the results */

   if (!id) {
      printf("There are %d primes less than or equal to %ld\n",
         global_count+1, n);
      printf("SIEVE (%d) %10.6f\n", p, elapsed_time);
   }
   MPI_Finalize();
   return 0;
}
