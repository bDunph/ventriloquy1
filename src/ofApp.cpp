#include "ofApp.h"
#include <random>

//--------------------------------------------------------------
void ofApp::setup(){
    
    //********** Gui Global Params ***********//
    camGui.setup();
    camGui.setPosition(0, ofGetWindowHeight() * .1);
    camGui.add(camX.setup("camX", 0.0f, -1.0f, 1.0f));
    camGui.add(camY.setup("camY", 0.0f, -1.0f, 1.0f));
    camGui.add(camZ.setup("camZ", 0.0f, -1.0f, 1.0f));
    
    lightGui.setup();
    lightGui.setPosition(0, ofGetWindowHeight() * .3);
    lightGui.add(lightColR.setup("lightColR", 1.f, 0.f, 1.f));
    lightGui.add(lightColG.setup("lightColG", 1.f, 0.f, 1.f));
    lightGui.add(lightColB.setup("lightColB", 1.f, 0.f, 1.f));
    lightGui.add(ambColR.setup("ambColR", 0.1f, 0.f, 1.f));
    lightGui.add(ambColG.setup("ambColG", 0.1f, 0.f, 1.f));
    lightGui.add(ambColB.setup("ambColB", 0.1f, 0.f, 1.f));
    lightGui.add(specColR.setup("specColR", 0.1f, 0.f, 1.f));
    lightGui.add(specColG.setup("specColG", 0.1f, 0.f, 1.f));
    lightGui.add(specColB.setup("specColB", 0.1f, 0.f, 1.f));
    lightGui.add(lightPow.setup("lightPow", 397000.f, 100000.f, 10000000.f));
    lightGui.add(lightPosX.setup("lightPosX", 0.f, -1000.f, 1000.f));
    lightGui.add(lightPosY.setup("lightPosY", 0.f, -1000.f, 1000.f));
    lightGui.add(lightPosZ.setup("lightPosZ", -780.f, -1000.f, 1000.f));
    lightGui.add(blurAmnt.setup("blurAmnt", .001f, 0.f, .01f));
    
    volGui.setup();
    volGui.setPosition(0, ofGetWindowHeight() * .5);
    volGui.add(masterVol.setup("masterVol", 0.5, 0.0, 1.0));
    
    //********************Maxim Setup**********************//
    
    sampleRate 	= 48000; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    int current = 0;
    ofSoundStreamListDevices();
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2, 2, this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
    //******* Rapidmix Setup (code from oF example rapidAPI_006) ***************//
#if PREPMODE
    trained = false;
    recording = false;
    loaded = false;
#endif
    
    drawGui = true;
    
    //****************** FBO and Blur Shader setup ****************//
    ofDisableArbTex();
    
    ofFbo::Settings settings;
    settings.width = ofGetWindowWidth();
    settings.height = ofGetWindowHeight();
    settings.useDepth = true;
    settings.internalformat = GL_RGBA;
    settings.maxFilter = GL_LINEAR, GL_NEAREST;
    settings.numSamples = 4;
    settings.numColorbuffers = 4;
    settings.useStencil = false;
    
    ofFbo::Settings settings2;
    settings2.width = ofGetWindowWidth();
    settings2.height = ofGetWindowHeight();
    settings2.useDepth = true;
    settings2.internalformat = GL_RGBA;
    settings2.maxFilter = GL_LINEAR, GL_NEAREST;
    settings2.numSamples = 4;
    settings2.numColorbuffers = 4;
    settings2.useStencil = false;
    
    fbo1.allocate(settings);
    fbo1.begin();
    ofClear(0, 0, 0);
    fbo1.end();
    
    fbo2.allocate(settings2);
    fbo2.begin();
    ofClear(0, 0, 0);
    fbo2.end();
    blurX.load("shaders/blurX");
    blurY.load("shaders/blurY");
    
#if PREPMODE
    avPrep.avSetup();
#endif
    
#if PERFORMANCEMODE
    for(int i = 0; i < NUMAVS; i++){
        av[i].avSetup();
        av[i].gui.loadFromFile("data/secondDraft_composition_180320/section"+ofToString(i)+"/reg"+ofToString(i)+"_obj0_mainGui.xml");
        av[i].guiRW.loadFromFile("data/secondDraft_composition_180320/section"+ofToString(i)+"/reg"+ofToString(i)+"_obj0_guiRW.xml");
        //av[i].reg.readJSON("data/secondDraft_composition_180320/trainedModels/2ndDraftReg"+ofToString(i)+".JSON");
    }
#endif
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    //*********** Maxim *****************//
    ofSoundStreamStop();
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    fbo1.begin();
    ofClear(0, 0, 0);
    fbo1.end();

    fbo2.begin();
    ofClear(0, 0, 0);
    fbo2.end();
    
    //**** PSMOVE ****//
    tracker.update();
    
    camX = ofMap(tracker.moveXPos, -5.0, 5.0, -1.0, 1.0);
    camY = ofMap(tracker.moveYPos, -4.0, 4.0, -1.0, 1.0);
    camZ = ofMap(tracker.moveZPos, -1.0, -40.0, -1.0, 1.0);
    blurAmnt = ofMap(tracker.wOrientation, -1.0, 1.0, 0.0, 0.01);
    
#if PREPMODE
    if(tracker.rand){
        avPrep.randomParams();
    }

    //*** training ***//
    if(tracker.train){
        trained = avPrep.trainModel();
    }
    
    //*** recording ***//
    if (tracker.record) {

        recording = true;
        avPrep.trainingExamples(tracker.moveXPos, tracker.moveYPos, tracker.moveZPos);
    } else if (!tracker.record){
        recording = false;
    }
    
    //**** trained ****//
        if (trained || loaded) {
    
            avPrep.trainedOutput(tracker.moveXPos, tracker.moveYPos, tracker.moveZPos);
        }
#endif
    
    if(tracker.drawInterface){
        drawGui = !drawGui;
    }
    unsigned int triggerVal = tracker.trig;
    
    float xPos = ofGetWindowWidth() * camX;
    float yPos = ofGetWindowHeight() * camY;
    float zPos = ofGetWindowHeight() * camZ;
    
    ofVec3f lookAtPos;
    camPos = ofVec3f(xPos, yPos, zPos);
    lookAtPos = ofVec3f(0, 0, 0);
    cam.setPosition(camPos);
    cam.lookAt(lookAtPos, ofVec3f(0, 1, 0));
    cam.setFov(90);
    cam.setNearClip(1);
    cam.setFarClip(5000);
    cameraSpace = cam.getModelViewMatrix();
    
    lightCol = ofVec3f(lightColR, lightColG, lightColB);
    ambCol = ofVec3f(ambColR, ambColG, ambColB);
    specCol = ofVec3f(specColR, specColG, specColB);
    lightPos = ofVec3f(lightPosX, lightPosY, lightPosZ);

#if PREPMODE
    avPrep.visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
        loaded = avPrep.readWrite();
#endif
    
#if PERFORMANCEMODE
    for(int i = 0; i < NUMAVS; i++){
        
        if(tracker.obj[0]){
            av[0].texColR = 63;
            av[0].texColG = 17;
            av[0].texColB = 0;
            av[0].shape = 1;
            av[0].waveform = 0;
            av[0].trainedOutput(tracker.moveXPos, tracker.moveYPos, tracker.moveZPos);
            av[0].visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
        }
        
        if(tracker.obj[1]){
            av[1].texColR = 47;
            av[1].texColG = 48;
            av[1].texColB = 47;
            av[1].shape = 0;
            av[0].waveform = 1;
            av[1].trainedOutput(tracker.moveXPos, tracker.moveYPos, tracker.moveZPos);
            av[1].visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
        }
        
        if(tracker.obj[2]){
            av[2].texColR = 63;
            av[2].texColG = 17;
            av[2].texColB = 0;
            av[2].shape = 0;
            av[2].waveform = 2;
            av[2].trainedOutput(tracker.moveXPos, tracker.moveYPos, tracker.moveZPos);
            av[2].visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
        }
    }
#endif
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    
    fbo1.begin();
    cam.begin();
    
    //***** Draw Objects *****//
#if PREPMODE
        avPrep.drawVisual(lightCol, ambCol, specCol, lightPow);
#endif
    
#if PERFORMANCEMODE
    for(int i = 0; i < NUMAVS; i++){
        if(tracker.obj[i]){
            av[i].drawVisual(lightCol, ambCol, specCol, lightPow);
        }
    }
#endif
    
    cam.end();
    fbo1.end();
    
    fbo1.getTexture().bind();
    fbo2.begin();
        blurX.begin();
        blurX.setUniform1f("blurAmnt", blurAmnt);
    fbo1.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        blurX.end();
    fbo2.end();
    fbo1.getTexture().unbind();
    
        fbo2.getTexture().bind();
        blurY.begin();
        blurY.setUniform1f("blurAmnt", blurAmnt);
    fbo2.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        blurY.end();
        fbo2.getTexture().unbind();
    
    //************ Gui ***********//
    
    if(drawGui){

        stringstream s;
        
#if PREPMODE
        s << "trained: " << trained;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.1, 10);
        s.str("");
        s << "recording: " << recording;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.3, 10);
        s.str("");
#endif
        
        s << "xPos: " << tracker.moveXPos;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.5, 10);
        s.str("");
        s << "yPos: " << tracker.moveYPos;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.5, 20);
        s.str("");
        s << "zPos: " << tracker.moveZPos;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.5, 30);
        s.str("");
        s << "xOr: " << tracker.xOrientation;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.6, 10);
        s.str("");
        s << "yOr: " << tracker.yOrientation;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.6, 20);
        s.str("");
        s << "zOr: " << tracker.zOrientation;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.6, 30);
        s.str("");
        s << "wOr: " << tracker.wOrientation;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.7, 10);
        s.str("");
        
#if PREPMODE
        avPrep.drawGuiAndGuiRW();
#endif
        
#if PERFORMANCEMODE
        for(int i = 0; i < NUMAVS; i++){
            if(tracker.obj[i]){
                av[i].drawGuiAndGuiRW();
            }
        }
#endif
        
        volGui.draw();
        camGui.draw();
        lightGui.draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
#if PREPMODE
        synthOutPrep = avPrep.audio(blurAmnt);
        prepChannel = *(synthOutPrep);
        prepPanPtr = avPrep.panner();
        prepPanVal = *(prepPanPtr);
        prepMix.stereo(prepChannel, prepChannelOut, prepPanVal);
        
        finalSig[0] += prepChannelOut[0];
        finalSig[1] += prepChannelOut[1];
#endif
        
#if PERFORMANCEMODE
        for(int j = 0; j < NUMAVS; j++){
            if(tracker.obj[j]){
                synthOut[j] = av[j].audio(blurAmnt);
                channel[j] = *(synthOut[j]);
                panning[j] = av[j].panner();
                panner[j] = *(panning[j]);
                channelMix[j].stereo(channel[j], channelOut[j], panner[j]);
            }
        }
        
        for(int j = 0; j < NUMAVS; j++){
            finalSig[0] += channelOut[j][0];
            finalSig[1] += channelOut[j][1];
        }
        
        if(tracker.obj[3]){
            float volDown = ofMap(tracker.wOrientation, -1.0, 1.0, 0.0, 1.0);
            masterVol = volDown;
        }
#endif
        
        
        //*** Limiter ***/
        
        if (finalSig[0] > 0.95) {
            finalSig[0] = 0.95;
        } else if (finalSig[0] < -0.95){
            finalSig[0] = -0.95;
        } else if (finalSig[1] > 0.95){
            finalSig[1] = 0.95;
        } else if(finalSig[1] < -0.95){
            finalSig[1] = -0.95;
        }
        
    output[i*nChannels    ] = finalSig[0] * masterVol;
    output[i*nChannels + 1] = finalSig[1] * masterVol;
    
    finalSig[0] = 0.f;
    finalSig[1] = 0.f;
    }
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
#if PREPMODE
    if(key >= 48 && key <= 53){

        objectNumber = key - 48;
        avPrep.loadExamples(objectNumber);
    }
#endif
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
