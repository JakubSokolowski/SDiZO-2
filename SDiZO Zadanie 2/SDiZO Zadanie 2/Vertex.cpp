#include "stdafx.h"
#include "Vertex.h"

using namespace sdz;

Vertex::Vertex()
	: vertex_id_(0)
	, edge_weight_(0)
{}

Vertex::Vertex(uint id, uint weight)
	: vertex_id_(id)
	, edge_weight_(weight)
{}


Vertex::~Vertex()
{
}
