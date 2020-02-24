#include "DirectedGraph.h"

DirectedGraph::DirectedGraph()
{
}

DirectedGraph::~DirectedGraph()
{
}

std::vector<DirectedWeightedEdge> DirectedGraph::GetOutgoingEdges(int i_nodeId)
{	
	return m_directedGraph[i_nodeId];
}
