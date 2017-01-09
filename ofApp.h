////////////////////////////
/////Project Name: Deep Submergence
/////08.01.2017
/////Written by Soon Park
/////soonpart@gmail.com
////////////////////////////

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    float time, angle;
    int minutes;
    int totalMillis;
    float noiseSeed;
    
    //SCENE 1 ----------------------------
    void drawHead(float x, float y, float size);
    void drawTalis(float x, float y, float size);
    void drawTentacles(float x,float y, float radius, float stepSize);
    void blackout(float speed);
    float locX1, locY1;
    int numTentacles;
    
    //SCENE 2 ----------------------------
    void drawStar(float x, float y, float size, float offset, int numParticles, int numLegs);
    int numStars;
    vector <float> locX2;
    vector <float> locY2;
    vector <float> size;
    vector <float> offset;
    vector <int> numParticles;
    vector <int> numLegs;
    
    //SCENE 3 ----------------------------
    void drawRing(float x,float y, float radius, float stepSize);
    void drawCore(float x,float y, float radius, float stepSize);
    void drawDot(float x,float y, float radius);
    float locX3, locY3;
    int totalRays;
    vector <float> noiseSeeds3;
    
    //SCENE 4 ----------------------------
    void drawBrunch(float length);
    void drawSkin(float x,float y, float radius, float stepSize);
    void drawNeedles(float x,float y, float radius);
    void drawHeart(float x,float y, float radius);
    void drawFlash(float x,float y, float radius);
    float locX4, locY4;
    int resolution;
    vector <float> noiseSeeds4;
};
