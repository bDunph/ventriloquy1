#include "ofApp.h"
#include <random>

//--------------------------------------------------------------
void ofApp::setup(){
    
    //******* Midi Setup ********//
    
//    midiIn.listPorts();
//    midiIn.openPort(0);
//    midiIn.ignoreTypes(false, false, false);
//    midiIn.addListener(this);
//    midiIn.setVerbose(true);
//
//    x_val = 0;
//    y_val = 0;
//    z_val = 0;
//    val = 0;
    
    //********** Gui Global Params ***********//
    
//    camGui.setup();
//    camGui.setPosition(0, ofGetWindowHeight() * .1);
//    camGui.add(camX.setup("camX", 0.0f, -1.0f, 1.0f));
//    camGui.add(camY.setup("camY", 0.0f, -1.0f, 1.0f));
//    camGui.add(camZ.setup("camZ", 0.0f, -1.0f, 1.0f));
//
//    lightGui.setup();
//    lightGui.setPosition(0, ofGetWindowHeight()*0.6);
//    lightGui.add(lightColR.setup("lightColR", 1.f, 0.f, 1.f));
//    lightGui.add(lightColG.setup("lightColG", 1.f, 0.f, 1.f));
//    lightGui.add(lightColB.setup("lightColB", 1.f, 0.f, 1.f));
//    lightGui.add(ambColR.setup("ambColR", 0.1f, 0.f, 1.f));
//    lightGui.add(ambColG.setup("ambColG", 0.1f, 0.f, 1.f));
//    lightGui.add(ambColB.setup("ambColB", 0.1f, 0.f, 1.f));
//    lightGui.add(specColR.setup("specColR", 0.1f, 0.f, 1.f));
//    lightGui.add(specColG.setup("specColG", 0.1f, 0.f, 1.f));
//    lightGui.add(specColB.setup("specColB", 0.1f, 0.f, 1.f));
//    lightGui.add(lightPow.setup("lightPow", 397000.f, 100000.f, 10000000.f));
//    lightGui.add(lightPosX.setup("lightPosX", 0.f, -1000.f, 1000.f));
//    lightGui.add(lightPosY.setup("lightPosY", 0.f, -1000.f, 1000.f));
//    lightGui.add(lightPosZ.setup("lightPosZ", -780.f, -1000.f, 1000.f));
//    lightGui.add(blurAmnt.setup("blurAmnt", .001f, 0.f, .01f));
//
//    volGui.setup();
//    volGui.setPosition(0, 0);
//    volGui.add(masterVol.setup("masterVol", 0.5, 0.0, 1.0));

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
#ifdef PREPMODE
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
    
#ifdef PREPMODE
    avPrep.avSetup();
#endif
    
#ifdef PERFORMANCEMODE
    for(int i = 0; i < NUMAVS; i++){
        av[i].avSetup();
        av[i].gui.loadFromFile("/Users/bryandunphy/Projects/of_v0.11.0_osx_release/apps/myApps/ventriloquy1/bin/data/secondDraft_composition_180320/section"+ofToString(i)+")/reg"+ofToString(i)+"_obj0_mainGui.xml");
        av[i].guiRW.loadFromFile("/Users/bryandunphy/Projects/of_v0.11.0_osx_release/apps/myApps/ventriloquy1/bin/data/secondDraft_composition_180320/section"+ofToString(i)+"/reg"+ofToString(i)+"_obj0_guiRW.xml");
        av[i].reg.readJSON("/Users/bryandunphy/Projects/of_v0.11.0_osx_release/apps/myApps/ventrilqoy1/bin/data/secondDraft_composition_180320/trainedModels/2ndDraftReg"+ofToString(i)+".JSON");
//        avToggle[i] = false;
    }
#endif
//    av0.avSetup();
//    av0.gui.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section0/reg0_obj0_mainGui.xml");
//    av0.guiRW.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section0/reg0_obj0_guiRW.xml");
//    av0.reg.readJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/trainedModels/1stDraftReg0.JSON");
//
//    av1.avSetup();
//    av1.gui.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section1/reg1_obj0_mainGui.xml");
//    av1.guiRW.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section1/reg1_obj0_guiRW.xml");
//    av1.reg.readJSON("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/trainedModels/1stDraftReg1.JSON");

//    av0Toggle = true;
//    av1Toggle = false;
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    //*********** Maxim *****************//
    
    ofSoundStreamStop();
    ofSoundStreamClose();
    
    //************ Midi **************//
    
    // clean up
//    midiIn.closePort();
//    midiIn.removeListener(this);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //************ Update Global Params **************//
    
//    float updatedGlobalParams[] = {camX, camY, camZ, lightColR, lightColG, lightColB, ambColR, ambColG, ambColB, specColR, specColG, specColB, lightPow, lightPosX, lightPosY, lightPosZ, blurAmnt};
//
//    float *globParamsPtr = &updatedGlobalParams[0];
//
////    avPrep.updateGlobalParams(globParamsPtr);
//    if(av0Toggle){
//    av0.updateGlobalParams(globParamsPtr);
//    }
//
//    if(av1Toggle){
//    av1.updateGlobalParams(globParamsPtr);
//    }
    
    fbo1.begin();
    ofClear(0, 0, 0);
    fbo1.end();

    fbo2.begin();
    ofClear(0, 0, 0);
    fbo2.end();
    
    //**** midi positions ****//
    
//    val = midiMessage.value;
//
//    if(val != 0){
//        switch (midiMessage.control) {
//
//            case 1: {
//                r = ofMap(val, 0, 127, 0, 255);
//                break;
//            }
//
//            case 2: {
//                g = ofMap(val, 0, 127, 0, 255);
//                break;
//            }
//
//            case 3: {
//                b = ofMap(val, 0, 127, 0, 255);
//                break;
//            }
//
//            case 4: {
//                a = ofMap(val, 0, 127, 0, 255);
//                break;
//            }
//
//#ifdef PSMOVE_OFF
//            case 13: {
//                x_val+=10;
//                if(x_val > ofGetWindowWidth()){
//                    x_val = ofGetWindowWidth();
//                }
//                break;
//            }
//
//            case 9: {
//                x_val-=10;
//                if(x_val < 0){
//                    x_val = 0;
//                }
//                break;
//            }
//
//            case 14: {
//                y_val+=10;
//                if(y_val > ofGetWindowHeight()){
//                    y_val = ofGetWindowHeight();
//                }
//                break;
//            }
//
//            case 10: {
//                y_val-=10;
//                if(y_val < 0){
//                    y_val = 0;
//                }
//                break;
//            }
//
//            case 15: {
//                z_val+=10;
//                if(z_val > 1000){
//                    z_val = 1000;
//                }
//                break;
//            }
//
//            case 11: {
//                z_val-=10;
//                if(z_val < 1){
//                    z_val = 1;
//                }
//                break;
//            }
//#endif
//        }
//    }
    
    //**** PSMOVE ****//
#ifdef PSMOVE_ON
    
    tracker.update();
    
    camX = ofMap(tracker.moveXPos, -5.0, 5.0, -1.0, 1.0);
    camY = ofMap(tracker.moveYPos, -4.0, 4.0, -1.0, 1.0);
    camZ = ofMap(tracker.moveZPos, -1.0, -40.0, -1.0, 1.0);
    blurAmnt = ofMap(tracker.wOrientation, -1.0, 1.0, 0.0, 0.01);
#ifdef PREPMODE
    if(tracker.rand){
        avPrep.randomParams();
//        globalRandParams();
    }

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
    
#elif defined PSMOVE_OFF
    
    //*** recording ***//
    
    if (recording) {
        avPrep.trainingExamples(x_val, y_val, z_val);
    }
    
    //**** trained ****//
    
    if (trained || loaded) {
        avPrep.trainedOutput(x_val, y_val, z_val);
        av2.trainedOutput(x_val, y_val, z_val);
        
    }
    
    unsigned int triggerVal = 0;
    
#endif
    
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
//    rawCamPos = ofVec3f(camX, camY, camZ);

#ifdef PREPMODE
    avPrep.visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
        loaded = avPrep.readWrite();
#endif
    
#ifdef PERFORMANCEMODE
    
    

    for(int i = 0; i < NUMAVS; i++){
        
        if(tracker.obj[0]){
            av[0].texColR = 63;
            av[0].texColG = 17;
            av[0].texColB = 0;
            av[0].shape = 1;
//            av[0].synth = 1;
            av[0].waveform = 0;
//            av[0].delaySig = 1;
            av[0].trainedOutput(tracker.moveXPos, tracker.moveYPos, tracker.moveZPos);
            av[0].visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
        }
        
        if(tracker.obj[1]){
            av[1].texColR = 47;
            av[1].texColG = 48;
            av[1].texColB = 47;
            av[1].shape = 0;
            av[0].waveform = 1;
//            av[1].synth = 0;
//            av[1].controlVoltage = 100;
//            av[1].delaySig = 0;
            av[1].trainedOutput(tracker.moveXPos, tracker.moveYPos, tracker.moveZPos);
            av[1].visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
        }
        
        if(tracker.obj[2]){
            av[2].texColR = 63;
            av[2].texColG = 17;
            av[2].texColB = 0;
            av[2].shape = 0;
//            av[2].synth = 1;
            av[2].waveform = 2;
//            av[2].delaySig = 1;
            av[2].trainedOutput(tracker.moveXPos, tracker.moveYPos, tracker.moveZPos);
            av[2].visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
        }
        
//        if(tracker.obj[3]){
//            av[3].texColR = 60;
//            av[3].texColG = 60;
//            av[3].texColB = 60;
//            av[3].shape = 1;
////            av[3].synth = 1;
//            av[3].waveform = 1;
////            av[3].delaySig = 1;
//            av[3].trainedOutput(tracker.moveXPos, tracker.moveYPos, tracker.moveZPos);
//            av[3].visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
//        }
    }
    
#endif
//    if(av0Toggle){
//        av0.visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
//    }
//
//    if(av1Toggle){
//        av1.visual(triggerVal, tracker.controllerModelViewMat, cameraSpace.getPtr(), camPos, lightPos);
//    }
    


//    globalReadWrite();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    ofBackground(0, 0, 0);
    
    
//    ofEnableAlphaBlending();
    
    ofEnableDepthTest();
    
    fbo1.begin();
    cam.begin();
    
#ifdef PSMOVE_ON
    
    //***** Draw Objects *****//
#ifdef PREPMODE
        avPrep.drawVisual(lightCol, ambCol, specCol, lightPow);
#endif
    
#ifdef PERFORMANCEMODE
    for(int i = 0; i < NUMAVS; i++){
        if(tracker.obj[i]){
            av[i].drawVisual(lightCol, ambCol, specCol, lightPow);
        }
    }
#endif
    
//    if(av0Toggle){
//        av0.drawVisual(lightCol, ambCol, specCol, lightPow);
//    }
//
//    if(av1Toggle){
//        av1.drawVisual(lightCol, ambCol, specCol, lightPow);
//    }
    
#endif
    
#ifdef PSMOVE_OFF
    
    //    avPrep.drawVisual();
    if(av0Toggle){
        av0.drawVisual();
    }
    
    if(av1Toggle){
        av1.drawVisual();
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
        
#ifdef PREPMODE
        s << "trained: " << trained;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.1, 10);
        s.str("");
        s << "recording: " << recording;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.3, 10);
        s.str("");
#endif
        
#ifdef PSMOVE_ON
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
#endif
        
#ifdef PSMOVE_OFF
        s << "xPos: " << x_val;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.5, 10);
        s.str("");
        s << "yPos: " << y_val;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.5, 20);
        s.str("");
        s << "zPos: " << z_val;
        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.5, 30);
        s.str("");
#endif
        
//        s << "velocity: " << val;
//        ofDrawBitmapString(s.str(), ofGetWindowWidth()*0.8, 10);
//        s.str("");
#ifdef PREPMODE
        avPrep.drawGuiAndGuiRW();
#endif
        
#ifdef PERFORMANCEMODE
        for(int i = 0; i < NUMAVS; i++){
            if(tracker.obj[i]){
                av[i].drawGuiAndGuiRW();
            }
        }
#endif
        
//        if(av0Toggle){
//            av0.drawGuiAndGuiRW();
//        }
//
//        if(av1Toggle){
//            av1.drawGuiAndGuiRW();
//        }
        //        av.drawCamAndLightGui();
        volGui.draw();
        camGui.draw();
        lightGui.draw();
    }
    
}

//_____________________________________________________________
//void ofApp::globalRandParams(){
//
//    std::random_device rd;
//    std::default_random_engine generator(rd());
//    std::uniform_real_distribution<double> distribution(-1.0, 1.0);
//
//    camX = distribution(generator);
//    if (camX < -1.0f){
//        camX = -1.0f;
//    } else if (camX > 1.0f){
//        camX = 1.0f;
//    }
//
//
//    camY = distribution(generator);
//    if (camY < -1.0f){
//        camY = -1.0f;
//    } else if (camY > 1.0f){
//        camY = 1.0f;
//    }
//
//
//    camZ = distribution(generator);
//    if (camZ < -1.0f){
//        camZ = -1.0f;
//    } else if (camZ > 1.0f){
//        camZ = 1.0f;
//    }
//
//    blurAmnt = abs(.01 * distribution(generator));
//    if (blurAmnt <= .001){
//        blurAmnt = .001;
//    } else if (blurAmnt >= .01){
//        blurAmnt = .01;
//    }
//
//}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
#ifdef PREPMODE
        synthOutPrep = avPrep.audio(blurAmnt);
        prepChannel = *(synthOutPrep);
        prepPanPtr = avPrep.panner();
        prepPanVal = *(prepPanPtr);
        prepMix.stereo(prepChannel, prepChannelOut, prepPanVal);
#endif
        
#ifdef PERFORMANCEMODE
        for(int j = 0; j < NUMAVS; j++){
            if(tracker.obj[j]){
                synthOut[j] = av[j].audio(blurAmnt);
                channel[j] = *(synthOut[j]);
                panning[j] = av[j].panner();
                panner[j] = *(panning[j]);
                channelMix[j].stereo(channel[j], channelOut[j], panner[j]);
            }
        }
#endif
        
//        if(av0Toggle){
//            synthOut1 = av0.audio();
//            channel1 = *(synthOut1);
//            panning1 = av0.panner();
//            panner1 = *(panning1);
//            mymix1.stereo(channel1, channel1Out, panner1);
//        }
//
//        if(av1Toggle){
//            synthOut2 = av1.audio();
//            channel2 = *(synthOut2);
//            panning2 = av1.panner();
//            panner2 = *(panning2);
//            mymix2.stereo(channel2, channel2Out, panner2);
//        }
        
#ifdef PREPMODE
        finalSig[0] += prepChannelOut[0];
        finalSig[1] += prepChannelOut[1];
#endif
        
#ifdef PERFORMANCEMODE
        
        for(int j = 0; j < NUMAVS; j++){
            finalSig[0] += channelOut[j][0];
            finalSig[1] += channelOut[j][1];
        }
        
        if(tracker.obj[3]){
            float volDown = ofMap(tracker.wOrientation, -1.0, 1.0, 0.0, 1.0);
            masterVol = volDown;
        }
#endif
        
        
        /*** Limiter ***/
        
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
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    
    // make a copy of the latest message
//    midiMessage = msg;
}

//--------------------------------------------------------------
//void ofApp::globalReadWrite(){
//
//    if(saveExample) {
//
//        camGui.saveToFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/reg1_obj5_camGui.xml");
//        lightGui.saveToFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/reg1_obj5_lightGui.xml");
//
//    }
//
//    if(loadExample) {
//
//        camGui.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section1/reg0_obj5_camGui.xml");
//        lightGui.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section1/reg0_obj5_lightGui.xml");
//
//    }
//
//}

//--------------------------------------------------------------
//void ofApp::globalLoadExamples(int objectNumber){

//    if(avToggle){
//    camGui.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section0/reg0_obj"+ofToString(objectNumber)+"_camGui.xml");
//    lightGui.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section0/reg0_obj"+ofToString(objectNumber)+"_lightGui.xml");
//    } else if(!avToggle){
//        camGui.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section1/reg1_obj"+ofToString(objectNumber)+"_camGui.xml");
//        lightGui.loadFromFile("/Users/bryandunphy/Documents/code/of_v0.9.8_osx_release/apps/myApps/regMap/bin/data/ventriloquy_regs/firstDraft_composition_180312/section1/reg1_obj"+ofToString(objectNumber)+"_lightGui.xml");
//    }
//}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    
#ifdef PREPMODE
    if(key >= 48 && key <= 53){

        objectNumber = key - 48;
        avPrep.loadExamples(objectNumber);
    }
#endif

    switch (key) {
//#ifdef PERFORMANCEMODE
//            /*q*/
//        case 113: {
//            avToggle[0] = !avToggle[0];
//            break;
//        }
//
//            /*w*/
//        case 119: {
//            avToggle[1] = !avToggle[1];
//            break;
//        }
//
//            /*a*/
//        case 97: {
//            avToggle[2] = !avToggle[2];
//            break;
//        }
//            /*s*/
//        case 115: {
//            avToggle[3] = !avToggle[3];
//            break;
//        }
//#endif
            
//            /*l*/
//        case 108: {
//            loadExample = true;
//            break;
//        }
//            /*s*/
//        case 115: {
//            saveExample = true;
//            break;
//        }
//#ifdef PSMOVE_OFF
//            /*r*/
//        case 114: {
//            recording = true;
//            break;
//        }
//            /*t*/
//        case 116: {
//            trained = avPrep.trainModel();
//            break;
//        }
//            /*space*/
//        case 32: {
//            avPrep.randomParams();
//            globalRandParams();
//            break;
//        }
//            /*q*/
//        case 113: {
//            drawGui = !drawGui;
//            break;
//        }
//#endif
    }

    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    //********** Rapidmix (code from oF example rapidAPI_006) ************//
#ifdef PSMOVE_OFF
    switch (key) {
        case 114:
            recording = false;
            break;
    }
#endif
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    //********** Rapidmix (code from oF example rapidAPI_006) ************//
#ifdef PSMOVE_OFF
    mouseDragged(x, y, button);
#endif
    
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
