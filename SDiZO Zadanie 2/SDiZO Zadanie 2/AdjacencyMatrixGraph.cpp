#include "stdafx.h"
#include "AdjacencyMatrixGraph.h"

using namespace SDZ;
//Creates new adjacency matrix able to hold 10 vertices
AdjacencyMatrixGraph::AdjacencyMatrixGraph()
	: vertices_count_(10)
{
	visited_ = new bool[vertices_count_];
	//Create Matrix
	matrix_ = new uint *[vertices_count_];
	//Create Rows
	for (uint i = 0; i < vertices_count_; i++)
	{
		matrix_[i] = new uint[vertices_count_];
		//Fill the rows with 0
		for (uint j = 0; j < vertices_count_; j++)
		{
			matrix_[i][j] = 0;
		}
	}
}

//Creates new adjacency matrix able to hold given number ov vertices
AdjacencyMatrixGraph::AdjacencyMatrixGraph(uint vertices_count)
	: vertices_count_(vertices_count)
{
	visited_ = new bool[vertices_count];
	//Create Matrix
	matrix_ = new uint *[vertices_count];
	//Create Rows
	for (uint i = 0; i < vertices_count; i++)
	{
		matrix_[i] = new uint[vertices_count];
		//Fill the rows with 0
		for (uint j = 0; j < vertices_count; j++)
		{
			matrix_[i][j] = 0;
		}
	}
}

//Frees the memory
AdjacencyMatrixGraph::~AdjacencyMatrixGraph()
{
	for (uint i = 0; i < vertices_count_; ++i)
	{
		delete[] matrix_[i];
	}
}

//Connects origin adn destination with edge. Only in unweighted grapgs
void AdjacencyMatrixGraph::AddEdge(uint origin, uint destination)
{
	if (IsValidEdge(origin, destination))
	{
		matrix_[origin - 1][destination - 1] = 1;
	}
}

//Connects origin and destinatnion with edge of given weight
void AdjacencyMatrixGraph::AddEdge(uint origin, uint destination, uint weight)
{
	if (IsValidEdge(origin, destination))
	{
		matrix_[origin - 1][destination - 1] = weight;
	}
}

//Displays the matrix
void AdjacencyMatrixGraph::Display()
{
	int row = 0, column = 0;

	for (int i = 1; i < vertices_count_ + 1; i++)
		std::cout << i;

	std::cout << std::endl;

	for (; row < vertices_count_; row++)
	{
		std::cout << row;
		for (; column < vertices_count_; column++)
			std::cout << matrix_[row][column] << " ";
		std::cout << std::endl;
	}
}

//Checks if given edge can be constructed
bool AdjacencyMatrixGraph::IsValidEdge(uint origin, uint destination)
{
	return (origin > vertices_count_ || destination > vertices_count_) ? false : true;
}
