#include "stdafx.h"
#include "IncidenceMatrix.h"

//Base constructor, creates matrix with 10 vertices and 10 edges
IncidenceMatrix::IncidenceMatrix()
	: vertices_(10)
	, edges_(10)
	, edge_count_(0)
{
	//Create Matrix
	matrix_ = new int *[10];

	//Create array to hold the weights of edges
	weights = new unsigned int[10]();

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
IncidenceMatrix::IncidenceMatrix(int number_of_vertices, int number_of_edges)
	: vertices_(number_of_vertices)
	, edges_(number_of_edges)
	, edge_count_(0)
{
	//Create Matrix
	matrix_ = new int *[number_of_vertices];
	//Create array to hold the weights of edges
	weights = new unsigned int[number_of_edges]();

	for (int i = 0; i < number_of_vertices; i++)
	{
		matrix_[i] = new int[number_of_edges];
		//Mark all rows as NO_EDGE
		for (int j = 0; j < number_of_edges; j++)
		{
			matrix_[i][j] = NO_EDGE;
		}
	}
}

//Free the memory
IncidenceMatrix::~IncidenceMatrix()
{
	for (int i = 0; i < vertices_;i++)
	{
		delete[] matrix_[i];
	}
}

//Connects origin and destination with edge of given weight
void IncidenceMatrix::AddEdge(unsigned int origin, unsigned int destination, unsigned int weight)
{
	if (IsValidEdge(origin, destination))
	{
		//Connect the origin and destination with edge of given weight
		std::cout << vertices_ << " " << edges_ << std::endl;
		matrix_[origin][edge_count_] = START;
		matrix_[destination][edge_count_] = END;
		weights[edge_count_] = weight;
		
		++edge_count_;
	}
}

void IncidenceMatrix::DisplayMatrix()
{
	
	std::cout << "  ";
	for (int i = 0; i < edges_; i++)
		std::cout << std::setw(3) << i << " ";

	std::cout << std::endl;

	for (int row = 0; row < vertices_; row++)
	{
		std::cout << row << " ";
		for (int column = 0; column < edges_; column++)
			std::cout << std::setw(3) << matrix_[row][column] << " ";
		std::cout << std::endl;
	}
}

void IncidenceMatrix::DisplayWeights()
{
	std::cout <<std::endl<< std::setw(2) << " ";
	for (int i = 0; i < edge_count_ ; i++)
		std::cout << std::setw(3) << i << " ";
	std::cout << std::setw(2) << std::endl << " ";
	for (int i = 0; i < edge_count_ ; i++)
		std::cout << std::setw(3) << weights[i] << " ";
	std::cout << std::endl;
}



bool IncidenceMatrix::IsValidEdge(unsigned int origin, unsigned int destination)
{
	return (origin > vertices_ || destination > vertices_) ? false : true;
}
