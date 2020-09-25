//
//  avObject.hpp
//  regMap
//
//  Created by Bryan Dunphy on 20/02/2017.
//
//
#ifndef avObject_hpp
#define avObject_hpp

#include <stdio.h>
#include <random>
#include <vector>
#include <math.h>
#include "ofxRapidLib.h"
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

typedef hannWinFunctor grainPlayerWin;

class avObject {
public:
    
    avObject();
    ~avObject();

    void avSetup();
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
    void drawGuiAndGuiRW();
    
    //********* elements accessed from ofApp av1, av2 etc*******//
    ofxPanel gui;
    ofxPanel guiRW;
    rapidlib::regression reg;
    ofxIntSlider texColR;
    ofxIntSlider texColG;
    ofxIntSlider texColB;
    ofxIntSlider shape;
    ofxIntSlider waveform;
    ofxIntSlider controlVoltage;
    unsigned int shapeSize;
    
private:
    
    //************ Global Params ***************//
    ofxIntSlider xTrans;
    ofxIntSlider yTrans;
    ofxIntSlider zTrans;
    ofxIntSlider noiseSpeed;
    ofxFloatSlider dispH;
    ofxFloatSlider visPulse;
    ofxIntSlider size;
    ofxIntSlider vertices;
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
    ofxButton saveParams;
    ofxButton r1;
    ofxButton w1;
    
    //********* Visual ***********//
    ofTexture tex;
    unsigned char texData[256 * 256 * 4];
    unsigned char * texPtr;
    ofBoxPrimitive box;
    ofSpherePrimitive sphere;
    ofShader cubeShader;
	ofShader sphereShader;
    maxiOsc noiseFreq;
    double speed;
    ofNode lights[NUMLIGHTS];
    ofVec4f globalLightPos[NUMLIGHTS];
    ofVec4f cameraSpaceLightPos[NUMLIGHTS];
    ofImage img;
    ofImage normMap;
    ofVec3f objPos;
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
    std::vector<rapidlib::trainingExample> trainingSet;
    bool result;
    bool isTrained;
    
    //************ PS MOVE *************//
    ofMatrix4x4 camModelViewMat;
    ofMatrix4x4 controllerModelViewMatrix;
    ofMatrix4x4 combinedModelView;
    unsigned int trigger;
};
#endif /* avObject_hpp */
