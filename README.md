# maze-generator
finally finished.
iterative implementation of the depth-first search algorithm.
some notes and to-do's:
 - possible glitch: when checking if a cell has unvisited neighbors, its possible that the same cell gets pushed to the stack multiple times. shouldnt be a problem but   could maybe possibly lead to undefined behaviour, fix or dont, seems to work fine as is lmao
 - customrect.cpp/.h are unused because the way i originally wanted to do this was to literally remove a vertex of the rectangle ( cells used to be rectangleshapes instead of 4 lines ). this didnt work so i just abandoned it.
 - dont look in include.h. im serious. 
