# Cut_points
Algorithm of finding cut_point for UNi 

## Algorithm
Main algorith cointaints in functions bfs and **bfs_list**. First is working with *adjacency matrix*, second with *adjacency list*.
With *adjacency matrix* algorithm costs more, because we should parse each collumn.

## Generating
Data generates in functions **Graph_gen**.
In function **matrix_to_list** adjacency matrix converts to list. In the end of this function, matrix will be deleted to save memory.   
