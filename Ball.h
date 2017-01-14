#pragma once

#include "ofMain.h"

class Ball{
    
public:
    Ball();
    
    void drawStar(float x, float y, float size, float offset, int numParticles, int numLegs, float angle, float time);
    void display(float angle, float time);
    
    int numStars;
    vector <float> locX;
    vector <float> locY;
    vector <float> size;
    vector <float> offset;
    vector <int> numParticles;
    vector <int> numLegs;
};
