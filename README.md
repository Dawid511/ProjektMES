### Introduction
The Finite Element Method (FEM) enables engineering calculations for objects with irregular shapes or properties not visible to the naked eye.
The main idea of FEM is to discretize the object into smaller elements consisting of a finite number of nodes.
This program focuses on conducting simulations of heat flow.
Code allows you to generate the data required for post-processing Finite Element Method (FEM) simulations.

### Model Description
The created program was tested on four sample data models. Each model consisted of four parts, containing general information about the model's characteristics, data regarding the coordinates of each node, element indices, and information about boundary conditions.

### Finite Element Method Description
The program conducts simulations using the following steps:
importing data describing the model
creating a universal element
determining the Jacobian
calculating matrices H, Hbc, C, and P
aggregating data
simulating, and determining temperatures.

### Code Characteristics
The program code was written in C++.
It is organized into several classes, which facilitates management and increases transparency. 
The code handles input and output data streams and provides data aggregation and simulation.
