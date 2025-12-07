# Collision Simulation
This project was developed as a final assignment for the Data Structures and Algorithms course. It features a physics simulation of bouncing balls to demonstrate collision detection techniques. The primary objective is to implement and benchmark the performance differences between a Brute Force and a Quadtree algorithm.

## Requirement
SFML 3

## How to build and run (on linux)
```bash 
mkdir build
./run.sh
```

## Brute Force Algorithm
The Brute Force algorithm works by checking every single possible combination. In this project, I use it to detect collisions by comparing every ball against every other ball. This results in a time complexity of O(N^2). While it runs fine with a small number of balls but the performance will drop if there are a lot of ball to process. For example, running 5,000 balls slows the simulation down drastically to just 2 FPS.

## Quad Tree Algorithm
Quad Tree work by recursively grouping data in two dimentional space to four quadrant. It works by breaking down a large area into smaller. The time complexity of this algorithm is O(N log N)

In this project, I use a Quadtree to store every particle position. Because the Quadtree divides the space into four quadrants recursively, I don't need to check every single ball to find collisions. The system only checks the area immediately surrounding the target ball. This saves significant processing time compared to a brute force algorithm. As you can see below, even with 5,000 balls, the simulation runs successfully at around 14 FPS.