#include "ofApp.h"
#define NUM_OF_POLYGONS 200
#define BPM 128
#define SOUND_NAME "perfume.mp3"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetSphereResolution(100);
    ofSetBoxResolution(1, 1, 1);
    ofEnableDepthTest(); //enable depth test (for drawing correctly)
    
    if (SOUND_NAME){
        soundPlayer.loadSound(SOUND_NAME);
        soundPlayer.setLoop(true);
        soundPlayer.play();
    }
    
    for (int i=0; i<NUM_OF_POLYGONS; i++){
        polygons.push_back(new Polygon3d());
    }
    for (int i=0; i<polygons.size(); i++) {
        polygons.at(i)->setPolygonPosition(ofRandom(-2000, 2000),ofRandom(-2000, 2000),ofRandom(-2000, 2000));
        polygons.at(i)->setPolygonType(floor(ofRandom(2)));
        polygons.at(i)->setPolygonSize(floor(ofRandom(10,100)));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    double rad = ofMap(ofGetElapsedTimeMillis()%(int)(60000/BPM), 0.0f, 60000.0f/BPM, 0.0f, M_PI);
    objectSizeScale = 1 + 0.3 * pow(sin(rad),6.0);

    if (accelFlag) cameraSpeed += 0.005;
    else if (cameraSpeed > 0) cameraSpeed -= 0.020;
    else cameraSpeed = 0;
    cameraPosition += cameraSpeed;

    camera.setPosition(2000*sin(cameraPosition), 0, 2000*cos(cameraPosition));
    camera.lookAt(ofVec3f(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    camera.begin();
    
    for (int i = 0; i<polygons.size(); i++) {
        ofSetColor(ofColor::fromHsb(0, 255, ofRandom(128,255)));
        ofLine(ofPoint(0,0,0), polygons.at(i)->getPolygonPosition());
        switch (polygons.at(i)->getPolygonType()) {
            case 0:
                ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
                boxPrimitive.setPosition(polygons.at(i)->getPolygonPosition());
                boxPrimitive.set(polygons.at(i)->getPolygonSize()*objectSizeScale);
                boxPrimitive.drawWireframe();
                break;
            case 1:
                ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
                spherePrimitive.setPosition(polygons.at(i)->getPolygonPosition());
                spherePrimitive.setRadius(polygons.at(i)->getPolygonSize()*objectSizeScale/2);
                spherePrimitive.drawWireframe();
            default:
                break;
        }
    }
    
    camera.end();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        accelFlag = true;
    } else if (key == 'f') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == ' '){
        accelFlag = false;
    }
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
