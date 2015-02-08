#include "ofApp.h"
#define NUM_OF_POLYGONS 200

class Polygon3d {
private:
    ofPoint mPolygonPosition = ofPoint(0,0,0);
    int mPolygonType = 0; //0:Box 1:Sphere
    int mPolygonSize = 0; //10~100
public:
    Polygon3d(){}; //Constructor
    ~Polygon3d(){}; //Destructor
    void setPolygonPosition(float x, float y, float z){
        mPolygonPosition.set(x, y, z);
    }
    void setPolygonPosition(ofPoint position){
        mPolygonPosition = position;
    }
    void setPolygonType(int id){
        mPolygonType = id;
    }
    void setPolygonSize(int size){
        mPolygonSize = size;
    }
    ofPoint getPolygonPosition(){
        return mPolygonPosition;
    }
    int getPolygonType(){
        return mPolygonType;
    }
    int getPolygonSize(){
        return mPolygonSize;
    }
};

vector<Polygon3d *> polygons;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetSphereResolution(100);
    ofEnableDepthTest(); //enable depth test (for drawing correctly)
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
    objectSizeScale = 1 + 0.3 * pow(sin((double)ofGetElapsedTimeMillis()/100),6.0);

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
