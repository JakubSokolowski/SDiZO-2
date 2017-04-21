#pragma once
#include <iostream>
#include <iomanip>

class IncidenceMatrix
{
public:
	IncidenceMatrix();
	IncidenceMatrix(int vertices_count, int edges_count);
	~IncidenceMatrix();

	void AddEdge(unsigned int origin, unsigned int destination, unsigned int weight);

	void DisplayMatrix();
	void DisplayWeights();

private:

	const int START = 1;
	const int END = -1;
	const int NO_EDGE = 0;

	
	int **matrix_;
	unsigned int vertices_;
	unsigned int edges_;
	unsigned int edge_count_;
	unsigned int *weights;

	bool IsValidEdge(unsigned int origin, unsigned int destination);

};

