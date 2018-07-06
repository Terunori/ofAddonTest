//
//  CustomCircle.hpp
//  ofAddonTest
//
//  Created by Hiroki Ihara on 7/6/18.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

// define Class customCircle by Inheritting ofxBox2dCircle
class CustomCircle : public ofxBox2dCircle {
public:
    void draw();
};
