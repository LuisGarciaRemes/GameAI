#include "DirectedGraph.h"
#include <fstream>
#include  <iostream>

DirectedGraph::DirectedGraph(std::string i_filename)
{

	std::fstream stream;
	stream.open(i_filename,std::ios::in);
	


	stream.close();
}

DirectedGraph::~DirectedGraph()
{
}

std::vector<DirectedWeightedEdge> DirectedGraph::GetOutgoingEdges(int i_nodeId)
{	
	return m_directedGraph[i_nodeId];
}
