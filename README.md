# Maze Solver

**C++ implementation** of a maze solver that uses the **A\*** (A-star) algorithm to find the shortest path from a start point `'S'` to an exit point `'E'` in a text-based maze.

## Problem Description

The maze is represented as a grid of characters in a text file where:
- `'S'` represents the start point.
- `'E'` represents the exit point.
- `'#'` represents a wall (impassable).
- `'.'` represents an open space (walkable).

The task is to find the shortest path from `'S'` to `'E'` using the A\* algorithm, avoiding walls and moving only through open spaces. The maze is guaranteed to contain exactly one start `'S'` and one exit `'E'`.

### Input Format
- The maze is provided as a text file (`.txt`), where each line corresponds to a row in the maze grid, and each character represents a cell in that row.

### Output
- The program outputs a sequence of moves that solve the maze (e.g., `UP`, `DOWN`, `LEFT`, `RIGHT`), or prints "No solution exists" if no path is found.

## Solution Approach: A\* Algorithm

The **A\*** (A-star) algorithm is a pathfinding algorithm that efficiently finds the shortest path using a combination of:
- **G-Score**: The actual cost to reach a node from the start.
- **H-Score** (Heuristic): An estimate of the cost to reach the exit from the current node. In this project, we use the **Euclidean distance** as the heuristic.
- **F-Score**: The total estimated cost (`F = G + H`).

 ## How to Build and Run the Program

To build and run the program, follow these steps:

1. **Prepare the Maze File**:
   - Create or modify a text file that represents the maze (e.g., `example_maze.txt`), following the input format described above.
   - Otherwise, You can generate a random maze using the map_generator.cpp file. Compile and run the file as follows:
      ```bash
      g++ -o map_generator map_generator.cpp
      ./map_generator
      ```

2. **Use the `buildandrun.sh` Script**:
   - Run the provided script `buildandrun.sh`. This script will build the project and run the maze solver.
     ```bash
     ./buildandrun.sh ../mazes/example_maze.txt
     ```

   The script automatically compiles the C++ code and runs the program with "map.txt" file as input.

   If the maze file is solved successfully, the program will output the sequence of moves to reach the exit, otherwise, it will print nothing.

