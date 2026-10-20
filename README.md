# Data Structures and Algorithms

C assignments from the 2024 summer semester course.

## Programs

- `gcd_calculator.c` calculates the greatest common divisor of multiple pairs of unsigned integers.
- `dijkstra_shortest_path.c` manages a weighted undirected graph and finds shortest paths with Dijkstra's algorithm and a min-heap.
- `prime_generator.c` prints all prime numbers in a chosen range.
- `hash_table_accounts.c` stores, searches, updates, and deletes account records in a hash table.
- `minimum_spanning_tree_prim.c` builds a minimum spanning tree with Prim's algorithm.
- `rational_number_binary_search.c` searches for rational-number values in a sorted sequence using binary search.
- `avl_tree.c` stores people in an AVL self-balancing binary search tree with insertion, lookup, deletion, and range search.
- `bracket_validator.c` validates matching parentheses and brackets using a stack.

## Compile

Compile any program with Clang:

```sh
clang -std=c11 -Wall -Wextra -Wpedantic program.c -o program
./program
```

Replace `program.c` and `program` with the selected source filename and output name.
