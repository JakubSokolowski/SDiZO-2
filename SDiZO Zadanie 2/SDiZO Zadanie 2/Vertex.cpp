#include "stdafx.h"
#include "Vertex.h"

sdz::Vertex::Vertex()
	: vertex_id_(0)
	, edge_weight_(0)
{}

sdz::Vertex::Vertex(uint id, uint weight)
	:vertex_id_(id)
	,edge_weight_(weight)
{}

sdz::Vertex::~Vertex()
{
}
