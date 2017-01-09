////////////////////////////
/////Project Name: Deep Submergence
/////08.01.2017
/////Written by Soon Park
/////soonpart@gmail.com
////////////////////////////

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetBackgroundColor(0);
    ofSetBackgroundAuto(false);
    ofSetCircleResolution(60);
    minutes = 3;
    totalMillis = minutes * 60 * 1000;
    noiseSeed = ofRandom(10000);
    
    //SCENE 1 ----------------------------
    numTentacles = 5;   //set the number of following yellow tentacles
    
    //SCENE 2 ----------------------------
    numStars = 20;  //set the number of the creatures
    for (int i = 0; i < numStars; i++)
    {
        locX2.push_back(ofGetWidth() + ofRandomWidth());
        locY2.push_back(ofGetHeight() + ofRandomHeight());
        size.push_back(ofRandom(10, 45));
        offset.push_back(ofRandom(10000));
        numParticles.push_back(ofRandom(3, 10));    //set the number of the particles on each leg
        numLegs.push_back(ofRandom(4, 12)); //set the number of the legs
    }
    
    //SCENE 3 ----------------------------
    totalRays = 20; //set the number of the jiggling points on the circle
    for(int i=0; i<totalRays; i++)
    {
        noiseSeeds3.push_back(ofRandom(10000));
    }
    
    //SCENE 4 ----------------------------
    resolution = 30;    //set the number of the jiggling points on the circle
    for(int i=0; i<resolution; i++)
    {
        noiseSeeds4.push_back(ofRandom(10000));
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    time = ofMap(ofGetElapsedTimeMillis(), 0, totalMillis, 0, 1, true); //convert time from '0 -> 180000' to '0 -> 1'
    angle++;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //SCENE 1 ----------------------------
    if(time<0.24)
    {
        locX1 = ofMap(time, 0, 0.24, 0, ofGetWidth() + 100, true);  //move horizontally from left to right
        locY1 = ofMap(ofNoise(time*20 + noiseSeed), 0, 1, 0, ofGetHeight(), true);  //move up and down
        drawHead(locX1, locY1, 60);
        drawTalis(locX1, locY1, 4);
        drawTentacles(locX1 - 800, 0, 180, 40);
    }
    if(time > 0.24 && time < 0.25)
    {
        blackout(20);
    }
    
    //SCENE 2 ----------------------------
    if(time>0.25 && time<0.49)
    {
        ofSetColor(0, 30);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()); //refill the background with motion blur
        for (int i = 0; i < numStars; i++)
        {
            locX2[i] += 2 * (ofNoise(time * 100 + offset[i]) - 0.8);    //move from right to left
            locY2[i] += 2 * (ofNoise(time * 100 + offset[i] + noiseSeed) - 0.8);    //move from bottom to top
            drawStar(locX2[i], locY2[i], size[i], offset[i], numParticles[i], numLegs[i]);
        }
    }
    if(time > 0.49 && time < 0.5)
    {
        blackout(20);
    }
    
    //SCENE 3 ----------------------------
    if(time>0.5 && time<0.74)
    {
        locX3 = ofMap(ofNoise(time*20 + noiseSeed), 0.2, 0.8, 0, ofGetWidth(), true);   //move hotrizontally
        locY3 = ofMap(time, 0.51, 0.74, -50, ofGetHeight() + 100, true);    //move from top to bottom
        drawCore(locX3, locY3, 35 + 10 * sin(ofDegToRad(angle)), 20);
        drawRing(locX3, locY3, 60, 8);
        drawDot(locX3, locY3, ofRandom(1, 3));
    }
    if(time > 0.74 && time < 0.75)
    {
        blackout(20);
    }
    
    //SCENE 4 ----------------------------
    if(time>0.75)
    {
        locX4 = ofMap(ofNoise(time*10 + noiseSeed), 0, 1, 0, ofGetWidth(), true);   //jiggle horizontally
        locY4 = ofMap(time, 0.75, 1, ofGetHeight() + 400, - 500, true); //move from bottom to top
        ofSetColor(0, 30);
        ofFill();
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()); //refill the background with motion blur
        ofTranslate(locX4, locY4);
        ofRotate(angle * 0.1);
        drawSkin(0, 0, 170, 20);    //draw inner skin
        drawSkin(0, 0, 200 + 20 * -sin(ofDegToRad(angle)), 60);  //draw outer double skin
        ofPushMatrix();
        ofRotate(-angle);
        drawSkin(0, 0, 200 + 20 * -sin(ofDegToRad(angle)), 60);  //draw outer double skin
        ofPopMatrix();
        drawNeedles(0, 0, 270 - 20 * sin(ofDegToRad(angle)));
        for(int i=0; i<5;i++)
        {
            ofPushMatrix();
            ofRotate(72 * i);
            drawBrunch(30 + 10 * ofNoise(time*10)); //draw five branches
            ofPopMatrix();
        }
        for(int i=0; i<5;i++)
        {
            drawHeart(0, 0, 20*i);  //draw five red dot on each line
        }
        drawFlash(0, 0, 170);
    }
}

//SCENE 1 ----------------------------
//function to draw magenta circle shape
void ofApp::drawHead(float x, float y, float size)
{
    ofSetColor(255, 0, ofMap(locY1, 0, ofGetHeight(), 0, 255, true), ofMap(locX1, 0, ofGetWidth(), 0, 40, true));
    ofNoFill();
    ofDrawCircle(x, y, size + size * 0.3 * sin(ofDegToRad(angle)));
}

//function to draw inner three dots
void ofApp::drawTalis(float x, float y, float size)
{
    ofTranslate(x, y);
    ofPushMatrix();
    ofRotate(angle);
    ofSetColor(255 * ofNoise(time * 85), 255 * ofNoise(time * 90), 255 * ofNoise(time * 95), ofMap(locX1, 0, ofGetWidth(), 0, 100, true));
    ofFill();
    ofDrawCircle(size * 2, 0, ofRandom(size));
    ofDrawCircle(size * -2, size * 2, ofRandom(size));
    ofDrawCircle(size * -2, size * -2, ofRandom(size));
    ofPopMatrix();
}

//function to draw five following tentacles
void ofApp::drawTentacles(float x, float y, float radius, float stepSize)
{
    float angleStep = 360.0/numTentacles;
    ofTranslate(x, y);
    ofPushMatrix();
    ofRotate(angle * 0.1);
    ofSetColor(200, 150, 0, ofMap(locX1, 0, ofGetWidth(), 0, 40, true));
    ofFill();
    for (int i=0; i<numTentacles; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds3[i]) * stepSize;
        float endX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float endY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds3[i] += 0.01;
        ofDrawCircle(endX, endY, 2);
    }
    ofPopMatrix();
}

//function to blackout between each scene
void ofApp::blackout(float speed)
{
    ofSetColor(0, speed);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetHeight());
}

//SCENE 2 ----------------------------
//function to draw individual creatures
void ofApp::drawStar(float x, float y, float size,float offset, int numParticles, int numLegs)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofPushMatrix();
    
    ofRotate(720 * ofNoise(time * 50 + offset));
    for (int j = 0; j<numLegs; j++) //draw legs spreadding from the center of the creature
    {
        ofPushMatrix();
        ofRotate(360/numLegs * j);
        for (int i = 0; i<numParticles; i++)    //draw a leg made of particles
        {
            float space = size/numParticles;
            ofSetColor(ofRandom(255), 0, 255, 100);
            ofFill();
            ofDrawCircle(space * i, 0, space/10 + space/2 * ofNoise((time * 100 + offset) * 5 + i));
        }
        ofPopMatrix();
    }
    
    ofSetColor(200, 255 * (1 - ofNoise(time * 200 + offset)));
    ofFill();
    ofDrawCircle(0, 0, size * ofNoise(time * 200 + offset));    //draw inner core
    ofNoFill();
    ofDrawCircle(0, 0, size * (1.5 + 0.1 * sin(ofDegToRad(angle + offset))));   //draw outer skin
    ofSetColor(255, 200, 0, 100);
    ofNoFill();
    ofDrawCircle(0, 0, size * (0.5 + 0.3 * sin(ofDegToRad(angle + offset))));   //draw inner ring
    ofPopMatrix();
    ofPushMatrix();
    ofRotate(angle * 0.3 + offset);
    ofSetColor(255, 220  * (1 + 0.1 * sin(ofDegToRad(angle + offset))), 0, 100);
    ofFill();
    ofDrawCircle(size * 1.2, 0, size/20);   //draw for dotating dots
    ofDrawCircle(size * -1.2, 0, size/20);   //draw for dotating dots
    ofDrawCircle(0, size * 1.2, size/20);   //draw for dotating dots
    ofDrawCircle(0, size * -1.2, size/20);   //draw for dotating dots
    ofPopMatrix();
    ofPopMatrix();
}

//SCENE 3 ----------------------------
//function to draw inner blue thin layer
void ofApp::drawCore(float x,float y, float radius, float stepSize)
{
    float angleStep = 360.0/totalRays;
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(angle * 0.8);
    ofSetColor(0, 255, 255, ofMap(time, 0.51, 0.53, 0, 30, true));
    ofNoFill();
    ofBeginShape();
    for (int i=0; i<totalRays; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds3[i]) * stepSize;
        float endX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float endY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds3[i] += 0.01;
        ofVertex(endX, endY);
    }
    ofEndShape(true);
    ofPopMatrix();
}

//function to draw outer yellow thin layer
void ofApp::drawRing(float x,float y, float radius, float stepSize)
{
    
    float angleStep = 360.0/totalRays;
    ofPushMatrix();
    ofTranslate(x, y);
    ofPushMatrix();
    ofRotate(angle);
    ofTranslate(10 * ofNoise(time), 0);
    ofSetColor(255, 255, 0, ofMap(time, 0.51, 0.53, 0, 10, true));
    ofNoFill();
    ofBeginShape();
    for (int i=0; i<totalRays; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds3[i]) * stepSize;
        float endX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float endY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds3[i]+=0.01;
        ofVertex(endX, endY);
    }
    ofEndShape(true);
    ofPopMatrix();
    ofPopMatrix();
}

//function to draw inner dots
void ofApp::drawDot(float x,float y, float radius)
{
    
    float angleStep = 360.0/totalRays;
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(angle * 100); //rotate very fast so that dots look like spawned randomely in center line
    ofSetColor(255, ofRandom(100, 200), ofRandom(100, 200), ofMap(ofNoise(time*30), 0, 1, 0, 255, true));
    ofFill();
    ofDrawCircle(10, 0, radius);
    ofPopMatrix();
}

//SCENE 4 ----------------------------
//function to draw a fractal brunch
void ofApp::drawBrunch(float length)
{
    ofSetColor(255, 100);
    ofDrawLine(0, 0, 0, -length);
    if(length > (30 + 10 * ofNoise(time*10))/8)
    {
        ofPushMatrix();
        ofTranslate(0, -length);
        ofPushMatrix();
        ofRotate(15 + 10 * sin(ofDegToRad(angle)));
        drawBrunch(length * 0.8);
        ofPopMatrix();
        ofPushMatrix();
        ofRotate(-15 - 10 * sin(ofDegToRad(angle)));
        drawBrunch(length * 0.8);
        ofPopMatrix();
        ofPopMatrix();
    }
}

//function to draw thin circle layer
void ofApp::drawSkin(float x,float y, float radius, float stepSize)
{
    float angleStep = 360.0/resolution;
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(255, 50);
    ofNoFill();
    ofBeginShape();
    for (int i=0; i<resolution; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds4[i]) * stepSize;
        float endX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float endY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds4[i] += 0.01;
        ofVertex(endX, endY);
    }
    ofEndShape(true);
    ofPopMatrix();
}

//function to draw five lines of dots
void ofApp::drawHeart(float x,float y, float radius)
{
    float angleStep = 360.0/5;
    ofPushMatrix();
    ofTranslate(x, y);
    for (int i=0; i<5; i++)
    {
        ofSetColor(ofRandom(100, 255), 0, 0);
        ofFill();
        float startX = sin(ofDegToRad(i*angleStep)) * radius * 0.95;
        float startY = cos(ofDegToRad(i*angleStep)) * radius * 0.95;
        float endX = sin(ofDegToRad(i*angleStep)) * radius;
        float endY = cos(ofDegToRad(i*angleStep)) * radius;
        noiseSeeds4[i] += 0.01;
        ofDrawCircle(endX, endY, radius/20 * (1 + sin(ofDegToRad(-angle))));
    }
    ofPopMatrix();
}

//function to draw outer surrounding needles
void ofApp::drawNeedles(float x,float y, float radius)
{
    float angleStep = 360.0/resolution;
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(angle * ofNoise(noiseSeeds4[0]));
    for (int i=0; i<resolution; i++)
    {
        ofSetColor(150, ofRandom(200, 255), ofRandom(200, 255));
        ofFill();
        float startX = sin(ofDegToRad(i*angleStep)) * radius * 0.95;
        float startY = cos(ofDegToRad(i*angleStep)) * radius * 0.95;
        float endX = sin(ofDegToRad(i*angleStep)) * radius;
        float endY = cos(ofDegToRad(i*angleStep)) * radius;
        noiseSeeds4[i] += 0.01;
        ofDrawLine(startX, startY, endX, endY); //length is 5% of radius
    }
    ofPopMatrix();
}

//function to draw outer surrounding needles
void ofApp::drawFlash(float x,float y, float radius)
{
    float flashSize = radius * (1 + abs(sin(ofDegToRad(angle))));
    ofSetColor(150, ofRandom(200, 255), ofRandom(200, 255), ofMap(flashSize, radius, radius * 2, 255, 0));
    ofNoFill();
    ofDrawCircle(x, y, flashSize);
}

