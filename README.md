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
SymReg
* `Cross` - 
* `RMHC` - 
* `

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
