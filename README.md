# Game of Life in C

This C program simulates Conway's Game of Life by mathematician John Conway. The Game of Life operates on a grid of cells, where each cell can be either alive or dead. The state of each cell evolves over time based on specific rules.
The code is designed to be cross-platform, supporting both Windows and Unix-like systems.

## Installation and Compilation

Firstly clone the repository to your local machine:

```bash
git clone https://github.com/RuiPedroDev/CGameOfLife
```

To compile the program, use a C compiler such as `gcc`. Open a terminal and navigate to the directory containing the source code file. Then, run the following command:

```bash
gcc GameOfLife.c -o GameOfLife
```

## Usage

To run the program, execute the compiled executable and optionally pass command‑line arguments to customize the run.

```bash
./GameOfLife [--pattern <pattern>] [--sleeptime <ms>] [--maxiterations <n>]
```

- `--pattern (-p) <0–8>` (optional): Select a pattern for the initial configuration. Default is 8.
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

## Examples

```bash
./GameOfLife --pattern 5 --maxiterations 5       # GLIDER pattern with 5 max iterations
./GameOfLife --sleeptime 50                      # RANDOM pattern with 50ms delay
```

## Notes

- The program will display the evolving state of the Game of Life grid, updating for a predefined number of iterations or until the grid stabilizes.

- Press Ctrl+C to terminate the simulation at any time.
