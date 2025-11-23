# Assignment 3: Pairs and Restaurant

## Problem A: Pairs

**Time limit per test:** 0.25 seconds  
**Memory limit per test:** 256 megabytes

### Problem Statement

Given two sequences A and B. The first consists of N integers, the second of M integers. You need to choose an X-element subset from the first sequence, an X-element subset from the second sequence, and sort both subsets. How many ways are there such that every element of the sorted subset chosen from set A is greater than the corresponding element of the sorted subset chosen from set B? Equal elements at different indices create different variants.

### Input

- First line: three integers N, M, and X (1<N≤1000, 1<M≤1000, 1≤X≤10, and X does not exceed M and N)
- Second line: N integers - elements of sequence A
- Third line: M integers - elements of sequence B

### Output

A single integer - the number of ways to choose X pairs according to the above condition. Output the answer modulo 1,000,000,009.

### Example

**Input:**

```
4 5 2
3 7 7 8
1 4 6 8 11
```

**Output:**

```
15
```

### Note

Example pairs: 3,7(first)→1,4; 3,7(second)→1,4; 3,7(first)→1,6; 3,7(second)→1,6; 3,8→1,4; 3,8→1,6; 7,7→1,4; 7,7→1,6; 7,7→4,6; 7(first),8→1,4; 7(second),8→1,4; 7(first),8→1,6; 7(second),8→1,6; 7(first),8→4,6; 7(second),8→4,6

---

## Problem B: Restaurant

**Time limit per test:** 0.25 seconds  
**Memory limit per test:** 256 megabytes

### Problem Statement

Buba's restaurant has become very popular and is visited daily by N (1≤N≤40000) customers in the same sequence. The restaurant prepares M (1≤M≤N) dishes, numbered from 1 to M. The i-th customer orders only one dish P_i (1≤P_i≤M). The restaurant needs K\*K time to clean up after preparing K different dishes. To save time, Buba lets customers in by groups, naturally maintaining their original order. After a group leaves, Buba cleans the restaurant and lets in the next group. Calculate the minimum total time needed to clean the restaurant after serving all customers.

### Input

- First line: two integers N and M
- Next N lines: one integer P_i each (dish ordered by i-th customer)

### Output

A single integer - the minimum time needed to clean the restaurant.

### Example

**Input:**

```
13 4
1
2
1
3
2
2
3
4
3
4
3
1
4
```

**Output:**

```
11
```

### Note

Explanation: According to the service, the first 4 groups contain one customer each. The fifth group has 2 clients. The sixth group has 5 clients who order dishes 3, 4, 3, 4, 3 respectively, which requires 4 time units to clean. Buba put one person each in the last two groups. Total cleaning time is 11.
