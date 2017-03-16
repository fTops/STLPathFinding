# STLPathFinding

## Description

STLPathFinding is a console application written in **C++** and using **STL** data structures which implements a [pathfinding algorithm](https://en.wikipedia.org/wiki/Pathfinding) of finding the shortest path between two points in a 2D grid. It is based on the common [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) and solves the following problem on Kattis: [https://paradox.kattis.com/problems/paradoxpath](https://paradox.kattis.com/problems/paradoxpath)

## Basic information on how it works:

In A*, each node discovered in the search for the target is given three costs; g, h and f.

- g is the cost it takes to reach the discovered node from the start, or in other words +1 for every move in the grid.
- h is the cost it takes to reach the target from the discovered node and it is calculated heuristically using the [Manhattan distance](https://en.wikipedia.org/wiki/Taxicab_geometry)
- f is the sum of g an h (f = g + h)

The basic algorithm works like this:

- Begin with the starting node in the Open Set
- Find the node with the lowest f cost in the Open Set and terminate if it's the target
- Otherwise, if the node is not already in the Closed Set insert it
- Search if it's possible to traverse to each of its neighbors (up, down, left, right)
- If yes and the discovered nodes haven't already been inserted in the Closed Set, insert them to the Open Set
- Repeat until either the target node is reached or the Open Set empties

## Implementation

For the Open Set, because its main purpose is to always provide the node that has the lowest f cost, the data structure of a min priority queue has been chosen. STL's implementation of a priority queue comes with the caveat that it doesn't provide a way of accessing any other but its top (min or max) element. This makes checking the Open Set for past appearances of a node before it is inserted impossible. This has been taken into account and as such discovered nodes are always inserted in the Open Set. Later, because the priority queue always serves the node with the lowest F cost, the "duplicates" can be discarded safely.

The Closed Set has been set up as a deque. This is because the it will be traversed backwards (from target to start) once the search completes succesfully, so it makes sense to use a data structure which can insert/delete new elements to/from its front.

Finally there's an array in which an indication is saved if a node has already been inserted into the Closed Set.

## Compiling

The repository includes the complete Visual Studio 2015 solution. As it's common with VS projects, it uses *#pragma once* and #include(s) the *stadfx.h* file with precompiled headers, so swap those out if using an incompatible compiler.
