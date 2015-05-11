//Created by Andreasmuller in 2015.

#pragma once

#include "ofMain.h"
#include "Math/MathUtils.h"

typedef MathUtils shape;        // Shortcut to make the code a tad more redable later

class ofApp : public ofBaseApp      //set up the public app
{
public:     //the rest code will be public
    
// -----------------------------------------------------------------------
    void setup();        //To define the basic environment conditions before the program starts.
    void update();       //To create the update code
    void draw();     //To excute the code.
    void drawTerrain( ofRectangle _rect, int _res, float _time, float _screenLengthInSecs  );        //draw the terrain
    void drawDashes( float _time, int _numDashes, float _pixelsPerSec );     //sdraw dashed
    void keyPressed( int _key );    //To set up the keyboard control.
    float getTerrainHeight( float _t );
    ofVec2f getTerrain( float _x, ofRectangle _rect, float _time, float _rectWidthInSecs );
    
    float time;     //to define time
    float screenLengthInSecs;       //to define screenLengthInSecs
    float keyTimeVel;       //to define keyTimeVel
    bool autoPlay;      //to define autoPlay
};
