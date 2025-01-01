# Minesweeper

Welcome to the Minesweeper project! This is a classic implementation of the Minesweeper game.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)

## Introduction

Minesweeper is a puzzle game where the objective is to clear a rectangular board containing hidden "mines" without detonating any of them, with help from clues about the number of neighboring mines in each field.

## Features

- Classic Minesweeper gameplay
- Customizable grid size and number of mines
- Planned: AC-3 algorithm to give hints and ensure that the puzzle is solvable without guessing

## Installation

To install and run the Minesweeper game, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/nadim-mott/minesweeper
    ```
2. Navigate to the project directory:
    ```bash
    cd minesweeper
    ```
3. Compile the code using the makefile:
    ```bash
    make release
    ```
4. Run the game:
    ```bash
    ./minesweeper <rows> <cols> <num_mines>
    ```

## Usage

- Type commands in the terminal when prompted
- Commands are of 2 types:
1. Flag a cell: 
    ```
    # f <cell number><cell letter>
    f 5E
    ```
2. Reveal a cell:
    ```
    # r <cell number><cell letter>
    r 3L
    ```
- Cell numbers and letters corresponds to the labels on the side of the grid
## Contributing

Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch:
    ```bash
    git checkout -b feature-name
    ```
3. Make your changes and commit them:
    ```bash
    git commit -m "Add feature"
    ```
4. Push to the branch:
    ```bash
    git push origin feature-name
    ```
5. Create a pull request.
