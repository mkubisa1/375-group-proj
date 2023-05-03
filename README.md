# 375 Project – Connecting the Brain
* Team members: Benjamin Fox; Matthew Kubisa
* Project type: “Propose a new method or combine existing algorithms (including the ones that are covered or not covered by this course) with implementation for solving a practical problem.”

Topics: Prim’s Algorithm; Kruzkal’s Algorithm; Minimum spanning trees

## Problem
Some buildings on the main campus are connected to each other from the inside. For others, however, it is necessary to go outside to move between them. Having a means of traveling through buildings while always staying indoors has benefits including avoiding rain/snow and more safe travel at night. To achieve this, assume that the university wants to have all buildings on the main campus connected by a system of tunnels.

## Approach
Our plan is to construct a Minimum Spanning Tree to represent an updated tunnel system for the main campus, which allows for underground/indoor movement between any two buildings. 
The campus is represented by a weighted and undirected graph, with nodes representing buildings and edges representing tunnels connecting them. The difficulty of constructing a tunnel is affected by two factors: 
1. The tunnel’s length
2. Any existing infrastructure the tunnel would travel under.
Ideally, both of these factors are minimized.

To ensure the best possible solution is found, we will utilize both Prim’s and Kruzkal’s algorithms to find the minimum spanning tree to verify each other’s results as accurate.