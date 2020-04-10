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
   int    prime_size;
   char  *prime_marked;
   int  *prime_store;
   int    sqrt_n;



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

   n = atoi(argv[1]);

   /* Figure out this process's share of the array, as
      well as the integers represented by the first and
      last array elements */

   low_value = 2 + (id)*(n-1)/p;
   high_value = 1 + (id+1)*(n-1)/p;
   size = high_value - low_value + 1;
   prime_size=((n-1)/p)>>1;
   //printf("数值初始化成功！");
   //fflush(stdout);

   if (low_value%2==0){
     size=size>>1;
     low_value+=1;
   }else{
     size=size%2+size>>1;
   }


   /* Bail out if all the primes used for sieving are
      not all held by process 0 */

   proc0_size = (n-1)/p;
   sqrt_n= (int) sqrt((double) n);
   //printf("sqrt_n:%d,prime_size:%d\n",sqrt_n,prime_size);
   if ((2 + proc0_size) < sqrt_n ){
      if (!id) printf("Too many processes\n");
      MPI_Finalize();
      exit(1);
   }

   /* Allocate this process's share of the array. */

   marked = (char *) malloc(size*sizeof(char));
   prime_marked=(char *) malloc(prime_size*sizeof(char));
   prime_store = (int *)malloc(sqrt_n*sizeof(int));

   if (marked == NULL) {
      printf("Cannot allocate enough memory\n");
      MPI_Finalize();
      exit(1);
   }

   if (prime_marked == NULL) {
      printf("Cannot allocate enough memory\n");
      MPI_Finalize();
      exit(1);
   }

   if (prime_store == NULL) {
      printf("Cannot allocate enough memory\n");
      MPI_Finalize();
      exit(1);
   }


   for (i = 0; i < size; i++) marked[i] = 0;
   for (i = 0; i < prime_size; i++)
      prime_marked[i] = 0;
   for (i=0;i<sqrt_n;i++) prime_store[i]=0;
   //printf("初始化成功");
   //fflush(stdout);
   int store = 0;
   for (i=0;i<sqrt_n;i++){
      if (prime_marked[i]==0){
         int prime_temp=(i + 1) * 2 + 1;
         int j;
         for (j=i ; j < prime_size; j += prime_temp)
         {
            // if (j==5) printf("prime_temp:%d\n",prime_temp);
            prime_marked[j] = 1;
         }
         prime_store[store] = prime_temp;
         store++;
         //printf("%d\n", prime_temp);
      }
   }

   // if (!id) Time(elapsed_time);

   int j = 0;
   for (prime = prime_store[j]; prime * prime <= n; prime = prime_store[++j])
   {
      if (prime * prime > low_value)
        first = (prime * prime - low_value);
      else {
         if (!(low_value % prime)) first = 0;
         else first = (prime - (low_value % prime));
      }
      if (first%2) first+=prime;
      first=first>>1;
      for (i = first; i < size; i += prime) marked[i] = 1;
   }
//     for (i=0;i<store;i++){
//        printf("id:%d, prime_store[%d]:%d\n",id,i,prime_store[i]);
//    }
//    printf("prime:%d, n:%d, j:%d\n",prime_store[j],n,j);
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
