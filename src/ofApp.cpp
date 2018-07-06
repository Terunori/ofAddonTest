#include "ofApp.h"
int flag=0;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    // video input size
    vidGrabber.initGrabber(320,240);
    // image size
    grayImg.allocate(320,240);
    grayBg.allocate(320,240);
    grayDiff.allocate(320,240);
    //set variables
    bLearnBakGround = true;
    threshold = 100;
    
    // init Box2D
    box2d.init();
    // gravity: downward, 5 units
    box2d.setGravity(0,1);
    box2d.createBounds(0,0,grayImg.width, grayImg.height);
    box2d.setFPS(90);
    box2d.checkBounds(true);
    box2d.registerGrabbing();
    
    // set 1000 Customcircles
    static const int NUM = 400;
    for (int i=0;i<NUM;i++){
        shared_ptr<CustomCircle> circle = shared_ptr<CustomCircle>(new CustomCircle);
        
        // mass, repulsion, friction
        circle.get()->setPhysics(1.2, 0.85, 0.0);
        circle.get()->setup(box2d.getWorld(), ofRandom(0,grayImg.width), ofRandom(0,grayImg.height), 3);
        
        circles.push_back(circle);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    box2d.update();
    
    // get new frame?
    bool bNewFrame = false;
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    // get the new frame
    if (bNewFrame) {
        colorImg.setFromPixels(vidGrabber.getPixels().getData(), 320, 240);
        grayImg = colorImg;
        // new background?
        if (bLearnBakGround == true) {
            grayBg = grayImg;
            bLearnBakGround = false;
        }
        // get diff
        grayDiff.absDiff(grayBg, grayImg);
        // abstruct countour
        grayDiff.threshold(threshold);
        contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, false);
        // clear circles on the boundary
        for (int i=0; i< contourCircles.size(); i++) {
            contourCircles[i].get()->destroy();
        }
        contourCircles.clear();
        // analyse Blob: objects
        for (int i=0; i<contourFinder.nBlobs; i++) {
            for (int j=0;j<contourFinder.blobs[i].pts.size(); j+=3) {
                // regular intervals
                ofPoint pos = contourFinder.blobs[i].pts[j];
                // add circle
                shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
                
                circle.get()->setPhysics(5.0, 0.6, 0.3);
                circle.get()->setup(box2d.getWorld(), pos.x, pos.y, 3);
                
                contourCircles.push_back(circle);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float ratioX = ofGetWidth()/320;
    float ratioY = ofGetHeight()/240;
    
    // rescale and show
    ofPushMatrix();
    ofScale((float)ofGetWidth() / (float)grayDiff.width, (float)ofGetHeight() / (float)grayDiff.height);
    // show original color img
    ofSetColor(255, 255, 255);
    if (flag) {
        colorImg.draw(0,0);
    } else {
        grayDiff.draw(0,0);
    }
    // show contours
    contourFinder.draw();
    // boundary circles
    ofNoFill();
    ofSetColor(255, 0, 0);
    for (int i=0; i<contourCircles.size();i++) {
        contourCircles[i].get()->draw();
    }
    // illustrate CustomCircles
    for (int i=0; i< circles.size(); i++) {
        circles[i].get()->draw();
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            bLearnBakGround = true;
            break;
        case '+':
            threshold++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold--;
            if (threshold < 0) threshold = 0;
            break;
        case 'b':
            flag=0;
            break;
        case 'c':
            flag=1;
            break;
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
