#include "ofApp.h"
#include "../Boid.h"
#include "ofAppRunner.h"
#include "../MovementAlgorithms.h"
#include <random>

Boid* boidKing;
std::vector<Boid*> loyalSubjects;
std::vector<Kinematic*> loyalSubjectsKinematics;
int simulationIndex = 0;
Kinematic* target;
MovementAlgorithms::Steering* steering;
float wanderOrientation = 0.0f;
float totalMass = 0.0f;
float xPosSum = 0.0f;
float yPosSum = 0.0f;
float xVelSum = 0.0f;
float yVelSum = 0.0f;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 255, 255);	
	boidKing = new Boid(50.0f, 700.0f, 0.0f,10.0f,100.0f);
	target = new Kinematic();
	target->SetPosition(ofVec2f(50.0f, 700.0f));
	srand(time(0));

	for (int i = 0; i < 3; i++)
	{
		Boid* boid = new Boid(50.0f + (i*50.0f), 300.0f, 0.0f, 10.0f, 10.0f);
		loyalSubjects.push_back(boid);
		loyalSubjectsKinematics.push_back(boid->GetKinematic());

		boid = new Boid(50.0f + (i*50.0f), 350.0f, 0.0f, 10.0f, 10.0f);
		loyalSubjects.push_back(boid);
		loyalSubjectsKinematics.push_back(boid->GetKinematic());

		boid = new Boid(50.0f + (i*50.0f), 400.0f, 0.0f, 10.0f, 10.0f);
		loyalSubjects.push_back(boid);
		loyalSubjectsKinematics.push_back(boid->GetKinematic());
	}

	totalMass = boidKing->GetKinematic()->GetMass();

	for (Boid* boid : loyalSubjects)
	{
		totalMass += boid->GetKinematic()->GetMass();
	}
}

//--------------------------------------------------------------
void ofApp::update(){

	//Update the king and his subjects kinematics
	boidKing->Update(ofGetLastFrameTime());
	for (Boid* boid : loyalSubjects)
	{
		boid->Update(ofGetLastFrameTime());
	}

	//Decide what simulation is taking place on screen
	switch (simulationIndex)
	{
		case 0:
			//Basic movement around the screen
			ofSetWindowTitle("Basic Motion - Snapping To Direction Of Movement");
			MovementAlgorithms::BasicMotion(boidKing->GetKinematic());
			MovementAlgorithms::SnapToDirectionOfTravel(boidKing->GetKinematic());
			break;
		case 1:
			//The King seeks to mouse click
			ofSetWindowTitle("Dynamic Seek - Delegating To Look Where You Are Going");
			boidKing->GetKinematic()->SetLinear(MovementAlgorithms::DynamicSeek(boidKing->GetKinematic(), target, 10.0f)->m_linear);		
			boidKing->GetKinematic()->SetAngular(MovementAlgorithms::LookWhereYouAreGoing(boidKing->GetKinematic(), 0.0698132f, 0.0698132f*100.0f, .25f, PI)->m_angular);
			break;
		case 2:
			//The King arrives to mouse click
			ofSetWindowTitle("Dynamic Arrive - Delegating To Look Where You Are Going");
			boidKing->GetKinematic()->SetLinear(MovementAlgorithms::DynamicArrive(boidKing->GetKinematic(), target, 10.0f, 10.0f, 850.0f)->m_linear);
			boidKing->GetKinematic()->SetAngular(MovementAlgorithms::LookWhereYouAreGoing(boidKing->GetKinematic(), 0.0698132f, 0.0698132f*100.0f, .25f, PI)->m_angular);
			break;
		case 3:
			//The King wanders
			ofSetWindowTitle("Dynamic Wander - Delegating To Face");
			steering = MovementAlgorithms::DynamicWander(boidKing->GetKinematic(), wanderOrientation, 100.0f, 500.0f, 500.0f, 2.0f, 10.0f);
			boidKing->GetKinematic()->SetLinear(steering->m_linear);
			boidKing->GetKinematic()->SetAngular(steering->m_angular);
			break;
		case 4:
			//The King wanders
			ofSetWindowTitle("Flock - 10 Total Boids");
			steering = MovementAlgorithms::DynamicWander(boidKing->GetKinematic(), wanderOrientation, 100.0f, 500.0f, 500.0f, 2.0f, 10.0f);
			boidKing->GetKinematic()->SetLinear(steering->m_linear);
			boidKing->GetKinematic()->SetAngular(steering->m_angular);

			//Get center of mass stuff
			xPosSum = boidKing->GetKinematic()->GetPosition().x * boidKing->GetKinematic()->GetMass(); 
			yPosSum = boidKing->GetKinematic()->GetPosition().y * boidKing->GetKinematic()->GetMass();
			xVelSum = boidKing->GetKinematic()->GetVelocity().x * boidKing->GetKinematic()->GetMass();
			yVelSum = boidKing->GetKinematic()->GetVelocity().y * boidKing->GetKinematic()->GetMass();

			for (Boid* boid : loyalSubjects)
			{
				xPosSum += boid->GetKinematic()->GetPosition().x * boid->GetKinematic()->GetMass();
				yPosSum += boid->GetKinematic()->GetPosition().y * boid->GetKinematic()->GetMass();
				xVelSum += boid->GetKinematic()->GetVelocity().x * boid->GetKinematic()->GetMass();
				yVelSum += boid->GetKinematic()->GetVelocity().y * boid->GetKinematic()->GetMass();
			}

			//Set target using center of mass stuff - reset somethings just in case
			target->SetPosition(ofVec2f(xPosSum/ totalMass, yPosSum / totalMass));
			target->SetLinear(ofVec2f(xVelSum / totalMass, yVelSum / totalMass));
			target->SetAngular(0.0f);
			target->SetRotation(0.0f);
			target->SetOrientation(0.0f);

			//His loyal subjects follow
			for (Boid* boid : loyalSubjects)
			{
				//To Do add (1 arrive (2 look at where you are going (3 separate (4 velocity match
				boid->GetKinematic()->SetLinear((.8)*MovementAlgorithms::DynamicSeek(boid->GetKinematic(), target, 10.0f)->m_linear + (1)*MovementAlgorithms::Separation(boid->GetKinematic(),loyalSubjectsKinematics,50.0f, 0.01f, 10.0f)->m_linear + (.6) *MovementAlgorithms::VelocityMatch(boid->GetKinematic(),target, 10.0f)->m_linear);
				boid->GetKinematic()->SetAngular(MovementAlgorithms::LookWhereYouAreGoing(boid->GetKinematic(), 0.0698132f, 0.0698132f*100.0f, .25f, PI)->m_angular);
			}
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

	//Draws boidKing
	ofSetColor(0,0,0);
	ofDrawCircle(boidKing->GetKinematic()->GetPosition(), boidKing->GetRadius());
	ofDrawTriangle(boidKing->GetTriangle()->point1, boidKing->GetTriangle()->point2, boidKing->GetTriangle()->point3);

	//Draws boidSubjects
	if (simulationIndex == 4)
	{
		for (Boid* boid : loyalSubjects)
		{
			ofDrawCircle(boid->GetKinematic()->GetPosition(), boid->GetRadius());
			ofDrawTriangle(boid->GetTriangle()->point1, boid->GetTriangle()->point2, boid->GetTriangle()->point3);
		}
	}
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
		if (simulationIndex == 3)
		{
			boidKing->GetKinematic()->SetPosition(ofVec2f(50.0f, 350.0f));
		}
		else if (simulationIndex == 4)
		{
			boidKing->GetKinematic()->SetPosition(ofVec2f(200.0f, 350.0f));
		}
		else
		{
			boidKing->GetKinematic()->SetPosition(ofVec2f(50.0f, 700.0f));
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

		if (simulationIndex == 4) {
			for (Boid* boid : loyalSubjects)
			{
				boid->GetKinematic()->SetPosition(ofVec2f(boid->GetKinematic()->GetPosition().x + 1025.0f, boid->GetKinematic()->GetPosition().y));
			}
		}
	}
	else if (boidKing->GetKinematic()->GetPosition().x > 1025.0f)
	{
		boidKing->GetKinematic()->SetPosition(ofVec2f(0.0f, boidKing->GetKinematic()->GetPosition().y));
		if (simulationIndex == 4) {
			for (Boid* boid : loyalSubjects)
			{
				boid->GetKinematic()->SetPosition(ofVec2f(boid->GetKinematic()->GetPosition().x - 1025.0f, boid->GetKinematic()->GetPosition().y));
			}
		}
	}
	else if (boidKing->GetKinematic()->GetPosition().y > 800.0f)
	{
		boidKing->GetKinematic()->SetPosition(ofVec2f(boidKing->GetKinematic()->GetPosition().x,0.0f));
		if (simulationIndex == 4) {
			for (Boid* boid : loyalSubjects)
			{
				boid->GetKinematic()->SetPosition(ofVec2f(boid->GetKinematic()->GetPosition().x, boid->GetKinematic()->GetPosition().y - 800.0f));
			}
		}
	}
	else if (boidKing->GetKinematic()->GetPosition().y < 0.0f)
	{
		boidKing->GetKinematic()->SetPosition(ofVec2f(boidKing->GetKinematic()->GetPosition().x,800.0f));
		if (simulationIndex == 4) {
			for (Boid* boid : loyalSubjects)
			{
				boid->GetKinematic()->SetPosition(ofVec2f(boid->GetKinematic()->GetPosition().x, boid->GetKinematic()->GetPosition().y + 800.0f));
			}
		}
	}
}