# Deadlock Detection Program

## Overview

This project implements a deadlock detection algorithm in C++. The algorithm processes a list of resource allocation and request edges to detect any deadlocks in the system. When a deadlock is detected, the algorithm stops and returns the index of the edge causing the deadlock along with the processes involved.

### Implementation

1. **Initialization**:
   - Initialize the `Result` structure with `edge_index = -1`
   - Initialize a graph representation using an adjacency list and an out-degree count for each node
   - Use unordered sets to keep track of processes and resources

2. **Processing Edges**:
   - For each edge, split the string to extract the nodes and update the sets of processes and resources
   - Update the adjacency list and out-degree counts based on the edge type (request or assignment)

3. **Topological Sorting**:
   - Perform a topological sort to detect cycles. Nodes with zero out-degrees are processed, and their out-degrees are decremented
   - If a cycle is detected (nodes with non-zero out-degrees after sorting), identify the processes involved and update the `Result` structure

4. **Return Result**:
   - If a deadlock is detected, return the `Result` structure with the edge index and list of processes
   - If no deadlock is detected after processing all edges, return the `Result` with `edge_index = -1` and an empty list of processes.

### Compilation

To compile all code, type:
```
$ make
```

To run the resulting code on file test1.txt:
```
$ ./deadlock < test1.txt
```


## Test files

These are the correct results for the test files included in this repo

| filename   | correct `edge_index` | correct `dl_procs` | minimum timings     | good timings     |
| :---------- | :-------------: | :-----------: | :-----------------: | :--------------: |
| `test1.txt` | `-1`            | `[]`          | `0.0000s`           | `0.0000s`        |
| `test2a.txt`| `6`             | `[4,5,7]`     | `0.0000s`           | `0.0000s`        |
| `test2b.txt`| `5`             | `[5,7]`       | `0.0000s`           | `0.0000s`        |
| `test3a.txt`| `3`             | `[p7,p3]`     | `0.0000s`           | `0.0000s`        |
| `test3b.txt`| `-1`            | `[]`          | `0.0000s`           | `0.0000s`        |
| `test4.txt` | `3`             | `[12,7]`      | `0.0000s`           | `0.0000s`        |
| `test5.txt` | `6`             | `[2,77]`      | `0.0000s`           | `0.0000s`        |
| `test6.txt` | `9903`          | `[ab,cd,ef]`  |`8.9431s`            | `0.8771s`        |
| `test7.txt` | `29941`         | `[is,this,answer,the,correct]`  |`191.7872s`    | `8.0726s`        |


