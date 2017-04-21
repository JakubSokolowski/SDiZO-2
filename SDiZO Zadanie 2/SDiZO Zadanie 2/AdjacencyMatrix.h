#pragma once
#include <iostream>

class AdjacencyMatrix
{
public:

	//Constructors & Destructors

	AdjacencyMatrix();
	AdjacencyMatrix(unsigned int vertices_count);
	~AdjacencyMatrix();

	//Edge Management

	void AddEdge(unsigned int origin, unsigned int destination);
	void AddEdge(unsigned int origin, unsigned int destination, unsigned int weight);

	void Display();

private:

	bool IsValidEdge(unsigned int origin, unsigned int destination);

	unsigned int vertices_count_;
	unsigned int **matrix_;
	bool *visited_;
	bool is_directed;

};

