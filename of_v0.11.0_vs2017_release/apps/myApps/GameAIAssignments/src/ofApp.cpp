#include "ofApp.h"
#include "../Boid.h"
#include "ofAppRunner.h"
#include "../MovementAlgorithms.h"
#include "../SearchAlgorithms.h"
#include <random>

Boid* boidKing;
int simulationIndex = 0;
Kinematic* target;
MovementAlgorithms::Steering* steering;
float wanderOrientation = 0.0f;

SearchAlgorithms::PriorityQueue test;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 255, 255);	
	boidKing = new Boid(50.0f, 700.0f, 0.0f,10.0f,500.0f);
	target = new Kinematic();
	target->SetPosition(ofVec2f(50.0f, 700.0f));
	srand(time(0));

	SearchAlgorithms::NodeRecord temp1;
	SearchAlgorithms::NodeRecord temp2;
	SearchAlgorithms::NodeRecord temp3;
	SearchAlgorithms::NodeRecord temp4;

	test.PriorityInsert(temp1,6);
	test.PriorityInsert(temp2,1);
	test.PriorityInsert(temp3,5);
	test.PriorityInsert(temp4,7);

	for (std::pair<SearchAlgorithms::NodeRecord,int> element : test.elements)
	{
		ofLog(OF_LOG_NOTICE, "the priority is " + ofToString(element.second));
	}
}

//--------------------------------------------------------------
void ofApp::update(){

	//Update the king and his subjects kinematics
	boidKing->Update(ofGetLastFrameTime());

	//Decide what simulation is taking place on screen
	switch (simulationIndex)
	{
		case 0:
			//Basic movement around the screen
			ofSetWindowTitle("Basic Motion - Snapping To Direction Of Movement");
			MovementAlgorithms::BasicMotion(boidKing->GetKinematic());
			MovementAlgorithms::SnapToDirectionOfTravel(boidKing->GetKinematic());
			break;
		default:
			simulationIndex = 0;
			break;
	}

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

	if (key == OF_KEY_LEFT || key == OF_KEY_RIGHT)
	{
		//Resets the king just in case
		boidKing->GetKinematic()->SetVelocity(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetRotation(0.0f);
		boidKing->GetKinematic()->SetOrientation(0.0f);
		boidKing->GetKinematic()->SetLinear(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetAngular(0.0f);
		boidKing->GetKinematic()->m_basicMotionIndex = 0;

		wanderOrientation = 0.0f;

		//Reset target just in case
		target->SetPosition(ofVec2f(50.0f, 700.0f));
		target->SetLinear(ofVec2f(0.0f, 0.0f));
		target->SetAngular(0.0f);
		target->SetRotation(0.0f);
		target->SetOrientation(0.0f);

		//switches simulation
		if (key == OF_KEY_RIGHT)
		{
			simulationIndex++;
		}


		//Special starting positions
		if (simulationIndex == 3 || simulationIndex == 4)
		{
			
		}


		//Clears the crumb trail
		boidKing->ClearBreadCrumbs();
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

	if (simulationIndex > 0 && simulationIndex < 3)
	{
		boidKing->GetKinematic()->SetVelocity(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetRotation(0.0f);
		boidKing->GetKinematic()->SetLinear(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetAngular(0.0f);
		target->SetPosition(ofVec2f(x, y));
		boidKing->ClearBreadCrumbs();
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