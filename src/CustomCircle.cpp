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
    ofPushMatrix();
    ofTranslate(getPosition().x, getPosition().y);
    ofFill();
    ofSetColor(31, 127, 25,100);
    ofDrawCircle(0,0,radius);
    ofSetColor(31, 127, 25,200);
    ofDrawCircle(0,0,radius*0.7);
    ofPopMatrix();
}
