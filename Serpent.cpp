#include "Serpent.hpp"

Serpent::Serpent()
{
    numPoints = 20;
    for(int i=0; i<numPoints; i++)
    {
        noiseSeeds.push_back(ofRandom(10000));
    }
}

void Serpent::drawCore(float x,float y, float radius, float stepSize, float angle, float time)
{
    float angleStep = 360.0/numPoints;
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(angle * 0.8);
    ofSetColor(255, 10, 0, 10);
    ofNoFill();
    ofBeginShape();
    for (int i=0; i<numPoints; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds[i]) * stepSize;
        float pointX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float pointY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds[i] += 0.01;
        ofVertex(pointX, pointY);
    }
    ofEndShape(true);
    ofPopMatrix();
}

//--------------------------------------------------------------
void Serpent::drawRing(float x,float y, float radius, float stepSize, float angle, float time)
{
    float angleStep = 360.0/numPoints;
    ofPushMatrix();
    ofTranslate(x, y);
    ofPushMatrix();
    ofRotate(angle);
    ofTranslate(10 * ofNoise(time), 0);
    ofSetColor(0, 20);
    ofNoFill();
    ofBeginShape();
    for (int i=0; i<numPoints; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds[i]) * stepSize;
        float pointX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float pointY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds[i]+=0.01;
        ofVertex(pointX, pointY);
    }
    ofEndShape(true);
    ofPopMatrix();
    ofPopMatrix();
}

//--------------------------------------------------------------
void Serpent::drawDot(float x,float y, float radius, float angle, float time)
{
    
    float angleStep = 360.0/numPoints;
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(angle * 100);
    ofSetColor(ofRandom(0, 50), ofMap(ofNoise(time*30), 0, 1, 0, 255, true));
    ofFill();
    ofDrawCircle(10, 0, radius);
    ofPopMatrix();
}

void Serpent::display(float angle, float time)
{
    locX = ofMap(ofNoise(time*20 + 777), 0, 1, 0, ofGetWidth(), true);
    locY = ofMap(time, 0.51, 0.74, -50, ofGetHeight() + 100, true);
    drawCore(locX, locY, 35 + 10 * sin(ofDegToRad(angle)), 20, angle, time);
    drawRing(locX, locY, 60, 8, angle, time);
    drawDot(locX, locY, ofRandom(1, 3), angle, time);
}
