#include "ofApp.h"
#include "../Boid.h"
#include "ofAppRunner.h"
#include "../MovementAlgorithms.h"
#include "../Pathfinding.h"
#include <random>

Boid* boidKing;
Kinematic* clickTarget;
MovementAlgorithms::Steering* steering;

DirectedGraph romeGraph;
DirectedGraph homeGraph;
DirectedGraph gridGraph;
SearchAlgorithms::Grid grid;
SearchAlgorithms::Heuristic romeConstant;
SearchAlgorithms::Heuristic homeConstant;
SearchAlgorithms::Heuristic romeRandom;
SearchAlgorithms::Heuristic homeRandom;
SearchAlgorithms::Heuristic gridEuclidian;

std::vector<int> path;
Pathfinding pathfinding;

bool displayGrid = false;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 255, 255);	
	boidKing = new Boid(ofGetWindowWidth()/2+32, ofGetWindowHeight()/2+32, 0.0f,10.0f,500.0f);
	clickTarget = new Kinematic();
	clickTarget->SetPosition(ofVec2f(50.0f, 700.0f));
	srand(343);

	gridGraph = DirectedGraph::DirectedGraph("DirectedGraphs/GridDirectedGraph.csv");
	homeGraph = DirectedGraph::DirectedGraph("DirectedGraphs/MyHouseDirectedGraph.csv");
	romeGraph = DirectedGraph::DirectedGraph("DirectedGraphs/RomeDirectedGraph.csv");

	grid = SearchAlgorithms::Grid();

	std::vector<int> tempConstant;
	std::vector<int> tempRandom;

	for (int i = 0; i < homeGraph.GetTotalNodes(); i++)
	{
		tempConstant.push_back(homeGraph.GetTotalNodes());
		tempRandom.push_back(rand() % 50);
	}

	homeRandom = SearchAlgorithms::Heuristic(tempRandom);
	homeConstant = SearchAlgorithms::Heuristic(tempConstant);

	for (int i = 0; i < romeGraph.GetTotalNodes(); i++)
	{
		tempConstant.push_back(romeGraph.GetTotalNodes());
		tempRandom.push_back(rand() % 500);
	}

	romeRandom = SearchAlgorithms::Heuristic(tempRandom);
	romeConstant = SearchAlgorithms::Heuristic(tempConstant);

	std::cout << "Running Dijkstra on small graph\n";
	path = SearchAlgorithms::Dijkstra(homeGraph,18,11);
	SearchAlgorithms::PrintPath(path);

	std::cout << "Running Dijkstra on large graph\n";
	path = SearchAlgorithms::Dijkstra(romeGraph, 180, 2568);
	SearchAlgorithms::PrintPath(path);

	std::cout << "Running A* on small graph with contant estimate\n";
	path = SearchAlgorithms::AStar(homeGraph, 18, 11, homeConstant);
	SearchAlgorithms::PrintPath(path);

	std::cout << "Running A* on large graph with contant estimate\n";
	path = SearchAlgorithms::AStar(romeGraph, 180, 2568, romeConstant);
	SearchAlgorithms::PrintPath(path);

	std::cout << "Running A* on small graph with random estimate\n";
	path = SearchAlgorithms::AStar(homeGraph, 18, 11, homeRandom);
	SearchAlgorithms::PrintPath(path);

	std::cout << "Running A* on large graph with random estimate\n";
	path = SearchAlgorithms::AStar(romeGraph, 180, 2568,romeRandom);
	SearchAlgorithms::PrintPath(path);

	path.clear();
}

//--------------------------------------------------------------
void ofApp::update(){

	//Update the king and his subjects kinematics
	boidKing->Update(ofGetLastFrameTime());

	//pathfinds
	if (!path.empty())
	{
		MovementAlgorithms::Steering result = pathfinding.ArrivePath(boidKing->GetKinematic(), path, grid,11.0f, 15.0f, 10.0f, 0.0698132f, 150.0f, 0.0698132f*50.0f, .75f, PI);
		boidKing->GetKinematic()->SetAngular(result.m_angular);
		boidKing->GetKinematic()->SetLinear(result.m_linear);
	}

	//Check boundaries
	CheckBoundaries();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//Draws Grid
	if (displayGrid)
	{
		ofSetColor(0, 0, 0);
		for (int i = 1; i < 16; i++)
		{
			ofDrawLine(0 + i * 64, 0, 0 + i * 64, ofGetWindowHeight());
		}

		for (int i = 1; i < 12; i++)
		{
			ofDrawLine(0, 0 + i * 64, ofGetWindowWidth(), 0 + i * 64);
		}
	}

	float radius = 26;

	//Draws Obstacles
	ofSetColor(0, 0, 0);
	ofDrawCircle(5 * 64 + 32, 3 * 64 + 32, radius);
	ofDrawCircle(8 * 64 + 32, 8 * 64 + 32, radius);
	ofDrawCircle(8 * 64 + 32, 7 * 64 + 32, radius);
	ofDrawCircle(12 * 64 + 32, 3 * 64 + 32, radius);
	ofDrawCircle(15 * 64 + 32, 11 * 64 + 32, radius);
	ofDrawCircle(1 * 64 + 32, 0 * 64 + 32, radius);
	ofDrawCircle(12 * 64 + 32, 0 * 64 + 32, radius);
	ofDrawCircle(1 * 64 + 32, 1 * 64 + 32, radius);
	ofDrawCircle(2 * 64 + 32, 1 * 64 + 32, radius);
	ofDrawCircle(1 * 64 + 32, 2 * 64 + 32, radius);
	ofDrawCircle(5 * 64 + 32, 1 * 64 + 32, radius);
	ofDrawCircle(6 * 64 + 32, 1 * 64 + 32, radius);
	ofDrawCircle(7 * 64 + 32, 1 * 64 + 32, radius);
	ofDrawCircle(8 * 64 + 32, 1 * 64 + 32, radius);
	ofDrawCircle(10 * 64 + 32, 1 * 64 + 32, radius);
	ofDrawCircle(14 * 64 + 32, 2 * 64 + 32, radius);
	ofDrawCircle(8 * 64 + 32, 3 * 64 + 32, radius);
	ofDrawCircle(9 * 64 + 32, 3 * 64 + 32, radius);
	ofDrawCircle(2 * 64 + 32, 4 * 64 + 32, radius);
	ofDrawCircle(9 * 64 + 32, 4 * 64 + 32, radius);
	ofDrawCircle(1 * 64 + 32, 5 * 64 + 32, radius);
	ofDrawCircle(2 * 64 + 32, 5 * 64 + 32, radius);
	ofDrawCircle(4 * 64 + 32, 5 * 64 + 32, radius);
	ofDrawCircle(6 * 64 + 32, 5 * 64 + 32, radius);
	ofDrawCircle(10 * 64 + 32, 6 * 64 + 32, radius);
	ofDrawCircle(12 * 64 + 32, 6 * 64 + 32, radius);
	ofDrawCircle(13 * 64 + 32, 6 * 64 + 32, radius);
	ofDrawCircle(0 * 64 + 32, 7 * 64 + 32, radius);
	ofDrawCircle(2 * 64 + 32, 7 * 64 + 32, radius);
	ofDrawCircle(4 * 64 + 32, 7 * 64 + 32, radius);
	ofDrawCircle(12 * 64 + 32, 7 * 64 + 32, radius);
	ofDrawCircle(13 * 64 + 32, 7 * 64 + 32, radius);
	ofDrawCircle(2 * 64 + 32, 8 * 64 + 32, radius);
	ofDrawCircle(4 * 64 + 32, 8 * 64 + 32, radius);
	ofDrawCircle(6 * 64 + 32, 8 * 64 + 32, radius);
	ofDrawCircle(10 * 64 + 32, 8 * 64 + 32, radius);
	ofDrawCircle(2 * 64 + 32, 9 * 64 + 32, radius);
	ofDrawCircle(3 * 64 + 32, 9 * 64 + 32, radius);
	ofDrawCircle(4 * 64 + 32, 9 * 64 + 32, radius);
	ofDrawCircle(6 * 64 + 32, 9 * 64 + 32, radius);
	ofDrawCircle(10 * 64 + 32, 9 * 64 + 32, radius);
	ofDrawCircle(12 * 64 + 32, 9 * 64 + 32, radius);
	ofDrawCircle(6 * 64 + 32, 10 * 64 + 32, radius);
	ofDrawCircle(7 * 64 + 32, 10 * 64 + 32, radius);
	ofDrawCircle(9 * 64 + 32, 10 * 64 + 32, radius);
	ofDrawCircle(10 * 64 + 32, 10 * 64 + 32, radius);
	ofDrawCircle(0 * 64 + 32, 11 * 64 + 32, radius);

	//Draws BreadCrumbs
	for (Boid::Breadcrumb crumb : boidKing->GetCrumbs())
	{
		ofSetColor(255, 0, 0);
		ofVec3f temp;
		temp.set(crumb.pos.x, crumb.pos.y,0.0f);
		ofDrawBox(temp,4);
	}

	//Draws Boid
	ofSetColor(150, 0, 150);
	ofDrawCircle(boidKing->GetKinematic()->GetPosition(), boidKing->GetRadius());
	ofDrawTriangle(boidKing->GetTriangle()->point1, boidKing->GetTriangle()->point2, boidKing->GetTriangle()->point3);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if (key == 32)
	{
		displayGrid = !displayGrid;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

		path.clear();
		boidKing->GetKinematic()->SetVelocity(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetRotation(0.0f);
		boidKing->GetKinematic()->SetLinear(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetAngular(0.0f);
		clickTarget->SetPosition(ofVec2f(x, y));
		boidKing->ClearBreadCrumbs();

		std::cout << "Running A* on grid graph with euclidan distance\n";
		int goal = grid.GetContainingNode(clickTarget->GetPosition());
		int current = grid.GetContainingNode(boidKing->GetKinematic()->GetPosition());

		if (!gridGraph.GetOutgoingEdges(goal).empty() && goal != current)
		{
			pathfinding.ResetPathIndex();
			gridEuclidian = SearchAlgorithms::Heuristic(GetEcluidianHeuristic(grid, gridGraph, goal));
			path = SearchAlgorithms::AStar(gridGraph, grid.GetContainingNode(boidKing->GetKinematic()->GetPosition()), goal, gridEuclidian);
			SearchAlgorithms::PrintPath(path);
		}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::CheckBoundaries()
{
	if (boidKing->GetKinematic()->GetPosition().x < 0.0f)
	{
		boidKing->GetKinematic()->SetPosition(ofVec2f(1025.0f, boidKing->GetKinematic()->GetPosition().y));
	}
	else if (boidKing->GetKinematic()->GetPosition().x > 1025.0f)
	{
		boidKing->GetKinematic()->SetPosition(ofVec2f(0.0f, boidKing->GetKinematic()->GetPosition().y));
	}
	else if (boidKing->GetKinematic()->GetPosition().y > 800.0f)
	{
		boidKing->GetKinematic()->SetPosition(ofVec2f(boidKing->GetKinematic()->GetPosition().x,0.0f));
	}
	else if (boidKing->GetKinematic()->GetPosition().y < 0.0f)
	{
		boidKing->GetKinematic()->SetPosition(ofVec2f(boidKing->GetKinematic()->GetPosition().x,800.0f));
	}
}

std::vector<int> ofApp::GetEcluidianHeuristic(SearchAlgorithms::Grid i_gridGraph, DirectedGraph i_graph, int i_goal)
{
	std::vector<int> temp;
	ofVec2f goalPos = i_gridGraph.GetCenterOfNode(i_goal);

	for (int i = 0; i < i_graph.GetTotalNodes(); i++)
	{
		ofVec2f currPos = i_gridGraph.GetCenterOfNode(i);

		ofVec2f distance = currPos - goalPos;

		int result = sqrt(pow(distance.x,2) + pow(distance.y, 2));

		temp.push_back(result);
	}

	return temp;
}
