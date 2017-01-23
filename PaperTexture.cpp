#include "PaperTexture.hpp"


PaperTexture::PaperTexture()
{
    numStrings = 1000;
    ofBackground(255, 255, 240);
    for (int i = 0; i<numStrings; i++)
    {
        backX.push_back(ofRandomWidth());
        backY.push_back(ofRandomHeight());
        stringColor.push_back(ofRandom(240, 255));
        length.push_back(ofRandom(50, 100));
    }
}

void PaperTexture::display(float fadeoutSpeed)
{
    ofSetColor(255, 255, 240, fadeoutSpeed);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetHeight());
    
    //draw plate
    plate.draw(ofGetWidth()/30, ofGetHeight()*28/30 - 300, 80, 300);
    ofSetColor(255, 255, 240);
    
    
    for (int i = 0; i<numStrings; i++)
    {
        ofSetColor(stringColor[i], stringColor[i], stringColor[i]-15, fadeoutSpeed);
        ofDrawLine(backX[i] - length[i], backY[i], backX[i] + length[i], backY[i]);
    }
}
