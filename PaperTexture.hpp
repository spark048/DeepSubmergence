#pragma once
#include "ofMain.h"
#include "Plate.hpp"

class PaperTexture
{
public:
    PaperTexture();
    
    void display(float fadeoutSpeed);
    
    vector <float> backX;
    vector <float> backY;
    vector  <float> stringColor;
    vector <float> length;
    int numStrings;
    ofImage backgroundImage;
    
    Plate plate;
};
