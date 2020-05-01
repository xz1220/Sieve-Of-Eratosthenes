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

void Time(double time){
   double time_now=time;
   time_now+=MPI_Wtime();
   printf("time_now:%10.6f\n", time_now);
   fflush(stdout);
}

int main(int argc, char *argv[])
{
   int    count;        /* Local prime count */
   double elapsed_time; /* Parallel execution time */
   int    first;        /* Index of first multiple */
   int    global_count; /* Global prime count */
   int    high_value;   /* Highest value on this proc */
   int    i;
   int    id;           /* Process ID number */
   int    index;        /* Index of current prime */
   int    low_value;    /* Lowest value on this proc */
   char  *marked;       /* Portion of 2,...,'n' */
   int    n;            /* Sieving from 2, ..., 'n' */
   int    p;            /* Number of processes */
   int    proc0_size;   /* Size of proc 0's subarray */
   int    prime;        /* Current prime */
   int    size;         /* Elements in 'marked' */
   int    prime_store;
   int   *prime_save;

   // double elapsed_time2;
   // double elapsed_time3;

   MPI_Init(&argc, &argv);

   /* Start the timer */

   MPI_Comm_rank(MPI_COMM_WORLD, &id);
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   MPI_Barrier(MPI_COMM_WORLD);
   elapsed_time = -MPI_Wtime();
   // elapsed_time2 = -MPI_Wtime();

   if (argc != 2) {
      if (!id) printf("Command line: %s <m>\n", argv[0]);
      MPI_Finalize();
      exit(1);
   }

   n = atoi(argv[1]);

   /* Figure out this process's share of the array, as
      well as the integers represented by the first and
      last array elements */

   // low_value = 2 + id*(n-1)/p;
   // high_value = 1 + (id+1)*(n-1)/p;
   low_value=0;
   int temp=(n-1)/p;
   for (i=0;i<id;i++){
      low_value+=temp;
   }
   low_value+=2;

   if((n-low_value)>(n-1)/p){
      high_value=low_value+temp-1;
   }else{
      high_value = n;
   }
   size = high_value - low_value + 1;

   if (low_value%2==0){
     size=size>>1;
     low_value+=1;
   }else{
     size=size%2+size>>1;
   }


   /* Bail out if all the primes used for sieving are
      not all held by process 0 */

   proc0_size = (n-1)/p;
   int sqrt_n=(int) sqrt((double) n);
   prime_store=sqrt_n/2;
   if ((2 + proc0_size) < sqrt_n) {
      if (!id) printf("Too many processes\n");
      MPI_Finalize();
      exit(1);
   }

   // elapsed_time2= -MPI_Wtime();
   /* Allocate this process's share of the array. */
   // elapsed_time2=-MPI_Wtime();
   marked = (char *) malloc(size);
   prime_save = (int *)malloc(prime_store*sizeof(int));
   // if (!id) Time(elapsed_time2);

   if (marked == NULL) {
      printf("Cannot allocate enough memory\n");
      MPI_Finalize();
      exit(1);
   }

   for (i = 0; i < size; i++) marked[i] = 0;
   for (i = 0; i < prime_store; i++) prime_save[i] =0;

   int j=0;
   index=0;
   for (i=0;i<prime_store; i++){
      if (prime_save[i]==0){
         int prime_temp=2*i+3;
         prime_save[j]=prime_temp;
         j++;

         for (index=i+prime_temp;index<prime_store;index+=prime_temp){
            prime_save[index]=1;
         }
      }
   }
   // if (!id) Time(elapsed_time2);

   // elapsed_time3= -MPI_Wtime();
   int cacheline = (1<<12)*6;
   int number,multi_cacheline=0;
   int high_value_temp;
   for (number = 0; number < size / cacheline + 1;number++){
      index = 0;
      high_value_temp=(multi_cacheline + cacheline<size)?(number+1)*cacheline:size;
      // if (!id) printf("low_temp %d   high_temp : %d\n",low_value,high_value_temp);
      // fflush(stdout);
      for (prime = prime_save[index]; index<j; prime = prime_save[++index])
      {
         if (prime * prime > low_value)
         first = (prime * prime - low_value);
         else {
            if (!(low_value % prime)) first = 0;
            else first = (prime - (low_value % prime));
         }
         if (first%2) first+=prime;
         first=first>>1;
         // if (!id) printf("first %d   id : %d\n",first,id);
         // fflush(stdout);
         for (i = first+multi_cacheline; i < high_value_temp; i += prime) {
            marked[i] = 1;
            // if (!id) printf("marked %d   id : %d\n",i,id);
            // fflush(stdout);
         }
      }
      multi_cacheline+=cacheline;
      low_value += cacheline*2;
   }

      // if (!id) {
      //    while (marked[++index]);
      //    prime = (index+1)*2+1;
      // }
      // if (p > 1) MPI_Bcast(&prime,  1, MPI_INT, 0, MPI_COMM_WORLD);
      // } while(prime * prime <= n);
      count = 0;
   for (i = 0; i < size; i++)
      if (!marked[i]) count++;

   if (p > 1) MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM,
      0, MPI_COMM_WORLD);
   else global_count=count;
   /* Stop the timer */

   elapsed_time += MPI_Wtime();


   /* Print the results */

   if (!id) {
      printf("There are %d primes less than or equal to %d\n",
         global_count+1, n);
      printf("SIEVE (%d) %10.6f\n", p, elapsed_time);
   }
   MPI_Finalize();
   return 0;
}
