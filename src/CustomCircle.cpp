//
//  CustomCircle.cpp
//  ofAddonTest
//
//  Created by Hiroki Ihara on 7/6/18.
//
//

#include "CustomCircle.hpp"

void CustomCircle::draw(){
    float radius = getRadius();
    // change coordination
    ofPushMatrix();
    // move coordination to object position
    ofTranslate(getPosition().x, getPosition().y);
    ofFill();
    ofSetColor(31,127,255,100);
    ofDrawCircle(0,0,radius);
    ofSetColor(31,127,255,200);
    ofDrawCircle(0,0,radius*0.7);
    // initialize coordination
    ofPopMatrix();
}
