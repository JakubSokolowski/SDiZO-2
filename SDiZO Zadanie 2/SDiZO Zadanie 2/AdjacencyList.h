#pragma once
#include <iostream>
#include "Array.h"

typedef unsigned int uint;


class AdjacencyList
{
public:


	// Constructors

	AdjacencyList();
	AdjacencyList(uint vertices);
	~AdjacencyList();

private:

	Array* list;



};

