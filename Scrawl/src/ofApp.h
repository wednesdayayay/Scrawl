#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp, public ofxMidiListener{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void newMidiMessage(ofxMidiMessage& message);
    
    
    ofxMidiIn midiIn;
    std::vector<ofxMidiMessage> midiMessages;
    std::size_t maxMessages = 10; //< max number of messages to keep track of
    
    
    
    
    ofImage imgScreenshot;
    int count;
    
    
    ofFbo fbo;
    
    
    bool fill = true;
    bool brushcolor = true;
    bool bcolorize = false;
    bool mirrorScale = false;
    bool mirror = false;
    bool erase = false;
    bool drawing = true;
    bool backGrad = false;
    bool backColor = false;
    bool brushpreview = true;
    
    
    //
    
    
    int brush = 1;
    int size = 45;
    int size2 = 15;
    int mirrorshape = 4;
    int scaleamount = 1.1;
    int randomtime = 30;
    int ColorofBrush = 1;
    
    //color values for the brushes
    int brushred = 255;
    int brushgreen = 255;
    int brushblue = 255;
    int brushalpha = 255;
    
    //random colors variables
    int ranred = 0;
    int rangreen = 0;
    int ranblue = 0;
    int ranalpha = 0;
    
    //background colors
    int bcolor1 = 0;
    int bcolor2 = 0;
    int bcolor3 = 0;
    
    //background gradient variables
    int bgcolor1 = 1;
    int bgcolor2 = 255;
    int bgcolor3 = 1;
    int bgcolor4 = 255;
    
    //translation XYZ
    int transx = 0;
    int transy = 0;
    int transz = 0;
    
    //extra variable for shapes like triangle+rectangle
    int trix=1;
    int triy=1;
    int triz=0;
    
    //circle resolution variable
    int cirres = 200;
    
    //MIDI mouse
    int midimouseX = 0;
    int midimouseY = 0;
    
    int screenX = ofGetHeight()/2;
    int screenY = ofGetWidth()/2;
    
    
    
    
    
};
