#pragma once
#include "DirectedGraph.h"
#include "ofVec2f.h"
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
		Heuristic();
		std::vector<int> m_heuristicList;
		virtual int getEstimate(int i_node);
	};

	struct Grid {

		int m_grid[12][16];

		Grid()
		{
			int nodeId = 0;

			for (int i = 0; i <12 ; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					m_grid[i][j] = nodeId;
					nodeId++;
				}
			}
		}

		int GetContainingNode(ofVec2f i_position)
		{
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					if ((i_position.x > j * 64 && i_position.x < j * 64 + 64) && (i_position.y > i * 64 && i_position.y < i * 64 + 64))
					{
						return m_grid[i][j];
					}
				}
			}
			return -1;
		}

		ofVec2f GetCenterOfNode(int i_node)
		{
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					if (m_grid[i][j] == i_node)
					{
						return ofVec2f(j*64+32,i*64+32);
					}
				}
			}
			return ofVec2f(-100.0f,-100.0f);
		}

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

