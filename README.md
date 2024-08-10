# Tetromino - A Tetris-Like Game

## Overview

Tetromino is a terminal-based Tetris-like game developed in C by a team of four Computer Science and Applied Mathematics students. The project explores optimization techniques and probability-based score calculation, with all code and comments written in French.

## Team Members

This project was a collaborative effort, with tasks equally distributed among all team members:
- **Cyprien N.**
- **Louis S.**
- **Amr K.**
- **Bechir S.**

## Project Structure

The project is organized into the following directories:
```
/tetromino
├── /bin # Contains the compiled executable 'prog'
├── /include # Header files (.h) for the project
│ ├── board.h
│ ├── carte.h
│ ├── constantes.h
│ ├── interface.h
│ └── tetromino.h
├── /obj # Object files (.o) generated during compilation
│ ├── board.o
│ ├── carte.o
│ ├── interface.o
│ ├── main.o
│ └── tetromino.o
├── /src # Source files (.c) containing the main game logic
│ ├── board.c
│ ├── carte.c
│ ├── interface.c
│ ├── main.c
│ └── tetromino.c
└── Makefile # Used to compile the project
```

## Installation and Setup

To compile and run the game, navigate to the project directory and use the Makefile:

```bash
# Compile the project
make

# Run the game
./bin/prog
```

## How to Play
The game is played on the terminal using keyboard controls.