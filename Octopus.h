#pragma once

#include "ofMain.h"

class Octopus{
    
public:
    Octopus();
    
    void drawHead(float x, float y, float size, float angle, float time);
    void drawTalis(float x, float y, float size, float angle, float time);
    void drawTentacles(float x,float y, float radius, float stepSize, float angle, float time);
    void display(float angle, float time);
    
    float locX, locY;
    int numTentacles;
    vector <float> noiseSeeds;
};
