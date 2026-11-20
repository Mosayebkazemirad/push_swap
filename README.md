This activity has been created as part of the 42 curriculum by gkudelka, mkazemir.
push_swap
Description

push_swap sorts integers using two stacks and a limited set of instructions. Stack A starts with the input numbers, stack B is empty, and the program prints the operations needed to leave A sorted in ascending order. The aim is to use as few operations as possible.

The allowed instructions are sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb and rrr.

We divided the work into two main areas:

    mkazemir: input parsing and validation, linked-list stacks, stack operations and memory cleanup.
    gkudelka: ranking and disorder, sorting strategies, adaptive selection, sorting helpers, benchmarking and output optimization.

We also worked on bringing the parts together and checking that the resulting program behaved correctly.
Instructions

Compile the project with:

make

The Makefile also provides clean, fclean and re.

Run the program with a list of integers. The default mode is --adaptive; the other flags force a particular sorting strategy.

./push_swap 4 1 3 2
./push_swap --simple 4 1 3 2
./push_swap --medium 4 1 3 2
./push_swap --complex 4 1 3 2
./push_swap --adaptive 4 1 3 2

Arguments can also contain several numbers in one quoted string:

./push_swap "4 1" 3 2

Operations are written to stdout, so the result can be passed to a Push_swap checker. --bench prints the initial disorder, the selected strategy, the total operation count and the counts for all eleven instructions to stderr.

ARG="4 1 3 2"
./push_swap --bench $ARG 2> bench.txt | ./checker_linux $ARG
cat bench.txt

The checker is a separate tool and is not built by our Makefile. With no arguments, the program prints nothing. Invalid numbers, duplicates or invalid flag combinations produce Error on stderr.
Input, stacks and operations (mkazemir)
Reading the arguments

The first part of the program handles the command-line arguments before sorting starts. select_strategy() separates optional flags from the numbers. The remaining arguments are passed to input_check(), which builds stack A.

The parser accepts individual integers and whitespace-separated numbers inside quoted arguments. ps_read_number() handles an optional + or - sign and checks the integer limit while reading the digits, before an overflow can happen. This covers values from INT_MIN to INT_MAX. Text that is not a valid integer, an empty argument and numbers outside that range are rejected.

ps_append_number() checks for duplicates before adding each number. This check searches the nodes already in A, so input validation can take O(n²) CPU work for n values. That is separate from the sorting-operation counts used for the project benchmarks.

Relevant files: check_input.c, parse_numbers.c, parse_stack.c and the flag handling in push_swap.c.
How the stacks are stored

Both stacks use singly linked lists. Each t_stack node stores the original number (n), its sorting rank and a pointer to the next node. The head pointer is the top of the stack; a NULL pointer marks its end. Stack B starts as NULL.

When parsing, new nodes are appended to A in input order and their rank starts at -1. Ranking happens later, just before sorting. The two stacks share the same node type, so moving a number between them means relinking a node rather than allocating a new one.
The eleven instructions

The operations are grouped into three basic actions:

    Swap (sa, sb, ss): exchange the top two nodes of A, B or both.
    Push (pa, pb): remove the top node from one stack and put it on top of the other.
    Rotate (ra, rb, rr) and reverse rotate (rra, rrb, rrr): move the first node to the end or the last node to the front. The combined instructions change both stacks but print only one instruction.

These functions mainly change pointers. In a singly linked list, ordinary and reverse rotation must also walk the list to find the end (or the node before the end). Every operation updates the stacks and prints its own instruction through the shared output function.

Relevant files: push.c, swap.c, rotate.c, rev_rotate.c and libft.c.
Errors and cleanup

If an argument is invalid, a duplicate is found or an allocation fails while building the input, ps_input_error() frees the nodes allocated so far, prints Error followed by a newline to stderr and exits with an error status. free_stack() also releases both stacks at the end of a normal run.

This keeps diagnostic output separate from the operation stream that the checker reads. The input data itself takes O(n) memory for n nodes.
Ranking and sorting (gkudelka)
Ranking and disorder

Before sorting, get_ranked() assigns every value a rank from 0 to n - 1. The smallest number gets rank 0, the next smallest rank 1 and so on. This lets the algorithms work with consecutive ranks even when the original input includes negative or widely separated numbers.

calc_disorder() measures how mixed up the original stack is. It counts inversions: pairs where a larger rank appears before a smaller one. The result is:

disorder = inversions / (n * (n - 1) / 2)

A sorted input has disorder 0, a reverse-sorted input has disorder 1, and an input with fewer than two numbers is treated as disorder 0.
Adaptive selection

The default strategy is selected from the initial disorder. We use the exact thresholds required by the subject:
Disorder 	Strategy 	Operation bound
Below 0.2 	Simple 	O(n²)
0.2 to below 0.5 	Medium 	O(n√n)
0.5 or higher 	Complex 	O(n log n)

The lower the disorder, the more existing order we can try to preserve. On more mixed inputs, balanced partitioning gives us a better upper bound. These boundaries are required by the assignment, not thresholds chosen from benchmark results.

sort_stack() calculates ranks and disorder once, selects the strategy, and runs shared quick checks before entering the larger algorithm. For example, an already sorted stack, a rotated sorted stack or a very small input can often be handled directly. A strategy flag overrides Adaptive's choice; the quick checks are shared optimizations.
Simple: LIS and greedy insertion

Main files: simple_algo.c, find_lis.c, greedy_sort.c, get_move.c, call_rotations.c.

Simple starts by finding a Longest Increasing Subsequence (LIS). Its elements are in increasing order but do not have to be next to each other in A. We leave that subsequence in A and push the remaining values to B.

We then look at the possible insertions from B back into A. For each candidate, the algorithm calculates its target position and the number of rotations needed. If both stacks rotate in the same direction, rr or rrr can combine two moves. We choose the cheapest candidate, insert it, and repeat until B is empty. Finally, A is rotated to put rank 0 at the top.

The method uses at most O(n²) Push_swap operations: there are at most n insertions, each requiring at most O(n) rotations. Its marking array uses O(n) additional memory. If that allocation fails, a simpler selection-sort fallback remains available.
Medium: natural run, limited greedy, then chunks

Main files: medium_algo.c, greedy_sort.c, medium_chunks.c.

Medium first finds the longest contiguous increasing run. Unlike the LIS used by Simple, the numbers in this run must be next to each other. It keeps that run in A and tries the same cheapest-insertion approach, with a limit of 12 * n operations.

This is a real sorting attempt, not a simulation. If it cannot finish within that budget, the program moves the remaining elements from B back to A and switches to the chunk fallback.

The fallback uses rank windows of width ceil(√n). It processes the windows in ascending order, pushing matching ranks to B, and then retrieves the ranks in descending order to rebuild A.

The O(n√n) operation bound comes from the chunks: there are about √n windows, each taking at most O(n) pushes and rotations to fill. In B, the pushed windows remain cyclically grouped, so retrieving the next rank takes O(√n) rotations, including transitions between neighboring windows (a conservative bound is about 2√n). Across n removals, this is O(n√n). The abandoned greedy attempt adds only O(n) operations, as does returning B to A. Medium uses O(n) extra memory for its marking array.

The repeated searches for ranks and cheap moves can take noticeably more CPU time than the number of emitted operations suggests. The subject's stated complexity model, however, measures the generated Push_swap instructions.
Complex: recursive partitioning

Main files: complex_algo.c, split_b.c, sort_three.c, sort_four.c.

Complex divides each rank range around its midpoint. Lower ranks move from A to B, while higher ranks remain in A. split_a() and split_b() recursively process those groups and put them back together in sorted order. Small groups of two to four values are handled by dedicated helpers.

Each level processes at most O(n) stack moves across its partitions, and the rank ranges are divided roughly in half. That gives O(log n) levels and O(n log n) generated operations. The recursive calls use O(log n) call-stack space, apart from the fixed-size output-optimizer buffers.
Output optimization and benchmarking

Complex also runs an optimizer over the instructions it produces. It can cancel inverse rotations and combine compatible operations, such as ra and rb into rr, without changing the final stack state. The optimizer works on the output instructions, not on the algorithm's choice of partitions.

The --bench counters track the instructions actually written, including the optimizer's combined instructions, rather than counting discarded intermediate operations. --bench never changes the instruction stream sent to the checker.

Relevant files: ps_opt_*.c, bench_state.c, bench_format.c, bench_output.c.
Why we changed the sorting approaches

Earlier versions used straightforward minimum extraction, basic chunks and binary radix. They were easier to implement and sorted correctly, but often used more instructions than necessary. We moved to LIS and natural runs to preserve order already present in the input, and to recursive partitioning for a predictable high-disorder bound. Shared helpers and quick checks reduce unnecessary operations in common cases.

The important distinction in our complexity arguments is between CPU work (searching and comparing values in C) and Push_swap operations (the instructions printed for the checker). The assignment measures the second one. The passing benchmarks are fewer than 2,000 operations for 100 random numbers and fewer than 12,000 for 500 random numbers.
Resources

    42 Push_swap subject, version 1.2: requirements, allowed operations, disorder rules and performance benchmarks.
    CP-Algorithms: Longest Increasing Subsequence: background for the LIS approach.
    Quicksort: background on divide-and-conquer partitioning; our version uses two stacks rather than an array.
    C library documentation for malloc, free, write and limits.h: relevant to memory handling, output and integer-range validation.

AI usage: We used AI to discuss sorting approaches, help with parts of the implementation and refactoring, investigate bugs, devise tests and check explanations. It also helped draft and revise this README. We compared the resulting code and descriptions with the actual source, compiled the project and tested the emitted operations with a checker.