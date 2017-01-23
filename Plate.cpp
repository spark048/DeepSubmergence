#include "Plate.hpp"

Plate::Plate()
{
    fontL.loadFont("AdobeKaitiStd-Regular.otf", 35);
    fontS.loadFont("AdobeKaitiStd-Regular.otf", 25);
    
    frameColorOut = ofColor(100);
    frameColorBorder = ofColor(255, 255, 240);
    frameColorIn = ofColor(255, 255, 240);
}

//draw plate 深淵之怪
void Plate::draw(float x, float y, float w, float h)
{
    ofPushStyle();
    ofSetColor(frameColorOut);
    ofFill();
    ofDrawRectangle(x, y, w, h);
    ofSetColor(frameColorBorder);
    ofNoFill();
    ofSetLineWidth(3);
    ofDrawRectangle(x + w * 0.05, y + w * 0.05, w * 0.9, h - w * 0.1);
    ofSetColor(frameColorIn);
    ofFill();
    ofDrawRectangle(x + w * 0.15, y + w * 0.15, w * 0.7, h - w * 0.3);
    
    ofSetColor(frameColorOut * 0.5);
    fontL.drawString("深", x + w * 0.21, y + h * 0.27);
    fontL.drawString("淵", x + w * 0.21, y + h * 0.27 + 60);
    fontS.drawString("之", x + w * 0.21 + 8, y + h * 0.27 + 110);
    fontL.drawString("怪", x + w * 0.21, y + h * 0.27 + 170);
    ofPopStyle();
}
