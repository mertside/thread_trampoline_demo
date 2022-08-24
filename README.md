# Samples for implementing a Thread Trampoline

Some samples on the idea of implementing pthreads. 

## Thread Trampoline

***Algorithm:*** Look at a memory address during spin-wait; 

> if zero, sleep; 

> if not, go to this address (it contains a function pointer). 

## Thread Pools

Implements a queue of tasks to be executed by threads.
