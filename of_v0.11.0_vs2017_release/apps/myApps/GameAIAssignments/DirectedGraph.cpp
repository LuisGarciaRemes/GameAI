#include "DirectedGraph.h"
#include <fstream>
#include  <iostream>

DirectedGraph::DirectedGraph(std::string i_filename)
{
	char line[100];
	std::fstream stream;
	stream.open(i_filename,std::ios::in);

	stream.getline(line,100);

	int source;
	int sink;
	float cost;

	if (!stream.is_open())
	{
		std::cout << i_filename.c_str() << " was not opened please check the file path";
	}

	while (line[0] != '\0')
	{
		std::string temp = "";

		int index = 0;

		for (char c : line)
		{
			if (c == ',')
			{
				switch (index)
				{
					case 0:
						source = std::atoi(temp.c_str());
						temp = "";
						break;
					case 1:
						sink = std::atoi(temp.c_str());
						temp = "";
						break;
					default:
						break;
				}

				index++;
			}
			else if (c == '\0')
			{
				cost = std::atof(temp.c_str());
				break;
			}
			else
			{
				temp += c;
			}			
		}

		if (source == m_directedGraph.size())
		{
			std::vector<DirectedWeightedEdge> tempEdges;

			tempEdges.push_back(DirectedWeightedEdge(source, sink, cost));

			m_directedGraph.push_back(tempEdges);

			//std::cout << "source: " << source << " sink: " << sink  << " cost: " << cost << "\n";
		}
		else
		{
			m_directedGraph[source].push_back(DirectedWeightedEdge(source, sink, cost));

			//std::cout << "source: " << source << " sink: " << sink << " cost: " << cost << "\n";
		}

		stream.getline(line, 100);
	}

	std::cout << i_filename.c_str() << " was loaded into DirectedGraph object\n";

	stream.close();
}

DirectedGraph::~DirectedGraph()
{
}

std::vector<DirectedWeightedEdge> DirectedGraph::GetOutgoingEdges(int i_nodeId)
{	
	return m_directedGraph[i_nodeId];
}
