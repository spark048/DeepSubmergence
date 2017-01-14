#pragma once

#include "ofMain.h"
#include "Octopus.h"
#include "Ball.h"
#include "Serpent.hpp"
#include "Jellyfish.hpp"
#include "PaperTexture.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    float time, angle;
    int minutes;
    int totalMillis;
    float noiseSeed;
    
    Octopus octopus;
    Ball ball;
    Serpent serpent;
    Jellyfish jellyfish;
    PaperTexture blackout;
};
