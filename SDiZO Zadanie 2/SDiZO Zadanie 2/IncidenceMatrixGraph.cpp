#include "stdafx.h"
#include "IncidenceMatrixGraph.h"

using namespace sdz;

//Base constructor, creates matrix with 10 vertices and 10 edges
IncidenceMatrixGraph::IncidenceMatrixGraph()
	: vertices_(10)
	, edges_(10)
	, number_of_edges_(0)
{
	//Create Matrix
	matrix_ = new int *[10];

	//Create array to hold the weights of edges
	weights = new uint[10]();

	for (int i = 0; i < 10; i++)
	{
		matrix_[i] = new int[10];
		//Mark all rows as NO_EDGE
		for (int j = 0; j < 10; j++)
		{
			matrix_[i][j] = NO_EDGE;
		}
	}
}

//Creates incidence matrix with given number vertices and edges
IncidenceMatrixGraph::IncidenceMatrixGraph(uint number_of_vertices, uint number_of_edges)
	: vertices_(number_of_vertices)
	, edges_(number_of_edges)
	, number_of_edges_(0)
{
	//Create Matrix
	matrix_ = new int *[number_of_vertices];
	//Create array to hold the weights of edges
	weights = new uint[number_of_edges]();

	for (uint i = 0; i < number_of_vertices; i++)
	{
		matrix_[i] = new int[number_of_edges];
		//Mark all rows as NO_EDGE
		for (uint j = 0; j < number_of_edges; j++)
		{
			matrix_[i][j] = NO_EDGE;
		}
	}
}

//Free the memory
IncidenceMatrixGraph::~IncidenceMatrixGraph()
{
	for (uint i = 0; i < vertices_;i++)
	{
		delete[] matrix_[i];
	}
}

//Connects origin and destination with edge of given weight
void IncidenceMatrixGraph::AddEdge(uint origin, uint destination, uint weight)
{
	if (IsValidEdge(origin, destination))
	{
		//Connect the origin and destination with edge of given weight
		matrix_[origin][number_of_edges_] = START;
		matrix_[destination][number_of_edges_] = END;
		weights[number_of_edges_] = weight;
		
		++number_of_edges_;
	}
}

void IncidenceMatrixGraph::DisplayMatrix()
{
	
	std::cout << "  ";
	for (uint i = 0; i < edges_; i++)
		std::cout << std::setw(3) << i << " ";

	std::cout << std::endl;

	for (uint row = 0; row < vertices_; row++)
	{
		std::cout << row << " ";
		for (uint column = 0; column < edges_; column++)
			std::cout << std::setw(3) << matrix_[row][column] << " ";
		std::cout << std::endl;
	}
}

void IncidenceMatrixGraph::DisplayWeights()
{
	std::cout <<std::endl<< std::setw(2) << " ";
	for (uint i = 0; i < number_of_edges_ ; i++)
		std::cout << std::setw(3) << i << " ";
	std::cout << std::setw(2) << std::endl << " ";
	for (uint i = 0; i < number_of_edges_ ; i++)
		std::cout << std::setw(3) << weights[i] << " ";
	std::cout << std::endl;
}



bool IncidenceMatrixGraph::IsValidEdge(uint origin, uint destination)
{
	return (origin > vertices_ || destination > vertices_) ? false : true;
}
