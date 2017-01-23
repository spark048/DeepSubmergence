#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetCircleResolution(60);
    ofSetBackgroundAuto(false);
    
    time = 0;
    angle = 0;
    minutes = 3;
    totalMillis = minutes * 60 * 1000;
}

//--------------------------------------------------------------
void ofApp::update()
{
    time = ofMap(ofGetElapsedTimeMillis(), 0, totalMillis, 0, 1, true);
    angle++;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //SCENE 1 ----------------
    if(time < 0.01) blackout.display(30);
    if(time<0.24)
    {
        octopus.display(angle, time);
    }
    if(time > 0.24 && time < 0.25) blackout.display(30);
    
    //SCENE 2 ----------------------------
    if(time>0.25 && time<0.49)
    {
        blackout.display(50);
        ball.display(angle, time);
    }
    if(time > 0.49 && time < 0.5) blackout.display(30);
    
    //SCENE 3 ----------------------------
    if(time == 0.5) blackout.display(30);
    if(time>0.5 && time<0.74)
    {
        serpent.display(angle, time);
    }
    if(time > 0.74 && time < 0.75) blackout.display(30);
    
    //SCENE 4 ----------------------------
    if(time>0.75)
    {
        blackout.display(50);
        jellyfish.display(angle, time);
    }
}
