#include "ofApp.h"
#include "../Boid.h"
#include "ofAppRunner.h"

Boid* boid;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 255, 255);
	boid = new Boid(50.0f, 700.0f, 0.0f,10.0f);
}

//--------------------------------------------------------------
void ofApp::update(){
	boid->Update(ofGetLastFrameTime());
	boid->BasicMotion();
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
