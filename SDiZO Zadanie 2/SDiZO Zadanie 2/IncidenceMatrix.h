#pragma once
#include <iostream>
#include <iomanip>

typedef unsigned int uint;

class IncidenceMatrix
{
public:
	IncidenceMatrix();
	IncidenceMatrix(uint vertices_count, uint edges_count);
	~IncidenceMatrix();

	void AddEdge(uint origin, uint destination, uint weight);

	void DisplayMatrix();
	void DisplayWeights();

private:

	const int START = 1;
	const int END = -1;
	const int NO_EDGE = 0;

	
	int **matrix_;
	uint vertices_;
	uint edges_;
	uint edge_count_;
	uint *weights;

	bool IsValidEdge(uint origin, uint destination);

};

