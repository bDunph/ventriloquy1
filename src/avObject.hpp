//
//  avObject.hpp
//  regMap
//
//  Created by Bryan Dunphy on 20/02/2017.
//
//

//MY NOTES
// Remove redundant or unused variables
//Use vector rather than 3 numbers
//magic numbers, use constants instead
// dont have function lonfer than a page
//sub divide your functions. A function should be no more than a page
// you can find programs than auto generate docs
//
//then do a class diagram (UML)
//Make empty classes
//move variables and functions piece by piece.

// CLASSES
// - Input class
//- GUI Class
// Audio Class
//- NNClass
// SHape
//GraphicsWorld


#ifndef avObject_hpp
#define avObject_hpp

#include <stdio.h>
#include <random>
#include <vector>
#include <math.h>


#include "regression.h"
#include "modelSet.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "ofMain.h"
#include "ofxMaxim.h"
#include "maximilian.h"
#include "maxiGrains.h"
#include "psMoveTrackerClass.hpp"


#define NUMTAPS 2
#define MESHES 2
#define numParams 21
#define numRandParams 22
#define NUMLIGHTS 2
#define PSMOVE_ON 1
//#define PSMOVE_OFF 1

typedef hannWinFunctor grainPlayerWin;

class avObject {
public:
    
    avObject();
    ~avObject();

    void avSetup();
//    void camAndLights();
//    void updateGlobalParams(float *paramPtr);
    void visual(const unsigned int triggerValue, float* moveModelView, float* camModelViewMatPtr, ofVec3f camPos, ofVec3f lightPos);
    void drawVisual(ofVec3f lightCol, ofVec3f ambCol, ofVec3f specCol, float lightPow);
    double * audio(float blur);
    double * panner();
    void randomParams();
    void trainingExamples(float x, float y, float z);
    bool trainModel();
    void trainedOutput(float x, float y, float z);
    bool readWrite();
    void loadExamples(const int objNum);
    bool loadModels(const int modelNum);
    void drawGuiAndGuiRW();
//    bool setUpFMSynthParams(std::vector<double> output);
//    void setupSubSynth(std::vector<double> output);
//    void drawCamAndLightGui();
//    void finish();
    
    //********* elements accessed from ofApp av1, av2 etc*******//
    ofxPanel gui;
    ofxPanel guiRW;
    regression reg;
    ofxIntSlider texColR;
    ofxIntSlider texColG;
    ofxIntSlider texColB;
    ofxIntSlider shape;
//    ofxToggle synth;
    ofxIntSlider waveform;
//    ofxToggle delaySig;
    ofxIntSlider controlVoltage;
    unsigned int shapeSize;
    
private:
    
//    //************ Global Params ***************//
//
//    float camX, camY, camZ;
//    float lightColR, lightColG, lightColB;
//    float ambColR, ambColG, ambColB;
//    float specColR, specColG, specColB;
//    float lightPow;
//    float lightPosX, lightPosY, lightPosZ;
//    float blurAmnt;
    
    //*************** Gui **************//
    
    
//    ofxPanel camGui;
//    ofxPanel lightGui;
    
    //*** visuals ***//
    
//    ofxFloatSlider camX;
//    ofxFloatSlider camY;
//    ofxFloatSlider camZ;
//    
//    ofxFloatSlider lightColR;
//    ofxFloatSlider lightColG;
//    ofxFloatSlider lightColB;
//    ofxFloatSlider ambColR;
//    ofxFloatSlider ambColG;
//    ofxFloatSlider ambColB;
//    ofxFloatSlider specColR;
//    ofxFloatSlider specColG;
//    ofxFloatSlider specColB;
//    ofxFloatSlider lightPow;
//    ofxFloatSlider lightPosX;
//    ofxFloatSlider lightPosY;
//    ofxFloatSlider lightPosZ;
//    ofxFloatSlider blurAmnt;

    ofxIntSlider xTrans;
    ofxIntSlider yTrans;
    ofxIntSlider zTrans;
    ofxIntSlider noiseSpeed;
    ofxFloatSlider dispH;
    ofxFloatSlider visPulse;
    ofxIntSlider size;
    ofxIntSlider vertices;
    
//    ofxToggle wireFrame;
//    ofxToggle texType;
    
    ofxIntSlider texColA;
    ofxFloatSlider brightness;
    
    //*** audio ***//
    
    
    ofxFloatSlider oscilFreq;
    ofxFloatSlider oscilAmp;
    ofxToggle FM;
    ofxToggle lfoOn;
    ofxFloatSlider lfoFreq;
    ofxIntSlider harmRatio;
    ofxFloatSlider modInd;
    
    ofxFloatSlider pulseDuty;
    ofxFloatSlider noiseFiltLowCut;
    ofxFloatSlider noiseFiltHiCut;
    ofxFloatSlider cf;
    ofxIntSlider q;
    ofxFloatSlider res;
    ofxIntSlider attack;
    ofxIntSlider decay;
    ofxIntSlider sustain;
    ofxIntSlider release;
    
    
    //********* Sub Synth *************//

//    ofxFloatSlider subFreq1;
//    ofxFloatSlider subFreq2;
    ofxIntSlider pole1Freq;
    ofxIntSlider pole2Freq;
    ofxIntSlider pole3Freq;
    ofxIntSlider pole4Freq;
    ofxFloatSlider pole1res;
    ofxFloatSlider pole2res;
    ofxFloatSlider pole3res;
    ofxFloatSlider pole4res;
    ofxIntSlider a1;
    ofxIntSlider d1;
    ofxIntSlider s1;
    ofxIntSlider rel1;
    ofxIntSlider a2;
    ofxIntSlider d2;
    ofxIntSlider s2;
    ofxIntSlider rel2;
    ofxIntSlider subEnv1CV;
    ofxIntSlider subEnv2CV;
    
    //*** read/write ***//

//    ofxIntSlider regNum;
    ofxButton saveParams;
//    ofxButton loadParams;
    ofxButton r1;
//    ofxButton r2;
//    ofxButton r3;
//    ofxButton r4;
//    ofxButton r5;
    ofxButton w1;
//    ofxButton w2;
//    ofxButton w3;
//    ofxButton w4;
//    ofxButton w5;
    
    //********* Visual ***********//
    
    ofTexture tex;
    unsigned char texData[256 * 256 * 4];
    unsigned char * texPtr;
    ofBoxPrimitive box;
    ofSpherePrimitive sphere;
    ofShader cubeShader;
//    ofEasyCam cam;
    
    maxiOsc noiseFreq;
    double speed;
    
//    ofNode light;
//    ofNode light2;
    ofNode lights[NUMLIGHTS];
//    ofMatrix4x4 psmoveModelView;
//    ofQuaternion controllerOrientation;
    ofVec4f globalLightPos[NUMLIGHTS];
//    ofVec4f globalLightPos2;
    ofVec4f cameraSpaceLightPos[NUMLIGHTS];
//    ofVec4f cameraSpaceLightPos2;
//    ofVec3f lightCol;
//    ofVec3f ambCol;
//    ofVec3f specCol;
    
    ofImage img;
//    ofTexture tex2;
    ofImage normMap;
    
//    ofFbo fbo1;
//    ofFbo fbo2;
//    ofShader blurX;
//    ofShader blurY;
//    ofVec3f camPos;
    
    
    ofVec3f objPos;
    
//    ofVec3f furthestPoint;

    double dist;
    double mappedDistVal;
    double distScale;
    double soundPower;
    double soundIntensity;
    double soundArea;
    double dbVal;
    double logCalc;
    double mappedVol;
    
    int texR, texG, texB, texA;
//    int objSel;

    ofColor objectRGB_col;
    float objectLightness;
    int lightness_freq_map;

    //*********** Audio **************//
    
    //********** Granular and FM Synths *************//

    maxiSample samp;
    
    maxiSample sample1;

    maxiOsc pulseGen1;
    maxiOsc pulseGen2;
    maxiOsc pulseGen3;
    maxiOsc pulseGen4;
    
    maxiOsc squareOsc1;
    maxiOsc squareOsc2;
    maxiOsc squareOsc3;
    maxiOsc squareOsc4;
    
    maxiOsc sineOsc1;
    maxiOsc sineOsc2;
    maxiOsc sineOsc3;
    maxiOsc sineOsc4;
    
    maxiOsc counter;
    maxiOsc mod;
    maxiOsc lfOsc;
    maxiOsc sawOsc1;
    maxiOsc sawOsc2;
    maxiOsc sawOsc3;
    maxiOsc sawOsc4;
    
    maxiFilter bassModLoPass;
    maxiFilter noiseFiltLow;
    maxiFilter noiseFiltHi;
    maxiFilter hiRes;
    maxiFilter loRes;
    maxiEnv ampEnv;
    maxiDelayline delay;
    
    maxiTimePitchStretch<grainPlayerWin, maxiSample> *gran;
    
    maxiTimePitchStretch<grainPlayerWin, maxiSample> *gran1, *gran2;
    
    double granVol;
    double grainSpeed;
    double grainLength;
    double grainSig;

    double grainSig1;

    double modulator;
    double harmonicity;
    double modAmp;
    double pulse1;
    double pulse2;
    double pulse3;
    double pulse4;
    
    double noiseFilter;
    double square1;
    double square2;
    double square3;
    double square4;
    
    double lfo;
    double sigMix;
    double lowPass;
    double hiPass;
    double band;
    double filteredSig;
    double amplitudeEnvelope;
    double envOutput;
    double gateOut;
    double hpc;
    double lpc;
    double hp;
    double lp;
    double delBoy;
    double delColl;
    int noteTrig;
    double outSig;
    
    double * multiOut;
    double * panOut;

    ofVec4f objPos_camSpace;
    double objPos_asPercentage_ofX_axis;
    double sine1;
    double sine2;
    double sine3;
    double sine4;
    
    double saw1;
    double saw2;
    double saw3;
    double saw4;
    
    //************* Sub Synth ***********//

    maxiOsc subOsc1;
    maxiOsc subOsc2;
    double subSig1;
    double subSig2;
    maxiFilter pole1;
    maxiFilter pole2;
    maxiFilter pole3;
    maxiFilter pole4;
    double pole1Out;
    double pole2Out;
    double pole3Out;
    double pole4Out;
    double subFilterOut;
    maxiEnv subADSR1;
    maxiEnv subADSR2;
    double ADSR1;
    double ADSR2;
    double subOut;
    maxiOsc env1osc;
    maxiOsc env2osc;
    int env1trigger;
    int env2trigger;
    double multOsc;
    double fourPoleOutput;
    double oscilOutEnv;
    maxiOsc subOsc1sympathetic1;
    maxiOsc subOsc2sympathetic1;
    double sympathetic1Osc1Out;
    double sympathetic1Osc2Out;
    
    //***************** AV Gui Params ************//
    
    double params[numParams];
    float randParams[numRandParams];
    
    //********** Rapidmix ************//
    
    
    std::vector<trainingExample> trainingSet;
    
    bool result;
    bool isTrained;
    
    //************ PS MOVE *************//
    
    ofMatrix4x4 camModelViewMat;
    
#ifdef PSMOVE_ON

    ofMatrix4x4 controllerModelViewMatrix;
    ofMatrix4x4 combinedModelView;
    
#endif
    
    unsigned int trigger;
    
    
};

#endif /* avObject_hpp */
