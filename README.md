# POMP'EIRB

This project is a simulation of a team of firefighter robots that work together to extinguish fires. The robots are programmed to find the nearest water source and then use it to put out the nearest fire. The program is written in C language and depends on CMake, SDL2, SDL2_ttf, SDL2_mixer, and SDL2_image libraries.

## Dependencies
To run this project, you will need to have the following dependencies installed:

- `CMake`
- `SDL2`
- `SDL2_ttf`
- `SDL2_mixer`
- `SDL2_image`

## How to Build and Run
To build and run the project, follow these steps:

1. Install the dependencies listed above.

2. Clone the project from its repository.

3. Open a terminal window and navigate to the project directory.

4. run the CMake: `cmake CMakeLists.txt`.

5. Run make: `make`

6. Run the program: `./main <map> <robots config file>`

## Finding its Way to HELL/PARADISE


For this project, a personal implementation of Dijkstra's algorithm has been used in C.

In order to find the nearest fire or water source, the robots scan the map using a breadth-first search (BFS) algorithm. The BFS algorithm starts from the robot's current position and explores all adjacent spots until it finds the desired target. The BFS algorithm is efficient for this task since the map is represented as a grid.

Once the BFS algorithm has found the nearest fire or water source, the robot executes Dijkstra's algorithm. Dijkstra's algorithm takes the robot's speed in each type of terrain (mountain, forest, or city) into account and returns an `int* path` with `path[0]` is the time taken to reach the spot, and stores all the indexes that uniquely correspond to each coordinate leading to the target spot.

The Dijkstra's algorithm uses a map that stores the speed of the specific robot in each spot. This map is important since the robot's speed can vary based on the terrain type. The map is used to calculate the shortest path from the robot's current position to the target spot while taking the robot's speed into account.

Once the path has been calculated, the robot moves to the next spot on the path and switches to the appropriate state based on whether it is searching for water or fire. The robot then continues to move along the path until it reaches its destination.

This process ensures that the robot always takes the most efficient path to reach the nearest fire or water source and helps to prevent the spread of fires by quickly extinguishing them.

## Robot States
Each robot has eight states, including an off state. The states are as follows:

- State -1: The robot is off.

- State 0: The robot is searching for the nearest water source and finding the nearest path using Dijkstra's algorithm. Once the path is found, the robot switches to state 1.

- State 1: The robot moves to the next spot on the path to the water source, then switches to state 3.

- State 3: The robot verifies whether it has arrived at the water source. If it has, the robot switches to state 4 and begins to fill its container with water. If not, the robot returns to state 1 to complete its path to the water source.

- State 4: The robot fills its container with water until it is full, then switches to state 5.

- State 5: The robot checks if there are any fires left. If there are, it generates the shortest path to the nearest fire and switches to state 6.

- State 6: The robot moves to the next spot on the path to the fire, then switches to state 7.

- State 7: The robot verifies whether it has arrived at the fire. If it has, the robot switches to state 8 and extinguishes the fire. If not, the robot returns to state 6 to continue moving towards the fire.

- State 8: The robot extinguishes the fire.

## Robot Features
- Each robot has a displayed counter over its head that shows the amount of water it is currently carrying. The counter updates in real-time as the robot fills and empties its container. 

- The robot also has a smooth movement based on a linear interpolation formula from spot A to B. When moving, the robot moves at an appropriate speed based on the terrain type (mountain, forest, city).

- During initialization, the user can specify the maximum capacity of the robot's container, its x and y coordinates, and its speeds in the three terrain types.

## Example Section:

To test the firefighter robot program, we provide a test folder containing several maps with different sizes and densities of water.

We also provide a config file for the robots, containing the specifications of each robot. The config file is a text file where each row represents a robot, and each column represents a specific attribute of the robot.

The format of the row in the file is as follows:

```
MaximalCapacityOfContainer  x  y  speedForest speedMountain speedCity
```
- `MaximalCapacityOfContainer`: is an integer representing the maximum capacity of the robot's container.

- `x` and `y` are integers representing the initial coordinates of the robot on the map.

- `speedForest`, `speedMountain`, and `speedCity`: are int numbers representing the speed of the robot in the forest, mountain, and city terrains, respectively.

To run the program, the user must specify the map file, the config file,


## Conclusion

This project demonstrates how robots can be used to fight fires in a coordinated manner. By searching for the nearest water source and then using it to extinguish the nearest fire, the robots can work together to quickly put out fires and prevent them from spreading. The program is written in C and uses various SDL libraries to create a graphical simulation of the robots in action.