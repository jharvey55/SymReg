# SymReg

A Symbolic Regression tool built in C++ that employs genetic algorithms on a user-provided dataset.

## Table of Contents

* [About](#about)
  * [Representation](#representation)
* [Technologies](#technologies)
* [Setup](#setup)
  * [Data Structure](#data-structure)
* [Features](#features)
  * [Optimizers](#optimizers)
  * [Selection](#selection)
  * [HFC Options](#hfc-options)
* [Example](#example)
  * [Equation](#equation)
  * [Learning Videos](#learning-videos)
  * [Learning Curve](#learning-curve)
* [Licence](#license)

## About

### Representation

This program stores the generated solution in a heap. Each node of the heap has a  It has a fixed set of operators to create an equation $f(x)$:   $x$, $c$, $+$, $-$, $\times$, $\div$, $\cos(x)$, $\sin(x)$.

Each node stores an operator `enum` and a float value.

## Technologies

* C++ 20
* CMake 3.16
* Julia
* GoogleTest
* Makie.jl

## Setup

### Data Structure

The program takes in data



## Features

### Optimizers
SymReg prompts the user to select an optimizer for generating new solutions. The valid options and their descriptions are listed below.

| Method   | Name                       | Description                                                  |
| -------- | -------------------------- | ------------------------------------------------------------ |
| `Cross`  | Crossover                  | 1. Selects 2 members from the population<br />2. Selects a random node in each parent member<br />3. Creates 2 new contenders by swapping "branches" in each heap <br /> |
| `RMHC`   | Rand Mutation Hill Climber | 1. Loops through each member of the population<br />2. Picks random node in member to mutate<br />3. Produces new member by mutating node, keeps parent or child <br /> |
| `Random` | Random Solutions           | 1. Create an entirely new random population each generation  |

### Selection

The user also selects the optimization loop. Unlike the optimizer, the loop chosen describes how to divide the population into segments for competition.

| Method | Name                          | Description                                                  |
| ------ | ----------------------------- | ------------------------------------------------------------ |
| `HFC`  | Hierarchical fair competition | 1. The user defines a base population size ($S$), number of tiers ($N$), graduation rate ($R$), and number of generations ($G$) between graduations <br />2. Performs optimization on base population for $G$ generations. using the selected optimizer<br />3.  Sorts base tier members by fitness<br />4. $R\%$ of base population with the highest fitness graduate to next tier, base population is reseeded with random population<br />5. Every $G$ generations, graduate each tier that has members to next tier (except tier $N$). Cull each tier to the appropriate population size. Reseed base population with random members.<br />6. Repeats until evaluation budget runs out<br /> |
| `BGA`  | Basic Genetic Algorithm       | Uses *truncation* selection with random mutation:<br />1.  Generates random starting population<br />2. Performs chosen optimizer to get new members<br />3. Sorts by members fitness<br />4. Now that population has doubled in size, culls the population by $50\%$, keeping the members with the best finesses<br />5. Repeats until evaluation budget runs out<br /> |

#### HFC Options:

If the user selects the `HFC ` loop, then the following parameters will need to be defined:

* *Grad-Rate* - $R$: `double` representing the percentage of members to graduate to the next tier as represented between
  $0.0 < G < 1.00$.
* *Num-Tiers* - $N$: `int` representing the number of tiers in the hierarchy
* *Generations* - $G$: `int` representing the number of generations between each graduation

## Example

### Equation

$f(x) = \cos((\sin(x)/(\sin((x+7.348103))+((x/x)/(-4.911469-8.001613)))))$

with data over $x \in [-0.8, 1.8]$

### Learning Videos

These help visualize the process of SymReg finding an approximate equation for the dataset. Each update represents
a instance where the algorithm found an equation with a better fitness (smaller RMSE), and shows what that equation
looks like plotted against the provided dataset. In the title string, the E is the current number of evaluations and R
is the current RMSE value. The blue dots are the test data and the orange thoughts are the current best solution.

![](https://github.com/jharvey55/SymReg/blob/portfolio/examples/f21/images/f21_BGA-Cross_long.gif)
<br>*Visualization of Equation 2 using BGA loop and Crossover*

![](https://github.com/jharvey55/SymReg/blob/portfolio/examples/f21/images/f21_HFC-Cross_accurate.gif)
<br>*Visualization of Equation 2 using HFC loop and Crossover*

### Learning Curve

The learning curve is used to show the relative efficiency of each optimization method. It is built by taking several
trials for each method and grouping them into cohorts. At a regular interval (100 evaluations in this graph), the
average
fitness of the method is determined. The error bars on this graph represent the standard deviation at that point. By
plotting
the methods together like this we can verify that the algorithm is working correctly. RMHC should beat Random, and
Crossover
should beat RMHC. It also highlights the number of evaluations needed for the Crossover.

![](https://github.com/jharvey55/SymReg/blob/portfolio/examples/f21/images/f21-LearningCurve-v2.png)
<br>*Learning Curve showing the speed each Method finds a solution at, averaged over 5 runs*



## Future Goals

This project has been deprecated in favor of creating [GDL](https://github.com/jharvey55/GDL) (a more general Evolutionary Algorithm framework built in Rust). The new library will be for more practical projects as well as testing out interesting experiments described in literature.

## Installation

### Run exe

Latest release can be found at [link]()
<br><br>
To run code, download latest release. Once running it will prompt user to supply:

1. Path to data set
2. Path to store results
3. Evaluation budget
4. Population
5. Optimization method
6. Optimization loop

### Example Protocol

```text
./path/to/data_file.txt
./path/to/experiment/dir/
200000
250
Cross
BGA
```

## License

[MIT](https://choosealicense.com/licenses/mit/)
