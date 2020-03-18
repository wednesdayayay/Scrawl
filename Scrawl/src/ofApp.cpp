#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofEnableAntiAliasing();
    ofEnableAlphaBlending();
    ofToggleFullscreen();
    
    ///MIDI setup
    midiIn.listInPorts();  // print input ports to console
    //if MIDI isn't working check your device number in the console when you first make it change the (0) to whatever your MIDI controller is
    //midiIn.openPort(0);//computer
    midiIn.openPort(1);//Raspberry pi
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true); // print received messages to the console
    ///
    
    //int width = 640;
    int height = 480;
    
    
    
    ///webcam/USB input setup
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.setup(640, 480);
    ///
    
    
    ofBackground(0);
    
    
    //allows for four quadrants to paint to navigated by translate X&Y
    //fbo.allocate(ofGetWidth()*2, ofGetHeight()*2 );
    
    
    ///FBO setup
    fbo.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA);
    paint.allocate(ofGetWidth(), ofGetHeight(),GL_RGB);
    
    paint.begin();
    ofClear(255);
    paint.end();
    
    fbo.begin();
    ofClear(0);
    fbo.end();
    ///
    
    ///Mirror multicolor setup
    colorR.resize(AMOUNT);
    colorG.resize(AMOUNT);
    colorB.resize(AMOUNT);
    colorA.resize(AMOUNT);
    
    for (int i=0;i<AMOUNT;i++){
        colorR[i] = ofRandom(0,255);
        colorG[i] = ofRandom(0,255);
        colorB[i] = ofRandom(0,255);
        colorA[i] = ofRandom(0,255); }
    ///
    
    
    
    xPos = 1;
    yPos = 1;
    
    xSpeed = 1;
    ySpeed = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidGrabber.update();//update cam
    
    
    ///Video painting setup || gets texture from video input and masks with current drawing
    if(videopainting == true){vidGrabber.getTexture().setAlphaMask(fbo.getTexture());}
    
    
    ///Clears video painting has to be here
    if(ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)){
        paint.begin(); ofClear(0); paint.end();}
    
    
    ///Randomness setup for scrolling
    if (randomdraw == true){
    if (ofGetFrameNum() % randomtime == 0){
		{xnoise = ofRandom(randomamount);}
		{ynoise = ofRandom(randomamount);}}}

    //randomness setup for size
    if (randomsize == true){
    if (ofGetFrameNum() % randomtime == 0){
    {size = ofRandom((randomamount+1.)*5.);}
    {size2 = ofRandom((randomamount+1.)*5.);}}}
    //else ynoise = 0;}//else xnoise = 0;
		
    
    ///mirroring setup for positioning on screen
    if ((mirror == true)
        or (mirrorScale == true)) {
        screenX  = 640/2;
        screenY = height/2;}
    
    if ((mirror == false) &&
        (mirrorScale==false)) {
        screenX = 0;
        screenY = 0;}
    ///
    
    
    ///keyboard to scroll k for X[left to right]
    if(ofGetKeyPressed('k') or (Xlr == true)) {
        xPos += xSpeed + xnoise;
        if(width<xPos){
            xPos = 0;}}
    
    
     ///keyboard to scroll i for X[right to left]
    if(ofGetKeyPressed('i') or (Xrl == true)){
        xPos -= xSpeed + xnoise;
        if(0>xPos){
            xPos = width;}}
    
    
    ///keyboard to scroll j for Y[top to bottom]
    if(ofGetKeyPressed('j') or (Ytb == true)){
        yPos += ySpeed + ynoise;
        if(height<yPos){
            yPos = 0;}}
    
    //keyboard to scroll u for Y[bottom to top]
    if(ofGetKeyPressed('u') or (Ybt == true)){
        yPos -= ySpeed + ynoise;
        if(0>yPos){
            yPos = height;}}
    
    
 
    
    ///pointer variable for ease of reading
    pointerX =(mouseX - screenX - midimouseX + xPos) / 720. * 640. ;
    pointerY = mouseY - screenY - midimouseY + yPos;
    
    
    /*///this will allow the result of pointer to wrap around the screen
     if ((mirror == false) &&
     (mirrorScale == false)){
    if(640<pointerX) {pointerX = pointerX-640;} 
    if(0>pointerX)     {pointerX = 640+pointerX;}
    if(height<pointerY){pointerY = pointerY-height;} 
     if(0>pointerY)     {pointerY = height+pointerY;}}
    */
        
    
    //wrap around for colorof brush [0-4]
    if(ColorofBrush == 5){ColorofBrush = 1;}
    if(ColorofBrush == 0){ColorofBrush = 4;}
    
    
    //wrap around for brush (keyboard) [0-6]
    if(brush == 7){brush = 1;}
    if(brush == 0){brush = 6;}
    
    //wrap around for mirrorshape [0-11]
    if(mirrorshape == 12){mirrorshape = 1;}
    if(mirrorshape == 0){mirrorshape = 11;}
    
    
    //sequencing mirrorshape/mirrornumber [0-11]
    switch (mirrorshape) {
        case 1 : mirrorshape = 1; mirrornumber = 2;  break;
        case 2 : mirrorshape = 2; mirrornumber = 3;  break;
        case 3 : mirrorshape = 3; mirrornumber = 4;  break;
        case 4 : mirrorshape = 4; mirrornumber = 5;  break;
        case 5 : mirrorshape = 5; mirrornumber = 6;  break;
        case 6 : mirrorshape = 6; mirrornumber = 7;  break;
        case 7 : mirrorshape = 7; mirrornumber = 8;  break;
        case 8 : mirrorshape = 8; mirrornumber = 9;  break;
        case 9 : mirrorshape = 9; mirrornumber = 16; break;
        case 10: mirrorshape =10; mirrornumber = 32; break;
        case 11: mirrorshape =11; mirrornumber = 64; break;
        default: mirrornumber = 3; break;
    }
    
    
    


}

//--------------------------------------------------------------
void ofApp::draw(){


    
    
    
    //ofVec2f mousePos(mouseX+midimouseX - screenX, mouseY+midimouseY - screenY);
    ofVec2f mousePos(mouseX - screenX - midimouseX + xPos, mouseY - screenY - midimouseY + yPos);
  
    
    
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
        or (ofGetKeyPressed('q')
        or (ofGetKeyPressed('w')))){
        
            fbo.begin();
            ofClear(0,0);
        
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
    
    //taken out for scaling
    //ofTranslate(transx, transy, 0);
    //ofTranslate(transx, transy, transz);
    
    
    
    
    fbo.begin();
    
    ////turn me off when not painting with video
    ////if off while video on whole video shows through instead
    if(videopainting == true){ofClear(0,0);}
    
    
    
    //
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
        
                //ofScale(transx, transx, 5);
        
        
                //start mirroring (should be after inital translate)
                ofPushMatrix();

                //logic to set correct translation for both mirroring and regular brush
                //when mirroring / scaling I want to be drawing from center of screen
                ofTranslate(screenX, screenY);
                
        
                    //mirroring substance
                    //i = number of brushes to be drawn
                    //[mirrorshape] set by 3 MIDI buttons to select between
                    //2,4,8,16,32,64
                    for (int i=0; i<mirrornumber; i++) {
                        
                        //if mirroring or scaling then set color to vector value randomized in the setup
                        //this allows each shape to have its own color value then is added with the knobs and wrapped around the maximum color value
                        //the colorization set by [colorofbrush] in the same way as before is added to the vector values per shape
                        //however if [brushcolor] is OFF then color is set by previous color settings which means you can swap between
                        //having all shapes different colors and all the same with randomizations
                        if(brushcolor == false){
                        if ((mirror == true) or
                            (mirrorScale == true)){{{{
                             if (ColorofBrush == 1){ofSetColor(
                                                        (colorR[i] + brushred) % 255,
                                                        (colorG[i] + brushgreen) % 255,
                                                        (colorB[i] + brushblue) % 255,
                                                        brushalpha);}}
                            
                            if (ColorofBrush == 2){ofSetColor(
                                                        (brushred) % 255,
                                                        (brushgreen) % 255,
                                                        (brushblue) % 255,
                                                        (colorA[i] + ranalpha) % 255);}}
                            
                            if (ColorofBrush == 3){ofSetColor(
                                                        (colorR[i] + ranred + brushred) % 255,
                                                        (colorG[i] + rangreen + brushgreen) % 255,
                                                        (colorB[i] + ranblue + brushblue) % 255,
                                                        brushalpha);}}
                        
                            if (ColorofBrush == 4){ofSetColor(
                                                        (colorR[i] + ranred) % 255,
                                                        (colorG[i] + rangreen) % 255,
                                                        (colorB[i] + ranblue) % 255,
                                                        (colorA[i] + ranalpha) % 255);}}}
                           
                        
                        
                        
                        
                        //allows for combining effect [mirror] and [mirrorScale]
                        //[mirrorScale] will scale the brush a specified amount for each time drawn [i]
                        //[mirror] will rotate a certain number of degrees each time [i] is drawn
                        if (mirrorScale == true){ofScale(scaleamount/711.0*1.25-1.25);}
                        if (mirror == true){ofRotateDeg(360.0/mirrornumber);}
                        
                        
                        
                        //Circle brush
                        if (brush == 1) {
                            //set circle resolution very high and you won't notice this behavior and you get a nice clean circle
                            //set it fairly low and you will start to see some noise introduced
                            //great for drawing more bold/chaotic lines with nofill OFF and paint ON
                            ofSetCircleResolution(cirres-ofRandom(0,10));
                            //if you don't want this one just comment out/delete above line & uncomment below
                            //ofSetCircleResolution(cirres);
                            ofDrawCircle (pointerX, pointerY, size/4.);}
                            
                     
                        
                        //Rectangle brush
                        if (brush == 2) {
                            ofSetRectMode(OF_RECTMODE_CENTER);
                            //pretty much same as above except the added [size2] which allows for rectangle shaping
                            
                                ofDrawRectangle(pointerX, pointerY,
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
                            int minRadius = cirres/5.;
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
                                               mouseX - ofGetHeight()/2- midimouseX + xPos,
                                               mouseY - ofGetWidth()/2 - midimouseY + yPos,
                                               mouseX+xOffset - ofGetHeight()/2 - midimouseX + xPos,
                                               mouseY+yOffset- ofGetWidth()/2 - midimouseY + yPos);}
                                
                                if ((mirror == false) &&
                                    (mirrorScale==false)){
                                    ofDrawLine(
                                               mouseX - midimouseX + xPos,
                                               mouseY - midimouseY + yPos,
                                               mouseX+xOffset-midimouseX + xPos,
                                               mouseY+yOffset-midimouseY + yPos);}}}
                        
                        //"advanced" triangle brush
                        if (brush == 6)
                            //lets you position all angles freely so you can conjur up many more forms
                            //especially when using mirroring
                            {ofDrawTriangle(trix - xPos,  size - yPos,
                                            triy*1.5 + yPos, mouseY - xPos,
                                            mouseX + xPos, size2*.7 + yPos);}
                        
                        
                        /*
                        if(brush == 7)
                        {
                            ofDrawRectangle(xPos, mouseY, xSpeed/(size /200. +1), ofGetHeight()-size2*2.75 );
                            //ofDrawRectangle(mouseX, mouseY, xPos, yPos);
                        }
                         */
                        
                        
                        //
                        
                        //if(ofGetKeyPressed('k') or (ofGetKeyPressed('i'))) {ofDrawRectangle(xPos, 0, xSpeed, ofGetHeight());}
                        
                        
                        
                        //ofDrawRectangle(0, yPos, ofGetWidth(), ySpeed/2);
                        
                        //if(ofGetKeyPressed('j') or (ofGetKeyPressed('u'))){ofDrawRectangle(0, yPos, ofGetWidth(), ySpeed);}
                        //ofDrawRectangle(0, yPos, ofGetWidth(), ySpeed);
                        
                        
                        
                        //ofDrawRectangle(mouseX, mouseY, xPos, yPos);
                        
                        
                        //ofDrawRectangle(ofGetMouseX()/2.3, ofGetMouseY() /2, xPos, yPos);
                        
                        }
                        ofPopStyle();
                        ofPopMatrix();
                    }
    
    fbo.end();
    
  
    if(videopainting == false){fbo.draw(0,0,ofGetWidth(),ofGetHeight());}
  
    
    paint.begin();
    if(videopainting == true & erase == false){vidGrabber.draw(0, 0);}
    else {ofClear(0,0);}
    paint.end();
    
    
    if(videopainting == true & erase == true){vidGrabber.draw(0, 0,ofGetWidth(),ofGetHeight());}
    
    
    if(videopainting == true & erase == false){paint.draw(0,0,ofGetWidth(),ofGetHeight());}
    

    
    
    ///taking out brush preview for now maybe bring back later
    ////
    //[brushpreview] controls ability to show brush and not paint it to FBO
    if(brushpreview == true)
    {
        
    //try to add back in mirroring?
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
            if (brush == 1) {ofDrawCircle (pointerX, pointerY, size/4.);}
            
            //Rectangle brush
            if (brush == 2) {
                ofSetRectMode(OF_RECTMODE_CENTER);
                //pretty much same as above except the added [size2] which allows for rectangle shaping
                ofDrawRectangle(pointerX, pointerY,size*2, size2);}
     
            //Triangle brush
            if (brush == 3){
                
                //ofTranslate(mouseX,mouseY);
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

    
    if(key == '1' || key == 'F'){ofToggleFullscreen();}
    
    
    if(key == '2') {Xlr = !Xlr; if(Xrl == true) {Xrl = !Xrl;}}
    if(key == '3') {Xrl = !Xrl; if(Xlr == true) {Xlr = !Xlr;}}
    if(key == '4') {Ytb = !Ytb; if(Ybt == true) {Ybt = !Ybt;}}
    if(key == '5') {Ybt = !Ybt; if(Ytb == true) {Ytb = !Ytb;}}
    
    
    if(key == '6') {videopainting = !videopainting;}
    
    
    
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
    if(key == '8'){brush += 1;}
    if(key == '7'){brush -= 1;}
    
    
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
        bcolor3 = 0;}
    
    
    if (key == '0') {
        brushred = ofRandom(0, 255);
        brushgreen = ofRandom(0, 255);
        brushblue = ofRandom(0, 255);}
     
     
    
    
}

//--------------------------------------------------------------

void ofApp::newMidiMessage(ofxMidiMessage& message){
    
    
    
    ///toggles///
    /////////////
    ///Top row///
    /////////////
    
    //cursor on/off 64 | 1
    if (message.control == 64) {
        if (message.value == 127) {ofShowCursor();}
        if (message.value == 0) {ofHideCursor();}}
    
    //erase buffer if OFF / paint mode is ON  cursor/spotlight mode
    if (message.control == 65) {
        if (message.value == 127) {erase=true;}
        if (message.value == 0) {erase=false;}}
    
    //MirrorScale on/off 66
    if (message.control == 66) {
        if (message.value == 127) {mirrorScale=true;}
        if (message.value == 0) {mirrorScale=false;}}

    //Background gradient on/off 67
    //if off result is standard solid color background
    if (message.control == 67) {
        if (message.value == 127) {backGrad=true;}
        if (message.value == 0) {backGrad=false;}}
    
    
    //background Color (from brush color) on/off 8
    if (message.control == 68) {
        if (message.value == 127) {backColor=true;}
        if (message.value == 0) {backColor=false;}}
    
    //random background (both if gradient is on) color button 39 CC | 8 top toggle
    if (message.control == 69)
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
    
    //Ybt 70
    if (message.control == 70) {
        if (message.value == 127) {Ybt = !Ybt; if(Ytb == true) {Ytb = !Ytb;}}
        if (message.value == 0) {Ybt = !Ybt; if(Ytb == true) {Ytb = !Ytb;}}}
    
    //Xlr on/off 39
    if (message.control == 39) {
        if (message.value == 127) {Xlr = !Xlr; if(Xrl == true) {Xrl = !Xrl;}}
        if (message.value == 0) {Xlr = !Xlr; if(Xrl == true) {Xrl = !Xrl;}}}
    
    ///random draw 61
    if(message.control==61){
        if(message.value==127){randomdraw = true;}
        if(message.value==0){randomdraw = false;}}
    
    
    ///Toggles///////
    /////////////////
    ////bottom row///
    /////////////////
    
    
    //cursor fill on / off 32 toggle
    if (message.control == 32) {
        if (message.value == 127) {fill=true;}
        if (message.value == 0) {fill=false;}}

    //simulation mouse press in order to draw shape on screen 33
    if (message.control == 33) {
        if (message.value == 127) {drawing=true;}
        if (message.value == 0) {drawing=false;}}
    
    //Mirror on/off 34
    if (message.control == 34) {
        if (message.value == 127) {mirror=true;}
        if (message.value == 0) {mirror=false;}}
    
    //Colorize Brush on / off 35 toggle
    if (message.control == 35) {
        if (message.value == 127) {brushcolor=true;}
        if (message.value == 0) {brushcolor=false;}}
    
    //random color button 36 CC | 9 bottom toggle
    if (message.control == 36)
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
    
    
    ///color inversion (brush) & randomization (brush & background)
    //Invert current brush color 37 CC | 9 top toggle
    if (message.control == 37) {if (message.value == 127) {
        brushred = 255 - brushred;
        brushgreen = 255 - brushgreen;
        brushblue = 255 - brushblue;}
        if (message.value == 0 ) {
            brushred = 255 - brushred;
            brushgreen = 255 - brushgreen;
            brushblue = 255 - brushblue;}}

    
    //Ytb on/off 38
    if (message.control == 38) {
        if (message.value == 127) {Ytb = !Ytb; if(Ybt == true) {Ybt = !Ybt;}}
        if (message.value == 0) {Ytb = !Ytb; if(Ybt == true) {Ybt = !Ybt;}}}
    
    
    //Xrl on/off 55
    if (message.control == 55) {
        if (message.value == 127) {Xrl = !Xrl; if(Xlr == true) {Xlr = !Xlr;}}
        if (message.value == 0) {Xrl = !Xrl; if(Xlr == true) {Xlr = !Xlr;}}}
    
    //Random Size on/off 60 | 9
    if (message.control == 60
        
        ) {
        if (message.value == 127) {randomsize = true;}
        if (message.value == 0) {randomsize = false;}}
    
  
   
    ///////////////////////
    ///transport buttons///
    ///////////////////////
    
    ///top row
    ///mirrorshape + 43
    if(message.control==43){
        if(message.value==127){mirrorshape += 1;}
        if(message.value==0){mirrorshape += 1;}}
    
    ///mirrorshape - 44
    if(message.control==44){
        if(message.value==127){mirrorshape -= 1;}
        if(message.value==0){mirrorshape -= 1;}}
    
    ///video painting on/off 42
    if(message.control==42){
        if(message.value==127){videopainting = true;}
        if(message.value==0){videopainting = false;}}
    
    ///
    
    ///bottom row
    ///color of brush + 41
    if(message.control==41){
        if(message.value==127){ColorofBrush += 1;}
        if(message.value==0){ColorofBrush += 1;}}
    
    ///color of brush - 45
    if(message.control==45){
        if(message.value==127){ColorofBrush -= 1;}
        if(message.value==0){ColorofBrush -= 1;}}
    
    /*
     when you are randomizing a value the knob will work as a maximum value for the randomization
     Colorbrush 1 full RGBA knob control
     softpaint 2 RGB knob control random A
     Colorrandom 3 RGB random A knob control
     fullrandom 4 RGBA random
     */
    
    ///brush preview on/off 46
    if(message.control==46){
        if(message.value==127){brushpreview = true;}
        if(message.value==0){brushpreview = false;}}
    
   ///
    
    
    ////MIDI CCs///////
    ///////////////////
    ///Top row knobs///
    ///////////////////
    
    ///MIDI brush changer 16 CC
    if (message.control==16){brush=message.value/127.0*6+1;}
    
    ///MIDI Size 17 CC
    if (message.control==17) {size=(message.value/127.00*ofGetWidth())+1;}
    
    //MIDI triangle X axis movement | if mirror scaling is on it controls scale amount  18 CC| 1
    if (message.control==18)
    {trix=(message.value*5.6);}
    
    ///MIDI mouse X 19 CC| channel 7 on controller
    if (message.control==19) {midimouseX=(message.value/127.0*760.0-380.0);}
    
    ///MIDI brush colorize Red 20 CC
    if (message.control==20)
    {if (backColor == true)
    {bgcolor1 = message.value*2;} else
    {brushred=(message.value*2);}}
    
    ///MIDI brush colorize Green 21 CC
    if (message.control==21)
    {if (backColor == true)
    {bgcolor2 = message.value*2;} else
    {brushgreen=(message.value*2);}}
    
    ///MIDI brush colorize Blue 22 CC
    if (message.control==22)
    {if (backColor == true)
    {bgcolor3 = message.value*2;} else
    {brushblue=(message.value*2);}}
    
    ///MIDI brush colorize Alpha 23 CC
    if (message.control==23)
    {if (backColor == true)
    {bgcolor4 = message.value*2;} else
    {brushalpha=(message.value*2);}}
    
    //MIDI Time between color/size/position/speed of scroll randomization 62 CC| 8
    if (message.control==62){randomtime = (message.value+1)*6.5;}
    
    
    /////////////
    ///Sliders///
    /////////////
    
    ///scale amount 120
     if (message.control==120)
    {scaleamount = message.value*5.6;}
    
    //MIDI size2 121 CC
    if (message.control==121)
    {if(brush == 7)
    {size2=(message.value-63.0)/63.00 *320.0;} else
    {size2=(message.value/127.0*ofGetHeight())+1;}}
    
    //MIDI triy 122 CC| 9
    if (message.control==122) {triy=(message.value*3.75);}
    
    ///MIDI mouse y 123 CC| channel 8 on controller
    if (message.control==123) {midimouseY=(message.value/127.0*520.0-260.0);}
    
    //MIDI background colorize Red 124 CC | 3
    if (message.control==124) {bcolor1=(message.value*2);}
    
    //MIDI background colorize Green 125 CC | 4
    if (message.control==125) {bcolor2=(message.value*2);}
    
    //MIDI background colorize Blue 126 CC | 5
    if (message.control==126) {bcolor3=(message.value*2);}
    
    ///circle resolution 127
    if (message.control==127) //{cirres=(message.value/127.0*150.0);}
    {cirres=(message.value/127.0*200.0);}
    
    ///random amount 119
    if (message.control==119)
    {randomamount = message.value/127.0 * 80.0;}
    
    
    ///
    
    
    ///not using Translate X&Y
    /*
     //translate X 125 CC | 6
     if (message.control==125) {transx=(message.value/127.0*640.0);}
     
     //translate y 126 CC | 7
     if (message.control==126) {transy=(message.value/127.0*-480.0);}
     */
    
    
    
    //in order to see in the console what MIDI messages are coming through
    cout << message.control << endl;
    cout << message.value << endl;
    
}





//add image as brush?

//depth testing enable/disable for layers?




//--------------------------------------------------------------
