#pragma once

#include "ofMain.h"

class Jellyfish{
    
public:
    Jellyfish();
    
    void drawBrunch(float length, float angle, float time);
    void drawSkin(float x,float y, float radius, float stepSize, float angle, float time);
    void drawNeedles(float x,float y, float radius, float angle, float time);
    void drawHeart(float x,float y, float radius, float angle, float time);
    void drawFlash(float x,float y, float radius, float angle, float time);
    void display(float angle, float time);
    
    float locX, locY;
    int resolution;
    vector <float> noiseSeeds;
};
