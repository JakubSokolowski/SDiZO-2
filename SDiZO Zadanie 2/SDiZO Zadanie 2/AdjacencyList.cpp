#include "stdafx.h"
#include "AdjacencyList.h"


AdjacencyList::AdjacencyList()
{
}

AdjacencyList::AdjacencyList(uint vertices)
{
	vertices_count_ = vertices;
	list_ = new AdjList[vertices_count_];
	for (uint i = 0; i < vertices_count_; ++i)
		list_[i].head_ = NULL;
}


AdjacencyList::~AdjacencyList()
{
}
