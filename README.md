The parameter edges[] is an ordered list of strings, each representing an edge. The function returns an
instance of Result containing two fields as described below.
Your function will start with an empty system state – by initializing an empty graph data structure. For
each string in edges[] it will parse it to determine if it represents an assignment edge or request edge,
and update the graph accordingly. After inserting each edge into the graph, the function will run an
algorithm that will look for a deadlock (by detecting if a cycle is present in the graph). If deadlock is
detected, your function will stop processing any more edges and immediately return Result:
• with edge_index set to the index of the edge in edges[] that caused the deadlock; and
• with dl_procs[] containing process names that are involved in a deadlock. Order is arbitrary.
If no deadlock is detected after processing all edges, your function will indicate this by returning Result
with edge_index=-1 and an empty dl_procs[].

# deadlock detection - skeleton for Assignment 4

To compile all code, type:
```
$ make
```

To run the resulting code on file test1.txt:
```
$ ./deadlock < test1.txt
```

## IMPORTANT

Only modify and submit the `deadlock_detector.cpp` file. Your TAs will
supply their own versions of the other files (such as main.cpp) to
compile and test your code.

## Test files

These are the correct results for the test files included in this repo.

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


