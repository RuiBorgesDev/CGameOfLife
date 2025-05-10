# Game of Life in C

This C program simulates Conway's Game of Life by mathematician John Conway. The Game of Life operates on a grid of cells, where each cell can be either alive or dead. The state of each cell evolves over time based on specific rules.
The code is designed to be cross-platform, supporting both Windows and Unix-like systems.

## Installation and Compilation

Firstly clone the repository to your local machine:

```bash
git clone https://github.com/RuiBorgesDev/CGameOfLife
```

To compile the program, use a C compiler such as `gcc`. Open a terminal and navigate to the directory containing the source code file. Then, run the following command:

```bash
gcc GameOfLife.c -o GameOfLife
```

## Usage

To run the program, execute the compiled executable and optionally pass command‑line arguments to customize the run.

```bash
./GameOfLife [--pattern <pattern>] [--sleeptime <ms>] [--maxiterations <n>] [--cols <n>] [--rows <n>] [--density <n>]
```

- `--pattern (-p) <0–8>` (optional): Select a pattern for the initial configuration. Default is 8 (RANDOM).
  - 0: BLINKER
  - 1: TOAD
  - 2: BEACON
  - 3: PULSAR
  - 4: PENTADECATHLON
  - 5: GLIDER
  - 6: GOSPER GLIDER GUN
  - 7: LWSS
  - 8: RANDOM

- `--sleeptime (-s) <0–10000>` (optional): Specify the sleep time between iterations in milliseconds. Default is 100.

- `--maxiterations (-m) <1–100000>` (optional): Specify the maximum number of iterations for the simulation. Default is 250.

- `--cols (-c) <1–100>` (optional): Specify the number of columns for the simulation, only works on RANDOM pattern. Default depends on the pattern.

- `--rows (-r) <1-50>` (optional): Specify the number of rows for the simulation, only works on RANDOM pattern. Default depends on the pattern.

- `--density (-d) <1–9>` (optional): Specify the density of alive cells for the start of the simulation in the random pattern. Default is 2.

- `--history (-h) <2–100>` (optional): Specify the number of previous generations to store for loop detection. Must be less than maxiterations. Default is 5.

## Examples

```bash
./GameOfLife --pattern 5 --maxiterations 5       # GLIDER pattern with 5 max iterations
./GameOfLife --sleeptime 50                      # RANDOM pattern with 50ms delay
./GameOfLife --rows 40 --maxiterations 100       # RANDOM pattern with 40 rows and 100 max iterations
./GameOfLife --density 8                         # RANDOM pattern with 80% density
./GameOfLife --maxiterations 500 --history 20    # RANDOM pattern, check for loops over the last 20 states up to 500 iterations
```

## Notes

- The program will display the evolving state of the Game of Life grid, updating for a predefined number of iterations or until the grid stabilizes.

- Press Ctrl+C to terminate the simulation at any time.
