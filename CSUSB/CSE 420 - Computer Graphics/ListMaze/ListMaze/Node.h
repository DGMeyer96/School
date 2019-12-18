class Node
{
public:
	int Full; //one or zero for printing maze
	int index;
	bool Visited; //whether rat has been here
	bool isWall; //is a wall
	bool isExit; //is an exit

	Node();
	void makeWall();
	void makeExit();
	void makePlayer();
};

/*
Function: Node
Author: Daniel Meyer
Description: Default constructor for an empty node in the maze
Input: N/A
Output: N/A
*/
Node::Node()
{
	Full = 0;
	Visited = false;
	isWall = false;
	isExit = false;
}

/*
Function: makeWall
Author: Daniel Meyer
Description: Sets the node to be a wall in the maze
Input: N/A
Output: N/A
*/
void Node::makeWall()
{
	Full = 1;
	isWall = true;
	isExit = false;
}

/*
Function: makeExit
Author: Daniel Meyer
Description: Sets the node to be an exit in the maze
Input: N/A
Output: N/A
*/
void Node::makeExit()
{
	Full = 1;
	isExit = true;
	isWall = false;
}

/*
Function: makeRat
Author: Daniel Meyer
Description: Sets the node to a space the rat has visited
Input: N/A
Output: N/A
*/
void Node::makePlayer()
{
	Full = 1;
	Visited = true;
}
