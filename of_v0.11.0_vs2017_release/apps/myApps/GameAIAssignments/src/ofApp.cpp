#include "ofApp.h"
#include "../Boid.h"
#include "ofAppRunner.h"
#include "../MovementAlgorithms.h"
#include "../SearchAlgorithms.h"
#include <random>

Boid* boidKing;
Kinematic* target;
MovementAlgorithms::Steering* steering;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 255, 255);	
	boidKing = new Boid(50.0f, 700.0f, 0.0f,10.0f,500.0f);
	target = new Kinematic();
	target->SetPosition(ofVec2f(50.0f, 700.0f));
	srand(time(0));

	DirectedGraph homeGraph = DirectedGraph::DirectedGraph("DirectedGraphs/MyHouseDirectedGraph.csv");
	std::cout << "Running Dijkstra on small graph\n";
	std::vector<int> path = SearchAlgorithms::Dijkstra(homeGraph,18,11);
	SearchAlgorithms::PrintPath(path);
}

//--------------------------------------------------------------
void ofApp::update(){

	//Update the king and his subjects kinematics
	boidKing->Update(ofGetLastFrameTime());

	//Check boundaries
	CheckBoundaries();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//Draws BreadCrumbs
	for (Boid::Breadcrumb crumb : boidKing->GetCrumbs())
	{
		ofSetColor(255, 0, 0);
		ofVec3f temp;
		temp.set(crumb.pos.x, crumb.pos.y,0.0f);
		ofDrawBox(temp,4);
	}


	ofSetColor(150, 0, 150);


	ofDrawCircle(boidKing->GetKinematic()->GetPosition(), boidKing->GetRadius());
	ofDrawTriangle(boidKing->GetTriangle()->point1, boidKing->GetTriangle()->point2, boidKing->GetTriangle()->point3);

	ofSetColor(0, 0, 0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	
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

		boidKing->GetKinematic()->SetVelocity(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetRotation(0.0f);
		boidKing->GetKinematic()->SetLinear(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetAngular(0.0f);
		target->SetPosition(ofVec2f(x, y));
		boidKing->ClearBreadCrumbs();
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