#pragma once

typedef unsigned int uint;

struct Node
{
	uint destination_;
	struct Node *next_;
};

struct AdjList
{
	Node *head_;
};

class AdjacencyList
{
public:

	AdjacencyList();
	AdjacencyList(uint vertices);
	~AdjacencyList();

private:
	uint vertices_count_;
	AdjList *list_;	

};

