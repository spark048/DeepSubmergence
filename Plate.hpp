#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class Plate{
    
public:
    Plate();
    void setup();
    void draw(float x, float y, float w, float h);
    
    ofColor frameColorOut;
    ofColor frameColorBorder;
    ofColor frameColorIn;
    
    ofxTrueTypeFontUC fontL;
    ofxTrueTypeFontUC fontS;
};
