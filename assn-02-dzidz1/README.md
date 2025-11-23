# Assignment 2: Bit Operations and Bird Migration

## Problem A: Bit Inversion

**Time limit per test:** 1 second  
**Memory limit per test:** 256 megabytes

### Problem Statement

Given a sequence of N bits, initially all set to 0. Bits are numbered from 1 to N. Two types of operations are performed:

1. **Type 0 (Inversion)**: Given two indices, invert all bits between them (inclusive). Inversion means changing 0 to 1 and 1 to 0.
2. **Type 1 (Count)**: Given two indices, count how many bits in that range have value 1 (inclusive).

### Input

- First line: two integers N (1<N≤100000) and K (1<K≤100000) - number of bits and operations
- Next K lines: three integers each
  - First integer: operation type (0 or 1)
  - Second and third integers: range indices for the operation

### Output

For each Type 1 operation, output one integer on a separate line - the count of ones in the specified range.

### Example

**Input:**

```
7 4
0 2 4
0 3 6
1 1 3
1 5 7
```

**Output:**

```
1
2
```

### Note

After first operation: 0111000  
After second operation: 0100110  
Third operation counts ones in [1,3]: answer is 1  
Fourth operation counts ones in [5,7]: answer is 2

---

## Problem B: Bird Migration

**Time limit per test:** 1 second  
**Memory limit per test:** 256 megabytes

### Problem Statement

It's autumn and birds are flying to warmer countries. Before crossing the Black Sea, they rest on a power line that can be represented as N (1≤N≤500000) positions numbered from 1 to N. Initially all positions are empty. During the day, M (1≤M≤300000) events occur:

1. **Type 1**: A flock of p birds (1≤p≤N) arrives. They want to sit on a continuous block of p positions. If multiple such blocks exist, they choose the one starting with the smallest number. If no such block exists, the birds continue flying without rest.

2. **Type 2**: Given two numbers a and b (1≤a,b≤N). All birds in the range [a, a+b-1] leave the power line and those positions become free.

### Input

- First line: two integers N and M
- Next M lines: each describes an event
  - Format "1 p": a flock of p birds arrives
  - Format "2 a b": positions [a, a+b-1] become free

### Output

For each Type 1 event, output one integer on a separate line:

- The smallest position number where the birds landed, or
- 0 if the flock couldn't find enough free consecutive positions

### Example

**Input:**

```
10 4
1 6
2 2 3
1 5
1 2
```

**Output:**

```
1
0
2
```

### Note

Total 10 positions and 4 events:

1. Flock of 6 birds occupies positions 1-6
2. Positions 2-4 become free
3. Flock of 5 birds arrives, but not enough consecutive free positions (output: 0)
4. Last flock of 2 birds occupies positions 2-3 (output: 2)
