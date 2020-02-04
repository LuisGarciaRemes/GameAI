#include "ofApp.h"
#include "../Boid.h"
#include "ofAppRunner.h"
#include "../MovementAlgorithms.h"
#include <random>
#include "ofAppGLFWWindow.h"

Boid* boidKing;
std::vector<Boid*> loyalSubjects;
int simulationIndex = 0;
Kinematic* target;
MovementAlgorithms::Steering* steering;
float wanderOrientation = 0.0f;
ofCamera camera;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 255, 255);	
	boidKing = new Boid(50.0f, 700.0f, 0.0f,10.0f,20.0f);
	target = new Kinematic();
	target->SetPosition(ofVec2f(50.0f, 700.0f));
	srand(time(0));

	for (int i = 0; i < 3; i++)
	{
		Boid* boid = new Boid(150.0f + (i*50.0f), 250.0f, 0.0f, 10.0f, 10.0f);
		loyalSubjects.push_back(boid);

		boid = new Boid(150.0f + (i*50.0f), 300.0f, 0.0f, 10.0f, 10.0f);
		loyalSubjects.push_back(boid);

		boid = new Boid(150.0f + (i*50.0f), 350.0f, 0.0f, 10.0f, 10.0f);
		loyalSubjects.push_back(boid);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	boidKing->Update(ofGetLastFrameTime());

	switch (simulationIndex)
	{
		case 0:
			ofSetWindowTitle("Basic Motion - Snapping To Direction Of Movement");
			MovementAlgorithms::BasicMotion(boidKing->GetKinematic());
			MovementAlgorithms::SnapToDirectionOfTravel(boidKing->GetKinematic());
			break;
		case 1:
			ofSetWindowTitle("Dynamic Seek - Delegating To Look Where You Are Going");
			boidKing->GetKinematic()->SetLinear(MovementAlgorithms::DynamicSeek(boidKing->GetKinematic(), target, 10.0f)->m_linear);		
			boidKing->GetKinematic()->SetAngular(MovementAlgorithms::LookWhereYouAreGoing(boidKing->GetKinematic(), 0.0698132f, 0.0698132f*100.0f, .25f, PI)->m_angular);
			break;
		case 2:
			ofSetWindowTitle("Dynamic Arrive - Delegating To Look Where You Are Going");
			boidKing->GetKinematic()->SetLinear(MovementAlgorithms::DynamicArrive(boidKing->GetKinematic(), target, 10.0f, 10.0f, 850.0f)->m_linear);
			boidKing->GetKinematic()->SetAngular(MovementAlgorithms::LookWhereYouAreGoing(boidKing->GetKinematic(), 0.0698132f, 0.0698132f*100.0f, .25f, PI)->m_angular);
			break;
		case 3:
			ofSetWindowTitle("Dynamic Wander - Delegating To Face");
			steering = MovementAlgorithms::DynamicWander(boidKing->GetKinematic(), wanderOrientation, 100.0f, 500.0f, 500.0f, .25f, 5.0f);
			boidKing->GetKinematic()->SetLinear(steering->m_linear);
			boidKing->GetKinematic()->SetAngular(steering->m_angular);
			break;
		case 4:
			ofSetWindowTitle("Flock - 10 Total Boids");

			for (Boid* boid : loyalSubjects)
			{
				
			}
			break;
		default:
			simulationIndex = 0;
			break;
	}

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

	//Draws Boid
	ofSetColor(0,0,0);
	ofDrawCircle(boidKing->GetKinematic()->GetPosition(), boidKing->GetRadius());
	ofDrawTriangle(boidKing->GetTriangle()->point1, boidKing->GetTriangle()->point2, boidKing->GetTriangle()->point3);

	if (simulationIndex == 4)
	{
		for (Boid* boid : loyalSubjects)
		{
			ofSetColor(0, 0, 0);
			ofDrawCircle(boid->GetKinematic()->GetPosition(), boid->GetRadius());
			ofDrawTriangle(boid->GetTriangle()->point1, boid->GetTriangle()->point2, boid->GetTriangle()->point3);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == OF_KEY_LEFT || key == OF_KEY_RIGHT)
	{
		boidKing->GetKinematic()->SetVelocity(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetRotation(0.0f);
		boidKing->GetKinematic()->SetOrientation(0.0f);
		boidKing->GetKinematic()->SetLinear(ofVec2f(0.0f, 0.0f));
		boidKing->GetKinematic()->SetAngular(0.0f);
		boidKing->GetKinematic()->m_basicMotionIndex = 0;
		target->SetPosition(ofVec2f(50.0f, 700.0f));

		if (key == OF_KEY_RIGHT)
		{
			simulationIndex++;
		}

		if (simulationIndex == 3)
		{
			boidKing->GetKinematic()->SetPosition(ofVec2f(50.0f, 350.0f));
		}
		else if (simulationIndex == 4)
		{
			boidKing->GetKinematic()->SetPosition(ofVec2f(300.0f, 300.0f));
		}
		else
		{
			boidKing->GetKinematic()->SetPosition(ofVec2f(50.0f, 700.0f));
		}

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