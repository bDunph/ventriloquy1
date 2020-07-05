//
//  psMoveTrackerClass.hpp
//  regMap
//
//  Created by Bryan Dunphy on 02/03/2018.
//

/**
 * PS Move API - An interface for the PS Move Motion Controller
 * Copyright (c) 2012 Thomas Perl <m@thp.io>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 **/

#ifndef psMoveTrackerClass_hpp
#define psMoveTrackerClass_hpp

#include <stdio.h>

#include <time.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "psmove_config.h"
#include "psmove.h"
#include "psmove_tracker.h"
#include "psmove_fusion.h"
#include "psmoveapi.h"

class psMoveTrackerClass {
public:
    psMoveTrackerClass();
    ~psMoveTrackerClass();
    void update();
    bool rand;
    bool train;
    bool drawInterface;
    bool record;
    float moveXPos, moveYPos, moveZPos;
    float wOrientation, xOrientation, yOrientation, zOrientation;
    float* controllerModelViewMat;
    unsigned int trig;
    bool obj[4];
    
private:
    PSMoveFusion *m_fusion;
    PSMove **m_moves;
    PSMoveTracker *m_tracker;
    PSMoveTrackerSettings settings;
    int m_count;
    int result;
};

#endif /* psMoveTrackerClass_hpp */
