#include "Jellyfish.hpp"

Jellyfish::Jellyfish()
{
    resolution = 30;
    for(int i=0; i<resolution; i++) noiseSeeds.push_back(ofRandom(10000));
}

void Jellyfish::drawBrunch(float length, float angle, float time)
{
    ofSetColor(255, 255, 240);
    ofDrawLine(0, 0, 0, -length);
    if(length > (30 + 10 * ofNoise(time*10))/8)
    {
        ofPushMatrix();
        ofTranslate(0, -length);
        ofPushMatrix();
        ofRotate(15 + 10 * sin(ofDegToRad(angle)));
        drawBrunch(length * 0.8, angle, time);
        ofPopMatrix();
        ofPushMatrix();
        ofRotate(-15 - 10 * sin(ofDegToRad(angle)));
        drawBrunch(length * 0.8, angle, time);
        ofPopMatrix();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void Jellyfish::drawSkin(float x,float y, float radius, float stepSize, float angle, float time)
{
    float angleStep = 360.0/resolution;
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(0, 50 * ofNoise(time*100));
    ofFill();
    ofBeginShape();
    for (int i=0; i<resolution; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds[i]) * stepSize;
        float endX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float endY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds[i] += 0.01;
        ofVertex(endX, endY);
    }
    ofEndShape(true);
    ofPopMatrix();
}

//--------------------------------------------------------------
void Jellyfish::drawInnerSkin(float x,float y, float radius, float stepSize, float angle, float time)
{
    float angleStep = 360.0/resolution;
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(255, 255, 240);
    ofNoFill();
    ofBeginShape();
    for (int i=0; i<resolution; i++)
    {
        float noisedRadius = radius + ofNoise(noiseSeeds[i]) * stepSize;
        float endX = sin(ofDegToRad(i*angleStep)) * noisedRadius;
        float endY = cos(ofDegToRad(i*angleStep)) * noisedRadius;
        noiseSeeds[i] += 0.01;
        ofVertex(endX, endY);
    }
    ofEndShape(true);
    ofPopMatrix();
}

//function to draw five lines of dots
void Jellyfish::drawHeart(float x,float y, float radius, float angle, float time)
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
        noiseSeeds[i] += 0.01;
        ofDrawCircle(endX, endY, radius/20 * (1 + sin(ofDegToRad(-angle))));
    }
    ofPopMatrix();
}

//function to draw outer surrounding needles
void Jellyfish::drawNeedles(float x,float y, float radius, float angle, float time)
{
    float angleStep = 360.0/resolution;
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(angle * ofNoise(noiseSeeds[0]));
    for (int i=0; i<resolution; i++)
    {
        ofSetColor(ofRandom(0, 255), 10, 0);
        ofFill();
        float startX = sin(ofDegToRad(i*angleStep)) * radius * 0.95;
        float startY = cos(ofDegToRad(i*angleStep)) * radius * 0.95;
        float endX = sin(ofDegToRad(i*angleStep)) * radius;
        float endY = cos(ofDegToRad(i*angleStep)) * radius;
        noiseSeeds[i] += 0.01;
        ofDrawLine(startX, startY, endX, endY); //length is 5% of radius
    }
    ofPopMatrix();
}

//function to draw outer surrounding needles
void Jellyfish::drawFlash(float x,float y, float radius, float angle, float time)
{
    float flashSize = radius * (1 + abs(sin(ofDegToRad(angle))));
    ofSetColor(ofRandom(0, 50), ofMap(flashSize, radius, radius * 2, 255, 0));
    ofNoFill();
    ofDrawCircle(x, y, flashSize);
}

void Jellyfish::display(float angle, float time)
{
    locX = ofMap(ofNoise(time*10 + 777), 0, 1, 0, ofGetWidth(), true);   //jiggle horizontally
    locY = ofMap(time, 0.75, 1, ofGetHeight() + 400, - 500, true); //move from bottom to top
    ofPushMatrix();
    ofTranslate(locX, locY);
    ofRotate(angle * 0.1);
    drawSkin(0, 0, 200 + 20 * -sin(ofDegToRad(angle)), 60, angle, time);  //draw outer double skin
    ofPushMatrix();
    ofRotate(-angle);
    drawSkin(0, 0, 200 + 20 * -sin(ofDegToRad(angle)), 60, angle, time);  //draw outer double skin
    ofPopMatrix();
    drawSkin(0, 0, 170, 20, angle, time);    //draw inner body
    drawInnerSkin(0, 0, 170, 20, angle, time);    //draw inner skin
    drawNeedles(0, 0, 270 - 20 * sin(ofDegToRad(angle)), angle, time);
    for(int i=0; i<5;i++)
    {
        ofPushMatrix();
        ofRotate(72 * i);
        drawBrunch(30 + 10 * ofNoise(time*10), angle, time); //draw five branches
        ofPopMatrix();
    }
    for(int i=0; i<5;i++)
    {
        drawHeart(0, 0, 20*i, angle, time);  //draw five red dot on each line
    }
    drawFlash(0, 0, 170, angle, time);
    ofPopMatrix();
}
