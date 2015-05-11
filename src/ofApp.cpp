//Created by Andreasmuller in 2015.

#include <ofApp.h>
void ofApp::setup()        //To define the basic environment conditions before the program starts.
{
    ofSetFrameRate( 60 );       //frame rate is 60
    screenLengthInSecs = 4.0f;      //screen length is 4.0f
    autoPlay = true;        //make the auto play work
    keyTimeVel = 0;     //time velocity is 0
    time = 0;       //set up time is 0
}

// -----------------------------------------------------------------------
void ofApp::update()       //To create the update code
{
    
    if( ofGetKeyPressed( OF_KEY_LEFT ) )        //key press in
    {
        keyTimeVel = ofLerp( keyTimeVel, screenLengthInSecs * -0.02f, 0.02 );       //set up the velocity od key time
        autoPlay = false;       //close the auto play
    }
    
    else if ( ofGetKeyPressed( OF_KEY_RIGHT ) )     //if ... else
    {
        keyTimeVel = ofLerp( keyTimeVel, screenLengthInSecs *  0.02, 0.02 );        //set up the velocity od key time
        autoPlay = false;       //close the auto play
    }
    
    if( autoPlay )      //if .. else
    {
        time += ofGetLastFrameTime();       //give an instruct to time
    }
    
    else        //if ... else
    {
        time += keyTimeVel;     //give a new instruct to time
    }
    
    keyTimeVel = ofLerp( keyTimeVel, 0.0f, 0.05 );      //key time velocity
}

// -----------------------------------------------------------------------
void ofApp::draw()     //To excute the code.
{
    float w = ofGetWidth();     //set up a float w
    float h = ofGetHeight();        //set up a float h
    float middleY = h * 0.7;        //set up a float middle Y
    float magnitude = 300;      //set up a float magnitude
    ofRectangle terrainRect( 0, middleY-magnitude, w, magnitude );      //set up a rectangle
    
    float mx = ofMap( ofGetMouseX(), 0, ofGetWidth(),  0.0f, 1.0f );        //float mx's width
    float my = ofMap( ofGetMouseY(), 0, ofGetHeight(), 0.0f, 1.0f );        //float my's height
    
    
    ofBackgroundGradient( ofColor( 10, 10, 40), ofColor::black, OF_GRADIENT_CIRCULAR );     //background color
    ofEnableBlendMode( OF_BLENDMODE_ALPHA );        //embed a new file
    
    ofSetColor( ofColor::white );       //set color
    ofLine( ofVec2f( 0, middleY), ofVec2f( ofGetWidth(), middleY ) );	// draw a line showing the middle
    
    bool drawClean = ofGetKeyPressed(' ');      //key press space button
    
    if( !drawClean )        //if .. else
    {
        // Draw some lines to show where the unit edges are (0,1,2, etc)
        drawDashes( time, (int)screenLengthInSecs, w / screenLengthInSecs );
        drawTerrain( terrainRect, ofGetWidth(), time, screenLengthInSecs );
    }
    
    // I'm storing this in a ofVec3f instead of a ofVec2f only because the oF ofVec2f doesn't have a cross product operator
    ofVec2f terrainMousePos 	= getTerrain( ofGetMouseX(), terrainRect, time, screenLengthInSecs );
    
    // We can easily get a normal for the point by simply sampling our terrain a little bit ahead in time and taking the cross product.
    // The further ahead we look, the smoother our normals will be, but look ahead too far and the normal isn't very representative
    float lookAheadPixels = 4;
    ofVec2f terrainMouseNormal = (terrainMousePos - getTerrain( ofGetMouseX() + lookAheadPixels, terrainRect, time, screenLengthInSecs)).getNormalized().getRotated(90);
    
    ofSetColor( ofColor::lightPink );       //set color
    ofCircle( terrainMousePos, 6.0 );       //set mouse position
    
    if( !drawClean ) ofLine( terrainMousePos, terrainMousePos + (terrainMouseNormal*12));       //draw the line
    
    ofSetColor( ofColor::slateGray, 20 );       //set color
    ofNoFill();     //no color fill in
				ofRect( terrainRect );      //the rect
    ofFill();       //fill color
}

// -----------------------------------------------------------------------
float ofApp::getTerrainHeight( float _t )      //float terrain height
{
    // We've set things up so the time units are seconds for this function
    float result = 0.0f;
    
    //result += shape::pulseSquare( 6.0, 1.0, _t );
    //result += shape::pulseTriangle( 3.0, 1.0, _t );
    //result += shape::pulseTriangle( 1.0, 1.0, _t );
    //result += shape::pulseLineDownUp( 3.0, 1.0, _t );
    //result += shape::pulseLineUpDown( 3.0, 1.0, _t );
    //result += shape::pulseSine( 3.0, 0.5, _t );
    //result += shape::pulseSmoothStep( 3.0, 0.0, 0.3, 0.8, 1.4, _t );
    //result += shape::pulseTriangle( 3.0, 1.5, _t );
    //result += shape::pulseLinearStep( 3.0, 0.0, 1.0, 2.0, 3.0, _t );
    //result += shape::pulseSmoothStep( 3.0, 0.0, 1.0, 1.2, 2.4, _t );
    //result += shape::pulseTriangle( 0.5, 0.5, _t ) * 0.2;
    result += shape::pulseSine( 0.5, 0.5, _t * (ofMap(ofNoise( _t * 0.3 ), 0, 1, 0.2, 1.0)) ) * 0.2;
    //result += shape::pulseSawTooth( 3.0, 1.0, _t );
    //result += ofNoise( _t * (16.0 * ofNoise( _t * 0.1 )) );// * shape::pulseSmoothStep( 3.0, 0.0, 0.3, 0.8, 1.4, _t );
    //result += ofNoise( _t * 1.0 ) * shape::pulseSmoothStep( 10.0, 0.0, 1.0, 3.0, 4.5, _t );
    //result *= ofNoise( _t * 0.1 );
    
    //result += ofNoise( _t * ((shape::pulseTriangle( 1.0, 1.0, _t ) * 2) + 2) );
    
    //result += ofNoise( _t * ofMap( shape::pulseTriangle( 10.0, 10.0, _t ), 0, 1, 0.01, 1) );
    //result += shape::fbm( _t * 1.4, 5 );
    //result += ofNoise( _t * 2 );
    
    //result += (shape::pulseTriangle( 10.0, 10.0, _t ) * 0.8) + (ofNoise( _t * 2 ) * 0.2);
    
    //result *= ofNoise( _t * 0.03 );
    
    //result /= 2.0;
    return result;      //the return function
}

// -----------------------------------------------------------------------
ofVec2f ofApp::getTerrain( float _x, ofRectangle _rect, float _time, float _rectWidthInSecs )      //set 2 new vectors
{
    float vertexTime = ofMap( _x, 0, _rect.width, _time, _time + _rectWidthInSecs );        //float vertex time
    
    ofVec2f pos;        //the position of the 2 vectors
    pos.x = _x;     //the position of x
    pos.y = -getTerrainHeight( vertexTime ) * _rect.height;     //the position of y
    pos += _rect.position + ofVec2f(0, _rect.height);       //the position of rect
    
    return pos;     //the return function
}

// -----------------------------------------------------------------------
void ofApp::drawTerrain( ofRectangle _rect, int _res, float _time, float _screenLengthInSecs  )        //draw the terrain
{
    float w = ofGetWidth();     //the acronym of width
    
    ofMesh mesh;        //set up mesh
    mesh.setMode( OF_PRIMITIVE_LINE_STRIP );        //mesh mode
    
    for( int i = 0; i < _res; i++ )     //for working the motion
    {
        float frac = i / (float)_res;       //float the frac
        float vertexTime = ofMap( i, 0, _res, _time, _time + _screenLengthInSecs );     //to define the vertex time
        
        ofVec2f pos;        //set up the vectors' position
        pos.x = ofMap( i,  0, _res,  0, _rect.width );      //the postion of x
        pos.y = -getTerrainHeight( vertexTime ) * _rect.height;     //the postion of y
        
        pos += _rect.position + ofVec2f(0, _rect.height);// + pos;
        
        mesh.addVertex( pos );      //add position
    }
    ofSetColor( ofColor::white );       //set color
    mesh.draw();        //to draw
}

// -----------------------------------------------------------------------
void ofApp::drawDashes( float _time, int _numDashes, float _pixelsPerSec )     //sdraw dashed
{
    float w = ofGetWidth();     //the acronym of width
    float h = ofGetHeight();        //the acronym of height
    ofMesh bgSecondsMesh;       //the name of ofMesh
    bgSecondsMesh.setMode( OF_PRIMITIVE_LINES );        //bg's mode
    for( int i = 0; i < _numDashes; i++ )       //to amke the animation move
    {
        float tmpX = w - ((fmodf( time, 1.0 ) + i) * _pixelsPerSec);        //float tmX
        bgSecondsMesh.addVertex( ofVec2f( tmpX, 0) );       //the position of bg
        bgSecondsMesh.addVertex( ofVec2f( tmpX, h) );       //the position of bg
    }
    ofSetColor( ofColor::white, 100 );      //to set the color
    bgSecondsMesh.draw();       //the draw function of bg
}

// -----------------------------------------------------------------------
void ofApp::keyPressed( int _key )     //To set up the keyboard control.
{
    if( _key == 'a' )       //key button a
    {
        autoPlay = true;        //make it work
    }
}
