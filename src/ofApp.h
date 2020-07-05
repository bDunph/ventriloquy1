#pragma once

#include <ofMain.h>
#include <ofxMaxim.h>
#include <maximilian.h>
#include <ofxGui.h>
#include <ofxXmlSettings.h>
#include <ofxMidi.h>

#include <stdio.h>

#include <time.h>
#include <assert.h>

#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"

#include "avObject.hpp"
#include "psMoveTrackerClass.hpp"

//#define PREPMODE 3
#define PERFORMANCEMODE 5
#define NUMAVS 3
#define PSMOVE_ON 1
//#define PSMOVE_OFF 2

class ofApp : public ofBaseApp, ofxMidiListener {
    
public:
    void setup();
    void exit();
    void update();
    void draw();
    void globalRandParams();
    //******** Maxim **********//
    void audioOut(float * output, int bufferSize, int nChannels);
    
    //****** Midi *********//
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    void globalReadWrite();
    void globalLoadExamples(int objectNumber);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //********** Global Params **************//
    
    ofxPanel camGui;
    ofxPanel lightGui;
    ofxPanel volGui;
    
    ofxFloatSlider masterVol;
    
    ofxFloatSlider camX;
    ofxFloatSlider camY;
    ofxFloatSlider camZ;
    
    ofxFloatSlider lightColR;
    ofxFloatSlider lightColG;
    ofxFloatSlider lightColB;
    ofxFloatSlider ambColR;
    ofxFloatSlider ambColG;
    ofxFloatSlider ambColB;
    ofxFloatSlider specColR;
    ofxFloatSlider specColG;
    ofxFloatSlider specColB;
    ofxFloatSlider lightPow;
    ofxFloatSlider lightPosX;
    ofxFloatSlider lightPosY;
    ofxFloatSlider lightPosZ;
    ofxFloatSlider blurAmnt;
    ofVec3f lightCol;
    ofVec3f ambCol;
    ofVec3f specCol;
    ofVec3f lightPos;
//    ofVec3f rawCamPos;
//    bool saveExample;
//    bool loadExample;
    int objectNumber;
    //************ Visuals **********//
    
    bool drawGui;
    ofEasyCam cam;
    ofFbo fbo1;
    ofFbo fbo2;
    ofShader blurX;
    ofShader blurY;
    ofVec3f camPos;
    ofMatrix4x4 cameraSpace;
    //*********** Maxim *****************//
    
#ifdef PREPMODE
    maxiMix prepMix;
    double* synthOutPrep;
    double prepChannel;
    double* prepPanPtr;
    double prepPanVal;
    double prepChannelOut[2];
    avObject avPrep;
    bool loaded;
    bool trained;
    bool recording;
#endif
    
    double sampleRate, bufferSize;
//    double * synthOut;
//    double * synthOut1;
//    double * synthOut2;
    
#ifdef PERFORMANCEMODE

    double* synthOut[NUMAVS];
    double* panning[NUMAVS];
    double channel[NUMAVS];
    double panner[NUMAVS];
    maxiMix channelMix[NUMAVS];
    double channelOut[NUMAVS][2];
    
    avObject av[NUMAVS];
//    bool avToggle[NUMAVS];
#endif
//    double * panning;
//    double * panning1;
//    double * panning2;
    double finalSig[2];
    double fullSig;
    
//    maxiMix mymix1;
//    maxiMix mymix2;
    
    
//    double outputs[2];
    maxiEnv lim;
    bool limTrig;
    double envSig;
//    double channelOut[2];
//    double synthMix;
//    double channel1, channel2;
//    double panVals;
//    double panner1, panner2;
//    double channel1Out[2];
//    double channel2Out[2];
    
    //********** Rapidmix ************//
    
    
    
    
//    int numVoices;
    
    //************ Midi *************//

//    ofxMidiIn midiIn;
//    ofxMidiMessage midiMessage;
//    int x_val;
//    int y_val;
//    int z_val;
//    int val;
//    int r, g, b, a;
    
#ifdef PSMOVE_ON
    
    //********** PS Move ***********//
    
    psMoveTrackerClass tracker;
    
#endif
    
};
