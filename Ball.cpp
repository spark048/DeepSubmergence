////////////////////////////
/////Project Name: Deep Submergence
/////08.01.2017
/////Written by Soonpart
/////soonpart@gmail.com
////////////////////////////

#include "Ball.h"

Ball::Ball()
{
    numStars = 20;
    for (int i = 0; i < numStars; i++)
    {
        locX.push_back(ofGetWidth() + ofRandomWidth());
        locY.push_back(ofGetHeight() + ofRandomHeight());
        size.push_back(ofRandom(10, 45));
        offset.push_back(ofRandom(10000));
        numParticles.push_back(ofRandom(3, 10));
        numLegs.push_back(ofRandom(4, 12));
    }
}

void Ball::drawStar(float x, float y, float size,float offset, int numParticles, int numLegs, float angle, float time)
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

void Ball::display(float angle, float time)
{
    for (int i = 0; i < numStars; i++)
    {
        locX[i] += ofGetWidth()/300 * (ofNoise(time * 100 + offset[i]) - 0.8);
        locY[i] += ofGetHeight()/300 * (ofNoise(time * 100 + offset[i] + 10000) - 0.8);
        drawStar(locX[i], locY[i], size[i], offset[i], numParticles[i], numLegs[i], angle, time);
    }
}
