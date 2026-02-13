# Project 2: Assignment

## Question 1:

This is a C program about a job scheduler using array max-heap to pick the highest priority job.

What it does is it builds max-heap from 11 jobs, inserts urgent job, remove it again, and print heap after each step.

Main functions are:
build_max_heap()
insert_job()
remove_job_by_priority
max_heapify
print_heap()

The program’s flow goes like this: Load - Heapify - Insert - Remove

## Question2:

This is a C program about a priority queue for a smart airport checkout and it uses an array based max-heap.

What it does is it loads 6 passengers with names and risk scores, builds max-heap, shows the screening order, insert a new high-risk passenger, remove that passenger, and it prints heap after each important step.

Main functions are: 
build_max_heap()
insert_passenger(name, risk)
extract_max()
remove_by_risk(risk)
max_heapify()

## Question 3:

This is a C program that finds the cheapest way to connect to 7 smart city hubs with fiber optic cables and it uses the Kruskal’s algorithm.

What it does is it shows the adjacency matrix, collects and sorts all cables that may be linked by cost, runs the Kruskal algorithm which helps pick the cheapest edges and skips cycles.

Main parts of the code are:
Adjacency matrix
Edge list and qsort by weight
Union-Find which is used with path compression to detect cycles
Printing the matrix to Using Kruskal to final edges and cost

## Question 4:

This is a C program that finds a compromised suspected workstation in a network of an enterprise.

What is does is it lets the user enter the suspected compromised workstation, shows the data transfer time which is minutes in this case for each connection, and identifies the neighboring workstation with the highest data transfer rate.

Main parts of the code are:

Hardcoded adjacency matrix
BFS implementation with queue and visited array
Loop that tracks and reports the neighbors with maximu transfer time

## Question 5:

This is a C program that analyzes financial transaction risks among branches in a national bank network.

What it does is it models the banking branches as  a weighted undirected graph, computes the minimum cumulative transaction cost, rebuilds and shows the actual shortes path for each destination, and detects and reports where there is any negative-weight cycles which shows routes that are exploitable or unstable.

Main parts of the code are:

Edge list
Bellman-Ford implementation using relaxation loop, predecessor array to rebuild paths.
Function for recursive path printing
Having a clear table viewing style which shows the branch, min cost, and the full path.

## How to run

Every file has been compiled using gcc filename.c -o filename.
To run the file you need a bash or linux terminal and the command ./filename

## Author

Credo Desparvis Gutabarwa
