Skyscrapers Puzzle Game

This project is a C implementation of the Skyscrapers solitaire puzzle game. It supports two modes:

Interactive Gameplay – allows users to play the game manually in a terminal.

Automated Solver – uses heuristic-based logic to automatically solve given puzzles.

The game can handle board sizes from 2×2 up to 8×8 and enforces all puzzle rules, including clue satisfaction, visibility constraints, and uniqueness in rows and columns.

How the Game Works:

In Skyscrapers, you are given:
An N × N grid representing building heights (from 1 to N).
Clues on the edges of the board that indicate how many buildings are visible from each direction.
The tallest buildings block the view of shorter ones. The goal is to fill in the board so that:
Each number 1 through N appears exactly once in each row and column.
All side clues are satisfied.

Features:

Interactive Mode:

Users can interact with the puzzle through a terminal-based interface:
Input the size, initial board state, and side clues via command-line arguments.
Place buildings interactively with real-time feedback.
Handles errors like duplicate heights, invalid placements, and clue violations.
Prints clear error messages and prompts for user actions.

Run with:
./build/hw1_game <size> <initial_board_string> <clue_string>

Example:
./build/hw1_game 4 "3-2-431-1-4--1-4" "2124242121333321"


Solver Mode:

Includes a solver that uses four heuristics to deduce correct building placements:
Edge Clue Initialization – Places values based on clues like “1” and “N”.
Constraint Propagation – Eliminates options based on uniqueness constraints.
Process of Elimination – Detects values that can only appear in one cell.
Clue Elimination / Sequence Filtration – Cross-references remaining options with clues to filter impossible configurations.

Run with:

./build/hw1_solver <size> <initial_board_string> <clue_string>


Build Instructions:

Configure build system:
cmake -S . -B build
Compile:
cmake --build build
