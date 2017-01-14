

#include "Octopus.h"

Octopus::Octopus()
{
    numTentacles = 5;
    for(int i=0; i<numTentacles; i++) noiseSeeds.push_back(ofRandom(10000));
}

void Octopus::drawHead(float x, float y, float size, float angle, float time)
{
    ofSetColor(ofMap(locY, 0, ofGetHeight(), 0, 100, true), ofMap(locX, 0, ofGetWidth(), 0, 40, true));
    ofNoFill();
    ofDrawCircle(x, y, size + size * 0.3 * sin(ofDegToRad(angle)));
}

//--------------------------------------------------------------
void Octopus::drawTalis(float x, float y, float size, float angle, float time)
{
    ofTranslate(x, y);
    ofPushMatrix();
    ofRotate(angle);
    ofSetColor(255 * ofNoise(time * 85), 20, 0, ofMap(locX, 0, ofGetWidth(), 0, 200, true));
    ofFill();
    ofDrawCircle(size * 2, 0, ofRandom(size));
    ofDrawCircle(size * -2, size * 2, ofRandom(size));
    ofDrawCircle(size * -2, size * -2, ofRandom(size));
    ofPopMatrix();
}

//--------------------------------------------------------------
void Octopus::drawTentacles(float x, float y, float radius, float stepSize, float angle, float time)
{
    float angleStep = 360.0/numTentacles;
    ofTranslate(x, y);
    ofPushMatrix();
    ofRotate(angle * 0.1);
    ofSetColor(100, ofMap(locX, 0, ofGetWidth(), 0, 40, true));
    ofFill();
    for (int i=0; i<numTentacles; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds[i]) * stepSize;
        float pointX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float pointY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds[i] += 0.01;
        ofDrawCircle(pointX, pointY, 2);
    }
    ofPopMatrix();
}

void Octopus::display(float angle, float time)
{
    {
        locX = ofMap(time, 0, 0.24, 0, ofGetWidth() + 200, true);
        locY = ofMap(ofNoise(time*20 + 777), 0, 1, 0, ofGetHeight(), true);
        drawHead(locX, locY, 60, angle, time);
        drawTalis(locX, locY, 4, angle, time);
        drawTentacles(locX - 800, 0, 180, 40, angle, time);
    }
}
