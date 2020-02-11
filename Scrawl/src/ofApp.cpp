#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    //ofSetFrameRate(30);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    
    
    ////MIDI stuff
    // print input ports to console
    midiIn.listInPorts();
    
    //if MIDI isn't working check your device number in the consdole when you first make it
    //change the (0) to whatever your MIDI controller is
    //midiIn.openPort(0);
    midiIn.openPort(1);
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    
    // print received messages to the console
    midiIn.setVerbose(true);
    ////
    
    ofBackground(0);
    //**if background color then double the FBO allocation on W&H otherwise don't
    
    //fbo.allocate(ofGetWidth()*2, ofGetHeight()*2 );
    fbo.allocate(ofGetWidth(), ofGetHeight());
    ofSetFrameRate(30);
    
    fbo.begin();
    ofClear(0);
    fbo.end();
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){


    
    if ((mirror == true)
        or (mirrorScale == true)) {
        screenX  = ofGetHeight()/2;
        screenY = ofGetWidth()/2;}
    
    if ((mirror == false) &&
        (mirrorScale==false)) {
        screenX = 0;
        screenY = 0;}
    
    ofVec2f mousePos(mouseX+midimouseX - screenX, mouseY+midimouseY - screenY);
    
    
    //sets the color vairables for the background gradient
    //[colorOne] | gradient color is set by the brush color [brush(Red,Green,Blue,Alpha)]
    //when background color [backcolor] is ON.
    //this allows the color to be stored and then set to something else for the brush when OFF
    //colorTwo | bcolor is set directly as it is for regular background operation
    ofColor colorOne = ofColor(bgcolor1, bgcolor2, bgcolor3);
    ofColor colorTwo = ofColor(bcolor1, bcolor2, bcolor3);
    //setting variables for color randomization so that it doesn't blank out in the FBO loop
    //allowing for a slowing of the randomization
    if (ofGetFrameNum() % randomtime == 0){
          ranred   = ofRandom(0,brushred),
          rangreen = ofRandom(0,brushgreen),
          ranblue  = ofRandom(0,brushblue),
          ranalpha = ofRandom(0,brushalpha);}
    
//** could to be momentary not toggle for MIDI??
    //if [backgrad] OFF
    //anytime the buffer is erased it points to [colorTwo] which is set by [bcolors(1-3)]
    
    //if [backgrad] ON
    //anytime the buffer is erased it points to [backgroundgradient] which is set by [bcolors(1-3),[bgcolors(1-4)]
    
    //meaning you can color the background then draw/point over that color
    if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)
        or (erase == true)
        or (ofGetKeyPressed('q'))){
        
            fbo.begin();
            ofClear(0);
        
            //background gradient [backGrad] ON/OFF this will allow you to set a gradient
            //rather than solid color background.
            //notice the use of [bgcolor4] here. if back ground gradient is ON
            //this allows you to fade in and out the [colorOne] via [brushalpha] knob
            //and will not change the brush alpha level at the same time.
            //Alpha fade only works when [backgrad] & [backcolor] are ON
            //that way you can set different levels of alpha for the brush and gradient
//**could be nice to be able to switch between gradient types
            if(backGrad == true) {ofBackgroundGradient(colorOne*(bgcolor4/255.0), colorTwo, OF_GRADIENT_CIRCULAR);}
                //if(backGrad == true) {ofBackgroundGradient(colorOne*(bgcolor4/255.0), colorTwo, OF_GRADIENT_BAR);}
                //if(backGrad == true) {ofBackgroundGradient(colorOne*(bgcolor4/255.0), colorTwo, OF_GRADIENT_LINEAR);}
        
            if(backGrad == false) {ofBackground(colorTwo);}
            fbo.end();}
    
    //XYZ translation for entire image double Width and Height then use traslate to access 4 quadrants
    //may change back...if so just cut this translate out and paste over next one ie [translate]0,0,0
    ofTranslate(transx, transy, 0);
    //ofTranslate(transx, transy, transz);
    
    
    
    
    fbo.begin();
    //start drawing loop
    //if drawing is true skip the background stuff and just do the brush
    if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)
        or (drawing == true)){
            ofPushStyle();
                //in all 4 of the next coloring modes you either have full control via knobs/keyboard interface
                //or one or more of the colors are randomized with the max being the knob/keyboard
                //so you can dial in certain ranges to randomize around
                if (brushcolor == true) {
                    //full control
                    if (ColorofBrush == 1)
                    {ofSetColor(brushred,brushgreen,brushblue,brushalpha);}
                    //alpha random color control
                    if (ColorofBrush == 2)
                    {ofSetColor(brushred,brushgreen,brushblue,ranalpha);}
                    //color random alpha control
                    //the following two modes have their time between randomization set by [randomtime]
                    if (ColorofBrush == 3)
                    {ofSetColor(ranred,rangreen,ranblue,brushalpha);}
                    //full random
                    if (ColorofBrush == 4)
                    {ofSetColor(ranred,rangreen,ranblue,ranalpha);}}
        
                //if [brushcolor] is OFF set to white with alpha control for brightness
                // you can toggle back and forth between your color and white
                if (brushcolor == false) {ofSetColor(255,brushalpha);}
        
        
                //this uses the fill toggle to turn [fill] ON and OFF for brushes
                if (fill == true) {ofFill();}
                if (fill == false) {ofNoFill();}
                //
        
                //XYZ translation for entire image
                //when mirroring shifts the whole image
                //moved translation stuff above FBO begin to allow for translating entire image
                ofTranslate(0, 0, 0);
        
                //start mirroring (should be after inital translate)
                ofPushMatrix();

                //logic to set correct translation for both mirroring and regular brush
                //when mirroring / scaling I want to be drawing from center of screen
                if ((mirror == true) or
                    (mirrorScale == true))
                        {ofTranslate(ofGetWidth()/2, ofGetHeight()/2);}
                if ((mirror == false) &&
                    (mirrorScale == false))
                        {ofTranslate(0,0);}
        
                    //mirroring substance
                    //i = number of brushes to be drawn
                    //[mirrorshape] set by 3 MIDI buttons to select between
                    //2,4,8,16,32,64
                    for (int i=0; i<mirrorshape; i++) {
                        
                        //allows for combining effect [mirror] and [mirrorScale]
                        //[mirrorScale] will scale the brush a specified amount for each time drawn [i]
                        //[mirror] will rotate a certain number of degrees each time [i] is drawn
                        if (mirrorScale == true){ofScale(scaleamount/711.0*3-3);}
                        if (mirror == true){ofRotateDeg(360.0/mirrorshape);}
                        
                        
                        
//** try colorization here too for random per shape?
                        //Circle brush
                        if (brush == 1) {
                            //set circle resolution very high and you won't notice this behavior and you get a nice clean circle
                            //set it fairly low and you will start to see some noise introduced
                            //great for drawing more bold/chaotic lines with nofill OFF and paint ON
                            ofSetCircleResolution(cirres-ofRandom(0,10));
                            //if you don't want this one just comment out/delete above line & uncomment below
                            //ofSetCircleResolution(cirres);
                            
                            //logic to set correct translation to allow for mirror/brush modes
                            if ((mirror == true) or
                                (mirrorScale == true)) {
                                ofDrawCircle (mouseX - ofGetWidth()/2 - midimouseX,
                                              mouseY - ofGetHeight()/2 - midimouseY,
                                              size);}
                            
                            if ((mirror == false) &&
                                (mirrorScale==false)){
                                ofDrawCircle (mouseX - midimouseX,
                                              mouseY - midimouseY,
                                              size);}}
                        
                        //Rectangle brush
                        if (brush == 2) {
                            ofSetRectMode(OF_RECTMODE_CENTER);
                            //pretty much same as above except the added [size2] which allows for rectangle shaping
                            if ((mirror == true) or
                                (mirrorScale == true)) {
                                ofDrawRectangle(mouseX - ofGetWidth()/2 - midimouseX,
                                                mouseY - ofGetHeight()/2 - midimouseY,
                                                size*2, size2);}
                            
                            if ((mirror == false) &&
                                (mirrorScale==false)){
                                ofDrawRectangle(mouseX - midimouseX,
                                                mouseY - midimouseY,
                                                size*2, size2);}}
                        
                        
                        
                        //Triangle brush
                        if (brush == 3){
                            //[size2,trix,triy] all used for triangle shaping on individual corners
                            //[size] used to change whole shape
                            ofVec2f p1(0 * (size/382.), -triy - 100.0 * (size/382.));
                            ofVec2f p2(trix - 100. * (size/382.), 0 * (size/382.));
                            ofVec2f p3(0 * (size/382.),size2 + -100.0 * (size/382.));
                            
                            // Rotate the triangle points around the origin in degrees
                            //rotation amount [cirres]
                            float rotation = cirres*2.5;
                            p1.rotate(rotation);
                            p2.rotate(rotation);
                            p3.rotate(rotation);
                            
                            // Shift the triangle to the mouse position
                            p1 += mousePos  ;
                            p2 += mousePos  ;
                            p3 += mousePos  ;
                            
                            ofDrawTriangle(p1, p2, p3);}
                       
                        
                        
                        //random line brush
                        //simple brush for creating random lines accross the screen
                        //no real control
                        
    //**set up above to also be controled by randomtime then call here
                        if (brush == 4){
                            
                                if ((mirror == true) or
                                    (mirrorScale == true)) {
                                    ofDrawLine(ofRandom(ofGetWidth()/2),
                                               ofRandom(ofGetHeight()/2),
                                               ofRandom(ofGetWidth()/2),
                                               ofRandom(ofGetHeight()/2));}
                            
                            
                                if ((mirror == false) &&
                                    (mirrorScale==false)){
                                    ofDrawLine(ofRandom(ofGetWidth()),
                                               ofRandom(ofGetHeight()),
                                               ofRandom(ofGetWidth()),
                                               ofRandom(ofGetHeight()));} }
                        
                        
                        
                        
                        //starburst brush
                        if (brush == 5) {
                            //int numLines = 30;
                            //if using mirroring the a high [size2] things can start to slow down on the RPI
                            //just bring the [size2] down to create less lines at a time
                            int numLines = size2/6+1;
                            //int minRadius = 25;
                            int minRadius = cirres/5;
                            // int maxRadius = ofGetHeight()/5;
                            int maxRadius = size;
                            for (int i=0; i<numLines; i++) {
                                float angle = ofRandom(ofDegToRad(360.0));
                                float distance = ofRandom(minRadius, maxRadius);
                                float xOffset = cos(angle) * distance;
                                float yOffset = sin(angle) * distance;
                                float alpha = ofMap(distance, minRadius, maxRadius, brushalpha, 0);  // Make shorter lines more opaque set by [brushalpha]
                                    //
        //**delete all for single color brush
                                
                                if (brushcolor == true) {
                                    if (ColorofBrush == 1)
                                    {ofSetColor(brushred,brushgreen,brushblue,alpha);}
                                    if (ColorofBrush == 2)
                                    {ofSetColor(brushred,brushgreen,brushblue,ofRandom(0,alpha+ranalpha));}
                                    if (ColorofBrush == 3)
                                    {ofSetColor
                                        (ofRandom(0,brushred),
                                         ofRandom(0,brushgreen),
                                         ofRandom(0,brushblue),
                                         alpha);}
                                    if (ColorofBrush == 4)
                                    {ofSetColor
                                        (ofRandom(0,brushred),
                                         ofRandom(0,brushgreen),
                                         ofRandom(0,brushblue),
                                         ofRandom(0,alpha));}}
                                 
                                 //
        //**single color brush delete above, uncomment below
                                //ofSetColor(brushred,brushgreen,brushblue,alpha);
                                
                                
                                if ((mirror == true) or
                                    (mirrorScale == true)) {
                                    ofDrawLine(
                                               mouseX+ midimouseX - ofGetHeight()/2,
                                               mouseY+ midimouseY - ofGetWidth()/2,
                                               mouseX+xOffset-midimouseX - ofGetHeight()/2,
                                               mouseY+yOffset-midimouseY - ofGetWidth()/2);}
                                
                                if ((mirror == false) &&
                                    (mirrorScale==false)){
                                    ofDrawLine(
                                               mouseX+ midimouseX,
                                               mouseY+ midimouseY,
                                               mouseX+xOffset-midimouseX,
                                               mouseY+yOffset-midimouseY);}}}
                        
                        //"advanced" triangle brush
                        if (brush == 6)
                            //lets you position all angles freely so you can conjur up many more forms
                            //especially when using mirroring
                            {ofDrawTriangle(trix,  size,
                                            triy*1.5, mouseY,
                                            mouseX, size2*.7);}
                        }
                        ofPopStyle();
                        ofPopMatrix();
                    }
    
    fbo.end();
    //ofSetColor(255, 255, 255, 255);
    fbo.draw(0,0);
    
    
    

    

    //[brushpreview] controls ability to show brush and not paint it to FBO
    if(brushpreview == true)
    {
    //**try to add back in mirroring?
        ofPushStyle();
        
        //ofSetColor(brushred,brushgreen,brushblue,brushalpha);
        if (brushcolor == true) {
            //full control
            if (ColorofBrush == 1)
            {ofSetColor(brushred,brushgreen,brushblue,brushalpha);}
            //alpha random color control
            if (ColorofBrush == 2)
            {ofSetColor(brushred,brushgreen,brushblue,ranalpha);}
            //color random alpha control
            //the following two modes have their time between randomization set by [randomtime]
            if (ColorofBrush == 3)
            {ofSetColor(ranred,rangreen,ranblue,brushalpha);}
            //full random
            if (ColorofBrush == 4)
            {ofSetColor(ranred,rangreen,ranblue,ranalpha);}}
        
        //if [brushcolor] is OFF set to white with alpha control for brightness
        // you can toggle back and forth between your color and white
        if (brushcolor == false) {ofSetColor(255,brushalpha);}
        
        
        
            //Circle brush
            if (brush == 1) {
                
                    ofDrawCircle (mouseX - midimouseX,
                                  mouseY  - midimouseY,
                                  size);}
        
            
            //Rectangle brush
            if (brush == 2) {
                ofSetRectMode(OF_RECTMODE_CENTER);
                //pretty much same as above except the added [size2] which allows for rectangle shaping
                
                
                    ofDrawRectangle(mouseX - midimouseX,
                                    mouseY - midimouseY,
                                    size*2, size2);}
            
            
            
            //Triangle brush
            if (brush == 3){
                //[size2,trix,triy] all used for triangle shaping on individual corners
                //[size] used to change whole shape
                ofVec2f p1(0 * (size/382.), -triy - 100.0 * (size/382.));
                ofVec2f p2(trix - 100. * (size/382.), 0 * (size/382.));
                ofVec2f p3(0 * (size/382.),size2 + -100.0 * (size/382.));
                
                // Rotate the triangle points around the origin in degrees
                //rotation amount [cirres]
                float rotation = cirres*2.5;
                p1.rotate(rotation);
                p2.rotate(rotation);
                p3.rotate(rotation);
                
                // Shift the triangle to the mouse position
                p1 += mousePos  ;
                p2 += mousePos  ;
                p3 += mousePos  ;
                
                ofDrawTriangle(p1, p2, p3);}
            
            
            //random line brush
            //simple brush for creating random lines accross the screen
            //no real control
            if (brush == 4){
                    ofDrawLine(ofRandom(ofGetWidth()),
                               ofRandom(ofGetHeight()),
                               ofRandom(ofGetWidth()),
                               ofRandom(ofGetHeight()));}
            
            //starburst brush
            if (brush == 5) {
                //int numLines = 30;
                //if using mirroring the a high [size2] things can start to slow down on the RPI
                //just bring the [size2] down to create less lines at a time
                int numLines = size2/6+1;
                //int minRadius = 25;
                int minRadius = cirres/5;
                // int maxRadius = ofGetHeight()/5;
                int maxRadius = size;
                for (int i=0; i<numLines; i++) {
                    float angle = ofRandom(ofDegToRad(360.0));
                    float distance = ofRandom(minRadius, maxRadius);
                    float xOffset = cos(angle) * distance;
                    float yOffset = sin(angle) * distance;
                    float alpha = ofMap(distance, minRadius, maxRadius, brushalpha, 0);  // Make shorter lines more opaque set by [brushalpha]
                    //
                    
                    if (brushcolor == true) {
                        //full control
                        if (ColorofBrush == 1)
                        {ofSetColor(brushred,brushgreen,brushblue,brushalpha);}
                        //alpha random color control
                        if (ColorofBrush == 2)
                        {ofSetColor(brushred,brushgreen,brushblue,ofRandom(0,alpha));}
                        //color random alpha control
                        //the following two modes have their time between randomization set by [randomtime]
                        if (ColorofBrush == 3)
                        {ofSetColor(ranred,rangreen,ranblue,brushalpha);}
                        //full random
                        if (ColorofBrush == 4)
                        {ofSetColor(ranred,rangreen,ranblue,ranalpha);}}
                    
                    //if [brushcolor] is OFF set to white wi
                
                        ofDrawLine(
                                   mouseX+ midimouseX,
                                   mouseY+ midimouseY,
                                   mouseX+xOffset-midimouseX,
                                   mouseY+yOffset-midimouseY);}}
            
            //"advanced" triangle brush
            if (brush == 6)
                //lets you position all angles freely so you can conjur up many more forms
                //especially when using mirroring
            {ofDrawTriangle(trix,  size,
                            triy*1.5, mouseY,
                            mouseX, size2*.7);}
        
        ofPopStyle();
        
    }
    
    
    
}
    


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    // if(key == '`') {glReadBuffer(GL_FRONT);
    //     ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");}
    
    
    
    //Hide cursor press A || Show cursor press Z
    if (key == 'a') {ofHideCursor();}
    if (key == 'z') {ofShowCursor();}
    
    //paint mode press S || spotlight mode press Z
    if (key == 's') {erase = false;}
    if (key == 'x') {erase = true;}
    
    //Don't fill brush D || Do fill brush C
    if(key == 'd') {fill = false;}
    if(key == 'c') {fill = true;}
    
    //Auto draw off E || Auto draw on press R
    if (key == 'e') {drawing = false;}
    if (key == 'r') {drawing = true;}
    
    //brush management
    if(key == '1'){brush = 1;}
    if(key == '2'){brush = 2;}
    if(key == '3'){brush = 3;}
    if(key == '4'){brush = 4;}
    if(key == '5'){brush = 5;}
    if(key == '6'){brush = 6;}
    
    
    //Add to size F || Subtract from size V
    if(key == 'f'){size += 10;}
    if(key == 'v'){size -= 10;}
    
    
    
    //Colorize Off G || Colorize On B
    if(key == 'g'){brushcolor = false;}
    if(key == 'b'){brushcolor = true;}
    
    
    
    //color value R add Y
    if (key == 'y') {brushred += 10;}
    //color value R subtract U
    if (key == 'u') {brushred -= 10;}
    //color value G add H
    if (key == 'h') {brushgreen += 10;}
    //color value G subtract J
    if (key == 'j') {brushgreen -= 10;}
    //color value B add N
    if (key == 'n') {brushblue += 10;}
    //color value B subtract M
    if (key == 'm') {brushblue -= 10;}
    //color value A add R
    if (key == 'r') {brushalpha += 15;}
    //color value A subtract T
    if (key == 't') {brushalpha -= 15;}
    //Background color value R add I
    if (key == 'i') {bcolor1 += 10;}
    //Background color value R subtract O
    if (key == 'o') {bcolor1 -= 10;}
    //Background color value G add K
    if (key == 'k') {bcolor2 += 10;}
    //Background color value G subtract L
    if (key == 'l') {bcolor2 -= 10;}
    //Background color value B add ,
    if (key == ',') {bcolor3 += 10;}
    //Background color value B subtract .
    if (key == '.') {bcolor3 -= 10;}
    
    //reset background color to black W
    if (key == 'w'){
        bcolor1 = 0;
        bcolor2 = 0;
        bcolor3 = 0;
    }
    
    
    if (key == '0') {
        brushred = ofRandom(0, 255);
        brushgreen = ofRandom(0, 255);
        brushblue = ofRandom(0, 255);
    }
     
    
}

//--------------------------------------------------------------

void ofApp::newMidiMessage(ofxMidiMessage& message){
    
    //Below MIDI toggle/buttons
    
    //cursor on / off 64 toggle
    if (message.control == 64) {
        if (message.value == 127) {ofShowCursor();}
        if (message.value == 0) {ofHideCursor();}}
    
    
    
    //cursor fill on / off 32 toggle
    if (message.control == 32) {
        if (message.value == 127) {fill=true;}
        if (message.value == 0) {fill=false;}}
    
    
    //MirrorScale on/off
    if (message.control == 65) {
        if (message.value == 127) {mirrorScale=true;}
        if (message.value == 0) {mirrorScale=false;}
    }
    
    
    //Colorize Brush on / off 33 toggle
    if (message.control == 33) {
        if (message.value == 127) {brushcolor=true;}
        if (message.value == 0) {brushcolor=false;}}
    
    //Mirror on/off 66
    if (message.control == 66) {
        if (message.value == 127) {mirror=true;}
        if (message.value == 0) {mirror=false;}
    }
    
    
    //Background gradient on/off 34
    //if off result is standard solid color background
    if (message.control == 34) {
        if (message.value == 127) {backGrad=true;}
        if (message.value == 0) {backGrad=false;}}
    
    
    
    //background Color (from brush color) on/off 35
    if (message.control == 35) {
        if (message.value == 127) {backColor=true;}
        if (message.value == 0) {backColor=false;}}
    
    /*
     
     //
     if (message.control == 67) {
     if (message.value == 127) {backGrad=true;}
     if (message.value == 0) {backGrad=false;}}
     
     //
     if (message.control == 36) {
     if (message.value == 127) {backGrad=true;}
     if (message.value == 0) {backGrad=false;}}
     
     //
     if (message.control == 68) {
     if (message.value == 127) {backGrad=true;}
     if (message.value == 0) {backGrad=false;}}
     
     //
     if (message.control == 37) {
     if (message.value == 127) {backGrad=true;}
     if (message.value == 0) {backGrad=false;}}
     
     //
     if (message.control == 69) {
     if (message.value == 127) {backGrad=true;}
     if (message.value == 0) {backGrad=false;}}
     
     */
    
    
    
    //erase buffer if OFF / paint mode is ON  cursor/spotlight mode
    if (message.control == 70) {
        if (message.value == 127) {erase=true;}
        if (message.value == 0) {erase=false;}}
    
    //simulation mouse press in order to draw shape on screen
    if (message.control == 38) {
        if (message.value == 127) {drawing=true;}
        if (message.value == 0) {drawing=false;}}
    
    ///color inversion (brush) & randomization (brush & background)
    
    //Invert current brush color 61 CC | 9 top toggle
    if (message.control == 61) {if (message.value == 127) {
        brushred = 255 - brushred;
        brushgreen = 255 - brushgreen;
        brushblue = 255 - brushblue;}
        if (message.value == 0 ) {
            brushred = 255 - brushred;
            brushgreen = 255 - brushgreen;
            brushblue = 255 - brushblue;}}
    
    
    //random color button 60 CC | 9 bottom toggle
    if (message.control == 60)
    {if (message.value == 0) {
        brushred = ofRandom(0, 255);
        brushgreen = ofRandom(0, 255);
        brushblue = ofRandom(0, 255);
        //if the brushalpha midi input is above 120 then alpha level stays the same on randomize
        //if below 120 then alpha is also randomized same below
        if(message.control==21)
        {if(message.value < 120)
        {brushalpha = ofRandom(0, 255);}}}
        
        if (message.value == 127 ) {
            brushred = ofRandom(0, 255);
            brushgreen = ofRandom(0, 255);
            brushblue = ofRandom(0, 255);
            if(message.control==21)
            {if(message.value < 120)
            {brushalpha = ofRandom(0, 255);}}}}
    
    
    
    //random background (both if gradient is on) color button 39 CC | 8 top toggle
    if (message.control == 39)
    {if (message.value == 0) {
        bcolor1 = ofRandom(0, 255);
        bcolor2 = ofRandom(0, 255);
        bcolor3 = ofRandom(0, 255);
        bgcolor1 = ofRandom(0, 255);
        bgcolor2 = ofRandom(0, 255);
        bgcolor3 = ofRandom(0, 255);}
        
        if (message.value == 127 ) {
            bcolor1 = ofRandom(0, 255);
            bcolor2 = ofRandom(0, 255);
            bcolor3 = ofRandom(0, 255);
            bgcolor1 = ofRandom(0, 255);
            bgcolor2 = ofRandom(0, 255);
            bgcolor3 = ofRandom(0, 255);}}
    
    
    //sets the number of brushes to be mirrored
    //which also sets the number of degrees to rotate
    if(message.control==43){
        if(message.value==127){mirrorshape = 4;}
        if(message.value==0){mirrorshape = 2;}}
    
    if(message.control==44){
        if(message.value==127){mirrorshape = 16;}
        if(message.value==0){mirrorshape = 8;}}
    
    if(message.control==42){
        if(message.value==127){mirrorshape = 64;}
        if(message.value==0){mirrorshape = 36;}}
    //
    
    if(message.control==41){
        if(message.value==127){ColorofBrush = 1;}
        if(message.value==0){ColorofBrush = 2;}}
    
    if(message.control==45){
        if(message.value==127){ColorofBrush = 3;}
        if(message.value==0){ColorofBrush = 4;}}
    
    
       if(message.control==46){
           if(message.value==127){brushpreview = true;}
           if(message.value==0){brushpreview = false;}}
    
    /*
     Colorbrush 1
     softpaint 2
     Colorrandom 3
     fullrandom 4
     */
    
    ////below MIDI CCs
    
    //MIDI brush changer 16 CC
    if (message.control==16){brush=message.value/127.0*5+1;}
    
    
    
    
    ///
    
    //MIDI Size 17 CC
    if (message.control==17) {size=(message.value/127.00*ofGetWidth())+1;}
    
    //MIDI size2 121 CC
    if (message.control==121) {size2=(message.value/127.0*ofGetHeight())+1;}
    
   // if (message.control==17) {size=(message.value/127.00*480.)+1;}
    
    
   // if (message.control==121) {size2=(message.value/127.0*720)+1;}
    
    
    ///
    
    //MIDI brush colorize Red 18 CC
    if (message.control==18)
    {if (backColor == true)
    {bgcolor1 = message.value*2;} else
    {brushred=(message.value*2);}}
    
    //MIDI brush colorize Green 19 CC
    if (message.control==19)
    {if (backColor == true)
    {bgcolor2 = message.value*2;} else
    {brushgreen=(message.value*2);}}
    
    //MIDI brush colorize Blue 20 CC
    if (message.control==20)
    {if (backColor == true)
    {bgcolor3 = message.value*2;} else
    {brushblue=(message.value*2);}}
    
    //MIDI brush colorize Alpha 21 CC
    if (message.control==21)
    {if (backColor == true)
    {bgcolor4 = message.value*2;} else
    {brushalpha=(message.value*2);}}
    
    ///
    
    //MIDI background colorize Red 2 CC | 3
    if (message.control==122) {bcolor1=(message.value*2);}
    
    //MIDI background colorize Green 3 CC | 4
    if (message.control==123) {bcolor2=(message.value*2);}
    
    //MIDI background colorize Blue 4 CC | 5
    if (message.control==124) {bcolor3=(message.value*2);}
    
    ///
    
    //MIDI translate X 125 CC| 6
    //if (message.control==125) {transx=(message.value/127.0*760.0-380.0);}
    if (message.control==125) {transx=(message.value/127.0*-640.0);}
    
    //MIDI translate y 126 CC| 7
    //if (message.control==126) {transy=(message.value/127.0*520.0-260.0);}
    if (message.control==126) {transy=(message.value/127.0*-480.0);}
    
    //MIDI Time between color randomization 127 CC| 8
     if (message.control==127){randomtime = message.value*6.5+1;}
    // if (message.control==127){transz=(message.value*3.25);}
    
    
    ///
    
    //MIDI triangle X axis movement | if mirror scaling is on it controls scale amount  120 CC| 1
    if (message.control==120)
    {if (mirrorScale == true)
    {scaleamount = message.value*5.6;} else
    {trix=(message.value*5.6);}}
    
    
    //MIDI triy 119 CC| 9
    if (message.control==119) {triy=(message.value*3.75);}
    
    //MIDI Circle Resolution 62 CC| 9
    if (message.control==62) {cirres=(message.value/127.0*150.0);}
    
    ///
    
    //MIDI mouse X 22 CC| channel 7 on controller
    if (message.control==22) {midimouseX=(message.value/127.0*760.0-380.0);}
    
    //MIDI mouse y 23 CC| channel 8 on controller
    if (message.control==23) {midimouseY=(message.value/127.0*520.0-260.0);}
    
    
    
    
    
    //in order to see in the console what MIDI messages are coming through
    cout << message.control << endl;
    cout << message.value << endl;
    
}





//add image as brush?




//video style oscillator
//gradients/rectangles used and repeated
//sizing vertically to allow oscillator to become repeating square shape gen



//--------------------------------------------------------------
