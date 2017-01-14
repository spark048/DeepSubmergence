#pragma once

#include "ofMain.h"

class Serpent{
    
public:
    Serpent();
    
    void drawRing(float x,float y, float radius, float stepSize, float angle, float time);
    void drawCore(float x,float y, float radius, float stepSize, float angle, float time);
    void drawDot(float x,float y, float radius, float angle, float time);
    void display(float angle, float time);
    
    float locX, locY;
    int numPoints;
    vector <float> noiseSeeds;
};
