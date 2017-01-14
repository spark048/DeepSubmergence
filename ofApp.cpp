#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetBackgroundColor(255, 255, 240);
//    ofSetBackgroundAuto(false);
    ofSetCircleResolution(60);
    time = 0;
    angle = 0;
    minutes = 3;
    totalMillis = minutes * 60 * 1000;
    noiseSeed = ofRandom(10000);
    
    //TEXTURE ----------------
    numStrings = 1000;
    ofBackground(255, 255, 240);
    ofSetBackgroundAuto(false);
    for (int i = 0; i<numStrings; i++)
    {
        backX.push_back(ofRandomWidth());
        backY.push_back(ofRandomHeight());
        stringColor.push_back(ofRandom(240, 255));
        length.push_back(ofRandom(50, 100));
    }
    
    //SCENE 1 ----------------
    numTentacles = 5;
    
    //SCENE 2 ----------------------------
    numStars = 20;
    for (int i = 0; i < numStars; i++)
    {
        locX2.push_back(ofGetWidth() + ofRandomWidth());
        locY2.push_back(ofGetHeight() + ofRandomHeight());
        size.push_back(ofRandom(10, 45));
        offset.push_back(ofRandom(10000));
        numParticles.push_back(ofRandom(3, 10));
        numLegs.push_back(ofRandom(4, 12));
    }
    
    //SCENE 3 ----------------------------
    totalRays = 20;
    for(int i=0; i<totalRays; i++)
    {
        noiseSeeds3.push_back(ofRandom(10000));
    }
    
    //SCENE 4 ----------------------------
    resolution = 30;
    for(int i=0; i<resolution; i++)
    {
        noiseSeeds4.push_back(ofRandom(10000));
    }
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
    if(time < 0.01)
        blackout(30);
    if(time<0.24)
    {
        locX1 = ofMap(time, 0, 0.24, 0, ofGetWidth() + 100, true);
        locY1 = ofMap(ofNoise(time*20 + noiseSeed), 0, 1, 0, ofGetHeight(), true);
        drawHead(locX1, locY1, 60);
        drawTalis(locX1, locY1, 4);
        drawTentacles(locX1 - 800, 0, 180, 40);
    }
    if(time > 0.24 && time < 0.25)
    {
        blackout(30);
    }
    
    //SCENE 2 ----------------------------
    if(time>0.25 && time<0.49)
    {
        blackout(50);
        for (int i = 0; i < numStars; i++)
        {
            locX2[i] += 2 * (ofNoise(time * 100 + offset[i]) - 0.8);
            locY2[i] += 2 * (ofNoise(time * 100 + offset[i] + noiseSeed) - 0.8);
            drawStar(locX2[i], locY2[i], size[i], offset[i], numParticles[i], numLegs[i]);
        }
    }
    if(time > 0.49 && time < 0.5)
    {
        blackout(30);
    }
    
    //SCENE 3 ----------------------------
    if(time == 0.5)
        blackout(100);
    if(time>0.5 && time<0.74)
    {
        locX3 = ofMap(ofNoise(time*20 + noiseSeed), 0.2, 0.8, 0, ofGetWidth(), true);
        locY3 = ofMap(time, 0.51, 0.74, -50, ofGetHeight() + 100, true);
        drawCore(locX3, locY3, 35 + 10 * sin(ofDegToRad(angle)), 20);
        drawRing(locX3, locY3, 60, 8);
        drawDot(locX3, locY3, ofRandom(1, 3));
    }
    if(time > 0.74 && time < 0.75)
    {
        blackout(30);
    }
    
    //SCENE 4 ----------------------------
    if(time>0.75)
    {
        blackout(50);
        locX4 = ofMap(ofNoise(time*10 + noiseSeed), 0, 1, 0, ofGetWidth(), true);   //jiggle horizontally
        locY4 = ofMap(time, 0.75, 1, ofGetHeight() + 400, - 500, true); //move from bottom to top
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

//SCENE 1 --------------------------------------------------
//--------------------------------------------------------------
void ofApp::drawHead(float x, float y, float size)
{
    ofSetColor(ofMap(locY1, 0, ofGetHeight(), 0, 50, true), ofMap(locX1, 0, ofGetWidth(), 0, 40, true));
    ofNoFill();
    ofDrawCircle(x, y, size + size * 0.3 * sin(ofDegToRad(angle)));
}

//--------------------------------------------------------------
void ofApp::drawTalis(float x, float y, float size)
{
    ofTranslate(x, y);
    ofPushMatrix();
    ofRotate(angle);
    ofSetColor(255 * ofNoise(time * 85), 20, 0, ofMap(locX1, 0, ofGetWidth(), 0, 200, true));
    ofFill();
    ofDrawCircle(size * 2, 0, ofRandom(size));
    ofDrawCircle(size * -2, size * 2, ofRandom(size));
    ofDrawCircle(size * -2, size * -2, ofRandom(size));
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawTentacles(float x, float y, float radius, float stepSize)
{
    float angleStep = 360.0/numTentacles;
    ofTranslate(x, y);
    ofPushMatrix();
    ofRotate(angle * 0.1);
    ofSetColor(50, ofMap(locX1, 0, ofGetWidth(), 0, 40, true));
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

//--------------------------------------------------------------
void ofApp::blackout(float speed)
{
    ofSetColor(255, 255, 240, speed);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetHeight());
    for (int i = 0; i<numStrings; i++)
    {
        ofSetColor(stringColor[i], stringColor[i], stringColor[i]-15, speed);
//        ofDrawLine(backX[i], backY[i] - length[i], backX[i], backY[i] + length[i]);
        ofDrawLine(backX[i] - length[i], backY[i], backX[i] + length[i], backY[i]);
    }
}

//SCENE 2 --------------------------------------------------
//--------------------------------------------------------------
void ofApp::drawStar(float x, float y, float size,float offset, int numParticles, int numLegs)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofPushMatrix();

    ofRotate(720 * ofNoise(time * 50 + offset));
    for (int j = 0; j<numLegs; j++)
    {
        ofPushMatrix();
        ofRotate(360/numLegs * j);
        for (int i = 0; i<numParticles; i++)
        {
            float space = size/numParticles;
            ofSetColor(ofRandom(255), 100);
            ofFill();
            ofDrawCircle(space * i, 0, space/10 + space/2 * ofNoise((time * 100 + offset) * 5 + i));
        }
        ofPopMatrix();
    }
    
    ofSetColor(50, 255 * (1 - ofNoise(time * 200 + offset)));
    ofFill();
    ofDrawCircle(0, 0, size * ofNoise(time * 200 + offset));
    ofNoFill();
    ofDrawCircle(0, 0, size * (1.5 + 0.1 * sin(ofDegToRad(angle + offset))));
    ofSetColor(255, 10, 0, 100);
    ofNoFill();
    ofDrawCircle(0, 0, size * (0.5 + 0.3 * sin(ofDegToRad(angle + offset))));
    ofPopMatrix();
    ofPushMatrix();
    ofRotate(angle * 0.3 + offset);
    ofSetColor(50  * (1 + 0.1 * sin(ofDegToRad(angle + offset))), 100);
    ofFill();
    ofDrawCircle(size * 1.2, 0, size/20);
    ofDrawCircle(size * -1.2, 0, size/20);
    ofDrawCircle(0, size * 1.2, size/20);
    ofDrawCircle(0, size * -1.2, size/20);
    ofPopMatrix();
    ofPopMatrix();
}

//SCENE 3 --------------------------------------------------
//--------------------------------------------------------------
void ofApp::drawCore(float x,float y, float radius, float stepSize)
{
    float angleStep = 360.0/totalRays;
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(angle * 0.8);
    ofSetColor(255, 10, 0, ofMap(time, 0.51, 0.53, 0, 10, true));
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

//--------------------------------------------------------------
void ofApp::drawRing(float x,float y, float radius, float stepSize)
{
    
    float angleStep = 360.0/totalRays;
    ofPushMatrix();
    ofTranslate(x, y);
    ofPushMatrix();
    ofRotate(angle);
    ofTranslate(10 * ofNoise(time), 0);
    ofSetColor(0, ofMap(time, 0.51, 0.53, 0, 30, true));
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

//--------------------------------------------------------------
void ofApp::drawDot(float x,float y, float radius)
{
    
    float angleStep = 360.0/totalRays;
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(angle * 100);
    ofSetColor(ofRandom(0, 50), ofMap(ofNoise(time*30), 0, 1, 0, 255, true));
    ofFill();
    ofDrawCircle(10, 0, radius);
    ofPopMatrix();
}

//SCENE 4 -----------------------------
//--------------------------------------------------------------
void ofApp::drawBrunch(float length)
{
    ofSetColor(0, 50);
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

//--------------------------------------------------------------
void ofApp::drawSkin(float x,float y, float radius, float stepSize)
{
    float angleStep = 360.0/resolution;
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(0, 50);
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
        ofSetColor(ofRandom(100, 255), 10, 0);
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
        ofSetColor(ofRandom(0, 255), 10, 0);
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
    ofSetColor(ofRandom(0, 50), ofMap(flashSize, radius, radius * 2, 255, 0));
    ofNoFill();
    ofDrawCircle(x, y, flashSize);
}
