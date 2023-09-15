# Data Structures Directions Project

This project was written for my CS3610 Data Structures class in Fall of 2022. The purpose of this project was to use Dijkstra's algorithm to find the shortest path between two nodes in a graph. 

The only files I modified were directions.cc and dijkstra.h. Other files were provided by Nasseef Abukamail (professor at Ohio University).

Project can be compiled with `make` and run with `./a.out` and the usage below:
```
Usage: [graph file] [first location] [second location]
[graph.txt location1 location2] (displays the shortest route, stops, and total distance)
[graph.txt location1] (displays the shortest route to all other locations)
[graph.txt] (displays all available locations)
```

`graph-undirected.txt` includes undirected lettered locations, `graph-directed.txt` includes directed lettered locations, and `graph-ohio.txt` includes locations in Ohio.