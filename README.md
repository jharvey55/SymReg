# SymReg

A **Sym**bolic **Reg**ression tool built in C++ that employs genetic algorithms on a user-provided dataset.

## Table of Contents

* [About](#about)
  * [Representation](#representation)
* [Technologies](#technologies)
* [Setup](#setup)
  * [Data Structure](#data-structure)
* [Features](#features)
  * [Optimizers](#optimizers)
  * [Selection](#selection)
* [Examples](#examples)
* [Sources](#sources)

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
| `HFC`  | Hierarchical fair competition | 1. User defines a base population size ($S$), number of tiers ($N$), graduation rate ($R$), and number of generations ($G$) between graduations <br />2. Performs optimization on base population, for $G$ generations. using the selected optimizer<br />3.  Sorts base tier members by fitness<br />4. $R\%$ of base population with the highest fitness graduate to next tier, base population is reseeded with random population<br />5. Every $G$ generations, graduate each tier that has members to next tier (except tier $N$). Cull each tier to appropriate population size. Reseed base population with random members.<br />6. Repeats until evaluation budget runs out<br /> |
| `BGA`  | Basic Genetic Algorithm       | Uses *truncation* selection with random mutation:<br />1.  Generates random starting population<br />2. Performs chosen optimizer to get new members<br />3. Sorts by members fitness<br />4. Now that population has doubled in size, culls the population by $50\%$, keeping the members with the best finesses<br />5. Repeats until evaluation budget runs out<br /> |


## Examples

### Equation 1

$f(x) = \cos(((((x+x)\cdot(1.022598--0.923627))+(x+(x\cdot5.691799)))+((x-\cos(x))\cdot(x+(x/x)))))$

with data over $x \in [-9.5, -3.5]$

#### Learning Video

#### Learning Curve

#### Dot Graph



### Equation 2

$f(x) = \cos((\sin(x)/(\sin((x+7.348103))+((x/x)/(-4.911469-8.001613)))))$

with data over $x \in [-0.8, 1.8]$



### Equation 3-

$f(x) = (\cos(((\sin(0.947494)-(6.047123-\left(x-5\right)))-(\left(x-5\right)/(5.246456+\left(x-5\right)))))+8.964315)$

with data over $x \in [0, 5]$

#### Learning Video

#### Learning Curve



## Future Goals

This project has been deprecated in favor of creating [GDL](https://github.com/jharvey55/GDL) (a more general Evolutionary Algorithm framework built in Rust). The new library will be for more practical projects as well as testing out interesting experiments described in literature.

## Sources
