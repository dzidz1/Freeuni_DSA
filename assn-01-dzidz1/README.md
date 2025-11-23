# DSA Assignments - Problem Descriptions

## Assignment 1: Two Rectangles

**Time limit per test:** 1 second  
**Memory limit per test:** 256 megabytes

### Problem Statement

Given N distinct points with different coordinates on a two-dimensional plane (3≤N≤50000). Place them inside two rectangles such that the sum of the areas of these rectangles is minimized. The sides of the rectangles must be parallel to the x and y coordinate axes. The rectangles must not intersect or touch each other. Points are allowed to lie on the edges of the rectangles. It is possible for one of the rectangles to have an area equal to 0 (zero width and/or zero height).

### Input

The first line contains one integer N, which indicates the number of points. Each of the next N lines contains two integers - the coordinates of the corresponding point. Coordinates are positive integers in the range from one to one billion.

### Output

A single line with one integer - the difference between two values: the area that would be needed to cover all points with one rectangle, minus the minimum total area of two rectangles that also covers all points.

### Example

**Input:**

```
5
3 3
3 5
5 3
5 5
10 11
```

**Output:**

```
52
```

### Note

For the test case given in the example, to cover all points with one rectangle, we would need a rectangle whose bottom-left point is (3,3) and top-right point is (10,11). Its area would be (10-3)×(11-3)=56. In the case of covering with two rectangles, we cover the first 4 points with a rectangle of area 2×2, and the fifth point with a rectangle of area 0. The total area is 4, and the difference value is 52.

---

## Assignment 2: Sum of Primes

**Time limit per test:** 1 second  
**Memory limit per test:** 256 megabytes

### Problem Statement

Let N be a positive integer. Denote by SUM(N) the number of ways in which N can be represented as the sum of two or more prime numbers. For example, SUM(9)=4, because 9=2+2+2+3=2+2+5=2+7=3+3+3. Let P be the smallest prime number that is greater than N. Write a program that finds the remainder when SUM(N) is divided by P.

### Input

One integer - N (2<N<50000).

### Output

One integer - the remainder when SUM(N) is divided by P.

### Example

**Input:**

```
9
```

**Output:**

```
4
```
