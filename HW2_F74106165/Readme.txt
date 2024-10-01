Just execute main.cpp.

It has some variations, 2 class, and 3 functions except main.

int maze[17][17];
	maze to solve, represent with 0 and 1
int mark[17][17];
	record whether have been or not
int steps;
	total steps	
MyStack myAns;
	clear path to solve maze(without repeated)
MyStack myRecord;
	full path in the process of solving maze(has repeated)
offsets direction[9];
	set 9 directions

class MyStack;
	the data structure used to solve this question
class Items;
	the unit stack of MyStack

void path(const int m, const int p);
	(m,p) is the destination of the maze
void setDirc();
	used to initialize the "offsets direction[8]"
void printStack();
	used to print the "stack<Items> record"






