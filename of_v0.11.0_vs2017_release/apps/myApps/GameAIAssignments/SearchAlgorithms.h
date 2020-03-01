#pragma once
#include "DirectedGraph.h"
class SearchAlgorithms
{

public:
	struct NodeRecord {

		int m_node = -1;
		DirectedWeightedEdge m_incomingEdge = DirectedWeightedEdge();
		float m_costSoFar = 0;
		float m_estimateToGoal = 0;
	};

	struct Heuristic {

		Heuristic(std::vector<int> i_estimates)
		{
			m_heuristicList = i_estimates;
		}
		std::vector<int> m_heuristicList;
		virtual int getEstimate(int i_node);
	};


	struct PriorityQueue {	
		std::vector<std::pair<NodeRecord, int>> elements;
		

		void PriorityInsert(NodeRecord i_record,int i_priority)
		{		
			int counter = 0;
			for (std::pair<NodeRecord, int> element : elements)
			{
				if (element.second > i_priority)
				{
					std::pair<NodeRecord, int> tempPair;
					tempPair.first = i_record;
					tempPair.second = i_priority;
					elements.insert(elements.begin() + counter, tempPair);
					return;
				}
				counter++;
			}

			std::pair<NodeRecord, int> tempPair;
			tempPair.first = i_record;
			tempPair.second = i_priority;
			elements.push_back(tempPair);
			return;
		}

		NodeRecord GetNext()
		{
			NodeRecord temp = elements.front().first;
			elements.erase(elements.begin());
			return temp;
		}

		bool Contains(int i_node)
		{
			for (std::pair<NodeRecord, int> element : elements)
			{
				if (element.first.m_node == i_node)
				{
					return true;
				}
			}
			return false;
		}

		//Find returns the desired node and removes it from vector
		NodeRecord Find(int i_node)
		{
			int counter = 0;
			NodeRecord temp;
			for (std::pair<NodeRecord, int> element : elements)
			{
				if (element.first.m_node == i_node)
				{
					temp = element.first;
					elements.erase(elements.begin() + counter);
					return temp;
				}
				counter++;
			}
			return temp;
		}

		bool Empty()
		{
			return elements.empty();	
		}

		size_t Size()
		{
			return elements.size();
		}

	};

	static std::vector<int> Dijkstra(DirectedGraph i_graph, int i_start, int i_goal);

	static std::vector<int> AStar(DirectedGraph i_graph, int i_start, int i_goal, Heuristic i_heuristic);

	static void PrintPath(std::vector<int> i_path);

private:

};

