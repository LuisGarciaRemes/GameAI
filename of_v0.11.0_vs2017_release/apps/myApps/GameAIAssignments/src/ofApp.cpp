#include "ofApp.h"
#include "../Boid.h"
#include "ofAppRunner.h"
#include "../MovementAlgorithms.h"
#include <random>

Boid* boid;
int simulationIndex = 0;
Kinematic* target;
MovementAlgorithms::Steering* steering;
float wanderOrientation = 0.0f;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 255, 255);
	boid = new Boid(50.0f, 700.0f, 0.0f,10.0f);
	target = new Kinematic();
	target->SetPosition(ofVec2f(50.0f, 700.0f));
	srand(time(0));
}

//--------------------------------------------------------------
void ofApp::update(){
	boid->Update(ofGetLastFrameTime());

	switch (simulationIndex)
	{
		case 0:
			ofSetWindowTitle("Basic Motion - Snapping To Direction Of Movement");
			MovementAlgorithms::BasicMotion(boid->GetKinematic());
			MovementAlgorithms::SnapToDirectionOfTravel(boid->GetKinematic());
			break;
		case 1:
			ofSetWindowTitle("Dynamic Seek - Delegating To Look Where You Are Going");
			boid->GetKinematic()->SetLinear(MovementAlgorithms::DynamicSeek(boid->GetKinematic(), target, 10.0f)->m_linear);		
			boid->GetKinematic()->SetAngular(MovementAlgorithms::LookWhereYouAreGoing(boid->GetKinematic(), 0.0698132f, 0.0698132f*100.0f, .25f, PI)->m_angular);
			break;
		case 2:
			ofSetWindowTitle("Dynamic Arrive - Delegating To Look Where You Are Going");
			boid->GetKinematic()->SetLinear(MovementAlgorithms::DynamicArrive(boid->GetKinematic(), target, 10.0f, 10.0f, 600.0f)->m_linear);
			boid->GetKinematic()->SetAngular(MovementAlgorithms::LookWhereYouAreGoing(boid->GetKinematic(), 0.0698132f, 0.0698132f*100.0f, .25f, PI)->m_angular);
			break;
		case 3:
			ofSetWindowTitle("Dynamic Wander - Delegating To Face");
			steering = MovementAlgorithms::DynamicWander(boid->GetKinematic(), wanderOrientation, 100.0f, 500.0f, 500.0f, .25f, 5.0f);
			boid->GetKinematic()->SetLinear(steering->m_linear);
			boid->GetKinematic()->SetAngular(steering->m_angular);
			break;
		case 4:
			break;
		default:
			simulationIndex = 0;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	//Draws BreadCrumbs
	for (Boid::Breadcrumb crumb : boid->GetCrumbs())
	{
		ofSetColor(255, 0, 0);
		ofVec3f temp;
		temp.set(crumb.pos.x, crumb.pos.y,0.0f);
		ofDrawBox(temp,4);
	}

	//Draws Boid
	ofSetColor(0,0,0);
	ofDrawCircle(boid->GetKinematic()->GetPosition(), boid->GetRadius());
	ofDrawTriangle(boid->GetTriangle()->point1, boid->GetTriangle()->point2, boid->GetTriangle()->point3);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == OF_KEY_LEFT || key == OF_KEY_RIGHT)
	{
		boid->GetKinematic()->SetVelocity(ofVec2f(0.0f, 0.0f));
		boid->GetKinematic()->SetRotation(0.0f);
		boid->GetKinematic()->SetOrientation(0.0f);
		boid->GetKinematic()->SetLinear(ofVec2f(0.0f, 0.0f));
		boid->GetKinematic()->SetAngular(0.0f);
		boid->GetKinematic()->m_basicMotionIndex = 0;
		target->SetPosition(ofVec2f(50.0f, 700.0f));

		if (key == OF_KEY_RIGHT)
		{
			simulationIndex++;
		}

		if (simulationIndex == 3)
		{
			boid->GetKinematic()->SetPosition(ofVec2f(50.0f, 350.0f));
		}
		else
		{
			boid->GetKinematic()->SetPosition(ofVec2f(50.0f, 700.0f));
		}

		boid->ClearBreadCrumbs();
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
		boid->GetKinematic()->SetVelocity(ofVec2f(0.0f, 0.0f));
		boid->GetKinematic()->SetRotation(0.0f);
		boid->GetKinematic()->SetLinear(ofVec2f(0.0f, 0.0f));
		boid->GetKinematic()->SetAngular(0.0f);
		target->SetPosition(ofVec2f(x, y));
		boid->ClearBreadCrumbs();
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
