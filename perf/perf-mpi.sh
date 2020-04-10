#!/usr/bin/zsh

# chmod 777 ./perf-mpi.sh  :fix bugs of permission denied

# output the cache-misses of programs
# mpirun <command> ./perf-mpi.sh  .Also change the parameters of perf to check 
# more performance indicators
#perf stat  -e cache-misses /home/xingzheng/mpi-exp/bin/sieve3
perf stat  -e cache-misses /home/xingzheng/mpi-exp/bin/sieve4